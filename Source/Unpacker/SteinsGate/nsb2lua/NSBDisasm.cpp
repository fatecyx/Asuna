#include "NSBDisasm.h"
#include "my_crtadd.cpp"
#include "my_api.cpp"

#include "Info.h"

CNsbDisassembler::CNsbDisassembler()
{
    m_pInfoMap = NULL;
    ZeroMemory(&m_FuncRecord, sizeof(m_FuncRecord));
    ZeroMemory(&m_NsbRecord, sizeof(m_NsbRecord));
}

CNsbDisassembler::~CNsbDisassembler()
{
    Reset();
    m_mem.SafeFree(&m_pInfoMap);
}

VOID CNsbDisassembler::Reset()
{
    m_mem.SafeFree(&m_FuncRecord.pMap);
    m_mem.SafeFree(&m_NsbRecord.pInstruction);
    ZeroMemory(&m_FuncRecord, sizeof(m_FuncRecord));
    ZeroMemory(&m_NsbRecord, sizeof(m_NsbRecord));
}

BOOL CNsbDisassembler::DisassembleFile(PWCHAR pszNsbFile, PWCHAR pszScriptFile /* = NULL */)
{
    BOOL        Result;
    PVOID       pvMapBuffer, pvNsbBuffer;
    ULONG       FileSize;
    WCHAR       szFile[MAX_PATH], *pszExtension;
    CFileDisk   file;

    if (!IsPathExistsW(pszNsbFile))
        return FALSE;

    lstrcpyW(szFile, pszNsbFile);
    pszExtension = findextw(szFile);
    lstrcpyW(pszExtension, MAKE_WSTRING(NAME_FUNCTION_MAP_EXTENSION));

    if (!file.Open(szFile))
        return FALSE;

    Reset();

    FileSize = file.GetSize();
    pvMapBuffer = m_mem.Alloc(FileSize);
    if (pvMapBuffer == NULL)
        return FALSE;

    pvNsbBuffer = NULL;
    Result = FALSE;
    LOOP_ONCE
    {
        if (!file.Read(pvMapBuffer))
            break;

        if (!ParseFunctionMap(pvMapBuffer, FileSize))
            break;

        lstrcpyW(pszExtension, MAKE_WSTRING(NAME_N2_SCRIPT_BIN_EXTENSION));
        if (!file.Open(szFile))
            break;

        FileSize = file.GetSize();
        pvNsbBuffer = m_mem.Alloc(FileSize);
        if (pvNsbBuffer == NULL)
            break;

        if (!file.Read(pvNsbBuffer))
            break;

        if (!ParseN2ScriptBin(pvNsbBuffer, FileSize))
            break;

        if (pszScriptFile == NULL)
        {
            pszScriptFile = szFile;
            lstrcpyW(pszExtension, MAKE_WSTRING(NAME_SCRIPT_EXTENSION));
        }

        Result = DumpToScript(pszScriptFile);
    }

    m_mem.Free(pvNsbBuffer);
    m_mem.Free(pvMapBuffer);
    return Result;
}

BOOL CNsbDisassembler::ParseFunctionMap(PVOID pvBuffer, ULONG BufferSize)
{
    PBYTE                pbBuffer, pbEnd;
    PN2_FUNCTION_MAP       *pMap;

    pbBuffer = (PBYTE)pvBuffer;
    pbEnd    = pbBuffer + BufferSize;

    m_FuncRecord.MaxCount = BufferSize / MIN_FUNCTION_MAP_SIZE;
    if (m_FuncRecord.MaxCount == 0)
        return FALSE;

    pMap = (PN2_FUNCTION_MAP * )m_mem.Alloc(m_FuncRecord.MaxCount * sizeof(*pMap), HEAP_ZERO_MEMORY);
    if (pMap == NULL)
        return FALSE;

    m_FuncRecord.Count = 0;
    m_FuncRecord.pMap  = pMap;
    while (pbBuffer < pbEnd)
    {
        *pMap = (PN2_FUNCTION_MAP)pbBuffer;
        pbBuffer += (*pMap)->FuncName.Length + sizeof((*pMap)->Offset) + sizeof((*pMap)->FuncName.Length);
        ++pMap;
        ++m_FuncRecord.Count;
    }

    for (ULONG i = m_FuncRecord.Count; i; --i)
    {
        pMap = m_FuncRecord.pMap;
        for (ULONG j = i - 1; j; ++pMap, --j)
        {
            if (pMap[0]->Offset > pMap[1]->Offset)
                Swap(pMap[0], pMap[1]);
        }
    }

    return TRUE;
}

BOOL CNsbDisassembler::ParseN2ScriptBin(PVOID pvBuffer, ULONG BufferSize)
{
    PBYTE                   pbBuffer, pbEnd;
    INSTRUCTION_ENTRY      *pEntry;

    pbBuffer = (PBYTE)pvBuffer;
    pbEnd    = pbBuffer + BufferSize;

    m_NsbRecord.MaxCount = BufferSize / MIN_INSTRUCTION_INFO;
    if (m_NsbRecord.MaxCount == 0)
        return FALSE;

    pEntry = (INSTRUCTION_ENTRY *)m_mem.Alloc(m_NsbRecord.MaxCount * sizeof(*pEntry));
    if (pEntry == NULL)
        return FALSE;

    m_NsbRecord.Count     = 0;
    m_NsbRecord.pInstruction = pEntry;
    while (pbBuffer < pbEnd)
    {
        ULONG Count;

        pEntry->Offset = (ULONG_PTR)pbBuffer - (ULONG_PTR)pvBuffer;
        pEntry->pInstruction = (PN2_INSTRUCTION_INFO)pbBuffer;

        Count = pEntry->pInstruction->ParamCount;
        pbBuffer += sizeof(pEntry->pInstruction->Index) + sizeof(pEntry->pInstruction->OP) + sizeof(pEntry->pInstruction->ParamCount);

        if (Count != 0) do
        {
            pbBuffer += 4 + *(PULONG)pbBuffer;
        } while (--Count);

        ++pEntry;
        ++m_NsbRecord.Count;
    }

    return TRUE;
}

BOOL CNsbDisassembler::WriteText(CFileDisk &file, PCHAR pBuffer, LPCSTR pszFormat, ...)
{
    LONG Length;
    va_list args;

    va_start(args, pszFormat);

    Length = vsprintf(
                pBuffer,
                pszFormat,
                args);

    if (Length == -1)
        return FALSE;

    return file.Write(pBuffer, Length);
}

#define WriteScr(...) { if (!WriteText(file, Buffer2, __VA_ARGS__)) return FALSE; }

PCHAR CopyString(PCHAR Buffer, PCHAR String, ULONG Length, BOOL bSplieMultiLine = FALSE)
{
    PCHAR p = Buffer;

    if (bSplieMultiLine)
    {
        *(PUSHORT)Buffer = TAG2('[[');
        Buffer += 2;
    }

    if (Length == 0)
    {
        *Buffer++ = 0;
        if (bSplieMultiLine)
            *(PUSHORT)Buffer = TAG2('[[');

        return p;
    }

    if (bSplieMultiLine)
    {
        *Buffer++ = '\r';
        *Buffer++ = '\n';
    }

    do
    {
        CHAR ch = *String++;

        switch (ch)
        {
            case '\n':
                if (bSplieMultiLine)
                {
                    *Buffer++ = '\r';
                    *Buffer++ = '\n';
//                    *(PULONG)Buffer = '    ';
//                    Buffer += 4;
                    continue;
                }

                *Buffer++ = '\\';
                ch = 'n';
/*
                if (bSplieMultiLine && *String != 0)
                {
                    *Buffer++ = ch;
                    *Buffer++ = '\'';
                    *(PULONG)Buffer = TAG4(' ...');
                    Buffer += 4;
                    *Buffer++ = '\r';
                    *Buffer++ = '\n';
                    *Buffer++ = ' ';
                    *(PULONG)Buffer = TAG4('   \'');
                    Buffer += 4;
                    continue;
                }
*/
                break;

//            case '"':
            case '\'':
            case '\\':
                *Buffer++ = '\\';
                break;

            default:
                if ((BYTE)ch < ' ')
                {
                    printf("%02X\n", (BYTE)ch);
                    getch();
                }
                break;
        }

        *Buffer++ = ch;
        if (ch < 0)
        {
            ch = *String++;
            if (ch == 0)
                break;

            *Buffer++ = ch;
            --Length;
        }

    } while (--Length);

    if (bSplieMultiLine)
    {
        *(PUSHORT)Buffer = TAG2(']]');
        Buffer += 2;
    }

    *Buffer = 0;

    return p;
}

BOOL CNsbDisassembler::CreateBaseScript(PWCHAR pszFileName, PCHAR Buffer2)
{
    if (IsPathExistsW(pszFileName))
        return TRUE;

    CFileDisk           file;
    INSTRUCTION_INFO   *pInfo;

    if (!file.Create(pszFileName))
        return FALSE;

    WriteScr("%s", szBaseFunc);

    pInfo = g_InsInfo;
    for (ULONG Count = countof(g_InsInfo); Count; ++pInfo, --Count)
    {
        if (pInfo->pszName == NULL)
            continue;

        if (pInfo->pszFunction != NULL)
        {
            WriteScr("%s\r\n", pInfo->pszFunction);
        }
        else
        {
            WriteScr(
                "function %s(...)\r\n"
                "   %s(0x%X, ...)\r\n"
                "end\r\n"
                "\r\n",
                pInfo->pszName,
                NAME_COMMON_HANDLER,
                pInfo->OP
            );
        }

    }

    WriteScr("\r\n");

    for (ULONG OP = 0, Count = MAX_INSTRUCTION_COUNT; Count; ++OP, --Count)
    {
        WriteScr(
            "function %s%X(...)\r\n"
            "   %s(0x%X, ...)\r\n"
            "end\r\n"
            "\r\n",
            NAME_DEFAULT_HANDLER_PREFIX,
            OP,
            NAME_COMMON_HANDLER,
            OP
        );
    }

    return TRUE;
}

BOOL CNsbDisassembler::DumpToScript(PWCHAR pszScriptName)
{
    ULONG                Offset;
    CFileDisk            file;
    PN2_FUNCTION_MAP    *pMap, *pMapEnd;
    INSTRUCTION_ENTRY   *pInstruction;

    CHAR   Buffer2[0x5000];
    PWCHAR pszFileName;
    union
    {
        CHAR  Buffer[0x5000];
        WCHAR szFile[MAX_PATH];
    };

    lstrcpyW(szFile, pszScriptName);
    pszFileName = findnamew(szFile);
    lstrcpyW(pszFileName, MAKE_WSTRING(NAME_DEFAULT_BASE_SCRIPT));
    CreateBaseScript(szFile, Buffer2);

    if (!file.Create(pszScriptName))
        return FALSE;

    if (m_pInfoMap == NULL)
    {
        m_pInfoMap = (INSTRUCTION_INFO *)m_mem.Alloc(MAX_INSTRUCTION_COUNT * sizeof(*m_pInfoMap), HEAP_ZERO_MEMORY);
        if (m_pInfoMap == NULL)
            return FALSE;

        for (ULONG Index = 0; Index != countof(g_InsInfo); ++Index)
            m_pInfoMap[g_InsInfo[Index].OP] = g_InsInfo[Index];
    }

    pszFileName = pszScriptName + (pszFileName - szFile);
    Offset = findextw(pszFileName) - pszFileName;
    Offset = WideCharToMultiByte(
                CP_ACP,
                0,
                pszFileName,
                Offset,
                Buffer,
                countof(Buffer),
                NULL,
                NULL);
    Buffer[Offset] = 0;
    WriteScr(szScriptInit, Buffer);

    pInstruction = m_NsbRecord.pInstruction;
    pMap = m_FuncRecord.pMap;
    pMapEnd = pMap + m_FuncRecord.Count;
    Offset = (*pMap)->Offset;
    while (pMap < pMapEnd && pInstruction->Offset == Offset)
    {
        PCHAR pName = (*pMap)->FuncName.Buffer;
        ULONG Length = (*pMap)->FuncName.Length;
        if (!StrNICompareA(pName, "include.", 8))
        {
            WriteScr("include('%s')\r\n", CopyString(Buffer, pName + 8, Length - 8));
        }
        else if (!StrNICompareA(pName, "chapter.", 8))
        {
            WriteScr("chapter('%s')\r\n", CopyString(Buffer, pName + 8, Length - 8));
        }
        else if (!StrNICompareA(pName, "function.", 9))
        {
            WriteScr("BeginFunction('%s')\r\n", CopyString(Buffer, pName + 9, Length - 9));
        }
        else if (!StrNICompareA(pName, "label.", 6))
        {
            WriteScr("label('%s')\r\n", CopyString(Buffer, pName + 6, Length - 6));
        }
        else if (!StrNICompareA(pName, "begin.", 6))
        {
            WriteScr("begin('%s')\r\n", CopyString(Buffer, pName + 6, Length - 6));
        }
        else
        {
            printf("%s\n", pName);
            getch();
        }

        if (++pMap >= pMapEnd)
            break;
        Offset = (*pMap)->Offset;
    }

    for (ULONG Count = m_NsbRecord.Count; Count; ++pInstruction, --Count)
    {
        ULONG             Params;
        PCHAR             pHandlerName;
        N2_ANSI_STRING_L *pParam;
        INSTRUCTION_INFO *pInfo;

        while (pMap < pMapEnd && pInstruction->Offset == Offset)
        {
            PCHAR pName = (*pMap)->FuncName.Buffer;
            ULONG Length = (*pMap)->FuncName.Length;
            if (!StrNICompareA(pName, "include.", 8))
            {
                WriteScr("include('%s')\r\n", CopyString(Buffer, pName + 8, Length - 8));
            }
            else if (!StrNICompareA(pName, "chapter.", 8))
            {
                WriteScr("chapter('%s')\r\n", CopyString(Buffer, pName + 8, Length - 8));
            }
            else if (!StrNICompareA(pName, "function.", 9))
            {
                WriteScr("\r\n");
                WriteScr("BeginFunction('%s')\r\n", CopyString(Buffer, pName + 9, Length - 9));
            }
            else if (!StrNICompareA(pName, "label.", 6))
            {
                WriteScr("label('%s')\r\n", CopyString(Buffer, pName + 6, Length - 6));
            }
            else if (!StrNICompareA(pName, "scene.", 6))
            {
                WriteScr("scene('%s')\r\n", CopyString(Buffer, pName + 6, Length - 6));
            }
            else if (!StrNICompareA(pName, "begin.", 6))
            {
                WriteScr("begin('%s')\r\n", CopyString(Buffer, pName + 6, Length - 6));
            }
            else
            {
                printf("%s\n", pName);
                getch();
            }

            if (++pMap >= pMapEnd)
                break;

            Offset = (*pMap)->Offset;
        }

        pInfo = &m_pInfoMap[pInstruction->pInstruction->OP];
        if (pInfo->pfHandler != NULL)
        {
            if ((this->*pInfo->pfHandler)(file, Buffer, Buffer2, pInstruction, pInfo))
                continue;
        }

        pHandlerName = pInfo->pszName;
        if (pHandlerName != NULL)
        {
            WriteScr("%s(", pHandlerName, pInstruction->pInstruction->OP);
        }
        else
        {
            WriteScr("%s%X(", NAME_DEFAULT_HANDLER_PREFIX, pInstruction->pInstruction->OP);
        }

        Params = pInstruction->pInstruction->ParamCount;
        if (Params != 0)
        {
            pParam = pInstruction->pInstruction->Param;

            WriteScr("'%s'", CopyString(Buffer, pParam->Buffer, pParam->Length));
            --Params;

            pParam = (N2_ANSI_STRING_L *)((ULONG_PTR)pParam + pParam->Length + sizeof(pParam->Length));
            for (; Params; --Params)
            {
                WriteScr(", '%s'", CopyString(Buffer, pParam->Buffer, pParam->Length));
                pParam = (N2_ANSI_STRING_L *)((ULONG_PTR)pParam + pParam->Length + sizeof(pParam->Length));
            }
        }

        WriteScr(")\r\n");
    }

    WriteScr(szScriptFinalize);

    return TRUE;
}

BOOL
CNsbDisassembler::
SetText(
    CFileDisk          &file,
    PCHAR               Buffer,
    PCHAR               Buffer2,
    INSTRUCTION_ENTRY  *pInstruction,
    INSTRUCTION_INFO   *pInfo
)
{
    ULONG             Params;
    PCHAR             pString;
    N2_ANSI_STRING_L *pParam;

    pString = pInfo->pszName;
    if (pString != NULL)
    {
        WriteScr("%s(", pString, pInstruction->pInstruction->OP);
    }
    else
    {
        WriteScr("%s%X(", NAME_DEFAULT_HANDLER_PREFIX, pInstruction->pInstruction->OP);
    }

    WriteScr("\r\n");

    Params = pInstruction->pInstruction->ParamCount;
    if (Params != 3)
    {
        printf("unknown SetText param\n");
        getch();
    }

    pParam = pInstruction->pInstruction->Param;
    pString = CopyString(Buffer, pParam->Buffer, pParam->Length);

    WriteScr("    '%s'", CopyString(Buffer, pParam->Buffer, pParam->Length));
    pParam = (N2_ANSI_STRING_L *)((ULONG_PTR)pParam + pParam->Length + sizeof(pParam->Length));
    WriteScr(
        ",\r\n"
        "    '%s'",
        CopyString(Buffer, pParam->Buffer, pParam->Length)
    );

    pParam = (N2_ANSI_STRING_L *)((ULONG_PTR)pParam + pParam->Length + sizeof(pParam->Length));
    WriteScr(
        ",\r\n"
        "    %s",
        CopyString(Buffer, pParam->Buffer, pParam->Length, TRUE)
    );

    pParam = (N2_ANSI_STRING_L *)((ULONG_PTR)pParam + pParam->Length + sizeof(pParam->Length));

    WriteScr("\r\n)\r\n");

    return TRUE;
}
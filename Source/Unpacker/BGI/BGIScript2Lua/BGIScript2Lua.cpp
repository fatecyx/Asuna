#include "BGIScript2Lua.h"
#include "BpInstruction.h"
#include "BurikoScript.h"

CBGIScript2Lua::CBGIScript2Lua()
{
    ZeroMemory(&m_Info, sizeof(m_Info));
    Initialize();
}

CBGIScript2Lua::~CBGIScript2Lua()
{
    Release();
    m.Free(m_pInstructionMap);
    m.Free(m_pScriptInfoMap);
}

VOID CBGIScript2Lua::Release()
{
    m.SafeFree(&m_Info.pvScriptBuffer);
    m.SafeFree(&m_Info.bp.pBpRecord);
    m.SafeFree(&m_Info.bp.pbMask);

    BGI_BURIKO_SCRIPT_RECORD *pScrRecord = m_Info.scr.pScriptRecord;

    if (pScrRecord != NULL)
    {
        for (ULONG Count = m_Info.RecordCount; Count; ++pScrRecord, --Count)
            m.Free(pScrRecord->pRecord);

        m.SafeFree(&m_Info.scr.pScriptRecord);
    }

    ZeroMemory(&m_Info, sizeof(m_Info));
}

HRESULT CBGIScript2Lua::Initialize()
{
    BGI_BP_INSTRUCTION *pInstructionMap;

    m_pInstructionMap = (BGI_BP_INSTRUCTION *)m.Alloc(BGI_BP_OP_MAX * sizeof(*m_pInstructionMap), HEAP_ZERO_MEMORY);
    if (m_pInstructionMap == NULL)
        return E_OUTOFMEMORY;

    pInstructionMap = g_BPInstrction;
    for (ULONG Count = countof(g_BPInstrction); Count; ++pInstructionMap, --Count)
    {
        ULONG OP = BP_GET_OP(pInstructionMap);

        if (OP >= BGI_BP_OP_MAX)
            continue;

        m_pInstructionMap[OP] = *pInstructionMap;
    }

    m_pScriptInfoMap = (BGI_BURIKO_SCRIPT_INSTRUCTION *)m.Alloc(SCR_OP_MAX * sizeof(*m_pScriptInfoMap));
    if (m_pScriptInfoMap == NULL)
        return E_OUTOFMEMORY;

    BGI_BURIKO_SCRIPT_INSTRUCTION *pScriptInfo;

    pScriptInfo = g_BurikoScriptInfo;
    for (ULONG Count = countof(g_BurikoScriptInfo); Count; ++pScriptInfo, --Count)
    {
        ULONG OP = SCR_GET_OP(pScriptInfo);

        if (OP >= SCR_OP_MAX)
            continue;

        m_pScriptInfoMap[OP] = *pScriptInfo;
    }

    return S_OK;
}

HRESULT CBGIScript2Lua::ConvertScript(PWCHAR pszScriptFile)
{
    union
    {
        BGI_BP_HEADER            bp;
        BGI_BURIKO_SCRIPT_HEADER buriko;
    } Header;

    HRESULT Result;
    WCHAR   szPath[MAX_PATH];

    Release();

    if (!file.Open(pszScriptFile))
        return TYPE_E_IOERROR;

    if (!file.Read(&Header, sizeof(Header)))
        return TYPE_E_IOERROR;

    if (Header.bp.HeaderSize >= sizeof(Header.bp) &&
        Header.bp.InstructionSize + Header.bp.HeaderSize == file.GetSize())
    {
        Result = ParseBPScript(&m_Info, &Header.bp);
        if (SUCCEEDED(Result))
        {
            lstrcpyW(szPath, pszScriptFile);
            lstrcpyW(findextw(szPath), MAKE_WSTRING(BP_NAME_EXTENSION));
            Result = ConvertBPToLua(&m_Info, szPath);
        }
    }
    else if (!CompareMemory(Header.buriko.Magic, BGI_BURIKO_SCRIPT_MAGIC, sizeof(Header.buriko.Magic)))
    {
        Result = ParseBurikoScript(&m_Info, &Header.buriko);
        if (SUCCEEDED(Result))
        {
            lstrcpyW(szPath, pszScriptFile);
            lstrcpyW(findextw(szPath), MAKE_WSTRING(SCR_NAME_EXTENSION));
            Result = ConvertScriptToLua(&m_Info, szPath);
        }
    }
    else
    {
        Result = E_NOTIMPL;
    }

    return Result;
}

/************************************************************************
  bp
************************************************************************/

HRESULT CBGIScript2Lua::AddBPInstruction(BGI_SCRIPT_INFO *pScrInfo, INSTRUCTION_RECORD *pInsRecord)
{
    INSTRUCTION_RECORD *pRecord;

    pRecord = pScrInfo->bp.pBpRecord;
    if (pRecord == NULL)
    {
        pScrInfo->RecordCount    = 0;
        pScrInfo->MaxRecordCount = 0x100;
        pRecord = (INSTRUCTION_RECORD *)m.Alloc(pScrInfo->MaxRecordCount * sizeof(*pRecord));
        if (pRecord == NULL)
            return E_OUTOFMEMORY;

        pScrInfo->bp.pBpRecord = pRecord;
    }
    else if (pScrInfo->RecordCount == pScrInfo->MaxRecordCount)
    {
        pScrInfo->MaxRecordCount *= 2;
        pRecord = pScrInfo->bp.pBpRecord;
        pRecord = (INSTRUCTION_RECORD *)m.ReAlloc(pRecord, pScrInfo->MaxRecordCount * sizeof(*pRecord));
        pScrInfo->bp.pBpRecord = pRecord;
        if (pRecord == NULL)
            return E_OUTOFMEMORY;
    }

    pRecord += pScrInfo->RecordCount;
    *pRecord = *pInsRecord;
    ++pScrInfo->RecordCount;

    return S_OK;
}

HRESULT CBGIScript2Lua::ParseBPScript(BGI_SCRIPT_INFO *pScrInfo,BGI_BP_HEADER *pHeader)
{
    HRESULT hResult;
    ULONG   ScriptSize;
    PBYTE   pbMask;

    if (!file.Seek(file.FILE_SEEK_BEGIN, pHeader->HeaderSize))
        return TYPE_E_IOERROR;

    ScriptSize = pHeader->HeaderSize + pHeader->InstructionSize;
    pScrInfo->pvScriptBuffer = m.Alloc(ScriptSize);
    if (pScrInfo->pvScriptBuffer == NULL)
        return E_OUTOFMEMORY;

    pScrInfo->pbBuffer = pScrInfo->pbScriptBuffer + pHeader->HeaderSize;
    if (!file.Read(pScrInfo->pbBuffer, pHeader->InstructionSize))
        return TYPE_E_IOERROR;

    pScrInfo->bp.pbMask = (PBYTE)m.Alloc(ScriptSize, HEAP_ZERO_MEMORY);
    if (pScrInfo->bp.pbMask == NULL)
        return E_OUTOFMEMORY;

    *pScrInfo->pBpHeader = *pHeader;
    pScrInfo->pbBegin    = pScrInfo->pbBuffer;
    pScrInfo->pbEnd = pScrInfo->pbScriptBuffer + ScriptSize;

    do
    {
        hResult = DisaseembleBP(pScrInfo);
    } while (hResult == S_CONTINUE);

    if (FAILED(hResult))
        return hResult;
/*
    LOOP_FOREVER
    {
        BOOL bFinished = TRUE;

        pbMask = pScrInfo->bp.pbMask;
        for (ULONG Count = ScriptSize; Count; ++pbMask, --Count)
        {
            if (!TEST_BITS(*pbMask, BP_MASK_PROC))
                continue;

            pScrInfo->pbBuffer = (PBYTE)pScrInfo->pvScriptBuffer + (pbMask - pScrInfo->bp.pbMask + pScrInfo->pBpHeader->HeaderSize);

//            do
//            {
//                hResult = Disaseemble(pScrInfo);
//            } while (hResult == S_CONTINUE);

//            if (FAILED(hResult))
//                goto _Exit;

            *pbMask &= ~BP_MASK_PROC;
            *pbMask |= BP_MASK_LABEL;
            bFinished = FALSE;
//            break;
        }

        if (bFinished)
            break;
    }
*/
    ULONG_PTR Base;
    INSTRUCTION_RECORD *pRecord;

    Base    = (ULONG_PTR)pScrInfo->pvScriptBuffer + pScrInfo->pBpHeader->HeaderSize - (ULONG_PTR)pScrInfo->bp.pbMask + 1;
    pbMask  = pScrInfo->bp.pbMask;
    pRecord = pScrInfo->bp.pBpRecord;

    pRecord += pScrInfo->RecordCount - 1;
    while (pRecord->OP == PushByte && *pRecord->pbParam == 0)
    {
        --pRecord;
        --pScrInfo->RecordCount;
    }

    pRecord = pScrInfo->bp.pBpRecord;
    for (ULONG Index = 0, Count = pScrInfo->RecordCount; Count; ++pRecord, ++Index, --Count)
    {
        pbMask = pRecord->pbParam - Base;
//        if (TEST_BITS(*pbMask, BP_MASK_LABEL))
        if (TEST_BITS(*pbMask, BGI_MASK_PROC | BGI_MASK_LABEL))
        {
            pRecord->Flags |= BGI_INSTRUCTION_FLAGS_LABEL;
        }
    }
/*
    pRecord = pScrInfo->bp.pBpInstructionRecord;
    for (ULONG i = pScrInfo->InstructionCount; i; --i)
    {
        for (ULONG j = 0; j != i - 1; ++j)
        {
            if (pRecord[j].Offset > pRecord[j + 1].Offset)
                Swap(pRecord[j], pRecord[j + 1]);
        }
    }

_Exit:
*/

    return FAILED(hResult) ? hResult : S_OK;
}

HRESULT
CBGIScript2Lua::
SetBPRecord(
    BGI_SCRIPT_INFO         *pScrInfo,
    PBYTE                    pbParam,
    BGI_BP_INSTRUCTION      *pIns,
    INSTRUCTION_RECORD   *pRecord
)
{
    pRecord->OP         = BP_GET_OP(pIns);
    pRecord->pbParam    = pbParam;
    pRecord->Flags      = pIns->Flags;
    pRecord->Offset     = pbParam - 1 - pScrInfo->pbScriptBuffer;

    return S_OK;
}

HRESULT CBGIScript2Lua::ParseBPParam(BGI_SCRIPT_INFO *pScrInfo, INSTRUCTION_RECORD *pRecord)
{
    ULONG   Count, OP;
    PBYTE   pbBuffer;
    PUSHORT pParamLength;
    PULONG  pFlags;

    OP = pRecord->OP;
    if (OP >= BGI_BP_OP_MAX)
        return S_OK;

    Count = m_pInstructionMap[OP].ParamCount;
    if (Count == 0)
        return S_OK;

    pFlags          = m_pInstructionMap[pRecord->OP].pParamFlags;
    pParamLength    = m_pInstructionMap[pRecord->OP].pParamLength;
    pbBuffer        = pScrInfo->pbBuffer;

    do
    {
        if (pFlags != NULL)
        {
            if (TEST_BITS(*pFlags, BGI_INSTRUCTION_FLAGS_PROC))
            {
                PBYTE   pbMask;
                ULONG64 Param = 0;

                switch (*pParamLength)
                {
                    case 1:
                        Param = *(PCHAR)pbBuffer;
                        break;

                    case 2:
                        Param = *(PSHORT)pbBuffer;
                        break;

                    case 4:
                        Param = *(PLONG)pbBuffer;

                    default:
                        return E_INVALIDARG;
                }

                pbMask = pScrInfo->bp.pbMask;
                pbMask += Param;
                pbMask += (pRecord->pbParam - 1) - (pScrInfo->pbScriptBuffer + pScrInfo->pBpHeader->HeaderSize);
                *pbMask |= BGI_MASK_PROC;
            }
            else if (TEST_BITS(*pFlags, BGI_INSTRUCTION_FLAGS_STRING))
            {
                pScrInfo->pbEnd = min(pScrInfo->pbEnd, pRecord->pbParam - 1 + *(PSHORT)pbBuffer);
            }

            ++pFlags;
        }

        pbBuffer += *pParamLength++;
    } while (--Count);

    pScrInfo->pbBuffer = pbBuffer;

    return S_OK;
}

HRESULT CBGIScript2Lua::DisaseembleBP(BGI_SCRIPT_INFO *pScrInfo)
{
    ULONG                   OP;
    BGI_BP_INSTRUCTION     *pIns;
    INSTRUCTION_RECORD   Record;

    if (pScrInfo->pbBuffer >= pScrInfo->pbEnd)
        return S_PROCESSED;

    OP = *pScrInfo->pbBuffer;
    pIns = &m_pInstructionMap[OP];
    if (!IS_INSTRUCTION_INIT(pIns->OP))
        return E_UNKNOWN_OP;

#if 0
    PBYTE bMask;
    pbMask = pScrInfo->bp.pbMask + (pScrInfo->pbBuffer - pScrInfo->pbScriptBuffer);
    if (TEST_BITS(*pbMask, BP_MASK_PROCESSED))
        return S_PROCESSED;

    *pbMask |= BP_MASK_PROCESSED;

#endif

    ++pScrInfo->pbBuffer;

    SetBPRecord(pScrInfo, pScrInfo->pbBuffer, pIns, &Record);
    if (IS_HANDLER(pIns))
    {
        HRESULT hResult;

        hResult = (this->*pIns->Handler)(pScrInfo, Record, TRUE);
        if (SUCCEEDED(hResult))
            return hResult;
    }

    ParseBPParam(pScrInfo, &Record);
    if (pScrInfo->pbBuffer > pScrInfo->pbEnd)
        return S_PROCESSED;

    AddBPInstruction(pScrInfo, &Record);
//    if (TEST_BITS(Record.Flags, BGI_INSTRUCTION_FLAGS_RETURN))
//        return S_PROC_RETURN;

    return S_CONTINUE;
}

HRESULT
FASTCALL
CBGIScript2Lua::
PushProcAddrHandler(
    BGI_SCRIPT_INFO         *pScrInfo,
    INSTRUCTION_RECORD      &Record,
    BOOL                     bParser
)
{
    UNREFERENCED_PARAMETER(pScrInfo);
    UNREFERENCED_PARAMETER(Record);

    if (bParser)
    {
        return E_NOTIMPL;
    }

    return E_NOTIMPL;
}

#define WriteScr(...) { hResult = WriteText(file, Buffer, __VA_ARGS__); if (FAILED(hResult)) return hResult; }

HRESULT CBGIScript2Lua::CreateBaseBPLua(PWCHAR pszLuaFile, PCHAR Buffer)
{
    HRESULT hResult;
    BGI_BP_INSTRUCTION *pIns;

    if (IsPathExistsW(pszLuaFile))
        return S_OK;

    if (!file.Create(pszLuaFile))
        return TYPE_E_IOERROR;

    WriteScr("%s\r\n", szBaseBpFunc);

    WriteScr("-- manual\r\n\r\n");

    pIns = g_BPInstrction;
    for (ULONG Count = countof(g_BPInstrction); Count; ++pIns, --Count)
    {
        if (pIns->Body == NULL)
            continue;

        WriteScr("%s\r\n\r\n", pIns->Body);
    }

    WriteScr("-- auto\r\n\r\n");

    pIns = g_BPInstrction;
    for (ULONG Count = countof(g_BPInstrction); Count; ++pIns, --Count)
    {
        ULONG   Params, Index;
        PUSHORT pLength;
        PULONG  pFlags;

        if (pIns->Body != NULL)
            continue;

        if (pIns->Name == NULL)
        {
            WriteScr("function %s%02X(", BP_NAME_DEFAULT_OP_PREFIX, BP_GET_OP(pIns));
        }
        else
        {
            WriteScr("function %s(", pIns->Name);
        }

        Params = pIns->ParamCount;
        if (Params != 0)
        {
            pLength = pIns->pParamLength;
            Index   = 0;

            WriteScr("%s%d", BP_NAME_DEFAULT_PARAM_PREFIX, ++Index);
            while (--Params)
            {
                WriteScr(", %s%d", BP_NAME_DEFAULT_PARAM_PREFIX, ++Index);
            }
        }

        WriteScr(")\r\n");

        pFlags = pIns->pParamFlags;
        if (pFlags != NULL)
        {
            Index  = 0;
            Params = pIns->ParamCount;
            for (; Params; ++pFlags, --Params)
            {
                if (!TEST_BITS(*pFlags, BGI_INSTRUCTION_FLAGS_PROC | BGI_INSTRUCTION_FLAGS_STRING))
                    continue;

                WriteScr(
                    "    %s(%s%d)\r\n",
                    (TEST_BITS(*pFlags, BGI_INSTRUCTION_FLAGS_PROC) ? BP_FUNC_ADD_PROC_LABEL : BP_FUNC_ADD_TEXT),
                    BP_NAME_DEFAULT_PARAM_PREFIX,
                    ++Index
                );
            }
        }

        WriteScr("    %s%s(0x%02X", "return ", BP_FUNC_WRITE_INSTRUCTION, BP_GET_OP(pIns));

        pFlags  = pIns->pParamFlags;
        pLength = pIns->pParamLength;
        for (Index = 1, Params = pIns->ParamCount; Params; --Params)
        {
            ULONG Flags = 0;

            if (pFlags != NULL)
                Flags = *pFlags++;

            if (TEST_BITS(Flags, BGI_INSTRUCTION_FLAGS_PROC | BGI_INSTRUCTION_FLAGS_STRING))
            {
                WriteScr(", -1, %d", *pLength++);
            }
            else
            {
                WriteScr(", %s%d, %d", BP_NAME_DEFAULT_PARAM_PREFIX, Index, *pLength++);
            }

            ++Index;
        }

        WriteScr(
            ")\r\n"
            "end\r\n"
            "\r\n"
        );
    }

    return S_OK;
}

HRESULT CBGIScript2Lua::WriteString(CFileDisk &file, PCHAR Buffer, PCHAR pString)
{
    PCHAR   pBuffer;
    HRESULT hResult;

    pBuffer = Buffer;
    *pBuffer++ = '"';
    LOOP_FOREVER
    {
        CHAR ch = *pString++;

        if (ch < 0)
        {
            *pBuffer++ = ch;
            ch = *pString++;
        }
        else switch (ch)
        {
            case '\r':
                *pBuffer++ = '\\';
                ch = 'r';
                break;

            case '\n':
                *pBuffer++ = '\\';
                ch = 'n';
                break;

            case '\f':
                *pBuffer++ = '\\';
                ch = 'f';
                break;

            case '\b':
                *pBuffer++ = '\\';
                ch = 'b';
                break;

            case '"':
            case '\\':
                *pBuffer++ = '\\';
                break;
        }

        *pBuffer++ = ch;
        if (ch == 0)
            break;
    }

    *(PULONG)&pBuffer[-1] = '"';

    WriteScr("%s", Buffer);

    return S_OK;
}

HRESULT CBGIScript2Lua::ConvertBPToLua(BGI_SCRIPT_INFO *pScrInfo, PWCHAR pszLuaFile)
{
    HRESULT hResult;
    INSTRUCTION_RECORD *pRecord;
    BGI_BP_INSTRUCTION *pMap;

    CHAR    Buffer[0x5000];
    WCHAR   szBaseLua[MAX_PATH];

    lstrcpyW(szBaseLua, pszLuaFile);
    lstrcpyW(findnamew(szBaseLua), MAKE_WSTRING(BP_NAME_DEFAULT_BASE_SCRIPT));
    CreateBaseBPLua(szBaseLua, Buffer);

    if (!file.Create(pszLuaFile))
        return TYPE_E_IOERROR;

    WideCharToMultiByte(
        CP_GB2312,
        0,
        findnamew(pszLuaFile),
        -1,
        (PCHAR)szBaseLua,
        sizeof(szBaseLua),
        NULL,
        NULL
    );

    rmexta((PCHAR)szBaseLua);
    WriteScr(szBpInit, (PCHAR)szBaseLua);

    pRecord = pScrInfo->bp.pBpRecord;
    for (ULONG Count = pScrInfo->RecordCount; Count; ++pRecord, --Count)
    {
        PBYTE   pbParam;
        ULONG   Params;
        ULONG64 Value;
        PULONG  pParamFlags;
        PUSHORT pParamLength;

        if (TEST_BITS(pRecord->Flags, BGI_INSTRUCTION_FLAGS_LABEL))
        {
            WriteScr("\r\n%s(\"%s%04X\")\r\n\r\n", BP_NAME_LABEL, BP_NAME_LABEL_PREFIX, pRecord->pbParam - 1 - pScrInfo->pbScriptBuffer);
        }

        pMap = &m_pInstructionMap[pRecord->OP];
        if (pMap->Name == NULL)
        {
            WriteScr("%s%02X(", BP_NAME_DEFAULT_OP_PREFIX, pRecord->OP);
        }
        else
        {
            WriteScr("%s(", pMap->Name);
        }

        if (pMap->ParamCount != 0)
        {
            pbParam         = pRecord->pbParam;
            pParamLength    = pMap->pParamLength;
            pParamFlags     = pMap->pParamFlags;
            Params          = pMap->ParamCount;

            if (pParamFlags != NULL)
            {
                ULONG Flags = *pParamFlags++;

                if (TEST_BITS(Flags, BGI_INSTRUCTION_FLAGS_STRING))
                {
                    LPSTR pString;

                    pString = (LPSTR)(*(PSHORT)pbParam + pbParam - 1);
                    WriteString(file, Buffer, pString);
                }
                else if (TEST_BITS(Flags, BGI_INSTRUCTION_FLAGS_PROC))
                {
                    WriteScr("\"%s%04X\"", BP_NAME_LABEL_PREFIX, *(PSHORT)pbParam + pbParam - 1 - pScrInfo->pbScriptBuffer);
                }
                else
                {
                    goto VALUE_PARAM_1;
                }
            }
            else
            {

VALUE_PARAM_1:
                Value = 0;
                CopyMemory(&Value, pbParam, *pParamLength);
                WriteScr("0x%I64X", Value);
            }

            pbParam += *pParamLength++;

            while (--Params)
            {
                if (pParamFlags != NULL)
                {
                    ULONG Flags = *pParamFlags++;

                    if (TEST_BITS(Flags, BGI_INSTRUCTION_FLAGS_STRING))
                    {
                        LPSTR pString;

                        WriteScr(", ");
                        pString = (LPSTR)(*(PSHORT)pbParam + pbParam - 1);
                        WriteString(file, Buffer, pString);
                    }
                    else
                    {
                        goto VALUE_PARAM_2;
                    }
                }
                else
                {

VALUE_PARAM_2:
                    Value = 0;
                    CopyMemory(&Value, pbParam, *pParamLength);
                    WriteScr(", 0x%I64X", Value);
                }

                pbParam += *pParamLength++;
            }
        }

        WriteScr(")\r\n");
    }

    WriteScr("\r\n%s\r\n", szBpFinalize);

    return S_OK;
}

/************************************************************************
  aiyoku BurikoScript
************************************************************************/

HRESULT
CBGIScript2Lua::
SetScriptRecord(
    BGI_SCRIPT_INFO                 *pScrInfo,
    PBYTE                            pbParam,
    BGI_BURIKO_SCRIPT_INSTRUCTION   *pInfo,
    INSTRUCTION_RECORD              *pRecord
)
{
    pRecord->OP         = BP_GET_OP(pInfo);
    pRecord->pbParam    = pbParam;
    pRecord->Flags      = pInfo->Flags;
    pRecord->Offset     = pbParam - 4 - pScrInfo->pbScriptBuffer;

    return S_OK;
}

HRESULT
CBGIScript2Lua::
AddFunction(
    BGI_SCRIPT_INFO           *pScrInfo,
    PCHAR                      pszFuncName,
    BGI_BURIKO_SCRIPT_RECORD **ppScriptRecord
)
{
    BGI_BURIKO_SCRIPT_RECORD *pScriptRecord;

    *ppScriptRecord = NULL;

    pScriptRecord = pScrInfo->scr.pScriptRecord;
    if (pScriptRecord == NULL)
    {
        pScrInfo->RecordCount = 0;
        pScrInfo->MaxRecordCount = 0x35;
        pScriptRecord = (BGI_BURIKO_SCRIPT_RECORD *)m.Alloc(pScrInfo->MaxRecordCount * sizeof(*pScriptRecord));
        if (pScriptRecord == NULL)
            return E_OUTOFMEMORY;

        pScrInfo->scr.pScriptRecord = pScriptRecord;
    }
    else if (pScrInfo->RecordCount == pScrInfo->MaxRecordCount)
    {
        pScrInfo->MaxRecordCount *= 2;
        pScriptRecord = (BGI_BURIKO_SCRIPT_RECORD *)m.ReAlloc(pScriptRecord, pScrInfo->MaxRecordCount * sizeof(*pScriptRecord));
        pScrInfo->scr.pScriptRecord = pScriptRecord;
        if (pScriptRecord == NULL)
            return E_OUTOFMEMORY;
    }

    pScriptRecord = pScriptRecord + pScrInfo->RecordCount;
    ++pScrInfo->RecordCount;

    pScriptRecord->FuncName     = pszFuncName;
    pScriptRecord->RecordCount  = 0;
    pScriptRecord->pRecord      = NULL;

    *ppScriptRecord = pScriptRecord;

    return S_OK;
}

HRESULT
CBGIScript2Lua::
AddScriptInstruction(
    BGI_BURIKO_SCRIPT_RECORD *pScriptRecord,
    INSTRUCTION_RECORD       *pInsRecord
)
{
    INSTRUCTION_RECORD *pRecord;

    pRecord = pScriptRecord->pRecord;
    if (pRecord == NULL)
    {
        pScriptRecord->RecordCount      = 0;
        pScriptRecord->MaxRecordCount   = 0x100;
        pRecord = (INSTRUCTION_RECORD *)m.Alloc(pScriptRecord->MaxRecordCount * sizeof(*pRecord));
        if (pRecord == NULL)
            return E_OUTOFMEMORY;

        pScriptRecord->pRecord = pRecord;
    }
    else if (pScriptRecord->RecordCount == pScriptRecord->MaxRecordCount)
    {
        pScriptRecord->MaxRecordCount *= 2;
        pRecord = pScriptRecord->pRecord;
        pRecord = (INSTRUCTION_RECORD *)m.ReAlloc(pRecord, pScriptRecord->MaxRecordCount * sizeof(*pRecord));
        pScriptRecord->pRecord = pRecord;
        if (pRecord == NULL)
            return E_OUTOFMEMORY;
    }

    pRecord += pScriptRecord->RecordCount;
    *pRecord = *pInsRecord;
    ++pScriptRecord->RecordCount;

    return S_OK;
}

HRESULT CBGIScript2Lua::ParseBurikoScript(BGI_SCRIPT_INFO *pScrInfo, BGI_BURIKO_SCRIPT_HEADER *pHeader)
{
    PBYTE   pbBuffer, pbMask;
    ULONG   ScriptSize, FuncCount;
    HRESULT hResult;

    if (!file.Seek(file.FILE_SEEK_BEGIN, sizeof(pHeader->Magic)))
        return TYPE_E_IOERROR;

    ScriptSize = file.GetSize();
    pScrInfo->pvScriptBuffer = m.Alloc(ScriptSize);
    if (pScrInfo->pvScriptBuffer == NULL)
        return E_OUTOFMEMORY;

    pScrInfo->scr.pbMask = (PBYTE)m.Alloc(ScriptSize, HEAP_ZERO_MEMORY);
    if (pScrInfo->scr.pbMask == NULL)
        return E_OUTOFMEMORY;

    if (!file.Read(pScrInfo->pbScriptBuffer + sizeof(pHeader->Magic), ScriptSize - sizeof(pHeader->Magic)))
        return TYPE_E_IOERROR;

    CopyMemory(pScrInfo->pBurikoHeader->Magic, pHeader->Magic, sizeof(pHeader->Magic));

    pScrInfo->pbBegin = pScrInfo->pbScriptBuffer + pScrInfo->pBurikoHeader->HeaderSize + sizeof(pScrInfo->pBurikoHeader->Magic);
    pScrInfo->pbEnd = pScrInfo->pbScriptBuffer + ScriptSize;

    pbBuffer = (PBYTE)(pScrInfo->pBurikoHeader + 1);
    FuncCount = *(PULONG)pbBuffer;
    pbBuffer += sizeof(FuncCount);

    if (FuncCount == 0)
        return S_OK;

    do
    {
        pScrInfo->pbBuffer = pbBuffer;
        hResult = DisaseembleScrFunc(pScrInfo);
        if (FAILED(hResult))
            return hResult;

        pbBuffer += StrLengthA((PCHAR)pbBuffer) + 1 + 4;

    } while (--FuncCount);

    ULONG                       BeginOffset, FuncVoiceOffset;
    INSTRUCTION_RECORD         *pRecord;
    BGI_BURIKO_SCRIPT_RECORD   *pScriptRecord;

    pbMask = pScrInfo->scr.pbMask;
    BeginOffset = pScrInfo->pbBegin - pScrInfo->pbScriptBuffer;
    pScriptRecord = pScrInfo->scr.pScriptRecord;

    FuncVoiceOffset = -1;
    for (ULONG FuncCount = pScrInfo->RecordCount; FuncCount; ++pScriptRecord, --FuncCount)
    {
        if (!StrICompareA(pScriptRecord->FuncName, "Voice"))
            continue;

        FuncVoiceOffset = pScriptRecord->pRecord->Offset;
        break;
    }

    pScriptRecord = pScrInfo->scr.pScriptRecord;
    for (FuncCount = pScrInfo->RecordCount; FuncCount; ++pScriptRecord, --FuncCount)
    {
        pRecord = pScriptRecord->pRecord;
        for (ULONG RecordCount = pScriptRecord->RecordCount; RecordCount; ++pRecord, --RecordCount)
        {
            if (TEST_BITS(pbMask[pRecord->Offset], BGI_MASK_PROC | BGI_MASK_LABEL))
                pRecord->Flags |= BGI_INSTRUCTION_FLAGS_LABEL;

            if (pRecord->OP == ScrMsg_ShowText) LOOP_ONCE
            {
                if (pRecord[-1].OP != ScrCtrl_PushString)
                {
                    PrintConsoleW(L"Error: missing ScrCtrl_PushString before ScrMsg_ShowText\n");
                    break;
                }

                if (pRecord[-2].OP == ScrCtrl_PushString)
                {
                    pRecord[-2].OP = SCR_EX_Say;
                    pRecord[-1].OP = SCR_NULL_OP;
                }
                else
                {
                    pRecord[-1].OP = SCR_EX_Text;
                }
            }
            else if (pRecord->OP == ScrMsg_ShowAutoText) LOOP_ONCE
            {
                if (pRecord[-2].OP != ScrCtrl_PushString)
                {
                    PrintConsoleW(L"Error: missing ScrCtrl_PushString before ScrMsg_ShowText\n");
                    break;
                }

                if (pRecord[-1].OP == ScrCtrl_PushString)
                {
                    pRecord[-2].OP = SCR_EX_AutoSay;
                    pRecord[-1].OP = SCR_NULL_OP;
                }
                else
                {
                    pRecord[-2].OP = SCR_EX_AutoText;
                }
            }
            else if (pRecord->OP == ScrCtrl_Call) LOOP_ONCE
            {
                if (pRecord[-1].OP != ScrCtrl_PushString)
                    break;

                ULONG FuncOffset = *(PULONG)pRecord->pbParam + pScrInfo->pbBegin - pScrInfo->pbScriptBuffer;

                if (FuncOffset == FuncVoiceOffset)
                    pRecord[-1].OP = SCR_EX_Voice;
            }
            else if (pRecord[+0].OP == ScrCtrl_09           &&
                     pRecord[-1].OP == ScrCtrl_PushString   &&
                     pRecord[-2].OP == ScrCtrl_20           &&
                     pRecord[-3].OP == ScrCtrl_22           &&
                     pRecord[-4].OP == ScrCtrl_Push         && *(PULONG)pRecord[-4].pbParam == 4 &&
                     pRecord[-5].OP == ScrCtrl_Push         &&
                     pRecord[-6].OP == ScrCtrl_02           && *(PULONG)pRecord[-6].pbParam == 8)
            {
                pRecord[-1].OP = SCR_EX_Select;
            }
        }
    }

    return S_OK;
}

HRESULT CBGIScript2Lua::DisaseembleScrFunc(BGI_SCRIPT_INFO *pScrInfo)
{
    ULONG                           OP;
    PCHAR                           pFuncName;
    PBYTE                           pbBuffer;
    HRESULT                         hResult;
    INSTRUCTION_RECORD              InsRecord;
    BGI_BURIKO_SCRIPT_RECORD       *pScriptRecord;
    BGI_BURIKO_SCRIPT_INSTRUCTION  *pInfo;

    pbBuffer  = pScrInfo->pbBuffer;
    pFuncName = (PCHAR)pbBuffer;
    pbBuffer  = pbBuffer + StrLengthA(pFuncName) + 1;
    pbBuffer  = pScrInfo->pbBegin + *(PULONG)pbBuffer;

    hResult = AddFunction(pScrInfo, pFuncName, &pScriptRecord);
    if (FAILED(hResult))
        return hResult;

    pScrInfo->pbBuffer = pbBuffer;

    do
    {
        OP = *(PULONG)pScrInfo->pbBuffer;
        pScrInfo->pbBuffer += 4;
        pInfo = &m_pScriptInfoMap[OP];
        if (!IS_INSTRUCTION_INIT(pInfo->OP))
            return E_UNKNOWN_OP;

        SetScriptRecord(pScrInfo, pScrInfo->pbBuffer, pInfo, &InsRecord);
        ParseScriptParam(pScrInfo, &InsRecord);
        if (pScrInfo->pbBuffer > pScrInfo->pbEnd)
            break;

        hResult = AddScriptInstruction(pScriptRecord, &InsRecord);
        if (FAILED(hResult))
            return hResult;

    } while (!TEST_BITS(pInfo->Flags, BGI_INSTRUCTION_FLAGS_RETURN));

    return S_OK;
}

HRESULT CBGIScript2Lua::ParseScriptParam(BGI_SCRIPT_INFO *pScrInfo, INSTRUCTION_RECORD *pRecord)
{
    ULONG   Count, Flags, BeginOffset, OP;
    PBYTE   pbBuffer;
    PUSHORT pLength;
    PULONG  pFlags;
    BGI_BURIKO_SCRIPT_INSTRUCTION *pInfo;

    OP = pRecord->OP;
    if (OP >= SCR_OP_MAX)
        return S_OK;

    pInfo = &m_pScriptInfoMap[OP];

    Count = pInfo->ParamCount;
    if (Count == 0)
        return S_OK;

    pFlags   = pInfo->pParamFlags;
    pLength  = pInfo->pParamLength;
    pbBuffer = pScrInfo->pbBuffer;
    BeginOffset = pScrInfo->pbBegin - pScrInfo->pbScriptBuffer;

    do
    {
        if (pFlags != NULL)
        {
            Flags = *pFlags++;
            if (TEST_BITS(Flags, BGI_INSTRUCTION_FLAGS_PROC))
            {
                pScrInfo->scr.pbMask[*(PULONG)pbBuffer + BeginOffset] |= BGI_MASK_PROC | BGI_MASK_LABEL;
            }
        }

        pbBuffer += *pLength++;

    } while (--Count);

    pScrInfo->pbBuffer = pbBuffer;

    return S_OK;
}

HRESULT CBGIScript2Lua::CreateBaseScrLua(PWCHAR pszLuaFile, PCHAR Buffer)
{
    HRESULT hResult;
    BGI_BURIKO_SCRIPT_INSTRUCTION *pIns;

    if (IsPathExistsW(pszLuaFile))
        return S_OK;

    if (!file.Create(pszLuaFile))
        return TYPE_E_IOERROR;

    WriteScr("%s\r\n", szBaseScrFunc);

    WriteScr("-- manual\r\n\r\n");

    pIns = g_BurikoScriptInfo;
    for (ULONG Count = countof(g_BurikoScriptInfo); Count; ++pIns, --Count)
    {
        if (pIns->Body == NULL)
            continue;

        WriteScr("%s\r\n\r\n", pIns->Body);
    }

    WriteScr("-- auto\r\n\r\n");

    pIns = g_BurikoScriptInfo;
    for (ULONG Count = countof(g_BurikoScriptInfo); Count; ++pIns, --Count)
    {
        ULONG   Params, Index;
        PULONG  pFlags;

        if (pIns->Body != NULL)
            continue;

        if (pIns->Name == NULL)
        {
            WriteScr("function %s%02X(", SCR_NAME_DEFAULT_OP_PREFIX, SCR_GET_OP(pIns));
        }
        else
        {
            WriteScr("function %s(", pIns->Name);
        }

        Params = pIns->ParamCount;
        if (Params != 0)
        {
            Index = 0;

            WriteScr("%s%d", BP_NAME_DEFAULT_PARAM_PREFIX, ++Index);
            while (--Params)
            {
                WriteScr(", %s%d", BP_NAME_DEFAULT_PARAM_PREFIX, ++Index);
            }
        }

        WriteScr(")\r\n");

        Index  = 1;
        Params = pIns->ParamCount;
        pFlags = pIns->pParamFlags;
        if (pFlags == NULL || pIns->Flags == 0)
        {
            WriteScr("    %s%s(0x%02X", "return ", SCR_FUNC_WRITE_INSTRUCTION, SCR_GET_OP(pIns));
            for (; Params; --Params)
            {
                ULONG Flags = 0;

                if (pFlags != NULL)
                    Flags = *pFlags++;

                if (TEST_BITS(Flags, BGI_INSTRUCTION_FLAGS_PROC | BGI_INSTRUCTION_FLAGS_STRING))
                {
                    WriteScr(", -1");
                }
                else
                {
                    WriteScr(", %s%d", SCR_NAME_DEFAULT_PARAM_PREFIX, Index);
                }

                ++Index;
            }

            WriteScr(")\r\n");
            goto WRITE_FUNC_TAIL;
        }

        WriteScr("    %s(0x%X, 4)\r\n", SCR_FUNC_WRITE_FILE, SCR_GET_OP(pIns));
        for (; Params; ++Index, --Params)
        {
            ULONG Flags;
            PCHAR pszFuncName;

            Flags = *pFlags++;

            if (TEST_BITS(Flags, BGI_INSTRUCTION_FLAGS_PROC))
            {
                pszFuncName = SCR_FUNC_ADD_CALL_LABEL;
            }
            else if (TEST_BITS(Flags, BGI_INSTRUCTION_FLAGS_STRING))
            {
                pszFuncName = SCR_FUNC_ADD_STRING;
            }
            else
            {
                pszFuncName = NULL;
            }

            if (pszFuncName == NULL)
            {
                WriteScr(
                    "    %s%s(%s%d, 4)\r\n",
                    Params == 1 ? "return " : "", SCR_FUNC_WRITE_FILE, SCR_NAME_DEFAULT_PARAM_PREFIX, Index
                );
            }
            else
            {
                WriteScr(
                    "    %s(%s%d)\r\n"
                    "    %s%s(-1, 4)\r\n",
                    pszFuncName, SCR_NAME_DEFAULT_PARAM_PREFIX, Index,
                    Params == 1 ? "return " : "", SCR_FUNC_WRITE_FILE
                );
            }
        }

WRITE_FUNC_TAIL:

        WriteScr(
            "end\r\n"
            "\r\n"
        );
    }

    return S_OK;
}

HRESULT CBGIScript2Lua::ConvertScriptToLua(BGI_SCRIPT_INFO *pScrInfo, PWCHAR pszLuaFile)
{
    if (!file.Create(pszLuaFile))
        return TYPE_E_IOERROR;

    BOOL                             bFirstParam;
    HRESULT                          hResult;
    CHAR                             Buffer[0x5000];
    WCHAR                            szBaseLua[MAX_PATH];
    ULONG                            BeginOffset;
    INSTRUCTION_RECORD              *pRecord;
    BGI_BURIKO_SCRIPT_RECORD        *pScriptRecord;
    BGI_BURIKO_SCRIPT_INSTRUCTION   *pIns;

    lstrcpyW(szBaseLua, pszLuaFile);
    lstrcpyW(findnamew(szBaseLua), MAKE_WSTRING(SCR_NAME_DEFAULT_BASE_SCRIPT));
    CreateBaseScrLua(szBaseLua, Buffer);

    if (!file.Create(pszLuaFile))
        return TYPE_E_IOERROR;

    WideCharToMultiByte(
        CP_GB2312,
        0,
        findnamew(pszLuaFile),
        -1,
        (PCHAR)szBaseLua,
        sizeof(szBaseLua),
        NULL,
        NULL
    );

    rmexta((PCHAR)szBaseLua);
    WriteScr(szScriptInit, (PCHAR)szBaseLua);

    BeginOffset = pScrInfo->pbBegin - pScrInfo->pbScriptBuffer;

    WriteScr("%s(", SCR_FUNC_ADD_FUNC);

    bFirstParam   = TRUE;
    pScriptRecord = pScrInfo->scr.pScriptRecord;
    for (ULONG FuncCount = pScrInfo->RecordCount; FuncCount; ++pScriptRecord, --FuncCount)
    {
        if (bFirstParam)
        {
            bFirstParam = FALSE;
        }
        else
        {
            WriteScr(", ");
        }

        WriteScr("\"%s\"", pScriptRecord->FuncName);
    }

    WriteScr(")\r\n\r\n");

    pScriptRecord = pScrInfo->scr.pScriptRecord;
    for (ULONG FuncCount = pScrInfo->RecordCount; FuncCount; ++pScriptRecord, --FuncCount)
    {
        pRecord = pScriptRecord->pRecord;
        pRecord->Flags &= ~BGI_INSTRUCTION_FLAGS_LABEL;

        WriteScr("%s(\"%s\")\r\n\r\n", SCR_FUNC_BEGIN_FUNC, pScriptRecord->FuncName);

        for (ULONG RecordCount = pScriptRecord->RecordCount; RecordCount; ++pRecord, --RecordCount)
        {
            ULONG   ParamCount, Flags, OP;
            PULONG  pParam, pFlags;

            if (TEST_BITS(pRecord->Flags, BGI_INSTRUCTION_FLAGS_LABEL))
            {
                WriteScr("\r\n%s(\"%s%04X\")\r\n\r\n", SCR_NAME_LABEL, SCR_NAME_LABEL_PREFIX, pRecord->Offset);
            }

            OP = pRecord->OP;
            if (OP == SCR_NULL_OP)
                continue;

            if (IS_EX_SCR_OP(OP))
            {
                hResult = ExScriptOPHandler(pScrInfo, pRecord, Buffer);
                if (SUCCEEDED(hResult))
                    continue;
            }

            pIns = &m_pScriptInfoMap[OP];
            if (pIns->Name != NULL)
            {
                WriteScr("%s(", pIns->Name);
            }
            else
            {
                WriteScr("%s%04X(", SCR_NAME_DEFAULT_OP_PREFIX, pRecord->OP);
            }

            ParamCount = pIns->ParamCount;
            if (ParamCount != 0)
            {
                pParam = (PULONG)pRecord->pbParam;
                pFlags = pIns->pParamFlags;
                bFirstParam = TRUE;

                do
                {
                    if (!bFirstParam)
                    {
                        WriteScr(", ");
                    }

                    bFirstParam = FALSE;
                    LOOP_ONCE
                    {
                        if (pFlags != NULL)
                        {
                            Flags = *pFlags++;
                            if (TEST_BITS(Flags, BGI_INSTRUCTION_FLAGS_STRING))
                            {
                                WriteString(file, Buffer, *pParam + (PCHAR)pScrInfo->pbBegin);
                                break;
                            }
                            else if (TEST_BITS(Flags, BGI_INSTRUCTION_FLAGS_PROC))
                            {
                                PCHAR pszFuncName = IsLabelFunction(pScrInfo, *pParam + BeginOffset);

                                if (pszFuncName != NULL)
                                {
                                    WriteScr("\"%s\"", pszFuncName);
                                }
                                else
                                {
                                    WriteScr("\"%s%04X\"", SCR_NAME_LABEL_PREFIX, *pParam + BeginOffset);
                                }

                                break;
                            }
                        }

                        WriteScr("0x%X", *pParam);
                    }

                    pParam++;
                } while (--ParamCount);
            }

            WriteScr(")\r\n");
        }

        WriteScr("\r\n\r\n");
    }

    WriteScr("%s\r\n", szScriptFinalize);

    return S_OK;
}

HRESULT CBGIScript2Lua::ExScriptOPHandler(BGI_SCRIPT_INFO *pScrInfo, INSTRUCTION_RECORD *pRecord, PCHAR Buffer)
{
    ULONG   OP;
    HRESULT hResult;
    BGI_BURIKO_SCRIPT_INSTRUCTION *pIns;

    OP   = SCR_GET_EX_OP(pRecord->OP);
    pIns = &g_BurikoScriptInfo[countof(g_BurikoScriptInfo) - (SCR_EX_OP_LAST - SCR_EX_OP_FIRST)];

    switch (pRecord->OP)
    {
        case SCR_EX_Say:
            WriteScr("%s(", SCR_FUNC_SAY);
            WriteString(file, Buffer, (PCHAR)(*(PULONG)pRecord[0].pbParam + pScrInfo->pbBegin));
            WriteScr(", ");
            WriteString(file, Buffer, (PCHAR)(*(PULONG)pRecord[1].pbParam + pScrInfo->pbBegin));
            WriteScr(")\r\n");
            break;

        case SCR_EX_AutoSay:
            WriteScr("%s(", SCR_FUNC_AUTO_SAY);
            WriteString(file, Buffer, (PCHAR)(*(PULONG)pRecord[1].pbParam + pScrInfo->pbBegin));
            WriteScr(", ");
            WriteString(file, Buffer, (PCHAR)(*(PULONG)pRecord[0].pbParam + pScrInfo->pbBegin));
            WriteScr(")\r\n");
            break;

        case SCR_EX_AutoText:
            WriteScr("%s(", SCR_FUNC_AUTO_TEXT);
            goto WRITE_FUNC_TEXT_PARAM;

        case SCR_EX_Text:
            WriteScr("%s(", SCR_FUNC_TEXT);
            goto WRITE_FUNC_TEXT_PARAM;

        case SCR_EX_Select:
            WriteScr("%s(", SCR_FUNC_SELECT);
            goto WRITE_FUNC_TEXT_PARAM;

        case SCR_EX_Voice:
            WriteScr("%s(", SCR_FUNC_VOICE);
            goto WRITE_FUNC_TEXT_PARAM;

        case SCR_EX_Debug:
            WriteScr("%s(", SCR_FUNC_DEBUG);
//            goto WRITE_FUNC_TEXT_PARAM;

WRITE_FUNC_TEXT_PARAM:

            WriteString(file, Buffer, (PCHAR)(*(PULONG)pRecord->pbParam + pScrInfo->pbBegin));
            WriteScr(")\r\n");
            break;
    }

    return S_OK;
}

PCHAR CBGIScript2Lua::IsLabelFunction(BGI_SCRIPT_INFO *pScrInfo, ULONG Offset)
{
    BGI_BURIKO_SCRIPT_RECORD *pScriptRecord = pScrInfo->scr.pScriptRecord;

    for (ULONG FuncCount = pScrInfo->RecordCount; FuncCount; ++pScriptRecord, --FuncCount)
    {
        if (pScriptRecord->pRecord != NULL && pScriptRecord->pRecord->Offset == Offset)
            return pScriptRecord->FuncName;
    }

    return NULL;
}

HRESULT CBGIScript2Lua::WriteText(CFileDisk &file, PCHAR pBuffer, LPCSTR pszFormat, ...)
{
    ULONG   Length;
    va_list pArg;

    va_start(pArg, pszFormat);
    Length = vsprintf(pBuffer, pszFormat, pArg);
    if (Length == -1)
        return E_NOT_SUFFICIENT_BUFFER;

    return file.Write(pBuffer, Length) ? S_OK : TYPE_E_IOERROR;
}

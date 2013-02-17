#include "ybn2lua.h"
#include "Info.h"

CYBNToLua::CYBNToLua()
{
    m_YbnInfo.pYbn      = NULL;
    m_pParamDataInfo    = NULL;
    m_pFuncInfo         = NULL;
}

CYBNToLua::~CYBNToLua()
{
    Reset();
    m_mem.SafeFree(&m_pFuncInfo);
    m_mem.SafeFree(&m_pParamDataInfo);
}

VOID CYBNToLua::Reset()
{
    m_mem.SafeFree(&m_YbnInfo.pYbn);
    if (m_pParamDataInfo == NULL)
    {
        m_pParamDataInfo = (YBN_PARAM_DATA_INFO *)m_mem.Alloc(DATA_LAST * sizeof(*m_pParamDataInfo), HEAP_ZERO_MEMORY);
        if (m_pParamDataInfo != NULL)
        {
            YBN_PARAM_DATA_INFO *pDataInfo;

            pDataInfo = g_ParamDataInfo;
            for (ULONG Count = countof(g_ParamDataInfo); Count; ++pDataInfo, --Count)
            {
                m_pParamDataInfo[pDataInfo->DataOP] = *pDataInfo;
            }
        }
    }

    if (m_pFuncInfo == NULL)
    {
        m_pFuncInfo = (YBN_FUNCTION_INFO *)m_mem.Alloc(256 * sizeof(*m_pFuncInfo), HEAP_ZERO_MEMORY);

        if (m_pFuncInfo != NULL)
        {
            YBN_FUNCTION_INFO *pFuncInfo;

            pFuncInfo = g_FuncInfo;
            for (ULONG Count = countof(g_FuncInfo); Count; ++pFuncInfo, --Count)
            {
                m_pFuncInfo[pFuncInfo->FuncID] = *pFuncInfo;
            }
        }
    }
}

BOOL CYBNToLua::WriteText(CFileDisk &file, PCHAR pBuffer, LPCSTR pszFormat, ...)
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

BOOL CYBNToLua::ConvertYbnToLua(PCWCHAR pszFileName)
{
    ULONG               Size;
    CFileDisk           file;
    YU_RIS_YBN_HEADER   header;

    if (!file.Open(pszFileName))
        return FALSE;

    if (!file.Read(&header, sizeof(header)))
        return FALSE;

    if (header.Magic != YBN_MAGIC)
        return FALSE;

    Reset();

    Size = file.GetSize();
    m_YbnInfo.pYbn = (YU_RIS_YBN_HEADER *)m_mem.Alloc(Size);
    if (m_YbnInfo.pYbn == NULL)
        return FALSE;

    *m_YbnInfo.pYbn = header;
    if (!file.Read(m_YbnInfo.pYbn + 1, Size - sizeof(header)))
        return FALSE;

    if (!ParseYbn(&m_YbnInfo, Size))
        return FALSE;

    return ConvertToLua(&m_YbnInfo, pszFileName);
}

BOOL CYBNToLua::ParseYbn(YU_RIS_YBN_INFO *pYbnInfo, ULONG BufferSize)
{
    PBYTE pbEnd = (PBYTE)pYbnInfo->pYbn + BufferSize;

    switch (pYbnInfo->pYbn->Version)
    {
        case 0x1C2:
            break;

        default:
            return FALSE;
    }

    pYbnInfo->pFunc = (YU_RIS_YBN_FUNCTION *)(pYbnInfo->pYbn + 1);
    if ((PBYTE)pYbnInfo->pFunc >= pbEnd)
        return FALSE;

    pYbnInfo->pParam = (YU_RIS_YBN_FUNCTION_PARAM *)((ULONG_PTR)pYbnInfo->pFunc + pYbnInfo->pYbn->FunctionSize);
    if ((PBYTE)pYbnInfo->pParam >= pbEnd)
        return FALSE;

    pYbnInfo->pData = (PYU_RIS_FUNCTION_DATA)((ULONG_PTR)pYbnInfo->pParam + pYbnInfo->pYbn->FunctionParamSize);
    if ((PBYTE)pYbnInfo->pData >= pbEnd)
        return FALSE;

    pYbnInfo->pUnknown = (PULONG)((ULONG_PTR)pYbnInfo->pData + pYbnInfo->pYbn->ParamDataSize);

    return (PBYTE)pYbnInfo->pUnknown < pbEnd;
}

BOOL
CYBNToLua::
WriteParam(
    YU_RIS_YBN_INFO             *pYbnInfo,
    YU_RIS_YBN_FUNCTION         *pFunc,
    YU_RIS_YBN_FUNCTION_PARAM   *pParam,
    YBN_FUNCTION_INFO           *pFuncInfo,
    CFileDisk                   &file,
    PCHAR                        Buffer
)
{
    PYU_RIS_FUNCTION_DATA pData;

    for (ULONG Index = 0, ParamCount = pFunc->ParamCount; ParamCount; ++pParam, ++Index, --ParamCount)
    {
        if (TEST_BITS(pFuncInfo->Flags, FUNC_FLAG_INITIALIZED) &&
            pFuncInfo->ParamCount < FUNC_NO_PARAM &&
            pFuncInfo->ParamCount < Index)
        {
/*
            WriteScr(
                "%s%s(0x%08X, 0x%X, 0x%X)",
                Index == 0 ? "" : ", ",
                NAME_FUNC_DUMMY_PARAM_LOCAL,
                *(PULONG)pParam->Option, pParam->DataLength, pParam->DataOffset
            );
*/
            continue;
        }

        WriteScr("%s%s(0x%08X", Index == 0 ? "" : ", ", NAME_FUNC_MAKE_PARAM_LOCAL, *(PULONG)pParam->Option);

        if (pParam->DataLength == 0)
            goto FUNC_PARAM_TAIL;

        pData = (PYU_RIS_FUNCTION_DATA)((ULONG_PTR)pYbnInfo->pData + pParam->DataOffset);
        if (pParam->DataLength > 0x30)
        {
            printf(
                "FuncID  = %02X       @ %08X\n"
                "Options = %08X @ %08X\n"
                "Offset  = %08X @ %08X\n"
                "Length  = %08X\n",
                pFunc->FuncID, (ULONG_PTR)pFunc - (ULONG_PTR)pYbnInfo->pYbn,
                *(PULONG)pParam->Option, (ULONG_PTR)pParam - (ULONG_PTR)pYbnInfo->pYbn,
                pParam->DataOffset, (ULONG_PTR)pData - (ULONG_PTR)pYbnInfo->pYbn,
                pParam->DataLength
            );

            getch();
            goto FUNC_PARAM_TAIL;
        }

        if (!WriteData(pData, pParam->DataLength, file, Buffer))
            return FALSE;

FUNC_PARAM_TAIL:

        WriteScr(")");
    }

    return TRUE;
}

BOOL CYBNToLua::WriteData(PYU_RIS_FUNCTION_DATA pData, ULONG DataLength, CFileDisk &file, PCHAR Buffer)
{
    ULONG DataFlag;
    PBYTE pbDataEnd;

    pbDataEnd = (PBYTE)pData + DataLength;
    while ((PBYTE)pData < pbDataEnd)
    {
        DataFlag = m_pParamDataInfo[pData->Type].Flags;

        if (TEST_BITS(DataFlag, DATA_FLAG_NUMBER))
        {
            ULONG64 Value = *(PULONG64)pData->Data & (((ULONG64)1 << (pData->Length * 8)) - 1);
            WriteScr(", 0x%I64X", Value);
            goto FUNC_DATA_TAIL;
        }

        if (TEST_BITS(DataFlag, DATA_FLAG_STRING))
        {
            CHAR bak = pData->Data[pData->Length];
            BOOL Result;

            pData->Data[pData->Length] = 0;
            Result = WriteText(file, Buffer, ", %s([[%s]])", NAME_FUNC_STRING, pData->Data);
            pData->Data[pData->Length] = bak;

            if (!Result)
                return Result;

            goto FUNC_DATA_TAIL;
        }

        if (pData->Length == 0)
        {
            WriteScr(", %s%02X()", NAME_FUNC_DATA_PREFIX, pData->Type);
        }
        else
        {
            WriteScr(", %s%02X(0x%I64X)", NAME_FUNC_DATA_PREFIX, pData->Type, *(PULONG64)pData->Data & (((ULONG64)1 << (pData->Length * 8)) - 1));
        }

FUNC_DATA_TAIL:
        pData = (PYU_RIS_FUNCTION_DATA)((ULONG_PTR)pData->Data + pData->Length);
    }

    return TRUE;
}

BOOL CYBNToLua::ConvertToLua(YU_RIS_YBN_INFO *pYbnInfo, PCWCHAR pszYbnName)
{
    CFileDisk file;
    PWCHAR pszFileName;
    CHAR  Buffer[0x5000];
    WCHAR szFile[MAX_PATH];

    YU_RIS_YBN_HEADER         *pYbn;
    YU_RIS_YBN_FUNCTION       *pFunc;
    YU_RIS_YBN_FUNCTION_PARAM *pParam;
    PULONG                     pUnknown;

    lstrcpyW(szFile, pszYbnName);
    pszFileName = findnamew(szFile);
    lstrcpyW(findextw(pszFileName), MAKE_WSTRING(NAME_SCRIPT_EXTENSION));
    if (!file.Create(szFile))
        return FALSE;

    lstrcpyW(pszFileName, MAKE_WSTRING(NAME_DEFAULT_BASE_SCRIPT));
    CreateBaseScript(szFile, Buffer);

    WideCharToMultiByte(
        CP_GB2312,
        0,
        pszFileName - szFile + pszYbnName,
        -1,
        (PCHAR)szFile,
        sizeof(szFile),
        NULL,
        NULL);

    WriteScr(szScriptInit, szFile);

    pYbn        = pYbnInfo->pYbn;
    pFunc       = pYbnInfo->pFunc;
    pParam      = pYbnInfo->pParam;
    pUnknown    = pYbnInfo->pUnknown;

    for (ULONG FuncCount = pYbn->FunctionCount; FuncCount; ++pFunc, --FuncCount)
    {
        ULONG FuncID;
        YBN_FUNCTION_INFO *pFuncInfo;

        FuncID = pFunc->FuncID;
        pFuncInfo = &m_pFuncInfo[FuncID];
        if (TEST_BITS(pFuncInfo->ParamCount, 0xFFFF0000))
        {
            if ((this->*pFuncInfo->Handler)(file, Buffer, pFuncInfo, pYbnInfo, pFunc, pParam))
            {
                pParam += pFunc->ParamCount;
                continue;
            }
        }

        if (pFuncInfo->pszFuncName == NULL)
        {
            WriteScr("%s%02X(", NAME_FUNC_FUNCTION_PREFIX, FuncID);
        }
        else
        {
            WriteScr("%s(", pFuncInfo->pszFuncName);
        }

        if (!WriteParam(pYbnInfo, pFunc, pParam, pFuncInfo, file, Buffer))
            return FALSE;

        pParam += pFunc->ParamCount;
        WriteScr(")\r\n");
    }

    return TRUE;
}

BOOL CYBNToLua::CreateBaseScript(PWCHAR pszFileName, PCHAR Buffer)
{
    UNREFERENCED_PARAMETER(Buffer);

    if (IsPathExistsW(pszFileName))
        return TRUE;

    CFileDisk file;

    if (!file.Create(pszFileName))
        return FALSE;

    return TRUE;
}

DECL_YBN_HANDLER(CYBNToLua::Func1E)
{
    PULONG pParam1E;
    YU_RIS_YBN_FUNCTION   Func;
    PYU_RIS_FUNCTION_DATA pData;

    UNREFERENCED_PARAMETER(file);
    UNREFERENCED_PARAMETER(Buffer);
    UNREFERENCED_PARAMETER(pFuncInfo);
    UNREFERENCED_PARAMETER(pFunc);
    UNREFERENCED_PARAMETER(pYbnInfo);
    UNREFERENCED_PARAMETER(pParam);

    pParam1E = (PULONG)(pParam + 1);
    pData = (PYU_RIS_FUNCTION_DATA)((ULONG_PTR)pParam + pParam->DataOffset);

    if (pFunc->ParamCount != 3)
    {
        printf(
            "Invalid Func1E @ %08X\n"
            "Param Count:  %X\n"
            "Param      :@ %08X\n"
            "Data       :@ %08X\n",
            (ULONG_PTR)pFunc - (ULONG_PTR)pYbnInfo->pYbn,
            pFunc->ParamCount,
            (ULONG_PTR)pParam - (ULONG_PTR)pYbnInfo->pYbn,
            (ULONG_PTR)pData - (ULONG_PTR)pYbnInfo->pYbn
        );
        getch();
    }

    WriteScr("%s(", pFuncInfo->pszFuncName);

    Func = *pFunc;
    Func.ParamCount = 1;
    if (!WriteParam(pYbnInfo, &Func, pParam, pFuncInfo, file, Buffer))
        return FALSE;

    for (ULONG Count = 2 * sizeof(YU_RIS_YBN_FUNCTION_PARAM) / sizeof(ULONG); Count; --Count)
    {
        WriteScr(", 0x%X", *pParam1E++);
    }

    WriteScr(")\r\n");

    return TRUE;
}

BOOL
CYBNToLua::
SetText(
    CFileDisk                   &file,
    PCHAR                        Buffer,
    YBN_FUNCTION_INFO           *pFuncInfo,
    YU_RIS_YBN_INFO             *pYbnInfo,
    YU_RIS_YBN_FUNCTION         *pFunc,
    YU_RIS_YBN_FUNCTION_PARAM   *pParam
)
{
    CHAR bak;
    BOOL Result;
    PBYTE pbData;

    UNREFERENCED_PARAMETER(pFunc);

    for (ULONG ParamCount = pFunc->ParamCount; ParamCount; ++pParam, --ParamCount)
    {
        pbData = (PBYTE)(pParam->DataOffset + (ULONG_PTR)pYbnInfo->pData);

        bak = pbData[pParam->DataLength];
        pbData[pParam->DataLength] = 0;
        Result = WriteText(file, Buffer, "%s([[%s]])\r\n", pFuncInfo->pszFuncName, pbData);
        pbData[pParam->DataLength] = bak;
    }

    return TRUE;
}

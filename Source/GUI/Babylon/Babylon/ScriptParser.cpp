#include "ScriptParser.h"
#include "FileDisk.h"
#include "Mem.h"

#define SCRIPT_PARSER_CHECK_BUFFER_SIZE(BufferSize, InfoBufferType) \
        if (BufferSize < sizeof(InfoBufferType)) \
            return BL_ERROR_NOT_ENOUGH_BUFFER;

Long
CBLScriptParser::
Parse(
    PTChar         pszScriptPath,
    SBLScriptBase *pScriptInfo,
    SizeT          BufferSize
)
{
    Long  Result;
    PVoid pBuffer;
    CFileDisk file;

    if (pScriptInfo == NULL)
        return BL_ERROR_INVALID_PARAMETER;

    pScriptInfo->ScriptType = BL_SCRIPT_TYPE_UNKNOWN;

    if (!file.Open(pszScriptPath))
        return BL_ERROR_IO_FAILED;

    pBuffer = mem.Alloc(file.GetSize());
    if (pBuffer == NULL)
        return BL_ERROR_OUT_OF_MEMORY;

    file.Read(pBuffer);

    Result = Parse(pBuffer, file.GetSize(), pScriptInfo, BufferSize);
    mem.Free(pBuffer);

    return Result;
}

Long
CBLScriptParser::
Parse(
    PVoid          pScript,
    SizeT          ScriptSize,
    SBLScriptBase *pScriptInfo,
    SizeT          BufferSize
)
{
    Long      Result;
    SXmlInfo  XmlInfo;
    SXmlNode *pNode;

    if (pScript == NULL || pScriptInfo == NULL)
        return BL_ERROR_INVALID_PARAMETER;

    pScriptInfo->ScriptType = BL_SCRIPT_TYPE_UNKNOWN;

    if (!XmlParse(pScript, &XmlInfo))
        return BL_ERROR_INVALID_FORMAT;

    pNode = XmlInfo.pNode;
    if (pNode == NULL)
        return BL_ERROR_INVALID_FORMAT;

    if (!StrCompare(pNode->pszNodeName, BL_SCRIPT_CONFIG_ROOT_TAG))
    {
        Result = ParseScriptConfig(&XmlInfo, (SBLScriptConfig *)pScriptInfo, BufferSize);
    }
    else if (!StrCompare(pNode->pszNodeName, BL_SCRIPT_LIST_ROOT_TAG))
    {
        Result = ParseScriptGameList(&XmlInfo, (SBLScriptGameList *)pScriptInfo, BufferSize);
    }
    else if (!StrCompare(pNode->pszNodeName, BL_SCRIPT_PLUGIN_ROOT_TAG))
    {
        Result = ParseScriptPlugin(&XmlInfo, (SBLScriptPlugin *)pScriptInfo, BufferSize);
    }
    else
    {
        Result = BL_ERROR_INVALID_FORMAT;
    }

    XmlDestroy(&XmlInfo);
    if (BL_FAILED(Result))
        FreeScriptInfo(pScriptInfo);

    return Result;
}

Long CBLScriptParser::FreeScriptInfo(SBLScriptBase *pScriptInfo)
{
    Long Result;

    if (pScriptInfo == NULL)
        return BL_ERROR_INVALID_PARAMETER;

    switch (pScriptInfo->ScriptType)
    {
        case BL_SCRIPT_TYPE_CONFIG:
            Result = FreeScriptConfig((SBLScriptConfig *)pScriptInfo);
            break;

        case BL_SCRIPT_TYPE_LIST:
            Result = FreeScriptGameList((SBLScriptGameList *)pScriptInfo);
            break;

        default:
            Result = BL_ERROR_INVALID_PARAMETER;
    }

    return Result;
}

Long
CBLScriptParser::
ParseScriptConfig(
    SXmlInfo        *pXmlInfo,
    SBLScriptConfig *pScriptConfig,
    SizeT            BufferSize
)
{
    SCRIPT_PARSER_CHECK_BUFFER_SIZE(BufferSize, SBLScriptConfig);

    ULong     GameTypeCount, BlockSize;
    SXmlNode *pNode;
    SBLScriptGameTypeItem *pGameType;

    ZeroMemory(pScriptConfig, sizeof(*pScriptConfig));
    pScriptConfig->ScriptType = BL_SCRIPT_TYPE_CONFIG;

    pNode = pXmlInfo->pNode->pSubNode;
    if (pNode == NULL)
        return BL_ERROR_INVALID_FORMAT;

    GameTypeCount = 0;
    for (ULong i = pXmlInfo->pNode->NodeCount; i; --i)
    {
        if (!StrCompare(pNode->pszNodeName, BL_SCRIPT_CONFIG_GROUP_TAG))
            ++GameTypeCount;
        ++pNode;
    }

    if (GameTypeCount == 0)
        return BL_ERROR_INVALID_FORMAT;

    BlockSize = GameTypeCount * sizeof(*pScriptConfig->pGameType);
    pScriptConfig->pGameType = (SBLScriptGameTypeItem *)mem.Alloc(BlockSize, HEAP_ZERO_MEMORY);
    if (pScriptConfig->pGameType == NULL)
        return BL_ERROR_OUT_OF_MEMORY;

    pNode = pXmlInfo->pNode->pSubNode;
    pScriptConfig->GameTypeCount = GameTypeCount;
    pGameType = pScriptConfig->pGameType;
    for (; GameTypeCount; ++pNode)
    {
        if (StrCompare(pNode->pszNodeName, BL_SCRIPT_CONFIG_GROUP_TAG))
            continue;

        SXmlAttribute *pAttribute;

        pAttribute = XmlFindAttribute(pNode, BL_SCRIPT_CONFIG_GROUP_NAME, NULL);
        if (pAttribute != NULL)
            pGameType->GameType = BLNewString(pAttribute->pszValue);

        pAttribute = XmlFindAttribute(pNode, BL_SCRIPT_CONFIG_GROUP_FILE, NULL);
        if (pAttribute != NULL)
            pGameType->ListScriptPath = BLNewString(pAttribute->pszValue);

        ++pGameType;
        --GameTypeCount;
    }

    return BL_ERROR_SUCCEES;
}

Long CBLScriptParser::FreeScriptConfig(SBLScriptConfig *pScriptConfig)
{
    SBLScriptGameTypeItem *pGameType;

    pGameType = pScriptConfig->pGameType;
    if (pGameType != NULL)
    {
        for (ULong i = pScriptConfig->GameTypeCount; i; --i)
        {
            BLFreeString(pGameType->GameType);
            BLFreeString(pGameType->ListScriptPath);
            ++pGameType;
        }

        mem.SafeFree(&pScriptConfig->pGameType);
    }

    return BL_ERROR_SUCCEES;
}

Long
CBLScriptParser::
ParseScriptGameList(
    SXmlInfo          *pXmlInfo,
    SBLScriptGameList *pScriptInfo,
    SizeT              BufferSize
)
{
    SCRIPT_PARSER_CHECK_BUFFER_SIZE(BufferSize, SBLScriptGameList);

    ULong     GroupCount, BlockSize;
    SXmlNode *pNode;
    SBLScriptGameInfo  *pGameList;
    SBLScriptGameListGroup *pGameGroup;

    pNode = pXmlInfo->pNode->pSubNode;
    if (pNode == NULL)
        return BL_ERROR_INVALID_FORMAT;

    ZeroMemory(pScriptInfo, sizeof(*pScriptInfo));
    pScriptInfo->ScriptType = BL_SCRIPT_TYPE_LIST;

    GroupCount = 0;
    for (ULong i = pXmlInfo->pNode->NodeCount; i; --i)
    {
        if (!StrCompare(pNode->pszNodeName, BL_SCRIPT_LIST_GROUP_TAG))
            ++GroupCount;
        ++pNode;
    }

    BlockSize = GroupCount * sizeof(*pScriptInfo->pGameGroup);
    pScriptInfo->pGameGroup = (SBLScriptGameListGroup *)mem.Alloc(BlockSize, HEAP_ZERO_MEMORY);
    if (pScriptInfo->pGameGroup == NULL)
        return BL_ERROR_OUT_OF_MEMORY;

    pScriptInfo->GroupCount = GroupCount;
    pGameGroup = pScriptInfo->pGameGroup;

    pNode = pXmlInfo->pNode->pSubNode;
    for (; GroupCount; ++pNode)
    {
        if (StrCompare(pNode->pszNodeName, BL_SCRIPT_LIST_GROUP_TAG))
            continue;

        SXmlNode      *pNodeGameInfo;
        SXmlAttribute *pAttribute;

        --GroupCount;

        pNodeGameInfo = pNode->pSubNode;
        if (pNodeGameInfo == NULL)
            continue;

        pAttribute = XmlFindAttribute(pNode, BL_SCRIPT_LIST_GROUP_NAME, NULL);
        if (pAttribute != NULL)
        {
            pGameGroup->pszGroupName = BLNewString(pAttribute->pszValue);
            if (pGameGroup->pszGroupName == NULL)
                return BL_ERROR_OUT_OF_MEMORY;
        }

        BlockSize = pNode->NodeCount * sizeof(*pGameGroup->pGameInfo);
        pGameGroup->pGameInfo = (SBLScriptGameInfo *)mem.Alloc(BlockSize, HEAP_ZERO_MEMORY);
        if (pGameGroup->pGameInfo == NULL)
            return BL_ERROR_OUT_OF_MEMORY;

        pGameGroup->GameCount = 0;
        pGameList = pGameGroup->pGameInfo;
        for (ULong GameListCount = pNode->NodeCount; GameListCount; --GameListCount)
        {
            pAttribute = XmlFindAttribute(pNodeGameInfo, BL_SCRIPT_LIST_GAME_INFO_NAME, NULL);
            if (pAttribute != NULL)
                pGameList->GameName = BLNewString(pAttribute->pszValue);

            pAttribute = XmlFindAttribute(pNodeGameInfo, BL_SCRIPT_LIST_GAME_INFO_PATH, NULL);
            if (pAttribute != NULL)
                pGameList->ScriptPath = BLNewString(pAttribute->pszValue);

            pAttribute = XmlFindAttribute(pNodeGameInfo, BL_SCRIPT_LIST_GAME_INFO_CODEPAGE, NULL);
            if (pAttribute != NULL)
            {
                if (!StrICompare(pAttribute->pszValue, _T("GB2312")) ||
                    !StrICompare(pAttribute->pszValue, _T("GBK")))
                {
                    pGameList->FileNameCodePage = CP_GB2312;
                }
                else if (!StrICompare(pAttribute->pszValue, _T("UNICODE")) ||
                         !StrICompare(pAttribute->pszValue, _T("UTF16")))
                {
                    pGameList->FileNameCodePage = CP_UTF16_LE;
                }
                else if (!StrICompare(pAttribute->pszValue, _T("SHIFT-JIS")) ||
                         !StrICompare(pAttribute->pszValue, _T("SHIFTJIS")))
                {
                    pGameList->FileNameCodePage = CP_SHIFTJIS;
                }
                else if (!StrICompare(pAttribute->pszValue, _T("BIG5")))
                {
                    pGameList->FileNameCodePage = CP_BIG5;
                }
                else
                {
                    pGameList->FileNameCodePage = (UInt)StringToInt64(pAttribute->pszValue);
                }
            }
            else
            {
                pGameList->FileNameCodePage = CP_ACP;
            }

            ++pGameList;
            ++pNodeGameInfo;
            ++pGameGroup->GameCount;
        }

        ++pGameGroup;
    }

    return BL_ERROR_SUCCEES;
}

Long CBLScriptParser::FreeScriptGameList(SBLScriptGameList *pScriptGameList)
{
    SBLScriptGameListGroup *pGameGroup;
    SBLScriptGameInfo  *pGameList;

    pGameGroup = pScriptGameList->pGameGroup;
    for (ULong GroupCount = pScriptGameList->GroupCount; GroupCount; --GroupCount)
    {
        BLFreeString(pGameGroup->pszGroupName);
        pGameList = pGameGroup->pGameInfo;
        for (ULong GameCount = pGameGroup->GameCount; GameCount; --GameCount)
        {
            BLFreeString(pGameList->GameName);
            BLFreeString(pGameList->ScriptPath);
            ++pGameList;
        }

        mem.SafeFree(&pGameGroup->pGameInfo);
        pGameGroup->GameCount = 0;
        ++pGameGroup;
    }

    pScriptGameList->GroupCount = 0;
    mem.SafeFree(&pScriptGameList->pGameGroup);

    return BL_ERROR_SUCCEES;
}

Long
CBLScriptParser::
ParseScriptPlugin(
    SXmlInfo        *pXmlInfo,
    SBLScriptPlugin *pScriptInfo,
    SizeT            BufferSize
)
{
    SCRIPT_PARSER_CHECK_BUFFER_SIZE(BufferSize, SBLScriptPlugin);

    return BL_ERROR_SUCCEES;
}
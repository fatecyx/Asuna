#ifndef _SCRIPTPARSER_H_
#define _SCRIPTPARSER_H_

#include "../common/bl_common.h"
#include "../common/my_xml.h"

#define BL_SCRIPT_CONFIG_ROOT_TAG          _T("主程序设置")
#define BL_SCRIPT_CONFIG_GROUP_TAG         _T("分类")
#define BL_SCRIPT_CONFIG_GROUP_NAME        _T("名称")
#define BL_SCRIPT_CONFIG_GROUP_FILE        _T("文件")

#define BL_SCRIPT_LIST_ROOT_TAG            _T("游戏列表")
#define BL_SCRIPT_LIST_GROUP_TAG           _T("分类")
#define BL_SCRIPT_LIST_GROUP_NAME          _T("名称")
#define BL_SCRIPT_LIST_GAME_INFO_TAG       _T("游戏")
#define BL_SCRIPT_LIST_GAME_INFO_NAME      _T("名称")
#define BL_SCRIPT_LIST_GAME_INFO_PATH      _T("文件")
#define BL_SCRIPT_LIST_GAME_INFO_CODEPAGE  _T("编码")

#define BL_SCRIPT_PLUGIN_ROOT_TAG          _T("游戏脚本")
#define BL_SCRIPT_PLUGIN_MANUAL_SPEC       _T("手动指定文件插件")
#define BL_SCRIPT_PLUGIN_PLUGIN_TAG        _T("插件")
#define BL_SCRIPT_PLUGIN_PLUGIN_PATH       _T("文件名")
#define BL_SCRIPT_PLUGIN_PLUGIN_INTERFACE  _T("接口名")
#define BL_SCRIPT_PLUGIN_FILE_TAG          _T("文件")
#define BL_SCRIPT_PLUGIN_FILE_NAME         _T("文件名")
#define BL_SCRIPT_PLUGIN_FILE_PLUGININDEX  _T("插件")
#define BL_SCRIPT_PLUGIN_FILE_DATAFILE     _T("数据文件")
#define BL_SCRIPT_PLUGIN_FILE_BEGIN        _T("起始")
#define BL_SCRIPT_PLUGIN_FILE_END          _T("结束")
#define BL_SCRIPT_PLUGIN_FILE_CODEPAGE     _T("编码")

enum // EScriptType
{
    BL_SCRIPT_TYPE_UNKNOWN = 0,
    BL_SCRIPT_TYPE_CONFIG,
    BL_SCRIPT_TYPE_LIST,
    BL_SCRIPT_TYPE_PLUGIN
};

#pragma pack(4)

struct SBLScriptBase
{
    ULong ScriptType;
};

typedef struct
{
    PTChar GameType;
    PTChar ListScriptPath;
} SBLScriptGameTypeItem;

struct SBLScriptConfig : public SBLScriptBase
{
    ULong GameTypeCount;
    SBLScriptGameTypeItem *pGameType;
};

typedef struct
{
    PTChar GameName;
    PTChar ScriptPath;
    UInt   FileNameCodePage;
} SBLScriptGameInfo;

typedef struct
{
    PTChar pszGroupName;
    ULong  GameCount;
    SBLScriptGameInfo *pGameInfo;
} SBLScriptGameListGroup;

struct SBLScriptGameList : public SBLScriptBase
{
    ULong GroupCount;
    SBLScriptGameListGroup *pGameGroup;
};

struct SBLScriptPlugin : public SBLScriptBase
{
    Int    pluginID;   // 插件索引号
    Char  *fileNameA;  // 搜索文件名A
    WChar *fileNameW;  // 搜索文件名W
    WChar *dataName;   // 数据文件名
    UInt32 head;       // 文件起始偏移
    UInt32 tail;       // 文件结束偏移
};

#pragma pack()

class CBLScriptParser
{
protected:
    CMem  mem;
public:
    Long Parse(PTChar pszScriptPath, SBLScriptBase *pScriptInfo, SizeT BufferSize);
    Long Parse(PVoid pScript, SizeT ScriptSize, SBLScriptBase *pScriptInfo, SizeT BufferSize);
    Long FreeScriptInfo(SBLScriptBase *pScriptInfo);

protected:
    Long ParseScriptConfig  (SXmlInfo *pXmlInfo, SBLScriptConfig *pScriptConfig, SizeT BufferSize);
    Long ParseScriptGameList(SXmlInfo *pXmlInfo, SBLScriptGameList *pScriptGameList, SizeT BufferSize);
    Long ParseScriptPlugin  (SXmlInfo *pXmlInfo, SBLScriptPlugin *pScriptPlugin, SizeT BufferSize);

    Long FreeScriptConfig  (SBLScriptConfig   *pScriptConfig);
    Long FreeScriptGameList(SBLScriptGameList *pScriptGameList);
    Long FreeScriptPlugin  (SBLScriptPlugin   *pScriptPlugin);
};

#endif /* _SCRIPTPARSER_H_ */
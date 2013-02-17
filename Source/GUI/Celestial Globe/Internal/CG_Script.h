#ifndef _CG_SCRIPT_H_d4093740_7b53_4a0b_83c3_c92c9b8cd37e
#define _CG_SCRIPT_H_d4093740_7b53_4a0b_83c3_c92c9b8cd37e

#include "pragma_once.h"
#include "CG_Types.h"
#include "CG_Interface.h"
#include "CG_Plugin.h"
#include "CG_Core.h"

enum CGScriptType
{
    CG_SCRIPT_TYPE_UNKNOWN = 0,
    CG_SCRIPT_TYPE_CONFIG,
    CG_SCRIPT_TYPE_GAME_LIST,
    CG_SCRIPT_TYPE_PLUGIN
};

struct CG_SCRIPT_BASE
{
    CGScriptType ScriptType;
};


// core config script

typedef struct
{
    UNICODE_STRING Name;
    UNICODE_STRING ScriptPath;
} CG_GAME_CATEGORY_ENTRY;

typedef struct
{
    ULONG                   Count;
    CG_GAME_CATEGORY_ENTRY *pCategory;
} CG_GAME_CATEGORY;

struct CG_SCRIPT_CORE_CONFIG : public CG_SCRIPT_BASE
{

    ULONG               BackgroundColor;
    UNICODE_STRING      UIModule;
    UNICODE_STRING      ImagePlugin;
    CG_GAME_CATEGORY    Category;
};


// game list script

struct CG_GAME_LIST;

typedef struct
{
    UNICODE_STRING  Name;
    UNICODE_STRING  ScriptPath;
    ULONG           Encoding;
} CG_GAME_INFO_ENTRY;

struct CG_GAME_LIST
{
    CG_CORE_OPTION      Option;
    ULONG               Count;
    CG_GAME_INFO_ENTRY *pGameInfo;
};

struct CG_SCRIPT_GAME_LIST : public CG_SCRIPT_BASE
{
    ULONG           Count;
    CG_GAME_LIST   *pGameList;
};


// plugin script

enum CGPluginDataEntryType
{
    CG_PLUGIN_DATA_ENTRY_CONFIG,
    CG_PLUGIN_DATA_ENTRY_PLUGIN,
    CG_PLUGIN_DATA_ENTRY_FILE,
};

typedef struct
{
    ULONG Type;
    union
    {
        struct
        {
        } Config;

        struct
        {
            ULONG           InterfaceID;
            UNICODE_STRING  PluginPath;
            UNICODE_STRING  InterfaceName;
            UNICODE_STRING  Parameter;
        } Plugin;

        struct
        {
            USHORT          InterfaceID;
            USHORT          Encoding;
            UNICODE_STRING  FileNameFilter;
            UNICODE_STRING  DataFilePath;
            UNICODE_STRING  Parameter;
            LARGE_INTEGER   BeginOffset;
            LARGE_INTEGER   EndOffset;
        } File;
    };
} CG_PLUGIN_DATA_ENTRY;

struct CG_SCRIPT_PLUGIN : public CG_SCRIPT_BASE
{
    ULONG                   Count;
    CG_PLUGIN_DATA_ENTRY   *pEntry;
};

#endif // _CG_SCRIPT_H_d4093740_7b53_4a0b_83c3_c92c9b8cd37e

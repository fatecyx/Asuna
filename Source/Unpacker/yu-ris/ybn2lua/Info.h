#ifndef _INFO_H_
#define _INFO_H_

#include "pragma_once.h"
#include "my_headers.h"
#include "ybn2lua.h"

#define NAME_DEFAULT_BASE_SCRIPT_NAME   "YbnBase"
#define NAME_DEFAULT_BASE_SCRIPT        "YbnBase.lua"
#define NAME_SCRIPT_EXTENSION           ".lua"

#if 1

#define NAME_FUNC_FUNCTION_PREFIX       "Func"
#define NAME_FUNC_DATA_PREFIX           "Data"
#define NAME_FUNC_STRING                "Str"
#define NAME_FUNC_MAKE_PARAM            "MakeParam"
#define NAME_FUNC_MAKE_DUMMY_PARAM      "DummyParam"
#define NAME_FUNC_MAKE_PARAM_LOCAL      "P"
#define NAME_FUNC_DUMMY_PARAM_LOCAL     "DP"

#define NAME_FUNC_1E                    "Func1E"
#define NAME_FUNC_29                    "Func29"
#define NAME_FUNC_TEXT                  "SetText"

#else
/*
#define NAME_FUNC_FUNCTION              "BeginFunction"
#define NAME_FUNC_PARAM                 "AddParam"
#define NAME_FUNC_DATA                  "Data"
#define NAME_FUNC_STRING                "AddString"
#define NAME_FUNC_TEXT                  "SetText"
*/
#endif

template<class Type>
ForceInline ULONG_PTR GetMethodAddr(Type Method)
{
    union
    {
        Type        Method;
        ULONG_PTR   Address;
    } u;

    u.Method = Method;

    return u.Address;
}

template<class Type>
ForceInline Type CastMethodAddr(ULONG_PTR Address)
{
    union
    {
        Type        Method;
        ULONG_PTR   Address;
    } u;

    u.Address = Address;

    return u.Method;
}

#pragma pack(1)

#define DATA_FLAG_VALUE     0x00000001L
#define DATA_FLAG_PREFIX    0x00000002L
#define DATA_FLAG_NUMBER    0x00000004L
#define DATA_FLAG_STRING    0x00000008L

struct YBN_PARAM_DATA_INFO
{
    ULONG DataOP;
    ULONG Flags;
};

struct YBN_FUNCTION_CONV_HANDLER
{
    ULONG FuncID;
    DECL_YBN_HANDLER(CYBNToLua::*FuncHandler);
};

typedef struct
{
    BYTE  DataType;
    PCHAR pszParamName;
} YBN_FUNCTION_PARAM_INFO;

#define FUNC_NO_PARAM                           0x0000FFFFL
#define FUNC_FLAG_VARG                          0x00000001L     // variable argument
#define FUNC_FLAG_FIRST_DATA                    0x00000002L     // only first param has data
#define FUNC_FLAG_CUSTOM_BODY                   0x10000000L     // custom function body
#define FUNC_FLAG_NO_AUTO_ARG_TYPE              0x20000000L
#define FUNC_FLAG_INITIALIZED                   0x80000000L

struct YBN_FUNCTION_INFO
{
    ULONG FuncID;
    LONG  Flags;
    union
    {
        FFuncHandler Handler;
        ULONG ParamCount;
    };
    YBN_FUNCTION_PARAM_INFO *pParamInfo;
    PCHAR pszFuncName;
};

#pragma pack()

#define FUNC_INFO1(id, flags, hdl, ...) { (id), ((flags) | FUNC_FLAG_INITIALIZED), (hdl), __VA_ARGS__ }
#define FUNC_INFO2(id, flags, cnt, ...) FUNC_INFO1((id), (flags), CastMethodAddr<FFuncHandler>(cnt))

YBN_FUNCTION_INFO g_FuncInfo[] =
{
    FUNC_INFO1(YURIS_FUNC_SETTEXT,  0, &CYBNToLua::SetText, NULL, NAME_FUNC_TEXT),
    FUNC_INFO1(YURIS_FUNC_1E,       0, &CYBNToLua::Func1E,  NULL, NAME_FUNC_1E),
//    FUNC_INFO1(YURIS_FUNC_29,       0, &CYBNToLua::Func29,  NULL, NAME_FUNC_29),
};

YBN_PARAM_DATA_INFO g_ParamDataInfo[] =
{
    { DATA_21,          DATA_FLAG_VALUE     },
    { DATA_25,          DATA_FLAG_VALUE     },
    { DATA_26,          DATA_FLAG_VALUE     },
    { DATA_29,          DATA_FLAG_VALUE     },
    { DATA_2A,          DATA_FLAG_VALUE     },
    { DATA_2B,          DATA_FLAG_VALUE     },
    { DATA_2C,          DATA_FLAG_VALUE     },
    { DATA_2D,          DATA_FLAG_VALUE     },
    { DATA_2F,          DATA_FLAG_VALUE     },
    { DATA_3C,          DATA_FLAG_VALUE     },
    { DATA_3D,          DATA_FLAG_VALUE     },

    { DATA_3E,          DATA_FLAG_VALUE     },
    { DATA_41,          DATA_FLAG_VALUE     },
    { DATA_CHAR,        DATA_FLAG_VALUE | DATA_FLAG_NUMBER },
    { DATA_46,          DATA_FLAG_VALUE },
    { DATA_USHORT,      DATA_FLAG_VALUE | DATA_FLAG_PREFIX },
    { DATA_LONG,        DATA_FLAG_VALUE | DATA_FLAG_NUMBER },
    { DATA_INT64,       DATA_FLAG_VALUE | DATA_FLAG_NUMBER },
    { DATA_STRING,      DATA_FLAG_STRING    },
    { DATA_4F,          DATA_FLAG_VALUE     },
    { DATA_52,          DATA_FLAG_VALUE     },

    { DATA_53,          DATA_FLAG_VALUE     },
    { DATA_56,          DATA_FLAG_VALUE | DATA_FLAG_PREFIX },
    { DATA_SHORT,       DATA_FLAG_VALUE | DATA_FLAG_NUMBER },
    { DATA_5A,          DATA_FLAG_VALUE     },
    { DATA_5E,          DATA_FLAG_VALUE     },
    { DATA_69,          DATA_FLAG_VALUE     },
    { DATA_73,          DATA_FLAG_VALUE     },
    { DATA_76,          DATA_FLAG_VALUE | DATA_FLAG_PREFIX },
    { DATA_7C,          DATA_FLAG_VALUE     },
};


CHAR szScriptInit[] = "\
require('"NAME_DEFAULT_BASE_SCRIPT_NAME"')\r\n\
local fscr, err = Create('%s')\r\n\
if not fscr then\r\n\
    print(err)\r\n\
    return -1\r\n\
end\r\n\
\r\n\
local "NAME_FUNC_MAKE_PARAM_LOCAL" = "NAME_FUNC_MAKE_PARAM"\r\n\
local "NAME_FUNC_DUMMY_PARAM_LOCAL" = "NAME_FUNC_MAKE_DUMMY_PARAM"\r\n\
\r\n\
";

#endif // _INFO_H_
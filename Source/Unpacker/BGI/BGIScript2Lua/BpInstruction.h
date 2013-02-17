#ifndef _BPINSTRUCTION_H_e4cd1630_5c60_4b05_b644_f8a38a8d9a29
#define _BPINSTRUCTION_H_e4cd1630_5c60_4b05_b644_f8a38a8d9a29

#include "BGIScript2Lua.h"

#pragma pack(1)

#define DEF_ERROR(x)        MAKE_HRESULT(1, 0x200, (x))
#define DEF_SUCCESS(x)      MAKE_HRESULT(0, 0x200, (x))

#define S_CONTINUE          S_OK
#define S_PROC_RETURN       DEF_SUCCESS(1)
#define S_PROCESSED         DEF_SUCCESS(2)

#define E_UNKNOWN_OP        DEF_ERROR(1)


struct BGI_BP_INSTRUCTION
{
    ULONG OP;
//    union
//    {
        DECL_HANDLER(*Handler);
        ULONG ParamCount;      // 65535 max
//    };

    PUSHORT pParamLength;
    PULONG  pParamFlags;
    PCHAR   Name;
    PCHAR   Body;
    ULONG   Flags;
};

#define BP_GET_OP(instruction)      (((instruction)->OP) & 0x7FFFFFFF)
#define BP_INSTRUCTION_INIT_FLAG    0x80000000
#define IS_INSTRUCTION_INIT(op)     (TEST_BITS((op), BP_INSTRUCTION_INIT_FLAG))
//#define IS_HANDLER(instruction)     (TEST_BITS((instruction)->ParamCount, 0xFFFF0000))
#define IS_HANDLER(instruction)     ((instruction)->Handler != NULL)

template<class Type>
FORCEINLINE ULONG CastHandlerToULong(Type Method)
{
    union
    {
        Type m;
        ULONG v;
    };

    m = Method;
    return v;
}

#define _DECL_INS(op, handler, ...) \
            { \
                ((op) | BP_INSTRUCTION_INIT_FLAG), \
                handler, \
                IF_EXIST(BP_INS_Length_##op) \
                { \
                    countof(BP_INS_Length_##op), \
                    BP_INS_Length_##op \
                } \
                IF_NOT_EXIST(BP_INS_Length_##op) \
                { \
                    0, \
                    NULL \
                }, \
                IF_EXIST(BP_INS_Flags_##op) \
                { \
                    BP_INS_Flags_##op \
                } \
                IF_NOT_EXIST(BP_INS_Flags_##op) \
                { \
                    0 \
                }, \
                *(PUSHORT)(#op) == TAG2('OP') ? NULL : #op, \
                IF_EXIST(BP_INS_Body_##op) \
                { \
                    BP_INS_Body_##op \
                } \
                IF_NOT_EXIST(BP_INS_Body_##op) \
                { \
                    NULL \
                }, \
                __VA_ARGS__, \
            }

#define DECL_INS(op, ...)           _DECL_INS(op, NULL, __VA_ARGS__)
#define DECL_INS2(op, handler, ...) _DECL_INS(op, &CBGIScript2Lua::handler, __VA_ARGS__)

#define DECL_FLAGS(op, ...)     ULONG  BP_INS_Flags_##op[countof(BP_INS_Length_##op)] = { __VA_ARGS__ }
#define DECL_LENGTH(op, ...)    USHORT BP_INS_Length_##op[] = { __VA_ARGS__ }
#define DECL_BODY(op, ...)      PCHAR  BP_INS_Body_##op = __VA_ARGS__


#define BGI_MASK_LABEL                   0x01
#define BGI_MASK_PROC                    0x02
#define BGI_MASK_STRING                  0x04
#define BGI_MASK_PROCESSED               0x08

#define BGI_INSTRUCTION_FLAGS_LABEL     0x00000001
#define BGI_INSTRUCTION_FLAGS_PROC      0x00000002
#define BGI_INSTRUCTION_FLAGS_STRING    0x00000004
#define BGI_INSTRUCTION_FLAGS_RETURN    0x00000008

enum // BGI_BP_OP
{
    PushByte                = 0x00,
    PushWord                = 0x01,
    PushDword               = 0x02,
    OP_04                   = 0x04,
    PushString              = 0x05,
    PushProcAddress         = 0x06,
    ReadMemory              = 0x08,
    WriteMemory             = 0x09,
    OP_0A                   = 0x0A,
    OP_0B                   = 0x0B,
    PopAllRetAddrFromStack  = 0x0C,
    PushIP                  = 0x10,
    PopIP                   = 0x11,
    OP_14                   = 0x14,
    GotoIf                  = 0x15,
    Call                    = 0x16,
    Return                  = 0x17,
    AddStackPop             = 0x20,
    SubStackPop             = 0x21,
    ImulStackPop            = 0x22,
    IdivStackPop            = 0x23,
    ModStackPop             = 0x24,
    AndStackPop             = 0x25,
    OrStackPop              = 0x26,
    XorStackPop             = 0x27,
    NotStackPop             = 0x28,
    ShlStackPop             = 0x29,
    ShrStackPop             = 0x2A,
    SarStackPop             = 0x2B,
    CmpEqStackPop           = 0x30,
    CmpNeStackPop           = 0x31,
    CmpLeStackPop           = 0x32,
    CmpGeStackPop           = 0x33,
    CmpLStackPop            = 0x34,
    CmpGStackPop            = 0x35,
    OP_38                   = 0x38,
    OP_39                   = 0x39,
    OP_3A                   = 0x3A,
    OP_40                   = 0x40,
    OP_42                   = 0x42,
    OP_43                   = 0x43,
    OP_48                   = 0x48,
    OP_49                   = 0x49,
    OP_50                   = 0x50,
    OP_51                   = 0x51,
    OP_52                   = 0x52,
    OP_53                   = 0x53,
    OP_54                   = 0x54,
    MemoryCopy              = 0x60,
    MemoryZero              = 0x61,
    MemoryFill              = 0x62,
    MemoryCompare           = 0x63,
    StringCompareA          = 0x66,
    OP_67                   = 0x67,
    StringLengthA           = 0x68,
    StringCompareA2         = 0x69,
    StringCopyA             = 0x6A,
    WriteErrorMsg           = 0x6B,
    IsPunctuation           = 0x6C,
    UpperStringA            = 0x6D,
    OP_6E                   = 0x6E,
    StringFormat            = 0x6F,
    OP_70                   = 0x70,
    OP_71                   = 0x71,
    ChangeSomeOPHandler     = 0x74,
    OP_75                   = 0x75,
    OP_77                   = 0x77,
    YesNoMsgBox             = 0x78,
    CriticalErrorMsgBox     = 0x79,
    OP_7A                   = 0x7A,
    OP_7B                   = 0x7B,
    ShowModelDialog         = 0x7C,
    OP_7D                   = 0x7D,
    CopyToClipBoard         = 0x7E,
    OP_7F                   = 0x7F,
    CallFunc1               = 0x80,
    CallFunc2               = 0x81,
    CallFunc3               = 0x90,
    CallFunc4               = 0x91,
    CallFunc5               = 0x92,
    CallFunc6               = 0xA0,
    CallFunc7               = 0xB0,
    CallFunc8               = 0xC0,
    OP_FF                   = 0xFF,

    BGI_BP_OP_MAX
};

DECL_LENGTH(PushByte,               1);
DECL_LENGTH(PushWord,               2);
DECL_LENGTH(PushDword,              4);
DECL_LENGTH(OP_04,                  2);
DECL_LENGTH(PushString,             2);
DECL_LENGTH(PushProcAddress,        2);
DECL_LENGTH(ReadMemory,             1);
DECL_LENGTH(WriteMemory,            1);
DECL_LENGTH(OP_0A,                  1);
DECL_LENGTH(OP_0B,                  1);
DECL_LENGTH(PopAllRetAddrFromStack, 1, 1);
DECL_LENGTH(GotoIf,                 1);
DECL_LENGTH(CallFunc1,              1);
DECL_LENGTH(CallFunc2,              1);
DECL_LENGTH(CallFunc3,              1);
DECL_LENGTH(CallFunc4,              1);
DECL_LENGTH(CallFunc5,              1);
DECL_LENGTH(CallFunc6,              1);
DECL_LENGTH(CallFunc7,              1);
DECL_LENGTH(CallFunc8,              1);
DECL_LENGTH(OP_FF,                  1);

//DECL_FLAGS(OP_04,                   BGI_INSTRUCTION_FLAGS_PROC);
DECL_FLAGS(PushString,              BGI_INSTRUCTION_FLAGS_STRING);
DECL_FLAGS(PushProcAddress,         BGI_INSTRUCTION_FLAGS_PROC);

/*
DECL_BODY(
    PushString,
    "function PushString(Text)\r\n"
    "   AddText(Text)\r\n"
    "   return WriteInstruction(0x05, -1, 2)\r\n"
    "end"
);

DECL_BODY(
    PushProcAddress,
    "function PushProcAddress(label)\r\n"
    "   AddInsLabel(label)\r\n"
    "   return WriteInstruction(0x06, -1, 2)\r\n"
    "end"
);
*/
BGI_BP_INSTRUCTION g_BPInstrction[] =
{
    DECL_INS(PushByte),
    DECL_INS(PushWord),
    DECL_INS(PushDword),
    DECL_INS(OP_04),
    DECL_INS(PushString),
    DECL_INS2(PushProcAddress, PushProcAddrHandler),
    DECL_INS(ReadMemory),
    DECL_INS(WriteMemory),
    DECL_INS(OP_0A),
    DECL_INS(OP_0B),
    DECL_INS(PopAllRetAddrFromStack),
    DECL_INS(PushIP),
    DECL_INS(PopIP),
    DECL_INS(OP_14),
    DECL_INS(GotoIf),
    DECL_INS(Call),
    DECL_INS(Return, BGI_INSTRUCTION_FLAGS_RETURN),
    DECL_INS(AddStackPop),
    DECL_INS(SubStackPop),
    DECL_INS(ImulStackPop),
    DECL_INS(IdivStackPop),
    DECL_INS(ModStackPop),
    DECL_INS(AndStackPop),
    DECL_INS(OrStackPop),
    DECL_INS(XorStackPop),
    DECL_INS(NotStackPop),
    DECL_INS(ShlStackPop),
    DECL_INS(ShrStackPop),
    DECL_INS(SarStackPop),
    DECL_INS(CmpEqStackPop),
    DECL_INS(CmpNeStackPop),
    DECL_INS(CmpLeStackPop),
    DECL_INS(CmpGeStackPop),
    DECL_INS(CmpLStackPop),
    DECL_INS(CmpGStackPop),
    DECL_INS(OP_38),
    DECL_INS(OP_39),
    DECL_INS(OP_3A),
    DECL_INS(OP_40),
    DECL_INS(OP_42),
    DECL_INS(OP_43),
    DECL_INS(OP_48),
    DECL_INS(OP_49),
    DECL_INS(OP_50),
    DECL_INS(OP_51),
    DECL_INS(OP_52),
    DECL_INS(OP_53),
    DECL_INS(OP_54),
    DECL_INS(MemoryCopy),
    DECL_INS(MemoryZero),
    DECL_INS(MemoryFill),
    DECL_INS(MemoryCompare),
    DECL_INS(StringCompareA),
    DECL_INS(OP_67),
    DECL_INS(StringLengthA),
    DECL_INS(StringCompareA2),
    DECL_INS(StringCopyA),
    DECL_INS(WriteErrorMsg),
    DECL_INS(IsPunctuation),
    DECL_INS(UpperStringA),
    DECL_INS(OP_6E),
    DECL_INS(StringFormat),
    DECL_INS(OP_70),
    DECL_INS(OP_71),
    DECL_INS(ChangeSomeOPHandler),
    DECL_INS(OP_75),
    DECL_INS(OP_77),
    DECL_INS(YesNoMsgBox),
    DECL_INS(CriticalErrorMsgBox),
    DECL_INS(OP_7A),
    DECL_INS(OP_7B),
    DECL_INS(ShowModelDialog),
    DECL_INS(OP_7D),
    DECL_INS(CopyToClipBoard),
    DECL_INS(OP_7F),
    DECL_INS(CallFunc1),
    DECL_INS(CallFunc2),
    DECL_INS(CallFunc3),
    DECL_INS(CallFunc4),
    DECL_INS(CallFunc5),
    DECL_INS(CallFunc6),
    DECL_INS(CallFunc7),
    DECL_INS(CallFunc8),
    DECL_INS(OP_FF),
};

#pragma pack()

#define BP_NAME_EXTENSION                   ".lua"
#define BP_NAME_LABEL                       "label"
#define BP_NAME_LABEL_PREFIX                "loc_"
#define BP_NAME_DEFAULT_OP_PREFIX           "OP_"
#define BP_NAME_DEFAULT_PARAM_PREFIX        "Param"

#define BP_NAME_DEFAULT_BASE_SCRIPT_NAME    "BGIBP"
#define BP_NAME_DEFAULT_BASE_SCRIPT         "BGIBP.lua"
#define BP_NAME_BGI_SCRIPT_BP_EXTENSION     "._bp"

#define BP_FUNC_WRITE_INSTRUCTION           "WriteInstruction"
#define BP_FUNC_ADD_LABEL                   "AddLabel"
#define BP_FUNC_ADD_PROC_LABEL              "AddProcLabel"
#define BP_FUNC_ADD_TEXT                    "AddText"
#define BP_FUNC_UPDATE_ALL_OFFSET           "UpdateAllOffset"


CHAR szBaseBpFunc[] = "\
local ffi = require('ffi')\r\n\
local hFile, FileName\r\n\
local TextMap = {}\r\n\
local LabelMap = {}\r\n\
local ProcLabelMap = {}\r\n\
\r\n\
local function Write(data, size)\r\n\
    local pdata = ffi.new('uint64_t[?]', size)\r\n\
    if type(data) ~= 'string' then\r\n\
        pdata[0] = data\r\n\
    else\r\n\
        ffi.copy(pdata, data, size)\r\n\
    end\r\n\
    return hFile:write(ffi.string(pdata, size))\r\n\
end\r\n\
\r\n\
function Create(Name)\r\n\
    local ErrorMsg\r\n\
    FileName = Name\r\n\
    hFile, ErrorMsg = io.open(Name .. '"BP_NAME_BGI_SCRIPT_BP_EXTENSION"', 'wb+')\r\n\
    if not hFile then\r\n\
        return hFile, ErrorMsg\r\n\
    end\r\n\
\r\n\
    Write(0x10, 0x10)\r\n\
\r\n\
    return hFile, ErrorMsg\r\n\
end\r\n\
\r\n\
function Seek(where, offset)\r\n\
    return hFile:seek(where, offset)\r\n\
end\r\n\
\r\n\
function GetPos()\r\n\
    return hFile:seek()\r\n\
end\r\n\
\r\n\
function Close()\r\n\
    return hFile:close()\r\n\
end\r\n\
\r\n\
local function "BP_FUNC_ADD_TEXT"(Text)\r\n\
    return table.insert(TextMap, { Offset = GetPos(), Data = Text })\r\n\
end\r\n\
\r\n\
local function "BP_FUNC_ADD_LABEL"(label)\r\n\
    LabelMap[label] = GetPos()\r\n\
end\r\n\
\r\n\
local function "BP_FUNC_ADD_PROC_LABEL"(label)\r\n\
    return table.insert(ProcLabelMap, { Offset = GetPos(), Name = label })\r\n\
end\r\n\
\r\n\
function label(l)\r\n\
    return "BP_FUNC_ADD_LABEL"(l)\r\n\
end\r\n\
\r\n\
local function WriteAllText()\r\n\
    local InsOffset, TextOffset, Count\r\n\
    local pos = ffi.new('int32_t[1]')\r\n\
    TextOffset = GetPos() + 16 - 1\r\n\
    pos[0] = TextOffset / 16\r\n\
    TextOffset = pos[0] * 16\r\n\
\r\n\
    Count = table.getn(TextMap)\r\n\
    for i = 1, Count do\r\n\
        local len\r\n\
        local m = TextMap[i]\r\n\
        Seek('set', m.Offset + 1)\r\n\
        Write(TextOffset - m.Offset, 2)\r\n\
        Seek('set', TextOffset)\r\n\
        len = string.len(m.Data) + 1\r\n\
        Write(m.Data, len)\r\n\
        TextOffset = TextOffset + len\r\n\
    end\r\n\
end\r\n\
\r\n\
local function UpdateLabel()\r\n\
    local map, label, Count\r\n\
\r\n\
    map = ProcLabelMap\r\n\
    label = LabelMap\r\n\
    Count = table.getn(map)\r\n\
    for i = 1, Count do\r\n\
        local ins = map[i]\r\n\
        local Offset = ins.Offset\r\n\
        Seek('set', Offset + 1)\r\n\
        Write(label[ins.Name] - Offset, 2)\r\n\
    end\r\n\
end\r\n\
\r\n\
function "BP_FUNC_UPDATE_ALL_OFFSET"()\r\n\
    WriteAllText()\r\n\
    UpdateLabel()\r\n\
\r\n\
    local Mod16Size\r\n\
\r\n\
    Seek('end')\r\n\
    Mod16Size = GetPos()\r\n\
\r\n\
    if Mod16Size % 16 ~= 0 then\r\n\
        local pos = ffi.new('int32_t[1]')\r\n\
\r\n\
        Mod16Size = Mod16Size + 16 - 1\r\n\
        pos[0] = Mod16Size / 16\r\n\
        Mod16Size = pos[0] * 16\r\n\
        Seek('set', Mod16Size - 1)\r\n\
        Write(0, 1)\r\n\
    end\r\n\
\r\n\
    Seek('set', 4)\r\n\
    Write(Mod16Size - 0x10, 4)\r\n\
end\r\n\
\r\n\
local function "BP_FUNC_WRITE_INSTRUCTION"(OP, ...)\r\n\
    local ParamCount, Param, Length\r\n\
\r\n\
    Write(OP, 1)\r\n\
\r\n\
    ParamCount = select('#', ...)\r\n\
    if ParamCount == 0 then\r\n\
        return\r\n\
    end\r\n\
\r\n\
    for i = 1, ParamCount, 2 do\r\n\
        Param = select(i, ...)\r\n\
        Length = select(i + 1, ...)\r\n\
        Write(Param, Length)\r\n\
    end\r\n\
end\r\n\
";

CHAR szBpInit[] = "\
require('"BP_NAME_DEFAULT_BASE_SCRIPT_NAME"')\r\n\
local fscr, err = Create('%s')\r\n\
if not fscr then\r\n\
    print(err)\r\n\
    return -1\r\n\
end\r\n\
\r\n\
";

CHAR szBpFinalize[] ="\
"BP_FUNC_UPDATE_ALL_OFFSET"()\
";

#endif // _BPINSTRUCTION_H_e4cd1630_5c60_4b05_b644_f8a38a8d9a29

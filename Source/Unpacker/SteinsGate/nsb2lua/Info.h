#ifndef _INFO_H_
#define _INFO_H_

#include "pragma_once.h"
#include "NSBDisasm.h"

#define MAX_INSTRUCTION_COUNT 286
#define MIN_FUNCTION_MAP_SIZE 4
#define MIN_INSTRUCTION_INFO  8

#define NAME_DEFAULT_HANDLER_PREFIX     "OP_"
#define NAME_UPDATE_FUNCTION_MAP        "UpdateFunctionMap"
#define NAME_COMMON_HANDLER             "WriteInstruction"
#define NAME_DEFAULT_BASE_SCRIPT_NAME   "N2ScriptBin"
#define NAME_DEFAULT_BASE_SCRIPT        "N2ScriptBin.lua"

#define NAME_FUNCTION_MAP_EXTENSION     ".map"
#define NAME_N2_SCRIPT_BIN_EXTENSION    ".nsb"
#define NAME_SCRIPT_EXTENSION           ".lua"


CHAR szScriptInit[] = "\
require('"NAME_DEFAULT_BASE_SCRIPT_NAME"')\r\n\
local fscr, err = Create('%s')\r\n\
if not fscr then\r\n\
    print(err)\r\n\
    return -1\r\n\
end\r\n\
\r\n\
";

CHAR szScriptFinalize[] ="\
"NAME_UPDATE_FUNCTION_MAP"()\r\n\
";


CHAR szBaseFunc[] = "\
local ffi = require('ffi')\r\n\
local hFile, FileName\r\n\
local InstructionIndex = 1\r\n\
local FunctionMap = {}\r\n\
\r\n\
function Create(Name)\r\n\
    local ErrorMsg\r\n\
    FileName = Name\r\n\
    hFile, ErrorMsg = io.open(Name .. '"NAME_N2_SCRIPT_BIN_EXTENSION"', 'wb+')\r\n\
    return hFile, ErrorMsg\r\n\
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
local function AddMap(FunctionName)\r\n\
    table.insert(FunctionMap, { Offset = GetPos(), Name = FunctionName })\r\n\
end\r\n\
\r\n\
function include(File)\r\n\
    return AddMap('include.' .. File)\r\n\
end\r\n\
\r\n\
function chapter(Name)\r\n\
    return AddMap('chapter.' .. Name)\r\n\
end\r\n\
\r\n\
function BeginFunction(FuncName)\r\n\
    return AddMap('function.' .. FuncName)\r\n\
end\r\n\
\r\n\
function label(LabelName)\r\n\
    return AddMap('label.' .. LabelName)\r\n\
end\r\n\
\r\n\
function scene(SceneName)\r\n\
    return AddMap('scene.' .. SceneName)\r\n\
end\r\n\
\r\n\
function begin(SceneName)\r\n\
    return AddMap('begin.' .. SceneName)\r\n\
end\r\n\
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
local function WriteInstruction(OP, ...)\r\n\
    local ParamCount, Text, Length\r\n\
    Write(InstructionIndex, 4)\r\n\
    InstructionIndex = InstructionIndex + 1\r\n\
    Write(OP, 2)\r\n\
    ParamCount = select('#', ...)\r\n\
    Write(ParamCount, 2)\r\n\
    for i = 1, ParamCount do\r\n\
        Text = select(i, ...)\r\n\
        Length = string.len(Text)\r\n\
        Write(Length, 4)\r\n\
        Write(Text, Length)\r\n\
    end\r\n\
end\r\n\
\r\n\
function UpdateFunctionMap()\r\n\
    local hFileNSB, hFileMap, ErrorMsg\r\n\
    hFileMap, ErrorMsg = io.open(FileName .. '.map', 'wb+')\r\n\
    if not hFileMap then\r\n\
        print(ErrorMsg)\r\n\
        return hFileMap, ErrorMsg\r\n\
    end\r\n\
\r\n\
    hFileNSB = hFile\r\n\
    hFile = hFileMap\r\n\
    table.sort(FunctionMap, function(t1, t2) return t1.Name < t2.Name end)\r\n\
    for i, v in pairs(FunctionMap) do\r\n\
        local Length, Text\r\n\
        Write(FunctionMap[i].Offset, 4)\r\n\
        Text = FunctionMap[i].Name\r\n\
        Length = string.len(Text)\r\n\
        Write(Length, 2)\r\n\
        Write(Text, Length)\r\n\
    end\r\n\
\r\n\
    hFile = hFileNSB\r\n\
    return hFileMap, ErrorMsg\r\n\
end\r\n\
\r\n\
";

#define SET_INFO(...) { __VA_ARGS__ }

INSTRUCTION_INFO g_InsInfo[] =
{
    SET_INFO(0x94, "SetEntry"),
    SET_INFO(0xD8, "SetText", NULL, &CNsbDisassembler::SetText),
};

#undef SET_INFO

#endif // _INFO_H_
local ffi = require('ffi')
local hFile, FileName
local TextMap = {}
local LabelMap = {}
local ProcLabelMap = {}

local function Write(data, size)
    local pdata = ffi.new('uint64_t[?]', size)
    if type(data) ~= 'string' then
        pdata[0] = data
    else
        ffi.copy(pdata, data, size)
    end
    return hFile:write(ffi.string(pdata, size))
end

function Create(Name)
    local ErrorMsg
    FileName = Name
    hFile, ErrorMsg = io.open(Name .. '.bp', 'wb+')
    if not hFile then
        return hFile, ErrorMsg
    end

    Write(0x10, 0x10)

    return hFile, ErrorMsg
end

function Seek(where, offset)
    return hFile:seek(where, offset)
end

function GetPos()
    return hFile:seek()
end

function Close()
    return hFile:close()
end

local function AddText(Text)
    return table.insert(TextMap, { Offset = GetPos(), Data = Text })
end

local function AddLabel(label)
    LabelMap[label] = GetPos()
end

local function AddInsLabel(label)
    return table.insert(ProcLabelMap, { Offset = GetPos(), Name = label })
end

function label(l)
    return AddLabel(l)
end

local function WriteAllText()
    local InsOffset, TextOffset, Count
    local pos = ffi.new('int32_t[1]')
    TextOffset = GetPos() + 16 - 1
    pos[0] = TextOffset / 16
    TextOffset = pos[0] * 16

    Count = table.getn(TextMap)
    for i = 1, Count do
        local len
        local m = TextMap[i]
        Seek('set', m.Offset + 1)
        Write(TextOffset - m.Offset, 2)
        Seek('set', TextOffset)
        len = string.len(m.Data) + 1
        Write(m.Data, len)
        TextOffset = TextOffset + len
    end
end

local function UpdateLabel()
    local map, label, Count

    map = ProcLabelMap
    label = LabelMap
    Count = table.getn(map)
    for i = 1, Count do
        local ins = map[i]
        local Offset = ins.Offset
        Seek('set', Offset + 1)
        Write(label[ins.Name] - Offset, 2)
    end
end

function UpdateAllOffset()
    WriteAllText()
    UpdateLabel()

    local Mod16Size

    Seek('end')
    Mod16Size = GetPos()

    if Mod16Size % 16 ~= 0 then
        local pos = ffi.new('int32_t[1]')

        Mod16Size = Mod16Size + 16 - 1
        pos[0] = Mod16Size / 16
        Mod16Size = pos[0] * 16
        Seek('set', Mod16Size - 1)
        Write(0, 1)
    end

    Seek('set', 4)
    Write(Mod16Size - 0x10, 4)
end

local function WriteInstruction(OP, ...)
    local ParamCount, Param, Length

    Write(OP, 1)

    ParamCount = select('#', ...)
    if ParamCount == 0 then
        return
    end

    for i = 1, ParamCount, 2 do
        Param = select(i, ...)
        Length = select(i + 1, ...)
        Write(Param, Length)
    end
end
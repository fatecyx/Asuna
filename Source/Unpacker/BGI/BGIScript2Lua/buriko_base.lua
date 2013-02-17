local ffi = require('ffi')
local hFile, FileName

local DataOffset
local LabelMap = {}
local CallLabelMap = {}
local StringTable = {}
local StringRefs = {}
local FuncMap = { --[[ FuncNam = '', Offset = 0 ]] }

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
    hFile, ErrorMsg = io.open(Name .. '_', 'wb+')
    if not hFile then
        return hFile, ErrorMsg
    end

    local magic = 'BurikoCompiledScriptVer1.00'
    Write(magic, string.len(magic) + 1)
    Write(0, 8)    -- header_size, reserve

    return hFile, ErrorMsg
end

local function Seek(where, offset)
    return hFile:seek(where, offset)
end

local function GetPos()
    return hFile:seek()
end

local function Close()
    return hFile:close()
end

local function WriteInstruction(OP, ...)
    local ParamCount, Param

    Write(OP, 4)

    ParamCount = select('#', ...)
    if ParamCount == 0 then
        return
    end

    for i = 1, ParamCount do
        Param = select(i, ...)
        Write(Param, 4)
    end
end

function AddFunc(...)
    local FuncCount, pos

    FuncCount = select('#', ...)
    Write(FuncCount, 4)

    pos = GetPos()
    for i = 1, FuncCount do
        local len, func

        func = select(i, ...)
        len = string.len(func) + 1
        Write(func, len)
        pos = pos + len
        FuncMap[func] = pos
        Write(0, 4)
        pos = pos + 4
    end

    local HeaderSize = pos

    if HeaderSize % 16 ~= 0 then
        local pos = ffi.new('int32_t[1]')

        HeaderSize = HeaderSize + 16 - 1
        pos[0] = HeaderSize / 16
        HeaderSize = pos[0] * 16
        Seek('set', HeaderSize - 1)
        Write(0, 1)
    end

    Seek('set', 0x1C)
    Write(HeaderSize - 0x1C, 4)
    Seek('end')
    DataOffset = HeaderSize
end

local function AddLabel(label)
    LabelMap[label] = GetPos()
end

local function AddCallLabel(label)
    return table.insert(CallLabelMap, { Offset = GetPos(), Name = label })
end

local function AddString(str)
    local p = StringRefs[str]
    if p == nil then
        table.insert(StringTable, str)
        StringRefs[str] = {}
        p = StringRefs[str]
    end
    return table.insert(p, GetPos())
end

local function WriteString()
    local strtbl = StringTable
    local strref = StringRefs

    for i = 1, table.getn(strtbl) do
        local text = strtbl[i]
        local len, pos

        len = string.len(text) + 1
        pos = GetPos()
        Write(text, len)

        local refs = strref[text]
        for j = 1, table.getn(refs) do
            local offset = refs[j]
            Seek('set', offset)
            Write(pos - DataOffset, 4)
        end

        Seek('end')
    end
end

local function UpdateLabel()
    local map, label, Count

    map = CallLabelMap
    label = LabelMap
    Count = table.getn(map)
    for i = 1, Count do
        local ins = map[i]
        Seek('set', ins.Offset)
        Write(label[ins.Name] - DataOffset, 4)
    end
end

function Finalize()
    WriteString()
    UpdateLabel()
end

function BeginFunc(func)
    local FuncOffset = FuncMap[func]
    local pos = GetPos()

    if FuncOffset == nil then
        print('undefined function \"' .. func .. '\"')
        error()
    end

    Seek('set', FuncOffset)
    Write(pos - DataOffset, 4)
    Seek('set', pos)

    return AddLabel(func)
end

function AddText(text)
    return AddString(text)
end

function AddImage(image)
    return AddString(image)
end

function AddScript(script)
    return AddString(script)
end

function label(l)
    return AddLabel(l)
end

local function SetString(Text)
    Write(0x3, 4)
    AddString(Text)
    return Write(-1, 4)
end
































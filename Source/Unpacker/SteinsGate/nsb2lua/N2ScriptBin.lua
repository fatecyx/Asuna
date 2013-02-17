local ffi = require('ffi')
local hFile, FileName
local InstructionIndex = 1
local FunctionMap = {}

function Create(Name)
    local ErrorMsg
    FileName = Name
    hFile, ErrorMsg = io.open(Name .. '.nsb', 'wb+')
    return hFile, ErrorMsg
end

function GetPos()
    return hFile:seek()
end

function Close()
    return hFile:close()
end

local function AddMap(FunctionName)
    table.insert(FunctionMap, { Offset = GetPos(), Name = FunctionName })
end

function include(File)
    return AddMap('include.' .. File)
end

function chapter(Name)
    return AddMap('chapter.' .. Name)
end

function BeginFunction(FuncName)
    return AddMap('function.' .. FuncName)
end

function label(LabelName)
    return AddMap('label.' .. LabelName)
end

function scene(SceneName)
    return AddMap('scene.' .. SceneName)
end

function begin(SceneName)
    return AddMap('begin.' .. SceneName)
end

local function Write(data, size)
    local pdata = ffi.new('uint64_t[?]', size)
    if type(data) ~= 'string' then
        pdata[0] = data
    else
        ffi.copy(pdata, data, size)
    end
    return hFile:write(ffi.string(pdata, size))
end

local function WriteInstruction(OP, ...)
    local ParamCount, Text, Length
    Write(InstructionIndex, 4)
    InstructionIndex = InstructionIndex + 1
    Write(OP, 2)
    ParamCount = select('#', ...)
    Write(ParamCount, 2)
    for i = 1, ParamCount do
        Text = select(i, ...)
        Length = string.len(Text)
        Write(Length, 4)
        Write(Text, Length)
    end
end

function UpdateFunctionMap()
    local hFileNSB, hFileMap, ErrorMsg
    hFileMap, ErrorMsg = io.open(FileName .. '.map', 'wb+')
    if not hFileMap then
        print(ErrorMsg)
        return hFileMap, ErrorMsg
    end

    hFileNSB = hFile
    hFile = hFileMap
    table.sort(FunctionMap, function(t1, t2) return t1.Name < t2.Name end)
    for i, v in pairs(FunctionMap) do
        local Length, Text
        Write(FunctionMap[i].Offset, 4)
        Text = FunctionMap[i].Name
        Length = string.len(Text)
        Write(Length, 2)
        Write(Text, Length)
    end

    hFile = hFileNSB
    return hFileMap, ErrorMsg
end

function SetEntry(...)
   WriteInstruction(0x94, ...)
end

function SetText(...)
   WriteInstruction(0xD8, ...)
end


function OP_0(...)
   WriteInstruction(0x0, ...)
end

function OP_1(...)
   WriteInstruction(0x1, ...)
end

function OP_2(...)
   WriteInstruction(0x2, ...)
end

function OP_3(...)
   WriteInstruction(0x3, ...)
end

function OP_4(...)
   WriteInstruction(0x4, ...)
end

function OP_5(...)
   WriteInstruction(0x5, ...)
end

function OP_6(...)
   WriteInstruction(0x6, ...)
end

function OP_7(...)
   WriteInstruction(0x7, ...)
end

function OP_8(...)
   WriteInstruction(0x8, ...)
end

function OP_9(...)
   WriteInstruction(0x9, ...)
end

function OP_A(...)
   WriteInstruction(0xA, ...)
end

function OP_B(...)
   WriteInstruction(0xB, ...)
end

function OP_C(...)
   WriteInstruction(0xC, ...)
end

function OP_D(...)
   WriteInstruction(0xD, ...)
end

function OP_E(...)
   WriteInstruction(0xE, ...)
end

function OP_F(...)
   WriteInstruction(0xF, ...)
end

function OP_10(...)
   WriteInstruction(0x10, ...)
end

function OP_11(...)
   WriteInstruction(0x11, ...)
end

function OP_12(...)
   WriteInstruction(0x12, ...)
end

function OP_13(...)
   WriteInstruction(0x13, ...)
end

function OP_14(...)
   WriteInstruction(0x14, ...)
end

function OP_15(...)
   WriteInstruction(0x15, ...)
end

function OP_16(...)
   WriteInstruction(0x16, ...)
end

function OP_17(...)
   WriteInstruction(0x17, ...)
end

function OP_18(...)
   WriteInstruction(0x18, ...)
end

function OP_19(...)
   WriteInstruction(0x19, ...)
end

function OP_1A(...)
   WriteInstruction(0x1A, ...)
end

function OP_1B(...)
   WriteInstruction(0x1B, ...)
end

function OP_1C(...)
   WriteInstruction(0x1C, ...)
end

function OP_1D(...)
   WriteInstruction(0x1D, ...)
end

function OP_1E(...)
   WriteInstruction(0x1E, ...)
end

function OP_1F(...)
   WriteInstruction(0x1F, ...)
end

function OP_20(...)
   WriteInstruction(0x20, ...)
end

function OP_21(...)
   WriteInstruction(0x21, ...)
end

function OP_22(...)
   WriteInstruction(0x22, ...)
end

function OP_23(...)
   WriteInstruction(0x23, ...)
end

function OP_24(...)
   WriteInstruction(0x24, ...)
end

function OP_25(...)
   WriteInstruction(0x25, ...)
end

function OP_26(...)
   WriteInstruction(0x26, ...)
end

function OP_27(...)
   WriteInstruction(0x27, ...)
end

function OP_28(...)
   WriteInstruction(0x28, ...)
end

function OP_29(...)
   WriteInstruction(0x29, ...)
end

function OP_2A(...)
   WriteInstruction(0x2A, ...)
end

function OP_2B(...)
   WriteInstruction(0x2B, ...)
end

function OP_2C(...)
   WriteInstruction(0x2C, ...)
end

function OP_2D(...)
   WriteInstruction(0x2D, ...)
end

function OP_2E(...)
   WriteInstruction(0x2E, ...)
end

function OP_2F(...)
   WriteInstruction(0x2F, ...)
end

function OP_30(...)
   WriteInstruction(0x30, ...)
end

function OP_31(...)
   WriteInstruction(0x31, ...)
end

function OP_32(...)
   WriteInstruction(0x32, ...)
end

function OP_33(...)
   WriteInstruction(0x33, ...)
end

function OP_34(...)
   WriteInstruction(0x34, ...)
end

function OP_35(...)
   WriteInstruction(0x35, ...)
end

function OP_36(...)
   WriteInstruction(0x36, ...)
end

function OP_37(...)
   WriteInstruction(0x37, ...)
end

function OP_38(...)
   WriteInstruction(0x38, ...)
end

function OP_39(...)
   WriteInstruction(0x39, ...)
end

function OP_3A(...)
   WriteInstruction(0x3A, ...)
end

function OP_3B(...)
   WriteInstruction(0x3B, ...)
end

function OP_3C(...)
   WriteInstruction(0x3C, ...)
end

function OP_3D(...)
   WriteInstruction(0x3D, ...)
end

function OP_3E(...)
   WriteInstruction(0x3E, ...)
end

function OP_3F(...)
   WriteInstruction(0x3F, ...)
end

function OP_40(...)
   WriteInstruction(0x40, ...)
end

function OP_41(...)
   WriteInstruction(0x41, ...)
end

function OP_42(...)
   WriteInstruction(0x42, ...)
end

function OP_43(...)
   WriteInstruction(0x43, ...)
end

function OP_44(...)
   WriteInstruction(0x44, ...)
end

function OP_45(...)
   WriteInstruction(0x45, ...)
end

function OP_46(...)
   WriteInstruction(0x46, ...)
end

function OP_47(...)
   WriteInstruction(0x47, ...)
end

function OP_48(...)
   WriteInstruction(0x48, ...)
end

function OP_49(...)
   WriteInstruction(0x49, ...)
end

function OP_4A(...)
   WriteInstruction(0x4A, ...)
end

function OP_4B(...)
   WriteInstruction(0x4B, ...)
end

function OP_4C(...)
   WriteInstruction(0x4C, ...)
end

function OP_4D(...)
   WriteInstruction(0x4D, ...)
end

function OP_4E(...)
   WriteInstruction(0x4E, ...)
end

function OP_4F(...)
   WriteInstruction(0x4F, ...)
end

function OP_50(...)
   WriteInstruction(0x50, ...)
end

function OP_51(...)
   WriteInstruction(0x51, ...)
end

function OP_52(...)
   WriteInstruction(0x52, ...)
end

function OP_53(...)
   WriteInstruction(0x53, ...)
end

function OP_54(...)
   WriteInstruction(0x54, ...)
end

function OP_55(...)
   WriteInstruction(0x55, ...)
end

function OP_56(...)
   WriteInstruction(0x56, ...)
end

function OP_57(...)
   WriteInstruction(0x57, ...)
end

function OP_58(...)
   WriteInstruction(0x58, ...)
end

function OP_59(...)
   WriteInstruction(0x59, ...)
end

function OP_5A(...)
   WriteInstruction(0x5A, ...)
end

function OP_5B(...)
   WriteInstruction(0x5B, ...)
end

function OP_5C(...)
   WriteInstruction(0x5C, ...)
end

function OP_5D(...)
   WriteInstruction(0x5D, ...)
end

function OP_5E(...)
   WriteInstruction(0x5E, ...)
end

function OP_5F(...)
   WriteInstruction(0x5F, ...)
end

function OP_60(...)
   WriteInstruction(0x60, ...)
end

function OP_61(...)
   WriteInstruction(0x61, ...)
end

function OP_62(...)
   WriteInstruction(0x62, ...)
end

function OP_63(...)
   WriteInstruction(0x63, ...)
end

function OP_64(...)
   WriteInstruction(0x64, ...)
end

function OP_65(...)
   WriteInstruction(0x65, ...)
end

function OP_66(...)
   WriteInstruction(0x66, ...)
end

function OP_67(...)
   WriteInstruction(0x67, ...)
end

function OP_68(...)
   WriteInstruction(0x68, ...)
end

function OP_69(...)
   WriteInstruction(0x69, ...)
end

function OP_6A(...)
   WriteInstruction(0x6A, ...)
end

function OP_6B(...)
   WriteInstruction(0x6B, ...)
end

function OP_6C(...)
   WriteInstruction(0x6C, ...)
end

function OP_6D(...)
   WriteInstruction(0x6D, ...)
end

function OP_6E(...)
   WriteInstruction(0x6E, ...)
end

function OP_6F(...)
   WriteInstruction(0x6F, ...)
end

function OP_70(...)
   WriteInstruction(0x70, ...)
end

function OP_71(...)
   WriteInstruction(0x71, ...)
end

function OP_72(...)
   WriteInstruction(0x72, ...)
end

function OP_73(...)
   WriteInstruction(0x73, ...)
end

function OP_74(...)
   WriteInstruction(0x74, ...)
end

function OP_75(...)
   WriteInstruction(0x75, ...)
end

function OP_76(...)
   WriteInstruction(0x76, ...)
end

function OP_77(...)
   WriteInstruction(0x77, ...)
end

function OP_78(...)
   WriteInstruction(0x78, ...)
end

function OP_79(...)
   WriteInstruction(0x79, ...)
end

function OP_7A(...)
   WriteInstruction(0x7A, ...)
end

function OP_7B(...)
   WriteInstruction(0x7B, ...)
end

function OP_7C(...)
   WriteInstruction(0x7C, ...)
end

function OP_7D(...)
   WriteInstruction(0x7D, ...)
end

function OP_7E(...)
   WriteInstruction(0x7E, ...)
end

function OP_7F(...)
   WriteInstruction(0x7F, ...)
end

function OP_80(...)
   WriteInstruction(0x80, ...)
end

function OP_81(...)
   WriteInstruction(0x81, ...)
end

function OP_82(...)
   WriteInstruction(0x82, ...)
end

function OP_83(...)
   WriteInstruction(0x83, ...)
end

function OP_84(...)
   WriteInstruction(0x84, ...)
end

function OP_85(...)
   WriteInstruction(0x85, ...)
end

function OP_86(...)
   WriteInstruction(0x86, ...)
end

function OP_87(...)
   WriteInstruction(0x87, ...)
end

function OP_88(...)
   WriteInstruction(0x88, ...)
end

function OP_89(...)
   WriteInstruction(0x89, ...)
end

function OP_8A(...)
   WriteInstruction(0x8A, ...)
end

function OP_8B(...)
   WriteInstruction(0x8B, ...)
end

function OP_8C(...)
   WriteInstruction(0x8C, ...)
end

function OP_8D(...)
   WriteInstruction(0x8D, ...)
end

function OP_8E(...)
   WriteInstruction(0x8E, ...)
end

function OP_8F(...)
   WriteInstruction(0x8F, ...)
end

function OP_90(...)
   WriteInstruction(0x90, ...)
end

function OP_91(...)
   WriteInstruction(0x91, ...)
end

function OP_92(...)
   WriteInstruction(0x92, ...)
end

function OP_93(...)
   WriteInstruction(0x93, ...)
end

function OP_94(...)
   WriteInstruction(0x94, ...)
end

function OP_95(...)
   WriteInstruction(0x95, ...)
end

function OP_96(...)
   WriteInstruction(0x96, ...)
end

function OP_97(...)
   WriteInstruction(0x97, ...)
end

function OP_98(...)
   WriteInstruction(0x98, ...)
end

function OP_99(...)
   WriteInstruction(0x99, ...)
end

function OP_9A(...)
   WriteInstruction(0x9A, ...)
end

function OP_9B(...)
   WriteInstruction(0x9B, ...)
end

function OP_9C(...)
   WriteInstruction(0x9C, ...)
end

function OP_9D(...)
   WriteInstruction(0x9D, ...)
end

function OP_9E(...)
   WriteInstruction(0x9E, ...)
end

function OP_9F(...)
   WriteInstruction(0x9F, ...)
end

function OP_A0(...)
   WriteInstruction(0xA0, ...)
end

function OP_A1(...)
   WriteInstruction(0xA1, ...)
end

function OP_A2(...)
   WriteInstruction(0xA2, ...)
end

function OP_A3(...)
   WriteInstruction(0xA3, ...)
end

function OP_A4(...)
   WriteInstruction(0xA4, ...)
end

function OP_A5(...)
   WriteInstruction(0xA5, ...)
end

function OP_A6(...)
   WriteInstruction(0xA6, ...)
end

function OP_A7(...)
   WriteInstruction(0xA7, ...)
end

function OP_A8(...)
   WriteInstruction(0xA8, ...)
end

function OP_A9(...)
   WriteInstruction(0xA9, ...)
end

function OP_AA(...)
   WriteInstruction(0xAA, ...)
end

function OP_AB(...)
   WriteInstruction(0xAB, ...)
end

function OP_AC(...)
   WriteInstruction(0xAC, ...)
end

function OP_AD(...)
   WriteInstruction(0xAD, ...)
end

function OP_AE(...)
   WriteInstruction(0xAE, ...)
end

function OP_AF(...)
   WriteInstruction(0xAF, ...)
end

function OP_B0(...)
   WriteInstruction(0xB0, ...)
end

function OP_B1(...)
   WriteInstruction(0xB1, ...)
end

function OP_B2(...)
   WriteInstruction(0xB2, ...)
end

function OP_B3(...)
   WriteInstruction(0xB3, ...)
end

function OP_B4(...)
   WriteInstruction(0xB4, ...)
end

function OP_B5(...)
   WriteInstruction(0xB5, ...)
end

function OP_B6(...)
   WriteInstruction(0xB6, ...)
end

function OP_B7(...)
   WriteInstruction(0xB7, ...)
end

function OP_B8(...)
   WriteInstruction(0xB8, ...)
end

function OP_B9(...)
   WriteInstruction(0xB9, ...)
end

function OP_BA(...)
   WriteInstruction(0xBA, ...)
end

function OP_BB(...)
   WriteInstruction(0xBB, ...)
end

function OP_BC(...)
   WriteInstruction(0xBC, ...)
end

function OP_BD(...)
   WriteInstruction(0xBD, ...)
end

function OP_BE(...)
   WriteInstruction(0xBE, ...)
end

function OP_BF(...)
   WriteInstruction(0xBF, ...)
end

function OP_C0(...)
   WriteInstruction(0xC0, ...)
end

function OP_C1(...)
   WriteInstruction(0xC1, ...)
end

function OP_C2(...)
   WriteInstruction(0xC2, ...)
end

function OP_C3(...)
   WriteInstruction(0xC3, ...)
end

function OP_C4(...)
   WriteInstruction(0xC4, ...)
end

function OP_C5(...)
   WriteInstruction(0xC5, ...)
end

function OP_C6(...)
   WriteInstruction(0xC6, ...)
end

function OP_C7(...)
   WriteInstruction(0xC7, ...)
end

function OP_C8(...)
   WriteInstruction(0xC8, ...)
end

function OP_C9(...)
   WriteInstruction(0xC9, ...)
end

function OP_CA(...)
   WriteInstruction(0xCA, ...)
end

function OP_CB(...)
   WriteInstruction(0xCB, ...)
end

function OP_CC(...)
   WriteInstruction(0xCC, ...)
end

function OP_CD(...)
   WriteInstruction(0xCD, ...)
end

function OP_CE(...)
   WriteInstruction(0xCE, ...)
end

function OP_CF(...)
   WriteInstruction(0xCF, ...)
end

function OP_D0(...)
   WriteInstruction(0xD0, ...)
end

function OP_D1(...)
   WriteInstruction(0xD1, ...)
end

function OP_D2(...)
   WriteInstruction(0xD2, ...)
end

function OP_D3(...)
   WriteInstruction(0xD3, ...)
end

function OP_D4(...)
   WriteInstruction(0xD4, ...)
end

function OP_D5(...)
   WriteInstruction(0xD5, ...)
end

function OP_D6(...)
   WriteInstruction(0xD6, ...)
end

function OP_D7(...)
   WriteInstruction(0xD7, ...)
end

function OP_D8(...)
   WriteInstruction(0xD8, ...)
end

function OP_D9(...)
   WriteInstruction(0xD9, ...)
end

function OP_DA(...)
   WriteInstruction(0xDA, ...)
end

function OP_DB(...)
   WriteInstruction(0xDB, ...)
end

function OP_DC(...)
   WriteInstruction(0xDC, ...)
end

function OP_DD(...)
   WriteInstruction(0xDD, ...)
end

function OP_DE(...)
   WriteInstruction(0xDE, ...)
end

function OP_DF(...)
   WriteInstruction(0xDF, ...)
end

function OP_E0(...)
   WriteInstruction(0xE0, ...)
end

function OP_E1(...)
   WriteInstruction(0xE1, ...)
end

function OP_E2(...)
   WriteInstruction(0xE2, ...)
end

function OP_E3(...)
   WriteInstruction(0xE3, ...)
end

function OP_E4(...)
   WriteInstruction(0xE4, ...)
end

function OP_E5(...)
   WriteInstruction(0xE5, ...)
end

function OP_E6(...)
   WriteInstruction(0xE6, ...)
end

function OP_E7(...)
   WriteInstruction(0xE7, ...)
end

function OP_E8(...)
   WriteInstruction(0xE8, ...)
end

function OP_E9(...)
   WriteInstruction(0xE9, ...)
end

function OP_EA(...)
   WriteInstruction(0xEA, ...)
end

function OP_EB(...)
   WriteInstruction(0xEB, ...)
end

function OP_EC(...)
   WriteInstruction(0xEC, ...)
end

function OP_ED(...)
   WriteInstruction(0xED, ...)
end

function OP_EE(...)
   WriteInstruction(0xEE, ...)
end

function OP_EF(...)
   WriteInstruction(0xEF, ...)
end

function OP_F0(...)
   WriteInstruction(0xF0, ...)
end

function OP_F1(...)
   WriteInstruction(0xF1, ...)
end

function OP_F2(...)
   WriteInstruction(0xF2, ...)
end

function OP_F3(...)
   WriteInstruction(0xF3, ...)
end

function OP_F4(...)
   WriteInstruction(0xF4, ...)
end

function OP_F5(...)
   WriteInstruction(0xF5, ...)
end

function OP_F6(...)
   WriteInstruction(0xF6, ...)
end

function OP_F7(...)
   WriteInstruction(0xF7, ...)
end

function OP_F8(...)
   WriteInstruction(0xF8, ...)
end

function OP_F9(...)
   WriteInstruction(0xF9, ...)
end

function OP_FA(...)
   WriteInstruction(0xFA, ...)
end

function OP_FB(...)
   WriteInstruction(0xFB, ...)
end

function OP_FC(...)
   WriteInstruction(0xFC, ...)
end

function OP_FD(...)
   WriteInstruction(0xFD, ...)
end

function OP_FE(...)
   WriteInstruction(0xFE, ...)
end

function OP_FF(...)
   WriteInstruction(0xFF, ...)
end

function OP_100(...)
   WriteInstruction(0x100, ...)
end

function OP_101(...)
   WriteInstruction(0x101, ...)
end

function OP_102(...)
   WriteInstruction(0x102, ...)
end

function OP_103(...)
   WriteInstruction(0x103, ...)
end

function OP_104(...)
   WriteInstruction(0x104, ...)
end

function OP_105(...)
   WriteInstruction(0x105, ...)
end

function OP_106(...)
   WriteInstruction(0x106, ...)
end

function OP_107(...)
   WriteInstruction(0x107, ...)
end

function OP_108(...)
   WriteInstruction(0x108, ...)
end

function OP_109(...)
   WriteInstruction(0x109, ...)
end

function OP_10A(...)
   WriteInstruction(0x10A, ...)
end

function OP_10B(...)
   WriteInstruction(0x10B, ...)
end

function OP_10C(...)
   WriteInstruction(0x10C, ...)
end

function OP_10D(...)
   WriteInstruction(0x10D, ...)
end

function OP_10E(...)
   WriteInstruction(0x10E, ...)
end

function OP_10F(...)
   WriteInstruction(0x10F, ...)
end

function OP_110(...)
   WriteInstruction(0x110, ...)
end

function OP_111(...)
   WriteInstruction(0x111, ...)
end

function OP_112(...)
   WriteInstruction(0x112, ...)
end

function OP_113(...)
   WriteInstruction(0x113, ...)
end

function OP_114(...)
   WriteInstruction(0x114, ...)
end

function OP_115(...)
   WriteInstruction(0x115, ...)
end

function OP_116(...)
   WriteInstruction(0x116, ...)
end

function OP_117(...)
   WriteInstruction(0x117, ...)
end

function OP_118(...)
   WriteInstruction(0x118, ...)
end

function OP_119(...)
   WriteInstruction(0x119, ...)
end

function OP_11A(...)
   WriteInstruction(0x11A, ...)
end

function OP_11B(...)
   WriteInstruction(0x11B, ...)
end

function OP_11C(...)
   WriteInstruction(0x11C, ...)
end

function OP_11D(...)
   WriteInstruction(0x11D, ...)
end


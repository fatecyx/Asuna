#ifndef _BURIKOSCRIPT_H_76a6fc53_829f_43e3_b63d_8fb912302066
#define _BURIKOSCRIPT_H_76a6fc53_829f_43e3_b63d_8fb912302066

#include "BpInstruction.h"

enum // BGI_BURIKO_SCRIPT_DATA_TYPE
{
    ScrCtrl_Push                    = 0x00,
    ScrCtrl_Call,
    ScrCtrl_02,
    ScrCtrl_PushString,
    ScrCtrl_08                      = 0x08,
    ScrCtrl_09,
    ScrCtrl_0A,
    ScrCtrl_10                      = 0x10,
    ScrCtrl_11,
    ScrCtrl_18                      = 0x18,
    ScrCtrl_19,
    ScrCtrl_1A,
    ScrCtrl_Return,
    ScrCtrl_1C,
    ScrCtrl_1D,
    ScrCtrl_1E,
    ScrCtrl_1F,
    ScrCtrl_20,
    ScrCtrl_21,
    ScrCtrl_22,
    ScrCtrl_23,
    ScrCtrl_24,
    ScrCtrl_25,
    ScrCtrl_26,
    ScrCtrl_27,
    ScrCtrl_28,
    ScrCtrl_29,
    ScrCtrl_2A,
    ScrCtrl_2B,
    ScrCtrl_30                      = 0x30,
    ScrCtrl_31,
    ScrCtrl_32,
    ScrCtrl_33,
    ScrCtrl_34,
    ScrCtrl_35,
    ScrCtrl_38                      = 0x38,
    ScrCtrl_39,
    ScrCtrl_3A,
    ScrCtrl_3F                      = 0x3F,
    ScrCtrl_40,
    ScrCtrl_48                      = 0x48,
    ScrCtrl_7F                      = 0x7F,
    ScrCtrl_80,
    ScrCtrl_81,
    ScrCtrl_82,
    ScrCtrl_83,
    ScrCtrl_90                      = 0x90,
    ScrCtrl_91,
    ScrCtrl_92,
    ScrCtrl_93,
    ScrCtrl_94,
    ScrCtrl_95,
    ScrCtrl_98                      = 0x98,
    ScrCtrl_99,
    ScrCtrl_A0                      = 0xA0,
    ScrCtrl_A8                      = 0xA8,
    ScrCtrl_AA                      = 0xAA,
    ScrCtrl_AC                      = 0xAC,
    ScrCtrl_E0                      = 0xE0,
    ScrCtrl_E1,
    ScrCtrl_E2,
    ScrCtrl_E3,
    ScrCtrl_E4,
    ScrCtrl_E5,
    ScrCtrl_E6,
    ScrCtrl_E7,
    ScrCtrl_E8,
    ScrCtrl_EA                      = 0xEA,
    ScrCtrl_EB,
    ScrCtrl_EC,
    ScrCtrl_F0                      = 0xF0,
    ScrCtrl_F1,
    ScrCtrl_F3                      = 0xF3,
    ScrCtrl_F4,
    ScrCtrl_F5,
    ScrCtrl_F6,
    ScrCtrl_F7,
    ScrCtrl_F8,
    ScrCtrl_F9,
    ScrCtrl_FA,
    ScrCtrl_FC                      = 0xFC,
    ScrCtrl_FE,
    ScrCtrl_FF,

    ScrSys_100                      = 0x100,
    ScrSys_101,
    ScrSys_108                      = 0x108,
    ScrSys_10F                      = 0x10F,
    ScrSys_110,
    ScrSys_111,
    ScrSys_112,
    ScrSys_113,
    ScrSys_114,
    ScrSys_116                      = 0x116,
    ScrSys_117,
    ScrSys_118,
    ScrSys_119,
    ScrSys_11A,
    ScrSys_11B,
    ScrSys_11C,
    ScrSys_120                      = 0x120,
    ScrSys_121,
    ScrSys_122,
    ScrSys_123,
    ScrSys_124,
    ScrSys_125,
    ScrSys_128                      = 0x128,
    ScrSys_12C                      = 0x12C,
    ScrSys_12F                      = 0x12F,
    ScrSys_130,
    ScrSys_131,
    ScrSys_132,
    ScrSys_136                      = 0x136,
    ScrSys_137,
    ScrSys_138,
    ScrSys_139,
    ScrSys_13A,
    ScrSys_13B,
    ScrSys_13C,
    ScrSys_13D,
    ScrSys_13F                      = 0x13F,

    ScrMsg_ShowText                 = 0x140,
    ScrMsg_141,
    ScrMsg_142,
    ScrMsg_ShowAutoText,
    ScrMsg_144,
    ScrMsg_145,
    ScrMsg_146,
    ScrMsg_147,
    ScrMsg_148,
    ScrMsg_149,
    ScrMsg_14A,
    ScrMsg_14B,
    ScrMsg_14C,
    ScrMsg_14D,
    ScrMsg_14E,
    ScrMsg_14F,
    ScrMsg_150,
    ScrMsg_151,
    ScrMsg_152,
    ScrMsg_153,
    ScrMsg_157                      = 0x157,
    ScrMsg_158,
    ScrMsg_159,
    ScrMsg_15C                      = 0x15C,
    ScrMsg_15D,
    ScrMsg_15E,
    ScrMsg_15F,

    ScrSelect_160                   = 0x160,
    ScrSelect_161,
    ScrSelect_164                   = 0x164,
    ScrSelect_165,
    ScrSelect_166,
    ScrSelect_168                   = 0x168,
    ScrSelect_169,
    ScrSelect_16C                   = 0x16C,

    ScrSound_180                    = 0x180,
    ScrSound_181,
    ScrSound_184                    = 0x184,
    ScrSound_185,
    ScrSound_186,
    ScrSound_190                    = 0x190,
    ScrSound_191,
    ScrSound_194                    = 0x194,
    ScrSound_195,
    ScrSound_196,
    ScrSound_198                    = 0x198,
    ScrSound_199,
    ScrSound_19C                    = 0x19C,
    ScrSound_19D,
    ScrSound_19E,
    ScrSound_1A0                    = 0x1A0,
    ScrSound_1A1,
    ScrSound_1A2,
    ScrSound_1A3,
    ScrSound_1A4,
    ScrSound_1A8                    = 0x1A8,
    ScrSound_1A9,
    ScrSound_1AA,
    ScrSound_1AC                    = 0x1AC,
    ScrSound_1BF                    = 0x1BF,

    ScrGrp1_220                     = 0x220,
    ScrGrp1_222                     = 0x222,
    ScrGrp1_228                     = 0x228,
    ScrGrp1_229,
    ScrGrp1_22A,
    ScrGrp1_230                     = 0x230,
    ScrGrp1_231,
    ScrGrp1_232,
    ScrGrp1_233,
    ScrGrp1_234,
    ScrGrp1_235,
    ScrGrp1_236,
    ScrGrp1_237,
    ScrGrp1_238,
    ScrGrp1_239,
    ScrGrp1_23C                     = 0x23C,
    ScrGrp1_23D,
    ScrGrp1_340                     = 0x340,
    ScrGrp1_348                     = 0x348,
    ScrGrp1_350                     = 0x350,
    ScrGrp1_351,
    ScrGrp1_352,
    ScrGrp1_353,
    ScrGrp1_358                     = 0x358,
    ScrGrp1_380                     = 0x380,
    ScrGrp1_388                     = 0x388,
    ScrGrp1_390                     = 0x390,
    ScrGrp1_391,
    ScrGrp1_392,
    ScrGrp1_393,
    ScrGrp1_394,
    ScrGrp1_3AF                     = 0x3AF,
    ScrGrp1_3C0                     = 0x3C0,
    ScrGrp1_3C1,
    ScrGrp1_3C2,
    ScrGrp1_3C4                     = 0x3C4,
    ScrGrp1_3C5,
    ScrGrp1_3C6,
    ScrGrp1_3C7,
    ScrGrp1_3C8,
    ScrGrp1_3C9,
    ScrGrp1_3D0                     = 0x3D0,
    ScrGrp1_3D2                     = 0x3D2,
    ScrGrp1_3D4                     = 0x3D4,
    ScrGrp1_3D5,
    ScrGrp1_3D6,
    ScrGrp1_3D8                     = 0x3D8,
    ScrGrp1_3DC                     = 0x3DC,
    ScrGrp1_3F0                     = 0x3F0,
    ScrGrp1_3F1,

    ScrGrp2_280                     = 0x280,
    ScrGrp2_281,
    ScrGrp2_284                     = 0x284,
    ScrGrp2_288                     = 0x288,
    ScrGrp2_289,
    ScrGrp2_28A,
    ScrGrp2_290                     = 0x290,
    ScrGrp2_2C0                     = 0x2C0,
    ScrGrp2_2C1,
    ScrGrp2_2C2,
    ScrGrp2_2C3,
    ScrGrp2_2C4,
    ScrGrp2_2C5,
    ScrGrp2_2C6,
    ScrGrp2_2C7,
    ScrGrp2_2C8,
    ScrGrp2_2CA                     = 0x2CA,
    ScrGrp2_2CB,
    ScrGrp2_2CC,
    ScrGrp2_2CE                     = 0x2CE,
    ScrGrp2_2CF,
    ScrGrp2_2D0,
    ScrGrp2_2D2                     = 0x2D2,
    ScrGrp2_2D8                     = 0x2D8,
    ScrGrp2_2DC                     = 0x2DC,
    ScrGrp2_2DF                     = 0x2DF,
    ScrGrp2_2E0,
    ScrGrp2_2E2                     = 0x2E2,
    ScrGrp2_2E4                     = 0x2E4,
    ScrGrp2_2E8                     = 0x2E8,
    ScrGrp2_2E9,
    ScrGrp2_2EA,
    ScrGrp2_2F0                     = 0x2F0,

    ScrGrp3_240                     = 0x240,
    ScrGrp3_241,
    ScrGrp3_242,
    ScrGrp3_244                     = 0x244,
    ScrGrp3_245,
    ScrGrp3_248                     = 0x248,
    ScrGrp3_24C                     = 0x24C,
    ScrGrp3_24D,
    ScrGrp3_24E,
    ScrGrp3_258                     = 0x258,
    ScrGrp3_25E                     = 0x25E,
    ScrGrp3_25F,
    ScrGrp3_260,
    ScrGrp3_262                     = 0x262,
    ScrGrp3_266                     = 0x266,
    ScrGrp3_268                     = 0x268,
    ScrGrp3_27F                     = 0x27F,

    ScrGrp4_300                     = 0x300,
    ScrGrp4_301,
    ScrGrp4_302,
    ScrGrp4_303,
    ScrGrp4_304,
    ScrGrp4_306                     = 0x306,
    ScrGrp4_307,
    ScrGrp4_308,
    ScrGrp4_309,
    ScrGrp4_30C                     = 0x30C,
    ScrGrp4_30E                     = 0x30E,
    ScrGrp4_31F                     = 0x31F,
    ScrGrp4_320,
    ScrGrp4_328                     = 0x328,
    ScrGrp4_32C                     = 0x32C,
    ScrGrp4_33F                     = 0x33F,

    SCR_OP_MAX                      = 0x400,

    SCR_EX_OP_FIRST                 = 0xFFFF0000,

    SCR_EX_Text                     = SCR_EX_OP_FIRST,
    SCR_EX_AutoText,
    SCR_EX_Say,
    SCR_EX_AutoSay,
    SCR_EX_Select,
    SCR_EX_Voice,
    SCR_EX_Image,
    SCR_EX_Debug,

    SCR_EX_OP_LAST,

    SCR_NULL_OP                     = 0xFFFFFFFF,
};

DECL_LENGTH(ScrCtrl_Push,         4);
DECL_LENGTH(ScrCtrl_Call,       4);
DECL_LENGTH(ScrCtrl_02,         4);
DECL_LENGTH(ScrCtrl_PushString,         4);
DECL_LENGTH(ScrCtrl_08,         4);
DECL_LENGTH(ScrCtrl_09,         4);
DECL_LENGTH(ScrCtrl_0A,         4);
DECL_LENGTH(ScrCtrl_19,         4);
DECL_LENGTH(ScrCtrl_7F,         4, 4);

DECL_FLAGS(ScrCtrl_Call,         BGI_INSTRUCTION_FLAGS_PROC);
DECL_FLAGS(ScrCtrl_PushString,   BGI_INSTRUCTION_FLAGS_STRING);
DECL_FLAGS(ScrCtrl_7F,           BGI_INSTRUCTION_FLAGS_STRING);


#define SCR_FUNC_SAY                        "Say"
#define SCR_FUNC_AUTO_SAY                   "AutoSay"
#define SCR_FUNC_TEXT                       "Text"
#define SCR_FUNC_AUTO_TEXT                  "AutoText"
#define SCR_FUNC_SELECT                     "Select"
#define SCR_FUNC_VOICE                      "Voice"
#define SCR_FUNC_IMAGE                      "Image"
#define SCR_FUNC_DEBUG                      "Debug"

DECL_BODY(
    SCR_EX_Text,
    "function "SCR_FUNC_TEXT"(t)\r\n"
    "   return SetString(t)\r\n"
    "end"
);

DECL_BODY(
    SCR_EX_AutoText,
    "function "SCR_FUNC_AUTO_TEXT"(t)\r\n"
    "   return SetString(t)\r\n"
    "end"
);

DECL_BODY(
    SCR_EX_Say,
    "function "SCR_FUNC_SAY"(char, text)\r\n"
    "   SetString(char)\r\n"
    "   return SetString(text)\r\n"
    "end"
);

DECL_BODY(
    SCR_EX_AutoSay,
    "function "SCR_FUNC_AUTO_SAY"(char, text)\r\n"
    "   SetString(text)\r\n"
    "   return SetString(char)\r\n"
    "end"
);

DECL_BODY(
    SCR_EX_Voice,
    "function "SCR_FUNC_VOICE"(snd)\r\n"
    "   return SetString(snd)\r\n"
    "end"
);

DECL_BODY(
    SCR_EX_Image,
    "function "SCR_FUNC_IMAGE"(img)\r\n"
    "   return SetString(img)\r\n"
    "end"
);

DECL_BODY(
    SCR_EX_Select,
    "function "SCR_FUNC_SELECT"(opt)\r\n"
    "   return SetString(opt)\r\n"
    "end"
);

/************************************************************************
  push text
  push char
  call AutoText

  push char
  push text
  call ManualText

  char or text can be NULL

************************************************************************/
// 09 140 143

struct BGI_BURIKO_SCRIPT_INSTRUCTION
{
    ULONG OP;

    DECL_HANDLER(*Handler);
    ULONG ParamCount;

    PUSHORT pParamLength;
    PULONG  pParamFlags;
    PCHAR   Name;
    PCHAR   Body;
    ULONG   Flags;
};

BGI_BURIKO_SCRIPT_INSTRUCTION g_BurikoScriptInfo[] =
{
    DECL_INS(ScrCtrl_Push),
    DECL_INS(ScrCtrl_Call,          BGI_INSTRUCTION_FLAGS_PROC),
    DECL_INS(ScrCtrl_02),
    DECL_INS(ScrCtrl_PushString,    BGI_INSTRUCTION_FLAGS_STRING),
    DECL_INS(ScrCtrl_08),
    DECL_INS(ScrCtrl_09),
    DECL_INS(ScrCtrl_0A),
    DECL_INS(ScrCtrl_10),
    DECL_INS(ScrCtrl_11),
    DECL_INS(ScrCtrl_18),
    DECL_INS(ScrCtrl_19),
    DECL_INS(ScrCtrl_1A),
    DECL_INS(ScrCtrl_Return,        BGI_INSTRUCTION_FLAGS_RETURN),
    DECL_INS(ScrCtrl_1C),
    DECL_INS(ScrCtrl_1D),
    DECL_INS(ScrCtrl_1E),
    DECL_INS(ScrCtrl_1F),
    DECL_INS(ScrCtrl_20),
    DECL_INS(ScrCtrl_21),
    DECL_INS(ScrCtrl_22),
    DECL_INS(ScrCtrl_23),
    DECL_INS(ScrCtrl_24),
    DECL_INS(ScrCtrl_25),
    DECL_INS(ScrCtrl_26),
    DECL_INS(ScrCtrl_27),
    DECL_INS(ScrCtrl_28),
    DECL_INS(ScrCtrl_29),
    DECL_INS(ScrCtrl_2A),
    DECL_INS(ScrCtrl_2B),
    DECL_INS(ScrCtrl_30),
    DECL_INS(ScrCtrl_31),
    DECL_INS(ScrCtrl_32),
    DECL_INS(ScrCtrl_33),
    DECL_INS(ScrCtrl_34),
    DECL_INS(ScrCtrl_35),
    DECL_INS(ScrCtrl_38),
    DECL_INS(ScrCtrl_39),
    DECL_INS(ScrCtrl_3A),
    DECL_INS(ScrCtrl_3F),
    DECL_INS(ScrCtrl_40),
    DECL_INS(ScrCtrl_48),
    DECL_INS(ScrCtrl_7F,            BGI_INSTRUCTION_FLAGS_STRING),
    DECL_INS(ScrCtrl_80),
    DECL_INS(ScrCtrl_81),
    DECL_INS(ScrCtrl_82),
    DECL_INS(ScrCtrl_83),
    DECL_INS(ScrCtrl_90),
    DECL_INS(ScrCtrl_91),
    DECL_INS(ScrCtrl_92),
    DECL_INS(ScrCtrl_93),
    DECL_INS(ScrCtrl_94),
    DECL_INS(ScrCtrl_95),
    DECL_INS(ScrCtrl_98),
    DECL_INS(ScrCtrl_99),
    DECL_INS(ScrCtrl_A0),
    DECL_INS(ScrCtrl_A8),
    DECL_INS(ScrCtrl_AA),
    DECL_INS(ScrCtrl_AC),
    DECL_INS(ScrCtrl_E0),
    DECL_INS(ScrCtrl_E1),
    DECL_INS(ScrCtrl_E2),
    DECL_INS(ScrCtrl_E3),
    DECL_INS(ScrCtrl_E4),
    DECL_INS(ScrCtrl_E5),
    DECL_INS(ScrCtrl_E6),
    DECL_INS(ScrCtrl_E7),
    DECL_INS(ScrCtrl_E8),
    DECL_INS(ScrCtrl_EA),
    DECL_INS(ScrCtrl_EB),
    DECL_INS(ScrCtrl_EC),
    DECL_INS(ScrCtrl_F0),
    DECL_INS(ScrCtrl_F1),
    DECL_INS(ScrCtrl_F3),
    DECL_INS(ScrCtrl_F4),
    DECL_INS(ScrCtrl_F5),
    DECL_INS(ScrCtrl_F6),
    DECL_INS(ScrCtrl_F7),
    DECL_INS(ScrCtrl_F8),
    DECL_INS(ScrCtrl_F9),
    DECL_INS(ScrCtrl_FA),
    DECL_INS(ScrCtrl_FC),
    DECL_INS(ScrCtrl_FE),
    DECL_INS(ScrCtrl_FF),

    DECL_INS(ScrSys_100),
    DECL_INS(ScrSys_101),
    DECL_INS(ScrSys_108),
    DECL_INS(ScrSys_10F),
    DECL_INS(ScrSys_110),
    DECL_INS(ScrSys_111),
    DECL_INS(ScrSys_112),
    DECL_INS(ScrSys_113),
    DECL_INS(ScrSys_114),
    DECL_INS(ScrSys_116),
    DECL_INS(ScrSys_117),
    DECL_INS(ScrSys_118),
    DECL_INS(ScrSys_119),
    DECL_INS(ScrSys_11A),
    DECL_INS(ScrSys_11B),
    DECL_INS(ScrSys_11C),
    DECL_INS(ScrSys_120),
    DECL_INS(ScrSys_121),
    DECL_INS(ScrSys_122),
    DECL_INS(ScrSys_123),
    DECL_INS(ScrSys_124),
    DECL_INS(ScrSys_125),
    DECL_INS(ScrSys_128),
    DECL_INS(ScrSys_12C),
    DECL_INS(ScrSys_12F),
    DECL_INS(ScrSys_130),
    DECL_INS(ScrSys_131),
    DECL_INS(ScrSys_132),
    DECL_INS(ScrSys_136),
    DECL_INS(ScrSys_137),
    DECL_INS(ScrSys_138),
    DECL_INS(ScrSys_139),
    DECL_INS(ScrSys_13A),
    DECL_INS(ScrSys_13B),
    DECL_INS(ScrSys_13C),
    DECL_INS(ScrSys_13D),
    DECL_INS(ScrSys_13F),

    DECL_INS(ScrMsg_ShowText),
    DECL_INS(ScrMsg_141),
    DECL_INS(ScrMsg_142),
    DECL_INS(ScrMsg_ShowAutoText),
    DECL_INS(ScrMsg_144),
    DECL_INS(ScrMsg_145),
    DECL_INS(ScrMsg_146),
    DECL_INS(ScrMsg_147),
    DECL_INS(ScrMsg_148),
    DECL_INS(ScrMsg_149),
    DECL_INS(ScrMsg_14A),
    DECL_INS(ScrMsg_14B),
    DECL_INS(ScrMsg_14C),
    DECL_INS(ScrMsg_14D),
    DECL_INS(ScrMsg_14E),
    DECL_INS(ScrMsg_14F),
    DECL_INS(ScrMsg_150),
    DECL_INS(ScrMsg_151),
    DECL_INS(ScrMsg_152),
    DECL_INS(ScrMsg_153),
    DECL_INS(ScrMsg_157),
    DECL_INS(ScrMsg_158),
    DECL_INS(ScrMsg_159),
    DECL_INS(ScrMsg_15C),
    DECL_INS(ScrMsg_15D),
    DECL_INS(ScrMsg_15E),
    DECL_INS(ScrMsg_15F),

    DECL_INS(ScrSelect_160),
    DECL_INS(ScrSelect_161),
    DECL_INS(ScrSelect_164),
    DECL_INS(ScrSelect_165),
    DECL_INS(ScrSelect_166),
    DECL_INS(ScrSelect_168),
    DECL_INS(ScrSelect_169),
    DECL_INS(ScrSelect_16C),

    DECL_INS(ScrSound_180),
    DECL_INS(ScrSound_181),
    DECL_INS(ScrSound_184),
    DECL_INS(ScrSound_185),
    DECL_INS(ScrSound_186),
    DECL_INS(ScrSound_190),
    DECL_INS(ScrSound_191),
    DECL_INS(ScrSound_194),
    DECL_INS(ScrSound_195),
    DECL_INS(ScrSound_196),
    DECL_INS(ScrSound_198),
    DECL_INS(ScrSound_199),
    DECL_INS(ScrSound_19C),
    DECL_INS(ScrSound_19D),
    DECL_INS(ScrSound_19E),
    DECL_INS(ScrSound_1A0),
    DECL_INS(ScrSound_1A1),
    DECL_INS(ScrSound_1A2),
    DECL_INS(ScrSound_1A3),
    DECL_INS(ScrSound_1A4),
    DECL_INS(ScrSound_1A8),
    DECL_INS(ScrSound_1A9),
    DECL_INS(ScrSound_1AA),
    DECL_INS(ScrSound_1AC),
    DECL_INS(ScrSound_1BF),

    DECL_INS(ScrGrp1_220),
    DECL_INS(ScrGrp1_222),
    DECL_INS(ScrGrp1_228),
    DECL_INS(ScrGrp1_229),
    DECL_INS(ScrGrp1_22A),
    DECL_INS(ScrGrp1_230),
    DECL_INS(ScrGrp1_231),
    DECL_INS(ScrGrp1_232),
    DECL_INS(ScrGrp1_233),
    DECL_INS(ScrGrp1_234),
    DECL_INS(ScrGrp1_235),
    DECL_INS(ScrGrp1_236),
    DECL_INS(ScrGrp1_237),
    DECL_INS(ScrGrp1_238),
    DECL_INS(ScrGrp1_239),
    DECL_INS(ScrGrp1_23C),
    DECL_INS(ScrGrp1_23D),
    DECL_INS(ScrGrp1_340),
    DECL_INS(ScrGrp1_348),
    DECL_INS(ScrGrp1_350),
    DECL_INS(ScrGrp1_351),
    DECL_INS(ScrGrp1_352),
    DECL_INS(ScrGrp1_353),
    DECL_INS(ScrGrp1_358),
    DECL_INS(ScrGrp1_380),
    DECL_INS(ScrGrp1_388),
    DECL_INS(ScrGrp1_390),
    DECL_INS(ScrGrp1_391),
    DECL_INS(ScrGrp1_392),
    DECL_INS(ScrGrp1_393),
    DECL_INS(ScrGrp1_394),
    DECL_INS(ScrGrp1_3AF),
    DECL_INS(ScrGrp1_3C0),
    DECL_INS(ScrGrp1_3C1),
    DECL_INS(ScrGrp1_3C2),
    DECL_INS(ScrGrp1_3C4),
    DECL_INS(ScrGrp1_3C5),
    DECL_INS(ScrGrp1_3C6),
    DECL_INS(ScrGrp1_3C7),
    DECL_INS(ScrGrp1_3C8),
    DECL_INS(ScrGrp1_3C9),
    DECL_INS(ScrGrp1_3D0),
    DECL_INS(ScrGrp1_3D2),
    DECL_INS(ScrGrp1_3D4),
    DECL_INS(ScrGrp1_3D5),
    DECL_INS(ScrGrp1_3D6),
    DECL_INS(ScrGrp1_3D8),
    DECL_INS(ScrGrp1_3DC),
    DECL_INS(ScrGrp1_3F0),
    DECL_INS(ScrGrp1_3F1),

    DECL_INS(ScrGrp2_280),
    DECL_INS(ScrGrp2_281),
    DECL_INS(ScrGrp2_284),
    DECL_INS(ScrGrp2_288),
    DECL_INS(ScrGrp2_289),
    DECL_INS(ScrGrp2_28A),
    DECL_INS(ScrGrp2_290),
    DECL_INS(ScrGrp2_2C0),
    DECL_INS(ScrGrp2_2C1),
    DECL_INS(ScrGrp2_2C2),
    DECL_INS(ScrGrp2_2C3),
    DECL_INS(ScrGrp2_2C4),
    DECL_INS(ScrGrp2_2C5),
    DECL_INS(ScrGrp2_2C6),
    DECL_INS(ScrGrp2_2C7),
    DECL_INS(ScrGrp2_2C8),
    DECL_INS(ScrGrp2_2CA),
    DECL_INS(ScrGrp2_2CB),
    DECL_INS(ScrGrp2_2CC),
    DECL_INS(ScrGrp2_2CE),
    DECL_INS(ScrGrp2_2CF),
    DECL_INS(ScrGrp2_2D0),
    DECL_INS(ScrGrp2_2D2),
    DECL_INS(ScrGrp2_2D8),
    DECL_INS(ScrGrp2_2DC),
    DECL_INS(ScrGrp2_2DF),
    DECL_INS(ScrGrp2_2E0),
    DECL_INS(ScrGrp2_2E2),
    DECL_INS(ScrGrp2_2E4),
    DECL_INS(ScrGrp2_2E8),
    DECL_INS(ScrGrp2_2E9),
    DECL_INS(ScrGrp2_2EA),
    DECL_INS(ScrGrp2_2F0),

    DECL_INS(ScrGrp3_240),
    DECL_INS(ScrGrp3_241),
    DECL_INS(ScrGrp3_242),
    DECL_INS(ScrGrp3_244),
    DECL_INS(ScrGrp3_245),
    DECL_INS(ScrGrp3_248),
    DECL_INS(ScrGrp3_24C),
    DECL_INS(ScrGrp3_24D),
    DECL_INS(ScrGrp3_24E),
    DECL_INS(ScrGrp3_258),
    DECL_INS(ScrGrp3_25E),
    DECL_INS(ScrGrp3_25F),
    DECL_INS(ScrGrp3_260),
    DECL_INS(ScrGrp3_262),
    DECL_INS(ScrGrp3_266),
    DECL_INS(ScrGrp3_268),
    DECL_INS(ScrGrp3_27F),

    DECL_INS(ScrGrp4_300),
    DECL_INS(ScrGrp4_301),
    DECL_INS(ScrGrp4_302),
    DECL_INS(ScrGrp4_303),
    DECL_INS(ScrGrp4_304),
    DECL_INS(ScrGrp4_306),
    DECL_INS(ScrGrp4_307),
    DECL_INS(ScrGrp4_308),
    DECL_INS(ScrGrp4_309),
    DECL_INS(ScrGrp4_30C),
    DECL_INS(ScrGrp4_30E),
    DECL_INS(ScrGrp4_31F),
    DECL_INS(ScrGrp4_320),
    DECL_INS(ScrGrp4_328),
    DECL_INS(ScrGrp4_32C),
    DECL_INS(ScrGrp4_33F),

    DECL_INS(SCR_EX_Text),
    DECL_INS(SCR_EX_AutoText),
    DECL_INS(SCR_EX_Select),
    DECL_INS(SCR_EX_Say),
    DECL_INS(SCR_EX_AutoSay),
    DECL_INS(SCR_EX_Voice),
    DECL_INS(SCR_EX_Image),
};

#define SCR_GET_OP                          BP_GET_OP
#define IS_EX_SCR_OP(op)                    (((op) & 0xFFFF0000) != 0)
#define SCR_GET_EX_OP(op)                   ((op) & 0x0000FFFF)

#define SCR_NAME_EXTENSION                  BP_NAME_EXTENSION
#define SCR_NAME_DEFAULT_OP_PREFIX          BP_NAME_DEFAULT_OP_PREFIX
#define SCR_NAME_LABEL                      BP_NAME_LABEL
#define SCR_NAME_LABEL_PREFIX               BP_NAME_LABEL_PREFIX
#define SCR_NAME_DEFAULT_BASE_SCRIPT_NAME   "BGIBS"
#define SCR_NAME_DEFAULT_BASE_SCRIPT        "BGIBS.lua"
#define SCR_NAME_DEFAULT_PARAM_PREFIX       BP_NAME_DEFAULT_PARAM_PREFIX

#define SCR_FUNC_BEGIN_FUNC                 "BeginFunc"
#define SCR_FUNC_ADD_FUNC                   "AddFunc"
#define SCR_FUNC_ADD_STRING                 "AddString"
#define SCR_FUNC_ADD_CALL_LABEL             "AddCallLabel"
#define SCR_FUNC_FINALIZE                   "Finalize"
#define SCR_FUNC_WRITE_INSTRUCTION          BP_FUNC_WRITE_INSTRUCTION
#define SCR_FUNC_WRITE_FILE                 "Write"

CHAR szBaseScrFunc[] = "\
local ffi = require('ffi')\r\n\
local hFile, FileName\r\n\
\r\n\
local DataOffset\r\n\
local LabelMap = {}\r\n\
local CallLabelMap = {}\r\n\
local StringTable = {}\r\n\
local StringRefs = {}\r\n\
local FuncMap = { --[[ FuncNam = '', Offset = 0 ]] }\r\n\
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
    hFile, ErrorMsg = io.open(Name, 'wb+')\r\n\
    if not hFile then\r\n\
        return hFile, ErrorMsg\r\n\
    end\r\n\
\r\n\
    local magic = '"BGI_BURIKO_SCRIPT_MAGIC"'\r\n\
    Write(magic, string.len(magic) + 1)\r\n\
    Write(0, 8)    -- header_size, reserve\r\n\
\r\n\
    return hFile, ErrorMsg\r\n\
end\r\n\
\r\n\
local function Seek(where, offset)\r\n\
    return hFile:seek(where, offset)\r\n\
end\r\n\
\r\n\
local function GetPos()\r\n\
    return hFile:seek()\r\n\
end\r\n\
\r\n\
local function Close()\r\n\
    return hFile:close()\r\n\
end\r\n\
\r\n\
local function WriteInstruction(OP, ...)\r\n\
    local ParamCount, Param\r\n\
\r\n\
    Write(OP, 4)\r\n\
\r\n\
    ParamCount = select('#', ...)\r\n\
    if ParamCount == 0 then\r\n\
        return\r\n\
    end\r\n\
\r\n\
    for i = 1, ParamCount do\r\n\
        Param = select(i, ...)\r\n\
        Write(Param, 4)\r\n\
    end\r\n\
end\r\n\
\r\n\
function AddFunc(...)\r\n\
    local FuncCount, pos\r\n\
\r\n\
    FuncCount = select('#', ...)\r\n\
    Write(FuncCount, 4)\r\n\
\r\n\
    pos = GetPos()\r\n\
    for i = 1, FuncCount do\r\n\
        local len, func\r\n\
\r\n\
        func = select(i, ...)\r\n\
        len = string.len(func) + 1\r\n\
        Write(func, len)\r\n\
        pos = pos + len\r\n\
        FuncMap[func] = pos\r\n\
        Write(0, 4)\r\n\
        pos = pos + 4\r\n\
    end\r\n\
\r\n\
    local HeaderSize = pos\r\n\
\r\n\
    if HeaderSize % 16 ~= 0 then\r\n\
        local pos = ffi.new('int32_t[1]')\r\n\
\r\n\
        HeaderSize = HeaderSize + 16 - 1\r\n\
        pos[0] = HeaderSize / 16\r\n\
        HeaderSize = pos[0] * 16\r\n\
        Seek('set', HeaderSize - 1)\r\n\
        Write(0, 1)\r\n\
    end\r\n\
\r\n\
    Seek('set', 0x1C)\r\n\
    Write(HeaderSize - 0x1C, 4)\r\n\
    Seek('end')\r\n\
    DataOffset = HeaderSize\r\n\
end\r\n\
\r\n\
local function AddLabel(label)\r\n\
    LabelMap[label] = GetPos()\r\n\
end\r\n\
\r\n\
local function AddCallLabel(label)\r\n\
    return table.insert(CallLabelMap, { Offset = GetPos(), Name = label })\r\n\
end\r\n\
\r\n\
local function AddString(str)\r\n\
    local p = StringRefs[str]\r\n\
    if p == nil then\r\n\
        table.insert(StringTable, str)\r\n\
        StringRefs[str] = {}\r\n\
        p = StringRefs[str]\r\n\
    end\r\n\
    return table.insert(p, GetPos())\r\n\
end\r\n\
\r\n\
local function WriteString()\r\n\
    local strtbl = StringTable\r\n\
    local strref = StringRefs\r\n\
\r\n\
    for i = 1, table.getn(strtbl) do\r\n\
        local text = strtbl[i]\r\n\
        local len, pos\r\n\
\r\n\
        len = string.len(text) + 1\r\n\
        pos = GetPos()\r\n\
        Write(text, len)\r\n\
\r\n\
        local refs = strref[text]\r\n\
        for j = 1, table.getn(refs) do\r\n\
            local offset = refs[j]\r\n\
            Seek('set', offset)\r\n\
            Write(pos - DataOffset, 4)\r\n\
        end\r\n\
\r\n\
        Seek('end')\r\n\
    end\r\n\
end\r\n\
\r\n\
local function UpdateLabel()\r\n\
    local map, label, Count\r\n\
\r\n\
    map = CallLabelMap\r\n\
    label = LabelMap\r\n\
    Count = table.getn(map)\r\n\
    for i = 1, Count do\r\n\
        local ins = map[i]\r\n\
        Seek('set', ins.Offset)\r\n\
        Write(label[ins.Name] - DataOffset, 4)\r\n\
    end\r\n\
end\r\n\
\r\n\
function Finalize()\r\n\
    WriteString()\r\n\
    UpdateLabel()\r\n\
end\r\n\
\r\n\
function BeginFunc(func)\r\n\
    local FuncOffset = FuncMap[func]\r\n\
    local pos = GetPos()\r\n\
\r\n\
    if FuncOffset == nil then\r\n\
        print('undefined function \"' .. func .. '\"')\r\n\
        error()\r\n\
    end\r\n\
\r\n\
    Seek('set', FuncOffset)\r\n\
    Write(pos - DataOffset, 4)\r\n\
    Seek('set', pos)\r\n\
\r\n\
    return AddLabel(func)\r\n\
end\r\n\
\r\n\
function AddText(text)\r\n\
    return AddString(text)\r\n\
end\r\n\
\r\n\
function AddImage(image)\r\n\
    return AddString(image)\r\n\
end\r\n\
\r\n\
function AddScript(script)\r\n\
    return AddString(script)\r\n\
end\r\n\
\r\n\
function label(l)\r\n\
    return AddLabel(l)\r\n\
end\r\n\
\r\n\
local function SetString(Text)\r\n\
    Write(0x3, 4)\r\n\
    AddString(Text)\r\n\
    return Write(-1, 4)\r\n\
end\r\n\
";

CHAR szScriptInit[] = "\
require('"SCR_NAME_DEFAULT_BASE_SCRIPT_NAME"')\r\n\
local fscr, err = Create('%s')\r\n\
if not fscr then\r\n\
    print(err)\r\n\
    return -1\r\n\
end\r\n\
\r\n\
";

CHAR szScriptFinalize[] ="\
"SCR_FUNC_FINALIZE"()\
";

#endif // _BURIKOSCRIPT_H_76a6fc53_829f_43e3_b63d_8fb912302066

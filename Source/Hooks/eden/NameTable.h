#ifndef _NAMETABLE_H_
#define _NAMETABLE_H_

#if defined(EF_FD)

enum ECharID
{
    ID_EFFD_INVALID = -1, 
    ID_EFFD_AMEMIYA, ID_EFFD_AKARI,  ID_EFFD_CHIHIRO, ID_EFFD_HIMURA,
    ID_EFFD_HIRO,    ID_EFFD_KEI,    ID_EFFD_KUZE,    ID_EFFD_KYOUSUKE, 
    ID_EFFD_ARISU,   ID_EFFD_MIZUKI, ID_EFFD_MIRAI,   ID_EFFD_MIYAKO,
    ID_EFFD_NAGI,    ID_EFFD_HAYAMA, ID_EFFD_RENJI,   ID_EFFD_SEI, 
    ID_EFFD_SUMIRE,  ID_EFFD_YUUKO
};

SCharNameMap CharName[] =
{
    { "塉媨",   "雨宮",   "雨宫"   },
    { "柧棦",   "明里",   "明里"   },
    { "愮恞",   "千尋",   "千寻"   },
    { "梉",     "夕",     "夕"     },
    { "峢",     "紘",     "纮"     },
    { "宨",     "景",     "景"     },
    { "媣悾",   "久瀬",   "久濑"   },
    { "嫗夘",   "京介",   "京介"   },
    { "傾儕僗", "アリス", "爱丽丝" },
    { "儈僘僉", "ミズキ", "瑞希"   },
    { "枹棃",   "未来",   "未来"   },
    { "傒傗偙", "みやこ", "宫子"   },
    { "撯",     "凪",     "凪"     },
    { "悈昉",   "水姫",   "水姬"   },
    { "楡帯",   "蓮治",   "莲治"   },
    { "惞",     "聖",     "圣"     },
    { "偡傒傟", "すみれ", "堇"     },
    { "桪巕",   "優子",   "优子"   },
};

SCharNameHashMap NameHash[] =
{
    { 0x281124FA, 0xA811E9EE, 0xA817492F },
    { 0xF812ABA0, 0xDC18616C, 0xDC18616C },
    { 0x9C124872, 0x9C11E326, 0x9C1A4332 },
    { 0x0012E05B, 0x0019E0A6, 0x0019E0A6 },
    { 0x0011A068, 0x00178087, 0x00180080 },
    { 0x00118069, 0x0017C0B0, 0x0017C0B0 },
    { 0xD8124522, 0x0C139F82, 0x0C1CDFFD },
    { 0x7811656C, 0xA417FFEB, 0xA417FFEB },
    { 0x2C0020DC, 0xA234F370, 0xD2F901DC },
    { 0x63F020CB, 0xE5E4F365, 0xC01984A0 },
    { 0x8812AB8A, 0xD01867B6, 0xD01867B6 },
    { 0x85C000B6, 0x9DE4D3F8, 0xB01ABC51 },
    { 0x001260E2, 0x0010804D, 0x0010804D },
    { 0x1412E852, 0xB8112528, 0xB817E525 },
    { 0x00118CA0, 0x3C1AA44C, 0xAC1AA04C },
    { 0x001200B9, 0x0018407D, 0x001940A5 },
    { 0x7F6000ED, 0x7784D3A7, 0x001BA0C0 },
    { 0x10118BF0, 0x781AA151, 0x141A8950 },
};

#elif defined(EDEN)

enum ECharID
{
    ID_EDEN_INVALID = -1, 
    ID_EDEN_RYO,   ID_EDEN_SION, ID_EDEN_RAVI, ID_EDEN_ERIKA, ID_EDEN_NATSUME, 
    ID_EDEN_INABA, ID_EDEN_MAYA, 
};

SCharNameMap CharName[] =
{
    { "椇",     "亮",     "亮",     },
    { "僔僆儞", "シオン", "诗音",   },
    { "儔償傿", "ラヴィ", "拉维",   },
    { "僄儕僇", "エリカ", "艾莉卡", },
    { "僫僣儊", "ナツメ", "夏目",   },
    { "堫梩",   "稲葉",   "稻叶",   },
    { "恀栭",   "真夜",   "真夜",   },
};

SCharNameHashMap NameHash[] = 
{
    { 0x0012E0BA, 0x001820C1, 0x001820C1 },
    { 0x21702014, 0xA364F33B, 0xAC1A25F6 },
    { 0x588020C6, 0xDE84F36A, 0xB419A0AE },
    { 0x2C6020CE, 0xA294F362, 0xC2D781CB },
    { 0x8A802006, 0x1CB4F328, 0x1018E73C },
    { 0xB812A477, 0x48195BFF, 0xF81A1A34 },
    { 0x781288E8, 0x981A2A3A, 0x981A2A3A },
};

#elif defined(EF_FIRST)

enum ECharID
{
    ID_EFFD_INVALID = -1, 
    ID_EFF_CHIHIRO,  ID_EFF_HIMURA, ID_EFF_HIRO,   ID_EFF_IZUMI, ID_EFL_KEI,
    ID_EFF_KYOUSUKE, ID_EFF_MIZUKI, ID_EFF_MIYAKO, ID_EFF_MOM,   ID_EFF_NAGI,
    ID_EFF_OOMURA,   ID_EFF_YUUKO,
};

SCharNameMap CharName[] =
{
    { "愮恞",   "千尋",   "千寻"   },
    { "梉",     "夕",     "夕"     },
    { "峢",     "紘",     "纮"     },
    { "愹",     "泉",     "泉"     },
    { "宨",     "景",     "景"     },
    { "嫗夘",   "京介",   "京介"   },
    { "儈僘僉", "ミズキ", "瑞希"   },
    { "傒傗偙", "みやこ", "宫子"   },
    { "曣",     "母",     "母"     },
    { "撯",     "凪",     "凪"     },
    { "戝懞",   "大村",   "大村"   },
    { "桪巕",   "優子",   "优子"   },
};

SCharNameHashMap NameHash[] =
{
    { 0x9C124872, 0x9C11E326, 0x9C1A4332 },
    { 0x0012E05B, 0x0019E0A6, 0x0019E0A6 },
    { 0x0011A068, 0x00178087, 0x00180080 },
    { 0x001200F2, 0x001900AA, 0x001900AA },
    { 0x00118069, 0x0017C0B0, 0x0017C0B0 },
    { 0x7811656C, 0xA417FFEB, 0xA417FFEB },
    { 0x63F020CB, 0xE5E4F365, 0xC01984A0 },
    { 0x85C000B6, 0x9DE4D3F8, 0xB01ABC51 },
    { 0x0012A0EA, 0x001880B8, 0x001880B8 },
    { 0x001260E2, 0x0010804D, 0x0010804D },
    { 0x94126839, 0xCC16DAE6, 0xCC16DAE6 },
    { 0x10118BF0, 0x781AA151, 0x141A8950 },
};

#elif defined(EF_LATTER)

enum ECharID
{
    ID_EFFD_INVALID = -1, 
    ID_EFL_AKANE, ID_EFL_AMEMIYA, ID_EFL_CHIHIRO, ID_EFL_HIMURA,  ID_EFL_KEI,
    ID_EFL_KUZE,  ID_EFL_MIZUKI,  ID_EFL_MIRAI,   ID_EFL_NAGI,    ID_EFL_HAYAMA,
    ID_EFL_RENJI, ID_EFL_SUMIRE,  ID_EFL_YUUKO,   ID_EFL_ONNANOKO,
};

SCharNameMap CharName[] =
{
    { "埄",     "茜",     "茜",    },
    { "塉媨",   "雨宮",   "雨宫"   },
    { "愮恞",   "千尋",   "千寻"   },
    { "梉",     "夕",     "夕"     },
    { "宨",     "景",     "景"     },
    { "媣悾",   "久瀬",   "久濑"   },
    { "儈僘僉", "ミズキ", "瑞希"   },
    { "枹棃",   "未来",   "未来"   },
    { "撯",     "凪",     "凪"     },
    { "悈昉",   "水姫",   "水姬"   },
    { "楡帯",   "蓮治",   "莲治"   },
    { "偡傒傟", "すみれ", "堇"     },
    { "桪巕",   "優子",   "优子"   },
    { "彈偺巕", "女の子", "女孩子" },
};

SCharNameHashMap NameHash[] =
{
    { 0x001100A9, 0x001B80E7, 0x001B80E7 },
    { 0x281124FA, 0xA811E9EE, 0xA817492F },
    { 0x9C124872, 0x9C11E326, 0x9C1A4332 },
    { 0x0012E05B, 0x0019E0A6, 0x0019E0A6 },
    { 0x00118069, 0x0017C0B0, 0x0017C0B0 },
    { 0xD8124522, 0x0C139F82, 0x0C1CDFFD },
    { 0x63F020CB, 0xE5E4F365, 0xC01984A0 },
    { 0x8812AB8A, 0xD01867B6, 0xD01867B6 },
    { 0x001260E2, 0x0010804D, 0x0010804D },
    { 0x1412E852, 0xB8112528, 0xB817E525 },
    { 0x00118CA0, 0x3C1AA44C, 0xAC1AA04C },
    { 0x7F6000ED, 0x7784D3A7, 0x001BA0C0 },
    { 0x10118BF0, 0x781AA151, 0x141A8950 },
    { 0x3961806C, 0x32FAB35A, 0x82FABC5B },
};

#endif

#endif /* _NAMETABLE_H_ */
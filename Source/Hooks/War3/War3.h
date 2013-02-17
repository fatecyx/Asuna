#include <Windows.h>
#include <d3d8.h>
#include "my_headers.h"

#define PATCH_NEW 0
#define PATCH_OLD 1

typedef struct _tagPatch
{
	Char	*cData[2];
	UInt32	dwSize;
	UInt32	dwAddress;
} sPatch;

typedef struct _tagFuncPatch
{
	BYTE  byFlag;
	UInt32 dwAddress;
	UInt32 dwFunc;
} sFuncPatch;

typedef struct 
{
    UInt32 dwMask;
    UInt32 dwFunction;
    LPCSTR lpParam;
    UInt32 dwReserve;
} TWar3StartupParam;

Bool HookChangeLocalName();
Void HookSetNameLimit();
Void FASTCALL ChangeLocalName(PChar pszLocalName, Int LocalNameLength, PChar pszDestBuffer, Int MaxLength);
Void FASTCALL ChangeChatTextColor(PChar pszChatText, Int Length, PChar pszDestBuffer, Int MaxLength);

// hack map
Int  FASTCALL GetObjectFlags(LPVoid This, Int_Ptr, Int_Ptr, Int_Ptr, Int_Ptr);
Bool STDCALL  IsMyObject(LPVoid);
Bool STDCALL  IsControlable(Byte, Word);

int  WINAPI mybind(SOCKET s, struct sockaddr FAR* name, int namelen);
Bool WINAPI NotifyGameStart(int X, int Y);
Bool WINAPI MyShowWindow(HWND hWnd, Int32 nCmdShow);
Bool WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
HWND WINAPI MyCreateWindowExA(IN DWORD dwExStyle, IN LPCSTR lpClassName, IN LPCSTR lpWindowName, IN DWORD dwStyle, IN Int32 X, IN Int32 Y, IN Int32 nWidth, IN int nHeight, IN HWND hWndParent, IN HMENU hMenu, IN HINSTANCE hInstance, IN LPVoid lpParam);
HIMC WINAPI MyImmAssociateContext(HWND hWnd, HIMC hIMC);

DWORD WINAPI HookCreateDevice(IDirect3D8 *lpD3D, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnWindowPosChanged(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnKeyDownAndUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnActivate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


TWar3StartupParam param[] = 
{
    { 0x00000, 0, "d3d" }, 
    { 0x00000, 1, "opengl" }, 
    { 0x00000, 2, "swtnl" },             // 关闭部分透明和光影以兼容旧显卡
    { 0x00000, 3, "classic" },           // ROC
    { 0x20000, 4, "datadir" }, 
    { 0x20000, 5, "loadfile" },          // -loadfile Maps\Test\WorldEditTestMap.w3m
    { 0x20000, 6, "gametype" },          // ??
    { 0x00000, 7, "fullscreen" }, 
    { 0x00000, 8, "w" }, 
};

SPatch patch_exe_120[] =
{
  // 1.20
    { 0x33,                          1, 0x189BE },
    { countof(param),                1, 0x3CA51 },
    { (UInt32)&param,                4, 0x3CA53 },
    { (UInt32)MyImmAssociateContext, 4, 0x4A098 }, 
/*
    // 1.21
    { 0x33,           1, 0x18B4E },
    { countof(param), 1, 0x3CDE1 },
    { (DWORD)&param,  4, 0x3CDE3 },
*/
};

SFuncPatch func_exe_120[] =
{
    { CALL, 0x189D8, mybind,	0x01 },	// 多开, 1.20e
    { CALL, 0x1F1B9, NotifyGameStart, 0x01 },	// 游戏开始
//    {CALL, 0x18B68, (DWORD)mybind,	0x01},	// 多开, 1.21
};

/*
SPatch patch_port_124[] = 
{
    { 0, 2, 0x65DFF4 },
    { 0, 4, 0x6640ED },
    { 0, 4, 0x6640F2 },
    { 0, 4, 0x662F15 },
};
*/

SPatch patch_game_120[] =
{
    { 0x00,                       1,	0x6DD573 },        // 4 MB
    { 0x80,                       1,	0x6EDCA4 },        // 4 MB
    { 0x80,                       1,	0x6F89B7 },        // 4 MB

    { 0xEB,                       1,	0x005C6B },        // 更多分辨率
//    { 0x81,                       1,    0x0DB19B },        // 彩字
    { 0xEB,                       1,	0x00602C },        // 多开
    { 0xEB,                       1,	0x006B34 },        // check system language
    { (UInt32)MyCreateWindowExA,  4,	0x705474 },
//    { 0x90D233,                   3,	0x0C8795 },        // temp
};

SPatch patch_game_124[] =
{   // 6387
    { 0xEB,                          1, 0x008FBD },        // 更多分辨率
//    { 0x81,                          1,	0x7B95C9 },        // 彩字
    { 0xEB,                          1,	0x00974C },        // 多开
    { 0xEB,                          1,	0x0076F6 },        // check system language
    { countof(param),                1, 0x4C24F1 },
    { (UInt32)&param,                4, 0x4C24F3 },
    { (UInt32)MyCreateWindowExA,     4,	0x87F8C4 },
    { (UInt32)MyImmAssociateContext, 4,	0x87F100 },

    // hack map
    { 0x0164808D, 4, 0x34E8EA },
};

SFuncPatch func_game_124[] = 
{
    { CALL, 0x6E290F, mybind,              0x01 },	// 多开
    { CALL, 0x59A71D, ChangeLocalName,     0x00 },	// name-Host
    { CALL, 0x59498D, ChangeLocalName,     0x00 },	// name-Guest
    { CALL, 0x5AFED8, ChangeChatTextColor, 0x00 },	// 对话自动彩字: 创建前
    { CALL, 0x2FD30C, ChangeChatTextColor, 0x00 },	// 对话自动彩字: 游戏中
    { CALL, 0x6C7179, NotifyGameStart,     0x01 },	// 游戏开始
    { CALL, 0x57DB0C, HookChangeLocalName, 0x01 },	// name
    { CALL, 0x57DA96, HookSetNameLimit,    0x03 },	// name len

    { JUMP, 0xF4E0,   GetObjectFlags,      0x00 },	// no foggy
//    { JUMP, 0x286830, IsMyObject,          0x00 },
//    { JUMP, 0x3A4100, IsControlable,       0x00 },
};

/*

0xF540 return -1, 大地图全亮

27B9B0
334CC0
606950
606460
35A800
32D3C0
2C7FD0
37A623
37AA28

*/

sPatch patch[] =
{
	{{"\xB8\x64\x01\x00\x00\x90", "\x8B\x87\x68\x01\x00\x00"}, 6, 0x127B3D},
	{{"\x00", "\x08"}, 1, 0x12DC1B},
	{{"\x00", "\x08"}, 1, 0x12DC5B},
	{{"\xEB", "\x75"}, 1, 0x13EF03},
	{{"\xEC", "\xE4"}, 1, 0x147C53},
	{{"\x00", "\x01"}, 1, 0x1491A8},
	{{"\x00\x00", "\xC0\x04"}, 2, 0x1494E4},
	{{"\x00", "\x14"}, 1, 0x150984},
	{{"\x00", "\x14"}, 1, 0x15159A},
	{{"\x00", "\x14"}, 1, 0x15164A},
	{{"\x00", "\x14"}, 1, 0x15174B},
	{{"\xEB", "\x74"}, 1, 0x1573EC},
	{{"\xEB\x06", "\x85\xC0"}, 2, 0x166E5E},
	{{"\x00", "\x78"}, 1, 0x16FE0D},
	{{"\x58\x40\xEB\x03", "\x50\x56\xE8\x5F"}, 4, 0x17D4EA},
	{{"\x40\xC3", "\xC3\x90"}, 2, 0x1ACFFC},
	{{"\x00", "\x2E"}, 1, 0x1BD5A8},
	{{"\xEB", "\x75"}, 1, 0x1BD5BB},

//	{{"\x8B\x4D\x18\x90\x90\x90\x90\xE8\x77", "\x8B\x55\xF4\x50\x8D\x4D\xF8\xE8\xD7"}, 9, 0x1BEBCD},		// 已方显示为红色

	{{"\x00", "\x11"}, 1, 0x1BED1C},
	{{"\xEB", "\x75"}, 1, 0x1BFABE},
	{{"\x03", "\x00"}, 1, 0x21EAD4},
	{{"\x03", "\x01"}, 1, 0x21EAE8},
	{{"\xE8", "\xC6"}, 1, 0x23D3C0},		// 不倒计时
	{{"\xEB", "\x7A"}, 1, 0x23D60F},
	{{"\x33\xDB\x33\xC9\x90\x90", "\x8B\x59\x14\x8B\x49\x10"}, 6, 0x2A07C5},
	{{"\x33\xD2\x33\xC0\x90\x90", "\x8B\x42\x14\x8B\x52\x10"}, 6, 0x2A0923},
	{{"\x3C\x4C\x74\x04\xB0\xFF\xEB\x04\xB0\xB0\x90\x90", "\x3D\xFF\x00\x00\x00\x76\x05\xC1\xF8\x1F\xF6\xD0"}, 0xC, 0x2C240C},
	{{"\x90\xE9", "\x0F\x84"}, 2, 0x2D34ED},

	{{"\xEB", "\x75"}, 1, 0x30C873},
	{{"\x00", "\x17"}, 1, 0x30C889},
	{{"\x00", "\x07"}, 1, 0x30C899},
	{{"\xEB", "\x75"}, 1, 0x30C9B0},
	{{"\x00", "\xB6"}, 1, 0x30CA06},
	{{"\x00", "\xA9"}, 1, 0x30CA13},
	{{"\xEB", "\x75"}, 1, 0x30CB75},
	{{"\x00", "\x1F"}, 1, 0x30CB8A},
	{{"\x00", "\x0F"}, 1, 0x30CB9A},
	{{"\x00", "\x8E"}, 1, 0x321CC8},
	{{"\x00", "\x7F"}, 1, 0x321CDA},
	{{"\x00", "\x08"}, 1, 0x406B55},
	{{"\x00", "\xDC"}, 1, 0x442CC2},
	{{"\x00", "\x1E"}, 1, 0x443376},
	{{"\x00\x00", "\x60\x01"}, 2, 0x45A643},
	{{"\x00\x00", "\x26\x01"}, 2, 0x45E7A0},    // 设置结点
	{{"\x00", "\x0F"}, 1, 0x466528},
	{{"\x00", "\x91"}, 1, 0x46B25A},
	{{"\x00", "\x0F"}, 1, 0x4A11A1},    // skills

	{{"\x00", "\xF7"}, 1, 0x54C0C1},    // some items
	{{"\x00\x00", "\x61\x01"}, 2, 0x557400},    // attack
	{{"\x00", "\x4A"}, 1, 0x55E15D},    // build
};
// 魔理沙与6色蘑菇 按键修改

#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")
//#pragma comment(linker,"/ENTRY:DllMain")
#define DIRECTINPUT_VERSION 0x800

#include <Windows.h>
#include "my_common.h"
#include "my_mem.h"
#include <dinput.h>

typedef struct
{
    BYTE orig;
    BYTE mod;
} SKeyMod;

Void WINAPI CenterWindow(HWND hWnd)
{
    int  x, y;
    RECT rcGame, rcSys;

    SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcSys, 0);
    GetWindowRect(hWnd, &rcGame);
    x = ((rcSys.right - rcSys.left) - (rcGame.right - rcGame.left)) >> 1;
    y = ((rcSys.bottom - rcSys.top) - (rcGame.bottom - rcGame.top)) >> 1;
    SetWindowPos(hWnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
}

BOOL WINAPI MyShowWindow(HWND hWnd, int nCmdShow)
{
    Char *szConfig = ".\\6kinoko.ini";
    Char *orig_key[] = { "UP", "DOWN", "LEFT", "RIGHT", "Z", "A", "C", "X" };
    SKeyMod km[countof(orig_key)] = { { DIK_UP }, { DIK_DOWN }, { DIK_LEFT }, { DIK_RIGHT }, { DIK_Z }, { DIK_A }, { DIK_C }, { DIK_X } };

    for (Int i = 0; i != countof(orig_key); ++i)
        km[i].mod = GetPrivateProfileIntA("Kanade", orig_key[i], km[i].orig, szConfig);

    SPatch p[] =
    {
        { km[0].mod, 4, 0x6E618 }, // up
        { km[1].mod, 4, 0x6E61F }, // down
        { km[2].mod, 4, 0x6E626 }, // left
        { km[3].mod, 4, 0x6E62D }, // right
        { km[4].mod, 4, 0x6E634 }, // z
        { km[5].mod, 4, 0x6E63B }, // a
        { km[6].mod, 4, 0x6E642 }, // c
        { km[7].mod, 4, 0x6E649 }, // v
        { DISCL_NONEXCLUSIVE|DISCL_FOREGROUND, 1, 0x08A84 }, // win key
    };
/*
    SFuncPatch f[] =
    {
        { CALL, 0xDF07, KeyStateModify, 0 },
    };
*/
    PatchMemory(p, countof(p), 0, 0, GetModuleHandle(0));

    CenterWindow(hWnd);
    return ShowWindow(hWnd, nCmdShow);
}
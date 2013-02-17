#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "d3d9.lib")
#define DIRECTINPUT_VERSION 0x800

#include <Windows.h>
#include <dinput.h>
#include "my_headers.h"

typedef struct
{
    UInt16 Original;
    UInt16 Modified;
} SKeyMap;

enum EKeyCombination { KEY_AB = 0xFF + 1, KEY_AC, KEY_BC, KEY_ABC, KEY_START };
enum EKeyIndex
{
    KEY_UP,    KEY_DOWN,   KEY_LEFT, KEY_RIGHT,
    KEY_LIGHT, KEY_MEDIUM, KEY_HARD, KEY_CHANGE, KEY_TAUNT,
};

SKeyMap KeyMap[] =
{
    { DIK_UP,      DIK_W },
    { DIK_DOWN,    DIK_S },
    { DIK_LEFT,    DIK_A },
    { DIK_RIGHT,   DIK_D },

    { DIK_Z,       DIK_J }, // Çá
    { DIK_X,       DIK_K }, // ÖÐ
    { DIK_C,       DIK_L }, // ÖØ
    { DIK_S,       DIK_H }, // »»ÈË
    { DIK_LSHIFT,  DIK_1 }, // ÌôÐÆ

    { KEY_AB,      DIK_U },
    { KEY_AC,      DIK_I },
    { KEY_BC,      DIK_O },
    { KEY_ABC,     DIK_Y },
    { KEY_START,   DIK_F1 },

    { DIK_A,       0 },
    { DIK_D,       0 },
    { DIK_Q,       0 },
    { DIK_E,       0 },
    { DIK_RETURN,  DIK_RETURN },
    { DIK_RSHIFT,  DIK_RSHIFT },
};

Void UpdateKeyMap(LPSIZE pWindowSize = NULL)
{
    WChar szConfig[MAX_PATH];
    PWChar KeyName[] =
    {
        L"UP", L"DOWN", L"LEFT", L"RIGHT",
        L"A", L"B", L"C", L"CHANGE", L"TAUNT",
        L"AB", L"AC", L"BC", L"ABC", L"START",
    };

    lstrcpyW(szConfig + GetExecuteDirectoryW(szConfig, countof(szConfig)), L"\\KeyBoard.ini");
    for (ULong i = 0; i != countof(KeyName); ++i)
    {
        KeyMap[i].Modified = GetPrivateProfileIntW(L"Amano", KeyName[i], KeyMap[i].Modified, szConfig);
    }

    if (pWindowSize)
    {
        pWindowSize->cx = GetPrivateProfileIntW(L"Amano", L"WIDTH",  pWindowSize->cx, szConfig);
        pWindowSize->cy = GetPrivateProfileIntW(L"Amano", L"HEIGHT", pWindowSize->cy, szConfig);
    }
}

HRESULT STDCALL KeyStateModify(PChar pbKeyState)
{
    Char     byKeyState[256];
    PUInt32  pKeyFlags;
    HRESULT  hResult;
    SKeyMap *pKeyMap;
    LPDIRECTINPUTDEVICE lpKeyboard;

    __asm
    {
        mov lpKeyboard, eax;
        lea eax, pbKeyState;
        lea eax, [eax+4+14h];
        mov pKeyFlags, eax;
    }

    *pKeyFlags = 0;
    __asm
    {
        mov eax, lpKeyboard;
        mov eax, [eax]IDirectInputDeviceA.GetDeviceState;
    }
    hResult = lpKeyboard->GetDeviceState(256, pbKeyState);

    if (FAILED(hResult))
    {
        return hResult;
    }

    CopyStruct(byKeyState, pbKeyState, sizeof(byKeyState));
    pKeyMap = KeyMap;
    for (int i = 0; i != countof(KeyMap); ++i)
    {
        if (pKeyMap[i].Original <= 0xFF)
        {
            Byte Key = (Byte)pKeyMap[i].Modified;
            pbKeyState[pKeyMap[i].Original] = Key ? byKeyState[Key] : 0;
        }
        else
        {
            if ((Char)byKeyState[pKeyMap[i].Modified] >= 0)
                continue;

            switch (pKeyMap[i].Original)
            {
                case KEY_AB:
                    pbKeyState[pKeyMap[KEY_LIGHT].Original]  |= 0x80;
                    pbKeyState[pKeyMap[KEY_MEDIUM].Original] |= 0x80;
                    break;

                case KEY_AC:
                    pbKeyState[pKeyMap[KEY_LIGHT].Original] |= 0x80;
                    pbKeyState[pKeyMap[KEY_HARD].Original]  |= 0x80;
                    break;

                case KEY_BC:
                    pbKeyState[pKeyMap[KEY_MEDIUM].Original] |= 0x80;
                    pbKeyState[pKeyMap[KEY_HARD].Original]   |= 0x80;
                    break;

                case KEY_ABC:
                    pbKeyState[pKeyMap[KEY_LIGHT].Original]  |= 0x80;
                    pbKeyState[pKeyMap[KEY_MEDIUM].Original] |= 0x80;
                    pbKeyState[pKeyMap[KEY_HARD].Original]   |= 0x80;
                    break;

                case KEY_START:
                    *pKeyFlags |= 0x100;
                    break;
            }
        }
    }

    if (pbKeyState[DIK_F5] < 0 && (pbKeyState[DIK_LCONTROL] < 0 || pbKeyState[DIK_RCONTROL] < 0))
        UpdateKeyMap();

    return hResult;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    if (ulReason == DLL_PROCESS_ATTACH)
    {
        WChar szPath[MAX_PATH];
        SIZE WindowSize = { 896, 504 };

        GetExecuteDirectoryW(szPath, countof(szPath));
        SetCurrentDirectoryW(szPath);
        UpdateKeyMap(&WindowSize);

        SPatch p[] =
        {
            { 0x6,        1, 0x4111 },
            { 0x0026748D, 4, 0x619F },

            { WindowSize.cx, 4, 0x6C20 },
            { WindowSize.cy, 4, 0x6C30 },
            { WindowSize.cx, 4, 0x6C44 },
            { WindowSize.cy, 4, 0x6C3D },
        };
        SFuncPatch f[] =
        {
            { CALL, 0x613F, KeyStateModify, 3},
        };
        PatchMemory(p, countof(p), f, countof(f), GetModuleHandleW(0));
    }

    return True;
}
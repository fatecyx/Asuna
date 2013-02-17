#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.CRT=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "imm32.lib")

#include <Windows.h>
#include <windowsX.h>
#include <WinUser.h>
#include <WinSock.h>
#include <shlwapi.h>
#include "my_mem.h"
#include "undoc_api.h"
#include "War3.h"
#include "my_commsrc.h"

#define _WSTRING(str) L##str
#define WSTRING(str) _WSTRING(str)

#define ConfigNameA  ".\\Amano.ini"
#define SectionNameA "Amano"
#define ConfigNameW  WSTRING(ConfigNameA)
#define SectionNameW WSTRING(SectionNameA)
#define TextColorLength 10

HWND    g_hGameWnd;
DWORD   g_dwGameBase;
WNDPROC g_lpfnOldWndProc;
BYTE    NewKeyMap[256];
LPDWORD g_pdwGameFramesCount;
Bool    g_bWindowMode, g_bIsTyping;
Bool   *g_pbIsStarted_Host, *g_pbIsStarted_Guest;
Char    g_szTextColor[11];
//SPatch *g_patch_port;
//DWORD   g_dwPortPatchCount;

ACCEL KeyMap[0xFF];

Int32 SetBrightness(Int32 iBrightnessDelta)
{
    HDC		hDC;
    HWND    hWnd;
    WORD	wRamp[3][256];
    Int32   iDelta = 0;

    static Bool  bBakup = False;
    static Int32 iBrightness;
    static WORD  wOldRamp[3][256];

    hWnd = g_hGameWnd;
    hDC = GetDC(hWnd);

    if (iBrightnessDelta == 0)
    {
        if (bBakup == True)
        {
            iDelta = iBrightness;
            iBrightness = 0;
            SetDeviceGammaRamp(hDC, (LPVoid)&wOldRamp);
        }
        ReleaseDC(hWnd, hDC);
        return iDelta;
    }

    if (bBakup == False)
    {
        bBakup = True;
        GetDeviceGammaRamp(hDC, (LPVoid)&wOldRamp);
    }

    iBrightness += iBrightnessDelta;
    GetDeviceGammaRamp(hDC, (LPVoid)&wRamp);
    for (Int32 iIndex = 0; iIndex != 256; iIndex++)
    {
        Int32 iArrayValue = iIndex * (iBrightness + 256);

        if (iArrayValue >> 16)
            iArrayValue = 65535;

        wRamp[0][iIndex] =
            wRamp[1][iIndex] =
            wRamp[2][iIndex] = (WORD)iArrayValue;
    }

    SetDeviceGammaRamp(hDC, (LPVoid)&wRamp);
    ReleaseDC(hWnd, hDC);

    return iBrightness;
}

HWND WINAPI MyCreateWindowExA(IN DWORD dwExStyle, IN LPCSTR lpClassName, IN LPCSTR lpWindowName, IN DWORD dwStyle, IN int X, IN int Y, IN int nWidth, IN int nHeight, IN HWND hWndParent, IN HMENU hMenu, IN HINSTANCE hInstance, IN LPVoid lpParam)
{
    HWND hWnd;

    hWnd = CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    if (hWnd && g_hGameWnd == NULL)
    {
        g_hGameWnd = hWnd;
        g_lpfnOldWndProc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)WndProc);
    }

    return hWnd;
}

int WINAPI mybind(SOCKET s, struct sockaddr FAR* name, int namelen)
{
    Int32 iRet;
    WORD *pwPort, wPort;
//    SPatch *p;

    iRet = bind(s, name, namelen);
    if (iRet != SOCKET_ERROR)
        return iRet;

    do
    {
        pwPort = (WORD *)(name->sa_data);
        wPort = *pwPort;
        if (wPort == 0xFFFF)
            break;

        wPort = (LOBYTE(wPort) << 8) | HIBYTE(wPort);
        ++wPort;
        *pwPort = (LOBYTE(wPort) << 8) | HIBYTE(wPort);
        iRet = bind(s, name, namelen);
    } while (iRet == SOCKET_ERROR);
/*
    if (iRet != SOCKET_ERROR && (p = g_patch_port))
    {
        DWORD j;

        j = g_dwPortPatchCount;
        for (int i = 0; i != j; ++i)
            p[i].dwData = wPort;
        PatchMemory(p, j, 0, 0, 0);
    }
*/
    return iRet;
}

DWORD WINAPI MsgBoxThread(LPVoid lpParam)
{
    Int r;
    r = MessageBoxTimeoutW(NULL, L"Game has been started", 
        L"Closed in 5 seconds", 64, 0, 5000);

    return r;
}

Bool WINAPI NotifyGameStart(int X, int Y)
{
    Bool r;
    HWND hWndActive, hWndGame;

    hWndGame = g_hGameWnd;
    hWndActive = GetActiveWindow();
    if (hWndActive != hWndGame)
    {
        HANDLE hThread;
        hThread = CreateThread(0, 0, MsgBoxThread, 0, 0, 0);
        if (hThread)
            CloseHandle(hThread);
    }

    return True;
    return SetCursorPos(X, Y);
}

Bool WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    Bool bResult = PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
    if (bResult == False)
    {
        DWORD dwTickCount;
        static DWORD dwLastTickCount, dwCount = 4;

        dwTickCount = GetTickCount();
        if (dwTickCount - dwLastTickCount < 10 && dwCount-- == 0)
        {
            dwCount = 4;
            Sleep(1);
        }
        dwLastTickCount = dwTickCount;
    }

    return bResult;
}

ASM DWORD FilterNonDesktopRefreshRate()
{
    __asm
    {
        xor eax, eax;
        cmp dword ptr [ebp-14h], 3Ch;
        jnz not_same;
        mov eax, dword ptr [ebp-10h];
        cmp eax, 16h;
not_same:
        ret;
    }
}

DWORD WINAPI HookCreateDevice(IDirect3D8 *lpD3D, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface)
{
    if (pPresentationParameters->Windowed == False)
    {
        DEVMODEW dm;

        dm.dmSize = sizeof(dm);
        EnumDisplaySettingsExW(NULL, ENUM_CURRENT_SETTINGS, &dm, 0);
        pPresentationParameters->FullScreen_RefreshRateInHz = dm.dmDisplayFrequency;
    }

    return SUCCEEDED(lpD3D->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface));
}

LRESULT WINAPI OnWindowPosChanged(HWND hWnd, LPWINDOWPOS lpWindowPos)
{
    static Bool bInit = False;
    Int32 x, y;
    RECT rcSystem;
    Char  ch;
    PCChar lpCmdLine;
    Char szKeyCmd[0x20];

    if (bInit == True)
        return ERROR_SUCCESS;

    bInit = True;

    lpCmdLine = GetCommandLineA();

    szKeyCmd[0] = '-';
    lstrcpyA(szKeyCmd + 1, param[countof(param) - 1].lpParam);
    x = lstrlenA(szKeyCmd);
    y = 0;
    while (ch = *lpCmdLine++)
    {
        if ((ch & 0xDF) == (szKeyCmd[y] & 0xDF))
        {
            if (++y == x)
                break;
        }
        else
            y = 0;
    }
    if (y == 0)
        return ERROR_SUCCESS;

    g_bWindowMode = True;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rcSystem, NULL);
    x = rcSystem.right - rcSystem.left;
    y = rcSystem.bottom - rcSystem.top;

    if (x == lpWindowPos->cx && y == lpWindowPos->cy)
        return ERROR_SUCCESS;

    x = (x - lpWindowPos->cx) >> 1;
    y = (y - lpWindowPos->cy) >> 1;
    SetWindowPos(hWnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
    OnActivate(hWnd, WM_ACTIVATE, WA_ACTIVE, 0);

    return ERROR_SUCCESS;
}

Bool FASTCALL IsValidTextColor(PCChar pszTextColor)
{
    if (pszTextColor == NULL)
        return False;
    if (pszTextColor[0] != '|' || (pszTextColor[1] & 0xDF) != 'C')
        return False;

    for (Int i = 2; i != sizeof(g_szTextColor); ++i)
    {
        Char ch = pszTextColor[i];
        if (ch <= '9' && ch >= '0')
            continue;

        ch &= 0xDF;
        if (ch >= 'A' && ch <= 'F')
            continue;

        return False;
    }

    return True;
}

WChar UpperChar(WChar ch)
{
    if (ch >= 'a' && ch <= 'z')
        ch &= 0xDF;

    return ch;
}

Void WINAPI UpdateSettings(PByte pbNewKey)
{
    WChar szKeyName[11];
    WChar ch, KeyRetrieve[0x100];
    PWChar pStart, pCur;
    Byte   fVirt;

    ZeroMemory(KeyMap, sizeof(KeyMap));
    for (Int32 i = 0; i != 9; ++i)
    {
        KeyRetrieve[0] = 0;
        wsprintfW(szKeyName, L"VK_NUMPAD%d", i + 1);
        if (GetPrivateProfileStringW(SectionNameW, szKeyName, KeyRetrieve, KeyRetrieve, countof(KeyRetrieve), ConfigNameW))
        {
            fVirt = 0;
            pStart = KeyRetrieve;
            pCur = pStart;

            while (ch = UpperChar(*pCur++))
            {
                if (ch == '+')
                {
                    *(pCur - 1) = 0;
                    if (!lstrcmpW(pStart, L"ALT"))
                        fVirt |= FALT;
                    else if (!lstrcmpW(pStart, L"SHIFT"))
                        fVirt |= FSHIFT;
                    else if (!lstrcmpW(pStart, L"CTRL"))
                        fVirt |= FCONTROL;

                    pStart = pCur;
                }
                else
                {
                    *(pCur - 1) = ch;
                }
            }

            if (pStart[1])
                continue;

            ch = pStart[0];
            if (ch > 'Z' || ch < 'A')
                continue;

            KeyMap[ch].fVirt = fVirt;
            KeyMap[ch].key = i + VK_NUMPAD1;
        }
    }

    szKeyName[1] = 0;
    for (Int32 i = 'A'; i != 'Z' + 1; ++i)
    {
        szKeyName[0] = i;
        KeyRetrieve[0] = 0;
        if (GetPrivateProfileStringW(SectionNameW, szKeyName, KeyRetrieve, KeyRetrieve, countof(KeyRetrieve), ConfigNameW))
        {
            fVirt = 0;
            pStart = KeyRetrieve;
            pCur = pStart;

            while (ch = UpperChar(*pCur++))
            {
                if (ch == '+')
                {
                    *(pCur - 1) = 0;
                    if (!lstrcmpW(pStart, L"ALT"))
                        fVirt |= FALT;
                    else if (!lstrcmpW(pStart, L"SHIFT"))
                        fVirt |= FSHIFT;
                    else if (!lstrcmpW(pStart, L"CTRL"))
                        fVirt |= FCONTROL;

                    pStart = pCur;
                }
                else
                {
                    *(pCur - 1) = ch;
                }
            }

            if (pStart[1])
                continue;

            ch = pStart[0];
            if (ch > 'Z' || ch < 'A')
                continue;

            KeyMap[ch].fVirt = fVirt;
            KeyMap[ch].key = i;

            continue;

            ch = KeyRetrieve[0] & 0xDF;
            if (ch <= 'Z' && ch >= 'A')
                NewKeyMap[ch] = i;
        }
    }

    if (GetPrivateProfileStringA(SectionNameA, "TextColor", g_szTextColor, 
            g_szTextColor, sizeof(g_szTextColor), ConfigNameA) != TextColorLength && 
        IsValidTextColor(g_szTextColor) == False)
    {
            g_szTextColor[0] = 0;
    }
}

DWORD WINAPI ButtonDown(LPVoid lParam)
{
    Int32 pos;
    POINT p;
    HWND hWnd;

    hWnd = g_hGameWnd;
    do
    {
        GetCursorPos(&p);
        ScreenToClient(hWnd, &p);
        pos = p.y << 16 | p.x;
        SendMessage(hWnd, (Int32)lParam, 0, pos);
        Sleep(50);
        SendMessage(hWnd, (Int32)lParam + 1, 0, pos);

    } while (GetKeyState(VK_SHIFT) < 0 || GetKeyState(VK_F5) >= 0);

    return 0;
}

Bool IsGameStarted()
{
    if (g_pdwGameFramesCount && *g_pdwGameFramesCount >= 0x150)
        return True;
    else if (g_pbIsStarted_Guest && *g_pbIsStarted_Guest)
        return True;
    else if (g_pbIsStarted_Host && *g_pbIsStarted_Host)
        return True;

    return False;
}

Bool Patch(Bool bOpen)
{
    PChar pDataOriginal, pDataToCopy;
    PByte pbBaseAddress, pbAddr;
    UInt  Size;

    pbBaseAddress = (PByte)GetModuleHandleW(L"Game.dll");
    for (Int i = 0; i != countof(patch); ++i)
    {
        pDataOriginal = patch[i].cData[bOpen];
        pDataToCopy   = patch[i].cData[!bOpen];
        Size = patch[i].dwSize;
        pbAddr = patch[i].dwAddress + pbBaseAddress;
        if (!memcmp(pbAddr, pDataOriginal, Size))
        {
            DWORD dwOld;
            if (VirtualProtectEx(NtCurrentProcess(), pbAddr, Size, PAGE_EXECUTE_READWRITE, &dwOld))
            {
                memcpy(pbAddr, pDataToCopy, Size);
                VirtualProtectEx(NtCurrentProcess(), pbAddr, Size, dwOld, &dwOld);
            }
        }
    }

    return True;
}

LRESULT WINAPI OnKeyUpAndDown(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Word KeyCode;
    if (IsGameStarted() && g_bIsTyping == False && wParam <= 0xFF && (KeyCode = KeyMap[wParam].key))
    {
        do
        {
            Byte CtrlKey[3] = { };
            Byte fVirt = KeyMap[wParam].fVirt;
            if (fVirt)
            {
                if (fVirt & FALT)
                {
                    if (GetKeyState(VK_MENU) >= 0)
                        break;

                    CtrlKey[0] = VK_MENU;
                }
                if (fVirt & FSHIFT)
                {
                    if (GetKeyState(VK_SHIFT) >= 0)
                        break;

                    CtrlKey[1] = VK_SHIFT;
                }
                if (fVirt & FCONTROL)
                {
                    if (GetKeyState(VK_CONTROL) >= 0)
                        break;

                    CtrlKey[2] = VK_CONTROL;
                }
            }

            for (Int i = 0; i != countof(CtrlKey); ++i)
            {
                if (CtrlKey[i])
                    SendMessageA(hWnd, WM_KEYUP, CtrlKey[i], lParam);
            }

            SendMessageA(hWnd, uMsg, KeyCode, lParam);
            for (Int i = 0; i != countof(CtrlKey); ++i)
            {
                if (CtrlKey[i])
                    SendMessageA(hWnd, WM_KEYDOWN, CtrlKey[i], lParam);
            }

            return ERROR_SUCCESS;
        } while (0);
    }

    if (uMsg == WM_KEYUP && GetKeyState(VK_SHIFT) < 0) switch (wParam)
    {
        case VK_F4:
            UpdateSettings(NewKeyMap);
            break;

        case VK_F5:
        case VK_F6:
        {
            ULong ExitCode;
            static HANDLE hThread;

            if (hThread)
            {
                if (GetExitCodeThread(hThread, &ExitCode) == False || ExitCode == STILL_ACTIVE)
                    break;

                CloseHandle(hThread);
            }

            hThread = CreateThread(NULL, 0, ButtonDown, 
                wParam == VK_F5 ? (LPVoid)WM_LBUTTONDOWN : (LPVoid)WM_RBUTTONDOWN, 
                0, NULL);

            break;
        }

        case VK_F7:
        case VK_F8:
            Patch(wParam == VK_F7);
    }

    return ERROR_SUCCESS;
}

LRESULT WINAPI OnActivate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (g_bWindowMode == False)
        return ERROR_SUCCESS;

    if (wParam == WA_INACTIVE)
        ClipCursor(NULL);
    else
    {
        INT iCaptionHeight;
        RECT rcGame;
        POINT ptCursor;

        GetClientRect(hWnd, &rcGame);
        ClientToScreen(hWnd, (LPPOINT)&(rcGame.left));
        ClientToScreen(hWnd, (LPPOINT)&(rcGame.right));
        iCaptionHeight = GetSystemMetrics(SM_CYCAPTION);
        GetCursorPos(&ptCursor);
        if (ptCursor.x < rcGame.left ||
            ptCursor.x > rcGame.right ||
            ptCursor.y < rcGame.top - iCaptionHeight || 
            ptCursor.y > rcGame.top)
        {
            ClipCursor(&rcGame);
        }
    }

    return ERROR_SUCCESS;
}

LRESULT HandleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hWnd, WM_WINDOWPOSCHANGED, OnWindowPosChanged);

        case WM_ACTIVATE:
            OnActivate(hWnd, uMsg, wParam, lParam);
            break;

        case WM_KEYUP:
        case WM_KEYDOWN:
            OnKeyUpAndDown(hWnd, uMsg, wParam, lParam);
            break;
    }

    return NO_ERROR;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HandleMessages(hWnd, uMsg, wParam, lParam);
    return g_lpfnOldWndProc(hWnd, uMsg, wParam, lParam);
    return CallWindowProc(g_lpfnOldWndProc, hWnd, uMsg, wParam, lParam);
}

HIMC WINAPI MyImmAssociateContext(HWND hWnd, HIMC hIMC)
{
    g_bIsTyping = !!hIMC;
    return ImmAssociateContext(hWnd, hIMC);
}

// color text
// |CAARRGGBB
// |CFFE19E55ColorText

Void
FASTCALL
ChangeChatTextColor(
    PChar pszChatText, 
    Int   Length, 
    PChar pszDestBuffer, 
    Int   MaxLength
)
{
    do
    {
        if (MaxLength < sizeof(g_szTextColor))
            break;
        if (g_szTextColor[0] == 0)
            break;
        if (GetKeyState(VK_CONTROL) < 0)
            break;

        CopyStruct(pszDestBuffer, g_szTextColor, TextColorLength);
        pszDestBuffer += TextColorLength;
        MaxLength -= TextColorLength;
    } while (0);

    memcpy(pszDestBuffer, pszChatText, Length + 1);
}

Void FASTCALL ChangeLocalName(
    PChar pszLocalName, 
    Int   LocalNameLength, 
    PChar pszDestBuffer, 
    Int   MaxLength
)
{
    Int   Length;
    WChar szLocalName[0x400];

    szLocalName[0] = 0;
    Length = GetPrivateProfileStringW(SectionNameW, 
                    L"LocalName", szLocalName, szLocalName, MaxLength, ConfigNameW);

    if (Length == 0)
    {
        if (pszLocalName)
            memcpy(pszDestBuffer, pszLocalName, LocalNameLength + 1);

        return;
    }

    WideCharToMultiByte(CP_UTF8, 0, szLocalName, -1, pszDestBuffer, MaxLength, 0, 0);
}

ASM Bool HookChangeLocalName()
{
    __asm
    {
        lea  eax, [esp+10h];
        xor  ecx, ecx;
        or   edx, -1;
        push 1000h;
        push eax;
        call ChangeLocalName;
        mov  ecx, [esi+1C4h];
        ret;
    }
}

ASM Void HookSetNameLimit()
{
    __asm
    {
        mov  eax, 0x1000;
        xchg eax, [esp];
        mov  ecx, [esi+1C4h];
        jmp  eax;
    }
}

Int FASTCALL GetObjectFlags(LPVoid This, Int_Ptr, Int_Ptr, Int_Ptr, Int_Ptr)
{
    return -1;
}

Bool STDCALL IsMyObject(LPVoid)
{
    return True;
}

Bool STDCALL IsControlable(Byte, Word)
{
    return True;
}

Void GetPatchData(LPVoid lpGameBaseAddress, SPatch **patch_exe, SFuncPatch **func_exe, SPatch **patch_game, SFuncPatch **func_game, LPDWORD pdwExePatchCount, LPDWORD pdwGamePatchCount, LPDWORD pdwExeFuncCount, LPDWORD pdwGameFuncCount)
{
    if (lpGameBaseAddress == NULL)
        return;

    SPatch *p_exe, *p_game;
    SFuncPatch *f_exe, *f_game;
    DWORD dwExePatch, dwGamePatch, dwExeFunc, dwGameFunc;
    Bool *pbIsStarted_Host, *pbIsStarted_Guest, *pbIsTyping;
    LPDWORD pdwGameFrames;

    pbIsTyping        = NULL;
    pbIsStarted_Host  = NULL;
    pbIsStarted_Guest = NULL;
    pdwGameFrames     = NULL;
    if (*(0xDB19B + (PByte)lpGameBaseAddress) == 0x87)
    {
        pbIsStarted_Host = (Bool *)0x87DEE0;
        pbIsStarted_Guest = (Bool *)0x875998;

        dwExePatch = countof(patch_exe_120);
        dwExeFunc  = countof(func_exe_120);
        dwGamePatch = countof(patch_game_120);
        dwGameFunc = 0;

        p_exe  = patch_exe_120;
        f_exe  = func_exe_120;
        p_game = patch_game_120;
        f_game = NULL;
    }
    else if (*(0x7B95C9 + (PByte)lpGameBaseAddress) == 0x87)
    {
        pdwGameFrames    = (LPDWORD)0xAE5498;
//        g_patch_port = patch_port_124;
//        g_dwPortPatchCount = countof(patch_port_124);

        dwExePatch  = 0;
        dwExeFunc   = 0;
        dwGamePatch = countof(patch_game_124);
        dwGameFunc  = countof(func_game_124);

        p_exe  = NULL;
        f_exe  = NULL;
        p_game = patch_game_124;
        f_game = func_game_124;
    }

//    g_pbIsTyping         = pbIsTyping;
    g_pdwGameFramesCount = pdwGameFrames;
    g_pbIsStarted_Host  = pbIsStarted_Host;
    g_pbIsStarted_Guest = pbIsStarted_Guest;

    if (pdwExePatchCount) *pdwExePatchCount = dwExePatch;
    if (pdwExeFuncCount) *pdwExeFuncCount = dwExeFunc;
    if (pdwGamePatchCount) *pdwGamePatchCount = dwGamePatch;
    if (pdwGameFuncCount) *pdwGameFuncCount = dwGameFunc;
    if (patch_game) *patch_game = p_game;
    if (patch_exe)  *patch_exe = p_exe;
    if (func_exe)   *func_exe = f_exe;
    if (func_game)  *func_game = f_game;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    switch (ulReason)
    {
        case DLL_PROCESS_ATTACH:
            {
                LPVoid  lpBaseAddress;
                DWORD   dwGamePatchCount, dwExePatchCount, dwGameFuncCount, dwExeFuncCount;
                SPatch *patch_game, *patch_exe;
                SFuncPatch *func_game, *func_exe;

                DisableThreadLibraryCalls(hInstance);

                lpBaseAddress = (LPVoid)GetModuleHandleW(L"Game.dll");
                if (lpBaseAddress == NULL)
                    return True;

                GetPatchData(
                    lpBaseAddress, 
                    &patch_exe, 
                    &func_exe, 
                    &patch_game, 
                    &func_game, 
                    &dwExePatchCount, 
                    &dwGamePatchCount, 
                    &dwExeFuncCount, 
                    &dwGameFuncCount);

//                if (patch_game && g_pdwGameFramesCount && g_pbIsTyping)
                if (patch_game)
                {
                    UpdateSettings(NewKeyMap);
                    g_dwGameBase = (DWORD)lpBaseAddress;
                    if (g_pbIsStarted_Host)
                        g_pbIsStarted_Host  += (DWORD)lpBaseAddress / sizeof(*g_pbIsStarted_Host);
                    if (g_pbIsStarted_Guest)
                        g_pbIsStarted_Guest += (DWORD)lpBaseAddress / sizeof(*g_pbIsStarted_Guest);
                    if (g_pdwGameFramesCount)
                        g_pdwGameFramesCount += (DWORD)lpBaseAddress / sizeof(*g_pdwGameFramesCount);
                    PatchMemory(patch_game, dwGamePatchCount, func_game, dwGameFuncCount, lpBaseAddress);

//                    for (DWORD i = 0, j = g_dwPortPatchCount; i != j; ++i)
//                          g_patch_port[i].dwOffset += (DWORD)lpBaseAddress;
                }
                if (patch_exe) PatchMemory(patch_exe, dwExePatchCount, func_exe, dwExeFuncCount, GetModuleHandleW(0));
                Patch(True);
            }
            break;

        case DLL_PROCESS_DETACH:
            {
                void (STDCALL *DllUnregisterServer)();
                DllUnregisterServer = (void (STDCALL *)())GetProcAddress(LoadLibraryExW(L"blizzard.ax", 0, 0), "DllUnregisterServer");
                if (DllUnregisterServer)
                    DllUnregisterServer();
            }
    }

    return True;
}
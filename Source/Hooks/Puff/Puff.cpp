#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(lib, "wodTunnel.lib")

#include <Windows.h>
#include "nt_api.h"
#include "my_common.h"

EXTC void WINAPI DllRegisterServer();
EXTC void WINAPI DllUnregisterServer();

VOID MyExitProcess(UINT uExitCode)
{
    DllUnregisterServer();
    ExitProcess(uExitCode);
}

WNDPROC glpfnWndProc;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CHAR:
        switch (wParam)
        {
        case 'I':
            ReleaseCapture();
            SendMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(493, 151));
            SendMessage(hWnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(493, 151));
            break;
        }
    }

    return CallWindowProc(glpfnWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL WINAPI MyShowWindow(HWND hWnd, int nCmdShow)
{
    static BOOL bInit = FALSE;
    BOOL bResult = ShowWindow(hWnd, nCmdShow);
    if (!bInit)
    {
        bInit = TRUE;
        ReleaseCapture();
        SendMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(493, 69));
        SendMessage(hWnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(493, 69));
    }

    return bResult;
}

FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    static BOOL bRegisterd = FALSE;

    if (!bRegisterd)
    {
        bRegisterd = TRUE;
        DllRegisterServer();
    }

    if ((int)lpProcName > 0xFFFF)
    {
        switch (HashAPI(lpProcName))
        {
            case 0xE4E07FDB: return (FARPROC)MyShowWindow;
            case 0x3DEA3901: return (FARPROC)MyExitProcess;
        }
    }

    return GetProcAddress(hModule, lpProcName);
}

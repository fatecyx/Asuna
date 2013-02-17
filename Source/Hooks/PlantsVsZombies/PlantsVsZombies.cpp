#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")

#include "PlantsVsZombies.h"
#include "my_mem.h"

HWND g_hMainWnd = NULL;

int WINAPI DllMain(HINSTANCE hInst, unsigned long reason, void* lpReserved)
{
    static BOOL bWrite = FALSE;

    if (reason != DLL_PROCESS_ATTACH || bWrite == TRUE)
        return TRUE;

    DWORD dwBaseAddress, dwOld, dwOld2;
    
    bWrite = TRUE;
    DisableThreadLibraryCalls(hInst);
    dwBaseAddress = (DWORD)GetModuleHandleA(0);
    PATCH_FRAME(patch, countof(patch), func, countof(func), dwBaseAddress, dwOld, dwOld2);
    return TRUE;
}

BOOL WINAPI MyGetMessageA(OUT LPMSG lpMsg, IN OPTIONAL HWND hWnd, IN UINT wMsgFilterMin, IN UINT wMsgFilterMax)
{
    BOOL bResult = GetMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
    if (GetForegroundWindow() != g_hMainWnd)
        Sleep(1);
    return bResult;
}

BOOL WINAPI MyPeekMessageA(OUT LPMSG lpMsg, IN OPTIONAL HWND hWnd, IN UINT wMsgFilterMin, IN UINT wMsgFilterMax, IN UINT wRemoveMsg)
{
    BOOL bResult = PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
    if (GetForegroundWindow() != g_hMainWnd)
        Sleep(1);
    return bResult;
}

#define KEY_DOWN(x) (GetAsyncKeyState(x) < 0)

DWORD WINAPI MyThread(LPVOID lpParam)
{
    HWND hWndMain = (HWND)lpParam;

    while (1)
    {
        Sleep(50);

        if (GetForegroundWindow() != hWndMain)
            continue;

        if (KEY_DOWN('A'))
        {
            LONG  pos;
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(hWndMain, &p);
            pos = p.y << 16 | p.x;
            SendMessage(hWndMain, WM_LBUTTONDOWN, 0, pos);
            Sleep(10);
            SendMessage(hWndMain, WM_LBUTTONUP, 0, pos);
        }
        else if (KEY_DOWN('S'))
        {
            LONG  pos;
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(hWndMain, &p);
            pos = p.y << 16 | p.x;
            SendMessage(hWndMain, WM_LBUTTONDOWN, 0, pos);
            Sleep(100);
            SendMessage(hWndMain, WM_LBUTTONUP, 0, pos);
        }
        else if (KEY_DOWN('Q'))
        {
            LONG  x, y, pos;
            SIZE  Block = {85, 90}, Start = {40, 90};

            x = 9 * 3;
            y = 6 * 4 + 1;
            POINT ptStart = {Start.cx + (Block.cx >> 2), Start.cy + (Block.cx / 3)};
            pos = ptStart.y << 16 | ptStart.x;
            for (int w = 0; w != x; ++w)
            {
                for (int h = 0; h != y; ++h)
                {
                    SendMessage(hWndMain, WM_LBUTTONDOWN, 0, pos);
                    PostMessage(hWndMain, WM_LBUTTONUP, 0, pos);
                    pos += (Block.cy >> 2) << 16;
                }
                pos += Block.cx / 3;
                pos = LOWORD(pos) | (ptStart.y << 16);
            }
        }
    }

    return 0;
}

HWND WINAPI MyCreateWindowExA(IN DWORD dwExStyle, IN LPCSTR lpClassName, IN LPCSTR lpWindowName, IN DWORD dwStyle, IN int X, IN int Y, IN int nWidth, IN int nHeight, IN HWND hWndParent, IN HMENU hMenu, IN HINSTANCE hInstance, IN LPVOID lpParam)
{
    HWND hWnd;

    hWnd = CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    if (g_hMainWnd == NULL)
    {
        g_hMainWnd = hWnd;
        CreateThread(NULL, 0, MyThread, (LPVOID)hWnd, 0, NULL);
    }

    return hWnd;
}
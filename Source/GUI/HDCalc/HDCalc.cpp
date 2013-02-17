#pragma comment(linker,"/ENTRY:WinMain")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")

#include <Windows.h>
#include "my_common.h"
#include "HDCalc.h"

HINSTANCE hInst;
static const CHAR szClassName[] = "Kaede";
static const CHAR szWindowsName[] = "HD Integer Calculator";

FORCEINLINE int WINAPI WinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    if (MyRegisterClass(hInstance) == 0)
    {
        MessageBoxA(NULL, "RegisterClassEx() failed", NULL, 64);
        return -1;
    }

    if (InitInstance(hInstance, nCmdShow) == FALSE)
    {
        MessageBoxA(NULL, "CreateWindowEx() failed", NULL, 64);
        return -2;
    }

    while (GetMessageA(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

ATOM WINAPI MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style			= 0;
    wcex.lpfnWndProc	= (WNDPROC)WndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcex.lpszMenuName	= NULL;
    wcex.lpszClassName	= szClassName;
    wcex.hIconSm        = NULL;

    return RegisterClassExA(&wcex);
}

void WINAPI CenterWindow(HWND hWnd, HWND hWndParant)
{
    int  x, y;
    RECT rcWnd, rcDesktop;

    if (hWndParant == NULL)
    {
        SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcDesktop, 0);
    }
    else
    {
        GetClientRect(hWndParant, &rcDesktop);
    }
    GetWindowRect(hWnd, &rcWnd);
    x = ((rcDesktop.right - rcDesktop.left) - (rcWnd.right - rcWnd.left)) >> 1;
    y = ((rcDesktop.bottom - rcDesktop.top) - (rcWnd.bottom - rcWnd.top)) >> 1;
    SetWindowPos(hWnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
}

BOOL WINAPI InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;

    hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindowEx(0, szClassName, szWindowsName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 382, 187, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

    CenterWindow(hWnd, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hDC;
    PAINTSTRUCT ps;
    int wmId, wmEvent;

    switch (message)
    {
    case WM_CREATE:
        break;

    case WM_CHAR:
        if (wParam == VK_ESCAPE)
            DestroyWindow(hWnd);
        break;

    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

        switch (wmId)
        {
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;

        case WM_PAINT:
            {
                HBRUSH brush;

                hDC = BeginPaint(hWnd, &ps);

                SelectObject(hDC, GetStockObject(DC_BRUSH));
                SetDCBrushColor(hDC, RGB(255, 0, 0));
                GetDCBrushColor(hDC);

                EndPaint(hWnd, &ps);
                break;
            }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    lpCmdLine = GetCommandLine() + 1;
    while (*lpCmdLine != '"') ++lpCmdLine;
    ExitProcess(WinMain2(GetModuleHandleA(NULL), 0, ++lpCmdLine, SW_SHOWDEFAULT));
}
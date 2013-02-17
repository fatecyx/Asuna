#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")
#pragma comment(linker,"/ENTRY:DllMain")

#include <Windows.h>
#include "my_common.h"
#include "my_mem.h"

BOOL WINAPI MySetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
    RECT rcDesktop;
    
    SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcDesktop, 0);
    X = ((rcDesktop.right - rcDesktop.left) - cx) >> 1;
    Y = ((rcDesktop.bottom - rcDesktop.top) - cy) >> 1;
    return SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags&~SWP_NOMOVE);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    static BOOL bInit = False;

    if (bInit == False)
    {
        TFuncPatch f[] = 
        {
            { CALL, 0x82A6, (DWORD)MySetWindowPos, 1 }, 
        };
        bInit = True;
        PatchMemory(0, 0, f, countof(f), GetModuleHandleA("D2gfx.dll"));
    }

    return True;
}
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")
#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(lib, "vfw32.lib")

#include "MyLibrary.cpp"

BOOL WINAPI MyUpdateWindow(HWND hWnd)
{
    int  x, y;
    RECT rcWindow, rcDesktop;

    SystemParametersInfoW(SPI_GETWORKAREA, 0, &rcDesktop, 0);
    GetWindowRect(hWnd, &rcWindow);

    x = ((rcDesktop.right - rcDesktop.left) - (rcWindow.right - rcWindow.left)) >> 1;
    y = ((rcDesktop.bottom - rcDesktop.top) - (rcWindow.bottom - rcWindow.top)) >> 1;

    SetWindowPos(hWnd, HWND_NOTOPMOST, x, y, 0, 0, SWP_NOSIZE);
    
    return UpdateWindow(hWnd);
}

ASM Void STDCALL SetChooseFontFlag(LPCHOOSEFONTW pcf)
{
    __asm
    {
        or  eax, 0x3000000;
        mov [edi]pcf.Flags, eax;
        ret;
    }
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    switch (ulReason)
    {
        case DLL_PROCESS_ATTACH:
            MEMORY_FUNCTION_PATCH f[] = 
            {
                //   const:7006
    //            { CALL , 0x0C6657, MyUpdateWindow,    1 },  // 29490 9th ref
    //            { CALL , 0x50AA57, SetChooseFontFlag, 1 },  // 29490  const:7006
                PATCH_FUNCTION(CALL, AUTO_DISASM, 0x5643E8, SetChooseFontFlag),
                PATCH_FUNCTION(CALL, AUTO_DISASM, 0x0D6BC7, MyUpdateWindow),
            };

            LdrDisableThreadCalloutsForDll(hInstance);

            Nt_PatchMemory(0, 0, f, countof(f), Nt_FindLdrModuleByName(&WCS2US(L"PotPlayer.dll"))->DllBase);
    }

    return True;
}

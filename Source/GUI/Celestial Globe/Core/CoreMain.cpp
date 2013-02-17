#pragma comment(linker, "/ENTRY:wWinMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "../UI/CelestialGlobeUI.lib")

#include "Core.h"
#include "my_commsrc.h"

ForceInline UInt WinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWChar lpCmdLine, Int nCmdShow)
{
    CCGCore Core(NULL);

    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    return Core.Run();
}

Int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWChar lpCmdLine, Int nCmdShow)
{
    Int   Result;

    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    g_HeapHandle = RtlCreateHeap(0, NULL, 0, 0, NULL, NULL);
//    MyLib_Initialize();
/*
    WChar end;
    lpCmdLine = GetCommandLineW();
    end = *lpCmdLine++ == '\"' ? '\"' : ' ';
    while (*lpCmdLine && *lpCmdLine != end) ++lpCmdLine;
    if (*++lpCmdLine)
    {
        while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;
    }
*/
    Result = WinMain2(/*GetModuleHandleW*/(NULL), 0, lpCmdLine, SW_SHOWDEFAULT);

    RtlDestroyHeap(g_HeapHandle);
//    MyLib_UnInitialize();

    NtTerminateProcess(NtCurrentProcess(), Result);
}

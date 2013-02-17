#pragma comment(linker,"/ENTRY:tWinMain")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")
#pragma comment(lib, "comctl32.lib")
#define NOT_USE_CUSTOM_MEMFUNC

#include "Babylon.h"
#include "my_headers.h"
#include "resource.h"
#include "Mem.cpp"

//TChar szTitle[] = _T("Gate of Babylon - ")_T(__DATE__)_T(" ")_T(__TIME__);
TChar szTitle[] = _T("Built on ")_T(__DATE__)_T(" ")_T(__TIME__);

ForceInline int WINAPI WinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    DWORD dwStyle, dwClsStyle;
    CBabylon Babylon;
    RECT rc = { 0, 0, 1024, 768 };
    LPRECT lprc = &rc;

    lprc = 0;

    InitCommonControls();

    if (Babylon.CheckSystemEnvironment() == False)
        return 1;

    dwStyle    = WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;// & ~WS_MAXIMIZEBOX;// & ~WS_SIZEBOX;
    dwClsStyle = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    if (Babylon.Create(
                    szTitle,
                    szTitle,
                    NULL,
                    hInstance, 
                    lprc,
                    dwClsStyle,
                    dwStyle,
                    0,
                    MAKEINTRESOURCE(IDI_KANADE),
                    hInstance) == NULL)
    {
        return 1;
    }

    Babylon.CenterWindow();
    Babylon.Show();

    return Babylon.Execute();
}

int WINAPI tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    TChar end;

    lpCmdLine = GetCommandLine();
    end = *lpCmdLine++ == '"' ? '"' : ' ';
    while (*lpCmdLine && *lpCmdLine != end) ++lpCmdLine;
    if (*++lpCmdLine)
    {
        while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;
    }

    ExitProcess(WinMain2(GetModuleHandle(NULL), 0, lpCmdLine, SW_SHOWDEFAULT));
}
#pragma comment(linker,"/ENTRY:tWinMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "Packer2.h"

TChar szTitle[] = _T("Built on ")_T(__DATE__)_T(" ")_T(__TIME__);

ForceInline Int WinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, PTChar lpCmdLine, Int nCmdShow)
{
    CPacker2 packer2;

    if (packer2.CreateEx(szTitle, szTitle, NULL, hInstance) == NULL)
        return 1;

    packer2.CenterWindow();
    packer2.Show();

    return packer2.Execute();
}

Int WINAPI tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PTChar lpCmdLine, Int nCmdShow)
{
    TChar end;
    lpCmdLine = GetCommandLine();
    end = *lpCmdLine++ == '\"' ? '\"' : ' ';
    while (*lpCmdLine && *lpCmdLine != end) ++lpCmdLine;
    if (*++lpCmdLine)
    {
        while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;
    }
    ExitProcess(WinMain2(GetModuleHandle(NULL), 0, lpCmdLine, SW_SHOWDEFAULT));
}
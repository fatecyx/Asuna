#pragma comment(linker,"/ENTRY:wWinMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "ControllerScript.h"
#include "ModelScript.h"
#include "ViewScript.h"
#include "Mem.cpp"

ForceInline UInt WinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWChar lpCmdLine, Int nCmdShow)
{
    CModelScript      ModelScript;
    CControllerScript Controller;
    CViewScriptEditor ScriptEditor;

    Controller.AttachModel(&ModelScript);
    Controller.AttachView(&ScriptEditor);

    return Controller.Execute();
}

Int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWChar lpCmdLine, Int nCmdShow)
{
    WChar end;
    lpCmdLine = GetCommandLineW();
    end = *lpCmdLine++ == '\"' ? '\"' : ' ';
    while (*lpCmdLine && *lpCmdLine != end) ++lpCmdLine;
    if (*++lpCmdLine)
    {
        while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;
    }
    ExitProcess(WinMain2(GetModuleHandleW(NULL), 0, lpCmdLine, SW_SHOWDEFAULT));
}
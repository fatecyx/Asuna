#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "msvcrt.lib")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"
#include "hrArc.h"

Bool bCtrlC;

BOOL CALLBACK HandlerRoutine(DWORD dwCtrlType)
{
    switch(dwCtrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        bCtrlC = True;
        return True;
    }
    return False;
}

ForceInline void main2(int argc, char **argv)
{
    ChrArc arc;

    SetConsoleCtrlHandler(HandlerRoutine, True);
    for (int i = 1; !bCtrlC && i != argc; ++i)
        arc.Auto(*++argv);
    if (bCtrlC)
    {
        printf("\nUser abort.\n");
        getch();
    }
}

void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
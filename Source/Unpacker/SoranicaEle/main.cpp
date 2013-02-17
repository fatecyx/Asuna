#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include <Windows.h>
#include "malie.h"
#include "Mem.cpp"

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

ForceInline Void main2(Int argc, WChar **argv)
{
    CMalie m;

    setlocale(LC_CTYPE, "");
    SetConsoleCtrlHandler(HandlerRoutine, True);
    for (Int32 i = 1; i != argc; ++i)
        m.Auto(*++argv);

    if (bCtrlC)
    {
        printf("user abort\n");
        getch();
    }
    return;
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
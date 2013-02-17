#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "Kara.h"

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
    setlocale(LC_CTYPE, "");
    SetConsoleCtrlHandler(HandlerRoutine, True);

    CKaranoShoujo kara;

    for (Int i = 1; i != argc; ++i)
    {
        kara.Auto(*++argv);
        printf("OK\n\n");
        Sleep(500);
    }

    if (bCtrlC)
    {
        printf("user abort\n");
        getch();
    }
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
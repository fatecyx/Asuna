#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"
#include "KeiOn.h"

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
    _wsetlocale(LC_CTYPE, L"");
    SetConsoleCtrlHandler(HandlerRoutine, True);

    CKeion kon;

    for (Int i = 1; i != argc; ++i)
    {
        kon.Auto(*++argv);
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
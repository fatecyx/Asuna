#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"
#include "piano.h"

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

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    printf("\noffset: %X\n", ExceptionInfo->ExceptionRecord->ExceptionAddress);
    getch();

    return EXCEPTION_CONTINUE_SEARCH;
}

ForceInline Void main2(Int argc, WChar **argv)
{
    CPiano piano;

    SetConsoleCtrlHandler(HandlerRoutine, True);
    AddVectoredExceptionHandler(True, VectoredHandler);
    for (Int32 i = 1; i != argc; ++i)
        piano.Auto(*++argv);

    if (bCtrlC)
    {
        printf("\nUser abort.\n");
        getch();
    }
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "frfr2.h"
#include "my_commsrc.h"

INIT_CONSOLE_HANDLER

ForceInline Void main2(Int argc, WCHAR **argv)
{
    if (argc == 1)
        return;

    CFrfr2 rs;
    while (--argc)
        rs.Auto(*++argv);
}

void __cdecl main(Int argc, WCHAR **argv)
{
    getargsW(&argc, &argv);
//    argv = CmdLineToArgvW(Nt_GetCommandLine(), &argc);
    main2(argc, argv);
    Nt_ExitProcess(0);
}
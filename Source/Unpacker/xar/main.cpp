#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "Xar.h"
#include "my_commsrc.h"

INIT_CONSOLE_HANDLER

ForceInline Void main2(Int argc, WCHAR **argv)
{
    if (argc == 1)
        return;

    CXar rs;
    while (--argc)
        rs.Auto(*++argv);
}

void __cdecl main(Int argc, WCHAR **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    Nt_ExitProcess(0);
}

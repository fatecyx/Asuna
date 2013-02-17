#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "BGI.H"
#include "my_commsrc.h"

INIT_CONSOLE_HANDLER

ForceInline Void main2(Int argc, WChar **argv)
{
    if (argc == 1)
        return;

    CBGIUnpacker bgi;
    while (--argc)
    {
        bgi.Auto(*++argv);
    }
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
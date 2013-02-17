#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Amano /SECTION:.Amano,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Amano")
#pragma comment(linker,"/MERGE:.data=.Amano")

#include "MagusTale.h"
#include "Mem.cpp"

INIT_CONSOLE_HANDLER

ForceInline Void main2(Int argc, WChar **argv)
{
    if (argc == 1)
        return;

    CYuris mt;
    while (--argc)
        mt.Auto(*++argv);
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
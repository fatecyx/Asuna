#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.CRT=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "Sharu.h"
#include "Mem.cpp"
#include "my_api.cpp"
#include "my_crtadd.cpp"

INIT_CONSOLE_HANDLER

ForceInline Void main2(Int argc, WChar **argv)
{
    if (argc == 1)
        return;

    CSharu sharu;

    while (--argc)
        sharu.Auto(*++argv);
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
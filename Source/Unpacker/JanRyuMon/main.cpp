#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "JanRyuMon.h"
#include "Mem.cpp"

INIT_CONSOLE_HANDLER

ForceInline Void main2(Int argc, WChar **argv)
{
    CJanryumon jrm;

    while (--argc)
        jrm.Auto(*++argv);
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
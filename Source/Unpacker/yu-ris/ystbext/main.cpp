#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "ystb.h"
#include "Mem.cpp"
#include "my_crtadd.cpp"

extern bool mask[0xFF];

ForceInline Void main2(Int argc, WChar **argv)
{
    CYurisScriptParser ysp;

    for (Int i = 1; i != argc; ++i)
    {
        wprintf(L"Processing \"%s\" ... ", *++argv);
        wprintf(L"%s\n", ysp.Auto(*argv) ? L"OK" : L"failed");
    }
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
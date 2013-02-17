#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")

#include "MyLibrary.cpp"
#include "thcm.h"

ForceInline Void main2(Long_Ptr argc, WChar **argv)
{
    if (argc < 2)
        return;

    THCMPak pak;

    while (--argc)
    {
        pak.Auto(*++argv);
    }
}

int __cdecl main(Long_Ptr argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    ReleaseArgv(argv);
    Nt_ExitProcess(0);
}

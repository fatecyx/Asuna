#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "nitroplus.h"
#include "MyLibraryUser.cpp"

ForceInline Void main2(Int argc, WChar **argv)
{
    if (argc == 1)
        return;

    NitroPlus np;
    while (--argc)
        np.Auto(*++argv);
}

int __cdecl main(int argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    return Nt_ExitProcess(0);
}
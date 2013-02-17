#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"
#include "mscdecl.h"

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    printf("code = %X\n"
        "addr = %p\n",
        ExceptionInfo->ExceptionRecord->ExceptionCode,
        ExceptionInfo->ExceptionRecord->ExceptionAddress);

    return EXCEPTION_CONTINUE_SEARCH;
}

ForceInline Void main2(Int argc, WChar **argv)
{
    CMscDecl md;

    AddVectoredExceptionHandler(True, VectoredHandler);
    for (int i = 1; i != argc ; i++)
    {
        wprintf(L"Peeking \"%s\" ... ", *++argv);
        printf("%s\n", md.PeekText(*argv) ? "OK" : "failed");
    }
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
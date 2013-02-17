#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "ntdll.lib")

#include "BGIScript2Lua.h"
#include "my_commsrc.h"

LONG STDCALL ProcessScript(PVOID, LPWIN32_FIND_DATAW pFindData, CBGIScript2Lua *bgi)
{
    ULONG ErrorCode;
    MESSAGE_RESOURCE_ENTRY *mre;

    PrintConsoleW(L"%s ... ", pFindData->cFileName);
    ErrorCode = bgi->ConvertScript(pFindData->cFileName);

    if (GetErrorMessage(NULL, HRESULT_CODE(ErrorCode), &mre))
    {
        PrintConsoleW((mre->Flags & 1) ? L"%s\n" : L"%S\n", mre->Text);
    }
    else
    {
        PrintConsoleW(L"failed\n");
    }

    return 0;
}

ForceInline Void main2(Int argc, WChar **argv)
{
    if (argc == 1)
        return;

    setlocale(LC_ALL, ".936");

    CBGIScript2Lua bgi;

    while (--argc)
    {
        EnumDirectoryFiles(
            NULL,
            L"*.*",
            0,
            *++argv,
            NULL,
            (FEnumDirectoryFilesCallBack)ProcessScript,
            (ULONG_PTR)&bgi,
            0
        );
    }
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
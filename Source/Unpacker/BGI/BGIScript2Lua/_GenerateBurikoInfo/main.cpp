#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "my_commsrc.h"

#pragma pack(1)

typedef struct
{
    BOOL    bValid;
    ULONG   ParamCount;
} BURIKO_SCRIPT_PARAM_INFO;

#pragma pack()

LONG STDCALL Callback(PVOID /* pvBuffer */, LPWIN32_FIND_DATAW pFindData, BURIKO_SCRIPT_PARAM_INFO *info)
{
    FILE *faiy;
    BURIKO_SCRIPT_PARAM_INFO *pInfo, Buffer[0x400];

    faiy = _wfopen(pFindData->cFileName, L"rb+");
    if (faiy == NULL)
        return 0;

    fread(Buffer, sizeof(Buffer), 1, faiy);
    fclose(faiy);

    pInfo = Buffer;
    for (ULONG Index = 0, Count = countof(Buffer); Count; ++pInfo, ++Index, --Count)
    {
        if (!pInfo->bValid || info[Index].bValid)
            continue;

        info[Index] = *pInfo;
    }

    return 0;
}

ForceInline Void main2(Int argc, WChar **argv)
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    FILE *fp = _wfopen(L"buriko_info.h", L"wb+");
    BURIKO_SCRIPT_PARAM_INFO info[0x400];

    if (fp == NULL)
        return;

    ZeroMemory(info, sizeof(info));

    EnumDirectoryFiles(
        NULL,
        L"*.aiy",
        0,
        NULL,
        NULL,
        (FEnumDirectoryFilesCallBack)Callback,
        (ULONG_PTR)info,
        0
    );

    BURIKO_SCRIPT_PARAM_INFO *pInfo;

    pInfo = info;
    for (ULONG Index = 0, Count = countof(info); Count; ++pInfo, ++Index, --Count)
    {
        ULONG n;

        if (!pInfo->bValid)
            continue;

        fprintf(fp, "%s0x%04X", "DECL_LENGTH(", Index);

        n = pInfo->ParamCount;
        if (n != 0)
        {
            do
            {
                fprintf(fp, ", 4");
            } while (--n);
        }
        else
        {
            //            fprintf(fp, ", 0");
        }

        fprintf(fp, ");\r\n");
    }

    fclose(fp);
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
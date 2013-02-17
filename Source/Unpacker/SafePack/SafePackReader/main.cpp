#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "SafePackReader.h"
#include "my_commsrc.h"

ForceInline Void main2(Int argc, WChar **argv)
{
    PVOID buf;
    NTSTATUS Status;
    CSafePackReader spr;
    SAFE_PACK_FILE_INFO FileInfo;

    Status = spr.Open(L"..\\Release.pack");
    if (!NT_SUCCESS(Status))
        return;

    Status = spr.GetFileInfo("aes_x86_v2.obj", &FileInfo);
    if (!NT_SUCCESS(Status))
        return;

    buf = AllocateMemory(FileInfo.Size);
    spr.Read(&FileInfo, buf, FileInfo.Size);
}

int __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    return Nt_ExitProcess(0);
}
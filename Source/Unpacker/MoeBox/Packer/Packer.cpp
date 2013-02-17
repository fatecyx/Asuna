#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "MyLibraryUser.h"
#include "MyLibraryUser.cpp"
#include "SafePacker.h"
#include "cxdec.cpp"

class SafePacker : public SafePackerImpl<SafePacker>
{
public:
    UPK_STATUS
    SetEntryContext2(
        SAFE_PACK_ENTRY *Entry,
        SAFE_PACK_ENTRY *EntryBase,
        SAFE_PACK_LIST  *FileList,
        SAFE_PACK_LIST  *FileListBase,
        ULONG            Flags
    )
    {
        UNREFERENCED_PARAMETER(EntryBase);
        UNREFERENCED_PARAMETER(FileList);
        UNREFERENCED_PARAMETER(FileListBase);
        UNREFERENCED_PARAMETER(Flags);

        Entry->EntrySize = sizeof(*Entry) - sizeof(Entry->Buffer) - sizeof(Entry->FileName);
//        Entry->EntrySize = ROUND_UP(Entry->EntrySize, 16);

        return STATUS_SUCCESS;
    }
};

ForceInline Void main2(Int argc, WChar **argv)
{
    if (--argc == 0)
        return;

    SafePacker d;

    do
    {
        d.Auto(*++argv);
    } while (--argc);
}

int __cdecl main(int argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    ReleaseArgv(argv);
    return Nt_ExitProcess(0);
}

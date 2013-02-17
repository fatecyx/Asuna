#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "MyLibrary.cpp"
#include "cxdec.cpp"
#include "key.h"

typedef struct
{
    ULONG Offset;
    ULONG Length;
    CHAR  String[1];

} *PTEXT_NODE;

typedef struct
{
    PTEXT_NODE  Text;
    ULONG       Hash[8];
    ULONG       Index[4];
    ULONG       Reserve[3];

} TEXT_HASH, *PTEXT_HASH;

extern ULONG cxdec_key[0x400];

typedef int (__cdecl *QSORT_COMPARE_ROUTINE)(const void *,const void *);

INT CDECL SortEntry(PTEXT_HASH t1, PTEXT_HASH t2)
{
    ULONG  Count;
    PULONG Hash1, Hash2;

    Hash1 = t1->Index;
    Hash2 = t2->Index;
    Count = countof(t1->Index);

    do
    {
        if (*Hash1 < *Hash2)
            return -1;
        else if (*Hash1 > *Hash2)
            return 1;

        ++Hash1;
        ++Hash2;

    } while (--Count);

    return 0;
}

NTSTATUS EncryptPsbin(PWSTR psbin)
{
    ULONG       Crc, Count, Size;
    PVOID       TextBuffer, EncryptedBase;
    PBYTE       Buffer, Encryped;;
    NTSTATUS    Status;
    NtFileDisk  file;
    PTEXT_HASH  TextHash, TextHashBase;

    Status = file.Open(psbin);
    FAIL_RETURN(Status);

    file.Read(&Count, sizeof(Count));
    file.Read(&Crc, sizeof(Crc));

    Size = file.GetSize32() - sizeof(Count);
    TextBuffer = AllocateMemory(Size);
    if (TextBuffer == NULL)
        return STATUS_NO_MEMORY;

    EncryptedBase = AllocateMemory(Size + Count * 0x40);
    if (EncryptedBase == NULL)
        return STATUS_NO_MEMORY;

    TextHashBase = (PTEXT_HASH)AllocateMemory(Count * sizeof(*TextHashBase));
    if (TextHashBase == NULL)
        return STATUS_NO_MEMORY;

    file.Read(TextBuffer, Size);
    file.Close();

    Buffer      = (PBYTE)TextBuffer;
    Encryped    = (PBYTE)EncryptedBase;
    TextHash    = TextHashBase;

    for (ULONG n = Count; n; --n)
    {
        PTEXT_NODE Text = (PTEXT_NODE)Buffer;

        TextHash->Text = Text;
        sha256(&Text->Offset, sizeof(Text->Offset), TextHash->Hash);

        TextHash->Index[0] = TextHash->Hash[0] ^ TextHash->Hash[4];
        TextHash->Index[1] = TextHash->Hash[1] ^ TextHash->Hash[5];
        TextHash->Index[2] = TextHash->Hash[2] ^ TextHash->Hash[6];
        TextHash->Index[3] = TextHash->Hash[3] ^ TextHash->Hash[7];

        Buffer += Text->Length + 8;
        ++TextHash;
    }

    qsort(TextHashBase, Count, sizeof(*TextHashBase), (QSORT_COMPARE_ROUTINE)SortEntry);

    CXDEC_OPTION Option;
    Cxdec cxdec;

    ULONG Body1[6] = { 2, 3, 1, 4, 5, 0 };
    ULONG Body2[8] = { 5, 6, 7, 1, 2, 3, 0, 4 };
    ULONG Tail[3]  = { 1, 0, 2 };

    Option.DecryptBlock     = irotori_key;
    Option.Body1IndexMap    = Body1;
    Option.Body2IndexMap    = Body2;
    Option.TailIndexMap     = Tail;
    Option.Const[0]         = TAG4('Rias');
    Option.Const[1]         = TAG4('Grmy');
    Option.FunctionCount    = 0x110;
    Option.FunctionSize     = 0x110;
    Option.LoopCount        = 6;

    cxdec.SetOption(&Option);
    cxdec.Initialize();

    TextHash = TextHashBase;
    for (ULONG n = Count; n; --n)
    {
        ULONG Length;

        //CopyStruct(Encryped, TextHash->Index, sizeof(TextHash->Index));
        //Encryped += sizeof(TextHash->Index);

        *(PULONG)Encryped = TextHash->Text->Offset | 0x80000000;
        Encryped += sizeof(ULONG);

        Length = TextHash->Text->Length;

        *(PULONG)Encryped = Length; // ^ TextHash->Index[0] ^ TextHash->Index[1] ^ TextHash->Index[2] ^ TextHash->Index[3];
        Encryped += sizeof(ULONG);

        Length = ROUND_UP(Length, 4);

        CopyMemory(Encryped, TextHash->Text->String, Length);
        //cxdec.Encrypt2(0, Encryped, Length, &TextHash->Hash[4]);
        Encryped += Length;

        ++TextHash;
    }

    WCHAR FileName[MAX_NTPATH];

    StrCopyW(FileName, psbin);
    StrCopyW(findnamew(FileName), L"mirai.bin");

    file.Create(FileName, 0, FILE_SHARE_READ, GENERIC_READ | GENERIC_WRITE, FILE_OPEN_IF);
    file.Seek(0, FILE_END);

    file.Write(&Count, sizeof(Count));
    file.Write(&Crc, sizeof(Crc));
    file.Write(EncryptedBase, PtrOffset(Encryped, EncryptedBase));

    FreeMemory(EncryptedBase);
    FreeMemory(TextBuffer);
    FreeMemory(TextHashBase);

    return STATUS_SUCCESS;
}

ForceInline NTSTATUS main2(Int argc, WChar **argv)
{
    if (--argc == 0)
        return -1;

    ++argv;

    if (!StrICompareW(*argv, L"-compress"))
    {
        if (--argc == 0)
            return 0;

        ++argv;

        NTSTATUS Status;
        NtFileMemory f;
        PVOID buf;
        ULONG_PTR len;

        Status = f.Open(*argv);
        FAIL_RETURN(Status);

        len = f.GetSize32() * 2;
        buf = AllocateMemory(len + 8);
        if (buf == NULL)
            return 0;

        Status = UCL_NRV2E_Compress(f.GetBuffer(), f.GetSize32(), PtrAdd(buf, 8), &len);
        if (!Status)
            return 0;

        *(PULONG)buf = len;
        ((PLARGE_INTEGER)buf)->HighPart = f.GetSize32();

        f.Close();

        NtFileDisk fd;

        Status = fd.Create(*argv);
        FAIL_RETURN(Status);

        fd.Write(buf, len + 8);

        return 0;
    }

    do
    {
        EncryptPsbin(*argv++);

    } while (--argc);

    return 0;
}

int __cdecl main(LongPtr argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    ReleaseArgv(argv);
    return Nt_ExitProcess(0);
}
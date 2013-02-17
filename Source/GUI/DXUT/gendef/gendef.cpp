#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "MyLibrary.cpp"

ForceInline Void main2(Int argc, WChar **argv)
{
    if (--argc == 0)
        return;

    NtFileDisk              File;
    ULONG                   Length;
    PVOID                   PeBuffer;
    PCHAR                   DefBuffer, Buffer;
    ULONG                   Size;
    NTSTATUS                Status;
    PIMAGE_DOS_HEADER       DosHeader;
    PIMAGE_NT_HEADERS       NtHeaders;
    PIMAGE_EXPORT_DIRECTORY ExportDirectory;
    ULONG_PTR               NumberOfNames;
    PCSTR                  *AddressOfNames;

    RtlWow64EnableFsRedirection(FALSE);

    Status = ReLoadDll(argv[1], &PeBuffer, NULL, RELOAD_DLL_IGNORE_IAT);
    if (!NT_SUCCESS(Status))
        return;

    SCOPE_EXIT
    {
        UnLoadDll(PeBuffer);
    }
    SCOPE_EXIT_END;

    DosHeader = (PIMAGE_DOS_HEADER)PeBuffer;
    NtHeaders = (PIMAGE_NT_HEADERS)PtrAdd(DosHeader, DosHeader->e_lfanew);
    Size = NtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
    if (Size == 0)
        return;

    DefBuffer = (PCHAR)AllocateMemory(Size * 0x10);
    if (DefBuffer == NULL)
        return;

    ExportDirectory = NULL;
    ExportDirectory = PtrAdd(ExportDirectory, PeBuffer);
    ExportDirectory = PtrAdd(ExportDirectory, NtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

    Buffer = DefBuffer;

    WCHAR FileName[MAX_NTPATH];

    StrCopyW(FileName, argv[1]);

    NumberOfNames   = ExportDirectory->NumberOfNames;
    AddressOfNames  = PtrAdd((PCSTR *)PeBuffer, ExportDirectory->AddressOfNames);

#define GEN_DEF 1

#if GEN_DEF

    ULONG Seed = (ULONG)ReadTimeStampCounter();
    pbool mask = (pbool)AllocateMemory(NumberOfNames, HEAP_ZERO_MEMORY);

    chextw(FileName, L".def");

    Length = sprintf(Buffer, "EXPORTS\n");
    Buffer += Length;

#else

    chextw(FileName, L"FunctionHash.h");

    PWSTR dllname;

    dllname = findnamew(argv[1]);
    rmextw(dllname);
    StringUpperW(dllname);

#endif

    do
    {
#if GEN_DEF

        ULONG Ordinal;

        do
        {
            Ordinal = RtlRandom(&Seed) % ExportDirectory->NumberOfNames;

        } while (mask[Ordinal]);

        mask[Ordinal] = true;

        //Buffer += sprintf(Buffer, "    %s @%d NONAME\n", PtrAdd(*AddressOfNames, PeBuffer), Ordinal + 1);
        Buffer += sprintf(Buffer, "    %s = winsta_shadow.%s\n", PtrAdd(*AddressOfNames, PeBuffer), PtrAdd(*AddressOfNames, PeBuffer));
        // Buffer += sprintf(Buffer, "    VOID %s() {}\n", PtrAdd(*AddressOfNames, PeBuffer), PtrAdd(*AddressOfNames, PeBuffer));

#else

        ULONG len;
        PCSTR FunctionName = PtrAdd(*AddressOfNames, PeBuffer);

        len = sprintf(Buffer, "#define %S_%s", dllname, FunctionName);
        Buffer += len;
        for (len = 76 - len; len; --len)
            Buffer += sprintf(Buffer, " ");

        Buffer += sprintf(Buffer, " 0x%08Xu\n", HashAPI(FunctionName));

#endif

        ++AddressOfNames;

    } while (--NumberOfNames);

    Status = File.Create(FileName);
    if (NT_SUCCESS(Status))
        File.Write(DefBuffer, PtrOffset(Buffer, DefBuffer));

#if GEN_DEF
    FreeMemory(mask);
#endif

    FreeMemory(DefBuffer);
}

int __cdecl main(LongPtr argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    ReleaseArgv(argv);
    return Nt_ExitProcess(0);
}
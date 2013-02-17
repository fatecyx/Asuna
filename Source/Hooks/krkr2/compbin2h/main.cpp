#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "MyLibraryUser.h"
#include "MyLibraryUser.cpp"

ForceInline Void main2(Int argc, WChar **argv)
{
    if (--argc == 0)
        return;

    PVOID           Buffer, Compressed;
    ULONG           Length, Size, CompressedSize, BufferSize, CompressBufferSize;
    NtFileDisk      File;
    NTSTATUS        Status;
    WCHAR           *Name, *Extension, FileName[MAX_NTPATH];
    MemoryAllocator Memory;

    Buffer              = NULL;
    BufferSize          = 0;
    Compressed          = NULL;
    CompressBufferSize  = 0;

    do
    {
        Status = File.Open(*++argv);
        if (!NT_SUCCESS(Status))
            continue;

        Size = File.GetSize32();
        if (Size > BufferSize)
        {
            BufferSize = Size;
            Buffer = Memory.ReAlloc(Buffer, BufferSize);
            if (Buffer == NULL)
                continue;
        }

        Status = File.Read(Buffer, Size);
        if (!NT_SUCCESS(Status))
            continue;

        if (Size * 2 > CompressBufferSize)
        {
            CompressBufferSize = Size * 2;
            Compressed = Memory.ReAlloc(Compressed, CompressBufferSize);
            if (Compressed == NULL)
                continue;
        }

        CompressedSize = CompressBufferSize;
        Status = UCL_NRV2E_Compress(Buffer, Size, Compressed, &CompressedSize);
        if (!Status)
            continue;

        if (BufferSize < CompressedSize * 10)
        {
            BufferSize = CompressedSize * 10;
            Buffer = Memory.ReAlloc(Buffer, BufferSize);
            if (Buffer == NULL)
                continue;
        }

        StrCopyW(FileName, *argv);
        Name = findnamew(FileName);

        Extension = findextw(Name);
        *(PULONG64)Extension = TAG2W('.h');
        Status = File.Create(FileName);
        if (!NT_SUCCESS(Status))
            continue;

        Length = sprintf(
                    (PSTR)Buffer,
                    "BYTE %.*S[] = \n"
                    "{\n"
                    "    ",
                    Extension - Name,
                    Name
                );

        Length += sprintf(
                    (PSTR)Buffer + Length,
                    "0x%02X, 0x%02X, 0x%02X, 0x%02X, \n    ",
                    LOBYTE(Size),
                    HIBYTE(Size),
                    LOBYTE(HIWORD(Size)),
                    HIBYTE(HIWORD(Size))
                  );

        for (ULONG Index = 0, Count = CompressedSize; Count; --Count)
        {
            Length += sprintf((PSTR)Buffer + Length, "0x%02X, ", ((PBYTE)Compressed)[Index++]);
            if ((Index % 16) == 0)
                Length += sprintf((PSTR)Buffer + Length, "\n    ");
        }

        Length += sprintf((PSTR)Buffer + Length, "\n};\n");

        File.Write(Buffer, Length);

    } while (--argc);

    Memory.Free(Buffer);
    Memory.Free(Compressed);
}

int __cdecl main(int argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    ReleaseArgv(argv);
    return Nt_ExitProcess(0);
}
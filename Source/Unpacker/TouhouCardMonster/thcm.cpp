#include "thcm.h"
#include "MTwister.h"
#include "ZLibExport.h"

ULONG ComputeCrc(PVOID Buffer, ULONG_PTR Size, ULONG PartialCrc = -1)
{
    static const ULONG CrcTable[] =
    {
        0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005, 0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61, 0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
        0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75, 0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd,
        0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039, 0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5, 0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
        0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95, 0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1, 0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d,
        0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072, 0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca,
        0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde, 0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02, 0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
        0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692, 0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6, 0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a,
        0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2, 0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a,
        0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637, 0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb, 0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
        0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b, 0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff, 0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
        0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b, 0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3,
        0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7, 0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b, 0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
        0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c, 0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8, 0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24,
        0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec, 0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654,
        0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0, 0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c, 0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
        0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c, 0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668, 0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
    };

    PBYTE Buf = (PBYTE)Buffer;

    for (; Size; --Size)
    {
        PartialCrc = (PartialCrc << 0x08) ^ CrcTable[(PartialCrc >> 0x18) ^ *Buf++];
    }

    return ~PartialCrc;
}

UPK_STATUS THCMPak::Open(PCWSTR FileName)
{
    NTSTATUS        Status;
    THCM_PAK_HEADER Header;
    PVOID           Index;

    Status = Pak.Open(FileName);
    FAIL_RETURN(Status);

    Status = Pak.Read(&Header, sizeof(Header));
    FAIL_RETURN(Status);

    Index = AllocateMemory(Header.IndexSize);
    if (Index == NULL)
        return STATUS_NO_MEMORY;

    Header.IndexSize -= sizeof(Header.IndexSize);

    Status = Pak.Read(Index, Header.IndexSize);
    if (NT_FAILED(Status))
    {
        FreeMemory(Index);
        return Status;
    }

    Status = InitIndex(Index, Header.IndexSize);

    FreeMemory(Index);

    return Status;
}

UPK_STATUS THCMPak::InitIndex(PVOID IndexBuffer, ULONG_PTR Size)
{
    ULONG_PTR                           Overhead;
    PBYTE                               Index;
    PTHCM_PAK_INDEX_ENTRY               PakEntry, PakEntryEnd;
    PTHCM_PAK_INDEX_HEADER              IndexHeader;
    THCM_PAK_ENTRY                      Entry;
    ml::GrowableArray<THCM_PAK_ENTRY>   Entries;

    m_Index.EntrySize = sizeof(Entry);

    Index       = (PBYTE)IndexBuffer;
    IndexHeader = (PTHCM_PAK_INDEX_HEADER)Index;
    PakEntry    = IndexHeader->Entry;
    PakEntryEnd = (PTHCM_PAK_INDEX_ENTRY)PtrAdd(IndexBuffer, Size);
    Overhead    = Size + FIELD_SIZE(THCM_PAK_HEADER, IndexSize);

    DecryptIndex(Index, Size, Overhead);

    if (ComputeCrc(PakEntry, Size - sizeof(IndexHeader->IndexCrc)) != IndexHeader->IndexCrc)
    {
        return STATUS_CRC_ERROR;
    }

    m_Index.FileCount.QuadPart = 0;


    while (PakEntry < PakEntryEnd)
    {
        WCHAR FileName[MAX_NTPATH];

        ZeroMemory(&Entry, sizeof(Entry));

        MultiByteToWideChar(CP_SHIFTJIS, 0, PakEntry->FileName, -1, FileName, countof(FileName));
        Entry.SetFileName(FileName);

        PakEntry = PakEntry->GetData();

        Entry.DecryptKey                = PakEntry->DecryptKey;
        Entry.CompressedSize.QuadPart   = PakEntry->CompressedSize;
        Entry.Size.QuadPart             = PakEntry->UncompressedSize;
        Entry.Offset.QuadPart           = PakEntry->Offset + Overhead;
        Entry.Uncompressed              = PakEntry->Uncompressed;

        Entries.Add(Entry);

        PakEntry = PakEntry->Next();
    }

    if (Entries.GetSize() == 0)
        return STATUS_NO_MORE_ENTRIES;

    m_Index.Entry = AllocateEntry(Entries.GetSize());
    if (m_Index.Entry == NULL)
    {
        PTHCM_PAK_ENTRY Entry;
        FOR_EACH_VEC(Entry, Entries)
        {
            RtlFreeUnicodeString(&Entry->FileName);
        }

        return STATUS_NO_MEMORY;
    }

    CopyMemory(m_Index.Entry, Entries.GetData(), Entries.GetSize() * sizeof(Entry));
    m_Index.FileCount.QuadPart = Entries.GetSize();

    return STATUS_SUCCESS;
}

VOID THCMPak::DecryptIndex(PVOID Buffer, ULONG_PTR Size, ULONG Key)
{
    PBYTE buf;
    CMTwister mt;

    buf = (PBYTE)Buffer;

    mt.SetSeed2(Key);

    for (; Size; --Size)
    {
        LARGE_INTEGER random = mt.GetRandom64();
        *buf = *buf ^ random.LowPart ^ random.HighPart;
        ++buf;
    }
}

UPK_STATUS THCMPak::GetFileData(PUNPACKER_FILE_INFO FileInfo, PUNPACKER_FILE_ENTRY_BASE BaseEntry, ULONG Flags /* = 0 */)
{
    PVOID           Buffer;
    ULONG_PTR       Size;
    NTSTATUS        Status;
    PTHCM_PAK_ENTRY Entry;

    Entry = (PTHCM_PAK_ENTRY)BaseEntry;

    Size = Entry->CompressedSize.QuadPart;
    Buffer = AllocateMemory(ROUND_UP(Size, 4));
    if (Buffer == NULL)
        return STATUS_NO_MEMORY;

    SCOPE_EXIT
    {
        FreeMemory(Buffer);
    }
    SCOPE_EXIT_END;

    Status = Pak.Read(Buffer, Size);
    FAIL_RETURN(Status);

    DecryptFileAlign4(Buffer, Size, Entry);

    Status = AllocateFileData(FileInfo, Entry->Size.QuadPart, UnpackerFileBinary);
    FAIL_RETURN(Status);

    if (Entry->Uncompressed)
    {
        CopyMemory(FileInfo->BinaryData.Buffer, Buffer, Size);
    }
    else
    {
        FileInfo->BinaryData.Size.QuadPart = Entry->Size.QuadPart;
        Status = uncompress(FileInfo->BinaryData.Buffer, &FileInfo->BinaryData.Size.LowPart, Buffer, Size);
        Status = Status == Z_OK ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
    }

    return Status;
}

VOID THCMPak::DecryptFileAlign4(PVOID Buffer, ULONG_PTR Size, PTHCM_PAK_ENTRY Entry)
{
    PULONG      Buf, Key;
    ULONG       DecTable[0x10];
    CMTwister   mt;

    mt.SetSeed2(Entry->DecryptKey);

    FOR_EACH(Key, DecTable, countof(DecTable))
    {
        LARGE_INTEGER random = mt.GetRandom64();
        *Key = random.LowPart ^ random.HighPart;
    }

    Buf = (PULONG)Buffer;
    Size = ROUND_UP(Size, 4);
    for (ULONG_PTR Index = 0, Count = Size / sizeof(DecTable[0]); Count; --Count)
    {
        *Buf++ ^= DecTable[Index++];
        Index %= countof(DecTable);
    }
}

UPK_STATUS THCMPak::Pack(PCWSTR InputPath, PCWSTR OutputFile /* = NULL */, PLARGE_INTEGER PackedFiles /* = NULL */, ULONG Flags /* = 0 */)
{
    LONG                                ZStatus;
    ULONG                               CompressedSize;
    ULONG_PTR                           Length, IndexSize, Size, BufferSize, CompressBufferSize;
    LARGE_INTEGER                       Offset;
    WCHAR                               Output[MAX_NTPATH];
    PVOID                               Buffer, CompressBuffer;
    NTSTATUS                            Status;
    PTHCM_PAK_ENTRY                     Entry;
    THCM_PAK_HEADER                     Header;
    ml::GrowableArray<THCM_PAK_ENTRY>   Entries;

    Length = StrLengthW(InputPath);

    if (OutputFile != NULL)
    {
        StrCopyW(Output, OutputFile);
    }
    else
    {
        Length -= InputPath[Length - 1] == '\\';
        swprintf(Output, L"%.*s.pak", Length, InputPath);
    }

    Status = BuildEntry(InputPath, Entries);
    FAIL_RETURN(Status);

    Status = Pak.Create(Output);
    FAIL_RETURN(Status);

    if (Entries.GetSize() == 0)
        return STATUS_NO_MORE_FILES;

    Length += InputPath[Length - 1] != '\\';

    IndexSize = ComputePakEntrySize(Entries, Length);

    Status = Pak.Seek(IndexSize + sizeof(Header), FILE_BEGIN);
    FAIL_RETURN(Status);

    BufferSize = 0;
    CompressBufferSize = BufferSize;

    Buffer = NULL;
    CompressBuffer = NULL;

    Offset.QuadPart = 0;

    NtFileDisk File;

    FOR_EACH_VEC(Entry, Entries)
    {
        Entry->Offset = Offset;

        Status = File.Open(Entry->GetFileName());
        FAIL_CONTINUE(Status);

        Size = File.GetSize32();
        if (Size > BufferSize)
        {
            BufferSize = Size;
            Buffer = ReAllocateMemory(Buffer, Size);
            if (Buffer == NULL)
            {
                Status = STATUS_NO_MEMORY;
                break;
            }
        }

        Status = File.Read(Buffer, Size);
        FAIL_CONTINUE(Status);

        if (ROUND_UP(Size * 2, 4) > CompressBufferSize)
        {
            CompressBufferSize = ROUND_UP(Size * 2, 4);
            CompressBuffer = ReAllocateMemory(CompressBuffer, CompressBufferSize);
            if (CompressBuffer == NULL)
            {
                Status = STATUS_NO_MEMORY;
                break;
            }
        }

        Entry->CompressedSize.QuadPart = CompressBufferSize;
        ZStatus = compress2(CompressBuffer, &Entry->CompressedSize.LowPart, Buffer, Size, Z_BEST_COMPRESSION);
        if (ZStatus != Z_OK)
        {
            Entry->CompressedSize.QuadPart = 0;
            continue;
        }

        Entry->DecryptKey = ComputeCrc(CompressBuffer, Entry->CompressedSize.LowPart);
        EncryptFileAlign4(CompressBuffer, Entry->CompressedSize.LowPart, Entry);

        Status = Pak.Write(CompressBuffer, Entry->CompressedSize.LowPart);
        if (NT_FAILED(Status))
        {
            Entry->CompressedSize.QuadPart = 0;
            continue;
        }

        Entry->Size.QuadPart = Size;
        Entry->CompressedSize.HighPart = 0;
        Offset.QuadPart += Entry->CompressedSize.QuadPart;
    }

    if (Buffer != NULL && NT_SUCCESS(Status)) LOOP_ONCE
    {
        if (BufferSize < IndexSize)
        {
            BufferSize = IndexSize;
            Buffer = ReAllocateMemory(Buffer, BufferSize);
            if (CompressBuffer == NULL)
            {
                Status = STATUS_NO_MEMORY;
                break;
            }
        }

        Pak.Rewind();

        Header.IndexSize = IndexSize + sizeof(Header.IndexSize);
        Status = Pak.Write(&Header, sizeof(Header));
        FAIL_BREAK(Status);

        Status = BuildPakEntry(Buffer, Entries, Length);
        FAIL_BREAK(Status);

        if (PackedFiles != NULL)
            PackedFiles->QuadPart = Entries.GetSize();
    }

    FreeMemory(Buffer);
    FreeMemory(CompressBuffer);

    return Status;
}

UPK_STATUS THCMPak::BuildEntry(PCWSTR InputPath, ml::GrowableArray<THCM_PAK_ENTRY> &Entries)
{
    if (!EnumDirectoryFiles(NULL, L"*.*", 0, InputPath, NULL,
            [] (PVOID, PWIN32_FIND_DATAW FindData, ULONG_PTR Entries) -> LONG_PTR
            {
                THCM_PAK_ENTRY Entry;

                ZeroMemory(&Entry, sizeof(Entry));

                Entry.SetFileName(FindData->cFileName);
                // Entry.Size.LowPart = FindData->nFileSizeLow;
                // Entry.Size.HighPart = FindData->nFileSizeHigh;

                ((ml::GrowableArray<THCM_PAK_ENTRY> *)Entries)->Add(Entry);

                return 0;
            },
            (ULONG_PTR)&Entries,
            EDF_SUBDIR
        ))
    {
        return STATUS_UNSUCCESSFUL;
    }

    return STATUS_SUCCESS;
}

ULONG_PTR THCMPak::ComputePakEntrySize(ml::GrowableArray<THCM_PAK_ENTRY> &Entries, ULONG_PTR PathLength)
{
    ULONG_PTR Size = 0;
    PTHCM_PAK_ENTRY Entry;

    FOR_EACH_VEC(Entry, Entries)
    {
        Size += sizeof(THCM_PAK_INDEX_ENTRY) - FIELD_SIZE(THCM_PAK_INDEX_ENTRY, FileName);
        Size += WideCharToMultiByte(
                    CP_SHIFTJIS,
                    0,
                    Entry->GetFileName() + PathLength,
                    Entry->GetFileNameLength() - PathLength,
                    NULL,
                    0,
                    NULL,
                    NULL
                );

        Size += 1;
    }

    return Size + FIELD_SIZE(THCM_PAK_INDEX_HEADER, IndexCrc);
}

UPK_STATUS THCMPak::BuildPakEntry(PVOID Buffer, ml::GrowableArray<THCM_PAK_ENTRY> &Entries, ULONG_PTR PathLength)
{
    PBYTE                   Buf;
    ULONG_PTR               Length;
    PTHCM_PAK_ENTRY         Entry;
    PTHCM_PAK_INDEX_ENTRY   PakEntry;
    PTHCM_PAK_INDEX_HEADER  IndexHeader;
    NTSTATUS                Status;

    IndexHeader = (PTHCM_PAK_INDEX_HEADER)Buffer;
    Buf         = (PBYTE)IndexHeader->Entry;

    FOR_EACH_VEC(Entry, Entries)
    {
        Length = WideCharToMultiByte(
                    CP_SHIFTJIS,
                    0,
                    Entry->GetFileName() + PathLength,
                    Entry->GetFileNameLength() - PathLength,
                    (PSTR)Buf,
                    0xFFFFFF,
                    NULL,
                    NULL
                );

        Buf[Length] = 0;
        PakEntry = (PTHCM_PAK_INDEX_ENTRY)(Buf + Length);

        PakEntry->DecryptKey            = Entry->DecryptKey;
        PakEntry->CompressedSize        = Entry->CompressedSize.LowPart;
        PakEntry->UncompressedSize      = Entry->Size.LowPart;
        PakEntry->Offset                = Entry->Offset.QuadPart;
        PakEntry->Uncompressed          = Entry->Uncompressed;

        Buf = (PBYTE)PakEntry->Next();
    }

    Length = PtrOffset(Buf, IndexHeader->Entry);
    IndexHeader->IndexCrc = ComputeCrc(IndexHeader->Entry, Length);

    Length += sizeof(IndexHeader->IndexCrc);

    EncryptIndex(Buffer, Length, Length + FIELD_SIZE(THCM_PAK_HEADER, IndexSize));

    return Pak.Write(Buffer, Length);
}

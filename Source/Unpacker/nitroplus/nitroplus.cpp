#pragma comment(lib, "zlib1.lib")

#include "nitroplus.h"
#include "ZLibExport.h"

NitroPlus::NitroPlus()
{
    *(PULONG)m_EncryptTable = 0;
}

UPK_STATUS
NitroPlus::Open(
    PCWSTR FileName
)
{
    PVOID                   EntryBuffer;
    LARGE_INTEGER           BytesRead;
    NTSTATUS                Status;
    NITRO_PLUS_NPA_HEADER   Header;

    Status = m_File.Open(FileName);
    FAIL_RETURN(Status);

    Status = m_File.Read(&Header, sizeof(Header), &BytesRead);
    FAIL_RETURN(Status);

    if (
        BytesRead.LowPart != sizeof(Header) ||
        (*(PULONG)Header.Signature & 0x00FFFFFF) != NPA_HEADER_MAGIC
       )
    {
        return STATUS_UNSUCCESSFUL;
    }

    switch (Header.Version)
    {
        case NPA_GCLX_VERSION:
            break;

        default:
            return STATUS_UNSUCCESSFUL;
    }

    EntryBuffer = AllocateMemory(Header.EntrySize);
    if (EntryBuffer == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    Status = m_File.Read(EntryBuffer, Header.EntrySize, &BytesRead);
    FAIL_RETURN(Status);

    if (BytesRead.LowPart != Header.EntrySize)
        return STATUS_UNSUCCESSFUL;

    Status = InitIndex(EntryBuffer, &Header);

    FreeMemory(EntryBuffer);

    return Status;
}

UPK_STATUS
NitroPlus::
GetFileData(
    UNPACKER_FILE_INFO         *FileInfo,
    UNPACKER_FILE_ENTRY_BASE   *BaseEntry,
    ULONG                       Flags /* = 0 */
)
{
    PBYTE               Buffer;
    ULONG               Size;
    NTSTATUS            Status;
    NITRO_PLUS_ENTRY   *Entry;

    Entry = (NITRO_PLUS_ENTRY *)BaseEntry;

    if (FLAG_ON(Entry->Attributes, FILE_ATTRIBUTE_DIRECTORY))
        return STATUS_UNSUCCESSFUL;

    Status = m_File.Seek(Entry->Offset, FILE_BEGIN);
    FAIL_RETURN(Status);

    Size   = Entry->CompressedSize.LowPart;
    Buffer = (PBYTE)AllocateMemory(Size);
    if (Buffer == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    FileInfo->FileType                  = UnpackerFileBinary;
    FileInfo->BinaryData.Buffer         = Buffer;
    FileInfo->BinaryData.Size.QuadPart  = Size;

    Status = m_File.Read(Buffer, Size);
    FAIL_RETURN(Status);

    if (FLAG_ON(Flags, UNPACKER_SAVE_RAW_DATA))
        return STATUS_SUCCESS;

    if (FLAG_ON(Entry->Flags, UNPACKER_ENTRY_ENCRYPTED))
    {
        DecryptData(Buffer, Entry->DecryptLength, Entry->Seed);
//        EncryptData(Buffer, Entry->DecryptLength, Entry->Seed);
//        DecryptData(Buffer, Entry->DecryptLength, Entry->Seed);
    }

    if (FLAG_ON(Entry->Flags, UNPACKER_ENTRY_COMPRESSED))
    {
        Size = Entry->Size.LowPart;
        Buffer = (PBYTE)AllocateMemory(Size);
        if (Buffer == NULL)
            return STATUS_INSUFFICIENT_RESOURCES;

        Status = uncompress(Buffer, &Size, FileInfo->BinaryData.Buffer, FileInfo->BinaryData.Size.LowPart);
        FreeMemory(FileInfo->BinaryData.Buffer);

        FileInfo->BinaryData.Buffer         = Buffer;
        FileInfo->BinaryData.Size.QuadPart  = Size;

        if (Status != Z_OK)
        {
            return STATUS_UNSUCCESSFUL;
        }
    }

    return STATUS_SUCCESS;
}

LONG STDCALL QueryFileList(NITRO_PLUS_ENTRY *Entry, PWIN32_FIND_DATAW FindData, ULONG_PTR Context)
{
    UNREFERENCED_PARAMETER(Context);

    Entry->Size.LowPart     = FindData->nFileSizeLow;
    Entry->Size.HighPart    = FindData->nFileSizeHigh;

    StrCopyW(Entry->FileName, FindData->cFileName);

    return 1;
}

UPK_STATUS
NitroPlus::
Pack(
    PCWSTR          InputPath,
    PCWSTR          OutputFile  /* = NULL */,
    PLARGE_INTEGER  PackedFiles /* = NULL */,
    ULONG           Flags       /* = 0 */
)
{
    UNREFERENCED_PARAMETER(OutputFile);
    UNREFERENCED_PARAMETER(Flags);

    ULONG                   PathLength, Length, Hash, Offset;
    ULONG                   Size, CompressedSize, FileBufferSize, CompresseBufferSize;
    WCHAR                   FilePath[MAX_NTPATH];
    PVOID                   NpaEntryBase, FileBuffer, CompresseBuffer;
    PBYTE                   NpaEntryBuffer;
    PWSTR                   FileName;
    NTSTATUS                Status;
    LARGE_INTEGER           FileCount, PackedFileCount;
    NITRO_PLUS_ENTRY       *BaseEntry, *Entry;
    NITRO_PLUS_NPA_HEADER   Header;
    NITRO_PLUS_NPA_ETNRY   *Info;
    NtFileDisk              File;

    if (PackedFiles == NULL)
        PackedFiles = &PackedFileCount;

    PackedFiles->QuadPart = 0;

    if (!EnumDirectoryFiles(
            (PVOID *)&BaseEntry,
            L"*.*",
            sizeof(*BaseEntry),
            InputPath,
            &FileCount,
            (EnumDirectoryFilesCallBackRoutine)QueryFileList,
            0,
            EDF_SUBDIR)
       )
    {
        return STATUS_UNSUCCESSFUL;
    }

    FileBufferSize      = 0;
    CompresseBufferSize = 0;
    FileBuffer          = NULL;
    CompresseBuffer     = NULL;

    *(PULONG)&Header.Signature  = NPA_HEADER_MAGIC;
    Header.Version              = NPA_GCLX_VERSION;
    Header.EntryCount           = FileCount.LowPart;
    Header.FileCount            = FileCount.LowPart;
    Header.DirectoryCount       = 0;
    Header.IsCompressed         = TRUE;
    Header.IsEncrypted          = TRUE;

    RtlRandom(&Header.Hash[0]);
    RtlRandom(&Header.Hash[1]);

    PathLength = StrLengthW(InputPath);

    if (OutputFile != NULL)
    {
        Status = m_File.Create(OutputFile);
    }
    else
    {
        FileName = FilePath + PathLength;
        CopyMemory(FilePath, InputPath, PathLength * sizeof(*FilePath));
        if (FileName[-1] == '\\')
            --FileName;

        *(PULONG64)FileName = TAG4W('.npa');
        FileName[4] = 0;

        Status = m_File.Create(FilePath);
    }

    if (!NT_SUCCESS(Status))
        goto RETURN_POINT;

    PathLength += InputPath[PathLength - 1] != '\\';

    NpaEntryBase = AllocateMemory(sizeof(*BaseEntry) * FileCount.LowPart);
    if (NpaEntryBase == NULL)
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto RETURN_POINT;
    }

    NpaEntryBuffer  = (PBYTE)NpaEntryBase;
    Entry           = BaseEntry;

    for (ULONG Index = 0, Count = FileCount.LowPart; Count; ++Index, --Count)
    {
        Length = StrLengthW(Entry->FileName) - PathLength;

        Length = WideCharToMultiByte(
                    CP_SHIFTJIS,
                    0,
                    Entry->FileName + PathLength,
                    Length,
                    (PSTR)NpaEntryBuffer + 4,
                    INT_MAX,
                    NULL,
                    NULL
                 );
//        Nt_UnicodeToAnsi((PSTR)NpaEntryBuffer + 4, INT_MAX, Entry->FileName + PathLength, Length, &Length);
        *(PULONG)NpaEntryBuffer = Length;

        NpaEntryBuffer += 4;

        Entry->DecryptLength    = Length;
        Entry->Seed             = HashBuffer(NpaEntryBuffer, Length);

        EncryptName(NpaEntryBuffer, Length, Index, &Header);

        NpaEntryBuffer += Length;
        NpaEntryBuffer += sizeof(*Info);

        ++Entry;
    }

    Header.EntrySize = PtrOffset(NpaEntryBuffer, NpaEntryBase);

    Hash            = Header.Hash[0] * Header.Hash[1];
    NpaEntryBuffer  = (PBYTE)NpaEntryBase;
    Entry           = BaseEntry;
    Offset          = 0;

    m_File.Seek(Header.EntrySize + sizeof(Header), FILE_BEGIN);

    for (ULONG Index = 0, Count = FileCount.LowPart; Count; ++Index, --Count)
    {
        Status = File.Open(Entry->FileName);
        if (!NT_SUCCESS(Status))
            break;

        Size = File.GetSize32();
        if (FileBufferSize < Size)
        {
            FileBufferSize = Size;
            FileBuffer = ReAllocateMemory(FileBuffer, FileBufferSize);
            if (FileBuffer == NULL)
            {
                Status = STATUS_INSUFFICIENT_RESOURCES;
                break;
            }
        }

        Status = File.Read(FileBuffer, Size);
        if (!NT_SUCCESS(Status))
            break;

        CompressedSize = Size * 4;
        if (CompresseBufferSize < CompressedSize)
        {
            CompresseBufferSize = CompressedSize;
            CompresseBuffer = ReAllocateMemory(CompresseBuffer, CompresseBufferSize);
            if (CompresseBuffer == NULL)
            {
                Status = STATUS_INSUFFICIENT_RESOURCES;
                break;
            }
        }

        CompressedSize = CompresseBufferSize;
        Status = compress2(CompresseBuffer, &CompressedSize, FileBuffer, Size, Z_BEST_COMPRESSION);
        if (Status != Z_OK)
        {
            Status = STATUS_UNSUCCESSFUL;
            break;
        }

        EncryptData(
            CompresseBuffer,
            MY_MIN(CompressedSize, Entry->DecryptLength + 0x1000),
            (Hash + Entry->Seed) * Size
        );

        NpaEntryBuffer += *(PULONG)NpaEntryBuffer + 4;
        Info            = (NITRO_PLUS_NPA_ETNRY *)NpaEntryBuffer;
        NpaEntryBuffer += sizeof(*Info);

        Info->FileType          = NP_FILE_TYPE_FILE;
        Info->CompressedSize    = CompressedSize;
        Info->Offset            = Offset;
        Info->OriginalSize      = Size;
        Info->DirectoryIndex    = 0;

        Status = m_File.Write(CompresseBuffer, CompressedSize);
        if (!NT_SUCCESS(Status))
            break;

        Offset += CompressedSize;
        ++Entry;
    }

    if (!NT_SUCCESS(Status))
        goto RETURN_POINT;

    m_File.Seek(0, FILE_BEGIN);
    Status = m_File.Write(&Header, sizeof(Header));
    if (!NT_SUCCESS(Status))
        goto RETURN_POINT;

    Status = m_File.Write(NpaEntryBase, Header.EntrySize);
    if (!NT_SUCCESS(Status))
        goto RETURN_POINT;

    PackedFiles->QuadPart = FileCount.QuadPart;

RETURN_POINT:

    FreeMemory(FileBuffer);
    EnumDirectoryFilesFree(BaseEntry);

    return Status;
}

UPK_STATUS
NitroPlus::
InitIndex(
    PVOID                   EntryBuffer,
    NITRO_PLUS_NPA_HEADER  *Header
)
{
    ULONG                   Length, Flags, HeaderSize, Hash;
    PBYTE                   Buffer;
    NITRO_PLUS_ENTRY       *Entry;
    NITRO_PLUS_NPA_ETNRY   *Info;

    m_Index.EntrySize = sizeof(*Entry);

    Entry = (NITRO_PLUS_ENTRY *)AllocateEntry(Header->EntryCount);
    if (Entry == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    Buffer      = (PBYTE)EntryBuffer;
    HeaderSize  = sizeof(*Header) + Header->EntrySize;
    Flags       = (Header->IsCompressed ? UNPACKER_ENTRY_COMPRESSED : 0) | (Header->IsEncrypted ? UNPACKER_ENTRY_ENCRYPTED : 0);
    Hash        = Header->Hash[0] * Header->Hash[1];

    for (ULONG Index = 0, Count = Header->EntryCount; Count; ++Index, --Count)
    {
        Length = *(PULONG)Buffer;
        Buffer += sizeof(Length);

        DecryptName(Buffer, Length, Index, Header);
        MultiByteToWideChar(
            IsShiftJISString((PSTR)Buffer, Length) ? CP_SHIFTJIS : CP_GB2312,
            0,
            (PSTR)Buffer,
            Length,
            Entry->FileName,
            countof(Entry->FileName)
        );

        Buffer += Length;
        Info = (NITRO_PLUS_NPA_ETNRY *)Buffer;
        switch (Info->FileType)
        {
            case NP_FILE_TYPE_DIRECTORY:
                Entry->Attributes = FILE_ATTRIBUTE_DIRECTORY;
                break;

            case NP_FILE_TYPE_FILE:
            default:
                Entry->Attributes               = FILE_ATTRIBUTE_NORMAL;
                Entry->DirectoryIndex           = Info->DirectoryIndex;
                Entry->Offset.QuadPart          = Info->Offset + HeaderSize;
                Entry->CompressedSize.QuadPart  = Info->CompressedSize;
                Entry->Size.QuadPart            = Info->OriginalSize;
                Entry->Flags                    = Flags;
                Entry->Seed                     = (Hash + HashBuffer(Buffer - Length, Length)) * Entry->Size.LowPart;
                Entry->DecryptLength            = MY_MIN(Entry->CompressedSize.LowPart, Length + 0x1000);
                break;
        }

        Buffer += sizeof(*Info);

        ++Entry;
    }

    m_Index.FileCount.QuadPart = Header->EntryCount;

    return STATUS_SUCCESS;
}

ULONG
NitroPlus::
HashBuffer(
    PVOID Buffer,
    ULONG Length
)
{
    PBYTE Buf;
    ULONG Hash;

    Hash = 0x20101118;
    Buf  = (PBYTE)Buffer;
    for (; Length; --Length)
    {
        Hash -= *Buf++;
    }

    return Hash * PtrOffset(Buf, Buffer);
}

UPK_STATUS
NitroPlus::
DecryptName(
    PVOID                   Name,
    ULONG                   Length,
    ULONG                   Index,
    NITRO_PLUS_NPA_HEADER  *Header
)
{
    ULONG Mask;
    BYTE  b;
    PBYTE Buffer;

    Mask    = Header->Hash[0] * Header->Hash[1];
    Buffer  = (PBYTE)Name;
    for (ULONG NameIndex = 0; Length; ++NameIndex, --Length)
    {
        b  = (BYTE)NameIndex * 0xFC;
        b -= (BYTE)(Mask >> 24);
        b -= (BYTE)(Mask >> 16);
        b -= (BYTE)(Mask >> 8);
        b -= (BYTE)(Mask);
        b -= (BYTE)(Index >> 24);
        b -= (BYTE)(Index >> 16);
        b -= (BYTE)(Index >> 8);
        b -= (BYTE)(Index);

        *Buffer++ += b;
    }

    return STATUS_SUCCESS;
}

/*++

movzx   edx, byte ptr [eax+edi]
mov     dl, byte ptr [edx+DecryptTable]
sub     dl, cl
sub     dl, al
mov     byte ptr [eax+edi], dl
inc     eax
cmp     eax, ebp

--*/

static BYTE DecryptTable[0x100] =

#if GUILTY_CROWN_LOST_XMAS_TRAILER
{
	0xC8, 0x38, 0xF3, 0xB9, 0xBC, 0x48, 0x35, 0x30, 0x83, 0x5C, 0xC9, 0x0A, 0x61, 0x15, 0xD5, 0x53,
    0x3F, 0x81, 0xA7, 0xEA, 0x52, 0xE6, 0xD6, 0x40, 0xD1, 0x19, 0xA2, 0x79, 0x21, 0x7A, 0xE1, 0xE9,
    0x9D, 0xCA, 0x9A, 0xA1, 0xB0, 0xB7, 0x6F, 0xDF, 0x27, 0x87, 0x13, 0x6B, 0xA9, 0xC3, 0xE7, 0x49,
    0x50, 0x75, 0x56, 0xE3, 0x3E, 0xF9, 0x55, 0x93, 0x36, 0xE2, 0x71, 0x41, 0x04, 0x1E, 0x29, 0x54,
    0x3C, 0xD8, 0xF4, 0x3A, 0x01, 0xF1, 0x74, 0x89, 0xEF, 0xD7, 0x42, 0x76, 0x5D, 0xFB, 0x6D, 0xFE,
    0xAE, 0x85, 0x66, 0x92, 0x34, 0x1C, 0xA8, 0x16, 0x47, 0x65, 0x88, 0xDA, 0x3D, 0x91, 0x7C, 0x64,
    0x10, 0xAF, 0x9F, 0x5E, 0x80, 0x2B, 0x22, 0xA0, 0xBA, 0x84, 0x4D, 0x9B, 0x2D, 0x0F, 0xC5, 0x43,
    0x07, 0x77, 0x39, 0x8B, 0xFF, 0x9C, 0xF2, 0x86, 0x97, 0xF6, 0x51, 0x6C, 0x67, 0x26, 0x0D, 0xDC,
    0x46, 0x68, 0x60, 0x5A, 0x24, 0xFA, 0x14, 0x99, 0x58, 0xB3, 0xC1, 0xAB, 0x73, 0x69, 0x44, 0xD9,
    0x0B, 0x06, 0x70, 0x7B, 0x8A, 0xAD, 0xCE, 0xF0, 0x5F, 0xC4, 0x95, 0x2E, 0x94, 0xCD, 0x8C, 0xBF,
    0xBD, 0x45, 0xC0, 0xDB, 0xF8, 0xFC, 0x7E, 0xDE, 0x02, 0xF5, 0xD2, 0x96, 0x98, 0x9E, 0xE4, 0x20,
    0x8D, 0x4E, 0xD0, 0x0C, 0x5B, 0x7D, 0x05, 0x1F, 0xD3, 0xA3, 0x57, 0xCF, 0x37, 0xBE, 0xB2, 0x4F,
    0x25, 0x28, 0xB4, 0x08, 0x0E, 0x2C, 0x11, 0x4B, 0x90, 0xDD, 0xE5, 0x1D, 0xA5, 0xEC, 0xCC, 0x63,
    0xC6, 0x03, 0xF7, 0xB5, 0x4A, 0x12, 0x72, 0x17, 0xD4, 0x82, 0xAC, 0xED, 0xA6, 0xEE, 0xEB, 0x00,
    0x2A, 0x2F, 0x09, 0x32, 0xE8, 0xAA, 0x7F, 0x3B, 0x6A, 0x78, 0x23, 0x8E, 0xB8, 0x1B, 0x8F, 0xA4,
	0xCB, 0xB1, 0x18, 0xB6, 0x33, 0xE0, 0xC7, 0xFD, 0x62, 0x6E, 0x31, 0x4C, 0xBB, 0x59, 0xC2, 0x1A,
};

// GUILTY_CROWN_LOST_XMAS_TRAILER
#elif AXANAEL
{
    0x21, 0x71, 0xF0, 0xD8, 0xD6, 0x81, 0x73, 0x7C, 0x00, 0x46, 0x28, 0x67, 0xBD, 0x93, 0xE3, 0x40,
    0x7F, 0x0D, 0x5A, 0x37, 0x4B, 0x39, 0xE9, 0x8C, 0xED, 0x98, 0x5B, 0xC8, 0xAD, 0xC7, 0x3D, 0x38,
    0x12, 0x27, 0x17, 0x5D, 0xDC, 0xDA, 0xBF, 0xEF, 0xAA, 0x0A, 0x90, 0xB4, 0x58, 0x20, 0x3A, 0x88,
    0x4C, 0xC3, 0x49, 0x30, 0x7E, 0xF8, 0x43, 0x10, 0x79, 0x3B, 0xCD, 0x8D, 0x65, 0x9E, 0xA8, 0x45,
    0x76, 0xE1, 0xF5, 0x77, 0x6D, 0xFD, 0xC5, 0x08, 0x3F, 0xEA, 0x8B, 0xC9, 0x42, 0xF4, 0xB2, 0xFE,
    0x5E, 0x03, 0xB9, 0x1B, 0x75, 0x96, 0x51, 0x99, 0x8A, 0xB3, 0x01, 0xE7, 0x72, 0x1D, 0xC6, 0xB5,
    0x9C, 0x5F, 0x1F, 0x4E, 0x0C, 0xA4, 0xAB, 0x5C, 0xD7, 0x05, 0x82, 0x14, 0xA2, 0x6F, 0x23, 0x80,
    0x6A, 0xCA, 0x78, 0x04, 0xFF, 0x16, 0xFB, 0x09, 0x1A, 0xF9, 0x4D, 0xB6, 0xBA, 0xA9, 0x62, 0xE6,
    0x89, 0xB1, 0xBC, 0x47, 0xA5, 0xF7, 0x95, 0x18, 0x41, 0xD0, 0x2D, 0x54, 0xC0, 0xB8, 0x85, 0xE8,
    0x64, 0x69, 0xCC, 0xC4, 0x07, 0x52, 0x2E, 0xFC, 0x4F, 0x25, 0x13, 0xAE, 0x15, 0x22, 0x06, 0xDF,
    0xD2, 0x83, 0x2C, 0xE4, 0xF1, 0xF6, 0xCE, 0xEE, 0x6B, 0xF3, 0xEB, 0x19, 0x11, 0x1E, 0x35, 0xAC,
    0x02, 0x8E, 0xEC, 0x66, 0x44, 0xC2, 0x63, 0x9F, 0xE0, 0x50, 0x4A, 0x2F, 0x7A, 0xDE, 0xDB, 0x8F,
    0xA3, 0xA1, 0xD5, 0x61, 0x6E, 0xA6, 0x9D, 0x84, 0x1C, 0xE2, 0x33, 0x92, 0x53, 0x36, 0x26, 0xB0,
    0x29, 0x60, 0xFA, 0xD3, 0x87, 0x9B, 0xCB, 0x9A, 0xE5, 0x0B, 0x56, 0x32, 0x59, 0x3E, 0x34, 0x6C,
    0xA7, 0xAF, 0x68, 0x7B, 0x31, 0x57, 0xCF, 0x74, 0xB7, 0xC1, 0xA0, 0x0E, 0xD1, 0x94, 0x0F, 0x55,
    0x24, 0xDD, 0x91, 0xD9, 0x70, 0x3C, 0x2A, 0xF2, 0xBB, 0xBE, 0x7D, 0x86, 0xD4, 0x48, 0x2B, 0x97
};

#endif

UPK_STATUS
NitroPlus::
DecryptData(
    PVOID Buffer,
    ULONG Length,
    ULONG Hash
)
{
    PBYTE Buf = (PBYTE)Buffer;

    for (ULONG Index = 0; Length; ++Index, --Length)
    {
        *Buf = DecryptTable[*Buf] - (BYTE)Hash - (BYTE)Index;
        ++Buf;
    }

    return STATUS_SUCCESS;
}

UPK_STATUS
NitroPlus::
EncryptName(
    PVOID                   Name,
    ULONG                   Length,
    ULONG                   Index,
    NITRO_PLUS_NPA_HEADER  *Header
)
{
    ULONG Mask;
    BYTE  b;
    PBYTE Buffer;

    Mask    = Header->Hash[0] * Header->Hash[1];
    Buffer  = (PBYTE)Name;
    for (ULONG NameIndex = 0; Length; ++NameIndex, --Length)
    {
        b  = (BYTE)NameIndex * 0xFC;
        b -= (BYTE)(Mask >> 24);
        b -= (BYTE)(Mask >> 16);
        b -= (BYTE)(Mask >> 8);
        b -= (BYTE)(Mask);
        b -= (BYTE)(Index >> 24);
        b -= (BYTE)(Index >> 16);
        b -= (BYTE)(Index >> 8);
        b -= (BYTE)(Index);

        *Buffer++ -= b;
    }

    return STATUS_SUCCESS;
}

UPK_STATUS
NitroPlus::
EncryptData(
    PVOID Buffer,
    ULONG Length,
    ULONG Hash
)
{
    if (*(PULONG)m_EncryptTable == 0)
    {
        PBYTE d, e;

        d = DecryptTable;
        e = m_EncryptTable;

        for (ULONG Count = countof(m_EncryptTable), Index = 0; Count; ++Index, --Count)
        {
            e[d[Index]] = (BYTE)Index;
        }
    }

    PBYTE Buf = (PBYTE)Buffer;

    for (ULONG Index = 0; Length; ++Index, --Length)
    {
        *Buf = m_EncryptTable[(BYTE)(*Buf + (BYTE)Hash + (BYTE)Index)];
        ++Buf;
    }

    return STATUS_SUCCESS;
}

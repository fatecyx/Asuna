#include "frfr2.h"

BOOL CFrfr2::Open(PCWSTR FileName)
{
    BOOL                Success;
    BYTE                Buffer[0x10], *SizeBuffer;
    PBYTE               EntryBuffer, FileNameBuffer;
    ULONG               Length, EntrySize, FileNameSize;
    NTSTATUS            Status;
    FRFR2_IGA_HEADER    Header;

    Status = file.Open(FileName);
    if (!NT_SUCCESS(Status))
        return FALSE;

    Status = file.Read(&Header, sizeof(Header));
    if (!NT_SUCCESS(Status))
        return FALSE;

    if (Header.Magic != FRFR2_IGA_MAGIC)
        return FALSE;

    switch (Header.Version)
    {
        case 1:
        case 2:
            break;

        default:
            // not implemented
            return FALSE;
    }

    Status = file.Read(Buffer, 5);
    if (!NT_SUCCESS(Status))
        return FALSE;

    SizeBuffer  = Buffer;
    EntrySize   = GetCompactInteger(SizeBuffer, &Length);
    if (Length < 1)
        return FALSE;

    Success         = FALSE;
    EntryBuffer     = NULL;
    FileNameBuffer  = NULL;

    LOOP_ONCE
    {
        EntryBuffer = (PBYTE)Alloc(EntrySize);
        if (EntryBuffer == NULL)
            break;

        Length = 5 - Length;
        Status = file.Read(EntryBuffer + Length, EntrySize - Length);
        if (!NT_SUCCESS(Status))
            break;

        CopyMemory(EntryBuffer, SizeBuffer, Length);

        Status = file.Read(Buffer, 5);
        if (!NT_SUCCESS(Status))
            break;

        SizeBuffer      = Buffer;
        FileNameSize    = GetCompactInteger(SizeBuffer, &Length);
        if (Length < 1)
            return FALSE;

        FileNameBuffer = (PBYTE)Alloc(FileNameSize);
        if (FileNameBuffer == NULL)
            break;

        Length = 5 - Length;
        Status = file.Read(FileNameBuffer + Length, FileNameSize - Length);
        if (!NT_SUCCESS(Status))
            break;

        CopyMemory(FileNameBuffer, SizeBuffer, Length);

        Success = InitIndex(&Header, EntryBuffer, EntrySize, FileNameBuffer, FileNameSize);
    }

    Free(EntryBuffer);
    Free(FileNameBuffer);

    return Success;
}

BOOL
CFrfr2::
InitIndex(
    FRFR2_IGA_HEADER   *Header,
    PBYTE               EntryBuffer,
    ULONG               EntrySize,
    PBYTE               FileNameBuffer,
    ULONG               FileNameSize
)
{
    ULONG               Length, FileNameOffset, FileCount, MaxFileCount;
    ULONG               BeginOffset;
    PWCHAR              FileName;
    MY_FILE_ENTRY_BASE *pEntry, *pEntryBase;

    UNREFERENCED_PARAMETER(Header);

    FileCount       = 0;
    MaxFileCount    = 0x100;
    pEntryBase = (MY_FILE_ENTRY_BASE *)Alloc(MaxFileCount * sizeof(*m_Index.pEntry), HEAP_ZERO_MEMORY);
    if (pEntryBase == NULL)
        return FALSE;

    pEntry          = pEntryBase;
    BeginOffset     = file.GetCurrentPos64();
    FileNameOffset  = GetCompactInteger(EntryBuffer, &Length);
    for (LONG SizeOfEntry = EntrySize - Length; SizeOfEntry > 0; ++FileCount)
    {
        ULONG   Offset2;
        LONG    FileNameLength;

        pEntry->Offset.QuadPart = GetCompactInteger(EntryBuffer, &Length) + BeginOffset;
        SizeOfEntry            -= Length;
        pEntry->Size.QuadPart   = GetCompactInteger(EntryBuffer, &Length);
        SizeOfEntry            -= Length;

        FileName        = pEntry->FileName;
        Offset2         = GetCompactInteger(EntryBuffer, &Length);
        SizeOfEntry    -= Length;
        FileNameLength  = Offset2 - FileNameOffset;
        FileNameSize   -= FileNameLength;

        if (SizeOfEntry < 0)
            FileNameLength += FileNameSize;

        for (; FileNameLength > 0; FileNameLength -= Length)
        {
            *FileName++ = GetCompactInteger(FileNameBuffer, &Length);
        }

        *FileName = 0;

        FileNameOffset  = Offset2;

        if (FileCount == MaxFileCount)
        {
            MaxFileCount *= 2;
            pEntryBase = (MY_FILE_ENTRY_BASE *)ReAlloc(pEntryBase, MaxFileCount * sizeof(*m_Index.pEntry), HEAP_ZERO_MEMORY);
            if (pEntryBase == NULL)
                return FALSE;

            pEntry = pEntryBase + FileCount;
        }

        *(PULONG_PTR)&pEntry += m_Index.cbEntrySize;
    }

    m_Index.pEntry = pEntryBase;
    m_Index.FileCount.QuadPart = FileCount;
    m_Index.pEntry = (MY_FILE_ENTRY_BASE *)ReAlloc(m_Index.pEntry, m_Index.FileCount.LowPart * sizeof(*m_Index.pEntry));

    return m_Index.pEntry != NULL;
}

BOOL
CFrfr2::
GetFileData(
    UNPACKER_FILE_INFO         *FileInfo,
    const MY_FILE_ENTRY_BASE   *BaseEntry,
    BOOL                        SaveRawData /* = FALSE */
)
{
    PBYTE       Buffer;
    ULONG       Size;
    NTSTATUS    Status;

    UNREFERENCED_PARAMETER(SaveRawData);

    Status = file.Seek(BaseEntry->Offset.QuadPart, FILE_BEGIN);
    if (!NT_SUCCESS(Status))
        return FALSE;

    Size = BaseEntry->Size.LowPart;
    Buffer = (PBYTE)Alloc(Size);
    if (Buffer == NULL)
        return FALSE;

    Status = file.Read(Buffer, Size);
    if (!NT_SUCCESS(Status))
    {
        Free(Buffer);
        return FALSE;
    }

    FileInfo->FileType              = UNPACKER_FILE_TYPE_BIN;
    FileInfo->FileNum               = 1;
    FileInfo->BinData.pbBuffer      = Buffer;
    FileInfo->BinData.BufferSize    = Size;

    for (BYTE Mask = 2; Size; --Size)
    {
        *Buffer++ ^= Mask++;
    }

    return TRUE;
}

ULONG CFrfr2::GetCompactInteger(PBYTE &Buffer, PULONG Length /* = NULL */)
{
    ULONG Value = 0;
    PBYTE Buf   = Buffer;

    while ((Value & 1) == 0)
    {
        Value = (Value << 7) | *Buf++;
    }

    if (Length != NULL)
        *Length = Buf - Buffer;

    Buffer = Buf;

    return Value / 2;
}
#include "Xar.h"

BOOL CXar::Open(LPCWSTR FileName)
{
    NTSTATUS    Status;
    XAR_HEADER  XarHeader;
    ULONG       Length;

    Status = file.Open(FileName);
    if (!NT_SUCCESS(Status))
        return FALSE;

    Status = file.Read(&XarHeader, sizeof(XarHeader));
    if (!NT_SUCCESS(Status))
        return FALSE;

    DecryptHeader(&XarHeader);

    if (CompareMemory(XarHeader.Signature, XAR_SIGNATURE, sizeof(XarHeader.Signature)))
        return FALSE;

    m_Index.pEntry = (MY_FILE_ENTRY_BASE *)Alloc(1 * sizeof(*m_Index.pEntry));
    if (m_Index.pEntry == NULL)
        return FALSE;

    m_BeginOffset                   = XarHeader.Offset;
    m_Index.FileCount.QuadPart      = 1;
    m_Index.pEntry->Offset.QuadPart = XarHeader.Offset;
    m_Index.pEntry->Size.QuadPart   = XarHeader.Size;
    m_Index.pEntry->Flags           = XarHeader.Unknown3;

    FileName = findnamew(FileName);
    Length = StrLengthW(FileName);
    CopyMemory(m_Index.pEntry->FileName, FileName, Length * sizeof(WCHAR));
    *(PULONG64)&m_Index.pEntry->FileName[Length] = TAG4W('.zip');
    m_Index.pEntry->FileName[Length + 4] = 0;

    return TRUE;
}

BOOL CXar::GetFileData(UNPACKER_FILE_INFO *FileInfo, const MY_FILE_ENTRY_BASE *BaseEntry, BOOL SaveRawData)
{
    NTSTATUS Status;
    PVOID    Buffer;
    ULONG    Size;
    
    UNREFERENCED_PARAMETER(SaveRawData);

    Status = file.Seek(BaseEntry->Offset.QuadPart, FILE_BEGIN);
    if (!NT_SUCCESS(Status))
        return FALSE;

    Size = BaseEntry->Size.LowPart;
    Buffer = Alloc(Size);
    if (Buffer == NULL)
        return FALSE;

    Status = file.Read(Buffer, Size);
    if (!NT_SUCCESS(Status))
    {
        Free(Buffer);
        return FALSE;
    }

    DecryptData(BaseEntry->Flags, Buffer, Size, BaseEntry->Offset.LowPart);

    FileInfo->FileType              = UNPACKER_FILE_TYPE_BIN;
    FileInfo->BinData.pbBuffer      = (PBYTE)Buffer;
    FileInfo->BinData.BufferSize    = Size;

    return TRUE;
}

VOID CXar::DecryptData(ULONG Unknown3, PVOID Buffer, ULONG Size, ULONG Offset)
{
    PBYTE Buf;

    Buf         = (PBYTE)Buffer;
    Offset     -= m_BeginOffset;
    for (BYTE Mask; Size; ++Offset, --Size)
    {
        Mask = Offset / Unknown3;
        *Buf++ ^= ((Mask + 3) * (Mask + 1) + (Unknown3 >> 8)) * (Unknown3 >> 8);
    }
}

VOID CXar::DecryptHeader(XAR_HEADER *Header)
{
    BYTE  Offset;
    PBYTE Buffer;

    Buffer  = (PBYTE)Header;
    Offset  = 0;

    for (ULONG Size = sizeof(*Header); Size; ++Offset, --Size)
    {
        *Buffer++ ^= ((Offset + 1) * (Offset + 1) + Offset + 2) * (BYTE)0xEA;
    }
}

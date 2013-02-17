#include "SafePackReader.h"
#include "sha_256_asm.cpp"

CSafePackReader::CSafePackReader()
{
    m_Entry                 = NULL;
    m_CompressedBuffer      = NULL;
    m_CompressedBufferSize  = 0;
}

CSafePackReader::~CSafePackReader()
{
    ReleaseAll();
}

NTSTATUS CSafePackReader::ReleaseAll()
{
    m_CompressedBufferSize = 0;
    SafeFree(&m_Entry);
    SafeFree(&m_CompressedBuffer);
    return file.Close();
}

NTSTATUS CSafePackReader::Open(PCWSTR FileName)
{
    ULONG               HeaderSize;
    NTSTATUS            Status;
    SAFE_PACK_HEADER   *Header;

    ReleaseAll();

    Status = file.Open(FileName);
    if (!NT_SUCCESS(Status))
        return Status;

    Header = (SAFE_PACK_HEADER *)AllocStack(sizeof(*Header));

    Status = file.Read(Header, sizeof(*Header));
    if (!NT_SUCCESS(Status))
        return Status;

    CSafePacker::DecryptHeader(Header, sizeof(*Header));
    if (Header->HeaderSize < sizeof(*Header))
        return STATUS_UNSUCCESSFUL;

    Header->Magic ^= SAFE_PACK_XOR;
    if ((Header->Magic += -(SAFE_PACK_XOR ^ SAFE_PACK_MAGIC)) != 0)
        return STATUS_UNSUCCESSFUL;

    HeaderSize = Header->HeaderSize;
    if (HeaderSize != sizeof(*Header))
    {
        Header = (SAFE_PACK_HEADER *)AllocStack(HeaderSize - sizeof(*Header));

        file.Seek(0, FILE_BEGIN);
        Status = file.Read(Header, HeaderSize);
        if (!NT_SUCCESS(Status))
            return Status;

        CSafePacker::DecryptHeader(Header, HeaderSize);
    }

    Status = file.Seek(Header->EntryOffset, FILE_BEGIN);
    if (!NT_SUCCESS(Status))
        return Status;

    m_Entry = (SAFE_PACK_ENTRY *)Alloc(Header->EntrySize.LowPart);
    if (m_Entry == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    m_EntryCount.QuadPart = Header->EntrySize.QuadPart / sizeof(*m_Entry);

    Status = file.Read(m_Entry, Header->EntrySize.LowPart);
    if (!NT_SUCCESS(Status))
    {
        SafeFree(&m_Entry);
        return Status;
    }

    return STATUS_SUCCESS;
}

NTSTATUS CSafePackReader::GetFileInfo(PCSTR FileName, SAFE_PACK_FILE_INFO *Info)
{
    ULONG Hash[4];
    SAFE_PACK_ENTRY *Entry;

    sha256(FileName, StrLengthA(FileName), Info->Hash);

    Hash[0] = Info->Hash[0] ^ Info->Hash[4];
    Hash[1] = Info->Hash[1] ^ Info->Hash[5];
    Hash[2] = Info->Hash[2] ^ Info->Hash[6];
    Hash[3] = Info->Hash[3] ^ Info->Hash[7];

    Entry = FindFile(m_Entry, m_EntryCount.LowPart, Hash);
    if (Entry == NULL)
        return STATUS_OBJECT_NAME_NOT_FOUND;

    Info->Size              = GET_ENTRY_SIZE(Entry, Hash);
    Info->Offset.LowPart    = GET_ENTRY_OFFSET_LOW(Entry, Hash);
    Info->Offset.HighPart   = GET_ENTRY_OFFSET_HIGH(Entry, Hash);
    Info->Flags             = GET_ENTRY_FLAG(Entry, Hash);

    return STATUS_SUCCESS;
}

NTSTATUS CSafePackReader::Read(SAFE_PACK_FILE_INFO *Info, PVOID Buffer, ULONG BufferSize)
{
    ULONG                       FileSize, PackedSize;
    NTSTATUS                    Status;
    aes_encrypt_ctx             AesContext;
    SAFE_PACK_COMPRESSED_HEADER CompressedHeader;

    if (Info->Size > BufferSize)
        return STATUS_BUFFER_TOO_SMALL;

RESTART_READ:

    Status = file.Seek(Info->Offset.QuadPart, FILE_BEGIN);
    if (!NT_SUCCESS(Status))
        return Status;

    FileSize = Info->Size;
    if (FLAG_ON(Info->Flags, UNPACKER_ENTRY_FLAG_COMPRESSED))
    {
        Status = file.Read(&CompressedHeader, sizeof(CompressedHeader));
        if (!NT_SUCCESS(Status))
            return Status;

        aes_encrypt_key128(&Info->Hash[4], &AesContext);
        CSafePacker::Decrypt(&AesContext, &CompressedHeader, sizeof(CompressedHeader), Info->Hash);
        if ((CompressedHeader.Magic ^= SAFE_PACK_COMPRESSED_MAGIC) != 0)
        {
            CLEAR_FLAG(Info->Flags, UNPACKER_ENTRY_FLAG_COMPRESSED);
            goto RESTART_READ;
        }

        PackedSize = CompressedHeader.CompressedSize.LowPart + sizeof(CompressedHeader);
        if (PackedSize > m_CompressedBufferSize)
        {
            m_CompressedBufferSize = PackedSize;
            m_CompressedBuffer = ReAlloc(m_CompressedBuffer, m_CompressedBufferSize);
            if (m_CompressedBuffer == NULL)
                return STATUS_INSUFFICIENT_RESOURCES;
        }

        file.Seek(Info->Offset.QuadPart, FILE_BEGIN);
        Status = file.Read(m_CompressedBuffer, PackedSize);
        if (!NT_SUCCESS(Status))
            return Status;

        CSafePacker::Decrypt(
            &AesContext,
            m_CompressedBuffer,
            PackedSize,
            Info->Hash
        );

        switch (CompressedHeader.CompressMethod)
        {
            case SPCM_UCL_NRV2E:
                if (!UCL_NRV2E_Decompress(
                    (PBYTE)m_CompressedBuffer + sizeof(CompressedHeader),
                    CompressedHeader.CompressedSize.LowPart,
                    Buffer,
                    &BufferSize)
                   )
                {
                    return STATUS_UNSUCCESSFUL;
                }
                break;
        }
    }
    else
    {
        Status = file.Read(Buffer, FileSize);
        if (!NT_SUCCESS(Status))
            return Status;

        aes_encrypt_key128(&Info->Hash[4], &AesContext);
        CSafePacker::Decrypt(&AesContext, Buffer, FileSize, Info->Hash);
    }

    return STATUS_SUCCESS;
}

#pragma push_macro("COMPARE_HASH")

#define COMPARE_HASH(_Index) \
            if (Entry->FileNameHash[_Index] < Hash[_Index]) \
            { \
                Left = Middle + 1; \
                continue; \
            } \
            else if (Entry->FileNameHash[_Index] > Hash[_Index]) \
            { \
                Right = Middle - 1; \
                continue; \
            }

SAFE_PACK_ENTRY* CSafePackReader::FindFile(SAFE_PACK_ENTRY *EntryBase, ULONG EntryCount, PULONG Hash)
{
    ULONG Left, Right, Middle;
    SAFE_PACK_ENTRY *Entry;

    Left  = 0;
    Right = EntryCount - 1;

    if (Hash[0] < EntryBase[Left].FileNameHash[0] ||
        Hash[0] > EntryBase[Right].FileNameHash[0])
    {
        return NULL;
    }

    while (Left < Right)
    {
        Middle = (Right - Left) / 2 + Left;
        Entry = &EntryBase[Middle];

        COMPARE_HASH(0);
        COMPARE_HASH(1);
        COMPARE_HASH(2);
        COMPARE_HASH(3);

        return Entry;
    }

    Entry = &EntryBase[Left];

    return (Entry->FileNameHash[0] == Hash[0] &&
            Entry->FileNameHash[1] == Hash[1] &&
            Entry->FileNameHash[2] == Hash[2] &&
            Entry->FileNameHash[3] == Hash[3]
           ) ? Entry : NULL;
}

#undef COMPARE_HASH
#pragma pop_macro("COMPARE_HASH")

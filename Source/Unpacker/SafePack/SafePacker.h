#ifndef _SAFEPACKER_H_5447b095_7f6d_4794_a657_bd31b4450648
#define _SAFEPACKER_H_5447b095_7f6d_4794_a657_bd31b4450648

#include "MyLibraryUser.h"
#include "UnpackerBase.h"
#include "aes.h"

#define SAFE_PACK_MAGIC         TAG4('FUCK')
#define NRV2E_MAGIC             TAG4('NRV2')
#define DATA_SHIFT_BITS         13

#define GET_ENTRY_OFFSET_LOW(_Entry, _Hash) ((_Entry)->Offset.LowPart ^ _rotl((_Hash)[0], DATA_SHIFT_BITS))
#define GET_ENTRY_OFFSET_HIGH(_Entry, _Hash) ((_Entry)->Offset.HighPart ^ _rotl((_Hash)[1], DATA_SHIFT_BITS))
#define GET_ENTRY_SIZE(_Entry, _Hash) ((_Entry)->Size ^ _rotl((_Hash)[2], DATA_SHIFT_BITS))
#define GET_ENTRY_FLAG(_Entry, _Hash) ((_Entry)->Flags ^ _rotl((_Hash)[3], DATA_SHIFT_BITS))

#pragma pack(1)

typedef struct
{
    PVOID           Buffer;
    ULONG           Flags;
    LARGE_INTEGER   Size;
    LARGE_INTEGER   Offset;
} SAFE_PACK_BUFFER;

typedef struct
{
    ULONG           Magic;
    ULONG           HeaderSize;
    ULONG           Flags;
    ULONG           Reserve;
    LARGE_INTEGER   EntryOffset;
    LARGE_INTEGER   EntrySize;
} SAFE_PACK_HEADER;

typedef struct
{
    ULONG           EntrySize;
    ULONG           Flags;
    LARGE_INTEGER   Offset;
    LARGE_INTEGER   FileSize;
    ULONG           Attributes;
    LARGE_INTEGER   CreationTime;
    LARGE_INTEGER   LastAccessTime;
    LARGE_INTEGER   LastWriteTime;
    ULONG           FileNameHash[4];
    UNICODE_STRING  FileName;
    WCHAR           Buffer[1];
} SAFE_PACK_ENTRY;

typedef enum
{
    NoCompress,
    CompressMethodNRV2E,

    CompressMethodUser = 0x80000000,

} SafePackCompressMethodClass;

typedef struct
{
    ULONG           Magic;
    ULONG           Flags;
    ULONG           CompressMethod;
    LARGE_INTEGER   CompressedSize;
    LARGE_INTEGER   OriginalSize;
} SAFE_PACK_COMPRESSED_HEADER;

struct SAFE_PACK_ENTRY2 : public UNPACKER_FILE_ENTRY_BASE
{
    ULONG           UnicodeHash[8];
    ULONG           AnsiHash[8];
    LARGE_INTEGER   CreationTime;
    LARGE_INTEGER   LastAccessTime;
    LARGE_INTEGER   LastWriteTime;
};

#pragma pack()

class SafePackerBase
{
public:
    static VOID EncryptHeader(PVOID Buffer, ULONG Size)
    {
        ULONG               Hash[8];
        aes_encrypt_ctx     AesContext;
        PIMAGE_DOS_HEADER   DosHeader;
        PIMAGE_NT_HEADERS   NtHeaders;

        DosHeader = (PIMAGE_DOS_HEADER)&__ImageBase;
        NtHeaders = (PIMAGE_NT_HEADERS)((ULONG_PTR)DosHeader + DosHeader->e_lfanew);
        sha256(IMAGE_FIRST_SECTION(NtHeaders)->Name, RTL_FIELD_SIZE(IMAGE_SECTION_HEADER, Name), Hash);
        aes_encrypt_key128(Hash, &AesContext);
        Encrypt(&AesContext, Buffer, Size, &Hash[4]);
    }

    static VOID DecryptHeader(PVOID Buffer, ULONG Size)
    {
        ULONG               Hash[8];
        aes_encrypt_ctx     AesContext;
        PIMAGE_DOS_HEADER   DosHeader;
        PIMAGE_NT_HEADERS   NtHeaders;

        DosHeader = (PIMAGE_DOS_HEADER)&__ImageBase;
        NtHeaders = (PIMAGE_NT_HEADERS)((ULONG_PTR)DosHeader + DosHeader->e_lfanew);
        sha256(IMAGE_FIRST_SECTION(NtHeaders)->Name, RTL_FIELD_SIZE(IMAGE_SECTION_HEADER, Name), Hash);
        aes_encrypt_key128(Hash, &AesContext);
        Decrypt(&AesContext, Buffer, Size, &Hash[4]);
    }

    static VOID Encrypt(aes_encrypt_ctx *AesContext, PVOID Buffer, ULONG Size, PULONG Key)
    {
        ULONG   Mod16Buffer[4], KeyLocal[4];
        PULONG  Data;

        Data = (PULONG)Buffer;
        CopyStruct(KeyLocal, Key, sizeof(KeyLocal));
        for (ULONG SizeMod16 = Size / 16; SizeMod16; --SizeMod16)
        {
            aes_encrypt(KeyLocal, KeyLocal, AesContext);

            Data[0] ^= KeyLocal[0];
            Data[1] ^= KeyLocal[1];
            Data[2] ^= KeyLocal[2];
            Data[3] ^= KeyLocal[3];

            CopyStruct(KeyLocal, Data, sizeof(KeyLocal));

            Data += 4;
        }

        Size %= 16;
        if (Size == 0)
            return;

        CopyMemory(Mod16Buffer, Data, Size);
        aes_encrypt(KeyLocal, KeyLocal, AesContext);

        Mod16Buffer[0] ^= KeyLocal[0];
        Mod16Buffer[1] ^= KeyLocal[1];
        Mod16Buffer[2] ^= KeyLocal[2];
        Mod16Buffer[3] ^= KeyLocal[3];

        CopyMemory(Data, Mod16Buffer, Size);
    }

    static VOID Decrypt(aes_encrypt_ctx *AesContext, PVOID Buffer, ULONG Size, PULONG Key)
    {
        ULONG   Mod16Buffer[4], KeyLocal[4];
        PULONG  Data;

        Data = (PULONG)Buffer;
        CopyStruct(KeyLocal, Key, sizeof(KeyLocal));
        for (ULONG SizeMod16 = Size / 16; SizeMod16; --SizeMod16)
        {
            aes_encrypt(KeyLocal, KeyLocal, AesContext);

            Swap(Data[0], KeyLocal[0]);
            Swap(Data[1], KeyLocal[1]);
            Swap(Data[2], KeyLocal[2]);
            Swap(Data[3], KeyLocal[3]);

            Data[0] ^= KeyLocal[0];
            Data[1] ^= KeyLocal[1];
            Data[2] ^= KeyLocal[2];
            Data[3] ^= KeyLocal[3];

            Data += 4;
        }

        Size %= 16;
        if (Size == 0)
            return;

        CopyMemory(Mod16Buffer, Data, Size);
        aes_encrypt(KeyLocal, KeyLocal, AesContext);

        Mod16Buffer[0] ^= KeyLocal[0];
        Mod16Buffer[1] ^= KeyLocal[1];
        Mod16Buffer[2] ^= KeyLocal[2];
        Mod16Buffer[3] ^= KeyLocal[3];

        CopyMemory(Data, Mod16Buffer, Size);
    }

    UPK_STATUS
    PreCompressData(
        SAFE_PACK_ENTRY2 *FileInfo,
        SAFE_PACK_BUFFER *Buffer
    )
    {
        UNREFERENCED_PARAMETER(FileInfo);
        UNREFERENCED_PARAMETER(Buffer);
        return STATUS_NOT_IMPLEMENTED;
    }

    UPK_STATUS
    CompressData(
        SAFE_PACK_ENTRY2 *FileInfo,
        SAFE_PACK_BUFFER *SourceBuffer,
        SAFE_PACK_BUFFER *DestinationBuffer
    )
    {
        BOOL Success;
        SAFE_PACK_COMPRESSED_HEADER *Header;

        UNREFERENCED_PARAMETER(FileInfo);
        return STATUS_COMPRESSION_DISABLED;

        if (DestinationBuffer->Size.QuadPart < SourceBuffer->Size.QuadPart * 2)
        {
            DestinationBuffer->Size.QuadPart = SourceBuffer->Size.QuadPart * 2;
            return STATUS_BUFFER_TOO_SMALL;
        }

        Header = (SAFE_PACK_COMPRESSED_HEADER *)DestinationBuffer->Buffer;

        Success = UCL_NRV2E_Compress(
                    SourceBuffer->Buffer,
                    SourceBuffer->Size.LowPart,
                    Header + 1,
                    &DestinationBuffer->Size.LowPart
                  );

        if (!Success)
            return STATUS_UNSUCCESSFUL;

        DestinationBuffer->Size.HighPart = 0;

        if (DestinationBuffer->Size.LowPart + sizeof(*Header) >= SourceBuffer->Size.LowPart)
        {
            return STATUS_COMPRESSION_DISABLED;
        }

        Header->Magic                     = NRV2E_MAGIC;
        Header->Flags                     = 0;
        Header->CompressMethod            = CompressMethodNRV2E;
        Header->OriginalSize.QuadPart     = SourceBuffer->Size.QuadPart;
        Header->CompressedSize.QuadPart   = DestinationBuffer->Size.QuadPart;

        DestinationBuffer->Size.QuadPart += sizeof(*Header);

        return STATUS_SUCCESS;
    }

    UPK_STATUS
    PostCompressData(
        SAFE_PACK_ENTRY2 *FileInfo,
        SAFE_PACK_BUFFER *Buffer
    )
    {
        aes_encrypt_ctx AesContext;

        return STATUS_NOT_IMPLEMENTED;

        aes_encrypt_key128(&FileInfo->UnicodeHash[4], &AesContext);
        Encrypt(&AesContext, Buffer->Buffer, Buffer->Size.LowPart, FileInfo->UnicodeHash);

        return STATUS_SUCCESS;
    }

    UPK_STATUS
    PreCompressEntry(
        SAFE_PACK_HEADER *Header,
        SAFE_PACK_BUFFER *SourceBuffer
    )
    {
        UNREFERENCED_PARAMETER(Header);
        UNREFERENCED_PARAMETER(SourceBuffer);

        return STATUS_NOT_IMPLEMENTED;
    }

    UPK_STATUS
    CompressEntry(
        SAFE_PACK_HEADER *Header,
        SAFE_PACK_BUFFER *SourceBuffer,
        SAFE_PACK_BUFFER *DestinationBuffer
    )
    {
        UNREFERENCED_PARAMETER(Header);
        return SafePackerBase::CompressData(NULL, SourceBuffer, DestinationBuffer);
    }

    UPK_STATUS
    PostCompressEntry(
        SAFE_PACK_HEADER *Header,
        SAFE_PACK_BUFFER *SourceBuffer
    )
    {
        UNREFERENCED_PARAMETER(Header);
        return STATUS_NOT_IMPLEMENTED;
        EncryptHeader(SourceBuffer->Buffer, SourceBuffer->Size.LowPart);
        return STATUS_SUCCESS;
    }

    UPK_STATUS
    EncryptPackHeader(
        SAFE_PACK_HEADER *Header
    )
    {
        return STATUS_NOT_IMPLEMENTED;

        SET_FLAG(Header->Flags, UNPACKER_ENTRY_ENCRYPTED);
        EncryptHeader(Header, Header->HeaderSize);

        return STATUS_SUCCESS;
    }

protected:
    static LARGE_INTEGER FileTimeToLargeInteger(FILETIME FileTime)
    {
        LARGE_INTEGER Large;

        Large.LowPart   = FileTime.dwLowDateTime;
        Large.HighPart  = FileTime.dwHighDateTime;

        return Large;
    }

    static
    LONG
    STDCALL
    EnumDirCallback(
        SAFE_PACK_ENTRY2   *Entry,
        PWIN32_FIND_DATAW   FindData,
        ULONG_PTR           Context
    )
    {
        CHAR    FileName[MAX_NTPATH];
        ULONG   Length;

        Length = StrLengthW(FindData->cFileName + Context);

        Entry->Attributes       = FindData->dwFileAttributes;
        Entry->CreationTime     = FileTimeToLargeInteger(FindData->ftCreationTime);
        Entry->LastAccessTime   = FileTimeToLargeInteger(FindData->ftLastAccessTime);
        Entry->LastWriteTime    = FileTimeToLargeInteger(FindData->ftLastWriteTime);
        Entry->Size.LowPart     = FindData->nFileSizeLow;
        Entry->Size.HighPart    = FindData->nFileSizeHigh;
        Entry->Flags            = 0;

        Nt_UnicodeToAnsi(FileName, countof(FileName), FindData->cFileName + Context, Length, &Length);
        StringUpperA(FileName, Length);
        sha256(FileName, Length, Entry->AnsiHash);

        CopyMemory(Entry->FileName, FindData->cFileName + Context, (Length + 1) * sizeof(WCHAR));
        StringUpperW(Entry->FileName, Length);
        sha256(Entry->FileName, Length * sizeof(WCHAR), Entry->UnicodeHash);

        CopyMemory(Entry->FileName, FindData->cFileName + Context, (Length + 1) * sizeof(WCHAR));

        return 1;
    }

    static INT CDECL SortEntry(SAFE_PACK_ENTRY *Entry1, SAFE_PACK_ENTRY *Entry2)
    {
        ULONG  Count;
        PULONG Hash1, Hash2;

        Hash1 = Entry1->FileNameHash;
        Hash2 = Entry2->FileNameHash;
        Count = countof(Entry1->FileNameHash);

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
};

template<class BaseType>
class SafePackerImpl : public UnpackerImpl<BaseType>, public SafePackerBase
{
public:
    UPK_STATUS
    Pack(
        PCWSTR          InputPath,
        PCWSTR          OutputFile   = NULL,
        PLARGE_INTEGER  PackedFiles  = NULL,
        ULONG           Flags        = 0
    );
};

template<class BaseType>
UPK_STATUS
SafePackerImpl<BaseType>::
Pack(
    PCWSTR          InputPath,
    PCWSTR          OutputFile  /* = NULL */,
    PLARGE_INTEGER  PackedFiles /* = NULL */,
    ULONG           Flags       /* = 0 */
)
{
    UPK_STATUS          Status;
    WCHAR               PackPath[MAX_NTPATH], *FileName;
    ULONG_PTR           Length, PackedFileNumber;
    ULONG_PTR           BufferSize, CompressedBufferSize, FileSize;
    ULONG_PTR           EntrySize, WriteSize;
    PVOID               FileBuffer, Buffer, Compressed, WriteBuffer;
    SAFE_PACK_BUFFER    SourceBuffer, DestinationBuffer;
    SAFE_PACK_HEADER    Header;
    SAFE_PACK_ENTRY    *EntryBase, *Entry;
    SAFE_PACK_ENTRY2   *FileList, *FileListBase;
    LARGE_INTEGER       FileNumber, DataOffset;
    BaseType           *This;

    if (Flags != 0)
        return STATUS_INVALID_PARAMETER;

    This                = GetTopClass();
    Buffer              = NULL;
    Compressed          = NULL;
    PackedFileNumber    = 0;

    if (PackedFiles != NULL)
        PackedFiles->QuadPart = 0;

    Length = StrLengthW(InputPath);

    Status = STATUS_UNSUCCESSFUL;
    if (
        !EnumDirectoryFiles(
            (PVOID *)&FileListBase,
            L"*.*",
            sizeof(*FileListBase),
            InputPath,
            &FileNumber,
            (EnumDirectoryFilesCallBackRoutine)EnumDirCallback,
            Length + (InputPath[Length - 1] != '\\'),
            EDF_SUBDIR | EDF_BEFORE)
       )
    {
        return Status;
    }

    NtFileDisk pack, file;

    EntrySize = (ULONG_PTR)FileNumber.QuadPart;
    EntrySize = EntrySize * (sizeof(*Entry) - sizeof(Entry->Buffer) + MAX_NTPATH * sizeof(WCHAR));
    EntryBase = (SAFE_PACK_ENTRY *)AllocateMemory(EntrySize);
    if (EntryBase == NULL)
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto CLEAN_UP;
    }

    if (OutputFile == NULL)
    {
        CopyMemory(PackPath, InputPath, Length * sizeof(WCHAR));
        Length -= PackPath[Length - 1] == '\\';
        *(PULONG64)&PackPath[Length + 0] = TAG4W('.pac');
        *(PULONG)&PackPath[Length + 4] = 'k';
    }
    else
    {
        Length = StrLengthW(OutputFile);
        CopyMemory(PackPath, OutputFile, (Length + 1) * sizeof(WCHAR));
        do
        {
            if (PackPath[Length] == '\\' || PackPath[Length] == '/')
                break;
        } while (--Length);
    }

    Status = pack.Create(PackPath);
    if (!NT_SUCCESS(Status))
        goto CLEAN_UP;

    Header.Magic                = SAFE_PACK_MAGIC;
    Header.HeaderSize           = sizeof(Header);
    Header.Flags                = 0;
    Header.EntryOffset.QuadPart = 0;
    Header.EntrySize.QuadPart   = 0;
    DataOffset.QuadPart         = Header.HeaderSize;

    Status = pack.Seek(DataOffset, FILE_BEGIN);
    if (!NT_SUCCESS(Status))
        goto CLEAN_UP;

    FileName = PackPath + Length;
    if (Length != 0)
        *FileName++ = '\\';

    BufferSize              = 0;
    CompressedBufferSize    = 0;
    Entry                   = EntryBase;
    FileList                = FileListBase;

    for (LARGE_INTEGER Count = FileNumber; Count.QuadPart; ++FileList, --Count.QuadPart)
    {
        Length = StrLengthW(FileList->FileName) * sizeof(WCHAR);

        Entry->Flags            = Flags;
        Entry->CreationTime     = FileList->CreationTime;
        Entry->LastAccessTime   = FileList->LastAccessTime;
        Entry->LastWriteTime    = FileList->LastWriteTime;
        Entry->FileNameHash[0]  = FileList->UnicodeHash[0] ^ FileList->UnicodeHash[4];
        Entry->FileNameHash[1]  = FileList->UnicodeHash[1] ^ FileList->UnicodeHash[5];
        Entry->FileNameHash[2]  = FileList->UnicodeHash[2] ^ FileList->UnicodeHash[6];
        Entry->FileNameHash[3]  = FileList->UnicodeHash[3] ^ FileList->UnicodeHash[7];
        Entry->Attributes       = FileList->Attributes;

        if (FLAG_ON(Entry->Attributes, FILE_ATTRIBUTE_DIRECTORY))
            goto PACK_NEXT_FILE;

        CopyMemory(FileName, FileList->FileName, Length + sizeof(WCHAR));

        Status = file.Open(PackPath);
        if (!NT_SUCCESS(Status))
            continue;

        FileSize = file.GetSize32();
        if (FileSize > BufferSize)
        {
            BufferSize = FileSize;
            Buffer = ReAllocateMemory(Buffer, BufferSize);
            if (Buffer == NULL)
            {
                Status = STATUS_INSUFFICIENT_RESOURCES;
                goto CLEAN_UP;
            }
        }

        Status = file.Read(Buffer, FileSize);
        if (!NT_SUCCESS(Status))
            goto CLEAN_UP;

        Entry->Offset.QuadPart      = DataOffset.QuadPart;
        Entry->FileSize.QuadPart    = FileList->Size.QuadPart;

        SourceBuffer.Buffer             = Buffer;
        SourceBuffer.Flags              = Flags;
        SourceBuffer.Offset.QuadPart    = 0;
        SourceBuffer.Size.QuadPart      = FileSize;

        Status = This->PreCompressData(FileList, &SourceBuffer);
        if (Status == STATUS_NOT_IMPLEMENTED)
        {
            ;
        }
        else if (!NT_SUCCESS(Status))
        {
            continue;
        }
        else
        {
            SET_FLAG(Entry->Flags, UNPACKER_ENTRY_ENCRYPTED);
        }

        if (FileSize * 2 > CompressedBufferSize)
        {
            CompressedBufferSize = FileSize * 2;
            Compressed = ReAllocateMemory(Compressed, CompressedBufferSize);
            if (Compressed == NULL)
            {
                Status = STATUS_INSUFFICIENT_RESOURCES;
                goto CLEAN_UP;
            }
        }

        FileBuffer = Buffer;

        SourceBuffer.Buffer                 = Buffer;
        SourceBuffer.Flags                  = Flags;
        SourceBuffer.Offset.QuadPart        = 0;
        SourceBuffer.Size.QuadPart          = FileSize;

        DestinationBuffer.Flags             = Flags;
        DestinationBuffer.Offset.QuadPart   = 0;
        DestinationBuffer.Size.QuadPart     = CompressedBufferSize;

        LOOP_FOREVER
        {
            DestinationBuffer.Buffer = Compressed;
            Status = This->CompressData(FileList, &SourceBuffer, &DestinationBuffer);
            if (Status != STATUS_BUFFER_TOO_SMALL)
                break;

            CompressedBufferSize = (ULONG_PTR)DestinationBuffer.Size.QuadPart;
            Compressed = ReAllocateMemory(Compressed, CompressedBufferSize);
            if (Compressed == NULL)
            {
                Status = STATUS_INSUFFICIENT_RESOURCES;
                goto CLEAN_UP;
            }
        }

        if (Status == STATUS_COMPRESSION_DISABLED || Status == STATUS_NOT_IMPLEMENTED)
        {
            WriteBuffer = SourceBuffer.Buffer;
            WriteSize   = (ULONG_PTR)SourceBuffer.Size.QuadPart;
        }
        else if (!NT_SUCCESS(Status))
        {
            ;
        }
        else
        {
            SET_FLAG(Entry->Flags, UNPACKER_ENTRY_COMPRESSED);

            WriteBuffer = DestinationBuffer.Buffer;
            WriteSize   = (ULONG_PTR)DestinationBuffer.Size.QuadPart;
        }

        SourceBuffer.Buffer                 = WriteBuffer;
        SourceBuffer.Flags                  = Flags;
        SourceBuffer.Offset.QuadPart        = 0;
        SourceBuffer.Size.QuadPart          = WriteSize;
        Status = This->PostCompressData(FileList, &SourceBuffer);
        if (!NT_SUCCESS(Status))
        {
            ;
        }
        else
        {
            SET_FLAG(Entry->Flags, UNPACKER_ENTRY_ENCRYPTED);
        }

        Status = pack.Write(WriteBuffer, WriteSize);
        if (!NT_SUCCESS(Status))
            goto CLEAN_UP;

        DataOffset.QuadPart += WriteSize;

PACK_NEXT_FILE:

        CopyMemory(Entry->Buffer, FileList->FileName, Length);

        Entry->FileName.Buffer          = PtrSub(Entry->Buffer, EntryBase);
        Entry->FileName.Length          = (USHORT)Length;
        Entry->FileName.MaximumLength   = (USHORT)Length;
        Entry->EntrySize                = sizeof(*Entry) - sizeof(Entry->Buffer) + Entry->FileName.MaximumLength;
        Entry->EntrySize                = ROUND_UP(Entry->EntrySize, 16);
        Entry                           = PtrAdd(Entry, Entry->EntrySize);
        ++PackedFileNumber;
    }

    Header.EntrySize.QuadPart   = PtrOffset(Entry, EntryBase);
    Header.EntryOffset.QuadPart = pack.GetCurrentPos64();

//    qsort(EntryBase, PackedFileNumber, sizeof(*EntryBase), (int (__cdecl *)(const void *,const void *))SortEntry);

    SourceBuffer.Buffer             = EntryBase;
    SourceBuffer.Flags              = Flags;
    SourceBuffer.Offset.QuadPart    = 0;
    SourceBuffer.Size.QuadPart      = Header.EntrySize.QuadPart;

    Status = This->PreCompressEntry(&Header, &SourceBuffer);

    SourceBuffer.Buffer                 = EntryBase;
    SourceBuffer.Flags                  = Flags;
    SourceBuffer.Offset.QuadPart        = 0;
    SourceBuffer.Size.QuadPart          = Header.EntrySize.QuadPart;

    DestinationBuffer.Buffer            = Compressed;
    DestinationBuffer.Flags             = Flags;
    DestinationBuffer.Offset.QuadPart   = 0;
    DestinationBuffer.Size.QuadPart     = CompressedBufferSize;

    LOOP_FOREVER
    {
        DestinationBuffer.Buffer = Compressed;
        Status = This->CompressEntry(&Header, &SourceBuffer, &DestinationBuffer);
        if (Status != STATUS_BUFFER_TOO_SMALL)
            break;

        CompressedBufferSize = (ULONG_PTR)DestinationBuffer.Size.QuadPart;
        Compressed = ReAllocateMemory(Compressed, CompressedBufferSize);
        if (Compressed == NULL)
        {
            Status = STATUS_INSUFFICIENT_RESOURCES;
            goto CLEAN_UP;
        }
    }

    if (Status == STATUS_COMPRESSION_DISABLED || Status == STATUS_NOT_IMPLEMENTED)
    {
        WriteBuffer = EntryBase;
        WriteSize   = (ULONG_PTR)Header.EntrySize.QuadPart;
    }
    else if (!NT_SUCCESS(Status))
    {
        goto CLEAN_UP;
    }
    else
    {
        SET_FLAG(Header.Flags, UNPACKER_ENTRY_COMPRESSED);

        WriteBuffer = DestinationBuffer.Buffer;
        WriteSize   = (ULONG_PTR)DestinationBuffer.Size.QuadPart;
    }

    SourceBuffer.Buffer                 = WriteBuffer;
    SourceBuffer.Flags                  = Flags;
    SourceBuffer.Offset.QuadPart        = 0;
    SourceBuffer.Size.QuadPart          = WriteSize;

    Status = This->PostCompressEntry(&Header, &SourceBuffer);

    pack.Seek(0, FILE_END);
    Status = pack.Write(WriteBuffer, WriteSize);
    if (!NT_SUCCESS(Status))
        goto CLEAN_UP;

    Header.EntrySize.QuadPart = WriteSize;

    EncryptPackHeader(&Header);
    pack.Seek(0, FILE_BEGIN);
    Status = pack.Write(&Header, sizeof(Header));

CLEAN_UP:

    EnumDirectoryFilesFree(FileListBase);
    FreeMemory(EntryBase);
    FreeMemory(Buffer);
    FreeMemory(Compressed);

    if (UPK_SUCCESS(Status) && PackedFiles != NULL)
        PackedFiles->QuadPart = PackedFileNumber;

    return Status;
}


#endif // _SAFEPACKER_H_5447b095_7f6d_4794_a657_bd31b4450648

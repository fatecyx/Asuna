#ifndef _NITROPLUS_H_f4eb1cd8_81e3_452a_b5fd_028c507e19de
#define _NITROPLUS_H_f4eb1cd8_81e3_452a_b5fd_028c507e19de

#include "MyLibraryUser.h"
#include "UnpackerBase.h"

#define STEINS_GATE_KEY TAG8('BUCK', 'TICK')

#pragma pack(1)

enum
{
    NPA_HEADER_MAGIC    = TAG3('NPA'),
    NPA_GCLX_VERSION    = 1,
};

typedef struct
{
    BYTE    Signature[3];
    ULONG   Version;
    ULONG   Hash[2];
    BYTE    IsCompressed;
    BYTE    IsEncrypted;
    ULONG   EntryCount;
    ULONG   DirectoryCount;
    ULONG   FileCount;
    ULONG   Reserve1;
    ULONG   Reserve2;
    ULONG   EntrySize;
} NITRO_PLUS_NPA_HEADER;

typedef struct
{
    BYTE  FileType;
    ULONG DirectoryIndex;
    ULONG Offset;
    ULONG CompressedSize;
    ULONG OriginalSize;
} NITRO_PLUS_NPA_ETNRY;

struct NITRO_PLUS_ENTRY : public UNPACKER_FILE_ENTRY_BASE
{
    ULONG DirectoryIndex;
    ULONG Seed;
    ULONG DecryptLength;
};

#pragma pack()

class NitroPlus : public UnpackerImpl<NitroPlus>
{
protected:
    NtFileDisk  m_File;
    BYTE        m_EncryptTable[0x100];

    enum
    {
        NP_FILE_TYPE_DIRECTORY  = 1,
        NP_FILE_TYPE_FILE       = 2,
    };

public:
    NitroPlus();

    UPK_STATUS
    Open(
        PCWSTR FileName
    );

    UPK_STATUS
    GetFileData(
        UNPACKER_FILE_INFO         *FileInfo,
        UNPACKER_FILE_ENTRY_BASE   *BaseEntry,
        ULONG                       Flags = 0
    );

    UPK_STATUS
    Pack(
        PCWSTR          InputPath,
        PCWSTR          OutputFile  = NULL,
        PLARGE_INTEGER  PackedFiles = NULL,
        ULONG           Flags = 0
    );

protected:
    UPK_STATUS
    InitIndex(
        PVOID                   EntryBuffer,
        NITRO_PLUS_NPA_HEADER  *Header
    );

    ULONG
    HashBuffer(
        PVOID Buffer,
        ULONG Length
    );

    UPK_STATUS
    DecryptName(
        PVOID                   Name,
        ULONG                   Length,
        ULONG                   Index,
        NITRO_PLUS_NPA_HEADER  *Header
    );

    UPK_STATUS
    DecryptData(
        PVOID Buffer,
        ULONG Length,
        ULONG Hash
    );

    UPK_STATUS
    EncryptName(
        PVOID                   Name,
        ULONG                   Length,
        ULONG                   Index,
        NITRO_PLUS_NPA_HEADER  *Header
    );

    UPK_STATUS
    EncryptData(
        PVOID Buffer,
        ULONG Length,
        ULONG Hash
    );
};

#endif // _NITROPLUS_H_f4eb1cd8_81e3_452a_b5fd_028c507e19de

#ifndef _THCM_H_99d737f2_04ad_4d91_8968_620c8ebcd0d9_
#define _THCM_H_99d737f2_04ad_4d91_8968_620c8ebcd0d9_

#include "MyLibrary.h"
#include "UnpackerBase.h"
#include "Vector.hpp"

#pragma pack(push, 1)

typedef struct
{
    ULONG IndexSize;

} THCM_PAK_HEADER, *PTHCM_PAK_HEADER;

typedef struct THCM_PAK_INDEX_ENTRY
{
    CHAR    FileName[1];
    ULONG   CompressedSize;
    ULONG   UncompressedSize;
    ULONG   Offset;
    BOOLEAN Uncompressed;
    ULONG   DecryptKey;

    THCM_PAK_INDEX_ENTRY* Next()
    {
        return this + 1;
    }

    THCM_PAK_INDEX_ENTRY* GetData()
    {
        return PtrAdd(this, StrLengthA(FileName));
    }

} THCM_PAK_INDEX_ENTRY, *PTHCM_PAK_INDEX_ENTRY;

typedef struct
{
    ULONG IndexCrc;
    THCM_PAK_INDEX_ENTRY Entry[1];

} THCM_PAK_INDEX_HEADER, *PTHCM_PAK_INDEX_HEADER;

#pragma pack(pop)

typedef struct THCM_PAK_ENTRY : public UNPACKER_FILE_ENTRY_BASE
{
    ULONG DecryptKey;
    BOOL  Uncompressed;

} THCM_PAK_ENTRY, *PTHCM_PAK_ENTRY;

class THCMPak : public UnpackerImpl<THCMPak>
{
protected:
    NtFileDisk Pak;

public:
    UPK_STATUS Open(PCWSTR FileName);
    UPK_STATUS GetFileData(PUNPACKER_FILE_INFO FileInfo, PUNPACKER_FILE_ENTRY_BASE BaseEntry, ULONG Flags = 0);
    UPK_STATUS Pack(PCWSTR InputPath, PCWSTR OutputFile = NULL, PLARGE_INTEGER PackedFiles = NULL, ULONG Flags = 0);

protected:
    UPK_STATUS InitIndex(PVOID IndexBuffer, ULONG_PTR Size);

    VOID DecryptIndex(PVOID Buffer, ULONG_PTR Size, ULONG Key);
    VOID DecryptFileAlign4(PVOID Buffer, ULONG_PTR Size, PTHCM_PAK_ENTRY Entry);

    VOID EncryptIndex(PVOID Buffer, ULONG_PTR Size, ULONG Key)
    {
        return DecryptIndex(Buffer, Size, Key);
    }

    VOID EncryptFileAlign4(PVOID Buffer, ULONG_PTR Size, PTHCM_PAK_ENTRY Entry)
    {
        return DecryptFileAlign4(Buffer, Size, Entry);
    }

    UPK_STATUS  BuildEntry(PCWSTR InputPath, ml::GrowableArray<THCM_PAK_ENTRY> &Entries);
    ULONG_PTR   ComputePakEntrySize(ml::GrowableArray<THCM_PAK_ENTRY> &Entries, ULONG_PTR PathLength);
    UPK_STATUS  BuildPakEntry(PVOID Buffer, ml::GrowableArray<THCM_PAK_ENTRY> &Entries, ULONG_PTR PathLength);
};

#endif // _THCM_H_99d737f2_04ad_4d91_8968_620c8ebcd0d9_

#ifndef _SHARU_H_
#define _SHARU_H_

#include "my_headers.h"
#include "gal_common.h"

#define SQLI_COMP_MAGIC 0xFF435031

#pragma pack(1)

typedef struct
{
    Char   Seed[32];
    UInt32 HashTableSize;
    Char   Data[256];
    UInt32 arr[192];
    Char   tag[16];
    UInt32 FileNum;
    Large_Integer IndexOffset;
} SPackHeader;

typedef struct
{
    UInt32  Magic;
    UInt32  Flag;
    UInt32  DecompressSize;
    Byte    Data[1];
} SPackEntryCompressedData;

typedef struct
{
    Char   HashVer[16];
    UInt32 SubTableNum;
    UInt32 FileNum;
    UInt32 FileIndexSize;
    UInt32 CompressedSize;
    SPackEntryCompressedData Data;
} SPackHashTableHeader;

struct SMyPackIndex : public MY_FILE_ENTRY_BASE
{
    UInt32 Hash;
};

typedef struct
{
    Large_Integer Offset;
    UInt32 CompressedSize;
    UInt32 DecompressSize;
    Bool   bCompressed;
    Bool   bEncrypted;
    UInt32 Hash;
//    WChar FileName[MAX_PATH];
} PACK_FILE_ENTRY_INFO;
/*
typedef struct
{
    UInt32 FileNum;
    SMyPackIndex *pIndex;
} SMyPackEntry;
*/
#pragma pack()

enum EEntryFlag
{
    FLAG_ENTRY_16BIT_LENGTH = 1,
};

class CSharu : public CUnpackerImpl<CSharu>
{
protected:
//    SMyPackEntry m_entry;
    UInt32 m_Key;
    CFileDisk file;

public:
    Bool Open(PCWChar pszFileName);
    Bool GetFileData(SFileInfo *pFileInfo, const MY_FILE_ENTRY_BASE *pBaseEntry);

protected:
    Bool   InitIndex(SPackHeader *pHeader, UInt32 Key);
    UInt32 Hash(LPVoid lpBuffer, Int32 BufferSize);
    UInt32 CrcString(PCChar pszString, UInt32 Length);
    Bool   Encrypt(LPVoid lpBuffer, Int32 BufferSize, UInt32 Key);
    Bool   Decrypt(LPVoid lpBuffer, Int32 BufferSize, UInt32 Key);
    Bool   DecryptWorker(LPVoid lpBuffer, Int32 BufferSize, UInt32 Key, Bool bDecrypt);
    UInt32 DecryptFileName(LPVoid lpFileName, UInt32 Length, UInt32 Key);
    UInt32 Uncompress(LPVoid lpInputBuffer, Int32 BufferSize, LPVoid lpOutputBuffer);
};

#endif /* _SHARU_H_ */
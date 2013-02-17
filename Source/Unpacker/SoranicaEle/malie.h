// Soranica Ele £­¥½¥é¥Ë¥« ¥¨¥ì£­

#ifndef _MALIE_H_
#define _MALIE_H_

#include "my_headers.h"
#include "camellia.h"

#pragma pack(1)

typedef struct
{
    UInt32 magic;   // 'LIBP'
    UInt32 IndexCount;
    UInt32 OffsetTableCount;
    UInt32 reserve;
} SMalieDatHeader;

typedef struct
{
    Char   name[0x16];
    UInt16 usIsFile;
    union
    {
        UInt32 SubFileIndex;       // when isfile == 1
        UInt32 OffsetIndex;
    };
    union
    {
        UInt32 SubFileNum;     // when isfile == 1
        UInt32 FileSize;
    };
} SMalieIndex;

typedef struct
{
    Char   name[MAX_PATH];
    UInt32 offset;
    UInt32 size;
} SMyMalieIndex;

typedef struct
{
    UInt32 count;
    SMyMalieIndex *pIndex;
} SMyMalieEntry;

typedef struct
{
    Byte  *data;
    UInt32 size;
} SBinaryData;

typedef struct
{
    PByte  data;
    UInt32 size;
    UInt32 w;
    UInt32 h;
    UInt32 bit;
} SImageData;

typedef struct
{
    UInt32 type;
    UInt32 count;
    PByte  extra;
    union
    {
        SBinaryData  BinData;
        SImageData  *ImgData;
    };
} SFileInfo;

enum EFileType
{
    BIN,
    IMG,
    GRAY,
};

#pragma pack()

class CMalie : public CMem
{
public:
    CMalie();
    ~CMalie();

    Bool   Open(PCWChar pszFileName);
    UInt32 ExtractFile(SMyMalieIndex *pInfo, PCWChar lpOutPath = NULL);
    Bool   GetFileData(SFileInfo *pFileInfo, const SMyMalieIndex *pInfo);
    Void   FreeFileData(SFileInfo *pFileInfo);

    Void   Auto(PCWChar pszFileName);

protected:
    Bool InitIndex(LPVoid lpIndex, UInt32 uIndexSize, LPVoid lpOffsetTable, UInt32 TableSize);
    Void Release();
    Void Decrypt(Int32 KeyBits, KEY_TABLE_TYPE KeyTable, LPVoid lpBuffer, Int32 Size, Int64 Offset);

protected:
    SMyMalieEntry m_entry;
    CFileDisk file;
    Int32 keyTable[52];
    const UInt32 keyBit;
    const static UInt32 RawKey[4];
};

#endif /* _MALIE_H_ */
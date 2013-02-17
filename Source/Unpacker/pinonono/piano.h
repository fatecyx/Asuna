#ifndef _PIANO_H_
#define _PIANO_H_

#include "my_common.h"
#include "FileDisk.h"
#include "mem.h"

#pragma pack(1)

typedef struct
{
    Char   tag[12];
    UInt32 filenum;
} SPianoHeader;

typedef struct
{
    Char name[16];
} SPianoFileName;

typedef struct
{
    Char name[32];
} SPianoFileName2;

typedef struct
{
    UInt32 offset;  // offset start from the end of indexes
    UInt32 size;
} SPianoFileIndex;

typedef struct
{
    SPianoFileName2 name;
    SPianoFileIndex index;
} SMyPianoFileIndex;

typedef struct
{
    UInt32 filenum;
    SMyPianoFileIndex *pIndex;
} SMyPianoIndex;

typedef struct
{
    union
    {
        UInt16 sTag;
        Byte   unk1;
        Byte   unk2;
        UInt32 uTag;
    };
    UInt32 flag;    // 0|4 = gray  1 = 24 bit  2 = 32 bit
    UInt32 width;
    UInt32 height;
} SPianoEPAHeader;

enum EEPType
{
    BIT8  = 0, 
    BIT24 = 1, 
    BIT32 = 2, 
};

enum EFileType
{
    BIN,    // 普通文件
    IMG,    // 图片文件
    GRAY,   // 灰度图
};

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
    UInt32 flag;
    UInt32 count;
    PByte  extra;
    union
    {
        SBinaryData BinData;
        SImageData  *ImgData;
    };
} SFileInfo;

#pragma pack()

class CPiano
{
public:
    CPiano();
    ~CPiano();

    Bool Open(WChar *szFileName);
    SMyPianoFileIndex* GetIndex(UInt32 i);
    UInt32 ExtractFile(SMyPianoFileIndex *pIndex, PWChar szOutPath = NULL);
    UInt32 Pack(PWChar lpszPath);

    Void Auto(WChar *szFileName);

protected:
    Bool   InitIndex(SPianoHeader *pHeader);
    Bool   InitIndex(PWChar lpszPath);
    Bool   GetFileData(SMyPianoFileIndex *pIndex, SFileInfo *info, Bool bConvert = True);
    Void   FreeFileData(SFileInfo *info);
    UInt32 DecodeEPA(SPianoEPAHeader *pEPA, UInt32 uSize, PByte &pbDest);
    Void   Decompress(PByte pbInput, UInt32 width, PByte pbOutput, Int32 iDestSize);
    Void   Free();

protected:
    CMem m;
    CFileDisk file;
    SMyPianoIndex m_index;
    static const UInt16 m_BitsTable[5];
};

#endif /* _PIANO_H_ */
#ifndef _HRARC_H_
#define _HRARC_H_

// haruuru Arc file
#pragma warning(disable:4530)

#include "my_common.h"
#include "FileDisk.h"
#include "Mem.h"
#include <vector>

using std::vector;

enum EFileType
{
    BIN,    // 普通文件
    IMG,    // 图片文件
    GRAY,   // 灰度图
};

#pragma pack(1)

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
        SBinaryData BinData;
        SImageData  *ImgData;
    };
} SFileInfo;

typedef struct
{
    Char   Eextension[4];
    UInt32 uiFileCount;
    UInt32 uiIndexOffset;
} SArcEntry;

typedef struct
{
    UInt32 uiEntryCount;
    SArcEntry *pEntry;
} SArcHeader, *LPSArcHeader;

typedef struct
{
    Char   FileName[9];
    UInt32 uiSize;
    UInt32 uiOffset;
} SArcSubIndex;

typedef struct
{
    UInt32 uiOffset;
    UInt32 uiSize;
    Char   FileName[16];  // mod 8
} SMyArcSubIndex;

typedef struct
{
    Char   Eextension[4];
    UInt32 uiFileCount;
    UInt32 uiIndexOffset;
    SMyArcSubIndex *pSubIndex;
} SMyArcEntry;
typedef struct
{
    UInt32 uiEntryCount;
    SMyArcEntry *pEntry;
    SMyArcSubIndex *pSubIndex;
} SMyArcIndex;

typedef struct
{
    Char   Extention[4];
    UInt32 uiFileCount;
    UInt32 uiIndexOffset;
    vector<SArcSubIndex> SubIndex;
} SArcEntryForPack;

#pragma warning(disable:4200)
typedef struct
{
    UInt32 uiTag;
    u16 usFrames;
    u16 usBPP;
    struct
    {
        UInt32 uiWidth;
        UInt32 uiHeight;
        UInt32 X;
        UInt32 Y;
        UInt32 unknown;
        UInt32 uiBlockSize;
    } Blocks[1];
} SWIPHeader;
#pragma warning(default:4200)

#pragma pack()

class ChrArc
{
public:
    ChrArc();
    ~ChrArc();

    Bool Open(TCHAR *szFileName);
    Void Close();
    Void Auto(TCHAR *szFileName);

    Bool GetFileData(SMyArcSubIndex *pIndex, SFileInfo *info, Bool bConvert = True);
    Bool ExtractFile(SMyArcSubIndex *pIndex, LPSTR lpOutPath = NULL);
    Void FreeFileData(SFileInfo *info);
    Bool   Pack(TCHAR *szPath);
    UInt32 ExtractAll();
    UInt32 GetFileCount();
    SMyArcSubIndex* GetIndex(UInt32 uiIndex);
    SMyArcSubIndex* Find(char *szFile);

protected:
    Void    Free();
    Bool    InitIndex();
    UInt32  Decompress(Byte *pbInput, Byte *pbOutput);
    Bool    DecryptWSC(PByte pbBuffer, UInt32 uiSize);
    Bool    Decode8BitFrame(SWIPHeader *pHeader, UInt32 uiFrame, SImageData *image);
    Bool    DecodeWIPFrame(SWIPHeader *pHeader, SWIPHeader *pMaskHeader, UInt32 uiFrame, SImageData *image);
    SMyArcSubIndex* FindFileInIndex(SMyArcEntry *pEntry, Char *szFile);

protected:
    UInt32 m_uiFiles;
    CMem      m;
    CFileDisk file;
    SMyArcIndex m_ArcIndex;
};

#endif /* _HRARC_H_ */
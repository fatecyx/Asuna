#ifndef _BMP2G00_H_
#define _BMP2G00_H_

#include <Windows.h>
#include <stdio.h>
#include "my_headers.h"

#pragma pack(push, 1)
#pragma warning(disable:4200)

typedef struct
{
    Char    id;
    UInt16 usWidth;
    UInt16 usHeight;
    Long    uiCompressedSize;   // uiCompressedSize = file_size - 5
    Long    uiUncompressedSize; // uiUncompressedSize = width * height * 4
//    struct { char r, g, b} pixel[usHeight][usWidth];      // [uiCompressedSize - 8];
} TG00Header_0;

typedef struct
{
    RECT    rcRegion;
    UInt32 uiOriginX, uiOriginY;
} TRegion;

typedef struct
{
    Char     id;
    UInt16  usWidth;
    UInt16  usHeight;
    UInt32  uiRegionCount;
    TRegion  Region[1];
} TG00Header_2;

typedef struct
{
    UInt32 uiOffset;
    UInt32 uiSize;
} TBlockIndex;

typedef struct
{
    UInt32  uiCompressedSize;       // file_size - above
    UInt32  uiUncompressedSize;     // each block size (no 0xFF) + block indexes size
    UInt32  uiBlockCount;           // always == RegionCount ?
    TBlockIndex BlockIndex[1];
} TBlockHeader;

typedef struct
{
//    UInt16 unknown; // always == 1 ?
//    UInt16 usPartCount;
    UInt32 uiUnknownAndPartCount;
    UInt32 uiBlockX;
    UInt32 uiBlockY;
    UInt32 uiBlockWidth;
    UInt32 uiBlockHeight;
    UInt32 uiOriginX;
    UInt32 uiOriginY;
    UInt32 uiSthWidth;     // == BlockWidth
    UInt32 uiSthHeight;    // == BlockHeight
    Byte  zero[80];
//  PartData[usPartCount]
} TBlockDataHeader;

typedef struct
{
    UInt16 usPartX;    // the part is copied to (part_x + regions[block].x1,
    UInt16 usPartY;    //                        part_y + regions[block].y1)
    UInt16 usTrans;    // whether to use the part's mask when the G00 is used as an object?
    UInt16 usPartWidth;
    UInt16 usPartHeight;
    UInt16 unknown;    // = 0
    Byte  zero[80];
//  struct { char r, g, b, a } pixel[PartHeight][PartWidth]
} TPartDataHeader;

typedef struct
{
    UInt32 uiBlockX;
    UInt32 uiBlockY;
    UInt32 uiBlockWidth;
    UInt32 uiBlockHeight;
    UInt32 uiOriginX;
    UInt32 uiOriginY;
    UInt32 uiSthWidth;     // == BlockWidth
    UInt32 uiSthHeight;    // == BlockHeight
    Byte  zero[80];
    //  PartData[usPartCount]
} TCustomBlockDataHeader;

typedef struct
{
    UInt32 uiBlockX;
    UInt32 uiBlockY;
    UInt32 uiBlockWidth;
    UInt32 uiBlockHeight;
    UInt32 uiOriginX;
    UInt32 uiOriginY;
    UInt32 uiSthWidth;     // == BlockWidth
    UInt32 uiSthHeight;    // == BlockHeight
} TMyBlockDataHeader;

typedef struct
{
    TG00Header_2       h;
    TRegion           *pRegion;
    TBlockDataHeader  *pBlock;
} TMyRegion;

#pragma warning(default:4200)
#pragma pack(pop)

class G00
{
public:
    G00();
    G00(Char *szFileName);
    G00(Char *pData, UInt32 uiInputBufferSize);
    ~G00();

public:
    BOOL    Open(Char *szFileName);

    // pData point to the Bitmap RAW data and uiInputBufferSize is the RAW data size
    BOOL    Open(Char *pData, SBitMapHeader *pBitMapHeader, UInt32 uiInputBufferSize);
    BOOL    Open(Char *pData, UInt32 uiInputBufferSize);    // pData point to a Bitmap file
    void    Close();
    UInt32 ConvertToG00(Char *szFileName);
    UInt32 ConvertToG00(Char **ppOutBuffer);
    void    FreeBuffer(Char *pBuffer);
    void    SetRegionInfo(TMyRegion *pMyRegionInfo, UInt32 uiRegionSize);

private:
    void    Reset();
    void    Free();
    UInt32 ConvertToG00_0(Char **ppOutBuffer);
    UInt32 ConvertToG00_2(Char **ppOutBuffer);
    Char   *BMPFlipVertical(Char *pDest, Char *pSrc, UInt32 uiWidth, UInt32 uiHeight, UInt32 uiBPP);

private:
    Char   *m_szInFile,   *m_szOutFile;
    Char   *m_pInBuffer,  *m_pOutBuffer, *m_pPartBuffer;
    UInt32 m_uiInBufSize, m_uiOutBufSize, m_uiRegionSize, m_uiPartBufferCount;
    FILE   *m_fInput,     *m_fOutput;
    TMyRegion *m_pMyRegion;
    SBitMapHeader *m_pBitMapHeader;
};

#endif /* _BMP2G00_H_ */
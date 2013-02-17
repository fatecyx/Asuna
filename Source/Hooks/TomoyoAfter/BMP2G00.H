#ifndef _BMP2G00_H_
#define _BMP2G00_H_

#include <Windows.h>
#include <stdio.h>
#include "my_image.h"
#include "my_common.h"

#pragma pack(1)

typedef struct 
{
    char r;
    char g;
    char b;
} TPixel;

typedef struct 
{
    char r;
    char g;
    char b;
    char a;
} TPixelA;

typedef struct
{
    char    id;
    uint_16 usWidth;
    uint_16 usHeight;
    long    uiCompressedSize;   // uiCompressedSize = file_size - 5
    long    uiUncompressedSize; // uiUncompressedSize = width * height * 4
//    TPixel *Pixel;           // [uiCompressedSize - 8];
} TG00Header_0;

typedef struct
{
    RECT    rcRegion;
    uint_32 uiOriginX, uiOriginY;
} TRegion;

typedef struct
{
    uint_16 usLeft, usTop, usRight, usBottom;
    uint_32 uiOriginX, uiOriginY;	// always == 0 ?
} TMyRegion;

typedef struct
{
    char     id;
    uint_16  usWidth;
    uint_16  usHeight;
    uint_32  uiRegionCount;
    TRegion *pRegion;
    uint_32  uiCompressedSize;       // file_size - above
    uint_32  uiUncompressedSize;     // each block size (no 0xFF) + block indexes size
    uint_32  uiBlockCount;           // always == RegionCount ?
} TG00Header_2;

typedef struct
{
    uint_32 uiOffset;
    uint_32 uiSize;
} TBlockIndex;

typedef struct
{
    uint_16 unknown; // always == 1 ?
    uint_16 usPartCount;
    uint_32 uiBlockX;
    uint_32 uiBlockY;
    uint_32 uiBlockWidth;
    uint_32 uiBlockHeight;
    uint_32 uiOriginX;
    uint_32 uiOriginY;
    uint_32 uiSthWidth;     // == BlockWidth
    uint_32 uiSthHeight;    // == BlockHeight
    byte_t  zero[80];
//  PartData[usPartCount]
} TBlockDataHeader;

typedef struct
{
    uint_16 usPartX;    // the part is copied to (part_x + regions[block].x1,
    uint_16 usPartY;    //                        part_y + regions[block].y1)
    uint_16 usTrans;    // whether to use the part's mask when the G00 is used as an object?
    uint_16 usPartWidth;
    uint_16 usPartHeight;
    uint_16 unknown;    // = 0
    byte_t  zero[80];
//  struct { char r, g, b, a } pixel[PartHeight][PartWidth]
} TPartDataHeader;

typedef struct
{
    HGLOBAL hMem;
    PBYTE   pbBitmap;
    DWORD   dwSize;
    DWORD   dwWidth;
    DWORD   dwHieght;
    DWORD   dwG00Type;
} TImageInfo;

#pragma pack()

class G00
{
public:
    G00();
    G00(char *szFileName);
    G00(char *pData, uint_32 uiInputBufferSize);
    ~G00();

public:
    BOOL    Open(char *szFileName);
    BOOL    Open(char *pData, TBitMapHeader *pBitMapHeader, uint_32 uiInputBufferSize);
    BOOL    Open(char *pData, uint_32 uiInputBufferSize);
    void    Close();
    uint_32 ConvertToG00(char *szFileName);     // output file name
    uint_32 ConvertToG00(char **ppOutBuffer);
    void    FreeBuffer(char *pBuffer);
    inline void SetRegionInfo(TMyRegion *pMyRegionInfo, uint_32 uiRegionSize);

private:
    void    Reset();
    void    Free();
    uint_32 ConvertToG00_0(char **ppOutBuffer);
    uint_32 ConvertToG00_2(char **ppOutBuffer);
    char   *BMPFlipVertical(char *pDest, char *pSrc, uint_32 uiWidth, uint_32 uiHeight, uint_32 uiBPP);

private:
    char   *m_szInFile,   *m_szOutFile;
    char   *m_pInBuffer,  *m_pOutBuffer;
    uint_32 m_uiInBufSize, m_uiOutBufSize, m_uiRegionSize;
    HANDLE  m_hHeap;
    TMyRegion *m_pMyRegion;
    TBitMapHeader *m_pBitMapHeader;
};

inline void G00::SetRegionInfo(TMyRegion *pMyRegionInfo, uint_32 uiRegionSize)
{
    m_uiRegionSize = uiRegionSize;
    if (uiRegionSize == 0 || pMyRegionInfo == NULL)
    {
        m_pMyRegion = NULL;
    }
    else
    {
        m_pMyRegion = (TMyRegion *)HeapAlloc(m_hHeap, 0, uiRegionSize);
        if (m_pMyRegion)
        {
            memcpy(m_pMyRegion, pMyRegionInfo, uiRegionSize);
            m_uiRegionSize = uiRegionSize;
        }
        else
        {
            m_uiRegionSize = 0;
        }
    }
}

#endif /* _BMP2G00_H_ */
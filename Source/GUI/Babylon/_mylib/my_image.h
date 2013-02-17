#ifndef _MY_IMAGE_H_
#define _MY_IMAGE_H_

#pragma warning(disable:4201)

#pragma comment(lib, "ucidec.lib")

#include "my_types.h"
#include "my_macros.h"

EXTC_IMPORT int STDCALL UCIDecode(const void *src, int srclen, void** dst, int* stride, int* w, int* h, int* bpp);
EXTC_IMPORT int STDCALL UCIFree(void* p);

#define RGBA(r, g, b, a) (UInt32)(((u32)(u8)(r)) | (((u32)(u8)(g) << 8)) | (((u32)(u8)(b) << 16)) | (((u32)(u8)(a) << 24)))

#pragma pack(push, 1)

typedef struct
{
    UInt16 wTag;                   // 0x00
    UInt32 dwFileSize;             // 0x02
    UInt32 dwReserve;              // 0x06
    UInt32 dwRawOffset;            // 0x0A
    struct
    {
        UInt32 dwInfoHeaderSize;   // 0x0E
        UInt32 dwWidth;            // 0x12
        UInt32 dwHeight;           // 0x16
        UInt16 wLayer;             // 0x1A
        UInt16 wBit;               // 0x1C
        UInt32 dwCompressed;       // 0x1E
        UInt32 dwSizeImage;        // 0x22
        Int32  iXPelsPerMeter;     // 0x26
        Int32  iYPelsPerMeter;     // 0x2A
        UInt32 dwClrUsed;          // 0x2E
        UInt32 dwClrImportant;     // 0x32
    } Info;
} IMG_BITMAP_HEADER, SBitMapHeader, *PBitMapHeader, *LPBitMapHeader;

typedef struct
{
    UChar  ID;
    UChar  byPaletteType;
    UChar  byImageType;
    UInt16 usPaletteEntry;
    UInt16 usPaletteLength;
    UChar  byPaletteBitCount;
    UInt16 usOriginX;
    UInt16 usOriginY;
    UInt16 usWidth;
    UInt16 usHeight;
    UChar  byPixelDepth;
    UChar  byImageDescription;
} IMG_TGA_HEADER, STGAHeader;

typedef struct
{
    union
    {
        LPVoid lpBuffer;
        PByte  pbBuffer;
    };
    Int32  Width;
    Int32  Height;
    Int32  BitsPerPixel;
    Int32  Stride;
    LPVoid lpExtraInfo;
    Int32  ExtraInfoSize;
} UCIInfo, *PUCIInfo, *LPUCIInfo;

#pragma pack(pop)

inline
Bool
FASTCALL
InitBitmapHeader(
    IMG_BITMAP_HEADER  *pHeader,
    Int32               Width,
    Int32               Height,
    Int32               BitsPerPixel,
    PInt32              pStride
)
{    
    Int32 Stride;

    if (pHeader == NULL)
        return False;

    ZeroMemory(pHeader, sizeof(*pHeader));
    pHeader->dwRawOffset = sizeof(*pHeader);
    pHeader->Info.dwHeight = Height;
    pHeader->Info.dwWidth  = Width;
    pHeader->wTag = TAG2('BM');
    pHeader->Info.dwInfoHeaderSize = sizeof(pHeader->Info);
    pHeader->Info.wLayer = 1;
    pHeader->Info.wBit = (UInt16)BitsPerPixel;
//    pHeader->Info.dwClrUsed = 1;
    Stride = (Width * BitsPerPixel / 8 + 3) & ~3;
    if (pStride)
        *pStride = Stride;
    pHeader->dwFileSize = Height * Stride + sizeof(*pHeader);

    return True;
}

inline LPVoid SkipUCIStream(LPVoid lpData, Int32 SrcLength, PInt32 pExtraInfoSize)
{
    PByte pbData = (PByte)lpData;
    UInt32 StreamCount;

    switch (*(PUInt32)pbData)
    {
        case TAG4('UCI3'): StreamCount = 1; break;
        case TAG4('UCI4'): StreamCount = 2; break;
        case TAG4('UCIT'): StreamCount = 3; break;
        case TAG4('UCIQ'): StreamCount = 4; break;
        default: return NULL;
    }

    pbData += 0xC;
    SrcLength -= 0xC;
    while (StreamCount--)
    {
        UInt32 Size = *(PUInt32)pbData + 4;
        pbData += Size;
        SrcLength -= Size;
    }

    if (SrcLength <= 0)
    {
        if (pExtraInfoSize)
           *pExtraInfoSize = 0;
        return NULL;
    }

    if (pExtraInfoSize)
        *pExtraInfoSize = SrcLength;

    return pbData;
}

inline Int32 UCIDecodeEx(LPVoid lpData, Int32 SrcLength, PUCIInfo pUCIInfo, Bool bGetExtraInfo)
{
    Int32 ret;

    if (pUCIInfo == NULL)
        return -1;

    ret = UCIDecode(lpData, SrcLength, &pUCIInfo->lpBuffer, &pUCIInfo->Stride, &pUCIInfo->Width, &pUCIInfo->Height, &pUCIInfo->BitsPerPixel);
    if (ret < 0)
        return ret;

    if (bGetExtraInfo)
        pUCIInfo->lpExtraInfo = SkipUCIStream(lpData, SrcLength, &pUCIInfo->ExtraInfoSize);
    else
    {
        pUCIInfo->lpExtraInfo = NULL;
        pUCIInfo->ExtraInfoSize = 0;
    }

    return ret;
}

inline Void UCIFreeEx(PUCIInfo pUCIInfo)
{
    if (pUCIInfo == NULL)
        return;

    UCIFree(pUCIInfo->lpBuffer);
}

#pragma warning(default:4201)

#endif /* _MY_IMAGE_H_ */
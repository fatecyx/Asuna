#ifndef _IMAGE_H_
#define _IMAGE_H_

//#include "CxImage/CxImage/ximage.h"
#include "my_types.h"
#include "my_image.h"

#pragma pack(1)

typedef struct
{
    union
    {
        PByte  buffer;
        SBitMapHeader *pHeader;
    };
    UInt32 size;
    UInt32 width;
    UInt32 height;
    UInt32 bpp;
} SImageFrame;

typedef struct
{
    UInt32       ImageType;
    UInt32       FrameNum;
    SImageFrame *pFrame;
} SImage;

typedef struct
{
    Byte r, g, b;
} SPixel;

typedef struct
{
    Byte r, g, b, a;
} SPixelA;

#pragma pack()
/*
enum EImageType
{
    IMG_UNKNOWN = CXIMAGE_FORMAT_UNKNOWN, 
    IMG_BMP     = CXIMAGE_FORMAT_BMP, 
    IMG_PNG     = CXIMAGE_FORMAT_PNG, 
    IMG_JPG     = CXIMAGE_FORMAT_JPG, 
    IMG_TGA     = CXIMAGE_FORMAT_TGA, 
    IMG_MNG     = CXIMAGE_FORMAT_MNG, 
};
*/
_MY_C_HEAD_

SImage* STDCALL Decode(PByte pbBuffer, UInt32 uSize);
Void    STDCALL Destroy(SImage *pImage);

_MY_C_TAIL_

#endif /* _IMAGE_H_ */
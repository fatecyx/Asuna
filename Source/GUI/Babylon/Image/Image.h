#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "CxImage/CxImage/ximage.h"
#include "my_common.h"
#include "my_image.h"
#include "upk_common.h"

#if !defined(IMAGE_DECODER_API)
    #define IMAGE_DECODER_API EXTC_IMPORT
#endif

#pragma pack(1)

typedef struct
{
    union
    {
        PByte           Buffer;
        SBitMapHeader  *pHeader;
    };
    UInt32 BufferSize;
    UInt32 Width;
    UInt32 Height;
    UInt32 BitsPerPixel;
} SImageFrame, IMAGE_FRAME;

typedef struct
{
    UInt32       ImageType;
    UInt32       FrameNum;
    SImageFrame *pFrame;
} SImage, IMAGE_INFO;

typedef struct
{
    Byte r, g, b;
} SPixel;

typedef struct
{
    Byte r, g, b, a;
} SPixelA;

#pragma pack()

enum EImageType
{
    IMG_UNKNOWN = CXIMAGE_FORMAT_UNKNOWN, 
    IMG_BMP     = CXIMAGE_FORMAT_BMP, 
    IMG_PNG     = CXIMAGE_FORMAT_PNG, 
    IMG_JPG     = CXIMAGE_FORMAT_JPG, 
    IMG_TGA     = CXIMAGE_FORMAT_TGA, 
    IMG_MNG     = CXIMAGE_FORMAT_MNG, 
};

_MY_C_HEAD_

IMAGE_DECODER_API SImage* STDCALL ImageDecode(PByte pbBuffer, UInt32 uSize);
IMAGE_DECODER_API SImage* STDCALL ImageEncode(PVoid InputBuffer, UInt32 InputSize, UInt32 EncodeType);
IMAGE_DECODER_API Void    STDCALL ImageDestroy(SImage *pImage);

_MY_C_TAIL_

#endif /* _IMAGE_H_ */
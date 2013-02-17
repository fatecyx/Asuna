#pragma comment(linker,"/MERGE:.text=.Amano /SECTION:.Amano,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Amano")
//#pragma comment(linker,"/MERGE:.data=.Amano")

#define IMAGE_DECODER_API EXTC_EXPORT

#include <Windows.h>
#include "Image.h"
#include "my_image.h"

IMAGE_INFO* STDCALL ImageEncode(PVoid InputBuffer, UInt32 InputSize, UInt32 EncodeType)
{
    if (InputBuffer == NULL || InputSize == 0)
        return NULL;

    switch (EncodeType)
    {
        case IMG_BMP:
        case IMG_PNG:
        case IMG_JPG:
        case IMG_TGA:
        case IMG_MNG:
            break;

        default:
            return NULL;
    }

    CxImage     Image;
    PBYTE       OutputBuffer, InBuffer;
    LONG        OutputSize;
    IMAGE_INFO *ImageInfo;

    InBuffer = (PByte)InputBuffer;

    if (!Image.Decode(InBuffer, InputSize, CXIMAGE_FORMAT_UNKNOWN))
        return NULL;

    OutputBuffer = NULL;
    if (!Image.Encode(OutputBuffer, OutputSize, EncodeType))
        return NULL;

    ImageInfo = (IMAGE_INFO *)malloc(sizeof(*ImageInfo));
    if (ImageInfo == NULL)
        return NULL;

    ImageInfo->pFrame = (IMAGE_FRAME *)malloc(sizeof(*ImageInfo->pFrame));
    if (ImageInfo->pFrame == NULL)
    {
        free(ImageInfo);
        return NULL;
    }

    ImageInfo->ImageType            = EncodeType;
    ImageInfo->FrameNum             = 1;
    ImageInfo->pFrame->Buffer       = OutputBuffer;
    ImageInfo->pFrame->BufferSize   = OutputSize;
    ImageInfo->pFrame->BitsPerPixel = 32;
    ImageInfo->pFrame->Height       = Image.GetHeight();
    ImageInfo->pFrame->Width        = Image.GetWidth();

    return ImageInfo;
}

SImage* STDCALL ImageDecode(PByte pbBuffer, UInt32 BufferSize)
{
    if (pbBuffer == 0 || BufferSize == 0)
        return NULL;

    CxImage img;
    SImage *pImage;
    SImageFrame *pFrame;

    if (!img.Decode(pbBuffer, BufferSize, CXIMAGE_FORMAT_UNKNOWN))
        return NULL;
    if (img.GetType() == CXIMAGE_FORMAT_UNKNOWN)
        return NULL;

    pImage = (SImage * )malloc(sizeof(*pImage));
    pImage->FrameNum  = img.GetNumFrames();
    pImage->ImageType = img.GetType();
    if (pImage->FrameNum == 0)
        ++pImage->FrameNum;

    pImage->pFrame = (SImageFrame * )malloc(pImage->FrameNum * sizeof(*pImage->pFrame));
    pFrame = pImage->pFrame;
    for (UInt32 i = 0; ; )
    {
        ZeroMemory(pFrame, sizeof(*pFrame));
        img.Encode(pFrame->Buffer, (Long&)pFrame->BufferSize, CXIMAGE_FORMAT_BMP);
        pFrame->BitsPerPixel    = ((SBitMapHeader *)(pFrame->Buffer))->Info.wBit;
        pFrame->Height          = img.GetHeight();
        pFrame->Width           = img.GetWidth();
        ++pFrame;

        if (++i == pImage->FrameNum)
            break;

        img.SetFrame(i);
        img.Decode(pbBuffer, BufferSize, img.GetType());
    }

    return pImage;
}

Void STDCALL ImageDestroy(SImage *pImage)
{
    IMAGE_FRAME *Frame;

    if (pImage == NULL)
        return;

    Frame = pImage->pFrame;

    for (UInt32 Count = pImage->FrameNum; Count; ++Frame, --Count)
        CxImage::FreeMemory(Frame->Buffer);

    free(pImage);
}
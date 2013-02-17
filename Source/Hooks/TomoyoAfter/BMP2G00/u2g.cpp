#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include <Windows.h>
#include "crt_h.h"
#include "BMP2G00.H"
#include "my_image.h"

Void STDCALL EncodeG00(uchar *pBuffer, uchar *pOut);

Void FORCEINLINE main2(int argc, char **argv)
{
    FILE *fp;
    u32   uiSize, uiG00Size, uiSizeToEncode, uiBlockCount;
    char  szName[MAX_PATH];
    uchar *pBuffer, *pOutBuffer, *pBitmap, *pOut, *pUCI;

    TG00Header_2 *pHeader;
    TBlockHeader *pBlockHeader;
    TMyBlockDataHeader *pBlockData;

    for (u32 i = 1; i != argc; ++i)
    {
        fp = fopen(argv[i], "rb");
        if (fp == NULL)
        {
            perror(argv[i]);
            continue;
        }

        uiSize = fsize(fp);
        pBuffer = new uchar[uiSize];
        if (pBuffer == NULL)
        {
            perror(0);
            fclose(fp);
            continue;
        }

        fread(pBuffer, uiSize, 1, fp);
        fclose(fp);

        pHeader = (TG00Header_2 *)pBuffer;
        if (pHeader->id != 2)
        {
            printf("%s isn't format 2 g00\n", argv[i]);
            delete[] pBuffer;
            continue;
        }

        pBlockData = (TMyBlockDataHeader *)((uchar *)&pHeader->Region[0] +
            pHeader->uiRegionCount * sizeof(TRegion));

        pUCI = NULL;
        uiBlockCount = 0;
        uiG00Size = 12;  // uiCompressedSize, uiUncompressedSize, uiBlockCount
        for (u32 j = 0; j != pHeader->uiRegionCount; ++j)
        {
            if ((*(pu32)&pBlockData[j] & 0xFFFFFF) != 'ICU')
            {
                uiG00Size += sizeof(TBlockDataHeader) + sizeof(TPartDataHeader) + sizeof(TBlockIndex);
                uiG00Size += pBlockData[j].uiBlockWidth * pBlockData[j].uiBlockHeight * 4;
                ++uiBlockCount;
            }
            else
            {
                uiG00Size += sizeof(TBlockIndex) * pHeader->uiRegionCount - j;
                break;
            }
        }

        if (uiBlockCount == 0)
        {
            delete[] pBuffer;
            continue;
        }

        uiSizeToEncode = uiG00Size += uiG00Size / 8;
        uiG00Size +=  (uchar *)pBlockData - pBuffer;    // estimate final size
        pUCI = (uchar *)&pBlockData[uiBlockCount];

        pOutBuffer = new uchar[uiG00Size];
        if (pOutBuffer == NULL)
        {
            delete[] pBuffer;
            continue;
        }

        memset(pOutBuffer, -2, uiG00Size);

        pOut = pOutBuffer;
        memcpy(pOut, pBuffer, (uchar *)pBlockData - pBuffer);   // header & regions
        pOut += (uchar *)pBlockData - pBuffer;      // point to comp_size & uncomp_size
        pBlockHeader = (TBlockHeader *)pOut;

        pBlockHeader->uiBlockCount = pHeader->uiRegionCount;
        pBlockHeader->uiUncompressedSize  = sizeof(TBlockIndex) * pBlockHeader->uiBlockCount + 4; // uiBlockCount
        for (u32 j = uiBlockCount; j != pBlockHeader->uiBlockCount; ++j)
        {
            pBlockHeader->BlockIndex[j].uiOffset = 0;
            pBlockHeader->BlockIndex[j].uiSize   = 0;
        }

        pOut += sizeof(*pBlockHeader->BlockIndex) * pBlockHeader->uiBlockCount + 12;   // uiBlockCount + 2 sizes

        for (u32 j = 0; j != uiBlockCount; ++j)
        {
            s32 stride, w, h, b;
            uchar *pSrc;
            TPartDataHeader  *pPart;
            TBlockDataHeader *pBlock;

            if (pUCI >= pBuffer + uiSize)
            {
                pBlockHeader->BlockIndex[j].uiOffset = 0;
                pBlockHeader->BlockIndex[j].uiSize   = 0;
                continue;
            }
            switch (h = *(LPDWORD)pUCI)
            {
                case '3ICU': h = 1; break;
                case '4ICU': h = 2; break;
                case 'TICU': h = 3; break;
                case 'QICU': h = 4; break;
                case -1:
                    pBlockHeader->BlockIndex[j].uiOffset = 0;
                    pBlockHeader->BlockIndex[j].uiSize   = 0;
                    pUCI += 4;
                    continue;

                default:
                    {
                        pBlockHeader->BlockIndex[j].uiOffset = pBlockHeader->BlockIndex[h].uiOffset;
                        pBlockHeader->BlockIndex[j].uiSize   = pBlockHeader->BlockIndex[h].uiSize;
                        pUCI += 4;
                        continue;
                    }
            }
            pSrc = pUCI;
            pUCI += 0xC;
            while (h--)
                pUCI += *(LPDWORD)pUCI + 4;

            if (UCIDecode(pSrc, pUCI - pSrc, (Void **)&pBitmap, &stride, &w, &h, &b) < 0)
            {
                pBlockHeader->BlockIndex[j].uiOffset = 0;
                pBlockHeader->BlockIndex[j].uiSize   = 0;
                continue;
            }

            pBlock = (TBlockDataHeader *)pOut;
            pBlock->uiUnknownAndPartCount = 0x010001;
            memcpy(&pBlock->uiBlockX, &pBlockData[j], sizeof(*pBlockData));
            memset(pBlock->zero, 0, sizeof(pBlock->zero));

            pOut += sizeof(*pBlock);
            pPart = (TPartDataHeader *)pOut;
            pPart->usPartX      = (uint_16)pBlockData[j].uiBlockX;
            pPart->usPartY      = (uint_16)pBlockData[j].uiBlockY;
            pPart->usTrans      = 1;
            pPart->usPartWidth  = (uint_16)pBlockData[j].uiBlockWidth;
            pPart->usPartHeight = (uint_16)pBlockData[j].uiBlockHeight;
            pPart->unknown      = 0;
            memset(pPart->zero, 0, sizeof(pPart->zero));

            pOut += sizeof(*pPart);

            for (u32 height = 0; height != h; ++height)
            {
                memcpy(pOut, pBitmap + stride * height, stride);
                pOut += stride;
            }
            pBlockHeader->BlockIndex[j].uiOffset = (uchar *)pBlock - (uchar *)pBlockHeader - 8;
            pBlockHeader->BlockIndex[j].uiSize = pOut - (uchar *)pBlock;
            pBlockHeader->uiUncompressedSize += pBlockHeader->BlockIndex[j].uiSize;

            UCIFree(pBitmap);
        }

        uiG00Size = pOut - (uchar *)pBlockHeader;
        uiG00Size += uiG00Size / 8;
        pBlockHeader->uiCompressedSize = uiG00Size;
        uiG00Size += (uchar *)pBlockHeader - pOutBuffer;

        EncodeG00((uchar *)pBlockHeader, pOut);

        strcpy(szName, argv[i]);
        rmext(szName);
        strcat(szName, ".g00");
        printf("Writting to %s\n", szName);
        fp = fopen(szName, "wb");
        if (fp)
        {
            fwrite(pOutBuffer, uiG00Size, 1, fp);
            fclose(fp);
        }
        else
        {
            perror(szName);
        }

        delete[] pOutBuffer;
        delete[] pBuffer;
    }
}

NoInline Void STDCALL EncodeG00(uchar *pBuffer, uchar *pOut)
{
    uchar *pEnd;
    u32 uiSizeToEncode, uiBlockToEncode, uiRemain;

    uiSizeToEncode = pOut - pBuffer;
    uiBlockToEncode = uiSizeToEncode / 8;
    uiRemain = uiSizeToEncode % 8;
    pEnd = pBuffer + uiSizeToEncode + uiBlockToEncode - 1;

    if (uiRemain)
    {
        pEnd -= uiRemain;
        pOut -= uiRemain;
        memcpy(pEnd + 1, pOut, uiRemain);
        *pEnd = -1;
    }

    pEnd -= 9;
    pOut -= 8;
    while (uiBlockToEncode--)
    {
        memcpy(pEnd + 1, pOut, 8);
        if (pEnd >= pOut)
            *pEnd = -1;
        pEnd -= 9;
        pOut -= 8;
    }
}

void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
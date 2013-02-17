#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include <Windows.h>
#include "crt_h.h"
#include "BMP2G00.H"

Void STDCALL EncodeG00(uchar *pBuffer, uchar *pOut, u32 uiG00Size);

void FORCEINLINE main2(int argc, char **argv)
{
    FILE *fp;
    u32   uiSize, uiG00Size, uiSizeToEncode, uiBlockCount, uiBMPSize;
    char  szName[MAX_PATH];
    uchar *pBuffer, *pOutBuffer, *pBitmap, *pOut;

    TG00Header_2 *pHeader;
    TBlockHeader *pBlockHeader;
    TCustomBlockDataHeader *pBlockData;

    for (u32 i = 1; i != argc; ++i)
    {
        fp = fopen(argv[i], "rb");
        if (fp == NULL)
        {
            printf("Can't open \"%s\"\n", argv[i]);
            perror(0);
            continue;
        }

        uiSize = fsize(fp);
        pBuffer = new uchar[uiSize];
        if (pBuffer == NULL)
        {
            printf("Can't allocate memory for input file.\n");
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

        pBlockData = (TCustomBlockDataHeader *)((uchar *)&pHeader->Region[0] +
            pHeader->uiRegionCount * sizeof(TRegion));

        uiBlockCount = min(pHeader->uiRegionCount, (uiSize - ((uchar *)pBlockData - pBuffer)) / sizeof(TCustomBlockDataHeader));
        if (uiBlockCount == 0)
        {
            delete[] pBuffer;
            continue;
        }

        uiG00Size = 12;  // uiCompressedSize, uiUncompressedSize, uiBlockCount
        for (u32 j = 0; j != pHeader->uiRegionCount; ++j)
        {
            if (j < uiBlockCount)
            {
                uiG00Size += sizeof(TBlockDataHeader) + sizeof(TPartDataHeader) + sizeof(TBlockIndex);
                uiG00Size += pBlockData[j].uiBlockWidth * pBlockData[j].uiBlockHeight * 4;
            }
            else
            {
                uiG00Size += sizeof(TBlockIndex);
            }
        }
        uiSizeToEncode = uiG00Size += uiG00Size / 8;
        uiG00Size +=  (uchar *)pBlockData - pBuffer;

        pOutBuffer = new uchar[uiG00Size];
        if (pOutBuffer == NULL)
        {
            delete[] pBuffer;
            continue;
        }

        rmext(argv[i]);

        pOut = pOutBuffer;
        memcpy(pOut, pBuffer, (uchar *)pBlockData - pBuffer);   // header & regions
        pOut += (uchar *)pBlockData - pBuffer;      // point to comp_size & uncomp_size
        pBlockHeader = (TBlockHeader *)pOut;

        pBlockHeader->uiBlockCount = pHeader->uiRegionCount;
        pBlockHeader->uiCompressedSize = uiG00Size - (pOut - pOutBuffer);
        pBlockHeader->BlockIndex[0].uiOffset = sizeof(TBlockIndex) * pHeader->uiRegionCount + 4;
        pBlockHeader->BlockIndex[0].uiSize   = sizeof(TBlockDataHeader) +
                                               sizeof(TPartDataHeader) +
                                               pBlockData[0].uiBlockWidth *
                                               pBlockData[0].uiBlockHeight * 4;
        pBlockHeader->uiUncompressedSize  = sizeof(TBlockIndex) * pBlockHeader->uiBlockCount + 4; // uiBlockCount
        pBlockHeader->uiUncompressedSize += pBlockHeader->BlockIndex[0].uiSize;
        for (u32 j = 1; j != pHeader->uiRegionCount; ++j)
        {
            pBlockHeader->BlockIndex[j].uiSize   = sizeof(TBlockDataHeader) +
                                                   sizeof(TPartDataHeader);
            if (j < uiBlockCount)
            {
                pBlockHeader->BlockIndex[j].uiOffset = pBlockHeader->BlockIndex[j - 1].uiOffset +
                                                       pBlockHeader->BlockIndex[j - 1].uiSize;
                pBlockHeader->BlockIndex[j].uiSize += pBlockData[j].uiBlockWidth * pBlockData[j].uiBlockHeight * 4;
                pBlockHeader->uiUncompressedSize += pBlockHeader->BlockIndex[j].uiSize;
            }
            else
            {
                pBlockHeader->BlockIndex[j].uiOffset = -1;
                pBlockHeader->BlockIndex[j].uiSize   = -1;
            }
        }

        pOut += sizeof(*pBlockHeader->BlockIndex) * pHeader->uiRegionCount + 12;   // uiBlockCount + 2 sizes

        for (u32 j = 0; j != uiBlockCount; ++j)
        {
            u32 stride;
            TPartDataHeader  *pPart;
            TBlockDataHeader *pBlock;
            TBitMapHeader    *h;
            
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
            memset(pOut, 0, pBlockHeader->BlockIndex[j].uiSize);

            sprintf(szName, "%s_%04u.bmp", argv[i], j);
            fp = fopen(szName, "rb");
            if (fp == NULL)
            {
                pOut += pBlockHeader->BlockIndex[j].uiSize;
                printf("Can't open \"%s\"\n", szName);
                continue;
            }

            uiBMPSize = fsize(fp);
            pBitmap = new uchar[uiBMPSize];
            if (pBitmap == NULL)
            {
                pOut += pBlockHeader->BlockIndex[j].uiSize;
                printf("Can't allocate memory for \"%s\"\n", szName);
                fclose(fp);
                continue;
            }

            fread(pBitmap, uiBMPSize, 1, fp);
            fclose(fp);

            h = (TBitMapHeader *)pBitmap;
            pBitmap += h->dwRawOffset;
//            stride = h->Info.dwWidth * h->Info.wBit / 8 + (h->Info.wBit == 24 ? (h->Info.dwWidth & 3) : 0);
            stride = pBlock->uiBlockWidth * 4;
            for (u32 height = h->Info.dwHeight; height; )
            {
                --height;
                memcpy(pOut, pBitmap + stride * height, stride);
                pOut += stride;
            }

            delete[] h;
        }

        EncodeG00((uchar *)pBlockHeader, pOut, uiSizeToEncode);

        sprintf(szName, "%s.g00", argv[i]);
        printf("Writting to %s\n", szName);
        fp = fopen(szName, "wb");
        if (fp)
        {
            fwrite(pOutBuffer, uiG00Size, 1, fp);
            fclose(fp);
        }

        delete[] pOutBuffer;
        delete[] pBuffer;
    }
}

NoInline Void STDCALL EncodeG00(uchar *pBuffer, uchar *pOut, u32 uiSizeToEncode)
{
    uchar *pEnd;
    u32 uiBlockToEncode, uiRemain;

    pEnd = pBuffer + uiSizeToEncode - 1;

    uiSizeToEncode = pOut - pBuffer;
    uiBlockToEncode = uiSizeToEncode / 8;
    uiRemain = uiSizeToEncode % 8;

    if (uiRemain)
    {
        pEnd -= uiRemain;
        pOut -= uiRemain;
        memcpy(pEnd + 1, pOut, uiRemain);
        *pEnd = -1;
    }

    pEnd -= 9;
    pOut -= 8;
    while (uiBlockToEncode-- && pOut > pBuffer)
    {
        memcpy(pEnd + 1, pOut, 8);
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
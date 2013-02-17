#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"
#include "BMP2G00.h"
#include <vector>

using std::vector;

ForceInline void main2(int argc, char **argv)
{
    FILE  *fp;
    u32    uSize, uOutSize, uBlockCount, uMaxBufferSize, uMaxOutputSize;
    uchar *pBuffer, *pOutput, *pWrite;
    char   szName[MAX_PATH];

    TG00Header_2 *pHeader;
    TMyBlockDataHeader     *pMyBlockHeader;
    TCustomBlockDataHeader *pBlockData;

    uMaxOutputSize = 0x3000;
    uMaxBufferSize = 0x3000;
    pBuffer = (uchar *)malloc(uMaxBufferSize);
    pOutput = (uchar *)malloc(uMaxOutputSize);

    for (u32 i = 1; i != argc; ++i)
    {
        fp = fopen(argv[i], "rb");
        if (fp == NULL)
        {
            perror(argv[i]);
            continue;
        }

        uSize = fsize(fp);
        if (uSize > uMaxBufferSize)
        {
            uMaxBufferSize = uSize;
            pBuffer = (uchar *)realloc(pBuffer, uSize);
        }
        fread(pBuffer, uSize, 1, fp);
        fclose(fp);

        pHeader = (TG00Header_2 *)pBuffer;
        pBlockData = (TCustomBlockDataHeader *)(pBuffer + 9 + pHeader->uiRegionCount * sizeof(*pHeader->Region));

        uBlockCount = min(pHeader->uiRegionCount, (uSize - ((uchar *)pBlockData - pBuffer)) / sizeof(TCustomBlockDataHeader));
        uOutSize = 12;  // uiCompressedSize, uiUncompressedSize, uiBlockCount
        for (u32 j = 0; j != pHeader->uiRegionCount; ++j)
        {
            if (j < uBlockCount)
            {
                uOutSize += sizeof(TBlockDataHeader) + sizeof(TPartDataHeader) + sizeof(TBlockIndex);
                uOutSize += pBlockData[j].uiBlockWidth * pBlockData[j].uiBlockHeight * 4;
            }
            else
            {
                uOutSize += sizeof(TBlockIndex);
            }
        }
        uOutSize += uOutSize / 8;
        uOutSize +=  (uchar *)pBlockData - pBuffer;

        if (uOutSize > uMaxOutputSize)
        {
            uMaxOutputSize = uOutSize;
            pOutput = (uchar *)realloc(pOutput, uOutSize);
        }

        pWrite = pOutput;
        memcpy(pWrite, pBuffer, 9 + pHeader->uiRegionCount * sizeof(*pHeader->Region));
        pWrite += 9 + pHeader->uiRegionCount * sizeof(*pHeader->Region);

        pMyBlockHeader = (TMyBlockDataHeader *)pWrite;
        for (u32 j = 0; j != uBlockCount; ++j)
        {
            memcpy(&pMyBlockHeader[j], &pBlockData[j], sizeof(*pMyBlockHeader));
        }
        
        Bool bSingleFrame;
        vector<u32> vec_size;
        vector<uchar*> vec_point;

        rmext(argv[i]);
        bSingleFrame = False;
        pWrite += sizeof(*pMyBlockHeader) * uBlockCount;
        for (u32 j = 0; j != uBlockCount && bSingleFrame == False; ++j)
        {
            u32 k;

            if (j == 0)
            {
                sprintf(szName, "%s.uci", argv[i]);
                fp = fopen(szName, "rb");
                if (fp)
                    bSingleFrame = True;
            }

            if (bSingleFrame == False)
            {
                sprintf(szName, "%s_%04u.uci", argv[i], j);
                fp = fopen(szName, "rb");
                if (fp == NULL)
                {
                    *(pu32)pWrite = -1;
                    pWrite += 4;
                    vec_size.push_back(0);
                    vec_point.push_back(0);
                    perror(szName);
                    continue;
                }
            }

            uSize = fsize(fp);
            if (uSize > uMaxBufferSize)
            {
                uMaxBufferSize = uSize;
                pBuffer = (uchar *)realloc(pBuffer, uSize);
            }
            fread(pBuffer, uSize, 1, fp);
            fclose(fp);

            for (k = 0; k != vec_size.size(); ++k)
            {
                if (uSize == vec_size[k] && !memcmp(vec_point[k], pBuffer, vec_size[k]))
                    {
                        *(pu32)pWrite = k;
                        pWrite += 4;
                        vec_size.push_back(vec_size[k]);
                        vec_point.push_back(vec_point[k]);
                        break;
                    }
            }
            if (k != vec_size.size())
                continue;

            vec_size.push_back(uSize);
            vec_point.push_back(pWrite);
            memcpy(pWrite, pBuffer, uSize);
            pWrite += uSize;
        }
        sprintf(szName, "%s.u00", argv[i]);
        fp = fopen(szName, "wb");
        if (fp == NULL)
        {
            perror(szName);
            continue;
        }
        fwrite(pOutput, pWrite - pOutput, 1, fp);
        fclose(fp);
    }

    free(pBuffer);
    free(pOutput);
}

void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
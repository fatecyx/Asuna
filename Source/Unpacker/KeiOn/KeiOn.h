#ifndef _KEION_H_
#define _KEION_H_

// ·ÅÕnááÝXÒô!¥¯¥é

#include "upk_common.h"
#include "my_api.h"
#include "my_image.h"

typedef struct
{
    UInt32 Offset;
    UInt32 bLow4Bits;
    UInt32 v2;
} SKeionDecompressInfo;

class CKeion : public CUnpakerBase
{
public:
    Void Auto(PCWChar pszFileName)
    {
        UInt Attributes = GetFileAttributesW(pszFileName);

        if (Attributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            WChar (*pszFileList)[MAX_PATH];
            Large_Integer FileCount;

            if (GetDirectoryFiles((LPVoid *)&pszFileList, L"*.*", sizeof(*pszFileList), NULL, &FileCount, CallBack, NULL) == False)
                return;

            for (UInt i = 0; i != FileCount.LowPart; ++i)
            {
                wprintf(L"Decompressing \"%s\" ... ", pszFileList[i]);
                printf("%s\n", DecompressFile(pszFileList[i]) ? "OK" : "failed");
            }

            FreeFileList(pszFileList);
        }
        else
        {
            wprintf(L"Decompressing \"%s\" ... ", pszFileName);
            printf("%s\n", DecompressFile(pszFileName) ? "OK" : "failed");
        }
    }

    UInt32 DecompressFile(PCWChar pszFileName)
    {
        UInt32 SizeCompressed, SizeUncompressed, SizeReturn;
        PByte pbCompressed, pbUncompressed;
        WChar szFile[MAX_PATH];

        if (file.Open(pszFileName) == False)
            return 0;

        SizeCompressed = file.GetSize();
        pbCompressed = (PByte)Alloc(SizeCompressed);
        if (pbCompressed == NULL)
            return 0;

        if (file.Read(pbCompressed) == False)
        {
            Free(pbCompressed);
            return 0;
        }

        pbUncompressed = NULL;
        SizeUncompressed = Decompress(pbCompressed, SizeCompressed, (LPVoid *)&pbUncompressed);
        Free(pbCompressed);
        if (SizeUncompressed == 0)
        {
            Free(pbUncompressed);
            return 0;
        }

        lstrcpyW(szFile, pszFileName);
        lstrcpyW(findextw(szFile), L".bmp");

        SizeReturn = 0;
        do
        {
            if (file.Open(szFile, file.WRITE, file.NEW) == False)
                break;
            if (file.Write(pbUncompressed, SizeUncompressed) == False)
                break;

            SizeReturn = SizeUncompressed;

        } while (0);

        Free(pbUncompressed);

        return SizeReturn;
    }

protected:
    UInt32 Decompress(LPVoid lpBufferCompressed, UInt32 BufferSize, LPVoid *ppBufferUncompressed)
    {
        if (lpBufferCompressed == NULL)
            return 0;
        if (ppBufferUncompressed == NULL)
            return 0;

        PByte pbBuffer, pbBitmap, pbEnd, pbEndBitmap;
        SBitMapHeader *pHeader;
        UInt32 BitmapSize, LoopCount, LoopTable[] = { 9, 4, 7, 2, 6, 8, 3, 5 };

        *ppBufferUncompressed = NULL;

        pbBuffer = (PByte)lpBufferCompressed;
        pHeader  = (SBitMapHeader *)lpBufferCompressed;
        if (*(PUInt16)pbBuffer != TAG2('BM'))
            return 0;

        BitmapSize = pHeader->dwFileSize;
        pbBitmap = (PByte)Alloc(BitmapSize + 1);
        if (pbBitmap == NULL)
            return NULL;

        *ppBufferUncompressed = pbBitmap;
        *(SBitMapHeader *)pbBitmap = *pHeader;
        pbBitmap += sizeof(*pHeader);

        m_info.bLow4Bits = False;

        pbEnd = pbBuffer + BufferSize;
        pbBuffer += sizeof(*pHeader);
        pbEndBitmap = pbBitmap + BitmapSize;
        while (pbBuffer < pbEnd)
        {
            LoopCount = Get4Bits(pbBuffer);
            if (LoopCount & 8)
            {
                LoopCount = LoopTable[LoopCount % countof(LoopTable)];
                while (LoopCount-- && pbBitmap < pbEndBitmap)
                {
                    *(PUInt32)pbBitmap = Decompress3Byte(pbBuffer);
                    pbBitmap += 3;
                }
            }
            else
            {
                UInt32 redundancy = Decompress3Byte(pbBuffer);
                LoopCount = LoopTable[LoopCount % countof(LoopTable)];
                while (LoopCount-- && pbBitmap < pbEndBitmap)
                {
                    *(PUInt32)pbBitmap = redundancy;
                    pbBitmap += 3;
                }
            }
        }

        return BitmapSize;
    }

    UInt32 Decompress3Byte(PByte &pbCompressed)
    {
        PByte pbBuffer;
        Byte by[3];

        pbBuffer = pbCompressed;

        for (UInt i = 0; i != countof(by); ++i)
        {
            by[i] = Get4Bits(pbBuffer) << 4;
            by[i] |= Get4Bits(pbBuffer) & 0xF;
        }

        pbCompressed = pbBuffer;
        return by[0] | ((UInt32)by[1] << 8) | ((UInt32)by[2] << 16);
    }

    UInt32 Get4Bits(PByte &pbBuffer)
    {
        UInt32 Bits;

        Bits = *pbBuffer;
        if (m_info.bLow4Bits == False)
            Bits >>= 4;

        pbBuffer += m_info.bLow4Bits;
        m_info.bLow4Bits ^= True;

        return (Byte)Bits;
    }

    static Int32 STDCALL CallBack(LPVoid lpBuffer, LPWIN32_FIND_DATAW pwfd, LPVoid lpParam)
    {
        lstrcpyW((LPWSTR)lpBuffer, pwfd->cFileName);
        return 1;
    }

protected:
    Bool  InitIndex(LPVoid lpIndex, UInt32 uSize);
    Void  Release();

protected:
    CFileDisk file;
    SKeionDecompressInfo m_info;
};

#endif /* _KEION_H_ */
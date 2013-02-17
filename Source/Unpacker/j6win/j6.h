#ifndef _J6_H_
#define _J6_H_

#include "my_headers.h"
#include "gal_common.h"

#pragma pack(1)

typedef struct
{
    Char   FileName[14];
    UInt32 Offset;
    UInt32 Size;
} SJ6List;

typedef struct
{
    UInt32 CompressedSize;
    UInt32 UncompressedSize;
    Byte   Data[1];
} SJ6CompessedFile;

#pragma pack()

class CJ6Unpacker : public CUnpackerTmpl<CJ6Unpacker>
{
protected:
    CFileDisk m_file;

public:
    Bool Open(PCWChar pszFileName)
    {
        WChar szFile[MAX_PATH];
        SJ6List *pFileList;
        UInt32 ListSize;
        SMyCommonFileEntry *pEntry;

        lstrcpyW(szFile, pszFileName);
        pszFileName = findextw(szFile) + 1;

        *(PUInt64)pszFileName = TAG3W('lst');
        if (!m_file.Open(szFile))
            return False;

        ListSize = m_file.GetSize();

        m_Index.cbEntrySize = sizeof(*m_Index.pEntry);
        m_Index.FileCount = ListSize / sizeof(*pFileList) - 1;
        m_Index.pEntry = (SMyCommonFileEntry *)Alloc((UInt32)m_Index.FileCount * m_Index.cbEntrySize);
        if (m_Index.pEntry == NULL)
            return False;

        pFileList = (SJ6List *)Alloc(ListSize);
        if (pFileList == NULL)
            return False;

        m_file.Read(pFileList);

        *(PUInt64)pszFileName = TAG3W('dat');
        if (!m_file.Open(szFile))
        {
            Free(pFileList);
            return False;
        }

        pEntry = m_Index.pEntry;
        for (UInt32 i = 0; i != (UInt32)m_Index.FileCount; ++i)
        {
            PChar pFileName = pFileList[i].FileName;
            MultiByteToWideChar(
                IsShiftJISString(pFileName, sizeof(pFileList->FileName)) ? CP_SHIFTJIS : CP_GB2312,
                0,
                pFileName,
                sizeof(pFileList->FileName),
                pEntry->FileName,
                MAX_PATH);

            pEntry->Offset.QuadPart = pFileList[i].Offset;
            pEntry->Size.QuadPart = pFileList[i].Size;
            pEntry->Flags = 0;
            ++pEntry;
        }

        Free(pFileList);

        return True;
    }

    Bool GetFileData(SFileInfo *pFileInfo, const SMyCommonFileEntry *pEntry)
    {
        Bool   Result;
        PByte  pbBuffer;
        PVoid  pvFileBuffer;
        PWChar pszExtension;
        UInt32 FileSize;
        Large_Integer Offset;

        Offset = pEntry->Offset;
        if (!m_file.Seek(m_file.FILE_SEEK_BEGIN, Offset.LowPart, &Offset.HighPart))
            return False;

        pbBuffer = (PByte)Alloc(pEntry->Size.LowPart);
        if (pbBuffer == NULL)
            return False;

        if (!m_file.Read(pbBuffer, pEntry->Size.LowPart))
        {
            Free(pbBuffer);
            return False;
        }

        pszExtension = findextw(pEntry->FileName);
        if (!StrICmpW(pszExtension, L".SO4"))
        {
            Result = UncompressSO4(pbBuffer, pEntry->Size.LowPart, &pvFileBuffer, &FileSize);
            Free(pbBuffer);
            if (!Result)
                return False;
        }
        else
        {
            pvFileBuffer = pbBuffer;
            FileSize = pEntry->Size.LowPart;
        }
/*
        pszExtension = findextw(pEntry->FileName);
        if (*(UInt32)(pbBuffer + 4) == TAG4('RIFF'))
        {
            pvFileBuffer = pbBuffer;
            FileSize = pEntry->Size.LowPart;
        }
        else if (!StrICmpW(pszExtension, L".SO4"))
        {
            Result = UncompressSO4(pbBuffer, pEntry->Size.LowPart, &pvFileBuffer, &FileSize);
            Free(pbBuffer);
            if (!Result)
                return False;
        }
        else if (!StrICmpW(pszExtension, L".PT1"))
        {
            ;
        }
        else
        {
            printf("dbg\n");
            getch();
        }
*/
        pFileInfo->FileType = UNPACKER_FILE_TYPE_BIN;
        pFileInfo->BinData.pbBuffer = (PByte)pvFileBuffer;
        pFileInfo->BinData.BufferSize = FileSize;
        pFileInfo->lpExtraData = NULL;

        return True;
    }

protected:
    Bool UncompressSO4(PVoid pvInput, UInt32 InSize, PVoid *ppvOutput, PUInt32 pOutSize)
    {
        Bool  Result;
        PVoid pvOutput;
        SJ6CompessedFile *pCompFile;

        *ppvOutput = NULL;
        *pOutSize = 0;

        pCompFile = (SJ6CompessedFile *)pvInput;

        pvOutput = Alloc(pCompFile->UncompressedSize);
        if (pvOutput == NULL)
            return False;

        Result = UncompressSO4Worker(pCompFile, InSize, pvOutput, pCompFile->UncompressedSize);
        if (!Result)
        {
            Free(pvOutput);
        }
        else
        {
            *ppvOutput = pvOutput;
            *pOutSize  = pCompFile->UncompressedSize;
        }

        return Result;
    }

    Void InitDictionary(PByte pbDict)
    {
        for (UInt32 i = 0; i != 256; ++i)
        {
            memset(pbDict, i, 0xD);
            pbDict += 0xD;
        }

        for (UInt32 i = 0; i != 256; ++i)
            *pbDict++ = i;
        for (UInt32 i = 256; i--;)
            *pbDict++ = i;

        ZeroMemory(pbDict, 0x80);
        pbDict += 0x80;
        memset(pbDict, ' ', 0x6E);
        pbDict += 0x6E;
        ZeroMemory(pbDict, 0x12);
    }

    Bool UncompressSO4Worker(SJ6CompessedFile *pCompFile, UInt32 InSize, PVoid pvOutput, UInt32 OutSize)
    {
        Byte   Dict[0x1000];
        PByte  pbInput, pbEnd, pbOutput;
        UInt32 DictCursor;

        pbInput = pCompFile->Data;
        pbOutput = (PByte)pvOutput;
        pbEnd = pbOutput + pCompFile->UncompressedSize;

        InitDictionary(Dict);

        DictCursor = 0xFEE;
        while (pbOutput < pbEnd)
        {
            Byte Flag = *pbInput++;
            for (Int32 i = 8; i && pbOutput < pbEnd; --i)
            {
                if (Flag & 1)
                {
                    Dict[DictCursor++] = *pbOutput++ = *pbInput++;
                    DictCursor &= 0xFFF;
                }
                else
                {
                    Word a;
                    UInt32 Length;

                    a = *(PWord)pbInput;
                    pbInput += 2;

                    Length = (HIBYTE(a) & 0xF) + 3;
                    if (pbOutput > pbEnd || pbOutput + Length > pbEnd)
                        break;

                    a = MAKEWORD(LOBYTE(a), HIBYTE(a) >> 4);

                    do
                    {
                        Byte by;

                        by = Dict[a++];
                        Dict[DictCursor++] = by;
                        *pbOutput++ = by;
                        a &= 0xFFF;
                        DictCursor &= 0xFFF;

                    } while (--Length);
                }

                Flag >>= 1;
            }
        }

        return True;
    }
};

#endif /* _J6_H_ */
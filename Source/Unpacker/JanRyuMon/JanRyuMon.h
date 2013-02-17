#ifndef _JANRYUMON_H_
#define _JANRYUMON_H_

#include "pragma_once.h"
#include "my_headers.h"
#include "gal_common.h"
#include "zlib/zlib.h"

#pragma pack(1)

typedef struct
{
    UInt32 Magic;       // TAG4('RES1')
    UInt32 Type;        // 2 <= x <= 5
    UInt32 Flags;       // 0 or 1
    UInt32 IndexOffset;
    UInt32 CompressedIndexSize;
    UInt32 EntryCount;
} JANRYUMON_ROM_HEADER;

typedef struct
{
    WChar  FileName[256];
    UInt32 Offset;
    UInt32 CompressedSize;
    UInt32 UncompressedSize;
    UInt32 Unknown1;
    UInt32 Unknown2;
    Bool   fCompressed;
} JANRYUMON_ROM_ENTRY_V3, JANRYUMON_ROM_ENTRY_V4;

struct JANRYUMON_ROM_ENTRY_V5 : public JANRYUMON_ROM_ENTRY_V4
{
    UInt32 Key;
};

struct MY_JANRYUMON_ROM_ENTRY : public MY_FILE_ENTRY_BASE
{
    UInt32 CompressedSize;
    UInt32 Key;
};

#pragma pack()

class CJanryumon : public CUnpackerImpl<CJanryumon>
{
protected:
    CFileDisk m_file;

public:
    Bool Open(PCWChar pszFileName)
    {
        JANRYUMON_ROM_HEADER header;

        if (!m_file.Open(pszFileName))
            return False;

        if (!m_file.Read(&header, sizeof(header)))
            return False;

        if (header.Magic != TAG4('RES1') ||
            header.Type < 1 ||
            header.Type > 5 ||
            !TEST_BITS(header.Flags, 1))
        {
            return False;
        }

        return InitIndex(&header);
    }

    Bool GetFileData(SFileInfo *pFileInfo, const MY_FILE_ENTRY_BASE *pEntry)
    {
        Int Result;
        PByte pbBuffer, pbCompressed;
        MY_JANRYUMON_ROM_ENTRY *pMyEntry = (MY_JANRYUMON_ROM_ENTRY *)pEntry;

        if (!m_file.Seek(m_file.FILE_SEEK_BEGIN, pMyEntry->Offset.LowPart))
            return False;

        pbBuffer = (PByte)Alloc(pMyEntry->Size.LowPart);
        if (pbBuffer == NULL)
            return False;

        if (TEST_BITS(pMyEntry->Flags, UNPACKER_ENTRY_FLAG_COMPRESSED))
        {
            pbCompressed = (PByte)Alloc(pMyEntry->CompressedSize);
            if (pbCompressed == NULL)
            {
                Free(pbBuffer);
                return False;
            }
        }
        else
        {
            pbCompressed = pbBuffer;
        }

        if (!m_file.Read(pbCompressed, pMyEntry->CompressedSize))
        {
            if (pbCompressed != pbBuffer)
                Free(pbCompressed);

            Free(pbBuffer);
            return False;
        }

        Decrypt(pbCompressed, pMyEntry->CompressedSize, pMyEntry->Key);

        pFileInfo->BinData.BufferSize = pMyEntry->Size.LowPart;

        if (TEST_BITS(pMyEntry->Flags, UNPACKER_ENTRY_FLAG_COMPRESSED))
        {
            Result = uncompress(pbBuffer, (PULong)&pFileInfo->BinData.BufferSize, pbCompressed, pMyEntry->CompressedSize);
            Free(pbCompressed);
            if (Result != Z_OK)
            {
                Free(pbBuffer);
                return False;
            }
        }

        pFileInfo->FileType = UNPACKER_FILE_TYPE_BIN;
        pFileInfo->BinData.pbBuffer = pbBuffer;

        return True;
    }

protected:
    Bool InitIndex(JANRYUMON_ROM_HEADER *pHeader)
    {
        Bool  Result, bHaveKey;
        SizeT EntrySize, OneEntrySize;
        PByte pbCompressedIndex;
        union
        {
            JANRYUMON_ROM_ENTRY_V3 *pRomEntryBase3;
            JANRYUMON_ROM_ENTRY_V4 *pRomEntryBase4;
            JANRYUMON_ROM_ENTRY_V5 *pRomEntryBase5;
        };
        MY_JANRYUMON_ROM_ENTRY *pEntry;

        switch (pHeader->Type)
        {
            case 3:
            case 4:
                bHaveKey = False;
                OneEntrySize = sizeof(*pRomEntryBase4);
                break;

            case 5:
                bHaveKey = True;
                OneEntrySize = sizeof(*pRomEntryBase5);
                break;

            default:
                return False;
        }

        pEntry = (MY_JANRYUMON_ROM_ENTRY *)Alloc(pHeader->EntryCount * sizeof(*pEntry));
        if (pEntry == NULL)
            return False;

        m_Index.pEntry = pEntry;

        pbCompressedIndex = (PByte)Alloc(pHeader->CompressedIndexSize);
        if (pbCompressedIndex == NULL)
            return False;

        EntrySize = pHeader->EntryCount * OneEntrySize;
        pRomEntryBase5 = (JANRYUMON_ROM_ENTRY_V5 *)Alloc(EntrySize);
        if (pRomEntryBase5 == NULL)
        {
            Free(pbCompressedIndex);
            return False;
        }

        Result = False;

        LOOP_ONCE
        {
            if (!m_file.Seek(m_file.FILE_SEEK_BEGIN, pHeader->IndexOffset))
                break;

            if (!m_file.Read(pbCompressedIndex, pHeader->CompressedIndexSize))
                break;

            if (uncompress((PByte)pRomEntryBase5, (PULong)&EntrySize, pbCompressedIndex, pHeader->CompressedIndexSize) != Z_OK)
                break;

            JANRYUMON_ROM_ENTRY_V5 *pRomEntry;
            pRomEntry = pRomEntryBase5;
            for (UInt32 FileNum = pHeader->EntryCount; FileNum; --FileNum)
            {
                pEntry->Flags           = pRomEntry->fCompressed ? UNPACKER_ENTRY_FLAG_COMPRESSED : 0;
                pEntry->Key             = bHaveKey ? pRomEntry->Key : 0;
                pEntry->Size.QuadPart   = pRomEntry->UncompressedSize;
                pEntry->Offset.QuadPart = pRomEntry->Offset;
                pEntry->CompressedSize  = pRomEntry->CompressedSize;
                lstrcpyW(pEntry->FileName, pRomEntry->FileName);

                ++pEntry;
                pRomEntry = (JANRYUMON_ROM_ENTRY_V5 *)((ULong_Ptr)pRomEntry + OneEntrySize);
            }

            m_Index.FileCount.QuadPart = pHeader->EntryCount;
            m_Index.cbEntrySize = sizeof(*pEntry);

            Result = True;
        }

        Free(pRomEntryBase5);
        Free(pbCompressedIndex);

        return Result;
    }

    Void Decrypt(PVoid pvBuffer, SizeT Size, UInt32 Key)
    {
        PByte pbBuffer;

        if (Key == 0)
            return;

        pbBuffer = (PByte)pvBuffer;
        Key = (Byte)(Key ^ (Key >> 8) ^ (Key >> 16) ^ (Key >> 24));
        Key = (Key) | (Key << 8);
        Key = (Key) | (Key << 16);
        while (Size & 3)
        {
            *pbBuffer++ ^= Key;
            --Size;
        }

        Size /= 4;
        while (Size--)
        {
            *(PUInt32)pbBuffer ^= Key;
            pbBuffer += 4;
        }
    }
};

#endif // _JANRYUMON_H_
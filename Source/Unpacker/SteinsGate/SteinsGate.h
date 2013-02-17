// N2System

#ifndef _STEINSGATE_H_
#define _STEINSGATE_H_

#include "pragma_once.h"
#include <Windows.h>
#include "my_headers.h"
#include "gal_common.h"

#define STEINS_GATE_KEY TAG8('BUCK', 'TICK')

#pragma pack(1)

typedef struct
{
    UInt32          NameLength;
    Char            FileName[1];
    UInt32          Size;
    Large_Integer   Offset;
} NPA_INDEX_ENTRY;

typedef struct
{
    UInt32 FileCount;
    NPA_INDEX_ENTRY Entry[1];
} NPA_INDEX;

typedef struct
{
    UInt32      IndexSize;
    NPA_INDEX   Index;
} NPA_HEADER;

#pragma pack()

class CSteinsGate : public CUnpackerImpl<CSteinsGate>
{
protected:
    CNtFileDisk m_file;

public:
    DEFINE_AUTO_METHOD();

    Bool Open(PCWChar pszFileName)
    {
        Bool   Result;
        UInt32 IndexSize;
        PByte  pbIndex;

        if (!NT_SUCCESS(m_file.Open(pszFileName)))
            return False;

        if (!NT_SUCCESS(m_file.Read(&IndexSize, 4)))
            return False;

        pbIndex = (PByte)Alloc(IndexSize);
        if (pbIndex == NULL)
            return False;

        if (!NT_SUCCESS(m_file.Read(pbIndex, IndexSize)))
        {
            Free(pbIndex);
            return False;
        }

        Decrypt(pbIndex, IndexSize);
        Result = InitIndex(pbIndex, IndexSize);
        Free(pbIndex);

        return Result;
    }

    Bool GetFileData(SFileInfo *pFileInfo, const MY_FILE_ENTRY_BASE *pEntry, BOOL)
    {
        PByte pbBuffer;
        Large_Integer Offset;

        Offset = pEntry->Offset;
        if (!NT_SUCCESS(m_file.Seek(Offset.QuadPart, FILE_BEGIN)))
            return False;

        pbBuffer = (PByte)Alloc(pEntry->Size.LowPart);
        if (pbBuffer == NULL)
            return False;

        if (!NT_SUCCESS(m_file.Read(pbBuffer, pEntry->Size.LowPart)))
        {
            Free(pbBuffer);
            return False;
        }

        Decrypt(pbBuffer, pEntry->Size.LowPart);

        pFileInfo->BinData.BufferSize = pEntry->Size.LowPart;
        pFileInfo->FileType = UNPACKER_FILE_TYPE_BIN;
        pFileInfo->BinData.pbBuffer = pbBuffer;

        return True;
    }

protected:
    Bool InitIndex(PByte pbIndex, UInt32 IndexSize)
    {
        NPA_INDEX           *pIndex;
        NPA_INDEX_ENTRY     *pEntry;
        MY_FILE_ENTRY_BASE  *pMyEntry;

        UNUSED_VARIABLE(IndexSize);
        pIndex = (NPA_INDEX *)pbIndex;
        pEntry = pIndex->Entry;

        m_Index.FileCount.QuadPart = pIndex->FileCount;
        m_Index.pEntry = (MY_FILE_ENTRY_BASE *)Alloc(m_Index.FileCount.QuadPart * m_Index.cbEntrySize);
        if (m_Index.pEntry == NULL)
            return False;

        pbIndex  = (PByte)pEntry;
        pMyEntry = m_Index.pEntry;
        for (UInt32 Count = m_Index.FileCount.QuadPart; Count; ++pMyEntry, --Count)
        {
            UInt32 FileNameLength, nChar;

            pMyEntry->Flags = 0;
            FileNameLength = *(PUInt32)pbIndex;
            pbIndex += 4;
            nChar = MultiByteToWideChar(
                        IsShiftJISString((PCChar)pbIndex, FileNameLength) ? CP_SHIFTJIS : CP_ACP,
                        0,
                        (LPCSTR)pbIndex,
                        FileNameLength,
                        pMyEntry->FileName,
                        countof(pMyEntry->FileName));

            pMyEntry->FileName[nChar] = 0;
            pbIndex += FileNameLength;
            pMyEntry->Size.QuadPart = *(PUInt32)pbIndex;
            pbIndex += 4;
            pMyEntry->Offset.QuadPart = *(PUInt64)pbIndex;
            pbIndex += 8;
        }
        
        return True;
    }

    Void Decrypt(PByte pbBuffer, UInt32 Size)
    {
        Byte    Buffer[sizeof(STEINS_GATE_KEY)];
        UInt64  Key;

        Key = ~STEINS_GATE_KEY;
        for (UInt32 AlignedSize = AlignedSize = Size / sizeof(STEINS_GATE_KEY); AlignedSize; --AlignedSize)
        {
            *(PUInt64)pbBuffer ^= Key;
            pbBuffer += sizeof(STEINS_GATE_KEY);
        }

        Size %= sizeof(STEINS_GATE_KEY);
        if (Size != 0)
        {
            CopyMemory(Buffer, pbBuffer, Size);
            *(PUInt64)Buffer ^= Key;
            CopyMemory(pbBuffer, Buffer, Size);
        }
    }
};

#endif // _STEINSGATE_H_
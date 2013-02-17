#include <Windows.h>
#include "Sharu.h"

Bool CSharu::Open(PCWChar pszFileName)
{
    ReleaseAll();

    if (file.Open(pszFileName) == False)
        return False;

    Bool ret;
    UInt32 Version, Key;
    SPackHeader header;
    SPackHashTableHeader *pHashTable;
    static Char Seed[] = "8hr48uky,8ugi8ewra4g8d5vbf5hb5s6";

    UNREFERENCED_PARAMETER(pHashTable);

    if (file.Seek(file.FILE_SEEK_END, -(Long)sizeof(header)) == False)
        return False;

    if (file.Read(&header, sizeof(header)) == False)
        return False;

    Version = *(PUInt32)&header.tag[11];
    if (Version > TAG3('3.0') || Version < TAG3('1.0'))
        return False;

    header.tag[11] = 0;
    if (StrICompareA(header.tag, "FilePackVer"))
        return False;

    Key = Hash(header.Data, sizeof(header.Data)) & 0x0FFFFFFF;
    Decrypt(header.Seed, sizeof(header.Seed), Key);

    if (Version == TAG3('3.0') && memcmp(header.Seed, Seed, sizeof(header.Seed)))
        return False;

    // what the fuck is it

#if 0
    pHashTable = (SPackHashTableHeader *)Alloc(header.HashTableSize);
    if (pHashTable == NULL)
        return False;

    if (file.Seek(file.FILE_SEEK_END, -(Long)(sizeof(header) + header.HashTableSize)) == False)
        return False;

    if (file.Read(pHashTable, header.HashTableSize) == False)
        return False;

    Version = *(PUInt32)&pHashTable->HashVer[7];

    do
    {
        ret = False;
        if (Version < TAG3('1.2') || Version > TAG3('1.3'))
            break;

        pHashTable->HashVer[7] = 0;
        if (lstrcmpiA(pHashTable->HashVer, "HashVer") || pHashTable->SubTableNum != 0x100)
            break;

        Decrypt(&pHashTable->Data, pHashTable->CompressedSize, 0x428);

        UInt32 DecompressSize;
        LPVoid lpDecrypted = Alloc(pHashTable->Data.DecompressSize);
        if (lpDecrypted == NULL)
            break;

        DecompressSize = Uncompress(&pHashTable->Data, pHashTable->CompressedSize, lpDecrypted);

        CFileDisk f;
        if (f.Open(L"K:\\galgame\\¥×¥ê¥ó¥»¥¹¥é¥Ð©`!\\GameData\\test.bin", f.W, f.N))
        {
            f.Write(pHashTable, sizeof(*pHashTable) - sizeof(pHashTable->Data));
            f.Write(lpDecrypted, DecompressSize);
        }

        Free(lpDecrypted);

    } while (0);

    Free(pHashTable);
    return False;
#endif

    if (Version == TAG3('1.0'))
        Key = 0xC4;

    ret = InitIndex(&header, Key);

    return ret;
}

Bool CSharu::InitIndex(SPackHeader *pHeader, UInt32 Key)
{
    if (file.Seek(file.FILE_SEEK_BEGIN, pHeader->IndexOffset.LowPart, &pHeader->IndexOffset.HighPart) == False)
        return False;

    Char szFileName[MAX_PATH];
    SMyPackIndex *pIndex;

    m_Index.cbEntrySize = sizeof(*pIndex);
    m_Index.FileCount.QuadPart = pHeader->FileNum;
    m_Index.pEntry = (SMyPackIndex *)Alloc(m_Index.FileCount.LowPart * m_Index.cbEntrySize, HEAP_ZERO_MEMORY);
    if (m_Index.pEntry == NULL)
        return False;

    pIndex = (SMyPackIndex *)m_Index.pEntry;
    for (UInt32 i = m_Index.FileCount.LowPart; i; ++pIndex, --i)
    {
        UInt32 NameLength, CodePage;
        PACK_FILE_ENTRY_INFO EntryInfo;

        file.Read(&NameLength, 2);
        NameLength = (UInt16)NameLength;
        file.Read(szFileName, NameLength);
        DecryptFileName(szFileName, NameLength, Key);
        CodePage = IsShiftJISString(szFileName, NameLength) ? CP_SHIFTJIS : CP_GB2312;
        MultiByteToWideChar(CodePage, 0, szFileName, NameLength, pIndex->FileName, countof(pIndex->FileName));
        file.Read(&EntryInfo, sizeof(EntryInfo));
        pIndex->Offset = EntryInfo.Offset;
        pIndex->Size.QuadPart = EntryInfo.DecompressSize;
        pIndex->CompressedSize.QuadPart = EntryInfo.CompressedSize;
        if (EntryInfo.bEncrypted)
            pIndex->Flags = UNPACKER_ENTRY_FLAG_ENCRYPTED;

        if (EntryInfo.bCompressed)
            pIndex->Flags |= UNPACKER_ENTRY_FLAG_COMPRESSED;

        pIndex->Hash  = EntryInfo.Hash;
    }

    m_Key = Key;

    return True;
}

Bool CSharu::GetFileData(SFileInfo *pFileInfo, const MY_FILE_ENTRY_BASE *pBaseEntry)
{
    PByte  pbBuffer;
    UInt32 BufferSize;
    SMyPackIndex *pIndex;

    pIndex = (SMyPackIndex *)pBaseEntry;

    BufferSize = max(pIndex->CompressedSize.LowPart, pIndex->Size.LowPart);
    if (BufferSize == 0)
    {
        pbBuffer = NULL;
        goto EMPTY_FILE;
    }

    pbBuffer = (PByte)Alloc(BufferSize);
    if (pbBuffer == NULL)
        return False;

    if (file.Seek(file.FILE_SEEK_BEGIN, pIndex->Offset.LowPart, (PLong)&pIndex->Offset.HighPart) == False)
        return False;
    if (file.Read(pbBuffer, pIndex->CompressedSize.LowPart) == False)
        return False;

    if (pIndex->CompressedSize.LowPart < 0x1000000)
    {
        if (Hash(pbBuffer, pIndex->CompressedSize.LowPart) != pIndex->Hash)
        {
            Free(pbBuffer);
            return False;
        }
    }

    if (TEST_BITS(pIndex->Flags, UNPACKER_ENTRY_FLAG_ENCRYPTED))
        Decrypt(pbBuffer, pIndex->CompressedSize.LowPart, m_Key);

    if (TEST_BITS(pIndex->Flags, UNPACKER_ENTRY_FLAG_COMPRESSED))
    {
        PByte pbTemp = (PByte)Alloc(pIndex->CompressedSize.LowPart);
        if (pbTemp == NULL)
        {
            Free(pbBuffer);
            return False;
        }

        memcpy(pbTemp, pbBuffer, pIndex->CompressedSize.LowPart);
        Uncompress(pbTemp, pIndex->CompressedSize.LowPart, pbBuffer);

        Free(pbTemp);
    }

EMPTY_FILE:
    pFileInfo->FileType = UNPACKER_FILE_TYPE_BIN;
    pFileInfo->lpExtraData = NULL;
    pFileInfo->BinData.pbBuffer = pbBuffer;
    pFileInfo->BinData.BufferSize = pIndex->Size.LowPart;

    return True;
}

UInt32 CSharu::DecryptFileName(LPVoid lpFileName, UInt32 Length, UInt32 Key)
{
    PChar pszFileName;

    Key ^= 0x3E;
    Key += Length;
    Key &= 0xFF;
    pszFileName = (PChar)lpFileName;
    for (UInt32 i = 0, j = 1; i != Length; ++i, ++j)
    {
        *pszFileName++ ^= ((j ^ Key) + j) & 0xFF;
    }

    return Length;
}

UInt32 CSharu::CrcString(PCChar pszString, UInt32 Length)
{
    if (Length == -1)
        Length = StrLengthA(pszString);

    UInt32 Crc;

    Crc = 0;
    for (UInt32 i = 0; i != Length; )
    {
        UInt32 c = *pszString++;
        ++i;
        Crc += c * ((i ^ 0xE7) & 0xFF);
    }

    return Crc;
}

UInt32 CSharu::Hash(LPVoid lpBuffer, Int32 BufferSize)
{
    if (BufferSize < 8)
        return 0;

    __asm
    {
        pxor    mm0, mm0;
        pxor    mm2, mm2;
        mov     eax, 03070307h;
        movd    mm3, eax;
        punpckldq mm3, mm3;
        mov     eax, lpBuffer;
        mov     ecx, BufferSize;
        shr     ecx, 3;
        mov     edx, 8;
PROC_LOOP:
            movq    mm1, qword ptr [eax];
            paddw   mm2, mm3;
            pxor    mm1, mm2;
            paddw   mm0, mm1;
            lea     eax, [edx+eax];
        loop     PROC_LOOP;
        movq    mm1, mm0;
        psrlq   mm1, 020h;
        pxor    mm0, mm1;
        movd    eax, mm0;
        emms;
    }
}

Bool CSharu::Encrypt(LPVoid lpBuffer, Int32 BufferSize, UInt32 Key)
{
    return DecryptWorker(lpBuffer, BufferSize, Key, False);
}

Bool CSharu::Decrypt(LPVoid lpBuffer, Int32 BufferSize, UInt32 Key)
{
    return DecryptWorker(lpBuffer, BufferSize, Key, True);
}

Bool CSharu::DecryptWorker(LPVoid lpBuffer, Int32 BufferSize, UInt32 Key, Bool bDecrypt)
{
    Key = (Key + BufferSize) ^ 0xFEC9753E;
    BufferSize /= 8;
    if (BufferSize <= 0)
        return False;

    PUInt64 pBuffer;
    Large_Integer Seed1, Seed2, Key64;

    pBuffer = (PUInt64)lpBuffer;
    Seed1.LowPart  = 0xCE24F523;
    Seed1.HighPart = Seed1.LowPart;     // mm6
    Seed2.LowPart  = 0xA73C5F9D;
    Seed2.HighPart = Seed2.LowPart;     // mm7
    Key64.LowPart  = Key;
    Key64.HighPart = Key64.LowPart;     // mm5

    if (bDecrypt)
    {
        while (BufferSize--)
        {
            Seed2.LowPart  += Seed1.LowPart;
            Seed2.HighPart += Seed1.HighPart;
            Seed2.QuadPart ^= Key64.QuadPart;
            Key64.QuadPart = *pBuffer ^ Seed2.QuadPart;
            *pBuffer++ = Key64.QuadPart;
        }
    }
    else
    {
        while (BufferSize--)
        {
            Seed2.LowPart  += Seed1.LowPart;
            Seed2.HighPart += Seed1.HighPart;
            Seed2.QuadPart ^= Key64.QuadPart;
            Key64.QuadPart = *pBuffer;
            *pBuffer++ ^= Seed2.QuadPart;
        }
    }

    return True;

    __asm
    {
        mov       eax, 0CE24F523h;      // seed1
        movd      mm6, eax;
        punpckldq mm6, mm6;
        mov       eax, 0A73C5F9Dh;      // seed2
        movd      mm7, eax;
        punpckldq mm7, mm7;
        mov       eax, Key;             // key
        movd      mm5, eax;
        punpckldq mm5, mm5;
        mov       ecx, bDecrypt;
        mov       edx, BufferSize;
        mov       eax, lpBuffer;
DECRYPT_LOOP:
            paddd     mm7, mm6;
            pxor      mm7, mm5;
            movq      mm0, qword ptr [eax];
            jecxz     ENCRYPT;
            pxor      mm0, mm7;
            movq      mm5, mm0;
            jmp       MODE_END;
ENCRYPT:
            movq      mm5, mm0;
            pxor      mm0, mm7;
MODE_END:
            movq      qword ptr [eax], mm0;
            add       eax, 8;
            dec       edx;
        jnz       DECRYPT_LOOP;
        emms
    }

    return True;
}

UInt32 CSharu::Uncompress(LPVoid lpInputBuffer, Int32 BufferSize, LPVoid lpOutputBuffer)
{
    Byte   dict_bak[256], dict1[256], dict2[256], dict3[256];
    PByte  pbBuffer, pbEnd, pbDecompress;
    UInt32 Flag, Size;
    SPackEntryCompressedData *pData;

    pData = (SPackEntryCompressedData *)lpInputBuffer;
    if (pData->Magic != SQLI_COMP_MAGIC)
    {
        Flag = 0;
        Size = 0;
        pbBuffer = (PByte)pData + 4;
        BufferSize -= 4;
    }
    else
    {
        if (pData->DecompressSize > 0x4000000)
            return 0;

        Flag = pData->Flag;
        Size = pData->DecompressSize;
        pbBuffer = (PByte)pData->Data;
        BufferSize -= sizeof(*pData) - sizeof(pData->Data);
    }

    pbEnd = pbBuffer + BufferSize;

    if (pbBuffer >= pbEnd)
        return 0;

    for (Int32 i = 0, j = 0x03020100; i != 256; ++i)
    {
//        dict_bak[i] = i;
        *(PUInt32)&dict_bak[i] = j;
        i += 3;
        j += 0x04040404;
    }

    pbDecompress = pbBuffer;
    pbDecompress = (PByte)lpOutputBuffer;
    while (pbBuffer < pbEnd)
    {
        Char b = *pbBuffer++;

        memcpy(dict1, dict_bak, sizeof(dict_bak));

        for (UInt32 i = 0; ;)
        {
            if (b < 0)
            {
                i += (Byte)b - 0x7F;
                b = 0;
            }
            BREAK_IF(i > 255);

            for (UInt32 j = 0, k = b + 1; j != k; ++j)
            {
                Byte by = *pbBuffer++;
                dict1[i] = by;
                if (by != i)
                    dict2[i] = *pbBuffer++;
                ++i;
            }

            BREAK_IF(i > 255);
            b = *pbBuffer++;
        }

        UInt32 j;
        if (Flag & FLAG_ENTRY_16BIT_LENGTH)
        {
            j = *(PUInt16)pbBuffer;
            pbBuffer += 2;
        }
        else
        {
            j = *(PUInt32)pbBuffer;
            pbBuffer += 4;
        }

        for (UInt32 k = 0; ; )
        {
            UInt32 Index;

            if (k)
            {
                Index = dict3[--k];
            }
            else
            {
                BREAK_IF(j == 0);
                --j;
                Index = *pbBuffer++;
            }

            if (Index == dict1[Index])
            {
                *pbDecompress++ = Index;
                continue;
            }

            dict3[k++] = dict2[Index];
            dict3[k++] = dict1[Index];
        }
    }

    return pbDecompress - (PByte)lpOutputBuffer;
}

#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "QLIE.h"
#include "gal_common.h"
#include "Mem.cpp"

UInt32 EncryptFileName(LPVoid lpFileName, UInt32 Length, UInt32 Key)
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

UInt32 Hash(LPVoid lpBuffer, Int32 BufferSize)
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

UInt32 CRC(PCChar pszString, UInt32 Length)
{
    UInt32 crc;

    crc = 0;
    for (UInt32 i = 0; i != Length; )
    {
        UInt32 c = *(PByte)pszString++;
        if (c == 0)
            break;

        ++i;
        crc += c * ((i ^ 0xE7) & 0xFF);
    }

    return crc;
}

Bool DecryptWorker(LPVoid lpBuffer, Int32 BufferSize, UInt32 Key, Bool bDecrypt)
{
    Key = (Key + BufferSize) ^ 0xFEC9753E;
    BufferSize /= 8;
    if (BufferSize <= 0)
        return False;

    PUInt64 pBuffer;
    LARGE_INTEGER Seed1, Seed2, Key64;

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
}

Bool Encrypt(LPVoid lpBuffer, Int32 BufferSize, UInt32 Key)
{
    return DecryptWorker(lpBuffer, BufferSize, Key, False);
}

Bool Decrypt(LPVoid lpBuffer, Int32 BufferSize, UInt32 Key)
{
    return DecryptWorker(lpBuffer, BufferSize, Key, True);
}

UInt32 GetStringSubIndex(PCChar pszString, Int32 Length, UInt32 MaxIndex)
{
    if (MaxIndex == 0)
        return 0;
    if (Length == -1)
        Length = StrLengthA(pszString);

    UInt32 hash = 0;

    for (UInt32 i = 0; i != Length; ++i)
    {
        UInt32 b = *(PByte)pszString++;
        hash += b * ((i + 1) & 0xFF);
    }

    return hash % MaxIndex;
}

UInt32 FakeCompress(LPVoid lpInput, Int32 InputSize, LPVoid lpOutput, Int32 OutputSize)
{
    PByte pbOutput;
    SPackEntryCompressedData *pData;

    pData = (SPackEntryCompressedData *)lpOutput;
    if (pData == NULL)
        return InputSize + sizeof(*pData) - sizeof(pData->Data) + 256;
    else if (OutputSize < InputSize + sizeof(*pData) - sizeof(pData->Data) + 256)
        return 0;

    pData->Magic = QLIE_COMP_MAGIC;
    pData->Flag = 0;
    pData->DecompressSize = InputSize;
    pbOutput = pData->Data;
    *pbOutput++ = 0x7F;
    for (Int32 i = 0, j = 0x03020100; i < 0x7F; i += 4)
    {
        *(PUInt32)pbOutput = j;
        pbOutput += 4;
        j += 0x04040404;
    }
    *pbOutput++ = 0x7F;
    for (Int32 i = 0, j = 0x83828180; i < 0x7F; i += 4)
    {
        *(PUInt32)pbOutput = j;
        pbOutput += 4;
        j += 0x04040404;
    }

    *(PUInt32)pbOutput = InputSize;
    pbOutput += 4;
    memcpy(pbOutput, lpInput, InputSize);
    pbOutput += InputSize;

    return pbOutput - (PByte)lpOutput;
}

ULong AddNode(SQLIECompressInfo *pInfo, UInt32 LastByte, UInt32 CurrentByte)
{
    ULong Index;

    Index = LastByte ^ (CurrentByte << 5);
    Index &= 0x1FFF;

    while (!(LastByte == pInfo->dict_2000[Index] && CurrentByte == pInfo->dict_4000[Index]) &&
        pInfo->dict_6000[Index] != 0)
    {
        ++Index;
        Index &= 0x1FFF;
    }

    pInfo->dict_2000[Index] = LastByte;
    pInfo->dict_4000[Index] = CurrentByte;

    return Index;
}

Bool InitDict(SQLIECompressInfo *pInfo)
{
    PByte pbBuffer, pbEnd;
    ULong MaskCount, Index, DictLength;
    UInt32 CurrentByte;

#if 0
    pbBuffer   = pInfo->pbBuffer;
    pbEnd      = pInfo->pbEnd;

    ZeroStruct(pInfo);
    pInfo->pbBuffer   = pbBuffer;
    pInfo->pbEnd      = pbEnd;

#else

    ZeroStruct(&pInfo->dict_6000);
    ZeroStruct(&pInfo->dict_6100);

#endif

    pbBuffer = pInfo->dict_6200;
    for (Int32 i = 0, j = 0x03020100; i < 0x100; i += 4)
    {
        *(PUInt32)pbBuffer = j;
        pbBuffer += 4;
        j += 0x04040404;
    }

    MaskCount  = 0;
    DictLength = 0;
    pbBuffer   = pInfo->pbBuffer;
    pbEnd      = pInfo->pbEnd;

    while (DictLength < 0x2000 && MaskCount < 200 && pbBuffer < pbEnd)
    {
        CurrentByte = *pbBuffer++;
        if (DictLength != 0)
        {
            Index = AddNode(pInfo, pInfo->dict_820C[DictLength - 2], CurrentByte);
            if (pInfo->dict_6000[Index] < 0xFF)
                ++pInfo->dict_6000[Index];
        }

        pInfo->dict_820C[DictLength - 1] = CurrentByte;
        ++DictLength;
        if (pInfo->dict_6100[CurrentByte] == 0)
        {
            pInfo->dict_6100[CurrentByte] = 1;
            ++MaskCount;
        }
    }

    pInfo->DictLength = DictLength;
    pInfo->pbBuffer   = pbBuffer;
    pInfo->pbEnd      = pbEnd;

    return pbBuffer >= pbEnd;
}

PByte WriteBlock(SQLIECompressInfo *pInfo, PByte pbBuffer, PByte pbEnd)
{
    Int Index, i;

    for (Index = 0; Index < 0x100;)
    {
        i = Index == pInfo->dict_6200[Index];
        ++Index;
        if (i)
        {
            i = 1;
            while (i < 0x7F && Index < 0x100 && Index == pInfo->dict_6200[Index])
            {
                ++i;
                ++Index;
            }

            if (pbBuffer >= pbEnd)
                return NULL;

            *pbBuffer++ = (Byte)i + 0x7F;
            i = 0;
            if (Index > 0xFF)
                break;
        }
        else
        {
            i = 0;
            for (; ; ++Index, ++i)
            {
                if (i < 0x7F && Index < 0x100)
                {
                    if (Index != pInfo->dict_6200[Index])
                        continue;
                }

                if (i >= 0x7D || Index >= 0xFE)
                    break;

                if (Index + 1 == pInfo->dict_6200[Index + 1])
                    break;
            }

            if (pbBuffer >= pbEnd)
                return NULL;

            *pbBuffer++ = i;
            Index -= i + 1;
        }

        if (i < 0)
            continue;

        ++i;
        do
        {
            if (pbBuffer >= pbEnd)
                return NULL;

            *pbBuffer++ = pInfo->dict_6200[Index];
            if (Index != pInfo->dict_6200[Index])
            {
                if (pbBuffer >= pbEnd)
                    return NULL;

                *pbBuffer++ = pInfo->dict_6100[Index];
            }

            ++Index;

        } while (--i);
    }

    if (pbBuffer + 2 + pInfo->DictLength >= pbEnd)
        return NULL;

    *(PUInt16)pbBuffer = pInfo->DictLength;
    pbBuffer += 2;
    memcpy(pbBuffer, pInfo->dict_820C - 1, pInfo->DictLength);
    pbBuffer += pInfo->DictLength;

    return pbBuffer;
}

ULong QLIECompress(LPVoid lpInput, Int32 InputSize, LPVoid lpOutput, Int32 OutputSize)
{
    Bool   bEnd;
    PByte  pbBuffer, pbOutEnd;
    UInt32 LastByte, CurrentByte;
    SPackEntryCompressedData *pData;
    SQLIECompressInfo Info;

    pData = (SPackEntryCompressedData *)lpOutput;
    if (pData == NULL)
        return InputSize + sizeof(*pData) - sizeof(pData->Data) + 256;
    else if (OutputSize < InputSize + sizeof(*pData) - sizeof(pData->Data) + 256)
        return 0;

    ZeroStruct(&Info);

    pData->Magic          = QLIE_COMP_MAGIC;
    pData->Flag           = FLAG_ENTRY_16BIT_LENGTH;
    pData->DecompressSize = InputSize;
    pbBuffer              = pData->Data;
    Info.pbBuffer         = (PByte)lpInput;
    Info.pbEnd            = Info.pbBuffer + InputSize;
    pbOutEnd              = (PByte)lpOutput + OutputSize;

    bEnd = False;
    while (!bEnd)
    {
        Long Index, val;
        ULong InsertIndex;
        bEnd = InitDict(&Info);

        Index = 0x100;
        while (Index-- > 0)
        {
            do
            {
                if (Info.dict_6200[Index] == Index && Info.dict_6100[Index] == 0)
                    break;
            } while (--Index >= 0);
            if (Index < 0)
                break;

            PByte dict_6000 = Info.dict_6000;
            PByte dict_4000 = Info.dict_4000;
            PByte dict_2000 = Info.dict_2000;

            val = 2;
            for (ULong i = 0x2000; i; --i)
            {
                if (*dict_6000 > val)
                {
                    val         = *dict_6000;
                    CurrentByte = *dict_2000;
                    LastByte    = *dict_4000;
                }

                dict_6000++;
                dict_2000++;
                dict_4000++;
            }

            if (val < 3)
                break;

            Int i, j, k;
            for (i = 0, k = 0, j = Info.DictLength - 1; i < j; ++i, ++k)
            {
                if (Info.dict_820C[i - 1] != CurrentByte || Info.dict_820C[i] != LastByte)
                {
                    Info.dict_820C[k - 1] = Info.dict_820C[i - 1];
                    continue;
                }

                if (i > 0)
                {
                    InsertIndex = AddNode(&Info, Info.dict_820C[k - 2], CurrentByte);
                    if (Info.dict_6000[InsertIndex] > 1)
                        --Info.dict_6000[InsertIndex];

                    InsertIndex = AddNode(&Info, Info.dict_820C[k - 2], Index);
                    if (Info.dict_6000[InsertIndex] != 0xFF)
                        ++Info.dict_6000[InsertIndex];
                }

                if (i < j - 1)
                {
                    InsertIndex = AddNode(&Info, LastByte, Info.dict_820C[i + 1]);
                    if (Info.dict_6000[InsertIndex] > 1)
                        --Info.dict_6000[InsertIndex];

                    InsertIndex = AddNode(&Info, Index, Info.dict_820C[i + 1]);
                    if (Info.dict_6000[InsertIndex] != 0xFF)
                        ++Info.dict_6000[InsertIndex];
                }

                Info.dict_820C[k - 1] = Index;
                ++i;
                --Info.DictLength;
            }

            Info.dict_820C[k - 1] = Info.dict_820C[i - 1];
            Info.dict_6200[Index] = CurrentByte;
            Info.dict_6100[Index] = LastByte;
            InsertIndex = AddNode(&Info, CurrentByte, LastByte);
            Info.dict_6000[InsertIndex] = 1;
        }

        pbBuffer = WriteBlock(&Info, pbBuffer, pbOutEnd);
        if (pbBuffer == NULL)
            return 0;
    }

    return pbBuffer - (PByte)pData;
}

ULong GetMaxCompressedSize(PVoid pvInput, ULong InputSize)
{
    return QLIECompress(pvInput, InputSize, NULL, 0) + 0x1000;
}

Void ReleaseGlobalData()
{
}

Void
CALLBACK
PackFiles(
    SPackFileInfo *pPackFileInfo,
    UInt32         uCount,
    PCWChar        pszOutput,
    PCWChar        pszFullInputPath,
    PCWChar        pszParam,
    FShowStatus    ShowStatus
)
{
    CMem    m;
    HANDLE  hFile, hFilePack;
    UInt32  BufferSize, CompressBufferSize;
    DWORD   dwRead;
    WChar   szPath[MAX_PATH];
    LPVoid  lpBuffer, lpCompressBuffer;
    Large_Integer liOffset;
    SPackFileInfo *pInfo;
    SMyPackIndex  *pIndex, *pPackIndex;

    hFilePack = CreateFileW(pszOutput, 
        GENERIC_READ|GENERIC_WRITE, 
        FILE_SHARE_READ|FILE_SHARE_WRITE, 
        NULL, 
        CREATE_ALWAYS, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL);
    if (hFilePack == INVALID_HANDLE_VALUE)
        return;

    GetCurrentDirectoryW(countof(szPath), szPath);
    SetCurrentDirectoryW(pszFullInputPath);

    pIndex = (SMyPackIndex *)m.Alloc(uCount * sizeof(*pIndex), HEAP_ZERO_MEMORY);
    if (pIndex == NULL)
        return;

    static Char Sig[]  = "Amano Tooko";
    static Char Tag[]  = "FilePackVer3.0";
    static Char Seed[] = "8hr48uky,8ugi8ewra4g8d5vbf5hb5s6";
    UInt32 Key;
    SPackHeader PackHeader;

    ZeroMemory(&PackHeader, sizeof(PackHeader));
    memcpy(PackHeader.Seed, Seed, sizeof(PackHeader.Seed));
    memcpy(PackHeader.tag, Tag, sizeof(PackHeader.tag));

#if 1
    for (UInt32 i = 0, j = 1; i != sizeof(PackHeader.Data) / sizeof(i); ++i)
    {
//        j = _rotl(GetRandom32(), (Byte)j);
        j = GetRandom32();
        *((PUInt32)PackHeader.Data + i) = j;
//        j = _rotl(j, (Byte)HIBYTE(j));
        Sleep(1);
    }
/*
    for (UInt32 i = 0, j = 1; i != sizeof(PackHeader.arr) / sizeof(i); ++i)
    {
//        j = _rotl(GetRandom32(), (Byte)j);
        j = GetRandom32();
        *((PUInt32)PackHeader.arr + i) = j;
        Sleep(1);
//        j = _rotl(j, (Byte)HIBYTE(j));
    }
*/
    memcpy((PByte)&PackHeader.tag - sizeof(Sig) + 1, Sig, sizeof(Sig) - 1);

#else
    lstrcpyA(PackHeader.Data, "Amano Tooko");
#endif

    PackHeader.FileNum = uCount;

    Key = Hash(PackHeader.Data, sizeof(PackHeader.Data)) & 0x0FFFFFFF;
    Encrypt(PackHeader.Seed, sizeof(PackHeader.Seed), Key);

    BufferSize = 0x10000;
    CompressBufferSize = BufferSize;
    lpBuffer = m.Alloc(BufferSize);
    lpCompressBuffer = m.Alloc(CompressBufferSize);

    liOffset.QuadPart = 0;
    pInfo = pPackFileInfo;
    pPackIndex = pIndex;
    for (UInt32 i = 0; i != uCount; ++i, ++pIndex, ++pInfo)
    {
        lstrcpyW(pIndex->FileName, pInfo->pFileName);
        hFile = CreateFileW(pInfo->pFileName, 
                    GENERIC_READ, 
                    FILE_SHARE_READ, 
                    NULL, 
                    OPEN_EXISTING, 
                    FILE_ATTRIBUTE_NORMAL, 
                    NULL);
        if (hFile == INVALID_HANDLE_VALUE)
            continue;

        dwRead = GetFileSize(hFile, NULL);
        pIndex->DecompressSize = dwRead;
        pIndex->CompressedSize = dwRead;
        pIndex->bEncrypted     = True;
        if (dwRead > BufferSize)
        {
            BufferSize = dwRead;
            lpBuffer = m.ReAlloc(lpBuffer, BufferSize);
        }

        if (dwRead)
        {
            ReadFile(hFile, lpBuffer, dwRead, &dwRead, NULL);
        }
        CloseHandle(hFile);

        pIndex->Offset = liOffset;
        if (dwRead)
        {
#if 1
            ULong MaxCompressedSize;

            MaxCompressedSize = GetMaxCompressedSize(lpBuffer, dwRead);
            if (MaxCompressedSize > CompressBufferSize)
            {
                CompressBufferSize = MaxCompressedSize;
                lpCompressBuffer = m.ReAlloc(lpCompressBuffer, CompressBufferSize);
            }

            if (MaxCompressedSize > BufferSize)
            {
                BufferSize = MaxCompressedSize;
                lpBuffer = m.ReAlloc(lpBuffer, BufferSize);
            }

            MaxCompressedSize = QLIECompress(
                                    lpBuffer,
                                    dwRead,
                                    lpCompressBuffer,
                                    MaxCompressedSize);

            if (MaxCompressedSize != 0 && MaxCompressedSize < dwRead)
            {
                dwRead = MaxCompressedSize;
                memcpy(lpBuffer, lpCompressBuffer, dwRead);
                pIndex->bCompressed = True;
                pIndex->CompressedSize = dwRead;
            }

#endif
            Encrypt(lpBuffer, dwRead, Key);
            pIndex->Hash = Hash(lpBuffer, dwRead);
        }
        else
        {
            SPackEntryCompressedData *pData = (SPackEntryCompressedData *)lpBuffer;

            pData->Magic = QLIE_COMP_MAGIC;
            pData->Flag = 1;
            pData->DecompressSize = 0;
            *(PUInt32)pData->Data = 0xFFFE7FFE;
            *(PUInt16)&pData->Data[4] = 0;

            pIndex->bEncrypted = False;
            pIndex->bCompressed = True;
            dwRead = 0x12;
            pIndex->CompressedSize = dwRead;
            pIndex->Hash = Hash(lpBuffer, dwRead);
        }

        WriteFile(hFilePack, lpBuffer, dwRead, &dwRead, NULL);
        liOffset.QuadPart += dwRead;
        if (ShowStatus)
        {
            WChar buf[400];
            swprintf(buf, L"%u / %u : %s", i + 1, uCount, pIndex->FileName);
            ShowStatus(buf, (i + 1) * 100 / uCount);
        }
    }

    UInt32 CodePage;
    Char szFile[MAX_PATH];
    PWChar pCharMap;

    pCharMap = CreateCharMapW(NULL, 0);

    CodePage = CP_SHIFTJIS;
    if (pszParam)
    {
        if (!StrICompareW(pszParam, L"gb2312"))
            CodePage = CP_GB2312;
    }

    pIndex = pPackIndex;
    for (UInt32 i = 0; i != uCount; ++i, ++pIndex)
    {
        UInt32 Len;
        FilterStringWithConvertTable(pIndex->FileName, -1, pCharMap);
        Len = WideCharToMultiByte(CodePage, 0, pIndex->FileName, -1, szFile, sizeof(szFile), 0, 0);
        --Len;
        EncryptFileName(szFile, Len, Key);
        WriteFile(hFilePack, &Len, 2, &dwRead, NULL);
        WriteFile(hFilePack, szFile, Len, &dwRead, NULL);
        dwRead = sizeof(*pIndex) - sizeof(pIndex->FileName);
        WriteFile(hFilePack, &pIndex->Offset, dwRead, &dwRead, NULL);
    }

    const UInt32 SubTableNum = 256;
    pbool  pMask;
    PByte  pbBuffer;
    UInt32 HashTableSize;
    SPackHashTableHeader hashtbl, *pHashTable;
    static Char HashVer[] = "HashVer1.3";

    // calc maximum hash table size

    HashTableSize = sizeof(*pHashTable) - sizeof(pHashTable->Data);
    HashTableSize += FakeCompress(0, 0, 0, 0);      // compressed data header

    // Len + Name(MAX) + Offset + Crc + FileIndex

    HashTableSize += uCount * (2 + MAX_PATH + 8 + 4) + uCount * 2;

    pHashTable = (SPackHashTableHeader *)m.Alloc(HashTableSize);
    if (pHashTable == NULL)
    {
        MessageBoxW(0, L"Allocate memory for hash table failed", 0, 64);
        goto PACK_END;
    }
    pMask = (pbool)m.Alloc(uCount, HEAP_ZERO_MEMORY);
    if (pMask == NULL)
    {
        m.Free(pHashTable);
        MessageBoxW(0, L"Allocate memory for hash table masks failed", 0, 64);
        goto PACK_END;
    }

    // generate

    memcpy(pHashTable->HashVer, HashVer, sizeof(pHashTable->HashVer));
    pHashTable->SubTableNum = SubTableNum;
    pHashTable->FileNum = uCount;
    pHashTable->FileIndexSize = uCount * 2;

    pbBuffer = (PByte)&pHashTable->Data;
    for (UInt32 i = 0; i != SubTableNum; ++i)
    {
        PByte pbOutput;
        UInt32 Count;

        Count = 0;
        pbOutput = pbBuffer + 2;
        pIndex = pPackIndex;
        for (UInt32 j = 0; j != uCount; ++j, ++pIndex)
        {
            UInt32 Len;
            CONTINUE_IF(pMask[j]);

            Len = WideCharToMultiByte(CodePage, 0, pIndex->FileName, -1, szFile, sizeof(szFile), 0, 0) - 1;
            if(GetStringSubIndex(szFile, Len, SubTableNum) != i)
            {
                continue;
            }

            pMask[j] = true;
            ++Count;

            *(PUInt16)pbOutput = Len;       // name len
            pbOutput += 2;
            memcpy(pbOutput, szFile, Len);  // name
            pbOutput += Len;
            *(PUInt64)pbOutput = j * 2;     // offset
            pbOutput += 8;
            *(PUInt32)pbOutput = CRC(szFile, Len);
            pbOutput += 4;
        }

        *(PUInt16)pbBuffer = Count;
        pbBuffer = pbOutput;
    }

    for (UInt32 i = 0; i != uCount; ++i)
    {
        *(PUInt16)pbBuffer = i;
        pbBuffer += 2;
    }

    HashTableSize = pbBuffer - (PByte)&pHashTable->Data;

#if 1
    ULong MaxCompressedSize;

    dwRead = HashTableSize;
    MaxCompressedSize = GetMaxCompressedSize(NULL, dwRead);
    if (MaxCompressedSize > CompressBufferSize)
    {
        CompressBufferSize = MaxCompressedSize;
        lpCompressBuffer = m.ReAlloc(lpCompressBuffer, CompressBufferSize);
    }

    MaxCompressedSize = QLIECompress(
                            &pHashTable->Data,
                            HashTableSize,
                            lpCompressBuffer,
                            CompressBufferSize);

    if (MaxCompressedSize == 0 || MaxCompressedSize >= dwRead)
    {
        dwRead = FakeCompress(
                     &pHashTable->Data,
                     HashTableSize,
                     lpCompressBuffer,
                     CompressBufferSize);
    }
    else
    {
        dwRead = MaxCompressedSize;
    }

#else
    dwRead = FakeCompress(0, HashTableSize, 0, 0);
    if (dwRead > CompressBufferSize)
    {
        CompressBufferSize = dwRead;
        lpCompressBuffer = m.ReAlloc(lpCompressBuffer, CompressBufferSize);
    }

    dwRead = FakeCompress(&pHashTable->Data, HashTableSize, lpCompressBuffer, CompressBufferSize);
#endif

    Encrypt(lpCompressBuffer, dwRead, 0x428);
    memcpy(&pHashTable->Data, lpCompressBuffer, dwRead);
    pHashTable->CompressedSize = dwRead;

    PackHeader.HashTableSize = sizeof(*pHashTable) - sizeof(pHashTable->Data) + dwRead;
    PackHeader.IndexOffset = liOffset;

    WriteFile(hFilePack, pHashTable, PackHeader.HashTableSize, &dwRead, NULL);
    WriteFile(hFilePack, &PackHeader, sizeof(PackHeader), &dwRead, NULL);

PACK_END:
    CloseHandle(hFilePack);

    FreeCharMap(pCharMap);
    m.Free(lpBuffer);
    m.Free(lpCompressBuffer);

    SetCurrentDirectoryW(szPath);

    ReleaseGlobalData();
}
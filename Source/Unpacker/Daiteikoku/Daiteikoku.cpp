#include "Daiteikoku.h"
#include "zlib/zlib.h"

Int MByteToWChar(PChar pAnsiString, SizeT AnsiLength, PWChar pUnicodeString, SizeT UnicodeLength)
{
    Int Length;
    Length = MultiByteToWideChar(
                IsShiftJISString(pAnsiString, AnsiLength) ? CP_SHIFTJIS : CP_ACP,
                0,
                pAnsiString,
                AnsiLength,
                pUnicodeString,
                UnicodeLength);
    if (Length < UnicodeLength)
        pUnicodeString[Length] = 0;

    return Length;
}

Bool CDaiteikoku::Open(PCWChar pszFileName)
{
    UInt32 Header;

    if (!m_file.Open(pszFileName))
        return False;

    if (!m_file.Read(&Header, sizeof(Header)))
        return False;

    if (!m_file.Rewind())
        return False;

    if (Header == TAG4('ALK0'))
    {
        return InitIndexALK();
    }
    else if ((Header & 0xFFFFFF) == TAG3('AI2'))
    {
        return ExtractAIN(pszFileName);
    }
    else if (Header == TAG4('VERS'))
    {
        return CompressAI2(pszFileName);
    }
    else if (Header == ALICE_AFA_MAGIC)
    {
        return InitIndexAFA();
    }
    else
    {
        pszFileName = findextw(pszFileName);
        if (*pszFileName == 0 || pszFileName[4] != 0)
            return False;

        ++pszFileName;
        if (CHAR_UPPER3W(*(PUInt64)pszFileName) != TAG3W('ALD'))
            return False;

        return InitIndexALD();
    }
}

Bool CDaiteikoku::InitIndexALD()
{
    Bool  Result;
    SizeT OffsetIndexCount, OffsetIndexSize;
    ALICE_ALD_OFFSET_INDEX *pOffsetIndex, *pOffsetIndexBegin;
    DECL_ALIGN(1) struct
    {
        UInt24 OffsetIndexOffset;
        UInt24 FirstFileOffset;
        UInt16 Pad;
    } AldHeader;
    struct
    {
        ALICE_ALD_FILE_INFO FileInfo;
        Char FileName[MAX_PATH];
    } PadFileInfo;

    if (!m_file.Read(&AldHeader, sizeof(AldHeader)))
        return False;

    OffsetIndexSize  = *(PUInt32)AldHeader.FirstFileOffset << 8;
    OffsetIndexSize -= *(PUInt32)AldHeader.OffsetIndexOffset << 8;
    OffsetIndexCount = OffsetIndexSize / sizeof(*pOffsetIndex);
    if (OffsetIndexSize < sizeof(*pOffsetIndex))
        return False;

    if (!m_file.Seek(m_file.FILE_SEEK_BEGIN, *(PUInt32)AldHeader.OffsetIndexOffset << 8))
        return False;

    pOffsetIndex = (ALICE_ALD_OFFSET_INDEX *)Alloc(OffsetIndexSize);
    if (pOffsetIndex == NULL)
        return False;

    pOffsetIndexBegin = pOffsetIndex;
    m_Index.cbEntrySize = sizeof(MY_ALICE_ALD_ENTRY);

    Result = False;
    LOOP_ONCE
    {
        SizeT Count;
        MY_ALICE_ALD_ENTRY *pEntry;

        if (!m_file.Read(pOffsetIndexBegin, OffsetIndexSize))
            break;

        m_Index.FileCount.QuadPart = 0;
        for (Count = OffsetIndexCount; Count; ++pOffsetIndex, --Count)
        {
            if (pOffsetIndex->bValid)
                ++m_Index.FileCount.LowPart;
        }

        if (m_Index.FileCount.LowPart == 0)
            break;

        pEntry = (MY_ALICE_ALD_ENTRY *)Alloc(m_Index.FileCount.LowPart * sizeof(MY_ALICE_ALD_ENTRY));
        if (pEntry == NULL)
            break;

        m_Index.pEntry = pEntry;
        pOffsetIndex = pOffsetIndexBegin;
        for (Count = 0; Count != OffsetIndexCount; ++pOffsetIndex, ++Count)
        {
            Long Length, Offset;

            if (!pOffsetIndex->bValid)
                continue;

            pEntry->Flags = 0;
            Offset = pOffsetIndex->IndexInOffsetTable - 1;
            Offset = Offset * sizeof(ALICE_ALD_OFFSET_TABLE) + sizeof(UInt24);
            pEntry->OriginalIndex = Count;
            if (!m_file.Seek(m_file.FILE_SEEK_BEGIN, Offset))
                break;
            if (!m_file.Read(&Offset, sizeof(Offset)))
                break;

            Offset <<= 8;
            if (!m_file.Seek(m_file.FILE_SEEK_BEGIN, Offset))
                break;

            if (!m_file.Read(&PadFileInfo, sizeof(PadFileInfo)))
                break;

            pEntry->Offset.QuadPart = Offset + PadFileInfo.FileInfo.MaxLength;
            pEntry->Size.QuadPart = PadFileInfo.FileInfo.FileSize;
            *(PUInt64)pEntry->MaybeHash = PadFileInfo.FileInfo.MaybeHash;

            Length = PadFileInfo.FileInfo.MaxLength - (sizeof(PadFileInfo.FileInfo) - sizeof(PadFileInfo.FileInfo.FileName));
            MByteToWChar(PadFileInfo.FileInfo.FileName, Length, pEntry->FileName, countof(pEntry->FileName));
            ++pEntry;
        }

        if (Count == OffsetIndexCount)
            Result = True;
    }

    Free(pOffsetIndexBegin);

    return Result;
}

Bool CDaiteikoku::InitIndexAFA()
{
    Bool  Result;
    PByte pbCompressed, pbIndex;
    ALICE_AFA_HEADER AFAHeader;
    ALICE_AFA_INDEX_HEADER IndexHeader;

    if (!m_file.Read(&AFAHeader, sizeof(AFAHeader)))
        return False;

    if (AFAHeader.Magic != ALICE_AFA_MAGIC ||
        AFAHeader.Tag != ALICE_AFA_HEADER_TAG ||
        AFAHeader.MustBeTrue != 1)
    {
        return False;
    }

    if (!m_file.Seek(m_file.FILE_SEEK_BEGIN, AFAHeader.HeaderSize))
        return False;

    if (!m_file.Read(&IndexHeader, sizeof(IndexHeader)))
        return False;

    if (IndexHeader.Tag != ALICE_AFA_INDEX_TAG ||
        IndexHeader.EntryCount == 0)
    {
        return False;
    }

    pbCompressed = (PByte)Alloc(IndexHeader.IndexSize - sizeof(IndexHeader));
    if (pbCompressed == NULL)
        return False;

    if (!m_file.Read(pbCompressed, IndexHeader.IndexSize - sizeof(IndexHeader)))
    {
        Free(pbCompressed);
        return False;
    }

    pbIndex = (PByte)Alloc(IndexHeader.DecompressSize);
    if (pbIndex == NULL)
    {
        Free(pbCompressed);
        return False;
    }

    Result = False;
    LOOP_ONCE
    {
        PByte pbAFAEntry;
        MY_ALICE_AFA_ENTRY *pEntry;

        Result = uncompress(pbIndex, (PULong)&IndexHeader.DecompressSize, pbCompressed, IndexHeader.IndexSize - sizeof(IndexHeader));
        if (Result != Z_OK)
        {
            Result = False;
            break;
        }

        Result = False;
        m_Index.cbEntrySize = sizeof(*pEntry);
        m_Index.FileCount.QuadPart = IndexHeader.EntryCount;
        pEntry = (MY_ALICE_AFA_ENTRY *)Alloc(m_Index.FileCount.LowPart * m_Index.cbEntrySize);
        if (pEntry == NULL)
            break;

        m_Index.pEntry = pEntry;
        pbAFAEntry = pbIndex;
        for (SizeT Count = IndexHeader.EntryCount; Count; --Count)
        {
            PALICE_AFA_ENTRY_NAME pName;
            ALICE_AFA_ENTRY_INFO *pInfo;

            pEntry->Flags = 0;
            pName = (PALICE_AFA_ENTRY_NAME)pbAFAEntry;
            MByteToWChar(pName->FileName, pName->Length, pEntry->FileName, countof(pEntry->FileName));
            pInfo = (ALICE_AFA_ENTRY_INFO *)(pbAFAEntry + pName->MaxLength + 8);
            pbAFAEntry = (PByte)pInfo + sizeof(*pInfo);
            pEntry->Offset.QuadPart = pInfo->Offset + AFAHeader.DataOffset;
            pEntry->Size.QuadPart = pInfo->Size;
            *(PUInt64)pEntry->Hash = *(PUInt64)pInfo->Hash;
            pEntry->Unknown = pInfo->Unknown;
            ++pEntry;
        }

        Result = True;
    }

    Free(pbIndex);
    Free(pbCompressed);

    return Result;
}

Bool CDaiteikoku::InitIndexALK()
{
    MY_FILE_ENTRY_BASE *pEntry;
    ALICE_ALK_HEADER AlkHeader;
    ALICE_ALK_ENTRY *pAlkEntry, *pAlkEntryBase;

    if (!m_file.Read(&AlkHeader, sizeof(AlkHeader)))
        return False;

    if (AlkHeader.Magic != ALICE_ALK_MAGIC ||
        AlkHeader.EntryCount == 0)
    {
        return False;
    }

    m_Index.pEntry = (MY_FILE_ENTRY_BASE *)Alloc(AlkHeader.EntryCount * sizeof(*m_Index.pEntry));
    if (m_Index.pEntry == NULL)
        return False;

    pAlkEntryBase = (ALICE_ALK_ENTRY *)Alloc(AlkHeader.EntryCount * sizeof(*pAlkEntryBase));
    if (pAlkEntryBase == NULL)
        return False;

    if (!m_file.Read(pAlkEntryBase, AlkHeader.EntryCount * sizeof(*pAlkEntryBase)))
    {
        Free(pAlkEntryBase);
        return False;
    }

    m_Index.FileCount.QuadPart = AlkHeader.EntryCount;
    pEntry = m_Index.pEntry;
    pAlkEntry = pAlkEntryBase;
    for (SizeT Index = 0, Count = AlkHeader.EntryCount; Count; --Count)
    {
        pEntry->Flags = 0;
        pEntry->Offset.QuadPart = pAlkEntry->Offset;
        pEntry->Size.QuadPart = pAlkEntry->Size;
        swprintf(pEntry->FileName, L"%08X.bin", Index++);
        ++pEntry;
        ++pAlkEntry;
    }

    Free(pAlkEntryBase);

    return True;
}

Bool CDaiteikoku::ExtractAIN(PCWChar pszFileName)
{
    PByte pbCompressed, pbBuffer;
    ALICE_AIN_HEADER AinHeader;

    if (!m_file.Read(&AinHeader, sizeof(AinHeader)))
        return False;

    if (AinHeader.Magic != ALICE_AIN_MAGIC ||
        AinHeader.AlwaysZero != 0)
    {
        return False;
    }

    pbCompressed = (PByte)Alloc(AinHeader.CompressedSize);
    if (pbCompressed == NULL)
        return False;

    pbBuffer = (PByte)Alloc(AinHeader.DecompressedSize);
    if (pbBuffer == NULL)
    {
        Free(pbCompressed);
        return False;
    }

    LOOP_ONCE
    {
        WChar szFile[MAX_PATH];

        if (!m_file.Read(pbCompressed, AinHeader.CompressedSize))
            break;

        if (uncompress(pbBuffer, (PULong)&AinHeader.DecompressedSize, pbCompressed, AinHeader.CompressedSize) != Z_OK)
            break;

        CFileDisk file;

        lstrcpyW(szFile, pszFileName);
        lstrcpyW(findextw(szFile), L".ai2");
        if (!file.Create(szFile))
            break;

        file.Write(pbBuffer, AinHeader.DecompressedSize);
    }

    Free(pbCompressed);
    Free(pbBuffer);

    return False;
}

Bool CDaiteikoku::CompressAI2(PCWChar pszFileName)
{
    Bool   Result;
    PVoid  pvBuffer;
    UInt32 FileSize;
    WChar  szFile[MAX_PATH];
    ALICE_AIN_HEADER *pAinHeader;

    FileSize = m_file.GetSize();
    pvBuffer = Alloc(FileSize);
    if (pvBuffer == NULL)
        return False;

    pAinHeader = (ALICE_AIN_HEADER *)Alloc(FileSize * 2 + sizeof(*pAinHeader));
    if (pAinHeader == NULL)
    {
        Free(pvBuffer);
        return False;
    }

    LOOP_ONCE
    {
        if (!m_file.Read(pvBuffer, FileSize))
            break;

        pAinHeader->Magic = ALICE_AIN_MAGIC;
        pAinHeader->DecompressedSize = FileSize;
        pAinHeader->AlwaysZero = 0;
        pAinHeader->CompressedSize = FileSize * 2;

        Result = compress2(
                    (PByte)pAinHeader + sizeof(*pAinHeader),
                    (PULong)&pAinHeader->CompressedSize,
                    (PByte)pvBuffer,
                    FileSize,
                    Z_BEST_COMPRESSION);
        if (Result != Z_OK)
        {
            Result = False;
            break;
        }

        CFileDisk file;
        
        lstrcpyW(szFile, pszFileName);
        lstrcpyW(findextw(szFile), L".ain");

        if (!file.Create(szFile))
            break;

        Result = file.Write(pAinHeader, pAinHeader->CompressedSize + sizeof(*pAinHeader));
    }

    Free(pvBuffer);
    Free(pAinHeader);

    return False;
}

Bool CDaiteikoku::GetFileData(SFileInfo *pFileInfo, const MY_FILE_ENTRY_BASE *pBaseEntry, Bool bConvert /* = False */)
{
    Bool  Result;
    PByte pbBuffer;
    MY_ALICE_ALD_ENTRY *pEntry;

    UNUSED_VARIABLE(bConvert);

//    if (StrCompareW(pBaseEntry->FileName, L"Á¢¤Á½}\\CG01010.QNT")) return False;

    pEntry = (MY_ALICE_ALD_ENTRY *)pBaseEntry;
    if (pEntry->Size.QuadPart == 0)
        return False;

    if (!m_file.SeekEx(m_file.FILE_SEEK_BEGIN, pEntry->Offset))
        return False;

    pbBuffer = (PByte)Alloc(pEntry->Size.LowPart);
    if (pbBuffer == NULL)
        return False;

    if (!m_file.Read(pbBuffer, pEntry->Size.LowPart))
    {
        Free(pbBuffer);
        return False;
    }

    Result = True;
    if ((*(PUInt32)pbBuffer & 0xFFFFFF) == ALICE_QNT_MAGIC)
    {
        Result = DecodeQNT(pbBuffer, pEntry->Size.LowPart, pFileInfo);
    }
    else
    {
        pFileInfo->FileType = *(PUInt32)pbBuffer == TAG4('RIFF') ? UNPACKER_FILE_TYPE_WAVE : UNPACKER_FILE_TYPE_BIN;
        pFileInfo->BinData.pbBuffer = pbBuffer;
        pFileInfo->BinData.BufferSize = pEntry->Size.LowPart;
        pbBuffer = NULL;
    }

    Free(pbBuffer);

    return Result;
}

Bool CDaiteikoku::DecodeQNT(PVoid pvQNT, SizeT Size, SFileInfo *pFileInfo)
{
    Bool Result;
    ALICE_QNT_HEADER *pHeader;

    UNUSED_VARIABLE(Size);

    Result = False;
    pHeader = (ALICE_QNT_HEADER *)pvQNT;
    switch (pHeader->Version)
    {
        case 1:
            Result = DecodeQNTV1(&pHeader->v1, pFileInfo);
            break;

        case 2:
            Result = DecodeQNTV2(&pHeader->v2, pFileInfo);
            break;
    }

    return Result;
}

Bool CDaiteikoku::DecodeQNTV1(ALICE_QNT_INFO_V1 *pHeader, SFileInfo *pFileInfo)
{
    UNUSED_VARIABLE(pHeader);
    UNUSED_VARIABLE(pFileInfo);
    return False;
}

Bool CDaiteikoku::DecodeQNTV2(ALICE_QNT_INFO_V2 *pHeader, SFileInfo *pFileInfo)
{
    Bool  Result;
    PByte pbRGB, pbAlpha, pbImage;
    ULong RGBSize, AlphaSize, Width, Height, Stride;
    IMG_BITMAP_HEADER *pBmpHeader;

    if (pHeader->Width == 0 || pHeader->Height == 0)
        return False;

    Width  = pHeader->Width  + (pHeader->Width & 1);
    Height = pHeader->Height + (pHeader->Height & 1);
    if (pHeader->AlphaLength != 0)
    {
        AlphaSize = Width * Height;
        pbAlpha = (PByte)Alloc(AlphaSize);
        if (pbAlpha == NULL)
            return False;
    }
    else
    {
        pbAlpha = NULL;
    }

    RGBSize = Width * Height * 3;
    pbRGB = (PByte)Alloc(RGBSize);
    if (pbRGB == NULL)
    {
        Free(pbAlpha);
        return False;
    }

    Stride = 0;
    pbImage = NULL;
    pBmpHeader = NULL;
    Result = False;
    LOOP_ONCE
    {
        if (pbAlpha != NULL)
        {
            Result = uncompress(
                        pbAlpha,
                        &AlphaSize,
                        (PByte)pHeader + pHeader->HeaderSize + pHeader->RGBLength - 8,
                        pHeader->AlphaLength);
            if (Result != Z_OK)
            {
                Result = False;
                break;
            }

            PByte p = pbAlpha;
            for (ULong w = Width - 1; w; --w)
            {
                ++p;
                p[0] = p[-1] - p[0];
            }

            ++p;
            for (ULong h = Height - 1; h; --h)
            {
                p[0] = p[-Width] - p[0];
                ++p;
                for (ULong w = Width - 1; w; --w)
                {
                    p[0] = ((p[-Width] + p[-1]) >> 1) - p[0];
                    ++p;
                }
            }
        }
        else
        {
            pbAlpha = (PByte)Alloc(Width * Height);
            if (pbAlpha == NULL)
                break;

            FillMemory(pbAlpha, Width * Height, -1);
        }

        Result = uncompress(pbRGB, &RGBSize, (PByte)pHeader + pHeader->HeaderSize - 8, pHeader->RGBLength);
        if (Result != Z_OK)
        {
            Result = False;
            break;
        }

        Result = False;
        pbImage = (PByte)Alloc(Width * Height * 4 + sizeof(*pBmpHeader));
        if (pbImage == NULL)
            break;

        pBmpHeader = (IMG_BITMAP_HEADER *)pbImage;
        InitBitmapHeader(pBmpHeader, pHeader->Width, pHeader->Height, 32, (PInt32)&Stride);
        pbImage += sizeof(*pBmpHeader);

        Bool  bIsHeightOdd;
        PByte p, r, g, b, a;
        ULong NextLine, StrideDiff;

        NextLine = Width * Height;
        r = pbRGB;
        g = r + NextLine;
        b = g + NextLine;
        a = pbAlpha;

#define ORIG 0

#if ORIG
        p = pbImage;
        Stride = Width * 3;
        for (ULong h = Height / 2; h; --h)
        {
            for (ULong w = Width / 2; w; --w)
            {
                p[0] = r[0];
                p[1] = g[0];
                p[2] = b[0];
                p[Stride + 0] = r[1];
                p[Stride + 1] = g[1];
                p[Stride + 2] = b[1];
                p[3] = r[2];
                p[4] = g[2];
                p[5] = b[2];
                p[Stride + 3] = r[3];
                p[Stride + 4] = g[3];
                p[Stride + 5] = b[3];

                p += 6;
                r += 4;
                g += 4;
                b += 4;
            }

            p += Stride;
        }
#else
        bIsHeightOdd = pHeader->Height & 1;
        StrideDiff = Width * 4 - Stride;
        p = pbImage + Stride * (pHeader->Height - 1);
        for (ULong h = Height / 2; h; --h)
        {
            PByte pBak = p;
            for (ULong w = Stride / 4 / 2; w; --w)
            {
                p[0] = r[0];
                p[1] = g[0];
                p[2] = b[0];
//                p[3] = a[0];

                p[4] = r[2];
                p[5] = g[2];
                p[6] = b[2];
//                p[7] = a[1];

                if (!bIsHeightOdd || h != 1)
                {
                    p[-Stride + 0] = r[1];
                    p[-Stride + 1] = g[1];
                    p[-Stride + 2] = b[1];
//                    p[-Stride + 3] = a[Width];

                    p[-Stride + 4] = r[3];
                    p[-Stride + 5] = g[3];
                    p[-Stride + 6] = b[3];
//                    p[-Stride + 7] = a[Width + 1];
                }
// 29A
                p += 8;
                r += 4;
                g += 4;
                b += 4;
//                a += 2;
            }

            if (StrideDiff != 0)
            {
                r += StrideDiff;
                g += StrideDiff;
                b += StrideDiff;
//                a += StrideDiff / 4;
            }

            p = pBak - Stride * 2;
        }
#endif

#if ORIG
        p = pbImage + 3;
        for (ULong w = Width - 1; w; --w)
        {
            p[0] = p[-3] - p[0];
            p[1] = p[-2] - p[1];
            p[2] = p[-1] - p[2];
            p += 3;
        }

        ULong stride = Width * 3;
        for (ULong h = Height - 1; h; --h)
        {
            p[0] = p[-stride + 0] - p[0];
            p[1] = p[-stride + 1] - p[1];
            p[2] = p[-stride + 2] - p[2];
            p += 3;
            for (ULong w = Width - 1; w; --w)
            {
                p[0] = ((p[-3] + p[-stride + 0]) >> 1) - p[0];
                p[1] = ((p[-2] + p[-stride + 1]) >> 1) - p[1];
                p[2] = ((p[-1] + p[-stride + 2]) >> 1) - p[2];
                p += 3;
            }
        }

        ULong diff;
        PByte prgb, pbTemp;
        IMG_BITMAP_HEADER hdr;

        InitBitmapHeader(&hdr, pHeader->Width, pHeader->Height, 32, (PInt32)&Stride);
        pbTemp = (PByte)Alloc(hdr.dwFileSize);
        p = pbTemp + sizeof(hdr);
        p += Stride * (pHeader->Height - 1);
        prgb = pbImage;
        diff = (Width - pHeader->Width) * 4;
        for (ULong h = pHeader->Height; h; --h)
        {
            PByte bak = prgb, baka = a;
            PByte pl = p;
            for (ULong w = pHeader->Width; w; --w)
            {
                *(PUInt32)p = (*(PUInt32)prgb & 0x00FFFFFF) | (*a << 24);
                p += 4;
                prgb += 3;
                ++a;
            }
            p = pl - Stride;
            p += diff;
            prgb = bak + Width * 3;
            a = baka + Width;
        }

        Free(pBmpHeader);
        pBmpHeader = (IMG_BITMAP_HEADER *)pbTemp;
        *pBmpHeader = hdr;
#else
        a = pbAlpha;
        p = pbImage + Stride * (pHeader->Height - 1);
        p[3] = *a++;
        p += 4;
        for (ULong w = Stride / 4 - 1; w; --w)
        {
            p[0] = p[-4] - p[0];
            p[1] = p[-3] - p[1];
            p[2] = p[-2] - p[2];
            p[3] = *a++;
            p += 4;
        }

        a = pbAlpha + Width;
        p = pbImage + Stride * (pHeader->Height - 2);
        for (ULong h = pHeader->Height - 1; h; --h)
        {
            PByte pBak = p;
            PByte pBaka = a;

            p[0] = p[Stride + 0] - p[0];
            p[1] = p[Stride + 1] - p[1];
            p[2] = p[Stride + 2] - p[2];
            p[3] = *a++;
            p += 4;

            for (ULong w = Stride / 4 - 1; w; --w)
            {
                p[0] = ((p[-4] + p[Stride + 0]) >> 1) - p[0];
                p[1] = ((p[-3] + p[Stride + 1]) >> 1) - p[1];
                p[2] = ((p[-2] + p[Stride + 2]) >> 1) - p[2];
                p[3] = *a++;
                p += 4;
            }

            a = pBaka + Width;
            p = pBak - Stride;
        }
#endif
        Result = True;
    }

    Free(pbAlpha);
    Free(pbRGB);

    if (Result)
    {
        pFileInfo->FileType = UNPACKER_FILE_TYPE_IMG;
        pFileInfo->FileNum = 1;
        pFileInfo->ImgData.pbBuffer     = (PByte)pBmpHeader;
        pFileInfo->ImgData.BufferSize   = pBmpHeader->dwFileSize;
        pFileInfo->ImgData.Width        = pHeader->Width;
        pFileInfo->ImgData.Heigth       = pHeader->Height;
        pFileInfo->ImgData.BitsPerPixel = 32;
    }
    else
    {
        Free(pbImage);
    }

    return Result;
}

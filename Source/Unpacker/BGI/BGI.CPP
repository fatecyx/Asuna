#define NRV2E

#include "BGI.H"
//#include "AudioPlayBack.h"
//#include "libvorbis/vorbisfile.h"
#include "ucl/ucl_conf.h"
#include "ucl/ucl.h"
//#include "n2_99.c"

LONG
WINAPI
EnumCallBack(
    MY_FILE_ENTRY_BASE *pEntry,
    LPWIN32_FIND_DATAW  pFindData,
    ULONG_PTR           Context
)
{
    UNREFERENCED_PARAMETER(Context);

    pEntry->Size.LowPart    = pFindData->nFileSizeLow;
    pEntry->Size.HighPart   = pFindData->nFileSizeHigh;
    lstrcpyW(pEntry->FileName, pFindData->cFileName);

    return 1;
}

ULONG CBGIUnpacker::Pack(PCWChar pszPath)
{
    return 0;
}

int __cdecl seek_func(void *datasource, ogg_int64_t offset, int whence)
{
    return my_fseek64((FILE *)datasource, offset, whence);
}
ULONG CBGIUnpacker::Pack(PCWChar pszPath)
{
    LARGE_INTEGER FileCount;
    MY_FILE_ENTRY_BASE *pEntry;

    if (!EnumDirectoryFiles(
            (PVOID *)&pEntry,
            L"*.*",
            sizeof(*pEntry),
            pszPath,
            &FileCount,
            (FEnumDirectoryFilesCallBack)EnumCallBack,
            0,
            EDF_SUBDIR))
    {
        return 0;
    }

    HANDLE              hFile, hFileArc;
    PVOID               pvFileBuffer;
    PBYTE               pbBuffer, pbCompressBuffer;
    ULONG               PackedFile, BytesTransferred, BufferSize, CompressBufferSize, PathLength;
    WCHAR               szPath[MAX_PATH];
    BGI_ARC_HEADER      ArcHeader;
    BGI_SOUND_HEADER    SoundHeader;
    BGI_ARC_ENTRY      *pArcEntry;

    lstrcpyW(szPath, pszPath);
    PathLength = StrLengthW(pszPath);
    if (pszPath[PathLength - 1] == '\\')
    {
        lstrcpyW(&szPath[PathLength - 1], L".arc");
        ++PathLength;
    }
    else
    {
        lstrcpyW(&szPath[PathLength], L".arc");
    }

    hFileArc = CreateFileW(
                    szPath,
                    GENERIC_READ|GENERIC_WRITE,
                    FILE_SHARE_READ,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    if (hFileArc == INVALID_HANDLE_VALUE)
    {
        EnumDirectoryFilesFree(pEntry);
        return 0;
    }

    PackedFile          = 0;
    pbBuffer            = NULL;
    pbCompressBuffer    = NULL;

    LOOP_ONCE
    {
        BufferSize          = 0x100000;
        CompressBufferSize  = 0x100000;
        pbBuffer = (PBYTE)Alloc(BufferSize);
        if (pbBuffer == NULL)
            break;

        pbCompressBuffer = (PBYTE)Alloc(CompressBufferSize);
        if (pbCompressBuffer == NULL)
            break;

        CAudioPlayback          ap;
        ucl_compress_config_t   UclConfig;

        FillMemory(&UclConfig, sizeof(UclConfig), -1);
        UclConfig.bb_endian  = 0;
        UclConfig.bb_size    = 32;
        UclConfig.max_offset = 0x3FFFFF;

        CopyMemory(ArcHeader.Magic, BGI_ARC_MAGIC, sizeof(ArcHeader.Magic));
        ArcHeader.FileCount = FileCount.LowPart;

        ZeroMemory(&SoundHeader, sizeof(SoundHeader));
        SoundHeader.cbSize  = sizeof(SoundHeader);
        SoundHeader.Magic   = BGI_SND_MAGIC;
        SoundHeader.State   = 3;

        WriteFile(hFileArc, &ArcHeader, sizeof(ArcHeader), &BytesTransferred, NULL);
        SetFilePointer(hFileArc, FileCount.LowPart * sizeof(*pArcEntry), NULL, FILE_CURRENT);
        for (ULONG Offset = 0, Count = FileCount.LowPart; Count; ++pEntry, --Count)
        {
            ULONG FileSize;

            hFile = CreateFileW(
                        pEntry->FileName,
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
            if (hFile == INVALID_HANDLE_VALUE)
                continue;

            if (pEntry->Size.LowPart > BufferSize)
            {
                BufferSize = pEntry->Size.LowPart;
                pbBuffer = (PBYTE)ReAlloc(pbBuffer, BufferSize);
                if (pbBuffer == NULL)
                {
                    pEntry -= FileCount.LowPart - Count;
                    goto _Exit;
                }
            }

            ReadFile(hFile, pbBuffer, pEntry->Size.LowPart, &FileSize, NULL);
            CloseHandle(hFile);
            pvFileBuffer = pbBuffer;

            pEntry->Offset.QuadPart = Offset;
            if (*(PULONG)pbBuffer == TAG4('OggS'))
            {
                FILE *fp;
                OggVorbis_File vf;
                ov_callbacks cb;

                fp = _wfopen(pEntry->FileName, L"rb+");
                if (fp == NULL)
                {
                    pEntry->Size.LowPart = 0;
                    continue;
                }

                *(PVOID *)&cb.read_func  = fread;
                *(PVOID *)&cb.seek_func  = seek_func;
                *(PVOID *)&cb.close_func = fclose;
                *(PVOID *)&cb.tell_func  = ftell;

                if (ov_open_callbacks(fp, &vf, NULL, 0, cb) != 0)
                {
                    pEntry->Size.LowPart = 0;
                    continue;
                }

                SoundHeader.Rate            = vf.vi->rate;
                SoundHeader.Channels        = vf.vi->channels;
                SoundHeader.Samples         = vf.pcmlengths[1];
                SoundHeader.AudioSteamSize  = pEntry->Size.LowPart;

                ov_clear(&vf);

                WriteFile(hFileArc, &SoundHeader, sizeof(SoundHeader), &BytesTransferred, NULL);
                pEntry->Size.LowPart += sizeof(SoundHeader);
                Offset += BytesTransferred;
            }
            else if ((*(PULONG)pbBuffer & 0xFFFFFF) == TAG3('UCA'))
            {
                INT Length;
                AUDIO_WAVE_HEADER *pWaveHeader;

                Length = -1;
                Length = UCADecode2(pbBuffer, pEntry->Size.LowPart, (PVOID *)&pWaveHeader, &Length, 44100);
                if (Length < 0)
                {
                    pEntry->Size.LowPart = 0;
                    continue;
                }

                SoundHeader.Rate = pWaveHeader->dwSamplesPerSec;
                SoundHeader.Channels = pWaveHeader->wChannels;
                SoundHeader.Samples = pWaveHeader->dwDataSize * 8 / pWaveHeader->wBitsPerSample;
                SoundHeader.AudioSteamSize = pEntry->Size.LowPart;

                UCAFree(pWaveHeader);

                WriteFile(hFileArc, &SoundHeader, sizeof(SoundHeader), &BytesTransferred, NULL);
                pEntry->Size.LowPart += sizeof(SoundHeader);
                Offset += BytesTransferred;
            }
            else if (*(PULONG)(pbBuffer + 4) == TAG4('ftyp') && *(PULONG)(pbBuffer + 8) == TAG4('mp42'))
            {
                Large_Integer Length;
                const BASS_CHANNELINFO *ci;

                Length.QuadPart = pEntry->Size.QuadPart;
                if (!ap.Open(pbBuffer, TRUE, &Length, TRUE))
                {
                    pEntry->Size.LowPart = 0;
                    continue;
                }

                ci = ap.GetChannelInfo();
                SoundHeader.Rate = ci->freq;
                SoundHeader.Channels = ci->chans;
                SoundHeader.Samples = ap.GetSamples();
                SoundHeader.AudioSteamSize = pEntry->Size.LowPart;

                WriteFile(hFileArc, &SoundHeader, sizeof(SoundHeader), &BytesTransferred, NULL);
                pEntry->Size.LowPart += sizeof(SoundHeader);
                Offset += BytesTransferred;
            }
            else if (!CompareMemory(pbBuffer, BGI_BURIKO_SCRIPT_MAGIC, sizeof(BGI_BURIKO_SCRIPT_MAGIC)))
            {
                if (FileSize + FileSize / 8 + 256 + sizeof(MY_MAGIC) > CompressBufferSize)
                {
                    CompressBufferSize = FileSize * 2;
                    pbCompressBuffer = (PBYTE)ReAlloc(pbCompressBuffer, CompressBufferSize);
                    if (pbCompressBuffer == NULL)
                        goto _Exit;
                }

                LONG Result;
                UINT OutSize = CompressBufferSize - sizeof(MY_MAGIC);

                Result = ucl_nrv2e_99_compress(
                            pbBuffer,
                            FileSize,
                            pbCompressBuffer + sizeof(MY_MAGIC),
                            &OutSize,
                            NULL,
                            10,
                            &UclConfig,
                            NULL
                         );

                if (Result != UCL_E_OK)
                    break;

                CopyMemory(pbCompressBuffer, MY_MAGIC, sizeof(MY_MAGIC));

                OutSize += sizeof(MY_MAGIC);
                pEntry->Size.QuadPart = OutSize;
                pvFileBuffer = pbCompressBuffer;
                FileSize = OutSize;
            }

            WriteFile(hFileArc, pvFileBuffer, FileSize, &BytesTransferred, NULL);
            Offset += BytesTransferred;
        }

        SetFilePointer(hFileArc, sizeof(ArcHeader), NULL, FILE_BEGIN);

        pEntry -= FileCount.LowPart;
        pArcEntry = (BGI_ARC_ENTRY *)Alloc(FileCount.LowPart * sizeof(*pArcEntry), HEAP_ZERO_MEMORY);
        if (pArcEntry == NULL)
            break;

        PathLength = findextw(szPath) + 1 - szPath;
        for (ULONG Count = FileCount.LowPart; Count; --Count)
        {
            ULONG64 Ext;
            PWCHAR  pszExtension;

            pArcEntry->Offset = pEntry->Offset.LowPart;
            pArcEntry->Size   = pEntry->Size.LowPart;

            pszExtension = findextw(pEntry->FileName + PathLength);
            Ext = *(PULONG64)(pszExtension + 1) & 0xFFFFFFDFFFDFFFDF;
            if (Ext == TAG3W('BMP') ||
                Ext == TAG3W('PNG') ||
                Ext == TAG3W('OGG') ||
                Ext == TAG3W('UCA') ||
                Ext == TAG3W('UCI') ||
                Ext == (TAG3W('M4A') & 0xFFFFFFDFFFDFFFDF))
            {
                *pszExtension = 0;
            }

            WideCharToMultiByte(
                CP_GB2312,
                0,
                pEntry->FileName + PathLength,
                -1,
                pArcEntry->FileName,
                countof(pArcEntry->FileName),
                NULL,
                NULL
            );

            ++pArcEntry;
            ++pEntry;
        }

        pEntry    -= FileCount.LowPart;
        pArcEntry -= FileCount.LowPart;

        WriteFile(hFileArc, pArcEntry, FileCount.LowPart * sizeof(*pArcEntry), &BytesTransferred, NULL);
        Free(pArcEntry);

        PackedFile = FileCount.LowPart;
    }

_Exit:
    CloseHandle(hFileArc);
    Free(pbBuffer);
    Free(pbCompressBuffer);
    EnumDirectoryFilesFree(pEntry);

    return PackedFile;
}

BOOL CBGIUnpacker::Open(PCWCHAR pszFileName)
{
    ULONG                BeginOffset;
    BGI_ARC_HEADER       Header;
    BGI_ARC_ENTRY       *pArcEntry;
    MY_FILE_ENTRY_BASE  *pEntry;

    ReleaseAll();

    if (!m_file.Open(pszFileName))
        return FALSE;

    if (!m_file.Read(&Header, sizeof(Header)))
        return FALSE;

    if (!CompareMemory(Header.Magic, BGI_SDC_MAGIC, sizeof(BGI_SDC_MAGIC)))
    {
        UNPACKER_FILE_INFO FileInfo;
        MY_FILE_ENTRY_BASE Entry;

        Entry.Offset.QuadPart = 0;
        Entry.Size.QuadPart = m_file.GetSize64();
        if (!GetFileData(&FileInfo, &Entry))
            return FALSE;

        lstrcpyW(Entry.FileName, pszFileName);
        lstrcatW(Entry.FileName, L".gbd_upk");

        if (m_file.Create(Entry.FileName))
        {
            m_file.Write(FileInfo.BinData.pbBuffer, FileInfo.BinData.BufferSize);
        }

        FreeFileData(&FileInfo);
        return FALSE;
    }
    if (CompareMemory(Header.Magic, BGI_ARC_MAGIC, sizeof(Header.Magic)))
    {
        return FALSE;
    }

    m_Index.FileCount.QuadPart = Header.FileCount;
    pEntry = (MY_FILE_ENTRY_BASE *)Alloc(m_Index.FileCount.LowPart * m_Index.cbEntrySize);
    if (pEntry == NULL)
        return FALSE;

    m_Index.pEntry = pEntry;

    pArcEntry = (BGI_ARC_ENTRY *)Alloc(Header.FileCount * sizeof(*pArcEntry));
    if (pArcEntry == NULL)
        return FALSE;

    if (!m_file.Read(pArcEntry, Header.FileCount * sizeof(*pArcEntry)))
    {
        Free(pArcEntry);
        return FALSE;
    }

    BeginOffset = Header.FileCount * sizeof(*pArcEntry) + sizeof(Header);
    for (ULONG Count = Header.FileCount; Count; --Count)
    {
        ULONG Length;
        Length = MultiByteToWideChar(
                    CP_GB2312,
                    0,
                    pArcEntry->FileName,
                    sizeof(pArcEntry->FileName),
                    pEntry->FileName,
                    countof(pEntry->FileName)
                );

        pEntry->FileName[Length] = 0;
        pEntry->Offset.QuadPart  = pArcEntry->Offset + BeginOffset;
        pEntry->Size.QuadPart    = pArcEntry->Size;

        ++pEntry;
        ++pArcEntry;
    }

    pArcEntry -= Header.FileCount;
    Free(pArcEntry);
    return TRUE;
}

BOOL CBGIUnpacker::GetFileData(UNPACKER_FILE_INFO *pFileInfo, const MY_FILE_ENTRY_BASE *pBaseEntry, BOOL)
{
    if (!m_file.SeekEx(m_file.FILE_SEEK_BEGIN, pBaseEntry->Offset))
        return FALSE;

    PBYTE pbBuffer, pbDecompressed;
    ULONG Size;
    BGI_GRP_HEADER   *pGrp;
    BGI_SOUND_HEADER *pSound;

    Size = pBaseEntry->Size.LowPart;
    pbBuffer = (PBYTE)Alloc(Size);
    if (pbBuffer == NULL)
        return FALSE;

    if (!m_file.Read(pbBuffer, Size))
    {
        Free(pbBuffer);
        return FALSE;
    }

    pFileInfo->FileType = UNPACKER_FILE_TYPE_BIN;
    pbDecompressed = pbBuffer;

    if (!CompareMemory(pbBuffer, BGI_DSC_MAGIC, sizeof(BGI_DSC_MAGIC)))
    {
        Size = DecompressDSC(pbBuffer, Size, (PVOID *)&pbDecompressed);
    }
    else if (!CompareMemory(pbBuffer, BGI_SDC_MAGIC, sizeof(BGI_SDC_MAGIC)))
    {
        Size = DecompressSDC(pbBuffer, Size, (PVOID *)&pbDecompressed);
    }
    else if (!CompareMemory(pbBuffer, BGI_BG_MAGIC, sizeof(BGI_BG_MAGIC)))
    {
        pFileInfo->FileType = UNPACKER_FILE_TYPE_BMP;
        Size = DecompressBG(pbBuffer, Size, (PVOID *)&pbDecompressed);
    }
    else if (!CompareMemory(pbBuffer, MY_MAGIC, sizeof(MY_MAGIC)))
    {
        UINT OutSize = Size * 20;

        pbDecompressed = (PBYTE)Alloc(OutSize);
        if (pbDecompressed == NULL)
        {
            Free(pbBuffer);
            return FALSE;
        }

        Size = UCL_NRV2E_DecompressASMFast32(pbBuffer + sizeof(MY_MAGIC), pbDecompressed);
    }

    pGrp    = (BGI_GRP_HEADER *)pbDecompressed;
    pSound  = (BGI_SOUND_HEADER *)pbDecompressed;
    if (Size == pGrp->Width * pGrp->Height * pGrp->BitsPerPixel / 8 + sizeof(*pGrp))
    {
        ULONG Stride, StrideRaw;
        PBYTE pbSrc, pbDest;
        IMG_BITMAP_HEADER *pBitMap;

        if (pbBuffer != pbDecompressed)
        {
            Free(pbBuffer);
            pbBuffer = pbDecompressed;
        }

        Size = ((pGrp->Width * pGrp->BitsPerPixel / 8 + 3) & ~3) * pGrp->Height + sizeof(*pBitMap);
        pBitMap = (IMG_BITMAP_HEADER *)Alloc(Size);
        if (pBitMap == NULL)
        {
            Free(pbBuffer);
            return FALSE;
        }

        pFileInfo->FileType = UNPACKER_FILE_TYPE_BMP;

        InitBitmapHeader(pBitMap, pGrp->Width, pGrp->Height, pGrp->BitsPerPixel, (PInt32)&Stride);
        pbDest = (PBYTE)(pBitMap + 1) + (pBitMap->Info.dwHeight - 1) * Stride;
        pbSrc  = (PBYTE)(pGrp + 1);
        StrideRaw = pBitMap->Info.dwWidth * pBitMap->Info.wBit / 8;

        for (ULONG Height = pBitMap->Info.dwHeight; Height; --Height)
        {
            CopyMemory(pbDest, pbSrc, StrideRaw);
            pbDest -= Stride;
            pbSrc  += StrideRaw;
        }

        pbDecompressed = (PBYTE)pBitMap;
    }
    else if (pSound->cbSize == sizeof(*pSound) && pSound->Magic == BGI_SND_MAGIC)
    {
        pbDecompressed = (PBYTE)Alloc(pSound->AudioSteamSize);
        if (pbDecompressed == NULL)
        {
            Free(pbBuffer);
            return FALSE;
        }

        CopyMemory(pbDecompressed, pSound + 1, pSound->AudioSteamSize);
        Size = pSound->AudioSteamSize;

        if (*(PULONG)(pSound + 1) == TAG4('OggS'))
            lstrcatW((PWCHAR)pBaseEntry->FileName, L".ogg");
        else if ((*(PULONG)(pSound + 1) & 0x00FFFFFF) == TAG3('UCA'))
            lstrcatW((PWCHAR)pBaseEntry->FileName, L".uca");
        else if (*(PULONG)((PBYTE)(pSound + 1) + 4) == TAG4('ftyp'))
            lstrcatW((PWCHAR)pBaseEntry->FileName, L".m4a");
    }
    else if ((*(PULONG)pbBuffer & 0x00FFFFFF) == TAG3('UCI'))
    {
        lstrcatW((PWCHAR)pBaseEntry->FileName, L".uci");
    }
    else if (*(PUSHORT)pbBuffer == TAG2('BM'))
    {
        lstrcatW((PWCHAR)pBaseEntry->FileName, L".bmp");
    }

    if (pbDecompressed != NULL && pbBuffer != pbDecompressed)
    {
        Free(pbBuffer);
        pbBuffer = pbDecompressed;
    }

    pFileInfo->BinData.pbBuffer   = pbBuffer;
    pFileInfo->BinData.BufferSize = Size;

    return TRUE;
}
/*
VOID InitBG1(PULONG pDict, PVOID pvCompressed, ULONG DictSize)
{
    PBYTE pbBuffer = (PBYTE)pvCompressed;

    for (ULONG Index = 0; DictSize; ++Index, --DictSize)
    {
        ULONG b, v1 = 0, v2 = 0;
        do
        {
            b = *pbBuffer++;
            v1 |= (b & 0x7F) << v2;
            v2 += 7;
            b &= 0x80;
        } while (b != 0);

        pDict[Index] = v1;
    }
}

VOID InitBG2(PULONG pDict1, PULONG pDict2, ULONG DictSize)
{
    ;
}
*/
ULONG CBGIUnpacker::DecompressBG(PVOID pvCompressed, ULONG CompressedSize, PVOID *pvDecompressed)
{
    ULONG Size, Stride, PaletteSize;
    PVOID pvBuffer;
    PBYTE pbSrc, pbDest;
    IMG_BITMAP_HEADER *pBitMap;
    BGI_COMPRESSED_BG_HEADER *pBG;

    UNREFERENCED_PARAMETER(CompressedSize);

    *pvDecompressed = NULL;

    pBG = (BGI_COMPRESSED_BG_HEADER *)pvCompressed;
    Size = ((pBG->Width * pBG->BitsPerPixel / 8 + 3) & ~3) * pBG->Height + sizeof(*pBitMap);
    pvBuffer = Alloc(Size);
    if (pvBuffer == NULL)
        return 0;

    PaletteSize = pBG->BitsPerPixel == 8 ? 256 * 4 : 0;
    pBitMap = (IMG_BITMAP_HEADER *)Alloc(Size + PaletteSize);
    if (pBitMap == NULL)
    {
        Free(pvBuffer);
        return 0;
    }

    Size = bg_decompress((bg_header_t *)pBG, CompressedSize, (PBYTE)pvBuffer, Size);
    if (Size != 0)
    {
        ULONG StrideRaw;

        InitBitmapHeader(pBitMap, pBG->Width, pBG->Height, pBG->BitsPerPixel, (PInt32)&Stride);
        pbSrc  = (PBYTE)pvBuffer;
        pbDest = (PBYTE)(pBitMap + 1) + Stride * (pBitMap->Info.dwHeight - 1) + PaletteSize;

        *pvDecompressed = pBitMap;

        if (PaletteSize != 0)
        {
            PULONG pPalette = (PULONG)(pBitMap + 1);
            for (ULONG Color = 0, Count = 256; Count; Color += 0x00010101, --Count)
                *pPalette++ = Color;
        }

        StrideRaw = pBitMap->Info.dwWidth * pBitMap->Info.wBit / 8;
        for (ULONG Height = pBitMap->Info.dwHeight; Height; --Height)
        {
            CopyMemory(pbDest, pbSrc, StrideRaw);
            pbDest -= Stride;
            pbSrc  += StrideRaw;
        }

        Size = pBitMap->dwFileSize;
    }

    Free(pvBuffer);

    return Size;

/*
    ULONG Dict1[0x100], Dict2[0x100];
    BGI_COMPRESSED_BG_HEADER *pBG;

    UNREFERENCED_PARAMETER(CompressedSize);

    *pvDecompressed = NULL;
    pBG = (BGI_COMPRESSED_BG_HEADER *)pvCompressed;

    InitBG1(Dict1, pBG + 1, countof(Dict1));
    InitBG2(Dict1, Dict2, countof(Dict2));

    return 0;
*/
}

ULONG CBGIUnpacker::DecompressSDC(PVOID pvCompressed, ULONG CompressedSize, PVOID *pvDecompressed)
{
    PBYTE pbCompressed, pbDecompressed;
    BGI_SDC_FORMAT_HEADER *pSdc, SDC;

    UNREFERENCED_PARAMETER(CompressedSize);
    *pvDecompressed = NULL;

    pSdc = (BGI_SDC_FORMAT_HEADER *)pvCompressed;
    SDC = *pSdc;
    if (!DecryptSDC(pSdc, pSdc))
        return 0;

    pbDecompressed = (PBYTE)Alloc(SDC.DecompressedSize);
    if (pbDecompressed == NULL)
        return 0;

    *pvDecompressed = pbDecompressed;
    pbCompressed = (PBYTE)(pSdc);
    for (ULONG Count = SDC.CompressedSize; Count; )
    {
        LONG b = (CHAR)*pbCompressed++;

        if (b < 0)
        {
            PBYTE pbSrc;

            Count -= 2;

            pbSrc = pbDecompressed - 2 - ((b & 7) << 8) - *pbCompressed++;
            for (ULONG Size = (((ULONG)b >> 3) & 0xF) + 2; Size; --Size)
                *pbDecompressed++ = *pbSrc++;
        }
        else
        {
            ++b;
            Count -= b + 1;
            CopyMemory(pbDecompressed, pbCompressed, b);
            pbDecompressed += b;
            pbCompressed   += b;
        }
    }

    return pbDecompressed - (PBYTE)*pvDecompressed;
}

BOOL CBGIUnpacker::DecryptSDC(BGI_SDC_FORMAT_HEADER *pSdc, PVOID pvDecryptBuffer)
{
    ULONG Key, CheckSum, CheckXor;
    PBYTE pbBuffer, pbSdc;
    BGI_SDC_FORMAT_HEADER SDC;

    if (pSdc->CompressedSize == 0)
        return FALSE;

    SDC      = *pSdc;
    Key      = SDC.Key;
    CheckSum = 0;
    CheckXor = 0;
    pbSdc    = (PBYTE)(pSdc + 1);
    pbBuffer = (PBYTE)pvDecryptBuffer;

    do
    {
        *pbBuffer++ = *pbSdc - (BYTE)UpdateKey(Key);
        CheckSum += *pbSdc;
        CheckXor ^= *pbSdc;
        ++pbSdc;
    }
    while (--SDC.CompressedSize);

    return SDC.CheckSum == (USHORT)CheckSum && SDC.CheckXor == (USHORT)CheckXor;
}

VOID CBGIUnpacker::InitTree(BGI_DSC_FORMAT_TREE_NODE *pDict, PVOID pvDscBuffer)
{
    PBYTE pbDsc;
    BGI_DSC_FORMAT_HEADER *pDscHeader;
    ULONG NodeCount, Key, *pNode, Node[sizeof(pDscHeader->Dict)], Tree[2][sizeof(pDscHeader->Dict)];

    pDscHeader = (BGI_DSC_FORMAT_HEADER *)pvDscBuffer;
    pbDsc = pDscHeader->Dict;

    Key = pDscHeader->Key;
    pNode = Node;
    for (ULONG Index = 0, Count = sizeof(pDscHeader->Dict); Count; ++Index, --Count)
    {
        ULONG Code;

        Code = (BYTE)(*pbDsc++ - (BYTE)UpdateKey(Key));
        if (Code == 0)
            continue;

        *pNode++ = (Code << 16) | Index;
    }

    *pNode = 0;
    NodeCount = pNode - Node;

    pNode = Node;
    for (ULONG i = NodeCount; i; --i)
    {
        for (ULONG j = 0; j != i - 1; ++j)
        {
            if (pNode[j] > pNode[j + 1])
                Swap(pNode[j], pNode[j + 1]);
        }
    }

    ULONG   NodeLeft, LeftIndex;
    PULONG  pTree1, pTree2, pTreePrev;

    LeftIndex   = 1;
    NodeLeft    = 1;
    pNode       = Node;
    pTree1      = Tree[0];
    Tree[0][0]  = 0;
    for (ULONG TreeIndex = 0, Index = 0; NodeCount; pTree1 = pTreePrev, ++Index)
    {
        TreeIndex ^= 1;
        pTree2 = Tree[TreeIndex];
        pTreePrev = pTree2;

        ULONG EquCount = 0;

        while (HIWORD(*pNode) == Index)
        {
            ULONG Idx;

            Idx = *pTree1++;
            pDict[Idx].bUnknown = FALSE;
            pDict[Idx].NodeIndex = *pNode & 0x1FF;
            ++pNode;
            ++EquCount;
            --NodeCount;
        }

        NodeLeft -= EquCount;
        for (ULONG Count = NodeLeft; Count; --Count)
        {
            ULONG Idx;

            Idx = *pTree1++;
            pDict[Idx].bUnknown = TRUE;
            for (ULONG *p = pDict[Idx].Index, Count = countof(pDict->Index); Count; ++p, --Count)
            {
                *p = LeftIndex;
                *pTree2++ = LeftIndex;
                ++LeftIndex;
            }
        }

        NodeLeft *= 2;
    }
}

ULONG CBGIUnpacker::UpdateKey(ULONG &OldKey)
{
    ULONG Key, Key1, Key2, Key3;

    Key = OldKey;

    Key1 = LOWORD(Key) * 0x4E35;
    Key2 = HIWORD(Key) * 0x4E35;
    Key3 = Key * 0x15A + Key2 + HIWORD(Key1);

    Key1 = LOWORD(Key1);
    Key3 = LOWORD(Key3);

    OldKey = (Key3 << 16) + Key1 + 1;

    return Key3 & 0x7FFF;
}

ULONG CBGIUnpacker::DecompressDSC(PVOID pvCompressed, ULONG CompressedSize, PVOID *pvDecompressed)
{
    PBYTE pbData, pbBuffer;
    BGI_DSC_FORMAT_HEADER *pDsc;
    BGI_DSC_FORMAT_TREE_NODE TreeNode[0x400];

    UNREFERENCED_PARAMETER(CompressedSize);

    pDsc = (BGI_DSC_FORMAT_HEADER *)pvCompressed;
    *pvDecompressed = (PBYTE)Alloc(pDsc->DecompressSize);
    if (*pvDecompressed == NULL)
        return 0;

    InitTree(TreeNode, pDsc);

    pbData = (PBYTE)(pDsc + 1);

    if (pDsc->DataSize <= 0)
        return 0;

    ULONG b, Index, Bits;

    Bits     = 0;
    b        = 0;
    pbBuffer = (PBYTE)*pvDecompressed;
    for (ULONG DataSize = pDsc->DataSize; DataSize; --DataSize)
    {
        Index = 0;
        LOOP_ALWAYS
        {
            if (Bits == 0)
            {
                Bits = 8;
                b = *pbData++;
            }

            Index = Index * 4 + (b >> 7);

            b = (BYTE)((BYTE)b + (BYTE)b);
            --Bits;
            Index = ((PULONG)TreeNode)[Index + 2];
            if (!TreeNode[Index].bUnknown)
                break;
        }

        Index = LOWORD(TreeNode[Index].NodeIndex);
        if (HIBYTE(Index) != 1)
        {
            *pbBuffer++ = LOBYTE(Index);
            continue;
        }

        b >>= 8 - Bits;
        if (Bits < 0xC)
        {
            ULONG Count = (0xB - Bits) / 8 + 1;
            Bits += Count * 8;
            for (; Count; --Count)
                b = (b << 8) + *pbData++;
        }

        Bits -= 0xC;

        PBYTE pbSrc;
        ULONG DupCount;

        DupCount = (USHORT)(b >> Bits);
        b = (BYTE)(b << (8 - Bits));
        pbSrc = pbBuffer - DupCount;
        pbSrc -= 2;
        for (ULONG Count = LOBYTE(Index) + 2; Count; --Count)
            *pbBuffer++ = *pbSrc++;
    }

    return pbBuffer - (PBYTE)*pvDecompressed;
}

ASM ULONG FASTCALL CBGIUnpacker::UCL_NRV2E_DecompressASMFast32(PVOID /* pvInput */, PVOID /* pvOutput */)
{
    INLINE_ASM
    {
        add     esp, -0x14;
        mov     [esp + 0x00], ebx;
        mov     [esp + 0x04], ebp;
        mov     [esp + 0x08], esi;
        mov     [esp + 0x0C], edi;
        mov     [esp + 0x10], edx;
        cld;
        mov     esi, ecx;
        mov     edi, edx;
        or      ebp, 0xFFFFFFFF;
        xor     ecx, ecx;
        jmp L029;

        INLINE_ASM __emit 0x8D INLINE_ASM __emit 0xB4 INLINE_ASM __emit 0x26 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00;   // lea esi, [esi]
        INLINE_ASM __emit 0x8D INLINE_ASM __emit 0xB4 INLINE_ASM __emit 0x26 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00;   // lea esi, [esi]
L022:
        mov     al, byte ptr [esi];
        inc     esi;
        mov     byte ptr [edi], al;
        inc     edi;
L026:
        add     ebx, ebx;
        jnb L033;
        jnz L022;
L029:
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
        jb L022;
L033:
        mov     eax, 0x1;
L034:
        add     ebx, ebx;
        jnz L039;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L039:
        adc     eax, eax;
        add     ebx, ebx;
        jnb L047;
        jnz L055;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
        jb L055;
L047:
        dec     eax;
        add     ebx, ebx;
        jnz L053;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L053:
        adc     eax, eax;
        jmp L034;
L055:
        sub     eax, 0x3;
        jb L072;
        shl     eax, 0x8;
        mov     al, byte ptr [esi];
        inc     esi;
        xor     eax, 0xFFFFFFFF;
        je L120;
        sar     eax, 1;
        mov     ebp, eax;
        jnb L078;
L065:
        add     ebx, ebx;
        jnz L070;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L070:
        adc     ecx, ecx;
        jmp L099;
L072:
        add     ebx, ebx;
        jnz L077;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L077:
        jb L065;
L078:
        inc     ecx;
        add     ebx, ebx;
        jnz L084;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L084:
        jb L065;
L085:
        add     ebx, ebx;
        jnz L090;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L090:
        adc     ecx, ecx;
        add     ebx, ebx;
        jnb L085;
        jnz L098;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
        jnb L085;
L098:
        add     ecx, 0x2;
L099:
        cmp     ebp, -0x500;
        adc     ecx, 0x2;
        lea     edx, dword ptr [edi+ebp];
        cmp     ebp, -0x4;
        jbe L111;
L104:
        mov     al, byte ptr [edx];
        inc     edx;
        mov     byte ptr [edi], al;
        inc     edi;
        dec     ecx;
        jnz L104;
        jmp L026;
L111:
        mov     eax, dword ptr [edx];
        add     edx, 0x4;
        mov     dword ptr [edi], eax;
        add     edi, 0x4;
        sub     ecx, 0x4;
        ja L111;
        add     edi, ecx;
        xor     ecx, ecx;
        jmp L026;
L120:
        mov     eax, edi;
        mov     ebx, [esp + 0x00];
        mov     ebp, [esp + 0x04];
        mov     esi, [esp + 0x08];
        mov     edi, [esp + 0x0C];
        sub     eax, [esp + 0x10];
        add     esp, 0x14;
        ret;
    }
}

// copy from crass

/********************* CompressedBG___ *********************/

void bits_init(struct bits *bits, unsigned char *stream, unsigned long stream_length)
{
    memset(bits, 0, sizeof(*bits));
    bits->stream = stream;
    bits->stream_length = stream_length;
}

int bits_get_high(struct bits *bits, unsigned int req_bits, unsigned int *retval)
{
    unsigned int bits_value = 0;

    while (req_bits > 0) {
        unsigned int req;

        if (!bits->curbits) {
            if (bits->curbyte >= bits->stream_length)
                return -1;
            bits->cache = bits->stream[bits->curbyte++];
            bits->curbits = 8;
        }

        if (bits->curbits < req_bits)
            req = bits->curbits;
        else
            req = req_bits;

        bits_value <<= req;
        bits_value |= bits->cache >> (bits->curbits - req);
        bits->cache &= (1 << (bits->curbits - req)) - 1;
        req_bits -= req;
        bits->curbits -= req;
    }
    *retval = bits_value;
    return 0;
}

int bit_get_high(struct bits *bits, void *retval)
{
    return bits_get_high(bits, 1, (unsigned int *)retval);
}

u8 update_key(u32 *key, u8 *magic)
{
    u32 v0, v1;

    v0 = (*key & 0xffff) * 20021;
    v1 = (magic[1] << 24) | (magic[0] << 16) | (*key >> 16);
    v1 = v1 * 20021 + *key * 346;
    v1 = (v1 + (v0 >> 16)) & 0xffff;
    *key = (v1 << 16) + (v0 & 0xffff) + 1;
    return v1 & 0x7fff;
}

void
CBGIUnpacker::
decode_bg(
    unsigned char *enc_buf,
    unsigned int enc_buf_len,
    unsigned int key,
    unsigned char *ret_sum,
    unsigned char *ret_xor
)
{
	unsigned char sum = 0;
	unsigned char xor = 0;
	u8 magic[2] = { 0, 0 };

	for (unsigned int i = 0; i < enc_buf_len; i++) {
		enc_buf[i] -= update_key(&key, magic);
		sum += enc_buf[i];
		xor ^= enc_buf[i];
	}
	*ret_sum = sum;
	*ret_xor = xor;
}

unsigned int CBGIUnpacker::bg_create_huffman_tree(bg_huffman_node *nodes, u32 *leaf_nodes_weight)
{
	unsigned int parent_node_index = 256;	/* 父节点从nodes[]的256处开始 */
	bg_huffman_node *parent_node = &nodes[parent_node_index];
	unsigned int root_node_weight = 0;	/* 根节点权值 */
	unsigned int i;

	/* 初始化叶节点 */
	for (i = 0; i < 256; i++) {
		nodes[i].valid = !!leaf_nodes_weight[i];
		nodes[i].weight = leaf_nodes_weight[i];
		nodes[i].is_parent = 0;
		root_node_weight += nodes[i].weight;
	}

	LOOP_ALWAYS {
		unsigned int child_node_index[2];

		/* 创建左右子节点 */
		for (i = 0; i < 2; i++) {
			unsigned int min_weight;

			min_weight = -1;
			child_node_index[i] = -1;
			/* 遍历nodes[], 找到weight最小的2个节点作为子节点 */
			for (unsigned int n = 0; n < parent_node_index; n++) {
				if (nodes[n].valid) {
					if (nodes[n].weight < min_weight) {
						min_weight = nodes[n].weight;
						child_node_index[i] = n;
					}
				}
			}
			/* 被找到的子节点标记为无效，以便不参与接下来的查找 */
			nodes[child_node_index[i]].valid = 0;
			nodes[child_node_index[i]].parent_index = parent_node_index;
		}
		/* 创建父节点 */
		parent_node->valid = 1;
		parent_node->is_parent = 1;
		parent_node->left_child_index = child_node_index[0];
		parent_node->right_child_index = child_node_index[1];
		parent_node->weight = nodes[parent_node->left_child_index].weight
			+ nodes[parent_node->right_child_index].weight;
		if (parent_node->weight == root_node_weight)
			break;
		parent_node = &nodes[++parent_node_index];
	}

	return parent_node_index;
}

ULONG
CBGIUnpacker::
bg_huffman_decompress(
    bg_huffman_node *huffman_nodes,
    unsigned int root_node_index,
	unsigned char *uncompr,
    unsigned int uncomprlen,
	unsigned char *compr,
    unsigned int comprlen
)
{
	struct bits bits;
    unsigned int act_uncomprlen;

	bits_init(&bits, compr, comprlen);
	for (act_uncomprlen = 0; act_uncomprlen < uncomprlen; act_uncomprlen++) {
		unsigned char child;
		unsigned int node_index;

		node_index = root_node_index;
		do {
			if (bit_get_high(&bits, &child))
				goto out;

			if (!child)
				node_index = huffman_nodes[node_index].left_child_index;
			else
				node_index = huffman_nodes[node_index].right_child_index;
		} while (huffman_nodes[node_index].is_parent);

		uncompr[act_uncomprlen] = node_index;
	}
out:
	return act_uncomprlen;
}

ULONG
CBGIUnpacker::
zero_decompress(
    unsigned char *uncompr,
    unsigned int uncomprlen,
    unsigned char *compr,
    unsigned int comprlen
)
{
	unsigned int act_uncomprlen = 0;
	int dec_zero = 0;
	unsigned int curbyte = 0;

	LOOP_ALWAYS {
		unsigned int bits = 0;
		unsigned int copy_bytes = 0;
		unsigned char code;

		do {
			if (curbyte >= comprlen)
				goto out;

			code = compr[curbyte++];
			copy_bytes |= (code & 0x7f) << bits;
			bits += 7;
		} while (code & 0x80);

		if (act_uncomprlen + copy_bytes > uncomprlen)
			break;
		if (!dec_zero && (curbyte + copy_bytes > comprlen))
			break;

		if (!dec_zero) {
			memcpy(&uncompr[act_uncomprlen], &compr[curbyte], copy_bytes);
			curbyte += copy_bytes;
			dec_zero = 1;
		} else {
			memset(&uncompr[act_uncomprlen], 0, copy_bytes);
			dec_zero = 0;
		}
		act_uncomprlen += copy_bytes;
	}
out:
	return act_uncomprlen;
}

void
CBGIUnpacker::
bg_average_defilting(
    unsigned char *dib_buf,
    unsigned int width,
    unsigned int height,
    unsigned int bpp
)
{
	unsigned int line_len = width * bpp;

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			for (unsigned int p = 0; p < bpp; p++) {
				unsigned int a, b;
				unsigned int avg;

				b = y ? dib_buf[(y - 1) * line_len + x * bpp + p] : -1;
				a = x ? dib_buf[y * line_len + (x - 1) * bpp + p] : -1;
				avg = 0;

				if (a != -1)
					avg += a;
				if (b != -1)
					avg += b;
				if (a != -1 && b != -1)
					avg /= 2;

				dib_buf[y * line_len + x * bpp + p] += avg;
			}
		}
	}
}

ULONG
CBGIUnpacker::
bg_decompress(
    bg_header_t *bg_header,
    unsigned int bg_len,
    unsigned char *image_buf,
    unsigned int image_size
)
{
	unsigned int act_uncomprlen = 0;
	unsigned int i;
	unsigned char *enc_buf = (unsigned char *)(bg_header + 1);

	/* 解密叶节点权值 */
	unsigned char sum;
	unsigned char xor;
	decode_bg(enc_buf, bg_header->encode_length, bg_header->key, &sum, &xor);
	if (sum != bg_header->sum_check || xor != bg_header->xor_check)
		return 0;

	/* 初始化叶节点权值 */
	u32 leaf_nodes_weight[256];
	unsigned int curbyte = 0;
	for (i = 0; i < 256; i++) {
		unsigned int bits = 0;
		u32 weight = 0;
		unsigned char code;

		do {
			if (curbyte >= bg_header->encode_length)
				return 0;
			code = enc_buf[curbyte++];
			weight |= (code & 0x7f) << bits;
			bits += 7;
		} while (code & 0x80);
		leaf_nodes_weight[i] = weight;
	}

	bg_huffman_node nodes[511];
	unsigned int root_node_index = bg_create_huffman_tree(nodes, leaf_nodes_weight);
	unsigned char *zero_compr = (unsigned char *)Alloc(bg_header->zero_comprlen);
	if (!zero_compr)
		return 0;

	unsigned char *compr = enc_buf + bg_header->encode_length;
	unsigned int comprlen = bg_len - sizeof(bg_header_t) - bg_header->encode_length;
	act_uncomprlen = bg_huffman_decompress(nodes, root_node_index,
		zero_compr, bg_header->zero_comprlen, compr, comprlen);
	if (act_uncomprlen != bg_header->zero_comprlen) {
		Free(zero_compr);
		return 0;
	}

	act_uncomprlen = zero_decompress(image_buf, image_size, zero_compr, bg_header->zero_comprlen);
	Free(zero_compr);

	bg_average_defilting(image_buf, bg_header->width, bg_header->height, bg_header->color_depth / 8);

	return act_uncomprlen;
}

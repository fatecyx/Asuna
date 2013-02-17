// きっと、確みわたる劾弼よりも
#include "asairo.h"

Bool CAsairo::Open(PWChar szFileName)
{
    ReleaseAll();

    if (!f.Open(szFileName))
        return False;

    UInt32 IndexSize;
    SMpkHeader h;
    MPK_ENTRY *pMpkIndex;
    MY_MPK_ENTRY *pEntry;

    if (!f.Read(&h, sizeof(h)))
        return False;

    if (!f.Seek(f.FILE_SEEK_BEGIN, h.uIndexOffset))
        return False;

    m_Index.cbEntrySize = sizeof(*pEntry);
    pEntry = (MY_MPK_ENTRY *)Alloc(h.FileNum * m_Index.cbEntrySize);
    if (pEntry == NULL)
        return False;

    m_Index.pEntry = pEntry;

    IndexSize = h.FileNum * sizeof(*pMpkIndex);
    pMpkIndex = (MPK_ENTRY *)Alloc(IndexSize);
    if (pMpkIndex == NULL)
        return False;

    if (!f.Read(pMpkIndex, IndexSize))
    {
        Free(pMpkIndex);
        return False;
    }

    memxor(pMpkIndex, 0x58, IndexSize);

    for (UInt32 Count = h.FileNum; Count; --Count)
    {
        pEntry->Offset.QuadPart = pMpkIndex->uOffset;
        pEntry->Size.QuadPart   = pMpkIndex->uSize;

        MultiByteToWideChar(
            CP_ACP,
            0,
            pMpkIndex->szFileName,
            -1,
            pEntry->FileName,
            countof(pEntry->FileName)
        );

        ++pEntry;
        ++pMpkIndex;
    }

    m_Index.FileCount.QuadPart = h.FileNum;
    pMpkIndex -= h.FileNum;
    Free(pMpkIndex);

    return True;
}

UInt32 CAsairo::Decompress(PByte pbBuffer, UInt32 uBufferSize, PByte pbOutput, UInt32 uOutBufferSize)
{
    UInt32 b, v;
    PByte  pbBufferEnd, pbOutEnd, pbSrc, pbDest, pbInput;

    pbBufferEnd = pbBuffer + uBufferSize;
    pbOutEnd    = pbOutput + uOutBufferSize;
    pbSrc       = pbBuffer;
    pbDest      = pbOutput;

    while (pbSrc < pbBufferEnd && pbDest < pbOutEnd)
    {
        b = *pbSrc++;
        if (b < 0x20)
        {
            ++b;
            if (pbDest + b >= pbOutEnd)
                break;
            memcpy(pbDest, pbSrc, b);
            pbDest += b;
            pbSrc  += b;
            continue;
        }

        v = b;
        b = (b & 0x1F) << 8;
        v >>= 5;
        pbInput = pbDest - b - 1;
        if (v == 7)
        {
            v = *pbSrc++ + 7;
        }
        b = *pbSrc++;
        pbInput -= b;
        v += 2;

        if (v + pbDest >= pbOutEnd || pbInput < pbOutput)
            break;

        while (v--)
            *pbDest++ = *pbInput++;
    }

    return pbDest - pbOutput;
}

Bool CAsairo::GetFileData(SFileInfo *pFileInfo, const MY_FILE_ENTRY_BASE *pIndex)
{
    PByte pbBuffer;

    if (!f.SeekEx(f.FILE_SEEK_BEGIN, pIndex->Offset))
        return False;

    pbBuffer = (PByte)Alloc(pIndex->Size.LowPart);
    if (pbBuffer == NULL)
        return False;

    if (!f.Read(pbBuffer, pIndex->Size.LowPart))
    {
        Free(pbBuffer);
        return False;
    }

    if (StrICompareW(pIndex->FileName + StrLengthW(pIndex->FileName) -  4, L".mgr"))
    {
        pFileInfo->FileType             = UNPACKER_FILE_TYPE_BIN;
        pFileInfo->BinData.pbBuffer     = pbBuffer;
        pFileInfo->BinData.BufferSize   = pIndex->Size.LowPart;
        return True;
    }

    UInt32 Frames, *puOffsets;;
    SMgrFile *pMgr;
    SImageData *pImage;

    Frames = *(PUInt16)pbBuffer;
    if (Frames != 1)
        puOffsets = (PUInt32)(pbBuffer + 2);
    else
        puOffsets = NULL;

    pFileInfo->FileType = UNPACKER_FILE_TYPE_BMP;
    pFileInfo->FileNum  = Frames;
    if (Frames > 1)
    {
        pImage = (SImageData *)Alloc(sizeof(SImageData) * Frames);
        pFileInfo->pImgData = pImage;
    }
    else
    {
        pImage = &pFileInfo->ImgData;
    }

    for (UInt32 i = 0; i != Frames; ++i, ++pImage)
    {
        UInt32 size;

        pMgr = (SMgrFile *)(pbBuffer + (puOffsets ? puOffsets[i] : 2));
        pImage->pbBuffer = (PByte)Alloc(pMgr->uDecompSize);
        if (pImage->pbBuffer == NULL)
            continue;

        size = Decompress(pMgr->byData, pMgr->uCompSize, pImage->pbBuffer, pMgr->uDecompSize);
        if (size < pMgr->uDecompSize)
            ZeroMemory(pImage->pbBuffer + size, pMgr->uDecompSize - size);

        pImage->BufferSize = pMgr->uDecompSize;
    }

    return True;
}

int CDECL cmp(const void *p1, const void *p2)
{
    Int Result;
    
    Result =  StrNICompareA(((MPK_ENTRY *)p1)->szFileName, ((MPK_ENTRY *)p2)->szFileName, sizeof(((MPK_ENTRY *)p1)->szFileName));

    return Result < 0 ? -1 : Result > 0 ? 1 : 0;
}

UInt32 CAsairo::Pack(PCWChar szPath)
{
    WChar szFileName[MAX_PATH];
    UInt32 MaxFiles, i, BufferSize, offset;
    LPVoid lpBuffer;
    HANDLE hFind;
    MPK_ENTRY *pIndex;
    SMpkHeader h;
    WIN32_FIND_DATAW wfd;

    lstrcpyW(wfd.cFileName, szPath);
    i = StrLengthW(wfd.cFileName) - 1;
    while (wfd.cFileName[i] == '\\') wfd.cFileName[i--] = 0;
    ++i;
    lstrcpyW(wfd.cFileName + i, L".mpk");

    CFileDisk file;
    if (!file.Create(wfd.cFileName))
        return 0;

    lstrcpyW(wfd.cFileName + i, L"\\*.*");
    lstrcpyW(szFileName, wfd.cFileName);
    ++i;
    hFind = FindFirstFileW(wfd.cFileName, &wfd);
    if (hFind == INVALID_HANDLE_VALUE)
        return 0;

    while (!StrCompareW(wfd.cFileName, L".") || !StrCompareW(wfd.cFileName, L".."))
    {
        if (!FindNextFileW(hFind, &wfd))
        {
            FindClose(hFind);
            return 0;
        }
    }

    CFileDisk fin;

    offset = sizeof(h);
    h.FileNum = 0;
    BufferSize = 0x1000;
    MaxFiles = 0x100;
    lpBuffer = Alloc(BufferSize);
    file.Write(&h, sizeof(h));
    pIndex = (MPK_ENTRY *)Alloc(MaxFiles * sizeof(*pIndex));
    if (pIndex) do
    {
        if (h.FileNum == MaxFiles)
        {
            MaxFiles *= 2;
            pIndex = (MPK_ENTRY *)ReAlloc(pIndex, MaxFiles * sizeof(*pIndex));
            if (pIndex == NULL)
            {
                h.FileNum = 0;
                break;
            }
        }

        pIndex[h.FileNum].szFileName[0] = '\\';
        WideCharToMultiByte(
            CP_ACP,
            0,
            wfd.cFileName,
            -1,
            pIndex[h.FileNum].szFileName + 1,
            sizeof(pIndex->szFileName),
            NULL,
            NULL);

        lstrcpyW(szFileName + i, wfd.cFileName);
        if (fin.Open(szFileName))
        {
            UInt32 size;

            size = fin.GetSize();
            if (size > BufferSize)
            {
                BufferSize = size;
                lpBuffer = ReAlloc(lpBuffer, BufferSize);
            }

            fin.Read(lpBuffer);
            file.Write(lpBuffer, size);
            pIndex[h.FileNum].uSize = size;
            pIndex[h.FileNum].uOffset = offset;
            offset += size;
        }
        else
            ZeroMemory(&pIndex[h.FileNum], sizeof(*pIndex));

        ++h.FileNum;
    } while (FindNextFileW(hFind, &wfd));

    FindClose(hFind);

    if (h.FileNum)
    {
        UInt32 size = h.FileNum * sizeof(*pIndex);
        h.uIndexOffset = file.GetCurrentPos();
        qsort(pIndex, h.FileNum, sizeof(*pIndex), cmp);
        memxor(pIndex, 0x58, size);
        file.Write(pIndex, size);
        file.Seek(file.FILE_SEEK_BEGIN, 0);
        file.Write(&h, sizeof(h));
    }
    Free(pIndex);

    return h.FileNum;
}
#include "hrArc.h"
#include "crt_h.h"
#include "my_crt.h"
#include "my_api.h"
#include "my_image.h"
#include "my_mem.h"
#include <algorithm>

using std::sort;

ChrArc::ChrArc()
{
    m_uiFiles            = 0;
    m_ArcIndex.pEntry    = NULL;
    m_ArcIndex.pSubIndex = NULL;
}

ChrArc::~ChrArc()
{
    Free();
}

Void ChrArc::Close()
{
    Free();
    file.Close();
}

Void ChrArc::Free()
{
    m.SafeFree(&m_ArcIndex.pSubIndex);
    m.SafeFree(&m_ArcIndex.pEntry);
}

Bool ChrArc::Open(TCHAR *szFileName)
{
    Close();

    if (file.Open(szFileName) == False)
        return False;

    if (InitIndex() == False)
        return False;

    return True;
}

Void ChrArc::Auto(TCHAR *szFileName)
{
    Char buf[20], szPath[MAX_PATH];
    DWORD dwAttr;
    extern Bool bCtrlC;

    dwAttr = GetFileAttributes(szFileName);
    if (dwAttr == -1)
    {
        printf("\"%s\" doesn't exist.\n", szFileName);
        return;
    }

    if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
    {
        printf("Packing \"%s\" ... %s\n", szFileName, Pack(szFileName) ? "OK" : "failed");
        return;
    }

    if (Open(szFileName) == False)
    {
        printf("Open \"%s\" failed.\n", szFileName);
        return;
    }

    strcpy(szPath, szFileName);
    rmext(szPath);
    for (UInt32 i = 0, j = GetFileCount(); !bCtrlC && i != j; )
    {
        SMyArcSubIndex *pIndex = GetIndex(i);
        if (pIndex == NULL)
            continue;
        sprintf(buf, "%u / %u", ++i, j);
        SetConsoleTitleA(buf);
        printf("Extracting \"%s\" ... ", pIndex->FileName);
        printf("%s\n", ExtractFile(pIndex, szPath) ? "OK" : "failed");
    }
}

Bool ChrArc::InitIndex()
{
    UInt32 uiEntryCount, uiSize, uiFiles, uiMaxFiles, uiMaxIndexCount;
    SArcSubIndex *pIndex;

    file.Read(&uiEntryCount, 4);
    if (uiEntryCount == 0)
        return False;

    uiSize = uiEntryCount * sizeof(*m_ArcIndex.pEntry);
    m_ArcIndex.pEntry = (SMyArcEntry *)m.Alloc(uiSize);
    if (m_ArcIndex.pEntry == NULL)
        return False;

    for (UInt32 i = 0; i != uiEntryCount; ++i)
    {
        if (file.Read(&m_ArcIndex.pEntry[i], sizeof(SArcEntry)) == False)
            return False;
        m_ArcIndex.pEntry[i].pSubIndex = NULL;
    }

    uiMaxFiles = 0;
    for (UInt32 i = 0; i != uiEntryCount; ++i)
    {
        uiMaxFiles += m_ArcIndex.pEntry[i].uiFileCount;
    }
    if (uiMaxFiles == 0)
    {
        return False;
    }

    m_ArcIndex.pSubIndex = (SMyArcSubIndex *)m.Alloc(uiMaxFiles * sizeof(*m_ArcIndex.pSubIndex));
    if (m_ArcIndex.pSubIndex == NULL)
        return False;

    uiMaxIndexCount = m_ArcIndex.pEntry[0].uiFileCount;
    pIndex = (SArcSubIndex *)m.Alloc(uiMaxIndexCount * sizeof(*pIndex));
    if (pIndex == NULL)
        return False;

    uiFiles = 0;
    for (UInt32 i = 0; i != uiEntryCount; ++i)
    {
        SMyArcSubIndex *pArcIndex;

        if (m_ArcIndex.pEntry[i].uiFileCount > uiMaxIndexCount)
        {
            uiMaxIndexCount = m_ArcIndex.pEntry[i].uiFileCount;
            pIndex = (SArcSubIndex *)m.ReAlloc(uiMaxIndexCount * sizeof(*pIndex), pIndex);
            if (pIndex == NULL)
            {
                m.Free(pIndex);
                return False;
            }
        }

        if (file.Seek(file.Seek_Beg, m_ArcIndex.pEntry[i].uiIndexOffset) == False)
        {
            m.Free(pIndex);
            return False;
        }

        if (file.Read(pIndex, m_ArcIndex.pEntry[i].uiFileCount * sizeof(*pIndex)) == False)
        {
            m.Free(pIndex);
            return False;
        }

        pArcIndex = &m_ArcIndex.pSubIndex[uiFiles];
        m_ArcIndex.pEntry[i].pSubIndex = pArcIndex;
        for (UInt32 j = 0, k = m_ArcIndex.pEntry[i].uiFileCount; j != k; ++j)
        {
            sprintf(pArcIndex->FileName, "%s.%s", pIndex[j].FileName, m_ArcIndex.pEntry[i].Eextension);
            pArcIndex->uiOffset = pIndex[j].uiOffset;
            pArcIndex->uiSize   = pIndex[j].uiSize;
            ++uiFiles;
            ++pArcIndex;
        }
    }

    memset(pIndex, 0, uiMaxIndexCount * sizeof(*pIndex));
    m.Free(pIndex);
    m_ArcIndex.uiEntryCount = uiEntryCount;
    m_uiFiles = uiFiles;

    return True;
}

UInt32 ChrArc::GetFileCount()
{
    return m_uiFiles;
}

SMyArcSubIndex* ChrArc::GetIndex(UInt32 uiIndex)
{
    if (uiIndex > m_uiFiles)
        return NULL;
    return &m_ArcIndex.pSubIndex[uiIndex];
}

Bool ChrArc::DecryptWSC(PByte pbBuffer, UInt32 uiSize)
{
    while (uiSize--)
    {
        pbBuffer[uiSize] = _rotr8(pbBuffer[uiSize], 2);
    }

    return True;
}

UInt32 ChrArc::Decompress(Byte *pbInput, Byte *pbOutput)
{
    Byte *p, dict[0x1000];
    UInt32 v;

    p = pbOutput;
    memset(dict, 0, sizeof(dict));
    v = 1;
    while (1)
    {
        Byte  ch, c;
        UInt32 round = 8, round2, round3;

        c = *pbInput++;
        do
        {
            if (c & 1)
            {
                ch = *pbInput++;
                *pbOutput++ = ch;
                dict[v++] = ch;
                v %= sizeof(dict);
            }
            else
            {
                round2 = ((u16)((pbInput[0] << 8) | pbInput[1])) >> 4;
                if (round2 == 0)
                    goto _DECOMP_FINISH_;

                round3 = (pbInput[1] & 0xF) + 2;
                pbInput += 2;

                do
                {
                    ch = dict[round2];
                    *pbOutput++ = ch;
                    dict[v++] = ch;
                    v %= sizeof(dict);
                    ++round2;
                    round2 %= sizeof(dict);
                } while (--round3);
            }

            c >>= 1;
        } while (--round);
    }

_DECOMP_FINISH_:

    return pbOutput - p;
}

Bool ChrArc::GetFileData(SMyArcSubIndex *pIndex, SFileInfo *info, Bool bConvert /* = True */)
{
    if (info == NULL)
        return False;

    PByte  pbFile;
    UInt32 uiSize;
    Char  *pExtension;
    SFileInfo       mskInfo;
    SWIPHeader     *pWipHeader;
    SMyArcSubIndex *pMaskIndex;

    memset(info, 0, sizeof(*info));
    pbFile = (Byte *)m.Alloc(pIndex->uiSize);
    if (pbFile == NULL)
        return False;

    if (!file.Seek(file.Seek_Beg, pIndex->uiOffset) ||
        !file.Read(pbFile, pIndex->uiSize, &uiSize))
    {
        m.Free(pbFile);
        return False;
    }

    pWipHeader = (SWIPHeader *)pbFile;
    pExtension = findext(pIndex->FileName);
    if (bConvert == False ||
        pExtension == NULL ||
//        pWipHeader->uiTag != TAG4('WIPF')
        stricmp(pExtension, ".wip")
        )
    {
        if (!stricmp(pExtension, ".wsc"))
            DecryptWSC(pbFile, uiSize);

        info->type = BIN;
        info->count = 1;
        info->BinData.data = pbFile;
        info->BinData.size = uiSize;

        return True;
    }

    do
    {
/*
        if (!stricmp(pExtension, ".mos") || !stricmp(pExtension, ".msk"))   // 8 bit gray
        {
            info->ImgData = (SImageData *)m.Alloc(pWipHeader->usFrames * sizeof(*info->ImgData));
            if (info->ImgData == NULL)
                break;

            info->type  = GRAY;
            info->count = pWipHeader->usFrames;
            info->extra = pbFile;
            for (UInt32 i = 0, j = info->count; i != j; ++i)
            {
                if (Decode8BitFrame(pWipHeader, i, info->ImgData + i) == False)
                    info->ImgData[i].data = NULL;
            }

            return True;
        }
*/
        info->type = IMG;
        *(LPDWORD)pExtension = TAG4('.msk');
        pMaskIndex = Find(pIndex->FileName);
        *(LPDWORD)pExtension = TAG4('.wip');
        if (pMaskIndex)
            GetFileData(pMaskIndex, &mskInfo, False);
        else
            mskInfo.BinData.data = NULL;

        info->ImgData = (SImageData *)m.Alloc(pWipHeader->usFrames * sizeof(*info->ImgData));
        if (info->ImgData == NULL)
            break;

        info->count = pWipHeader->usFrames;
        for (UInt32 i = 0, j = info->count; i != j; ++i)
        {
            if (DecodeWIPFrame(pWipHeader, (SWIPHeader *)mskInfo.BinData.data, i, info->ImgData + i) == False)
                info->ImgData[i].data = NULL;
        }

        info->extra = pbFile;

        return True;

    } while (0);

    m.Free(&pbFile);

    return False;
}

Void ChrArc::FreeFileData(SFileInfo *info)
{
    if (info == NULL)
        return;

    m.Free(info->extra);

    if (info->type == BIN)
        m.Free(info->BinData.data);
    else if (info->type == IMG)
    {
        if (info->ImgData == NULL)
            return;

        for (UInt32 i = 0, j = info->count; i != j; ++i)
            m.Free(info->ImgData[i].data);
        m.Free(info->ImgData);
    }
}

Bool ChrArc::ExtractFile(SMyArcSubIndex *pIndex, LPSTR lpOutPath /* = NULL */)
{
    UInt32 uiSize;
    HANDLE hFile;
    Char ext, *fmt, *pExtension, szOut[MAX_PATH];
    SFileInfo info;

    if (GetFileData(pIndex, &info/*, False*/) == False)
        return False;

    if (lpOutPath == NULL)
        lpOutPath = ".";
    else
        MyCreateDirectoryA(lpOutPath);

    if (info.type == BIN)
    {
        if (info.BinData.data == NULL)
        {
            FreeFileData(&info);
            return False;
        }

        sprintf(szOut, "%s\\%s", lpOutPath, pIndex->FileName);
        hFile = CreateFileA(szOut,
                    GENERIC_WRITE,
                    FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
        if (hFile != INVALID_HANDLE_VALUE)
        {
            WriteFile(hFile, info.BinData.data, info.BinData.size, (LPDWORD)&uiSize, NULL);
            CloseHandle(hFile);
        }

        FreeFileData(&info);
        return hFile != INVALID_HANDLE_VALUE;
    }

    pExtension = findext(pIndex->FileName);
    if (info.count != 1)
        fmt = "%s\\%s_%05u.bmp";
    else
        fmt = "%s\\%s.bmp";

    if (info.type == IMG)
    {
        ext = *pExtension;
        *pExtension = 0;
    }
    if (info.extra)
    {
        sprintf(szOut, "%s\\%s.bin", lpOutPath, pIndex->FileName);
        hFile = CreateFileA(szOut,
            GENERIC_WRITE,
            FILE_SHARE_WRITE,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (hFile != INVALID_HANDLE_VALUE)
        {
            SWIPHeader *pWipHeader;
            pWipHeader = (SWIPHeader *)info.extra;
            WriteFile(hFile, pWipHeader, 8 + pWipHeader->usFrames * sizeof(pWipHeader->Blocks), (LPDWORD)&uiSize, NULL);
            CloseHandle(hFile);
        }
    }

    for (UInt32 i = 0; i != info.count; ++i)
    {
        sprintf(szOut, fmt, lpOutPath, pIndex->FileName, i);
        hFile = CreateFileA(szOut,
                    GENERIC_WRITE,
                    FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
        if (hFile != INVALID_HANDLE_VALUE)
        {
            WriteFile(hFile, info.ImgData[i].data, info.ImgData[i].size, (LPDWORD)&uiSize, NULL);
            CloseHandle(hFile);
        }
    }

    if (info.type == IMG)
        *pExtension = ext;

    FreeFileData(&info);
    return hFile != INVALID_HANDLE_VALUE;
}

SMyArcSubIndex* ChrArc::Find(Char *szFile)
{
    SMyArcEntry *pEntry;
    Char *pExtension;

    pExtension = findext(szFile);
    if (pExtension == NULL)
        return NULL;

    pEntry = NULL;
    ++pExtension;
    for (UInt32 i = 0; i != m_ArcIndex.uiEntryCount; ++i)
    {
        if (!stricmp(m_ArcIndex.pEntry[i].Eextension, pExtension))
        {
            pEntry = &m_ArcIndex.pEntry[i];
            break;
        }
    }
    if (pEntry == NULL)
        return NULL;

    return FindFileInIndex(pEntry, szFile);
}

SMyArcSubIndex* ChrArc::FindFileInIndex(SMyArcEntry *pEntry, Char *szFile)
{
    UInt32 l, r, m;
    SMyArcSubIndex *pIndex;

    l = 0;
    r = pEntry->uiFileCount;

    while (l < r)
    {
        int i;
        m = (l + r) / 2;

        pIndex = &pEntry->pSubIndex[m];
        i = stricmp(pIndex->FileName, szFile);
        if (i < 0) l = m + 1;
        else if (i > 0) r = m;
        else return pIndex;
    }

    return NULL;
}

Bool ChrArc::Decode8BitFrame(SWIPHeader *pHeader, UInt32 uiFrame, SImageData *image)
{
    PByte  pbBlock, pbDecompress;
    UInt32 uiSize, width, height;
    TBitMapHeader *h;

    if (pHeader->uiTag != TAG4('WIPF') || uiFrame + 1 > pHeader->usFrames)
        return False;

    width  = pHeader->Blocks[uiFrame].uiWidth;
    height = pHeader->Blocks[uiFrame].uiHeight;
    uiSize = width * height + 0x10 + sizeof(*h);
    pbDecompress = (PByte)m.Alloc(uiSize);
    if (pbDecompress == NULL)
        return False;

    pbBlock = (PByte)&pHeader->Blocks[pHeader->usFrames] + 0x400;
    for (UInt32 i = 0; i != uiFrame; ++i)
    {
        pbBlock += pHeader->Blocks[i].uiBlockSize + 0x400;
    }

    h = (TBitMapHeader *)pbDecompress;
    memset(h, 0, sizeof(*h));

    image->data = pbDecompress;
    image->size = Decompress(pbBlock, pbDecompress + sizeof(*h)) + sizeof(*h);
    image->w = width;
    image->h = height;

    h->Info.dwHeight = height;
    h->Info.dwWidth  = width;
    h->wTag = TAG2('BM');
    h->dwRawOffset = sizeof(*h);
    h->Info.dwInfoHeaderSize = sizeof(h->Info);
    h->Info.wLayer = 1;
    h->Info.wBit = 8;

    return True;
}

Bool ChrArc::DecodeWIPFrame(SWIPHeader *pHeader, SWIPHeader *pMaskHeader, UInt32 uiFrame, SImageData *image)
{
    PByte pbBlock, pbDecompress, pbBitmap, r, g, b, a;
    UInt32 uiSize, width, height, stride;
    SImageData img;
    TBitMapHeader *h;

    if (pHeader->uiTag != TAG4('WIPF') || uiFrame + 1 > pHeader->usFrames)
        return False;

    if (pMaskHeader)
    {
        if (memcmp(&pMaskHeader->Blocks[uiFrame],
                   &pHeader->Blocks[uiFrame],
                   sizeof(pHeader->Blocks) - 4))    // exclude the BlockSize
            return False;
    }

    width  = pHeader->Blocks[uiFrame].uiWidth;
    height = pHeader->Blocks[uiFrame].uiHeight;
    stride = width * 4;
    uiSize = stride * height;
    pbDecompress = (Byte *)m.Alloc(uiSize);
    if (pbDecompress == NULL)
        return False;

    if (pMaskHeader)
    {
        Decode8BitFrame(pMaskHeader, uiFrame, &img);
        a = img.data + img.size;
    }
    else
    {
        a = NULL;
    }

    pbBlock = (PByte)&pHeader->Blocks[pHeader->usFrames];
    for (UInt32 i = 0; i != uiFrame; ++i)
        pbBlock += pHeader->Blocks[i].uiBlockSize;

    Decompress(pbBlock, pbDecompress);
    pbBitmap = (Byte *)m.Alloc(uiSize + sizeof(*h));
    if (pbBitmap == NULL)
    {
        m.Free(pbDecompress);
        return False;
    }

    // 32 bit bmp only
    uiSize /= 4;
    h = (TBitMapHeader *)pbBitmap;
    memset(h, 0, sizeof(*h));
    h->wTag = TAG2('BM');
    h->dwRawOffset = sizeof(*h);
    h->Info.dwInfoHeaderSize = sizeof(h->Info);
    h->Info.wLayer = 1;
    h->Info.dwHeight = height;
    h->Info.dwWidth  = width;
    h->Info.wBit = 32;

    r = pbDecompress + uiSize - 1;
    g = r + uiSize;
    b = g + uiSize;
    pbBlock = pbBitmap + sizeof(*h) + stride - 4;
    for (UInt32 i = 0, j = stride / 4; i != uiSize; ++i)
    {
        *(pu32)pbBlock = RGBA(*r, *g, *b, a ? *--a : 0);
        --r;
        --g;
        --b;
        pbBlock -= 4;
        if (--j == 0)
        {
            j = stride / 4;
            pbBlock += stride * 2;
        }
    }

    image->data = pbBitmap;
    image->size = uiSize * 4 + sizeof(*h);
    image->bit  = h->Info.wBit;
    image->h    = height;
    image->w    = width;

    m.Free(pbDecompress);
    if (pMaskHeader) m.Free(img.data);
    return True;
}

UInt32 WINAPI FindExt(vector<SArcEntryForPack> &entry, PChar pExt)
{
    UInt32 i, j;

    for (i = 0, j = entry.size(); i != j; ++i)
        if (!stricmp(entry[i].Extention, pExt))
            break;
    if (i == j)
    {
        SArcEntryForPack pak;
        strcpy(pak.Extention, pExt);
        pak.uiFileCount = 0;
        pak.uiIndexOffset = 0;
        entry.push_back(pak);
    }

    return i;
}

bool EntryComp(SArcEntryForPack &v1, SArcEntryForPack &v2)
{
    return strncmp(v1.Extention, v2.Extention, sizeof(v1.Extention)) <= 0;
}

bool IndexComp(SArcSubIndex &v1, SArcSubIndex &v2)
{
    return strncmp(v1.FileName, v2.FileName, sizeof(v1.FileName)) <= 0;
}

Bool ChrArc::Pack(TCHAR *szPath)
{
    TCHAR  buf[MAX_PATH];
    PChar  pExt;
    UInt32 i, HeadSize, offset;
    HANDLE hFind;
    WIN32_FIND_DATA wfd;
    SArcSubIndex SubIndex;
    vector<SArcEntryForPack> entry;

    strcpy(buf, szPath);
    i = strlen(buf) - 1;
    if (buf[i] == '\\')
        buf[i] = 0;
    strcat(buf, "\\*.*");

    hFind = FindFirstFile(buf, &wfd);
    if (hFind == INVALID_HANDLE_VALUE)
        return False;

    do
    {
        if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, ".."))
            continue;

        if (strlen(wfd.cFileName) - 4 > 9)
        {
            printf("%s\\%s: filename too long (9 max)\n", szPath, wfd.cFileName);
            continue;
        }

        pExt = findext(wfd.cFileName);
        if (pExt == NULL)
        {
            printf("%s\\%s: no extension\n");
            continue;
        }
        if (strlen(++pExt) > 4)
        {
            printf("%s\\%s: extension too long (4 max)\n", szPath, wfd.cFileName);
            continue;
        }

        strupr(pExt);
        i = FindExt(entry, pExt);
        rmext(wfd.cFileName);
        strupr(wfd.cFileName);
        strncpy(SubIndex.FileName, wfd.cFileName, sizeof(SubIndex.FileName));
        SubIndex.uiOffset = 0;
        SubIndex.uiSize   = 0;
        entry[i].SubIndex.push_back(SubIndex);

    } while (FindNextFile(hFind, &wfd));

    FindClose(hFind);

    HeadSize = 0;
    sort(entry.begin(), entry.end(), EntryComp);
    for (UInt32 i = 0, j = entry.size(); i != j; ++i)
    {
        SArcEntryForPack *pEntry = &entry[i];
        sort(pEntry->SubIndex.begin(), pEntry->SubIndex.end(), IndexComp);
        HeadSize += sizeof(SArcEntry) + pEntry->SubIndex.size() * sizeof(SArcSubIndex);
    }

    if (HeadSize == 0)
        return False;

    i = strlen(buf) - 4;
    strcpy(buf + i, ".arc");
    CFileDisk f;

    if (f.Open(buf, f.WRITE, f.NEW) == False)
        return False;

    HeadSize += 4;
    {
        LPVoid pmem = m.Alloc(HeadSize);
        if (pmem == NULL)
            return False;
        f.Write(pmem, HeadSize);
        m.Free(pmem);
    }

    UInt32 bufSize, FileSize;
    LPVoid lpBuffer;

    bufSize = 10240;
    lpBuffer = m.Alloc(bufSize);
    offset = HeadSize;
    for (UInt32 l, i = 0, j = entry.size(); i != j; ++i)
    {
        SArcEntryForPack *pEntry = &entry[i];
        pExt = pEntry->Extention;
        l = pEntry->SubIndex.size();
        pEntry->uiFileCount = l;
        for (UInt32 k = 0; k != l; ++k)
        {
            SArcSubIndex *pIndex = &pEntry->SubIndex[k];
            sprintf(buf, "%s\\%s.%s", szPath, pIndex->FileName, pExt);
            if (file.Open(buf) == False)
                continue;

            FileSize = file.GetSize();
            if (bufSize < FileSize)
            {
                bufSize = FileSize;
                lpBuffer = m.ReAlloc(bufSize, lpBuffer);
            }
            file.Read(lpBuffer);
            f.Write(lpBuffer, FileSize);
            pIndex->uiOffset = offset;
            pIndex->uiSize = FileSize;
            offset += FileSize;
        }
    }

    m.Free(lpBuffer);
    i = entry.size();
    f.Rewind();
    f.Write(&i, 4);
    f.Seek(f.Seek_Cur, i * sizeof(SArcEntry));

    for (UInt32 j = 0; j != i; ++j)
    {
        SArcEntryForPack *pEntry = &entry[j];
        SArcSubIndex *pIndex = &pEntry->SubIndex[0];

        pEntry->uiIndexOffset = f.GetCurrentPos();
        f.Write(pIndex, sizeof(*pIndex) * pEntry->SubIndex.size());
    }

    f.Seek(f.Seek_Beg, 4);
    for (UInt32 j = 0; j != i; ++j)
    {
        SArcEntryForPack *pEntry = &entry[j];
        f.Write(pEntry, sizeof(SArcEntry));
    }

    return True;
}
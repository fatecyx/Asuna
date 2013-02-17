#pragma comment(lib, "ntdll.lib")

#include "piano.h"
#include "my_api.h"
#include "crt_h.h"
#include "my_crt.h"
#include "my_image.h"
#include "my_mem.h"

static Char DatHeader[] = "GAMEDAT PAC2";

CPiano::CPiano()
{
    m_index.pIndex = NULL;
}

CPiano::~CPiano()
{
    Free();
}

Void CPiano::Free()
{
    m.SafeFree(&m_index.pIndex);
}

Void CPiano::Auto(WChar *szFileName)
{
    DWORD dwAttr;

    dwAttr = GetFileAttributesW(szFileName);
    if (dwAttr == -1)
        return;

    if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
    {
        if (InitIndex(szFileName) == False)
            return;
        wprintf(L"Packing \"%s\" ... ", szFileName);
        wprintf(L"%u files packed\n", Pack(szFileName));

        return;
    }

    if (Open(szFileName) == False)
        return;

    WChar buf[20], szPath[MAX_PATH];
    SMyPianoFileIndex *pIndex;
    extern Bool bCtrlC;

    wcscpy(szPath, szFileName);
    rmextw(szPath);
    pIndex = m_index.pIndex;
    for (UInt32 i = 0; !bCtrlC && i != m_index.filenum; )
    {
        swprintf(buf, L"%u / %u", ++i, m_index.filenum);
        SetConsoleTitleW(buf);
        printf("Extracting \"%s\" ... ", pIndex->name.name);
        printf("%s\n", ExtractFile(pIndex, szPath) ? "OK" : "failed");
        ++pIndex;
    }
}

Bool CPiano::Open(WChar *szFileName)
{
    if (file.Open(szFileName) == False)
        return False;

    SPianoHeader header;

    file.Read(&header, sizeof(header));
    if (memcmp(header.tag, DatHeader, sizeof(DatHeader) - 2))
        return False;

    return InitIndex(&header);
}

Bool CPiano::InitIndex(SPianoHeader *pHeader)
{
    m_index.pIndex = (SMyPianoFileIndex *)m.Alloc(pHeader->filenum * sizeof(*m_index.pIndex));
    if (m_index.pIndex == NULL)
        return False;

    UInt32 type, size, offset;
    PByte pbName;
    SPianoFileIndex *index;
    SMyPianoFileIndex *pIndex;

    type = pHeader->tag[sizeof(pHeader->tag) - 1];
    size = type == '2' ? sizeof(SPianoFileName2) : sizeof(SPianoFileName);
    type = size;
    size += sizeof(SPianoFileIndex);
    size *= pHeader->filenum;
    pbName = (PByte)m.Alloc(size);
    if (pbName == NULL)
        return False;

    file.Read(pbName, size);

    offset = size + 0x10;
    size = type;
    index = (SPianoFileIndex *)(pbName + size * pHeader->filenum);
    pIndex = m_index.pIndex;
    m_index.filenum = pHeader->filenum;
    for (UInt32 i = 0; i != m_index.filenum; ++i)
    {
        pIndex->index = *index++;
        pIndex->index.offset += offset;
        memcpy(pIndex->name.name, pbName, size);
        pbName += size;
        ++pIndex;
    }

    m.Free(pbName);
    return True;
}

SMyPianoFileIndex* CPiano::GetIndex(UInt32 i)
{
    if (m_index.pIndex == NULL)
        return NULL;

    return i > m_index.filenum ? NULL : &m_index.pIndex[i];
}

UInt32 CPiano::ExtractFile(SMyPianoFileIndex *pIndex, PWChar szOutPath /* = NULL */)
{
    WChar szPath[MAX_PATH];
    UInt32 uSize;
    CFileDisk f;
    UNICODE_STRING ustr;
    SFileInfo info;

    if (GetFileData(pIndex, &info, False) == False)
        return 0;

    uSize = swprintf(szPath, L"%s\\", szOutPath ? szOutPath : L".");
    MyCreateDirectoryW(szPath);
    CFileDisk::AnsiToUnicode(&ustr, pIndex->name.name, szPath + uSize, MAX_PATH - uSize);

    if (info.flag == BIN)
    {
        if (f.Open(szPath, f.W, f.N))
        {
            f.Write(info.BinData.data, info.BinData.size);
        }

        uSize = info.BinData.size;
    }
    else if (info.flag == IMG)
    {
        chextw(szPath, L".bmp");
        if (f.Open(szPath, f.W, f.N))
        {
            f.Write(info.ImgData->data, info.ImgData->size);
        }

        uSize = info.ImgData->size;
    }

    FreeFileData(&info);

    return uSize;
}

Void CPiano::FreeFileData(SFileInfo *info)
{
    if (info == NULL)
        return;

    m.Free(info->extra);

    if (info->flag == BIN)
        m.Free(info->BinData.data);
    else if (info->flag == IMG)
    {
        if (info->ImgData == NULL)
            return;

        for (UInt32 i = 0, j = info->count; i != j; ++i)
            m.Free(info->ImgData[i].data);
        m.Free(info->ImgData);
    }
}

Bool CPiano::GetFileData(SMyPianoFileIndex *pIndex, SFileInfo *info, Bool bConvert /* = True */)
{
    PByte pbBuffer;
    UInt32 v;

    if (file.Seek(file.Seek_Beg, pIndex->index.offset) == False)
        return False;

    pbBuffer = (PByte)m.Alloc(pIndex->index.size);
    if (pbBuffer == NULL)
        return False;

    bConvert = True;
    file.Read(pbBuffer, pIndex->index.size);
    v = *(PUInt32)pbBuffer;
    info->extra = NULL;
    if (bConvert && (v & 0xFFFF) == TAG2('EP') && (v & 0xFF0000) == 0x010000 && (v >>= 24) <= 2 && v > 0)
    {
        SPianoEPAHeader *pHeader = (SPianoEPAHeader *)pbBuffer;
        
        info->ImgData = (SImageData *)m.Alloc(sizeof(*info->ImgData));
        info->ImgData->bit = m_BitsTable[pHeader->flag & 0xFF];
        if (info->ImgData->bit == 0)
        {
            m.Free(info->ImgData);
            m.Free(pbBuffer);
            return False;
        }

        info->flag = IMG;
        info->count = 1;
        info->ImgData->w = pHeader->width;
        info->ImgData->h = pHeader->height;
        info->ImgData->size = DecodeEPA(pHeader, pIndex->index.size, info->ImgData->data);

        m.Free(pbBuffer);
    }
    else if (0)
    {
        info->flag = BIN;
        info->BinData.data = pbBuffer;
        info->BinData.size = pIndex->index.size;
        if (bConvert && !stricmp(pIndex->name.name, "textdata.bin"))
        {
            Byte c, key = 0xC5;
            PByte p = pbBuffer;

            for (UInt32 i = 0; i != info->BinData.size; ++i)
            {
//                c = *pbBuffer ^ key;
//                *pbBuffer++ = c ? c : '\n';
                *pbBuffer++ ^= key;
                key += 0x5C;
            }
        }
    }
    else
    {
        m.Free(pbBuffer);
        return False;
    }

    return True;
}

const UInt16 CPiano::m_BitsTable[5] = { 8, 24, 32, 0, 8 };

UInt32 CPiano::DecodeEPA(SPianoEPAHeader *pEPA, UInt32 uSize, PByte &pbDest)
{
    UInt32 uChannalSize, uDecompSize, uBufferSize, bpp, stride, pad;
    PByte  pbSrc, pbDecompress, pbBitmap, r, g, b, a;
    SBitMapHeader *h;

    if (pEPA->flag & 0xFF000000)    // unsupported
        return 0;

    bpp = m_BitsTable[pEPA->flag & 0xFF] / 8;
    uChannalSize = pEPA->width * pEPA->height;
    switch (bpp)
    {
        case 1:
            uDecompSize = uChannalSize;
            uBufferSize = uChannalSize * 2 + 2 + 256 * 3;
            pbSrc = (PByte)pEPA + 0x310;
            break;

        case 3:
        case 4:
            uDecompSize = uChannalSize * bpp;
            uBufferSize = uDecompSize;
            pbSrc = (PByte)pEPA + 0x10;
            break;

        default:
            return 0;
    }

    pbDecompress = (PByte)m.Alloc(uBufferSize);
    if (pbDecompress == NULL)
        return 0;

    Decompress(pbSrc, pEPA->width, pbDecompress, uDecompSize);

    if (bpp == 1)
    {
        PByte pbPalette;
        uChannalSize = pEPA->width * pEPA->height + sizeof(*h) + 256 * 4;   // palette
        pbBitmap = (PByte)m.Alloc(uChannalSize);
        if (pbBitmap == NULL)
            return 0;

        pbDest = pbBitmap;
        h = (SBitMapHeader *)pbBitmap;
        pbBitmap += sizeof(*h);
        r = pbDecompress;
        pbPalette = (PByte)pEPA + 0x10;
        for (UInt32 i = 0; i != 256; ++i)
        {
            *(PUInt32)pbBitmap = *(PUInt32)pbPalette & 0xFFFFFF;
            pbBitmap += 4;
            pbPalette += 3;
        }
        memcpy(pbBitmap, pbDecompress, uChannalSize - sizeof(*h) - 256 * 4);

        m.Free(pbDecompress);

        ZeroMemory(h, sizeof(*h));
        h->dwRawOffset = sizeof(*h) + 256 * 4;
        h->Info.dwHeight = pEPA->height;
        h->Info.dwWidth  = pEPA->width;
        h->wTag = TAG2('BM');
        h->Info.dwInfoHeaderSize = sizeof(h->Info);
        h->Info.wLayer = 1;
        h->Info.wBit = 8;
        h->Info.dwClrUsed = 1;

        return h->dwFileSize = uChannalSize;
    }

    r = pbDecompress;
    g = r + uChannalSize;
    b = g + uChannalSize;
    if (bpp == 4)
    {
        a = b + uChannalSize;
        pad = 0;
    }
    else
    {
        a = NULL;
        pad = pEPA->width & 3;
    }

    stride = pEPA->width * bpp + pad;
    uBufferSize = pEPA->height * stride + sizeof(*h);
    pbBitmap = (PByte)m.Alloc(uBufferSize + 16);
    if (pbBitmap == NULL)
    {
        m.Free(pbDecompress);
        return 0;
    }

    pbDest = pbBitmap;
    h = (SBitMapHeader *)pbBitmap;
    pbBitmap += sizeof(*h);
    pbBitmap += stride * (pEPA->height - 1);
    for (UInt32 i = 0, k = pEPA->width; i != uChannalSize; ++i)
    {
        *(PUInt32)pbBitmap = RGBA(*r++, *g++, *b++, a ? *a++ : (Byte)a);
        pbBitmap += bpp;
        if (--k == 0)
        {
            pbBitmap += pad;
            pbBitmap -= stride * 2;
            k = pEPA->width;
        }
    }

    m.Free(pbDecompress);

    ZeroMemory(h, sizeof(*h));
    h->dwRawOffset = sizeof(*h);
    h->Info.dwHeight = pEPA->height;
    h->Info.dwWidth  = pEPA->width;
    h->wTag = TAG2('BM');
    h->Info.dwInfoHeaderSize = sizeof(h->Info);
    h->Info.wLayer = 1;
    h->Info.wBit = bpp * 8;

    return h->dwFileSize = uBufferSize;
}

Void CPiano::Decompress(PByte pbInput, UInt32 width, PByte pbOutput, Int32 iDestSize)
{
    UInt32 b, b2;

    UInt32 key[] =
    {
        0,
        1,
        width,
        width + 1,
        2,
        width - 1,
        width * 2,
        3,
        width * 2 + 2,
        width + 2,
        width * 2 + 1,
        width * 2 - 1,
        width * 2 - 2,
        width - 2,
        width * 3,
        4
    };

    while (iDestSize > 0)
    {
        b = *pbInput++;
        b2 = b;
        if ((b & 0xF0) && (b & 8))
            b = ((b & 7) << 8) + *pbInput++;
        else
            b &= 7;

        if (b2 & 0xF0)
        {
            if (b)
            {
                PByte p;
                b2 >>= 4;
                p = pbOutput - key[b2];
                iDestSize -= b;
                while (b--)
                    *pbOutput++ = *p++;
            }
        }
        else if (b2)
        {
            memcpy(pbOutput, pbInput, b2);
            pbOutput += b2;
            pbInput  += b2;
            iDestSize -= b2;
        }
    }
}

UInt32 CPiano::Pack(PWChar lpszPath)
{
    DWORD  dwRead, dwSize, dwOffset, dwBufferSize;
    PByte  pbBuffer;
    HANDLE hFile;
    WChar  szPath[MAX_PATH];
    SMyPianoFileIndex *pIndex;

    wcscpy(szPath, lpszPath);
    dwRead = wcslen(lpszPath);
    while (szPath[--dwRead] == '\\')
        szPath[dwRead] = 0;

    ++dwRead;
    wcscpy(szPath + dwRead, L".dat");
    if (file.Open(szPath, file.W, file.N) == False)
        return 0;

    GetCurrentDirectoryW(countof(szPath), szPath);
    SetCurrentDirectoryW(lpszPath);

    dwOffset = 0;
    dwBufferSize = m_index.filenum * (sizeof(SPianoFileIndex) + sizeof(SPianoFileName2));
    pbBuffer = (PByte)m.Alloc(dwBufferSize);
    file.Write(DatHeader, sizeof(DatHeader) - 1);
    file.Write(&m_index.filenum, 4);
    file.Write(pbBuffer, dwBufferSize);
    pIndex =m_index.pIndex;
    for (UInt32 i = 0; i != m_index.filenum; ++i, ++pIndex)
    {
        hFile = CreateFileA(pIndex->name.name,
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
        if (hFile == INVALID_HANDLE_VALUE)
            continue;

        dwSize = GetFileSize(hFile, NULL);
        pIndex->index.size = dwSize;
        pIndex->index.offset = dwOffset;
        dwOffset += dwSize;
        if (dwSize > dwBufferSize)
        {
            dwBufferSize = dwSize;
            pbBuffer = (PByte)m.ReAlloc(dwBufferSize, pbBuffer);
        }
        ReadFile(hFile, pbBuffer, dwSize, &dwRead, NULL);
        CloseHandle(hFile);
        file.Write(pbBuffer, dwSize);
    }

    file.Seek(file.Seek_Beg, sizeof(SPianoHeader));
    pIndex =m_index.pIndex;
    for (UInt32 i = 0; i != m_index.filenum; ++i, ++pIndex)
        file.Write(pIndex->name.name, sizeof(pIndex->name.name));

    pIndex =m_index.pIndex;
    for (UInt32 i = 0; i != m_index.filenum; ++i, ++pIndex)
        file.Write(&pIndex->index, sizeof(pIndex->index));

    m.Free(pbBuffer);
    SetCurrentDirectoryW(szPath);

    return m_index.filenum;
}

Bool CPiano::InitIndex(PWChar lpszPath)
{
    DWORD  dwMaxNum, dwLength;
    HANDLE hFind;
    WChar szPath[MAX_PATH];
    ANSI_STRING ansi;
    WIN32_FIND_DATAW wfd;
    SMyPianoFileIndex *pIndex;

    wcscpy(szPath, lpszPath);
    dwLength = wcslen(szPath);
    wcscpy(szPath + dwLength, L"\\*.*");

    hFind = FindFirstFileW(szPath, &wfd);
    if (hFind == INVALID_HANDLE_VALUE)
        return False;

    while (!wcscmp(wfd.cFileName, L".") || !wcscmp(wfd.cFileName, L".."))
    {
        if (FindNextFileW(hFind, &wfd) == False)
        {
            FindClose(hFind);
            return False;
        }
    }

    dwMaxNum = 200;
    m_index.filenum = 0;
    pIndex = m_index.pIndex = (SMyPianoFileIndex *)m.Alloc(dwMaxNum * sizeof(*m_index.pIndex));
    if (pIndex == NULL)
    {
        FindClose(hFind);
        return False;
    }

    do
    {
        if (wcslen(wfd.cFileName) > sizeof(pIndex->name.name))
            continue;

        if (m_index.filenum == dwMaxNum)
        {
            dwMaxNum = dwMaxNum * 2;
            m_index.pIndex = (SMyPianoFileIndex *)m.ReAlloc(dwMaxNum * sizeof(*m_index.pIndex), m_index.pIndex);
            pIndex = m_index.pIndex + m_index.filenum;
        }

        ++m_index.filenum;
        ZeroMemory(pIndex->name.name, sizeof(pIndex->name.name));
        CFileDisk::UnicodeToAnsi(&ansi, wfd.cFileName, pIndex->name.name, sizeof(pIndex->name.name));
        ++pIndex;

    } while (FindNextFileW(hFind, &wfd));

    FindClose(hFind);
    m_index.pIndex = (SMyPianoFileIndex *)m.ReAlloc(m_index.filenum * sizeof(*m_index.pIndex), m_index.pIndex);

    return True;
}
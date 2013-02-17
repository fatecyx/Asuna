#pragma comment(lib, "ntdll.lib")

#include "malie.h"

const UInt32 CMalie::RawKey[] = { 0x485F4C5D, 0x7766756F, 0x7B54447D, 0x743B2D55 };

CMalie::CMalie() : keyBit(128)
{
    m_entry.pIndex = NULL;
}

CMalie::~CMalie()
{
    Release();
}

Void CMalie::Release()
{
    SafeFree(&m_entry.pIndex);
}

Void CMalie::Auto(PCWChar pszFileName)
{
    DWORD dwAttr = GetFileAttributesW(pszFileName);
    WChar szPath[MAX_PATH];
    WChar  buf[30];
    extern Bool bCtrlC;

    if (dwAttr == -1)
        return;

    if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
    {
        return;
    }

    if (Open(pszFileName) == False)
        return;

    lstrcpyW(szPath, pszFileName);
    rmextw(szPath);
    lstrcatW(szPath, L"\\");
    for (UInt32 i = 0; i != m_entry.count && !bCtrlC; ++i)
    {
        printf("Extracting \"%s\" ... ", &m_entry.pIndex[i]);
        swprintf(buf, L"%u / %u", i + 1, m_entry.count);
        SetConsoleTitleW(buf);
        printf("%s\n", ExtractFile(&m_entry.pIndex[i], szPath) ? "OK" : "failed");
    }
}

Bool CMalie::Open(PCWChar pszFileName)
{
    if (file.Open(pszFileName) == False)
        return False;

    Bool   r;
    UInt32 IndexSize;
    LPVoid lpBuffer;
    SMalieDatHeader header;

    if (file.Read(&header, sizeof(header)) == False)
        return False;

    Camellia_Ekeygen(keyBit, (PByte)RawKey, keyTable);
    Decrypt(keyBit, keyTable, &header, sizeof(header), 0);
    IndexSize = (header.IndexCount * 8 + header.OffsetTableCount) * 4 +16;
    IndexSize = header.IndexCount * sizeof(SMalieIndex) + header.OffsetTableCount * 4;
//    len = ((len + 0xFFF) >> 0xC) << 2;

    lpBuffer = Alloc(IndexSize);
    if (lpBuffer == NULL)
        return False;

    if (file.Read(lpBuffer, IndexSize) == False)
    {
        Free(lpBuffer);
        return False;
    }

    Decrypt(keyBit, keyTable, lpBuffer, IndexSize, sizeof(header));

    IndexSize = header.IndexCount * sizeof(SMalieIndex);
    r = InitIndex(lpBuffer, IndexSize, (PByte)lpBuffer + IndexSize, header.OffsetTableCount * 4);
    Free(lpBuffer);

    return r;
}

UInt32 AddFile(SMyMalieIndex *pMyIndex, UInt32 Count, SMyMalieIndex *pMyEnd, SMalieIndex *pIndex, UInt32 FileIndex, LPVoid lpOffsetTable, UInt32 OffsetCount, PChar pszFullPath, UInt32 IndexSize)
{
    UInt32 i, n;
    PUInt32 pOffsetTable = (PUInt32)lpOffsetTable;
    SMalieIndex *pCurIndex, *pEnd;
    SMyMalieIndex *pMyCurIndex;

    pEnd = (SMalieIndex *)lpOffsetTable;
    pCurIndex = pIndex + FileIndex;
    if (pCurIndex >= pEnd)
        return 0;

    pMyCurIndex = pMyIndex + Count;
    if (pMyCurIndex >= pMyEnd)
        return 0;

    i = StrLengthA(pszFullPath);
    if (i && pszFullPath[i - 1] != '\\')
        lstrcpyA(pszFullPath + i++, "\\");
    strncpy(pszFullPath + i, pCurIndex->name, sizeof(pCurIndex->name));

    if (!pCurIndex->usIsFile)
    {
        SMalieIndex *pSubFile;

        n = 0;
        pSubFile = pIndex + pCurIndex->SubFileIndex;
        for (UInt32 Files = 0; Files != pCurIndex->SubFileNum; ++Files, ++pSubFile)
        {
            n += AddFile(pMyIndex, Count + n, pMyEnd, pIndex, pSubFile - pIndex, lpOffsetTable, OffsetCount, pszFullPath, IndexSize);
        }

        Count = n;
    }
    else
    {
        Count = 1;
        strcpy(pMyCurIndex->name, pszFullPath);
        pMyCurIndex->offset = (pOffsetTable[pCurIndex->OffsetIndex] + IndexSize)  * 1024;
        pMyCurIndex->size   = pCurIndex->FileSize;
    }

    pszFullPath[i] = 0;

    return Count;
}

Bool CMalie::InitIndex(LPVoid lpIndex, UInt32 uIndexSize, LPVoid lpOffsetTable, UInt32 TableSize)
{
    Char   szFullPath[MAX_PATH];
    UInt32 MaxCount, Count;
    SMalieIndex *pIndex, *pEnd;

    MaxCount = uIndexSize / sizeof(*pIndex);
    if (MaxCount < TableSize / 4)
        MaxCount = TableSize / 4;

    m_entry.pIndex = (SMyMalieIndex *)Alloc(MaxCount * sizeof(*m_entry.pIndex));
    if (m_entry.pIndex == NULL)
        return False;

    pIndex = (SMalieIndex *)lpIndex;
    pEnd   = (SMalieIndex *)((PByte)lpIndex + uIndexSize);
    szFullPath[0] = 0;
    Count  = AddFile(m_entry.pIndex, 
                     0, 
                     m_entry.pIndex + MaxCount, 
                     pIndex, 
                     0, 
                     lpOffsetTable, 
                     TableSize / 4, szFullPath, 
                     (((uIndexSize + TableSize) + 0xFFF) >> 12) << 2);

    if (Count == 0)
        return False;

    if (Count != MaxCount)
        m_entry.pIndex = (SMyMalieIndex *)ReAlloc(m_entry.pIndex, Count * sizeof(*m_entry.pIndex));
    m_entry.count = Count;

    return True;
}

UInt32 CMalie::ExtractFile(SMyMalieIndex *pInfo, PCWChar lpOutPath /* = NULL */)
{
    UInt32 uSize;
    SFileInfo info;
    WChar szFile[MAX_PATH * 2];
    UNICODE_STRING ustr;

//    if (stricmp(pInfo->name, "screen\\char\\00.png")) return 0;

    if (GetFileData(&info, pInfo) == False)
        return 0;

    if (lpOutPath)
    {
        lstrcpyW(szFile, lpOutPath);
        rmextw(szFile);
        lstrcatW(szFile, L"\\");
        uSize = StrLengthW(szFile);
    }
    else
    {
        szFile[0] = 0;
        uSize = 0;
    }

    UNUSED_VARIABLE(ustr);
//    CFileDisk::AnsiToUnicode(&ustr, pInfo->name, szFile + uSize, countof(szFile) - uSize);
    MultiByteToWideChar(CP_ACP, 0, pInfo->name, -1, szFile + uSize, countof(szFile) - uSize);
    uSize = findnamew(szFile) - szFile;
    if (uSize)
    {
        szFile[--uSize] = 0;
        MyCreateDirectoryW(szFile);
        szFile[uSize] = L'\\';
    }

    CFileDisk f;

    uSize = 0;
    if (info.type == BIN)
    {
        if (f.Create(szFile))
        {
            f.Write(info.BinData.data, info.BinData.size);
            uSize = info.BinData.size;
        }
    }

    FreeFileData(&info);

    return uSize;
}

Bool CMalie::GetFileData(SFileInfo *pFileInfo, const SMyMalieIndex *pInfo)
{
    if (file.Seek(file.FILE_SEEK_BEGIN, pInfo->offset) == False)
        return False;

    PByte pbBuffer;
    UInt32 Size = pInfo->size;

    Size = (Size + 15) & ~15;
    pbBuffer = (PByte)Alloc(Size);
    if (pbBuffer == NULL)
        return False;

    if (file.Read(pbBuffer, Size) == False)
    {
        Free(pbBuffer);
        return False;
    }

    pFileInfo->extra = NULL;
    pFileInfo->type = BIN;
    pFileInfo->BinData.size = pInfo->size;
    pFileInfo->BinData.data = pbBuffer;

    Decrypt(keyBit, keyTable, pbBuffer, Size, pInfo->offset);

    return True;
}

Void CMalie::Decrypt(Int32 KeyBits, KEY_TABLE_TYPE KeyTable, LPVoid lpBuffer, Int32 Size, Int64 Offset)
{
    PByte  pbBuffer;
    Int32 stride;

    stride = KeyBits / 8;
    pbBuffer = (PByte)lpBuffer;
    while (Size >= stride)
    {
        UInt32 mask = ((Offset >> 4) & 0xF) + 16;
        *(PUInt32)pbBuffer      = _rotl(*(PUInt32)pbBuffer, mask);
        *(PUInt32)&pbBuffer[4]  = _rotr(*(PUInt32)&pbBuffer[4], mask);
        *(PUInt32)&pbBuffer[8]  = _rotl(*(PUInt32)&pbBuffer[8], mask);
        *(PUInt32)&pbBuffer[12] = _rotr(*(PUInt32)&pbBuffer[12], mask);
        Camellia_DecryptBlock(KeyBits, pbBuffer, KeyTable, pbBuffer);

        Size -= stride;
        Offset += stride;
        pbBuffer += stride;
    }
/*
    if (0) if (Size)
    {
        PByte buf;
        UInt32 mask = ((Offset >> 4) & 0xF) + 16;

        buf = (PByte)_alloca(stride);
        ZeroMemory(buf, stride);
        memcpy(buf, pbBuffer, Size);

        *(PUInt32)buf      = _rotl(*(PUInt32)buf, mask);
        *(PUInt32)&buf[4]  = _rotr(*(PUInt32)&buf[4], mask);
        *(PUInt32)&buf[8]  = _rotl(*(PUInt32)&buf[8], mask);
        *(PUInt32)&buf[12] = _rotr(*(PUInt32)&buf[12], mask);

        Camellia_DecryptBlock(KeyBits, buf, KeyTable, buf);

        memcpy(pbBuffer, buf, Size);
    }
*/
}

Void CMalie::FreeFileData(SFileInfo *info)
{
    if (info == NULL)
        return;

    Free(info->extra);

    if (info->type == BIN)
        Free(info->BinData.data);
    else if (info->type == IMG)
    {
        if (info->ImgData == NULL)
            return;

        for (UInt32 i = 0, j = info->count; i != j; ++i)
            Free(info->ImgData[i].data);
        Free(info->ImgData);
    }
}
// yu-ris script engine
// MagusTale～世界樹と恋する魔法使い～
// 女装山脈

#pragma comment(lib, "ntdll.lib")

#include "MagusTale.h"
#include "zlib/zlib.h"

Bool CYuris::Open(PCWChar szFileName)
{
    ReleaseAll();

    if (f.Open(szFileName) == False)
        return False;

    Bool  r;
    PByte pbEntry;
    YURIS_YPF_HEADER h;

    if (f.Read(&h, sizeof(h)) == False)
        return False;

    if (h.Magic != TAG3('YPF') || (h.Version != 0x107 && h.Version != 0x122 && h.Version != 0x1C2))
        return False;

    pbEntry = (PByte)m.Alloc(h.EntrySize + 1);
    if (pbEntry == NULL)
        return False;

    f.Seek(f.FILE_SEEK_BEGIN, 0x20);
    if (f.Read(pbEntry, h.EntrySize) == False)
    {
        m.Free(pbEntry);
        return False;
    }

    r = InitIndex(pbEntry, h.EntrySize, &h);
    m.Free(pbEntry);

    return r;
}

Bool CYuris::InitIndex(PByte pbBuffer, UInt32 uSize, const YURIS_YPF_HEADER *pHeader)
{
    if (pbBuffer == NULL || pHeader == NULL || pHeader->FileCount == 0)
        return False;

    PByte  pbEnd, pbLengthTable;
    UInt32 Key, CodePage;
    YURIS_YPF_FILE_INFO *info;
    YURIS_YPF_ENTRY     *pInfo;

#define NEKOKOI

    switch (pHeader->Version)
    {
        case 0x107:
            Key = 0x40;
            pbLengthTable = (PByte)LengthTable_107;
            break;

        case 0x122:
#if defined(NEKOKOI)
            Key = 0xCB;
#else
            Key = 0x3F;
#endif
            pbLengthTable = (PByte)LengthTable_122;
            break;

        case 0x1C2:
            Key = 0;
            pbLengthTable = (PByte)LengthTable_1C2;
            break;

        default:
            return False;
    }

    m_Index.cbEntrySize = sizeof(YURIS_YPF_ENTRY);
    m_Index.pEntry = (YURIS_YPF_ENTRY *)m.Alloc(m_Index.cbEntrySize * pHeader->FileCount);
    if (m_Index.pEntry == NULL)
        return False;

    pInfo = (YURIS_YPF_ENTRY *)m_Index.pEntry;
    m_Index.FileCount.QuadPart = 0;

    pbEnd = pbBuffer + uSize;
    for (UInt32 i = pHeader->FileCount + 1; --i && pbBuffer < pbEnd; ++pInfo)
    {
        Byte len;

        ++m_Index.FileCount.QuadPart;
        pInfo->Hash1 = *(PUInt32)pbBuffer;
        pbBuffer += 4;
        len = *pbBuffer++;
        len = pbLengthTable[len];
        DecryptFileName(pbBuffer, len, Key);
        CodePage = IsShiftJISString((PCChar)pbBuffer, len) ? CP_SHIFTJIS : CP_GB2312;
        CodePage = MultiByteToWideChar(CodePage, 0, (PCChar)pbBuffer, len, pInfo->FileName, countof(pInfo->FileName));
        pbBuffer += len;
        pInfo->FileName[CodePage] = 0;
        info = (YURIS_YPF_FILE_INFO *)pbBuffer;
        pbBuffer += sizeof(*info);

        pInfo->Flags                    = !!info->bComp;
        pInfo->FileType                 = info->FileType;
        pInfo->CompressedSize.QuadPart  = info->compsize;
        pInfo->Size.QuadPart            = info->decompsize;
        pInfo->FileHash                 = info->hash;
        pInfo->Offset.QuadPart          = info->offset;
    }

    m_YpfVersion = pHeader->Version;

    return True;
}

Bool CYuris::GetFileData(SFileInfo *pFileInfo, const MY_FILE_ENTRY_BASE *pEntry)
{
    PByte pbBuffer, pbFile;
    ULong ulDestSize, ulSrcSize;
    ULong Mask;
    const YURIS_YPF_ENTRY *pInfo;

    pInfo = (const YURIS_YPF_ENTRY *)pEntry;

    switch (m_YpfVersion)
    {
        case 0x107:
            Mask = TAG4(0x07B4024A);
            break;

        case 0x122:
        case 0x1C2:
            Mask = 0x96AC6FD3;
            break;

        default:
            return False;
    }

    ulSrcSize = max(pInfo->Size.LowPart, pInfo->Size.LowPart);
    pbFile = (PByte)m.Alloc(ulSrcSize);
    if (pbFile == NULL)
        return False;

    f.Seek(f.FILE_SEEK_BEGIN, pInfo->Offset.LowPart);
    f.Read(pbFile, pInfo->CompressedSize.LowPart);
    if (pInfo->Flags & UNPACKER_ENTRY_FLAG_COMPRESSED)
    {
        Bool r;

        pbBuffer = (PByte)m.Alloc(pInfo->CompressedSize.LowPart);
        if (pbBuffer == NULL)
        {
            m.Free(pbFile);
            return False;
        }

        memcpy(pbBuffer, pbFile, pInfo->CompressedSize.LowPart);
        ulDestSize = pInfo->Size.LowPart;
        r = uncompress(pbFile, &ulDestSize, pbBuffer, pInfo->CompressedSize.LowPart);
        m.Free(pbBuffer);
        if (r != Z_OK)
        {
            m.Free(pbFile);
            return False;
        }
    }

    if (*(PUInt32)pbFile == TAG4('YSTB'))
    {
        EncryptScript(pbFile, pInfo->Size.LowPart, m_YpfVersion);
    }

#if 0
    if (0) LOOP_ONCE
    {
        ULong Part1, Part2;

        switch (m_YpfVersion)
        {
            case 0x107:
                Part1 = *(PULong)(pbFile + 0x8);
                Part2 = *(PULong)(pbFile + 0xC);
                break;

            case 0x122:
            case 0x1C2:
                Part1 = *(PULong)(pbFile + 0xC);
                Part2 = *(PULong)(pbFile + 0x10);
                break;

            default:
                m_mem.Free(pbFile);
                return False;
        }

        pbBuffer = pbFile + 0x20;

/************************************************************************
mov     r32, r32
and     r32, 0x3
movzx   r32, byte ptr [r32+const]
xor     byte ptr [r32 - const], r8
inc     r32
cmp     r32, r32
************************************************************************/

        while (Part1 > 3)
        {
            *(PULong)pbBuffer ^= Mask;
            pbBuffer += 4;
            Part1 -= 4;
        }
        for (ULong i = 0, j = Part1; i != j; ++i)
            *pbBuffer++ ^= Mask >> (i * 8);

        while (Part2 > 3)
        {
            *(PULong)pbBuffer ^= Mask;
            pbBuffer += 4;
            Part2 -= 4;
        }
        for (ULong i = 0, j = Part2; i != j; ++i)
            *pbBuffer++ ^= Mask >> (i * 8);

        if (m_YpfVersion == 0x107)
            break;

        Part1 = *(PULong)(pbFile + 0x14);
        Part2 = *(PULong)(pbFile + 0x18);

        while (Part1 > 3)
        {
            *(PULong)pbBuffer ^= Mask;
            pbBuffer += 4;
            Part1 -= 4;
        }
        for (ULong i = 0, j = Part1; i != j; ++i)
            *pbBuffer++ ^= Mask >> (i * 8);

        while (Part2 > 3)
        {
            *(PULong)pbBuffer ^= Mask;
            pbBuffer += 4;
            Part2 -= 4;
        }
        for (ULong i = 0, j = Part2; i != j; ++i)
            *pbBuffer++ ^= Mask >> (i * 8);
    }

#endif

    pFileInfo->FileType           = UNPACKER_FILE_TYPE_BIN;
    pFileInfo->BinData.pbBuffer   = pbFile;
    pFileInfo->BinData.BufferSize = pInfo->Size.LowPart;

    return True;
}

HRESULT CYuris::EncryptScript(PVOID pvBuffer, ULONG BufferSize, ULONG Version)
{
    PBYTE pbFile, pbBuffer;
    ULONG Mask, Part1, Part2;

    UNREFERENCED_PARAMETER(BufferSize);

    pbFile = (PByte)pvBuffer;
    pbBuffer = pbFile + 0x20;

    switch (Version)
    {
        case 0x107:
            Mask = TAG4(0x07B4024A);
            Mask = 0x4A02B407;
            Part1 = *(PULong)(pbFile + 0x8);
            Part2 = *(PULong)(pbFile + 0xC);
            break;

        case 0x122:
        case 0x1C2:
            Part1 = *(PULong)(pbFile + 0xC);
            Part2 = *(PULong)(pbFile + 0x10);
            Mask = 0x96AC6FD3;
            break;

        default:
            return TYPE_E_UNSUPFORMAT;
    }

    while (Part1 > 3)
    {
        *(PULong)pbBuffer ^= Mask;
        pbBuffer += 4;
        Part1 -= 4;
    }
    for (ULong i = 0, j = Part1; i != j; ++i)
        *pbBuffer++ ^= Mask >> (i * 8);

    while (Part2 > 3)
    {
        *(PULong)pbBuffer ^= Mask;
        pbBuffer += 4;
        Part2 -= 4;
    }
    for (ULong i = 0, j = Part2; i != j; ++i)
        *pbBuffer++ ^= Mask >> (i * 8);

    if (Version == 0x107)
        return S_OK;

    Part1 = *(PULong)(pbFile + 0x14);
    Part2 = *(PULong)(pbFile + 0x18);

    while (Part1 > 3)
    {
        *(PULong)pbBuffer ^= Mask;
        pbBuffer += 4;
        Part1 -= 4;
    }
    for (ULong i = 0, j = Part1; i != j; ++i)
        *pbBuffer++ ^= Mask >> (i * 8);

    while (Part2 > 3)
    {
        *(PULong)pbBuffer ^= Mask;
        pbBuffer += 4;
        Part2 -= 4;
    }
    for (ULong i = 0, j = Part2; i != j; ++i)
        *pbBuffer++ ^= Mask >> (i * 8);

    return S_OK;
}

Void CYuris::DecryptFileName(PByte pbBuffer, UInt32 uSize, Byte Key)
{
    while (uSize--)
        pbBuffer[uSize] = (-pbBuffer[uSize] - 1) ^ Key;
}

UInt32 CYuris::HashFileName(LPVoid lpFileName, Int32 Length)
{
    PByte  pbFileName = (PByte)lpFileName;
    UInt32 Hash = -1;

    while (Length--)
    {
        Hash = (Hash >> 8) ^ HashTable[(*pbFileName++ ^ Hash) & 0xFF];
    }

    return ~Hash;
}

PWChar CYuris::GetExtensionByFileType(UInt32 FileType)
{
    WChar *szExtension[] =
    {
        NULL, L".bmp", L".png", L".jpg", L".gif", L".wav", L".ogg", L".psd",
    };

    return FileType < countof(szExtension) ? szExtension[FileType] : NULL;
}

LONG STDCALL EnumCallback(YURIS_YPF_ENTRY *pEntry, PWIN32_FIND_DATAW pFindData, ULONG_PTR Length)
{
    lstrcpyW(pEntry->FileName, pFindData->cFileName + Length);
    pEntry->Flags           = 0;
    pEntry->Size.LowPart    = pFindData->nFileSizeLow;
    pEntry->Size.HighPart   = pFindData->nFileSizeHigh;

    return 1;
}

ULONG
CYuris::
GenerateYpfIndex(
    YURIS_YPF_ENTRY *pFileList,
    LARGE_INTEGER    FileCount,
    PVOID            pvYpfIndexBuffer,
    ULONG            BufferSize
)
{
    CHAR             szAnsiName[MAX_PATH];
    PBYTE            pbIndex;
    ULONG            Length;
    YURIS_YPF_ENTRY *pEntry;

    UNREFERENCED_PARAMETER(BufferSize);

    if (pvYpfIndexBuffer == NULL)
    {
        BYTE FileNameLength;

        UNREFERENCED_PARAMETER(FileNameLength);

        BufferSize = 0;

        for (; FileCount.LowPart; --FileCount.LowPart)
        {
            WCHAR szFile[MAX_PATH];

            BufferSize += sizeof(pFileList->Hash1) + sizeof(FileNameLength) + sizeof(YURIS_YPF_FILE_INFO);

            Length = StrLengthW(pFileList->FileName);
            CopyMemory(szFile, pFileList->FileName, Length * sizeof(*szFile));
            FilterString(szFile, Length);
            BufferSize += WideCharToMultiByte(CP_GB2312, 0, pFileList->FileName, Length, NULL, 0, NULL, NULL);

            ++pFileList;
        }

        return BufferSize;
    }

    pEntry   = pFileList;
    pbIndex  = (PBYTE)pvYpfIndexBuffer;
    for (ULONG Count = FileCount.LowPart; Count; ++pEntry, --Count)
    {
        ULONG LengthIndex;
        YURIS_YPF_FILE_INFO *pYpfInfo;

        Length = WideCharToMultiByte(
                    CP_GB2312,
                    0,
                    pEntry->FileName,
                    -1,
                    szAnsiName,
                    countof(szAnsiName),
                    NULL,
                    NULL);
        --Length;

        for (LengthIndex = 0; LengthIndex != 256; ++LengthIndex)
            if (Length == LengthTable_122[LengthIndex])
                break;

        *(PULONG)pbIndex = pEntry->Hash1;
        pbIndex += sizeof(ULONG);
        *pbIndex++ = LengthIndex;
        CopyMemory(pbIndex, szAnsiName, Length);
        DecryptFileName(pbIndex, Length, 0xCB);
        pbIndex += Length;

        pYpfInfo = (YURIS_YPF_FILE_INFO *)pbIndex;

        pYpfInfo->bComp         = TEST_BITS(pEntry->Flags, UNPACKER_ENTRY_FLAG_COMPRESSED);
        pYpfInfo->compsize      = pEntry->CompressedSize.LowPart;
        pYpfInfo->decompsize    = pEntry->Size.LowPart;
        pYpfInfo->offset        = pEntry->Offset.LowPart;
        pYpfInfo->hash          = pEntry->FileHash;
        pYpfInfo->FileType      = GetYpfFileType(pEntry->FileName);

        pbIndex += sizeof(*pYpfInfo);
    }

    return (ULONG_PTR)pbIndex - (ULONG_PTR)pvYpfIndexBuffer;
}

ULONG CYuris::GetYpfFileType(PWChar pszFileName)
{
    WChar *szExtension[] = 
    {
        NULL, L".bmp", L".png", L".jpg", L".gif", L".wav", L".ogg", L".psd", 
    };
    
    for (UInt i = 0; i != countof(szExtension); ++i)
        if (!StrICompareW(szExtension[i], findextw(pszFileName)))
            return i;
        return 0;
}

ULONG CYuris::CalcYpfIndexSize(YURIS_YPF_ENTRY *pFileList, LARGE_INTEGER FileCount)
{
    return GenerateYpfIndex(pFileList, FileCount, NULL, 0);
}

SizeT CYuris::Pack(PCWChar pszPath)
{
    WCHAR               szYpfFileName[MAX_PATH];
    PWCHAR              pszFileName;
    PVOID               pvCompressed, pvBuffer;
    ULONG               Length, PackedFile, YpfIndexSize, CompressedBufferSize, BufferSize;
    LARGE_INTEGER       FileCount;
    YURIS_YPF_ENTRY    *pFileList;
    YURIS_YPF_HEADER    YpfHeader;
    CFileDisk           ypf;

    Length = StrLengthW(pszPath);
    
    pszFileName = szYpfFileName + Length;

    CopyMemory(szYpfFileName, pszPath, Length * sizeof(*pszPath));
    pszFileName -= pszFileName[-1] == '\\';
    CopyMemory(pszFileName, YURIS_YPF_EXTENSION, sizeof(YURIS_YPF_EXTENSION));

    if (!ypf.Create(szYpfFileName))
        return 0;

    if (!EnumDirectoryFiles(
            (PVOID *)&pFileList,
            L"*.*",
            sizeof(*pFileList),
            pszPath,
            &FileCount,
            (EnumDirectoryFilesCallBackFunc)EnumCallback,
            Length + (pszPath[Length - 1] != '\\'),
            ENUM_DIRECTORY_FILES_FLAG_ENUMSUBDIR
         ))
    {
        return 0;
    }

    PackedFile = 0;
    YpfIndexSize = CalcYpfIndexSize(pFileList, FileCount);

    YpfHeader.Magic     = YURIS_YPF_MAGIC;
    YpfHeader.Version   = 0x122;
    YpfHeader.EntrySize = YpfIndexSize;
    YpfHeader.FileCount = FileCount.LowPart;

    ypf.Write(&YpfHeader, sizeof(YpfHeader));
    ypf.Seek(ypf.FILE_SEEK_CURRENT, YpfIndexSize + YURIS_YPF_HEADER_OVERHEAD);

    BufferSize              = MY_MAX(YpfIndexSize, 0x100000);
    CompressedBufferSize    = BufferSize;

    pvBuffer        = NULL;
    pvCompressed    = NULL;

    LOOP_ONCE
    {
        PVOID            pvFile;
        LARGE_INTEGER    Offset;
        YURIS_YPF_ENTRY *pEntry;

        pvBuffer = Alloc(BufferSize);
        if (pvBuffer == NULL)
            break;

        pvCompressed = Alloc(CompressedBufferSize);
        if (pvCompressed == NULL)
            break;

        *pszFileName++ = '\\';
        Offset.QuadPart = sizeof(YpfHeader) + YpfIndexSize + YURIS_YPF_HEADER_OVERHEAD;

        pEntry = pFileList;
        for (ULONG Count = FileCount.LowPart; Count; ++pEntry, --Count)
        {
            ULONG Magic;

            lstrcpyW(pszFileName, pEntry->FileName);
            if (!f.Open(szYpfFileName))
                continue;

            pEntry->Offset.QuadPart = Offset.QuadPart;

            Length = f.GetSize();
            if (Length == 0)
            {
                pEntry->CompressedSize.QuadPart = Length;
                continue;
            }

            if (Length > BufferSize)
            {
                BufferSize = Length;
                pvBuffer = ReAlloc(pvBuffer, BufferSize);
                if (pvBuffer == NULL)
                    goto _Error;
            }

            f.Read(pvBuffer, Length);

            Magic = *(PULONG)pvBuffer;
            if (Magic == YURIS_YBN_MAGIC)
            {
                EncryptScript(pvBuffer, Length, YpfHeader.Version);
                pEntry->Flags = UNPACKER_ENTRY_FLAG_COMPRESSED;
            }
            else if (Magic                  != TAG4('OggS') &&
                    (Magic >> 8)            != TAG3('PNG') &&
                    (Magic & 0x00FFFFFF)    != 0xFFD8FF)
            {
                pEntry->Flags = UNPACKER_ENTRY_FLAG_COMPRESSED;
            }
            else
            {
                pEntry->Flags = 0;
            }

            pvFile = pvBuffer;
            if (TEST_BITS(pEntry->Flags, UNPACKER_ENTRY_FLAG_COMPRESSED))
            {
                if (Length > CompressedBufferSize)
                {
                    CompressedBufferSize = Length;
                    pvCompressed = ReAlloc(pvCompressed, CompressedBufferSize);
                    if (pvCompressed == NULL)
                        goto _Error;
                }

                if (Length * 4 > BufferSize)
                {
                    BufferSize = Length * 4;
                    pvBuffer = ReAlloc(pvBuffer, BufferSize);
                    if (pvBuffer == NULL)
                        goto _Error;
                }

                CopyMemory(pvCompressed, pvBuffer, Length);

                pEntry->CompressedSize.LowPart = BufferSize;
                if (compress2(
                        (PBYTE)pvBuffer,
                        &pEntry->CompressedSize.LowPart,
                        (PBYTE)pvCompressed,
                        Length,
                        Z_BEST_COMPRESSION
                    ) != Z_OK)
                {
                    goto _Error;
                }

                if (Length < pEntry->CompressedSize.LowPart)
                    pvFile = pvCompressed;
                else
                    Length = pEntry->CompressedSize.LowPart;
            }

            pEntry->CompressedSize.QuadPart = Length;
            pEntry->FileHash = adler32(1, (PBYTE)pvBuffer, Length);
            Offset.QuadPart += Length;
            ypf.Write(pvFile, Length);
        }

        qsort(pFileList, FileCount.LowPart, sizeof(*pFileList), (int (CDECL *)(const void*,const void*))compare);

        YpfIndexSize = GenerateYpfIndex(pFileList, FileCount, pvBuffer, BufferSize);
        ypf.Seek(ypf.FILE_SEEK_BEGIN, sizeof(YpfHeader) + YURIS_YPF_HEADER_OVERHEAD);
        ypf.Write(pvBuffer, YpfIndexSize);

        PackedFile = FileCount.LowPart;
    }

_Error:
    Free(pvBuffer);
    Free(pvCompressed);
    EnumDirectoryFilesFree(pFileList);

    return PackedFile;
}

int CDECL CYuris::compare(YURIS_YPF_ENTRY *p1, YURIS_YPF_ENTRY *p2)
{
    UInt32 len1, len2;
    Char n1[MAX_PATH], n2[MAX_PATH];

    len1 = WideCharToMultiByte(CP_GB2312, 0, p1->FileName, -1, n1, sizeof(n1), 0, 0) - 1;
    len2 = WideCharToMultiByte(CP_GB2312, 0, p2->FileName, -1, n2, sizeof(n2), 0, 0) - 1;

    len1 = HashFileName(n1, len1);
    len2 = HashFileName(n2, len2);

    p1->Hash1 = len1;
    p2->Hash1 = len2;

    if (len1 < len2)
        return -1;
    if (len1 == len2)
        return 0;
    return 1;
}

const Byte CYuris::LengthTable_107[256] =
{
    0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6,
    0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0, 0xEF, 0xEE, 0xED, 0xEC,
    0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2,
    0xE1, 0xE0, 0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8,
    0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0, 0xCF, 0xCE,
    0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4,
    0xC3, 0xC2, 0xC1, 0xC0, 0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA,
    0xB9, 0xB8, 0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0,
    0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0xA7, 0xA6,
    0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0, 0x9F, 0x9E, 0x9D, 0x9C,
    0x9B, 0x9A, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0x92,
    0x91, 0x90, 0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88,
    0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80, 0x7F, 0x7E,
    0x7D, 0x7C, 0x7B, 0x7A, 0x79, 0x78, 0x77, 0x76, 0x75, 0x74,
    0x73, 0x72, 0x71, 0x70, 0x6F, 0x6E, 0x6D, 0x6C, 0x6B, 0x6A,
    0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x60,
    0x5F, 0x5E, 0x5D, 0x5C, 0x5B, 0x5A, 0x59, 0x58, 0x57, 0x56,
    0x55, 0x54, 0x53, 0x52, 0x51, 0x50, 0x4F, 0x4E, 0x4D, 0x4C,
    0x4B, 0x4A, 0x49, 0x48, 0x47, 0x46, 0x45, 0x44, 0x43, 0x42,
    0x41, 0x40, 0x3F, 0x3E, 0x3D, 0x3C, 0x3B, 0x3A, 0x39, 0x38,
    0x37, 0x36, 0x35, 0x34, 0x33, 0x2E, 0x31, 0x30, 0x2C, 0x32,
    0x2D, 0x2F, 0x2B, 0x2A, 0x26, 0x28, 0x27, 0x29, 0x25, 0x24,
    0x20, 0x22, 0x21, 0x23, 0x1F, 0x1C, 0x1D, 0x1E, 0x15, 0x1A,
    0x11, 0x18, 0x17, 0x16, 0x1B, 0x14, 0x0D, 0x12, 0x19, 0x0C,
    0x0F, 0x0E, 0x13, 0x10, 0x09, 0x0A, 0x0B, 0x08, 0x07, 0x06,
    0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
};

const Byte CYuris::LengthTable_122[256] =
{
    0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6,
    0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0, 0xEF, 0xEE, 0xED, 0xEC,
    0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2,
    0xE1, 0xE0, 0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8,
    0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0, 0xCF, 0xCE,
    0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4,
    0xC3, 0xC2, 0xC1, 0xC0, 0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA,
    0xB9, 0xB8, 0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0,
    0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0xA7, 0xA6,
    0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0, 0x9F, 0x9E, 0x9D, 0x9C,
    0x9B, 0x9A, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0x92,
    0x91, 0x90, 0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88,
    0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80, 0x7F, 0x7E,
    0x7D, 0x7C, 0x7B, 0x7A, 0x79, 0x78, 0x77, 0x76, 0x75, 0x74,
    0x73, 0x72, 0x71, 0x70, 0x6F, 0x6E, 0x6D, 0x6C, 0x6B, 0x6A,
    0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x60,
    0x5F, 0x5E, 0x5D, 0x5C, 0x5B, 0x5A, 0x59, 0x58, 0x57, 0x56,
    0x55, 0x54, 0x53, 0x52, 0x51, 0x50, 0x4F, 0x4E, 0x4D, 0x4C,
    0x4B, 0x4A, 0x49, 0x03, 0x47, 0x46, 0x45, 0x44, 0x43, 0x42,
    0x41, 0x40, 0x3F, 0x3E, 0x3D, 0x3C, 0x3B, 0x3A, 0x39, 0x38,
    0x37, 0x36, 0x06, 0x34, 0x33, 0x2E, 0x31, 0x30, 0x2C, 0x32,
    0x2D, 0x2F, 0x2B, 0x2A, 0x26, 0x28, 0x27, 0x29, 0x25, 0x24,
    0x20, 0x22, 0x21, 0x23, 0x1F, 0x1C, 0x1D, 0x1E, 0x15, 0x1A,
    0x11, 0x18, 0x17, 0x16, 0x1B, 0x14, 0x0D, 0x12, 0x19, 0x0C,
    0x0F, 0x0E, 0x13, 0x10, 0x09, 0x0A, 0x0B, 0x08, 0x07, 0x35,
    0x05, 0x04, 0x48, 0x02, 0x01, 0x00,
};

const Byte CYuris::LengthTable_1C2[256] =
{
    0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6,
    0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0, 0xEF, 0xEE, 0xED, 0xEC,
    0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2,
    0xE1, 0xE0, 0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8,
    0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0, 0xCF, 0xCE,
    0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4,
    0xC3, 0xC2, 0xC1, 0xC0, 0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA,
    0xB9, 0xB8, 0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0,
    0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0xA7, 0xA6,
    0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0, 0x9F, 0x9E, 0x9D, 0x9C,
    0x9B, 0x9A, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0x92,
    0x91, 0x90, 0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88,
    0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80, 0x7F, 0x7E,
    0x7D, 0x7C, 0x7B, 0x7A, 0x79, 0x78, 0x77, 0x76, 0x75, 0x74,
    0x73, 0x72, 0x71, 0x70, 0x6F, 0x6E, 0x6D, 0x6C, 0x6B, 0x6A,
    0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x60,
    0x5F, 0x5E, 0x5D, 0x5C, 0x5B, 0x5A, 0x59, 0x58, 0x57, 0x56,
    0x55, 0x54, 0x53, 0x52, 0x51, 0x50, 0x4F, 0x4E, 0x4D, 0x4C,
    0x4B, 0x4A, 0x49, 0x03, 0x47, 0x46, 0x45, 0x44, 0x43, 0x42,
    0x41, 0x40, 0x3F, 0x3E, 0x3D, 0x3C, 0x3B, 0x3A, 0x39, 0x38,
    0x37, 0x36, 0x06, 0x34, 0x33, 0x2E, 0x31, 0x30, 0x2C, 0x32,
    0x2D, 0x2F, 0x2B, 0x2A, 0x26, 0x28, 0x27, 0x29, 0x25, 0x24,
    0x20, 0x22, 0x21, 0x23, 0x1F, 0x1C, 0x1D, 0x1E, 0x15, 0x1A,
    0x11, 0x18, 0x17, 0x16, 0x1B, 0x14, 0x0D, 0x12, 0x19, 0x0C,
    0x0F, 0x0E, 0x13, 0x10, 0x09, 0x0A, 0x0B, 0x08, 0x07, 0x35,
    0x05, 0x04, 0x48, 0x02, 0x01, 0x00,
};

const UInt32 CYuris::HashTable[256] =
{
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3, 0x0EDB8832, 0x79DCB8A4,
    0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, 0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
    0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7, 0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9,
    0xFA0F3D63, 0x8D080DF5, 0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59, 0x26D930AC, 0x51DE003A,
    0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F, 0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
    0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D, 0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F,
    0x9FBFE4A5, 0xE8B8D433, 0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, 0x65B0D9C6, 0x12B7E950,
    0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65, 0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
    0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB, 0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5,
    0xAA0A4C5F, 0xDD0D7CC9, 0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD, 0xEDB88320, 0x9ABFB3B6,
    0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683, 0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
    0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1, 0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB,
    0x196C3671, 0x6E6B06E7, 0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B, 0xD80D2BDA, 0xAF0A1B4C,
    0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79, 0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
    0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F, 0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31,
    0x2CD99E8B, 0x5BDEAE1D, 0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, 0x86D3D2D4, 0xF1D4E242,
    0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777, 0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
    0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45, 0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7,
    0x4969474D, 0x3E6E77DB, 0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF, 0xB3667A2E, 0xC4614AB8,
    0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};
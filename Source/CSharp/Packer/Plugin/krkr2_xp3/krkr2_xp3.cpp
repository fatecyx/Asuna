#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text /MERGE:.data1=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "krkr2_xp3.h"
#include "my_crt.h"
#include "zlib/zlib.h"
#include "DynamicCode.h"
#include "../plugin_common.h"

OVERLOAD_OP_NEW

Bool STDCALL Decrypt_Golden(const SXP3ExtractionInfo *pInfo, LPVoid lpExtraInfo);

enum EDYNAMICPARAM { E_FATE_HA, E_REAL_SISTER, E_NATSU_ZORA, E_TENSHIN };

SParam param[] = 
{
    { L"fatesn",     Decrypt_FateSN }, 
    { L"fateha",     Decrypt_Dynamic, (LPVoid)E_FATE_HA }, 
    { L"realsister", Decrypt_Dynamic, (LPVoid)E_REAL_SISTER }, 
    { L"natsuzora",  Decrypt_Dynamic, (LPVoid)E_NATSU_ZORA }, 
    { L"tenshin",    Decrypt_Dynamic, (LPVoid)E_TENSHIN }, 
    { L"golden",     Decrypt_Golden }, 
};

Bool STDCALL Decrypt_Golden(const SXP3ExtractionInfo *pInfo, LPVoid lpExtraInfo)
{
    Byte  Hash = ~pInfo->FileHash;
    PByte pbBuffer = (PByte)pInfo->Buffer;

    for (UInt32 i = 0; i != pInfo->BufferSize; ++i, ++pbBuffer)
        *pbBuffer = ~(*pbBuffer ^ Hash);

    return True;
}

Bool STDCALL Decrypt_FateSN(const SXP3ExtractionInfo *pInfo, LPVoid lpExtraInfo)
{
    SXP3ExtractionInfo Info;
    PByte pbBuffer;

    Info = *pInfo;
    pbBuffer = (PByte)Info.Buffer;

    if (Info.Offset.QuadPart <= 0x13 && Info.Offset.QuadPart + Info.BufferSize > 0x13)
    {
        pbBuffer[0x13 - Info.Offset.QuadPart] ^= 1;
    }
    if (Info.Offset.QuadPart <= 0x2EA29 && Info.Offset.QuadPart + Info.BufferSize > 0x2EA29)
    {
        pbBuffer[0x2EA29 - Info.Offset.QuadPart] ^= 3;
    }

    memxor4(pbBuffer, 0x36363636, Info.BufferSize);

    return True;
}

CDynamicCodeBase *g_dcode;

Bool DecryptInternal(UInt32 Hash, LARGE_INTEGER liOffset, LPVoid lpBuffer, UInt32 BufferSize)
{
    PByte  pbBuffer;
    UInt32 Hash2;
    LARGE_INTEGER liHash, liCurPos;
    CDynamicCodeBase *pCode;

    pCode = g_dcode;

    pbBuffer = (PByte)lpBuffer;
    Hash2 = pCode->GetMask(Hash);

    liCurPos.QuadPart = liOffset.QuadPart + BufferSize;
    liHash.QuadPart = LoWord(Hash2);
    if (liHash.QuadPart >= liOffset.QuadPart && liHash.QuadPart < liCurPos.QuadPart)
    {
        *(pbBuffer + liHash.LowPart - liOffset.LowPart) ^= Hash >> 16;
    }

    liHash.QuadPart = HiWord(Hash2);
    if (liHash.QuadPart >= liOffset.QuadPart && liHash.QuadPart < liCurPos.QuadPart)
    {
        *(pbBuffer + liHash.LowPart - liOffset.LowPart) ^= Hash >> 8;
    }

    memxor(pbBuffer, Hash, BufferSize);

    return True;
}

Bool STDCALL Decrypt_Dynamic(const SXP3ExtractionInfo *pInfo, LPVoid lpExtraInfo)
{
    UInt32 SegmLength, Hash;
    LARGE_INTEGER liCurPos, liSegmSize;
    SXP3ExtractionInfo Info;
    CDynamicCodeBase *pCode;

    pCode = g_dcode;
    if (pCode == NULL)
    {
        switch ((UInt32)lpExtraInfo)
        {
        case E_FATE_HA:
            pCode = g_dcode = new CFateHA;
            break;

        case E_REAL_SISTER:
            pCode = g_dcode = new CRealSister;
            break;

        case E_NATSU_ZORA:
            pCode = g_dcode = new CNatsuZora;
            break;

        case E_TENSHIN:
            pCode = g_dcode = new CTenshin;
            break;

        default:
            return False;
        }

        if (pCode == NULL)
            return False;
    }

    Info = *pInfo;

    switch ((UInt32)lpExtraInfo)
    {
    case E_FATE_HA:
        SegmLength = (Info.FileHash & 0x143) + 0x787;
        break;

    case E_REAL_SISTER:
        SegmLength = (Info.FileHash & 0x2B2) + 0x2E6;
        break;

    case E_NATSU_ZORA:
        SegmLength = (Info.FileHash & 0x2F5) + 0x6F0;
        break;

    case E_TENSHIN:
        SegmLength = (Info.FileHash & 0x167) + 0x498;
        break;

    default:
        return False;
    }

    liSegmSize.QuadPart = SegmLength;
    liCurPos.QuadPart = Info.Offset.QuadPart + Info.BufferSize;
    if (Info.Offset.QuadPart < liSegmSize.QuadPart && liCurPos.QuadPart > liSegmSize.QuadPart)
    {
        Hash = Info.FileHash;
        SegmLength = liSegmSize.LowPart - Info.Offset.LowPart;
        DecryptInternal(Hash, Info.Offset, Info.Buffer, SegmLength);

        Hash = (Info.FileHash >> 16) ^ Info.FileHash;
        Info.Buffer = (PByte)Info.Buffer + SegmLength;
        DecryptInternal(Hash, liSegmSize, Info.Buffer, Info.BufferSize - SegmLength);
    }
    else
    {
        if (Info.Offset.QuadPart < liSegmSize.LowPart)
        {
            Hash = Info.FileHash;
        }
        else
        {
            Hash = (Info.FileHash >> 16) ^ Info.FileHash;
        }

        DecryptInternal(Hash, Info.Offset, Info.Buffer, Info.BufferSize);
    }

    return True;
}

Bool FASTCALL IsNeedCompress(SMyXP3Index *pIndex)
{
    PWChar pExtension;

    pExtension = findextw(pIndex->info.filename);
    if (pExtension == NULL)
        return False;

    if (0 ||
        !StrICompareW(pExtension, L".uci") ||
        !StrICompareW(pExtension, L".png") ||
        !StrICompareW(pExtension, L".m4a") ||
        !StrICompareW(pExtension, L".ogg") ||
        !StrICompareW(pExtension, L".avi") ||
        !StrICompareW(pExtension, L".mpg") || 
        !StrICompareW(pExtension, L".mkv") || 
        0)
        return False;

    return True;
}

Bool FASTCALL IsNeesEncrypt(SMyXP3Index *pIndex)
{
    PWChar pExtension;

    pExtension = findextw(pIndex->info.filename);
    if (pExtension == NULL)
        return False;

    if (0 ||
        !StrICompareW(pExtension, L".uca") ||
        0)
        return False;

    return True;
}

Void CALLBACK PackFiles(SPackFileInfo *pPackFileInfo, UInt32 uCount, PCWChar pszOutput, PCWChar pszFullInputPath, PCWChar pszParam, FShowStatus ShowStatus)
{
    Bool    r;
    HANDLE  hHeap, hFile, hFileXP3;
    PByte   pbIndex;
    UInt32  uBufferSize, uCompressSize;
    DWORD   dwRead;
    WChar   szPath[MAX_PATH], szBuffer[MAX_PATH * 2];
    LPVoid  lpBuffer, lpCompressBuffer, lpExtraInfo;
    LARGE_INTEGER liSize, Offset;
    SMyXP3Index *pXP3Index, *pIndex;
    SPackFileInfo *pInfo;
    SXP3DataHeader IndexHeader;
    FDecrypt Decrypt = NULL;
    INTEL_STATIC SXP3Header header = { { 0x58, 0x50, 0x33, 0x0D, 0x0A, 0x20, 0x0A, 0x1A, 0x8B, 0x67, 0x01 } };

    if (pszParam && *pszParam)
    {
        Int32 i;
        for (i = 0; i != countof(param); ++i)
            if (!StrICompareW(pszParam, param[i].param))
            {
                Decrypt = param[i].func;
                lpExtraInfo = param[i].extrainfo;
                break;
            }

            if (i == countof(param))
            {
                if (ShowStatus)
                {
                    swprintf(szBuffer, L"Invalid param: %s", pszParam);
                    ShowStatus(szBuffer, 0);
                    Sleep(1000);
                }
                return;
            }
    }

    hFileXP3 = CreateFileW(pszOutput, 
                        GENERIC_READ|GENERIC_WRITE, 
                        FILE_SHARE_READ|FILE_SHARE_WRITE, 
                        NULL, 
                        CREATE_ALWAYS, 
                        FILE_ATTRIBUTE_NORMAL, 
                        NULL);
    if (hFileXP3 == INVALID_HANDLE_VALUE)
        return;

    GetCurrentDirectoryW(countof(szPath), szPath);
    SetCurrentDirectoryW(pszFullInputPath);

    hHeap = GetProcessHeap();
    uBufferSize = 0x10000;
    uCompressSize = uBufferSize;
    lpBuffer = HeapAlloc(hHeap, 0, uBufferSize);
    lpCompressBuffer = HeapAlloc(hHeap, 0, uCompressSize);
    pXP3Index = (SMyXP3Index *)HeapAlloc(hHeap, 0, sizeof(*pXP3Index) * uCount);
    pIndex = pXP3Index;
    pInfo  = pPackFileInfo;

    WriteFile(hFileXP3, &header, sizeof(header), &dwRead, NULL);

    Offset.QuadPart = dwRead;
    for (UInt32 i = 0; i != uCount; ++i, ++pIndex, ++pInfo)
    {
        ZeroMemory(pIndex, sizeof(*pIndex));
        pIndex->file.tag = TAG4('File');
        pIndex->info.tag = TAG4('info');
        pIndex->segm.tag = TAG4('segm');
        pIndex->adlr.tag = TAG4('adlr');
        pIndex->segm.size.QuadPart = sizeof(pIndex->segm.segm);
        pIndex->adlr.size.QuadPart = sizeof(pIndex->adlr) - sizeof(pIndex->adlr.tag) - sizeof(pIndex->adlr.size);

        hFile = CreateFileW(pInfo->pFileName, 
                        GENERIC_READ, 
                        FILE_SHARE_READ, 
                        NULL, 
                        OPEN_EXISTING, 
                        FILE_ATTRIBUTE_NORMAL, 
                        NULL);
        if (hFile == INVALID_HANDLE_VALUE)
            continue;

        GetFileSizeEx(hFile, &liSize);
        if (liSize.LowPart > uBufferSize)
        {
            uBufferSize = liSize.LowPart;
            lpBuffer = HeapReAlloc(hHeap, 0, lpBuffer, uBufferSize);
        }

        r = ReadFile(hFile, lpBuffer, liSize.LowPart, &dwRead, NULL);
        CloseHandle(hFile);
        if (r == False || dwRead != liSize.LowPart)
            continue;

        pIndex->segm.segm->offset = Offset;
        pIndex->info.filename = (PWChar)pInfo->pFileName;
        pIndex->info.namelen  = StrLengthW(pInfo->pFileName);

        pIndex->file.size.QuadPart = sizeof(*pIndex) - sizeof(pIndex->file);
        pIndex->info.size.QuadPart = sizeof(pIndex->info) - sizeof(pIndex->info.tag) - sizeof(pIndex->info.size);
        pIndex->file.size.QuadPart = pIndex->file.size.QuadPart - sizeof(pIndex->info.filename) + pIndex->info.namelen * 2;
        pIndex->info.size.QuadPart = pIndex->info.size.QuadPart - sizeof(pIndex->info.filename) + pIndex->info.namelen * 2;

        pIndex->adlr.hash = adler32(1/*adler32(0, 0, 0)*/, (Bytef *)lpBuffer, dwRead);
        pIndex->segm.segm->origsize.LowPart = dwRead;
        pIndex->info.origsize.LowPart = dwRead;
        if (Decrypt)
        {
            SXP3ExtractionInfo info = { sizeof(info), { 0 }, lpBuffer, dwRead, pIndex->adlr.hash };
            Decrypt(&info, lpExtraInfo);
            pIndex->info.encrypted = 0x80000000;
        }

        if (IsNeedCompress(pIndex))
        {
            if (liSize.LowPart > uCompressSize)
            {
                uCompressSize = liSize.LowPart;
                lpCompressBuffer = HeapReAlloc(hHeap, 0, lpCompressBuffer, uCompressSize);
            }
            if (liSize.LowPart * 2 > uBufferSize)
            {
                uBufferSize = liSize.LowPart * 2;
                lpBuffer = HeapReAlloc(hHeap, 0, lpBuffer, uBufferSize);
            }

            pIndex->segm.segm->bZlib = 1;
            memcpy(lpCompressBuffer, lpBuffer, liSize.LowPart);
            dwRead = uBufferSize;
            compress2((PByte)lpBuffer, &dwRead, (PByte)lpCompressBuffer, liSize.LowPart, Z_BEST_COMPRESSION);
        }

        pIndex->segm.segm->compsize.LowPart = dwRead;
        pIndex->info.compsize.LowPart = dwRead;
        Offset.QuadPart += dwRead;

        WriteFile(hFileXP3, lpBuffer, dwRead, &dwRead, NULL);
        swprintf(szBuffer, L"%u / %u: %s", i + 1, uCount, pInfo->pFileName);
        if (!ShowStatus(szBuffer, (i + 1) * 100 / uCount))
            break;
    }

    uCount = pIndex - pXP3Index;
    header.IndexOffset = Offset;

    // generate index, calculate index size first
    liSize.LowPart = 0;
    pIndex = pXP3Index;
    for (UInt32 i = 0; i != uCount; ++i, ++pIndex)
    {
        liSize.LowPart += pIndex->file.size.LowPart + sizeof(pIndex->file);
    }

    if (liSize.LowPart > uCompressSize)
    {
        uCompressSize = liSize.LowPart;
        lpCompressBuffer = HeapReAlloc(hHeap, 0, lpCompressBuffer, uCompressSize);
    }
    if (liSize.LowPart * 2 > uBufferSize)
    {
        uBufferSize = liSize.LowPart * 2;
        lpBuffer = HeapReAlloc(hHeap, 0, lpBuffer, uBufferSize);
    }

    // generate index to lpCompressBuffer
    pIndex = pXP3Index;
    pbIndex = (PByte)lpCompressBuffer;
    for (UInt32 i = 0; i != uCount; ++i, ++pIndex)
    {
        UInt32 n = (PByte)&pIndex->info.filename - (PByte)pIndex;
        memcpy(pbIndex, &pIndex->file, n);
        pbIndex += n;
        n = pIndex->info.namelen * 2;
        memcpy(pbIndex, pIndex->info.filename, n);
        pbIndex += n;
        n = (PByte)&pIndex->adlr.hash - (PByte)&pIndex->segm + 4;
        memcpy(pbIndex, &pIndex->segm, n);
        pbIndex += n;
    }

    IndexHeader.bZlib = 1;
    IndexHeader.DecompSize.QuadPart = liSize.LowPart;
    IndexHeader.CompSize.LowPart = uBufferSize;
    uBufferSize = liSize.LowPart;
    compress((PByte)lpBuffer, &IndexHeader.CompSize.LowPart, (PByte)lpCompressBuffer, uBufferSize);
    IndexHeader.CompSize.HighPart = 0;

    WriteFile(hFileXP3, &IndexHeader, sizeof(IndexHeader), &dwRead, NULL);
    WriteFile(hFileXP3, lpBuffer, IndexHeader.CompSize.LowPart, &dwRead, NULL);
    SetFilePointer(hFileXP3, 0, NULL, FILE_BEGIN);
    WriteFile(hFileXP3, &header, sizeof(header), &dwRead, NULL);

    CloseHandle(hFileXP3);

    HeapFree(hHeap, 0, lpBuffer);
    HeapFree(hHeap, 0, lpCompressBuffer);
    HeapFree(hHeap, 0, pXP3Index);

    SetCurrentDirectoryW(szPath);

    ReleaseGlobalData();
}

Void ReleaseGlobalData()
{
    safe_delete(g_dcode);
}
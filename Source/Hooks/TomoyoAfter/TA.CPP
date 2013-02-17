//#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/MERGE:.text=.Amano /SECTION:.Amano,EWR")
#pragma comment(linker, "/MERGE:.rdata=.Amano")
#pragma comment(lib, "VERSION.lib")

#include "ta.h"
#include "BMP2G00/BMP2G00.h"

#define USE_CACHE
#define Voice 0
#define Image 1
#define MaxWasteCount 5
#define szCGExtension    ".g00"
#define szVoiceExtension ".wav"
static const HANDLE hMyImageHandle = (HANDLE)-3;
static const HANDLE hMyAudioHandle = (HANDLE)-2;
static const HANDLE hMyFindFile    = (HANDLE)0;

HANDLE ghHeap;
PBYTE  gpbBuffer;
DWORD  gdwMaxBufferSize;

TMyHandle MyHandle[5];
const DWORD dwMinAudioHandle = (DWORD)INVALID_HANDLE_VALUE - countof(MyHandle);

#ifdef USE_CACHE

const DWORD dwMaxCacheCount = 81;
DWORD gdwUCIReadCount, gdwCacheHitCount, gdwCacheCount; //, gdwHashConflictCount;
CHAR  gszVoiceName[MAX_PATH];
TCacheIndex CacheIndex[dwMaxCacheCount];

#endif

HANDLE WINAPI MyFindFirstFileA(LPSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
    DWORD dwLength, dwVoiceIndex, dwExtension;
    CHAR  szFile[MAX_PATH];

    if (GetFileAttributesA(lpFileName) == -1 && (dwLength = StrLengthA(lpFileName)) > 4)
    {
        dwExtension = *(LPDWORD)(lpFileName + dwLength - 3);
        if ((dwExtension & 0xFFDFDFDF) == TAG3('WAV'))
        {
            lstrcpyA(szFile, lpFileName);
            *(LPDWORD)(szFile + dwLength - 3) = 'acu';
            if (GetFileAttributesA(szFile) != -1)
            {
                lpFindFileData->dwFileAttributes = 0;
                return hMyFindFile;
            }
            else if ((dwVoiceIndex = GetVoiceIndex(szFile)) != -1)
            {
                BOOL bResult;
                HANDLE hFile;
                DWORD dwIndexCount, dwRead, dwOffset[2];

                hFile = CreateFileA(szFile,
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
                if (hFile != INVALID_HANDLE_VALUE)
                {
                    SetFilePointer(hFile, -4, 0, FILE_END);
                    bResult = ReadFile(hFile, &dwIndexCount, 4, &dwRead, NULL);
                    if (bResult == True && dwRead == 4 && dwVoiceIndex <= dwIndexCount)
                    {
                        SetFilePointer(hFile, -(4 + 4 + 4 * (int)dwVoiceIndex), 0, FILE_END);
                        bResult = ReadFile(hFile, dwOffset, 8, &dwRead, NULL);
                        if (bResult == True && dwRead == 8 && dwOffset[0] - dwOffset[1] != 0)
                        {
                            CloseHandle(hFile);
                            lpFindFileData->dwFileAttributes = 0;
                            return hMyFindFile;
                        }
                    }
                    CloseHandle(hFile);
                }
            }
        }
        else if ((dwExtension & 0xFFFFFFDF) == TAG3('G00'))
        {
            lstrcpyA(szFile, lpFileName);
            *(LPDWORD)(szFile + dwLength - 3) = TAG3('u00');
            if (GetFileAttributesA(szFile) != -1)
            {
                lpFindFileData->dwFileAttributes = 0;
                return hMyFindFile;
            }
            *(LPDWORD)(szFile + dwLength - 3) = TAG3('uci');
            if (GetFileAttributesA(szFile) != -1)
            {
                lpFindFileData->dwFileAttributes = 0;
                return hMyFindFile;
            }
        }
    }

    return FindFirstFileA(lpFileName, lpFindFileData);
}

BOOL WINAPI MyFindClose(HANDLE hFindFile)
{
    return hFindFile == hMyFindFile ? True : FindClose(hFindFile);
}

DWORD WINAPI GetVoiceIndex(IN OUT LPSTR lpSourceFile)
{
    DWORD dwLength, dwLength2, dwVoiceIndex;
    CHAR  szVoicePak[MAX_PATH];
    // J:\KEY\智代アフター\KOE\0000\Z000000002.uca

    dwLength = StrLengthA(lpSourceFile);
    if (dwLength < 15)
        return -1;

    dwLength -= 15;
    if (lpSourceFile[dwLength] != '\\' ||
        (lpSourceFile[dwLength + 1] & 0xDF) != 'Z' ||
        lpSourceFile[dwLength - 5] != '\\')
        return -1;

    lstrcpyA(szVoicePak, lpSourceFile);

    szVoicePak[dwLength] = 0;
    szVoicePak[dwLength - 5] = 0;

    dwLength2 = wsprintfA(lpSourceFile, "%s\\z%s.", szVoicePak, &szVoicePak[dwLength - 5] + 1);

    *(LPDWORD)&lpSourceFile[dwLength2] = TAG3('nwk');
    if (GetFileAttributesA(lpSourceFile) != -1)
        return -1;

    *(LPDWORD)&lpSourceFile[dwLength2] = TAG3('ovk');
    if (GetFileAttributesA(lpSourceFile) != -1)
        return -1;

    *(LPDWORD)&lpSourceFile[dwLength2] = TAG3('koe');
    if (GetFileAttributesA(lpSourceFile) != -1)
        return -1;

    *(LPDWORD)&lpSourceFile[dwLength2] = TAG3('pak');

    dwLength += 6;
    dwVoiceIndex = (szVoicePak[dwLength] - '0') * 10 + (szVoicePak[dwLength + 1] - '0');
    dwVoiceIndex = dwVoiceIndex * 10 + szVoicePak[dwLength + 2] - '0';
    dwVoiceIndex = dwVoiceIndex * 10 + szVoicePak[dwLength + 3] - '0';
    dwVoiceIndex = dwVoiceIndex * 10 + szVoicePak[dwLength + 4] - '0';

    return dwVoiceIndex + 1;    // Z0000 00002.uca -> 03
}

ForceInline DWORD WINAPI FindInvalidHanle()
{
    DWORD dwIndex;

    for (dwIndex = 0; dwIndex != countof(MyHandle); ++dwIndex)
    {
        if (MyHandle[dwIndex].dwSize == 0)
            break;
    }

    return dwIndex == countof(MyHandle) ? -1 : dwIndex;
}

ForceInline DWORD WINAPI GetIndexFromHandle(HANDLE hFile)
{
    return (DWORD)hFile < dwMinAudioHandle ? -1 : (DWORD)INVALID_HANDLE_VALUE - (DWORD)hFile - 1;
}

HANDLE WINAPI CreateAudio(LPCSTR lpFileName, DWORD dwLength)
{
    BOOL   bResult;
    DWORD  dwRead, dwWaveSize, dwHandleIndex;
    PBYTE  pbWave;
    HANDLE hFile, hAudioHandle, hHeap;
    CHAR   szFile[MAX_PATH];

    PBYTE pbBuffer;
    LPSTR lpszFile;
    TMyHandle *pHandle;
    SWaveHeader *h;

#ifdef USE_CACHE
    lpszFile = gszVoiceName;
#else
    lpszFile = szFile;
#endif

    dwHandleIndex = FindInvalidHanle();
    if (dwHandleIndex == -1)
    {
        return INVALID_HANDLE_VALUE;
    }

    h = NULL;
    pbWave = NULL;
    hAudioHandle = INVALID_HANDLE_VALUE;

    do
    {
        lstrcpyA(lpszFile, lpFileName);
        *(LPDWORD)(lpszFile + dwLength - 3) = TAG3('uca');
        hFile = CreateFileA(lpszFile,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (hFile != INVALID_HANDLE_VALUE)
        {
            dwLength = GetFileSize(hFile, NULL);
        }
        else
        {
            DWORD dwVoiceIndex;
            DWORD dwOffset[2];

            if (lpszFile != szFile)
            {
                lstrcpyA(szFile, lpszFile);
            }
            dwVoiceIndex = GetVoiceIndex(szFile);
            if (dwVoiceIndex == -1)
                break;

            hFile = CreateFileA(szFile,
                GENERIC_READ,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
            if (hFile == INVALID_HANDLE_VALUE)
                break;

            SetFilePointer(hFile, -(4 + 4 + 4 * (int)dwVoiceIndex), 0, FILE_END);
            bResult = ReadFile(hFile, dwOffset, 8, &dwRead, NULL);
            dwLength = dwOffset[0] - dwOffset[1];
            if (bResult == False || dwRead != 8 || dwLength == 0)
            {
                break;
            }

            SetFilePointer(hFile, dwOffset[1], 0, FILE_BEGIN);
        }

        hHeap = ghHeap;
        pbBuffer = gpbBuffer;
        if (dwLength > gdwMaxBufferSize)
        {
            pbBuffer = (PBYTE)HeapReAlloc(hHeap, 0, gpbBuffer, dwLength);
            if (pbBuffer == NULL)
                break;

            gdwMaxBufferSize = dwLength;
            gpbBuffer = pbBuffer;
        }

        bResult = ReadFile(hFile, pbBuffer, dwLength, &dwRead, NULL);
        if (bResult == False || dwRead != dwLength)
            break;
/*
        h = (TWaveHeader *)gpbBuffer;
        if (h->RIFF == 'FFIR' && h->WAVE == 'EVAW' && h->fmt == ' tmf')
        {
            pbWave = (PBYTE)h;
        }
        else
*/      {
            dwWaveSize = -1;
            if (UCADecode2(gpbBuffer, dwLength, (void **)&pbWave, (int *)&dwWaveSize, 48000) < 0)
                break;
        }

        pHandle = &MyHandle[dwHandleIndex];
        pbBuffer = pHandle->pbBuffer;
        if (pbBuffer == NULL)
        {
            pbBuffer = (PBYTE)HeapAlloc(hHeap, 0, dwWaveSize);
            if (pbBuffer == NULL)
                break;

            pHandle->dwBufferSize = dwWaveSize;
            pHandle->pbBuffer = pbBuffer;
        }
        else if (dwWaveSize > pHandle->dwBufferSize)
        {
            pbBuffer = (PBYTE)HeapReAlloc(hHeap, 0, pHandle->pbBuffer, dwWaveSize);
            if (pbBuffer == NULL)
                break;

            pHandle->dwBufferSize = dwWaveSize;
            pHandle->pbBuffer = pbBuffer;
        }

        hAudioHandle = (HANDLE)((DWORD)INVALID_HANDLE_VALUE - dwHandleIndex - 1);
        pHandle->dwOffset = 0;
        pHandle->dwSize = dwWaveSize;
        memcpy(pbBuffer, pbWave, dwWaveSize);

    } while (0);

    if (pbWave)
        UCAFree(pbWave);

    if (hFile != INVALID_HANDLE_VALUE)
        CloseHandle(hFile);

    return hAudioHandle;
}

HANDLE WINAPI CreateImage(LPCSTR lpFileName, DWORD dwLength)
{
    BOOL   bResult, bG00Format0;
    DWORD  dwRead, dwHandleIndex;
    PBYTE  pbBitmap, pbOutBuffer;
    HANDLE hFile, hImageHandle, hHeap;
    CHAR   szFile[MAX_PATH];
    PBYTE  pbBuffer;
    TMyHandle *pHandle;

    dwHandleIndex = FindInvalidHanle();
    if (dwHandleIndex == -1)
    {
        return INVALID_HANDLE_VALUE;
    }

    hHeap = ghHeap;
    pbBitmap     = NULL;
    pbOutBuffer  = NULL;
    hImageHandle = INVALID_HANDLE_VALUE;

    do
    {
#ifdef USE_CACHE
        DWORD  dwHash, dwIndex;
        TCacheIndex *pCache;

        dwHash = HashAPI(lpFileName);
        dwIndex = dwHash % dwMaxCacheCount;
        pCache = &CacheIndex[dwIndex];
        if (pCache->pbBuffer)
        {
            if (!StrICompareA(lpFileName, pCache->szName))
            {
                pHandle = &MyHandle[dwHandleIndex];
                pbBuffer = pHandle->pbBuffer;
                if (pbBuffer == NULL)
                {
                    pbBuffer = (PBYTE)HeapAlloc(hHeap, 0, pCache->dwSize);
                    if (pbBuffer == NULL)
                        break;

                    pHandle->dwBufferSize = pCache->dwSize;
                    pHandle->pbBuffer = pbBuffer;
                }
                else if (pCache->dwSize > pHandle->dwBufferSize)
                {
                    pbBuffer = (PBYTE)HeapReAlloc(hHeap, 0, pHandle->pbBuffer, pCache->dwSize);
                    if (pbBuffer == NULL)
                        break;

                    pHandle->dwBufferSize = pCache->dwSize;
                    pHandle->pbBuffer = pbBuffer;
                }

                hImageHandle = (HANDLE)((DWORD)INVALID_HANDLE_VALUE - dwHandleIndex - 1);
                dwLength = pCache->dwSize;
                pHandle->dwOffset = 0;
                pHandle->dwSize = dwLength;
                memcpy(pbBuffer, pCache->pbBuffer, dwLength);
                if (dwLength * 2 < pCache->dwMaxSize && ++pCache->dwWaste == MaxWasteCount)
                {
                    PBYTE pbReAlloc;
                    pCache->dwWaste = 0;
                    dwLength *= 2;
                    pbReAlloc = (PBYTE)HeapReAlloc(hHeap, 0, pCache->pbBuffer, dwLength);
                    if (pbReAlloc)
                    {
                        pCache->pbBuffer = pbReAlloc;
                        pCache->dwMaxSize = dwLength;
                    }
                }

                ++gdwCacheHitCount;
                ++gdwUCIReadCount;

//                pCache->dwConflict ? --pCache->dwConflict : 0;

                return hImageHandle;
            }
//            ++gdwHashConflictCount;
        }
#endif
        memcpy(szFile, lpFileName, dwLength + 1);
        *(LPDWORD)(szFile + dwLength - 3) = TAG3('u00');
        if (GetFileAttributesA(szFile) == -1)
        {
            *(LPDWORD)(szFile + dwLength - 3) = TAG3('uci');
            bG00Format0 = True;
        }
        else
        {
            bG00Format0 = False;
        }

        hFile = CreateFileA(szFile,
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
        if (hFile == INVALID_HANDLE_VALUE)
            break;

        dwLength = GetFileSize(hFile, NULL);
        pbBuffer = gpbBuffer;
        if (dwLength > gdwMaxBufferSize)
        {
            pbBuffer = (PBYTE)HeapReAlloc(hHeap, 0, pbBuffer, dwLength + 0x100);
            if (pbBuffer == NULL)
            {
                CloseHandle(hFile);
                break;
            }
            gdwMaxBufferSize = dwLength + 0x100;
            gpbBuffer = pbBuffer;
        }

        bResult = ReadFile(hFile, pbBuffer, dwLength, &dwRead, NULL);
        CloseHandle(hFile);
        if (bResult == False || dwRead != dwLength)
            break;

        Int32 stride, h, w, b;
        PBYTE pbUCI, pbOut, pbEnd;
        DWORD dwBlockCount, dwBlocks, dwTailSize;
        TG00Header_0 h0;
        TG00Header_2 *pHeader;
        TBlockHeader *pBlockHeader;
        TMyBlockDataHeader *pBlockData;

        if (bG00Format0)
        {
            if (UCIDecode(pbBuffer, dwLength, (LPVOID *)&pbBitmap, &stride, &w, &h, &b) < 0)
                break;

            h0.id = 0;
            h0.usWidth  = w;
            h0.usHeight = h;
            h0.uiUncompressedSize = w * h * 4;
//            stride = w * b / 8 + (b == 24 ? w & 3 : 1);
            dwLength = stride * h;
            h0.uiCompressedSize = dwLength + sizeof(h0) - 5;

            dwBlocks = dwLength / 24;
            dwTailSize = dwLength % 24;
            h0.uiCompressedSize += dwBlocks + (dwTailSize != 0);

            dwLength = h0.uiCompressedSize + 5;
        }
        else
        {
            pHeader = (TG00Header_2 *)pbBuffer;
            if (pHeader->id != 2)
                break;

            pbEnd = pbBuffer + dwLength;
            pBlockData = (TMyBlockDataHeader *)((PBYTE)pHeader->Region + pHeader->uiRegionCount * sizeof(TRegion));
            pbUCI = NULL;
            dwBlockCount = 0;
            dwLength = 12;  // uiCompressedSize, uiUncompressedSize, uiBlockCount
            for (DWORD j = 0; j != pHeader->uiRegionCount; ++j)
            {
                if ((*(LPDWORD)&pBlockData[j] & 0x00FFFFFF) != TAG3('UCI'))
                {
                    dwLength += sizeof(TBlockDataHeader) + sizeof(TPartDataHeader) + sizeof(TBlockIndex);
                    dwLength += pBlockData[j].uiBlockWidth * pBlockData[j].uiBlockHeight * 4;
                    ++dwBlockCount;
                }
                else
                {
                    dwLength += sizeof(TBlockIndex) * (pHeader->uiRegionCount - j);
                    break;
                }
            }

            if (dwBlockCount == 0)
                break;

            dwLength += dwLength / 8 + ((PBYTE)pBlockData - pbBuffer);    // estimate final size

            pbOutBuffer = (PBYTE)HeapAlloc(hHeap, 0, dwLength);
            if (pbOutBuffer == NULL)
                break;

            pbUCI = (PBYTE)&pBlockData[dwBlockCount];
            pbOut = pbOutBuffer;
            memcpy(pbOut, pbBuffer, (PBYTE)pBlockData - pbBuffer);   // header & regions
            pbOut += (PBYTE)pBlockData - pbBuffer;      // point to comp_size & uncomp_size

            pBlockHeader = (TBlockHeader *)pbOut;
            pBlockHeader->uiBlockCount = pHeader->uiRegionCount;
            pBlockHeader->uiUncompressedSize  = sizeof(TBlockIndex) * pBlockHeader->uiBlockCount + 4; // uiBlockCount
            for (DWORD j = dwBlockCount; j != pBlockHeader->uiBlockCount; ++j)
            {
                pBlockHeader->BlockIndex[j].uiOffset = 0;
                pBlockHeader->BlockIndex[j].uiSize   = 0;
            }

            pbOut += sizeof(*pBlockHeader->BlockIndex) * pBlockHeader->uiBlockCount + 12;   // uiBlockCount + 2 sizes
            for (DWORD j = 0; j != dwBlockCount; ++j)
            {
                PBYTE pbSrc;
                TPartDataHeader  *pPart;
                TBlockDataHeader *pBlock;

                if (pbUCI >= pbEnd)
                {
                    pBlockHeader->BlockIndex[j].uiOffset = 0;
                    pBlockHeader->BlockIndex[j].uiSize   = 0;
                    continue;
                }
                switch (h = *(LPDWORD)pbUCI)
                {
                    case TAG4('UCI3'): h = 1; break;
                    case TAG4('UCI4'): h = 2; break;
                    case TAG4('UCIT'): h = 3; break;
                    case TAG4('UCIQ'): h = 4; break;
                    case -1:
                        pBlockHeader->BlockIndex[j].uiOffset = 0;
                        pBlockHeader->BlockIndex[j].uiSize   = 0;
                        pbUCI += 4;
                        continue;

                    default:
                        pBlockHeader->BlockIndex[j].uiOffset = pBlockHeader->BlockIndex[h].uiOffset;
                        pBlockHeader->BlockIndex[j].uiSize   = pBlockHeader->BlockIndex[h].uiSize;
                        pbUCI += 4;
                        continue;
                }
                pbSrc = pbUCI;
                pbUCI += 0xC;
                while (h--)
                    pbUCI += *(LPDWORD)pbUCI + 4;

                if (UCIDecode(pbSrc, pbUCI - pbSrc, (LPVOID*)&pbBitmap, &stride, &w, &h, &b) < 0)
                {
                    pBlockHeader->BlockIndex[j].uiOffset = 0;
                    pBlockHeader->BlockIndex[j].uiSize   = 0;
                    continue;
                }

                pBlock = (TBlockDataHeader *)pbOut;
                pBlock->uiUnknownAndPartCount = 0x010001;
                memcpy(&pBlock->uiBlockX, &pBlockData[j], sizeof(*pBlockData));
                memset(pBlock->zero, 0, sizeof(pBlock->zero));

                pbOut += sizeof(*pBlock);
                pPart = (TPartDataHeader *)pbOut;
                pPart->usPartX      = (WORD)pBlockData[j].uiBlockX;
                pPart->usPartY      = (WORD)pBlockData[j].uiBlockY;
                pPart->usTrans      = 1;
                pPart->usPartWidth  = (WORD)pBlockData[j].uiBlockWidth;
                pPart->usPartHeight = (WORD)pBlockData[j].uiBlockHeight;
                pPart->unknown      = 0;
                memset(pPart->zero, 0, sizeof(pPart->zero));

                pbOut += sizeof(*pPart);

                for (DWORD height = 0; height != h; ++height)
                {
                    memcpy(pbOut, pbBitmap + stride * height, stride);
                    pbOut += stride;
                }
                pBlockHeader->BlockIndex[j].uiOffset = (PBYTE)pBlock - (PBYTE)pBlockHeader - 8;
                pBlockHeader->BlockIndex[j].uiSize = pbOut - (PBYTE)pBlock;
                pBlockHeader->uiUncompressedSize += pBlockHeader->BlockIndex[j].uiSize;

                UCIFree(pbBitmap);
            }

            pbBitmap = NULL;
            dwLength = pbOut - (PBYTE)pBlockHeader;
            dwLength += dwLength / 8;
            pBlockHeader->uiCompressedSize = dwLength;
            dwLength += (PBYTE)pBlockHeader - pbOutBuffer;
        }

        pHandle = &MyHandle[dwHandleIndex];
        pbBuffer = pHandle->pbBuffer;
        if (pbBuffer == NULL)
        {
            pbBuffer = (PBYTE)HeapAlloc(hHeap, 0, dwLength);
            if (pbBuffer == NULL)
                break;

            pHandle->dwBufferSize = dwLength;
            pHandle->pbBuffer = pbBuffer;
        }
        else if (dwLength > pHandle->dwBufferSize)
        {
            pbBuffer = (PBYTE)HeapReAlloc(hHeap, 0, pHandle->pbBuffer, dwLength);
            if (pbBuffer == NULL)
                break;

            pHandle->dwBufferSize = dwLength;
            pHandle->pbBuffer = pbBuffer;
        }

        hImageHandle = (HANDLE)((DWORD)INVALID_HANDLE_VALUE - dwHandleIndex - 1);
        pHandle->dwOffset = 0;

        if (bG00Format0)
        {
            PBYTE pSrc;

            *(TG00Header_0 *)pbBuffer = h0;
            pSrc  = pbBitmap;
            pbBuffer += sizeof(h0);
            while (dwBlocks--)
            {
                *pbBuffer++ = -1;
                memcpy(pbBuffer, pSrc, 24);
                pSrc  += 24;
                pbBuffer += 24;
            }
            if (dwTailSize)
            {
                *pbBuffer++ = -1;
                memcpy(pbBuffer, pSrc, dwTailSize);
                pbBuffer += dwTailSize;
            }
        }
        else
        {
            memcpy(pbBuffer, pbOutBuffer, (PBYTE)pBlockHeader - pbOutBuffer);
            pbBuffer += (PBYTE)pBlockHeader - pbOutBuffer;

            dwLength = pbOut - (PBYTE)pBlockHeader;
            pbOut = (PBYTE)pBlockHeader;
            dwBlockCount = dwLength / 8;
            while (dwBlockCount--)
            {
                memcpy(pbBuffer, pbOut, 8);
                pbBuffer[8] = -1;
                pbBuffer += 9;
                pbOut += 8;
            }
            if (dwBlockCount = dwLength % 8)
            {
                memcpy(pbBuffer, pbOut, dwBlockCount);
                pbBuffer += dwBlockCount;
            }
        }

        pHandle->dwSize = pbBuffer - pHandle->pbBuffer;

#ifdef USE_CACHE

        ++gdwUCIReadCount;
        dwLength = pHandle->dwSize;
/*
        if (dwLength >= 0x1400000)
            break;

        if (0 && pCache->pbBuffer && pCache->dwConflict != 3)
        {
            ++pCache->dwConflict;
        }
        else
*/
        {
            lstrcpyA(pCache->szName, lpFileName);
            if (pCache->pbBuffer == NULL)
            {
                ++gdwCacheCount;
                pCache->dwMaxSize = dwLength;
                pCache->pbBuffer = (PBYTE)HeapAlloc(hHeap, 0, dwLength);
            }
            else if (dwLength > pCache->dwMaxSize)
            {
                PBYTE pbReAlloc;
                pbReAlloc = (PBYTE)HeapReAlloc(hHeap, 0, pCache->pbBuffer, dwLength);
                if (pbReAlloc == NULL)
                {
                    pCache->szName[0] = 0;
                }
                else
                {
                    pCache->dwMaxSize = dwLength;
                    pCache->pbBuffer  = pbReAlloc;
                }
            }

            if (pCache->szName[0])
            {
//                pCache->dwConflict = 0;
                pCache->dwSize = dwLength;
                memcpy(pCache->pbBuffer, pHandle->pbBuffer, dwLength);
            }

            if (dwLength * 2 < pCache->dwMaxSize && ++pCache->dwWaste == MaxWasteCount)
            {
                PBYTE pbReAlloc;

                pCache->dwWaste = 0;
                dwLength *= 2;
                pbReAlloc = (PBYTE)HeapReAlloc(hHeap, 0, pCache->pbBuffer, dwLength);
                if (pbReAlloc)
                {
                    pCache->pbBuffer = pbReAlloc;
                    pCache->dwMaxSize = dwLength;
                }
            }
        }
#endif

    } while (0);

    if (pbBitmap)
        UCIFree(pbBitmap);
    if (pbOutBuffer)
        HeapFree(hHeap, 0, pbOutBuffer);

    return hImageHandle;
}

HANDLE WINAPI MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    DWORD dwLength;

    if (GetFileAttributesA(lpFileName) == -1 && (dwLength = StrLengthA(lpFileName)) > 4)
    {
        HANDLE hFile;
        DWORD  dwExtension;

        if (lpFileName[dwLength - 4] == '.')
        {
            dwExtension = *(LPDWORD)(lpFileName + dwLength - 3);
            if ((dwExtension & 0xFFFFFFDF) == TAG3('G00'))
            {
                hFile = CreateImage(lpFileName, dwLength);
                if (hFile != INVALID_HANDLE_VALUE)
                    return hFile;
            }
            else if ((dwExtension & 0xFFDFDFDF) == TAG3('WAV'))
            {
                hFile = CreateAudio(lpFileName, dwLength);
                if (hFile != INVALID_HANDLE_VALUE)
                    return hFile;
            }
        }
    }

    return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

DWORD WINAPI MySetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod)
{
    DWORD dwIndex = GetIndexFromHandle(hFile);

    if (dwIndex != -1)
    {
        TMyHandle *pHandle;

        pHandle = &MyHandle[dwIndex];

        switch (dwMoveMethod)
        {
        case FILE_BEGIN:
            pHandle->dwOffset = lDistanceToMove;
            break;

        case FILE_CURRENT:
            pHandle->dwOffset += lDistanceToMove;
            break;

        case FILE_END:
            pHandle->dwOffset = pHandle->dwSize + lDistanceToMove;
        }

        return pHandle->dwOffset;
    }

    return SetFilePointer(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
}

BOOL WINAPI MyReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
{
    DWORD dwIndex = GetIndexFromHandle(hFile);

    if (dwIndex != -1)
    {
        TMyHandle *pHandle;

        pHandle = &MyHandle[dwIndex];
        memcpy(lpBuffer, pHandle->pbBuffer + pHandle->dwOffset, nNumberOfBytesToRead);
        pHandle->dwOffset += nNumberOfBytesToRead;
        if (lpNumberOfBytesRead)
        {
            *lpNumberOfBytesRead = nNumberOfBytesToRead;
        }

        return True;
    }

    return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

DWORD WINAPI MyGetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh)
{
    DWORD dwIndex = GetIndexFromHandle(hFile);

    if (dwIndex != -1)
    {
        if (lpFileSizeHigh)
        {
            *lpFileSizeHigh = 0;
        }

        return MyHandle[dwIndex].dwSize;
    }

    return GetFileSize(hFile, lpFileSizeHigh);
}

BOOL WINAPI MyCloseHandle(HANDLE hObject)
{
    DWORD dwIndex = GetIndexFromHandle(hObject);

    if (dwIndex != -1)
    {
        TMyHandle *pHandle;

        pHandle = &MyHandle[dwIndex];
        pHandle->dwOffset = 0;
        pHandle->dwSize   = 0;
        if (pHandle->dwBufferSize >= pHandle->dwSize * 2 && ++pHandle->dwWaste == MaxWasteCount)
        {
            HeapFree(ghHeap, 0, pHandle->pbBuffer);
            pHandle->dwWaste = 0;
            pHandle->pbBuffer = 0;
            pHandle->dwBufferSize = 0;
        }
        return True;
    }

    return CloseHandle(hObject);
}

BOOL WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    static Bool bFastSkip = False;
    BOOL bResult = PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);

    if (bResult == False && bFastSkip == False)
    {
        DWORD dwTickCount;
        static DWORD dwLastTickCount, dwCount;

        dwTickCount = GetTickCount();
        if (dwTickCount - dwLastTickCount < 10 && dwCount-- == 0)
        {
            dwCount = 4;
            Sleep(1);
        }
        dwLastTickCount = dwTickCount;
    }
    else
    {
        switch (lpMsg->message)
        {
            case WM_KEYDOWN:
                switch (lpMsg->wParam)
                {
                    case VK_CONTROL:
                        bFastSkip = True;
                        break;
                }
                break;

            case WM_KEYUP:
                switch (lpMsg->wParam)
                {
                    case VK_CONTROL:
                        bFastSkip = False;
                        break;
                }

            default:
                if (lpMsg->hwnd != GetForegroundWindow())
                {
                    Sleep(10);
                    bFastSkip = False;
                }
        }
    }

    return bResult;
}

BOOL WINAPI MyGetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
    BOOL bResult = GetMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);

    if (bResult <= 0)
    {
        HANDLE hHeap = ghHeap;
/*
        if (gpbBuffer) HeapFree(hHeap, 0, gpbBuffer);

        for (UInt32 i = 0; i != countof(MyHandle); ++i)
        {
            PBYTE pbBuffer = MyHandle[i].pbBuffer;
            if (pbBuffer)
                HeapFree(hHeap, 0, pbBuffer);
        }
*/
        HeapDestroy(hHeap);

#ifdef USE_CACHE1
        for (UInt32 i = 0; i != dwMaxCacheCount; ++i)
        {
            if (CacheIndex[i].pbBuffer)
            {
                HeapFree(hHeap, 0, CacheIndex[i].pbBuffer);
            }
        }
#endif
    }
    else if(GetAsyncKeyState(VK_SHIFT) >= 0)
    {
        switch (lpMsg->message)
        {
        case WM_KEYDOWN:
            switch (lpMsg->wParam)
            {
#ifdef USE_CACHE
            case VK_DELETE:
                if (MessageBoxA(lpMsg->hwnd, "确定要清空所有CG缓存吗?", NULL, MB_OKCANCEL|MB_ICONASTERISK) == IDOK)
                {
                    HANDLE hHeap = ghHeap;
                    for (UInt32 i = 0; i != dwMaxCacheCount; ++i)
                    {
                        if (CacheIndex[i].pbBuffer)
                        {
                            HeapFree(hHeap, 0, CacheIndex[i].pbBuffer);
                            CacheIndex[i].pbBuffer = NULL;
                        }
                    }

                    HeapCompact(hHeap, 0);

                    gdwCacheCount = 0;
                    gdwCacheHitCount = 0;
                    gdwUCIReadCount = 0;
                }
                break;

            case VK_HOME:
                {
                    WCHAR szBuffer[200 + MAX_PATH];
                    DWORD dwCacheSize;

                    dwCacheSize = 0;
                    for (int i = 0; i != dwMaxCacheCount; ++i)
                    {
                        if (CacheIndex[i].pbBuffer)
                            dwCacheSize += CacheIndex[i].dwMaxSize;
                    }

                    dwCacheSize = wsprintfW(
                                      szBuffer,
                                      L"Cache当前数: %u / %u\n"
                                      L"UCI读取次数: %u\n"
                                      L"Cache命中数: %u\n"
                                      L"Cache命中率: %u%%\n"
                                      L"Cache总大小: %u MB\n"
                                      L"\n"
                                      L"语音文件名:\n",
                                      gdwCacheCount, dwMaxCacheCount,
                                      gdwUCIReadCount,
                                      gdwCacheHitCount,
                                      gdwUCIReadCount ? gdwCacheHitCount * 100 / gdwUCIReadCount : 0,
                                      dwCacheSize / 1024 / 1024);
                    MultiByteToWideChar(CP_ACP, 0, gszVoiceName, -1, szBuffer + dwCacheSize, MAX_PATH);
                    MessageBoxW(lpMsg->hwnd, szBuffer, NULL, 64);
                }
                break;
#endif
            }
            break;
        }
    }

    return bResult;
}

HWND WINAPI MyCreateWindowExA(IN DWORD dwExStyle, IN LPCSTR lpClassName, IN LPCSTR lpWindowName, IN DWORD dwStyle, IN int X, IN int Y, IN int nWidth, IN int nHeight, IN HWND hWndParent, IN HMENU hMenu, IN HINSTANCE hInstance, IN LPVOID lpParam)
{
    HWND hWnd;

    hWnd = CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle|0x50000, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    return hWnd;
}

FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    static HMODULE hModuleKernel32;

    if (hModuleKernel32 == NULL)
    {
        HANDLE hHeap;

        hHeap = HeapCreate(0, 0, 0);
        ghHeap = hHeap;
        hModuleKernel32 = GetKernel32Handle();
        gdwMaxBufferSize = 0x10000;
        gpbBuffer = (PBYTE)HeapAlloc(hHeap, 0, gdwMaxBufferSize);
        DisableThreadLibraryCalls((HMODULE)&__ImageBase);
    }

    if ((int)lpProcName > 0xFFFF)
    {
        switch (HashAPI(lpProcName))
        {
            case 0xBC87B0BD: return (FARPROC)MyFindFirstFileA;
            case 0xF02590AF: return (FARPROC)MyFindClose;
#if !defined(LBEX_CN)
            case 0xFFADBAB0: return (FARPROC)MyPeekMessageA;
#endif
            case 0xFF85A538: return (FARPROC)MyGetMessageA;
            case 0xB231F005: return (FARPROC)MyCreateFileA;
            case 0xA3925CB0: return (FARPROC)MySetFilePointer;
            case 0x9EE55C22: return (FARPROC)MyGetFileSize;
            case 0x3254E3A4: return (FARPROC)MyReadFile;
            case 0x038499FB: return (FARPROC)MyCloseHandle;
//        case 0x0BD83C26: return (FARPROC)MyGetVersion;
//        case 0x16B489DD: return (FARPROC)MyCreateWindowExA;
        }
    }

#if defined(LBEX_CN)
    FARPROC ProcAddress = GetProcAddress(hModule, lpProcName);
    if (ProcAddress == NULL)
        ProcAddress = GetProcAddress(hModuleKernel32, lpProcName);

    return ProcAddress;

#else

    return GetProcAddress(hModule == (HMODULE)&__ImageBase ? hModuleKernel32 : hModule, lpProcName);

#endif
}

DWORD WINAPI MyGetVersion()
{
    static BOOL bInit = False;

    if (bInit == False)
    {
        bInit = True;
        SFuncPatch f[] =
        {
            { JUMP, 0x8A1A0, SetCursorMask, 0 },
        };
        PatchMemory(0, 0, f, countof(f), GetModuleHandle(0));
    }

    return GetVersion();
}

template<class T> inline T myabs(T v1)
{
    return v1 < 0 ? -v1 : v1;
}

Void CDECL SetCursorMask(TImagePointer *p, BYTE color1, BYTE color2, BYTE color3)
{
    Int32 h, w, delta;
    PBYTE pbRaw;

    if (p->unknown == NULL)
        return;

    delta = 64;
    pbRaw = p->pbRaw;
    h = p->iHeight;
    w = p->iWidth;
    while (h--)
    {
        Int32 width = w;
        while (width--)
        {
//            if (pbRaw[0] == color1 && pbRaw[1] == color2 && pbRaw[2] == color3)
            if (myabs(int(pbRaw[0] - color1)) < delta &&
                myabs(int(pbRaw[1] - color2)) < delta &&
                myabs(int(pbRaw[2] - color3)) < delta)
            {
                pbRaw[3] = 0;
            }
            else
            {
                pbRaw[3] = -1;
            }
            pbRaw += 4;
        }
    }
}
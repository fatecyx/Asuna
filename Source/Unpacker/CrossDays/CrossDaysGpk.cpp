#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "ntdll.lib")

#include "CrossDaysGpk.h"
#include <Shlwapi.h>
#include "my_api.h"
#include "my_mem.h"
#include "zlib.h"
#include "zconf.h"
#include "FileDisk.cpp"
#include "Mem.cpp"

CCrossDaysGpk::CCrossDaysGpk()
{
    Reset();
}

Void CCrossDaysGpk::Reset()
{
    m_pIndex = NULL;
}

CCrossDaysGpk::~CCrossDaysGpk()
{
    Close();
}

Void CCrossDaysGpk::Close()
{
    if (m_pIndex)
    {
        for (DWORD i = 0; i != m_dwFiles; ++i)
        {
            Free(m_pIndex[i].pbHead);
        }
        Free(m_pIndex);
        m_pIndex = NULL;
    }
}

LONG CCrossDaysGpk::Open(WChar *szFile)
{
    Bool  bResult;
    PBYTE pbBuffer;
    TGpkTail Tail;

    Close();
    if (szFile == NULL)
        return CDG_EGENERAL;

    if (FileDisk.Open(szFile, FileDisk.READ, FileDisk.EXIST) == False)
        return -CDG_EOPEN;

    if (FileDisk.Seek(FileDisk.Seek_End, -(LONG)sizeof(Tail)) == False)
        return -CDG_ESEEK;

    if (FileDisk.Read(&Tail, sizeof(Tail)) == False)
        return -CDG_ESEEK;

//    if (lstrcmpA(Tail.tag1, "STKFile0PIDX") || lstrcmpA(Tail.tag2, "STKFile0PACKFILE"))
//        return -CDG_FORMAT;

    if (*(LPDWORD)&Tail.tag1[0]  != 'FKTS' || *(LPDWORD)&Tail.tag1[4] != '0eli' ||
        *(LPDWORD)&Tail.tag1[8]  != 'XDIP' || *(LPDWORD)&Tail.tag2[0] != 'FKTS' ||
        *(LPDWORD)&Tail.tag2[4]  != '0eli' || *(LPDWORD)&Tail.tag2[8] != 'KCAP' ||
        *(LPDWORD)&Tail.tag2[12] != 'ELIF')
        return -CDG_EFORMAT;

    if (FileDisk.Seek(FileDisk.Seek_End, -(INT32)(sizeof(Tail) + Tail.uiIndexSize)) == False)
        return -CDG_ESEEK;

    pbBuffer = (PBYTE)Alloc((Tail.uiIndexSize + 3) & ~3);
    if (pbBuffer == NULL)
        return -CDG_EMEMORY;
    if (FileDisk.Read(pbBuffer, Tail.uiIndexSize) == False)
        return -CDG_EREAD;

    bResult = InitIndex(pbBuffer, Tail.uiIndexSize);
    Free(pbBuffer);

    return bResult;
}

LONG CCrossDaysGpk::InitIndex(PBYTE pbBuffer, DWORD dwSize)
{
//    DWORD IndexMask[] = { 0x901B7C56, 0xDB3FFEB6, 0xEA7906B6, 0x4FA011CC };    
    DWORD IndexMask[] = { 0xB31DEE82, 0xC22CE957, 0x107B542F, 0x49759A4C };
    Bool  bResult;
    PBYTE pbIndex;
    DWORD dwUncompressSize, dwMaxFiles, dwLength;

    for (DWORD i = 0, j = 0; i < dwSize; i += 4)
    {
        *(LPDWORD)&pbBuffer[i] ^= IndexMask[j++];
        if (j == countof(IndexMask)) j = 0;
    }

    dwUncompressSize = *(LPDWORD)pbBuffer;
    pbIndex = (PBYTE)Alloc(dwUncompressSize);
    if (pbIndex == NULL)
        return -CDG_EMEMORY;

    bResult = uncompress(pbIndex, &dwUncompressSize, pbBuffer + 4, dwSize - 4);
    if (bResult != Z_OK)
    {
        Free(pbIndex);
        return CDG_EGENERAL;
    }

    // estimate file number
    dwMaxFiles = dwUncompressSize / sizeof(TGpkIndexInFile);
    m_pIndex = (TMyGpkIndex *)Alloc(dwMaxFiles * sizeof(*m_pIndex));
    if (m_pIndex == NULL)
    {
        Free(pbIndex);
        return -CDG_EMEMORY;
    }

    m_dwFiles = 0;
    for (PBYTE p = pbIndex, pbEnd = pbIndex + dwUncompressSize; p < pbEnd; )
    {
        TMyGpkIndex *pIndex;
        if (m_dwFiles == dwMaxFiles)
        {
            dwMaxFiles += dwMaxFiles / 2;
            m_pIndex = (TMyGpkIndex *)ReAlloc(dwMaxFiles * sizeof(*m_pIndex), m_pIndex);
            if (m_pIndex == NULL)
                return -CDG_EMEMORY;
        }

        dwLength = *(LPWORD)p;
        if (dwLength == 0)
            break;

        pIndex = &m_pIndex[m_dwFiles];
        p += 2;
        lstrcpynW((LPWSTR)pIndex->szName, (LPWSTR)p, dwLength + 1);
        p += dwLength * sizeof(WCHAR);
        dwLength = sizeof(*pIndex) - sizeof(pIndex->szName) - sizeof(pIndex->pbHead) - sizeof(pIndex->dwHeadLength);
        memcpy(&pIndex->v1, p, dwLength);
        p += dwLength;
        pIndex->dwHeadLength = *p;
        ++p;

        if (pIndex->dwHeadLength)
        {
            pIndex->pbHead = (PBYTE)Alloc(pIndex->dwHeadLength);
            if (pIndex->pbHead == NULL)
                return -CDG_EMEMORY;

            dwLength = pIndex->dwHeadLength;
            memcpy(pIndex->pbHead, p, dwLength);
            p += dwLength;
        }
        else
        {
            pIndex->pbHead = NULL;
        }

        ++m_dwFiles;
    }

    m_pIndex = (TMyGpkIndex *)ReAlloc(m_dwFiles * sizeof(*m_pIndex), m_pIndex);

    return m_pIndex ? CDG_SUCCESS : -CDG_EMEMORY;
}

DWORD CCrossDaysGpk::GetFileCount()
{
    return m_dwFiles;
}

TMyGpkIndex* CCrossDaysGpk::GetIndexPointer(DWORD dwIndex)
{
    if (m_pIndex == NULL || dwIndex >= m_dwFiles)
        return NULL;

    return &m_pIndex[dwIndex];
}

LONG CCrossDaysGpk::GetFileData(TMyGpkIndex *pIndex, PBYTE *ppbFile, LPDWORD pdwFileSize)
{
    LONG  Status;
    DWORD dwFileSize;
    PBYTE pbBuffer, pbUncompress;

    if (ppbFile == NULL)
    {
        if (pdwFileSize == NULL)
            return CDG_EGENERAL;

        switch (pIndex->dwTag)
        {
            case ZLIB_COMP:
                *pdwFileSize = pIndex->dwUncompressSize;
                break;
            case NO_COMP:
                *pdwFileSize = pIndex->dwSize;
                break;
            default:
                *pdwFileSize = 0;
        }

        return CDG_SUCCESS;
    }
    
    pbBuffer = NULL;
    pbUncompress = NULL;

    do
    {
        *ppbFile = NULL;
        *pdwFileSize = 0;

        if (FileDisk.Seek(FileDisk.Seek_Beg, pIndex->dwOffset) == False)
        {
            Status = -CDG_ESEEK;
            break;
        }

        pbBuffer = (PBYTE)Alloc(pIndex->dwSize);
        if (pbBuffer == NULL)
        {
            Status = -CDG_EMEMORY;
            break;
        }

        if (FileDisk.Read(pbBuffer + pIndex->dwHeadLength, pIndex->dwSize - pIndex->dwHeadLength) == False)
        {
            Status = -CDG_EREAD;
            break;
        }

        if (pIndex->dwHeadLength)
            memcpy(pbBuffer, pIndex->pbHead, pIndex->dwHeadLength);

        if (pIndex->dwTag == ZLIB_COMP)
        {
            Bool bRet;
            pbUncompress = (PBYTE)Alloc(pIndex->dwUncompressSize);
            if (pbUncompress == NULL)
            {
                Status = -CDG_EMEMORY;
                break;
            }

            dwFileSize = pIndex->dwUncompressSize;
            bRet = uncompress(pbUncompress, &dwFileSize, pbBuffer, pIndex->dwSize);
            Free(pbBuffer);
            if (bRet != Z_OK)
            {
                Status = -CDG_EDECOMP;
                break;
            }

            pbBuffer = pbUncompress;
        }
        else if (pIndex->dwTag == NO_COMP)
        {
            dwFileSize = pIndex->dwSize;
        }
        else
        {
            Status = -CDG_EFORMAT;
            break;
        }

        *ppbFile = pbBuffer;
        *pdwFileSize = dwFileSize;
        Status = CDG_SUCCESS;
    } while (0);

    return Status;
}

LONG CCrossDaysGpk::ExtractFile(TMyGpkIndex *pIndex, LPWSTR lpOutDirectory)
{
    LONG   Status;
    DWORD  dwFileSize;
    PBYTE  pbFile;
    WCHAR  szCurDirectory[MAX_PATH];
    LPWSTR lpFileName;

    if (m_pIndex == NULL)
        return CDG_EGENERAL;

    pbFile = NULL;

    do
    {
        Status = GetFileData(pIndex, &pbFile, &dwFileSize);
        if (Status != CDG_SUCCESS)
        {
            break;
        }

        if (lpOutDirectory)
        {
            GetCurrentDirectoryW(countof(szCurDirectory), szCurDirectory);
            CreateDirectoryW(lpOutDirectory, NULL);
            if (SetCurrentDirectoryW(lpOutDirectory) == False)
            {
                Status = -CDG_EGENERAL;
                break;
            }
        }

        lpFileName = PathFindFileNameW(pIndex->szName);
        if (lpFileName != pIndex->szName)
        {
            WCHAR ch;
            ch = *lpFileName;
            *lpFileName = 0;
            MyCreateDirectoryW(pIndex->szName);
            *lpFileName = ch;
        }

        CFileDisk fd;
        if (fd.Open(pIndex->szName, FileDisk.WRITE, FileDisk.NEW) == False)
        {
            Status = CDG_EGENERAL;
            if (lpOutDirectory)
                SetCurrentDirectoryW(szCurDirectory);
            break;
        }
        if (fd.Write(pbFile, dwFileSize) == False)
        {
            Status = CDG_EGENERAL;
        }
        else
        {
            Status = CDG_SUCCESS;
        }

        if (lpOutDirectory)
            SetCurrentDirectoryW(szCurDirectory);
    } while (0);

    Free(pbFile);

    return Status;
}

DWORD CCrossDaysGpk::ExtractAll(LPWSTR lpOutDirectory)
{
    DWORD dwFiles;
    WCHAR szCurDirectory[MAX_PATH];

    if (lpOutDirectory)
    {
        GetCurrentDirectoryW(countof(szCurDirectory), szCurDirectory);
        CreateDirectoryW(lpOutDirectory, NULL);
        if (SetCurrentDirectoryW(lpOutDirectory) == False)
            return -1;
    }

    dwFiles = 0;
    for (DWORD i = 0; i != m_dwFiles; ++i)
    {
        if (ExtractFile(&m_pIndex[i], NULL) == CDG_SUCCESS)
            ++dwFiles;
    }

    if (lpOutDirectory)
        SetCurrentDirectoryW(szCurDirectory);

    return dwFiles;
}
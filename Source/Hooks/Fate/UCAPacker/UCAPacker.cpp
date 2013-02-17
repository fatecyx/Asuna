#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "../ucadec.lib")
#pragma comment(lib, "../ucidec.lib")
#pragma comment(lib, "bass.lib")
#pragma comment(lib, "bass_aac.lib")
#pragma warning(disable:4200)

#include "../SPI.h"
#include <Shlwapi.h>
#include <stdio.h>
#include <locale.h>
#include "my_common.h"
#include "getmainargs.h"
#include "../Fate.h"

_MY_C_HEAD_
#include "LZMA/7zVersion.h"
#include "LZMA/Alloc.h"
#include "LZMA/Lzma86.h"
_MY_C_TAIL_

void __cdecl main2(int argc, wchar_t **argv)
{
    if (argc < 3)
    {
        printf("Too few parameters\n");
        return;
    }

    Byte  *outBuffer, FileType, bLZMA;
    SizeT  inSize, outSize, outMaxSize;
    WCHAR  szFileName[MAX_PATH];
    WCHAR  *szFileType[] = { L"UCA", L"UCI", L"AAC", L"M4A", L"Unknown" };
    PBYTE  pbFile;
    DWORD  dwFileNumber, dwErrorCount, dwMaxNumber, dwFileSize, dwRead;
    DWORD  dwBufferSize, dwMaxFileNumber, dwMethod[] = {'ACU', 'ICU', 'CAA', 'A4M', 'KNU'};
    HANDLE hFind, hHeap, hFile, hDestFile;
    WIN32_FIND_DATAW wfd;
    TSpiArchiveInfo *pSpiArcInfo;
    LARGE_INTEGER liFrequency, liStart, liStop;

    setlocale(LC_CTYPE, "");

    hDestFile = CreateFileW(argv[2],
                    GENERIC_READ|GENERIC_WRITE,
                    FILE_SHARE_READ|FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    if (hDestFile == INVALID_HANDLE_VALUE)
    {
        wprintf(L"Can't create %s\n", argv[2]);
        return;
    }

    swprintf(szFileName, L"%s\\*.*", argv[1]);
    hFind = FindFirstFileW(szFileName, &wfd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        wprintf(L"Can't find %s\n", szFileName);
        return;
    }

    outMaxSize   = 0;
    dwBufferSize = 0;
    dwErrorCount = 0;
    dwFileNumber = 0;
    dwMaxNumber  = 1000;
    hHeap = GetProcessHeap();
    pbFile = (PBYTE)HeapAlloc(hHeap, 0, 0);
    outBuffer = (Byte *)HeapAlloc(hHeap, 0, 0);
    pSpiArcInfo = (TSpiArchiveInfo *)HeapAlloc(hHeap,
                        HEAP_ZERO_MEMORY, dwMaxNumber * sizeof(*pSpiArcInfo));
    WriteFile(hDestFile, pSpiArcInfo, 0x10, &dwRead, NULL);

    bLZMA = argc >= 4 ? (Byte)wcstoul(argv[3], NULL, 10) : 1;
    dwMaxFileNumber = argc == 5 ? wcstoul(argv[4], NULL, 10) : -1;
    QueryPerformanceFrequency(&liFrequency);
    QueryPerformanceCounter(&liStart);

    do
    {
        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;

        swprintf(szFileName, L"%s\\%s", argv[1], wfd.cFileName);
        hFile = CreateFileW(szFileName,
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            wprintf(L"Open %s failed.\n", szFileName);
            ++dwErrorCount;
            continue;
        }

        if (dwFileNumber >= dwMaxNumber)
        {
            dwMaxNumber = dwMaxNumber + (dwMaxNumber >> 1);
            pSpiArcInfo = (TSpiArchiveInfo *)HeapReAlloc(hHeap, HEAP_ZERO_MEMORY,
                pSpiArcInfo, dwMaxNumber * sizeof(*pSpiArcInfo));
        }

        dwFileSize = GetFileSize(hFile, NULL);
        if (dwFileSize > dwBufferSize)
        {
            dwBufferSize = dwFileSize;
            pbFile = (PBYTE)HeapReAlloc(hHeap, 0, pbFile, dwBufferSize);
        }

        ReadFile(hFile, pbFile, dwFileSize, &dwRead, NULL);
        CloseHandle(hFile);

        FileType = CheckFileType(pbFile);

        wprintf(L"Packing %s ... %s ", szFileName, szFileType[FileType]);
        pSpiArcInfo[dwFileNumber].position = SetFilePointer(hDestFile, 0, 0, FILE_CURRENT);
        if (dwFileSize > 300 && bLZMA && FileType != UCI && FileType != M4A && FileType != AAC)
        {
            outSize = dwFileSize / 20 * 21 + (1 << 16) + 4;
            if (outSize > outMaxSize)
            {
                outMaxSize = outSize;
                outBuffer = (Byte *)HeapReAlloc(hHeap, 0, outBuffer, outSize);
            }
            Lzma86_Encode(outBuffer, &outSize, (Byte *)pbFile, dwFileSize, 9, 1 << 27, 0);
            pSpiArcInfo[dwFileNumber].compsize = outSize;
            WriteFile(hDestFile, outBuffer, outSize, &dwRead, NULL);
            wprintf(L"@ compressed ... ");
        }
        else
        {
            if (FileType != UCI && FileType != UCA)
            {
                WriteFile(hDestFile, &dwFileSize, 4, &dwRead, NULL);
            }
            WriteFile(hDestFile, pbFile, dwFileSize, &dwRead, NULL);
            pSpiArcInfo[dwFileNumber].compsize = dwFileSize;
        }

		if (FileType != UNKNOWN)
        {
			*(LPDWORD)&pSpiArcInfo[dwFileNumber].method = dwMethod[FileType];
		}

        int w, h, b;
        CHAR *p;
        HSTREAM hStream;
        static BOOL bBassInit = FALSE;
        
        WideCharToMultiByte(936,
                    0,
                    wfd.cFileName,
                    -1,
                    pSpiArcInfo[dwFileNumber].filename,
                    sizeof(pSpiArcInfo[dwFileNumber].filename),
                    NULL, NULL);
		if (FileType == UNKNOWN)
		{
			CHAR *pExt = PathFindExtensionA(pSpiArcInfo[dwFileNumber].filename);
			if (pExt++)
			{
				lstrcpynA((LPSTR)pSpiArcInfo[dwFileNumber].method, pExt, sizeof(pSpiArcInfo->method));
			}
			else
			{
				*(LPDWORD)&pSpiArcInfo[dwFileNumber].method = 'KNU';
			}
		}
        
        p = PathFindExtensionA(pSpiArcInfo[dwFileNumber].filename);
        switch (FileType)
        {
        case UCA:
            UCADecode(pbFile, dwFileSize, NULL,(int *)&pSpiArcInfo[dwFileNumber].filesize);
            if (p)
            {
                lstrcpyA(p + 1, "wav");
            }
            printf("OK!");
            break;

        case UCI:
            UCIDecode(pbFile, dwFileSize, NULL, NULL, &w, &h, &b);
            pSpiArcInfo[dwFileNumber].filesize =
                (w * b / 8 + (b == 0x18 ? (w & 3) : 0)) * h + sizeof(TBitMapHeader);
            if (p)
            {
                lstrcpyA(p + 1, "bmp");
            }
            printf("OK!");
            break;

        case AAC:
        case M4A:
            if (bBassInit == FALSE)
            {
                bBassInit = TRUE;
                if (BASS_Init(0, 44100, 0, NULL, NULL) == FALSE)
                {
                    ++dwErrorCount;
                    printf("failed!");
                    break;
                }
            }

            hStream = FileType == AAC ? 
                BASS_AAC_StreamCreateFile(TRUE, pbFile, 0, dwFileSize, BASS_STREAM_DECODE) :
                BASS_MP4_StreamCreateFile(TRUE, pbFile, 0, dwFileSize, BASS_STREAM_DECODE);
            if (hStream)
            {
                pSpiArcInfo[dwFileNumber].filesize =
                    (DWORD)BASS_ChannelGetLength(hStream, BASS_POS_BYTE) +  + sizeof(TWaveHeader);

                BASS_StreamFree(hStream);

                if (p)
                {
                    lstrcpyA(p + 1, "wav");
                }

                printf("OK!");
            }
            else
            {
                ++dwErrorCount;
                printf("failed!");
            }
            break;

        default:
            pSpiArcInfo[dwFileNumber].filesize = dwFileSize;
            printf("OK!");
        }
        wprintf(L"\n");

        ++dwFileNumber;

    } while (dwFileNumber < dwMaxFileNumber && FindNextFileW(hFind, &wfd));

    HeapFree(hHeap, 0, pbFile);
    FindClose(hFind);

    TUCXPHeader header;

    header.dwTag = 'etaF';

    header.dwIndexOffset = SetFilePointer(hDestFile, 0, 0, FILE_CURRENT);
    header.dwFileNumber = dwFileNumber++;   // Ô¤ÁôÒ»¸ö¿Õ°×

    if (dwFileNumber == dwMaxNumber)
    {
        pSpiArcInfo = (TSpiArchiveInfo *)HeapReAlloc(hHeap, HEAP_ZERO_MEMORY,
                pSpiArcInfo, (dwFileNumber + 1) * sizeof(*pSpiArcInfo));
    }

    // compress index
    inSize = dwFileNumber * sizeof(*pSpiArcInfo);
    outSize = inSize / 20 * 21 + (1 << 16) + 4;
    if (outSize > outMaxSize)
    {
        outMaxSize = outSize;
        outBuffer = (Byte *)HeapReAlloc(hHeap, 0, outBuffer, outSize);
    }

    if (Lzma86_Encode(outBuffer, &outSize, (Byte *)pSpiArcInfo, inSize, 9, 1 << 27, 0))
    {
        printf("Compress index ERROR!\n");
    }

    HeapFree(hHeap, 0, pSpiArcInfo);
    header.dwIndexSize = outSize;

    WriteFile(hDestFile, outBuffer, outSize, &dwRead, NULL);
    SetFilePointer(hDestFile, 0, 0, FILE_BEGIN);
    WriteFile(hDestFile, &header, sizeof(header), &dwRead, NULL);

    double size;
    size = GetFileSize(hDestFile, NULL);
    CloseHandle(hDestFile);

    HeapFree(hHeap, 0, outBuffer);

    QueryPerformanceCounter(&liStop);

    WCHAR *unit;

    if (size > 1024 * 1024)
    {
        unit = L"MB";
        size /= 1024 * 1024;
    }
    else if (size > 1024)
    {
        unit = L"KB";
        size /= 1024;
    }
    else
    {
        unit = L"B";
    }

    wprintf(L"\nTarget file: %s\n"
            L"File size: %.2f %s\n"
            L"Failed: %u\n"
            L"Total: %u file(s)\n"
            L"Elapsed time: %u ms\n",
            argv[2], size, unit, dwErrorCount, dwFileNumber - 1,
            (liStop.QuadPart - liStart.QuadPart) * 1000 / liFrequency.QuadPart);
}

void main(int argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
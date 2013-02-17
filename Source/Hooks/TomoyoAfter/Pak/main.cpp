#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(lib, "Shlwapi.lib")

#include <Windows.h>
#include <Shlwapi.h>
#include <stdio.h>
#include "getmainargs.h"
#include "../TA.h"

FORCEINLINE void main2(int argc, char **argv)
{
    if (argc == 1)
        return;

    CHAR szFile[MAX_PATH];
    LPSTR lpPath;
    PBYTE pbBuffer;
    DWORD dwOffset, dwSize, dwRead, dwOrder, dwNameOrder;
    DWORD dwIndexCount, dwMaxIndexCount, dwBufferSize;
    HANDLE hHeap, hFind, hFile, hSrc;
    LPDWORD pIndex, pIndexReverse;
    WIN32_FIND_DATA wfd;

    dwBufferSize = 0;
    dwMaxIndexCount = 1000;
    hHeap = GetProcessHeap();
    pbBuffer = (PBYTE)HeapAlloc(hHeap, 0, 0);
    pIndex = (LPDWORD)HeapAlloc(hHeap, 0, sizeof(*pIndex) * dwMaxIndexCount);

    for (int i = 1; i != argc; ++i)
    {
        printf("Packing %s ... ", argv[i]);
        if ((GetFileAttributes(argv[i]) & FILE_ATTRIBUTE_DIRECTORY) == 0)
        {
            printf("isn't a directory.\n", argv[i]);
            continue;
        }

        dwSize = lstrlen(argv[i]) - 1;
        if (argv[i][dwSize] == '\\')
            argv[i][dwSize--] = 0;
        while (dwSize && argv[i][dwSize] != '\\')
            --dwSize;
        if (dwSize)
            ++dwSize;
        lpPath = &argv[i][dwSize];

        dwSize = GetFullPathName(argv[i], sizeof(szFile), szFile, NULL);
        if (szFile[dwSize - 1] == '\\')
        {
            szFile[dwSize - 1] = '.';
        }
        else
        {
            szFile[dwSize++] = '.';
        }
        *(LPDWORD)&szFile[dwSize] = 'kap';

        hFile = CreateFile(szFile,
                    GENERIC_WRITE,
                    FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            printf("Can't create %s.\n", szFile);
            continue;
        }
        SetCurrentDirectory(argv[i]);
        hFind = FindFirstFile("*.uca", &wfd);
        if (hFind == INVALID_HANDLE_VALUE)
        {
            printf("Can't find any file in %s.\n", argv[i]);
            CloseHandle(hFile);
            DeleteFile(szFile);
            continue;
        }

        dwOrder = 0;
        dwOffset = 0;
        dwIndexCount = 0;

        do
        {
            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                continue;

            if (sscanf(wfd.cFileName, "%*c%*4u%5u", &dwNameOrder) != 1)
            {
                printf("Invalid file name %s.\n", wfd.cFileName);
                continue;
            }

            hSrc = CreateFile(wfd.cAlternateFileName,
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
            if (hSrc == INVALID_HANDLE_VALUE)
            {
                printf("Can't open %s.\n", wfd.cFileName);
                continue;
            }

            dwSize = GetFileSize(hSrc, NULL);

            while (1)
            {
                if (dwIndexCount + 1 == dwMaxIndexCount)
                {
                    dwMaxIndexCount += dwMaxIndexCount >> 1;
                    pIndex = (LPDWORD)HeapReAlloc(hHeap, 0, pIndex, sizeof(*pIndex) * dwMaxIndexCount);
                }

                if (dwOrder < dwNameOrder)
                {
                    pIndex[dwIndexCount] = dwOffset;
                    ++dwIndexCount;
                    ++dwOrder;
                }
                else
                {
                    pIndex[dwIndexCount] = dwOffset;
                    ++dwIndexCount;
                    ++dwOrder;
                    dwOffset += dwSize;
                    break;
                }
            }

            if (dwSize > dwBufferSize)
            {
                dwBufferSize = dwSize;
                pbBuffer = (PBYTE)HeapReAlloc(hHeap, 0, pbBuffer, dwBufferSize);
            }

            ReadFile(hSrc, pbBuffer, dwSize, &dwRead, NULL);
            CloseHandle(hSrc);
            WriteFile(hFile, pbBuffer, dwSize, &dwRead, NULL);
        } while (FindNextFile(hFind, &wfd));

        if (dwIndexCount)
        {
            pIndex[dwIndexCount++] = dwOffset;
            pIndexReverse = (LPDWORD)HeapAlloc(hHeap, 0, dwIndexCount * sizeof(*pIndexReverse));

            for (DWORD i = 0; i != dwIndexCount; ++i)
            {
                pIndexReverse[i] = pIndex[dwIndexCount - i - 1];
            }

            WriteFile(hFile, pIndexReverse, sizeof(*pIndexReverse) * dwIndexCount, &dwRead, NULL);
            --dwIndexCount;
            WriteFile(hFile, &dwIndexCount, 4, &dwRead, NULL);
            HeapFree(hHeap, 0, pIndexReverse);
        }
        CloseHandle(hFile);
        printf("OK\n");
    }

    HeapFree(hHeap, 0, pbBuffer);
    HeapFree(hHeap, 0, pIndex);

    return;
}

void CDECL main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}

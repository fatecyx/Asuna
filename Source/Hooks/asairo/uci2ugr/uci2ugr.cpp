#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"
#include <set>
#include <vector>
#include <string>

using std::set;
using std::string;
using std::vector;

Int32 GetOutputName(PChar szFileName, const Char *szInFile)
{
    Int32 len;
    PChar pUL;

    len = StrLenA(szInFile);
    memcpy(szFileName, szInFile, len + 1);
    if (len < 9 || 
        !(pUL = strstr(szFileName, "__")) || 
        (pUL[2] > '9' || pUL[2] < '0') || 
        (pUL[3] > '9' || pUL[3] < '0') || 
        (pUL[4] > '9' || pUL[4] < '0') || 
        (pUL[5] > '9' || pUL[5] < '0') || 
        (pUL[6] > '9' || pUL[6] < '0') )
    {
        rmext(szFileName);
        strcat(szFileName, ".ugr");
        return 1;
    }

    strcpy(pUL, ".ugr");

    return 0;
}

ForceInline Void main2(Int argc, WChar **argv)
{
    HANDLE hHeap;
    LPVoid lpBuffer;
    UInt32 Len, uSize, uMaxBuffer, uMaxFrames, uFrames, *puOffsets;

    uMaxBuffer = 0x1000;
    uMaxFrames = 100;
    hHeap = GetProcessHeap();
    lpBuffer  = HeapAlloc(hHeap, 0, uMaxBuffer);;
    puOffsets = (PUInt32)HeapAlloc(hHeap, 0, uMaxFrames * 4);
    for (Int i = 1; i != argc; ++i)
    {
        DWORD dwRead, offset;
        HANDLE hFind, hFile, hFileUCI;
        Char  szFile[MAX_PATH], *pSn;
        WIN32_FIND_DATAA wfd;
        set<string> nameset;
        vector<string> name;

        SetCurrentDirectoryW(*++argv);
        hFind = FindFirstFileA("*.uci", &wfd);
        if (hFind == INVALID_HANDLE_VALUE)
            continue;

        do
        {
            name.push_back(wfd.cFileName);
        } while (FindNextFileA(hFind, &wfd));

        FindClose(hFind);

        if (name.size() > uMaxFrames)
        {
            uMaxFrames = name.size();
            puOffsets = (PUInt32)HeapReAlloc(hHeap, 0, puOffsets, uMaxFrames * 4);
        }

        for (size_t i = 0; i != name.size(); ++i)
        {
            Len = GetOutputName(szFile, name[i].c_str());
            if (nameset.count(szFile))
                continue;

            nameset.insert(szFile);
            hFile = CreateFileA(szFile,
                            GENERIC_WRITE,
                            FILE_SHARE_WRITE,
                            NULL,
                            CREATE_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);
            if (hFile == INVALID_HANDLE_VALUE)
                continue;

            if (Len)
            {
                hFileUCI = CreateFileA(name[i].c_str(),
                                GENERIC_READ,
                                FILE_SHARE_READ,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);
                if (hFileUCI == INVALID_HANDLE_VALUE)
                {
                    CloseHandle(hFile);
                    DeleteFile(szFile);
                    continue;
                }

                uSize = GetFileSize(hFileUCI, NULL);
                if (uSize > uMaxBuffer)
                {
                    uMaxBuffer = uSize;
                    lpBuffer = HeapReAlloc(hHeap, 0, lpBuffer, uMaxBuffer);
                }
                ReadFile(hFileUCI, lpBuffer, uSize, &dwRead, NULL);
                CloseHandle(hFileUCI);

                offset = 1;
                WriteFile(hFile, &offset, 2, &dwRead, NULL);
                WriteFile(hFile, lpBuffer, uSize, &dwRead, NULL);
                CloseHandle(hFile);

                continue;
            }

            uFrames = 0;
            pSn = findext(szFile);
            do
            {
                sprintf(pSn, "__%05u.uci", uFrames++);
            } while (GetFileAttributesA(szFile) != -1);
            --uFrames;

            if (uFrames > uMaxFrames)
            {
                uMaxFrames = uFrames;
                puOffsets = (PUInt32)HeapReAlloc(hHeap, 0, puOffsets, uMaxFrames * 4);
            }

            WriteFile(hFile, &uFrames, 2, &dwRead, NULL);
            WriteFile(hFile, puOffsets, uFrames * 4, &dwRead, NULL);

            offset = 2 + uFrames * 4;
            for (UInt32 i = 0; i != uFrames; ++i)
            {
                puOffsets[i] = offset;
                sprintf(pSn, "__%05u.uci", i);
                hFileUCI = CreateFileA(szFile,
                                GENERIC_READ,
                                FILE_SHARE_READ,
                                NULL,
                                OPEN_EXISTING, 
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);
                if (hFileUCI == INVALID_HANDLE_VALUE)
                {
                    CloseHandle(hFile);
                    continue;
                }

                uSize = GetFileSize(hFileUCI, NULL);
                offset += uSize;
                if (uSize > uMaxBuffer)
                {
                    uMaxBuffer = uSize;
                    lpBuffer = HeapReAlloc(hHeap, 0, lpBuffer, uMaxBuffer);
                }
                ReadFile(hFileUCI, lpBuffer, uSize, &dwRead, NULL);
                CloseHandle(hFileUCI);
                WriteFile(hFile, lpBuffer, uSize, &dwRead, NULL);
            }

            SetFilePointer(hFile, 2, NULL, FILE_BEGIN);
            WriteFile(hFile, puOffsets, uFrames * 4, &dwRead, NULL);
            CloseHandle(hFile);
        }
    }

    HeapFree(hHeap, 0, lpBuffer);
    HeapFree(hHeap, 0, puOffsets);
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
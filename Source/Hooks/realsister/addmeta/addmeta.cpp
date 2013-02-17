#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(lib, "Shlwapi.lib")

#include <Windows.h>
#include "my_headers.h"

Void _DeleteFile(LPWSTR lpFileName)
{
    DWORD  dwSize;
    HANDLE hFile, hFileMeta, hHeap;
    PByte  pbBuffer;

    if (StrICmpW(findextw(lpFileName), L".uci"))
    {
//        wprintf(L"\"%s\" is not a uci image file.\n", lpFileName);
        return;
    }

//    wprintf(L"Processing \"%s\" ... ", lpFileName);
    SetFileAttributesW(lpFileName, FILE_ATTRIBUTE_NORMAL);
    hFile = CreateFileW(lpFileName,
        GENERIC_READ|GENERIC_WRITE,
        FILE_SHARE_READ|FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
//        printf("failed\n");
        return;
    }

    rmextw(lpFileName);
    lstrcatW(lpFileName, L".meta");
    hFileMeta = CreateFileW(lpFileName,
                GENERIC_READ,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if (hFileMeta == INVALID_HANDLE_VALUE)
    {
//        printf("failed\n");
        CloseHandle(hFile);
        return;
    }

    dwSize = GetFileSize(hFileMeta, NULL);

    do
    {
        hHeap = GetProcessHeap();
        pbBuffer = (PByte)HeapAlloc(hHeap, 0, dwSize);
        if (pbBuffer == NULL)
            break;

        ReadFile(hFileMeta, pbBuffer, dwSize, &dwSize, NULL);
        SetFilePointer(hFile, 0, 0, FILE_END);
        WriteFile(hFile, pbBuffer, dwSize, &dwSize, NULL);
        HeapFree(hHeap, 0, pbBuffer);
    } while (0);

    CloseHandle(hFileMeta);
    CloseHandle(hFile);
//    printf("OK\n");
}

NoInline Bool FASTCALL IsParentDirectory(PCWChar pszPath)
{
    return !lstrcmpW(pszPath, L".") || !lstrcmpW(pszPath, L"..");
}

Void DeleteFolder(LPWSTR lpPath, LPWIN32_FIND_DATAW pWfd)
{
    LPWSTR lpEnd;
    HANDLE hFind;

    if (GetFileAttributesW(lpPath) == -1)
        return;

    lpEnd = lpPath + lstrlenW(lpPath);
    lstrcpyW(lpEnd, L"\\*.*");

    hFind = FindFirstFileW(lpPath, pWfd);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (IsParentDirectory(pWfd->cFileName))
                continue;

            lstrcpyW(lpEnd + 1, pWfd->cFileName);
            if (pWfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                DeleteFolder(lpPath, pWfd);
            }
            else
            {
                _DeleteFile(lpPath);
            }
        } while (FindNextFileW(hFind, pWfd));
        FindClose(hFind);
    }

    *lpEnd = 0;
}

void ForceInline main2(int argc, WChar **argv)
{
    LPWSTR lpFileName;
    WCHAR  szPath[MAX_PATH];
    HANDLE hFind;
    WIN32_FIND_DATAW wfd;

//    setlocale(LC_CTYPE, "");
    for (int i = 1; i != argc; ++i)
    {
        hFind = FindFirstFileW(argv[i], &wfd);
        if (hFind == INVALID_HANDLE_VALUE)
            continue;

        lstrcpyW(szPath, argv[i]);
        lpFileName = findnamew(szPath);

        do
        {
            if (IsParentDirectory(wfd.cFileName))
                continue;

            lstrcpyW(lpFileName, wfd.cFileName);

            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                DeleteFolder(szPath, &wfd);
            else
                _DeleteFile(szPath);
        } while (FindNextFileW(hFind, &wfd));

        FindClose(hFind);
    }
}

void __cdecl main(int argc, WChar **argv)
{
    argv = CmdLineToArgvW(GetCommandLineW(), &argc);
    main2(argc, argv);
    ExitProcess(0);
}
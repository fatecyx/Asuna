#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")

#include <Windows.h>
#include "getmainargs.h"

void __cdecl main(int argc, wchar_t* argv[])
{
    getargsW(&argc, &argv);

    if (argc < 2)
        return;

    BOOL   flag;
    WCHAR  raw, replace;
    HANDLE hFind;
    WIN32_FIND_DATAW wfd;

    if (SetCurrentDirectoryW(argv[1]) == FALSE)
        return;

    hFind = FindFirstFileW(L"*.*", &wfd);
    if (hFind == INVALID_HANDLE_VALUE)
        return;

    if (*argv[2] == 'c')
    {
        raw = 0x30FB;
        replace = 0x00B7;
        raw = L'%';
        replace = L'ге';
    }
    else
    {
        raw = 0x00B7;
        replace = 0x30FB;
        raw = L'ге';
        replace = L'%';
    }

    do
    {
        if (GetFileAttributesW(wfd.cFileName) & FILE_ATTRIBUTE_DIRECTORY)
            continue;

        int i;
        int len = lstrlenW(wfd.cFileName);
        WCHAR file[MAX_PATH];

        flag = FALSE;
        for (i = 0; wfd.cFileName[i]; ++i)
        {
            file[i] = wfd.cFileName[i];
            if (wfd.cFileName[i] == raw)
            {
                file[i] = replace;
                flag = TRUE;
            }
        }
        file[i] = 0;

        if (flag == TRUE)
        {
            MoveFileW(wfd.cFileName, file);
        }
    } while (FindNextFileW(hFind, &wfd));

    FindClose(hFind);
}
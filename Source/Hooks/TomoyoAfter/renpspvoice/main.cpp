// 174 -> 142
#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(lib, "Shlwapi.lib")

#include <Windows.h>
#include <Shlwapi.h>
#include <stdio.h>
#include <conio.h>
#include "getmainargs.h"
#include "my_crtadd.h"
#include "my_api.h"

void FORCEINLINE main2(int argc, char **argv)
{
    if (argc < 3)
        return;

    DWORD dwPakIndex, dwVoiceIndex, dwAdd;
    LPSTR lpName;
    CHAR  szDestName[MAX_PATH];

    dwAdd = 0x50;
    lpName = PathFindFileName(argv[1]);
    sscanf(lpName, "%03X%04X", &dwPakIndex, &dwVoiceIndex);
    ++dwPakIndex;
    dwVoiceIndex = ((dwVoiceIndex & 0xF0) << 4) | ((dwVoiceIndex & 0xF) << 12) | HIBYTE(dwVoiceIndex);
    if (lpName == argv[1])
    {
        sprintf(szDestName, "%04u\\z%04u%05u.wav", dwPakIndex, dwPakIndex, dwVoiceIndex);
    }
    else
    {
        *(lpName - 1) = 0;
        while (1)
        {
            sprintf(szDestName, "%s\\%04u\\z%04u%05u.wav", argv[2], dwPakIndex, dwPakIndex, dwVoiceIndex);
            if (GetFileAttributes(szDestName) != -1)
            {
                dwPakIndex += dwAdd;
                dwAdd -= 0x10;
                printf("%s =>\n%s\n\n", PathFindFileName(argv[1]), PathFindFileName(szDestName));
            }
            else
            {
                break;
            }
        }
        *(lpName - 1) = '\\';
    }

    lpName = PathFindFileName(szDestName);
    if (lpName == szDestName)
    {
        printf("fuck you!\n");
        return;
    }
    --lpName;
    *lpName = 0;
    if (GetFileAttributes(szDestName) == -1)
    {
        MyCreateDirectory(szDestName);
    }
    *lpName = '\\';
    if (CopyFile(argv[1], szDestName, FALSE) == FALSE)
    {
        printf("Copy %s to %s failed.\n", argv[1], szDestName);
    }
    if (dwAdd != 0x50)
        printf("%X\n\n", dwAdd);

    return;
}

void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}

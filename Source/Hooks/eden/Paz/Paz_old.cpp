#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")

#include "my_crt.h"
#include "Paz.h"
#include "blowfish.h"
#include "my_api.h"

enum EInfoIndex { EF_FIRST, EF_LATTER, EDEN, EF_FD };
enum EDefault { DEFAULT_MODE = EF_FD };

const DWORD dwInfoIndex = DEFAULT_MODE;

Bool   g_bIsMovie, bIsVoice, bNeedXor;
HANDLE ghHeap;
DWORD  dwKeyIndex;
Char   headers[][0x20] = 
{
    "ef_first", "ef_latter", "eden_main", "ef_fd", "eden_PlusMosaic"
};

CHAR  *szType[] =
{
    "scr"  , "bgm" , "bg"  , "st"  , "sys"  , "voice"  , "se"  , "mov"  ,
    "pmscr", "pmbgm","pmbg", "pmst", "pmsys", "pmvoice", "pmse", "pmmov",
};

ForceInline void main2(int argc, TCHAR **argv)
{
    if (argc < 2)
    {
        _tprintf(_T("%s input_dir\n"), findname(argv[0]));
        return;
    }

    TCHAR  szOutFile[MAX_PATH];
    HANDLE hOut, hHeap;
    DWORD  dwLength, dwEntryCount;
    PAZTYPE PazType;
    TMyPAZEntry *pEntry;

    hHeap = GetProcessHeap();
    ghHeap = hHeap;
    for (int i = 1; i != argc; ++i)
    {
        Char  (*pPazHeader)[sizeof(headers[0])];
        DWORD dwAttributes;

        dwAttributes = GetFileAttributes(argv[i]);
        if (dwAttributes == -1)
        {
            _tprintf(_T("\"%s\" doesn't exist.\n"), argv[i]);
            continue;
        }
        else if ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
        {
            _tprintf(_T("%s isn't a directory.\n"), argv[i]);
            continue;
        }

        LPCSTR lpPath;

        lstrcpy(szOutFile, argv[i]);
        dwLength = lstrlen(szOutFile);
        if (szOutFile[dwLength - 1] == '\\')
            szOutFile[dwLength - 1] = 0;
        lstrcat(szOutFile, ".paz");

        lpPath = argv[i];
        PazType = NONE;
        if (i + 2 < argc)
        {
            int j = i + 1;
            if (argv[j][0] == '-' && ((argv[j][1] & 0xDF) == 'T'))
            {
                ++j;
                for (int k = 0; k != countof(szType); ++k)
                {
                    if (!lstrcmpi(szType[k], argv[j]))
                    {
                        i = j;
                        PazType = (PAZTYPE)k;
                        break;
                    }
                }
            }
        }
        else
        {
            PazType = GetPazTypeFromFileName(szOutFile);
        }

        if (PazType == NONE)
        {
            _tprintf(_T("Please specify one PAZ type by -t type or use a special file name.\n")
                _T("Following type is valid: \n\t")
                );
            for (int i = 0; i != countof(szType); ++i)
            {
                printf("%s ", szType[i]);
                if (i == countof(szType) / 2)
                    printf("\n\t");
            }

            break;
        }

        dwKeyIndex = GetKeyIndex(szType[PazType], &GameInfo[dwInfoIndex]);
        if (dwKeyIndex == -1)
        {
            printf("%s: don't know encryption key.\n", szOutFile);
            continue;
        }

        hOut = CreateFile(szOutFile,
                        GENERIC_READ|GENERIC_WRITE,
                        FILE_SHARE_READ|FILE_SHARE_WRITE,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
        if (hOut == INVALID_HANDLE_VALUE)
        {
            _tprintf(_T("Can't create \"%s\"\n"), szOutFile);
            continue;
        }

        g_bIsMovie = IsMovie(szOutFile);
        bIsVoice = IsAudio(szOutFile);
        SetCurrentDirectory(lpPath);
        dwEntryCount = GenerateEntry(&pEntry);
        if (dwEntryCount == 0 || pEntry == NULL)
        {
            _tprintf(_T("There is no file in \"%s\"\n"), argv[i]);
            continue;
        }

        bNeedXor = strnicmp(szType[PazType], "pm", 2) != 0;
        _tprintf(_T("Packing %s ...\n"), szOutFile);
        if (bNeedXor)
        {
            pPazHeader = (Char (*)[32])headers[dwInfoIndex];
        }
        else
            pPazHeader = (Char (*)[32])headers[countof(headers) - 1];

        WriteFile(hOut, pPazHeader, sizeof(*pPazHeader), &dwLength, NULL);
        WriteEntry(hOut, pEntry, dwEntryCount, False);

        WriteFileToPaz(hOut, pEntry, dwEntryCount, PazType);
        WriteEntry(hOut, pEntry, dwEntryCount, True);

        HeapFree(hHeap, 0, pEntry);
        CloseHandle(hOut);
    }
}

Void WINAPI WriteEntry(HANDLE hFile, TMyPAZEntry *pEntry, DWORD dwCount, Bool bEncrypt)
{
    DWORD  dwLength, dwEntryPos, dwRemainder;
    PBYTE  pbEntry;
    BYTE   byMovieSeed[256], byMod8[8];

    *(LPDWORD)&byMod8[0] = 0;
    *(LPDWORD)&byMod8[3] = 0;
    dwEntryPos = 0x24 + (g_bIsMovie ? 0x100 : 0);
    SetFilePointer(hFile, 0x20, 0, FILE_BEGIN);
    WriteFile(hFile, &dwCount, 4, &dwLength, NULL); // entry size
    WriteFile(hFile, &dwCount, 4, &dwLength, NULL); // entry count

    if (g_bIsMovie)
    {
        if (bEncrypt == False)
        {
            if (dwInfoIndex != EF_FIRST)
            {
                memset(byMovieSeed, 0, sizeof(byMovieSeed));
                WriteFile(hFile, byMovieSeed, sizeof(byMovieSeed), &dwLength, NULL);
            }
            else
            {
                for (int i = 0; i != 256; ++i)
                {
                    byMovieSeed[i] = i;
                }

                for (int i = 0; i != 256; ++i)
                    WriteFile(hFile, byMovieSeed, sizeof(byMovieSeed), &dwLength, NULL);
            }
        }
        else
        {
            SetFilePointer(hFile, dwInfoIndex != EF_FIRST ? 0x100 : 0x10000, 0, FILE_CURRENT);
        }
    }

    for (DWORD i = dwCount; i; )
    {
        LPSTR lpExt;

        --i;
        lpExt = findext(pEntry[i].szName);
        if (lpExt)
        {
            if (lstrcmpiA(lpExt, ".uca") && bIsVoice)
                *lpExt = 0;
            else if (lstrcmpiA(lpExt, ".ogg") && lstrcmpiA(lpExt, ".m4a"))
                lpExt = NULL;
        }

        dwLength = lstrlenA(pEntry[i].szName) + 1;
        WriteFile(hFile, pEntry[i].szName, dwLength, &dwLength, NULL);
        if (lpExt && *lpExt == 0)
        {
            *lpExt = '.';
        }

        WriteFile(hFile, &pEntry[i].l64Offset, sizeof(*pEntry) - sizeof(pEntry->szName), &dwLength, NULL);
    }
    dwCount = SetFilePointer(hFile, 0, 0, FILE_CURRENT) - sizeof(TPAZHeader);

    dwRemainder = dwCount % 8;
    if (dwRemainder)
    {
        dwRemainder = 8 - dwRemainder;
        WriteFile(hFile, byMod8, dwRemainder, &dwLength, NULL);
        dwCount += dwRemainder;
    }

    if (bEncrypt)
    {
        HANDLE hHeap;
        CBlowFish bf;

        hHeap = ghHeap;
        pbEntry = (PBYTE)HeapAlloc(hHeap, 0, dwCount);
        SetFilePointer(hFile, 0x24, 0, FILE_BEGIN);
        ReadFile(hFile, pbEntry, dwCount, &dwLength, NULL);

        bf.Initialize(GameInfo[dwInfoIndex].key[dwKeyIndex].IndexKey, sizeof(GameInfo[dwInfoIndex].key[dwKeyIndex].IndexKey));
        dwLength = bf.Encode(pbEntry, pbEntry, dwLength);
        if (bNeedXor)
        {
            Xor(pbEntry, dwLength);
        }

        SetFilePointer(hFile, 0x24, 0, FILE_BEGIN);
        WriteFile(hFile, pbEntry, dwLength, &dwLength, NULL);
        dwCount = SetFilePointer(hFile, 0, 0, FILE_CURRENT) - sizeof(TPAZHeader) + 4;
    }
    dwCount += 4;

    SetFilePointer(hFile, 0x20, NULL, FILE_BEGIN);
    WriteFile(hFile, &dwCount, 4, &dwLength, NULL); // entry size
    if (bEncrypt && bNeedXor)
    {
        CHAR h[0x24];
        SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
        ReadFile(hFile, h, sizeof(h), &dwLength, NULL);
        Xor((PBYTE)h, sizeof(h));
        SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
        WriteFile(hFile, h, sizeof(h), &dwLength, NULL);
    }
    SetFilePointer(hFile, 0, 0, FILE_END);
}

Bool WINAPI WriteFileToPaz(HANDLE hFile, TMyPAZEntry *pEntry, DWORD dwCount, PAZTYPE PazType)
{
    Bool   bResult;
    PBYTE  pbBuffer;
    DWORD  dwSize, dwBufferSize, dwRemainder;
    LONG64 llOffset;
    HANDLE hInput, hHeap;
    CHAR   szTitle[20];

    bResult = True;
    hHeap = ghHeap;
    dwBufferSize = 0;
    pbBuffer = (PBYTE)HeapAlloc(hHeap, 0, dwBufferSize);
    for (DWORD i = 0; i != dwCount; ++i)
    {
        hInput = CreateFile(pEntry[i].szName,
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
        if (hInput == INVALID_HANDLE_VALUE)
        {
            _tprintf(_T("Can't open \"%s\"\n"), pEntry->szName);
            bResult = False;
            break;
        }

        llOffset = 0;
        dwSize = SetFilePointer(hFile, 0, (PLONG)&llOffset, FILE_CURRENT);
        llOffset = (llOffset << 32) | dwSize;
        dwSize = GetFileSize(hInput, NULL);
        pEntry[i].dwUncompSize = dwSize;
        pEntry[i].dwCompSize   = dwSize;
        pEntry[i].l64Offset    = llOffset;
        if (dwSize + 8 >= dwBufferSize)
        {
            dwBufferSize = dwSize + 8;
            pbBuffer = (PBYTE)HeapReAlloc(hHeap, 0, pbBuffer, dwBufferSize);
        }
        ReadFile(hInput, pbBuffer, dwSize, &dwSize, NULL);
        CloseHandle(hInput);
        dwRemainder = dwSize % 8;
        if (dwRemainder)
        {
            dwRemainder = 8 - dwRemainder;
            memset(&pbBuffer[dwSize], 0, dwRemainder);
            dwSize += dwRemainder;
        }
        pEntry[i].dwDecryptSize = dwSize;
        Encrypt(pbBuffer, &pEntry[i]);
        sprintf(szTitle, "%u / %u", i + 1, dwCount);
        SetConsoleTitleA(szTitle);
        printf("\tWriting \"%s\" ...\n", pEntry[i].szName);
        WriteFile(hFile, pbBuffer, dwSize, &dwSize, NULL);
    }
    HeapFree(hHeap, 0, pbBuffer);

    return bResult;
}

Void WINAPI Xor(PBYTE pbBuffer, DWORD dwSize)
{
    DWORD dwXor = dwInfoIndex == EF_FIRST ? 0x7F7F7F7F : 0xAAAAAAAA;
    while (dwSize & 3)
    {
        pbBuffer[--dwSize] ^= dwXor;
    }
    dwSize /= 4;
    while (dwSize--)
    {
        ((LPDWORD)pbBuffer)[dwSize] ^= dwXor;
    }
}

DWORD WINAPI Encrypt(PBYTE pbBuffer, TMyPAZEntry *pEntry)
{
    CHAR   szName[MAX_PATH];
    BYTE   bySeed[400];
    DWORD  dwSeed, dwSize;
    LPCSTR lpCrud;
    LPSTR  lpExt, lpFileName;

    lpFileName = pEntry->szName;
    lstrcpy(szName, lpFileName);
    lpExt = findext(szName);
    if (lpExt && bIsVoice)
    {
        *lpExt = 0;
    }

    dwSize = pEntry->dwCompSize;
    lpCrud = GetCrud(findext(lpFileName), &GameInfo[dwInfoIndex]);
    if (lpCrud)
        dwSeed = sprintf((char *)bySeed, "%s %08X %s", strlwr(lpFileName), pEntry->dwCompSize, lpCrud ? lpCrud : "");
    else
    {
        dwSeed = 0;
        return 0;
    }

    if (g_bIsMovie == False)
    {
        CBlowFish bf;
        bf.Initialize(GameInfo[dwInfoIndex].key[dwKeyIndex].DataKey, sizeof(GameInfo[dwInfoIndex].key[dwKeyIndex].DataKey));
        if (lpCrud)
        {
            Decrypt(bySeed, dwSeed, pbBuffer, dwSize);
        }
        dwSize = bf.Encode(pbBuffer, pbBuffer, pEntry->dwDecryptSize);
    }
    else
    {
        if (dwInfoIndex != EF_FIRST)
        {
            memset(&bySeed[dwSeed + 10], 0, 0x100);
            DecryptMovie(&bySeed[dwSeed + 10], bySeed, dwSeed, pbBuffer, pEntry->dwCompSize);
        }
        else
        {
        }
    }

    if (bNeedXor)
        Xor(pbBuffer, dwSize);

    return dwSize;
}

Void WINAPI DecryptMovie(const PBYTE pbMovieSeed, const PBYTE pbSeed, DWORD dwSeedLength, PBYTE pbBuffer, DWORD dwBufferSize)
{
    static const DWORD dwKeyLength = 0x10000;
    BYTE key[dwKeyLength], pbRC4Table[256], pbRC4Key[256];

    if (dwSeedLength)
    {
        for (unsigned long i = 0; i != 256; i++)
        {
            pbRC4Key[i] = pbMovieSeed[i] ^ pbSeed[i % dwSeedLength];
        }
    }

    InitRC4Table(pbRC4Table, pbRC4Key);
    GenerateBlock(key, sizeof(key), pbRC4Table, sizeof(pbRC4Table));

    for (unsigned long i = 0; i != dwBufferSize; i++)
    {
        pbBuffer[i] ^= key[i % dwKeyLength];
    }
}

Void WINAPI InitRC4Table(PBYTE pbRC4Table, const PBYTE key)
{
    DWORD i, j, k;

    for (int a = 0; a != 256; ++a)
    {
        pbRC4Table[a] = a;
    }

    for (i = j = k = 0; i != 256; ++i, ++j)
    {
        k = (key[i] + pbRC4Table[j] + k) & 0xFF;
        Swap(pbRC4Table[k], pbRC4Table[j]);
    }
}

Void WINAPI GenerateBlock(PBYTE pbBlock, DWORD dwBlockSize, PBYTE pbRC4Key, DWORD dwKeySize)
{
    DWORD i, j, k, l;

    i = 1;
    j = 0;
    k = 0;

    while (dwBlockSize--)
    {
        k = (k + pbRC4Key[i]) & 0xFF;
        l = pbRC4Key[i] + pbRC4Key[k];
        Swap(pbRC4Key[i], pbRC4Key[k]);
        *pbBlock++ = pbRC4Key[l & 0xFF];
        ++i &= 0xFF;
    }
}

Void WINAPI Decrypt(PBYTE pbSeed, DWORD dwSeedLength, PBYTE pbBuffer, DWORD dwSize)
{
    CHAR  scramble[256];
    DWORD index, index1, index2;

    index  = 0;
    index1 = 0;
    index2 = 0;
    for (unsigned long i = 0; i != 256; i++)
    {
        scramble[i] = (unsigned char) i;
    }

    for (unsigned long i = 0; i != 256; i++)
    {
        index = (unsigned char) (index + scramble[i] + pbSeed[i % dwSeedLength]);
        Swap(scramble[i], scramble[index]);
    }

    for (unsigned long i = 0; i != dwSize; i++)
    {
        index1 = (unsigned char) (index1 + 1);
        index2 = (unsigned char) (index2 + scramble[index1]);
        Swap(scramble[index1], scramble[index2]);

        pbBuffer[i] ^= scramble[(unsigned char)(scramble[index1] + scramble[index2])];
    }
}

DWORD WINAPI GetKeyIndex(LPSTR lpFileName, TGameInfo *pGameInfo)
{
    CHAR  szName[MAX_PATH];
    LPSTR lpPrefix;
    DWORD dwLength, dwLength2;

    strcpy(szName, findname(lpFileName));
    lpPrefix = findext(szName);
    if (lpPrefix) *lpPrefix = 0;
    dwLength = strlen(szName);

    for (DWORD i = 0; pGameInfo->key[i].lpFileName; ++i)
    {
        lpPrefix = pGameInfo->key[i].lpFileName;
        dwLength2 = strlen(lpPrefix);
        if (!strnicmp(szName, lpPrefix, max(dwLength2, dwLength)))
            return i;
    }

    return -1;
}

DWORD WINAPI GenerateEntry(TMyPAZEntry **ppMyPAZEntry)
{
    HANDLE hFind, hHeap;
    DWORD  dwEntryCount, dwMaxEntry;
    TMyPAZEntry *pMyPAZEntry;
    WIN32_FIND_DATA wfd;

    *ppMyPAZEntry = NULL;
    hFind = FindFirstFile(_T("*.*"), &wfd);
    if (hFind == INVALID_HANDLE_VALUE)
        return 0;

    hHeap = ghHeap;
    dwEntryCount = 0;
    dwMaxEntry   = 1000;
    pMyPAZEntry  = (TMyPAZEntry *)HeapAlloc(hHeap,
        HEAP_ZERO_MEMORY, sizeof(*pMyPAZEntry) * 1000);

    if (pMyPAZEntry == NULL)
    {
        _tprintf(_T("Can't allocate memory for MyPAZEntry.\n"));
        return 0;
    }

    do
    {
        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;

#ifndef UNICODE
        if (GetFileAttributesA(wfd.cFileName) == -1) // file name contains some non-ANSI symbols
        {
            _tprintf(_T("%s: file name invalid.\n"), wfd.cFileName);
            continue;
        }
#endif
        if (dwEntryCount == dwMaxEntry)
        {
            dwMaxEntry += dwMaxEntry / 2;
            pMyPAZEntry = (TMyPAZEntry *)HeapReAlloc(hHeap, HEAP_ZERO_MEMORY, pMyPAZEntry, sizeof(*pMyPAZEntry) * dwMaxEntry);
            if (pMyPAZEntry == NULL)
            {
                NTSTATUS Status = GetLastError();
                _tprintf(_T("Can't reallocate memory for MyPAZEntry.\n"));
                dwEntryCount = 0;
                break;
            }
        }
        lstrcpy(pMyPAZEntry[dwEntryCount].szName, wfd.cFileName);
        ++dwEntryCount;

    } while (FindNextFile(hFind, &wfd));

    FindClose(hFind);
    *ppMyPAZEntry = pMyPAZEntry;
    return dwEntryCount;
}

Bool WINAPI IsMovie(LPCSTR lpFileName)
{
    CHAR szName[MAX_PATH];
    LPSTR lpExt;

    strcpy(szName, findname((char *)lpFileName));
    if (strlen(lpFileName) < 2)
        return False;

    lpExt = findext(szName);
    if (lpExt) *lpExt = 0;
    strlwr(szName);
    return strstr(szName, "mov") != NULL;
}

Bool WINAPI IsAudio(LPCSTR lpFileName)
{
    CHAR szName[MAX_PATH];
    LPSTR lpExt;

    strcpy(szName, findname((char *)lpFileName));
    if (strlen(szName) < 2)
        return False;

    lpExt = findext(szName);
    if (lpExt) *lpExt = 0;
    strlwr(szName);

    return strstr(szName, "voice") != NULL;
}

LPCSTR WINAPI GetCrud(LPCSTR lpExtension, TGameInfo *pGameInfo)
{
    LPCSTR lpCrud;

    if (dwInfoIndex != EF_FIRST && lpExtension)
    {
        if (!lstrcmpi(lpExtension, ".png"))
        {
            lpCrud = pGameInfo->CrudInfo.png;
        }
        else if (bIsVoice || !lstrcmpiA(lpExtension, ".ogg") || !lstrcmpiA(lpExtension, ".m4a"))
        {
            lpCrud = pGameInfo->CrudInfo.ogg;
        }
        else if (!lstrcmpi(lpExtension, ".sc"))
        {
            lpCrud = pGameInfo->CrudInfo.scr;
        }
        else if (!lstrcmpi(lpExtension, ".avi"))
        {
            lpCrud = pGameInfo->CrudInfo.avi;
        }
        else
        {
            lpCrud = NULL;
        }
    }
    else
    {
        lpCrud = NULL;
    }

    return lpCrud;
}

PAZTYPE WINAPI GetPazTypeFromFileName(LPSTR lpFileName)
{
    DWORD dwLength;
    CHAR  szName[MAX_PATH];

    lpFileName = findname(lpFileName);
    lstrcpyA(szName, lpFileName);
    lpFileName = findext(szName);
    if (lpFileName) *lpFileName = 0;
    dwLength = lstrlenA(szName);

    if (dwLength > 3 && !lstrcmpiA(szName + dwLength - 3, "_sc"))
    {
        dwLength -= 3;
        szName[dwLength] = 0;
/*
        for (int i = dwLength; i >= 0; --i)
            szName[i + 2] = szName[i];
        *(LPWORD)szName = 'mp';
*/
        return GetPazTypeFromFileName(szName);
    }

    for (int i = 0; i != countof(szType); ++i)
    {
        if (!lstrcmpiA(szName, szType[i]))
            return (PAZTYPE)i;
    }

    return NONE;
}

void __cdecl main(int argc, TCHAR **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
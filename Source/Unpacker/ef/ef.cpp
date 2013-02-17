#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")

#include "ef.h"
#include "blowfish.h"
#include "zlib/zlib.h"
#include "zlib/zconf.h"

enum EInfoIndex { EF_FIRST, EF_LATTER, EDEN, EF_FD, LAST_MODE };
enum ESpecPaz   { NORMAL, GS_FIRST, GS_LATTER, LAST_SPEC };
enum EDefault { DEFAULT_MODE = EF_LATTER };

Bool bCtrlC;
int InfoIndex;

ForceInline void main2(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage:\n"
               "   %s input.paz [0|1]\n"
               "      0 = ef\n"
               "      1 = eden* (default)\n", findname(argv[0]));
        return;
    }

    FILE *fInput, *fOutput;
    Bool  bIsMovie, bIsAudio;
    CHAR  szTitle[20];
    BYTE  SpecKey[0x20], xor[] = { 0x6D, 0x69, 0x6E, 0x6F, 0x72, 0x69, 0x58 };
    DWORD dwSimpleKey, dwEntryCount, dwKeyIndex, dwSpecMode;
    DWORD dwFileCount, dwBufferSize, dwSeedLen, dwEntrySize;
    PBYTE pbEntry, pbData, pbMovieSeed, pbSeed, pbBuffer;
    LPSTR lpExt;
    TPAZEntry *pPAZEntry;
    TGameInfo *pGameInfo;

    fInput = fopen(argv[1], "rb");
    if (fInput == NULL)
    {
        printf("Can't open \"%s\"\n", argv[1]);
        return;
    }

    InfoIndex = argc > 2 ? (argv[2][0] - '0') : DEFAULT_MODE;
    if (InfoIndex < EF_FIRST && InfoIndex >= LAST_MODE)
    {
        printf("Unknown mode \"%d\"", InfoIndex);
        return;
    }

    dwSpecMode = argc > 3 ? argv[3][0] - '0' : NORMAL;
    if (dwSpecMode < NORMAL && dwSpecMode >= LAST_SPEC)
        dwSpecMode = NORMAL;

    pGameInfo = &GameInfo[InfoIndex];
    if (dwSpecMode == GS_LATTER)
        dwKeyIndex = 0;
    else
    {
        dwKeyIndex = GetKeyIndex(argv[1], pGameInfo);
        if (dwKeyIndex == -1)
        {
            printf("%s: Unknown encryption key.\n", argv[1]);
            fclose(fInput);
            return;
        }
    }

    fseek(fInput, 0x23, SEEK_SET);
    fgetc(fInput);
    __asm
    {
        and eax, 0xFF;
        mov ah, al;
        mov edx, eax;
        shl eax, 16;
        or  eax, edx;
        mov dwSimpleKey, eax;
    }
    fseek(fInput, 32, SEEK_SET);
    fread(&dwEntrySize, 4, 1, fInput);
    dwEntrySize ^= dwSimpleKey;
    pbEntry = (PBYTE)malloc(dwEntrySize);
    ReadDecrypt(fInput, dwSimpleKey, (LPVOID)pbEntry, dwEntrySize);

    CBlowFish bf;

    if (dwSpecMode != GS_LATTER)
    {
        memcpy(SpecKey, pGameInfo->key[dwKeyIndex].IndexKey, sizeof(pGameInfo->key[dwKeyIndex].IndexKey));
        if (dwSpecMode == GS_FIRST)
        {
            for (int a = 0; a != sizeof(SpecKey); ++a)
                SpecKey[a] = -(SpecKey[a] ^ xor[a % 6]);
        }
        bf.Initialize(SpecKey, sizeof(SpecKey));
        bf.Decode(pbEntry, pbEntry, dwEntrySize);
    }
    dwEntryCount = *(LPDWORD)pbEntry;
    pbData = pbEntry + 4;

    bIsMovie = IsMovie(argv[1]);
    if (bIsMovie)
    {
        bIsAudio = False;
        pbMovieSeed = pbData;
        if (InfoIndex != EF_FIRST)
            pbData += 256;
        else
        {
            if (dwEntrySize < 0x10000)
            {
                printf("%s: Invalid\n", argv[1]);
                free(pbEntry);
                fclose(fInput);
                return;
            }
            pbData += 0x10000;
        }
    }
    else
    {
        bIsAudio = IsAudio(argv[1]);
    }

    lpExt = findexta(argv[1]);
    if (lpExt)
    {
        *lpExt = 0;
    }
    CreateDirectoryA(argv[1], NULL);
    SetCurrentDirectoryA(argv[1]);
    if (lpExt)
    {
        *lpExt = '.';
    }

    dwFileCount = 0;
    dwSeedLen = 0;
    dwBufferSize = 0;
    pbSeed   = (PBYTE)malloc(0);
    pbBuffer = (PBYTE)malloc(0);
    SetConsoleCtrlHandler(HandlerRoutine, True);
    for (DWORD i = 0; bCtrlC == False && i != dwEntryCount; ++i)
    {
        CHAR   szName[MAX_PATH], *pFileName;
        DWORD  dwSeed;
        LPSTR lpName, lpCrud;

        lpName = (LPSTR)pbData;
        lpExt  = findexta(lpName);
        strcpy(szName, lpName);

        if (bIsAudio && *lpExt == 0)
        {
            strcat(szName, ".ogg");
        }

        pbData += strlen(lpName) + 1;
        pPAZEntry = (TPAZEntry *)pbData;
        pbData += sizeof(*pPAZEntry);
        ++dwFileCount;
        if (pPAZEntry->dwDecryptSize == 0)
            continue;

        pFileName = findname(szName);
        if (pFileName != szName)
        {
            Char ch = *pFileName;
            *pFileName = 0;
            MyCreateDirectoryA(szName);
            *pFileName = ch;
        }

        fOutput = fopen(szName, "wb");
        if (fOutput == NULL)
        {
            printf("Can't create \"%s\"\n", lpName);
            continue;
        }

        dwSeed = max(pPAZEntry->dwDecryptSize, pPAZEntry->dwUncompSize);
        if (dwBufferSize < dwSeed)
        {
            dwBufferSize = dwSeed;
            pbBuffer = (PBYTE)realloc(pbBuffer, dwBufferSize);
        }

        my_fseek64(fInput, pPAZEntry->l64Offset, SEEK_SET);
        if (ReadDecrypt(fInput, dwSimpleKey, pbBuffer, pPAZEntry->dwDecryptSize) == 0)
        {
            remove(szName);
            fclose(fOutput);
            printf("Can't read \"%s\"\n", szName);
            continue;
        }

        if (InfoIndex == EF_FIRST)
            lpCrud = NULL;
        else if (dwSpecMode != GS_LATTER)
        {
            lpCrud = bIsAudio ? (/*rmext((PChar)lpName), */pGameInfo->CrudInfo.ogg) : GetCrud(lpExt, pGameInfo);

            if (lpCrud)
            {
                dwSeed = strlen(lpName) + 10 + (lpCrud ? strlen(lpCrud) : 0) + 1;
                if (dwSeed > dwSeedLen)
                {
                    dwSeedLen = dwSeed;
                    pbSeed = (PBYTE)realloc(pbSeed, dwSeedLen);
                }
                dwSeed = sprintf((char *)pbSeed, "%s %08X %s", strlwr((char *)lpName), pPAZEntry->dwCompSize, lpCrud ? lpCrud : "");
            }
        }

        if (bIsMovie)
        {
            if (strnicmp(pGameInfo->key[dwKeyIndex].lpFileName, "pm", 2) && dwSpecMode != GS_LATTER)
                DecryptMovie(pbMovieSeed, pbSeed, dwSeed, pbBuffer, pPAZEntry->dwCompSize);
        }
        else if (dwSpecMode != GS_LATTER)
        {
            memcpy(SpecKey, pGameInfo->key[dwKeyIndex].DataKey, sizeof(pGameInfo->key[dwKeyIndex].DataKey));
            if (dwSpecMode == GS_FIRST)
            {
                for (int a = 0; a != sizeof(SpecKey); ++a)
                    SpecKey[a] = -(SpecKey[a] ^ xor[a % 6]);
            }
            bf.Initialize(SpecKey, sizeof(SpecKey));
            bf.Decode(pbBuffer, pbBuffer, pPAZEntry->dwDecryptSize);

            if (lpCrud)
                Decrypt(pbSeed, dwSeed, pbBuffer, pPAZEntry->dwCompSize);

            if (pPAZEntry->bIsComp)
            {
                void *p;
                Bool bResult;
                DWORD size = dwBufferSize;

                p = malloc(pPAZEntry->dwCompSize);
                memcpy(p, pbBuffer, pPAZEntry->dwCompSize);
                bResult = uncompress(pbBuffer, &size, (Bytef *)p, pPAZEntry->dwCompSize);
                free(p);
                if (bResult != Z_OK)
                {
                    printf("Uncompress \"%s\" failed\n", szName);
                    fclose(fOutput);
                    continue;
                }
            }
        }

        printf("Writing %s ...\n", szName);
        sprintf(szTitle, "%u / %u", dwFileCount, dwEntryCount);
        SetConsoleTitleA(szTitle);
        fwrite(pbBuffer, pPAZEntry->dwUncompSize, 1, fOutput);
        fclose(fOutput);
    }

    free(pbSeed);
    free(pbBuffer);
    free(pbEntry);
    fclose(fInput);
}

Void WINAPI Decrypt(PBYTE pbSeed, DWORD dwSeedLength, PBYTE pbBuffer, DWORD dwSize)
{
    char scramble[256];
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

void WINAPI DecryptMovie(PBYTE pbMovieSeed, const PBYTE pbSeed, DWORD dwSeedLength, PBYTE pbBuffer, DWORD dwBufferSize)
{
    static const DWORD dwDictSize = 0x10000;
    BYTE dict[dwDictSize], pbRC4Table[256], pbRC4Key[256];

    if (InfoIndex != EF_FIRST)
    {
        for (unsigned long i = 0; i != 256; i++)
        {
            pbRC4Key[i] = pbMovieSeed[i] ^ pbSeed[i % dwSeedLength];
        }

        InitRC4Table(pbRC4Table, pbRC4Key);
        InitDict(dict, sizeof(dict), pbRC4Table, sizeof(pbRC4Table));

        for (unsigned long i = 0; i != dwBufferSize; i++)
        {
            pbBuffer[i] ^= dict[i % dwDictSize];
        }

        return;
    }
    else
    {
        PBYTE pbDict = dict;

        for (int i = 0; i != 256; ++i)
        {
            for (int j = 0; j != 256; ++j)
            {
                *pbDict = 0;
                for (int k = 0; k != 256; ++k)
                {
                    if (pbMovieSeed[k] == j)
                    {
                        *pbDict = k;
                        break;
                    }
                }
                ++pbDict;
            }

            pbMovieSeed += 256;
        }

        for (DWORD i = 0; i != dwBufferSize; ++i)
        {
            pbBuffer[i] = dict[pbBuffer[i] + ((i >> 8) & 0xFF00)];
        }
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

Void WINAPI InitDict(PBYTE pbDict, DWORD dwDictSize, PBYTE pbRC4Key, DWORD dwKeySize)
{
    DWORD i, j, k, l;

    i = 1;
    j = 0;
    k = 0;

    while (dwDictSize--)
    {
        k = (k + pbRC4Key[i]) & 0xFF;
        l = pbRC4Key[i] + pbRC4Key[k];
        Swap(pbRC4Key[i], pbRC4Key[k]);
        *pbDict++ = pbRC4Key[l & 0xFF];
        ++i &= 0xFF;
    }
}

DWORD WINAPI ReadDecrypt(FILE *fp, DWORD dwKey, LPVOID lpBuffer, DWORD dwSize)
{
    PBYTE pbBuffer = (PBYTE)lpBuffer;
    DWORD dwRead;

    dwRead = fread(pbBuffer, 1, dwSize, fp);
    if (dwRead && dwKey)
    {
        while (dwSize & 3)
        {
            pbBuffer[--dwSize] ^= dwKey;
        }
        dwSize /= 4;
        while (dwSize--)
        {
            ((LPDWORD)pbBuffer)[dwSize] ^= dwKey;
        }
    }

    return dwRead;
}

DWORD WINAPI GetKeyIndex(LPSTR lpFileName, TGameInfo *pGameInfo)
{
    CHAR  szName[MAX_PATH];
    LPSTR lpPrefix;
    DWORD dwLength, dwLength2;

    strcpy(szName, findname(lpFileName));
    lpPrefix = findexta(szName);
    if (lpPrefix) *lpPrefix = 0;
    dwLength = strlen(szName);

    if (dwLength > 3 && (!stricmp(szName + dwLength - 3, "_cn") || !stricmp(szName + dwLength - 3, "_sc")))
    {
        dwLength -= 3;
        szName[dwLength] = 0;

        return GetKeyIndex(szName, pGameInfo);
    }

    for (DWORD i = 0; pGameInfo->key[i].lpFileName; ++i)
    {
        lpPrefix = pGameInfo->key[i].lpFileName;
        dwLength2 = strlen(lpPrefix);
        if (!strnicmp(szName, lpPrefix, max(dwLength2, dwLength)))
            return i;
    }

    return -1;
}

Bool WINAPI IsMovie(LPCSTR lpFileName)
{
    CHAR szName[MAX_PATH];
    LPSTR lpExt;

    strcpy(szName, findname((char *)lpFileName));
    if (strlen(lpFileName) < 2)
        return False;

    lpExt = findexta(szName);
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

    lpExt = findexta(szName);
    if (lpExt) *lpExt = 0;
    strlwr(szName);

    return strstr(szName, "voice") != NULL;
}

LPSTR WINAPI GetCrud(LPCSTR lpExtension, TGameInfo *pGameInfo)
{
    LPSTR lpCrud;

    if (InfoIndex != EF_FIRST && lpExtension)
    {
        if (!stricmp(lpExtension, ".png"))
        {
            lpCrud = pGameInfo->CrudInfo.png;
        }
        else if (!stricmp(lpExtension, ".ogg") || !stricmp(lpExtension, ".m4a") || !stricmp(lpExtension, ".uca"))
        {
            lpCrud = pGameInfo->CrudInfo.ogg;
        }
        else if (!stricmp(lpExtension, ".sc"))
        {
            lpCrud = pGameInfo->CrudInfo.scr;
        }
        else if (!stricmp(lpExtension, ".avi"))
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

Bool CALLBACK HandlerRoutine(DWORD dwCtrlType)
{
    switch(dwCtrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        bCtrlC = 1;
        return TRUE;
    }
    return False;
}

void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
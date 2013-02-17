#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")

#include "ef.h"
#include "my_image.h"

ForceInline void main2(int argc, char **argv)
{
	if (argc < 2)
    {
        return;
    }

    FILE *fInput, *fOutput;
    PBYTE pbBuffer;
    DWORD dwBufferSize, dwEntryCount, dwPrefixLen, dwFileSize;
    DWORD dwOffsetX, dwOffsetY;
    int   w, h, b, stride;
    CHAR  *p1, *p2, szName[MAX_PATH], szPath[MAX_PATH];
    TMyANIEntry Entry;
    TANIHeader header = {0x100, 4, 0};
    intptr_t hfind;
    __finddata64_t finddata;

    dwBufferSize = 0;
    pbBuffer = (PBYTE)malloc(dwBufferSize);
    for (int i = 1; i != argc; ++i)
    {
        p1 = findname(argv[i]);
        if (p1) *--p1 = 0;
        strcpy(szPath, argv[i]);
        if (p1) *p1 = '\\';
        p1 = findext(argv[i]);
        if (p1) *p1 = 0;

        sprintf(szName, "%s.uni", argv[i]);
        fOutput = fopen(szName, "wb");
        if (fOutput == NULL)
        {
            printf("Can't create \"%s\"\n", szName);
            continue;
        }

        sprintf(szName, "%s\\%s_????_*_????_????.uci", szPath, findname(argv[i]));
        hfind = _findfirst64(szName, &finddata);
        if (hfind == -1)
        {
            printf("Can't find \"%s\"\n", szName);
            fclose(fOutput);
            continue;
        }

        fwrite(&header, sizeof(header), 1, fOutput);
        dwPrefixLen  = strlen(findname(argv[i])) + 1;
        dwEntryCount = 0;
        do
        {
            sprintf(szName, "%s\\%s", szPath, finddata.name);
            p1 = strchr(&(findname(szName)[dwPrefixLen]), '_');
            if (p1 == NULL)
                continue;

            p2 = strchr(++p1, '_');
            if (p2 == NULL)
                continue;

            strncpy(Entry.szName, p1, p2 - p1);
            Entry.szName[p2 - p1] = 0;
            ++p2;
            if (sscanf(p2, "%04X_%04X", &dwOffsetX, &dwOffsetY) != 2)
                continue;

            fInput = fopen(szName, "rb");
            dwFileSize = fsize(fInput);
            if (dwFileSize >= dwBufferSize)
            {
                dwBufferSize = dwFileSize;
                pbBuffer = (PBYTE)realloc(pbBuffer, dwBufferSize);
            }

            fread(pbBuffer, dwFileSize, 1, fInput);
            fclose(fInput);
            if (UCIDecode(pbBuffer, dwFileSize, NULL, &stride, &w, &h, &b) < 0)
                continue;

            Entry.wWidth = w;
            Entry.wHeight = h;
            Entry.wBPP = 32;
            Entry.wOffsetX = (WORD)dwOffsetX;
            Entry.wOffsetY = (WORD)dwOffsetY;
            fwrite(Entry.szName, strlen(Entry.szName) + 1, 1, fOutput);
            fwrite((PBYTE)Entry.szName + sizeof(Entry.szName), sizeof(Entry) - sizeof(Entry.szName), 1, fOutput);
            fwrite(pbBuffer, dwFileSize, 1, fOutput);

            ++dwEntryCount;
        } while (!_findnext64(hfind, &finddata));
        
        _findclose(hfind);
        fseek(fOutput, 2, SEEK_SET);
        fwrite(&dwEntryCount, 2, 1, fOutput);
        fclose(fOutput);
    }

    free(pbBuffer);
}

void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
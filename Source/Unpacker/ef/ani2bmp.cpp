#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")

#include "ef.h"
#include "MyLibraryUser.cpp"

ForceInline void main2(int argc, char **argv)
{    
    if (argc < 2)
    {
        printf("%s input.ani\n", findname(argv[0]));
        return;
    }

    FILE *fInput, *fOutput;
    PBYTE pbBuffer, pbData;
    DWORD dwBufferSize, dwFileSize;
    CHAR  *lpName, *lpExt, szName[MAX_PATH];
    TANIHeader   *aniheader;
    TANIEntry    *pEntry;
    IMAGE_BITMAP_HEADER h;

    InitBitmapHeader(&h, 0, 0, 32, NULL);

    dwBufferSize = 0;
    pbBuffer = (PBYTE)malloc(dwBufferSize);
    for (int i = 1; i != argc; ++i)
    {
        fInput = fopen(argv[i], "rb");
        if (fInput == NULL)
        {
            printf("Can't open \"%s\"\n", argv[i]);
            continue;
        }

        dwFileSize = fsize(fInput);
        if (dwFileSize >= dwBufferSize)
        {
            dwBufferSize = dwFileSize;
            pbBuffer = (PBYTE)realloc(pbBuffer, dwBufferSize);
        }
        fread(pbBuffer, dwFileSize, 1, fInput);
        fclose(fInput);

        pbData = pbBuffer;
        aniheader = (TANIHeader *)pbData;
        pbData += sizeof(*aniheader);
        for (int j = 0; j != aniheader->usEntryCount; ++j)
        {
            lpName = (CHAR *)pbData;
            pbData += strlen(lpName) + 1;
            pEntry = (TANIEntry *)pbData;
            pbData += sizeof(*pEntry);
            h.FileSize = (pEntry->wWidth * pEntry->wBPP / 8 + 
                (pEntry->wBPP == 24 ? (pEntry->wWidth & 3) : 0)) * pEntry->wHeight + 
                sizeof(h);
            h.Info.Height = pEntry->wHeight;
            h.Info.Width  = pEntry->wWidth;
            h.Info.Bit     = pEntry->wBPP;
            lpExt = findext(argv[i]);
            if (lpExt) *lpExt = 0;
            sprintf(szName, "%s_%04X_%s_%04X_%04X.bmp", argv[i], j, lpName, pEntry->wOffsetX, pEntry->wOffsetY);
            if (lpExt) *lpExt = '.';
            fOutput = fopen(szName, "wb");
            fwrite(&h, sizeof(h), 1, fOutput);
            pbData += fwrite(pbData, 1, h.FileSize - sizeof(h), fOutput);
            fclose(fOutput);
        }
    }
}

void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
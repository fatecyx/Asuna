#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")

#include <dsound.h>
#include "crt_h.h"
#include "my_mem.h"

NoInline int my_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\n' && str[i] != '\r' && str[i])
        ++i;
    return i;
}

void Export(char *pFileName, char *pText, int offset_begin, int block_size)
{
    FILE *fp;
    int  iFileSize;
    char *p, *src, *end, szOutput[MAX_PATH];

    if (offset_begin == 0 && block_size == 0)
    {
        printf("Please input a valid offset and block size\n");
        return;
    }

    fp = fopen(pFileName, "rb");
    if (fp == NULL)
    {
        perror(pFileName);
        return;
    }

    iFileSize = fsize(fp);
    if (iFileSize < offset_begin)
    {
        printf("File size %d less than begin offset %d\n", iFileSize, block_size);
        fclose(fp);
        return;
    }
    else if (block_size + offset_begin > iFileSize)
    {
        printf("block too large\n");
        fclose(fp);
        return;
    }

    src = (char *)malloc(iFileSize);
    fread(src, iFileSize, 1, fp);
    fclose(fp);

    p = findext(pFileName);
    if (p) *p = 0;
    sprintf(szOutput, "%s.txt", pFileName);
    fp = fopen(szOutput, "wb");
    if (fp == NULL)
    {
        free(src);
        printf("Can't open \"%s\"\n", szOutput);
        return;
    }

    p = src + offset_begin;
    end = p + block_size;
    while (p < end)
    {
        if (*p == NULL)
        {
            ++p;
            continue;
        }

        fprintf(fp, "==================================================%X\n", p - src);
        fprintf(fp, "%s\n", p);
        fprintf(fp, "--------------------------------------\n\n");

        p += strlen(p) + 1;
    }

    free(src);
    fclose(fp);
}

void Import(char *pFileName, char *pText)
{
    HANDLE hFile;
    FILE *fp, *fText;
    int iTextSize, offset, srclen, dstlen;
    char *p, *pSrc, *pDst, *pEnd, buf[0x400];

    hFile = CreateFileA(pFileName,
                    GENERIC_READ|GENERIC_WRITE,
                    FILE_SHARE_READ|FILE_SHARE_WRITE,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("Can't open \"%s\"\n", pFileName);
        return;
    }

    fText = fopen(pText, "rb");
    if (fText == NULL)
    {
        CloseHandle(hFile);
        printf("Can't open \"%s\"\n", pFileName);
        return;
    }

    iTextSize = fsize(fText);
    pText = (char *)malloc(iTextSize);
    fread(pText, iTextSize, 1, fText);
    fclose(fText);

    p = pText;
    pEnd = pText + iTextSize;
    while (p <= pEnd)
    {
        char c;
        if (*p == '=')
        {
            ++p;
            continue;
        }

        if (sscanf(p, "%X", &offset) != 1)
        {
            int i = my_strlen(p);
            strncpy(buf, p, i);
            buf[i] = 0;
            printf("Invalid offset \"%s\"\n", buf);
            while (*p++ != '\n' && p <= pEnd);
            continue;
        }

        while (*p++ != '\n' && p <= pEnd);
        pSrc = p;
        while (*p++ != '\n' && p <= pEnd);
        while (*p++ != '\n' && p <= pEnd);
        pDst = p;
        while (*p++ != '\n' && p <= pEnd);
        if (p > pEnd)
            break;

        srclen = my_strlen(pSrc);
        dstlen = my_strlen(pDst);
        if (dstlen > srclen)
        {
            printf("%X: Dest string length %d is longer than source length %d.\n", offset, srclen, dstlen);
            continue;
        }

        SetFilePointer(hFile, offset - 1, NULL, FILE_BEGIN);
        ReadFile(hFile, &c, 1, (LPDWORD)&iTextSize, NULL);
        if (c != 0)
        {
            printf("%X: may not be the begin of the string, check it manually.\n", offset);
            continue;
        }

        if (dstlen == 0)
        {
            printf("%X: empty, skip ...\n", offset);
            continue;
        }

        strncpy(buf, pDst, dstlen);
        buf[dstlen] = 0;
        while (dstlen != srclen)
        {
            buf[++dstlen] = 0;
        }

        WriteFile(hFile, buf, dstlen, (LPDWORD)&iTextSize, NULL);

        ++p;
    }

    CloseHandle(hFile);
    free(pText);
}

ForceInline void main2(int argc, char **argv)
{
    int  iOffsetBegin, iBlockSize, param;
    char *pInput, *pOutput, *pText;

    pInput = NULL;
    pText = NULL;
    pOutput = NULL;
    iOffsetBegin = 0;
    iBlockSize = 0;

    for (int i = 1; i < argc; ++i)
    {
        param = 0;
        strlwr(argv[i]);

        if (argv[i][0] != '-')
        {
            printf("Invalid option \"%s\" \n", argv[i]);
            continue;
        }

        for (int j = 1; argv[i][j]; ++j)
        {
            param = (param << 8)|argv[i][j];
        }

        switch (param)
        {
        case 'o':
            if (++i < argc) pOutput = argv[i];
            break;

        case 'i':
            if (++i < argc) pInput = argv[i];
            break;

        case 't':
            if (++i < argc) pText = argv[i];
            break;

        case 'b':
            if (++i < argc) sscanf(argv[i], "%X", &iOffsetBegin);
            break;

        case 's':
            if (++i < argc) sscanf(argv[i], "%X", &iBlockSize);
            break;
        }
    }

    if (pInput && pOutput)
    {
        printf("Please only specify only one mode, export or import.\n");
        return;
    }

    if (pInput)
    {
        Import(pInput, pText);
        return;
    }
    else if (pOutput)
    {
        Export(pOutput, pText, iOffsetBegin, iBlockSize);
        return;
    }

    return;
}

void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
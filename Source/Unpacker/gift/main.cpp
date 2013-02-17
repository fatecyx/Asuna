#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")
#pragma comment(lib, "ntdll.lib")

#include <Windows.h>
#include "zlib/zlib.h"
#include "my_api.h"
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"
#include "gift.h"
#include "FileDisk.h"

Bool bCtrlC;

BOOL CALLBACK HandlerRoutine(DWORD dwCtrlType)
{
    switch(dwCtrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        bCtrlC = True;
        return True;
    }
    return False;
}

ForceInline Void main2(Int argc, WChar **argv)
{
    FILE *fp;
    UInt32 IndexSize, BufferSize;
    LPVoid lpBuffer;
    WChar  *pFileName, szFileName[MAX_PATH];
    SGiftPakHeader header;
    SGiftPakIndex *pIndex, *index;

    fp = NULL;
    pIndex = NULL;
    BufferSize = 0x10000;
    lpBuffer = malloc(BufferSize);
    SetConsoleCtrlHandler(HandlerRoutine, True);
    for (Int i = 1; i != argc && !bCtrlC; ++i)
    {
        if (fp)
        {
            fclose(fp);
            fp = NULL;
        }

        if (pIndex)
        {
            free(pIndex);
            pIndex = NULL;
        }

        fp = _wfopen(*++argv, L"rb");
        if (!fp)
        {
            _wperror(*argv);
            continue;
        }

        fread(&header, sizeof(header), 1, fp);
        if (memcmp(header.magic, "DATA$TOP", sizeof(header.magic)))
        {
            wprintf(L"%s: Invalid gift pak file", *argv);
            continue;
        }

        IndexSize = --header.FileNum * sizeof(*pIndex);
        pIndex = (SGiftPakIndex *)malloc(IndexSize);
        if (pIndex == NULL)
        {
            _wperror(*argv);
            continue;
        }

        wcscpy(szFileName, *argv);
        pFileName = findextw(szFileName);
        if (pFileName)
            *pFileName++ = '\\';
        else
            pFileName = szFileName + wcslen(szFileName);

        index = pIndex;
        fread(pIndex, IndexSize, 1, fp);
        IndexSize += sizeof(header);
        for (UInt32 j = 0; j != header.FileNum && !bCtrlC; ++j, ++index)
        {
            printf("Extracting \"%s\" ...\n", index->name);
            if (index->size > BufferSize)
            {
                BufferSize = index->size;
                lpBuffer = realloc(lpBuffer, BufferSize);
            }

//            fseek(fp, index->offset + 0x1F400, SEEK_SET);
            fseek(fp, index->offset + IndexSize, SEEK_SET);
            fread(lpBuffer, index->size, 1, fp);

            sprintf((PChar)pFileName, "%u / %u", j + 1, header.FileNum);
            SetConsoleTitleA((PChar)pFileName);

            FILE *fOut;
            PWChar pName;
            UNICODE_STRING u;

            CFileDisk::AnsiToUnicode(&u, index->name, pFileName, countof(szFileName) - (pFileName - szFileName));

            pName = findnamew(szFileName);
            if (pName) *--pName = 0;
            MyCreateDirectoryW(szFileName);
            if (pName) *pName = '\\';
            fOut = _wfopen(szFileName, L"wb");
            if (fOut)
            {
                fwrite(lpBuffer, index->size, 1, fOut);
                fclose(fOut);
            }
        }
    }

    free(lpBuffer);
    if (fp) fclose(fp);
    if (pIndex) free(pIndex);

    if (bCtrlC)
    {
        printf("user abort\n");
        getch();
    }
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
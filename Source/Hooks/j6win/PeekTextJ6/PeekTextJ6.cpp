#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "gal_common.h"
#include "sha2.h"

typedef struct
{
    UInt16 OPCode;
    UInt16 Legnth;
    Byte   Data;
} SJ6OPHeader;

#define EXP { PrintException(pbScript - pbBuffer, pszFileName); break; }

NoInline Void PrintException(UInt32 Offset, PWChar pszFileName)
{
    printf("%ws: Found unknown code at %08X\n", pszFileName, Offset);
    getch();
}

Bool IsAnsi(PCChar p, UInt32 len)
{
    for (UInt32 i = 0; i != len; ++p, ++i)
    {
        if (*p < 0)
            return False;
        if (*p == 0)
            break;
    }

    return True;
}

NoInline PByte Execute(PByte pbScript, PByte pbEnd)
{
    Byte  param;

    while (pbScript < pbEnd)
    {
        param = *pbScript++;

        if (param > 0x9B)
            continue;
        if (param == 0)
            break;
        if (param == 1 || param == 2)
            pbScript += 4;
    }

    return pbScript;
}

UInt32 PeekText(PWChar pszFileName)
{
    PByte     pbScript, pbBuffer, pbEnd;
    UInt32    ScriptSize, Header, LinePeeked;
    WChar     szTextFile[MAX_PATH], szText[0x1000], szBuffer[0x2000];
    CFileDisk file;
    CMem      mem;
    SJ6OPHeader *pOPCode;

    if (!file.Open(pszFileName))
        return 0;

    ScriptSize = file.GetSize();
    pbBuffer = (PByte)mem.Alloc(ScriptSize);
    if (pbBuffer == NULL)
        return 0;

    if (!file.Read(pbBuffer))
    {
        mem.Free(pbBuffer);
        return 0;
    }

    lstrcpyW(szTextFile, pszFileName);
    lstrcpyW(findextw(szTextFile), L".txt");

    if (!file.Open(szTextFile, file.FILE_ACCESS_WRITE, file.FILE_SHAREMODE_READ, file.FILE_CREATE_ALWAYS))
    {
        mem.Free(pbBuffer);
        return 0;
    }

    pbScript   = pbBuffer;
    pbEnd      = pbBuffer + ScriptSize;
    LinePeeked = 0;

    Header = 0xFEFF;
    file.Write(&Header, 2);
    Header = swprintf(szBuffer, L";%s\n", findnamew(pszFileName));
    file.Write(szBuffer, Header * 2);

    while (pbScript < pbEnd)
    {
        PByte pbTemp = pbScript;

        pOPCode = (SJ6OPHeader *)pbScript;

        if (pOPCode->OPCode == 0x21A && 0)
        {
            pbTemp = pbBuffer + *(PUInt32)&pOPCode->Data;
            if (pbTemp < pbEnd)
            {
                pbScript = pbTemp;
                continue;
            }
        }
        else
        {
            PByte pbOPEnd = pbScript + pOPCode->Legnth;

            pbTemp = &pOPCode->Data;
            switch (pOPCode->OPCode)
            {
                default:
                    goto UNKNOWN_CODE;

                case 0xD:   // ¡¸
                case 0x15:
                    pbTemp = Execute(pbTemp, pbOPEnd);
                    break;

                case 0x1F:
                case 0x21:
                    for (UInt32 i = 4; i-- ;)
                        pbTemp = Execute(pbTemp, pbOPEnd);
                    break;

                case 0xE1:
                    switch (*pbTemp++)
                    {
                        default:
                            goto UNKNOWN_CODE;

                        case 0x22:
                        case 0x32:
                            pbTemp = Execute(pbTemp, pbOPEnd);
                            break;

                        case 0x3A:
                            pbTemp = Execute(pbTemp, pbOPEnd);
                            pbTemp = Execute(pbTemp, pbOPEnd);
                            break;

                        case 0x3D:
                            pbTemp = Execute(pbTemp, pbOPEnd);
                            pbTemp = Execute(pbTemp, pbOPEnd);
                            pbTemp = Execute(pbTemp, pbOPEnd);
                            break;
                    }
                    break;

                case 0xE7:
                    switch (*pbTemp++)
                    {
                        default:
                            goto UNKNOWN_CODE;

                        case 0:
                            pbTemp = Execute(pbTemp, pbOPEnd);
                            break;

                        case 4:
                        case 5:
                            for (UInt32 i = 6; i-- ;)
                                pbTemp = Execute(pbTemp, pbOPEnd);

                            break;

                        case 0xC:
                            pbTemp = Execute(pbTemp, pbOPEnd);
                            pbTemp = Execute(pbTemp, pbOPEnd);
                            break;

                        case 0xD:
                            break;
                    }

                    break;

                case 0x237:
                case 0x465:
                case 0x488:
                    pbTemp = Execute(pbTemp, pbOPEnd);
                    pbTemp = Execute(pbTemp, pbOPEnd);
                    break;
            }

            if (pbTemp > pbEnd)
                break;

            if (!IsAnsi((PCChar)pbTemp, -1))
            {
                UInt32 Hash[8];

                Header = MultiByteToWideChar(CP_SHIFTJIS, 0, (PChar)pbTemp, -1, szText, countof(szText));
                if (pbTemp - 0x50 < pbBuffer)
                {
                    printf("fuck\n");
                    getch();
                }

                sha256(pbTemp - 0x50, StrLenA((PChar)pbTemp) + 0x50, (PByte)Hash);

                Header = swprintf(
                    szBuffer,
                    L"============================================================%X,%X,%08X%08X%08X%08X%08X%08X%08X%08X\r\n"
                    L"%s\r\n"
                    L"----------------------------------------------------------------------------------\r\n"
                    L"%s\r\n",

                    pOPCode->OPCode, pbScript - pbBuffer,
                    Bswap(Hash[0]), Bswap(Hash[1]), Bswap(Hash[2]), Bswap(Hash[3]),
                    Bswap(Hash[4]), Bswap(Hash[5]), Bswap(Hash[6]), Bswap(Hash[7]),
                    szText,
                    szText
                    );

                file.Write(szBuffer, Header * 2);
                ++LinePeeked;
            }
        }

UNKNOWN_CODE:

        pbScript += pOPCode->Legnth;
    }

    mem.Free(pbBuffer);
    file.Close();

    if (LinePeeked == 0)
        DeleteFileW(szTextFile);

    return LinePeeked;
}

Int32 STDCALL EnumFilesCallback(PVoid pvBuffer, LPWIN32_FIND_DATAW pFindData, PVoid pvParam)
{
    lstrcpyW((PWChar)pvBuffer, pFindData->cFileName);
    return 1;
}

ForceInline Void main2(Int argc, WChar **argv)
{
    _wsetlocale(LC_CTYPE, L"");

    while (--argc)
    {
        UInt32 Lines;
        PWChar pszPath = *++argv;

        printf("Processing \"%ws\" ... ", pszPath);

        Lines = 0;
        if (GetFileAttributesW(pszPath) & FILE_ATTRIBUTE_DIRECTORY)
        {
            WChar (*szFiles)[MAX_PATH];
            Large_Integer FileCount;

            if (EnumDirectoryFiles(
                (PVoid *)&szFiles,
                L"*.SO4",
                sizeof(*szFiles),
                pszPath,
                &FileCount,
                EnumFilesCallback,
                NULL,
                0))
            {
                while (FileCount.LowPart--)
                    Lines += PeekText(szFiles[FileCount.LowPart]);

                EnumDirectoryFilesFree(szFiles);
            }
        }
        else
        {
            Lines = PeekText(pszPath);
        }

        printf("%d line%c\n", Lines, Lines > 1 ? 's' : 0);
    }

    Sleep(500);
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
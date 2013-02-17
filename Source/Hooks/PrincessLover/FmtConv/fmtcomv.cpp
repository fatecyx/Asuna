#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "gal_common.h"
#include "Mem.cpp"

Bool PeekLine(LPVoid lpBuffer, LPVoid lpEndOfBuffer, LPVoid lpOutBuffer, PInt32 pcbOutBuffer)
{
    if (lpBuffer == NULL)
        return False;

    WChar  ch;
    PWChar pStart, pEnd, pOutput;
    Int32  BufferSize;

    if (pcbOutBuffer)
    {
        BufferSize = *pcbOutBuffer;
        *pcbOutBuffer = 0;
    }

    pStart = (PWChar)lpBuffer;
    pEnd   = lpEndOfBuffer ? (PWChar)lpEndOfBuffer : pStart + StrLengthW(pStart);

    if (pStart >= pEnd)
        return False;

    pOutput = (PWChar)lpOutBuffer;
    while (pStart < pEnd)
    {
        ch = *pStart++;
        if (pOutput)
        {
            if (BufferSize > 0)
            {
                *pOutput++ = ch;
                BufferSize -= 2;
            }
            else
                break;
        }

        if (ch == '\n')
            break;
    }

    if (pOutput && BufferSize > 0)
        *pOutput = 0;

    if (pcbOutBuffer)
        *pcbOutBuffer = (PByte)pOutput - (PByte)lpOutBuffer;

    return True;
}

Bool IsCommandSentance(WChar ch)
{
    switch (ch)
    {
        case '@':
        case '/':
        case '\\':
        case '^':
        case '\r':
        case '\n':
        case 0:
            return True;
    }

    return False;
}

Void ReplaceMark(PWChar pLine, PWChar pSrc)
{
    WChar  ch;
    PWChar p, pBracket, pComma;

    pComma   = NULL;
    pBracket = NULL;
    p = pLine;
    while (ch = *p++)
    {
        switch (ch)
        {
            case L'£¬':
                if (pComma == NULL)
                    pComma = p - 1;
                break;

            case L'¡¸':
                if (pBracket == NULL)
                    pBracket = p - 1;
                break;

            case L'¨D':     // 0x2015
                *(p - 1) = L'¡ª';   // 0x2014
                break;

            case 0x30FB:
                *(p - 1) = L'¡¤';
                break;
        }
    }

    if (pBracket && pComma && pComma < pBracket)
        *pComma = L',';

    p = pLine + StrLengthW(pLine) - 1;
    if ((ch = *p) != L'¡¹')
    {
        switch (ch)
        {
            case L'£¿':
            case L'?':
            case L'.':
            case L'¡£':
            case L'¡­':
            case L'¡«':
            case L'¨D':     // 0x2015
            case L'¡ª':     // 0x2014
                return;
        }

        *++p = *(pSrc + StrLengthW(pSrc) - 1);
        *++p = 0;
    }
}

Bool ProcessFile(LPVoid lpBuffer, LPVoid lpEndOfBuffer, PWChar pszFileName)
{
    FILE  *fp;
    Int32  RecvSize, LineNum;
    WChar  ch, line1[0x500], line2[0x500], path[MAX_PATH];
    PWChar pBuffer, pEnd, p1, p2, p;

    pBuffer = (PWChar)lpBuffer;
    pEnd = (PWChar)lpEndOfBuffer;

    if (pBuffer >= pEnd)
        return False;

    wcscpy(path, pszFileName);
    wcscat(path, L".txt");
    fp = _wfopen(path, L"wb");
    if (!fp)
        fp = stdout;
    else
    {
        UInt16 bom = 0xFEFF;
        fwrite(&bom, 2, 1, fp);
    }

    LineNum = 0;
    while (pBuffer < pEnd)
    {
        RecvSize = sizeof(line1);
        if (++LineNum, PeekLine(pBuffer, pEnd, line1, &RecvSize) == False)
            break;

        if (RecvSize == 0)
            break;

        RecvSize /= 2;
        pBuffer += RecvSize;
        while (RecvSize > 0 && (ch = line1[--RecvSize]))
        {
            if (ch != '\r' && ch != '\n')
                break;
            line1[RecvSize] = 0;
        }

        p1 = line1;
        while (*p1 == ' ' || *p1 == '\t' || *p1 == L'¡¡')
            ++p1;

        if (IsCommandSentance(*p1))
        {
            if (fp != stdout)
            {
                FilterString(line1, -1);
                fwprintf(fp, L"%s\n", line1);
            }
            continue;
        }

        if (!wcsncmp(line1, L"op01YOU064", 10))
            __asm nop;
        RecvSize = sizeof(line2);
        if (++LineNum, PeekLine(pBuffer, pEnd, line2, &RecvSize) == False)
            break;

        if (RecvSize == 0)
            break;

        RecvSize /= 2;
        pBuffer += RecvSize;
        while (RecvSize > 0 && (ch = line2[--RecvSize]))
        {
            if (ch != '\r' && ch != '\n')
                break;
            line2[RecvSize] = 0;
        }

        p2 = line2;
        while (*p2 == ' ' || *p2 == '\t' || *p2 == L'¡¡')
            ++p2;

        if (IsCommandSentance(*p2))
        {
            PWChar pline = line2;

//            if (line2[0] == 0)
            {
                FilterString(line1, -1);
                fwprintf(fp, L"%s\n", line1);
                wprintf(L"%s\nformat corrupt at %u line\n\n", pszFileName, LineNum);
                getch();
            }

            if (fp != stdout)
            {
                FilterString(line2, -1);
                fwprintf(fp, L"%s\n", line2);
            }

            continue;
        }

        p1 = line1;
        p2 = line2;

        p = wcschr(p1, ',');
        if (p)
            p1 = p + 1;

        while (*p1 == ' ' || *p1 == '\t' || *p1 == L'¡¡')
            ++p1;

        while (*p2 == ' ' || *p2 == '\t' || *p2 == L'¡¡')
            ++p2;

        ReplaceMark(p2, p1);
        if (fp == stdout)
            fwprintf(fp, L"%s\n%s\n\n", p1, p2);
        else
        {
            *p1 = 0;
            fwprintf(fp, L"%s%s\n\n", line1, p2);
        }
    }

    fclose(fp);

    return True;
}

typedef struct
{
    WChar FullPath[MAX_PATH];
} SFullPath;

typedef MyLib::Vector<SFullPath> VectorPath;

LONG STDCALL CallBack(LPVoid lpBuffer, LPWIN32_FIND_DATAW pFindData, ULONG_PTR lpParam)
{
    PWChar pszExtension;
    VectorPath *pFiles = (VectorPath *)lpParam;
//    static WChar *suffix[] = { L".s", L".dat", L".txt" };
    static WChar *suffix[] = { L".lua", L".cgm", L".ks", L".tjs", L".ep", L".mev", L".dic", L".tim", L".asd" };

    pszExtension = findextw(pFindData->cFileName);
    for (Int32 i = 0; i != countof(suffix); ++i)
    {
        if (!StrICompareW(pszExtension, suffix[i]))
        {
            (*pFiles).push_back(*(SFullPath *)&pFindData->cFileName);
            break;
        }
    }

    return 0;
}

Void ConvertScriptToUnicode(Int argc, WChar **argv)
{
    if (argc-- == 1)
        return;
    
    VectorPath files;

    do
    {
        EnumDirectoryFiles(
            NULL,
            L"*.*",
            0,
            *++argv,
            NULL,
            CallBack,
            (ULONG_PTR)&files,
            ENUM_DIRECTORY_FILES_FLAG_ENUMSUBDIR);

    } while (--argc);

    if (files.size() == 0)
        return;

    FILE *fp;
    CMem mem;
    Bool  bUseDefaultChar;
    PVoid pvBuffer, pvOutBuffer;
    SizeT BufferSize, OutBufferSize, FileSize;
    PWChar pCharMap;
    SFullPath *pPath;

    _wsetlocale(LC_CTYPE, L"");

    BufferSize            = 0x10000;
    OutBufferSize         = BufferSize;
    pvBuffer              = mem.Alloc(BufferSize);
    pvOutBuffer           = mem.Alloc(OutBufferSize);
    *(PUInt16)pvOutBuffer = BOM_UTF16_LE;

    pCharMap = CreateCharMapW(0, 0);
    pCharMap[0x266A] = 0;
    pPath = &files[0];

    for (SizeT i = files.size(); i; --i, ++pPath)
    {
        fp = _wfopen(pPath->FullPath, L"rb+");
        if (fp == NULL)
            continue;

        FileSize = 0;
        fread(&FileSize, 2, 1, fp);
        if (FileSize == BOM_UTF16_LE)
        {
            fclose(fp);
            continue;
        }

        fseek(fp, SEEK_SET, 0);
        FileSize = fsize(fp);
        if (FileSize == 0)
        {
            fclose(fp);
            continue;
        }

        if (FileSize > BufferSize)
        {
            BufferSize = FileSize;
            pvBuffer = mem.ReAlloc(pvBuffer, BufferSize);
        }
        if (FileSize * 2 + 2 > OutBufferSize)
        {
            OutBufferSize = FileSize * 2 + 2;
            pvOutBuffer = mem.ReAlloc(pvOutBuffer, OutBufferSize);
            *(PUInt16)pvOutBuffer = BOM_UTF16_LE;
        }

        fread(pvBuffer, FileSize, 1, fp);
        if (*(PUInt16)pvBuffer == BOM_UTF16_LE)
        {
            fclose(fp);
            continue;
        }

        FileSize = MultiByteToWideChar(
                       CP_SHIFTJIS,
                       0,
                       (LPSTR)pvBuffer,
                       FileSize,
                       (LPWSTR)pvOutBuffer + 1,
                       OutBufferSize - 2);

        FilterStringWithConvertTable((PWChar)pvOutBuffer + 1, FileSize, pCharMap);

        FileSize = WideCharToMultiByte(
            CP_GB2312,
            0,
            (LPWSTR)pvOutBuffer + 1,
            FileSize,
            (LPSTR)pvOutBuffer,
            FileSize * 2,
            NULL,
            &bUseDefaultChar
        );

        if (bUseDefaultChar)
        {
            printf("%ws\n", pPath->FullPath);
            getch();
        }

        fseek(fp, 0, SEEK_SET);
        fwrite(pvOutBuffer, FileSize, 1, fp);
        fclose(fp);
    }

    FreeCharMap(pCharMap);
    mem.Free(pvBuffer);
    mem.Free(pvOutBuffer);
}

ForceInline Void main2(Int argc, WChar **argv)
{
    FILE *fp;
    LPVoid lpBuffer, lpEndOfBuffer;
    UInt32 BufferSize, FileSize;

    ConvertScriptToUnicode(argc, argv);
    return;

    BufferSize = 0x1000;
    lpBuffer = malloc(BufferSize);
    _wsetlocale(LC_CTYPE, L"");
    for (Int32 i = 1; i != argc; ++i)
    {
        fp = _wfopen(*++argv, L"rb+");
        if (!fp)
        {
            _wperror(*argv);
            continue;
        }

        FileSize = fsize(fp);
        if (FileSize > BufferSize)
        {
            BufferSize = FileSize;
            lpBuffer = realloc(lpBuffer, BufferSize);
        }

        fread(lpBuffer, FileSize, 1, fp);
        fclose(fp);
        if (*(PUInt16)lpBuffer != 0xFEFF)
        {
            wprintf(L"%s\nsupport unicode only\n\n", *argv);
            fclose(fp);
            continue;
        }

        lpEndOfBuffer = (PByte)lpBuffer + FileSize;
        ProcessFile((PByte)lpBuffer + 2, lpEndOfBuffer, *argv);
    }

    free(lpBuffer);
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
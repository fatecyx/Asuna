#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"

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
    if (*pStart == BOM_UTF16_LE)
        ++pStart;

    while (pStart < pEnd)
    {
        ch = *pStart++;
        if (pOutput)
        {
            if (BufferSize > 0 && ch != '\n' && ch != '\r')
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

WChar FilterChar(WChar ch)
{
    switch (ch)
    {
        case 0x30FB: return L'¡¤';
    }

    return ch;
}

UInt32 FilterString(PWChar pszString, UInt32 Length)
{
    WChar  ch;
    UInt32 i;

    for (i = 0; i != Length; ++i)
    {
        ch = *pszString;
        BREAK_IF(ch == 0);
        *pszString = FilterChar(ch);
        ++pszString;
    }

    return i;
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

Bool ProcessFile(LPVoid lpBuffer, LPVoid lpEndOfBuffer, PWChar pszFileName)
{
    FILE  *fp;
    Int32  RecvSize, LineNum;
    WChar  ch, line1[0x500], path[MAX_PATH];
    PWChar pBuffer, pEnd, p1;

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
        ++LineNum;
        if (!PeekLine(pBuffer, pEnd, line1, &RecvSize))
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
            continue;
        }

        fwprintf(
            fp,
            L"===========================================================%d\r\n"
            L"%s\r\n"
            L"------------------------------------------------------------------------------\r\n"
            L"%s\r\n",
            LineNum - 1, line1, line1);
    }

    fclose(fp);

    return True;
}

ForceInline Void main2(Int argc, WChar **argv)
{
    FILE *fp;
    LPVoid lpBuffer, lpEndOfBuffer;
    UInt32 BufferSize, FileSize;

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
            wprintf(L"%s\nsupport UTF-16 only\n\n", *argv);
            fclose(fp);
            continue;
        }

        lpEndOfBuffer = (PByte)lpBuffer + FileSize;
        ProcessFile((PByte)lpBuffer, lpEndOfBuffer, *argv);
    }

    free(lpBuffer);
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
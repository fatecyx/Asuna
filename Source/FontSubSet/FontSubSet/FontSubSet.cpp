#pragma comment(lib, "FontSub.lib")

#include "FontSubSet.h"
#include "FontSub.h"

enum opt
{
    T_TTF,
    T_TTC,
    T_UNKNOWN,
    T_OPEN_FAIL,
    IN_FONT                    = 'f',
    IN_SUB                    = 's',
    OUT_FONT                = 'of',
    OVERWRITE                = 'n',
    CP_GBK                    = 936,
    CP_UNICODE_BIG_ENDIAN    = 1201,
};

BOOL CFontSubSet::ParseAss()
{
    FILE *fass;
    DWORD dwAssSize, dwEncoding, dwFileOffset;

    fass = my_fopen(m_szInSub, L"rb", &dwAssSize);
    if (fass == NULL)
    {
        return FALSE;
    }

    dwEncoding = 0;
    if (fread(&dwEncoding, 3, 1, fass) == 0)
    {
        _tprintf(_T("Read \"%s\" failed.\n"), m_szInSub);
        fclose(fass);
        return FALSE;
    }
    fseek(fass, 0, SEEK_SET);

    dwFileOffset = 0;
    CodePage = CP_GBK;
    switch (LOWORD(dwEncoding))
    {
    case 0xBBEF:
        if (HIWORD(dwEncoding) == 0xBF)
        {
            CodePage = CP_UTF8;
            dwFileOffset = 3;
        }
        break;

    case 0xFFFE:
        CodePage = CP_UNICODE_BIG_ENDIAN;
        dwFileOffset = 2;
        break;

    case 0xFEFF:
        CodePage = CP_WINUNICODE;
        dwFileOffset = 2;
        break;

    default:
        fseek(fass, 0, SEEK_SET);
        if (IsTextUTF8(fass, dwAssSize))
        {
            CodePage = CP_UTF8;
            dwFileOffset = 3;
        }
    }
    fseek(fass, dwFileOffset, SEEK_SET);

    DWORD dwVersion;

    dwVersion = CheckAssVersion(fass, dwAssSize);
    m_dwMaxStyles = GetStyleNames(fass, m_dwMaxStyles, dwAssSize);
//    m_dwKeepList = min(m_dwInFonts, m_dwMaxStyles);
    m_dwKeepList = m_dwMaxStyles;

    if (m_dwKeepList)
    {
        m_pKeepList = (WCHAR **)my_malloc(alloc_zero, m_dwKeepList * sizeof(*m_pKeepList));
        m_pKeepList = GetKeepList(fass, m_pKeepList, m_dwKeepList, dwVersion, dwAssSize);
    }

    fclose(fass);
    return TRUE;
}

BOOL CFontSubSet::SubSet()
{
    if (m_dwKeepList == 0)
    {
        return FALSE;
    }

    WCHAR szOutFont[MAX_PATH];

    wprintf(
        L"Subtitle     : %s\n"
        L"Encoding     : %s\n"
        L"Style number : %d\n"
        L"\n",
        m_szInSub,
        CodePage == CP_GBK ? L"GBK" :
        CodePage == CP_WINUNICODE ? L"Unicode (Little endian)" :
        CodePage == CP_UTF8 ? L"UTF-8" : L"Unicode (Big endian)",
        m_dwMaxStyles);
    for (DWORD i = 0; i != m_dwKeepList; ++i)
    {
        wprintf(L"Style: %s,   %d glyphs\n", m_szStyle[i], m_usWordCount[i]);
        FontSubSet(m_szInFont[i],
            m_pKeepList[i],
            m_usWordCount[i],
            GetDefaultFileName(szOutFont, m_szInFont[i], i));
        printf("\n");
    }

    _tprintf(_T("Elapsed time: %u ms\n"), clock());

    return TRUE;
}

void CFontSubSet::FontSubSet(WCHAR *szInFont, WCHAR *pKeepList, USHORT usCount, WCHAR *szOutFont)
{
    if (usCount == 0)
    {
        return;
    }

    UCHAR    ucType;
    USHORT    usFlag;
    FILE    *fInFont, *fOutFont;

    ucType = CheckFontType(szInFont, &fInFont);

    switch (ucType)
    {
        case T_TTF: usFlag = TTFCFP_FLAGS_SUBSET; break;
        case T_TTC: usFlag = TTFCFP_FLAGS_SUBSET | TTFCFP_FLAGS_TTC; break;
        case T_UNKNOWN: _tprintf(_T("Unknown font format.\n"));
        case T_OPEN_FAIL: _tprintf(_T("\"%s\": Can't open source font.\n"), szInFont);
        default: return;
    }

    DWORD  dwSize;
    UCHAR *puchDestBuffer, *puchMergeFontBuffer;
    UCHAR *cInFontBuf, *puchFontPackageBuffer = NULL;
    ULONG  ret, ulFontPackageBufferSize = 0, ulBytesWritten = 0;
    ULONG  ulDestBufferSize, ulMergeFontBufferSize;
    USHORT usSubsetFormat;

    dwSize = fsize(fInFont);
    fOutFont = _wfopen(szOutFont, L"rb+");
    cInFontBuf = (UCHAR *)my_malloc(0, dwSize);
    fread(cInFontBuf, dwSize, 1, fInFont);
    fclose(fInFont);
    usSubsetFormat = fOutFont ? TTFCFP_DELTA : TTFCFP_SUBSET1;

    ret = CreateFontPackage(
                cInFontBuf,
                dwSize,
                &puchFontPackageBuffer,
                &ulFontPackageBufferSize,
                &ulBytesWritten,
                usFlag,
                0,
                usSubsetFormat,
                0,
                TTFCFP_MS_PLATFORMID,
                TTFCFP_UNICODE_CHAR_SET,
                (unsigned short *)pKeepList,
                usCount,
                malloc,
                realloc,
                free,
                NULL);

    if (ret != NO_ERROR)
    {
        _tprintf(_T("CreateFontPackage() failed.\n"));
        _tprintf(_T("Error code: %d\n")
                 _T("Error string: %s\n"),
                 ret, GetErrorString(ret));
        my_free(cInFontBuf);
        return;
    }

    if (fOutFont == NULL)
    {
        usSubsetFormat = TTFMFP_SUBSET1;
        puchMergeFontBuffer = NULL;
        fOutFont = my_fopen(szOutFont, L"wb");
    }
    else
    {
        ulMergeFontBufferSize = fsize(fOutFont);
        usSubsetFormat = TTFMFP_DELTA;
        puchMergeFontBuffer = (UCHAR *)my_malloc(0, ulMergeFontBufferSize);
        fread(puchMergeFontBuffer, ulMergeFontBufferSize, 1, fOutFont);
    }

    wprintf(L"%s => %s ... ", szInFont, szOutFont);
    ret = MergeFontPackage(
                puchMergeFontBuffer,
                ulMergeFontBufferSize,
                puchFontPackageBuffer,
                ulBytesWritten,
                &puchDestBuffer,
                &ulDestBufferSize,
                &ulDestBufferSize,
                usSubsetFormat,
                malloc,
                realloc,
                free,
                NULL);
    if (puchDestBuffer)
    {
        _tprintf(_T("OK\n%.2f KB => %.2f KB (%.2lf%%)\n"),
            dwSize / 1024.0,
            ulDestBufferSize / 1024.0,
            (double)ulDestBufferSize / (double)dwSize * 100.0);
        fseek(fOutFont, 0, SEEK_SET);
        fwrite(puchDestBuffer, ulDestBufferSize, 1, fOutFont);
    }
    else
    {
        _tprintf(_T("failed\n")
                 _T("MergeFontPackage() failed.\n"));
    }

    _tprintf(_T("Error code: %d\nError string: %s\n"), ret, GetErrorString(ret));
    my_free(cInFontBuf);
    fclose(fOutFont);
}

EXTC IMAGE_DOS_HEADER __ImageBase;

Bool GetErrorString(HMODULE hModule, ULong ErrorCode, PWChar *pErrorString)
{
    NTSTATUS Status;
    MESSAGE_RESOURCE_ENTRY *mre;

    if (pErrorString == NULL)
    {
        BaseSetLastNTError(ERROR_INVALID_PARAMETER);
        return False;
    }

    *pErrorString = NULL;
    if (hModule == NULL)
        hModule = GetKernel32Handle();

    Status = RtlFindMessage(hModule, (ULong)RT_MESSAGETABLE, LANG_SYSTEM_DEFAULT, ErrorCode, &mre);
    if (!NT_SUCCESS(Status))
    {
        BaseSetLastNTError(Status);
        return False;
    }

    *pErrorString = (PWChar)mre->Text;

    return True;
}

TCHAR *CFontSubSet::GetErrorString(ULONG ulErrCode)
{
    HMODULE hModule;
    PWChar ErrorString;

    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)MergeFontPackage, &hModule);
    ::GetErrorString(hModule, ulErrCode, &ErrorString);
    if (ErrorString)
        return (TChar *)ErrorString;

    if (ulErrCode == 0)
    {
        return _T("NO_ERROR");
    }

    if (ulErrCode > 1116)
    {
        return _T("UNKNOWN_ERROR");
    }
    else if (ulErrCode < 1016)
    {
        return szErrorString[ulErrCode - 1000];
    }
    else if (ulErrCode < 1045)
    {
        return szErrorString[ulErrCode - 1000 - 14];
    }
    else if (ulErrCode < 1074)
    {
        return szErrorString[ulErrCode - 1000 - 29];
    }
    else if (ulErrCode < 1090)
    {
        return szErrorString[ulErrCode - 1000 - 35];
    }
    else
    {
        return szErrorString[ulErrCode - 1000 - 45];
    }
}

UCHAR CFontSubSet::CheckFontType(WCHAR *szFont, FILE **f)
{
    UCHAR ucType;
    WCHAR szName[MAX_PATH];
    DWORD dwTag;
    FILE *fp;

    swprintf(szName, L"%s.ttf", szFont);
    fp = _wfopen(szName, L"rb");
    if (fp == NULL)
    {
        swprintf(szName, L"%s.ttc", szFont);
        fp = _wfopen(szName, L"rb");
        if (fp == NULL)
        {
            return T_OPEN_FAIL;
        }
    }

    if (fread(&dwTag, 4, 1, fp) == 0)
    {
        ucType = T_UNKNOWN;
    }
    else switch (dwTag)
    {
    case 'fctt':
        ucType = T_TTC;
        break;

    case 0x100:
        fread(&dwTag, 2, 1, fp);
        if (LOWORD(dwTag))
        {
            ucType = T_TTF;
            break;
        }

    default:
        ucType = T_UNKNOWN;
    }

    if (f)
    {
        *f = fp;
        fseek(fp, 0, SEEK_SET);
    }
    else
        fclose(fp);

    return ucType;
}

WCHAR *CFontSubSet::GetDefaultFileName(WCHAR *szDest, WCHAR *szInput, DWORD index)
{
    int    i = 0;
    WCHAR *szStyle, *pExt;

    if (m_bMerge == FALSE)
    {
        szStyle = m_szStyle[index];
    }

    wcscpy(szDest, m_szInSub);
//    pExt = findextw(szDest);
    pExt = wcschr(findnamew(szDest), L'.');
    if (pExt)
        *pExt = 0;
    else
        pExt = szDest + wcslen(szDest);
//    wcscpy(pExt, L".ttf");
//    swprintf(szDest, L".%s_sub.ttf", szInput);
    swprintf(pExt, L".%s_sub.ttf", szInput);
    if (m_bMerge == FALSE)
    {
        while (1)
        {
            if (_waccess(szDest, 0) == 0)
            {
//                swprintf(szDest, L"%s_sub_%s_%d.ttf", szInput, szStyle, i++);
                swprintf(pExt, L"_%u.ttf", i++);
            }
            else
            {
                break;
            }
        }
    }

    return szDest;
}

WCHAR **CFontSubSet::GetKeepList(FILE *fp, WCHAR **pKeepList, DWORD dwKeepList, DWORD dwVersion, DWORD dwSize)
{
    DWORD    pos, dwMaxLength, dwLineLength;
    bool    *bWordMask;
    WCHAR    *szLine;
    static const WCHAR szKeyWord[] = L"Dialogue:";

    pos = ftell(fp);
    dwMaxLength = 0;
    szLine = (WCHAR *)my_malloc(0, 0);
    bWordMask = (bool *)my_malloc(alloc_zero, m_dwKeepList * 0xFFFF);
    m_usWordCount = (USHORT *)my_malloc(alloc_zero, m_dwKeepList * sizeof(*m_usWordCount));

    while (dwSize > (DWORD)ftell(fp))
    {
        dwLineLength = ReadLine(fp, szLine, dwMaxLength);
        if (dwLineLength < sizeof(szKeyWord) - 2)
        {
            continue;
        }
        if (!wcsnicmp(szLine, szKeyWord, sizeof(szKeyWord) / sizeof(WCHAR) - 1))
        {
            int        iStyleIndex;
            WCHAR *pWord, *pLine = szLine + sizeof(szKeyWord) / sizeof(WCHAR) - 1;

            if (dwVersion <= 4)                    // Marked =
            {
                pLine = SkipStr(pLine, L'=');
                pLine = SkipStr(pLine);
            }
            if (dwVersion >= 5)
            {
                pLine = SkipStr(pLine);            // Layer
            }
            for (byte ix = 0; ix != 2; ++ix)    // hh:mm:ss.sss * 2
            {                                    // style, actor
                pLine = SkipStr(pLine);            // marginRect(left, top, right)
            }
            iStyleIndex = GetStyleIndexByName(pLine);
            for (byte ix = 0; ix != 5; ++ix)    // actor
            {
                pLine = SkipStr(pLine);            // marginRect(left, top, right)
            }
            if (dwVersion >= 6)                    // marginRect.Bottom
            {
                pLine = SkipStr(pLine);
            }
            pLine = SkipStr(pLine);            // Effect
            if(iStyleIndex == -1)
            {
                continue;
            }

            dwLineLength >>= 1;
            pWord = pLine;                        // point to text
            while (*pWord != '\n' && *pWord && (DWORD)(pWord - szLine) < dwLineLength)
            {
                if (*pWord == '\\')
                {
                    ++pWord;
                    if (*pWord == 'N' && *pWord == 'n' && *pWord == 'h')
                    {
                        ++pWord;
                        continue;
                    }
                    --pWord;
                }
                else if (*pWord == L'{')
                {
                    pWord = SkipEffect(++pWord);
                    continue;
                }
                if (*pWord == '\r' || *pWord == L' ' || *pWord == 0x3000) // Full-width space
                {
                    ++pWord;
                    continue;
                }
                if (bWordMask[iStyleIndex * 0xFFFF + *pWord] == false)
                {
                    bWordMask[iStyleIndex * 0xFFFF + *pWord] = true;
                    ++m_usWordCount[iStyleIndex];
                }
                ++pWord;
            }
        }
    }

    for (DWORD i = 0; i != m_dwKeepList; ++i)
    {
        CONTINUE_IF(m_usWordCount[i] == 0);

        DWORD dwCount = 0;
        pKeepList[i] = (WCHAR *)my_malloc(alloc_zero, m_usWordCount[i] * sizeof(*pKeepList[i]));
        for (DWORD j = 0; j != 0xFFFF; ++j)
        {
            if (bWordMask[i * 0xFFFF + j] == true)
            {
                pKeepList[i][dwCount++] = (WCHAR)j;
            }
        }
    }

    my_free(bWordMask);
    my_free(szLine);
    fseek(fp, pos, SEEK_SET);
    return pKeepList;
}

int CFontSubSet::GetStyleIndexByName(WCHAR *pStyle)
{
    int     iIndex;
    DWORD    dwLength;
    WCHAR    *szStyle, *pEnd = wcschr(pStyle, ',');

    if (pEnd == NULL)
    {
        return -1;
    }
    while (pStyle < pEnd)
    {
        if (*pStyle != L'*' && *pStyle != '@')
        {
            break;
        }
        ++pStyle;
    }
    dwLength = pEnd - pStyle;
    szStyle = (WCHAR *)my_malloc(alloc_zero, (dwLength + 1) * sizeof(WCHAR));
    wcsncpy(szStyle, pStyle, dwLength);
    szStyle[dwLength] = 0;
    for (iIndex = 0; iIndex != m_dwKeepList; ++iIndex)
    {
        if (!wcsicmp(szStyle, m_szStyle[iIndex]))
        {
            break;
        }
    }
    my_free(szStyle);
    return iIndex == m_dwKeepList ? -1 : iIndex;
}

DWORD CFontSubSet::GetStyleNames(FILE *fp, DWORD dwMaxStyles, DWORD dwSize)
{
    DWORD dwStyles = 0, dwMaxLength = 0, pos;
    WCHAR *szLine;
    static const WCHAR szKeyWord[] = L"Style:";

    pos = ftell(fp);
    szLine     = (WCHAR *)my_malloc(0, 0);
    m_szStyle  = (WCHAR **)my_malloc(alloc_zero, dwMaxStyles * sizeof(*m_szStyle));
    m_szInFont = (WCHAR **)my_malloc(alloc_zero, dwMaxStyles * sizeof(*m_szInFont));

    while (dwSize > (DWORD)ftell(fp))
    {
        if (ReadLine(fp, szLine, dwMaxLength) < sizeof(szKeyWord) - 2)
        {
            continue;
        }
        if (!wcsnicmp(szLine, szKeyWord, sizeof(szKeyWord) / sizeof(WCHAR) - 1))
        {
            DWORD    dwLength;
            WCHAR    wc, *pStyle = szLine + sizeof(szKeyWord) / sizeof(WCHAR) - 1;

            while (1)    // skip tabs and spaces
            {
                wc = *pStyle;
                if (wc != ' ' && wc != '\t' && wc != '*')
                {
                    break;
                }
                ++pStyle;
            }
            if (dwStyles >= dwMaxStyles)
            {
                dwMaxStyles += 5;
                m_szStyle  = (WCHAR **)my_realloc(0, m_szStyle,  dwMaxStyles * sizeof(*m_szStyle));
                m_szInFont = (WCHAR **)my_realloc(0, m_szInFont, dwMaxStyles * sizeof(*m_szInFont));
            }

            // copy style name
            dwLength = (CHAR *)wcschr(pStyle, ',') - (CHAR *)pStyle;
            m_szStyle[dwStyles] = (WCHAR *)my_malloc(0, dwLength + sizeof(WCHAR));
            dwLength /= sizeof(WCHAR);
            wcsncpy(m_szStyle[dwStyles], pStyle, dwLength);
            m_szStyle[dwStyles][dwLength] = 0;

            // copy font name
            pStyle += dwLength + 1;
            while (1)    // skip tabs and spaces
            {
                wc = *pStyle;
                if (wc != ' ' && wc != '\t' && wc != '*' && wc != '@')
                {
                    break;
                }
                ++pStyle;
            }
            dwLength = (CHAR *)wcschr(pStyle, ',') - (CHAR *)pStyle;
            m_szInFont[dwStyles] = (WCHAR *)my_malloc(0, dwLength + 2);
            dwLength /= 2;
            wcsncpy(m_szInFont[dwStyles], pStyle, dwLength);
            m_szInFont[dwStyles][dwLength] = 0;

            ++dwStyles;
        }
    }

    dwMaxStyles = dwStyles;
    my_free(szLine);
    fseek(fp, pos, SEEK_SET);
    return dwMaxStyles;
}

DWORD CFontSubSet::CheckAssVersion(FILE *fp, DWORD dwSize)
{
    WCHAR *szLine, *pLine;
    static const WCHAR szKeyWord[] = L"scripttype";
    DWORD dwVersion = 3, dwMaxLength = 0, pos;

    pos = ftell(fp);
    szLine = (WCHAR *)my_malloc(0, 0);

    while (dwSize > (DWORD)ftell(fp))
    {
        if (ReadLine(fp, szLine, dwMaxLength) < sizeof(szKeyWord) / sizeof(WCHAR) - 1)
        {
            continue;
        }
        if (!wcsnicmp(szLine, szKeyWord, sizeof(szKeyWord) / sizeof(WCHAR) - 1))
        {
            DWORD dwLen;

            dwLen = wcslen(wcschr(szLine, ':') + 1);
            pLine = szLine + wcslen(szLine) - 1;
            while (*pLine == L' ' || *pLine == L'\n' || *pLine == L'\r')
                --pLine;
            ++pLine;

            if (dwLen >= 4 && !wcsncmp(pLine - 4, L"4.00", 4))
            {
                dwVersion = 4;
                break;
            }
            else if (dwLen >= 5 && !wcsncmp(pLine - 5, L"4.00+", 5))
            {
                dwVersion = 5;
                break;
            }
            else if (dwLen >= 6 && !wcsncmp(pLine - 6, L"4.00++", 6))
            {
                dwVersion = 6;
                break;
            }
        }
    }
    wprintf(L"ASS version: %s", dwVersion == 3 ? L"3 (Default)" : pLine - dwVersion - 1);
    my_free(szLine);
    fseek(fp, pos, SEEK_SET);

    return dwVersion;
}

LPWSTR CFontSubSet::MByteToWChar(UINT CodePage, LPCSTR lpMBStr, DWORD &dwStrlen)
{
    LPWSTR lpWCStr;
    DWORD dwMinSize = MultiByteToWideChar(CodePage, 0, lpMBStr, -1, NULL, 0);
    if (dwMinSize == 0)
    {
        return NULL;
    }
    lpWCStr = (LPWSTR)my_malloc(0, dwMinSize * sizeof(WCHAR));
    dwStrlen = MultiByteToWideChar(CodePage, 0, lpMBStr, -1, lpWCStr, dwMinSize) << 1;
    return lpWCStr;
}

DWORD CFontSubSet::ReadLine(FILE *fp, WCHAR *&szLine, DWORD &dwMaxLength)
{
    BOOL    bComment = FALSE;
    LPWSTR    lpWCStr;
    DWORD    dwLineLen = 0;
    size_t    pos = ftell(fp);

    if (CodePage == CP_WINUNICODE || CodePage == CP_UNICODE_BIG_ENDIAN)
    {
        WCHAR c, eol, comment;

        switch (CodePage)
        {
        case CP_WINUNICODE:
            eol = '\n';
            comment = ';';
            break;
        default:
            eol = '\n' << 8 | HIBYTE('\n');
            comment = ';' << 8 | HIBYTE(';');
        }

        c = fgetwc(fp);
        if (c == comment)
        {
            bComment = TRUE;
        }
        while (1)
        {
            if (feof(fp))
            {
                break;
            }

            dwLineLen += 2;
            if (c == eol)
            {
                break;
            }
            c = fgetwc(fp);
        }
    }
    else
    {
        CHAR c = fgetc(fp);

        if (c == ';')
        {
            bComment = TRUE;
        }
        while (1)
        {
            ++dwLineLen;
            if (feof(fp) || c == '\n')
            {
                break;
            }
            c = fgetc(fp);
        }
    }
    if (bComment == TRUE)
    {
        return 0;
    }

    fseek(fp, pos, SEEK_SET);

    if (dwLineLen + 2 > dwMaxLength)
    {
        dwMaxLength = dwLineLen + 2;
        szLine = (WCHAR *)my_realloc(0, szLine, dwMaxLength);
    }
    fread(szLine, dwLineLen, 1, fp);
    szLine[dwLineLen >> 1] = 0;

    if (CodePage == CP_WINUNICODE)
    {
        return dwLineLen;
    }
    else if (CodePage == CP_UNICODE_BIG_ENDIAN)
    {
        WCHAR wc;
        for (WCHAR *p = szLine; p != szLine + (dwLineLen >> 1); ++p)
        {
            wc = *p;
            wc = (wc << 8) | HIBYTE(wc);
            *p = wc;
        }
        return dwLineLen;
    }

    lpWCStr = MByteToWChar(CodePage, (CHAR *)szLine, dwLineLen);
    if (lpWCStr == NULL)
    {
        return 0;
    }
    if (dwLineLen > dwMaxLength)
    {
        dwMaxLength = dwLineLen;
        szLine = (WCHAR *)my_realloc(0, szLine, dwMaxLength);
    }
    wcscpy(szLine, lpWCStr);

    my_free(lpWCStr);
    return dwLineLen;
}

BOOL CFontSubSet::ParseCmdLine()
{
    if (m_argc < 2)
    {
        PrintHelp(m_argv);
        return FALSE;
    }

    return ParseCmdLine(m_argc, m_argv);
}

BOOL CFontSubSet::ParseCmdLine(int argc, WCHAR **argv)
{
    int        i;
    DWORD    dwParam, dwInFonts = 0, dwOutFonts = 0;
/*
    m_szInFont    = (TCHAR **)my_malloc(alloc_zero, (argc - 1) * sizeof(*m_szInFont));
    m_szOutFont    = (TCHAR **)my_malloc(alloc_zero, (argc - 1) * sizeof(*m_szOutFont));
*/
    for (i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            wcslwr(argv[i]);
            dwParam = (DWORD)argv[i][1];
            for (int j = 2; argv[i][j]; ++j)
            {
                dwParam = dwParam << 8 | (TCHAR)argv[i][j];
            }
        }
        else
        {
            dwParam = 0;
        }
        switch (dwParam)
        {
        case IN_FONT:
//            if (++i >= argc) break;
//            m_szInFont[dwInFonts++] = argv[i];
            break;

        case OUT_FONT:
//            if (++i >= argc) break;
//            m_szOutFont[dwOutFonts++] = argv[i];
            break;

        case OVERWRITE:
            m_bMerge = FALSE;
            break;

        case IN_SUB:
            if (++i >= argc) break;
        default:
            m_szInSub = argv[i];
        }
    }

    if (m_szInSub == NULL || i < argc)
    {
        return FALSE;
    }

    m_dwInFonts  = dwInFonts;
    m_dwOutFonts = dwOutFonts;

    WCHAR *pExt = wcsrchr(m_szInSub, '\\');
    if (pExt)
    {
        *pExt = 0;
        _wchdir(m_szInSub);
        *pExt = '\\';
    }

    return TRUE;
}

void CFontSubSet::PrintHelp(PWChar *argv)
{
    TChar *p, *szFileName = findnamew(*argv);

    p = _tcsrchr(szFileName, '"');
    if (p) *p = 0;
    _tprintf(
        L"FontSubSet 0.4 by Kanade\n"
        L"built on " MAKE_WSTRING(__DATE__) L", MSVC %02u.%02u"
        L"\n"
        L"\n"
        L"Usage: \n"
//       L"%s -f in_font -s in_sub -of out_font\n"
        L"%s [-s] sub.ass [-n]\n"
        L"\n"
        L"Options:\n"
//        L"         -f  Set input fonts (ttf and ttc only)\n"
//        L"         -s  Set input subtitle(ass only)\n"
//        L"             support v4.00, v4.00+, v4.00++\n"
//        L"         -of Set output font names, default: infont_sub.ttf\n"
        L"         -n  Don't merge with a previous one\n"
        L"\n"
        L"Remark: \n"
        L"1.Use the font names in \"Style\" of \"sub.ass\" to rename the fonts.\n"
        L"2.All options are case-insensitive.\n\n"
        , _MSC_VER / 100, _MSC_VER % 100, szFileName);
}

CFontSubSet::CFontSubSet(int argc, WCHAR **argv) : m_argc(argc), m_argv(argv)
{
#if (CRT_ALLOC == 0)
    m_hHeap = GetProcessHeap();
#endif
    m_szInFont        = NULL;
    m_szOutFont        = NULL;
    m_szStyle        = NULL;
    m_pKeepList        = NULL;
    m_usWordCount    = NULL;
    m_dwMaxStyles    = 10;
    m_bMerge        = TRUE;
}

CFontSubSet::~CFontSubSet()
{
    if (m_szInFont)
    {
        my_free(m_szInFont);
    }
    if (m_szOutFont)
    {
        my_free(m_szOutFont);
    }
    if (m_szStyle)
    {
        while (m_dwMaxStyles--)
        {
            my_free(m_szStyle[m_dwMaxStyles]);
            my_free(m_szInFont[m_dwMaxStyles]);
        }
        my_free(m_szStyle);
        my_free(m_szInFont);
    }
    if (m_pKeepList)
    {
        while (m_dwKeepList)
        {
            my_free(m_pKeepList[--m_dwKeepList]);
        }
        my_free(m_pKeepList);
    }
    if (m_usWordCount)
    {
        my_free(m_usWordCount);
    }
}

FILE *CFontSubSet::my_fopen(WCHAR *szFileName, WCHAR *szMode, LPDWORD dwSize)
{
    FILE *fp = _wfopen(szFileName, szMode);

    if (fp == NULL)
    {
        wprintf(L"Can't open \"%s\".\n", szFileName);
    }
    if (dwSize != NULL)
    {
        *dwSize = fsize(fp);
    }

    return fp;
}

BOOL CFontSubSet::IsTextUTF8(FILE *fp, DWORD dwLen)
{
    DWORD dwOctets;     // octets to go in this UTF-8 encoded character
    UCHAR chr;
    BOOL  bAllAscii = TRUE;

    dwOctets = 0;
    for (DWORD i = 0; i < dwLen; i++)
    {
        chr = fgetc(fp);

        if(chr & 0x80)
        {
            bAllAscii = FALSE;
        }

        if(dwOctets == 0)
        {
            // 7 bit ascii after 7 bit ascii is just fine.   Handle start of encoding case.
            if(chr >= 0x80)
            {
                // count of the leading 1 bits is the number of characters encoded
                do {
                    chr <<= 1;
                    dwOctets++;
                }
                while(chr & 0x80);

                dwOctets--;                // count includes this character
                if(dwOctets == 0)
                {
                    return FALSE;        // must start with 11xxxxxx
                }
            }
        }
        else                            // non-leading bytes must start as 10xxxxxx
        {
            if((chr & 0xC0) != 0x80)
            {
                return FALSE;
            }
            dwOctets--;                    // processed another octet in encoding
        }
    }

    // End of text. Check for consistency.

    if(dwOctets > 0)    // anything left over at the end is an error
    {
        return FALSE;
    }

    if(bAllAscii)    // Not utf-8 if all ascii. Forces caller to use code pages for conversion
    {
        return FALSE;
    }

    return TRUE;
}

WCHAR *CFontSubSet::SkipStr(WCHAR *p, WCHAR sep)
{
    WCHAR *p1;
    p1 = wcschr(p, sep);
    return ++p1;
}

WCHAR *CFontSubSet::SkipEffect(WCHAR *p)
{
    while (*p != L'}')
    {
        if (*p == L'{') p = SkipEffect(++p);
        else ++p;
    }
    return ++p;
}
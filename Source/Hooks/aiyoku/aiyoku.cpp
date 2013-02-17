#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text /MERGE:.data1=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(linker, "/EXPORT:DirectSoundCreate8=DSOUND.DirectSoundCreate8")
#pragma comment(lib, "dsound.lib")

#define INITGUID

// /DELAYLOAD:ucadec.dll /DELAYLOAD:bass.dll /DELAYLOAD:bass_aac.dll /DELAYLOAD:ucidec.dll

#define LOG_FILE L"K:\\galgame\\∑x“Ì§Œ•Ê©`•π•∆•£•¢\\aiyoku.txt"

#define HAVE_COMPRESS 0
#define HAVE_SUPPORT_AUDIO 0
#define HOOK_LOAD_FILE 0
#define HOOK_PARSE_SCRIPT 0

#include "aiyoku.h"
#include "gal_common.h"
#include <Uuids.h>
#include "my_commsrc.h"

BOOL g_bForceShiftJis = FALSE;

OVERLOAD_CPP_NEW_WITH_HEAP(CMem::GetGlobalHeap())

#if HAVE_SUPPORT_AUDIO
    #define SUPPORT_AAC_DECODE
    #define DEFAULT_STRUCT_ALIGN 8
    #include "vorbishook.cpp"
#endif

ULONG AnsiToUnicode(LPCSTR lpAnsi, ULONG Length, LPWSTR lpUnicodeBuffer, ULONG BufferCount, ULONG CodePage = CP_ACP)
{
    return MultiByteToWideChar(CodePage, 0, lpAnsi, Length, lpUnicodeBuffer, BufferCount);
}

BOOL CDECL CheckOSDefaultLangID(ULONG PrimaryLangID)
{
    UNREFERENCED_PARAMETER(PrimaryLangID);
    return TRUE;
}

BOOL WINAPI MyTextOutA(HDC hDC, int X, int Y, LPCTSTR lpString, int cbCount)
{
    BOOL    Result;
    WCHAR   c, ch[0x400];
    ULONG   CodePage;
    HFONT   hFont, hFontOld;

    hFont    = NULL;
    hFontOld = NULL;

    if (g_bForceShiftJis)
    {
        CodePage = CP_SHIFTJIS;
        goto MBYTE_TO_WCHAR;
    }

    CodePage = CP_GB2312;
    if (cbCount > 2)
    {
        if (IsShiftJISString((PCHAR)lpString, cbCount))
            CodePage = CP_SHIFTJIS;

        goto MBYTE_TO_WCHAR;
    }
    else if (cbCount == 2)
    {
        c = *(PWCHAR)lpString;
        switch ((ULONG)c)
        {
            case SWAPCHAR('°—'):
//                c = SWAPCHAR('ÅÙ');
                ch[0] = 0x266A;
                break;

            default:
//                if (IsShiftJISString((LPSTR)&c, 2))
//                    CodePage = CP_SHIFTJIS;

                goto MBYTE_TO_WCHAR;
        }

        hFont = DuplicateFontW(hDC, SHIFTJIS_CHARSET);
        if (hFont != NULL)
        {
            hFontOld = (HFONT)SelectObject(hDC, hFont);
            if (hFontOld == NULL)
            {
                DeleteObject(hFont);
                hFont = NULL;
            }
        }

        cbCount = 1;
        goto SKIP_CONV;
    }

MBYTE_TO_WCHAR:
    cbCount = MultiByteToWideChar(CodePage, 0, lpString, cbCount, ch, countof(ch));

SKIP_CONV:
    Result = TextOutW(hDC, X, Y, ch, cbCount);

    if (hFont != NULL)
    {
        SelectObject(hDC, hFontOld);
        DeleteObject(hFont);
    }

    return Result;
}

HFONT
WINAPI
MyCreateFontA(
    int     cHeight,
    int     cWidth,
    int     cEscapement,
    int     cOrientation,
    int     cWeight,
    DWORD   bItalic,
    DWORD   bUnderline,
    DWORD   bStrikeOut,
    DWORD   iCharSet,
    DWORD   iOutPrecision,
    DWORD   iClipPrecision,
    DWORD   iQuality,
    DWORD   iPitchAndFamily,
    LPCSTR  pszFaceName
)
{
    LOGFONTW lf;

    UNREFERENCED_PARAMETER(iCharSet);
    UNREFERENCED_PARAMETER(iQuality);

    lf.lfHeight         = cHeight;
    lf.lfWidth          = cWidth;
    lf.lfEscapement     = cEscapement;
    lf.lfOrientation    = cOrientation;
    lf.lfWeight         = cWeight;
    lf.lfItalic         = bItalic;
    lf.lfUnderline      = bUnderline;
    lf.lfStrikeOut      = bStrikeOut;
    lf.lfCharSet        = GB2312_CHARSET;
    lf.lfOutPrecision   = iOutPrecision;
    lf.lfClipPrecision  = iClipPrecision;
    lf.lfQuality        = CLEARTYPE_QUALITY;
    lf.lfPitchAndFamily = iPitchAndFamily;

    AnsiToUnicode(pszFaceName, -1, lf.lfFaceName, countof(lf.lfFaceName), IsShiftJISString(pszFaceName, -1) ? CP_SHIFTJIS : CP_GB2312);

    return CreateFontIndirectW(&lf);
}

ULONG UnicodeWin32FindDataToAnsi(LPWIN32_FIND_DATAW pwfdW, LPWIN32_FIND_DATAA pwfdA)
{
    pwfdA->dwFileAttributes = pwfdW->dwFileAttributes;
    pwfdA->ftCreationTime   = pwfdW->ftCreationTime;
    pwfdA->ftLastAccessTime = pwfdW->ftLastAccessTime;
    pwfdA->ftLastWriteTime  = pwfdW->ftLastWriteTime;
    pwfdA->nFileSizeHigh    = pwfdW->nFileSizeHigh;
    pwfdA->nFileSizeLow     = pwfdW->nFileSizeLow;
    pwfdA->dwReserved0      = pwfdW->dwReserved0;
    pwfdA->dwReserved1      = pwfdW->dwReserved1;

    WideCharToMultiByte(CP_ACP, 0, pwfdW->cFileName, -1, pwfdA->cFileName, sizeof(pwfdA->cFileName), 0, 0);
    return WideCharToMultiByte(CP_ACP, 0, pwfdW->cAlternateFileName, -1, pwfdA->cAlternateFileName, sizeof(pwfdA->cAlternateFileName), 0, 0);
}

ULONG IsArcValid(LPWIN32_FIND_DATAW FindData)
{
    ULONG           Length, ExtensionType;
    PWCHAR          pszExtension;
    ULARGE_INTEGER  Extension;
    enum { EXTENSION_TYPE_ARC, EXTENSION_TYPE_SC };

    if (TEST_BITS(FindData->dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY))
        return 0;

    Length = StrLengthW(FindData->cFileName);
    if (FindData->cFileName[Length - 4] == '.')
        Length -= 3;
    else if (FindData->cFileName[Length - 3] == '.')
        Length -= 2;
    else
        return 0;

    pszExtension = FindData->cFileName + Length;
    Extension.QuadPart = *(PULONG64)pszExtension;
    if (CHAR_UPPER3W(Extension.QuadPart) == TAG3W('ARC'))
        ExtensionType = EXTENSION_TYPE_ARC;
    else if (CHAR_UPPER2W(Extension.QuadPart) == TAG2W('SC'))
        ExtensionType = EXTENSION_TYPE_SC;
    else
        return 0;

    if ((*(PULONG64)&pszExtension[-4] & 0xFFFFFFDFFFDFFFFF) != TAG4W('_SC.'))
    {
        if (ExtensionType == EXTENSION_TYPE_ARC)
        {
            *(PULONG64)pszExtension = TAG2W('sc');
            if (IsPathExistsW(FindData->cFileName))
                return 0;

            *(PULONG64)&pszExtension[-1] = TAG4W('_sc.');
            *(PULONG64)&pszExtension[+3] = TAG2W('sc');
            if (IsPathExistsW(FindData->cFileName))
                return 0;
        }

        *(PULONG64)&pszExtension[-1] = TAG4W('.arc');
        pszExtension[3] = 0;

        return Length;
    }

    pszExtension[0] = 0;
    *(PULONG64)&pszExtension[-4] = TAG3W('.sc');
    if (IsPathExistsW(FindData->cFileName))
        return 0;

    *(PULONG64)&pszExtension[-4] = TAG4W('.arc');
    if (ExtensionType == EXTENSION_TYPE_SC)
        return Length;

    if (IsPathExistsW(FindData->cFileName))
        return 0;

    return Length;
}

HANDLE WINAPI MyFindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
    HANDLE              hFind;
    BOOL                bUseNewFilter;
    ULONG               Length;
    WCHAR               szFile[MAX_PATH];
    WIN32_FIND_DATAW    FindData;
    static WCHAR        szNewFilter[] = L"data0????*.arc";

    Length = AnsiToUnicode(lpFileName, -1, szFile, countof(szFile)) - 1;
    if (!StrICompareW(szFile, L"data0????.arc"))
    {
        *(PULONG64)&szFile[Length - 4] = TAG4W('*.*c');
        *(PULONG)&szFile[Length] = 0;
        bUseNewFilter = TRUE;
    }
    else
    {
        bUseNewFilter = FALSE;
    }

    hFind = FindFirstFileW(szFile, &FindData);
    if (hFind == INVALID_HANDLE_VALUE)
        return hFind;

    LOOP_ONCE
    {
        ULONG64 Extension;

        if (!bUseNewFilter && szFile[Length - 4] != '.')
            break;

        Extension = *(PULONG64)&szFile[Length - 3];
        if (CHAR_UPPER3W(Extension) != TAG3W('ARC') &&
            CHAR_UPPER2W(Extension) != TAG2W('SC')  &&
            !bUseNewFilter)
        {
            break;
        }

        hFind = (HANDLE)((ULONG_PTR)hFind | 1);
        if (IsArcValid(&FindData) != 0)
            break;

        *(PULONG)FindData.cFileName = '.';
        FindData.dwFileAttributes |= FILE_ATTRIBUTE_DIRECTORY;
    }

    UnicodeWin32FindDataToAnsi(&FindData, lpFindFileData);

    return hFind;
}

BOOL WINAPI MyFindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
{
    BOOL Result, bIsArc;
    WIN32_FIND_DATAW FindData;

    bIsArc = (ULONG_PTR)hFindFile & 1;
    hFindFile = (HANDLE)((ULONG_PTR)hFindFile & ~1);
    Result = FindNextFileW(hFindFile, &FindData);
    if (!Result || !bIsArc)
        return Result;

    if (IsArcValid(&FindData) == 0)
    {
        *(PULONG)FindData.cFileName = '.';
        FindData.dwFileAttributes |= FILE_ATTRIBUTE_DIRECTORY;
    }

    UnicodeWin32FindDataToAnsi(&FindData, lpFindFileData);
    return Result;
}

BOOL WINAPI MyFindClose(HANDLE hFindFile)
{
    return FindClose((HANDLE)((ULONG_PTR)hFindFile & ~1));
}

PWCHAR GetFileArcName(PWCHAR szFile, ULONG Length)
{
    PWCHAR  pszExtensionW;
    ULONG64 Extension;

    pszExtensionW = szFile + Length - 4;
    Extension = *(PULONG64)&pszExtensionW[1];

    *(PULONG64)&pszExtensionW[1] = TAG2W('sc');
    if (IsPathExistsW(szFile))
        return szFile;

    *(PULONG64)&pszExtensionW[0] = TAG4W('_sc.');
    *(PULONG64)&pszExtensionW[4] = TAG2W('sc');
    if (IsPathExistsW(szFile))
        return szFile;

    pszExtensionW[0] = '.';
    *(PULONG64)&pszExtensionW[1] = Extension;

    if (IsPathExistsW(szFile))
        return szFile;

    *(PULONG64)&pszExtensionW[0] = TAG4W('_sc.');
    *(PULONG64)&pszExtensionW[4] = Extension;

    return szFile;
}

HANDLE
WINAPI
MyCreateFileA(
    LPCSTR                  lpFileName,
    DWORD                   dwDesiredAccess,
    DWORD                   dwShareMode,
    LPSECURITY_ATTRIBUTES   lpSecurityAttributes,
    DWORD                   dwCreationDisposition,
    DWORD                   dwFlagsAndAttributes,
    HANDLE                  hTemplateFile
)
{
    WCHAR   szFile[MAX_PATH];
    LPCSTR  pszExtensionA;
    ULONG   Length;
    ULONG64 Extension;

    pszExtensionA = lpFileName + StrLengthA(lpFileName) - 3;
    Length = AnsiToUnicode(lpFileName, pszExtensionA + 3 - lpFileName + 1, szFile, countof(szFile));
    LOOP_ONCE
    {
        if (pszExtensionA[-1] != '.')
            break;

        Extension = CHAR_UPPER4(*(PULONG)pszExtensionA);
        if ((ULONG)Extension != TAG3('ARC') && ((ULONG)Extension & 0x00FFFFFF) != TAG2('SC'))
            break;

        GetFileArcName(szFile, Length - 1);
    }

#if HOOK_LOAD_FILE
    FILE *fp = _wfopen(LOG_FILE, L"ab+");
    if (fp)
    {
        fprintf(fp, "%S\r\n", szFile);
        fclose(fp);
    }
#endif

    return CreateFileW(szFile, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

DWORD WINAPI MyGetFileAttributesA(LPCSTR lpFileName)
{
    ULONG   Length;
    LPSTR   pszExtensionA;
    ULONG64 Extension;
    WCHAR   szFile[MAX_PATH];

    pszExtensionA = (LPSTR)lpFileName + StrLengthA(lpFileName) - 3;
    Length = AnsiToUnicode(lpFileName, pszExtensionA + 3 - lpFileName + 1, szFile, countof(szFile));
    LOOP_ONCE
    {
        if (pszExtensionA[-1] != '.')
            break;

        Extension = CHAR_UPPER4(*(PULONG)pszExtensionA);

        if ((ULONG)Extension != TAG3('ARC') && ((ULONG)Extension & 0x00FFFFFF) != TAG2('SC'))
            break;

        GetFileArcName(szFile, Length - 1);
    }

#if HOOK_LOAD_FILE
    FILE *fp = _wfopen(LOG_FILE, L"ab+");
    if (fp)
    {
        fprintf(fp, "%S\r\n", szFile);
        fclose(fp);
    }
#endif

    return GetFileAttributesW(szFile);
}

ASM ULONG FASTCALL _______UCL_NRV2E_DecompressASMFast32(PVOID /* pvInput */, PVOID /* pvOutput */)
{
    INLINE_ASM
    {
        lea     esp, [esp - 0x14];
        mov     [esp + 0x00], ebx;
        mov     [esp + 0x04], ebp;
        mov     [esp + 0x08], esi;
        mov     [esp + 0x0C], edi;
        mov     [esp + 0x10], edx;
        cld;
        mov     esi, ecx;
        mov     edi, edx;
        or      ebp, 0xFFFFFFFF;
        xor     ecx, ecx;
        jmp L029;

        INLINE_ASM __emit 0x8D INLINE_ASM __emit 0xB4 INLINE_ASM __emit 0x26 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00;   // lea esi, [esi]
        INLINE_ASM __emit 0x8D INLINE_ASM __emit 0xB4 INLINE_ASM __emit 0x26 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00 INLINE_ASM __emit 0x00;   // lea esi, [esi]
L022:
        mov     al, byte ptr [esi];
        inc     esi;
        mov     byte ptr [edi], al;
        inc     edi;
L026:
        add     ebx, ebx;
        jnb L033;
        jnz L022;
L029:
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
        jb L022;
L033:
        mov     eax, 0x1;
L034:
        add     ebx, ebx;
        jnz L039;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L039:
        adc     eax, eax;
        add     ebx, ebx;
        jnb L047;
        jnz L055;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
        jb L055;
L047:
        dec     eax;
        add     ebx, ebx;
        jnz L053;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L053:
        adc     eax, eax;
        jmp L034;
L055:
        sub     eax, 0x3;
        jb L072;
        shl     eax, 0x8;
        mov     al, byte ptr [esi];
        inc     esi;
        xor     eax, 0xFFFFFFFF;
        je L120;
        sar     eax, 1;
        mov     ebp, eax;
        jnb L078;
L065:
        add     ebx, ebx;
        jnz L070;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L070:
        adc     ecx, ecx;
        jmp L099;
L072:
        add     ebx, ebx;
        jnz L077;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L077:
        jb L065;
L078:
        inc     ecx;
        add     ebx, ebx;
        jnz L084;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L084:
        jb L065;
L085:
        add     ebx, ebx;
        jnz L090;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
L090:
        adc     ecx, ecx;
        add     ebx, ebx;
        jnb L085;
        jnz L098;
        mov     ebx, dword ptr [esi];
        sub     esi, -0x4;
        adc     ebx, ebx;
        jnb L085;
L098:
        add     ecx, 0x2;
L099:
        cmp     ebp, -0x500;
        adc     ecx, 0x2;
        lea     edx, dword ptr [edi+ebp];
        cmp     ebp, -0x4;
        jbe L111;
L104:
        mov     al, byte ptr [edx];
        inc     edx;
        mov     byte ptr [edi], al;
        inc     edi;
        dec     ecx;
        jnz L104;
        jmp L026;
L111:
        mov     eax, dword ptr [edx];
        add     edx, 0x4;
        mov     dword ptr [edi], eax;
        add     edi, 0x4;
        sub     ecx, 0x4;
        ja L111;
        add     edi, ecx;
        xor     ecx, ecx;
        jmp L026;
L120:
        mov     eax, edi;
        mov     ebx, [esp + 0x00];
        mov     ebp, [esp + 0x04];
        mov     esi, [esp + 0x08];
        mov     edi, [esp + 0x0C];
        sub     eax, [esp + 0x10];
        lea     esp, [esp + 0x14];
        ret;
    }
}

ASM
LONG
CDECL
OldDecompressFile(
    PVOID  pvDecompressed,
    PULONG pOutSize,
    PVOID  pvCompressed,
    ULONG  InSize,
    ULONG  SkipBytes,
    ULONG  OutBytes
)
{
    UNREFERENCED_PARAMETER(pvDecompressed);
    UNREFERENCED_PARAMETER(pOutSize);
    UNREFERENCED_PARAMETER(pvCompressed);
    UNREFERENCED_PARAMETER(InSize);
    UNREFERENCED_PARAMETER(SkipBytes);
    UNREFERENCED_PARAMETER(OutBytes);
    ASM_DUMMY_AUTO();
}

#if HOOK_PARSE_SCRIPT

PBYTE pbBegin, pbEnd;
ULONG OPCount;

typedef struct
{
    BOOL    bValid;
    ULONG   ParamCount;
} BURIKO_SCRIPT_PARAM_INFO;

BURIKO_SCRIPT_PARAM_INFO *pCurInfo, bsInfo[0x400];

ASM ULONG OldBGI_ReadDword()
{
    ASM_DUMMY_AUTO();
}

ASM ULONG BGI_ReadDword()
{
    INLINE_ASM
    {
        cmp esi, pbBegin;
        jb  _EXIT;
        cmp esi, pbEnd;
        jae _EXIT;

        mov eax, [edi+0x14];    // offset

        cmp eax, 0x321D8;
        je  RAED_OP;
        cmp eax, 0x9CC6;
        jnz _EXIT;

// READ_DATA:

        mov     ecx, pCurInfo;
        jecxz   _EXIT;

        inc [ecx];

        jmp _EXIT;

RAED_OP:

        mov ecx, [esi];         // op
        lea eax, [bsInfo + ecx * 8];
        mov pCurInfo, 0;
        cmp [eax], 1;
        je  _EXIT;

        inc OPCount;
        mov [eax], 1;
        lea eax, [eax + 4];
        mov pCurInfo, eax;

_EXIT:

        jmp OldBGI_ReadDword;
    }
}

#endif

LONG
CDECL
DecompressFile(
    PVOID  pvDecompressed,
    PULONG pOutSize,
    PVOID  pvCompressed,
    ULONG  InSize,
    ULONG  SkipBytes,
    ULONG  OutBytes
)
{
    ULONG Result, Magic;

    Result = 5;
    LOOP_ONCE
    {
        Magic = *(PULONG)pvCompressed;
        if ((Magic & 0x00FFFFFF) == TAG3('UCI'))
        {
            UCI_INFO uci;
            UCI_META_INFO *pMeta;
            IMG_BITMAP_HEADER *pHeader;

            if (UCIDecodeEx(pvCompressed, InSize, &uci, TRUE) < 0)
                break;

            pHeader = (IMG_BITMAP_HEADER *)pvDecompressed;
            pMeta = (UCI_META_INFO *)uci.lpExtraInfo;
            if (pMeta != NULL && pMeta->Magic == UCI_META_INFO_MAGIC)
                ConvertRawToBitMap(&uci, pMeta->Width, pMeta->Height, pMeta->BitsPerPixel, pvDecompressed, -1);
            else
                ConvertRawToBitMap(&uci, uci.Width, uci.Height, uci.BitsPerPixel, pvDecompressed, -1);

            UCIFreeEx(&uci);

            if (pOutSize != NULL)
                *pOutSize = pHeader->dwFileSize;
        }
        else if (InSize > sizeof(MY_BURIKO_SCRIPT_MAGIC) &&
                !CompareMemory(pvCompressed, MY_BURIKO_SCRIPT_MAGIC, sizeof(MY_BURIKO_SCRIPT_MAGIC)))
        {
            UINT OutSize;

            OutSize = UCL_NRV2E_DecompressASMFast32((PBYTE)pvCompressed + sizeof(MY_BURIKO_SCRIPT_MAGIC), pvDecompressed);
            if (pOutSize != NULL)
                *pOutSize = OutSize;
        }
        else
        {
            break;
        }

        Result = 0;
    }

#if HOOK_PARSE_SCRIPT
    if (Result == 0)
        return Result;

    static CHAR szMagic[] = "BurikoCompiledScriptVer1.00";

    Result = OldDecompressFile(pvDecompressed, pOutSize, pvCompressed, InSize, SkipBytes, OutBytes);
    if (CompareMemory(pvDecompressed, szMagic, sizeof(szMagic)))
    {
//        pbBegin = 0;
//        pbEnd   = 0;
        return Result;
    }

    ULONG HeadSize = *(PULONG)((ULONG_PTR)pvDecompressed + sizeof(szMagic));

    pbBegin = (PBYTE)pvDecompressed + HeadSize + sizeof(szMagic);
    pbEnd   = (PBYTE)pvDecompressed + *pOutSize;

    return Result;

#else
    return Result == 0 ? Result : OldDecompressFile(pvDecompressed, pOutSize, pvCompressed, InSize, SkipBytes, OutBytes);
#endif
}

#if HAVE_COMPRESS

ASM
LONG
FASTCALL
OldLoadFileInternal(
    PVOID,
    PVOID,
    PVOID,
    PCHAR,
    PCHAR,
    ULONG,
    ULONG
)
{
    ASM_DUMMY_AUTO();
}

LONG
FASTCALL
LoadFileInternal(
    PVOID This,
    PVOID,
    PVOID pvBuffer,
    PCHAR pszArcPath,
    PCHAR pszFileName,
    ULONG v1,
    ULONG v2
)
{
    FILE *fp = _wfopen(LOG_FILE, L"ab+");
    if (fp)
    {
        fprintf(fp, "%s @ %s\r\n", pszFileName, pszArcPath);
        fclose(fp);
    }

    SetWindowTextA(*(HWND *)0x53FFC8, pszFileName);
    return OldLoadFileInternal(This, 0, pvBuffer, pszArcPath, pszFileName, v1, v2);
}

#endif // HAVE_COMPRESS

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    FILE *fp;

    fp = _wfopen(LOG_FILE, L"ab");
    if (fp)
    {
        SYSTEMTIME st;

        GetLocalTime(&st);
        fprintf(
            fp,
            "%02d:%02d:%02d: code = %08X, addr = %08X\r\n",
            st.wHour, st.wMinute, st.wSecond,
            ExceptionInfo->ExceptionRecord->ExceptionCode,
            ExceptionInfo->ExceptionRecord->ExceptionAddress
        );

        fclose(fp);
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

VOID Init()
{
    HMODULE hModule;
    static CHAR szSplitter[] = ",.°¢°£:;?!\"°„°§°¢°££¨£Æ£∫£ª£ø£°©a©b©\]})£©°≥£›£˝°µ°∑°π°ª°ø°Æ°∞";
/*
    WCHAR  end;
    PWCHAR lpCmdLine;

    lpCmdLine = GetCommandLineW();
    end = *lpCmdLine++ == '"' ? '"' : ' ';
    while (*lpCmdLine && *lpCmdLine != end) ++lpCmdLine;
    if (*++lpCmdLine)
    {
        while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;
    }

    if (*lpCmdLine != 0)
    {
        if (CHAR_UPPER2W(*(PULONG)lpCmdLine) == TAG2W('JP'))
            g_bForceShiftJis = TRUE;

        do
        {
            lpCmdLine[0] = lpCmdLine[2];
        } while (lpCmdLine++[2] != 0);
    }
*/
//    AddVectoredExceptionHandler(TRUE, VectoredHandler);

    INTEL_STATIC MEMORY_PATCH p[] =
    {
        { 0x07,  1, 0x23947 },
        { 0xEB,  1, 0x6CE8A },
        { 0x00,  1, 0x225AD },      // if greater then TextOutW  0042230A
        { 0x00,  1, 0x2367B },      // same

#if HAVE_COMPRESS
        // MEDIASUBTYPE_MPEG1System -> MEDIASUBTYPE_Avi
        { (ULONG_PTR)&MEDIASUBTYPE_Avi, sizeof(MEDIASUBTYPE_Avi), 0xA2CC8 },
#endif

        // char set
        { GB2312_CHARSET, 1, 0x22011 },
        { GB2312_CHARSET, 4, 0x21F7A },
        { GB2312_CHARSET, 4, 0x234C6 },

        // font
        { STRTOULONG(BGI_FONT_1), 4, 0x49F56 },
        { STRTOULONG(BGI_FONT_2), 4, 0x49F60 },

        // misc
        { STRTOULONG(szSplitter), 4, 0x229F1 },
        { STRTOULONG(szSplitter), 4, 0x229FD },

        // window class
        { STRTOULONG(BGI_WINDOW_CLASS), 4, 0x4C5C1 },
        { STRTOULONG(BGI_WINDOW_CLASS), 4, 0x4C782 },
        { STRTOULONG(BGI_WINDOW_CLASS), 4, 0x65954 },

        // iat
        { (ULONG_PTR)MyCreateFontA,             4, 0xA1080 },
        { (ULONG_PTR)MyGetFileAttributesA,      4, 0xA122C },
        { (ULONG_PTR)MyCreateFileA,             4, 0xA129C },
        { (ULONG_PTR)MyFindFirstFileA,          4, 0xA1210 },
        { (ULONG_PTR)MyFindNextFileA,           4, 0xA1214 },
        { (ULONG_PTR)MyFindClose,               4, 0xA121C },
        { (ULONG_PTR)MyTextOutA,                4, 0xA1078 },
    };

    INTEL_STATIC MEMORY_FUNCTION_PATCH f[] =
    {
        { JUMP, 0x4EDB0, CheckOSDefaultLangID },

#if HOOK_PARSE_SCRIPT
        { JUMP, 0x525D8, BGI_ReadDword,         0, OldBGI_ReadDword },
#endif
        
        { JUMP, 0x47E60, DecompressFile,        3, OldDecompressFile        },

#if HOOK_LOAD_FILE
        { JUMP, 0x052F0, LoadFileInternal,      3, OldLoadFileInternal      },
#endif

#if HAVE_SUPPORT_AUDIO
        { JUMP, 0x79860, my_ov_open_callbacks,  0, old_ov_open_callbacks    },
        { JUMP, 0x7B370, my_ov_read,            1, old_ov_read              },
        { JUMP, 0x7AD40, my_ov_pcm_seek,        3, old_ov_pcm_seek          },
        { JUMP, 0x79760, my_ov_clear,           0, old_ov_clear             },

#endif
    };

    hModule = GetModuleHandleW(NULL);
    PatchMemory(p, countof(p), f, countof(f), hModule);

#if HAVE_SUPPORT_AUDIO

    vorbis_func.ov_open_callbacks   = old_ov_open_callbacks;
    vorbis_func.ov_read             = old_ov_read;
    vorbis_func.ov_pcm_seek         = old_ov_pcm_seek;
    vorbis_func.ov_clear            = old_ov_clear;

#endif

    SetExecuteDirectoryAsCurrentW();
    g_bForceShiftJis = IsPathExistsW(L"JP");
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            CMem::CreateGlobalHeap();
            Init();

#if HOOK_LOAD_FILE
            DeleteFileW(LOG_FILE), setlocale(LC_ALL, ".936");
#endif
            break;

        case DLL_PROCESS_DETACH:
            CMem::DestroyGlobalHeap();
            break;
    }

    return TRUE;
}

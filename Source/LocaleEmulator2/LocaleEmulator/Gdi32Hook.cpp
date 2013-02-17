#include "stdafx.h"

HFONT NTAPI LeCreateFontIndirectExW(PENUMLOGFONTEXDVW penumlfex)
{
    ENUMLOGFONTEXDVW enumlfex;
    PLeGlobalData GlobalData = LeGetGlobalData();

    if (penumlfex != NULL) LOOP_ONCE
    {
        ULONG_PTR Charset;

        Charset = penumlfex->elfEnumLogfontEx.elfLogFont.lfCharSet;

        if (Charset != ANSI_CHARSET && Charset != DEFAULT_CHARSET)
            break;

        enumlfex = *penumlfex;
        enumlfex.elfEnumLogfontEx.elfLogFont.lfCharSet = GlobalData->GetLeb()->DefaultCharset;

        penumlfex = &enumlfex;
    }

    return GlobalData->CreateFontIndirectExW(penumlfex);
}

HDC NTAPI LeCreateCompatibleDC(HDC hDC)
{
    HFONT           Font;
    LOGFONTW        LogFont;
    PLeGlobalData   GlobalData = LeGetGlobalData();

    hDC = GlobalData->CreateCompatibleDC(hDC);
    if (hDC == NULL)
        return hDC;

    Font = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
    if (Font == NULL)
        return hDC;

    if (GetObjectW(Font, sizeof(LogFont), &LogFont) == 0)
        return hDC;

    CopyStruct(&LogFont.lfFaceName, GlobalData->GetLeb()->DefaultFaceName, sizeof(LogFont.lfFaceName));
    Font = CreateFontIndirectW(&LogFont);
    if (Font == NULL)
        return hDC;

    SelectObject(hDC, Font);
    DeleteObject(Font);

    return hDC;
}

int NTAPI LeEnumFontFamiliesExA(HDC hdc, LPLOGFONTA lpLogfont, FONTENUMPROCA lpProc, LPARAM lParam, DWORD dwFlags)
{
    ULONG_PTR       Charset;
    LOGFONTA        lf;
    PLeGlobalData   GlobalData = LeGetGlobalData();

    LOOP_ONCE
    {
        if (lpLogfont == NULL)
            break;

        Charset = lpLogfont->lfCharSet;
        if (Charset != ANSI_CHARSET && Charset != DEFAULT_CHARSET)
            break;

        lf = *lpLogfont;
        lf.lfCharSet = GlobalData->GetLeb()->DefaultCharset;

        lpLogfont = &lf;
    }

    return GlobalData->EnumFontFamiliesExA(hdc, lpLogfont, lpProc, lParam, dwFlags);
}

int NTAPI LeEnumFontFamiliesExW(HDC hdc, LPLOGFONTW lpLogfont, FONTENUMPROCW lpProc, LPARAM lParam, DWORD dwFlags)
{
    ULONG_PTR       Charset;
    LOGFONTW        lf;
    PLeGlobalData   GlobalData = LeGetGlobalData();

    LOOP_ONCE
    {
        if (lpLogfont == NULL)
            break;

        Charset = lpLogfont->lfCharSet;
        if (Charset != ANSI_CHARSET && Charset != DEFAULT_CHARSET)
            break;

        lf = *lpLogfont;
        lf.lfCharSet = GlobalData->GetLeb()->DefaultCharset;

        lpLogfont = &lf;
    }

    return GlobalData->EnumFontFamiliesExW(hdc, lpLogfont, lpProc, lParam, dwFlags);
}

int NTAPI LeEnumFontFamiliesA(HDC hdc, PCSTR lpLogfont, FONTENUMPROCA lpProc, LPARAM lParam)
{
    LOGFONTA lf;

    lf.lfCharSet = DEFAULT_CHARSET;
    StrCopyA(lf.lfFaceName, lpLogfont);

    return LeEnumFontFamiliesExA(hdc, &lf, lpProc, lParam, 0);
}

int NTAPI LeEnumFontFamiliesW(HDC hdc, PCWSTR lpLogfont, FONTENUMPROCW lpProc, LPARAM lParam)
{
    LOGFONTW lf;

    lf.lfCharSet = DEFAULT_CHARSET;
    StrCopyW(lf.lfFaceName, lpLogfont);

    return LeEnumFontFamiliesExW(hdc, &lf, lpProc, lParam, 0);
}

NTSTATUS LeGlobalData::HookGdi32Routines(PVOID Gdi32)
{
    MEMORY_FUNCTION_PATCH f[] =
    {
        EAT_HOOK_JUMP_HASH(Gdi32, GDI32_CreateFontIndirectExW,  LeCreateFontIndirectExW,    HookStub.StubCreateFontIndirectExW),
        EAT_HOOK_JUMP_HASH(Gdi32, GDI32_CreateCompatibleDC,     LeCreateCompatibleDC,       HookStub.StubCreateCompatibleDC),
        EAT_HOOK_JUMP_HASH(Gdi32, GDI32_EnumFontFamiliesExA,    LeEnumFontFamiliesExA,      HookStub.StubEnumFontFamiliesExA),
        EAT_HOOK_JUMP_HASH(Gdi32, GDI32_EnumFontFamiliesExW,    LeEnumFontFamiliesExW,      HookStub.StubEnumFontFamiliesExW),

        EAT_HOOK_JUMP_HASH_NULL(Gdi32, GDI32_EnumFontFamiliesA, LeEnumFontFamiliesA),
        EAT_HOOK_JUMP_HASH_NULL(Gdi32, GDI32_EnumFontFamiliesW, LeEnumFontFamiliesW),
    };

    return Nt_PatchMemory(NULL, 0, f, countof(f), Gdi32);
}

NTSTATUS LeGlobalData::UnHookGdi32Routines()
{
    Nt_RestoreMemory(&HookStub.StubCreateFontIndirectExW);
    Nt_RestoreMemory(&HookStub.StubCreateCompatibleDC);
    Nt_RestoreMemory(&HookStub.StubEnumFontFamiliesExA);
    Nt_RestoreMemory(&HookStub.StubEnumFontFamiliesExW);

    return 0;
}

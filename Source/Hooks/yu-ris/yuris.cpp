#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "COMCTL32.lib")

#include "yuris.h"
#include "my_commsrc.h"

#define DEFAULT_FACE_NAME L"ºÚÌå"

Int WINAPI MyMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
    ULONG CodePage, Length;
    PWCHAR pWText, pWCaption;

    Length = StrLengthA(lpText);
    pWText = (PWCHAR)AllocStack(Length * sizeof(*pWText));

    if (IsShiftJISString(lpText, -1))
        CodePage = CP_SHIFTJIS;
    else
        CodePage = CP_GB2312;

    MultiByteToWideChar(CodePage, 0, lpText, -1, pWText, Length);

    Length = StrLengthA(lpCaption);
    pWCaption = (PWCHAR)AllocStack(Length * sizeof(*pWCaption));

    if (IsShiftJISString(lpCaption, -1))
        CodePage = CP_SHIFTJIS;
    else
        CodePage = CP_GB2312;

    MultiByteToWideChar(CodePage, 0, lpCaption, -1, pWCaption, Length);

    return MessageBoxW(hWnd, pWText, pWCaption, uType);
}

HFONT WINAPI MyCreateFontIndirectA(LOGFONTA *lplf)
{
    LOGFONTW lf;

    CopyStruct(&lf, lplf, sizeof(*lplf) - sizeof(lplf->lfFaceName));
    lf.lfCharSet = GB2312_CHARSET;
    CopyStruct(lf.lfFaceName, DEFAULT_FACE_NAME, sizeof(DEFAULT_FACE_NAME));

    return CreateFontIndirectW(&lf);
}

BOOL WINAPI MyTextOutA(HDC hDC, int nXStart, int nYStart, LPCTSTR lpString, int cbCount)
{
    BOOL    r;
    WCHAR   c, ch[0x100];
    ULONG   CodePage;

    CodePage = CP_GB2312;
    if (cbCount > 2 && IsShiftJISString((PCHAR)lpString, cbCount))
    {
        CodePage = CP_SHIFTJIS;
    }
    else if (cbCount == 2)
    {
        c = *(PWCHAR)lpString;
        switch (c)
        {
            case SWAPCHAR('¡Ñ'):
                ch[0] = 0x266A;
                goto SKIP_CONV;

            default:
                if (IsShiftJISChar(SWAPCHAR(c)))
                    CodePage = CP_SHIFTJIS;
                goto NOT_CHANGE_CHAR;
        }
    }

NOT_CHANGE_CHAR:
    CodePage = MultiByteToWideChar(CodePage, 0, lpString, cbCount, ch, countof(ch));

SKIP_CONV:

    r = TextOutW(hDC, nXStart, nYStart, ch, CodePage);

    return r;
}

BOOL WINAPI MySetWindowTextA(HWND hWnd, LPCSTR lpString)
{
    ULONG Length, CP;
    PWCHAR pszString;

    Length = StrLengthA(lpString);
    pszString = (PWCHAR)AllocStack(Length * sizeof(*pszString));
    CP = IsShiftJISString(lpString, Length) ? CP_SHIFTJIS : CP_GB2312;
//    CP = CP_SHIFTJIS;
    MultiByteToWideChar(CP, 0, lpString, Length + 1, pszString, Length * 2);

    return SetWindowTextW(hWnd, pszString);
}

HWND WINAPI MyCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    PWCHAR pszClass, pszWindow;
    ULONG Length, CP;

    Length = StrLengthA(lpClassName);
    pszClass = (PWCHAR)AllocStack(Length * 2);
    CP = CP_SHIFTJIS;
    MultiByteToWideChar(CP, 0, lpClassName, Length + 1, pszClass, Length * 2);

    Length = StrLengthA(lpWindowName);
    pszWindow = (PWCHAR)AllocStack(Length * 2);
    MultiByteToWideChar(CP, 0, lpWindowName, Length + 1, pszWindow, Length * 2);

    return CreateWindowExW(dwExStyle, pszClass, pszWindow, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

Void Init()
{
    static bool LeadByteTable[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0
    };

    MEMORY_PATCH p[] =
    {
        // misc
        { STRTOULONG("save_sc\\"), 4, 0x11371C },

        { (ULONG_PTR)LeadByteTable, sizeof(LeadByteTable), 0x1130A0 },

        // iat
        { (ULONG_PTR)MyTextOutA,            4, 0x9A8040 },
        { (ULONG_PTR)MyCreateFontIndirectA, 4, 0x9A803C },
        { (ULONG_PTR)MyMessageBoxA,         4, 0x9A8394 },
    };
/*
    MEMORY_FUNCTION_PATCH f[] =
    {
//        { CALL, 0x3E621, MyCreateWindowExA, 0x01 },
        { CALL, 0x47B21, MySetWindowTextA, 0x01 },
    };
*/
    HMODULE hModule = GetModuleHandleW(0);

    PatchMemory(p, countof(p), NULL, 0, hModule);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            Init();            
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

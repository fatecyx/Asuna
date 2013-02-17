// ¤¯¥ÎÒ»½Û¹£
#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "gal_common.h"
#include "TextHandler.h"
#include "Mem.cpp"

OVERLOAD_OP_NEW

#define hInvalid (HKEY)-2

CTextHandler *g_Text;

BOOL
WINAPI
MyTextOutA(
    HDC     hDC,
    int     nXStart,
    int     nYStart,
    LPCTSTR lpString,
    int     cbString
)
{
    WChar szText[0x200];
    UInt  CodePage;

    CodePage = CP_GB2312;
    if (cbString > 1 && IsShiftJISString(lpString, cbString))
        CodePage = CP_SHIFTJIS;

    cbString = MultiByteToWideChar(CodePage, 0, lpString, cbString, szText, countof(szText));

    return TextOutW(hDC, nXStart, nYStart, szText, cbString);
}

HFONT WINAPI MyCreateFontIndirectA(LOGFONTA *lplf)
{
    LOGFONTW lf;
    static WChar szFaceName[LF_FACESIZE] = L"ºÚÌå";

    CopyStruct(&lf, lplf, GetStructMemberOffset(LOGFONTA, lfHeight, lfFaceName));
    CopyStruct(lf.lfFaceName, szFaceName, sizeof(lf.lfFaceName));
    lf.lfCharSet = GB2312_CHARSET;

    return CreateFontIndirectW(&lf);
}

BOOL
WINAPI
MyInsertMenuA(
    HMENU    hMenu,
    UINT     uPosition,
    UINT     uFlags,
    UINT_PTR uIDNewItem,
    LPCSTR   lpNewItem
)
{
    if ((uFlags & MF_OWNERDRAW) == 0 && (uFlags & MF_BITMAP) == 0)
    {
        UInt Length, CodePage;
        PWChar pszNewItem;

        Length = StrLenA(lpNewItem) + 1;
        pszNewItem = (PWChar)_alloca(Length * 2);

        CodePage = IsShiftJISString(lpNewItem, -1) ? CP_SHIFTJIS : CP_ACP;
        MultiByteToWideChar(CodePage, 0, lpNewItem, -1, pszNewItem, Length);
        lpNewItem = (LPCSTR)pszNewItem;
    }

    return InsertMenuW(hMenu, uPosition, uFlags, uIDNewItem, (LPWSTR)lpNewItem);
}

int
WINAPI
MyMessageBoxA(
    HWND   hWnd,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT   uType
)
{
    PWChar pszText, pszCaption;
    UInt CodePage, Length;

    Length   = StrLenA(lpText) + 1;
    pszText  = (PWChar)_alloca(Length * 2);
    CodePage = IsShiftJISString(lpText, -1) ? CP_SHIFTJIS : CP_ACP;
    MultiByteToWideChar(CodePage, 0, lpText, -1, pszText, Length);

    Length      = StrLenA(lpCaption) + 1;
    pszCaption  = (PWChar)_alloca(Length * 2);
    CodePage    = IsShiftJISString(lpCaption, -1) ? CP_SHIFTJIS : CP_ACP;
    MultiByteToWideChar(CodePage, 0, lpCaption, -1, pszCaption, Length);

    return MessageBoxW(hWnd, pszText, pszCaption, uType);
}

ASM PChar OldSkipText()
{
    ASM_DUMMY(6);
    ASM_UNIQUE();
}

PChar SkipText()
{
    PChar pszText;
    Int   Length;
    WChar szTextBuffer[0x500];
    CTextHandler *pText;

    pszText = OldSkipText();
/*
    if ((Int_Ptr)pszText - ROUND_DOWN((Int_Ptr)pszText, 64 * 1024) < 0x50)
        return pszText;
*/
    static Char s_szBuffer[0x500];

    pText = g_Text;
    if (pText == NULL)
        return pszText;

    Length = StrLenA(pszText);
    if (Length == 0)
        return pszText;

    Length = pText->GetText(szTextBuffer, sizeof(szTextBuffer), pszText - 0x50, Length + 0x50);
    if (Length == 0)
        return pszText;

    Length = WideCharToMultiByte(CP_GB2312, 0, szTextBuffer, Length / 2, s_szBuffer, countof(s_szBuffer), NULL, NULL);
    s_szBuffer[Length] = 0;

    return s_szBuffer;
}

LSTATUS
WINAPI
MyRegOpenKeyExA(
    HKEY   hKey,
    PChar  lpSubKey,
    DWORD  ulOptions,
    REGSAM samDesired,
    PHKEY  phkResult
)
{
    Int32 Length;
    LSTATUS Status;
    static Char szKeyLM[] = "SOFTWARE\\BLACKPACKAGE-TRY\\J6WIN\\1.0";
    static Char szKeyPath[] = "SOFTWARE\\MICROSOFT\\WINDOWS\\CURRENTVERSION\\APP PATHS\\J6WIN.EXE";

    Status = RegOpenKeyExA(hKey, lpSubKey, ulOptions, samDesired, phkResult);
    if (Status == ERROR_SUCCESS)
        return Status;

    if (hKey != HKEY_LOCAL_MACHINE)
        return Status;

    Length = StrLenA(lpSubKey);
    if (Length != sizeof(szKeyPath) - 1 && Length != sizeof(szKeyLM) - 1)
        return Status;

    StringUpperA(lpSubKey);

    if ((Length == sizeof(szKeyLM)   - 1 && !memcmp(lpSubKey, szKeyLM, sizeof(szKeyLM))) ||
        (Length == sizeof(szKeyPath) - 1 && !memcmp(lpSubKey, szKeyPath, sizeof(szKeyPath))))
    {
        if (phkResult != NULL)
            *phkResult = hInvalid;

        return ERROR_SUCCESS;
    }

    return Status;
}

LSTATUS
WINAPI
MyRegQueryValueExA(
    HKEY    hKey,
    PChar   lpValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE  lpData,
    LPDWORD lpcbData
)
{
    LSTATUS Status;

    if (hKey == hInvalid)
    {
        if (lpValueName[4] != 0 && lpValueName[3] != 0)
            return ERROR_FILE_NOT_FOUND;

        switch ((*(PUInt32)lpValueName & 0xDFDFDFDF))
        {
            case TAG4('PATH'):
                if (lpData != NULL)
                {
                    Status = GetExecuteDirectoryA((PChar)lpData, MAX_PATH);
                    ((PChar)lpData)[--Status] = 0;
                    if (lpcbData != NULL)
                        *lpcbData = Status;
                }
                break;

            case TAG3('VER'):
                if (lpcbData != NULL)
                    *lpcbData = 4;
                if (lpData != NULL)
                {
                    *(PUInt32)lpData = TAG4('1.00');
                    lpData[4] = 0;
                }
                break;
        }

        return ERROR_SUCCESS;
    }

    Status = RegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);

    return Status;
}

LSTATUS WINAPI MyRegCloseKey(HKEY hKey)
{
    return hKey == hInvalid ? ERROR_SUCCESS : RegCloseKey(hKey);
}

Void InitText()
{
    BOOL   bResult;
    PBYTE  pbBuffer;
    DWORD  dwSize;
    HANDLE hFile;
    CMem   mem;

    do
    {
        hFile = CreateFileW(L"j6.sc",
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
        if (hFile == INVALID_HANDLE_VALUE)
            break;

        dwSize = GetFileSize(hFile, NULL);
        pbBuffer = (PByte)mem.Alloc(dwSize);
        if (pbBuffer == NULL)
        {
            CloseHandle(hFile);
            break;
        }

        bResult = ReadFile(hFile, pbBuffer, dwSize, &dwSize, NULL);
        CloseHandle(hFile);

        if (bResult)
        {
            if (g_Text)
                delete g_Text;

            g_Text = new CTextHandler;
            if (g_Text)
            {
                if (g_Text->Init(pbBuffer, dwSize) == False)
                {
                    delete g_Text;
                    g_Text = NULL;
                }
            }
        }

        mem.Free(pbBuffer);

    } while (0);
}

Void Init()
{
    WChar  szPath[MAX_PATH];

    GetExecuteDirectoryW(szPath, countof(szPath));
    SetCurrentDirectoryW(szPath);

    InitText();

    SPatch p[] =
    {
        // crack
        { 0xEB,                         1, 0x48CBC },

        // bound
        { 0x0000FF80,                   4, 0x62F00 },
        { 0x0000FF80,                   4, 0x62F30 },
        { 0x0000FF80,                   4, 0x62F60 },
        { 0x0000FF80,                   4, 0x62F90 },
        { 0x0000FF80,                   4, 0x62FC0 },

        { (ULong)MyTextOutA,            4, 0x5C078 },
        { (ULong)MyCreateFontIndirectA, 4, 0x5C060 },
        { (ULong)MyMessageBoxA,         4, 0x5C3DC },
        { (ULong)MyInsertMenuA,         4, 0x5C2B4 },
        { (ULong)MyRegOpenKeyExA,       4, 0x5C000 },
        { (ULong)MyRegQueryValueExA,    4, 0x5C010 },
        { (ULong)MyRegCloseKey,         4, 0x5C00C },
    };
    SFuncPatch f[] =
    {
        { JUMP, 0x30E90, SkipText, 1, OldSkipText },
    };

    PatchMemory(p, countof(p), f, countof(f), GetModuleHandleW(NULL));
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    if (ulReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hInstance);
        Init();
    }
    else if (ulReason == DLL_PROCESS_DETACH)
        safe_delete(g_Text);

    return True;
}
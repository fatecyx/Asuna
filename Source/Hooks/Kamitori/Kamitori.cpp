// Éñ’ñ¤ê¥¢¥ë¥±¥ß©`¥Þ¥¤¥¹¥¿©`
#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "msvcrt.lib")
#pragma comment(lib, "ntdll.lib")

#include <Windows.h>
#include <shlobj.h>
#include "my_headers.h"
#include "gal_common.h"

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    FILE *fp = fopen(".\\log.txt", "ab+");

// 005568F2
    if (fp)
    {
        fprintf(
            fp,
            "code = %X\n"
            "addr = %p\n",
            ExceptionInfo->ExceptionRecord->ExceptionCode,
            ExceptionInfo->ExceptionRecord->ExceptionAddress);
        fclose(fp);
    }

    return EXCEPTION_CONTINUE_EXECUTION;
}

/*
font
 lea     ecx, dword ptr [esi+14938+0x54] + 0x28
 [esi+57F30]+114F
 esi+4D7C+464
 [[5c9bc8]+4D7C+464+28]+6C1

cfg
 esi+28+35*4
 [[5c9bc8]+0A4B7C+4+28]+35*4
*/

HANDLE WINAPI MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    DWORD Length;
    WCHAR szFileName[MAX_PATH];

    Length = MultiByteToWideChar(CP_ACP, 0, lpFileName, -1, szFileName, countof(szFileName));

    return CreateFileW(szFileName, dwDesiredAccess, dwShareMode | FILE_SHARE_READ, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HFONT WINAPI MyCreateFontIndirectA(LOGFONTA *lplf)
{
    LOGFONTW lf;

    CopyStruct(&lf, lplf, GetStructMemberOffset(LOGFONTA, lfHeight, lfFaceName));

    lf.lfCharSet = SHIFTJIS_CHARSET;
    MultiByteToWideChar(
        IsShiftJISString(lplf->lfFaceName, -1) ? CP_SHIFTJIS : CP_ACP,
        0,
        lplf->lfFaceName,
        sizeof(lplf->lfFaceName),
        lf.lfFaceName,
        countof(lf.lfFaceName));

    return CreateFontIndirectW(&lf);
}

HWND WINAPI MyCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    RECT    rcWordArea;
    ULONG   Length;
    LPWSTR  pszClassName, pszWindowName;

    Length = StrLengthA(lpClassName) + 1;
    pszClassName = (LPWSTR)AllocStack(Length * sizeof(WCHAR));
    MultiByteToWideChar(
        IsShiftJISString(lpClassName, -1) ? CP_SHIFTJIS : CP_ACP,
        0,
        lpClassName,
        -1,
        pszClassName,
        Length);

    Length = StrLengthA(lpWindowName) + 1;
    pszWindowName = (LPWSTR)AllocStack(Length * sizeof(WCHAR));
    MultiByteToWideChar(
        IsShiftJISString(lpWindowName, -1) ? CP_SHIFTJIS : CP_ACP,
        0,
        lpWindowName,
        -1,
        pszWindowName,
        Length);

    if (SystemParametersInfoW(SPI_GETWORKAREA, 0, &rcWordArea, 0))
    {
        X = ((rcWordArea.right - rcWordArea.left) - nWidth) / 2;
        Y = ((rcWordArea.bottom - rcWordArea.top) - nHeight) / 2;
    }

    return CreateWindowExW(dwExStyle, pszClassName, pszWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

ASM VOID SetDefaultValueScreenMode()
{
    INLINE_ASM
    {
        mov  dword ptr [ebp-0x114], 1;
        ret;
    }
}

BOOL WINAPI MySHGetSpecialFolderPathA(HWND hWndOwner, LPSTR lpszPath, INT nFolder, BOOL fCreate)
{
    if (nFolder != CSIDL_APPDATA)
        return SHGetSpecialFolderPathA(hWndOwner, lpszPath, nFolder, fCreate);

    return !!GetExecuteDirectoryA(lpszPath, MAX_PATH);
}

HRESULT WINAPI MySHGetFolderPathA(HWND hWndOwner, INT nFolder, HANDLE hToken, DWORD dwFlags, LPTSTR pszPath)
{
    if ((nFolder & ~CSIDL_FLAG_MASK) != CSIDL_LOCAL_APPDATA)
        return SHGetFolderPathA(hWndOwner, nFolder, hToken, dwFlags, pszPath);

    return !GetExecuteDirectoryA(pszPath, MAX_PATH);
}

FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    if ((ULONG_PTR)lpProcName & 0xFFFF0000)
    {
        switch (HashAPI(lpProcName))
        {
            case 0xBACE91A1: return (FARPROC)MySHGetFolderPathA;
        }
    }

    return GetProcAddress(hModule, lpProcName);
}

VOID Init()
{
    HMODULE hModule;

    INTEL_STATIC MEMORY_PATCH p[] =
    {
        // crack
        { 0x81,         1, 0x11BC0 },   // Error msg box
        { 0x00,         1, 0x55058 },   // Error msg box

        { 0x09EBC033,   4, 0x5171E },   // failed to find font

        // iat
        { (ULONG_PTR)MyGetProcAddress,          4, 0x1740C8 },
        { (ULONG_PTR)MyCreateFontIndirectA,     4, 0x174034 },
        { (ULONG_PTR)MyCreateWindowExA,         4, 0x1742B4 },
        { (ULONG_PTR)MyCreateFileA,             4, 0x174224 },
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        { CALL, 0x71761, SetDefaultValueScreenMode, 1 },
    };

    hModule = GetModuleHandleW(NULL);
    PatchMemory(p, countof(p), f, countof(f), hModule);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID lpReserved)
{
    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            Init();
            break;
    }

    return TRUE;
}
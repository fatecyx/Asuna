#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,EWR")
#pragma comment(linker, "/MERGE:.rdata=.Kaede")
#pragma comment(linker, "/MERGE:.data=.Kaede")
#pragma comment(lib, "Shlwapi.lib")

#include "VSHook.h"
#include <shlwapi.h>
#include "nt_api.h"

int WINAPI DllMain(HANDLE HDllHandle, DWORD _Reason, LPVOID _Reserved)
{
    static BOOL bWritten = FALSE;

    if (_Reason != DLL_PROCESS_ATTACH || bWritten == TRUE)
        return TRUE;

    DWORD dwOld, dwOld2;
    LPVOID lpBaseAddress;

    lpBaseAddress = GetModuleHandleA(0);
    if (lpBaseAddress == NULL)
        return TRUE;

    bWritten = TRUE;

    PATCH_FRAME(patch_VSClient, countof(patch_VSClient), 0, 0, lpBaseAddress, dwOld, dwOld2);
    
    return TRUE;
}

BOOL WINAPI MyRegisterHotKey(HWND hWnd, int id, UINT fsModifiers, UINT vk)
{
    return TRUE;
}

FORCEINLINE BOOL IsFileExist(LPSTR lpFileName)
{
    return GetFileAttributesA(lpFileName) != -1;
}

HANDLE WINAPI MyCreateFileA(LPSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    CHAR c;
    DWORD dwLength;
    HANDLE hFile;
    
    dwLength = lstrlenA(lpFileName) - 1;
    c = lpFileName[dwLength];
    lpFileName[dwLength] = '_';
    if (IsFileExist(lpFileName))
    {
        hFile = CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
        lpFileName[dwLength] = c;
    }
    else
    {
        lpFileName[dwLength] = c;
        hFile = CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    
    return hFile;
}

FILE* myfopen(char * _Filename, const char * _Mode)
{
    CHAR c;
    FILE *fp;
    DWORD dwLength;

    dwLength = lstrlenA(_Filename) - 1;
    c = _Filename[dwLength];
    _Filename[dwLength] = '_';
    if (IsFileExist(_Filename))
    {
        fp = fopen(_Filename, _Mode);
        _Filename[dwLength] = c;
    }
    else
    {
        _Filename[dwLength] = c;
        fp = fopen(_Filename, _Mode);
    }

    return fp;
}
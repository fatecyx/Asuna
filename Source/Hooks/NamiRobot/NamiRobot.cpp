#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,EWR")
#pragma comment(linker, "/MERGE:.rdata=.Kaede")
#pragma comment(linker, "/MERGE:.data=.Kaede")

#include <Windows.h>
#include <Winerror.h>
#include "nt_api.h"

LONG WINAPI MyRegCreateKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition)
{
	if (wcsstr(lpSubKey, L"\\MenuExt\\"))
	{
		return 1;
	}

	return RegCreateKeyExW(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
}

FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    if ((int)lpProcName > 0xFFFF)
    {
        if (HashAPI(lpProcName) == 0xDA47568D)
        {
            return (FARPROC)MyRegCreateKeyExW;
        }
    }
	
    return GetProcAddress(hModule, lpProcName);
}
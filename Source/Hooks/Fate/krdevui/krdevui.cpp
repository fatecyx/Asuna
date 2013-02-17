#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")

#include "krdevui.h"
#include "my_mem.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call != DLL_PROCESS_ATTACH)
		return TRUE;

    static BOOL bWrite = FALSE;

	DisableThreadLibraryCalls(hModule);

	if (bWrite == FALSE)
	{
		ULONG  ulProtectSize;
		LPVOID lpBaseAddress;
		DWORD dwOld;

		lpBaseAddress = (LPVOID)GetModuleHandleA("krdevui.dll");
		if (lpBaseAddress == NULL)
			return TRUE;
		
		bWrite = TRUE;

		ulProtectSize = *(LPDWORD)((DWORD)lpBaseAddress + *(LPDWORD)((DWORD)lpBaseAddress + 0x3C) + 0x50);

		if (VirtualProtect(lpBaseAddress, ulProtectSize, PAGE_EXECUTE_READWRITE, &dwOld) == TRUE)
		{
			PATCH_FRAME(0, 0, func, countof(func), lpBaseAddress);
		}
	}

    return TRUE;
}

BOOL WINAPI MyFindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
{
	BOOL bResult;
	WIN32_FIND_DATAW wfd;

	bResult = FindNextFileW(hFindFile, &wfd);
	memcpy(lpFindFileData, &wfd, sizeof(wfd) - sizeof(wfd.cFileName) - sizeof(wfd.cAlternateFileName));
	WideCharToMultiByte(932, 0, wfd.cFileName, sizeof(wfd.cFileName), lpFindFileData->cFileName, sizeof(lpFindFileData->cFileName), NULL, NULL);
	
	return bResult;
}

HANDLE WINAPI MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	if (dwCreationDisposition != OPEN_EXISTING)
		return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

	HANDLE hFile;
	WCHAR szFile[MAX_PATH];

	MultiByteToWideChar(932, 0, lpFileName, -1, szFile, sizeof(szFile));
	hFile = CreateFileW(szFile, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

	return hFile;
}

int WINAPI MyMultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar)
{
	return MultiByteToWideChar(932, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar);
}
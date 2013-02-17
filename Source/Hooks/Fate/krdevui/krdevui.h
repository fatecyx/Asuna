#ifndef _KRDEVUI_H_
#define _KRDEVUI_H_

#include <Windows.h>
#include "my_common.h"

BOOL   WINAPI MyFindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);
HANDLE WINAPI MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, IN DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
int    WINAPI MyMultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);

TFuncPatch func[] =
{
	{CALL, 0x1894D, (DWORD)MyCreateFileA, 0x00},
	{CALL, 0xE59E3, (DWORD)MyFindNextFileA, 0x00},
	{CALL, 0xEE655, (DWORD)MyMultiByteToWideChar, 0x00},
};

#endif /* _KRDEVUI_H_ */
#include <Windows.h>
#include <d3d8.h>

/*
extern "C"
{
	#include "../3rdText/7zAlloc.h"
	#include "../3rdText/LzmaDec.h"
	HANDLE hHeap = INVALID_HANDLE_VALUE;
}
*/

typedef DWORD (*READPAKFILE)(LPSTR lpszPak, LPSTR lpszFile, PBYTE *ppbOutBuffer);
DWORD __stdcall ReadPakFile(LPSTR lpszPak, LPSTR lpszFile, PBYTE *ppbOutBuffer);
DWORD __stdcall Decode(PBYTE pbSrc, PBYTE pbDest, DWORD dwSrcLen, DWORD dwDestLen);
BOOL MyPeekMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
DWORD ReadFileFromPak(LPSTR lpszPak, LPSTR lpszFile, PBYTE *ppbOutBuffer, 
					  LPSTR lpszPakNameBuffer, LPSTR lpszFormat, ...);

typedef struct _tagPakFileInfo
{
	BOOL	bIsCompressed;
	TCHAR	szFileName[0x18];
	DWORD	dwFileOffset;
	DWORD	dwFileSize;
} PakFileInfo;
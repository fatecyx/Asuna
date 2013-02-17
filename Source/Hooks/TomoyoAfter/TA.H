#ifndef _TA_H_
#define _TA_H_

#include <Windows.h>
#include "my_headers.h"
#include "BASS/bass.h"
#include "BASS/BASS_AAC.h"

#pragma pack(1)

typedef struct
{
    PBYTE pbBuffer;
    DWORD dwSize;
    DWORD dwMaxSize;
    DWORD dwWaste;
//    DWORD dwConflict;
    CHAR  szName[MAX_PATH];
} TCacheIndex;

typedef struct
{
    DWORD dwOffset;
    DWORD dwSize;
} TPakIndex;

typedef struct
{
    DWORD  dwSize;
    DWORD  dwOffset;
    DWORD  dwWaste;
    PBYTE  pbBuffer;
    DWORD  dwBufferSize;
} TMyHandle;

typedef struct
{
    PBYTE unknown;
    PBYTE pbRaw;
    Int32 iWidth;
    Int32 iHeight;
} TImagePointer;

#pragma pack()

Void    CDECL  SetCursorMask(TImagePointer *pIP, BYTE color1, BYTE color2, BYTE color3);

DWORD   WINAPI MyGetVersion();
DWORD   WINAPI GetVoiceIndex(IN OUT LPSTR lpSourceFile);
HANDLE  WINAPI MyFindFirstFileA(LPSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
BOOL    WINAPI MyFindClose(HANDLE hFindFile);
HANDLE  WINAPI MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
DWORD   WINAPI MySetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
BOOL    WINAPI MyReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
DWORD   WINAPI MyGetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
BOOL    WINAPI MyCloseHandle(HANDLE hObject);
BOOL    WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
BOOL    WINAPI MyGetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
HWND    WINAPI MyCreateWindowExA(IN DWORD dwExStyle, IN LPCSTR lpClassName, IN LPCSTR lpWindowName, IN DWORD dwStyle, IN int X, IN int Y, IN int nWidth, IN int nHeight, IN HWND hWndParent, IN HMENU hMenu, IN HINSTANCE hInstance, IN LPVOID lpParam);
FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName);
DWORD   WINAPI GetHandleType(HANDLE hFile);

#endif /* _TA_H_ */
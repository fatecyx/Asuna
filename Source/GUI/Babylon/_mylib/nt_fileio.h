#ifndef _NT_FILEIO_H_
#define _NT_FILEIO_H_

#include <Windows.h>
#include "nt_api.h"
#include "my_types.h"

_MY_C_HEAD_

/* My Functions */
//MY_NTLIB_DLL_EXPORT HANDLE   NTAPI Nt_GetCurrentModuleHandle();
//MY_NTLIB_DLL_EXPORT HANDLE   NTAPI Nt_GetCurrentDirectoryHandle();

HANDLE
Nt_CreateFileW(
    LPCWSTR			        lpFileName,
    DWORD			        dwDesiredAccess,
    DWORD			        dwShareMode,
    LPSECURITY_ATTRIBUTES	lpSecurityAttributes,
    DWORD			        dwCreationDisposition,
    DWORD			        dwFlagsAndAttributes,
    HANDLE			        hTemplateFile
);

BOOL
Nt_ReadFile(
    IN  HANDLE       hFile,
    IN  LPVOID       lpBuffer,
    IN  DWORD        nNumberOfBytesToRead,
    OUT LPDWORD      lpNumberOfBytesRead  OPTIONAL,
    IN  LPOVERLAPPED lpOverlapped         OPTIONAL
);

BOOL
Nt_WriteFile(
    IN  HANDLE       hFile,
    IN  PVOID        lpBuffer,
    IN  DWORD        nNumberOfBytesToWrite  OPTIONAL,
    OUT LPDWORD      lpNumberOfBytesWritten OPTIONAL,
    IN  LPOVERLAPPED lpOverlapped           OPTIONAL
);

DWORD
Nt_SetFilePointer(
    HANDLE hFile,
    LONG   lDistanceToMove,
    PLONG  lpDistanceToMoveHigh,
    DWORD  dwMoveMethod
);

NTSTATUS Nt_CloseHandle(HANDLE Handle);

BOOL Nt_SetEndOfFile(HANDLE hFile);

_MY_C_TAIL_

#if defined(UNICODE) || defined(_UNICODE)
    #define Nt_CreateFile          Nt_CreateFileW
#else
    #define Nt_CreateFile          Nt_CreateFileA
#endif /* UNICODE */

#endif /* _NT_FILEIO_H_ */
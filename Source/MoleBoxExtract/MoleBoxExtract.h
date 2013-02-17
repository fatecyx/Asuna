#ifndef _MOLEBOXEXTRACT_H_
#define _MOLEBOXEXTRACT_H_

#include <Windows.h>
#include "my_common.h"

typedef HANDLE (WINAPI *CREATEFILEA)(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
typedef BOOL   (WINAPI *READFILE)(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
typedef DWORD  (WINAPI *GETFILESIZE)(HANDLE hFile, LPDWORD lpFileSizeHigh);
typedef BOOL   (WINAPI *CLOSEHANDLE)(HANDLE hObject);
typedef HANDLE (WINAPI *FINDFIRSTFILEA)(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
typedef BOOL   (WINAPI *FINDNEXTFILEA)(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);
typedef BOOL   (WINAPI *FINDCLOSE)(HANDLE hFindFIle);

typedef struct
{
    LPSTR lpFileName;
    DWORD  Unknown;
    DWORD  dwSize;
    DWORD  Unknown2;
} TMoleBoxFile;

typedef struct
{
    DWORD dwAddressStart;
    DWORD dwAddressEnd;
} TSection;

int     WINAPI MyEntryPoint();
HMODULE WINAPI MyLoadLibraryExA(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
HMODULE WINAPI MyGetModuleHandleA(LPCSTR lpModuleName);
Void    WINAPI Extract(READFILE lpfnReadFile, GETFILESIZE lpfnGetFileSize, CREATEFILEA lpfnCreateFileA, TMoleBoxFile *lpNames, DWORD dwFileNum);
Void    WINAPI Extract2(TMoleBoxFile *pMoleBoxFile);
HRESULT WINAPI MyGetFileTime(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
BOOL    WINAPI MyCreateDirectory(LPCTSTR lpPathName);
DWORD   WINAPI MyCharUpperBuffA(LPSTR lpsz, DWORD cchLength);
LPVOID  WINAPI MyVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
BOOL    WINAPI MyVirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);
BOOL    WINAPI MyVirtualProtect( IN LPVOID lpAddress, IN SIZE_T dwSize, IN DWORD flNewProtect, OUT PDWORD lpflOldProtect );
FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName);
DWORD WINAPI MyGetFullPathNameA(IN LPSTR lpFileName, IN DWORD nBufferLength, OUT LPSTR lpBuffer, OUT LPSTR* lpFilePart);


#endif /* _MOLEBOXEXTRACT_H_ */
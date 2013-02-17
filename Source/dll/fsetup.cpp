//#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"

#if !defined(NtCurrentProcess)
    #define NtCurrentProcess() ((HANDLE)-1)
#endif

PBYTE
GetIATItem(
   PBYTE        pbBuffer,
   PBYTE        pbEnd,
   PULONG_PTR   pRVA,
   PULONG_PTR   pKey,
   LPWSTR       pDllName,
   LPSTR        pProcName
)
{
    PBYTE       pbDllStart, pbProcStart;
    ULONG_PTR   Value, Base;
    PULONG_PTR  pValuePointer[] = { pRVA, pKey };

    for (;;)
    {
        BYTE c = *pbBuffer;

        if (c != ' '  &&
            c != '\t' &&
            c != '\r' &&
            c != '\n')
        {
            break;
        }

        if (++pbBuffer >= pbEnd)
            return pbBuffer;
    }

    for (DWORD i = 0; i != _countof(pValuePointer); ++i)
    {
        Value = 0;
        while (*pbBuffer != '/')
        {
            BYTE c = *pbBuffer;

            if (pbBuffer > pbEnd || c == '\r' || c == '\n')
                return NULL;

            ++pbBuffer;

            if (c < 'z' && c > 'a')
                c &= 0xDF;

            if (c >= '0' && c <= '9')
                Base = '0';
            else if (c >= 'A' && c <= 'Z')
                Base = 'A' - 10;
            else
                return NULL;

            Value = (Value << 4) | (c - Base);
        }

        ++pbBuffer;
        *pValuePointer[i] = Value;
    }

    pbDllStart = pbBuffer;
    for (;;)
    {
        BYTE c = *pbBuffer;
        if (pbBuffer > pbEnd || c == '\r' || c == '\n')
            return NULL;

        ++pbBuffer;
        if (c == '/')
            break;
    }

    pbBuffer[-1] = 0;
    MultiByteToWideChar(
        CP_ACP,
        0,
        (LPSTR)pbDllStart,
        -1,
        pDllName,
        MAX_PATH);

    pbProcStart = pbBuffer;
    for (;;)
    {
        BYTE c = *pbBuffer;
        if (pbBuffer > pbEnd)
            return NULL;

        ++pbBuffer;
        if (c == '\r' || c == '\n' || c == 0)
            break;
    }

    Value = pbBuffer - pbProcStart - 1;
    CopyMemory(pProcName, pbProcStart, Value);
    pProcName[Value] = 0;

    for (;;)
    {
        BYTE c = *pbBuffer++;
        if (c == 0 || c == '\n')
            break;
    }

    return pbBuffer;
}

BOOL FixFakeIAT()
{
    BOOL        Result;
    DWORD       Length, BytesRead;
    WCHAR       szPath[MAX_PATH];
    LPWSTR      pFileName;
    HANDLE      hFile, hHeap;
    HMODULE     hModule;
    PVOID       pvBuffer;
    PBYTE       pbBuffer, pbEnd;

    ULONG_PTR   Rva, Key;
    CHAR        ProcName[MAX_PATH];

    hModule = GetModuleHandleW(NULL);
    Length = GetModuleFileNameW(hModule, szPath, _countof(szPath));
    if (Length == 0)
        return FALSE;

    pFileName = NULL;
    for (DWORD i = 0; i != Length; ++i)
    {
        if (szPath[i] == '.')
            pFileName = &szPath[i];
    }

    if (pFileName == NULL)
        pFileName = &szPath[Length];

    lstrcpyW(pFileName, L"_IAT.txt");

    hFile = CreateFileW(
                szPath,
                GENERIC_READ,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return FALSE;

    Length = GetFileSize(hFile, NULL);

    Result   = FALSE;
    pvBuffer = NULL;
    hHeap    = GetProcessHeap();
    for (BOOL __c = TRUE; __c; __c = FALSE)
    {
        pvBuffer = HeapAlloc(hHeap, 0, Length);
        if (pvBuffer == NULL)
            break;

        Result = ReadFile(hFile, pvBuffer, Length, &BytesRead, NULL);
        if (!Result || Length != BytesRead)
            break;

        pbBuffer = (PBYTE)pvBuffer;
        pbEnd    = pbBuffer + Length;

        for (;;)
        {
            DWORD OldProtection;

            pbBuffer = GetIATItem(pbBuffer, pbEnd, &Rva, &Key, szPath, ProcName);
            if (pbBuffer == NULL)
                break;

            Rva += (ULONG_PTR)hModule;
            Result = VirtualProtectEx(
                        NtCurrentProcess(),
                        (PVOID)Rva,
                        4,
                        PAGE_READWRITE,
                        &OldProtection);
            if (!Result)
                break;

            *(PULONG_PTR)Rva = (ULONG_PTR)GetProcAddress(GetModuleHandleW(szPath), ProcName) - Key;

            VirtualProtectEx(
                NtCurrentProcess(),
                (PVOID)Rva,
                4,
                OldProtection,
                &OldProtection);

            if (pbBuffer >= pbEnd)
            {
                Result = TRUE;
                break;
            }
        }
    }

    CloseHandle(hFile);
    if (pvBuffer != NULL)
        HeapFree(hHeap, 0, pvBuffer);

    return Result;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            return FixFakeIAT();

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

EXTC
BOOL
WINAPI
CreateProcessInternalA(
    HANDLE                  hToken,
    LPCSTR                  lpApplicationName,
    LPSTR                   lpCommandLine,
    LPSECURITY_ATTRIBUTES   lpProcessAttributes,
    LPSECURITY_ATTRIBUTES   lpThreadAttributes,
    BOOL                    bInheritHandles,
    DWORD                   dwCreationFlags,
    LPVOID                  lpEnvironment,
    LPCSTR                  lpCurrentDirectory,
    LPSTARTUPINFOA          lpStartupInfo,
    LPPROCESS_INFORMATION   lpProcessInformation,
    PHANDLE                 hNewToken
)
{
    return FALSE;
}

EXTC
BOOL
WINAPI
CreateProcessInternalW(
    HANDLE                  hToken,
    LPCWSTR                 lpApplicationName,
    LPWSTR                  lpCommandLine,
    LPSECURITY_ATTRIBUTES   lpProcessAttributes,
    LPSECURITY_ATTRIBUTES   lpThreadAttributes,
    BOOL                    bInheritHandles,
    DWORD                   dwCreationFlags,
    LPVOID                  lpEnvironment,
    LPCWSTR                 lpCurrentDirectory,
    LPSTARTUPINFOW          lpStartupInfo,
    LPPROCESS_INFORMATION   lpProcessInformation,
    PHANDLE                 hNewToken
    )
{
    return FALSE;
}
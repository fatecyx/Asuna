#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(lib, "Shlwapi.lib")

#define _INC_MALLOC

#include <malloc.h>
#include <Shlwapi.h>
#include <stdio.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"
#include "nt_api.h"

ASM HANDLE WINAPI _CreateFileW( __in LPCWSTR lpFileName, __in DWORD dwDesiredAccess, __in DWORD dwShareMode, __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes, __in DWORD dwCreationDisposition, __in DWORD dwFlagsAndAttributes, __in_opt HANDLE hTemplateFile )
{
    __asm
    {
        push ebp;
        mov  ebp, esp;
        mov  eax, dword ptr [CreateFileW];
        lea  eax, dword ptr [eax+5];
        jmp  eax;
    }
}

HANDLE WINAPI MyCreateFileW( __in LPCWSTR lpFileName, __in DWORD dwDesiredAccess, __in DWORD dwShareMode, __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes, __in DWORD dwCreationDisposition, __in DWORD dwFlagsAndAttributes, __in_opt HANDLE hTemplateFile )
{
    if (!lstrcmpiW(PathFindFileNameW(lpFileName), L"PS2 G00 1.1.DAT"))
    {
        MessageBoxA(0, 0, 0, 64);
    }
    return _CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

int WINAPI DllMain(HINSTANCE hInstance, unsigned long reason, void* lpReserved)
{
    FILE *fp;
    CHAR szModule[MAX_PATH];
    PIMAGE_DOS_HEADER        pDosHeader;
    PIMAGE_OPTIONAL_HEADER32 pOptionalHeader;
    PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor;

    fp = fopen("E:\\Desktop\\Source\\dll\\ta.def", "wb");
    pDosHeader = (PIMAGE_DOS_HEADER)GetModuleHandleA(0);
    pOptionalHeader = (PIMAGE_OPTIONAL_HEADER32)((PBYTE)pDosHeader + pDosHeader->e_lfanew + 4 + sizeof(IMAGE_FILE_HEADER));
    pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(pOptionalHeader->DataDirectory[1].VirtualAddress + (DWORD)pDosHeader);

    fprintf(fp, "EXPORTS\n");
    do
    {
		strcpy(szModule, (LPSTR)pImportDescriptor->Name + (DWORD)pDosHeader);

        if (szModule[0])
        {
            LPSTR *lpFuncName = (LPSTR *)((LPSTR)pImportDescriptor->OriginalFirstThunk + (DWORD)pDosHeader);

			rmext(szModule);
            while (*lpFuncName)
            {
                LPSTR lpName = *lpFuncName;

                if ((DWORD)lpName & 0x80000000)
                {
                    int i = (WORD)lpName;
                    fprintf(fp, "\t = %s.@%u\n", szModule, i);
                }
                else
                {
                    lpName += (DWORD)pDosHeader + 2;
                    fprintf(fp, "\t%s = %s.%s\n", lpName, szModule, lpName);
                }

                fflush(fp);
                ++lpFuncName;
            }
        }

        ++pImportDescriptor;
    } while (pImportDescriptor->FirstThunk);
    fclose(fp);

    ExitProcess(0);

	return TRUE;
}

VOID WINAPI myexit(UINT uExitCode)
{
    HMODULE hFilter;
    void (STDCALL *DllUnregisterServer)();
    hFilter = LoadLibraryA("CamtasiaFilters.dll");
    if (hFilter)
    {
        DllUnregisterServer = (void (STDCALL *)())GetProcAddress(hFilter, "DllUnregisterServer");
        if (DllUnregisterServer)
            DllUnregisterServer();
        FreeLibrary(hFilter);
    }
    ExitProcess(uExitCode);
}

FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    static BOOL bInit = FALSE;
    static HMODULE hDllModule, hKernel32Module;

    if (bInit == FALSE)
    {
        HMODULE hFilter;
        void (STDCALL *DllRegisterServer)();

        bInit = TRUE;

        hFilter = LoadLibraryA("CamtasiaFilters.dll");
        if (hFilter)
        {
            DllRegisterServer = (void (STDCALL *)())GetProcAddress(hFilter, "DllRegisterServer");
            if (DllRegisterServer)
                DllRegisterServer();
            FreeLibrary(hFilter);
        }
        hDllModule = GetModuleHandleA("cr.dll");
        hKernel32Module = GetModuleHandleA("KERNEL32.dll");
    }

    if ((DWORD)lpProcName > 0xFFFF && !lstrcmpA(lpProcName, "exit"))
    {
        return (FARPROC)myexit;
    }

    return GetProcAddress(hModule == hDllModule ? hKernel32Module : hModule, lpProcName);
}
#pragma comment(linker, "/ENTRY:EntryPoint")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "my_commsrc.h"

#pragma comment(linker, "/INCLUDE:__tls_used")

LONG _tls_addr;
VOID NTAPI TlsCallBackFunction(PVOID ModuleHandle, DWORD Reason, PVOID Reserved);
EXTC PIMAGE_TLS_CALLBACK _my_tls_callbacktbl[] = { TlsCallBackFunction, 0 };
EXTC IMAGE_TLS_DIRECTORY32 _tls_used = { (DWORD)&_tls_addr, (DWORD)&_tls_addr, (DWORD)&_tls_addr, (DWORD)_my_tls_callbacktbl, 0, 0};

Int WINAPI EntryPoint()
{
    NTSTATUS            Status;
    WCHAR               DllPathBuffer[MAX_NTPATH];
    UNICODE_STRING      DllFullPath;
    PROCESS_INFORMATION ProcessInformation;

    Nt_SetExeDirectoryAsCurrent();

    LOOP_ONCE
    {
        Status = Nt_CreateProcess(L"euphoria.exe", NULL, NULL, CREATE_SUSPENDED, NULL, &ProcessInformation);
        if (!NT_SUCCESS(Status))
            break;

        DllFullPath.Buffer = DllPathBuffer;
        DllFullPath.Length = Nt_GetExeDirectory(DllPathBuffer, countof(DllPathBuffer));

        *(PULONG64)&DllPathBuffer[DllFullPath.Length + 0] = TAG4W('euph');
        *(PULONG64)&DllPathBuffer[DllFullPath.Length + 4] = TAG4W('oria');
        *(PULONG64)&DllPathBuffer[DllFullPath.Length + 8] = TAG4W('_sc.');
        *(PULONG64)&DllPathBuffer[DllFullPath.Length + 12] = TAG3W('dll');

        DllFullPath.Length += CONST_STRLEN(L"euphoria_sc.dll");
        DllFullPath.Length *= sizeof(WCHAR);
        DllFullPath.MaximumLength = sizeof(DllPathBuffer);

//        InjectDllToRemoteProcess(ProcessInformation.hProcess, ProcessInformation.hThread, &DllFullPath, FALSE);
        NtClose(ProcessInformation.hProcess);
        NtClose(ProcessInformation.hThread);
    }

    return Nt_ExitProcess(0);
}

VOID NTAPI TlsCallBackFunction(PVOID ModuleHandle, DWORD Reason, PVOID Reserved)
{
    NTSTATUS            Status;
    WCHAR               DllPathBuffer[MAX_NTPATH];
    UNICODE_STRING      DllFullPath;
    PROCESS_INFORMATION ProcessInformation;

    Nt_SetExeDirectoryAsCurrent();

    LOOP_ONCE
    {
        Status = Nt_CreateProcess(L"euphoria.exe", NULL, NULL, CREATE_SUSPENDED, NULL, &ProcessInformation);
        if (!NT_SUCCESS(Status))
            break;

        DllFullPath.Buffer = DllPathBuffer;
        DllFullPath.Length = Nt_GetExeDirectory(DllPathBuffer, countof(DllPathBuffer));

        *(PULONG64)&DllPathBuffer[DllFullPath.Length + 0] = TAG4W('euph');
        *(PULONG64)&DllPathBuffer[DllFullPath.Length + 4] = TAG4W('oria');
        *(PULONG64)&DllPathBuffer[DllFullPath.Length + 8] = TAG4W('_sc.');
        *(PULONG64)&DllPathBuffer[DllFullPath.Length + 12] = TAG3W('dll');

        DllFullPath.Length += CONST_STRLEN(L"euphoria_sc.dll");
        DllFullPath.Length *= sizeof(WCHAR);
        DllFullPath.MaximumLength = sizeof(DllPathBuffer);

        InjectDllToRemoteProcess(ProcessInformation.hProcess, ProcessInformation.hThread, &DllFullPath, FALSE);
        NtClose(ProcessInformation.hProcess);
        NtClose(ProcessInformation.hThread);
    }
}

#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma warning(disable:4127)
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "undoc_k32.lib")

#include <Windows.h>
#include <shlobj.h>
#include "my_headers.h"
#include "my_commsrc.h"

typedef struct
{
    DWORD           ReturnAddr;
    PVOID           pfLdrLoadDll;
    UNICODE_STRING  ModuleFileName;
} INJECT_DLL_CURRENT_THREAD;

NTSTATUS InjectSelfToRemoteProcess(HANDLE hProcess, HANDLE hThread)
{
    NTSTATUS    Status;
    PVOID       pvBuffer;
    DWORD       Length;
    WCHAR       szSelfPath[MAX_PATH];
    CONTEXT     ThreadContext;
    LARGE_INTEGER TimeOut;
    INJECT_DLL_CURRENT_THREAD inj;

    ThreadContext.ContextFlags = CONTEXT_CONTROL;
    Status = NtGetContextThread(hThread, &ThreadContext);
    if (!NT_SUCCESS(Status))
    {
//        BaseSetLastNTError(Status);
//        PrintError(RtlGetLastWin32Error());
        return Status;
    }

//    PrintConsoleW(L"Eip = %08X\n", ThreadContext.Eip);
//    getch();

    Length = Nt_GetExeDirectory(szSelfPath, countof(szSelfPath));
    if (Length == NULL)
        return STATUS_UNSUCCESSFUL;

    static WCHAR szDll[] = L"LocaleEmulator.dll";
    StrCopyW(szSelfPath + Length, szDll);
    Length += CONST_STRLEN(szDll);

    pvBuffer = NULL;
    Status = Nt_AllocateMemory(hProcess, &pvBuffer, MEMORY_PAGE_SIZE);
    if (!NT_SUCCESS(Status))
    {
//        BaseSetLastNTError(Status);
//        PrintError(RtlGetLastWin32Error());
        return Status;
    }

    Length *= sizeof(WCHAR);
    inj.pfLdrLoadDll = LdrLoadDll;
    inj.ReturnAddr   = ThreadContext.Eip;
    inj.ModuleFileName.Length = Length;
    inj.ModuleFileName.MaximumLength = Length + sizeof(WCHAR);
    inj.ModuleFileName.Buffer = (LPWSTR)((ULONG_PTR)pvBuffer + sizeof(inj));

    Status = STATUS_UNSUCCESSFUL;
    LOOP_ONCE
    {
        Status = Nt_WriteMemory(hProcess, pvBuffer, &inj, sizeof(inj));
        if (!NT_SUCCESS(Status))
            break;

        Length += sizeof(WCHAR);
        Status = Nt_WriteMemory(hProcess, (PVOID)((ULONG_PTR)pvBuffer + sizeof(inj)), szSelfPath, Length);
        if (!NT_SUCCESS(Status))
            break;

        ThreadContext.Eip = (DWORD)(PBYTE)pvBuffer + sizeof(inj) + Length;
        Status = Nt_WriteMemory(
                    hProcess,
                    (PVOID)ThreadContext.Eip,
                    LoadExternDll,
                    (ULONG_PTR)_LoadExternDllEnd - (ULONG_PTR)LoadExternDll
                 );
        if (!NT_SUCCESS(Status))
            break;

        Status = NtSetContextThread(hThread, &ThreadContext);
        if (!NT_SUCCESS(Status))
            break;

        Status = NtResumeThread(hThread, NULL);
        if (!NT_SUCCESS(Status))
            break;

        BaseFormatTimeOut(&TimeOut, 500);
        for (DWORD TryTimes = 30; TryTimes; --TryTimes)
        {
            DWORD Val;
            Status = Nt_ReadMemory(hProcess, pvBuffer, &Val, sizeof(Val));
            if (!NT_SUCCESS(Status))
                break;

            if (Val != 0)
            {
                NtDelayExecution(FALSE, &TimeOut);
                continue;
            }

            break;
        }

        if (!NT_SUCCESS(Status))
            break;

        NtDelayExecution(FALSE, &TimeOut);
        Status = NtGetContextThread(hThread, &ThreadContext);
        if (!NT_SUCCESS(Status))
            break;

        if ((ULONG_PTR)ThreadContext.Eip < (ULONG_PTR)pvBuffer ||
            (ULONG_PTR)ThreadContext.Eip > (ULONG_PTR)pvBuffer + MEMORY_PAGE_SIZE)
        {
            Status = STATUS_SUCCESS;
        }
        else
        {
            Status = STATUS_UNSUCCESSFUL;
        }
    }

//    BaseSetLastNTError(Status);
//    PrintError(RtlGetLastWin32Error());

//    Nt_FreeMemory(hProcess, pvBuffer);

    return Status;
}

NTSTATUS
Nt_CreateProcess(
    LPCWSTR                 ApplicationName,
    LPWSTR                  CommandLine,
    ULONG                   CreationFlags,
    LPCWSTR                 CurrentDirectory,
    LPSTARTUPINFO           StartupInfo,
    LPPROCESS_INFORMATION   ProcessInformation
)
{
    NTSTATUS                        Status;
    WCHAR                           FullPathBuffer[MAX_PATH *2], DllPathBuffer[0x3000];
    UNICODE_STRING                  PathVariableName, DllPath, ImagePathName;
    UNICODE_STRING                  _CommandLine, _CurrentDirectory;
    PRTL_USER_PROCESS_PARAMETERS    ProcessParameters;
    RTL_USER_PROCESS_INFORMATION    ProcessInfo;

    if (!RtlDosPathNameToNtPathName_U(ApplicationName, &ImagePathName, NULL, NULL))
        return STATUS_OBJECT_PATH_NOT_FOUND;

    RTL_CONST_STRING(PathVariableName, L"Path");
    DllPath.Length = 0;
    DllPath.MaximumLength = sizeof(DllPathBuffer);
    DllPath.Buffer = DllPathBuffer;
    RtlQueryEnvironmentVariable_U(NULL, &PathVariableName, &DllPath);

    if (CommandLine != NULL)
        RtlInitUnicodeString(&_CommandLine, CommandLine);
    if (CurrentDirectory != NULL)
        RtlInitUnicodeString(&_CurrentDirectory, CurrentDirectory);

    Status = RtlCreateProcessParameters(
                &ProcessParameters,
                &ImagePathName,
                &DllPath,
                CurrentDirectory == NULL ? NULL : &_CurrentDirectory,
                CommandLine == NULL ? NULL : &_CommandLine,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL
             );

    if (!NT_SUCCESS(Status))
    {
        RtlFreeUnicodeString(&ImagePathName);
        return Status;
    }

    ProcessInfo.Size = sizeof(ProcessInfo);
    Status = RtlCreateUserProcess(
                &ImagePathName,
                OBJ_CASE_INSENSITIVE,
                ProcessParameters,
                NULL,
                NULL,
                NULL,
                FALSE,
                NULL,
                NULL,
                &ProcessInfo
             );

    RtlDestroyProcessParameters(ProcessParameters);
    RtlFreeUnicodeString(&ImagePathName);

    if (!NT_SUCCESS(Status))
        return Status;

    if (!FLAG_ON(CreationFlags, CREATE_SUSPENDED))
    {
        NtResumeThread(ProcessInfo.ThreadHandle, NULL);
    }

    if (ProcessInformation == NULL)
    {
        NtClose(ProcessInfo.ProcessHandle);
        NtClose(ProcessInfo.ThreadHandle);
        return Status;
    }

    ProcessInformation->dwProcessId = (ULONG)ProcessInfo.ClientId.UniqueProcess;
    ProcessInformation->dwThreadId  = (ULONG)ProcessInfo.ClientId.UniqueThread;
    ProcessInformation->hProcess    = ProcessInfo.ProcessHandle;
    ProcessInformation->hThread     = ProcessInfo.ThreadHandle;

    return Status;
}

NTSTATUS GetPathFromLinkFile(PCWSTR LinkFilePath, PWCHAR FullPath, ULONG BufferCount)
{
    HRESULT         hResult;
    IShellLinkW    *ShellLink;
	IPersistFile   *PersistFile;

    CoInitialize(NULL);

    hResult = S_OK;
    ShellLink = NULL;
    PersistFile = NULL;

    LOOP_ONCE
    {
        hResult = CoCreateInstance(
                    CLSID_ShellLink,
                    NULL,
                    CLSCTX_INPROC_SERVER,
                    IID_IShellLinkW,
                    (PVOID *)&ShellLink
                  );
        if (FAILED(hResult))
            break;

        hResult = ShellLink->QueryInterface(IID_IPersistFile, (PVOID *)&PersistFile);
        if (FAILED(hResult))
            break;

        hResult = PersistFile->Load(LinkFilePath, 0);
        if (FAILED(hResult))
            break;

        hResult = ShellLink->GetPath(FullPath, BufferCount, NULL, SLGP_UNCPRIORITY);
    }

    if (PersistFile != NULL)
        PersistFile->Release();

    if (ShellLink != NULL)
        ShellLink->Release();

    CoUninitialize();

    return hResult;
}

ForceInline Void main2(Int argc, WChar **argv)
{
    NTSTATUS            Status;
    WCHAR               *pExePath, szDllPath[MAX_NTPATH], FullExePath[MAX_NTPATH];
    STARTUPINFOW        si;
    PROCESS_INFORMATION pi;

    if (argc == 1)
        return;

    RtlAdjustPrivilege(SE_DEBUG_PRIVILEGE, TRUE, FALSE, (PBOOLEAN)&Status);
    while (--argc)
    {
        pExePath = findextw(*++argv);
        if (CHAR_UPPER4W(*(PULONG64)pExePath) == CHAR_UPPER4W(TAG4W('.LNK')))
        {
            if (FAILED(GetPathFromLinkFile(*argv, FullExePath, countof(FullExePath))))
            {
                pExePath = *argv;
            }
            else
            {
                pExePath = FullExePath;
            }
        }
        else
        {
            pExePath = *argv;
        }

        RtlGetFullPathName_U(pExePath, sizeof(szDllPath), szDllPath, NULL);
        rmnamew(szDllPath);
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        Status = CreateProcessInternalW(
                    NULL,
                    pExePath,
                    NULL,
                    NULL,
                    NULL,
                    FALSE,
                    CREATE_SUSPENDED,
                    NULL,
                    *szDllPath == 0 ? NULL : szDllPath,
                    &si,
                    &pi,
                    NULL);
        if (!Status)
        {
            PrintConsoleW(L"CreateProcess() failed.\n");
            continue;
        }

        Status = InjectSelfToRemoteProcess(pi.hProcess, pi.hThread);

        if (!NT_SUCCESS(Status))
        {
//            PrintError(GetLastError());
            NtTerminateProcess(pi.hProcess, 0);
        }

        NtClose(pi.hProcess);
        NtClose(pi.hThread);
    }
}

int __cdecl main(Int argc, WChar **argv)
{
    argv = CmdLineToArgvW(Nt_CurrentPeb()->ProcessParameters->CommandLine.Buffer, &argc);
    main2(argc, argv);
    return Nt_ExitProcess(0);
}

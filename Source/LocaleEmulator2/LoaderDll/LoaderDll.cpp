//#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")
//#pragma comment(linker, "/EXPORT:LeCreateProcess=_LeCreateProcess@44")

#include "MyLibrary.cpp"
#include "LoaderDll.h"

EXTC
NTSTATUS
NTAPI
LeCreateProcess(
    PLEB                    Leb,
    PCWSTR                  ApplicationName,
    PWSTR                   CommandLine,
    PCWSTR                  CurrentDirectory,
    ULONG                   CreationFlags,
    LPSTARTUPINFOW          StartupInfo,
    PML_PROCESS_INFORMATION ProcessInformation,
    LPSECURITY_ATTRIBUTES   ProcessAttributes,
    LPSECURITY_ATTRIBUTES   ThreadAttributes,
    PVOID                   Environment,
    HANDLE                  Token
)
{
    ULONG_PTR               Length;
    PWSTR                   DllFullPath;
    PLDR_MODULE             Module;
    NTSTATUS                Status;
    ML_PROCESS_INFORMATION  ProcessInfo;

    static WCHAR Dll[] = L"LocaleEmulator.dll";

    Module = FindLdrModuleByHandle(NULL);

    Length = Module->FullDllName.Length - Module->BaseDllName.Length;
    DllFullPath = (PWSTR)AllocStack(Length + sizeof(Dll));
    CopyMemory(DllFullPath, Module->FullDllName.Buffer, Length);
    CopyStruct(PtrAdd(DllFullPath, Length), Dll, sizeof(Dll));

    Status = CreateProcessWithDll(
                CPWD_BEFORE_KERNEL32,
                DllFullPath,
                ApplicationName,
                CommandLine,
                CurrentDirectory,
                CreationFlags | CREATE_SUSPENDED,
                StartupInfo,
                &ProcessInfo,
                ProcessAttributes,
                ThreadAttributes,
                Environment,
                Token
            );

    if (NT_FAILED(Status))
        return Status;

    PLEPEB LePeb;

    LePeb = NULL;

    LOOP_ONCE
    {
        LePeb = OpenOrCreateLePeb(ProcessInfo.dwProcessId, TRUE);
        if (LePeb == NULL)
        {
            Status = STATUS_UNSUCCESSFUL;
            break;
        }

        if (Leb != NULL)
        {
            LePeb->Leb = *Leb;
        }
        else
        {
            InitDefaultLeb(&LePeb->Leb);
        }

        LePeb->LdrLoadDllAddress = GetCallDestination(ProcessInfo.FirstCallLdrLoadDll);
        LePeb->LdrLoadDllBackupSize = LDR_LOAD_DLL_BACKUP_SIZE;
        ReadMemory(ProcessInfo.hProcess, LePeb->LdrLoadDllAddress, LePeb->LdrLoadDllBackup, LDR_LOAD_DLL_BACKUP_SIZE);

        StrCopyW(LePeb->LeDllFullPath, DllFullPath);

        if (!FLAG_ON(CreationFlags, CREATE_SUSPENDED))
            Status = ZwResumeProcess(ProcessInfo.hProcess);
    }

    CloseLePeb(LePeb);

    if (NT_FAILED(Status))
    {
        ZwTerminateProcess(ProcessInfo.hProcess, Status);
        ZwClose(ProcessInfo.hProcess);
        ZwClose(ProcessInfo.hThread);
    }
    else if (ProcessInformation != NULL)
    {
        *ProcessInformation = ProcessInfo;
    }
    else
    {
        ZwClose(ProcessInfo.hProcess);
        ZwClose(ProcessInfo.hThread);
    }

    return Status;
}

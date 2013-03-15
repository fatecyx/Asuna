#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
//#pragma comment(linker, "/EXPORT:__strdup=msvcrt._strdup")

#include "MyLibrary.cpp"
#include <Windns.h>

OVERLOAD_CPP_NEW_WITH_HEAP(MemoryAllocator::GetGlobalHeap())

TYPE_OF(NtQueryDirectoryFile)*      StubNtQueryDirectoryFile;
TYPE_OF(NtQueryAttributesFile)*     StubNtQueryAttributesFile;
TYPE_OF(NtQueryFullAttributesFile)* StubNtQueryFullAttributesFile;

NTSTATUS
NTAPI
TGitNtQueryDirectoryFile(
    HANDLE                  FileHandle,
    HANDLE                  Event  OPTIONAL,
    PIO_APC_ROUTINE         ApcRoutine  OPTIONAL,
    PVOID                   ApcContext  OPTIONAL,
    PIO_STATUS_BLOCK        IoStatusBlock,
    PVOID                   FileInformation,
    ULONG                   Length,
    FILE_INFORMATION_CLASS  FileInformationClass,
    BOOLEAN                 ReturnSingleEntry,
    PUNICODE_STRING         FileName  OPTIONAL,
    BOOLEAN                 RestartScan
)
{
    NTSTATUS Status;

    Status = StubNtQueryDirectoryFile(FileHandle, Event, ApcRoutine, ApcContext, IoStatusBlock, FileInformation, Length, FileInformationClass, ReturnSingleEntry, FileName, RestartScan);
    if (NT_SUCCESS(Status) && FileInformationClass == FileBothDirectoryInformation)
    {
        PFILE_BOTH_DIR_INFORMATION FileInfo;

        FileInfo = (PFILE_BOTH_DIR_INFORMATION)FileInformation;

        if (FileInfo != NULL)
        {
            CLEAR_FLAG(FileInfo->FileAttributes, FILE_ATTRIBUTE_REPARSE_POINT);
        }
    }

    return Status;
}

NTSTATUS
NTAPI
TGitNtQueryAttributesFile(
    POBJECT_ATTRIBUTES      ObjectAttributes,
    PFILE_BASIC_INFORMATION FileInformation
)
{
    NTSTATUS Status;

    Status = StubNtQueryAttributesFile(ObjectAttributes, FileInformation);

    if (NT_SUCCESS(Status) && FileInformation != NULL)
    {
        CLEAR_FLAG(FileInformation->FileAttributes.LowPart, FILE_ATTRIBUTE_REPARSE_POINT);
    }

    return Status;
}

NTSTATUS
NTAPI
TGitNtQueryFullAttributesFile(
    POBJECT_ATTRIBUTES              ObjectAttributes,
    PFILE_NETWORK_OPEN_INFORMATION  FileInformation
)
{
    NTSTATUS Status;

    Status = StubNtQueryFullAttributesFile(ObjectAttributes, FileInformation);

    if (NT_SUCCESS(Status))
    {
        CLEAR_FLAG(FileInformation->FileAttributes, FILE_ATTRIBUTE_REPARSE_POINT);
    }

    return Status;
}

#if ML_AMD64

TYPE_OF(DnsQuery_W)*    StubDnsQuery_W;
TYPE_OF(DnsFree)*       StubDnsFree;

EXTC
DNS_STATUS
WINAPI
GitDnsQuery_W(
    PCWSTR          pszName,
    WORD            wType,
    DWORD           Options,
    PVOID           pExtra,
    PDNS_RECORD*   ppQueryResults,
    PVOID *         pReserved
)
{
    return StubDnsQuery_W(pszName, wType, Options, pExtra, ppQueryResults, pReserved);
}

EXTC
VOID
WINAPI
GitDnsFree(
    PVOID           pData,
    DNS_FREE_TYPE   FreeType
)
{
    StubDnsFree(pData, FreeType);
}

#endif

#include "../Drivers/AntiAntiKernelDebug/ShadowSysCall.h"

#pragma comment(linker, "/EXPORT:CEPlugin_GetVersion=_CEPlugin_GetVersion@8")
#pragma comment(linker, "/EXPORT:CEPlugin_InitializePlugin=_CEPlugin_InitializePlugin@8")
#pragma comment(linker, "/EXPORT:CEPlugin_DisablePlugin=_CEPlugin_DisablePlugin@0")

EXTC BOOL __stdcall CEPlugin_GetVersion(PVOID pv , int sizeofpluginversion)
{
    ZeroMemory(pv, 8);
    return TRUE;
}

EXTC BOOL __stdcall CEPlugin_InitializePlugin(PVOID ef , int pluginid)
{
    return TRUE;
}

EXTC BOOL __stdcall CEPlugin_DisablePlugin()
{
    return TRUE;
}

VOID SetThemesAccessAny(NtFileDisk &SsDevice)
{
    NTSTATUS    Status;
    SC_HANDLE   ScManager, Themes;

    ScManager = OpenSCManagerW(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (ScManager == NULL)
        return;

    Themes = OpenServiceW(ScManager, L"Themes", SERVICE_ALL_ACCESS);
    if (Themes == NULL)
    {
        CloseServiceHandle(ScManager);
        return;
    }

    ULONG Needed;
    SERVICE_STATUS_PROCESS ServiceProcess;

    if (QueryServiceStatusEx(Themes, SC_STATUS_PROCESS_INFO, (PBYTE)&ServiceProcess, sizeof(ServiceProcess), &Needed))
    {
        SS_PROCESS_OBJECT obj;

        obj.ProcessId   = ServiceProcess.dwProcessId;
        obj.AccessAny   = TRUE;

        ControlShadowDevice(SsDevice, IOCTL_SET_PROCESS_INFO, &obj, sizeof(obj));
    }

    CloseServiceHandle(Themes);
    CloseServiceHandle(ScManager);
}

BOOL Initialize(PVOID BaseAddress)
{
    ml::MlInitialize();

    NTSTATUS Status;

    LOOP_ONCE
    {
        NtFileDisk SsDevice;

        Status = SsDevice.OpenDevice(SHADOW_SYSCALL_DEVICE_SYMBOLIC);
        FAIL_BREAK(Status);

        SetThemesAccessAny(SsDevice);

        SS_PROCESS_OBJECT obj;

        obj.ProcessId = CurrentPid();
        obj.ShadowSystemCall = TRUE;
        obj.DenyAccess = TRUE;
        obj.AccessAny = TRUE;
        Status = ControlShadowDevice(SsDevice, IOCTL_SET_PROCESS_INFO, &obj, sizeof(obj));
    }

    return TRUE;
}

BOOL CDECL UnInitialize(PVOID BaseAddress)
{
    // ml::MlUnInitialize();

    return FALSE;
}

BOOL WINAPI DllMain(PVOID BaseAddress, ULONG Reason, PVOID Reserved)
{
    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Initialize(BaseAddress) || UnInitialize(BaseAddress);

        case DLL_PROCESS_DETACH:
            UnInitialize(BaseAddress);
            break;
    }

    return TRUE;
}

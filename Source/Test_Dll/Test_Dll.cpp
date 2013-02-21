#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(linker, "/EXPORT:__strdup=msvcrt._strdup")

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

BOOL Initialize(PVOID BaseAddress)
{
    ml::MlInitialize();

    PVOID           Dnsapi;
    PLDR_MODULE     ntdll, exe;
    PWSTR           FullPath;
    ULONG_PTR       Length;
    UNICODE_STRING  Home, ExePath;

#if ML_AMD64

    static WCHAR DnsapiDll[] = L"DNSAPI.dll";

    ntdll = GetNtdllLdrModule();

    Length = ntdll->FullDllName.Length - ntdll->BaseDllName.Length;
    FullPath = (PWSTR)AllocateMemoryP(Length + sizeof(DnsapiDll));
    if (FullPath == NULL)
        return FALSE;

    CopyMemory(FullPath, ntdll->FullDllName.Buffer, Length);
    CopyStruct(PtrAdd(FullPath, Length), DnsapiDll, sizeof(DnsapiDll));

    Dnsapi = Ldr::LoadDll(FullPath);
    if (Dnsapi != NULL)
    {
        *(PVOID *)&StubDnsQuery_W   = GetRoutineAddress(Dnsapi, "DnsQuery_W");
        *(PVOID *)&StubDnsFree      = GetRoutineAddress(Dnsapi, "DnsFree");
    }

#endif

    exe = FindLdrModuleByHandle(BaseAddress);

    RTL_CONST_STRING(Home, L"HOME");
    ExePath = exe->FullDllName;
    ExePath.Length -= exe->BaseDllName.Length;

    RtlSetEnvironmentVariable(NULL, &Home, &ExePath);

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_JUMP(NtQueryDirectoryFile,      TGitNtQueryDirectoryFile,       StubNtQueryDirectoryFile),
        INLINE_HOOK_JUMP(NtQueryAttributesFile,     TGitNtQueryAttributesFile,      StubNtQueryAttributesFile),
        INLINE_HOOK_JUMP(NtQueryFullAttributesFile, TGitNtQueryFullAttributesFile,  StubNtQueryFullAttributesFile),
    };

    Nt_PatchMemory(NULL, 0, f, countof(f));

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

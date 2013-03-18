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

struct LolPacket
{
    BOOL THISCALL RecvPacket(ULONG unk, ULONG type1, ULONG type2, ULONG len, PBYTE buf);
};

TYPE_OF(&LolPacket::RecvPacket) StubRecvPacket;

BOOL THISCALL LolPacket::RecvPacket(ULONG unk, ULONG type1, ULONG type2, ULONG len, PBYTE buf)
{
    LOOP_ONCE
    {
        WCHAR file[MAX_NTPATH];
        NTSTATUS st;
        LARGE_INTEGER cnt;
        NtFileDisk bin;

        if (buf == NULL || len == 0)
            break;

        RtlQueryPerformanceCounter(&cnt);
        swprintf(file, L"C:\\lelog\\ts=%I64d_op=%X_len=%X_t1=%d_t2=%d", cnt.QuadPart, buf[0], len, type1, type2);

        st = bin.Create(file);
        FAIL_BREAK(st);

        bin.Write(buf, len);
    }

    return (this->*StubRecvPacket)(unk, type1, type2, len, buf);
}

BOOL Initialize(PVOID BaseAddress)
{
    ml::MlInitialize();

    NTSTATUS Status;

    if (BaseAddress != NULL)
        return TRUE;

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_JUMP(0xABFDA0, (PVOID)PtrAdd(NULL, &LolPacket::RecvPacket), StubRecvPacket),
    };

    Nt_PatchMemory(NULL, 0, f, countof(f));

    return TRUE;
}

BOOL CDECL UnInitialize(PVOID BaseAddress)
{
    ml::MlUnInitialize();

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

#pragma comment(linker, "/EXPORT:Direct3DCreate9=_Direct3DCreate9@4")
#pragma comment(linker, "/EXPORT:D3DPERF_SetMarker=_D3DPERF_SetMarker@8")
#pragma comment(linker, "/EXPORT:D3DPERF_BeginEvent=_D3DPERF_BeginEvent@8")
#pragma comment(linker, "/EXPORT:D3DPERF_EndEvent=_D3DPERF_EndEvent@0")

#include <d3d9.h>

PVOID GetD3DRoutine(PCSTR Name)
{
    ULONG           Length;
    NTSTATUS        Status;
    PVOID           hModule;
    WCHAR           szPath[MAX_NTPATH];
    UNICODE_STRING  DllPath;

    static WCHAR D3d9Dll[] = L"d3d9.dll";

    Length = Nt_GetSystemDirectory(szPath, countof(szPath));

    CopyStruct(szPath + Length, D3d9Dll, sizeof(D3d9Dll));
    DllPath.Buffer = szPath;
    DllPath.Length = (USHORT)((Length + CONST_STRLEN(D3d9Dll)) * sizeof(WCHAR));
    DllPath.MaximumLength = DllPath.Length;

    Status = LdrLoadDll(NULL, 0, &DllPath, &hModule);
    if (!NT_SUCCESS(Status))
        return NULL;

    LdrAddRefDll(LDR_ADDREF_DLL_PIN, hModule);

    return Nt_GetProcAddress(hModule, Name);
}

EXTC IDirect3D9* STDCALL Direct3DCreate9(UINT SDKVersion)
{
    static IDirect3D9* (STDCALL *pfDirect3DCreate9)(UINT SDKVersion);

    if (pfDirect3DCreate9 == NULL)
    {
        *(PVOID *)&pfDirect3DCreate9 = GetD3DRoutine("Direct3DCreate9");
        if (pfDirect3DCreate9 == NULL)
            return NULL;

        Initialize(NULL);
    }

    return pfDirect3DCreate9(SDKVersion);
}

EXTC VOID WINAPI D3DPERF_SetMarker(D3DCOLOR Color, PCWSTR Name)
{
    static VOID (STDCALL *pfD3DPERF_SetMarker)(D3DCOLOR Color, PCWSTR Name);

    if (pfD3DPERF_SetMarker == NULL)
    {
        *(PVOID *)&pfD3DPERF_SetMarker = GetD3DRoutine("D3DPERF_SetMarker");
    }

    pfD3DPERF_SetMarker(Color, Name);
}

EXTC int WINAPI D3DPERF_BeginEvent( D3DCOLOR col, LPCWSTR wszName )
{
    static TYPE_OF(D3DPERF_BeginEvent)* BeginEvent;

    if (BeginEvent == NULL)
    {
        *(PVOID *)&BeginEvent = GetD3DRoutine("D3DPERF_BeginEvent");
    }

    return BeginEvent(col, wszName);
}

EXTC int WINAPI D3DPERF_EndEvent( void )
{
    static TYPE_OF(D3DPERF_EndEvent)* EndEvent;

    if (EndEvent == NULL)
    {
        *(PVOID *)&EndEvent = GetD3DRoutine("D3DPERF_EndEvent");
    }

    return EndEvent();
}

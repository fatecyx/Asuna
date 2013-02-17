#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "NativeApi.h"

_MY_C_HEAD_

NTSTATUS
NTAPI
NtInitializeNlsFiles(
    OUT PVOID*          BaseAddress,
    OUT PLCID           DefaultLocaleId,
    OUT PLARGE_INTEGER  DefaultCasingTableSize
)
{
    return 0;
}

NTSTATUS
NTAPI
LdrRegisterDllNotification(
    IN  ULONG                           Flags,
    IN  PLDR_DLL_NOTIFICATION_FUNCTION  NotificationFunction,
    IN  PVOID                           Context OPTIONAL,
    OUT PVOID*                          Cookie
)
{
    return 0;
}

NTSTATUS
NTAPI
LdrUnregisterDllNotification(
    IN PVOID Cookie
)
{
    return 0;
}

BOOLEAN
NTAPI
RtlDosPathNameToRelativeNtPathName_U(
    IN  PWSTR                   DosFileName,
    OUT PUNICODE_STRING         NtFileName,
    OUT PWSTR*                  FilePart OPTIONAL,
    OUT PRTL_RELATIVE_NAME_U    RelativeName OPTIONAL
){return 0;}

NTSTATUS
NTAPI
RtlWow64EnableFsRedirectionEx(
    BOOL    Enable,
    PBOOL   PreviousState
)
{
    return 0;
}

VOID DbgBreakPoint(){}

VOID
NTAPI
RtlSetUnhandledExceptionFilter(
    LPTOP_LEVEL_EXCEPTION_FILTER TopLevelExceptionFilter
)
{
}

BOOL
NTAPI
RtlQueryPerformanceCounter(
    OUT PLARGE_INTEGER PerformanceCount
)
{
    return 0;
}

void* __cdecl _memset(void * _Dst, int _Val, size_t _Size)
{
    return 0;
}

void* __cdecl _memcpy(void *dest, const void *src, size_t count)
{
    return 0;
}

int __cdecl _vsnwprintf (
    wchar_t *string,
    size_t count,
    const wchar_t *format,
    va_list ap
)
{
    return 0;
}

NTSTATUS
NTAPI
RtlWow64EnableFsRedirection(
    BOOLEAN Enable
)
{
    return 0;
}

VOID NTAPI LdrInitializeThunk(PCONTEXT ThreadContext, PVOID NtdllBase)
{
    ;
}

VOID FASTCALL KiFastSystemCall()
{
}

PVOID NTAPI RtlAddVectoredContinueHandler(IN LONG FirstHandler, IN PVECTORED_EXCEPTION_HANDLER Handler)
{
    return 0;
}

ULONG NTAPI RtlRemoveVectoredContinueHandler(IN PVOID Handler)
{
    return 0;
}

ULONG NTAPI NtGetTickCount()
{
    return 0;
}

NTSTATUS
NTAPI
NtCreateKey(
    OUT PHANDLE             KeyHandle,
    IN  ACCESS_MASK         DesiredAccess,
    IN  POBJECT_ATTRIBUTES  ObjectAttributes,
    IN  ULONG               TitleIndex,
    IN  PUNICODE_STRING     Class OPTIONAL,
    IN  ULONG               CreateOptions,
    OUT PULONG              Disposition OPTIONAL
)
{
    return 0;
}

NTSTATUS
NTAPI
NtSetValueKey(
    IN  HANDLE          KeyHandle,
    IN  PUNICODE_STRING ValueName,
    IN  ULONG           TitleIndex OPTIONAL,
    IN  ULONG           ValueType,
    IN  LPCVOID         ValueData OPTIONAL,
    IN  ULONG           ValueDataSize
)
{
    return 0;
}

VOID
NTAPI
A_SHAInit(
    PRTL_SHA_CTX ShaContext
)
{
}

VOID
NTAPI
A_SHAUpdate(
    PRTL_SHA_CTX    ShaContext,
    PVOID           Buffer,
    ULONG           BufferSize
)
{
}

VOID
NTAPI
A_SHAFinal(
    PRTL_SHA_CTX ShaContext,
    PRTL_SHA_DIG Digest
)
{
}

VOID
NTAPI
MD5Init(
    OUT PRTL_MD5_CTX Context
)
{
}

VOID
NTAPI
MD5Update(
    IN OUT  PRTL_MD5_CTX    Context,
    IN      PVOID           Buffer,
    IN      ULONG           BufferSize
)
{
}

VOID
NTAPI
MD5Final(
    IN OUT  PRTL_MD5_CTX Context
)
{
}

NTSTATUS
NTAPI
NtCreateUserProcess(
    PHANDLE                         ProcessHandle,
    PHANDLE                         ThreadHandle,
    ACCESS_MASK                     ProcessDesiredAccess,
    ACCESS_MASK                     ThreadDesiredAccess,
    POBJECT_ATTRIBUTES              ProcessObjectAttributes OPTIONAL,
    POBJECT_ATTRIBUTES              ThreadObjectAttributes OPTIONAL,
    ULONG                           ProcessFlags,                   // PROCESS_CREATE_FLAGS_*
    ULONG                           ThreadFlags,                    // THREAD_CREATE_FLAGS_*
    PRTL_USER_PROCESS_PARAMETERS    ProcessParameters,
    PPS_CREATE_INFO                 CreateInfo,
    PPS_ATTRIBUTE_LIST              AttributeList
)
{
    return 0;
}

NTSTATUS
NTAPI
NtCreateThreadEx(
    PHANDLE             ThreadHandle,
    ACCESS_MASK         DesiredAccess,
    POBJECT_ATTRIBUTES  ObjectAttributes,
    HANDLE              ProcessHandle,
    PVOID               StartAddress,
    PVOID               Parameter,
    BOOL                CreateSuspended,
    ULONG               StackZeroBits,
    ULONG               SizeOfStackCommit,
    ULONG               SizeOfStackReserve,
    PVOID               BytesBuffer
)
{
    return 0;
}

_MY_C_TAIL_

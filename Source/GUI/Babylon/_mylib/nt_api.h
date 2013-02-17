#ifndef _NT_API_H__
#define _NT_API_H__

#pragma warning(disable:4615)
//#pragma comment(lib,"ntdll.lib")

#include "my_types.h"
#include "my_macros.h"

#if !defined(_MY_NTLIB_DLL_) && !defined(_MY_NTLIB_)
//    #pragma comment(lib,"MyLib.lib")
#elif !defined(_NTDDK_)
    #include <stdlib.h>
#endif

#if defined(_MY_NTLIB_) || defined(_MY_NTLIB_DLL_)
#include "nt_defs.h"

/* Undocumented APIs */
EXTC_IMPORT NTSTATUS NTAPI RtlFormatMessage(
        LPWSTR        Message,              // [In] Message to format
        UCHAR         MaxWidth,             // [In] Maximum width in characters of each output line
        BOOLEAN       IgnoreInserts,        // [In] Whether to copy the message without processing inserts
        BOOLEAN       Ansi,                 // [In] Whether Arguments may have ANSI strings
        BOOLEAN       ArgumentIsArray,      // [In] Whether Arguments is actually an array rather than a va_list *
        va_list      *Arguments,
        LPWSTR        Buffer,               // [Out] Buffer to store processed message in
        ULONG         BufferSize            // [In] Size of Buffer (in bytes?)
);

#else /* _MY_NTLIB_ */

#if defined(__AFX_H__) || defined(_NTDDK_)
    #include <Windows.h>
#endif
    #include "nt_defs.h"
#endif /* _MY_NTLIB_ */

_MY_C_HEAD_

EXTC DECL_IMPORT UINT    NlsAnsiCodePage;
EXTC DECL_IMPORT BOOLEAN NlsMbCodePageTag;

MY_DLL_IMPORT NTSTATUS NTAPI RtlGetVersion(IN OUT PRTL_OSVERSIONINFOW  lpVersionInformation);
MY_DLL_IMPORT HANDLE   NTAPI RtlCreateHeap(IN ULONG Flags, IN PVOID HeapBase OPTIONAL, IN SIZE_T ReserveSize OPTIONAL, IN SIZE_T CommitSize OPTIONAL, IN PVOID Lock OPTIONAL, IN PRTL_HEAP_PARAMETERS Parameters OPTIONAL);
MY_DLL_IMPORT HANDLE   NTAPI RtlDestroyHeap(IN HANDLE HeapHandle);
MY_DLL_IMPORT LPVOID   NTAPI RtlAllocateHeap(IN HANDLE hHeap, IN ULONG dwFlags, IN SIZE_T dwBytes);
MY_DLL_IMPORT BOOLEAN  NTAPI RtlFreeHeap(IN HANDLE hHeap, IN ULONG dwFlags, IN LPVOID lpMem);
MY_DLL_IMPORT LPVOID   NTAPI RtlReAllocateHeap(IN HANDLE hHeap, IN ULONG dwFlags, IN LPVOID lpMem, IN SIZE_T dwBytes);
MY_DLL_IMPORT ULONG    NTAPI RtlNtStatusToDosError(NTSTATUS Status);
MY_DLL_IMPORT NTSTATUS NTAPI RtlGetLastWin32Error();
MY_DLL_IMPORT VOID     NTAPI RtlSetLastWin32Error(IN ULONG dwErrCode);
MY_DLL_IMPORT VOID     NTAPI RtlSetLastWin32ErrorAndNtStatusFromNtStatus(IN NTSTATUS NtStatus);
MY_DLL_IMPORT NTSTATUS NTAPI RtlFindMessage(HMODULE DllHandle, ULONG MessageTableId, ULONG MessageLanguageId, ULONG MessageId, MESSAGE_RESOURCE_ENTRY **MessageEntry);
MY_DLL_IMPORT VOID     NTAPI RtlFreeAnsiString(PANSI_STRING AnsiString);
MY_DLL_IMPORT VOID     NTAPI RtlFreeUnicodeString(PUNICODE_STRING UnicodeString);
MY_DLL_IMPORT NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
MY_DLL_IMPORT PVOID    NTAPI RtlAddVectoredExceptionHandler(IN BOOL bFirstHandler, IN PVECTORED_EXCEPTION_HANDLER Handler);
MY_DLL_IMPORT NTSTATUS NTAPI RtlSetCurrentDirectory_U(PUNICODE_STRING Path);

MY_DLL_IMPORT NTSTATUS NTAPI LdrGetDllHandle(IN PUSHORT pwPath OPTIONAL, IN PVOID Unused OPTIONAL, IN PUNICODE_STRING ModuleFileName, OUT HMODULE *pHModule );
MY_DLL_IMPORT NTSTATUS NTAPI LdrLoadDll(IN PWCHAR PathToFile OPTIONAL, IN ULONG Flags OPTIONAL, IN PUNICODE_STRING ModuleFileName, OUT HMODULE *ModuleHandle);
MY_DLL_IMPORT NTSTATUS NTAPI LdrUnloadDll(HANDLE ModuleHandle);
MY_DLL_IMPORT NTSTATUS NTAPI LdrGetProcedureAddress(IN HMODULE ModuleHandle, IN PANSI_STRING FunctionName OPTIONAL, IN USHORT Ordinal OPTIONAL, OUT PVOID *FunctionAddress);
MY_DLL_IMPORT NTSTATUS NTAPI LdrDisableThreadCalloutsForDll(IN HMODULE hDllModule);

MY_DLL_IMPORT NTSTATUS NTAPI ZwAddAtom(PCWSTR AtomString, ULONG BytesInString, ATOM *pAtom);
MY_DLL_IMPORT NTSTATUS NTAPI ZwDeleteAtom(ATOM Atom);
MY_DLL_IMPORT NTSTATUS NTAPI ZwQueryAttributesFile(IN POBJECT_ATTRIBUTES pObjectAttributes, OUT PFILE_BASIC_INFORMATION pFileBasicInfo);
MY_DLL_IMPORT NTSTATUS NTAPI ZwQueryInformationFile(IN HANDLE  FileHandle, OUT PIO_STATUS_BLOCK  IoStatusBlock, OUT PVOID  FileInformation, IN ULONG  Length, IN INT32 FileInformationClass);
MY_DLL_IMPORT NTSTATUS NTAPI ZwQuerySystemInformation(IN UINT SystemInformationClass, OUT PVOID SystemInformation, IN ULONG SystemInformationLength,OUT PULONG ReturnLength OPTIONAL);
MY_DLL_IMPORT NTSTATUS NTAPI ZwTerminateThread(IN HANDLE hThread, IN ULONG dwExitCode);
MY_DLL_IMPORT NTSTATUS NTAPI ZwProtectVirtualMemory(IN HANDLE ProcessHandle, IN OUT PVOID *BaseAddress, IN OUT PULONG ProtectSize, IN ULONG NewProtect, OUT PULONG OldProtect);
MY_DLL_IMPORT NTSTATUS NTAPI ZwDelayExecution(IN BOOLEAN Alertable, IN PLARGE_INTEGER Interval);
MY_DLL_IMPORT NTSTATUS NTAPI ZwCreateSection(OUT PHANDLE SectionHandle, IN ACCESS_MASK DesiredAccess, IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL, IN PLARGE_INTEGER MaximumSize OPTIONAL, IN ULONG SectionPageProtection, IN ULONG  AllocationAttributes, IN HANDLE FileHandle OPTIONAL);
MY_DLL_IMPORT NTSTATUS NTAPI ZwOpenSection(OUT PHANDLE SectionHandle, IN ACCESS_MASK DesiredAccess, IN POBJECT_ATTRIBUTES ObjectAttributes);
MY_DLL_IMPORT NTSTATUS NTAPI ZwSetInformationFile(IN HANDLE FileHandle, OUT PIO_STATUS_BLOCK IoStatusBlock, IN PVOID FileInformation, IN ULONG Length, IN INT FileInformationClass);

MY_DLL_IMPORT NTSTATUS NTAPI NtAddAtom(PCWSTR AtomString, ULONG BytesInString, ATOM *pAtom);
MY_DLL_IMPORT NTSTATUS NTAPI NtDeleteAtom(ATOM Atom);
MY_DLL_IMPORT NTSTATUS NTAPI NtQuerySystemInformation(IN UINT SystemInformationClass, OUT PVOID SystemInformation, IN ULONG SystemInformationLength,OUT PULONG ReturnLength OPTIONAL);
MY_DLL_IMPORT NTSTATUS NTAPI NtTerminateThread(IN HANDLE hThread, IN ULONG dwExitCode);
MY_DLL_IMPORT NTSTATUS NTAPI NtQueryInformationFile(IN HANDLE FileHandle, OUT PIO_STATUS_BLOCK IoStatusBlock, OUT PVOID  FileInformation, IN ULONG  Length, IN INT32 FileInformationClass);
MY_DLL_IMPORT NTSTATUS NTAPI NtDelayExecution(IN BOOLEAN Alertable, IN PLARGE_INTEGER Interval);
MY_DLL_IMPORT NTSTATUS NTAPI NtCreateSection(OUT PHANDLE SectionHandle, IN ACCESS_MASK DesiredAccess, IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL, IN PLARGE_INTEGER MaximumSize OPTIONAL, IN ULONG SectionPageProtection, IN ULONG  AllocationAttributes, IN HANDLE FileHandle OPTIONAL);
MY_DLL_IMPORT NTSTATUS NTAPI NtOpenSection(OUT PHANDLE SectionHandle, IN ACCESS_MASK DesiredAccess, IN POBJECT_ATTRIBUTES ObjectAttributes);
MY_DLL_IMPORT NTSTATUS NTAPI NtMapViewOfSection(IN HANDLE SectionHandle, IN HANDLE ProcessHandle, IN OUT PVOID *BaseAddress, IN ULONG_PTR ZeroBits, IN SIZE_T CommitSize, IN OUT PLARGE_INTEGER SectionOffset OPTIONAL, IN OUT PSIZE_T ViewSize, IN SECTION_INHERIT InheritDisposition, IN ULONG AllocationType, IN ULONG Win32Protect);
MY_DLL_IMPORT NTSTATUS NTAPI NtUnmapViewOfSection(IN HANDLE ProcessHandle, IN PVOID BaseAddress);
MY_DLL_IMPORT NTSTATUS NTAPI NtGetContextThread(IN HANDLE ThreadHandle, OUT PCONTEXT Context);
MY_DLL_IMPORT NTSTATUS NTAPI NtSetContextThread(IN HANDLE ThreadHandle, IN PCONTEXT Context);

MY_DLL_IMPORT
NTSTATUS
NTAPI
RtlCreateUserThread(
  IN     HANDLE               ProcessHandle,
  IN     PSECURITY_DESCRIPTOR SecurityDescriptor OPTIONAL,
  IN     BOOLEAN              CreateSuspended,
  IN     ULONG                StackZeroBits,
  IN OUT PULONG               StackReserved,
  IN OUT PULONG               StackCommit,
  IN     PVOID                StartAddress,
  IN     PVOID                StartParameter OPTIONAL,
  OUT    PHANDLE              ThreadHandle,
  OUT    PCLIENT_ID           ClientID
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtSuspendThread(
    IN  HANDLE ThreadHandle,
    OUT PULONG PreviousSuspendCount OPTIONAL
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtResumeThread(
    IN  HANDLE ThreadHandle,
    OUT PULONG PreviousSuspendCount OPTIONAL
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtAllocateVirtualMemory(
    IN      HANDLE  ProcessHandle,
    IN OUT  PVOID  *BaseAddress,
    IN      ULONG   ZeroBits,
    IN OUT  PSIZE_T RegionSize,
    IN      ULONG   AllocationType,
    IN      ULONG   Protect
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtFreeVirtualMemory(
    IN      HANDLE  ProcessHandle,
    IN OUT  PVOID  *BaseAddress,
    IN OUT  PSIZE_T RegionSize,
    IN      ULONG   FreeType
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtProtectVirtualMemory(
    IN      HANDLE  ProcessHandle,
    IN OUT  PVOID  *BaseAddress,
    IN OUT  PULONG  ProtectSize,
    IN      ULONG   NewProtect,
    OUT     PULONG  OldProtect
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtReadVirtualMemory(
  IN    HANDLE  ProcessHandle,
  IN    PVOID   BaseAddress,
  OUT   PVOID   Buffer,
  IN    ULONG   NumberOfBytesToWrite,
  OUT   PULONG  NumberOfBytesWritten OPTIONAL
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtWriteVirtualMemory(
  IN    HANDLE  ProcessHandle,
  IN    PVOID   BaseAddress,
  IN    PVOID   Buffer,
  IN    ULONG   NumberOfBytesToWrite,
  OUT   PULONG  NumberOfBytesWritten OPTIONAL
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtFlushInstructionCache(
    IN HANDLE ProcessHandle,
    IN PVOID  BaseAddress,
    IN ULONG  NumberOfBytesToFlush
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtCreateFile(
    OUT PHANDLE FileHandle,
    IN  ACCESS_MASK DesiredAccess,
    IN  POBJECT_ATTRIBUTES ObjectAttributes,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    OUT PLARGE_INTEGER AllocationSize OPTIONAL,
    IN  ULONG FileAttributes,
    IN  ULONG ShareAccess,
    IN  ULONG CreateDisposition,
    IN  ULONG CreateOptions,
    IN  PVOID EaBuffer,
    IN  ULONG EaLength
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtReadFile(
    IN  HANDLE FileHandle,
    IN  HANDLE Event OPTIONAL,
    IN  PIO_APC_ROUTINE ApcRoutine OPTIONAL,
    IN  PVOID ApcContext OPTIONAL,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    OUT PVOID Buffer,
    IN  ULONG Length,
    IN  PLARGE_INTEGER ByteOffset OPTIONAL,
    IN  PULONG Key OPTIONAL
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtWriteFile(
    IN  HANDLE FileHandle,
    IN  HANDLE Event,
    IN  PIO_APC_ROUTINE ApcRoutine OPTIONAL,
    IN  PVOID ApcContext OPTIONAL,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    IN  PVOID Buffer,
    IN  ULONG Length,
    IN  PLARGE_INTEGER ByteOffset OPTIONAL,
    IN  PULONG Key OPTIONAL
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtFlushBuffersFile(
    IN  HANDLE FileHandle,
    OUT PIO_STATUS_BLOCK IoStatusBlock
);

#if CPP_DEFINED

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtSetInformationFile(
    IN  HANDLE                  FileHandle,
    OUT PIO_STATUS_BLOCK        IoStatusBlock,
    IN  PVOID                   FileInformation,
    IN  ULONG                   Length,
    IN  FILE_INFORMATION_CLASS  FileInformationClass
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtQueryDirectoryFile(
    IN  HANDLE                  FileHandle,
    IN  HANDLE                  Event  OPTIONAL,
    IN  PIO_APC_ROUTINE         ApcRoutine  OPTIONAL,
    IN  PVOID                   ApcContext  OPTIONAL,
    OUT PIO_STATUS_BLOCK        IoStatusBlock,
    OUT PVOID                   FileInformation,
    IN  ULONG                   Length,
    IN  FILE_INFORMATION_CLASS  FileInformationClass,
    IN  BOOLEAN                 ReturnSingleEntry,
    IN  PUNICODE_STRING         FileName  OPTIONAL,
    IN  BOOLEAN                 RestartScan
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtWaitForSingleObject(
    IN HANDLE         Handle,
    IN BOOLEAN        Alertable,
    IN PLARGE_INTEGER Timeout OPTIONAL
);

MY_DLL_IMPORT
BOOLEAN
NTAPI
RtlDosPathNameToNtPathName_U(
    IN PCWSTR DosName,
    OUT PUNICODE_STRING NtName,
    OUT PCWSTR *DosFilePath OPTIONAL,
    OUT PUNICODE_STRING NtFilePath OPTIONAL
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtQueryEaFile(
    IN  HANDLE FileHandle,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    OUT PVOID Buffer,
    IN  ULONG Length,
    IN  BOOLEAN ReturnSingleEntry,
    IN  PVOID EaList OPTIONAL,
    IN  ULONG EaListLength,
    IN  PULONG EaIndex OPTIONAL,
    IN  BOOLEAN RestartScan
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
CsrClientCallServer(
    PCSR_API_MESSAGE    ApiMessage,
    PCSR_CAPTURE_BUFFER CaptureBuffer OPTIONAL,
    CSR_API_NUMBER      ApiNumber,
    ULONG               RequestLength
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtGetNlsSectionPtr(
    ULONG    Unknown0,
    ULONG    Unknown1,
    PVOID    pUnknown OPTIONAL,
    PVOID   *pSectionBase,
    PSIZE_T  pSectionSize
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
NtSystemDebugControl(
    IN  SYSDBG_COMMAND  Command,
    IN  PVOID           InputBuffer,
    IN  ULONG           InputBufferLength,
    OUT PVOID           OutputBuffer,
    IN  ULONG           OutputBufferLength,
    OUT PULONG          ReturnLength
);

#endif

MY_DLL_IMPORT NTSTATUS NTAPI NtClose(IN HANDLE Handle);

#if !defined(_MY_NTLIB_DLL_ ) && !defined(_MY_NTLIB_)
MY_DLL_IMPORT Void     NTAPI RtlInitAnsiString(IN OUT PANSI_STRING DestinationString, IN LPCSTR SourceString);
MY_DLL_IMPORT NTSTATUS NTAPI RtlInitAnsiStringEx(IN OUT PANSI_STRING DestinationString, IN LPCSTR SourceString);
MY_DLL_IMPORT Void     NTAPI RtlInitUnicodeString(IN OUT PUNICODE_STRING  DestinationString, IN LPCWSTR  SourceString);
MY_DLL_IMPORT NTSTATUS NTAPI RtlInitUnicodeStringEx(IN OUT PUNICODE_STRING  DestinationString, IN LPCWSTR  SourceString);
MY_DLL_IMPORT NTSTATUS NTAPI RtlAnsiStringToUnicodeString(IN OUT PUNICODE_STRING  DestinationString, IN PANSI_STRING  SourceString, IN BOOLEAN  AllocateDestinationString);
MY_DLL_IMPORT NTSTATUS NTAPI RtlUnicodeStringToAnsiString(IN OUT PANSI_STRING  DestinationString, IN PUNICODE_STRING  SourceString, IN BOOLEAN  AllocateDestinationString);
MY_DLL_IMPORT NTSTATUS NTAPI RtlMultiByteToUnicodeN(PWSTR UnicodeString, ULONG MaxBytesInUnicodeString, PULONG BytesInUnicodeString OPTIONAL, PCHAR MultiByteString, ULONG BytesInMultiByteString);
MY_DLL_IMPORT NTSTATUS NTAPI RtlUnicodeToMultiByteSize(PULONG BytesInMultiByteString, PWSTR UnicodeString, ULONG BytesInUnicodeString);
MY_DLL_IMPORT NTSTATUS NTAPI RtlUnicodeToMultiByteN(OUT PCHAR MultiByteString, IN ULONG MaxBytesInMultiByteString, OUT PULONG BytesInMultiByteString OPTIONAL, IN PWSTR UnicodeString, IN ULONG BytesInUnicodeString);
MY_DLL_IMPORT NTSTATUS NTAPI RtlMultiByteToUnicodeSize(OUT PULONG BytesInUnicodeString, IN PCHAR MultiByteString, IN ULONG BytesInMultiByteString);

#ifndef _NTIFS_

MY_DLL_IMPORT VOID NTAPI RtlInitCodePageTable(IN PUSHORT pTableBase, OUT PCPTABLEINFO pCodePageTable);

MY_DLL_IMPORT
NTSTATUS
NTAPI
ZwGetNlsSectionPtr(
    ULONG  SectionIndex,
    ULONG  CodePage,
    ULONG  Unknown_0,
    PVOID  pSectionBase,
    PULONG pSectionSize
);
/*
MY_DLL_IMPORT
NTSTATUS
NTAPI
NtGetNlsSectionPtr(
    ULONG  SectionIndex,
    ULONG  CodePage,
    ULONG  Unknown_0,
    PVOID  pSectionBase,
    PULONG pSectionSize
);
*/
MY_DLL_IMPORT
NTSTATUS
NTAPI
RtlCustomCPToUnicodeN(
    IN  PCPTABLEINFO    pCustomCP,
    OUT PWCH            UnicodeString,
    IN  ULONG           MaxBytesInUnicodeString,
    OUT PULONG          BytesInUnicodeString OPTIONAL,
    IN  PCHAR           CustomCPString,
    IN  ULONG           BytesInCustomCPString
);

MY_DLL_IMPORT
NTSTATUS
NTAPI
RtlUnicodeToCustomCPN(
    IN  PCPTABLEINFO    pCustomCP,
    OUT PCHAR           pMultiByteString,
    IN  ULONG           MaxBytesInMultiByteString,
    OUT PULONG          BytesInMultiByteString OPTIONAL,
    IN  PWSTR           pUnicodeString,
    IN  ULONG           BytesInUnicodeString
);

#endif

MY_DLL_IMPORT NTSTATUS NTAPI ZwCreateThread(OUT PHANDLE ThreadHandle, IN ACCESS_MASK DesiredAccess, IN POBJECT_ATTRIBUTES ObjectAttributes, IN HANDLE ProcessHandle, OUT PCLIENT_ID ClientId, IN PCONTEXT ThreadContext, IN PUSER_STACK UserStack, IN BOOLEAN CreateSuspended);
MY_DLL_IMPORT NTSTATUS NTAPI NtCreateThread(OUT PHANDLE ThreadHandle, IN ACCESS_MASK DesiredAccess, IN POBJECT_ATTRIBUTES ObjectAttributes, IN HANDLE ProcessHandle, OUT PCLIENT_ID ClientId, IN PCONTEXT ThreadContext, IN PUSER_STACK UserStack, IN BOOLEAN CreateSuspended);
#endif

/************************************************************************/
/* my nt api                                                            */
/************************************************************************/
HMODULE Nt_GetModuleHandle(LPCWSTR lpModuleName);
ULONG   RtlGetModuleFileName(HMODULE hModule, LPWSTR lpFilename, ULONG nSize);
BOOL    Nt_SetExecuteDirectoryAsCurrent();

ULONG
Nt_WaitForSingleObjectEx(
    IN HANDLE hHandle,
    IN ULONG  Milliseconds,
    IN BOOL   bAlertable
);

MY_NTLIB_DLL_EXPORT VOID NTAPI MessageBoxErrorW(HWND hWnd, NTSTATUS Status, LPWSTR lpCaption, UINT uType);
MY_NTLIB_DLL_EXPORT VOID NTAPI PrintError(NTSTATUS Status);
MY_NTLIB_DLL_EXPORT VOID NTAPI Nt_Sleep(ULONG dwMilliseconds);
MY_NTLIB_DLL_EXPORT BOOL NTAPI Nt_TerminateThread(IN HANDLE hThread, IN ULONG dwExitCode);

FARPROC Nt_GetProcAddress(HMODULE hModule, LPCSTR lpProcName);

MY_NTLIB_DLL_EXPORT FORCEINLINE ULONG NTAPI HashAPI(PCChar pszName)
{
    ULONG Hash = 0;

    while (*(PByte)pszName)
    {
        Hash = _rotl(Hash, 0x0D) ^ *(PByte)pszName++;
    }

    return Hash;
}

FORCEINLINE HMODULE RtlGetExeModuleHandle()
{
    PVOID pTEB, pPebLdr;
    pTEB = NtCurrentTeb();
    pPebLdr = *(PVOID *)(*(PULONG_PTR)((ULONG_PTR)pTEB + 0x30) + 0xC);
    return *(HMODULE *)(*(PULONG_PTR)((ULONG_PTR)pTEB + 0x30) + 0x8);
}

inline ULONG RtlGetExecuteDirectoryW(PWCHAR pszPath, ULONG BufferCount)
{
    WCHAR szPath[MAX_PATH];
    ULONG i;

    if (pszPath == NULL)
    {
        pszPath = szPath;
        BufferCount = countof(szPath);
    }

    i = RtlGetModuleFileName(NULL, pszPath, BufferCount);
    if (i)
    {
        while (pszPath[--i] != '\\');
        pszPath[++i] = 0;
    }

    return i;
}

inline ULONG Nt_GetExecuteDirectoryA(PChar pszPath, ULONG BufferCount)
{
    WCHAR  szPath[MAX_PATH];
    ULONG i;

    i = RtlGetExecuteDirectoryW(szPath, countof(szPath));
    if (i)
    {
        i *= sizeof(WCHAR);
        RtlUnicodeToMultiByteN(pszPath, BufferCount, &i, szPath, i);
        if (i < BufferCount)
            pszPath[i] = 0;
    }

    return i;
}

FORCEINLINE VOID BaseSetLastNTError(NTSTATUS Status)
{
    RtlSetLastWin32ErrorAndNtStatusFromNtStatus(Status);
}

FORCEINLINE HANDLE RtlGetProcessHeap()
{
    PVOID pTEB;
    pTEB = NtCurrentTeb();
    pTEB = *(PVOID *)((ULONG_PTR)pTEB + 0x30);
    return *(PHANDLE)((ULONG_PTR)pTEB + 0x18);
}

FORCEINLINE PUSHORT RtlGetDefaultCodePageBase()
{
    PVOID pPEB, pTEB;

    pTEB = NtCurrentTeb();
    pPEB = *(PVOID *)((ULONG_PTR)pTEB + 0x30);
    return *(PUSHORT *)((ULONG_PTR)pPEB + 0x58);
}

/*
ForceInline HMODULE NTAPI GetKernel32Module()
{
    __asm
    {
        mov  eax, dword ptr fs:[030h];
        mov  eax, dword ptr [eax+0Ch];
        mov  eax, dword ptr [eax+01Ch];
        mov  eax, dword ptr [eax];
        mov  eax, dword ptr [eax+8];
    }
}
*/

FORCEINLINE ULONG RtlGetCurrentThreadId()
{
    return *(PDWORD)((ULONG_PTR)NtCurrentTeb() + 0x24);
}

FORCEINLINE HMODULE GetKernel32Handle()
{
    PVOID     pPEB;
    ULONG_PTR pKernel32;

    pPEB = (PVOID)__readfsdword(0x30);
    pKernel32 = (ULONG_PTR)pPEB;
    pKernel32 = *(PULONG_PTR)((ULONG_PTR)pKernel32 + 0xC);
    pKernel32 = *(PULONG_PTR)((ULONG_PTR)pKernel32 + 0xC);
    pKernel32 = *(PULONG_PTR)pKernel32;
    pKernel32 = *(PULONG_PTR)pKernel32;
    pKernel32 = *(PULONG_PTR)(pKernel32 + 0x18);
    return (HMODULE)pKernel32;
}

FORCEINLINE HMODULE GetNtdllHandle()
{
    PVOID     pPEB;
    ULONG_PTR pNtDll;

    pPEB = (PVOID)__readfsdword(0x30);
    pNtDll = (ULONG_PTR)pPEB;
    pNtDll = *(PULONG_PTR)((ULONG_PTR)pNtDll + 0xC);
    pNtDll = *(PULONG_PTR)((ULONG_PTR)pNtDll + 0x1C);
    pNtDll = *(PULONG_PTR)(pNtDll + 0x8);
    return (HMODULE)pNtDll;
/*
    _asm
    {
        mov eax, fs:[0x30];
        mov eax, [eax+0Ch];
        mov eax, [eax+1Ch];
        mov eax, [eax+8h];
    }
*/
}

inline HANDLE Nt_GetCurrentDirectoryHandle()
{
    PVOID pTEB;

    pTEB = (PVOID)NtCurrentTeb();
    return *(PHANDLE)(*(PULONG_PTR)(*(PULONG_PTR)((ULONG_PTR)pTEB + 0x30) + 0x10) + 0x2C);
}

inline Bool GetErrorMessage(HMODULE hModuleDll, ULONG ErrorCode, MESSAGE_RESOURCE_ENTRY **ppMsgEntry)
{
    NTSTATUS Status;

    if (hModuleDll == NULL)
        hModuleDll = GetKernel32Handle();

    Status = RtlFindMessage(hModuleDll, (ULONG)RT_MESSAGETABLE, LANG_SYSTEM_DEFAULT, ErrorCode, ppMsgEntry);

    return NT_SUCCESS(Status);
}

FORCEINLINE Int32 FASTCALL StringCompare(PCChar lpString1, PCChar lpString2)
{
    Char ch1, ch2;

    do
    {
        ch1 = *lpString1++;
        ch2 = *lpString2++;
    } while (ch1 && !(ch1 ^ ch2));
    return (Int32)(ch1 - ch2);

    __asm
    {
        mov esi,lpString1;
        mov edi,lpString2;
START:
        lodsb;
        scasb;
        jne NOTEQ;
        test al,al;
        jne START;
        xor eax,eax;
        jmp ENDCMP;
NOTEQ:
        mov eax,1;
        jl ENDCMP;
        neg eax;

ENDCMP:
    }
}

#pragma intrinsic(memcmp)
FARPROC WINAPI GetFunctionAddress(HMODULE hModule, LPCSTR lpProcName);

inline FARPROC WINAPI GetFunctionAddressWorker(HMODULE hModule, LPCSTR lpProcName, Bool bRecursion)
{
    PIMAGE_DOS_HEADER       pDosHeader;
    PIMAGE_NT_HEADERS       pNtHeader;
    PIMAGE_DATA_DIRECTORY   pDataDirectory;
    PIMAGE_EXPORT_DIRECTORY pExportDirectory;
    ULONG dwIndex;
    LPSTR lpFunName;
    PDWORD pAddressOfNames;
    PUSHORT pAddressOfNameOrdinals;
    PDWORD pAddressOfFunctions;

    static HMODULE (WINAPI *LoadLibraryExW)(LPCWSTR lpFileName, HANDLE hFile, ULONG dwFlags);
    static HMODULE (WINAPI *GetModuleHandleExW)(ULONG dwFlags, LPCWSTR lpModuleName, HMODULE* phModule);

    if (hModule == NULL || lpProcName == NULL)
        return NULL;

    //判断PE合法性
    pDosHeader = (IMAGE_DOS_HEADER*)hModule;
    if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
        return NULL;

    pNtHeader = (IMAGE_NT_HEADERS*)((PByte)hModule + pDosHeader->e_lfanew);
    if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
        return NULL;

    //判断是否有导出表
    pDataDirectory = &pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (pDataDirectory->Size == 0 || pDataDirectory->VirtualAddress == 0)
        return NULL;

    pExportDirectory=(PIMAGE_EXPORT_DIRECTORY)((PByte)hModule + pDataDirectory->VirtualAddress);

    pAddressOfNames = (PDWORD)pExportDirectory->AddressOfNames;
    if (pAddressOfNames == NULL)
        return NULL;

    pAddressOfNameOrdinals = (LPWORD)pExportDirectory->AddressOfNameOrdinals;
    if (pAddressOfNameOrdinals == NULL)
        return NULL;

    pAddressOfFunctions = (PDWORD)pExportDirectory->AddressOfFunctions;
    if (pAddressOfFunctions == NULL)
        return NULL;

    pAddressOfNames        += (ULONG)hModule / sizeof(*pAddressOfNames);
    pAddressOfNameOrdinals += (ULONG)hModule / sizeof(*pAddressOfNameOrdinals);
    pAddressOfFunctions    += (ULONG)hModule / sizeof(*pAddressOfFunctions);

    if (bRecursion == False && LoadLibraryExW == NULL)
    {
        HMODULE hKernel32 = GetKernel32Handle();
        *(FARPROC *)&LoadLibraryExW = GetFunctionAddressWorker(hKernel32, "LoadLibraryExW", True);
        *(FARPROC *)&GetModuleHandleExW = GetFunctionAddressWorker(hKernel32, "GetModuleHandleExW", True);
    }

    //按序号导出
    if ((ULONG)lpProcName < 0x10000)
    {
        dwIndex = (ULONG)lpProcName-pExportDirectory->Base;

        if (dwIndex >= pExportDirectory->NumberOfFunctions)
            return NULL;

        return (FARPROC)(ULong_Ptr)((PByte)hModule + pAddressOfFunctions[dwIndex]);
    }
    else    // 按名称导出
    {
        for (dwIndex = 0; dwIndex < pExportDirectory->NumberOfFunctions; dwIndex++)
        {
            lpFunName=(LPSTR)((PByte)hModule + pAddressOfNames[dwIndex]);
            if (!StringCompare(lpProcName, lpFunName))
            {
                PByte pbFunction;

                pbFunction = (PByte)hModule + pAddressOfFunctions[pAddressOfNameOrdinals[dwIndex]];
                if (pbFunction > (PByte)pExportDirectory && pbFunction < (PByte)pExportDirectory + pDataDirectory->Size)
                {
                    HMODULE hModule;
                    WCHAR *pDllName, szDllName[MAX_PATH];

                    pDllName = szDllName;
                    while ((*pDllName++ = (WCHAR)*pbFunction++) != L'.');
                    *--pDllName = 0;

                    GetModuleHandleExW(2, szDllName, &hModule);
                    if (hModule == NULL)
                    {
                        hModule = LoadLibraryExW(szDllName, 0, 0);
                    }
                    pbFunction = (PByte)(ULong_Ptr)GetFunctionAddress(hModule, (LPCSTR)pbFunction);
                }

                return (FARPROC)(ULong_Ptr)pbFunction;
            }
        }
    }

    return NULL;
}

inline FARPROC WINAPI GetFunctionAddress(HMODULE hModule, LPCSTR lpProcName)
{
    return GetFunctionAddressWorker(hModule, lpProcName, False);
}

_MY_C_TAIL_

#if CPP_DEFINED

#undef GetFuncAddress
#define GetFuncAddress(p, m, n) *(LPVoid *)&(p) = GetFunctionAddress(m, n)

struct SFunctionBaseUser32
{
    // user32.dll
    int   (WINAPI *MessageBoxA)(HWND hWnd, LPCSTR  lpText, LPCTSTR lpCaption, UINT uType);
    int   (WINAPI *MessageBoxW)(HWND hWnd, LPCWSTR lpText, LPCTSTR lpCaption, UINT uType);
    BOOL  (WINAPI *GetMessageA)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
    BOOL  (WINAPI *GetMessageW)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
    BOOL  (WINAPI *PeekMessageA)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
    BOOL  (WINAPI *PeekMessageW)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
    int   (CDECL  *wsprintfA)(LPSTR  lpOut, LPCSTR  lpFmt, ...);
    int   (CDECL  *wsprintfW)(LPWSTR lpOut, LPCWSTR lpFmt, ...);
    SHORT (WINAPI *GetKeyState)(int nVirtKey);
    SHORT (WINAPI *GetAsyncKeyState)(int nVirtKey);
};

struct SFunctionBaseGdi32
{
    // gdi32.dll
    BOOL    (WINAPI *GetTextMetricsA)(HDC hdc, LPTEXTMETRICA lptm);
    HGDIOBJ (WINAPI *SelectObject)(HDC hDC, HGDIOBJ hGdiObj);
    HFONT   (WINAPI *CreateFontIndirectA)(IN CONST LOGFONTA *lplf);
    ULONG   (WINAPI *GetGlyphOutlineW)(IN HDC hdc, IN UINT uChar, IN UINT fuFormat, OUT LPGLYPHMETRICS lpgm, IN ULONG cjBuffer, LPVOID pvBuffer, IN CONST MAT2 *lpmat2);
};

struct SFunctionBaseKernel32
{
    // kernel32.dll
#if defined(__cplusplus)
    HMODULE (WINAPI *LoadStayedLibraryA)(LPCSTR lpLibFileName, SFunctionBaseKernel32 *k);
#endif
    HANDLE  (WINAPI *CreateMutexA)(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR  lpName);
    HANDLE  (WINAPI *CreateMutexW)(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName);
    HGLOBAL (WINAPI *GlobalAlloc)(UINT uFlags, SIZE_T dwBytes);
    ULONG   (WINAPI *GetFileAttributesA)(LPCSTR lpFileName);
    HANDLE  (WINAPI *CreateFileA)(LPCSTR  lpFileName, ULONG dwDesiredAccess, ULONG dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, ULONG dwCreationDisposition, ULONG dwFlagsAndAttributes, HANDLE hTemplateFile);
    HANDLE  (WINAPI *CreateFileW)(LPCWSTR lpFileName, ULONG dwDesiredAccess, ULONG dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, ULONG dwCreationDisposition, ULONG dwFlagsAndAttributes, HANDLE hTemplateFile);
    ULONG   (WINAPI *SetFilePointer)(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, ULONG dwMoveMethod);
    BOOL    (WINAPI *ReadFile)(HANDLE hFile, LPVOID lpBuffer, ULONG nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
    Bool    (WINAPI *CloseHandle)(HANDLE hObject);
    HMODULE (WINAPI *GetModuleHandleA)(LPCSTR lpModuleName);
    HMODULE (WINAPI *GetModuleHandleW)(LPCWSTR lpModuleName);
    HMODULE (WINAPI *GetModuleHandleExA)(ULONG dwFlags, LPCSTR  lpModuleName, HMODULE *phModule);
    HMODULE (WINAPI *GetModuleHandleExW)(ULONG dwFlags, LPCWSTR lpModuleName, HMODULE *phModule);
    ULONG   (WINAPI *GetModuleFileNameA)(HMODULE hModule, LPSTR  lpFilename,ULONG nSize);
    ULONG   (WINAPI *GetModuleFileNameW)(HMODULE hModule, LPWSTR lpFilename,ULONG nSize);
    int     (WINAPI *MultiByteToWideChar)(UINT CodePage, ULONG dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
    ULONG   (WINAPI *GetLastError)();
    BOOL    (WINAPI *CreateDirectoryA)(LPCSTR lpPathName,  LPSECURITY_ATTRIBUTES lpSecurityAttributes);
    BOOL    (WINAPI *CreateDirectoryW)(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
    LPSTR   (WINAPI *lstrcpyA)(LPSTR  lpString1,  LPCSTR lpString2);
    LPSTR   (WINAPI *lstrcpyW)(LPWSTR lpString1, LPCWSTR lpString2);
    int     (WINAPI *lstrlenA)(LPCSTR lpString);
    int     (WINAPI *lstrlenW)(LPCWSTR lpString);
    int     (WINAPI *lstrcmpA)(LPCSTR  lpString1, LPCSTR  lpString2);
    int     (WINAPI *lstrcmpW)(LPCWSTR lpString1, LPCWSTR lpString2);
    int     (WINAPI *lstrcmpiA)(LPCSTR  lpString1, LPCSTR  lpString2);
    int     (WINAPI *lstrcmpiW)(LPCWSTR lpString1, LPCWSTR lpString2);
    HANDLE  (WINAPI *GetProcessHeap)();
    LPVOID  (WINAPI *HeapAlloc)(HANDLE hHeap, ULONG dwFlags, SIZE_T dwBytes);
    LPVOID  (WINAPI *HeapReAlloc)(HANDLE hHeap, ULONG dwFlags, LPVOID lpMem, SIZE_T dwBytes);
    BOOL    (WINAPI *HeapFree)(HANDLE hHeap, ULONG dwFlags, LPVOID lpMem);
    Void    (WINAPI *Sleep)(ULONG dwMilliseconds);
    Void    (WINAPI *InitializeCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
    Void    (WINAPI *EnterCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
    Void    (WINAPI *LeaveCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
    Void    (WINAPI *DeleteCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
    HANDLE  (WINAPI *CreateEventA)(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR  lpName);
    HANDLE  (WINAPI *CreateEventW)(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName);
    BOOL    (WINAPI *SetEvent)(HANDLE hEvent);
    BOOL    (WINAPI *ResetEvent)(HANDLE hEvent);
    ULONG   (WINAPI *WaitForSingleObject)(HANDLE hHandle, ULONG dwMilliseconds);
    ULONG   (WINAPI *WaitForSingleObjectEx)(HANDLE hHandle, ULONG dwMilliseconds, BOOL bAlertable);
    BOOL    (WINAPI *TerminateThread)(HANDLE hThread, ULONG dwExitCode);
//    LONG    (WINAPI *InterlockedIncrement)(IN PLONG Addend);
//    LONG    (WINAPI *InterlockedDecrement)(IN PLONG Addend);
//    LONG    (WINAPI *InterlockedExchange)(IN OUT PLONG  Target, IN LONG  Value);
//    LONG    (WINAPI *InterlockedCompareExchange)(IN OUT PLONG  Destination, IN LONG  Exchange, IN LONG  Comparand);
    HMODULE (WINAPI *LoadLibraryA)(LPCSTR  lpLibFileName);
    HMODULE (WINAPI *LoadLibraryW)(LPCWSTR lpLibFileName);
    HMODULE (WINAPI *LoadLibraryExA)(LPCSTR  lpLibFileName, HANDLE hFile, ULONG dwFlags);
    HMODULE (WINAPI *LoadLibraryExW)(LPCWSTR lpLibFileName, HANDLE hFile, ULONG dwFlags);
    HMODULE (WINAPI *FreeLibrary)(HMODULE hModule);
    BOOL    (WINAPI *VirtualProtectEx)(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, ULONG flNewProtect, PDWORD lpflOldProtect);
};

struct SFunctionUCI
{
    // ucidec.dll
    int (WINAPI *UCIDecode)(const void *src, int srclen, void** dst, int* stride, int* w, int* h, int* bpp);
    int (WINAPI *UCIFree)(void* p);

    // ucadec.dll
    int (WINAPI *UCADecode)(const void *src, int srclen, void** dst, int* dstlen);
    int (WINAPI *UCADecode2)(const void *src, int srclen, void** dst, int* dstlen, int sample);
    int (WINAPI *UCAFree)(void* p);
};

#endif // CPP_DEFINED

#endif // _NT_API_H__
#ifndef _IROTORI_H_dca8efd8_b07d_4f39_83fd_1f7d60d8fa2d_
#define _IROTORI_H_dca8efd8_b07d_4f39_83fd_1f7d60d8fa2d_

#include "MyLibraryUser.h"
#include "cxdec.h"

#pragma warning(disable:4201 4238)

#define CODE_PAGE_NLS_KEY           L"SYSTEM\\ControlSet001\\Control\\Nls\\CodePage"
#define SYSTEM_PATH_KEY             L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Installer"
#define SYSTEM_PATH_VALUE           L"InstallerLocation"
#define IOCTL_DECRYPT_TEXT          ((ULONG)CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_IN_DIRECT, FILE_ANY_ACCESS) | (1 << 31))

#define THREAD_TEXT_BUFFER_MAGIC        TAG4('TTBM')
#define THREAD_START_PARAMETER_MAGIC    TAG4('TSPM')
#define DEFAULT_THREAD_START_ADDRESS    (ULONG_PTR)~0u

typedef struct
{
    ULONG Hash[4];
    ULONG Length;
    CHAR  Text[1];

} TEXT_NODE, *PTEXT_NODE;

typedef struct
{
    struct
    {
        UCHAR   Initialized : 1;
    };
/*
    CPTABLEINFO     CpTable936;
    CPTABLEINFO     CpTable932;
    PVOID           CP932;
    PVOID           CP936;
*/
    PVOID           TextBuffer;
    ULONG           TextCount;
    PTEXT_NODE*     Text;
    NtFileDisk      Device;

    Cxdec           cxdec;


    TYPE_OF(RtlPushFrame)           *RtlPushFrame;
    TYPE_OF(RtlGetFrame)            *RtlGetFrame;
    TYPE_OF(RtlPopFrame)            *RtlPopFrame;
    TYPE_OF(CompareStringA)         *CompareStringA;
    TYPE_OF(NtProtectVirtualMemory) *NtProtectVirtualMemory;
    TYPE_OF(NtGetContextThread)     *NtGetContextThread;
    TYPE_OF(NtSetContextThread)     *NtSetContextThread;
    TYPE_OF(NtCreateTimer)          *NtCreateTimer;
    TYPE_OF(NtSetTimer)             *NtSetTimer;
    TYPE_OF(NtTestAlert)            *NtTestAlert;
    TYPE_OF(LdrInitializeThunk)     *StubLdrInitializeThunk;
    TYPE_OF(DbgUiRemoteBreakin)     *DbgUiRemoteBreakin;
    TYPE_OF(NtCreateThread)         *NtCreateThread;
    TYPE_OF(NtCreateThreadEx)       *NtCreateThreadEx;
    TYPE_OF(RtlCreateUserThread)    *RtlCreateUserThread;
    TYPE_OF(LdrInitializeThunk)     *LdrInitializeThunk;

} IROTORI_INFO, *PIROTORI_INFO;

typedef struct
{
    UCHAR   Type;
    UCHAR   PadFor2Byte;
    USHORT  StackBase;
    ULONG   Value;

} IROTORI_STACK_ENTRY, *PIROTORI_STACK_ENTRY;

typedef struct
{
    DUMMY_STRUCT(4);                        // 0x000

    PVOID ScriptBuffer;                     // 0x004
    IROTORI_STACK_ENTRY StackEntry[0x100];  // 0x008

    DUMMY_STRUCT(0x14);                     // 0x808

    ULONG_PTR NextOpOfffset;                // 0x81C
    ULONG_PTR StackTop;                     // 0x820

} IROTORI_SCRIPT_OBJECT, *PIROTORI_SCRIPT_OBJECT;

struct THREAD_TEXT_BUFFER : TEB_ACTIVE_FRAME
{
    ULONG                   Length;
    PCHAR                   Buffer;
    PTEXT_NODE              Text;
    PULONG                  Hash;
    ULONG                   TextLength;
    PIROTORI_SCRIPT_OBJECT  Object;

    THREAD_TEXT_BUFFER()
    {
        ZeroMemory(this, sizeof(*this));
        this->Context = THREAD_TEXT_BUFFER_MAGIC;
    }
};

typedef THREAD_TEXT_BUFFER *PTHREAD_TEXT_BUFFER;

struct IrotoriScriptObject
{
    PSTR *Prefix;

    VOID THISCALL HookCopyPrefix(PSTR String);
    VOID THISCALL HookCatString(PSTR String);
    VOID THISCALL HookCatQuote(PSTR String);
    VOID THISCALL HookCopyDescription(PSTR String);
};

struct THREAD_START_PARAMETER : public TEB_ACTIVE_FRAME
{
    PVOID ThreadStartRoutine;
    PVOID Parameter;

    THREAD_START_PARAMETER()
    {
        Context = THREAD_START_PARAMETER_MAGIC;
    }
};

typedef THREAD_START_PARAMETER *PTHREAD_START_PARAMETER;

#endif // _IROTORI_H_dca8efd8_b07d_4f39_83fd_1f7d60d8fa2d_

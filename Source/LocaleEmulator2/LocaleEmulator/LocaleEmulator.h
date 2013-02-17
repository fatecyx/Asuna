#ifndef _LOCALEEMULATOR_H_cd444a0d_c7f9_44b2_aac8_8107e9a07ca2_
#define _LOCALEEMULATOR_H_cd444a0d_c7f9_44b2_aac8_8107e9a07ca2_

#include "MyLibrary.h"
#include "mlns.h"

#define ROOTDIR_SYSTEM32            L"\\SystemRoot\\system32\\"

#define REGKEY_ROOT                 HKEY_LOCAL_MACHINE

#define REGPATH_CODEPAGE            L"System\\CurrentControlSet\\Control\\Nls\\CodePage"
#define REGPATH_LANGUAGE            L"System\\CurrentControlSet\\Control\\Nls\\Language"
#define REGKEY_ACP                  L"ACP"
#define REGKEY_OEMCP                L"OEMCP"
#define REGKEY_DEFAULT_LANGUAGE     L"Default"

#define PROP_WINDOW_ANSI_PROC       L"Asuna"
#define PROP_WINDOW_UNICODE_PROC    L"½Y³ÇÃ÷ÈÕÄÎ"

#define FORMAT_LOCALE_ENUMLATOR_PROCESS_ENVIRONMENT_BLOCK   L"Local\\LOCALE_ENUMLATOR_PROCESS_ENVIRONMENT_BLOCK_SECTION_%p"

typedef struct
{
    ULONG AnsiCodePage;
    ULONG OemCodePage;
    ULONG LocaleID;
    ULONG DefaultCharset;

    WCHAR DefaultFaceName[LF_FACESIZE];

    RTL_TIME_ZONE_INFORMATION Timezone;

} LOCALE_ENUMLATOR_ENVIRONMENT_BLOCK, *PLOCALE_ENUMLATOR_ENVIRONMENT_BLOCK, LEB, *PLEB;

typedef struct
{
    LEB Leb;

    HANDLE  Section;
    PVOID   ooxxAddress;
    ULONG   ooxxValue;
    PVOID   SelfShadowToFree;

    WCHAR   LeDllFullPath[MAX_NTPATH];

} LOCALE_ENUMLATOR_PROCESS_ENVIRONMENT_BLOCK, *PLOCALE_ENUMLATOR_PROCESS_ENVIRONMENT_BLOCK, LEPEB, *PLEPEB;

inline
ULONG_PTR
GetLePebSectionName(
    PWSTR       Buffer,
    ULONG_PTR   ProcessId
)
{
    return swprintf(Buffer, FORMAT_LOCALE_ENUMLATOR_PROCESS_ENVIRONMENT_BLOCK, ProcessId);
}

inline NTSTATUS CloseLePeb(PLEPEB LePeb)
{
    return LePeb == NULL ? STATUS_INVALID_PARAMETER : ZwUnmapViewOfSection(CurrentProcess, LePeb);
}

inline
PLEPEB
OpenOrCreateLePeb(
    ULONG_PTR   ProcessId   = CurrentPid(),
    BOOL        Create      = FALSE
)
{
    NTSTATUS            Status;
    WCHAR               SectionNameBuffer[MAX_NTPATH];
    OBJECT_ATTRIBUTES   ObjectAttributes;
    UNICODE_STRING      SectionName, BaseNamedObjectsName;
    HANDLE              SectionHandle, BaseNamedObjects;
    PLEPEB              LePeb;
    ULONG_PTR           ViewSize, SessionId;
    LARGE_INTEGER       MaximumSize;

    SessionId = GetSessionId(ProcessId);
    if (SessionId == INVALID_SESSION_ID)
        return NULL;

    BaseNamedObjectsName.Length         = swprintf(SectionNameBuffer, L"\\Sessions\\%d\\BaseNamedObjects", SessionId) * sizeof(WCHAR);
    BaseNamedObjectsName.MaximumLength  = BaseNamedObjectsName.Length;
    BaseNamedObjectsName.Buffer         = SectionNameBuffer;

    InitializeObjectAttributes(&ObjectAttributes, &BaseNamedObjectsName, OBJ_CASE_INSENSITIVE, NULL, NULL);
    Status = ZwOpenDirectoryObject(&BaseNamedObjects, DIRECTORY_ALL_ACCESS, &ObjectAttributes);
    if (NT_FAILED(Status))
        return NULL;

    SectionName.Length          = (USHORT)GetLePebSectionName(SectionNameBuffer, ProcessId) * sizeof(WCHAR);
    SectionName.MaximumLength   = SectionName.Length;
    SectionName.Buffer          = SectionNameBuffer;

    InitializeObjectAttributes(&ObjectAttributes, &SectionName, 0, BaseNamedObjects, NULL);

    Status = ZwOpenSection(&SectionHandle, SECTION_ALL_ACCESS, &ObjectAttributes);
    if (NT_FAILED(Status) && Create)
    {
        MaximumSize.QuadPart = sizeof(*LePeb);
        Status = ZwCreateSection(
                    &SectionHandle,
                    SECTION_ALL_ACCESS,
                    &ObjectAttributes,
                    &MaximumSize,
                    PAGE_READWRITE,
                    SEC_COMMIT,
                    NULL
                );
    }

    ZwClose(BaseNamedObjects);

    if (NT_FAILED(Status))
        return NULL;

    ViewSize = 0;
    LePeb = NULL;
    Status = ZwMapViewOfSection(
                SectionHandle,
                CurrentProcess,
                (PVOID *)&LePeb,
                0,
                sizeof(*LePeb),
                NULL,
                &ViewSize,
                ViewShare,
                0,
                PAGE_READWRITE
            );

    if (NT_FAILED(Status))
    {
        ZwClose(SectionHandle);
        return NULL;
    }

    if (Create) LOOP_ONCE
    {
        HANDLE ProcessHandle;

        ProcessHandle = PidToHandle(ProcessId);
        if (ProcessHandle == NULL)
        {
            Status = STATUS_ACCESS_DENIED;
            break;
        }

        Status = ZwDuplicateObject(CurrentProcess, SectionHandle, ProcessHandle, &LePeb->Section, 0, 0, DUPLICATE_SAME_ACCESS);
        FAIL_BREAK(Status);
    }

    ZwClose(SectionHandle);
    if (NT_FAILED(Status))
    {
        CloseLePeb(LePeb);
        return NULL;
    }

    return LePeb;
}

class LeGlobalData
{
protected:
    BOOLEAN Wow64 : 1;

    LEPEB LePeb;

    PVOID CodePageMapView;
    ULONG_PTR AnsiCodePageOffset, OemCodePageOffset, UnicodeCaseTableOffset;

    PVOID DllNotificationCookie;

    UNICODE_STRING SystemDirectory;

public:

    struct
    {
        API_POINTER(NtUserMessageCall)          StubNtUserMessageCall;
        API_POINTER(NtUserDefSetText)           StubNtUserDefSetText;
        API_POINTER(SetWindowLongA)             StubSetWindowLongA;
        API_POINTER(GetWindowLongA)             StubGetWindowLongA;
        API_POINTER(IsWindowUnicode)            StubIsWindowUnicode;

        union
        {
            PVOID                                       StubNtUserCreateWindowEx;
            API_POINTER(::NtUserCreateWindowEx_Win7)    StubNtUserCreateWindowEx_Win7;
            API_POINTER(::NtUserCreateWindowEx_Win8)    StubNtUserCreateWindowEx_Win8;
        };

        API_POINTER(CreateFontIndirectExW)      StubCreateFontIndirectExW;
        API_POINTER(CreateCompatibleDC)         StubCreateCompatibleDC;
        API_POINTER(EnumFontFamiliesExA)        StubEnumFontFamiliesExA;
        API_POINTER(EnumFontFamiliesExW)        StubEnumFontFamiliesExW;

    } HookStub;

    ATOM AtomAnsiProc; //, AtomUnicodeProc;

    struct HookRoutineData
    {
        ~HookRoutineData()
        {
            RtlFreeUnicodeString(&CodePageKey);
            RtlFreeUnicodeString(&LanguageKey);
        }

        UNICODE_STRING CodePageKey;
        UNICODE_STRING LanguageKey;

    } HookRoutineData;

public:
    LeGlobalData()
    {
        ZeroMemory(this, sizeof(*this));
    }

    ~LeGlobalData()
    {
        UnInitialize();
    }

    PLEPEB GetLePeb()
    {
        return &LePeb;
    }

    PLEB GetLeb()
    {
        return &LePeb.Leb;
    }

    NTSTATUS Initialize();
    NTSTATUS UnInitialize();

    VOID DllNotification(ULONG NotificationReason, PCLDR_DLL_NOTIFICATION_DATA NotificationData);
    VOID HookModule(PVOID DllBase, PCUNICODE_STRING DllName, BOOL DllLoad);

    NTSTATUS HookUser32Routines(PVOID User32);
    NTSTATUS UnHookUser32Routines();

    NTSTATUS HookGdi32Routines(PVOID Gdi32);
    NTSTATUS UnHookGdi32Routines();

    NTSTATUS HookNtdllRoutines(PVOID Ntdll);
    NTSTATUS UnHookNtdllRoutines();

    NTSTATUS InjectSelfToChildProcess(HANDLE Process, PCLIENT_ID Cid);

    /************************************************************************
      helper func
    ************************************************************************/

    /************************************************************************
      user32
    ************************************************************************/

    PVOID GetWindowDataA(HWND Window)
    {
        return GetPropW(Window, (PCWSTR)AtomAnsiProc);
    }

    BOOL SetWindowDataA(HWND Window, PVOID Data)
    {
        return SetPropW(Window, (PCWSTR)AtomAnsiProc, Data);
    }
/*
    PVOID GetWindowDataW(HWND Window)
    {
        return GetPropW(Window, (PCWSTR)AtomUnicodeProc);
    }

    BOOL SetWindowDataW(HWND Window, PVOID Data)
    {
        return SetPropW(Window, (PCWSTR)AtomUnicodeProc, Data);
    }
*/
    LONG_PTR GetWindowLongA(HWND hWnd, int Index)
    {
        return HookStub.StubGetWindowLongA(hWnd, Index);
    }

    LONG_PTR SetWindowLongA(HWND hWnd, int Index, LONG_PTR NewLong)
    {
        return HookStub.StubSetWindowLongA(hWnd, Index, NewLong);
    }

    BOOL IsWindowUnicode(HWND hWnd)
    {
        return HookStub.StubIsWindowUnicode(hWnd);
    }

    LRESULT NtUserMessageCall(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam, ULONG_PTR xParam, DWORD xpfnProc, ULONG Flags)
    {
        return HookStub.StubNtUserMessageCall(hWnd, Message, wParam, lParam, xParam, xpfnProc, Flags);
    }

    HWND NtUserCreateWindowEx_Win7(ULONG ExStyle, PLARGE_UNICODE_STRING ClassName, PLARGE_UNICODE_STRING ClassVersion, PLARGE_UNICODE_STRING WindowName, ULONG Style, LONG X, LONG Y, LONG Width, LONG Height, HWND ParentWnd, HMENU Menu, PVOID Instance, LPVOID Param, ULONG ShowMode, ULONG Unknown)
    {
        return HookStub.StubNtUserCreateWindowEx_Win7(ExStyle, ClassName, ClassVersion, WindowName, Style, X, Y, Width, Height, ParentWnd, Menu, Instance, Param, ShowMode, Unknown);
    }

    HWND NtUserCreateWindowEx_Win8(ULONG ExStyle, PLARGE_UNICODE_STRING ClassName, PLARGE_UNICODE_STRING ClassVersion, PLARGE_UNICODE_STRING WindowName, ULONG Style, LONG X, LONG Y, LONG Width, LONG Height, HWND ParentWnd, HMENU Menu, PVOID Instance, LPVOID Param, ULONG ShowMode, ULONG Unknown, ULONG Unknown2)
    {
        return HookStub.StubNtUserCreateWindowEx_Win8(ExStyle, ClassName, ClassVersion, WindowName, Style, X, Y, Width, Height, ParentWnd, Menu, Instance, Param, ShowMode, Unknown, Unknown2);
    }

    BOOL NtUserSetDefText(HWND hWnd, PLARGE_UNICODE_STRING Text)
    {
        return HookStub.StubNtUserDefSetText(hWnd, Text);
    }

    /************************************************************************
      gdi32
    ************************************************************************/

    HFONT CreateFontIndirectExW(PENUMLOGFONTEXDVW penumlfex)
    {
        return HookStub.StubCreateFontIndirectExW(penumlfex);
    }

    HDC CreateCompatibleDC(HDC hDC)
    {
        return HookStub.StubCreateCompatibleDC(hDC);
    }

    int EnumFontFamiliesExA(HDC hdc, LPLOGFONTA lpLogfont, FONTENUMPROCA lpProc, LPARAM lParam, DWORD dwFlags)
    {
        return HookStub.StubEnumFontFamiliesExA(hdc, lpLogfont, lpProc, lParam, dwFlags);
    }

    int EnumFontFamiliesExW(HDC hdc, LPLOGFONTW lpLogfont, FONTENUMPROCW lpProc, LPARAM lParam, DWORD dwFlags)
    {
        return HookStub.StubEnumFontFamiliesExW(hdc, lpLogfont, lpProc, lParam, dwFlags);
    }
};

typedef LeGlobalData* PLeGlobalData;

ForceInline PLeGlobalData LeGetGlobalData()
{
    extern PLeGlobalData g_GlobalData;
    return g_GlobalData;
}

#endif // _LOCALEEMULATOR_H_cd444a0d_c7f9_44b2_aac8_8107e9a07ca2_

#pragma comment(linker, "/ENTRY:wWinMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "MyLibrary.cpp"
#include "WindowBase.h"
#include "resource.h"
#include "AntiDebug.cpp"
#include "mlns.h"

using namespace MlWindowClass;

enum
{
    ExceptionVerifyString   = EXCEPTION_CODE(EXCEPTION_CODE_USER + 1),
};

SIZE_T (NTAPI *StubRtlCompareMemory)(PVOID Source1, PVOID Source2, SIZE_T Length);

ForceInline
ULONG
HashBuffer(
    PVOID Buffer,
    ULONG Length
)
{
    PBYTE Buf;
    ULONG Hash;

    Hash = 0x20101118;
    Buf  = (PBYTE)Buffer;
    for (; Length; --Length)
    {
        Hash -= *Buf++;
    }

    return Hash * PtrOffset(Buf, Buffer);
}

SIZE_T NTAPI HookRtlCompareMemory(PVOID Source1, PVOID Source2, SIZE_T Length)
{
    SIZE_T      Length2, Result;
    WCHAR       TrueString[0x10];
    PLDR_MODULE Module;

    if (Length < 10 || HashBuffer(Source2, 10) != 0x40A097B8)   // L"Amano"
    {
NORMAL_COMPARE:
        return StubRtlCompareMemory(Source1, Source2, Length);
    }

    Module = FindLdrModuleByHandle(NULL);
    if (
        (ULONG_PTR)Source2 < (ULONG_PTR)Module->DllBase ||
        (ULONG_PTR)Source2 > (ULONG_PTR)PtrAdd(Module->DllBase, Module->SizeOfImage)
       )
    {
        goto NORMAL_COMPARE;
    }

    // RiasGremory
    *(PULONG64)&TrueString[0] = TAG4W('Rias') ^ DEBUGGER_EXCEPTION_XOR_SEED;
    *(PULONG64)&TrueString[4] = TAG4W('Grem') ^ DEBUGGER_EXCEPTION_XOR_SEED;
    *(PULONG64)&TrueString[8] = TAG3W('ory')  ^ DEBUGGER_EXCEPTION_XOR_SEED;

    INLINE_ASM lea eax, TrueString;

    Source2 = TrueString;
    Length2 = MY_MAX(sizeof(L"RiasGremory") - 2, Length);

    *(PULONG64)&TrueString[8] ^= DEBUGGER_EXCEPTION_XOR_SEED;
    *(PULONG64)&TrueString[0] ^= DEBUGGER_EXCEPTION_XOR_SEED;
    *(PULONG64)&TrueString[4] ^= DEBUGGER_EXCEPTION_XOR_SEED;

    Result  = StubRtlCompareMemory(Source1, Source2, Length2);
    if (Result == Length2)
    {
        Result = -(SSIZE_T)Length;
        *(PULONG64)PtrAdd(Source1, 0) = TAG4W('Succ') ^ DEBUGGEE_EXCEPTION_XOR_SEED;
        *(PULONG64)PtrAdd(Source1, 8) = TAG3W('ess') ^ DEBUGGEE_EXCEPTION_XOR_SEED;
    }

    return Result;
}

class AntiDebug2 : public AntiDebugImpl<AntiDebug2>
{
protected:
    TYPE_OF(RtlCompareMemory)   *RtlCompareMemory;

public:
    NTSTATUS InitializeDebugger()
    {
        PVOID NtdllBase, RtlCompareMemory;
        PLDR_MODULE NtdllModule;

        NtdllModule = GetNtdllLdrModule();

        ReLoadDll(NtdllModule->FullDllName.Buffer, &NtdllBase, NtdllModule->DllBase, RELOAD_DLL_IGNORE_IAT);

        RtlCompareMemory = EATLookupRoutineByHashNoFix(NtdllBase, NTDLL_RtlCompareMemory);
        RtlCompareMemory = PtrAdd(*(PVOID *)RtlCompareMemory, NtdllBase);

        *(PVOID *)&this->RtlCompareMemory = RtlCompareMemory;

        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_JUMP(RtlCompareMemory, HookRtlCompareMemory, StubRtlCompareMemory),
        };

        return Nt_PatchMemory(NULL, 0, f, countof(f), NULL);
    }

    NTSTATUS VerifyString(PIO_CONTROL_PARAMETER IoControl)
    {
        ULONG Length;
        static WCHAR FakeString[] = L"Amano";

        if (
            IoControl->InputBuffer == NULL ||
            IoControl->InputBufferLength < CONST_STRLEN(FakeString) * sizeof(WCHAR) ||
            IoControl->OutputBuffer == NULL ||
            IoControl->OutputBufferLength < 16        // "Success"
           )
        {
            return STATUS_UNSUCCESSFUL;
        }

        Length = RtlCompareMemory(IoControl->InputBuffer, FakeString, IoControl->InputBufferLength);
        if (Length != -(SSIZE_T)(CONST_STRLEN(L"RiasGremory") * sizeof(WCHAR)))
            return STATUS_UNSUCCESSFUL;

        CopyMemory(IoControl->OutputBuffer, IoControl->InputBuffer, 16);
        *(PULONG64)PtrAdd(IoControl->OutputBuffer, 0) ^= DEBUGGEE_EXCEPTION_XOR_SEED;
        *(PULONG64)PtrAdd(IoControl->OutputBuffer, 8) ^= DEBUGGEE_EXCEPTION_XOR_SEED;
        IoControl->OutputBufferLength                  = 16;

        return STATUS_SUCCESS;
    }

    BEGIN_EXCEPTION_MAP
        HANDLE_EXCEPTION(ExceptionVerifyString, VerifyString)
    END_EXCEPTION_MAP
};

class Dialog : public CDialogImpl<Dialog>
{
protected:
    HWND        m_Edit;
    ULONG       m_ParentID;
    AntiDebug2  m_ad;

public:
    BOOL OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
    {
        UNREFERENCED_PARAMETER(hWnd);
        UNREFERENCED_PARAMETER(hWndFocus);
        UNREFERENCED_PARAMETER(lParam);

        NTSTATUS                Status;
        ATDBG_IO_REQUEST_PACKET Irp;

        if (!NT_SUCCESS(m_ad.Initialize()))
            return TRUE;

        m_ad.BuildIoControlRequest(&Irp, 0, 0, &m_ParentID, sizeof(m_ParentID));
        Status = m_ad.SendIoControlRequest(ExceptionQueryDebuggerPid, &Irp);

        if (!NT_SUCCESS(Status))
            return TRUE;

        m_Edit = GetDlgItem(IDC_EDIT);
        Edit_LimitText(m_Edit, 200);

        return TRUE;
    }

    VOID OnCommand(HWND hWnd, INT ID, HWND hWndCtl, UINT CodeNotify)
    {
        NTSTATUS                Status;
        ATDBG_IO_REQUEST_PACKET Irp;
        ULONG                   Length;
        WCHAR                   Buffer[0x200];

        UNREFERENCED_PARAMETER(hWnd);
        UNREFERENCED_PARAMETER(CodeNotify);
        UNREFERENCED_PARAMETER(hWndCtl);

        switch (ID)
        {
            case IDOK:
                Length = ::Edit_GetText(m_Edit, Buffer, countof(Buffer));
                if (Length == 0)
                    break;

                m_ad.BuildIoControlRequest(
                    &Irp,
                    Buffer,
                    Length * sizeof(WCHAR),
                    Buffer,
                    sizeof(Buffer)
                );

                Status = m_ad.SendIoControlRequest(ExceptionVerifyString, &Irp);
                if (NT_SUCCESS(Status))
                {
                    ExceptionBox(Buffer, NULL);
                }

                ::SetFocus(m_Edit);
                break;

            case IDCANCEL:
                EndDialog(0);
                return;
        }
    }

    VOID OnLButtonUp(HWND hWnd, Int x, Int y, UInt keyFlags)
    {
        SendMessage(WM_NCLBUTTONUP, HTCAPTION);
    }

    VOID OnLButtonDown(HWND hWnd, Bool fDoubleClick, Int x, Int y, UInt keyFlags)
    {
        SendMessage(WM_NCLBUTTONDOWN, HTCAPTION);
    }

    VOID OnPaint(HWND hWnd)
    {
        PAINTSTRUCT ps;
        HDC hDC = BeginPaint(&ps);

        HFONT           OldFont, Font;
        LOGFONTW        LogFont;

        SetBkMode(hDC, TRANSPARENT);

        Font = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
        GetObjectW(Font, sizeof(LogFont), &LogFont);

        static WCHAR face[] = L"Buxton Sketch";

        CopyStruct(&LogFont.lfFaceName, face, sizeof(face));
        Font = CreateFontIndirectW(&LogFont);

        // OldFont = (HFONT)SelectObject(hDC, Font);
        // DeleteObject(Font);

        static WCHAR txt[] = L"FUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCK";
        TextOutW(hDC, 0, 78, txt, CONST_STRLEN(txt));

        // SelectObject(hDC, OldFont);
        DeleteObject(Font);

        EndPaint(&ps);
    }

    BEGIN_MSG_MAP(Dialog)
        // MSG_HANDLER(WM_PAINT,       OnPaint)
        MSG_HANDLER(WM_COMMAND,     OnCommand)
        MSG_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
        MSG_HANDLER(WM_LBUTTONUP,   OnLButtonUp)
        MSG_HANDLER(WM_INITDIALOG,  OnInitDialog)
    END_MSG_MAP()

    FRIEND_OVERRIDE_DIALOG_METHOD(Dialog, CDialogImpl)
};

#pragma comment(lib, "comctl32.lib")

Int STDCALL wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWChar lpCmdLine, Int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    InitCommonControls();
    nCmdShow = Dialog().DoModal(IDD_DIALOG2, NULL);
    Nt_ExitProcess(nCmdShow);
}

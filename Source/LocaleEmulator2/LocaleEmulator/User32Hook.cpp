#include "stdafx.h"
#include "mlns.h"
#include "MessageTable.h"

/************************************************************************
  ansi to unicode
************************************************************************/

UserMessageCall(EMPTY)
{
    return CallUserMessageCallA();
}

UserMessageCall(INLPCREATESTRUCT)
{
    LRESULT         Result;
    LPCREATESTRUCTW CreateStructW;
    CREATESTRUCTA   CreateStructA;

    CreateStructW = (LPCREATESTRUCTW)lParam;

    CreateStructA.lpszClass = NULL;
    CreateStructA.lpszName = NULL;

    LOOP_ONCE
    {
        if (CreateStructW == NULL)
            break;

        CreateStructA = *(LPCREATESTRUCTA)CreateStructW;

        CreateStructA.lpszClass = NULL;
        CreateStructA.lpszName = NULL;

        CreateStructA.lpszClass = ClassWCharToMByte(CreateStructW->lpszClass);
        if (CreateStructA.lpszClass == NULL)
            break;

        if (CreateStructW->lpszName != NULL)
        {
            CreateStructA.lpszName = TitleWCharToMByte(CreateStructW->lpszName);
            if (CreateStructA.lpszName == NULL)
                break;
        }

        lParam = (LPARAM)&CreateStructA;
    }

    Result = CallUserMessageCallA();

    FreeClass((PVOID)CreateStructA.lpszClass);
    FreeString((PVOID)CreateStructA.lpszName);

    return Result;
}

UserMessageCall(INSTRINGNULL)
{
    PSTR    Ansi;
    LRESULT Result, Length;

    Ansi = NULL;

    LOOP_ONCE
    {
        if (lParam == NULL)
            break;

        Length = StrLengthW((PWSTR)lParam);
        if (Length == 0)
            break;

        Ansi = WCharToMByte((PWSTR)lParam, Length);
        if (Ansi == NULL)
            break;

        lParam = (LPARAM)Ansi;
    }

    Result = CallUserMessageCallA();

    FreeString(Ansi);

    return Result;
}

UserMessageCall(OUTSTRING)
{
    LRESULT OutputSize, Length;
    PWSTR   OutputBuffer;
    PSTR    Ansi;

    OutputSize = wParam;
    OutputBuffer = (PWSTR)lParam;

    Length = OutputSize * sizeof(WCHAR);
    Ansi = AllocAnsi(Length);
    if (Ansi == NULL)
        return 0;

    wParam = Length;
    lParam = (LPARAM)Ansi;

    Length = CallUserMessageCallA();

    if (Length != 0)
        AnsiToUnicode(OutputBuffer, OutputSize, Ansi, Length, (PULONG_PTR)&Length);

    FreeString(Ansi);

    return Length / sizeof(WCHAR);
}

UserMessageCall(INSTRING)
{
    return CallUserLocalCall(INSTRINGNULL);
}

UserMessageCall(INCNTOUTSTRING)
{
    LRESULT OutputSize, Length;
    PWSTR   OutputBuffer;
    PSTR    Ansi;

    PMSG_INPUT_COUNT_OUPUT_STRING ParamA, ParamW;

    ParamW = (PMSG_INPUT_COUNT_OUPUT_STRING)lParam;

    OutputSize = ParamW->BufferSize;
    OutputBuffer = ParamW->UnicodeBuffer;

    Length = OutputSize * sizeof(WCHAR);
    Ansi = AllocAnsi(Length);
    if (Ansi == NULL)
        return 0;

    ParamA = (PMSG_INPUT_COUNT_OUPUT_STRING)Ansi;
    ParamA->BufferSize = Length;
    lParam = (LPARAM)ParamA;

    Length = CallUserMessageCallA();

    if (Length != 0)
        AnsiToUnicode(OutputBuffer, OutputSize, Ansi, Length, (PULONG_PTR)&Length);

    FreeString(Ansi);

    return Length / sizeof(WCHAR);
}

UserMessageCall(INCBOXSTRING)
{
    return CallUserLocalCall(INSTRINGNULL);
}

UserMessageCall(OUTCBOXSTRING)
{
    LRESULT OutputSize, Length;
    PWSTR   OutputBuffer;
    PSTR    Ansi;

    OutputSize = CallWindowProcA(PrevProc, Window, Message + 1, wParam, 0);
    if (OutputSize == 0 || OutputSize == LB_ERR)
        return OutputSize;

    OutputBuffer = (PWSTR)lParam;
    ++OutputSize;
    Ansi = AllocAnsi(OutputSize);
    if (Ansi == NULL)
        return 0;

    Length = CallWindowProcA(PrevProc, Window, Message, wParam, (LPARAM)Ansi);

    if (Length != 0 && Length != LB_ERR)
        AnsiToUnicode(OutputBuffer, -1, Ansi, Length, (PULONG_PTR)&Length);

    FreeString(Ansi);

    return Length / sizeof(WCHAR);
}

UserMessageCall(INLBOXSTRING)
{
    return CallUserLocalCall(INSTRINGNULL);
}

UserMessageCall(OUTLBOXSTRING)
{
    return CallUserLocalCall(OUTCBOXSTRING);
}

UserMessageCall(INCNTOUTSTRINGNULL)
{
    return CallUserLocalCall(OUTSTRING);
}

UserMessageCall(GETDBCSTEXTLENGTHS)
{
    PSTR    Ansi;
    LRESULT Length;

    Length = CallUserMessageCallA();
    if (Length == 0 || Length == LB_ERR)
        return 0;

    ++Length;
    Ansi = AllocAnsi(Length);
    if (Ansi == NULL)
        return 0;

    wParam = Message == WM_GETTEXTLENGTH ? Length : wParam;
    lParam = (LPARAM)Ansi;
    --Message;
    Length = CallUserMessageCallA();

    if (Length != 0 && Length != LB_ERR)
    {
        ULONG UnicodeBytes;
        RtlMultiByteToUnicodeSize(&UnicodeBytes, Ansi, Length);
        Length = UnicodeBytes;
    }

    FreeString(Ansi);

    return Length / sizeof(WCHAR);
}

LRESULT NTAPI WindowProcW(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
{
    WNDPROC             PrevProc;
    FNUSERMESSAGECALL   MessageCall;
    PLeGlobalData       GlobalData = LeGetGlobalData();

    PrevProc = (WNDPROC)GlobalData->GetWindowDataA(Window);

    if (Message < countof(MessageTable))
    {
        MessageCall = gapfnMessageCall[MessageTable[Message].Function].UserCall;
        return MessageCall(PrevProc, Window, Message, wParam, lParam);
    }

    return CallUserMessageCallA();
}

/************************************************************************
  unicode to ansi
************************************************************************/

KernelMessageCall(EMPTY)
{
    return CallNtUserMessageCall();
}

KernelMessageCall(INLPCREATESTRUCT)
{
    LRESULT         Result;
    LPCREATESTRUCTA CreateStructA;
    CREATESTRUCTW   CreateStructW;

    CreateStructA = (LPCREATESTRUCTA)lParam;
    CreateStructW.lpszClass = NULL;
    CreateStructW.lpszName = NULL;

    LOOP_ONCE
    {
        if (CreateStructA == NULL)
            break;

        CreateStructW = *(LPCREATESTRUCTW)CreateStructA;

        CreateStructW.lpszClass = NULL;
        CreateStructW.lpszName = NULL;

        CreateStructW.lpszClass = ClassMByteToWChar(CreateStructA->lpszClass);
        if (CreateStructW.lpszClass == NULL)
            break;

        if (CreateStructA->lpszName != NULL)
        {
            CreateStructW.lpszName = TitleMByteToWChar(CreateStructA->lpszName);
            if (CreateStructW.lpszName == NULL)
                break;
        }

        lParam = (LPARAM)&CreateStructW;
        CLEAR_FLAG(Flags, WINDOW_FLAG_ANSI);
    }

    Result = CallNtUserMessageCall();

    FreeClass((PVOID)CreateStructW.lpszClass);
    FreeString((PVOID)CreateStructW.lpszName);

    return Result;
}

KernelMessageCall(INSTRINGNULL)
{
    PWSTR   Unicode;
    LRESULT Result, Length;

    Unicode = NULL;

    LOOP_ONCE
    {
        if (lParam == NULL)
            break;

        Length = StrLengthA((PSTR)lParam);
        if (Length == 0)
            break;

        Unicode = MByteToWChar((PSTR)lParam, Length);
        if (Unicode == NULL)
            break;

        lParam = (LPARAM)Unicode;
        CLEAR_FLAG(Flags, WINDOW_FLAG_ANSI);
    }

    Result = CallNtUserMessageCall();

    FreeString(Unicode);

    return Result;
}

KernelMessageCall(OUTSTRING)
{
    LRESULT Length, OutputSize;
    PWSTR   Unicode;
    PSTR    OutputBuffer;

    PLeGlobalData GlobalData = LeGetGlobalData();

    CLEAR_FLAG(Flags, WINDOW_FLAG_ANSI);

    OutputBuffer = (PSTR)lParam;
    OutputSize = wParam;

    Length = GlobalData->NtUserMessageCall(Window, Message + 1, wParam, lParam, xParam, xpfnProc, Flags);
    if (Length == 0)
        return 0;

    ++Length;
    Unicode = AllocUnicode(Length);
    if (Unicode == NULL)
        return 0;

    Length = GlobalData->NtUserMessageCall(Window, Message, Length, (LPARAM)Unicode, xParam, xpfnProc, Flags);

    UnicodeToAnsi(OutputBuffer, OutputSize, Unicode, Length, (PULONG_PTR)&Length);

    FreeString(Unicode);

    return Length;
}

KernelMessageCall(INSTRING)
{
    return CallNtUserLocalCall(INSTRINGNULL);
}

KernelMessageCall(INCNTOUTSTRING)
{
    LRESULT OutputSize, Length;
    PSTR    OutputBuffer;
    PWSTR   Unicode;

    PMSG_INPUT_COUNT_OUPUT_STRING ParamA, ParamW;

    ParamA = (PMSG_INPUT_COUNT_OUPUT_STRING)lParam;

    OutputSize = ParamA->BufferSize;
    OutputBuffer = ParamA->AnsiBuffer;

    Unicode = AllocUnicode(OutputSize);
    if (Unicode == NULL)
        return 0;

    ParamW = (PMSG_INPUT_COUNT_OUPUT_STRING)Unicode;
    ParamW->BufferSize = OutputSize;
    lParam = (LPARAM)ParamW;

    Length = CallNtUserMessageCallW();

    if (Length != 0)
        UnicodeToAnsi(OutputBuffer, OutputSize, Unicode, Length, (PULONG_PTR)&Length);

    FreeString(Unicode);

    return Length;
}

KernelMessageCall(INCBOXSTRING)
{
    return CallNtUserLocalCall(INSTRINGNULL);
}

KernelMessageCall(OUTCBOXSTRING)
{    
    LRESULT Length, OutputSize;
    PWSTR   Unicode;
    PSTR    OutputBuffer;

    PLeGlobalData GlobalData = LeGetGlobalData();

    CLEAR_FLAG(Flags, WINDOW_FLAG_ANSI);

    OutputBuffer = (PSTR)lParam;

    Length = GlobalData->NtUserMessageCall(Window, Message + 1, wParam, lParam, xParam, xpfnProc, Flags);
    if (Length == 0 || Length == LB_ERR)
        return 0;

    ++Length;
    Unicode = AllocUnicode(Length);
    if (Unicode == NULL)
        return 0;

    Length = GlobalData->NtUserMessageCall(Window, Message, wParam, (LPARAM)Unicode, xParam, xpfnProc, Flags);

    if (Length != 0 && Length != LB_ERR)
        UnicodeToAnsi(OutputBuffer, -1, Unicode, Length, (PULONG_PTR)&Length);

    FreeString(Unicode);

    return Length;
}

KernelMessageCall(INLBOXSTRING)
{
    return CallNtUserLocalCall(INSTRINGNULL);
}

KernelMessageCall(OUTLBOXSTRING)
{
    return CallNtUserLocalCall(OUTCBOXSTRING);
}

KernelMessageCall(INCNTOUTSTRINGNULL)
{
    return CallNtUserLocalCall(OUTSTRING);
}

KernelMessageCall(GETDBCSTEXTLENGTHS)
{
    LRESULT Length;
    PWSTR   Unicode;

    Length = CallNtUserMessageCallW();
    if (Length == 0 || Length == LB_ERR)
        return 0;

    ++Length;
    Unicode = AllocUnicode(Length);
    if (Unicode == NULL)
        return 0;

    wParam = Message == WM_GETTEXTLENGTH ? Length : wParam;
    lParam = (LPARAM)Unicode;
    --Message;
    Length = CallNtUserMessageCallW();

    if (Length != 0 && Length != LB_ERR)
    {
        ULONG AnsiBytes;
        RtlUnicodeToMultiByteSize(&AnsiBytes, Unicode, Length * sizeof(WCHAR));
        Length = AnsiBytes;
    }

    FreeString(Unicode);

    return Length;
}

LRESULT
NTAPI
LeNtUserMessageCall(
    HWND         Window,
    UINT         Message,
    WPARAM       wParam,
    LPARAM       lParam,
    ULONG_PTR    xParam,
    ULONG        xpfnProc,
    ULONG        Flags
)
{
    FNMESSAGECALL MessageCall;

    LOOP_ONCE
    {
        if (Message >= countof(MessageTable))
            continue;

        if (!FLAG_ON(Flags, WINDOW_FLAG_ANSI))
            break;

        MessageCall = gapfnMessageCall[MessageTable[Message].Function].KernelCall;
        return CALLNTMSGCALL(MessageCall);
    }

    return CallNtUserMessageCall();
}

BOOL
NTAPI
LeNtUserDefSetText(
    HWND                    hWnd,
    PLARGE_UNICODE_STRING   Text
)
{
    BOOL                    Success;
    LARGE_UNICODE_STRING    UnicodeText;
    PLeGlobalData           GlobalData = LeGetGlobalData();

    InitEmptyLargeString(&UnicodeText);

    LOOP_ONCE
    {
        if (Text == NULL)
            break;

        if (GlobalData->GetWindowDataA(hWnd) == NULL)
            break;

        if (LargeStringAnsiToUnicode(Text, &UnicodeText) == NULL)
            break;

        Text = &UnicodeText;
    }

    Success = GlobalData->NtUserSetDefText(hWnd, Text);

    FreeLargeString(&UnicodeText);

    return Success;
}

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    PCBT_PROC_PARAM CbtParam = (PCBT_PROC_PARAM)FindThreadFrame(CBT_PROC_PARAM_CONTEXT);

    if (nCode == HCBT_CREATEWND) LOOP_ONCE
    {
        HWND    hWnd;
        WNDPROC OriginalProcA, OriginalProcW;
        PLeGlobalData GlobalData;

        hWnd = (HWND)wParam;

        if (IsWindowUnicode(hWnd))
            break;

        GlobalData = CbtParam->GlobalData;

        if (GlobalData->GetWindowDataA(hWnd) != NULL)
            break;

        OriginalProcA = (WNDPROC)GlobalData->GetWindowLongA(hWnd, GWLP_WNDPROC);
        OriginalProcW = (WNDPROC)SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)WindowProcW);

        GlobalData->SetWindowDataA(hWnd, OriginalProcA);
        // GlobalData->SetWindowDataW(hWnd, OriginalProcW);
    }

    return CallNextHookEx(CbtParam->Hook, nCode, wParam, lParam);
}

HWND
NTAPI
LeNtUserCreateWindowEx_Win7(
    ULONG                   ExStyle,
    PLARGE_UNICODE_STRING   ClassName,
    PLARGE_UNICODE_STRING   ClassVersion,
    PLARGE_UNICODE_STRING   WindowName,
    ULONG                   Style,
    LONG                    X,
    LONG                    Y,
    LONG                    Width,
    LONG                    Height,
    HWND                    ParentWnd,
    HMENU                   Menu,
    PVOID                   Instance,
    LPVOID                  Param,
    ULONG                   ShowMode,
    ULONG                   Unknown
)
{
    HWND                    hWnd;
    NTSTATUS                LastError;
    LARGE_UNICODE_STRING    UnicodeWindowName;
    PLeGlobalData           GlobalData;
    CBT_PROC_PARAM          CbtParam;

    GlobalData = LeGetGlobalData();

    InitEmptyLargeString(&UnicodeWindowName);

    LOOP_ONCE
    {
        if (!FLAG_ON(ExStyle, WS_EX_ANSI))
            break;

        if (WindowName != NULL)
        {
            if (CaptureAnsiWindowName(WindowName, &UnicodeWindowName) == NULL)
                break;
        }

        WindowName = &UnicodeWindowName;

        CbtParam.Hook = SetWindowsHookExA(WH_CBT, CBTProc, NULL, CurrentTid());
        if (CbtParam.Hook != NULL)
        {
            CbtParam.GlobalData = GlobalData;
            CbtParam.Push();
        }
    }

    hWnd = GlobalData->NtUserCreateWindowEx_Win7(
            ExStyle,
            ClassName,
            ClassVersion,
            WindowName,
            Style,
            X,
            Y,
            Width,
            Height,
            ParentWnd,
            Menu,
            Instance,
            Param,
            ShowMode,
            Unknown
        );

    LastError = RtlGetLastWin32Error();

    if (CbtParam.Hook != NULL)
    {
        CbtParam.Pop();
        UnhookWindowsHookEx(CbtParam.Hook);
    }

    FreeLargeString(&UnicodeWindowName);

    RtlSetLastWin32Error(LastError);

    return hWnd;
}

HWND
NTAPI
LeNtUserCreateWindowEx_Win8(
    ULONG                   ExStyle,
    PLARGE_UNICODE_STRING   ClassName,
    PLARGE_UNICODE_STRING   ClassVersion,
    PLARGE_UNICODE_STRING   WindowName,
    ULONG                   Style,
    LONG                    X,
    LONG                    Y,
    LONG                    Width,
    LONG                    Height,
    HWND                    ParentWnd,
    HMENU                   Menu,
    PVOID                   Instance,
    LPVOID                  Param,
    ULONG                   ShowMode,
    ULONG                   Unknown,
    ULONG                   Unknown2
)
{
    HWND                    hWnd;
    NTSTATUS                LastError;
    LARGE_UNICODE_STRING    UnicodeWindowName;
    PLeGlobalData           GlobalData;
    CBT_PROC_PARAM          CbtParam;

    GlobalData = LeGetGlobalData();

    InitEmptyLargeString(&UnicodeWindowName);

    LOOP_ONCE
    {
        if (!FLAG_ON(ExStyle, WS_EX_ANSI))
            break;

        if (WindowName != NULL)
        {
            if (CaptureAnsiWindowName(WindowName, &UnicodeWindowName) == NULL)
                break;
        }

        WindowName = &UnicodeWindowName;

        CbtParam.Hook = SetWindowsHookExA(WH_CBT, CBTProc, NULL, CurrentTid());
        if (CbtParam.Hook != NULL)
        {
            CbtParam.GlobalData = GlobalData;
            CbtParam.Push();
        }
    }

    hWnd = GlobalData->NtUserCreateWindowEx_Win8(
            ExStyle,
            ClassName,
            ClassVersion,
            WindowName,
            Style,
            X,
            Y,
            Width,
            Height,
            ParentWnd,
            Menu,
            Instance,
            Param,
            ShowMode,
            Unknown,
            Unknown2
        );

    LastError = RtlGetLastWin32Error();

    if (CbtParam.Hook != NULL)
    {
        CbtParam.Pop();
        UnhookWindowsHookEx(CbtParam.Hook);
    }

    FreeLargeString(&UnicodeWindowName);

    RtlSetLastWin32Error(LastError);

    return hWnd;
}

LONG_PTR NTAPI LeGetWindowLongA(HWND hWnd, int Index)
{
    PVOID           Proc;
    PLeGlobalData   GlobalData = LeGetGlobalData();

    switch (Index)
    {
        case GWL_WNDPROC:
            Proc = GlobalData->GetWindowDataA(hWnd);
            if (Proc == NULL)
                break;

            return (LONG_PTR)Proc;
    }

    return GlobalData->GetWindowLongA(hWnd, Index);
}

LONG_PTR NTAPI LeSetWindowLongA(HWND hWnd, int Index, LONG_PTR NewLong)
{
    PVOID           Proc;
    PLeGlobalData   GlobalData = LeGetGlobalData();

    switch (Index)
    {
        case GWL_WNDPROC:
            Proc = GlobalData->GetWindowDataA(hWnd);
            if (Proc != NULL)
            {
                GlobalData->SetWindowDataA(hWnd, (PVOID)NewLong);
                return (LONG_PTR)Proc;
            }
            break;
    }

    return GlobalData->SetWindowLongA(hWnd, Index, NewLong);
}

BOOL NTAPI LeIsWindowUnicode(HWND hWnd)
{
    PLeGlobalData GlobalData = LeGetGlobalData();

    return GlobalData->GetWindowDataA(hWnd) == NULL ? GlobalData->IsWindowUnicode(hWnd) : FALSE;
}

HANDLE NTAPI LeSetClipboardData(UINT Format, HANDLE Memory)
{
    HGLOBAL             Data;
    PWSTR               Unicode;
    PSTR                Ansi;
    ULONG_PTR           Length;
    PLeGlobalData       GlobalData = LeGetGlobalData();

    Ansi = NULL;
    switch (Format)
    {
        case CF_TEXT:

            Ansi = (PSTR)GlobalLock(Memory);
            if (Ansi == NULL)
                break;

            Length = StrLengthA(Ansi);
            if (Length == 0)
                break;

            ++Length;
            Data = GlobalAlloc(GHND, Length * sizeof(WCHAR));
            if (Data == NULL)
                break;

            Unicode = (PWSTR)GlobalLock(Data);
            AnsiToUnicode(Unicode, Length, Ansi, Length - 1);
            GlobalUnlock(Data);

            if (GlobalData->SetClipboardData(CF_UNICODETEXT, Data) == NULL)
            {
                GlobalFree(Data);
            }

            break;
    }

    if (Ansi != NULL)
        GlobalUnlock(Memory);

    return GlobalData->SetClipboardData(Format, Memory);
}

HANDLE NTAPI LeGetClipboardData(UINT Format)
{
    HGLOBAL             Data, AnsiData;
    ULONG_PTR           Length, Flags;
    PWSTR               Unicode;
    PSTR                Ansi;
    PLeGlobalData       GlobalData = LeGetGlobalData();

    switch (Format)
    {
        case CF_TEXT:
            Data = GlobalData->GetClipboardData(CF_UNICODETEXT);
            if (Data == NULL)
                break;

            Flags = GlobalFlags(Data);
            if (FLAG_ON(Flags, GMEM_INVALID_HANDLE))
                break;

            Unicode = (PWSTR)GlobalLock(Data);
            if (Unicode == NULL)
                break;

            Length = StrLengthW(Unicode);
            AnsiData = GlobalAlloc(GHND, Length * 2);
            if (AnsiData == NULL)
            {
                GlobalUnlock(Data);
                break;
            }

            Ansi = (PSTR)GlobalLock(AnsiData);

            UnicodeToAnsi(Ansi, Length * 2, Unicode, Length);

            GlobalUnlock(AnsiData);
            GlobalUnlock(Data);

            Data = SetClipboardData(CF_TEXT, AnsiData);
            if (Data == NULL)
            {
                GlobalFree(AnsiData);
            }

            break;
    }

    return GlobalData->GetClipboardData(Format);
}

/************************************************************************
  init
************************************************************************/

PVOID FindNtUserMessageCall(PVOID User32)
{
    PVOID NtUserMessageCall = NULL;
    PVOID SendNotifyMessageW = EATLookupRoutineByHashPNoFix(User32, USER32_SendNotifyMessageW);

    NtUserMessageCall = WalkOpCodeT(SendNotifyMessageW, 0x40,
        WalkOpCodeM(Buffer, OpLength, Ret)
        {
            switch (Buffer[0])
            {
                case CALL:
                    Buffer = GetCallDestination(Buffer);
                    if (Buffer[0] != 0xB8)
                        break;

                    Ret = Buffer;
                    return STATUS_SUCCESS;

                case 0xC2:
                    return STATUS_TIMEOUT;
            }

            return STATUS_NOT_FOUND;
        }
    );

    return NtUserMessageCall;
}

PVOID FindNtUserMessageCall2(PVOID User32)
{
    ULONG Phase;
    PVOID NtUserMessageCall;
    PVOID GlobalRoutines[3];
    PVOID fnCOPYGLOBALDATA[3];

    GlobalRoutines[0] = IATLookupRoutineByHash(User32, KERNEL32_GlobalLock);
    GlobalRoutines[1] = IATLookupRoutineByHash(User32, KERNEL32_GlobalUnlock);
    GlobalRoutines[2] = IATLookupRoutineByHash(User32, KERNEL32_GlobalFree);

    NtUserMessageCall = NULL;

    Phase = 0;

    static const ULONG FinalPhase = countof(GlobalRoutines);

    WalkRelocTableT(User32,
        WalkRelocCallbackM(ImageBase, RelocationEntry, Offset, Context)
        {
            PVOID *VA = (PVOID *)PtrAdd(ImageBase, RelocationEntry->VirtualAddress + Offset->Offset);

            if (*VA != GlobalRoutines[Phase])
            {
                Phase = 0;
                return 0;
            }

            fnCOPYGLOBALDATA[Phase++] = VA;

            if (Phase != FinalPhase)
                return 0;

            PBYTE Begin, End;

            Begin = (PBYTE)fnCOPYGLOBALDATA[0] + sizeof(*VA);
            End   = (PBYTE)fnCOPYGLOBALDATA[1] + sizeof(*VA);

            WalkOpCodeT(Begin, End - Begin,
                WalkOpCodeM(Buffer, OpLength, Ret)
                {
                    switch (Buffer[0])
                    {
                        case CALL:
                            SEH_TRY
                            {
                                Buffer = GetCallDestination(Buffer);
                                if (Buffer[0] != 0xB8)
                                    break;
                            }
                            SEH_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
                            {
                                break;
                            }

                            NtUserMessageCall = Buffer;
                            return STATUS_SUCCESS;
                    }

                    return STATUS_NOT_FOUND;
                }
            );

            if (NtUserMessageCall == NULL)
            {
                Phase = 0;
                return STATUS_SUCCESS;
            }

            return STATUS_UNSUCCESSFUL;
        },
        0
    );

    return NtUserMessageCall;
}

PVOID FindNtUserCreateWindowEx(PVOID User32)
{
    PVOID NtUserCreateWindowEx, IATRtlQueryInformationActiveActivationContext;

    IATRtlQueryInformationActiveActivationContext = IATLookupRoutineByHash(User32, NTDLL_RtlQueryInformationActiveActivationContext);
    if (IATRtlQueryInformationActiveActivationContext == NULL)
        return NULL;

    NtUserCreateWindowEx = NULL;

    WalkRelocTableT(User32,
        WalkRelocCallbackM(ImageBase, RelocationEntry, Offset, Context)
        {
            PVOID *VA = (PVOID *)PtrAdd(ImageBase, RelocationEntry->VirtualAddress + Offset->Offset);

            if (*VA != IATRtlQueryInformationActiveActivationContext)
                return 0;

            VA = PtrAdd(VA, -2);
            if (*(PUSHORT)VA != 0x15FF) // call dword ptr [RtlQueryInformationActiveActivationContext]
                return 0;

            WalkOpCodeT(VA, 0x150,
                WalkOpCodeM(Buffer, OpLength, Ret)
                {
                    switch (Buffer[0])
                    {
                        case 0xE8:
                            Buffer = GetCallDestination(Buffer);
                            if (Buffer[0] != 0xB8)
                                break;

                            NtUserCreateWindowEx = Buffer;
                            return STATUS_SUCCESS;

                        case 0xC2:
                        case 0xC3:
                            return STATUS_NOTHING_TO_TERMINATE;
                    }

                    return STATUS_NOT_FOUND;
                }
            );

            return NtUserCreateWindowEx == NULL ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
        },
        0
    );

    return NtUserCreateWindowEx;
}

PVOID FindNtUserDefSetText(PVOID User32)
{
    PLDR_MODULE Module;

    PVOID Start, End;

    PVOID NotifyWinEvent;
    PVOID push_EVENT_OBJECT_NAMECHANGE;
    PVOID CallNotifyWinEvent;
    PVOID DefSetText;
    PVOID NtUserDefSetText;

    BYTE Stubpush_EVENT_OBJECT_NAMECHANGE[] =
    {
        0x68, 0x0C, 0x80, 0x00, 0x00,
    };

    SEARCH_PATTERN_DATA PushEVENT_OBJECT_NAMECHANGE[] =
    {
        ADD_PATTERN(Stubpush_EVENT_OBJECT_NAMECHANGE),
    };

    push_EVENT_OBJECT_NAMECHANGE    = NULL;
    CallNotifyWinEvent              = NULL;
    DefSetText                      = NULL;
    NtUserDefSetText                = NULL;

    *(PVOID *)&NotifyWinEvent = EATLookupRoutineByHashPNoFix(User32, USER32_NotifyWinEvent);

    Module = FindLdrModuleByHandle(User32);

    Start = PtrAdd(User32, IMAGE_FIRST_SECTION((PIMAGE_NT_HEADERS)PtrAdd(User32, ((PIMAGE_DOS_HEADER)User32)->e_lfanew))->VirtualAddress);
    End = PtrAdd(Start, Module->SizeOfImage - PtrOffset(Start, User32));

    while (Start < End)
    {
        push_EVENT_OBJECT_NAMECHANGE = SearchPattern(
                                            PushEVENT_OBJECT_NAMECHANGE,
                                            countof(PushEVENT_OBJECT_NAMECHANGE),
                                            Start,
                                            PtrOffset(End, Start)
                                        );

        if (push_EVENT_OBJECT_NAMECHANGE == NULL)
            return NULL;

        WalkOpCodeT(push_EVENT_OBJECT_NAMECHANGE, 0x10,
            WalkOpCodeM(Buffer, OpLength, Ret)
            {
                if (Buffer[0] != CALL)
                    return STATUS_NOT_FOUND;

                if (GetCallDestination(Buffer) != NotifyWinEvent)
                    return STATUS_NOT_FOUND;

                CallNotifyWinEvent = Buffer;

                return STATUS_SUCCESS;
            }
        );

        if (CallNotifyWinEvent != NULL)
            break;

        Start = PtrAdd(push_EVENT_OBJECT_NAMECHANGE, 1);
    }

    if (CallNotifyWinEvent == NULL)
        return NULL;

    Start = User32;

    for (ULONG_PTR Length = 0x10; Length; --Length)
    {
        PBYTE Buffer = (PBYTE)PtrSub(push_EVENT_OBJECT_NAMECHANGE, Length);
        if (Buffer[0] != CALL)
            continue;

        DefSetText = GetCallDestination(Buffer);
        if (!IN_RANGEEX(Start, DefSetText, End))
        {
            DefSetText = NULL;
            continue;
        }

        if (*(PULONG)DefSetText != 0x8B55FF8B)
        {
            DefSetText = NULL;
            continue;
        }

        break;
    }

    if (DefSetText == NULL)
        return NULL;

    WalkOpCodeT(DefSetText, 0x50,
        WalkOpCodeM(Buffer, OpLength, Ret)
        {
            switch (Buffer[0])
            {
                case CALL:
                    Buffer = GetCallDestination(Buffer);
                    if (Buffer[0] != 0xB8)
                        break;

                    NtUserDefSetText = Buffer;
                    return STATUS_SUCCESS;

                case 0xC9:  // leave
                case 0xC2:
                case 0xC3:
                    return STATUS_SUCCESS;
            }

            return STATUS_NOT_FOUND;
        }
    );

    return NtUserDefSetText;
}

LRESULT CALLBACK SendMessageWorkerProbe(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    PVOID *StackFrame, *PrevFrame;

    if (Message != WM_SETTEXT)
        return 0;

    AllocStack(1);

    StackFrame = (PVOID *)_AddressOfReturnAddress() - 1;
    PrevFrame = NULL;
    while (*StackFrame < (PVOID)lParam)
    {
        PrevFrame = StackFrame;
        StackFrame = (PVOID *)*StackFrame;
    }

    if (PrevFrame != NULL)
    {
        PBYTE Buffer = (PBYTE)PrevFrame[1] - 5;

        if (Buffer[0] == CALL)
            return (LRESULT)GetCallDestination(Buffer);
    }

    return NULL;
}

PVOID FindSendMessageWorker(PVOID User32)
{
    API_POINTER(CreateWindowExA)    CreateWindowExA;
    API_POINTER(SetWindowLongPtrA)  SetWindowLongPtrA;
    API_POINTER(SendMessageA)       SendMessageA;
    API_POINTER(DestroyWindow)      DestroyWindow;

    HWND        ProbeButton;
    LONG_PTR    WndProc;
    PVOID       SendMessageWorker;

    *(PVOID *)&CreateWindowExA      = EATLookupRoutineByHashPNoFix(User32, USER32_CreateWindowExA);
    *(PVOID *)&SetWindowLongPtrA    = EATLookupRoutineByHashPNoFix(User32, USER32_SetWindowLongA);
    *(PVOID *)&SendMessageA         = EATLookupRoutineByHashPNoFix(User32, USER32_SendMessageA);
    *(PVOID *)&DestroyWindow        = EATLookupRoutineByHashPNoFix(User32, USER32_DestroyWindow);

    ProbeButton         = CreateWindowExA(0, WC_BUTTONA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    WndProc             = SetWindowLongPtrA(ProbeButton, GWLP_WNDPROC, (LONG_PTR)SendMessageWorkerProbe);
    SendMessageWorker   = (PVOID)SendMessageA(ProbeButton, WM_SETTEXT, 0, (LPARAM)AllocStack(1));
    SetWindowLongPtrA(ProbeButton, GWLP_WNDPROC, WndProc);
    DestroyWindow(ProbeButton);

    return SendMessageWorker;
}

NTSTATUS LeGlobalData::HookUser32Routines(PVOID User32)
{
    PVOID       NtUserMessageCall;
    PVOID       NtUserCreateWindowEx;
    PVOID       NtUserDefSetText;
    PVOID       SendMessageWorker;
    PVOID       HookNtUserCreateWindowEx;
    NTSTATUS    Status;

    Status = ZwAddAtom(PROP_WINDOW_ANSI_PROC, CONST_STRLEN(PROP_WINDOW_ANSI_PROC) * sizeof(WCHAR), &this->AtomAnsiProc);
    FAIL_RETURN(Status);
/*
    Status = ZwAddAtom(PROP_WINDOW_UNICODE_PROC, CONST_STRLEN(PROP_WINDOW_UNICODE_PROC) * sizeof(WCHAR), &this->AtomUnicodeProc);
    FAIL_RETURN(Status);
*/
    NtUserMessageCall = FindNtUserMessageCall2(User32);
    if (NtUserMessageCall == NULL)
        return STATUS_NOT_FOUND;

    NtUserCreateWindowEx = FindNtUserCreateWindowEx(User32);
    if (NtUserCreateWindowEx == NULL)
        return STATUS_NOT_FOUND;

    NtUserDefSetText = FindNtUserDefSetText(User32);
    if (NtUserDefSetText == NULL)
        return STATUS_NOT_FOUND;

    HookNtUserCreateWindowEx = Ps::CurrentPeb()->OSBuildNumber > 7700 ? (PVOID)LeNtUserCreateWindowEx_Win8 : LeNtUserCreateWindowEx_Win7;

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_JUMP(NtUserCreateWindowEx,  HookNtUserCreateWindowEx,   HookStub.StubNtUserCreateWindowEx),
        INLINE_HOOK_JUMP(NtUserMessageCall,     LeNtUserMessageCall,        HookStub.StubNtUserMessageCall),
        INLINE_HOOK_JUMP(NtUserDefSetText,      LeNtUserDefSetText,         HookStub.StubNtUserDefSetText),

        EAT_HOOK_JUMP_HASH(User32, USER32_SetWindowLongA,   LeSetWindowLongA,   HookStub.StubSetWindowLongA),
        EAT_HOOK_JUMP_HASH(User32, USER32_GetWindowLongA,   LeGetWindowLongA,   HookStub.StubGetWindowLongA),
        EAT_HOOK_JUMP_HASH(User32, USER32_IsWindowUnicode,  LeIsWindowUnicode,  HookStub.StubIsWindowUnicode),
        EAT_HOOK_JUMP_HASH(User32, USER32_GetClipboardData, LeGetClipboardData, HookStub.StubGetClipboardData),
        EAT_HOOK_JUMP_HASH(User32, USER32_SetClipboardData, LeSetClipboardData, HookStub.StubSetClipboardData),
    };

    return Nt_PatchMemory(NULL, 0, f, countof(f), User32);
}

NTSTATUS LeGlobalData::UnHookUser32Routines()
{
    Nt_RestoreMemory(&HookStub.StubNtUserCreateWindowEx);
    Nt_RestoreMemory(&HookStub.StubNtUserMessageCall);
    Nt_RestoreMemory(&HookStub.StubNtUserDefSetText);

    Nt_RestoreMemory(&HookStub.StubSetWindowLongA);
    Nt_RestoreMemory(&HookStub.StubGetWindowLongA);
    Nt_RestoreMemory(&HookStub.StubIsWindowUnicode);

    Nt_RestoreMemory(&HookStub.StubGetClipboardData);
    Nt_RestoreMemory(&HookStub.StubSetClipboardData);

    if (AtomAnsiProc != NULL)
    {
        ZwDeleteAtom(AtomAnsiProc);
        AtomAnsiProc = NULL;
    }
/*
    if (AtomUnicodeProc != NULL)
    {
        ZwDeleteAtom(AtomUnicodeProc);
        AtomUnicodeProc = NULL;
    }
*/
    return 0;
}

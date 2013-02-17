#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "AntiInject.h"
#include "MyLibraryUser.cpp"

_MY_C_HEAD_

ULONG_PTR g_NtCreateThread, g_NtCreateThreadEx, g_RtlCreateUserThread, g_DbgUiRemoteBreakin;

_MY_C_TAIL_

PVOID FindCallRtlDispatchException_Pass1()
{
    ULONG Length;
    PBYTE KiUserExceptionDispatcher;

    KiUserExceptionDispatcher = (PBYTE)::KiUserExceptionDispatcher;
    for (LONG Size = 0x17; Size > 0; Size -= Length)
    {
        if (KiUserExceptionDispatcher[0] == 0xE8)
        {
            return KiUserExceptionDispatcher;
        }

        Length = GetOpCodeSize(KiUserExceptionDispatcher);
        KiUserExceptionDispatcher += Length;
    }

    return NULL;
}

NAKED PVOID FASTCALL FindCallRtlDispatchException_Pass2(PVOID)
{
    INLINE_ASM
    {
        __emit 0xCC;
        ret;
    }
}

LONG WINAPI FindCallRtlDispatchExceptionHandler(PEXCEPTION_POINTERS ExceptionPointers)
{
    PULONG_PTR  StackBase, Stack;
    ULONG_PTR   CallRtlDispatchExceptionAddress;

    if (ExceptionPointers->ContextRecord->Eip != (ULONG_PTR)FindCallRtlDispatchException_Pass2)
        return EXCEPTION_CONTINUE_SEARCH;

    ++ExceptionPointers->ContextRecord->Eip;
    ExceptionPointers->ContextRecord->Eax = IMAGE_INVALID_RVA;

    Stack = (PULONG_PTR)&ExceptionPointers;
    StackBase = (PULONG_PTR)Nt_CurrentTeb()->NtTib.StackBase;
    CallRtlDispatchExceptionAddress = ExceptionPointers->ContextRecord->Ecx + 5;

    while (Stack < StackBase)
    {
        if (*Stack == CallRtlDispatchExceptionAddress)
        {
            ExceptionPointers->ContextRecord->Eax = CallRtlDispatchExceptionAddress - 5;
            break;
        }

        ++Stack;
    }

    return EXCEPTION_CONTINUE_EXECUTION;
}

PVOID FindCallRtlDispatchException()
{
    PVOID veh, P1, P2;

    P1 = FindCallRtlDispatchException_Pass1();
    veh = RtlAddVectoredExceptionHandler(TRUE, FindCallRtlDispatchExceptionHandler);
    P2 = FindCallRtlDispatchException_Pass2(P1);
    RtlRemoveVectoredExceptionHandler(veh);

    return P1 == P2 ? P1 : NULL;
}

PVOID FindCallLdrpInitialize()
{
    ULONG Length;
    PBYTE Address;

    Address = (PBYTE)LdrInitializeThunk;
    for (LONG Size = 0x17; Size > 0; Size -= Length)
    {
        switch (Address[0])
        {
            case CALL:
            case JUMP:
                return *(PULONG_PTR)(Address + 1) + Address + 5;
        }

        Length = GetOpCodeSize(Address);
        Address += Length;
    }

    return (PVOID)IMAGE_INVALID_RVA;
}

NTSTATUS
(NTAPI
*OldNtCreateThread)(
    OUT PHANDLE             ThreadHandle,
    IN  ACCESS_MASK         DesiredAccess,
    IN  POBJECT_ATTRIBUTES  ObjectAttributes,
    IN  HANDLE              ProcessHandle,
    OUT PCLIENT_ID          ClientId,
    IN  PCONTEXT            ThreadContext,
    IN  PUSER_STACK         UserStack,
    IN  BOOLEAN             CreateSuspended
);

NTSTATUS
(NTAPI
*OldNtCreateThreadEx)(
    OUT PHANDLE             ThreadHandle,
    IN  ACCESS_MASK         DesiredAccess,
    IN  POBJECT_ATTRIBUTES  ObjectAttributes,
    IN  HANDLE              ProcessHandle,
    IN  PVOID               StartAddress,
    IN  PVOID               Parameter,
    IN  BOOL                CreateSuspended,
    IN  ULONG               StackZeroBits,
    IN  ULONG               SizeOfStackCommit,
    IN  ULONG               SizeOfStackReserve,
    OUT PVOID               BytesBuffer
);

VOID
(CDECL
*OldLdrpInitialize)(
    PCONTEXT    ThreadContext,
    PVOID       NtdllBase
);

NTSTATUS
(NTAPI
*OldNtContinue)(
    PCONTEXT Context,
    BOOLEAN  TestAlert
);

NTSTATUS
(NTAPI
*OldLdrLoadDll)(
    PWCHAR          PathToFile,
    PULONG          Flags,
    PUNICODE_STRING ModuleFileName,
    PVOID          *ModuleBase
);

BOOLEAN
(NTAPI
*OldRtlDispatchException)(
    PEXCEPTION_RECORD   ExceptionRecord,
    PCONTEXT            Context
);

ULONG STDCALL ThreadStart(THREAD_START_PARAMETER*)
{
    return 0;
}

THREAD_START_PARAMETER*
AllocateThreadParameter(
    PVOID StartAddress,
    PVOID Parameter
)
{
    THREAD_START_PARAMETER *StartParameter;

    StartParameter = (THREAD_START_PARAMETER *)MemoryAllocator::AllocateMemory(sizeof(*StartParameter));

    StartParameter->Context              = THREAD_START_PARAMETER_MAGIC;
    StartParameter->Parameter            = Parameter;
    StartParameter->ThreadStartRoutine   = StartAddress;

    return StartParameter;
}

BOOL
FreeThreadParameter(
    THREAD_START_PARAMETER *Parameter
)
{
    return MemoryAllocator::FreeMemory(Parameter);
}

NTSTATUS
NTAPI
HookNtCreateThreadEx(
    OUT PHANDLE             ThreadHandle,
    IN  ACCESS_MASK         DesiredAccess,
    IN  POBJECT_ATTRIBUTES  ObjectAttributes,
    IN  HANDLE              ProcessHandle,
    IN  PVOID               StartAddress,
    IN  PVOID               Parameter,
    IN  BOOL                CreateSuspended,
    IN  ULONG               StackZeroBits,
    IN  ULONG               SizeOfStackCommit,
    IN  ULONG               SizeOfStackReserve,
    OUT PVOID               BytesBuffer
)
{
    THREAD_START_PARAMETER *StartParameter;

    StartParameter = AllocateThreadParameter(StartAddress, Parameter);

    return OldNtCreateThreadEx(
                ThreadHandle,
                DesiredAccess,
                ObjectAttributes,
                ProcessHandle,
                ThreadStart,
                StartParameter,
                CreateSuspended,
                StackZeroBits,
                SizeOfStackCommit,
                SizeOfStackReserve,
                BytesBuffer
           );
}

NTSTATUS
NTAPI
HookNtCreateThread(
    OUT PHANDLE             ThreadHandle,
    IN  ACCESS_MASK         DesiredAccess,
    IN  POBJECT_ATTRIBUTES  ObjectAttributes,
    IN  HANDLE              ProcessHandle,
    OUT PCLIENT_ID          ClientId,
    IN  PCONTEXT            ThreadContext,
    IN  PUSER_STACK         UserStack,
    IN  BOOLEAN             CreateSuspended
)
{
    CONTEXT                 NewContext;
    THREAD_START_PARAMETER *StartParameter;

    NewContext = *ThreadContext;

    StartParameter = AllocateThreadParameter((PVOID)NewContext.Eax, (PVOID)NewContext.Ebx);
    NewContext.Eax = (ULONG_PTR)ThreadStart;
    NewContext.Ebx = (ULONG_PTR)StartParameter;

    return OldNtCreateThread(
                ThreadHandle,
                DesiredAccess,
                ObjectAttributes,
                ProcessHandle,
                ClientId,
                &NewContext,
                UserStack,
                CreateSuspended
           );
}

THREAD_START_PARAMETER SystemThreadParameter;

VOID
CDECL
LdrpInitialize(
    PCONTEXT    ThreadContext,
    PVOID       NtdllBase
)
{
    ULONG_PTR               ThreadStartAddress;
    PLDR_MODULE             NtdllModule;
    THREAD_START_PARAMETER *Parameter;

    NtdllModule = (PLDR_MODULE)FIELD_BASE(Nt_CurrentPeb()->Ldr->InInitializationOrderModuleList.Flink, LDR_MODULE, InInitializationOrderModuleList);

    ThreadStartAddress = ThreadContext->Eax;

    if (ThreadStartAddress == (ULONG_PTR)ThreadStart)
    {
        Parameter = (THREAD_START_PARAMETER *)ThreadContext->Ebx;
        RtlPushFrame(Parameter);

        ThreadContext->Eax = (ULONG_PTR)Parameter->ThreadStartRoutine;
        ThreadContext->Ebx = (ULONG_PTR)Parameter->Parameter;
    }
    else if (ThreadStartAddress >= (ULONG_PTR)NtdllModule->BaseAddress &&
             ThreadStartAddress <= (ULONG_PTR)NtdllModule->BaseAddress + NtdllModule->SizeOfImage &&
             ThreadStartAddress != g_NtCreateThread &&
             ThreadStartAddress != g_NtCreateThreadEx &&
             ThreadStartAddress != g_RtlCreateUserThread &&
             ThreadStartAddress != g_DbgUiRemoteBreakin)
    {
        RtlPushFrame(&SystemThreadParameter);
    }
    else
    {
        Parameter = (THREAD_START_PARAMETER *)Nt_FindThreadFrameByContext(THREAD_START_PARAMETER_MAGIC);
        if (Parameter == NULL || Parameter->ThreadStartRoutine != (PVOID)IMAGE_INVALID_RVA)
        {
            PrintConsoleW(L"remote thread: Routine = %08X, Context = %08X\n", ThreadStartAddress, ThreadContext->Ebx);
            RtlPushFrame(&SystemThreadParameter);
            ThreadContext->Eax = (ULONG_PTR)ThreadStart;
        }
    }

    INLINE_ASM mov ebx, esp;
    OldLdrpInitialize(ThreadContext, NtdllBase);
    INLINE_ASM mov esp, ebx;
}

NTSTATUS
NTAPI
HookNtContinue(
    PCONTEXT Context,
    BOOLEAN  TestAlert
)
{
    ULONG_PTR               StackBase, ReturnAddress;
    THREAD_START_PARAMETER *Parameter;

    if (!TestAlert)
        goto ROUTINE_RETURN;

    Parameter = (THREAD_START_PARAMETER *)Nt_FindThreadFrameByContext(THREAD_START_PARAMETER_MAGIC);
    if (Parameter == NULL)
        goto ROUTINE_RETURN;

    if (Parameter->ThreadStartRoutine == (PVOID)IMAGE_INVALID_RVA)
        goto ROUTINE_RETURN;

    ReturnAddress = (ULONG_PTR)_ReturnAddress();

//    if (PtrOffset(_ReturnAddress(), Parameter->Parameter) >= 0x28)
//        goto ROUTINE_RETURN;

    StackBase = (ULONG_PTR)Nt_CurrentTeb()->NtTib.StackBase;
    if (PtrOffset(StackBase, Context) > sizeof(*Context) * 3 / 2)
        goto ROUTINE_RETURN;

    if (PtrOffset(Context, _AddressOfReturnAddress()) > 0x30)
        goto ROUTINE_RETURN;

    SET_FLAG(Context->EFlags, 0x100);   // single step exception

    Parameter->ThreadStartRoutine   = (PVOID)IMAGE_INVALID_RVA;
    Parameter->Parameter            = (PVOID)Context->Eip;

ROUTINE_RETURN:

    return OldNtContinue(Context, TestAlert);
}

NTSTATUS
NTAPI
HookLdrLoadDll(
    PWCHAR          PathToFile,
    PULONG          Flags,
    PUNICODE_STRING ModuleFileName,
    PVOID          *ModuleBase
)
{
    THREAD_START_PARAMETER *Parameter;

    if (GetImageBaseAddress(_ReturnAddress()) == GetNtdllHandle())
        goto LOAD_DLL;

    Parameter = (THREAD_START_PARAMETER *)Nt_FindThreadFrameByContext(LOAD_DLL_FRAME_MAGIC);
    if (Parameter == NULL)
        return STATUS_UNSUCCESSFUL;

    if (Parameter->ThreadStartRoutine   != (PVOID)TAG4('Aman') ||
        Parameter->Parameter            != (PVOID)TAG4('otko'))
    {
        return STATUS_UNSUCCESSFUL;
    }

LOAD_DLL:
    return OldLdrLoadDll(PathToFile, Flags, ModuleFileName, ModuleBase);
}

NTSTATUS
NTAPI
HookLdrLoadDllPushFrame(
    PWCHAR          PathToFile,
    PULONG          Flags,
    PUNICODE_STRING ModuleFileName,
    PVOID          *ModuleBase
)
{
    NTSTATUS                Status;
    THREAD_START_PARAMETER  Parameter;

    Parameter.Context               = LOAD_DLL_FRAME_MAGIC;
    Parameter.ThreadStartRoutine    = (PVOID)TAG4('Aman');
    Parameter.Parameter             = (PVOID)TAG4('otko');

    RtlPushFrame(&Parameter);

    Status = HookLdrLoadDll(PathToFile, Flags, ModuleFileName, ModuleBase);

    RtlPopFrame(&Parameter);

    return Status;
}

LONG (WINAPI *OldMessageBoxW)(HWND hWnd, PCWSTR Text, PCWSTR Caption, ULONG Type);

LONG WINAPI HookMessageBoxW(HWND hWnd, PCWSTR Text, PCWSTR Caption, ULONG Type)
{
    UNREFERENCED_PARAMETER(Caption);
    return OldMessageBoxW(hWnd, Text, L"Hook", Type);
}

LONG STDCALL MainThreadStepExceptionHandler(PEXCEPTION_POINTERS ExceptionPointers)
{
    PLDR_MODULE             LdrModule;
    THREAD_START_PARAMETER *Parameter;

    Parameter = (THREAD_START_PARAMETER *)Nt_FindThreadFrameByContext(THREAD_START_PARAMETER_MAGIC);
    if (Parameter == NULL || Parameter->ThreadStartRoutine != (PVOID)IMAGE_INVALID_RVA)
        return EXCEPTION_CONTINUE_SEARCH;

    PrintConsoleW(
        L"OriginalStartAddress = %08X, Eip = %08X\n",
        Parameter->Parameter, ExceptionPointers->ContextRecord->Eip
    );

    LdrModule = Nt_FindLdrModuleByHandle(GetNtdllHandle());
    if (ExceptionPointers->ContextRecord->Eip > (ULONG_PTR)LdrModule->BaseAddress &&
        ExceptionPointers->ContextRecord->Eip < (ULONG_PTR)PtrAdd(LdrModule->BaseAddress, LdrModule->SizeOfImage))
    {
        goto NOT_INJECT;
    }

    LdrModule = Nt_FindLdrModuleByHandle(GetKernel32Handle());
    if (ExceptionPointers->ContextRecord->Eip > (ULONG_PTR)LdrModule->BaseAddress &&
        ExceptionPointers->ContextRecord->Eip < (ULONG_PTR)PtrAdd(LdrModule->BaseAddress, LdrModule->SizeOfImage))
    {
        goto NOT_INJECT;
    }

    return EXCEPTION_CONTINUE_EXECUTION;

    /************************************************************************
      eax = StartAddress
      ebx = ThreadContext
      if (eip != eax)
          injected
      else
          init hooks
    ************************************************************************/

NOT_INJECT:

    CLEAR_FLAG(ExceptionPointers->ContextRecord->EFlags, 0x100);

    PrintConsoleW(
        L"eax = %08X, ebx = %08X, eip = %08X\n",
        ExceptionPointers->ContextRecord->Eax, ExceptionPointers->ContextRecord->Ebx, ExceptionPointers->ContextRecord->Eip
    );

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK2(MessageBoxW, HookMessageBoxW, OldMessageBoxW),
    };

    Nt_PatchMemory(0, 0, f, 1, 0);

    Nt_RestoreMemory(&OldNtContinue);
    RtlPopFrame(Parameter);
    FreeThreadParameter(Parameter);

    return EXCEPTION_CONTINUE_EXECUTION;
}

BOOLEAN STDCALL RtlDispatchException(PEXCEPTION_RECORD ExceptionRecord, PCONTEXT Context)
{
    EXCEPTION_POINTERS ExceptionPointers;

    ExceptionPointers.ContextRecord = Context;
    ExceptionPointers.ExceptionRecord = ExceptionRecord;

    if (MainThreadStepExceptionHandler(&ExceptionPointers) == EXCEPTION_CONTINUE_EXECUTION)
        return TRUE;

    return OldRtlDispatchException(ExceptionRecord, Context);
}

BOOL Init(PVOID BaseAddress)
{
    PLDR_MODULE             LdrModule, FirstModule;
    THREAD_START_PARAMETER *Parameter;

    PVOID NtdllBase;
    PVOID NtdllEatLdrLoadDll, IatLdrLoadDll;
    PVOID ClientLoadLibrary;
    PVOID RtlDispatchExceptionAddress;
    PVOID NtCreateThreadAddress;
    PVOID NtCreateThreadExAddress;
    PVOID LdrInitializeThunkAddress;

    UNREFERENCED_PARAMETER(BaseAddress);

    if (MemoryAllocator::CreateGlobalHeap() == NULL)
        return FALSE;

    RtlDispatchExceptionAddress = FindCallRtlDispatchException();
    if (RtlDispatchExceptionAddress == NULL)
    {
        RtlDispatchExceptionAddress = (PVOID)IMAGE_INVALID_RVA;
        RtlAddVectoredExceptionHandler(TRUE, MainThreadStepExceptionHandler);
    }
    else
    {
        RtlDispatchExceptionAddress = GetCallDestination(RtlDispatchExceptionAddress);
    }

    NtdllBase           = GetNtdllHandle();
    NtdllEatLdrLoadDll  = EATLookupRoutineByEntryNoFix(NtdllBase, LdrLoadDll);

    LdrInitializeThunkAddress = FindCallLdrpInitialize();
    if (LdrInitializeThunkAddress != (PVOID)IMAGE_INVALID_RVA)
    {
        NtCreateThreadAddress = Nt_GetProcAddress(NtdllBase, "NtCreateThread");
        if (NtCreateThreadAddress == NULL)
        {
            NtCreateThreadAddress = (PVOID)IMAGE_INVALID_RVA;
        }
        else
        {
            g_NtCreateThread = (ULONG_PTR)NtCreateThreadAddress;
        }

        NtCreateThreadExAddress = Nt_GetProcAddress(NtdllBase, "NtCreateThreadEx");
        if (NtCreateThreadExAddress == NULL)
        {
            NtCreateThreadExAddress = (PVOID)IMAGE_INVALID_RVA;
        }
        else
        {
            g_NtCreateThreadEx = (ULONG_PTR)NtCreateThreadExAddress;
        }

        g_RtlCreateUserThread   = (ULONG_PTR)Nt_GetProcAddress(NtdllBase, "RtlCreateUserThread");
        g_DbgUiRemoteBreakin    = (ULONG_PTR)Nt_GetProcAddress(NtdllBase, "DbgUiRemoteBreakin");
    }
    else
    {
        NtCreateThreadAddress   = (PVOID)IMAGE_INVALID_RVA;
        NtCreateThreadExAddress = (PVOID)IMAGE_INVALID_RVA;
    }

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY(PtrSub(HookLdrLoadDllPushFrame, NtdllBase), sizeof(ULONG_PTR), NtdllEatLdrLoadDll),
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK2(RtlDispatchExceptionAddress,   RtlDispatchException,   OldRtlDispatchException),
        INLINE_HOOK2(NtContinue,                    HookNtContinue,         OldNtContinue),
        INLINE_HOOK2(LdrLoadDll,                    HookLdrLoadDll,        OldLdrLoadDll),

        INLINE_HOOK2(NtCreateThreadAddress,         HookNtCreateThread,     OldNtCreateThread),
        INLINE_HOOK2(NtCreateThreadExAddress,       HookNtCreateThreadEx,   OldNtCreateThreadEx),
        INLINE_HOOK2(LdrInitializeThunkAddress,     LdrpInitialize,         OldLdrpInitialize),

    };

    LdrModule   = FIELD_BASE(Nt_CurrentPeb()->Ldr->InLoadOrderModuleList.Flink, LDR_MODULE, InLoadOrderModuleList);
    FirstModule = LdrModule;
    do
    {
        IatLdrLoadDll = IATLookupRoutineByEntryNoFix(LdrModule->BaseAddress, LdrLoadDll);
        if (IatLdrLoadDll != NULL)
        {
            MEMORY_PATCH p[] =
            {
                PATCH_MEMORY(HookLdrLoadDllPushFrame, sizeof(ULONG_PTR), IatLdrLoadDll),
            };

            Nt_PatchMemory(p, countof(p), NULL, 0, NULL);
        }

        LdrModule = FIELD_BASE(LdrModule->InLoadOrderModuleList.Flink, LDR_MODULE, InLoadOrderModuleList);

    } while (LdrModule != FirstModule);

    Parameter = AllocateThreadParameter(NULL, LdrInitializeThunk);
    RtlPushFrame(Parameter);

    Nt_PatchMemory(p, countof(p), f, countof(f), NULL);

    AllocConsole();
    PrintConsoleW(L"Init\n");
//    MessageBoxW(NULL, L"attach", NULL, 64);

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, PVOID Reserved)
{
    THREAD_START_PARAMETER *Parameter;

    UNREFERENCED_PARAMETER(Reserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Init(hInstance);

        case DLL_THREAD_ATTACH:
            Parameter = (THREAD_START_PARAMETER *)Nt_FindThreadFrameByContext(THREAD_START_PARAMETER_MAGIC);
            if (Parameter == NULL)
                break;

            RtlPopFrame(Parameter);
            if (Parameter == &SystemThreadParameter)
                break;

            FreeThreadParameter(Parameter);
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

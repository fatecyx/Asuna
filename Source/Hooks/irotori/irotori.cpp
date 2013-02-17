#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(linker, "/EXPORT:Direct3DCreate9=d3d9.Direct3DCreate9")

#include "irotori.h"
#include "key.h"
#include "MyLibraryUser.cpp"
#include "cxdec.cpp"
#include "HookPort.cpp"

TYPE_OF(LdrInitializeThunk) *g_LdrInitializeThunk;

BOOL Initialize(PVOID BaseAddress);

OVERLOAD_CPP_NEW_WITH_HEAP(MemoryAllocator::GetGlobalHeap())

PIROTORI_INFO g_Info;

template<class PtrType> PtrType Nt_EncodePointer(PtrType Pointer, ULONG_PTR Cookie)
{
    return (PtrType)_rotr((ULONG_PTR)PtrXor(Pointer, Cookie), Cookie & 0x1F);
}

template<class PtrType> PtrType Nt_DecodePointer(PtrType Pointer, ULONG_PTR Cookie)
{
    return (PtrType)PtrXor(_rotl((ULONG_PTR)Pointer, Cookie & 0x1F), Cookie);
}

#if 0

HWND WINAPI HookCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    RECT    rcWordArea;
    ULONG   Length;
    LPWSTR  ClassName, WindowName;
    PIROTORI_INFO Info;

    Info = g_Info;

    Length = StrLengthA(lpClassName) + 1;
    ClassName = (LPWSTR)AllocStack(Length * sizeof(WCHAR));
    RtlCustomCPToUnicodeN(
        &Info->CpTable932,
        ClassName,
        Length * sizeof(WCHAR),
        NULL,
        lpClassName,
        Length
    );

    Length = StrLengthA(lpWindowName) + 1;
    WindowName = (LPWSTR)AllocStack(Length * sizeof(WCHAR));
    RtlCustomCPToUnicodeN(
        &Info->CpTable936,
        WindowName,
        Length * sizeof(WCHAR),
        NULL,
        lpWindowName,
        Length
    );
/*
    if (SystemParametersInfoW(SPI_GETWORKAREA, 0, &rcWordArea, 0))
    {
        X = ((rcWordArea.right - rcWordArea.left) - nWidth) / 2;
        Y = ((rcWordArea.bottom - rcWordArea.top) - nHeight) / 2;
    }
*/
    return CreateWindowExW(dwExStyle, ClassName, WindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

#endif

HFONT WINAPI HookCreateFontA(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic, DWORD bUnderline, __in DWORD bStrikeOut, __in DWORD iCharSet, __in DWORD iOutPrecision, __in DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, LPCSTR pszFaceName)
{
    LOGFONTW lf;
    PIROTORI_INFO Info = g_Info;

    lf.lfHeight         = cHeight;
    lf.lfWidth          = cWidth;
    lf.lfEscapement     = cEscapement;
    lf.lfOrientation    = cOrientation;
    lf.lfWeight         = cWeight;
    lf.lfItalic         = (BYTE)bItalic;
    lf.lfUnderline      = (BYTE)bUnderline;
    lf.lfStrikeOut      = (BYTE)bStrikeOut;
    lf.lfCharSet        = (BYTE)(Info->Initialized ? GB2312_CHARSET : iCharSet);
    lf.lfOutPrecision   = (BYTE)iOutPrecision;
    lf.lfClipPrecision  = (BYTE)iClipPrecision;
    lf.lfQuality        = CLEARTYPE_QUALITY;
    lf.lfPitchAndFamily = (BYTE)iPitchAndFamily;

    Nt_AnsiToUnicode(lf.lfFaceName, countof(lf.lfFaceName), pszFaceName);

    return CreateFontIndirectW(&lf);
}

int WINAPI HookEnumFontFamiliesExA(HDC hdc, LPLOGFONTA lpLogfont, FONTENUMPROCA lpProc, LPARAM lParam, DWORD dwFlags)
{
    lpLogfont->lfCharSet = g_Info->Initialized ? GB2312_CHARSET : lpLogfont->lfCharSet;
    return EnumFontFamiliesExA(hdc, lpLogfont, lpProc, lParam, dwFlags);
}

int WINAPI HooklstrcmpiA(LPCSTR lpString1, LPCSTR lpString2)
{
    return g_Info->CompareStringA(0x411, NORM_IGNORECASE, lpString1, -1, lpString2, -1) - 2;
}

#pragma push_macro("COMPARE_HASH")

#define COMPARE_HASH(_Index) \
            if (Text->Hash[_Index] < Hash[_Index]) \
            { \
                Left = Middle + 1; \
                continue; \
            } \
            else if (Text->Hash[_Index] > Hash[_Index]) \
            { \
                Right = Middle - 1; \
                continue; \
            }

PTEXT_NODE FindTextByHash(PIROTORI_INFO Info, PULONG Hash)
{
    ULONG Left, Right, Middle;
    PTEXT_NODE Text, *TextBase;

    Left        = 0;
    Right       = Info->TextCount - 1;
    TextBase    = Info->Text;

    if (Hash[0] < Nt_DecodePointer(TextBase[Left], *(PULONG)g_LdrInitializeThunk)->Hash[0] ||
        Hash[0] > Nt_DecodePointer(TextBase[Right], *(PULONG)Info->LdrInitializeThunk)->Hash[0])
    {
        return NULL;
    }

    while (Left < Right)
    {
        Middle = (Right - Left) / 2 + Left;
        Text = Nt_DecodePointer(TextBase[Middle], *(PULONG)g_LdrInitializeThunk);

        COMPARE_HASH(0);
        COMPARE_HASH(1);
        COMPARE_HASH(2);
        COMPARE_HASH(3);

        return Text;
    }

    Text = Info->Text[Left];
    Text = (PTEXT_NODE)Nt_DecodePointer(Text, *(PULONG)Info->LdrInitializeThunk);

    return (Text->Hash[0] == Hash[0] &&
            Text->Hash[1] == Hash[1] &&
            Text->Hash[2] == Hash[2] &&
            Text->Hash[3] == Hash[3]
           ) ? Text : NULL;
}

#pragma pop_macro("COMPARE_HASH")

PTEB_ACTIVE_FRAME Nt_FindThreadFrameByContext2(ULONG_PTR Context)
{
    PTEB_ACTIVE_FRAME Frame;

    Frame = g_Info->RtlGetFrame();
    while (Frame != NULL && Frame->Context != Context)
        Frame = Frame->Previous;

    return Frame;
}

VOID
NTAPI
DecryptAPCTimer(
    PVOID   TimerContext,
    ULONG   TimerLowValue,
    LONG    TimerHighValue
)
{
    NTSTATUS            Status;
    PVOID               BaseAddress, TextBase;
    ULONG               Size, TextSize, Protect1, Protect2;
    CONTEXT             Context, NewContext;
    PIROTORI_INFO       Info;
    PTHREAD_TEXT_BUFFER TextBuffer;

    TextBuffer  = (PTHREAD_TEXT_BUFFER)Nt_FindThreadFrameByContext2(THREAD_TEXT_BUFFER_MAGIC);
    if (TextBuffer == NULL)
        return;

    TextSize = TextBuffer->TextLength;
    if (TextSize == 0)
        return;

    Info = (PIROTORI_INFO)TimerContext;

    BaseAddress = Info;
    TextBase    = TextBuffer->Buffer;
    Size        = sizeof(*Info);

#if 1

    Status = Info->NtProtectVirtualMemory(
                NtCurrentProcess(),
                &BaseAddress,
                &Size,
                PAGE_READWRITE,
                &Protect1
             );
    if (!NT_SUCCESS(Status))
        return;

    Status = Info->NtProtectVirtualMemory(
                NtCurrentProcess(),
                &TextBase,
                &TextSize,
                PAGE_READWRITE,
                &Protect2
             );
    if (!NT_SUCCESS(Status))
        return;

    Context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    Status = Info->NtGetContextThread(NtCurrentThread(), &Context);
    if (!NT_SUCCESS(Status))
        return;

    NewContext = Context;

    NewContext.Dr0 = 0;
    NewContext.Dr1 = 0;
    NewContext.Dr2 = 0;
    NewContext.Dr3 = 0;
    NewContext.Dr6 = 0;
    NewContext.Dr7 = 0;

    Status = Info->NtSetContextThread(NtCurrentThread(), &NewContext);
    if (!NT_SUCCESS(Status))
        return;

    Info->cxdec.Decrypt2(
        0,
        TextBuffer->Buffer,
        TextBuffer->TextLength,
        &TextBuffer->Hash[4]
    );

    TextBuffer->TextLength = 0;

    Info->NtSetContextThread(NtCurrentThread(), &Context);

    Info->NtProtectVirtualMemory(
        NtCurrentProcess(),
        &TextBase,
        &TextSize,
        Protect2,
        &Protect2
    );

    Info->NtProtectVirtualMemory(
        NtCurrentProcess(),
        &BaseAddress,
        &Size,
        Protect1,
        &Protect1
    );

#else
  
    Info->cxdec.Decrypt2(
    0,
    TextBuffer->Buffer,
    TextBuffer->TextLength,
    &TextBuffer->Hash[4]
    );
    
    TextBuffer->TextLength = 0;

#endif
}

NTSTATUS
HOOKPORT_CALLTYPE
HookNtDeviceIoControlFile(
    PSYSCALL_INFO       SysCallInfo,
    PSYSTEM_CALL_ACTION Action,
    HANDLE              FileHandle,
    HANDLE              Event,
    PIO_APC_ROUTINE     ApcRoutine,
    PVOID               ApcContext,
    PIO_STATUS_BLOCK    IoStatusBlock,
    ULONG               IoControlCode,
    PVOID               InputBuffer,
    ULONG               InputBufferLength,
    PVOID               OutputBuffer,
    ULONG               OutputBufferLength
)
{
    if (_rotr(IoControlCode, 11) != _rotr(IOCTL_DECRYPT_TEXT, 11))
        return STATUS_SUCCESS;

    NTSTATUS            Status;
    CONTEXT             Context, NewContext;
    PTHREAD_TEXT_BUFFER TextBuffer;
    PIROTORI_INFO       Info;

    Action->Action = BlockSystemCall;

    TextBuffer = (PTHREAD_TEXT_BUFFER)Nt_FindThreadFrameByContext2(THREAD_TEXT_BUFFER_MAGIC);
    if (TextBuffer == NULL)
        return STATUS_SUCCESS;

#if 1

    Info = (PIROTORI_INFO)Action->FilterContext;

    Context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    Status = Info->NtGetContextThread(NtCurrentThread(), &Context);
    if (!NT_SUCCESS(Status))
        return Status;

    NewContext = Context;

    NewContext.Dr0 = 0;
    NewContext.Dr1 = 0;
    NewContext.Dr2 = 0;
    NewContext.Dr3 = 0;
    NewContext.Dr6 = 0;
    NewContext.Dr7 = 0;

    Status = Info->NtSetContextThread(NtCurrentThread(), &NewContext);
    if (!NT_SUCCESS(Status))
        return Status;

    ApcContext          = TextBuffer;
    OutputBufferLength  = sizeof(*TextBuffer);

    Status = Info->NtProtectVirtualMemory(
                NtCurrentProcess(),
                &ApcContext,
                &OutputBufferLength,
                PAGE_READWRITE,
                &OutputBufferLength
             );
    if (!NT_SUCCESS(Status))
        return Status;

    TextBuffer->Hash        = (PULONG)OutputBuffer;
    TextBuffer->TextLength  = InputBufferLength;

    while (TextBuffer->TextLength != 0) Info->NtTestAlert();

    Info->NtProtectVirtualMemory(
        NtCurrentProcess(),
        &ApcContext,
        &OutputBufferLength,
        OutputBufferLength,
        &OutputBufferLength
    );

    Info->NtSetContextThread(NtCurrentThread(), &Context);

#else
    DecryptAPCTimer(Action->FilterContext, 0, 0);

#endif
    return STATUS_SUCCESS;
}

TYPE_OF(&IrotoriScriptObject::HookCatString) StubCatString;
TYPE_OF(&IrotoriScriptObject::HookCatString) StubCatQuote;
TYPE_OF(&IrotoriScriptObject::HookCatString) StubCopyPrefix;
TYPE_OF(&IrotoriScriptObject::HookCatString) StubCopyDescription;

PSTR GetTextBuffer(PIROTORI_SCRIPT_OBJECT Object, PSTR String)
{
    ULONG                   Length, Hash[8], Index[4];
    ULONG_PTR               Offset;
    PSTR                    Buffer;
    PTEXT_NODE              Text;
    PIROTORI_INFO           Info;
    PTHREAD_TEXT_BUFFER     TextBuffer;

    if (String[-2] != 0xE)
        return String;

    if (String[(BYTE)String[-1] - 1] != 0)
        return String;

    Info = g_Info;
    if (!Info->Initialized)
        return String;

    Offset = PtrOffset(String, Object->ScriptBuffer) - 1;

    sha256(&Offset, sizeof(Offset), Hash);

    Index[0] = Hash[0] ^ Hash[4];
    Index[1] = Hash[1] ^ Hash[5];
    Index[2] = Hash[2] ^ Hash[6];
    Index[3] = Hash[3] ^ Hash[7];

    Text = FindTextByHash(Info, Index);
    if (Text == NULL)
        return String;

    Length = Text->Length ^ Text->Hash[0] ^ Text->Hash[1] ^ Text->Hash[2] ^ Text->Hash[3];

    TextBuffer = (PTHREAD_TEXT_BUFFER)Nt_FindThreadFrameByContext2(THREAD_TEXT_BUFFER_MAGIC);
    if (TextBuffer == NULL)
    {
        TextBuffer = new THREAD_TEXT_BUFFER;
        if (TextBuffer == NULL)
            return String;

        Info->RtlPushFrame(TextBuffer);

        TextBuffer->Buffer = NULL;
        TextBuffer->Length = 0;
    }

    if (TextBuffer->Length <= Length)
    {
        TextBuffer->Length = Length + 1;
        TextBuffer->Buffer = (PCHAR)MemoryAllocator::ReAllocateMemory(TextBuffer->Buffer, Length + 1);
        if (TextBuffer->Buffer == NULL)
            return String;
    }

    Buffer = TextBuffer->Buffer;
    CopyMemory(Buffer, Text->Text, Length);
    Info->Device.DeviceIoControl(IOCTL_DECRYPT_TEXT, &Offset, Length, &Hash, Length);
//    Info->cxdec.Decrypt2(0, Buffer, Length, &Hash[4]);

    Buffer[Length] = 0;

    String = Buffer;

    return Buffer;
}

NAKED VOID THISCALL IrotoriScriptObject::HookCopyDescription(PSTR String)
{
    INLINE_ASM
    {
        push    edi;
        mov     edi, ecx;

        lea     ecx, dword ptr [ebx+0x643F18]
        mov     edx, [esp + 8];
        call    GetTextBuffer;
        mov     ecx, edi;
        pop     edi;
        mov     [esp + 4], eax;
        jmp     dword ptr [StubCopyDescription];
    }
}

NAKED VOID THISCALL IrotoriScriptObject::HookCopyPrefix(PSTR String)
{
    INLINE_ASM
    {
        push    edi;
        mov     edi, ecx;

        mov     ecx, esi;
        mov     edx, [esp + 8];
        call    GetTextBuffer;
        mov     ecx, edi;
        pop     edi;
        mov     [esp + 4], eax;
        jmp     dword ptr [StubCopyPrefix];
    }
}

NAKED VOID IrotoriScriptObject::HookCatString(PSTR String)
{
    INLINE_ASM
    {
        push    edi;
        mov     edi, ecx;

        mov     ecx, esi;
        mov     edx, [esp + 8];
        call    GetTextBuffer;
        mov     ecx, edi;
        pop     edi;
        mov     [esp + 4], eax;
        jmp     dword ptr [StubCatString];
    }
}

NAKED VOID IrotoriScriptObject::HookCatQuote(PSTR String)
{
    INLINE_ASM
    {
        push    edi;
        mov     edi, ecx;

        mov     ecx, esi;
        mov     edx, [esp + 8];
        call    GetTextBuffer;
        mov     ecx, edi;
        pop     edi;
        mov     [esp + 4], eax;
        jmp     dword ptr [StubCatString];
    }
}

NTSTATUS
InitCodePageTable(
    PCPTABLEINFO  CodePageTable,
    PVOID        *CPBuffer,
    PWSTR         CodePage,
    PWSTR         NlsDirectory,
    ULONG         PathLength
)
{
    ULONG       Length;
    NTSTATUS    Status;
    NtFileDisk  NlsFile;
    PKEY_VALUE_PARTIAL_INFORMATION Partial;

    Length  = MAX_NTPATH * sizeof(WCHAR) + sizeof(*Partial);
    Partial = (PKEY_VALUE_PARTIAL_INFORMATION)AllocStack(Length);
    Status  = Nt_RegGetValue(
                HKEY_LOCAL_MACHINE,
                CODE_PAGE_NLS_KEY,
                CodePage,
                KeyValuePartialInformation,
                Partial,
                Length
              );
    if (!NT_SUCCESS(Status))
        return Status;

    CopyMemory(NlsDirectory + PathLength, Partial->Data, Partial->DataLength);
    NlsDirectory[PathLength + Partial->DataLength / sizeof(WCHAR)] = 0;

    Status = NlsFile.Open(NlsDirectory);
    if (!NT_SUCCESS(Status))
        return Status;

    Status = Nt_AllocateMemory(NtCurrentProcess(), CPBuffer, NlsFile.GetSize32());
    if (!NT_SUCCESS(Status))
        return Status;

    Status = NlsFile.Read(*CPBuffer);
    if (!NT_SUCCESS(Status))
        return Status;

    RtlInitCodePageTable((PUSHORT)*CPBuffer, CodePageTable);

    return Status;
}

NTSTATUS LoadText(PIROTORI_INFO Info)
{
    WCHAR       TextPath[MAX_NTPATH];
    ULONG       Length, Count, MaxCount;
    PBYTE       Buffer, End;
    NTSTATUS    Status;
    NtFileDisk  File;
    PTEXT_NODE  *Text, *TextBase;

    Length = Nt_GetExeDirectory(TextPath, countof(TextPath));
    CopyStruct(TextPath + Length, L"world.bin", sizeof(L"world.bin"));

    Status = File.Open(TextPath);
    if (!NT_SUCCESS(Status))
        return Status;

    Length = File.GetSize32();
    Buffer = new BYTE[Length];
    if (Buffer == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    Info->TextBuffer = Buffer;
    TextBase = NULL;

    SCOPE_EXIT
    {
        if (NT_SUCCESS(Status))
            return;

        delete[] Buffer;

        MemoryAllocator::FreeMemory(TextBase);

        Info->TextBuffer = NULL;
    }
    SCOPE_EXIT_END;

    Status = File.Read(Buffer, Length);
    if (!NT_SUCCESS(Status))
        return Status;

    MaxCount = 0x2000;
    TextBase = (PTEXT_NODE*)MemoryAllocator::AllocateMemory(MaxCount * sizeof(*TextBase));
    if (TextBase == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    Text    = TextBase;
    End     = Buffer + Length;

    for (Count = MaxCount; Buffer < End; )
    {
        PTEXT_NODE Node;

        if (--Count == 0)
        {
            Count = MaxCount;
            MaxCount *= 2;
            TextBase = (PTEXT_NODE *)MemoryAllocator::ReAllocateMemory(TextBase, MaxCount * sizeof(*TextBase));
            if (TextBase == NULL)
                return STATUS_INSUFFICIENT_RESOURCES;

            Text = TextBase + Count - 1;
        }

        Node    = (PTEXT_NODE)Buffer;
        *Text++ = Nt_EncodePointer(Node, *(PULONG)Info->LdrInitializeThunk);
        Length  = Node->Length ^ Node->Hash[0] ^ Node->Hash[1] ^ Node->Hash[2] ^ Node->Hash[3];
        Length  = ROUND_UP(Length, 4);
        Buffer += Length + FIELD_SIZE(TEXT_NODE, Hash) + FIELD_SIZE(TEXT_NODE, Length);
    }

    Count = Text - TextBase;
    if (Count != MaxCount)
    {
        TextBase = (PTEXT_NODE *)MemoryAllocator::ReAllocateMemory(TextBase, Count * sizeof(*TextBase));
        if (TextBase == NULL)
            return STATUS_INSUFFICIENT_RESOURCES;
    }

    Info->Text      = TextBase;
    Info->TextCount = Count;

    return STATUS_SUCCESS;
}

ULONG STDCALL StubThreadStart(THREAD_START_PARAMETER*)
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
HOOKPORT_CALLTYPE
HookNtCreateThreadEx(
    PSYSCALL_INFO       SysCallInfo,
    PSYSTEM_CALL_ACTION Action,
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
    THREAD_START_PARAMETER *StartParameter;

    StartParameter = AllocateThreadParameter(StartAddress, Parameter);

    Action->Action = BlockSystemCall;

    return CallSysCall(
                NtCreateThreadEx,
                SysCallInfo,
                ThreadHandle,
                DesiredAccess,
                ObjectAttributes,
                ProcessHandle,
                (PVOID)DEFAULT_THREAD_START_ADDRESS,
                StartParameter,
                CreateSuspended,
                StackZeroBits,
                SizeOfStackCommit,
                SizeOfStackReserve,
                BytesBuffer
           );
}

NTSTATUS
HOOKPORT_CALLTYPE
HookNtCreateThread(
    PSYSCALL_INFO       SysCallInfo,
    PSYSTEM_CALL_ACTION Action,
    PHANDLE             ThreadHandle,
    ACCESS_MASK         DesiredAccess,
    POBJECT_ATTRIBUTES  ObjectAttributes,
    HANDLE              ProcessHandle,
    PCLIENT_ID          ClientId,
    PCONTEXT            ThreadContext,
    PUSER_STACK         UserStack,
    BOOLEAN             CreateSuspended
)
{
    CONTEXT                 NewContext;
    THREAD_START_PARAMETER *StartParameter;

    NewContext = *ThreadContext;

    StartParameter = AllocateThreadParameter((PVOID)NewContext.Eax, (PVOID)NewContext.Ebx);
    NewContext.Eax = DEFAULT_THREAD_START_ADDRESS;
    NewContext.Ebx = (ULONG_PTR)StartParameter;

    Action->Action = BlockSystemCall;

    return CallSysCall(
                NtCreateThread,
                SysCallInfo,
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

VOID NTAPI HookLdrInitializeThunk(PCONTEXT ThreadContext, PVOID NtdllBase)
{
    PIROTORI_INFO           Info;
    ULONG_PTR               ThreadStartAddress;
    PLDR_MODULE             NtdllModule;
    PTHREAD_START_PARAMETER Parameter;

    Info = g_Info;

    NtdllModule = GetNtdllLdrModule();

    ThreadStartAddress = ThreadContext->Eax;

    Info->RtlPushFrame(&SystemThreadParameter);

    if (ThreadStartAddress + 1 == 0)
    {
        ThreadContext->Eax = NULL;
    }
    else if (
             ThreadStartAddress >= (ULONG_PTR)NtdllModule->DllBase &&
             ThreadStartAddress <= PtrAdd(NtdllModule->SizeOfImage, NtdllModule->DllBase) &&
             ThreadStartAddress != (ULONG_PTR)Info->NtCreateThread &&
             ThreadStartAddress != (ULONG_PTR)Info->NtCreateThreadEx &&
             ThreadStartAddress != (ULONG_PTR)Info->RtlCreateUserThread &&
             ThreadStartAddress != (ULONG_PTR)Info->DbgUiRemoteBreakin
            )
    {
    }
    else
    {
        ThreadContext->Eax = (ULONG_PTR)StubThreadStart;
    }

    if (NtdllBase != NULL)
        return Info->StubLdrInitializeThunk(ThreadContext, NtdllBase);
}

NAKED VOID HookLdrInitializeThunkNT5(PCONTEXT ThreadContext, PVOID NtdllBase, ULONG_PTR, CONTEXT)
{
    INLINE_ASM
    {
        lea     eax, [esp + 08h];

FIND_CONTEXT_PTR:
            lea     eax, [eax + 04h];
            mov     ebx, [eax];
            and     ebx, CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_i386;
            xor     ebx, CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_i386;
        jnz     FIND_CONTEXT_PTR;

        push    0;
        push    eax;
        call    HookLdrInitializeThunk;
        mov     eax, g_Info;
        jmp     [eax]PIROTORI_INFO.StubLdrInitializeThunk;
    }
}

NTSTATUS
HOOKPORT_CALLTYPE
HookNtContinue(
    PSYSCALL_INFO       SysCallInfo,
    PSYSTEM_CALL_ACTION Action,
    PCONTEXT            Context,
    BOOLEAN             TestAlert
)
{
    NTSTATUS                    Status;
    PTHREAD_TEXT_BUFFER         Probe;
    PIROTORI_INFO               Info;
    PTHREAD_START_PARAMETER     Parameter;
    TYPE_OF(RtlExitUserThread)* RtlExitUserThread;

    if (!TestAlert)
        return STATUS_SUCCESS;

    Info = g_Info;

    Probe = (PTHREAD_TEXT_BUFFER)Nt_FindThreadFrameByContext2(THREAD_TEXT_BUFFER_MAGIC);
    if (Probe != NULL)
    {
        if (Probe != Action->FilterContext)
            return STATUS_SUCCESS;

        if (Context->Eax != (ULONG_PTR)Probe->Buffer)
            return STATUS_SUCCESS;

        if (Context->Ebx != (ULONG_PTR)Nt_CurrentPeb())
            return STATUS_SUCCESS;

        Info->RtlPopFrame(Probe);
        MemoryAllocator::FreeMemory(Probe);

        if (*(PBYTE)Context->Eax * 2 == 0xCC * 2)
        {
            Context->Eax = (ULONG_PTR)EATLookupRoutineByHashPNoFix(Probe->Object, NTDLL_RtlExitUserThread);
        }
        else
        {
            Initialize(NULL);
        }

        return STATUS_SUCCESS;
    }

    Parameter = (PTHREAD_START_PARAMETER)Nt_FindThreadFrameByContext2(THREAD_START_PARAMETER_MAGIC);
    if (Parameter == NULL)
        return STATUS_SUCCESS;

    Info->RtlPopFrame(Parameter);

    if (Context->Eax + 1 == 0)
        return STATUS_SUCCESS;

    if (PtrXor(Context->Eax, StubThreadStart) == 0)
    {
        Action->Action = BlockSystemCall;
        return STATUS_SUCCESS;
    }

    if (Context->Eax != NULL)
        return STATUS_SUCCESS;

    Parameter = (PTHREAD_START_PARAMETER)Context->Ebx;

    Context->Eax = (ULONG_PTR)Parameter->ThreadStartRoutine;
    Context->Ebx = (ULONG_PTR)Parameter->Parameter;

    MemoryAllocator::FreeMemory(Parameter);

    return STATUS_SUCCESS;
}

BOOL UnInitialize(PVOID BaseAddress)
{
    PIROTORI_INFO Info = g_Info;

    UnInstallHookPort();

    if (Info == NULL)
        return FALSE;

//    Nt_FreeMemory(NtCurrentProcess(), Info->CP932);

    MemoryAllocator::FreeMemory(Info->TextBuffer);
    MemoryAllocator::FreeMemory(Info->Text);

    delete Info;

    return FALSE;
}

BOOL Initialize(PVOID BaseAddress)
{
    NTSTATUS            Status;
    HANDLE              Timer;
    WCHAR               SystemDirectory[MAX_NTPATH];
    PWSTR               NlsPath;
    ULONG               Length;
    PIROTORI_INFO       Info;
    LARGE_INTEGER       DueTime;

    Info = g_Info;
/*
    Length = Nt_GetSystemDirectory64(SystemDirectory, countof(SystemDirectory));
    if (Length == NULL)
        return FALSE;

    NlsPath = SystemDirectory;

    Status = InitCodePageTable(
                &Info->CpTable932,
                &Info->CP932,
                L"932",
                NlsPath,
                Length
             );
    if (!NT_SUCCESS(Status))
        return FALSE;

    Status = InitCodePageTable(
                &Info->CpTable936,
                &Info->CP936,
                L"936",
                NlsPath,
                Length
             );
    if (!NT_SUCCESS(Status))
        return FALSE;
*/
    Status = Info->NtCreateTimer(&Timer, TIMER_ALL_ACCESS, NULL, SynchronizationTimer);
    if (!NT_SUCCESS(Status))
        return FALSE;

    FormatTimeOut(&DueTime, 100);

    Status = Info->NtSetTimer(Timer, &DueTime, DecryptAPCTimer, Info, FALSE, 1, NULL);
    NtClose(Timer);
    if (!NT_SUCCESS(Status))
        return FALSE;

    Info->Device = Nt_CurrentPeb()->ProcessParameters->CurrentDirectory.Handle;

    CXDEC_OPTION Option;

    ULONG Body1[6] = { 2, 3, 1, 4, 5, 0 };
    ULONG Body2[8] = { 5, 6, 7, 1, 2, 3, 0, 4 };
    ULONG Tail[3]  = { 1, 0, 2 };

    Option.DecryptBlock     = irotori_key;
    Option.Body1IndexMap    = Body1;
    Option.Body2IndexMap    = Body2;
    Option.TailIndexMap     = Tail;
    Option.Const[0]         = TAG4('Rias');
    Option.Const[1]         = TAG4('Grmy');
    Option.FunctionCount    = 0x110;
    Option.FunctionSize     = 0x110;
    Option.LoopCount        = 6;

    Info->cxdec.SetOption(&Option);
    Info->cxdec.Initialize();

    ADD_FILTER(NtDeviceIoControlFile, Info);

    static CHAR FontFace[] = "SIMHEI";

    PVOID HookLdrInitializeThunk;

    HookLdrInitializeThunk = (Nt_CurrentPeb()->OSMajorVersion > 5) ? ::HookLdrInitializeThunk : (PVOID)HookLdrInitializeThunkNT5;

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY(0x33,      1, 0x30DBF),     // ggo full-width space
        PATCH_MEMORY(FontFace,  4, 0x3F268),
        PATCH_MEMORY(0x33,      1, 0x41BD8),    // enum font family
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
//        PATCH_FUNCTION(CALL, 0, 0x418E6, HookCreateWindowExA,       1),
        PATCH_FUNCTION(CALL, 0, 0x2C25D, HookCreateFontA,           1),
        PATCH_FUNCTION(CALL, 0, 0x41C7D, HookEnumFontFamiliesExA,   1),
        PATCH_FUNCTION(CALL, 0, 0x4049B, HooklstrcmpiA,             1),

        PATCH_FUNCTION(CALL, FIRST_CALL_TO_JUMP | AUTO_DISASM2, 0x42B4D, PtrAdd((PVOID)NULL, &IrotoriScriptObject::HookCopyPrefix),         0, &StubCopyPrefix),
        PATCH_FUNCTION(CALL, FIRST_CALL_TO_JUMP | AUTO_DISASM2, 0x42B64, PtrAdd((PVOID)NULL, &IrotoriScriptObject::HookCatString),          0, &StubCatString),
        PATCH_FUNCTION(CALL, FIRST_CALL_TO_JUMP | AUTO_DISASM2, 0x42C06, PtrAdd((PVOID)NULL, &IrotoriScriptObject::HookCatQuote),           0, &StubCatQuote),
        PATCH_FUNCTION(CALL, FIRST_CALL_TO_JUMP | AUTO_DISASM2, 0x3AD31, PtrAdd((PVOID)NULL, &IrotoriScriptObject::HookCopyDescription),    0, &StubCopyDescription),

        INLINE_HOOK_JUMP(Info->LdrInitializeThunk, HookLdrInitializeThunk, Info->StubLdrInitializeThunk),
    };

    Status = Nt_PatchMemory(p, countof(p), f, countof(f), Nt_GetExeModuleHandle());

    Info->Initialized = NT_SUCCESS(LoadText(Info));

    RtlSetUnhandledExceptionFilter(
        [] (PEXCEPTION_POINTERS ExceptionPointers) -> LONG_PTR
        {
            CreateMiniDump(ExceptionPointers);
            return ExceptionContinueSearch;
        }
    );

    return NT_SUCCESS(Status);
}

BOOL InitializeBase(PVOID BaseAddress)
{
    NTSTATUS            Status;
    PTHREAD_TEXT_BUFFER Probe;
    PIROTORI_INFO       Info;

    MemoryAllocator::CreateGlobalHeap();

    Info = new IROTORI_INFO;
    if (Info == NULL)
        return FALSE;

    g_Info = Info;

    ZeroMemory(Info, sizeof(*Info));

    Status = InstallHookPort();
    if (!NT_SUCCESS(Status))
        return FALSE;

    LdrDisableThreadCalloutsForDll(BaseAddress);

#if 1

    PVOID Pointer, NtdllBase;
    PLDR_MODULE NtdllModule;

    NtdllModule = GetNtdllLdrModule();
    NtdllBase   = NtdllModule->DllBase;

    *(PVOID *)&Info->NtCreateThread             = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_NtCreateThread);
    *(PVOID *)&Info->NtCreateThreadEx           = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_NtCreateThreadEx);
    *(PVOID *)&Info->RtlCreateUserThread        = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_RtlCreateUserThread);
    *(PVOID *)&Info->DbgUiRemoteBreakin         = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_DbgUiRemoteBreakin);

    Status = ReLoadDll(NtdllModule->FullDllName.Buffer, &NtdllBase, NtdllModule->DllBase, RELOAD_DLL_IGNORE_IAT);
    if (!NT_SUCCESS(Status))
        return FALSE;

    *(PVOID *)&Info->RtlPushFrame               = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_RtlPushFrame);
    *(PVOID *)&Info->RtlGetFrame                = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_RtlGetFrame);
    *(PVOID *)&Info->RtlPopFrame                = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_RtlPopFrame);
    *(PVOID *)&Info->LdrInitializeThunk         = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_LdrInitializeThunk);
    *(PVOID *)&Info->NtProtectVirtualMemory     = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_NtProtectVirtualMemory);
    *(PVOID *)&Info->NtGetContextThread         = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_NtGetContextThread);
    *(PVOID *)&Info->NtSetContextThread         = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_NtSetContextThread);
    *(PVOID *)&Info->NtCreateTimer              = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_NtCreateTimer);
    *(PVOID *)&Info->NtSetTimer                 = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_NtSetTimer);
    *(PVOID *)&Info->NtTestAlert                = EATLookupRoutineByHashPNoFix(NtdllBase, NTDLL_NtTestAlert);
    *(PVOID *)&Info->CompareStringA             = EATLookupRoutineByHashPNoFix(GetKernel32Handle(), KERNEL32_CompareStringA);

    if (*(PUSHORT)Info->LdrInitializeThunk == 0xFF8B)
        Info->LdrInitializeThunk = PtrAdd(Info->LdrInitializeThunk, 2);

    Info->LdrInitializeThunk = PtrAdd(Info->LdrInitializeThunk, PtrOffset(NtdllModule->DllBase, NtdllBase));
    g_LdrInitializeThunk = Info->LdrInitializeThunk;

    Probe = new THREAD_TEXT_BUFFER;
    if (Probe == NULL)
        return FALSE;

    ADD_FILTER(NtContinue,          Probe);
    ADD_FILTER(NtCreateThread,      Info);
    ADD_FILTER(NtCreateThreadEx,    Info);

    NtSystemDebugControl(SysDbgDisableKernelDebugger, NULL, 0, NULL, 0, NULL);

    Info->RtlPushFrame(Probe);

    Probe->Buffer = (PCHAR)Nt_FindLdrModuleByHandle(NULL)->EntryPoint;
    Probe->Object = (PIROTORI_SCRIPT_OBJECT)NtdllBase;

    return TRUE;

#else

    return Initialize(BaseAddress);

#endif
}

BOOL WINAPI DllMain(PVOID BaseAddress, ULONG Reason, PVOID Reserved)
{
    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return InitializeBase(BaseAddress) || UnInitialize(BaseAddress);

        case DLL_PROCESS_DETACH:
            UnInitialize(BaseAddress);
            break;
    }

    return TRUE;
}

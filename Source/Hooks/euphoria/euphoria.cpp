#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "d3d9.lib")

#include <Windows.h>
#include "euphoria.h"
#include "my_commsrc.h"
#include "../../Unpacker/SafePack/SafePackReader/SafePackReader.cpp"

#define ANTI_DEBUG 1

#if ANTI_DEBUG
    #define ANTI_DEBUG_INLINE ForceInline
#else
    #define ANTI_DEBUG_INLINE
#endif

FAKE_GLOBAL_INFO *g_FakeGlobalInfo;

OVERLOAD_CPP_NEW_WITH_HEAP(Nt_CurrentPeb()->ProcessHeap)

NTSTATUS CDECL LoadFile(YU_RIS_GLOBAL_INFO *GlobalInfo, ULONG, ULONG, bool FileInfoInitialized)
{
    BOOL                    Unknown;
    NTSTATUS                Status;
    PCSTR                   FileName;
    YU_RIS_LOAD_FILE_INFO  *Info;
//    YU_RIS_GLOBAL_INFO     *GlobalInfo;
    SAFE_PACK_FILE_INFO     FileInfo;

    INLINE_ASM mov FileName, edx;
    INLINE_ASM mov Info, eax;
    INLINE_ASM mov Unknown, ecx;

//    GlobalInfo = (YU_RIS_GLOBAL_INFO *)Nt_FindThreadFrameByContext(YURIS_GLOBAL_INFO_MAGIC);
//    if (GlobalInfo == NULL)
//        goto DEFAULT_PROC;

    Status = GlobalInfo->PackReader->GetFileInfo(FileName, &FileInfo);
    if (!NT_SUCCESS(Status))
        goto DEFAULT_PROC;

    Info->Buffer = GlobalInfo->malloc(FileInfo.Size);
    if (Info->Buffer == NULL)
        goto DEFAULT_PROC;

    Status = GlobalInfo->PackReader->Read(&FileInfo, Info->Buffer, FileInfo.Size);
    if (!NT_SUCCESS(Status))
        goto DEFAULT_PROC;

    Info->Size                  = FileInfo.Size;
    Info->FileIndex             = 0;
    Info->FileInfoOffsetOfYpf   = 0;
    Info->PacIndex              = 0;
    Info->FileType              = FileInfo.Flags >> 24;
    Info->StorageType           = STORAGE_YPF;

    return STATUS_SUCCESS;

DEFAULT_PROC:

    return GlobalInfo->LoadFileFunc(Info, FileName, Unknown, FileInfoInitialized);
}

BOOL WINAPI MyTextOutA(HDC hDC, INT X, INT Y, LPCSTR String, INT Count)
{
    PWSTR Unicode;

    Unicode = (PWSTR)AllocStack(Count * sizeof(*Unicode));
    Nt_AnsiToUnicode(Unicode, Count, String, Count);

    return TextOutW(hDC, X, Y, Unicode, Count);
}

NTSTATUS RebuildNtdll(PEB_BASE *Peb, ULONG_PTR BaseAddress, PVOID &NewNtdllIATBase)
{
    NTSTATUS                    Status;
    LPCSTR                      DllName;
    PVOID                       NewNtdllBase;
    PLDR_MODULE                 LdrModule;
    PIMAGE_DOS_HEADER           DosHeader;
    PIMAGE_NT_HEADERS           NtHeader;
    PIMAGE_IMPORT_DESCRIPTOR    ImportDescriptor;
    PIMAGE_THUNK_DATA           ImageThunk;
    PIMAGE_BASE_RELOCATION2     Relocation;

    LdrModule = FIELD_BASE(Peb->Ldr->InInitializationOrderModuleList.Flink, LDR_MODULE, InInitializationOrderModuleList);
    Status = ReLoadDll(LdrModule->FullDllName.Buffer, &NewNtdllBase, LdrModule->BaseAddress);
    if (!NT_SUCCESS(Status))
        return Status;

    DosHeader           = (PIMAGE_DOS_HEADER)BaseAddress;
    NtHeader            = (PIMAGE_NT_HEADERS)((ULONG_PTR)DosHeader + DosHeader->e_lfanew);
    ImportDescriptor    = (PIMAGE_IMPORT_DESCRIPTOR)(NtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress + (ULONG_PTR)BaseAddress);

    for (; ImportDescriptor->Name != NULL; ++ImportDescriptor)
    {
//        PVOID       NewNtdllIATBase;
        ULONG       NtdllIATSize;
        ULONG_PTR   BaseAddressOffset;
        LONG        SizeOfBlock, SizeOfRelocation;
        PBYTE       RelocateBase, Address;
        PUSHORT     TypeOffset;

        DllName = (LPCSTR)BaseAddress + ImportDescriptor->Name;
        if ((HashAPIUpper(DllName) != 0xB4D8D9D7 || HashAPI2Upper(DllName) != 0x7FCCF52F) &&    // ntdll.dll
            (HashAPIUpper(DllName) != 0x14E9AA4D || HashAPI2Upper(DllName) != 0x455ABE13)       // ntdll
           )
        {
            continue;
        }

        ImageThunk = (PIMAGE_THUNK_DATA)(BaseAddress + ImportDescriptor->FirstThunk);
        BaseAddressOffset = (ULONG_PTR)NewNtdllBase - (ULONG_PTR)LdrModule->BaseAddress;

        Relocation = (PIMAGE_BASE_RELOCATION2)NtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
        if (Relocation == NULL)
        {
            for (; ImageThunk->u1.Function != NULL; ++ImageThunk)
                ImageThunk->u1.Function += BaseAddressOffset;

            break;
        }

        SizeOfRelocation = NtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;
        *(PULONG_PTR)&Relocation += (ULONG_PTR)BaseAddress;

        while (ImageThunk->u1.Function != NULL)
            ++ImageThunk;

        NtdllIATSize = (ULONG_PTR)ImageThunk - (BaseAddress + ImportDescriptor->FirstThunk);
        if (NewNtdllIATBase == NULL)
        {
//            NewNtdllIATBase = NULL;
            Status = Nt_AllocateMemory(NtCurrentProcess(), &NewNtdllIATBase, NtdllIATSize);
            if (!NT_SUCCESS(Status))
                break;
        }

        ImageThunk = (PIMAGE_THUNK_DATA)(BaseAddress + ImportDescriptor->FirstThunk);
        for (PIMAGE_THUNK_DATA Thunk1 = ImageThunk, Thunk2 = (PIMAGE_THUNK_DATA)NewNtdllIATBase; Thunk1->u1.Function != NULL; ++Thunk2, ++Thunk1)
            Thunk2->u1.Function = Thunk1->u1.Function + BaseAddressOffset;

        BaseAddressOffset = (ULONG_PTR)NewNtdllIATBase - (ULONG_PTR)ImageThunk;

        for (; SizeOfRelocation > 0; )
        {
            TypeOffset      = Relocation->TypeOffset;
            SizeOfBlock     = Relocation->SizeOfBlock;
            RelocateBase    = (PBYTE)BaseAddress + Relocation->VirtualAddress;

            SizeOfRelocation    -= SizeOfBlock;
            SizeOfBlock         -= sizeof(*Relocation) - sizeof(Relocation->TypeOffset);

            for (; SizeOfBlock > 0; ++TypeOffset, SizeOfBlock -= sizeof(*TypeOffset))
            {
                if (*TypeOffset == 0)
                    continue;

                switch (*TypeOffset >> 12)
                {
                    case 0:
                    case 1:
                    case 2:
                    default:
                        break;

                    case 3:
                        Address = *(PBYTE *)(RelocateBase + (*TypeOffset & 0x0FFF));
                        if (((ULONG_PTR)Address & 3) == 0 && Address - (PBYTE)ImageThunk <= NtdllIATSize)
                        {
                            *(PULONG_PTR)(RelocateBase + (*TypeOffset & 0x0FFF)) += BaseAddressOffset;
                        }
                        break;
                }
            }

            *(PULONG_PTR)&Relocation += Relocation->SizeOfBlock;
        }

        break;
    }

    return STATUS_SUCCESS;
}

#if 0

VOID
Redirect(
    ULONG_PTR               Offset,
    PVOID                  &BaseAddress,
    HINSTANCE               hInstance,
    MEMORY_PATCH           *Patch,
    MEMORY_FUNCTION_PATCH  *Function
)
{

    ULONG GbkLeadByteTable[] =
    {
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,

        ((*(PULONG_PTR)_AddressOfReturnAddress() += Offset), 0x01010100),
        0x01010101, 0x01010101, 0x01010101,

        0x01010101, 0x01010101, 0x01010101, 0x01010101,
        0x01010101, 0x01010101, 0x01010101, 0x01010101,
        0x01010101, 0x01010101, 0x01010101, 0x01010101,
		0x01010101, 0x01010101, 0x01010101, 0x01010101,
        0x01010101, 0x01010101, 0x01010101, 0x01010101,
        0x01010101, 0x01010101, 0x01010101, 0x01010101,
        0x01010101, 0x01010101, 0x01010101, 0x00010101
    };

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY("SaveChs\\",       sizeof(ULONG_PTR),          0x185730),     // save path
//        PATCH_MEMORY("CHINESE_GB2312",  sizeof(ULONG_PTR),          0x0035D3),     // enum font
        PATCH_MEMORY(GB2312_CHARSET,    1,                          0x052D26),     // create font charset
        PATCH_MEMORY(MyTextOutA,        sizeof(ULONG_PTR),          0x15D034),
        PATCH_MEMORY(GbkLeadByteTable,  sizeof(GbkLeadByteTable),   0x1850A0),
    };

    CopyStruct(Patch, p, sizeof(p));
}

#endif

ASM VOID FASTCALL SetThreadGlobalInfo(YU_RIS_GLOBAL_INFO * /* GlobalInfo */)
{
    INLINE_ASM
    {
        mov     eax, g_FakeGlobalInfo;
        and     dword ptr [eax], 1;
        je      NOT_INITIALIZED;
        push    ecx;
        call    dword ptr [RtlPushFrame];

NOT_INITIALIZED:
        ret;
    }
/*
    if (g_FakeGlobalInfo->Flags &= 1)
    {
        RtlPushFrame(GlobalInfo);
    }
*/
}

PVOID FindCallRtlDispatchException_Pass1()
{
    ULONG Length;
    PBYTE pKiUserExceptionDispatcher;

    pKiUserExceptionDispatcher = (PBYTE)KiUserExceptionDispatcher;
    for (LONG Size = 0x17; Size > 0; Size -= Length)
    {
        if (pKiUserExceptionDispatcher[0] == 0xE8)
        {
            return pKiUserExceptionDispatcher;
        }

        Length = GetOpCodeSize(pKiUserExceptionDispatcher);
        pKiUserExceptionDispatcher += Length;
    }

    return NULL;
}

ASM PVOID FASTCALL FindCallRtlDispatchException_Pass2(PVOID)
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

ANTI_DEBUG_INLINE PVOID FindCallRtlDispatchException()
{
    PVOID veh, P1, P2;

    P1 = FindCallRtlDispatchException_Pass1();
    veh = RtlAddVectoredExceptionHandler(TRUE, FindCallRtlDispatchExceptionHandler);
    P2 = FindCallRtlDispatchException_Pass2(P1);
    RtlRemoveVectoredExceptionHandler(veh);

    return P1 == P2 ? P1 : NULL;
}

ASM BOOLEAN STDCALL OldRtlDispatchException(PEXCEPTION_RECORD, PCONTEXT)
{
    ASM_DUMMY_AUTO();
}

VOID RelocationExe(ULONG_PTR BaseAddress, ULONG_PTR Offset)
{
    PBYTE Buffer;

    *(PULONG_PTR)(BaseAddress + 0x10C87) += Offset;
    *(PULONG_PTR)(BaseAddress + 0x45FAB) += Offset;
    *(PULONG_PTR)(BaseAddress + 0x4EF26) += Offset;
    *(PULONG_PTR)(BaseAddress + 0x4B436) += Offset;

//    *(PULONG_PTR)(BaseAddress + 0x56F30) += Offset;
//    *(PULONG_PTR)(BaseAddress + 0x58211) += Offset;

    *(PULONG_PTR)(BaseAddress + 0x4F4FB) += Offset;
    *(PULONG_PTR)(BaseAddress + 0x4F536) += Offset;
    *(PULONG_PTR)(BaseAddress + 0x4F4C5) += Offset;

    Buffer = (PBYTE)BaseAddress + 0x4B44A;
    for (ULONG Count = 0x58; Count; --Count)
    {
        *(PULONG_PTR)Buffer += Offset;
        Buffer += 0xA;
    }

    Buffer = (PBYTE)BaseAddress + 0x5265E;
    for (ULONG Count = 0xE; Count; --Count)
    {
        *(PULONG_PTR)Buffer += Offset;
        Buffer += 0xA;
    }

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY((ULONG_PTR)"SaveChs\\",            sizeof(ULONG_PTR),          0x185730),  // save path
//        PATCH_MEMORY((ULONG_PTR)"CHINESE_GB2312",   sizeof(ULONG_PTR),          0x0035D3),     // enum font
        PATCH_MEMORY(GB2312_CHARSET,                1,  0x03777),                               // enum font
        PATCH_MEMORY(0,                             1,  0x035E9),                               // enum font
        PATCH_MEMORY(GB2312_CHARSET,                1,  0x52D26),                               // create font charset
    };

    Nt_PatchMemory(p, countof(p), 0, 0, (PVOID)BaseAddress);
}

BOOLEAN STDCALL RtlDispatchException(PEXCEPTION_RECORD ExceptionRecord, PCONTEXT Context)
{
    PDR7_INFO   Dr7;
    BOOLEAN     Result;

    switch (ExceptionRecord->ExceptionCode)
    {
        case EXCEPTION_SINGLE_STEP:
            if (COMPARE_CONST(Context->Eip, EXE_ENTRY_POINT))
            {
                PLDR_MODULE         LdrModule;
                ULONG_PTR           Offset;
                PVOID               NewImageBase, NewImageBase2;
                NTSTATUS            Status;
                YU_RIS_GLOBAL_INFO *GlobalInfo;
                WCHAR               PackPath[20]; // = L"euphoria_sc.pack";

                *(PULONG64)&PackPath[0]  = TAG4W('euph') ^ MakeLong64(YURIS_GLOBAL_INFO_MAGIC, YURIS_GLOBAL_INFO_MAGIC);
                *(PULONG64)&PackPath[4]  = TAG4W('oria') ^ MakeLong64(YURIS_GLOBAL_INFO_MAGIC, YURIS_GLOBAL_INFO_MAGIC);
                *(PULONG64)&PackPath[8]  = TAG4W('_sc.') ^ MakeLong64(YURIS_GLOBAL_INFO_MAGIC, YURIS_GLOBAL_INFO_MAGIC);
                *(PULONG64)&PackPath[12] = TAG4W('pack') ^ MakeLong64(YURIS_GLOBAL_INFO_MAGIC, YURIS_GLOBAL_INFO_MAGIC);
                *(PULONG)&PackPath[16]   = 0;

                INLINE_ASM lea eax, PackPath;

                *(PULONG64)&PackPath[0]  ^= MakeLong64(YURIS_GLOBAL_INFO_MAGIC, YURIS_GLOBAL_INFO_MAGIC);
                *(PULONG64)&PackPath[4]  ^= MakeLong64(YURIS_GLOBAL_INFO_MAGIC, YURIS_GLOBAL_INFO_MAGIC);
                *(PULONG64)&PackPath[8]  ^= MakeLong64(YURIS_GLOBAL_INFO_MAGIC, YURIS_GLOBAL_INFO_MAGIC);
                *(PULONG64)&PackPath[12] ^= MakeLong64(YURIS_GLOBAL_INFO_MAGIC, YURIS_GLOBAL_INFO_MAGIC);

//                MessageBoxW(0, 0, 0, 64);

                GlobalInfo = (YU_RIS_GLOBAL_INFO *)Context->Dr2;
                Status = GlobalInfo->PackReader->Open(PackPath);
                if (!NT_SUCCESS(Status))
                    goto CLEAN_UP;

                Context->Dr3 = 0;
                LdrModule = Nt_FindLdrModuleByName(NULL);

                Status = ReLoadDll(LdrModule->FullDllName.Buffer, &NewImageBase);
                if (!NT_SUCCESS(Status))
                    goto CLEAN_UP;

                Offset = (ULONG_PTR)NewImageBase - (Context->Eip & 0x00F00000);
                Context->Eip += Offset;
                Context->Dr3  = (ULONG_PTR)NewImageBase + 0x4E655;

//#define ORIG_DEBUG
#ifdef ORIG_DEBUG
                Context->Dr1  = (ULONG_PTR)LdrModule->BaseAddress + 0x4E655;
#endif

                RelocationExe((ULONG_PTR)NewImageBase, Offset);
                GlobalInfo->LoadFileHookOffset = (ULONG_PTR)LoadFile - Context->Dr3;

#ifdef ORIG_DEBUG
                GlobalInfo->LoadFileHookOffset = (ULONG_PTR)LoadFile;
#endif

                NewImageBase2 = NULL;
                Status = Nt_AllocateMemory(NtCurrentProcess(), &NewImageBase2, LdrModule->SizeOfImage);
                if (!NT_SUCCESS(Status))
                {
                    UnLoadDll(NewImageBase);
                    goto CLEAN_UP;
                }

                CopyMemory(NewImageBase2, NewImageBase, LdrModule->SizeOfImage);

                *(PULONG_PTR)&GlobalInfo->LoadFileFunc ^= YURIS_GLOBAL_INFO_MAGIC;
                *(PULONG_PTR)&GlobalInfo->LoadFileFunc  = _rotr((ULONG_PTR)GlobalInfo->LoadFileFunc, 12) + (ULONG_PTR)NewImageBase2;
            }
            else if (COMPARE_CONST(Context->Eip & 0xFFFF, 0x0E655))
            {
                *(PULONG_PTR)(Context->Esp + 4) = (ULONG_PTR)Context->Dr2;
                Context->Eip += ((YU_RIS_GLOBAL_INFO *)Context->Dr2)->LoadFileHookOffset;

#ifdef ORIG_DEBUG
                Context->Eip = ((YU_RIS_GLOBAL_INFO *)Context->Dr2)->LoadFileHookOffset;
#endif
            }
            else
            {
                break;
            }

            Context->ContextFlags |= CONTEXT_DEBUG_REGISTERS;

            return TRUE;

        case EXCEPTION_GUARD_PAGE:
            if (ExceptionRecord->ExceptionInformation[0] != 1)
                break;
            if (ExceptionRecord->ExceptionInformation[1] != (ULONG_PTR)Context->Dr3)
                break;

            Context->Eip += 3;
            Context->Dr2 = (ULONG_PTR)((FAKE_GLOBAL_INFO *)Context->Dr3)->GlobalInfo;
            Context->Dr7 = 0;

            Dr7 = (PDR7_INFO)&Context->Dr7;

//            Dr7->L1         = 1;
//            Dr7->RW1        = 0;
            Dr7->L3         = 1;
            Dr7->RW3        = 0;
//            Context->Dr3    = EXE_ENTRY_POINT;

            INLINE_ASM
            {
                mov ecx, Context;
                lea ecx, [ecx]CONTEXT.Dr3;
                mov dword ptr [ecx], EXE_ENTRY_POINT ^ 0x7324DAE4;
                add dword ptr [ecx], EXE_ENTRY_POINT - (EXE_ENTRY_POINT ^ 0x7324DAE4);
            }

            Context->ContextFlags |= CONTEXT_DEBUG_REGISTERS;

            return TRUE;
    }

    Result = OldRtlDispatchException(ExceptionRecord, Context);
    CLEAR_FLAG(Context->ContextFlags, (CONTEXT_DEBUG_REGISTERS & ~CONTEXT_i386));

    return Result;

CLEAN_UP:
    Context->ContextFlags |= CONTEXT_DEBUG_REGISTERS;
    Context->Dr2 = 0;
    Context->Dr3 = 0;
    Context->Dr7 = 0;

    return TRUE;
}

HANDLE WINAPI MyCreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName)
{
    CONTEXT ctx;

    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    NtGetContextThread(NtCurrentProcess(), &ctx);
    PrintConsoleW(L"%08X\n", ctx.Dr3);

    return CreateMutexA(lpMutexAttributes, bInitialOwner, lpName);
}

ULONG WINAPI ShowDr3(HANDLE ThreadHandle)
{
    CONTEXT ctx;
    LARGE_INTEGER TimeOut;

    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    BaseFormatTimeOut(&TimeOut, 400);
    AllocConsole();
    LOOP_FOREVER
    {
        NtGetContextThread(ThreadHandle, &ctx);
        PrintConsoleW(L"%08X: %08X\n", GetTickCount(), ctx.Dr3);
        NtDelayExecution(FALSE, &TimeOut);
    }
}

BOOL CDECL cmp(PCSTR str1, PCSTR str2)
{
    AllocConsole();
    PrintConsoleW(L"%08X: %S, %S\n", GetTickCount(), str1, str2);
    return 0;
}

ANTI_DEBUG_INLINE BOOL Init(HINSTANCE hInstance)
{
    ULONG               Protect;
    ULONG_PTR           NewImageOffset, RtlDispatchExceptionAddress;
    PVOID               BaseAddress, NewSelfBase, NewNtdllIatBase;
    YU_RIS_GLOBAL_INFO *GlobalInfo;
    PLDR_MODULE         SelfModule;
    CONTEXT             Context;

    ULONG GbkLeadByteTable[] =
    {
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,

        (SelfModule = Nt_FindLdrModuleByHandle(hInstance), 0x00000000),
        0x00000000, 0x00000000, 0x00000000,

        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x01010100, 0x01010101, 0x01010101, 0x01010101,
        0x01010101, 0x01010101, 0x01010101, 0x01010101,

        (ReLoadDll(SelfModule->FullDllName.Buffer, &NewSelfBase), 0x01010101),
        0x01010101, 0x01010101, 0x01010101,

        0x01010101, 0x01010101, 0x01010101, 0x01010101,
        0x01010101, 0x01010101, 0x01010101, 0x01010101,
        0x01010101, 0x01010101, 0x01010101, 0x01010101,
        0x01010101, 0x01010101, 0x01010101, 0x01010101,
        0x01010101, 0x01010101, 0x01010101, 0x00010101
    };

    BaseAddress = Nt_GetExeModuleHandle();

    RtlDispatchExceptionAddress = (ULONG_PTR)FindCallRtlDispatchException();
    if (RtlDispatchExceptionAddress != NULL)
    {
        RtlDispatchExceptionAddress += *(PULONG_PTR)(RtlDispatchExceptionAddress + 1) + 5;
        RtlDispatchExceptionAddress -= (ULONG_PTR)BaseAddress;
    }
    else
    {
        --RtlDispatchExceptionAddress;
    }

    NewImageOffset = (ULONG_PTR)NewSelfBase - (ULONG_PTR)hInstance;

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY((ULONG_PTR)"SaveChs\\",        sizeof(ULONG_PTR),          0x185730),      // save path
        PATCH_MEMORY(GB2312_CHARSET,                1,  0x03777),                               // enum font
        PATCH_MEMORY(0,                             1,  0x035E9),                               // enum font
//        PATCH_MEMORY((ULONG_PTR)"CHINESE_GB2312",   sizeof(ULONG_PTR),          0x0035D3),      // enum font
        PATCH_MEMORY(GB2312_CHARSET,                1,                          0x052D26),      // create font charset
        PATCH_MEMORY(GbkLeadByteTable,              sizeof(GbkLeadByteTable),   0x1850A0),
    };

    *(PULONG_PTR)&NewSelfBase |= ((ULONG_PTR)hInstance ^ (ULONG_PTR)NewSelfBase) ? 0 : IMAGE_INVALID_RVA;

    MEMORY_FUNCTION_PATCH f[] =
    {
//        PATCH_FUNCTION(JUMP, AUTO_DISASM, 0x4E655, (PVOID)((ULONG_PTR)LoadFile + NewImageOffset), 0, (PVOID)((ULONG_PTR)OldLoadFile + NewImageOffset)),
        PATCH_FUNCTION(JEAX, AUTO_DISASM, RtlDispatchExceptionAddress, (PVOID)((ULONG_PTR)RtlDispatchException + NewImageOffset), 0, (PVOID)((ULONG_PTR)OldRtlDispatchException + NewImageOffset)),
//        PATCH_FUNCTION(CALL, 0, 0x035D8, cmp),
    };

    LdrDisableThreadCalloutsForDll(hInstance);

    NewNtdllIatBase = NULL;
    Nt_AllocateMemory(NtCurrentProcess(), &NewNtdllIatBase, MEMORY_PAGE_SIZE * 2);

    *(PULONG_PTR)&NewNtdllIatBase += MEMORY_PAGE_SIZE / 2;
    RebuildNtdll(Nt_CurrentPeb(), (ULONG_PTR)NewSelfBase, NewNtdllIatBase);
    *(PULONG_PTR)&NewNtdllIatBase += MEMORY_PAGE_SIZE / 2;
    g_FakeGlobalInfo = (FAKE_GLOBAL_INFO *)NewNtdllIatBase;
    *(PULONG_PTR)((ULONG_PTR)&g_FakeGlobalInfo + NewImageOffset) = (ULONG_PTR)g_FakeGlobalInfo;

    Nt_PatchMemory(p, countof(p), f, (++*(PULONG_PTR)&NewSelfBase ? -1 : 0) & countof(f), BaseAddress);

    Nt_SetExeDirectoryAsCurrent();

    GlobalInfo = (YU_RIS_GLOBAL_INFO *)AllocateMemory(sizeof(*GlobalInfo));
    if (GlobalInfo == NULL)
        return FALSE;

    GlobalInfo->Context                 = YURIS_GLOBAL_INFO_MAGIC;
    *(PULONG_PTR)&GlobalInfo->malloc    = (ULONG_PTR)BaseAddress + RVA_MALLOC;
    *(PULONG_PTR)&GlobalInfo->free      = (ULONG_PTR)BaseAddress + RVA_FREE;
    GlobalInfo->PackReader              = new CSafePackReader;

    *(PULONG_PTR)&GlobalInfo->LoadFileFunc = _rotl(0x4E648, 12) ^ YURIS_GLOBAL_INFO_MAGIC;

    g_FakeGlobalInfo->Flags     |= 1;
    g_FakeGlobalInfo->GlobalInfo = GlobalInfo;

    Nt_ProtectMemory(NtCurrentProcess(), g_FakeGlobalInfo, MEMORY_PAGE_SIZE, PAGE_READWRITE | PAGE_GUARD, &Protect);

    Context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    NtGetContextThread(NtCurrentThread(), &Context);

    Context.Dr3 = (ULONG_PTR)NewNtdllIatBase;
    NtSetContextThread(NtCurrentThread(), &Context);

    SetThreadGlobalInfo(GlobalInfo);

//    NtGetContextThread(NtCurrentThread(), &Context);

//    AllocConsole();
//    PrintConsoleW(L"%08X\n", Context.Dr3);

//    HANDLE ThreadHandle;

//    NtDuplicateObject(NtCurrentProcess(), NtCurrentThread(), NtCurrentProcess(), &ThreadHandle, 0, 0, DUPLICATE_SAME_ACCESS);
//    Nt_CreateThread(ShowDr3, ThreadHandle);

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID Reserved)
{
    UNREFERENCED_PARAMETER(Reserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Init(hInstance);

        case DLL_PROCESS_DETACH:
            FreeMemory(Nt_FindThreadFrameByContext(YURIS_GLOBAL_INFO_MAGIC));
            break;
    }

    return TRUE;
}

#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "msimg32.lib")
#pragma warning(disable:4238)

#include <Windows.h>
#include "krkr2.h"
#include "my_commsrc.h"

OVERLOAD_CPP_NEW_WITH_HEAP(CMem::GetGlobalHeap())

#define USE_DYNAMIC_EXE     1
#define USE_DYNAMIC_SELF    1
#define USE_RELOAD_DLL      1
#define USE_UPX             0

#define DECL_ASM_DUMMY(_Type, _CallConv, _Name, ...) ASM _Type _CallConv _Name(...) { ASM_DUMMY_AUTO() }

Krkr2TJSBinaryStreamReadRoutine Krkr2TJSBinaryStreamReadFunc;

ULONG_PTR g_NtCreateThread, g_NtCreateThreadEx, g_RtlCreateUserThread, g_DbgUiRemoteBreakin;
MODULE_MAP g_ModuleMap;

#pragma warning(push, 0)

NTSTATUS
NTAPI
OldNtCreateThread(
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
    ASM_DUMMY_AUTO();
}

NTSTATUS
NTAPI
OldNtCreateThreadEx(
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
    ASM_DUMMY_AUTO();
}

VOID
CDECL
OldLdrpInitialize(
    PCONTEXT    ThreadContext,
    PVOID       NtdllBase
)
{
    ASM_DUMMY_AUTO();
}

NTSTATUS
NTAPI
OldLdrLoadDll(
    PWCHAR          PathToFile,
    PULONG          Flags,
    PUNICODE_STRING ModuleFileName,
    PVOID          *ModuleBase
)
{
    ASM_DUMMY_AUTO();
}

ULONG STDCALL ThreadStart(THREAD_START_PARAMETER *Parameter)
{
    return 0;
//    RtlPushFrame(Parameter);
//    return Parameter->ThreadStartRoutine(Parameter->Parameter);
}

#pragma warning(pop)

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

THREAD_START_PARAMETER*
AllocateThreadParameter(
    PVOID StartAddress,
    PVOID Parameter
)
{
    THREAD_START_PARAMETER *StartParameter;

    StartParameter = (THREAD_START_PARAMETER *)CMem::AllocateMemory(sizeof(*StartParameter));

    StartParameter->Context              = THREAD_START_PARAMETER_MAGIC;
    StartParameter->Parameter            = Parameter;
    StartParameter->ThreadStartRoutine   = StartAddress;

    return StartParameter;
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

    INLINE_ASM lea eax, NewContext;

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

/*
    {
        ULONG_PTR addr = (ULONG_PTR)ThreadStartAddress;
        PLDR_MODULE first, cur;

        first = FIELD_BASE(Nt_CurrentPeb()->Ldr->InLoadOrderModuleList.Flink, LDR_MODULE, InLoadOrderModuleList);

        cur = first;
        do
        {
            if (IN_RANGE((ULONG_PTR)cur->BaseAddress, addr, (ULONG_PTR)cur->BaseAddress + cur->SizeOfImage))
            {
                PrintConsoleW(
                    L"addr = %08X, module = %.*s\n",
                    addr,
                    cur->FullDllName.Length,
                    cur->FullDllName.Buffer
                );

                if (addr == g_DbgUiRemoteBreakin)
                    while (1);
                break;
            }

            cur = FIELD_BASE(cur->InLoadOrderModuleList.Flink, LDR_MODULE, InLoadOrderModuleList);
        } while (cur != first);
    }
*/

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
        RtlPushFrame(&SystemThreadParameter);
        ThreadContext->Eax = (ULONG_PTR)ThreadStart;
    }

    INLINE_ASM mov ebx, esp;
    OldLdrpInitialize(ThreadContext, NtdllBase);
    INLINE_ASM mov esp, ebx;
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
    PWSTR       PathBuffer;
    ULONG       Length, System32Length;
    NTSTATUS    Status;

    System32Length = Nt_GetSystemDirectory(NULL, 0);
    Length = StrLengthW(PathToFile);
    PathBuffer = (PWSTR)AllocStack((Length + System32Length) * sizeof(WCHAR));

    Nt_GetSystemDirectory(PathBuffer, System32Length);
    *(PULONG)&PathBuffer[System32Length++] = ';';

    if (PathToFile != NULL)
    {
        CopyMemory(PathBuffer + System32Length, PathToFile, Length * sizeof(WCHAR));
    }

    Status = OldLdrLoadDll(PathBuffer, Flags, ModuleFileName, ModuleBase);

    if (NT_SUCCESS(Status))
    {
        MODULE_MAP_ENTRY *Entry = g_ModuleMap.Entry;

        for (ULONG Count = g_ModuleMap.Count; Count; ++Entry, --Count)
        {
            if (*ModuleBase == Entry->OriginalBase)
                return Status;
        }

        HookModuleIAT(&g_ModuleMap, *ModuleBase);
    }

    return Status;
}

PVOID STDCALL HookLoadLibraryA(PCSTR LibFileName)
{
    WCHAR           Unicode[MAX_NTPATH];
    PVOID           BaseAddress;
    ULONG           Length;
    NTSTATUS        Status;
    UNICODE_STRING  UnicodeLibFileName;
    PLDR_MODULE     LdrModule;

    Nt_AnsiToUnicode(Unicode, countof(Unicode), LibFileName, -1, &Length);

    UnicodeLibFileName.Buffer           = findnamew(Unicode);
    UnicodeLibFileName.Length           = Length - (UnicodeLibFileName.Buffer - Unicode) * sizeof(WCHAR);
    UnicodeLibFileName.MaximumLength    = UnicodeLibFileName.Length;

    LdrModule = Nt_FindLdrModuleByName(&UnicodeLibFileName);
    if (LdrModule != NULL)
    {
        if (LdrModule->LoadCount != -1)
            ++LdrModule->LoadCount;

        return LdrModule->BaseAddress;
    }

    UnicodeLibFileName.Buffer           = Unicode;
    UnicodeLibFileName.Length           = Length;
    UnicodeLibFileName.MaximumLength    = Length;

    Status = LdrLoadDll(NULL, 0, &UnicodeLibFileName, &BaseAddress);

    return NT_SUCCESS(Status) ? BaseAddress : NULL;
}

FARPROC STDCALL HookGetProcAddress(PVOID ModuleBase, PCSTR ProcName)
{
    FARPROC ProcAddress;
    MODULE_MAP_ENTRY *Entry;

    ProcAddress = Nt_GetProcAddress(ModuleBase, ProcName);
    if (ProcAddress == NULL)
        return ProcAddress;

    Entry = g_ModuleMap.Entry;

    for (ULONG Count= g_ModuleMap.Count; Count; ++Entry, --Count)
    {
        if (ModuleBase == Entry->OriginalBase)
        {
            ProcAddress = PtrAdd(ProcAddress, PtrOffset(Entry->MappedBase, Entry->OriginalBase));
            break;
        }
    }

    return ProcAddress;
}

#define CRAZY_XP3
#define CRAZY_XP3_INIT
#define CXDEC_NO_ENCRYPT_BLOCK 1

#define m_EncryptBlock 0x400000

#include "../../Unpacker/krkr2/cxdec.cpp"
/*
VOID InitDecryptBlock(CCxdec *cxdec)
{
    ULONG           Protect, BlockSize, BlockCount, *Block;
    PBYTE           Buffer;
    RTL_SHA_CTX     Context;

    const PVOID ImageBase   = (PVOID)0x401000;
    const ULONG SizeOfImage = 0x200000;

    UNREFERENCED_PARAMETER(cxdec);

    BlockCount  = countof(cxdec->m_EncryptBlock) / countof(((PRTL_SHA_DIG)0)->Digest);
    BlockSize   = SizeOfImage / BlockCount;
    Buffer      = (PBYTE)ImageBase;

    Nt_ProtectMemory(NtCurrentProcess(), ImageBase, SizeOfImage, PAGE_EXECUTE_READ, &Protect);

    A_SHAInit(&Context);

    Block = (PULONG)cxdec->m_EncryptBlock;
    for (; BlockCount; --BlockCount)
    {
        A_SHAUpdate(&Context, Buffer, BlockSize);
        A_SHAFinal(&Context, (PRTL_SHA_DIG)Block);
        Block += 5;
        Buffer += BlockSize;
    }

    if (Protect != PAGE_EXECUTE_READ)
        Nt_ProtectMemory(NtCurrentProcess(), ImageBase, SizeOfImage, Protect, &Protect);
}
*/
VOID DecryptCxdecInternal(ULONG Hash, LARGE_INTEGER Offset, PVOID lpBuffer, ULONG BufferSize)
{
    PBYTE           pbBuffer;
    ULONG           Mask, Mask2;
    LARGE_INTEGER   CurrentPos;

    static CCxdec *cxdec;

    if (cxdec == NULL)
        cxdec = new CCxdec;

#if !defined(CRAZY_XP3_INIT)
    InitDecryptBlock(cxdec);
#endif

    pbBuffer = (PBYTE)lpBuffer;
    Mask = cxdec->GetMask(Hash);

    Mask2 = LOWORD(Mask);
    CurrentPos.QuadPart = Offset.QuadPart + BufferSize;

    if (Mask2 >= Offset.QuadPart && Mask2 < CurrentPos.QuadPart)
    {
        *(pbBuffer + Mask2 - Offset.LowPart) ^= Hash >> 16;
    }

    Mask2 = HIWORD(Mask);
    if (Mask2 >= Offset.QuadPart && Mask2 < CurrentPos.QuadPart)
    {
        *(pbBuffer + Mask2 - Offset.LowPart) ^= Hash >> 8;
    }

    memxor(pbBuffer, Hash, BufferSize);
}

NoInline ULONG GetSegmentLength(ULONG FileHash, ULONG &SegmLength)
{
    SegmLength = (FileHash & 0x233) + 0x466;
    return -SegmLength;
}

VOID STDCALL ExtractionFilter(XP3_EXTRACTION_INFO &Info)
{
    ULONG SegmLength, Hash;
    LARGE_INTEGER CurrentPos, Offset2;

    GetSegmentLength(Info.FileHash, SegmLength);
    INLINE_ASM mov Hash, eax;

    Offset2.QuadPart = SegmLength;
    CurrentPos.QuadPart = Info.Offset.QuadPart + Info.BufferSize;
    if (Info.Offset.QuadPart < Offset2.QuadPart && CurrentPos.QuadPart > Offset2.QuadPart)
    {
        Hash = Info.FileHash;
        SegmLength = Offset2.LowPart - Info.Offset.LowPart;
        DecryptCxdecInternal(Hash, Info.Offset, Info.Buffer, SegmLength);

        Hash = (Info.FileHash >> 16) ^ Info.FileHash;
        Info.Buffer = (PBYTE)Info.Buffer + SegmLength;
        DecryptCxdecInternal(Hash, Offset2, Info.Buffer, Info.BufferSize - SegmLength);
    }
    else
    {
        if (Info.Offset.QuadPart < Offset2.LowPart)
        {
            Hash = Info.FileHash;
        }
        else
        {
            Hash = (Info.FileHash >> 16) ^ Info.FileHash;
        }

        DecryptCxdecInternal(Hash, Info.Offset, Info.Buffer, Info.BufferSize);
    }
}

ULONG64 CDECL MemStreamSeek(MEMORY_STREAM *Stream, ULONG64 Offset, ULONG SeekMethod)
{
    NTSTATUS        Status;
    LARGE_INTEGER   Position;

    Status = CNtFileDisk::Seek(Stream->FileHandle, Offset, SeekMethod, &Position);

    return NT_SUCCESS(Status) ? Position.QuadPart : 0;
}

ULONG CDECL MemStreamRead(MEMORY_STREAM *Stream, PVOID Buffer, ULONG Size)
{
    NTSTATUS        Status;
    LARGE_INTEGER   BytesRead;

    Status = CNtFileDisk::Read(Stream->FileHandle, Buffer, Size, &BytesRead);

    return NT_SUCCESS(Status) ? BytesRead.LowPart : 0;
}

ULONG CDECL MemStreamWrite(MEMORY_STREAM *Stream, PVOID Buffer, ULONG Size)
{
    NTSTATUS        Status;
    LARGE_INTEGER   BytesWritten;

    Status = CNtFileDisk::Write(Stream->FileHandle, Buffer, Size, &BytesWritten);

    return NT_SUCCESS(Status) ? BytesWritten.LowPart : 0;
}

ULONG64 CDECL MemStreamGetSize(MEMORY_STREAM *Stream)
{
    NTSTATUS        Status;
    LARGE_INTEGER   FileSize;

    Status = CNtFileDisk::GetSize(Stream->FileHandle, &FileSize);

    return NT_SUCCESS(Status) ? FileSize.QuadPart : 0;
}

ULONG CDECL Krkr2TJSBinaryStreamRead(IKrkr2TJSBinaryStream *Stream, PVOID Buffer, ULONG Size)
{
    ULONG                   BytesWritten, Protect;
    LARGE_INTEGER           Offset;
    TJSBINSTREAM_SEGM_INFO *Segment;

    Segment = Stream->m_FileInfo.SegmentInfo;
    Nt_ProtectMemory(NtCurrentProcess(), Segment, sizeof(*Segment), PAGE_READWRITE, &Protect);

    if (Segment->DataOffset.HighPart < 0)
    {
        Offset.QuadPart = Segment->DataOffset.QuadPart;

        Offset.LowPart  ^= TAG4('AMNO');
        Offset.QuadPart  = -Offset.QuadPart;

        Segment->DataOffset.QuadPart        = Offset.QuadPart;
    }

    if (Protect != PAGE_READWRITE)
        Nt_ProtectMemory(NtCurrentProcess(), Segment, sizeof(*Segment), Protect, &Protect);

    BytesWritten = Krkr2TJSBinaryStreamReadFunc(Stream, Buffer, Size);

    return BytesWritten;
}

VOID
FASTCALL
CreateTempFileStream(
    IKrkr2TJSBinaryStream   *DllStream,
    Krkr2String             *DllFullPath
)
{
    ULONG           FileSize, Length;
    PVOID           FileBuffer;
    PWSTR           PathBuffer;
    UNICODE_STRING  DllName;

    FileSize = DllStream->GetSize();
    FileBuffer = CMem::AllocateMemory(FileSize);
    if (FileBuffer == NULL)
        return;

    DllStream->Read(FileBuffer, FileSize);
    PathBuffer = DllFullPath->GetBuffer();

    if (!IsValidImage(FileBuffer, 0))
    {
        HANDLE      FileHandle;
        NTSTATUS    Status;
        ULONG       ch;

        PathBuffer = findnamew(PathBuffer);
        ch = *PathBuffer;
        *PathBuffer = 0;
        MyCreateDirectoryW(DllFullPath->GetBuffer());
        *PathBuffer = ch;

        Status = CNtFileDisk::Create(&FileHandle, DllFullPath->GetBuffer());
        if (!NT_SUCCESS(Status))
            return;

        CNtFileDisk::Write(FileHandle, FileBuffer, FileSize);
        NtClose(FileHandle);

        return;
    }

    Length                  = StrLengthW(PathBuffer);
    DllName.Buffer          = PathBuffer;
    DllName.Length          = Length * sizeof(WCHAR);
    DllName.MaximumLength   = DllName.Length;

    do
    {
        if (*PathBuffer == '/')
            *PathBuffer = '\\';

        ++PathBuffer;
    } while (--Length);

    LoadDllFromMemory(FileBuffer, FileSize, &DllName);

    CMem::FreeMemory(FileBuffer);
}

ASM VOID CreateTempFileStreamNaked()
{
    INLINE_ASM
    {
        and  dword ptr [eax], 0;
        mov  ecx, [ebp - 1Ch];
        mov  edx, [edx];
        call CreateTempFileStream;
        ret;
    }
}

ASM VOID BypassCheckPluginOnDisk()
{
    INLINE_ASM mov eax, 0;
}

ASM VOID LoadTpmPlugins()
{
    INLINE_ASM
    {
        add dword ptr [esp], 80h;
        ret;
    }
}

VOID RelocateNewExe(ULONG_PTR BaseAddress, ULONG_PTR Offset)
{
    ULONG_PTR *Table;

    static ULONG_PTR RelocateTable[] =
    {
/*
        0x17DA5C, 0x27EDB4, 0x200C69, 0x200C73, 0x19DD59, 0x06B0D7,
        0x06B835, 0x04DF46, 0x04E004, 0x202721, 0x00FED1,

        // dispatch table
        0x00FED5, 0x00FED9, 0x00FEDD, 0x00FEE1,
        0x00FEE5, 0x00FEE9, 0x00FEED, 0x00FEF1,
        0x00FEF5, 0x00FEF9, 0x00FEFD, 0x00FF01,
        0x00FF05, 0x00FF09, 0x00FF0D, 0x00FF11,
        0x00FF15, 0x00FF19, 0x00FF1D, 0x00FF21,
        0x00FF25, 0x00FF29, 0x00FF2D, 0x00FF31,
        0x00FF35, 0x00FF39, 0x00FF3D, 0x00FF41,
        0x00FF45, 0x00FF49, 0x00FF4D, 0x00FF51,
        0x00FF55, 0x00FF59, 0x00FF5D, 0x00FF61,
        0x00FF65, 0x00FF69, 0x00FF6D, 0x00FF71,
        0x00FF75, 0x00FF79, 0x00FF7D, 0x00FF81,
        0x00FF85, 0x00FF89, 0x00FF8D, 0x00FF91,
        0x00FF95, 0x00FF99, 0x00FF9D, 0x00FFA1,
        0x00FFA5, 0x00FFA9, 0x00FFAD, 0x00FFB1,
        0x00FFB5, 0x00FFB9, 0x00FFBD, 0x00FFC1,
        0x00FFC5, 0x00FFC9, 0x00FFCD, 0x00FFD1,
        0x00FFD5, 0x00FFD9, 0x00FFDD, 0x00FFE1,
        0x00FFE5, 0x00FFE9, 0x00FFED, 0x00FFF1,
        0x00FFF5, 0x00FFF9, 0x00FFFD, 0x010001,
        0x010005, 0x010009, 0x01000D, 0x010011,
        0x010015, 0x010019, 0x01001D, 0x010021,
        0x010025, 0x010029, 0x01002D, 0x010031,
        0x010035, 0x010039, 0x01003D, 0x010041,
        0x010045, 0x010049, 0x01004D, 0x010051,
        0x010055, 0x010059, 0x01005D, 0x010061,
        0x010065, 0x010069, 0x01006D, 0x010071,
        0x010075, 0x010079, 0x01007D, 0x010081,
        0x010085, 0x010089, 0x01008D, 0x010091,
        0x010095, 0x010099, 0x01009D, 0x0100A1,
        0x0100A5, 0x0100A9, 0x0100AD, 0x0100B1,
        0x0100B5, 0x0100B9, 0x0100BD, 0x0100C1,
        0x0100C5, 0x0100C9, 0x0100CD, 0x0100D1,

        0x35CDDC, 0x35CDE0, 0x35CDE4, 0x35CDE8,
        0x35CDEC, 0x35CDF0, 0x35CDF4, 0x35CDF8,
        0x35CDFC, 0x35CE00, 0x35CE04, 0x35CE08,
        0x35CE0C, 0x35CE10, 0x35CE14, 0x35CE18,
        0x35CE1C, 0x35CE20, 0x35CE24, 0x35CE28,
        0x35CE2C, 0x35CE30, 0x35CE34, 0x35CE38,
        0x35CE3C, 0x35CE40, 0x35CE44, 0x35CE48,
        0x35CE4C, 0x35CE50, 0x35CE54, 0x35CE58,

        0x357910, 0x357914, 0x357918, 0x35791C,
        0x357920, 0x357924, 0x357928, 0x35792C,
        0x357930, 0x357934, 0x357938, 0x35793C,
        0x357940, 0x357944, 0x357948, 0x35794C,
        0x357950, 0x357954, 0x357958, 0x35795C,
        0x357960, 0x357964, 0x357968, 0x35796C,
        0x357970, 0x357974, 0x357978, 0x35797C,
        0x357980, 0x357984, 0x357988,
*/

        0x39F9FC, 0x39FA00, 0x39FA04, 0x39FA08,
        0x39FA0C, 0x39FA10, 0x39FA14, 0x39FA18,
        0x39FA1C, 0x39FA20, 0x39FA24, 0x39FA28,
        0x39FA2C, 0x39FA30, 0x39FA34, 0x39FA38,
        0x39FA3C, 0x39FA40, 0x39FA44, 0x39FA48,
        0x39FA4C, 0x39FA50, 0x39FA54, 0x39FA58,
        0x39FA5C, 0x39FA60, 0x39FA64, 0x39FA68,
        0x39FA6C, 0x39FA70, 0x39FA74, 0x39FA78,
        0x39FA7C, 0x39FA80, 0x39FA84,
    };

    Table = RelocateTable;
    for (ULONG Count = countof(RelocateTable); Count; ++Table, --Count)
    {
        if (*Table == 0)
            continue;

        *(PULONG_PTR)(BaseAddress + *Table) += Offset;
    }
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

enum
{
    RMI_REMOVE_IAT  = 0x00000001,
};

NTSTATUS
RedirectModuleIAT(
    PVOID ModuleBase,
    PVOID ImportModule,
    PVOID NewImportModule,
    ULONG ImportModuleSize,
    PCSTR ModuleName,
    ULONG Flags
)
{
    PSTR                        DllName;
    ULONG                       Protect, IatSize;
    ULONG_PTR                   BaseAddressOffset, MinAddress, MaxAddress;
    PIMAGE_DOS_HEADER           DosHeader;
    PIMAGE_NT_HEADERS           NtHeader;
    PIMAGE_IMPORT_DESCRIPTOR    ImportDescriptor;
    PIMAGE_THUNK_DATA           ImageThunk;

    DosHeader           = (PIMAGE_DOS_HEADER)ModuleBase;
    NtHeader            = (PIMAGE_NT_HEADERS)PtrAdd(DosHeader, DosHeader->e_lfanew);
    ImportDescriptor    = (PIMAGE_IMPORT_DESCRIPTOR)(NtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress + (ULONG_PTR)ModuleBase);

    for (; ImportDescriptor->Name != NULL; ++ImportDescriptor)
    {
        DllName = (PSTR)ModuleBase + ImportDescriptor->Name;
        if (StrICompareA(DllName, ModuleName))
            continue;

        ImageThunk          = (PIMAGE_THUNK_DATA)PtrAdd(ModuleBase, ImportDescriptor->FirstThunk);
        BaseAddressOffset   = PtrOffset(NewImportModule, ImportModule);

        if (ImageThunk->u1.Function == NULL)
            break;

        IatSize = 0;
        do
        {
            IatSize += sizeof(ULONG_PTR);
        } while ((++ImageThunk)->u1.Function != NULL);

        ImageThunk = (PIMAGE_THUNK_DATA)PtrAdd(ModuleBase, ImportDescriptor->FirstThunk);

        Nt_ProtectMemory(
            NtCurrentProcess(),
            &ImageThunk->u1.Function,
            IatSize,
            PAGE_EXECUTE_READWRITE,
            &Protect
        );

        MinAddress = (ULONG_PTR)ImportModule;
        MaxAddress = MinAddress + ImportModuleSize;
        do
        {
            if (ImageThunk->u1.Function >= MinAddress && ImageThunk->u1.Function < MaxAddress)
                ImageThunk->u1.Function += BaseAddressOffset;
        } while ((++ImageThunk)->u1.Function != NULL);

        if (Protect != PAGE_EXECUTE_READWRITE)
        {
            ImageThunk = (PIMAGE_THUNK_DATA)PtrAdd(ModuleBase, ImportDescriptor->FirstThunk);

            Nt_ProtectMemory(
                NtCurrentProcess(),
                &ImageThunk->u1.Function,
                IatSize,
                PAGE_EXECUTE_READWRITE,
                &Protect
                );
        }

        if (FLAG_ON(Flags, RMI_REMOVE_IAT))
        {
            Nt_ProtectMemory(
                NtCurrentProcess(),
                &ImportDescriptor->Name,
                1,
                PAGE_EXECUTE_READWRITE,
                &Protect
            );

            ImportDescriptor->Name = (ImportDescriptor + 1)->Name;

            if (Protect != PAGE_EXECUTE_READWRITE)
            {
                Nt_ProtectMemory(
                    NtCurrentProcess(),
                    &ImportDescriptor->Name,
                    1,
                    PAGE_EXECUTE_READWRITE,
                    &Protect
                );
            }
        }

        break;
    }

    return STATUS_SUCCESS;
}

NTSTATUS HookModuleIAT(MODULE_MAP *ModuleMap, PVOID ModuleToRedirect)
{
    MODULE_MAP_ENTRY *Entry;

    Entry = ModuleMap->Entry;
    for (ULONG Count = ModuleMap->Count; Count; ++Entry, --Count)
    {
        RedirectModuleIAT(
            ModuleToRedirect,
            Entry->OriginalBase,
            Entry->MappedBase,
            Entry->SizeOfImage,
            Entry->ModuleName,
            RMI_REMOVE_IAT
        );
    }

    return STATUS_SUCCESS;
}

BOOL InitHooks(PVOID BaseAddress)
{
    ULONG       Length;
    ULONG_PTR   ExeBase, NewExeBase, Offset, SelfOffset;
    PVOID       ChkPlg, OriginalBase;
    PVOID       NtdllBase, NewNtdllIATBase;
    PVOID       NewGdi32Base, NewUser32Base;
    PVOID       NtCreateThreadAddress;
    PVOID       NtCreateThreadExAddress;
    PVOID       LdrInitializeThunkAddress;
    WCHAR       FullDllBuffer[MAX_NTPATH];
    PLDR_MODULE ImportUser32, ImportGdi32;

    static CHAR  Gdi32AnsiName[]    = "GDI32.dll";
    static CHAR  User32AnsiName[]   = "USER32.dll";
    static WCHAR Gdi32DllName[]     = L"GDI32.dll";
    static WCHAR User32DllName[]    = L"USER32.dll";

    CMem::CreateGlobalHeap();

    OriginalBase = (PVOID)g_NtCreateThread;
    SelfOffset   = -PtrOffset(BaseAddress, OriginalBase);
    *(PVOID *)((ULONG_PTR)CMem::GetAddressOfGlobalHeap() + SelfOffset) = CMem::GetGlobalHeap();

    ExeBase = (ULONG_PTR)Nt_GetExeModuleHandle();
    NtdllBase = GetNtdllHandle();

#if USE_DYNAMIC_EXE
    ReLoadDll(Nt_CurrentPeb()->ProcessParameters->ImagePathName.Buffer, (PVOID *)&NewExeBase);
#else
    NewExeBase = ExeBase;
#endif

    Offset = NewExeBase - ExeBase;
//    RelocateNewExe(NewExeBase, Offset);
    ChkPlg = BypassCheckPluginOnDisk;

#pragma push_macro("ADD_OFFSET")
#undef ADD_OFFSET
#define ADD_OFFSET(_RVA, _BASE, _OFFSET) \
            PATCH_MEMORY((_OFFSET) + *(PULONG_PTR)((_RVA) + (_BASE)), 4, (_RVA))

    MEMORY_PATCH p[] =
    {
        // old base
        PATCH_MEMORY(0xB8,                  1, 0x001C0A),   // bypass load tpm
        PATCH_MEMORY(0xB8,                  1, 0x18A230),   // bypass create temp folder
//        PATCH_MEMORY(0xBC,                  1, 0x2D850C),   // create toolbarwindows32
        PATCH_MEMORY(ChkPlg,                5, 0x19EC90),   // find plg in root
        PATCH_MEMORY(ChkPlg,                5, 0x19ED5E),   // find plg in system
        PATCH_MEMORY(ChkPlg,                5, 0x19EE2E),   // find plg in plugins
        PATCH_MEMORY(MemStreamSeek,         4, 0x383C38 + NewExeBase - ExeBase),
        PATCH_MEMORY(MemStreamRead,         4, 0x383C3C + NewExeBase - ExeBase),
        PATCH_MEMORY(MemStreamWrite,        4, 0x383C40 + NewExeBase - ExeBase),
        PATCH_MEMORY(MemStreamGetSize,      4, 0x383C48 + NewExeBase - ExeBase),

#if USE_DYNAMIC_EXE
        PATCH_MEMORY(0x000000BC,            4, 0x1B9AF9),   // anti TVPGetFunctionExporter
        PATCH_MEMORY(0x75,                  1, 0x17E456 + NewExeBase - ExeBase),   // call [NULL] -> ExtractionFilter
        PATCH_MEMORY(0xB8,                  1, 0x18A230 + NewExeBase - ExeBase),   // bypass create temp folder
#else
        PATCH_MEMORY(0x75,                  1, 0x17E456),   // call [NULL] -> ExtractionFilter
#endif
        PATCH_MEMORY(0xBC,                  1, 0x2073B5),   // anti TVPCreateStream

        ADD_OFFSET(0x1BD46B, ExeBase, Offset),      // redirect load plugin
        ADD_OFFSET(0x1231A0, ExeBase, Offset),      // redirect call TVPGetFunctionExporter
        ADD_OFFSET(0x1B9F7C, ExeBase, Offset),      // redirect call TVPGetFunctionExporter
        ADD_OFFSET(0x1B9AFA, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x38AF74, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x38AF78, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x389ACC, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x10A4F0, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x10CB46, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x10CC68, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x124055, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x179BF4, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x179CC2, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x17A984, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x188CD5, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x189410, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x18943A, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x1B9C69, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x1BC606, ExeBase, Offset),      // anti TVPCreateStream
        ADD_OFFSET(0x19DB22, ExeBase, Offset),      // anti xp3dumper mode1
        ADD_OFFSET(0x193A25, ExeBase, Offset),      // anti call xp3dumper mode1
        ADD_OFFSET(0x194153, ExeBase, Offset),      // anti call xp3dumper mode1
        ADD_OFFSET(0x1972D5, ExeBase, Offset),      // anti call xp3dumper mode1
        ADD_OFFSET(0x19DD59, ExeBase, Offset),      // create mem stream
        ADD_OFFSET(0x11FB14, ExeBase, Offset),      // func VideoOverlay

        // new exe
        ADD_OFFSET(0x17A8EB, NewExeBase, Offset),   // disk stm vtbl offset
        ADD_OFFSET(0x37EDB4, NewExeBase, Offset),   // disk stm vtbl_init addr
        ADD_OFFSET(0x17DA5C, NewExeBase, Offset),   // mem stm vtbl offset
        ADD_OFFSET(0x37ED78, NewExeBase, Offset),   // mem stm vtbl_read addr

        PATCH_MEMORY(Krkr2TJSBinaryStreamRead,  4, 0x37ED78),

#if USE_RELOAD_DLL
        PATCH_MEMORY(HookGetProcAddress,        4, 0x479468),
#endif // USE_RELOAD_DLL
    };

#pragma pop_macro("ADD_OFFSET")

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

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK(NtCreateThreadAddress,      HookNtCreateThread,     OldNtCreateThread),
        INLINE_HOOK(NtCreateThreadExAddress,    HookNtCreateThreadEx,   OldNtCreateThreadEx),
        INLINE_HOOK(LdrLoadDll,                 HookLdrLoadDll,         OldLdrLoadDll),
        INLINE_HOOK(LdrInitializeThunkAddress,  LdrpInitialize,         OldLdrpInitialize),

//        PATCH_FUNCTION(CALL, NOT_RVA, 0x18A277 + ExeBase, (PVOID)((ULONG_PTR)CreateTempDllStreamNaked + SelfOffset)),
//#if USE_DYNAMIC_EXE
        PATCH_FUNCTION(JUMP, NOT_RVA, NULL,                  ExtractionFilter),
        PATCH_FUNCTION(CALL, NOT_RVA, 0x123060 + NewExeBase, HookLoadLibraryA),
        PATCH_FUNCTION(CALL, NOT_RVA, 0x1B9E4B + NewExeBase, HookLoadLibraryA),
        PATCH_FUNCTION(CALL, NOT_RVA, 0x18A277 + NewExeBase, (PVOID)((ULONG_PTR)CreateTempFileStreamNaked + SelfOffset)),
//#endif
    };

    *(PULONG_PTR)&Krkr2TJSBinaryStreamReadFunc = NewExeBase + 0x17E3C4;

#if USE_DYNAMIC_SELF
    NewNtdllIATBase = NULL;
    RebuildNtdll(Nt_CurrentPeb(), (ULONG_PTR)BaseAddress, NewNtdllIATBase);
#endif

    NewNtdllIATBase = (PVOID)1;
    Nt_AllocateMemory(NtCurrentProcess(), &NewNtdllIATBase, MEMORY_PAGE_SIZE);

    Nt_PatchMemory(p, countof(p), f, countof(f), (PVOID)ExeBase);
    Nt_FindLdrModuleByHandle(OriginalBase)->EntryPoint = TrueDllEntry;

#if USE_RELOAD_DLL

    Length = Nt_GetSystemDirectory(FullDllBuffer, ARRAYSIZE(FullDllBuffer));

    ImportGdi32     = Nt_FindLdrModuleByName(&WCS2US(Gdi32DllName));
    ImportUser32    = Nt_FindLdrModuleByName(&WCS2US(User32DllName));

    CopyStruct(FullDllBuffer + Length, Gdi32DllName, sizeof(Gdi32DllName));
    ReLoadDll(FullDllBuffer, &NewGdi32Base, ImportGdi32->BaseAddress);

    CopyStruct(FullDllBuffer + Length, User32DllName, sizeof(User32DllName));
    ReLoadDll(FullDllBuffer, &NewUser32Base, ImportUser32->BaseAddress);

    g_ModuleMap.Count = 2;
    g_ModuleMap.Entry = new MODULE_MAP_ENTRY[2];
    g_ModuleMap.Entry[0].OriginalBase   = ImportGdi32->BaseAddress;
    g_ModuleMap.Entry[0].MappedBase     = NewGdi32Base;
    g_ModuleMap.Entry[0].ModuleName     = Gdi32AnsiName;
    g_ModuleMap.Entry[0].SizeOfImage    = ImportGdi32->SizeOfImage;
    g_ModuleMap.Entry[1].OriginalBase   = ImportUser32->BaseAddress;
    g_ModuleMap.Entry[1].MappedBase     = NewUser32Base;
    g_ModuleMap.Entry[1].ModuleName     = User32AnsiName;
    g_ModuleMap.Entry[1].SizeOfImage    = ImportUser32->SizeOfImage;

    HookModuleIAT(&g_ModuleMap, NewGdi32Base);
    HookModuleIAT(&g_ModuleMap, NewUser32Base);
    HookModuleIAT(&g_ModuleMap, (PVOID)ExeBase);

#if USE_DYNAMIC_EXE
    HookModuleIAT(&g_ModuleMap, (PVOID)NewExeBase);
#endif

#endif  // USE_RELOAD_DLL

    return TRUE;
}

BOOL WINAPI TrueDllEntry(HINSTANCE hInstance, ULONG Reason, PVOID Reserved)
{
    RTL_THREAD_FRAME *Frame;

    UNREFERENCED_PARAMETER(Reserved);

    switch (Reason + 1)
    {
        case DLL_PROCESS_ATTACH + 1:
            break;

        case DLL_THREAD_ATTACH + 1:
            if (Nt_FindThreadFrameByContext(THREAD_START_PARAMETER_MAGIC) == NULL)
            {
                Nt_FreeMemory(NtCurrentProcess(), (PVOID)1);
            }
            break;

        case DLL_THREAD_DETACH + 1:
            Frame = Nt_FindThreadFrameByContext(THREAD_START_PARAMETER_MAGIC);
            if (Frame != NULL && Frame != &SystemThreadParameter)
            {
                RtlPopFrame(Frame);
                CMem::FreeMemory(Frame);
            }
            break;

        case DLL_PROCESS_DETACH + 1:
            CMem::DestroyGlobalHeap();
            break;

        case DLL_INIT_HOOKS + 1:
            return InitHooks(hInstance);
    }

    return TRUE;
}

ASM VOID PreTrueDllEntry()
{
    INLINE_ASM
    {
        lea esp, [esp - 10h];
        mov eax, [esp]DLL_MAIN_PARAMETERS.Reserved;
        mov [esp]DLL_MAIN_PARAMETERS.ReturnAddress, eax;
        jmp TrueDllEntry;
    }
}

BOOL Init(PVOID AddressOfDllMain, PVOID BaseAddress)
{
    PVOID                NewSelfBase;
    ULONG_PTR            Offset;
    PLDR_MODULE          LdrModule;
    DLL_MAIN_PARAMETERS *DllMainParameters;

    DllMainParameters   = (DLL_MAIN_PARAMETERS *)AddressOfDllMain;
    LdrModule           = Nt_FindLdrModuleByHandle(BaseAddress);

#if USE_DYNAMIC_SELF
    ReLoadDll(LdrModule->FullDllName.Buffer, &NewSelfBase);
#else
    NewSelfBase = BaseAddress;
#endif

    Offset = (ULONG_PTR)NewSelfBase - (ULONG_PTR)BaseAddress;

    LdrModule->EntryPoint               = (PVOID)PtrAdd(Offset, LdrModule->EntryPoint);
    DllMainParameters->Reserved         = DllMainParameters->ReturnAddress;
    DllMainParameters->BaseAddress      = NewSelfBase;
    DllMainParameters->Reason           = DLL_INIT_HOOKS;

    *(PULONG_PTR)PtrAdd(&g_NtCreateThread, Offset) = (ULONG_PTR)BaseAddress;

#if !USE_UPX

    DllMainParameters->ReturnAddress = (PVOID)PtrAdd(PreTrueDllEntry, Offset);

#else // USE_UPX

    ((PBYTE)LdrModule->EntryPoint)[4] = -1;
    ((DllMainRoutine)LdrModule->EntryPoint)((HINSTANCE)NewSelfBase, -1, 0);
    ((PBYTE)LdrModule->EntryPoint)[4] = 1;

    *(PULONG_PTR)((ULONG_PTR)LdrModule->EntryPoint + 0x2B5) += PtrOffset(PreTrueDllEntry, DllMain);
    DllMainParameters->ReturnAddress = LdrModule->EntryPoint;

#endif

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, PVOID Reserved)
{
    UNREFERENCED_PARAMETER(Reserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Init(_AddressOfReturnAddress(), hInstance);

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

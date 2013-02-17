#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")
#pragma comment(linker, "/EXPORT:RunEngine=_RunEngine@8")

#include "tcm.h"
#include "MyLibrary.cpp"
#include "HandleTable.cpp"
#include "mlns.h"

OVERLOAD_CPP_NEW_WITH_HEAP(MemoryAllocator::GetGlobalHeap())

MlHandleTable*  g_TextTable;
MlHandleTable*  g_FileStreamTable;
PVOID           g_TextBuffer;

PStlString  (STDCALL *StubVM_PushString)(ULONG SrbOffset);
VOID        (CDECL *StubCacheFile)(PMemoryStream *Stream, PVOID, PStlString Name);
VOID        (CDECL *Stubthfree)(PVOID Block);

VOID CDECL CacheFile(PStlString Name)
{
    PMemoryStream*  Stream;
    PSTR            FileName;

    INLINE_ASM mov Stream, ecx;

    FileName = findnamea(Name->GetBuffer());

    if (!StrICompareA(findexta(FileName), ".srb"))
        g_FileStreamTable->Insert(*Stream)->Handle = (PVOID)HashStringLowerT(FileName);

    INLINE_ASM
    {
        push    Name;
        mov     ecx, Stream;
        call    StubCacheFile;
    }
}

VOID CDECL thfree(PVOID Block)
{
    g_FileStreamTable->Remove(Block);
    return Stubthfree(Block);
}

ULONG
FASTCALL
MemoryStream_Read(
    PVOID           ReadRoutine,
    PMemoryStream   TargetStream,
    PFileObject2    File,
    PVOID           Buffer,
    ULONG           BlockSize,
    ULONG           BlockCount
)
{
    ULONG BlockRead;
    ULONG (STDCALL *Read)(PFileObject2 File, PVOID Buffer, ULONG BlockSize, ULONG BlockCount);

    *(PVOID *)&Read = ReadRoutine;

    BlockRead = Read(File, Buffer, BlockSize, BlockCount);

    TargetStream->Hash = (ULONG)g_FileStreamTable->Lookup(File->File.Stream)->Handle;

    return BlockRead;
}

NAKED ULONG NakedMemoryStream_Read(ULONG BlockCount)
{
    INLINE_ASM
    {
        push    [esp + 04h];
        push    ebx;
        push    eax;
        push    ebp;
        call    MemoryStream_Read;
        ret     4;
    }
}

ULONG FASTCALL LookupTranslatedOffset(PMemoryStream Srb, ULONG SrbOffset)
{
    MlHandleTable          *TextTable, *SubTable;
    PML_HANDLE_TABLE_ENTRY  Entry;
    PTEXTBIN_ENTRY          Text;
    ULONG                   NewOffset;

    TextTable = g_TextTable;

    NewOffset = ~0u;

    LOOP_ONCE
    {
        if (TextTable == NULL)
            break;

        Entry = TextTable->Lookup(Srb->Hash);
        if (Entry == NULL)
            break;

        SubTable = (MlHandleTable *)Entry->Handle;
        Entry = SubTable->Lookup(SrbOffset);
        if (Entry == NULL)
            break;

        Text = (PTEXTBIN_ENTRY)Entry->Handle;
        if (Text == NULL)
            break;

        NewOffset = PtrOffset(Text->Text, Srb->Begin);
    }

    return NewOffset;
}

NAKED PStlString STDCALL VM_PushString(ULONG SrbOffset)
{
    INLINE_ASM
    {
        mov     ecx, [edi + 40h];
        mov     ecx, [ecx - 0Ch];
        mov     edx, [esi];
        call    LookupTranslatedOffset;
        inc     eax;

        jnz     TRANS_FOUND;
        jmp     StubVM_PushString;

TRANS_FOUND:

        push    ebx;
        push    edi;

        lea     eax, [eax - 01h];

        mov     ebx, [esi];
        mov     [esi], eax;
        push    [esp + 0Ch];
        call    StubVM_PushString;
        mov     edx, eax;

        or      ecx, -1;
        xor     eax, eax;
        mov     edi, [esp + 0Ch];
        lea     edi, [edi + ebx];
        repne   scasb;
        not     ecx;
        lea     ebx, [ebx + ecx];
        mov     [esi], ebx;

        mov     eax, edx;

        pop     edi;
        pop     ebx;
        ret     4;
    }
}

VOID DestroyTextTable()
{
    MlHandleTable *TextTable;

    TextTable = g_TextTable;
    if (TextTable == NULL)
        return;

    TextTable->Destroy(
        HandleTableDestroyM(Entry, Count, Context)
        {
            MlHandleTable *SubTable;

            for (; Count; ++Entry, --Count)
            {
                SubTable = (MlHandleTable *)Entry->Handle;
                delete SubTable;
            }

            return STATUS_SUCCESS;
        },
        0
    );

    delete TextTable;

    FreeMemoryP(g_TextBuffer);

    g_TextBuffer = NULL;
    g_TextTable = NULL;
}

NTSTATUS InitTextBin()
{
    WCHAR           MiraiText[MAX_NTPATH];
    NtFileMemory    bin;
    PVOID           Buffer;
    ULONG_PTR       CompressedSize, UncompressedSize;
    NTSTATUS        Status;
    PTEXTBIN_HEADER Header, End;
    PTEXTBIN_ENTRY  Entry;
    MlHandleTable  *TextTable, *SubTable;
    PML_HANDLE_TABLE_ENTRY  HtEntry;

    TextTable = new MlHandleTable;
    if (TextTable == NULL)
        return STATUS_NO_MEMORY;

    if (TextTable->Create() == NULL)
    {
        delete TextTable;
        return STATUS_NO_MEMORY;
    }

    g_TextTable = TextTable;

    SCOPE_EXIT
    {
        if (NT_FAILED(Status))
        {
            DestroyTextTable();
        }
    }
    SCOPE_EXIT_END;

    Status = bin.Open(L"tcm.bin");
    FAIL_RETURN(Status);

    Status = STATUS_NO_MEMORY;

#if 0

    CompressedSize = *(PULONG)bin.GetBuffer();
    UncompressedSize = *((PULONG)bin.GetBuffer() + 1);

    Buffer = AllocateMemoryP(UncompressedSize);
    if (Buffer == NULL)
        return Status;

    UCL_NRV2E_Decompress(PtrAdd(bin.GetBuffer(), 8), CompressedSize, Buffer, &UncompressedSize);
#else

    UncompressedSize = bin.GetSize32();

    Buffer = AllocateMemoryP(UncompressedSize);
    if (Buffer == NULL)
        return Status;

    CopyMemory(Buffer, bin.GetBuffer(), UncompressedSize);

#endif

    g_TextBuffer = Buffer;

    Header  = (PTEXTBIN_HEADER)Buffer;
    End     = PtrAdd(Header, UncompressedSize);

    while (Header < End)
    {
        SubTable = new MlHandleTable;
        if (SubTable == NULL)
            return Status;

        if (SubTable->Create() == NULL)
            return Status;

        HtEntry = TextTable->Insert(Header->Hash);
        if (HtEntry == NULL)
            return Status;

        HtEntry->Handle = SubTable;

        Entry = Header->Entry;
        for (ULONG_PTR Count = Header->Count; Count; --Count)
        {
            HtEntry = SubTable->Insert(Entry->Offset);
            if (HtEntry == NULL)
                return Status;

            HtEntry->Handle = Entry;
            Entry = Entry->Next();
        }

        Header = (PTEXTBIN_HEADER)Entry;
    }

    Status = STATUS_SUCCESS;

    return Status;
}

#if DBG_ON

NtFileDisk logfile;
RTL_CRITICAL_SECTION cs;

#include "SectionProtector.h"

TYPE_OF(malloc) *gmalloc;

PVOID CDECL galloc(ULONG_PTR size)
{
    PVOID mem = gmalloc(size);

    if (mem != NULL && size == 0x10)
    {
        PROTECT_SECTION(&cs)
        {
            logfile.Print(NULL, L"%p @ %p\r\n", mem, _ReturnAddress());
        }
    }

    return mem;
}

#endif

EXTC VOID STDCALL RunEngine(PSTR CommandLine, HICON Icon)
{
    PVOID Engine;
    TYPE_OF(RunEngine) *RunEngine;

    ml::MlInitialize();

    SetExeDirectoryAsCurrent();

    Engine = LoadDll(L"Engine.dll");
    if (Engine == NULL)
        return;

    LOOP_ONCE
    {
        if (NT_FAILED(InitTextBin()))
            break;

        g_FileStreamTable = new MlHandleTable;
        if (g_FileStreamTable == NULL)
            break;

        if (g_FileStreamTable->Create() == NULL)
            break;

#if DBG_ON

        RtlInitializeCriticalSectionAndSpinCount(&cs, 4000);
        logfile.Create(L"log.txt");
        ULONG BOM = BOM_UTF16_LE;
        logfile.Write(&BOM, 2);

#endif

        MEMORY_PATCH p[] =
        {
            PATCH_MEMORY(GB2312_CHARSET,    1, 0x8E9EF),
            PATCH_MEMORY("system_cn.ini",   4, 0x16C2C0),

            // PATCH_MEMORY(0x14,              1, 0x07A326),   // mem obj size add 4   compressed
            // PATCH_MEMORY(0x14,              1, 0x07A3AF),   // mem obj size add 4   uncompressed
            // PATCH_MEMORY(0x14,              1, 0x07A600),   // mem obj size add 4   disk file
            PATCH_MEMORY(0x14,              1, 0x0B9964),   // mem obj size add 4   create mem srb stream
            // PATCH_MEMORY(0x14,              1, 0x07AA5D),   // mem obj size add 4   cached compressed
            // PATCH_MEMORY(0x14,              1, 0x07AAFA),   // mem obj size add 4   cached uncompressed
        };

        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_CALL_RVA_NULL(0x0B99BF, NakedMemoryStream_Read),

            INLINE_HOOK_JUMP_RVA(0x07A750,  CacheFile,      StubCacheFile),
            INLINE_HOOK_CALL_RVA(0x0B9BCE,  thfree,         Stubthfree),
            INLINE_HOOK_CALL_RVA(0x0AE1A9,  VM_PushString,  StubVM_PushString),
            // INLINE_HOOK_JUMP_RVA(0x7A0F0,   LoadFile,       StubLoadFile),
            // INLINE_HOOK_JUMP_RVA(0x7A8D0,   LoadFile2,      StubLoadFile2),
            // INLINE_HOOK_JUMP_RVA(0xD1B7C,   galloc,         gmalloc),
        };

        Nt_PatchMemory(p, countof(p), f, countof(f), Engine);
    }

    *(PVOID *)&RunEngine = GetRoutineAddress(Engine, "RunEngine");
    if (RunEngine == NULL)
        return;

    // BOM = 0xFEEB;
    // WriteProtectMemory(CurrentProcess, PtrAdd(Engine, 0x7A8D0), &BOM, 2);

    return RunEngine(CommandLine, Icon);
}

BOOL UnInitialize(PVOID BaseAddress)
{
    DestroyTextTable();
    delete g_FileStreamTable;

    return FALSE;
}

BOOL Initialize(PVOID BaseAddress)
{
    return TRUE;
}

BOOL WINAPI DllMain(PVOID BaseAddress, ULONG Reason, PVOID Reserved)
{
    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Initialize(BaseAddress) || UnInitialize(BaseAddress);

        case DLL_PROCESS_DETACH:
            UnInitialize(BaseAddress);
            break;
    }

    return TRUE;
}

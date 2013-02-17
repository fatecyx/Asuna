#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")
#pragma comment(linker, "/EXPORT:Direct3DCreate9=d3d9.Direct3DCreate9")

#include "th135.h"
#include "MyLibrary.cpp"
#include "mlns.h"

HANDLE          g_PakcnHandle;
PTH135_PAKCN    g_Pak;

UncompressTFBMRoutine   StubUncompressTFBM;
PVOID                   StubReadACT1;

PTH135_PAKCN_ENTRY LookupFileEntry(ULONG Hash)
{
    PTH135_PAKCN_ENTRY Entry;

    Entry = BinarySearch(g_Pak->Entry, g_Pak->Entry + g_Pak->Count, Hash,
                [] (PTH135_PAKCN_ENTRY Entry, ULONG Hash, ULONG_PTR) -> LONG_PTR
                {
                    return Entry->Hash < Hash ? -1 : Entry->Hash > Hash ? 1 : 0;
                },
                0
            );

    return Entry;
}

VOID CopyFileInfoToPakObjectAndReset(PakFileObject *Pak, PTH135_PAKCN_ENTRY Entry)
{
    Pak->FileInfo.DecKeyIndex   = 4;
    Pak->FileInfo.Hash          = Entry->Hash;
    Pak->FileInfo.Offset        = Entry->Offset;
    Pak->FileInfo.Size          = Entry->Size;

    CopyStruct(Pak->FileInfo.DecryptKey, Entry->Key, sizeof(Entry->Key));
    *(PULONG)&Pak->FileInfo.DecryptKeyPad = *(PULONG)&Entry->Key[0];

    Pak->BufferSize     = 0;
    Pak->Size           = 0;
    Pak->CurrentOffset  = 0;
}

VOID FASTCALL BeforeReadCsv(PakFileObject *Pak)
{
    HANDLE PakHandle;
    PTH135_PAKCN_ENTRY  Entry;

    Entry = LookupFileEntry(Pak->FileInfo.Hash);
    if (Entry == NULL)
        return;

    PakHandle = Pak->FileHandle;
    NtClose(PakHandle);

    CopyFileInfoToPakObjectAndReset(Pak, Entry);

    Pak->FileInfo.DecKeyIndex = 4;

    NtDuplicateObject(CurrentProcess, g_PakcnHandle, CurrentProcess, &Pak->FileHandle, 0, 0, DUPLICATE_SAME_ACCESS);
    NtFileDisk::Seek(Pak->FileHandle, Entry->Offset + 4, FILE_BEGIN);
}

NAKED VOID NakedBeforeReadCsv()
{
    INLINE_ASM
    {
        lea     ecx, dword ptr [ebp+0xFFFEFFB0];
        push    ecx;
        push    eax;
        call    BeforeReadCsv;
        pop     eax;
        pop     ecx;
        ret;
    }
}

BOOLEAN
FASTCALL
UncompressTFBM(
    PakFileObject*      Pak,
    PVOID,
    PTH135_IMAGE_OBJECT ImageObject,
    PULONG              FileMagic
)
{
    HANDLE              PakHandle;
    BOOLEAN             Success;
    TH135_PAKCN_ENTRY   LocalEntry;
    PTH135_PAKCN_ENTRY  Entry;

    Entry = LookupFileEntry(Pak->FileInfo.Hash);
    if (Entry == NULL)
        return StubUncompressTFBM(Pak, NULL, ImageObject, FileMagic);

    auto FileInfo = Pak->FileInfo;

    PakHandle = Pak->FileHandle;

    CopyFileInfoToPakObjectAndReset(Pak, Entry);

    Pak->FileInfo.DecKeyIndex = 4;

    Pak->BufferSize     = 0;
    Pak->Size           = 0;
    Pak->FileHandle     = g_PakcnHandle;
    Pak->CurrentOffset  = 0;

    NtFileDisk::Seek(Pak->FileHandle, Entry->Offset + 4, FILE_BEGIN);

    Success = StubUncompressTFBM(Pak, NULL, ImageObject, FileMagic);

    Pak->FileInfo       = FileInfo;
    Pak->FileHandle     = PakHandle;
    Pak->BufferSize     = 0;
    Pak->Size           = 0;
    Pak->CurrentOffset  = 0;

    return Success;
}

VOID CDECL ReadACT1(PakFileObject2 *Pak)
{
    PTH135_PAKCN_ENTRY Entry;

    LOOP_ONCE
    {
        if (Pak == NULL)
            break;

        Entry = LookupFileEntry(Pak->Pak.FileInfo.Hash);
        if (Entry == NULL)
            break;

        CopyFileInfoToPakObjectAndReset(&Pak->Pak, Entry);

        Pak->Pak.FileInfo.DecKeyIndex = 0;

        NtClose(Pak->Pak.FileHandle);
        NtDuplicateObject(CurrentProcess, g_PakcnHandle, CurrentProcess, &Pak->Pak.FileHandle, 0, 0, DUPLICATE_SAME_ACCESS);
        NtFileDisk::Seek(Pak->Pak.FileHandle, Entry->Offset, FILE_BEGIN);
    }

    *(PVOID *)_AddressOfReturnAddress() = StubReadACT1;
}

HFONT WINAPI ThCreateFontA(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, PCSTR pszFaceName)
{
    return CreateFontW(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, GB2312_CHARSET, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, L"ºÚÌå");
}

BOOL UnInitialize(PVOID BaseAddress)
{
    FreeMemory(g_Pak);
    g_Pak = NULL;

    if (g_PakcnHandle != NULL)
    {
        NtClose(g_PakcnHandle);
        g_PakcnHandle = NULL;
    }

    return FALSE;
}

BOOL Initialize(PVOID BaseAddress)
{
    LdrDisableThreadCalloutsForDll(BaseAddress);

    NTSTATUS Status;

    Status = STATUS_SUCCESS;

    LOOP_ONCE
    {
        NtFileDisk      Pak;
        PLDR_MODULE     ExeModule;
        PWSTR           PakcnPath;
        ULONG           Length;
        PTH135_PAKCN    PakBuffer;

        ExeModule = FindLdrModuleByHandle(NULL);

        Length = ExeModule->FullDllName.Length;
        PakcnPath = (PWSTR)AllocStack(Length + sizeof(PakcnPath));
        Length -= ExeModule->BaseDllName.Length;

        swprintf(PakcnPath, L"%.*s%s", Length / sizeof(WCHAR), ExeModule->FullDllName.Buffer, L"th135cn.pak");

        Status = Pak.Open(PakcnPath);
        FAIL_BREAK(Status);

        Status = Pak.Read(&Length, sizeof(PakBuffer->Count));
        FAIL_BREAK(Status);

        Length = (Length * sizeof(PakBuffer->Entry[0])) + sizeof(*PakBuffer) - sizeof(PakBuffer->Entry);

        PakBuffer = (PTH135_PAKCN)AllocateMemory(Length);
        if (PakBuffer == NULL)
        {
            Status = STATUS_NO_MEMORY;
            break;
        }

        g_Pak = PakBuffer;

        Pak.Rewind();

        Status = Pak.Read(PakBuffer, Length);
        FAIL_BREAK(Status);

        qsort(PakBuffer->Entry, PakBuffer->Count, sizeof(PakBuffer->Entry),
            [] (const void *entry1, const void *entry2) -> int
            {
                PTH135_PAKCN_ENTRY ent1, ent2;

                ent1 = (PTH135_PAKCN_ENTRY)entry1;
                ent2 = (PTH135_PAKCN_ENTRY)entry2;

                return ent1->Hash < ent2->Hash ? -1 : ent1->Hash > ent2->Hash ? 1 : 0;
            }
        );

        Status = NtDuplicateObject(CurrentProcess, Pak, CurrentProcess, &g_PakcnHandle, 0, 0, DUPLICATE_SAME_ACCESS);
    }

    if (NT_FAILED(Status))
    {
        UnInitialize(BaseAddress);
        return TRUE;
    }

    BaseAddress = Ldr::GetExeModuleHandle();

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY("–|·½ÐÄ¾_Â¥",      4, 0x00F9F0),
        PATCH_MEMORY(GB2312_CHARSET,    4, 0x2D7FBA),
        PATCH_MEMORY(ThCreateFontA,     4, IATLookupRoutineRVAByHashNoFix(BaseAddress, GDI32_CreateFontA)),
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_JUMP_RVA(0x19F080, UncompressTFBM,  StubUncompressTFBM),
        PATCH_FUNCTION(CALL, AUTO_DISASM2 | FORCE_JUMP_BACK, 0x298BE4, ReadACT1, 0, &StubReadACT1),

        INLINE_HOOK_CALL_RVA_NULL(0x1A6044, NakedBeforeReadCsv),
    };

    Nt_PatchMemory(p, countof(p), f, countof(f), BaseAddress);

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

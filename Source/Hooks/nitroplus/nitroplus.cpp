#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(linker, "/EXPORT:MakeSureDirectoryPathExists=imagehlp.MakeSureDirectoryPathExists")

#include "nitroplus.h"
#include "NitroPlusStub.h"

#include "MyLibraryUser.cpp"
#include "cxdec.cpp"
#include "AntiDebug.cpp"

OVERLOAD_CPP_NEW_WITH_HEAP(MemoryAllocator::GetGlobalHeap())

PNITRO_PLUS_INFO g_NpInfo;

ULONG ConvertShiftJisToGbk(PSTR Source, PSTR Destination, ULONG Length = ~0u, BOOL Reverse = FALSE)
{
    PWSTR               Unicode;
    PNITRO_PLUS_INFO    NpInfo;
    PCPTABLEINFO        SourceCP, DestinationCP;

    NpInfo = g_NpInfo;

    if (Length == -1)
        Length = StrLengthA(Source);

    if (!Reverse && !IsShiftJISString(Source, Length))
    {
        if (Source != Destination)
        {
            CopyMemory(Destination, Source, Length);
            Destination[Length] = 0;
        }

        return Length;
    }

    Unicode = (PWSTR)AllocStack(Length * sizeof(WCHAR));

    if (Reverse)
    {
        SourceCP        = &NpInfo->CpTable936;
        DestinationCP   = &NpInfo->CpTable932;
    }
    else
    {
        SourceCP        = &NpInfo->CpTable932;
        DestinationCP   = &NpInfo->CpTable936;
    }

    RtlCustomCPToUnicodeN(
        SourceCP,
        Unicode,
        Length * sizeof(WCHAR),
        &Length,
        Source,
        Length
    );

    RtlUnicodeToCustomCPN(
        DestinationCP,
        Destination,
        MAX_NTPATH,
        &Length,
        Unicode,
        Length
    );

    Destination[Length] = 0;

    return Length;
}

ULONG
NpHashBuffer(
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

ULONG
FASTCALL
HashFilePathWorker(
    PSTR                    FileName,
    PNITRO_PLUS_FILE_ENTRY  FileEntry,
    PNPA_HEADER_INFO        NpaHeader
)
{
    ULONG Hash, Hash2;

    Hash        = NpHashBuffer(FileName, StrLengthA(FileName));
    FileName    = (PSTR)_AddressOfReturnAddress() + 0x28;
    Hash2       = NpHashBuffer(FileName, StrLengthA(FileName));

    FileEntry->ShiftJisHash = (Hash2 + (NpaHeader->Hash[0] * NpaHeader->Hash[1])) * FileEntry->FileSize;

    return Hash;
}

NAKED ULONG HashFilePath()
{
    INLINE_ASM
    {
        mov     ecx, eax;
        mov     edx, ebp;
        push    esi;
        call    HashFilePathWorker;
        ret;
    }
}

NAKED VOID NpGetFileNameHash()
{
    INLINE_ASM
    {
        mov ecx, [ebx]PNITRO_PLUS_FILE_ENTRY.ShiftJisHash;
        jmp StubNpGetFileNameHash;
    }
}

PVOID CDECL ConvertFileNameEncoding(PSTR Destination, PSTR Source, ULONG Length)
{
    ConvertShiftJisToGbk(Source, Destination, Length);
    return Destination;
}

BOOL CDECL NpNpaReader(PNITRO_PLUS_FILE_STREAM Stream)
{
    BOOL                Success;
    ULONG               Length;
    PSTR                Extension, Script;
    PNITRO_PLUS_INFO    NpInfo;

    Success = StubNpNpaReader(Stream);
    if (!Success)
        return Success;

    Length = Stream->FileSize;
    if (Length < 2 || Stream->Buffer == NULL)
        return Success;

    Extension = findexta(Stream->FileName);
    if (Extension == Stream->FileName)
        return Success;

    if ((*(PULONG)(Extension + 1) & 0xFFDFDFDF) != TAG3('NSS'))
        return Success;

    if (*(PUSHORT)Stream->Buffer != BOM_UTF16_LE)
    {
        ConvertShiftJisToGbk((PSTR)Stream->Buffer, (PSTR)Stream->Buffer, Length);
        return Success;
    }

    NpInfo = g_NpInfo;

    RtlUnicodeToCustomCPN(
        &NpInfo->CpTable936,
        (PSTR)Stream->Buffer,
        Length,
        &Length,
        (PWSTR)Stream->Buffer + 1,
        Length - sizeof(WCHAR)
    );

    Stream->FileSize = Length;
    ((PSTR)Stream->Buffer)[Length] = 0;

    Script = (PSTR)Stream->Buffer;
    for (ULONG Count = Length; Count; --Count)
    {
        LONG ch = *Script++;

        if (ch >= 0)
            continue;

        --Count;

        ch = (ch << 8) | (BYTE)(*Script++);
        ch &= 0xFFFF;

        if (ch == 0xA1A1)    // Fullwidth space
            *(PUSHORT)&Script[-2] = 0x4081;
    }

    return Success;
}

BOOL NpLoadFile()
{
    ULONG   Length;
    PVOID   FileReader;
    PSTR    FileName, GbkFileName;

    INLINE_ASM
    {
        mov FileName,   edi;
        mov FileReader, eax;
    }

    Length      = StrLengthA(FileName);
    GbkFileName = (PSTR)AllocStack(Length + 1);

    ConvertShiftJisToGbk(FileName, GbkFileName, Length);

    INLINE_ASM
    {
        mov     eax, FileReader;
        mov     edi, GbkFileName;
        call    StubNpLoadFile;
    }
}

BOOL CDECL NpNpaReader2(PNITRO_PLUS_FILE_STREAM Stream)
{
    PSTR                    FileName;
    PVOID                   Buffer;
    ULONG                   Seed, Size;
    NTSTATUS                Status;
    PNITRO_PLUS_INFO        NpInfo;
    ATDBG_IO_REQUEST_PACKET Irp;

    DECL_ALIGN(16) NP_FIND_FILE_INFO FindInfo;

    NpInfo = g_NpInfo;
    Buffer = NULL;

    FileName = Stream->FileName;
    if (FileName[0] == '.')
        FileName += 2;

    Status = NpInfo->npack->FindFile(FileName, &FindInfo);
    if (!NT_SUCCESS(Status))
        goto DEFAULT_READER;

    Size   = FindInfo.FileSize;
    Buffer = AllocateMemory(Size);
    if (Buffer == NULL)
        goto DEFAULT_READER;

    Seed = (ULONG)ReadTimeStampCounter();
    if (Seed & 1)
    {
        Seed = 0;
    }
    else
    {
        Status = Nt_DebugActiveProcess(NpInfo->ParentPid);
        if (NT_SUCCESS(Status))
        {
            Nt_DebugActiveProcessStop(NpInfo->ParentPid);
            Seed = 0;
        }
        else
        {
            ULONG OldProtect;
            PVOID Address       = Nt_ExitProcess;
            PVOID Destination   = PtrAdd(Nt_GetExeModuleHandle(), 0x01593);

            Nt_ProtectMemory(NtCurrentProcess(), Destination, sizeof(Destination), PAGE_EXECUTE_READWRITE, &OldProtect);
            NpInfo->Helper->BuildIoControlRequest(&Irp, &Address, sizeof(Address), Destination, sizeof(Address));
            NpInfo->Helper->SendIoControlRequest(ExceptionWriteMemory, &Irp);
        }
    }

    NpInfo->Helper->BuildIoControlRequest(&Irp, &FindInfo, sizeof(FindInfo), Buffer, Size);
    Status = NpInfo->Helper->SendIoControlRequest(ExceptionReadFileData ^ Seed, &Irp);
    if (!NT_SUCCESS(Status))
        goto DEFAULT_READER;

    Stream->Buffer      = Buffer;
    Stream->FileSize    = Size;

    return TRUE;

DEFAULT_READER:
    if (Buffer != NULL)
        FreeMemory(Buffer);

    return StubNpNpaReader(Stream);
}

BOOL UnInitialize(PVOID BaseAddress)
{
    PNITRO_PLUS_INFO NpInfo;

    UNREFERENCED_PARAMETER(BaseAddress);

    NpInfo = g_NpInfo;
    if (NpInfo != NULL)
    {
        if (NpInfo->CP932 != NULL)
            Nt_FreeMemory(NtCurrentProcess(), NpInfo->CP932);

        if (NpInfo->CP936 != NULL)
            Nt_FreeMemory(NtCurrentProcess(), NpInfo->CP936);

        if (NpInfo->npack != NULL)
            delete NpInfo->npack;
    }

    RtlFreeUnicodeString(&NpInfo->SystemDirectory);

    MemoryAllocator::DestroyGlobalHeap();

    return FALSE;
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

NTSTATUS DetectDebugger()
{
    BOOL                HasDebugger;
    NTSTATUS            Status;
    PNITRO_PLUS_INFO    NpInfo;

    static ULONG Count;

#if ENABLE_ANTI_DEBUG_DEBUG
    HasDebugger = TRUE;
#else
    HasDebugger = StubDetectDebugger() != STATUS_SUCCESS;
#endif

    if (--Count != -3)
    {
        return STATUS_SUCCESS;
    }

    NpInfo = g_NpInfo;

    NpInfo->Helper = new NitruPlusHelper;
    NpInfo->Helper->Initialize(!HasDebugger);
    if (HasDebugger)
    {
        WCHAR PackFile[MAX_NTPATH];
        ATDBG_IO_REQUEST_PACKET Irp;

        NpInfo->npack = new NPackReader;

        NpInfo->Helper->BuildIoControlRequest(&Irp, NULL, 0, PackFile, sizeof(PackFile));
        Status = NpInfo->Helper->SendIoControlRequest(ExceptionQueryPackPath, &Irp);

        if (NT_SUCCESS(Status))
            NpInfo->npack->Open(PackFile);

        NpInfo->Helper->BuildIoControlRequest(&Irp, NULL, 0, &NpInfo->ParentPid, sizeof(NpInfo->ParentPid));
        NpInfo->Helper->SendIoControlRequest(ExceptionQueryDebuggerPid, &Irp);
    }

    Nt_RestoreMemory(&StubDetectDebugger);

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY(0x90C3C033, 4, 0xA2DC0), // IsDeubggerPresent
    };

    Nt_PatchMemory(p, countof(p), NULL, 0, Nt_GetExeModuleHandle());

    return STATUS_SUCCESS;
}

BOOL Initialize(PVOID BaseAddress)
{
    BOOL                Success;
    PNITRO_PLUS_INFO    NpInfo;

    if (MemoryAllocator::CreateGlobalHeap() == NULL)
        return FALSE;

    NpInfo = new NITRO_PLUS_INFO;
    if (NpInfo == NULL)
        return FALSE;

    ZeroMemory(NpInfo, sizeof(*NpInfo));

    g_NpInfo = NpInfo;

//    NpInfo->npack = new NPackReader;
//    NpInfo->npack->Open(L"axanael_cn.npack");

/*

    NTSTATUS            Status;
    WCHAR               SystemDirectory[MAX_NTPATH];
    PWSTR               NlsPath;
    ULONG               Length;

    RtlCreateUnicodeString(&NpInfo->SystemDirectory, SystemDirectory);

    Length = Nt_GetSystemDirectory64(SystemDirectory, countof(SystemDirectory));
    if (Length == NULL)
        return FALSE;

    NlsPath = SystemDirectory;

    Status = InitCodePageTable(
                &NpInfo->CpTable932,
                &NpInfo->CP932,
                L"932",
                NlsPath,
                Length
             );
    if (!NT_SUCCESS(Status))
        return FALSE;

    Status = InitCodePageTable(
                &NpInfo->CpTable936,
                &NpInfo->CP936,
                L"936",
                NlsPath,
                Length
             );
    if (!NT_SUCCESS(Status))
        return FALSE;

*/

    LdrDisableThreadCalloutsForDll(BaseAddress);

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY(NpNpaReader2,  4, 0x01593), // NpaFileReader
//        PATCH_MEMORY(0x90C3C033,    4, 0xA2DC0), // IsDeubggerPresent
//        PATCH_MEMORY(0x00000084,    4, 0x018E8), // FileInfoSize
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
//        PATCH_FUNCTION(CALL, 0, 0x01A90, ConvertFileNameEncoding),
//        PATCH_FUNCTION(CALL, 0, 0x01B74, HashFilePath),

//        INLINE_HOOK_RVA(0x4AE70, NpLoadFile,        StubNpLoadFile),
//        INLINE_HOOK_RVA(0x01CC6, NpGetFileNameHash, StubNpGetFileNameHash),

        INLINE_HOOK_RVA(0xA2DC0, DetectDebugger, StubDetectDebugger),
    };

    Success = NT_SUCCESS(Nt_PatchMemory(p, countof(p), f, countof(f), Nt_GetExeModuleHandle()));

    if (Success)
        *(PULONG_PTR)&StubNpNpaReader = p[0].DataBak;

    return Success;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, PVOID Reserved)
{
    UNREFERENCED_PARAMETER(Reserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Initialize(hInstance) || UnInitialize(hInstance);

        case DLL_PROCESS_DETACH:
            UnInitialize(hInstance);
            break;
    }

    return TRUE;
}

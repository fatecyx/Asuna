#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "VERSION.lib")
#pragma comment(lib, "ucxdec/ucxdec.lib")

#include "krkr2.h"
#include "MyLibraryUser.cpp"
#include "cxdec.cpp"
#include "Krkr2AudioDecoder.h"

OVERLOAD_CPP_NEW_WITH_HEAP(MemoryAllocator::GetGlobalHeap())

Cxdec *g_Cxdec;

BOOL DecryptCxdecInternal(ULONG Hash, LARGE_INTEGER Offset, PVOID lpBuffer, ULONG BufferSize)
{
    PBYTE           pbBuffer;
    ULONG           Mask, Mask2;
    LARGE_INTEGER   CurrentPos;

    pbBuffer = (PBYTE)lpBuffer;
    Mask = g_Cxdec->GetMask(Hash);

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

    XorMemory(pbBuffer, (BYTE)Hash, BufferSize);

    return TRUE;
}

VOID STDCALL DecryptCxdec(PXP3_EXTRACTION_INFO Info)
{
    ULONG               SegmLength, Hash;
    LARGE_INTEGER       CurrentPos, Offset2;

    if (Info->SizeOfSelf != sizeof(*Info))
        return;

#if MAHOYO
    SegmLength = (Info->FileHash & 0x22A) + 0x2A2;       // mahoyo
#elif TENSHIN
    SegmLength = (Info->FileHash & 0x167) + 0x498;       // tenshin
#endif

    Offset2.QuadPart = SegmLength;
    CurrentPos.QuadPart = Info->Offset.QuadPart + Info->BufferSize;
    if (Info->Offset.QuadPart < Offset2.QuadPart && CurrentPos.QuadPart > Offset2.QuadPart)
    {
        Hash = Info->FileHash;
        SegmLength = Offset2.LowPart - Info->Offset.LowPart;
        DecryptCxdecInternal(Hash, Info->Offset, Info->Buffer, SegmLength);

        Hash = (Info->FileHash >> 16) ^ Info->FileHash;
        Info->Buffer = (PBYTE)Info->Buffer + SegmLength;
        DecryptCxdecInternal(Hash, Offset2, Info->Buffer, Info->BufferSize - SegmLength);
    }
    else
    {
        if (Info->Offset.QuadPart < Offset2.LowPart)
        {
            Hash = Info->FileHash;
        }
        else
        {
            Hash = (Info->FileHash >> 16) ^ Info->FileHash;
        }

        DecryptCxdecInternal(Hash, Info->Offset, Info->Buffer, Info->BufferSize);
    }
}

#include "Cxdex_DecryptBlock.h"

WCHAR DataXp3[] = L"\\data.xp3";

BOOL IsDataXp3(PUNICODE_STRING FileName, BOOL ContainSlash)
{
    ULONG Length;
    PWSTR Name;

    if (FileName == NULL)
        return FALSE;

    Length = !ContainSlash;

    if (FileName->Length < sizeof(DataXp3) - sizeof(WCHAR) * 3 - Length)
        return FALSE;

    Name = DataXp3 + Length;
    Length += CONST_STRLEN(DataXp3) - Length;

    return !StrNICompareW(FileName->Buffer + FileName->Length / sizeof(WCHAR) - Length, Name, Length);
}

BOOL IsXp3AndNotExist(PUNICODE_STRING FileName)
{
    ULONG Length;
    PWSTR Name;

    if (FileName == NULL)
        return FALSE;

    if (FileName->Length < 6)
        return FALSE;

    Name = FileName->Buffer + FileName->Length / sizeof(WCHAR) - 4;

    if ((*(PULONG64)Name & 0xFFFFFFDFFFDFFFFF) != TAG4W('.XP3'))
        return FALSE;

    OBJECT_ATTRIBUTES       ObjectAttributes;
    FILE_BASIC_INFORMATION  FileInfo;

    InitializeObjectAttributes(&ObjectAttributes, FileName, 0, NULL, NULL);

    return !NT_SUCCESS(StubNtQueryAttributesFile(&ObjectAttributes, &FileInfo));
}

NTSTATUS
NTAPI
HookNtQueryDirectoryFile(
    HANDLE                  FileHandle,
    HANDLE                  Event  OPTIONAL,
    PIO_APC_ROUTINE         ApcRoutine  OPTIONAL,
    PVOID                   ApcContext  OPTIONAL,
    PIO_STATUS_BLOCK        IoStatusBlock,
    PVOID                   FileInformation,
    ULONG                   Length,
    FILE_INFORMATION_CLASS  FileInformationClass,
    BOOLEAN                 ReturnSingleEntry,
    PUNICODE_STRING         FileName  OPTIONAL,
    BOOLEAN                 RestartScan
)
{
    NTSTATUS        Status;
    UNICODE_STRING  Filter;

    static WCHAR TpmSuffix[] = L"<.tpm";

    if (
        FileInformationClass == FileBothDirectoryInformation &&
        FileName != NULL
       )
    {
        if (
            FileName->Length >= sizeof(TpmSuffix) - sizeof(WCHAR) &&
            !StrNICompareW(FileName->Buffer + FileName->Length / sizeof(WCHAR) - CONST_STRLEN(TpmSuffix), TpmSuffix, CONST_STRLEN(TpmSuffix))
           )
        {
            PLDR_MODULE Module;

            Module = Nt_FindLdrModuleByHandle(&__ImageBase);

            FileName = &Module->BaseDllName;
        }
        else if (IsDataXp3(FileName, TRUE))
        {
            RTL_CONST_STRING(Filter, DATA_XP3_FILE_NAME);
            FileName = &Filter;
        }
    }

    Status = StubNtQueryDirectoryFile(FileHandle, Event, ApcRoutine, ApcContext, IoStatusBlock, FileInformation, Length, FileInformationClass, ReturnSingleEntry, FileName, RestartScan);
    if (NT_SUCCESS(Status))
        return Status;

    if (!IsXp3AndNotExist(FileName))
        return Status;

    ULONG NameLength;
    WCHAR Buffer[MAX_NTPATH];

    NameLength = FileName->Length - 8;
    CopyMemory(Buffer, FileName->Buffer, NameLength);
    CopyStruct((PBYTE)Buffer + NameLength, SC_XP3_SUFFIX, sizeof(SC_XP3_SUFFIX));

    Filter.Buffer           = Buffer;
    Filter.Length           = (USHORT)(NameLength + CONST_STRLEN(SC_XP3_SUFFIX) * sizeof(WCHAR));
    Filter.MaximumLength    = Filter.Length;

    FileName = &Filter;

    return StubNtQueryDirectoryFile(FileHandle, Event, ApcRoutine, ApcContext, IoStatusBlock, FileInformation, Length, FileInformationClass, ReturnSingleEntry, FileName, RestartScan);
}

NTSTATUS
NTAPI
HookNtQueryAttributesFile(
    POBJECT_ATTRIBUTES      ObjectAttributes,
    PFILE_BASIC_INFORMATION FileInformation
)
{
    ULONG           Length;
    WCHAR           Buffer[MAX_NTPATH];
    NTSTATUS        Status;
    PUNICODE_STRING FileName;
    UNICODE_STRING  Filter;

    FileName = ObjectAttributes == NULL ? NULL : ObjectAttributes->ObjectName;

    if (IsDataXp3(FileName, TRUE))
    {
        NtFileDisk::QueryFullNtPath(DATA_XP3_FILE_NAME, &Filter);
        ObjectAttributes->ObjectName = &Filter;
    }
    else if (IsXp3AndNotExist(FileName))
    {

        Length = FileName->Length - 8;
        CopyMemory(Buffer, FileName->Buffer, Length);
        CopyStruct((PBYTE)Buffer + Length, SC_XP3_SUFFIX, sizeof(SC_XP3_SUFFIX));

        Filter.Buffer           = Buffer;
        Filter.Length           = (USHORT)(Length + CONST_STRLEN(SC_XP3_SUFFIX) * sizeof(WCHAR));
        Filter.MaximumLength    = Filter.Length;

        ObjectAttributes->ObjectName = &Filter;

        FileName = NULL;
    }
    else
    {
        FileName = NULL;
    }

    Status = StubNtQueryAttributesFile(ObjectAttributes, FileInformation);

    if (FileName != NULL)
        RtlFreeUnicodeString(&Filter);

    return Status;
}

NTSTATUS
NTAPI
HookNtCreateFile(
    PHANDLE             FileHandle,
    ACCESS_MASK         DesiredAccess,
    POBJECT_ATTRIBUTES  ObjectAttributes,
    PIO_STATUS_BLOCK    IoStatusBlock,
    PLARGE_INTEGER      AllocationSize OPTIONAL,
    ULONG               FileAttributes,
    ULONG               ShareAccess,
    ULONG               CreateDisposition,
    ULONG               CreateOptions,
    PVOID               EaBuffer,
    ULONG               EaLength
)
{
    ULONG           Length;
    WCHAR           Buffer[MAX_NTPATH];
    NTSTATUS        Status;
    PUNICODE_STRING FileName;
    UNICODE_STRING  Xp3;

    FileName = ObjectAttributes == NULL ? NULL : ObjectAttributes->ObjectName;

    if (IsDataXp3(FileName, TRUE))
    {
        NtFileDisk::QueryFullNtPath(DATA_XP3_FILE_NAME, &Xp3);
        ObjectAttributes->ObjectName = &Xp3;
    }
    else if (IsXp3AndNotExist(FileName))
    {

        Length = FileName->Length - 8;
        CopyMemory(Buffer, FileName->Buffer, Length);
        CopyStruct((PBYTE)Buffer + Length, SC_XP3_SUFFIX, sizeof(SC_XP3_SUFFIX));

        Xp3.Buffer           = Buffer;
        Xp3.Length           = (USHORT)(Length + CONST_STRLEN(SC_XP3_SUFFIX) * sizeof(WCHAR));
        Xp3.MaximumLength    = Xp3.Length;

        ObjectAttributes->ObjectName = &Xp3;

        FileName = NULL;
    }
    else
    {
        FileName = NULL;
    }

    Status = StubNtCreateFile(
                FileHandle,
                DesiredAccess,
                ObjectAttributes,
                IoStatusBlock,
                AllocationSize,
                FileAttributes,
                ShareAccess,
                CreateDisposition,
                CreateOptions,
                EaBuffer,
                EaLength
             );

    if (FileName != NULL)
        RtlFreeUnicodeString(&Xp3);

    return Status;
}

ULONG
WINAPI
HookGetGlyphOutlineW(
    HDC             hDC,
    UINT            uChar,
    UINT            Format,
    LPGLYPHMETRICS  GlyphMetrics,
    ULONG           BufferCount,
    LPVOID          Buffer,
    CONST MAT2*     Mat2
)
{
    HFONT       FontGB;
    ULONG       RecvSize;
    LOGFONTW    lf;

    static WCHAR JpFace[] = L"MS Gothic";

    switch (uChar)
    {
        default:
            FontGB = NULL;
            break;

        case 0x30FB:    // ¡¤
        case 0x266A:    // eighth note
            FontGB = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
            GetObjectW(FontGB, sizeof(lf), &lf);
            lf.lfCharSet = SHIFTJIS_CHARSET;
            CopyStruct(lf.lfFaceName, JpFace, sizeof(JpFace));
            FontGB = (HFONT)SelectObject(hDC, CreateFontIndirectW(&lf));
            break;
    }

    RecvSize = StubGetGlyphOutlineW(hDC, uChar, Format, GlyphMetrics, BufferCount, Buffer, Mat2);
    if (FontGB)
        DeleteObject(SelectObject(hDC, FontGB));

    return RecvSize;
}

NAKED VOID FASTCALL StubTVPGetPlacedPath(PSttstr *ppFindName, PSttstr *ppFindResult)
{
    INLINE_ASM mov eax, ecx;
    ASM_DUMMY_AUTO();
}

VOID FASTCALL TVPGetPlacedPathInternal(PSttstr *ppFindName, PSttstr *FindResult)
{
    ULONG   FileType;
    ULONG64 OrigExtension;
    PSttstr FindName;
    PWSTR   Extension;

    StubTVPGetPlacedPath(ppFindName, FindResult);
    if (FindResult == NULL || *FindResult != NULL || ppFindName == NULL)
        return;

    FindName = *ppFindName;
    if (FindName == NULL)
        return;

    Extension = findextw(FindName->Buffer ? FindName->Buffer : FindName->String);
    if (*Extension != '.')
        return;

    ++Extension;
    OrigExtension = *(PULONG64)Extension;
    switch (OrigExtension & 0xFFFFFFDFFFDFFFDF)
    {
        case TAG3W('WAV'):
        case TAG3W('OGG'):
            *(PULONG64)Extension = TAG3W('uca');
            StubTVPGetPlacedPath(ppFindName, FindResult);
            if (*FindResult != NULL)
                return;

            *(PULONG64)Extension = TAG3W('m4a');
            break;

        case TAG3W('BMP'):
            *(PULONG64)Extension = TAG3W('uci');
            break;

        case TAG3W('MPG'):
            *(PULONG64)Extension = TAG3W('avi');
            break;

        default:
            return;
    }

    StubTVPGetPlacedPath(ppFindName, FindResult);

    if (*FindResult == NULL)
        *(PULONG64)Extension = OrigExtension;
}

NAKED VOID FASTCALL TVPGetPlacedPath(PSttstr *ppFindName, PSttstr *ppFindResult)
{
    INLINE_ASM
    {
        mov ecx, eax;
        jmp TVPGetPlacedPathInternal;
    }
}

NTSTATUS
NTAPI
HookLdrLoadDll(
    PWCHAR          PathToFile,
    PULONG          Flags,
    PUNICODE_STRING ModuleFileName,
    PVOID*          ModuleBase
)
{
    ULONG       Length;
    NTSTATUS    Status;

    static WChar WuVorbis[] = L"wuvorbis.dll";

    Status = StubLdrLoadDll(PathToFile, Flags, ModuleFileName, ModuleBase);
    if (!NT_SUCCESS(Status))
        return Status;

    Length = ModuleFileName->Length / sizeof(WCHAR);

    if (
        Length > CONST_STRLEN(WuVorbis) &&
        !StrNICompareW(ModuleFileName->Buffer + Length - CONST_STRLEN(WuVorbis), WuVorbis, CONST_STRLEN(WuVorbis))
       )
    {
        *ModuleBase = &__ImageBase;
    }

    return Status;
}

HFONT WINAPI HookCreateFontIndirectExW(const ENUMLOGFONTEXDVW *EnumLogFontEx)
{
    ((PENUMLOGFONTEXDVW)EnumLogFontEx)->elfEnumLogfontEx.elfLogFont.lfCharSet = GB2312_CHARSET;
    return StubCreateFontIndirectExW(EnumLogFontEx);
}

BOOL UnInitialize(PVOID BaseAddress)
{
    UNREFERENCED_PARAMETER(BaseAddress);

    SafeDeleteT(g_Cxdec);
    MemoryAllocator::DestroyGlobalHeap();

    return FALSE;
}

EXTC HRESULT STDCALL V2Link(ITVPFunctionExporter *Exporter)
{
    static WCHAR *Function[] =
    {
        L"void ::TVPSetXP3ArchiveExtractionFilter(tTVPXP3ArchiveExtractionFilter)",
    };

    if (*Function == NULL)
    {
        *EATLookupNameByNameNoFix(&__ImageBase, "GetPicture") = 0;
        return S_OK;
    }

    if (g_Cxdec != NULL)
    {
        VOID (STDCALL *TVPSetXP3ArchiveExtractionFilter)(TVP_XP3_EXCTRACTION_FILTER);

        if (!Exporter->QueryFunctions(Function, (PVOID *)&TVPSetXP3ArchiveExtractionFilter, 1))
            return E_FAIL;

        TVPSetXP3ArchiveExtractionFilter(DecryptCxdec);
    }

    *Function = NULL;

    PVOID TVPGetPlacedPathWorker;

    TVPGetPlacedPathWorker = FindTVPGetPlacedPath(Exporter);
    if (TVPGetPlacedPathWorker == NULL)
        return E_FAIL;

    MEMORY_FUNCTION_PATCH f[] =
    {
        PATCH_FUNCTION(JUMP, AUTO_DISASM | NOT_RVA, TVPGetPlacedPathWorker, TVPGetPlacedPath, 0, PtrAdd(StubTVPGetPlacedPath, 2)),
    };

    return Nt_PatchMemory(NULL, 0, f, countof(f), NULL);
}

EXTC HRESULT STDCALL V2Unlink()
{
    SafeDeleteT(g_Cxdec);

    return S_OK;
}

EXTC
HRESULT
STDCALL
GetModuleInstance(
    ITSSModule          **Object,
    ITSSStorageProvider *Provider,
    IStream             *Config,
    HWND                 MainWindow
)
{

    *Object = new AudioModule(Provider);

    return *Object == NULL ? E_OUTOFMEMORY : S_OK;
}

BOOL Initialize(PVOID BaseAddress)
{
    Cxdec *CxdecObject;

    if (MemoryAllocator::CreateGlobalHeap() == NULL)
        return FALSE;

    CxdecObject = new Cxdec;
    if (CxdecObject == NULL)
        return FALSE;

    CXDEC_OPTION Option;
    ULONG FunctionCount, FunctionSize, LoopCount;

    FunctionCount   = 0x80;
    FunctionSize    = 0x80;
    LoopCount       = 5;

#if MAHOYO

    ULONG Body1[6] = { 3, 2, 1, 4, 5, 0 };
    ULONG Body2[8] = { 7, 6, 5, 1, 0, 3, 4, 2 };
    ULONG Tail[3]  = { 1, 0, 2 };

#elif TENSHIN

    ULONG Body1[6] = { 1, 0, 5, 4, 3, 2 };
    ULONG Body2[8] = { 4, 2, 3, 5, 6, 1, 7, 0 };
    ULONG Tail[3]  = { 1, 0, 2 };

#endif

    if (LoopCount != 0)
    {
        Option.DecryptBlock     = DecryptBlock;
        Option.Body1IndexMap    = Body1;
        Option.Body2IndexMap    = Body2;
        Option.TailIndexMap     = Tail;
        Option.Const[0]         = 0xAAAAAAAA;
        Option.Const[1]         = 0x55555555;
        Option.FunctionCount    = FunctionCount;
        Option.FunctionSize     = FunctionSize;
        Option.LoopCount        = LoopCount;

        CxdecObject->SetOption(&Option);

        if (!CxdecObject->Initialize())
            return FALSE;

        g_Cxdec = CxdecObject;
    }
    else
    {
        delete CxdecObject;
    }

    LdrDisableThreadCalloutsForDll(BaseAddress);
    Nt_SetExeDirectoryAsCurrent();

    PVOID Base;
    UNICODE_STRING ucxdec;

    RTL_CONST_STRING(ucxdec, L"ucxdec.dll");
    LdrLoadDll(NULL, NULL, &ucxdec, &Base);

    return InitializeHook(BaseAddress);
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

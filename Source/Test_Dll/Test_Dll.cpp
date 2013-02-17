#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "MyLibrary.cpp"

OVERLOAD_CPP_NEW_WITH_HEAP(MemoryAllocator::GetGlobalHeap())

LONG STDCALL DecCallback(PVOID, LPWIN32_FIND_DATAW pfd, ULONG_PTR)
{
    ULONG Header;
    NTSTATUS Status;
    NtFileDisk file;

    file.Open(pfd->cFileName);
    file.Read(&Header, 4);
    file.Close();

    if (Header != TAG4('SDFA'))
        return 0;

    CHAR FileName[MAX_PATH];

    PrintConsoleW(L"%s\n", pfd->cFileName);
    Nt_UnicodeToAnsi(FileName, countof(FileName), pfd->cFileName);

    API_POINTER(fopen)  fopen   = (TYPE_OF(fopen))0x5F489E;
    API_POINTER(fseek)  fseek   = (TYPE_OF(fseek))0x5F7BF1;
    API_POINTER(ftell)  ftell   = (TYPE_OF(ftell))0x5F795C;
    API_POINTER(fread)  fread   = (TYPE_OF(fread))0x5F38D6;
    API_POINTER(fclose) fclose  = (TYPE_OF(fclose))0x5F45B8;

    FILE *fp = fopen(FileName, "rb");
    fseek(fp, 0, SEEK_END);
    Header = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    PBYTE p = (PBYTE)AllocateMemory(Header);
    if (fread(p, Header, 1, fp) == 0)
        PrintConsoleW(L"failed\n");

    fclose(fp);

    ULONG len;
    static WCHAR dir[] = L"F:\\ys7\\data_sc\\";

    WCHAR Path[MAX_NTPATH];

    swprintf(Path, L"%s%s", dir, pfd->cFileName);

    WCHAR c, *pname;

    pname = findnamew(Path);
    c = *pname;
    *pname = 0;
    CreateDirectoryRecursiveW(Path);
    *pname = c;

    Status = file.Create(Path);
//    PrintConsoleW(L"file.Create(): %08X\n", Status);

    if (NT_SUCCESS(Status))
    {
        Status = file.Write(p, Header);
//        PrintConsoleW(L"file.Write(): Status = %08X, Size = %08X\n", Status, Header);
    }

    FreeMemory(p);

//    getch();

    return 0;
}

VOID CDECL dec()
{
    SetPriorityClass(NtCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
    AllocConsole();
    Nt_SetExeDirectoryAsCurrent();

    EnumDirectoryFiles(NULL, L"*.*", 0, L"bgm", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"chr", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"dump", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"efx", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"inc", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"map", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"mmv3", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"movie", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"obj", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"pack123", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"savedata", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"savefile", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"script", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"se", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"system", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"text", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"visual", NULL, DecCallback, 0, EDF_SUBDIR);
    EnumDirectoryFiles(NULL, L"*.*", 0, L"web", NULL, DecCallback, 0, EDF_SUBDIR);

    FreeConsole();

    Nt_ExitProcess(0);
}

#include <map>
#include "SectionProtector.h"

typedef std::map<PVOID, PVOID> memlist;
memlist *mem;

RTL_CRITICAL_SECTION cs;

TYPE_OF(malloc)    *StubRtlAllocateHeap;
TYPE_OF(realloc)  *StubRtlReAllocateHeap;
TYPE_OF(free)        *StubRtlFreeHeap;

EXTC_EXPORT BOOL CDECL UnInitialize(PVOID BaseAddress);

static PVOID CDECL HCH_RtlAllocateHeap(SIZE_T Bytes)
{
    PVOID Memory;

    Memory = StubRtlAllocateHeap(Bytes);

    if (GetAsyncKeyState(VK_CONTROL) < 0)
    {
        RtlEnterCriticalSection(&cs);
        UnInitialize(0);
        Nt_ExitProcess(0);
    }

    if (GetAsyncKeyState(VK_SHIFT) >= 0)
        return Memory;

    PROTECT_SECTION(&cs)
    {
        mem->insert(std::make_pair(Memory, _ReturnAddress()));
    }

    return Memory;
}

static VOID CDECL HCH_RtlFreeHeap(LPVOID Memory)
{
    PROTECT_SECTION(&cs)
    {
        memlist::iterator it = mem->find(Memory);

        if (it == mem->end())
            break;

        mem->erase(it);
    }

    StubRtlFreeHeap(Memory);
}

static PVOID CDECL HCH_RtlReAllocateHeap(PVOID Memory, SIZE_T Bytes)
{
    PVOID NewMemory;

    NewMemory = StubRtlReAllocateHeap(Memory, Bytes);
    if (NewMemory == NULL)
        return NewMemory;

    PROTECT_SECTION(&cs)
    {
        memlist::iterator it = mem->find(Memory);

        if (it == mem->end())
            break;

        mem->erase(it);
        mem->insert(std::make_pair(NewMemory, _ReturnAddress()));
    }

    return NewMemory;
}

NTSTATUS EnableHeapCorruptionHelper2()
{
    PVOID vc71 = Nt_LoadLibrary(L"msvcr71.dll");
    PVOID de = Nt_LoadLibrary(L"download_engine.dll");

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_JUMP(PtrAdd(de, 0x24A56),   HCH_RtlAllocateHeap,    StubRtlAllocateHeap),
        INLINE_HOOK_JUMP(Nt_GetProcAddress(vc71, "realloc"), HCH_RtlReAllocateHeap,  StubRtlReAllocateHeap),
        INLINE_HOOK_JUMP(Nt_GetProcAddress(vc71, "free"),       HCH_RtlFreeHeap,        StubRtlFreeHeap),
    };

    NTSTATUS    Status;
    PLDR_MODULE ntdll;
    PVOID       ShadowNtdll;

    auto ReloadNtdll =
    WalkIATCallbackM(ImageBase, ImportDescriptor, Thunk, DllName, Ordinal, FunctionName, ShadowNtdll)
    {
        if (HashAPILower(DllName) != CONST_STRHASH("ntdll.dll"))
            return 0;

        if (FunctionName != NULL)
            *Thunk = (ULONG_PTR)EATLookupRoutineByHashPNoFix((PVOID)ShadowNtdll, HashAPI(FunctionName));

        return 0;
    };

    ntdll = GetNtdllLdrModule();
    Status = ReLoadDll(ntdll->FullDllName.Buffer, &ShadowNtdll, ntdll->DllBase);

    WalkImportTableT(&__ImageBase, ReloadNtdll, (ULONG_PTR)ShadowNtdll);

    return Nt_PatchMemory(NULL, 0, f, countof(f));
}

BOOL Initialize(PVOID BaseAddress)
{
    ml::MlInitialize();

    RtlInitializeCriticalSectionAndSpinCount(&cs, 4000);

    mem = new memlist;

    EnableHeapCorruptionHelper2();

    return TRUE;
}

EXTC_EXPORT BOOL CDECL UnInitialize(PVOID BaseAddress)
{
    if (mem == NULL)
        return 1;

    NtFileDisk f;
    WCHAR buf[0x1000];

    f.Create(L"E:\\Desktop\\xfuck.txt");
    ULONG BOM = BOM_UTF16_LE;

    f.Write(&BOM, 2);

    PROTECT_SECTION(&cs)
    {
        for (memlist::iterator it = mem->begin(); it != mem->end(); ++it)
        {
            PLDR_MODULE mod;

            mod = Nt_FindLdrModuleByHandle(it->second);

            f.Print(
                NULL,
                L"%p @ VA = %p, RVA = %p, Module = %s\r\n",
                it->first,
                it->second,
                PtrOffset(it->second, mod->DllBase),
                mod->FullDllName.Buffer
            );
        }

        SAFE_DELETE(mem);
    }

    return FALSE;
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

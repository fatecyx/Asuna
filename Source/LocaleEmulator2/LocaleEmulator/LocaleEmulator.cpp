#include "stdafx.h"
#include "mlns.h"

OVERLOAD_CPP_NEW_WITH_HEAP(MemoryAllocator::GetGlobalHeap())

#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")

#define DLL_IS(_dllname) RtlEqualUnicodeString(DllName, &WCS2US(_dllname), TRUE)

PLeGlobalData g_GlobalData;

ForceInline VOID LeSetGlobalData(PLeGlobalData GlobalData)
{
    g_GlobalData = GlobalData;
}

ForceInline VOID LeReleaseGlobalData()
{
    SafeDeleteT(g_GlobalData);
}

NTSTATUS GetNlsFile(PUNICODE_STRING NlsFile, ULONG NlsIndex, PCWSTR SubKey)
{
    BOOL        Success;
    WCHAR       NlsIndexBuffer[16];
    NTSTATUS    Status;
    PKEY_VALUE_PARTIAL_INFORMATION FileName;

    swprintf(NlsIndexBuffer, L"%d", NlsIndex);

    Status = GetKeyValue(REGKEY_ROOT, SubKey, NlsIndexBuffer, &FileName);
    FAIL_RETURN(Status);

    Success = RtlCreateUnicodeString(NlsFile, (PWSTR)FileName->Data);
    FreeMemoryP(FileName);

    return Success ? STATUS_SUCCESS : STATUS_NO_MEMORY;
}

NTSTATUS GetLangFile(PUNICODE_STRING LangFile, ULONG LangIndex, PCWSTR SubKey)
{
    BOOL        Success;
    WCHAR       LangIndexBuffer[16];
    NTSTATUS    Status;
    PKEY_VALUE_PARTIAL_INFORMATION FileName;

    swprintf(LangIndexBuffer, L"%04x", LangIndex);

    Status = GetKeyValue(REGKEY_ROOT, SubKey, LangIndexBuffer, &FileName);
    FAIL_RETURN(Status);

    Success = RtlCreateUnicodeString(LangFile, (PWSTR)FileName->Data);
    FreeMemoryP(FileName);

    return Success ? STATUS_SUCCESS : STATUS_NO_MEMORY;
}

NTSTATUS ReadFileInSystemDirectory(NtFileMemory &File, PUNICODE_STRING Path)
{
    PWSTR       Buffer;
    ULONG_PTR   Length;
    NTSTATUS    Status;

    Length = sizeof(ROOTDIR_SYSTEM32) + Path->Length + sizeof(WCHAR);
    Buffer = (PWSTR)AllocateMemoryP(Length);
    if (Buffer == NULL)
        return STATUS_NO_MEMORY;

    Length = CONST_STRLEN(ROOTDIR_SYSTEM32);
    CopyMemory(Buffer, ROOTDIR_SYSTEM32, Length * sizeof(WCHAR));
    CopyMemory(Buffer + Length, Path->Buffer, Path->Length);
    Buffer[Length + Path->Length / sizeof(WCHAR)] = 0;

    Status = File.Open(Buffer, NFD_NOT_RESOLVE_PATH);

    FreeMemoryP(Buffer);

    return Status;
}

NTSTATUS LeGlobalData::Initialize()
{
    PLEPEB          LePeb;
    PLDR_MODULE     Ntdll;
    PPEB_BASE       Peb;
    NTSTATUS        Status;
    NLSTABLEINFO    NlsTableInfo;
    UNICODE_STRING  SystemDirectory, NlsFileName, OemNlsFileName, LangFileName;
    PKEY_VALUE_PARTIAL_INFORMATION IndexValue;

    Wow64 = Ps::IsWow64Process();
    Ntdll = GetNtdllLdrModule();

    LePeb = OpenOrCreateLePeb();
    if (LePeb == NULL)
    {
        PVOID           ReloadedNtdll;
        PUNICODE_STRING FullDllName;

        LePeb = GetLePeb();

        InitDefaultLeb(&LePeb->Leb);

        FullDllName = &FindLdrModuleByHandle(&__ImageBase)->FullDllName;
        CopyMemory(LePeb->LeDllFullPath, FullDllName->Buffer, FullDllName->Length + sizeof(WCHAR));

        Status = LoadPeImage(Ntdll->FullDllName.Buffer, &ReloadedNtdll, NULL, LOAD_PE_IGNORE_RELOC);
        if (NT_SUCCESS(Status))
        {
            PVOID LdrLoadDllAddress;

            LdrLoadDllAddress = EATLookupRoutineByHashPNoFix(ReloadedNtdll, NTDLL_LdrLoadDll);
            LePeb->LdrLoadDllAddress = PtrAdd(LdrLoadDllAddress, PtrOffset(Ntdll->DllBase, ReloadedNtdll));
            CopyMemory(LePeb->LdrLoadDllBackup, LdrLoadDllAddress, LDR_LOAD_DLL_BACKUP_SIZE);
            LePeb->LdrLoadDllBackupSize = LDR_LOAD_DLL_BACKUP_SIZE;

            UnloadPeImage(ReloadedNtdll);
        }
    }
    else
    {
        *GetLePeb() = *LePeb;

        ZwClose(LePeb->Section);
        CloseLePeb(LePeb);
    }

    WriteLog(L"init leb %s", GetLePeb()->LeDllFullPath);

    SystemDirectory = Ntdll->FullDllName;
    SystemDirectory.Length -= Ntdll->BaseDllName.Length;

    Status = RtlDuplicateUnicodeString(RTL_DUPSTR_ADD_NULL, &SystemDirectory, &this->SystemDirectory);
    FAIL_RETURN(Status);

    RtlInitEmptyUnicodeString(&NlsFileName, NULL, 0);
    RtlInitEmptyUnicodeString(&OemNlsFileName, NULL, 0);
    RtlInitEmptyUnicodeString(&LangFileName, NULL, 0);

    SCOPE_EXIT
    {
        RtlFreeUnicodeString(&NlsFileName);
        RtlFreeUnicodeString(&OemNlsFileName);
        RtlFreeUnicodeString(&LangFileName);
    }
    SCOPE_EXIT_END;

    Status = GetNlsFile(&NlsFileName, GetLeb()->AnsiCodePage, REGPATH_CODEPAGE);
    FAIL_RETURN(Status);

    Status = GetNlsFile(&OemNlsFileName, GetLeb()->OemCodePage, REGPATH_CODEPAGE);
    FAIL_RETURN(Status);

    Status = GetLangFile(&LangFileName, GetLeb()->LocaleID, REGPATH_LANGUAGE);
    FAIL_RETURN(Status);

    NtFileMemory AnsiFile, OemFile, LangFile;

    Status = ReadFileInSystemDirectory(AnsiFile, &NlsFileName);
    FAIL_RETURN(Status);

    Status = ReadFileInSystemDirectory(OemFile, &OemNlsFileName);
    FAIL_RETURN(Status);

    Status = ReadFileInSystemDirectory(LangFile, &LangFileName);
    FAIL_RETURN(Status);

    AnsiCodePageOffset      = 0;
    OemCodePageOffset       = ROUND_UP(AnsiFile.GetSize32(), 16);
    UnicodeCaseTableOffset  = OemCodePageOffset + ROUND_UP(OemFile.GetSize32(), 16);

    Status = AllocVirtualMemory(&CodePageMapView, UnicodeCaseTableOffset + LangFile.GetSize32(), PAGE_READWRITE, MEM_COMMIT | MEM_TOP_DOWN);
    FAIL_RETURN(Status);

    CopyMemory(PtrAdd(CodePageMapView, AnsiCodePageOffset),     AnsiFile.GetBuffer(),   AnsiFile.GetSize32());
    CopyMemory(PtrAdd(CodePageMapView, OemCodePageOffset),      OemFile.GetBuffer(),    OemFile.GetSize32());
    CopyMemory(PtrAdd(CodePageMapView, UnicodeCaseTableOffset), LangFile.GetBuffer(),   LangFile.GetSize32());

    ProtectVirtualMemory(CodePageMapView, UnicodeCaseTableOffset + LangFile.GetSize32(), PAGE_READONLY);

    RtlInitNlsTables(
        (PUSHORT)PtrAdd(CodePageMapView, AnsiCodePageOffset),
        (PUSHORT)PtrAdd(CodePageMapView, OemCodePageOffset),
        (PUSHORT)PtrAdd(CodePageMapView, UnicodeCaseTableOffset),
        &NlsTableInfo
    );

    RtlResetRtlTranslations(&NlsTableInfo);

    WriteLog(L"reset nls");

    Peb = Ps::CurrentPeb();

    Peb->AnsiCodePageData       = (PUSHORT)PtrAdd(CodePageMapView, AnsiCodePageOffset);
    Peb->OemCodePageData        = (PUSHORT)PtrAdd(CodePageMapView, OemCodePageOffset);
    Peb->UnicodeCaseTableData   = (PUSHORT)PtrAdd(CodePageMapView, UnicodeCaseTableOffset);

    // LdrInitShimEngineDynamic(&__ImageBase);

    LdrRegisterDllNotification(0,
        [] (ULONG NotificationReason, PCLDR_DLL_NOTIFICATION_DATA NotificationData, PVOID Context)
        {
            return ((PLeGlobalData)Context)->DllNotification(NotificationReason, NotificationData);
        },
        this,
        &DllNotificationCookie
    );

    Status = InstallHookPort();
    FAIL_RETURN(Status);

    WriteLog(L"inst hp");

    HookNtdllRoutines(Ntdll->DllBase);

    WriteLog(L"hook ntdll");

    PLDR_MODULE Kernel32Ldr;

    Kernel32Ldr = GetKernel32Ldr();
    if (Kernel32Ldr != NULL)
    {
        HookKernel32Routines(Kernel32Ldr->DllBase);
    }

    WriteLog(L"init %p", Status);

    return Status;
}

BOOL NTAPI DelayInitDllEntry(PVOID BaseAddress, ULONG Reason, PVOID Reserved)
{
    BOOL Success;
    PLDR_MODULE Module = FindLdrModuleByHandle(BaseAddress);
    PIMAGE_NT_HEADERS NtHeaders;

    NtHeaders = PtrAdd((PIMAGE_NT_HEADERS)BaseAddress, ((PIMAGE_DOS_HEADER)BaseAddress)->e_lfanew);
    Module->EntryPoint = PtrAdd(BaseAddress, NtHeaders->OptionalHeader.AddressOfEntryPoint);

    Success = ((API_POINTER(DelayInitDllEntry))Module->EntryPoint)(BaseAddress, Reason, Reserved);

    if (Reason == DLL_PROCESS_ATTACH && !Success)
        return Success;

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            if (!Success)
                return Success;
        case DLL_PROCESS_DETACH:
            break;

        default:
            return Success;
    }

    LeGetGlobalData()->HookModule(BaseAddress, &Module->BaseDllName, Reason == DLL_PROCESS_ATTACH);

    return Success;
}

VOID LeGlobalData::HookModule(PVOID DllBase, PCUNICODE_STRING DllName, BOOL DllLoad)
{
    TYPE_OF(&LeGlobalData::HookNtdllRoutines)     HookRoutine;
    TYPE_OF(&LeGlobalData::UnHookNtdllRoutines)   UnHookRoutine;

    if (DLL_IS(L"USER32.dll"))
    {
        HookRoutine     = &LeGlobalData::HookUser32Routines;
        UnHookRoutine   = &LeGlobalData::UnHookUser32Routines;
    }
    else if (DLL_IS(L"GDI32.dll"))
    {
        HookRoutine     = &LeGlobalData::HookGdi32Routines;
        UnHookRoutine   = &LeGlobalData::UnHookGdi32Routines;
    }
    else if (DLL_IS(L"KERNEL32.dll"))
    {
        if (GetLePeb()->SelfShadowToFree != NULL)
        {
            Mm::FreeVirtualMemory(GetLePeb()->SelfShadowToFree);
        }

        HookRoutine     = &LeGlobalData::HookKernel32Routines;
        UnHookRoutine   = &LeGlobalData::UnHookKernel32Routines;
    }
    else
    {
        return;
    }

    DllLoad ? (this->*HookRoutine)(DllBase) : (this->*UnHookRoutine)();
}

VOID LeGlobalData::DllNotification(ULONG NotificationReason, PCLDR_DLL_NOTIFICATION_DATA NotificationData)
{
    NTSTATUS            Status;
    PVOID               DllBase;
    ULONG_PTR           Length;
    PLDR_MODULE         Module;
    UNICODE_STRING      DllPath;
    PCUNICODE_STRING    DllName;

    switch (NotificationReason)
    {
        case LDR_DLL_NOTIFICATION_REASON_LOADED:
            DllPath = *NotificationData->Loaded.FullDllName;
            DllPath.Length -= NotificationData->Loaded.BaseDllName->Length;
            DllName = NotificationData->Loaded.BaseDllName;
            DllBase = NotificationData->Loaded.DllBase;
            break;

        case LDR_DLL_NOTIFICATION_REASON_UNLOADED:
            DllPath = *NotificationData->Unloaded.FullDllName;
            DllPath.Length -= NotificationData->Unloaded.BaseDllName->Length;
            DllName = NotificationData->Unloaded.BaseDllName;
            DllBase = NotificationData->Loaded.DllBase;
            break;

        default:
            return;
    }

    if (!RtlEqualUnicodeString(&SystemDirectory, &DllPath, TRUE))
        return;

    if (
        DLL_IS(L"USER32.dll")  ||
        DLL_IS(L"GDI32.dll")   ||
        DLL_IS(L"KERNEL32.dll")
       )
    {
    }
    else
    {
        return;
    }

    Module = FindLdrModuleByHandle(DllBase);
    if (!FLAG_ON(Module->Flags, LDRP_PROCESS_ATTACH_CALLED))
    {
        Module->EntryPoint = DelayInitDllEntry;
    }
    else
    {
        HookModule(DllBase, DllName, NotificationReason == LDR_DLL_NOTIFICATION_REASON_LOADED);
    }
}

NTSTATUS LeGlobalData::UnInitialize()
{
    if (DllNotificationCookie != NULL)
    {
        LdrUnregisterDllNotification(DllNotificationCookie);
        DllNotificationCookie = NULL;
    }

    UnHookGdi32Routines();
    UnHookUser32Routines();
    UnHookKernel32Routines();
    UnHookNtdllRoutines();

    UnInstallHookPort();

    RtlFreeUnicodeString(&SystemDirectory);

    return 0;
}

inline BOOL UnInitialize(PVOID BaseAddress)
{
    LeReleaseGlobalData();
    ml::MlUnInitialize();
    return FALSE;
}

BOOL Initialize(PVOID BaseAddress)
{
    NTSTATUS            Status;
    PLDR_MODULE         Kernel32;
    PLeGlobalData       GlobalData;

    Kernel32 = GetKernel32Ldr();

    if (Kernel32 != NULL && FLAG_ON(Kernel32->Flags, LDRP_PROCESS_ATTACH_CALLED))
    {
        ExceptionBox(L"fuck");
        return FALSE;
    }

    LdrDisableThreadCalloutsForDll(BaseAddress);
    ml::MlInitialize();

    GlobalData = new LeGlobalData;
    if (GlobalData == NULL)
        return FALSE;

    LeSetGlobalData(GlobalData);

    Status = GlobalData->Initialize();
    if (NT_FAILED(Status))
        return FALSE;

    RtlSetUnhandledExceptionFilter(
        [] (PEXCEPTION_POINTERS ExceptionPointers) -> LONG
        {
            ExceptionBox(L"crashed");
            CreateMiniDump(ExceptionPointers);
            return ExceptionContinueSearch;
        }
    );

    WriteLog(L"init ret");

    return TRUE;
}

BOOL NTAPI DllMain(PVOID BaseAddress, ULONG Reason, PVOID Reserved)
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

#include "stdafx.h"

NTSTATUS QueryRegKeyFullPath(HANDLE Key, PUNICODE_STRING KeyFullPath)
{
    NTSTATUS                    Status;
    PKEY_NAME_INFORMATION       KeyFullName;
    ULONG_PTR                   MaxLength;
    ULONG                       ReturnedLength;

    KeyFullName = NULL;
    MaxLength   = 0;

    LOOP_FOREVER
    {
        Status = ZwQueryKey(Key, KeyNameInformation, KeyFullName, MaxLength, &ReturnedLength);
        if (Status != STATUS_BUFFER_TOO_SMALL)
            break;

        KeyFullName = (PKEY_NAME_INFORMATION)ReAllocateMemoryP(KeyFullName, ReturnedLength + sizeof(WCHAR));
        if (KeyFullName == NULL)
        {
            Status = STATUS_NO_MEMORY;
            break;
        }

        MaxLength = ReturnedLength;
    }

    if (NT_SUCCESS(Status))
    {
        PtrAdd(KeyFullName->Name, KeyFullName->NameLength)[0] = 0;
        Status = RtlCreateUnicodeString(KeyFullPath, KeyFullName->Name) ? STATUS_SUCCESS : STATUS_NO_MEMORY;
    }

    FreeMemoryP(KeyFullName);
    return Status;
}

NoInline NTSTATUS FASTCALL LoadSelfAsFirstDll(PVOID ReturnAddress)
{
    PLEPEB LePeb;

    LOOP_ONCE
    {
        PVOID DllHandle;

        LePeb = OpenOrCreateLePeb();
        if (LePeb == NULL)
            break;

        LePeb->SelfShadowToFree = &__ImageBase;

        WriteProtectMemory(CurrentProcess, PtrSub(ReturnAddress, 4), &LePeb->ooxxValue, sizeof(LePeb->ooxxValue));

        UNICODE_STRING DllPath;

        RtlInitUnicodeString(&DllPath, LePeb->LeDllFullPath);

        if (NT_FAILED(LdrLoadDll(NULL, NULL, &DllPath, &DllHandle)))
        {
            CloseLePeb(LePeb);
            break;
        }

        *(PULONG_PTR)_AddressOfReturnAddress() += PtrOffset(DllHandle, &__ImageBase);

        CloseLePeb(LePeb);
    }

    return 0;
}

NTSTATUS
NTAPI
LoadFirstDll(
    PWCHAR              PathToFile OPTIONAL,
    PULONG              DllCharacteristics OPTIONAL,
    PCUNICODE_STRING    ModuleFileName,
    PVOID*              DllHandle
)
{
    LoadSelfAsFirstDll(_ReturnAddress());
    return LdrLoadDll(PathToFile, DllCharacteristics, ModuleFileName, DllHandle);
}

NTSTATUS
HPCALL
LeNtQuerySystemInformation(
    HPARGS
    IN  SYSTEM_INFORMATION_CLASS    SystemInformationClass,
    OUT PVOID                       SystemInformation,
    IN  ULONG_PTR                   SystemInformationLength,
    OUT PULONG                      ReturnLength OPTIONAL
)
{
    NTSTATUS Status = 0;
    PLeGlobalData GlobalData = (PLeGlobalData)HPARG_FLTINFO->FilterContext;

    switch (SystemInformationClass)
    {
        case SystemCurrentTimeZoneInformation:
            if (SystemInformation == NULL)
                break;

            if (SystemInformationLength < sizeof(GlobalData->GetLeb()->Timezone))
                break;

            *((PRTL_TIME_ZONE_INFORMATION)SystemInformation) = GlobalData->GetLeb()->Timezone;

            if (ReturnLength != NULL)
                *ReturnLength = SystemInformationLength;

            HPARG_FLTINFO->Action = BlockSystemCall;

            return STATUS_SUCCESS;
    }

    return Status;
}

NTSTATUS LeGlobalData::InjectSelfToChildProcess(HANDLE Process, PCLIENT_ID Cid)
{
    NTSTATUS    Status;
    PVOID       SelfShadow, LocalSelfShadow, ShadowLoadFirstDll;
    ULONG_PTR   SizeOfImage;
    LONG        Offset;
    PLEPEB      TargetLePeb;
    HANDLE      Section;

    // Process = CurrentProcess;

    if (Wow64 && !Ps::IsWow64Process(Process))
        return STATUS_NOT_SUPPORTED;

    if (GetLePeb()->ooxxAddress == NULL)
        return STATUS_UNSUCCESSFUL;

    SizeOfImage = FindLdrModuleByHandle(&__ImageBase)->SizeOfImage;

    SelfShadow = NULL;
    Status = AllocVirtualMemory(&SelfShadow, SizeOfImage, PAGE_EXECUTE_READWRITE, MEM_COMMIT, Process);
    if (NT_FAILED(Status))
        return Status;

    LocalSelfShadow = AllocateMemoryP(SizeOfImage);
    if (LocalSelfShadow == NULL)
    {
        Mm::FreeVirtualMemory(SelfShadow, Process);
        return STATUS_NO_MEMORY;
    }

    CopyMemory(LocalSelfShadow, &__ImageBase, SizeOfImage);
    RelocPeImage(LocalSelfShadow, &__ImageBase, SelfShadow);

    Status = WriteMemory(Process, SelfShadow, LocalSelfShadow, SizeOfImage);
    FreeMemoryP(LocalSelfShadow);

    if (NT_FAILED(Status))
    {
        Mm::FreeVirtualMemory(SelfShadow, Process);
        return Status;
    }

    ShadowLoadFirstDll = PtrAdd(LoadFirstDll, PtrOffset(SelfShadow, &__ImageBase));
    Offset = PtrOffset(ShadowLoadFirstDll, PtrAdd(GetLePeb()->ooxxAddress, 5));

    Status = WriteProtectMemory(Process, PtrAdd(GetLePeb()->ooxxAddress, 1), &Offset, sizeof(Offset));
    if (NT_FAILED(Status))
    {
        Mm::FreeVirtualMemory(SelfShadow, Process);
        return Status;
    }

    TargetLePeb = OpenOrCreateLePeb((ULONG_PTR)Cid->UniqueProcess, TRUE);
    if (TargetLePeb == NULL)
        return STATUS_UNSUCCESSFUL;

    Section = TargetLePeb->Section;
    *TargetLePeb = *GetLePeb();
    TargetLePeb->Section = Section;

    CloseLePeb(TargetLePeb);

    return STATUS_SUCCESS;
}

NTSTATUS
HPCALL
LeNtCreateUserProcess(
    HPARGS
    PHANDLE                         ProcessHandle,
    PHANDLE                         ThreadHandle,
    ACCESS_MASK                     ProcessDesiredAccess,
    ACCESS_MASK                     ThreadDesiredAccess,
    POBJECT_ATTRIBUTES              ProcessObjectAttributes,
    POBJECT_ATTRIBUTES              ThreadObjectAttributes,
    ULONG                           ProcessFlags,
    ULONG                           ThreadFlags,
    PRTL_USER_PROCESS_PARAMETERS    ProcessParameters,
    PPS_CREATE_INFO                 CreateInfo,
    PPS_ATTRIBUTE_LIST              AttributeList
)
{
    PLEPEB              TargetLePeb;
    NTSTATUS            Status, Status2;
    PLeGlobalData       GlobalData;
    PPS_ATTRIBUTE_LIST  LocalAttributeList;
    PPS_ATTRIBUTE       Attribute;
    CLIENT_ID           LocalCid, *Cid;
    ULONG_PTR           ReturnLength;
    LONG                Offset;
    PVOID               SelfShadow;

    HPARG_FLTINFO->Action = BlockSystemCall;

    LocalAttributeList = NULL;
    Attribute = NULL;
    Cid = NULL;

    if (AttributeList != NULL)
    {
        ULONG_PTR Count;

        Attribute = AttributeList->Attributes;
        Count = (PPS_ATTRIBUTE)PtrAdd(AttributeList, AttributeList->TotalLength) - Attribute;
        FOR_EACH(Attribute, AttributeList->Attributes, Count)
        {
            if (Attribute->AttributeNumber != PsAttributeClientId)
                continue;

//            if (Attribute->AttributeFlags != PS_ATTRIBUTE_FLAG_THREAD)
//                break;

            Cid = (PCLIENT_ID)Attribute->ValuePtr;
            break;
        }
    }

    if (Cid == NULL)
    {
        ULONG_PTR ListLength;

        ListLength = (AttributeList != NULL ? AttributeList->TotalLength : sizeof(AttributeList->TotalLength)) + sizeof(*Attribute);
        LocalAttributeList = (PPS_ATTRIBUTE_LIST)AllocStack(ListLength);

        if (AttributeList != NULL)
            CopyMemory(LocalAttributeList, AttributeList, AttributeList->TotalLength);

        LocalAttributeList->TotalLength = ListLength;
        Attribute = (PPS_ATTRIBUTE)PtrAdd(LocalAttributeList, LocalAttributeList->TotalLength) - 1;

        Attribute->AttributeNumber  = PsAttributeClientId;
        Attribute->AttributeFlags   = PS_ATTRIBUTE_FLAG_THREAD;
        Attribute->ValuePtr         = &LocalCid;
        Attribute->Size             = sizeof(LocalCid);
        Attribute->ReturnLength     = &ReturnLength;

        Cid = &LocalCid;

        AttributeList = LocalAttributeList;
    }

    Status = HpCallSysCall(
                NtCreateUserProcess,
                ProcessHandle,
                ThreadHandle,
                ProcessDesiredAccess,
                ThreadDesiredAccess,
                ProcessObjectAttributes,
                ThreadObjectAttributes,
                ProcessFlags,
                ThreadFlags,
                ProcessParameters,
                CreateInfo,
                AttributeList
            );

    if (NT_FAILED(Status))
        return Status;

    GlobalData = (PLeGlobalData)HPARG_FLTINFO->FilterContext;

    GlobalData->InjectSelfToChildProcess(*ProcessHandle, Cid);

    return Status;
}

NTSTATUS
HPCALL
LeNtInitializeNlsFiles(
    HPARGS
    PVOID*          BaseAddress,
    PLCID           DefaultLocaleId,
    PLARGE_INTEGER  DefaultCasingTableSize
)
{
    NTSTATUS Status;
    PLeGlobalData GlobalData;

    HPARG_FLTINFO->Action = BlockSystemCall;

    Status = HpCallSysCall(
                NtInitializeNlsFiles,
                BaseAddress,
                DefaultLocaleId,
                DefaultCasingTableSize
            );

    FAIL_RETURN(Status);

    GlobalData = (PLeGlobalData)HPARG_FLTINFO->FilterContext;

    *DefaultLocaleId = GlobalData->GetLeb()->LocaleID;

    return Status;
}

NTSTATUS
HPCALL
LeNtQueryValueKey(
    HPARGS
    HANDLE                      KeyHandle,
    PUNICODE_STRING             ValueName,
    KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    PVOID                       KeyValueInformation,
    ULONG                       Length,
    PULONG                      ResultLength
)
{
    NTSTATUS        Status;
    UNICODE_STRING  KeyFulPath;
    PLeGlobalData   GlobalData;
    ULONG_PTR       KeyType, BufferLength;
    WCHAR           Buffer[MAX_NTPATH];

    enum { CodePageKeyHandle, LanguageKeyHandle };

    if (NT_FAILED(RtlValidateUnicodeString(0, ValueName)))
        return 0;

    Status = QueryRegKeyFullPath(KeyHandle, &KeyFulPath);
    FAIL_RETURN(Status);

    GlobalData = (PLeGlobalData)HPARG_FLTINFO->FilterContext;

    if (RtlEqualUnicodeString(&KeyFulPath, &GlobalData->HookRoutineData.CodePageKey, TRUE))
    {
        KeyType = CodePageKeyHandle;
    }
    else if (RtlEqualUnicodeString(&KeyFulPath, &GlobalData->HookRoutineData.LanguageKey, TRUE))
    {
        KeyType = LanguageKeyHandle;
    }
    else
    {
        RtlFreeUnicodeString(&KeyFulPath);
        return 0;
    }

    RtlFreeUnicodeString(&KeyFulPath);

    switch (KeyType)
    {
        default:
            return 0;

        case CodePageKeyHandle:
            if (RtlEqualUnicodeString(ValueName, &WCS2US(REGKEY_ACP), TRUE))
            {
                BufferLength = swprintf(Buffer, L"%d", GlobalData->GetLeb()->AnsiCodePage);
            }
            else if (RtlEqualUnicodeString(ValueName, &WCS2US(REGKEY_OEMCP), TRUE))
            {
                BufferLength = swprintf(Buffer, L"%d", GlobalData->GetLeb()->OemCodePage);
            }
            else
            {
                return 0;
            }
            break;

        case LanguageKeyHandle:
            if (RtlEqualUnicodeString(ValueName, &WCS2US(REGKEY_DEFAULT_LANGUAGE), TRUE))
            {
                BufferLength = swprintf(Buffer, L"%04x", GlobalData->GetLeb()->LocaleID);
            }
            else
            {
                return 0;
            }
            break;
    }

    ++BufferLength;
    BufferLength *= sizeof(WCHAR);

    HPARG_FLTINFO->Action = BlockSystemCall;

    Status = HpCallSysCall(
                NtQueryValueKey,
                KeyHandle,
                ValueName,
                KeyValueInformationClass,
                KeyValueInformation,
                Length,
                ResultLength
            );

    if (Status == STATUS_BUFFER_TOO_SMALL)
    {
        if (ResultLength != NULL)
            *ResultLength += BufferLength;
    }

    if (NT_FAILED(Status))
        return Status;

    union
    {
        PKEY_VALUE_PARTIAL_INFORMATION          PartialInfo;
        PKEY_VALUE_PARTIAL_INFORMATION_ALIGN64  PartialInfoAlign64;
        PKEY_VALUE_FULL_INFORMATION             FullInfo;
        PVOID                                   ValueInformation;
    };

    ValueInformation = KeyValueInformation;

    switch (KeyValueInformationClass)
    {
        case KeyValuePartialInformation:
            if (PartialInfo->Type != REG_SZ)
                break;

            CopyMemory(PartialInfo->Data, Buffer, BufferLength);
            PartialInfo->DataLength = BufferLength - sizeof(WCHAR);
            break;

        case KeyValueFullInformation:
            if (FullInfo->Type != REG_SZ)
                break;

            CopyMemory(PtrAdd(FullInfo, FullInfo->DataOffset), Buffer, BufferLength);
            FullInfo->DataLength = BufferLength - sizeof(WCHAR);
            break;

        case KeyValuePartialInformationAlign64:
            if (PartialInfoAlign64->Type != REG_SZ)
                break;

            CopyMemory(PartialInfoAlign64->Data, Buffer, BufferLength);
            PartialInfoAlign64->DataLength = BufferLength - sizeof(WCHAR);
            break;
    }

    return Status;
}

NTSTATUS LeGlobalData::HookNtdllRoutines(PVOID Gdi32)
{
    NTSTATUS            Status;
    HANDLE              RootKey;
    OBJECT_ATTRIBUTES   ObjectAttributes;
    UNICODE_STRING      SubKey;

    RootKey = NULL;

    LOOP_ONCE
    {
        HANDLE CodePageKey, LanguageKey;

        Status = OpenPredefinedKeyHandle(&RootKey, REGKEY_ROOT, KEY_QUERY_VALUE);
        FAIL_BREAK(Status);

        RTL_CONST_STRING(SubKey, REGPATH_CODEPAGE);
        InitializeObjectAttributes(&ObjectAttributes, &SubKey, OBJ_CASE_INSENSITIVE, RootKey, NULL);
        Status = ZwOpenKey(&CodePageKey, KEY_QUERY_VALUE, &ObjectAttributes);
        FAIL_BREAK(Status);

        Status = QueryRegKeyFullPath(CodePageKey, &HookRoutineData.CodePageKey);
        ZwClose(CodePageKey);
        FAIL_BREAK(Status);

        RTL_CONST_STRING(SubKey, REGPATH_LANGUAGE);
        Status = ZwOpenKey(&LanguageKey, KEY_QUERY_VALUE, &ObjectAttributes);
        FAIL_BREAK(Status);

        Status = QueryRegKeyFullPath(LanguageKey, &HookRoutineData.LanguageKey);
        ZwClose(LanguageKey);
        FAIL_BREAK(Status);

        ADD_FILTER_(NtQueryValueKey, LeNtQueryValueKey, this);
    }

    if (RootKey != NULL)
        ZwClose(RootKey);

    ADD_FILTER_(NtQuerySystemInformation,   LeNtQuerySystemInformation, this);
    ADD_FILTER_(NtCreateUserProcess,        LeNtCreateUserProcess,      this);
    ADD_FILTER_(NtInitializeNlsFiles,       LeNtInitializeNlsFiles,     this);

    return STATUS_SUCCESS;
}

NTSTATUS LeGlobalData::UnHookNtdllRoutines()
{
    return 0;
}

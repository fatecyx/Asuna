#include "stdafx.h"

#pragma comment(linker, "/EXPORT:SE_InstallBeforeInit=_SE_InstallBeforeInit@8")
#pragma comment(linker, "/EXPORT:SE_InstallAfterInit=_SE_InstallAfterInit@8")
#pragma comment(linker, "/EXPORT:SE_DllLoaded=_SE_DllLoaded@4")
#pragma comment(linker, "/EXPORT:SE_DllUnloaded=_SE_DllUnloaded@4")
#pragma comment(linker, "/EXPORT:SE_GetProcAddressLoad=_SE_GetProcAddressLoad@4")
#pragma comment(linker, "/EXPORT:SE_ProcessDying=_SE_ProcessDying@0")

_ML_C_HEAD_

SE_InitializeEngine

SE_ShimDllLoaded

SE_LdrEntryRemoved

SE_LdrResolveDllName

SE_GetProcAddressForCaller

ApphelpCheckModule


NTSTATUS
STDCALL
SE_InitializeEngine(
    PUNICODE_STRING     EngineWorker,
    PUNICODE_STRING     ExeFullPath,
    PSHIM_ENGINE_DATA   ShimData
)
{
    ;
}

BOOLEAN
STDCALL
SE_InstallBeforeInit(
    PUNICODE_STRING     ModuleLoading,
    PSHIM_ENGINE_DATA   ShimData
)
{
    return TRUE;
}

BOOLEAN
STDCALL
SE_InstallAfterInit(
    PUNICODE_STRING     ModuleLoading,
    PSHIM_ENGINE_DATA   ShimData
)
{
    return SE_InstallBeforeInit(ModuleLoading, ShimData);
}

VOID
STDCALL
SE_DllLoaded(
    PLDR_DATA_TABLE_ENTRY DllLoaded
)
{
    LDR_DLL_NOTIFICATION_DATA NotificationData;

    NotificationData.Loaded.BaseDllName = &DllLoaded->BaseDllName;
    NotificationData.Loaded.FullDllName = &DllLoaded->FullDllName;
    NotificationData.Loaded.Flags       = 0;
    NotificationData.Loaded.SizeOfImage = DllLoaded->SizeOfImage;
    NotificationData.Loaded.DllBase     = DllLoaded->DllBase;

    LeGetGlobalData()->DllNotification(LDR_DLL_NOTIFICATION_REASON_LOADED, &NotificationData);
}

VOID
STDCALL
SE_DllUnloaded(
    PLDR_DATA_TABLE_ENTRY DllUnLoading
)
{
    LDR_DLL_NOTIFICATION_DATA NotificationData;

    NotificationData.Unloaded.BaseDllName   = &DllUnLoading->BaseDllName;
    NotificationData.Unloaded.FullDllName   = &DllUnLoading->FullDllName;
    NotificationData.Unloaded.Flags         = 0;
    NotificationData.Unloaded.SizeOfImage   = DllUnLoading->SizeOfImage;
    NotificationData.Unloaded.DllBase       = DllUnLoading->DllBase;

    LeGetGlobalData()->DllNotification(LDR_DLL_NOTIFICATION_REASON_UNLOADED, &NotificationData);
}

VOID
STDCALL
SE_GetProcAddressLoad(
    PLDR_DATA_TABLE_ENTRY LdrEntryLinks
)
{
}

VOID
STDCALL
SE_ProcessDying(
    VOID
)
{
    ;
}

_ML_C_TAIL_

#include "D3DHook.h"

BOOLEAN
STDCALL
SE_InstallBeforeInit(
    PUNICODE_STRING     ModuleLoading,
    PSHIM_ENGINE_DATA   ShimData
)
{
    UNREFERENCED_PARAMETER(ModuleLoading);
    UNREFERENCED_PARAMETER(ShimData);

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
    CheckDllLoadUnLoad(DllLoaded, TRUE);
}

VOID
STDCALL
SE_DllUnloaded(
    PLDR_DATA_TABLE_ENTRY DllUnLoading
)
{
    CheckDllLoadUnLoad(DllUnLoading, FALSE);
}

VOID
STDCALL
SE_GetProcAddressLoad(
    PLDR_DATA_TABLE_ENTRY LdrEntryLinks
)
{
    UNREFERENCED_PARAMETER(LdrEntryLinks);
}

VOID
STDCALL
SE_ProcessDying(
    VOID
)
{
    ;
}

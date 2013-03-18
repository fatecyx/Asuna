#include "stdafx.h"

PVOID LeGetGetCurrentNlsCache()
{
    PULONG          CurrentNlsNode;
    PULONG_PTR      NlsCache;
    PLeGlobalData   GlobalData = LeGetGlobalData();

    NlsCache = (PULONG_PTR)GlobalData->GetCurrentNlsCache();

    CurrentNlsNode = (PULONG)NlsCache[2];
    if (CurrentNlsNode == NULL)
        return NlsCache;

    *CurrentNlsNode = GlobalData->GetLeb()->LocaleID;

    return NlsCache;
}

NTSTATUS LeGlobalData::HookKernel32Routines(PVOID Kernel32)
{
    PVOID KernelBase, GetUserDefaultLCID, GetCurrentNlsCache;

    WriteLog(L"hook k32");

    KernelBase = FindLdrModuleByName(&WCS2US(L"KERNELBASE.dll"))->DllBase;

    GetUserDefaultLCID = EATLookupRoutineByHashPNoFix(KernelBase, KERNEL32_GetUserDefaultLCID);
    if (GetUserDefaultLCID == NULL)
        return STATUS_NOT_FOUND;

    GetCurrentNlsCache = NULL;

    WalkOpCodeT(GetUserDefaultLCID, 0x10,
        WalkOpCodeM(Buffer, OpLength, Ret)
        {
            switch (Buffer[0])
            {
                case CALL:
                    GetCurrentNlsCache = GetCallDestination(Buffer);
                    return STATUS_SUCCESS;
            }

            return STATUS_NOT_FOUND;
        }
    );

    if (GetCurrentNlsCache == NULL)
        return STATUS_NOT_FOUND;

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_JUMP(GetCurrentNlsCache, LeGetGetCurrentNlsCache, HookStub.StubGetCurrentNlsCache),
    };

    return Nt_PatchMemory(NULL, 0, f, countof(f));
}

NTSTATUS LeGlobalData::UnHookKernel32Routines()
{
    return 0;
}

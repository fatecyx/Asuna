#define CINTERFACE 1

#include "D3DHook.h"
#include "HookInterface8.h"

static PDHOOK_HOOK_INFO DInput8CallbackContext;

TYPE_OF(DirectInput8Create) *StubDirectInput8Create;

HRESULT
(WINAPI
*StubGetDeviceState)(
    PVOID Device,
    ULONG DataSize,
    PVOID Data
);

HRESULT
(WINAPI
*StubGetDeviceData)(
    PVOID                   Device,
    ULONG                   ObjectDataSize,
    LPDIDEVICEOBJECTDATA    ObjectData,
    PULONG                  OutputSize,
    ULONG                   Flags
);

HRESULT
WINAPI
HookGetDeviceStateInternal(
    PVOID   Device,
    ULONG   DataSize,
    PVOID   Data,
    BOOL    Unicode
)
{
    DHOOK_CALLBACK_PARAMETER Parameter;

    Parameter.Version   = DInputVersion8;
    Parameter.Device    = Device;
    Parameter.Function  = DInputGetDeviceState;

    Parameter.dinput8.GetState.Unicode  = Unicode;
    Parameter.dinput8.GetState.DataSize = DataSize;
    Parameter.dinput8.GetState.Data     = Data;

    if (!NT_SUCCESS(OnGetDeviceState(DInput8CallbackContext, &Parameter)))
        return S_OK;

    return StubGetDeviceState(Device, DataSize, Data);
}

HRESULT
HookGetDeviceDataInternal(
    PVOID                   Device,
    ULONG                   ObjectDataSize,
    LPDIDEVICEOBJECTDATA    ObjectData,
    PULONG                  OutputSize,
    ULONG                   Flags,
    BOOL                    Unicode
)
{
    DHOOK_CALLBACK_PARAMETER Parameter;

    Parameter.Version   = DInputVersion8;
    Parameter.Device    = Device;
    Parameter.Function  = DInputGetDeviceData;

    Parameter.dinput8.GetData.Unicode           = Unicode;
    Parameter.dinput8.GetData.ObjectDataSize    = ObjectDataSize;
    Parameter.dinput8.GetData.ObjectData        = ObjectData;
    Parameter.dinput8.GetData.OutputSize        = OutputSize;
    Parameter.dinput8.GetData.Flags             = Flags;

    if (!NT_SUCCESS(OnGetDeviceData(DInput8CallbackContext, &Parameter)))
        return S_OK;

    return StubGetDeviceData(Device, ObjectDataSize, ObjectData, OutputSize, Flags);
}

HRESULT
WINAPI
HookGetDeviceStateW(
    LPDIRECTINPUTDEVICE8W   Device,
    ULONG                   DataSize,
    PVOID                   Data
)
{
    return HookGetDeviceStateInternal(Device, DataSize, Data, TRUE);
}

HRESULT
WINAPI
HookGetDeviceDataW(
    LPDIRECTINPUTDEVICE8W   Device,
    ULONG                   ObjectDataSize,
    LPDIDEVICEOBJECTDATA    ObjectData,
    PULONG                  OutputSize,
    ULONG                   Flags
)
{
    return HookGetDeviceDataInternal(Device, ObjectDataSize, ObjectData, OutputSize, Flags, TRUE);
}

HRESULT
WINAPI
HookGetDeviceStateA(
    LPDIRECTINPUTDEVICE8A   Device,
    ULONG                   DataSize,
    PVOID                   Data
)
{
    return HookGetDeviceStateInternal(Device, DataSize, Data, FALSE);
}

HRESULT
WINAPI
HookGetDeviceDataA(
    LPDIRECTINPUTDEVICE8A   Device,
    ULONG                   ObjectDataSize,
    LPDIDEVICEOBJECTDATA    ObjectData,
    PULONG                  OutputSize,
    ULONG                   Flags
)
{
    return HookGetDeviceDataInternal(Device, ObjectDataSize, ObjectData, OutputSize, Flags, FALSE);
}

HRESULT
WINAPI
HookDirectInput8Create(
    PVOID       ModuleBase,
    ULONG       Version,
    REFIID      IID,
    PVOID*      Out,
    LPUNKNOWN   UnknownOuter
)
{
    HRESULT Result;
    PVOID   HookGetDeviceData, HookGetDeviceState;

    Result = StubDirectInput8Create((HINSTANCE)ModuleBase, Version, IID, Out, UnknownOuter);
    if (FAILED(Result))
        return Result;

    if (IID == IID_IDirectInput8A)
    {
        HookGetDeviceData   = HookGetDeviceDataA;
        HookGetDeviceState  = HookGetDeviceStateA;
    }
    else if (IID == IID_IDirectInput8W)
    {
        HookGetDeviceData   = HookGetDeviceDataW;
        HookGetDeviceState  = HookGetDeviceStateW;
    }
    else
    {
        return Result;
    }

    SCOPE_EXIT
    {
        Nt_RestoreMemory(&StubDirectInput8Create);
    }
    SCOPE_EXIT_END;

    LPDIRECTINPUT8W         DInput8W;
    LPDIRECTINPUTDEVICE8W   KeyboardW;

    DInput8W = (LPDIRECTINPUT8W)*Out;
    if (FAILED(IDirectInput8_CreateDevice(DInput8W, GUID_SysKeyboard, &KeyboardW, NULL)))
        return Result;

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_JUMP(KeyboardW->lpVtbl->GetDeviceState, HookGetDeviceState, StubGetDeviceState),
        INLINE_HOOK_JUMP(KeyboardW->lpVtbl->GetDeviceData,  HookGetDeviceData,  StubGetDeviceData),
    };

    Nt_PatchMemory(NULL, 0, f, countof(f), NULL);

    IDirectInputDevice8_Release(KeyboardW);

    return Result;
}

NTSTATUS HookDirectInput8(PVOID *ModuleBase, PDHOOK_HOOK_INFO Context)
{
    PVOID           DInput8ModuleBase;
    NTSTATUS        Status;
    UNICODE_STRING  DllName;
    LPDIRECTINPUT8W dinput;

    HRESULT (WINAPI *DirectInput8Create)(HINSTANCE, DWORD, REFIID, PVOID*, LPUNKNOWN);

    Status  = STATUS_UNSUCCESSFUL;
    dinput  = NULL;

    LOOP_ONCE
    {
        RTL_CONST_STRING(DllName, L"dinput8.dll");

        Status = LdrGetDllHandle(NULL, 0, &DllName, &DInput8ModuleBase);
        if (!NT_SUCCESS(Status))
            return Status;

        Status = STATUS_UNSUCCESSFUL;

        *(PVOID *)&DirectInput8Create = Nt_GetProcAddress(DInput8ModuleBase, "DirectInput8Create");
        if (DirectInput8Create == NULL)
            break;

        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_JUMP(DirectInput8Create, HookDirectInput8Create, StubDirectInput8Create),
        };

        Status = Nt_PatchMemory(NULL, 0, f, countof(f), NULL);

        if (ModuleBase != NULL)
            *ModuleBase = DInput8ModuleBase;

        DInput8CallbackContext = Context;
    }

    return Status;
}

NTSTATUS UnHookDirectInput8(PVOID ModuleBase)
{
    Nt_RestoreMemory(&StubDirectInput8Create);
    Nt_RestoreMemory(&StubGetDeviceState);
    Nt_RestoreMemory(&StubGetDeviceData);

    return STATUS_SUCCESS;
}

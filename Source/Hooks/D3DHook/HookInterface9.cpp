#define CINTERFACE 1

#include "D3DHook.h"
#include "HookInterface9.h"

static PDHOOK_HOOK_INFO D3D9Context;

IDirect3D9*
(STDCALL
*StubDirect3DCreate9)(
    ULONG Version
);

HRESULT
(STDCALL
*StubDirect3DCreateDevice9)(
    IDirect3D9             *This,
    UINT                    Adapter,
    D3DDEVTYPE              DeviceType,
    HWND                    hFocusWindow,
    ULONG                   BehaviorFlags,
    D3DPRESENT_PARAMETERS*  PresentationParameters,
    IDirect3DDevice9**      ReturnedDeviceInterface
);

HRESULT
(STDCALL
*StubDirect3DDeviceRelease9)(
    IDirect3DDevice9 *Device
);

HRESULT
(STDCALL
*StubDirect3DDeviceReset9)(
    IDirect3DDevice9        *Device,
    D3DPRESENT_PARAMETERS   *pPresentationParameters
);

HRESULT
(STDCALL
*StubDirect3DDevicePresent9)(
    IDirect3DDevice9   *Device,
    PRECT               SourceRect,
    PRECT               DestRect,
    HWND                DestWindowOverride,
    PRGNDATA            DirtyRegion
);

HRESULT
STDCALL
Direct3DDeviceReset9(
    IDirect3DDevice9        *Device,
    D3DPRESENT_PARAMETERS   *PresentationParameters
)
{
    HRESULT                 Result;
    DHOOK_CALLBACK_PARAMETER  Parameter;

    Parameter.Version   = D3dVersion9;
    Parameter.Function  = D3dFunctionLost;
    Parameter.Device    = Device;

    Result = OnLostDevice(D3D9Context, &Parameter);

    Result = StubDirect3DDeviceReset9(Device, PresentationParameters);
    if (FAILED(Result))
        return Result;

    Parameter.Version                                   = D3dVersion9;
    Parameter.Function                                  = D3dFunctionReset;
    Parameter.Device                                    = Device;
    Parameter.d3d9.ResetDevice.PresentationParameters   = PresentationParameters;

    OnResetDevice(D3D9Context, &Parameter);

    return Result;
}

HRESULT
STDCALL
Direct3DDeviceRelease9(
    IDirect3DDevice9 *Device
)
{
    ULONG RefCount = StubDirect3DDeviceRelease9(Device);

    if (RefCount == 1)
    {
        DHOOK_CALLBACK_PARAMETER Parameter;

        Parameter.Version   = D3dVersion9;
        Parameter.Function  = D3dFunctionDestroy;
        Parameter.Device    = Device;

        if (!FAILED(OnDestroyDevice(D3D9Context, &Parameter)))
            RefCount = StubDirect3DDeviceRelease9(Device);
    }

    return RefCount;
}

HRESULT
STDCALL
Direct3DDevicePresent9(
    IDirect3DDevice9   *Device,
    PRECT               SourceRect,
    PRECT               DestRect,
    HWND                DestWindowOverride,
    PRGNDATA            DirtyRegion
)
{
    HRESULT Result;
    DHOOK_CALLBACK_PARAMETER Parameter;

    Parameter.Version                               = D3dVersion9;
    Parameter.Function                              = D3dFunctionRenderFrame;
    Parameter.Device                                = Device;
    Parameter.d3d9.RenderFrame.SourceRect           = SourceRect;
    Parameter.d3d9.RenderFrame.DestRect             = DestRect;
    Parameter.d3d9.RenderFrame.DestWindowOverride   = DestWindowOverride;
    Parameter.d3d9.RenderFrame.DirtyRegion          = DirtyRegion;

    Result = OnRenderFrame(D3D9Context, &Parameter);
    if (FAILED(Result))
        return S_OK;

    Result = StubDirect3DDevicePresent9(Device, SourceRect, DestRect, DestWindowOverride, DirtyRegion);

    return Result;
}

HRESULT
STDCALL
HookDirect3DCreateDevice9(
    IDirect3D9             *This,
    UINT                    Adapter,
    D3DDEVTYPE              DeviceType,
    HWND                    hFocusWindow,
    ULONG                   BehaviorFlags,
    D3DPRESENT_PARAMETERS*  PresentationParameters,
    IDirect3DDevice9**      ReturnedDeviceInterface
)
{
    HRESULT                 Result;
    HWND                    hGameMainWindow;
    DHOOK_CALLBACK_PARAMETER  Parameter;

    Result = StubDirect3DCreateDevice9(
                This,
                Adapter,
                DeviceType,
                hFocusWindow,
                BehaviorFlags,
                PresentationParameters,
                ReturnedDeviceInterface
             );
    if (FAILED(Result))
        return Result;

    (*ReturnedDeviceInterface)->lpVtbl->AddRef(*ReturnedDeviceInterface);

    Nt_RestoreMemory(&StubDirect3DCreateDevice9);

    hGameMainWindow = hFocusWindow == NULL ? PresentationParameters->hDeviceWindow : hFocusWindow;

    Parameter.Version                                   = D3dVersion9;
    Parameter.Function                                  = D3dFunctionCreate;
    Parameter.Device                                    = *ReturnedDeviceInterface;
    Parameter.d3d9.CreateDevice.MainWindow              = hGameMainWindow;
    Parameter.d3d9.CreateDevice.Windowed                = PresentationParameters->Windowed;
    Parameter.d3d9.CreateDevice.PresentationParameters  = PresentationParameters;

    if (FAILED(OnCreateDevice(D3D9Context, &Parameter)))
        return Result;

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_JUMP((*ReturnedDeviceInterface)->lpVtbl->Release,   Direct3DDeviceRelease9,  StubDirect3DDeviceRelease9),
        INLINE_HOOK_JUMP((*ReturnedDeviceInterface)->lpVtbl->Reset,     Direct3DDeviceReset9,    StubDirect3DDeviceReset9),
        INLINE_HOOK_JUMP((*ReturnedDeviceInterface)->lpVtbl->Present,   Direct3DDevicePresent9, StubDirect3DDevicePresent9),
    };

    Nt_PatchMemory(NULL, 0, f, countof(f), NULL);

    return Result;
}

IDirect3D9* WINAPI HookDirect3DCreate9(ULONG Version)
{
    IDirect3D9 *d3d;

    d3d = StubDirect3DCreate9(Version);
    if (d3d == NULL)
        return d3d;

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_JUMP(d3d->lpVtbl->CreateDevice, HookDirect3DCreateDevice9, StubDirect3DCreateDevice9),
    };

    Nt_RestoreMemory(&StubDirect3DCreate9);
    Nt_PatchMemory(NULL, 0, f, countof(f), NULL);

    return d3d;
}

NTSTATUS HookDirect3D9(PVOID *ModuleBase, PDHOOK_HOOK_INFO Context)
{
    PVOID           D3D9ModuleBase;
    NTSTATUS        Status;
    UNICODE_STRING  DllName;
    IDirect3D9     *d3d;

    IDirect3D9* (WINAPI *Direct3DCreate9)(UINT);

    Status  = STATUS_UNSUCCESSFUL;
    d3d     = NULL;

    LOOP_ONCE
    {
        RTL_CONST_STRING(DllName, L"d3d9.dll");

        Status = LdrGetDllHandle(NULL, 0, &DllName, &D3D9ModuleBase);
        if (!NT_SUCCESS(Status))
            return Status;

        Status = STATUS_UNSUCCESSFUL;

        *(PVOID *)&Direct3DCreate9 = Nt_GetProcAddress(D3D9ModuleBase, "Direct3DCreate9");
        if (Direct3DCreate9 == NULL)
            break;

        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_JUMP(Direct3DCreate9, HookDirect3DCreate9, StubDirect3DCreate9),
        };

        Status = Nt_PatchMemory(NULL, 0, f, countof(f), NULL);

        if (ModuleBase != NULL)
            *ModuleBase = D3D9ModuleBase;

        D3D9Context = Context;
    }

    return Status;
}

NTSTATUS UnHookDirect3D9(PVOID ModuleBase)
{
    UNREFERENCED_PARAMETER(ModuleBase);

    Nt_RestoreMemory(&StubDirect3DCreate9);
    Nt_RestoreMemory(&StubDirect3DCreateDevice9);
    Nt_RestoreMemory(&StubDirect3DDeviceRelease9);
    Nt_RestoreMemory(&StubDirect3DDeviceReset9);
    Nt_RestoreMemory(&StubDirect3DDevicePresent9);

    return STATUS_SUCCESS;
}

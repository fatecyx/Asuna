#ifndef _D3DHOOK_H_43d3c89f_33d4_4e4f_af35_fc79ca7141b7_
#define _D3DHOOK_H_43d3c89f_33d4_4e4f_af35_fc79ca7141b7_

#include "MyLibrary.h"
#include "DXUTLite.h"

#define DIRECTINPUT_VERSION 0x800

// Direct3D9 includes
#include <d3d9.h>
#include <d3dx9.h>

// Direct3D10 includes
#include <d3dcommon.h>
#include <dxgi.h>
#include <d3d10_1.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include <d3dx10.h>
#include <dinput.h>

#pragma warning(disable:4201)

typedef struct
{
    union
    {
        struct
        {
            UCHAR D3D8Hooked    : 1;
            UCHAR D3D9Hooked    : 1;
            UCHAR D3D10Hooked   : 1;
            UCHAR D3D11Hooked   : 1;
            UCHAR DInput8Hooked : 1;
            UCHAR Windowed      : 1;
        };

        ULONG D3DFlags;
    };

    PVOID   D3D8Module;
    PVOID   D3D9Module;
    PVOID   D3D10Module;
    PVOID   D3D11Module;
    PVOID   DInput8Module;

    HWND    MainWindow;

    union
    {

#define DHOOK_KEY_PRESSED       (1 << 0)
#define DHOOK_KEY_RELEASED      (1 << 1)
#define DHOOK_MOUSE_PRESSED     (1 << 2)
#define DHOOK_MOUSE_RELEASED    (1 << 3)

        struct
        {
            UCHAR KeyPressed        : 1;
            UCHAR KeyReleased       : 1;
            UCHAR MousePressed      : 1;
            UCHAR MouseReleased     : 1;
            UCHAR ShowDialog        : 1;
        };

        ULONG WindowFlags;
    };

//    LARGE_INTEGER KeyboardHandledTimeStamp;
//    LARGE_INTEGER MouseHandledTimeStamp;
//    LARGE_INTEGER CounterPerThreshold;

    DXUTLite *dxut;

    struct DINPUT_DEVICE_POOL
    {
        PVOID Device;
        ULONG Type;
    } DinputDevicePool[7];

} DHOOK_HOOK_INFO, *PDHOOK_HOOK_INFO;

typedef enum
{
    D3dFunctionCreate,
    D3dFunctionLost,
    D3dFunctionReset,
    D3dFunctionDestroy,
    D3dFunctionChange,
    D3dFunctionRenderFrame,
    DInputAcquireDevice,
    DInputGetDeviceState,
    DInputGetDeviceData,
};

typedef struct
{
    ULONG Version;
    ULONG Function;

    union
    {
        PVOID                    Device;
        IDirect3DDevice9        *Device9;
        IDirectInputDevice8A    *Dinput8A;
        IDirectInputDevice8W    *Dinput8W;
    };

    union
    {
        union
        {
            struct
            {
                HWND                    MainWindow;
                BOOL                    Windowed;
                D3DPRESENT_PARAMETERS*  PresentationParameters;

            } CreateDevice;

            struct
            {
                D3DPRESENT_PARAMETERS*  PresentationParameters;

            } LostDevice;

            struct
            {
                D3DPRESENT_PARAMETERS*  PresentationParameters;

            } ResetDevice;

            struct
            {
                ;
            } DestroyDevice;

            struct
            {
                ;
            } ChangeDevice;

            struct
            {
                PRECT       SourceRect;
                PRECT       DestRect;
                HWND        DestWindowOverride;
                PRGNDATA    DirtyRegion;

            } RenderFrame;

        } d3d9;

        union
        {
            
        } d3d10;

        union
        {
            struct
            {
                BOOL Unicode;
            } AcquireDevice;

            struct
            {
                BOOL    Unicode;
                ULONG   DataSize;
                PVOID   Data;

            } GetState;

            struct
            {
                BOOL                    Unicode;
                ULONG                   ObjectDataSize;
                LPDIDEVICEOBJECTDATA    ObjectData;
                PULONG                  OutputSize;
                ULONG                   Flags;

            } GetData;

        } dinput8;
    };

} DHOOK_CALLBACK_PARAMETER, *PDHOOK_CALLBACK_PARAMETER;

VOID
CheckDllLoadUnLoad(
    PLDR_DATA_TABLE_ENTRY   DllEntry,
    BOOL                    Loading
);

NTSTATUS
OnCreateDevice(
    PDHOOK_HOOK_INFO          Info,
    PDHOOK_CALLBACK_PARAMETER Parameter
);

NTSTATUS
OnLostDevice(
    PDHOOK_HOOK_INFO          Info,
    PDHOOK_CALLBACK_PARAMETER Parameter
);

NTSTATUS
OnResetDevice(
    PDHOOK_HOOK_INFO          Info,
    PDHOOK_CALLBACK_PARAMETER Parameter
);

NTSTATUS
OnDestroyDevice(
    PDHOOK_HOOK_INFO          Info,
    PDHOOK_CALLBACK_PARAMETER Parameter
);

NTSTATUS
OnRenderFrame(
    PDHOOK_HOOK_INFO          Info,
    PDHOOK_CALLBACK_PARAMETER Parameter
);

NTSTATUS
OnAcqureDevice(
    PDHOOK_HOOK_INFO              Info,
    PDHOOK_CALLBACK_PARAMETER   Parameter
);

NTSTATUS
OnGetDeviceState(
    PDHOOK_HOOK_INFO              Info,
    PDHOOK_CALLBACK_PARAMETER   Parameter
);

NTSTATUS
OnGetDeviceData(
    PDHOOK_HOOK_INFO              Info,
    PDHOOK_CALLBACK_PARAMETER   Parameter
);

#endif // _D3DHOOK_H_43d3c89f_33d4_4e4f_af35_fc79ca7141b7_

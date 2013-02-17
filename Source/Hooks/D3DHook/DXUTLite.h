#ifndef _DXUTLITE_H_08b98108_299c_451b_96e3_a30ad0487f74_
#define _DXUTLITE_H_08b98108_299c_451b_96e3_a30ad0487f74_

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "usp10.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma warning(disable:4101)
#pragma warning(disable:4197)

#include "MyLibrary.h"
#include "DXUT/DXUT.h"
#include "DXUT/DXUTConfig.h"

enum
{
    D3dVersionNone,
    D3dVersion9,
    D3dVersion10,
    DInputVersion8,
};

class DXUTLite
{
public:
    enum NotifyRoutineClass
    {
        NotifyCreateDevice,
        NotifyResetDevice,
        NotifyDeviceChange,
        NotifyLostDevice,
        NotifyDestroyDevice,
        NotifyRenderFrame,
        NotifyMessageProc,
        NotifyKeyboardProc,
        NotifyMouseProc,

        NotifyRoutineMax,
    };

    enum WindowTypeClass
    {
        WindowAnsi,
        WindowUnicode,
    };

protected:
    typedef
    HRESULT
    (CALLBACK
    *CreateDeviceNotifyRoutine)(
        IDirect3DDevice9   *Device,
        D3DSURFACE_DESC    *BackBufferSurfaceDesc,
        PVOID               UserContext
    );

    typedef
    HRESULT
    (CALLBACK
    *ResetDeviceNotifyRoutine)(
        IDirect3DDevice9    *Device,
        D3DSURFACE_DESC     *BackBufferSurfaceDesc,
        PVOID                UserContext
    );

    typedef
    HRESULT
    (CALLBACK
    *LostDeviceNotifyRoutine)(
        PVOID UserContext
    );

    typedef
    HRESULT
    (CALLBACK
    *DestroyDeviceNotifyRoutine)(
        PVOID UserContext
    );

    typedef
    HRESULT
    (CALLBACK
    *FrameRenderRoutine)(
        IDirect3DDevice9   *Device,
        double              Time,
        float               ElapsedTime,
        PVOID               UserContext
    );

    typedef
    LRESULT
    (CALLBACK
    *MessageProcRoutine)(
        HWND        hWnd,
        UINT        Message,
        WPARAM      wParam,
        LPARAM      lParam,
        BOOL       &NoFurtherProcessing,
        PVOID       UserContext
    );

    typedef
    HRESULT
    (CALLBACK
    *KeyboardProcRoutine)(
        UINT    nChar,
        BOOL    KeyDown,
        BOOL    AltDown,
        PVOID   UserContext
    );

    typedef
    HRESULT
    (CALLBACK
    *MouseProcRoutine)(
        BOOL    LeftButtonDown,
        BOOL    RightButtonDown,
        BOOL    MiddleButtonDown,
        BOOL    SideButton1Down,
        BOOL    SideButton2Down,
        LONG    MouseWheelDelta,
        LONG    xPos,
        LONG    yPos,
        PVOID   UserContext
    );

    typedef
    NTSTATUS
    (STDCALL
    *QueryPerformanceCounterRoutine)(
        PLARGE_INTEGER  Counter
    );

    typedef struct
    {
        PVOID Routine;
        PVOID Context;

    } DXUT_NOTIFY_ROUTINE;

protected:
    ULONG           m_D3DVersion;
    HWND            m_hWndFocus;
    LARGE_INTEGER   m_BaseTime;
    LARGE_INTEGER   m_LastTimeStamp;
    LARGE_INTEGER   m_TicksPerSecond;

    QueryPerformanceCounterRoutine m_QueryPerformanceCounter;

    DXUT_NOTIFY_ROUTINE m_NotifyRoutine[NotifyRoutineMax];
    PVOID               m_Direct3DDevice;

    union
    {
        struct
        {
            D3DSURFACE_DESC BackBufferDesc;

        } d3d9;

    } m_DeviceInfo;

public:
    DXUTLite();

    PVOID   SetNotifyRoutine(NotifyRoutineClass RoutineType, PVOID Routine, PVOID Context);
    WNDPROC SetWindowProc(HWND hWnd);

    VOID TimerReset();

    VOID
    TimerGetTime(
        PLARGE_INTEGER TimeNow          = NULL,
        PLARGE_INTEGER TimeElapsed      = NULL,
        PLARGE_INTEGER TicksPerSecond   = NULL
    );

    HWND SetFocusWindow(HWND FocusWindow);
    HWND GetFocusWindow();

    HRESULT CreateDevice(PVOID Device, ULONG D3DVersion);
    HRESULT CreateDevice9(IDirect3DDevice9 *Device);
    HRESULT CreateDevice10();

    HRESULT LostDevice(PVOID Device);
    HRESULT LostDevice9(IDirect3DDevice9 *Device);
    HRESULT LostDevice10();

    HRESULT ResetDevice(PVOID Device);
    HRESULT ResetDevice9(IDirect3DDevice9 *Device);
    HRESULT ResetDevice10();

    HRESULT DestroyDevice(PVOID Device);
    HRESULT DestroyDevice9(IDirect3DDevice9 *Device);
    HRESULT DestroyDevice10();

    HRESULT RenderFrame(PVOID Device);
    HRESULT FrameRender9(IDirect3DDevice9 *Device);
    HRESULT Render10();

    LRESULT
    RealWindowProc(
        HWND    hWnd,
        UINT    Message,
        WPARAM  wParam,
        LPARAM  lParam,
        BOOL    UnicodeWindow,
        BOOL    &Handled
    );

protected:
    BOOL CheckDeviceValid(PVOID Device);
};

inline ULONG GetDefTextureFullPath(PWSTR Path, ULONG Count)
{
    ULONG Length;

    static WCHAR TextureFolder[] = L"Texture\\";

    Length = Nt_GetModulePath(&__ImageBase, Path, Count);
    if (Length + CONST_STRLEN(TextureFolder) >= Count)
    {
        Path[0] = 0;
        return 0;
    }

    CopyStruct(Path + Length, TextureFolder, sizeof(TextureFolder));

    return Length + CONST_STRLEN(TextureFolder);
}

#if DISABLE_DXUT_DEBUG
#   define DXUT_DbgPrint(...)
#else

#   define DXUT_DbgPrint(...) (AllocConsole(), PrintConsoleW(__VA_ARGS__))
#endif

NTSTATUS InitializeDXUTLite(DXUTLite **DXUTObject = NULL);
NTSTATUS UnInitializeDXUTLite();

#endif // _DXUTLITE_H_08b98108_299c_451b_96e3_a30ad0487f74_

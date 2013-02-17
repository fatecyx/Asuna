#include "DXUTLite.h"
#include <DXUT.h>

DXUTLite *g_dxut;

NTSTATUS InitializeDXUTLite(DXUTLite **DXUTObject /* = NULL */)
{
    DXUTLite *dxut;

    dxut = new DXUTLite;
    if (dxut == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    g_dxut = dxut;

    if (DXUTObject != NULL)
        *DXUTObject = dxut;

    return STATUS_SUCCESS;
}

NTSTATUS UnInitializeDXUTLite()
{
    SAFE_DELETE(g_dxut);

    return STATUS_SUCCESS;
}

double WINAPI DXUTGetTime()
{
    LARGE_INTEGER TimeNow;

    g_dxut->TimerGetTime(&TimeNow, NULL);

    return (double)TimeNow.QuadPart;
}

HWND WINAPI DXUTGetHWND()
{
    return g_dxut->GetFocusWindow();
}

/************************************************************************
  DXUTLite impl
************************************************************************/

NTSTATUS STDCALL QueryPerformanceCounterNT5(PLARGE_INTEGER Counter)
{
    LARGE_INTEGER Frequency;
    return NtQueryPerformanceCounter(Counter, &Frequency);
}

DXUTLite::DXUTLite()
{
    m_D3DVersion        = 0;
    m_hWndFocus         = NULL;
    m_Direct3DDevice    = NULL;

    NtQueryPerformanceCounter(&m_BaseTime, &m_TicksPerSecond);
    m_LastTimeStamp = m_BaseTime;

    m_QueryPerformanceCounter = (QueryPerformanceCounterRoutine)Nt_GetProcAddress(GetNtdllHandle(), "RtlQueryPerformanceCounter");
    m_QueryPerformanceCounter = m_QueryPerformanceCounter == NULL ? QueryPerformanceCounterNT5 : m_QueryPerformanceCounter;

    ZeroMemory(m_NotifyRoutine, sizeof(m_NotifyRoutine));
}

PVOID
DXUTLite::
SetNotifyRoutine(
    NotifyRoutineClass  RoutineType,
    PVOID               Routine,
    PVOID               Context
)
{
    if ((ULONG)RoutineType >= (ULONG)NotifyRoutineMax)
        return NULL;

    DXUT_NOTIFY_ROUTINE *NotifyRoutine;

    NotifyRoutine = m_NotifyRoutine + RoutineType;

    Routine = _InterlockedExchangePointer(&NotifyRoutine->Routine, Routine);
    NotifyRoutine->Context = Context;

    return Routine;
}

VOID DXUTLite::TimerReset()
{
    m_QueryPerformanceCounter(&m_BaseTime);
}

VOID
DXUTLite::
TimerGetTime(
    PLARGE_INTEGER TimeNow          /* = NULL */,
    PLARGE_INTEGER TimeElapsed      /* = NULL */,
    PLARGE_INTEGER TicksPerSecond   /* = NULL */
)
{
    LARGE_INTEGER Time;

    m_QueryPerformanceCounter(&Time);

    if (TimeNow != NULL)
        TimeNow->QuadPart = Time.QuadPart - m_BaseTime.QuadPart;

    if (TimeElapsed != NULL)
        TimeElapsed->QuadPart = Time.QuadPart - m_LastTimeStamp.QuadPart;

    if (TicksPerSecond != NULL)
        TicksPerSecond->QuadPart = m_TicksPerSecond.QuadPart;

    m_LastTimeStamp = Time;
}

HWND DXUTLite::SetFocusWindow(HWND FocusWindow)
{
    m_hWndFocus = FocusWindow;
    return m_hWndFocus;
}

HWND DXUTLite::GetFocusWindow()
{
    return m_hWndFocus;
}

BOOL DXUTLite::CheckDeviceValid(PVOID Device)
{
    return Device != NULL && Device == m_Direct3DDevice;
}

/************************************************************************
  notify callbacks
************************************************************************/

HRESULT DXUTLite::CreateDevice(PVOID Device, ULONG D3DVersion)
{
    if (m_Direct3DDevice != NULL)
    {
        DestroyDevice(m_Direct3DDevice);
    }

    m_D3DVersion = D3DVersion;
    switch (m_D3DVersion)
    {
        case D3dVersion9:
            return CreateDevice9((IDirect3DDevice9 *)Device);

        case D3dVersion10:
            break;
    }

    return E_NOTIMPL;
}

HRESULT DXUTLite::CreateDevice9(IDirect3DDevice9 *Device)
{
    HRESULT              Result;
    DXUT_NOTIFY_ROUTINE *Routine;
    IDirect3DSurface9   *BackBuffer;

    Routine = &m_NotifyRoutine[NotifyCreateDevice];
    if (Routine->Routine == NULL)
        return S_OK;

    BackBuffer = NULL;
    Result = Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BackBuffer);
    if (FAILED(Result))
        return Result;

    Result = BackBuffer->GetDesc(&m_DeviceInfo.d3d9.BackBufferDesc);
    if (FAILED(Result))
    {
        BackBuffer->Release();
        return Result;
    }

    Result = ((CreateDeviceNotifyRoutine)Routine->Routine)(
                Device,
                &m_DeviceInfo.d3d9.BackBufferDesc,
                Routine->Context
              );

    BackBuffer->Release();

    if (!FAILED(Result))
        m_Direct3DDevice = Device;

    return Result;
}

HRESULT DXUTLite::RenderFrame(PVOID Device)
{
    if (!CheckDeviceValid(Device))
        return E_FAIL;

    switch (m_D3DVersion)
    {
        case D3dVersion9:
            return FrameRender9((IDirect3DDevice9 *)Device);

        case D3dVersion10:
            break;
    }

    return E_NOTIMPL;
}

HRESULT DXUTLite::FrameRender9(IDirect3DDevice9 *Device)
{
    DOUBLE               ElapsedTime, AbsoluteTime;
    LARGE_INTEGER        TimeNow, TimeElapsed, Ticks;
    HRESULT              Result;
    DXUT_NOTIFY_ROUTINE *Routine;

    Routine = &m_NotifyRoutine[NotifyRenderFrame];
    if (Routine->Routine == NULL)
        return S_OK;

    TimerGetTime(&TimeNow, &TimeElapsed, &Ticks);

    ElapsedTime     = (DOUBLE)TimeElapsed.QuadPart / Ticks.QuadPart;
    AbsoluteTime    = (DOUBLE)TimeNow.QuadPart / Ticks.QuadPart;

    Result = ((FrameRenderRoutine)Routine->Routine)(
                Device,
                AbsoluteTime,
                (FLOAT)ElapsedTime,
                Routine->Context
             );

    return Result;
}

HRESULT DXUTLite::LostDevice(PVOID Device)
{
    if (!CheckDeviceValid(Device))
        return E_FAIL;

    switch (m_D3DVersion)
    {
        case D3dVersion9:
            return LostDevice9((IDirect3DDevice9 *)Device);

        case D3dVersion10:
            break;
    }

    return E_NOTIMPL;
}

HRESULT DXUTLite::LostDevice9(IDirect3DDevice9 *Device)
{
    HRESULT              Result;
    DXUT_NOTIFY_ROUTINE *Routine;

    Routine = &m_NotifyRoutine[NotifyLostDevice];
    if (Routine->Routine == NULL)
        return S_OK;

    Result = ((LostDeviceNotifyRoutine)Routine->Routine)(
                Routine->Context
             );

    return Result;
}

HRESULT DXUTLite::ResetDevice(PVOID Device)
{
    if (!CheckDeviceValid(Device))
        return E_FAIL;

    switch (m_D3DVersion)
    {
        case D3dVersion9:
            return ResetDevice9((IDirect3DDevice9 *)Device);

        case D3dVersion10:
            break;
    }

    return E_NOTIMPL;
}

HRESULT DXUTLite::ResetDevice9(IDirect3DDevice9 *Device)
{
    HRESULT              Result;
    DXUT_NOTIFY_ROUTINE *Routine;
    IDirect3DSurface9   *BackBuffer;

    Routine = &m_NotifyRoutine[NotifyResetDevice];
    if (Routine->Routine == NULL)
        return S_OK;

    BackBuffer = NULL;
    Result = Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BackBuffer);
    if (FAILED(Result))
        return Result;

    Result = BackBuffer->GetDesc(&m_DeviceInfo.d3d9.BackBufferDesc);
    if (FAILED(Result))
    {
        BackBuffer->Release();
        return Result;
    }

    Result = ((ResetDeviceNotifyRoutine)Routine->Routine)(
                Device,
                &m_DeviceInfo.d3d9.BackBufferDesc,
                Routine->Context
              );

    BackBuffer->Release();

    return Result;
}

HRESULT DXUTLite::DestroyDevice(PVOID Device)
{
    if (!CheckDeviceValid(Device))
        return E_FAIL;

    switch (m_D3DVersion)
    {
        case D3dVersion9:
            return DestroyDevice9((IDirect3DDevice9 *)Device);

        case D3dVersion10:
            break;
    }

    return E_NOTIMPL;
}

HRESULT DXUTLite::DestroyDevice9(IDirect3DDevice9 *Device)
{
    HRESULT              Result;
    DXUT_NOTIFY_ROUTINE *Routine;
    
    Routine = &m_NotifyRoutine[NotifyResetDevice];
    if (Routine->Routine == NULL)
        return S_OK;
    
    Result = ((DestroyDeviceNotifyRoutine)Routine->Routine)(
                Routine->Context
             );

    m_Direct3DDevice = NULL;
    m_D3DVersion = D3dVersionNone;

    return Result;
}

LRESULT
DXUTLite::
RealWindowProc(
    HWND    hWnd,
    UINT    Message,
    WPARAM  wParam,
    LPARAM  lParam,
    BOOL    UnicodeWindow,
    BOOL    &Handled
)
{
    LONG    MouseButtonState, MouseWheelDelta, X, Y;
    BOOL    KeyDown, AltDown;
    BOOL    LeftButton, RightButton, MiddleButton, SideButton1, SideButton2;
    LRESULT Result;

    if (hWnd != m_hWndFocus)
        return 0;

    union
    {
        DXUT_NOTIFY_ROUTINE NotifyRoutine;
        KeyboardProcRoutine KeyboardProc;
        MessageProcRoutine  MessageProc;
        MouseProcRoutine    MouseProc;
    };

    Result = NO_ERROR;

    switch (Message)
    {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
            NotifyRoutine = m_NotifyRoutine[NotifyKeyboardProc];
            if (NotifyRoutine.Routine == NULL)
                break;

            KeyDown = (Message == WM_KEYDOWN || Message == WM_SYSKEYDOWN);
            AltDown = FLAG_ON(lParam, 1 << 29);

            KeyboardProc((UINT)wParam, KeyDown, AltDown, NotifyRoutine.Context);
            break;

        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_LBUTTONDBLCLK:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MBUTTONDBLCLK:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_RBUTTONDBLCLK:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
        case WM_XBUTTONDBLCLK:
        case WM_MOUSEWHEEL:
        case WM_MOUSEMOVE:
            NotifyRoutine = m_NotifyRoutine[NotifyKeyboardProc];
            if (NotifyRoutine.Routine == NULL)
                break;

            X = LOWORD(lParam);
            Y = HIWORD(lParam);

            MouseWheelDelta     = (Message == WM_MOUSEWHEEL) ? HIWORD(wParam) : 0;
            MouseButtonState    = LOWORD(wParam);
            LeftButton          = FLAG_ON(MouseButtonState, MK_LBUTTON);
            RightButton         = FLAG_ON(MouseButtonState, MK_RBUTTON);
            MiddleButton        = FLAG_ON(MouseButtonState, MK_MBUTTON);
            SideButton1         = FLAG_ON(MouseButtonState, MK_XBUTTON1);
            SideButton2         = FLAG_ON(MouseButtonState, MK_XBUTTON2);

            MouseProc(
                LeftButton,
                RightButton,
                MiddleButton,
                SideButton1,
                SideButton2,
                MouseWheelDelta,
                X,
                Y,
                NotifyRoutine.Context
            );
            break;
    }

    NotifyRoutine = m_NotifyRoutine[NotifyMessageProc];
    if (NotifyRoutine.Routine != NULL)
    {
        Result = MessageProc(hWnd, Message, wParam, lParam, Handled, NotifyRoutine.Context);
        if (Handled)
            return Result;
    }

    return Result;
}

#ifndef _DIRECTDRAWHOOK_H_
#define _DIRECTDRAWHOOK_H_

#define _WIN32_WINNT 0x502

#include "pragma_once.h"
#include <Windows.h>
#include "my_headers.h"
#include <ddraw.h>

typedef struct
{
    PVOID pfOrigCallback;
    PVOID pvOrigContext;
    PVOID Context;
} CALL_BACK_PARAM;

typedef union
{
    struct
    {
        unsigned long Data1;
        unsigned long Data2;
        unsigned long Data3;
        unsigned long Data4;
    } s;
    GUID guid;
} MY_GUID;

struct DDRAW_HOOK_OPTION
{
    BOOL  bWindowMode;
    PRECT prcWindow;

    DDRAW_HOOK_OPTION()
    {
        bWindowMode = FALSE;
        prcWindow   = NULL;
    }
};

#define DDRAW_SetDisplayMode_Offset 0x54

class MyDirectDraw : public IDirectDraw7
{
public:
    DDRAW_HOOK_OPTION m_Option;

protected:
    ULONG         m_RefCount, m_Version;
    LPDIRECTDRAW7 m_pDirectDraw;

public:
    MyDirectDraw();
    MyDirectDraw(LPDIRECTDRAW7 pDD, DDRAW_HOOK_OPTION *pOption = NULL);

    HRESULT CreateDirectDraw(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter);
    HRESULT SetOption(DDRAW_HOOK_OPTION *pOption);

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj);
    STDMETHOD_(ULONG,AddRef) (THIS);
    STDMETHOD_(ULONG,Release) (THIS);
    /*** IDirectDraw methods ***/
    STDMETHOD(Compact)(THIS);
    STDMETHOD(CreateClipper)(THIS_ DWORD, LPDIRECTDRAWCLIPPER*, IUnknown * );
    STDMETHOD(CreatePalette)(THIS_ DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE*, IUnknown * );
    STDMETHOD(CreateSurface)(THIS_  LPDDSURFACEDESC2, LPDIRECTDRAWSURFACE7 *, IUnknown *);
    STDMETHOD(DuplicateSurface)( THIS_ LPDIRECTDRAWSURFACE7, LPDIRECTDRAWSURFACE7 * );
    STDMETHOD(EnumDisplayModes)( THIS_ DWORD, LPDDSURFACEDESC2, LPVOID, LPDDENUMMODESCALLBACK2 );
    STDMETHOD(EnumSurfaces)(THIS_ DWORD, LPDDSURFACEDESC2, LPVOID,LPDDENUMSURFACESCALLBACK7 );
    STDMETHOD(FlipToGDISurface)(THIS);
    STDMETHOD(GetCaps)( THIS_ LPDDCAPS, LPDDCAPS);
    STDMETHOD(GetDisplayMode)( THIS_ LPDDSURFACEDESC2);
    STDMETHOD(GetFourCCCodes)(THIS_  LPDWORD, LPDWORD );
    STDMETHOD(GetGDISurface)(THIS_ LPDIRECTDRAWSURFACE7 *);
    STDMETHOD(GetMonitorFrequency)(THIS_ LPDWORD);
    STDMETHOD(GetScanLine)(THIS_ LPDWORD);
    STDMETHOD(GetVerticalBlankStatus)(THIS_ LPBOOL );
    STDMETHOD(Initialize)(THIS_ GUID *);
    STDMETHOD(RestoreDisplayMode)(THIS);
    STDMETHOD(SetCooperativeLevel)(THIS_ HWND, DWORD);
    STDMETHOD(SetDisplayMode)(THIS_ DWORD, DWORD,DWORD, DWORD, DWORD);
    STDMETHOD(WaitForVerticalBlank)(THIS_ DWORD, HANDLE );
    /*** Added in the v2 interface ***/
    STDMETHOD(GetAvailableVidMem)(THIS_ LPDDSCAPS2, LPDWORD, LPDWORD);
    /*** Added in the V4 Interface ***/
    STDMETHOD(GetSurfaceFromDC) (THIS_ HDC, LPDIRECTDRAWSURFACE7 *);
    STDMETHOD(RestoreAllSurfaces)(THIS);
    STDMETHOD(TestCooperativeLevel)(THIS);
    STDMETHOD(GetDeviceIdentifier)(THIS_ LPDDDEVICEIDENTIFIER2, DWORD );
    STDMETHOD(StartModeTest)(THIS_ LPSIZE, DWORD, DWORD );
    STDMETHOD(EvaluateMode)(THIS_ DWORD, DWORD * );
};

class MyDirectDrawSurface : public IDirectDrawSurface7
{
public:
    DDRAW_HOOK_OPTION m_Option;

protected:
    ULONG m_RefCount;
    LPDIRECTDRAWSURFACE7 m_pDDSurface;

    friend MyDirectDraw;

protected:
    BOOL ConvertSurface16To32(MyDirectDrawSurface *lpDDSurface, LPRECT lpDestRect);
    HRESULT
    EnumDeleteAttachedSurfaceWorker(
        LPDIRECTDRAWSURFACE7 lpDDSurface,
        LPDDSURFACEDESC2     lpDDSurfaceDesc,
        BOOL                 bRelease
    );

    static
    HRESULT
    WINAPI
    EnumDeleteAttachedSurface(
        LPDIRECTDRAWSURFACE7 lpDDSurface,
        LPDDSURFACEDESC2     lpDDSurfaceDesc,
        CALL_BACK_PARAM     *pContext
    );

public:
    MyDirectDrawSurface();
    MyDirectDrawSurface(LPDIRECTDRAWSURFACE7 pDDS, DDRAW_HOOK_OPTION *pOption = NULL);


    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj);
    STDMETHOD_(ULONG,AddRef) (THIS);
    STDMETHOD_(ULONG,Release) (THIS);
    /*** IDirectDrawSurface methods ***/
    STDMETHOD(AddAttachedSurface)(THIS_ LPDIRECTDRAWSURFACE7);
    STDMETHOD(AddOverlayDirtyRect)(THIS_ LPRECT);
    STDMETHOD(Blt)(THIS_ LPRECT,LPDIRECTDRAWSURFACE7, LPRECT,DWORD, LPDDBLTFX);
    STDMETHOD(BltBatch)(THIS_ LPDDBLTBATCH, DWORD, DWORD );
    STDMETHOD(BltFast)(THIS_ DWORD,DWORD,LPDIRECTDRAWSURFACE7, LPRECT,DWORD);
    STDMETHOD(DeleteAttachedSurface)(THIS_ DWORD,LPDIRECTDRAWSURFACE7);
    STDMETHOD(EnumAttachedSurfaces)(THIS_ LPVOID,LPDDENUMSURFACESCALLBACK7);
    STDMETHOD(EnumOverlayZOrders)(THIS_ DWORD,LPVOID,LPDDENUMSURFACESCALLBACK7);
    STDMETHOD(Flip)(THIS_ LPDIRECTDRAWSURFACE7, DWORD);
    STDMETHOD(GetAttachedSurface)(THIS_ LPDDSCAPS2, LPDIRECTDRAWSURFACE7 *);
    STDMETHOD(GetBltStatus)(THIS_ DWORD);
    STDMETHOD(GetCaps)(THIS_ LPDDSCAPS2);
    STDMETHOD(GetClipper)(THIS_ LPDIRECTDRAWCLIPPER*);
    STDMETHOD(GetColorKey)(THIS_ DWORD, LPDDCOLORKEY);
    STDMETHOD(GetDC)(THIS_ HDC *);
    STDMETHOD(GetFlipStatus)(THIS_ DWORD);
    STDMETHOD(GetOverlayPosition)(THIS_ LPLONG, LPLONG );
    STDMETHOD(GetPalette)(THIS_ LPDIRECTDRAWPALETTE*);
    STDMETHOD(GetPixelFormat)(THIS_ LPDDPIXELFORMAT);
    STDMETHOD(GetSurfaceDesc)(THIS_ LPDDSURFACEDESC2);
    STDMETHOD(Initialize)(THIS_ LPDIRECTDRAW, LPDDSURFACEDESC2);
    STDMETHOD(IsLost)(THIS);
    STDMETHOD(Lock)(THIS_ LPRECT,LPDDSURFACEDESC2,DWORD,HANDLE);
    STDMETHOD(ReleaseDC)(THIS_ HDC);
    STDMETHOD(Restore)(THIS);
    STDMETHOD(SetClipper)(THIS_ LPDIRECTDRAWCLIPPER);
    STDMETHOD(SetColorKey)(THIS_ DWORD, LPDDCOLORKEY);
    STDMETHOD(SetOverlayPosition)(THIS_ LONG, LONG );
    STDMETHOD(SetPalette)(THIS_ LPDIRECTDRAWPALETTE);
    STDMETHOD(Unlock)(THIS_ LPRECT);
    STDMETHOD(UpdateOverlay)(THIS_ LPRECT, LPDIRECTDRAWSURFACE7,LPRECT,DWORD, LPDDOVERLAYFX);
    STDMETHOD(UpdateOverlayDisplay)(THIS_ DWORD);
    STDMETHOD(UpdateOverlayZOrder)(THIS_ DWORD, LPDIRECTDRAWSURFACE7);
    /*** Added in the v2 interface ***/
    STDMETHOD(GetDDInterface)(THIS_ LPVOID *);
    STDMETHOD(PageLock)(THIS_ DWORD);
    STDMETHOD(PageUnlock)(THIS_ DWORD);
    /*** Added in the v3 interface ***/
    STDMETHOD(SetSurfaceDesc)(THIS_ LPDDSURFACEDESC2, DWORD);
    /*** Added in the v4 interface ***/
    STDMETHOD(SetPrivateData)(THIS_ REFGUID, LPVOID, DWORD, DWORD);
    STDMETHOD(GetPrivateData)(THIS_ REFGUID, LPVOID, LPDWORD);
    STDMETHOD(FreePrivateData)(THIS_ REFGUID);
    STDMETHOD(GetUniquenessValue)(THIS_ LPDWORD);
    STDMETHOD(ChangeUniquenessValue)(THIS);
    /*** Moved Texture7 methods here ***/
    STDMETHOD(SetPriority)(THIS_ DWORD);
    STDMETHOD(GetPriority)(THIS_ LPDWORD);
    STDMETHOD(SetLOD)(THIS_ DWORD);
    STDMETHOD(GetLOD)(THIS_ LPDWORD);
};

#endif // _DIRECTDRAWHOOK_H_
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

#include "DirectDrawHook.h"

MY_GUID IID_DDRAW_HOOK = {TAG4('DIRE'), TAG4('CTDR'), TAG4('AWHO'), TAG2('OK') };

#define IS_INTERFACE_HOOKED(p) ((BOOL)((p) != NULL && (*(PVOID *)this) == (*(PVOID *)(p))))
#define DD_IF_HOOK_RESTORE(p) \
            if (IS_INTERFACE_HOOKED(p)) \
            { \
                (p) = ((MyDirectDraw *)(PVOID)p)->m_pDirectDraw; \
            }

#define DDS_IF_HOOK_RESTORE(p) \
            if (IS_INTERFACE_HOOKED(p)) \
            { \
                (p) = ((MyDirectDrawSurface *)(PVOID)p)->m_pDDSurface; \
            }

HRESULT GetHookedInterface(LPDIRECTDRAWSURFACE7 pDDS, MyDirectDrawSurface **pMyDDS)
{
    DWORD Size;

    if (pDDS == NULL || pMyDDS == NULL)
        return DDERR_INVALIDPARAMS;

    Size = sizeof(pMyDDS);
    return pDDS->GetPrivateData(IID_DDRAW_HOOK.guid, pMyDDS, &Size);
}

/************************************************************************
  MyDirectDraw
************************************************************************/

MyDirectDraw::MyDirectDraw()
{
    m_pDirectDraw   = NULL;
    m_RefCount      = 1;
    m_Version       = 7;
}

MyDirectDraw::MyDirectDraw(LPDIRECTDRAW7 pDD, DDRAW_HOOK_OPTION *pOption /* = NULL */)
{
    m_pDirectDraw   = pDD;
    m_RefCount      = 1;
    m_Version       = 7;
    if (pOption != NULL)
        m_Option = *pOption;
}

HRESULT MyDirectDraw::CreateDirectDraw(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter)
{
    HRESULT hResult;

    hResult = ::DirectDrawCreate(lpGUID, (LPDIRECTDRAW *)&m_pDirectDraw, pUnkOuter);
    if (!SUCCEEDED(hResult))
        return hResult;

    *(MyDirectDraw **)lplpDD = this;

    return hResult;
}

HRESULT MyDirectDraw::SetOption(DDRAW_HOOK_OPTION *pOption)
{
    if (pOption == NULL)
        return DDERR_INVALIDPARAMS;

    m_Option = *pOption;

    return DD_OK;
}

/************************************************************************
  IUnknown methods
************************************************************************/

HRESULT STDCALL MyDirectDraw::QueryInterface(REFIID iid, PVOID *ppvObject)
{
    ULONG   Version;
    HRESULT hResult;

    if (iid == IID_IDirectDraw4)
        Version = 4;
    else if (iid == IID_IDirectDraw7)
        Version = 7;
    else if (iid == IID_IDirectDraw2)
        Version = 2;
    else if (iid == IID_IDirectDraw)
        Version = 1;
    else
        Version = -1;

    hResult = m_pDirectDraw->QueryInterface(Version != -1 ? IID_IDirectDraw7 : iid, ppvObject);
    if (!SUCCEEDED(hResult) || Version == -1)
        return hResult;

    MyDirectDraw *pDD = new MyDirectDraw((LPDIRECTDRAW7)*ppvObject, &m_Option);
    if (pDD == NULL)
        return hResult;

    pDD->m_Version = Version;
    *(MyDirectDraw **)ppvObject = pDD;
    return hResult;
}

ULONG STDCALL MyDirectDraw::AddRef()
{
    return _InterlockedIncrement((PLONG)&m_RefCount);
}

ULONG STDCALL MyDirectDraw::Release()
{
    ULONG RefCount;

    RefCount = _InterlockedDecrement((PLONG)&m_RefCount);
    if (RefCount == 0)
    {
        if (m_pDirectDraw != NULL)
            m_pDirectDraw->Release();
        delete this;
    }

    return RefCount;
}

/************************************************************************
  IDirectDraw methods
************************************************************************/

HRESULT
STDCALL
MyDirectDraw::
CreateClipper(
    DWORD dwFlags,
    LPDIRECTDRAWCLIPPER *lplpDDClipper,
    IUnknown *pUnkOuter
)
{
    return m_pDirectDraw->CreateClipper(dwFlags, lplpDDClipper, pUnkOuter);
}

HRESULT
STDCALL
MyDirectDraw::
CreatePalette(
    DWORD                dwFlags,
    LPPALETTEENTRY       lpColorTable,
    LPDIRECTDRAWPALETTE *lplpDDPalette,
    IUnknown            *pUnkOuter
)
{
    return m_pDirectDraw->CreatePalette(dwFlags, lpColorTable, lplpDDPalette, pUnkOuter);
}

HRESULT
STDCALL
MyDirectDraw::
CreateSurface(
    LPDDSURFACEDESC2      lpDDSurfaceDesc,
    LPDIRECTDRAWSURFACE7 *lplpDDSurface,
    IUnknown             *pUnkOuter
)
{
    HRESULT hResult;
    MyDirectDrawSurface *pDDS;
    extern WCHAR path[MAX_PATH];
    FILE *fp;

    if (lpDDSurfaceDesc->dwHeight == (DWORD)GetSystemMetrics(SM_CYSCREEN) &&
        lpDDSurfaceDesc->dwWidth  == (DWORD)GetSystemMetrics(SM_CXSCREEN))
    {
        lpDDSurfaceDesc->dwWidth = 640;
        lpDDSurfaceDesc->dwHeight = 480;
/*
        DDSURFACEDESC2 dds;
        dds.dwSize = sizeof(dds);
        (*lplpDDSurface)->Lock(NULL, &dds, 0, NULL);
        (*lplpDDSurface)->Unlock(NULL);
*/
    }
/*
    fp = _wfopen(path, L"ab");
    if (fp)
    {
        fprintf(
            fp,
            "Return     = %8X\r\n"
            "this       = %08X\r\n"
            "Width      = %08X\r\n"
            "Height     = %08X\r\n"
            "dwFlagfs   = %08X\r\n"
            "\r\n",
            _ReturnAddress(),
            this,
            lpDDSurfaceDesc->dwWidth,
            lpDDSurfaceDesc->dwHeight,
            lpDDSurfaceDesc->dwFlags);

        fclose(fp);
    }
*/
    hResult = m_pDirectDraw->CreateSurface(lpDDSurfaceDesc, lplpDDSurface, pUnkOuter);
    if (!SUCCEEDED(hResult))
        return hResult;

    pDDS = new MyDirectDrawSurface(*lplpDDSurface, &m_Option);
    if (pDDS == NULL)
        return hResult;

    *(MyDirectDrawSurface **)lplpDDSurface = pDDS;
    return hResult;
}

HRESULT STDCALL MyDirectDraw::Compact()
{
    return m_pDirectDraw->Compact();
}

HRESULT
STDCALL
MyDirectDraw::
DuplicateSurface(
    LPDIRECTDRAWSURFACE7  lpDDSurface,
    LPDIRECTDRAWSURFACE7 *lplpDupDDSurface
)
{
    HRESULT hResult;
    LPDIRECTDRAWSURFACE7 lpDDSurfaceToDuplicate;
    MyDirectDrawSurface *pDDS;

    lpDDSurfaceToDuplicate = lpDDSurface;
    DDS_IF_HOOK_RESTORE(lpDDSurfaceToDuplicate);

    hResult = m_pDirectDraw->DuplicateSurface(lpDDSurfaceToDuplicate, lplpDupDDSurface);
    if (!SUCCEEDED(hResult) || !IS_INTERFACE_HOOKED(lpDDSurface))
        return hResult;

    pDDS = new MyDirectDrawSurface(*lplpDupDDSurface, &((MyDirectDrawSurface *)lpDDSurface)->m_Option);
    if (pDDS == NULL)
        return hResult;

    *(MyDirectDrawSurface **)lplpDupDDSurface = pDDS;
    return hResult;
}

//HRESULT WINAPI EnumModesCallback(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext);

HRESULT
STDCALL
MyDirectDraw::
EnumDisplayModes(
    DWORD                  dwFlags,
    LPDDSURFACEDESC2       lpDDSurfaceDesc,
    LPVOID                 lpContext,
    LPDDENUMMODESCALLBACK2 lpEnumCallback
)
{
    return m_pDirectDraw->EnumDisplayModes(dwFlags, lpDDSurfaceDesc, lpContext, lpEnumCallback);
}

HRESULT
WINAPI
DDHook_EnumSurfacesCallback2(
    LPDIRECTDRAWSURFACE7 lpDDSurface,
    LPDDSURFACEDESC2     lpDDSurfaceDesc,
    CALL_BACK_PARAM     *lpContext
)
{
    GetHookedInterface(lpDDSurface, (MyDirectDrawSurface **)&lpDDSurface);
    return ((LPDDENUMSURFACESCALLBACK7)lpContext->pfOrigCallback)(lpDDSurface, lpDDSurfaceDesc, lpContext->pvOrigContext);
}

HRESULT
STDCALL
MyDirectDraw::
EnumSurfaces(
    DWORD                     dwFlags,
    LPDDSURFACEDESC2          lpDDSD,
    LPVOID                    lpContext,
    LPDDENUMSURFACESCALLBACK7 lpEnumCallback
)
{
    CALL_BACK_PARAM Param = { lpEnumCallback, lpContext, this };
    return m_pDirectDraw->EnumSurfaces(dwFlags, lpDDSD, &Param, (LPDDENUMSURFACESCALLBACK7)DDHook_EnumSurfacesCallback2);
}

HRESULT STDCALL MyDirectDraw::FlipToGDISurface()
{
    return m_pDirectDraw->FlipToGDISurface();
}

HRESULT STDCALL MyDirectDraw::GetCaps(LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps)
{
    return m_pDirectDraw->GetCaps(lpDDDriverCaps, lpDDHELCaps);
}

HRESULT STDCALL MyDirectDraw::GetDisplayMode(LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    return m_pDirectDraw->GetDisplayMode(lpDDSurfaceDesc);
}

HRESULT STDCALL MyDirectDraw::GetFourCCCodes(DWORD *lpNumCodes, DWORD *lpCodes)
{
    return m_pDirectDraw->GetFourCCCodes(lpNumCodes, lpCodes);
}

HRESULT STDCALL MyDirectDraw::GetGDISurface(LPDIRECTDRAWSURFACE7 *lplpGDIDDSSurface)
{
    HRESULT hResult;

    hResult = m_pDirectDraw->GetGDISurface(lplpGDIDDSSurface);
    if (!SUCCEEDED(hResult))
        return hResult;

    GetHookedInterface(*lplpGDIDDSSurface, (MyDirectDrawSurface **)lplpGDIDDSSurface);
    return hResult;
}

HRESULT STDCALL MyDirectDraw::GetMonitorFrequency(LPDWORD lpdwFrequency)
{
    return m_pDirectDraw->GetMonitorFrequency(lpdwFrequency);
}

HRESULT STDCALL MyDirectDraw::GetScanLine(LPDWORD lpdwScanLine)
{
    return m_pDirectDraw->GetScanLine(lpdwScanLine);
}

HRESULT STDCALL MyDirectDraw::GetVerticalBlankStatus(LPBOOL lpbIsInVB)
{
    return m_pDirectDraw->GetVerticalBlankStatus(lpbIsInVB);
}

HRESULT STDCALL MyDirectDraw::Initialize(GUID *lpGUID)
{
    return m_pDirectDraw->Initialize(lpGUID);
}

HRESULT STDCALL MyDirectDraw::RestoreDisplayMode()
{
    return m_pDirectDraw->RestoreDisplayMode();
}

HRESULT STDCALL MyDirectDraw::SetCooperativeLevel(HWND hWnd, DWORD dwFlags)
{
    if (m_Option.bWindowMode)
        dwFlags = DDSCL_NORMAL;

    return m_pDirectDraw->SetCooperativeLevel(hWnd, dwFlags);
}

ASM
HRESULT
STDCALL
MyDirectDraw::
SetDisplayMode(
    DWORD dwWidth,
    DWORD dwHeight,
    DWORD dwBPP,
    DWORD dwRefreshRate,
    DWORD dwFlags
)
{
    UNREFERENCED_PARAMETER(dwWidth);
    UNREFERENCED_PARAMETER(dwHeight);
    UNREFERENCED_PARAMETER(dwBPP);
    UNREFERENCED_PARAMETER(dwRefreshRate);
    UNREFERENCED_PARAMETER(dwFlags);
    INLINE_ASM
    {
        mov  eax, [esp+4];
        cmp  [eax]MyDirectDraw.m_Version, 1;
        je   DDRAW_V1;

        cmp  [eax]MyDirectDraw.m_Option.bWindowMode, 0;
        jnz  DDRAW_WNDMODE;

        push [esp+0x18];
        push [esp+0x18];
        push [esp+0x18];
        push [esp+0x18];
        push [esp+0x18];
        mov  eax, [eax]MyDirectDraw.m_pDirectDraw;
        push eax;
        mov  eax, [eax];
        call [eax + DDRAW_SetDisplayMode_Offset];
        ret  0x18;
DDRAW_WNDMODE:
        xor  eax, eax;
        ret  0x18;

DDRAW_V1:
        cmp  [eax]MyDirectDraw.m_Option.bWindowMode, 0;
        jnz  DDRAW_WNDMODE_V1;

        push 0;
        push 0;
        push [esp+0x10];
        push [esp+0x10];
        push [esp+0x10];
        mov  eax, [eax]MyDirectDraw.m_pDirectDraw;
        push eax;
        mov  eax, [eax];
        call [eax + DDRAW_SetDisplayMode_Offset];
        ret  0x10;
DDRAW_WNDMODE_V1:
        xor  eax, eax;
        ret  0x10;
    }
}

HRESULT STDCALL MyDirectDraw::WaitForVerticalBlank(DWORD dwFlags, HANDLE hEvent)
{
    return m_pDirectDraw->WaitForVerticalBlank(dwFlags, hEvent);
}

/************************************************************************
  v2 interface
************************************************************************/

HRESULT
STDCALL
MyDirectDraw::
GetAvailableVidMem(
    LPDDSCAPS2 lpDDSCaps,
    LPDWORD    lpdwTotal,
    LPDWORD    lpdwFree
)
{
    return m_pDirectDraw->GetAvailableVidMem(lpDDSCaps, lpdwTotal, lpdwFree);
}

/************************************************************************
  Added in the V4 Interface
************************************************************************/

HRESULT
STDCALL
MyDirectDraw::
GetSurfaceFromDC(
    HDC                   hDC,
    LPDIRECTDRAWSURFACE7 *lpDDS
)
{
    HRESULT hResult;

    hResult = m_pDirectDraw->GetSurfaceFromDC(hDC, lpDDS);
    if (!SUCCEEDED(hResult))
        return hResult;

    GetHookedInterface(*lpDDS, (MyDirectDrawSurface **)lpDDS);
    return hResult;
}

HRESULT STDCALL MyDirectDraw::RestoreAllSurfaces()
{
    return m_pDirectDraw->RestoreAllSurfaces();
}

HRESULT STDCALL MyDirectDraw::TestCooperativeLevel()
{
    return m_pDirectDraw->TestCooperativeLevel();
}

HRESULT
STDCALL
MyDirectDraw::
GetDeviceIdentifier(
    LPDDDEVICEIDENTIFIER2 lpdddi,
    DWORD                 dwFlags
)
{
    return m_pDirectDraw->GetDeviceIdentifier(lpdddi, dwFlags);
}

HRESULT
STDCALL
MyDirectDraw::
StartModeTest(
    LPSIZE lpModesToTest,
    DWORD  dwNumEntries,
    DWORD  dwFlags
)
{
    return m_pDirectDraw->StartModeTest(lpModesToTest, dwNumEntries, dwFlags);
}

HRESULT STDCALL MyDirectDraw::EvaluateMode(DWORD dwFlags, LPDWORD pSecondsUntilTimeout)
{
    return m_pDirectDraw->EvaluateMode(dwFlags, pSecondsUntilTimeout);
}


/************************************************************************
  MyDirectDrawSurface
************************************************************************/
MyDirectDrawSurface::MyDirectDrawSurface()
{
    m_RefCount = 1;
    m_pDDSurface = NULL;
}

MyDirectDrawSurface::MyDirectDrawSurface(LPDIRECTDRAWSURFACE7 pDDS, DDRAW_HOOK_OPTION *pOption /* = NULL */)
{
    MyDirectDrawSurface *pThis;

    m_RefCount = 1;
    m_pDDSurface = NULL;
    m_pDDSurface = pDDS;

    pThis = this;
    pDDS->SetPrivateData(IID_DDRAW_HOOK.guid, &pThis, sizeof(pThis), 0);
    if (pOption != NULL)
        m_Option = *pOption;
}

/************************************************************************
  IUnknown methods
************************************************************************/
HRESULT STDCALL MyDirectDrawSurface::QueryInterface(REFIID iid, PVOID *ppvObject)
{
    ULONG   Version;
    HRESULT hResult;

    if (iid == IID_IDirectDrawSurface4)
        Version = 4;
    else if (iid == IID_IDirectDrawSurface7)
        Version = 7;
    else if (iid == IID_IDirectDrawSurface2)
        Version = 2;
    else if (iid == IID_IDirectDrawSurface)
        Version = 1;
    else
        Version = -1;

    hResult = m_pDDSurface->QueryInterface(Version != -1 ? IID_IDirectDrawSurface7 : iid, ppvObject);
    if (!SUCCEEDED(hResult) || Version == -1)
        return hResult;

    MyDirectDrawSurface *pDDS = new MyDirectDrawSurface((LPDIRECTDRAWSURFACE7)*ppvObject, &m_Option);
    if (pDDS == NULL)
        return hResult;

    *(MyDirectDrawSurface **)ppvObject = pDDS;

    return hResult;
}

ULONG STDCALL MyDirectDrawSurface::AddRef()
{
    return _InterlockedIncrement((PLONG)&m_RefCount);
}

ULONG STDCALL MyDirectDrawSurface::Release()
{
    ULONG RefCount;

    RefCount = _InterlockedDecrement((PLONG)&m_RefCount);
    if (RefCount == 0)
    {
        if (m_pDDSurface != NULL)
            m_pDDSurface->Release();
        delete this;
    }

    return RefCount;
}

/************************************************************************
  IDirectDrawSurface methods
************************************************************************/

HRESULT STDCALL MyDirectDrawSurface::AddAttachedSurface(LPDIRECTDRAWSURFACE7 lpDDSurface)
{
    DDS_IF_HOOK_RESTORE(lpDDSurface);
    return m_pDDSurface->AddAttachedSurface(lpDDSurface);
}

HRESULT STDCALL MyDirectDrawSurface::AddOverlayDirtyRect(LPRECT lpRect)
{
    return m_pDDSurface->AddOverlayDirtyRect(lpRect);
}

ASM VOID STDCALL ColorConvert32(DWORD dwPixel, LPDWORD lpPixel1, LPDWORD lpPixel2)
{
    UNREFERENCED_PARAMETER(dwPixel);
    UNREFERENCED_PARAMETER(lpPixel1);
    UNREFERENCED_PARAMETER(lpPixel2);
    __asm
    {
        push    ebp
        mov     ebp, esp
        sub     esp, 8
        push    ebx
        mov     eax, dword ptr [ebp+8]
        mov     ebx, dword ptr [ebp+8]
        and     eax, 0FFFFh
        and     ebx, 0FFFF0000h
        shr     ebx, 010h
        shl     eax, 6
        shl     ebx, 6
        shr     ax, 3
        shr     bx, 3
        shr     al, 3
        shr     bl, 3
        shl     eax, 3
        shl     ebx, 3
        mov     dword ptr [ebp-4], eax
        mov     dword ptr [ebp-8], ebx
        mov     eax, dword ptr [ebp+0Ch]
        mov     ecx, dword ptr [ebp-4]
        mov     edx, dword ptr [ebp+010h]
        pop     ebx
        mov     dword ptr [eax], ecx
        mov     eax, dword ptr [ebp-8]
        mov     dword ptr [edx], eax
        mov     al, 1
        mov     esp, ebp
        pop     ebp
        ret     0Ch
    }
}

BOOL MyDirectDrawSurface::ConvertSurface16To32(MyDirectDrawSurface *lpDDSurface, LPRECT lpDestRect)
{
    HRESULT hResult;
    DDSURFACEDESC2 ddsd;

    UNREFERENCED_PARAMETER(lpDestRect);

    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_WIDTH|DDSD_HEIGHT;

    if (lpDestRect == NULL)
    {
        lpDDSurface->m_pDDSurface->GetSurfaceDesc(&ddsd);
        if (ddsd.dwWidth == 640 && ddsd.dwHeight == 480)
            lpDestRect = m_Option.prcWindow;
    }

    ddsd.dwFlags = 0;
    hResult = lpDDSurface->m_pDDSurface->Lock(lpDestRect, &ddsd, DDLOCK_WAIT, NULL);
    if (!SUCCEEDED(hResult))
        return DD_FALSE;

    LONG   lLine = 0, lPixelNumPerLine = ddsd.lPitch / 4;			// Ã¿ÐÐÏñËØÊý
    PBYTE  pbSurface;
    LPVOID lpSurface;

    pbSurface = (PBYTE)AllocStack(ddsd.lPitch);

    lpSurface = ddsd.lpSurface;
    while (lLine < (LONG)ddsd.dwHeight)
    {
        LONG lCount;

        CopyMemory(pbSurface, lpSurface, ddsd.lPitch);
        lCount = lPixelNumPerLine / 2;
        if (lCount > 0)
        {
            LPDWORD lpBakSurface, lpSF;

            lpBakSurface = (LPDWORD)pbSurface;
            lpSF = (LPDWORD)lpSurface;
            while (lCount--)
            {
                ColorConvert32(*lpBakSurface, lpSF, lpSF + 1);
                lpSF += 2;
                ++lpBakSurface;
            }
        }

        lpSurface = (PBYTE)lpSurface + ddsd.dwWidth * 4;
        ++lLine;
    }

    lpDDSurface->m_pDDSurface->Unlock(NULL);
    return DD_OK;
}

#include <set>
using std::set;

HRESULT
STDCALL
MyDirectDrawSurface::
Blt(
    LPRECT               lpDestRect,
    LPDIRECTDRAWSURFACE7 lpDDSrcSurface,
    LPRECT               lpSrcRect,
    DWORD                dwFlags,
    LPDDBLTFX            lpDDBltFx
)
{
    if (IS_INTERFACE_HOOKED(lpDDSrcSurface))
    {
        if (m_Option.bWindowMode)// &&
//            *(PVOID *)0x5244C4 != NULL &&
//            *(PVOID *)0x5244C8 != NULL)
        {

            extern WCHAR path[MAX_PATH];
            static set<PVOID> *retaddr;

            if (retaddr == NULL)
            {
                retaddr = new set<PVOID>;
            }

            if (retaddr != NULL)
            {
                PVOID ret = _ReturnAddress();
/*
              switch ((ULONG_PTR)ret)
              {
                    case 0x452BEA:
                    case 0x452DE3:
                    case 0x45311F:
                    case 0x4531A4:
                    case 0x4531D2:
                    case 0x452840:
                    case 0x452D6E:
                        goto SKIP_CONV;
                }
*/
/*
                if (retaddr->count(ret) == 0)
                {
                    FILE *fp;

                    retaddr->insert(ret);

                    fp = _wfopen(path, L"ab");
                    if (fp)
                    {
                        fprintf(
                            fp,
                            "Return Address = %08X\r\n"
                            "this           = %08X\r\n"
                            "BattleSurface1 = %08X\r\n"
                            "BattleSurface2 = %08X\r\n"
                            "lpDestRect     = %08X\r\n"
                            "lpDDSrcSurface = %08X\r\n"
                            "lpSrcRect      = %08X\r\n"
                            "dwFlags        = %08X\r\n"
                            "lpDDBltFx      = %08X\r\n"
                            "\r\n",
                            ret,
                            this,
                            *(PVOID *)0x5244C4,
                            *(PVOID *)0x5244C8,
                            lpDestRect,
                            lpDDSrcSurface,
                            lpSrcRect,
                            dwFlags,
                            lpDDSrcSurface);
                        fclose(fp);
                    }
                }
*/
            }

            ConvertSurface16To32((MyDirectDrawSurface *)(PVOID)lpDDSrcSurface, lpDestRect);
            if (lpDestRect == NULL)
                lpDestRect = m_Option.prcWindow;
        }

SKIP_CONV:
        lpDDSrcSurface = ((MyDirectDrawSurface *)(PVOID)lpDDSrcSurface)->m_pDDSurface;
    }

    return m_pDDSurface->Blt(lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
}

HRESULT
STDCALL
MyDirectDrawSurface::
BltBatch(
    LPDDBLTBATCH lpDDBltBatch,
    DWORD        dwCount,
    DWORD        dwFlags
)
{
    return m_pDDSurface->BltBatch(lpDDBltBatch, dwCount, dwFlags);
}

HRESULT
STDCALL
MyDirectDrawSurface::
BltFast(
    DWORD dwX,
    DWORD dwY,
    LPDIRECTDRAWSURFACE7 lpDDSrcSurface,
    LPRECT lpSrcRect,
    DWORD dwFlags
)
{
    DDS_IF_HOOK_RESTORE(lpDDSrcSurface);
    return m_pDDSurface->BltFast(dwX, dwY, lpDDSrcSurface, lpSrcRect, dwFlags);
}

HRESULT
WINAPI
MyDirectDrawSurface::
EnumDeleteAttachedSurface(
    LPDIRECTDRAWSURFACE7 lpDDSurface,
    LPDDSURFACEDESC2     lpDDSurfaceDesc,
    CALL_BACK_PARAM     *pContext
)
{
    MyDirectDrawSurface *pDDS;

    pDDS = (MyDirectDrawSurface *)pContext->Context;
    return pDDS->EnumDeleteAttachedSurfaceWorker(lpDDSurface, lpDDSurfaceDesc, (BOOL)pContext->pvOrigContext);
}

HRESULT
MyDirectDrawSurface::
EnumDeleteAttachedSurfaceWorker(
    LPDIRECTDRAWSURFACE7 lpDDSurface,
    LPDDSURFACEDESC2     lpDDSurfaceDesc,
    BOOL                 bRelease
)
{
    HRESULT hResult;

    UNREFERENCED_PARAMETER(lpDDSurfaceDesc);

    hResult = GetHookedInterface(lpDDSurface, (MyDirectDrawSurface **)&lpDDSurface);
    if (SUCCEEDED(hResult) && IS_INTERFACE_HOOKED(lpDDSurface))
    {
        if (!bRelease)
        {
            ((MyDirectDrawSurface *)lpDDSurface)->m_pDDSurface->AddRef();
        }
        else
        {
            if (bRelease == ~TRUE)
                ((MyDirectDrawSurface *)lpDDSurface)->m_pDDSurface->Release();
            ((MyDirectDrawSurface *)lpDDSurface)->Release();
        }
    }

    return DDENUMRET_OK;
}

HRESULT
STDCALL
MyDirectDrawSurface::
DeleteAttachedSurface(
    DWORD dwFlags,
    LPDIRECTDRAWSURFACE7 lpDDSAttachedSurface
)
{
    BOOL    bIsHooked;
    HRESULT hResult;
    LPDIRECTDRAWSURFACE7 pDDSAttached;

    bIsHooked = IS_INTERFACE_HOOKED(lpDDSAttachedSurface);
    if (lpDDSAttachedSurface != NULL)
    {
        if (bIsHooked)
            ((MyDirectDrawSurface *)lpDDSAttachedSurface)->m_pDDSurface->AddRef();
    }
    else
    {
        CALL_BACK_PARAM Param = { NULL, (PVOID)FALSE, this };
        m_pDDSurface->EnumAttachedSurfaces(&Param, (LPDDENUMSURFACESCALLBACK7)EnumDeleteAttachedSurface);
    }

    pDDSAttached = lpDDSAttachedSurface;
    DDS_IF_HOOK_RESTORE(pDDSAttached);
    hResult = m_pDDSurface->DeleteAttachedSurface(dwFlags, pDDSAttached);
    if (lpDDSAttachedSurface != NULL)
    {
        if (!SUCCEEDED(hResult))
            ((MyDirectDrawSurface *)lpDDSAttachedSurface)->m_pDDSurface->Release();
        if (bIsHooked)
            ((MyDirectDrawSurface *)lpDDSAttachedSurface)->m_pDDSurface->Release();
    }
    else
    {
        CALL_BACK_PARAM Param = { NULL, SUCCEEDED(hResult) ? (PVOID)TRUE : (PVOID)~TRUE, this };
        m_pDDSurface->EnumAttachedSurfaces(&Param, (LPDDENUMSURFACESCALLBACK7)EnumDeleteAttachedSurface);
    }

    return hResult;
}

HRESULT
STDCALL
MyDirectDrawSurface::
EnumAttachedSurfaces(
    LPVOID lpContext,
    LPDDENUMSURFACESCALLBACK7 lpEnumSurfacesCallback
)
{
    CALL_BACK_PARAM Param = { lpEnumSurfacesCallback, lpContext, this };
    return m_pDDSurface->EnumAttachedSurfaces(&Param, (LPDDENUMSURFACESCALLBACK7)DDHook_EnumSurfacesCallback2);
}

HRESULT
STDCALL
MyDirectDrawSurface::
EnumOverlayZOrders(
    DWORD dwFlags,
    LPVOID lpContext,
    LPDDENUMSURFACESCALLBACK7 lpfnCallback
)
{
    return m_pDDSurface->EnumOverlayZOrders(dwFlags, lpContext, lpfnCallback);
}

HRESULT
STDCALL
MyDirectDrawSurface::
Flip(
    LPDIRECTDRAWSURFACE7 lpDDSurfaceTargetOverride,
    DWORD dwFlags
)
{
    DDS_IF_HOOK_RESTORE(lpDDSurfaceTargetOverride);
    return m_pDDSurface->Flip(lpDDSurfaceTargetOverride, dwFlags);
}

HRESULT
STDCALL
MyDirectDrawSurface::
GetAttachedSurface(
    LPDDSCAPS2 lpDDSCaps,
    LPDIRECTDRAWSURFACE7 *lplpDDAttachedSurface
)
{
    HRESULT hResult;

    hResult = m_pDDSurface->GetAttachedSurface(lpDDSCaps, lplpDDAttachedSurface);
    if (!SUCCEEDED(hResult))
        return hResult;

    GetHookedInterface(*lplpDDAttachedSurface, (MyDirectDrawSurface **)lplpDDAttachedSurface);
    return hResult;
}

HRESULT STDCALL MyDirectDrawSurface::GetBltStatus(DWORD dwFlags)
{
    return m_pDDSurface->GetBltStatus(dwFlags);
}

HRESULT STDCALL MyDirectDrawSurface::GetCaps(LPDDSCAPS2 lpDDSCaps)
{
    return m_pDDSurface->GetCaps(lpDDSCaps);
}

HRESULT STDCALL MyDirectDrawSurface::GetClipper(LPDIRECTDRAWCLIPPER *lplpDDClipper)
{
    return m_pDDSurface->GetClipper(lplpDDClipper);
}

HRESULT
STDCALL
MyDirectDrawSurface::
GetColorKey(
    DWORD dwFlags,
    LPDDCOLORKEY lpDDColorKey
)
{
    return m_pDDSurface->GetColorKey(dwFlags, lpDDColorKey);
}

HRESULT STDCALL MyDirectDrawSurface::GetDC(HDC *lphDC)
{
    return m_pDDSurface->GetDC(lphDC);
}

HRESULT STDCALL MyDirectDrawSurface::GetFlipStatus(DWORD dwFlags)
{
    return m_pDDSurface->GetFlipStatus(dwFlags);
}

HRESULT STDCALL MyDirectDrawSurface::GetOverlayPosition(LPLONG lplX, LPLONG lplY)
{
    return m_pDDSurface->GetOverlayPosition(lplX, lplY);
}

HRESULT STDCALL MyDirectDrawSurface::GetPalette(LPDIRECTDRAWPALETTE *lplpDDPalette)
{
    return m_pDDSurface->GetPalette(lplpDDPalette);
}

HRESULT STDCALL MyDirectDrawSurface::GetPixelFormat(LPDDPIXELFORMAT lpDDPixelFormat)
{
    HRESULT hResult;

    hResult = m_pDDSurface->GetPixelFormat(lpDDPixelFormat);
    if (!SUCCEEDED(hResult) || !m_Option.bWindowMode)
        return hResult;

    lpDDPixelFormat->dwRBitMask = 0x7C00;
    lpDDPixelFormat->dwGBitMask = 0x3E0;
    lpDDPixelFormat->dwBBitMask = 0x1F;

    return hResult;
}

HRESULT STDCALL MyDirectDrawSurface::GetSurfaceDesc(LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    HRESULT hResult;

    hResult = m_pDDSurface->GetSurfaceDesc(lpDDSurfaceDesc);
    if (!SUCCEEDED(hResult) || !m_Option.bWindowMode)
        return hResult;
/*
    if (lpDDSurfaceDesc->dwHeight == (DWORD)GetSystemMetrics(SM_CYSCREEN) &&
        lpDDSurfaceDesc->dwWidth  == (DWORD)GetSystemMetrics(SM_CXSCREEN))
    {
        lpDDSurfaceDesc->dwHeight = 480;
        lpDDSurfaceDesc->dwWidth  = 640;
    }
*/
    lpDDSurfaceDesc->lPitch /= 2;

    return hResult;
}

HRESULT
STDCALL
MyDirectDrawSurface::
Initialize(
    LPDIRECTDRAW lpDD,
    LPDDSURFACEDESC2 lpDDSurfaceDesc
)
{
    return m_pDDSurface->Initialize(lpDD, lpDDSurfaceDesc);
}

HRESULT STDCALL MyDirectDrawSurface::IsLost()
{
    return m_pDDSurface->IsLost();
}

HRESULT
STDCALL
MyDirectDrawSurface::
Lock(
    LPRECT           lpDestRect,
    LPDDSURFACEDESC2 lpDDSurfaceDesc,
    DWORD            dwFlags,
    HANDLE           hEvent
)
{
    return m_pDDSurface->Lock(lpDestRect, lpDDSurfaceDesc, dwFlags, hEvent);
}

HRESULT STDCALL MyDirectDrawSurface::ReleaseDC(HDC hDC)
{
    return m_pDDSurface->ReleaseDC(hDC);
}

HRESULT STDCALL MyDirectDrawSurface::Restore()
{
    return m_pDDSurface->Restore();
}

HRESULT STDCALL MyDirectDrawSurface::SetClipper(LPDIRECTDRAWCLIPPER lpDDClipper)
{
    return m_pDDSurface->SetClipper(lpDDClipper);
}

HRESULT STDCALL MyDirectDrawSurface::SetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey)
{
    return m_pDDSurface->SetColorKey(dwFlags, lpDDColorKey);
}

HRESULT STDCALL MyDirectDrawSurface::SetOverlayPosition(LONG lX, LONG lY)
{
    return m_pDDSurface->SetOverlayPosition(lX, lY);
}

HRESULT STDCALL MyDirectDrawSurface::SetPalette(LPDIRECTDRAWPALETTE lpDDPalette)
{
    return m_pDDSurface->SetPalette(lpDDPalette);
}

HRESULT STDCALL MyDirectDrawSurface::Unlock(LPRECT lpRect)
{
    return m_pDDSurface->Unlock(lpRect);
}

HRESULT
STDCALL
MyDirectDrawSurface::
UpdateOverlay(
    LPRECT lpSrcRect,
    LPDIRECTDRAWSURFACE7 lpDDDestSurface,
    LPRECT lpDestRect,
    DWORD dwFlags,
    LPDDOVERLAYFX lpDDOverlayFx
)
{
    IS_INTERFACE_HOOKED(lpDDDestSurface);
    return m_pDDSurface->UpdateOverlay(lpSrcRect, lpDDDestSurface, lpDestRect, dwFlags, lpDDOverlayFx);
}

HRESULT STDCALL MyDirectDrawSurface::UpdateOverlayDisplay(DWORD dwFlags)
{
    return m_pDDSurface->UpdateOverlayDisplay(dwFlags);
}

HRESULT
STDCALL
MyDirectDrawSurface::
UpdateOverlayZOrder(
    DWORD dwFlags,
    LPDIRECTDRAWSURFACE7 lpDDSReference
)
{
    IS_INTERFACE_HOOKED(lpDDSReference);
    return m_pDDSurface->UpdateOverlayZOrder(dwFlags, lpDDSReference);
}

/************************************************************************
  Added in the v2 interface
************************************************************************/
HRESULT STDCALL MyDirectDrawSurface::GetDDInterface(LPVOID *lplpDD)
{
    return m_pDDSurface->GetDDInterface(lplpDD);
}

HRESULT STDCALL MyDirectDrawSurface::PageLock(DWORD dwFlags)
{
    return m_pDDSurface->PageLock(dwFlags);
}

HRESULT STDCALL MyDirectDrawSurface::PageUnlock(DWORD dwFlags)
{
    return m_pDDSurface->PageUnlock(dwFlags);
}

/************************************************************************
  Added in the v3 interface
************************************************************************/
HRESULT STDCALL MyDirectDrawSurface::SetSurfaceDesc(LPDDSURFACEDESC2 lpDDsd2, DWORD dwFlags)
{
    return m_pDDSurface->SetSurfaceDesc(lpDDsd2, dwFlags);
}

/************************************************************************
  Added in the v4 interface
************************************************************************/
HRESULT
STDCALL
MyDirectDrawSurface::
SetPrivateData(
    REFGUID guidTag,
    LPVOID lpData,
    DWORD cbSize,
    DWORD dwFlags
)
{
    return m_pDDSurface->SetPrivateData(guidTag, lpData, cbSize, dwFlags);
}

HRESULT
STDCALL
MyDirectDrawSurface::
GetPrivateData(
    REFGUID guidTag,
    LPVOID lpBuffer,
    LPDWORD lpcbBufferSize
)
{
    return m_pDDSurface->GetPrivateData(guidTag, lpBuffer, lpcbBufferSize);
}

HRESULT STDCALL MyDirectDrawSurface::FreePrivateData(REFGUID guidTag)
{
    return m_pDDSurface->FreePrivateData(guidTag);
}

HRESULT STDCALL MyDirectDrawSurface::GetUniquenessValue(LPDWORD lpValue)
{
    return m_pDDSurface->GetUniquenessValue(lpValue);
}

HRESULT STDCALL MyDirectDrawSurface::ChangeUniquenessValue()
{
    return m_pDDSurface->ChangeUniquenessValue();
}

/************************************************************************
  Moved Texture7 methods here
************************************************************************/
HRESULT STDCALL MyDirectDrawSurface::SetPriority(DWORD dwPriority)
{
    return m_pDDSurface->SetPriority(dwPriority);
}

HRESULT STDCALL MyDirectDrawSurface::GetPriority(LPDWORD lpdwPriority)
{
    return m_pDDSurface->GetPriority(lpdwPriority);
}

HRESULT STDCALL MyDirectDrawSurface::SetLOD(DWORD dwMaxLOD)
{
    return m_pDDSurface->SetLOD(dwMaxLOD);
}

HRESULT STDCALL MyDirectDrawSurface::GetLOD(LPDWORD lpdwMaxLOD)
{
    return m_pDDSurface->GetLOD(lpdwMaxLOD);
}

#pragma warning(disable:4100)

#include "d3d8porti.h"

#pragma push_macro("STDMETHODIMPL")
#pragma push_macro("STDMETHODIMPL_")

#undef STDMETHODIMPL
#undef STDMETHODIMPL_

#define STDMETHODIMPL(method) STDMETHODIMP method
#define STDMETHODIMPL_(type, method) STDMETHODIMP_(type) method

/************************************************************************
  Direct3D8Port implement
************************************************************************/

DECL_SELECTANY D3DFORMAT Direct3D8Port::m_Format8[6] =
{
    D3DFMT_A1R5G5B5,
    D3DFMT_A8R8G8B8,
    D3DFMT_R5G6B5,
    D3DFMT_X1R5G5B5,
    D3DFMT_X8R8G8B8,
};

Direct3D8Port::Direct3D8Port(IDirect3D9 *d3d9)
{
    m_d3d9          = d3d9;
    m_QualityLevel  = 0;
}

Direct3D8Port::operator PDIRECT3D9()
{
    return (PDIRECT3D9)this;
}

/*** IUnknown methods ***/
HRESULT Direct3D8Port::QueryInterface8(REFIID riid, void** ppvObj)
{
    return m_d3d9->QueryInterface(riid, ppvObj);
}

ULONG Direct3D8Port::AddRef8()
{
    return m_d3d9->AddRef();
}

ULONG Direct3D8Port::Release8()
{
    return D3DAutoRelease(this, m_d3d9);
}

/*** IDirect3D8 methods ***/
HRESULT Direct3D8Port::RegisterSoftwareDevice8(void* pInitializeFunction)
{
    return m_d3d9->RegisterSoftwareDevice(pInitializeFunction);
}

UINT Direct3D8Port::GetAdapterCount8()
{
    return m_d3d9->GetAdapterCount();
}

HRESULT Direct3D8Port::GetAdapterIdentifier8(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER8* pIdentifier)
{
    HRESULT Result;
    D3DADAPTER_IDENTIFIER9 IDentifier;

    Result = m_d3d9->GetAdapterIdentifier(Adapter, Flags, &IDentifier);
    if (FAILED(Result))
        return Result;

    CopyStruct(pIdentifier->Driver, IDentifier.Driver, FIELD_OFFSET(D3DADAPTER_IDENTIFIER8, DriverVersion));
    CopyStruct(&pIdentifier->DriverVersion, &IDentifier.DriverVersion, sizeof(*pIdentifier) - FIELD_OFFSET(D3DADAPTER_IDENTIFIER8, DriverVersion));

    return Result;
}

UINT Direct3D8Port::GetAdapterModeCount8(UINT Adapter)
{
    ULONG       ModeCount = 0;
    D3DFORMAT  *Format = m_Format8;

    for (ULONG Count = countof(m_Format8); Count; ++Format, --Count)
        ModeCount += m_d3d9->GetAdapterModeCount(Adapter, *Format);

    return ModeCount;
}

HRESULT Direct3D8Port::EnumAdapterModes8(UINT Adapter,UINT Mode,D3DDISPLAYMODE* pMode)
{
    D3DFORMAT  *Format = m_Format8;

    for (ULONG Count = countof(m_Format8); Count; ++Format, --Count)
    {
        ULONG ModeIndex;

        ModeIndex = m_d3d9->GetAdapterModeCount(Adapter, *Format);
        if (ModeIndex == 0)
            continue;

        if (Mode >= ModeIndex)
        {
            Mode -= ModeIndex;
            continue;
        }

        return m_d3d9->EnumAdapterModes(Adapter, *Format, Mode, pMode);
    }

    return E_FAIL;
}

HRESULT Direct3D8Port::GetAdapterDisplayMode8(UINT Adapter,D3DDISPLAYMODE* pMode)
{
    return m_d3d9->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT Direct3D8Port::CheckDeviceType8(UINT Adapter,D3DDEVTYPE CheckType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL Windowed)
{
    return m_d3d9->CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed);
}

HRESULT Direct3D8Port::CheckDeviceFormat8(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat)
{
    return m_d3d9->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT Direct3D8Port::CheckDeviceMultiSampleType8(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType)
{
    return m_d3d9->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, &m_QualityLevel);
}

HRESULT Direct3D8Port::CheckDepthStencilMatch8(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat)
{
    return m_d3d9->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT Direct3D8Port::GetDeviceCaps8(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS8* pCaps)
{
    HRESULT  Result;
    D3DCAPS9 Caps;

    Result = m_d3d9->GetDeviceCaps(Adapter, DeviceType, &Caps);
    if (FAILED(Result))
        return Result;

    D3DCaps9To8(pCaps, &Caps);

    return Result;
}

HMONITOR Direct3D8Port::GetAdapterMonitor8(UINT Adapter)
{
    return m_d3d9->GetAdapterMonitor(Adapter);
}

HRESULT Direct3D8Port::CreateDevice8(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3D8PRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice8** ppReturnedDeviceInterface)
{
    HRESULT                 Result;
    PDIRECT3DDEVICE9        Device9;
    D3DPRESENT_PARAMETERS   PresentParameters;
    Direct3DDevice8Port    *Device8Port;

    PresentParam8To9(pPresentationParameters, &PresentParameters, m_QualityLevel);

    Result = m_d3d9->CreateDevice(
                Adapter,
                DeviceType,
                hFocusWindow,
                BehaviorFlags,
                &PresentParameters,
                &Device9
             );

    if (FAILED(Result))
        return Result;

    Device8Port = NULL;
//    Device8Port = new Direct3DDevice8Port(Device9, this);
    if (Device8Port == NULL)
    {
        Device9->Release();
        return E_OUTOFMEMORY;
    }

    *(PVOID *)ppReturnedDeviceInterface = Device8Port;

    return Result;
}

/************************************************************************
  d3d9 interface
************************************************************************/
HRESULT Direct3D8Port::QueryInterface(REFIID riid, void** ppvObj)
{
    return m_d3d9->QueryInterface(riid, ppvObj);
}

ULONG Direct3D8Port::AddRef()
{
    return m_d3d9->AddRef();
}

ULONG Direct3D8Port::Release()
{
    return D3DAutoRelease(this, m_d3d9);
}

/*** IDirect3D9 methods ***/
HRESULT Direct3D8Port::RegisterSoftwareDevice(void* pInitializeFunction)
{
    return m_d3d9->RegisterSoftwareDevice(pInitializeFunction);
}

UINT Direct3D8Port::GetAdapterCount()
{
    return m_d3d9->GetAdapterCount();
}

HRESULT Direct3D8Port::GetAdapterIdentifier(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier)
{
    return m_d3d9->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT Direct3D8Port::GetAdapterModeCount(UINT Adapter,D3DFORMAT Format)
{
    return m_d3d9->GetAdapterModeCount(Adapter, Format);
}

HRESULT Direct3D8Port::EnumAdapterModes(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode)
{
    return m_d3d9->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

HRESULT Direct3D8Port::GetAdapterDisplayMode(UINT Adapter,D3DDISPLAYMODE* pMode)
{
    return m_d3d9->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT Direct3D8Port::CheckDeviceType(UINT Adapter,D3DDEVTYPE DevType,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed)
{
    return m_d3d9->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
}

HRESULT Direct3D8Port::CheckDeviceFormat(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat)
{
    return m_d3d9->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT Direct3D8Port::CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels)
{
    return m_d3d9->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT Direct3D8Port::CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat)
{
    return m_d3d9->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT Direct3D8Port::CheckDeviceFormatConversion(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat)
{
    return m_d3d9->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT Direct3D8Port::GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps)
{
    return m_d3d9->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR Direct3D8Port::GetAdapterMonitor(UINT Adapter)
{
    return m_d3d9->GetAdapterMonitor(Adapter);
}

HRESULT Direct3D8Port::CreateDevice(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
{
    return m_d3d9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
}

/************************************************************************
  Direct3DDevice8Port implement
************************************************************************/
STDMETHODIMPL(Direct3DDevice8Port::TestCooperativeLevel8)()
{
    return m_Device->TestCooperativeLevel();
}

STDMETHODIMPL_(UINT, Direct3DDevice8Port::GetAvailableTextureMem8)()
{
    return m_Device->GetAvailableTextureMem();
}

STDMETHODIMPL(Direct3DDevice8Port::ResourceManagerDiscardBytes8)(DWORD Bytes)
{
    return m_Device->EvictManagedResources();
}

STDMETHODIMPL(Direct3DDevice8Port::GetDirect3D8)(IDirect3D8** ppD3D8)
{
    m_d3d8->AddRef();
    *(PVOID *)ppD3D8 = m_d3d8;
    return S_OK;
}

STDMETHODIMPL(Direct3DDevice8Port::GetDeviceCaps8)(D3DCAPS8* pCaps)
{
    HRESULT     Result;
    D3DCAPS9    Caps;

    Result = m_Device->GetDeviceCaps(&Caps);
    if (FAILED(Result))
        return Result;

    D3DCaps9To8(pCaps, &Caps);

    return Result;
}

STDMETHODIMPL(Direct3DDevice8Port::GetDisplayMode8)(D3DDISPLAYMODE* pMode)
{
    return m_Device->GetDisplayMode(0, pMode);
}

STDMETHODIMPL(Direct3DDevice8Port::GetCreationParameters8)(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
    return m_Device->GetCreationParameters(pParameters);
}

STDMETHODIMPL(Direct3DDevice8Port::SetCursorProperties8)(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface8* pCursorBitmap)
{
    Direct3DSurface8Port *Cursor = (Direct3DSurface8Port *)(PVOID)pCursorBitmap;
    return m_Device->SetCursorProperties(XHotSpot, YHotSpot, Cursor);
}

STDMETHODIMPL_(void, Direct3DDevice8Port::SetCursorPosition8)(int X,int Y,DWORD Flags)
{
    return m_Device->SetCursorPosition(X, Y, Flags);
}

STDMETHODIMPL_(BOOL, Direct3DDevice8Port::ShowCursor8)(BOOL bShow)
{
    return m_Device->ShowCursor(bShow);
}

STDMETHODIMPL(Direct3DDevice8Port::CreateAdditionalSwapChain8)(D3D8PRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain8** pSwapChain)
{
    HRESULT Result;
    Direct3DSwapChain8Port *SwapChains;
    IDirect3DSwapChain9    *SC9;
    D3DPRESENT_PARAMETERS   PresentParameters;

    PresentParam8To9(pPresentationParameters, &PresentParameters);

    Result = m_Device->CreateAdditionalSwapChain(&PresentParameters, &SC9);
    if (FAILED(Result))
        return Result;

    SwapChains = new Direct3DSwapChain8Port(SC9, this);
    if (SwapChains == NULL)
    {
        SC9->Release();
        return E_OUTOFMEMORY;
    }

    *(PVOID *)pSwapChain = SwapChains;

    return Result;
}

STDMETHODIMPL(Direct3DDevice8Port::Reset8)(D3D8PRESENT_PARAMETERS* pPresentationParameters)
{
    D3DPRESENT_PARAMETERS PresentParameters;

    PresentParam8To9(pPresentationParameters, &PresentParameters);

    return m_Device->Reset(&PresentParameters);
}

STDMETHODIMPL(Direct3DDevice8Port::Present8)(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion)
{
    return m_Device->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

STDMETHODIMPL(Direct3DDevice8Port::GetBackBuffer8)(UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer)
{    
    HRESULT Result;
    IDirect3DSurface9 *Surface9;
    Direct3DSurface8Port *SurfacePort;

    Result = m_Device->GetBackBuffer(0, BackBuffer, Type, &Surface9);
    if (FAILED(Result))
        return Result;

    SurfacePort = new Direct3DSurface8Port(Surface9, this);
    if (SurfacePort == NULL)
    {
        Surface9->Release();
        return E_OUTOFMEMORY;
    }

    *(PVOID *)ppBackBuffer = SurfacePort;

    return Result;
}

STDMETHODIMPL(Direct3DDevice8Port::GetRasterStatus8)(D3DRASTER_STATUS* pRasterStatus)
{
    return m_Device->GetRasterStatus(0, pRasterStatus);
}

STDMETHODIMPL_(void, Direct3DDevice8Port::SetGammaRamp8)(DWORD Flags,CONST D3DGAMMARAMP* pRamp)
{
    return m_Device->SetGammaRamp(0, Flags, pRamp);
}

STDMETHODIMPL_(void, Direct3DDevice8Port::GetGammaRamp8)(D3DGAMMARAMP* pRamp)
{
    return m_Device->GetGammaRamp(0, pRamp);
}

STDMETHODIMPL(Direct3DDevice8Port::CreateTexture8)(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture8** ppTexture)
{
    HRESULT                  Result;
    IDirect3DTexture9       *Texture9;
    Direct3DTexture8Port    *TexturePort;

    Result = m_Device->CreateTexture(Width, Height, Levels, Usage, Format, Pool, &Texture9, NULL);
    if (FAILED(Result))
        return Result;

    TexturePort = new Direct3DTexture8Port(Texture9, this);
    if (TexturePort == NULL)
    {
        Texture9->Release();
        return E_OUTOFMEMORY;
    }

    *(PVOID *)ppTexture = TexturePort;

    return Result;
}

STDMETHODIMPL(Direct3DDevice8Port::CreateVolumeTexture8)(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture8** ppVolumeTexture)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::CreateCubeTexture8)(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture8** ppCubeTexture)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::CreateVertexBuffer8)(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer8** ppVertexBuffer)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::CreateIndexBuffer8)(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer8** ppIndexBuffer)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::CreateRenderTarget8)(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,BOOL Lockable,IDirect3DSurface8** ppSurface)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::CreateDepthStencilSurface8)(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,IDirect3DSurface8** ppSurface)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::CreateImageSurface8)(UINT Width,UINT Height,D3DFORMAT Format,IDirect3DSurface8** ppSurface)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::CopyRects8)(IDirect3DSurface8* pSourceSurface,CONST RECT* pSourceRectsArray,UINT cRects,IDirect3DSurface8* pDestinationSurface,CONST POINT* pDestPointsArray)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::UpdateTexture8)(IDirect3DBaseTexture8* pSourceTexture,IDirect3DBaseTexture8* pDestinationTexture)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::GetFrontBuffer8)(IDirect3DSurface8* pDestSurface)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::SetRenderTarget8)(IDirect3DSurface8* pRenderTarget,IDirect3DSurface8* pNewZStencil)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::GetRenderTarget8)(IDirect3DSurface8** ppRenderTarget)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::GetDepthStencilSurface8)(IDirect3DSurface8** ppZStencilSurface)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::BeginScene8)()
{
    return m_Device->BeginScene();
}

STDMETHODIMPL(Direct3DDevice8Port::EndScene8)()
{
    return m_Device->EndScene();
}

STDMETHODIMPL(Direct3DDevice8Port::Clear8)(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil)
{
    return m_Device->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

STDMETHODIMPL(Direct3DDevice8Port::SetTransform8)(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
{
    return m_Device->SetTransform(State, pMatrix);
}

STDMETHODIMPL(Direct3DDevice8Port::GetTransform8)(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix)
{
    return m_Device->GetTransform(State, pMatrix);
}

STDMETHODIMPL(Direct3DDevice8Port::MultiplyTransform8)(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX *Matrix)
{
    return m_Device->MultiplyTransform(State, Matrix);
}

STDMETHODIMPL(Direct3DDevice8Port::SetViewport8)(CONST D3DVIEWPORT8* pViewport)
{
    return m_Device->SetViewport((D3DVIEWPORT9*)pViewport);
}

STDMETHODIMPL(Direct3DDevice8Port::GetViewport8)(D3DVIEWPORT8* pViewport)
{
    return m_Device->GetViewport((D3DVIEWPORT9*)pViewport);
}

STDMETHODIMPL(Direct3DDevice8Port::SetMaterial8)(CONST D3DMATERIAL8* pMaterial)
{
    return m_Device->SetMaterial((D3DMATERIAL9*)pMaterial);
}

STDMETHODIMPL(Direct3DDevice8Port::GetMaterial8)(D3DMATERIAL8* pMaterial)
{
    return m_Device->GetMaterial((D3DMATERIAL9*)pMaterial);
}

STDMETHODIMPL(Direct3DDevice8Port::SetLight8)(DWORD Index,CONST D3DLIGHT8* Light)
{
    return m_Device->SetLight(Index, (D3DLIGHT9 *)Light);
}

STDMETHODIMPL(Direct3DDevice8Port::GetLight8)(DWORD Index,D3DLIGHT8* Light)
{
    return m_Device->GetLight(Index, (D3DLIGHT9 *)Light);
}

STDMETHODIMPL(Direct3DDevice8Port::LightEnable8)(DWORD Index,BOOL Enable)
{
    return m_Device->LightEnable(Index, Enable);
}

STDMETHODIMPL(Direct3DDevice8Port::GetLightEnable8)(DWORD Index,BOOL* pEnable)
{
    return m_Device->GetLightEnable(Index, pEnable);
}

STDMETHODIMPL(Direct3DDevice8Port::SetClipPlane8)(DWORD Index,CONST float* pPlane)
{
    return m_Device->SetClipPlane(Index, pPlane);
}

STDMETHODIMPL(Direct3DDevice8Port::GetClipPlane8)(DWORD Index,float* pPlane)
{
    return m_Device->GetClipPlane(Index, pPlane);
}

STDMETHODIMPL(Direct3DDevice8Port::SetRenderState8)(D3DRENDERSTATETYPE State,DWORD Value)
{
    return m_Device->SetRenderState(State, Value);
}

STDMETHODIMPL(Direct3DDevice8Port::GetRenderState8)(D3DRENDERSTATETYPE State,DWORD* pValue)
{
    return m_Device->GetRenderState(State, pValue);
}

STDMETHODIMPL(Direct3DDevice8Port::BeginStateBlock8)()
{
    return m_Device->BeginStateBlock();
}

STDMETHODIMPL(Direct3DDevice8Port::EndStateBlock8)(DWORD* pToken)
{
    return m_Device->EndStateBlock((IDirect3DStateBlock9 **)pToken);
}

STDMETHODIMPL(Direct3DDevice8Port::ApplyStateBlock8)(DWORD Token)
{
    IDirect3DStateBlock9 *Block = (IDirect3DStateBlock9 *)Token;

    return Block->Apply();
}

STDMETHODIMPL(Direct3DDevice8Port::CaptureStateBlock8)(DWORD Token)
{
    IDirect3DStateBlock9 *Block = (IDirect3DStateBlock9 *)Token;
    return Block->Capture();
}

STDMETHODIMPL(Direct3DDevice8Port::DeleteStateBlock8)(DWORD Token)
{
    IDirect3DStateBlock9 *Block = (IDirect3DStateBlock9 *)Token;

    Block->Release();

    return S_OK;
}

STDMETHODIMPL(Direct3DDevice8Port::CreateStateBlock8)(D3DSTATEBLOCKTYPE Type, DWORD* pToken)
{
    HRESULT                  Result;
    IDirect3DStateBlock9    *Block9;
    Direct3DStateBlock8Port *BlockPort;

    Result = m_Device->CreateStateBlock(Type, &Block9);
    if (FAILED(Result))
        return Result;

    BlockPort = new Direct3DStateBlock8Port(Block9, this);
    if (BlockPort == NULL)
    {
        Block9->Release();
        return E_OUTOFMEMORY;
    }

    *(PVOID *)pToken = BlockPort;

    return Result;
}

STDMETHODIMPL(Direct3DDevice8Port::SetClipStatus8)(CONST D3DCLIPSTATUS8* pClipStatus)
{
    return m_Device->SetClipStatus((D3DCLIPSTATUS9 *)pClipStatus);
}

STDMETHODIMPL(Direct3DDevice8Port::GetClipStatus8)(D3DCLIPSTATUS8* pClipStatus)
{
    return m_Device->GetClipStatus((D3DCLIPSTATUS9 *)pClipStatus);
}

STDMETHODIMPL(Direct3DDevice8Port::GetTexture8)(DWORD Stage,IDirect3DBaseTexture8** ppTexture)
{
    HRESULT                      Result;
    IDirect3DBaseTexture9       *Texture9;
    Direct3DBaseTexture8Port    *TexturePort;

    Result = m_Device->GetTexture(Stage, &Texture9);
    if (FAILED(Result))
        return Result;

    TexturePort = new Direct3DBaseTexture8Port(Texture9, this);
    if (TexturePort == NULL)
    {
        Texture9->Release();
        return E_OUTOFMEMORY;
    }

    *(PVOID *)ppTexture = TexturePort;

    return Result;
}

STDMETHODIMPL(Direct3DDevice8Port::SetTexture8)(DWORD Stage,IDirect3DBaseTexture8* pTexture)
{
    IDirect3DBaseTexture9 *Texture9 = (Direct3DBaseTexture8Port *)(PVOID)pTexture;

    return m_Device->SetTexture(Stage, Texture9);
}

STDMETHODIMPL(Direct3DDevice8Port::GetTextureStageState8)(DWORD Stage,D3D8TEXTURESTAGESTATETYPE Type,DWORD* pValue)
{
    D3DSAMPLERSTATETYPE SampleType;

    if (TextureStageState8ToSampleStage9(Type, &SampleType))
    {
        return m_Device->GetSamplerState(Stage, SampleType, pValue);
    }
    else
    {
        return m_Device->GetTextureStageState(Stage, (D3DTEXTURESTAGESTATETYPE)Type, pValue);
    }
}

STDMETHODIMPL(Direct3DDevice8Port::SetTextureStageState8)(DWORD Stage,D3D8TEXTURESTAGESTATETYPE Type,DWORD Value)
{
    D3DSAMPLERSTATETYPE SampleType;
    
    if (TextureStageState8ToSampleStage9(Type, &SampleType))
    {
        return m_Device->SetSamplerState(Stage, SampleType, Value);
    }
    else
    {
        return m_Device->SetTextureStageState(Stage, (D3DTEXTURESTAGESTATETYPE)Type, Value);
    }
}

STDMETHODIMPL(Direct3DDevice8Port::ValidateDevice8)(DWORD* pNumPasses)
{
    return m_Device->ValidateDevice(pNumPasses);
}

STDMETHODIMPL(Direct3DDevice8Port::GetInfo8)(DWORD DevInfoID,void* pDevInfoStruct,DWORD DevInfoStructSize)
{
    HRESULT          Result;
    D3DQUERYTYPE     QueryType;
    IDirect3DQuery9 *Query9;

    QueryType = DevInfoIdToQueryType(DevInfoID);
    if (QueryType == (D3DQUERYTYPE)-1)
    {
        return D3DERR_INVALIDCALL;
    }

    Result = m_Device->CreateQuery(QueryType, &Query9);
    if (FAILED(Result))
        return Result;

    if (Query9->GetDataSize() > DevInfoStructSize)
    {
        Query9->Release();
        return D3DERR_INVALIDCALL;
    }

    Result = Query9->GetData(pDevInfoStruct, DevInfoStructSize, 0);
    Query9->Release();

    return Result;
}

STDMETHODIMPL(Direct3DDevice8Port::SetPaletteEntries8)(UINT PaletteNumber,CONST PALETTEENTRY* pEntries)
{
    return m_Device->SetPaletteEntries(PaletteNumber, pEntries);
}

STDMETHODIMPL(Direct3DDevice8Port::GetPaletteEntries8)(UINT PaletteNumber,PALETTEENTRY* pEntries)
{
    return m_Device->GetPaletteEntries(PaletteNumber, pEntries);
}

STDMETHODIMPL(Direct3DDevice8Port::SetCurrentTexturePalette8)(UINT PaletteNumber)
{
    return m_Device->SetCurrentTexturePalette(PaletteNumber);
}

STDMETHODIMPL(Direct3DDevice8Port::GetCurrentTexturePalette8)(UINT *PaletteNumber)
{
    return m_Device->GetCurrentTexturePalette(PaletteNumber);
}

STDMETHODIMPL(Direct3DDevice8Port::DrawPrimitive8)(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount)
{
    return m_Device->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

STDMETHODIMPL(Direct3DDevice8Port::DrawIndexedPrimitive8)(D3DPRIMITIVETYPE PrimitiveType,UINT minIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
    return m_Device->DrawIndexedPrimitive(PrimitiveType, 0, minIndex, NumVertices, startIndex, primCount);
}

STDMETHODIMPL(Direct3DDevice8Port::DrawPrimitiveUP8)(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
    return m_Device->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMPL(Direct3DDevice8Port::DrawIndexedPrimitiveUP8)(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertexIndices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
    return m_Device->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertexIndices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMPL(Direct3DDevice8Port::ProcessVertices8)(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer8* pDestBuffer,DWORD Flags)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::CreateVertexShader8)(CONST DWORD* pDeclaration,CONST DWORD* pFunction,DWORD* pHandle,DWORD Usage)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::SetVertexShader8)(DWORD Handle)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::GetVertexShader8)(DWORD* pHandle)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::DeleteVertexShader8)(DWORD Handle)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::SetVertexShaderConstant8)(DWORD Register,CONST void* pConstantData,DWORD ConstantCount)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::GetVertexShaderConstant8)(DWORD Register,void* pConstantData,DWORD ConstantCount)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::GetVertexShaderDeclaration8)(DWORD Handle,void* pData,DWORD* pSizeOfData)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::GetVertexShaderFunction8)(DWORD Handle,void* pData,DWORD* pSizeOfData)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::SetStreamSource8)(UINT StreamNumber,IDirect3DVertexBuffer8* pStreamData,UINT Stride)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::GetStreamSource8)(UINT StreamNumber,IDirect3DVertexBuffer8** ppStreamData,UINT* pStride)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::SetIndices8)(IDirect3DIndexBuffer8* pIndexData,UINT BaseVertexIndex)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::GetIndices8)(IDirect3DIndexBuffer8** ppIndexData,UINT* pBaseVertexIndex)
{
    
}

STDMETHODIMPL(Direct3DDevice8Port::CreatePixelShader8)(CONST DWORD* pFunction,DWORD* pHandle)
{
    HRESULT Result;
    IDirect3DPixelShader9 *Shader;

    Result = m_Device->CreatePixelShader(pFunction, &Shader);
    if (FAILED(Result))
        return Result;

    *(PVOID *)pHandle = new Direct3DPixelShader8Port(Shader, this);
    if (*pHandle == NULL)
    {
        Shader->Release();
        return E_OUTOFMEMORY;
    }    

    return S_OK;
}

STDMETHODIMPL(Direct3DDevice8Port::SetPixelShader8)(DWORD Handle)
{
    return m_Device->SetPixelShader((IDirect3DPixelShader9 *)Handle);
}

STDMETHODIMPL(Direct3DDevice8Port::GetPixelShader8)(DWORD* pHandle)
{
    return m_Device->GetPixelShader((IDirect3DPixelShader9 **)pHandle);
}

STDMETHODIMPL(Direct3DDevice8Port::DeletePixelShader8)(DWORD Handle)
{
    ((Direct3DPixelShader8Port *)Handle)->Release8();
    return S_OK;
}

STDMETHODIMPL(Direct3DDevice8Port::SetPixelShaderConstant8)(DWORD Register,CONST void* pConstantData,DWORD ConstantCount)
{
    return m_Device->SetPixelShaderConstantI(Register, (PINT)pConstantData, ConstantCount);
}

STDMETHODIMPL(Direct3DDevice8Port::GetPixelShaderConstant8)(DWORD Register,void* pConstantData,DWORD ConstantCount)
{
    return m_Device->GetPixelShaderConstantI(Register, (PINT)pConstantData, ConstantCount);
}

STDMETHODIMPL(Direct3DDevice8Port::GetPixelShaderFunction8)(DWORD Handle,void* pData,DWORD* pSizeOfData)
{
    Direct3DPixelShader8Port *Shader = (Direct3DPixelShader8Port *)Handle;

    return ((PDIRECT3DPIXELSHADER9)*Shader)->GetFunction(pData, (PUINT)pSizeOfData);
}

STDMETHODIMPL(Direct3DDevice8Port::DrawRectPatch8)(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
    return m_Device->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

STDMETHODIMPL(Direct3DDevice8Port::DrawTriPatch8)(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
    return m_Device->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

STDMETHODIMPL(Direct3DDevice8Port::DeletePatch8)(UINT Handle)
{
    return m_Device->DeletePatch(Handle);
}


/************************************************************************
  Direct3DSwapChain8Port impl
************************************************************************/

/*** IUnknown methods ***/
STDMETHODIMPL(Direct3DSwapChain8Port::QueryInterface8)(REFIID riid, void** ppvObj)
{
    return m_SwapChain->QueryInterface(riid, ppvObj);
}

STDMETHODIMPL_(ULONG,Direct3DSwapChain8Port::AddRef8)()
{
    return m_SwapChain->AddRef();
}

STDMETHODIMPL_(ULONG,Direct3DSwapChain8Port::Release8)()
{
    return D3DAutoRelease(this, m_SwapChain);
}

/*** IDirect3DSwapChain8 methods ***/
STDMETHODIMPL(Direct3DSwapChain8Port::Present8)(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion)
{
    return m_SwapChain->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, 0);
}

STDMETHODIMPL(Direct3DSwapChain8Port::GetBackBuffer8)(UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer)
{
    HRESULT Result;
    IDirect3DSurface9 *Surface9;
    Direct3DSurface8Port *SurfacePort;

    Result = m_SwapChain->GetBackBuffer(BackBuffer, Type, &Surface9);
    if (FAILED(Result))
        return Result;

    SurfacePort = new Direct3DSurface8Port(Surface9, m_Device);
    if (SurfacePort == NULL)
    {
        Surface9->Release();
        return E_OUTOFMEMORY;
    }

    *(PVOID *)ppBackBuffer = SurfacePort;

    return Result;
}

/************************************************************************
  9
************************************************************************/
/*** IUnknown methods ***/
STDMETHODIMPL(Direct3DSwapChain8Port::QueryInterface)(REFIID riid, void** ppvObj)
{
    return m_SwapChain->QueryInterface(riid, ppvObj);
}

STDMETHODIMPL_(ULONG,Direct3DSwapChain8Port::AddRef)()
{
    return m_SwapChain->AddRef();
}

STDMETHODIMPL_(ULONG,Direct3DSwapChain8Port::Release)()
{
    return D3DAutoRelease(this, m_SwapChain);
}

/*** IDirect3DSwapChain9 methods ***/
STDMETHODIMPL(Direct3DSwapChain8Port::Present)(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags)
{
    return m_SwapChain->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
}

STDMETHODIMPL(Direct3DSwapChain8Port::GetFrontBufferData)(IDirect3DSurface9* pDestSurface)
{
    return m_SwapChain->GetFrontBufferData(pDestSurface);
}

STDMETHODIMPL(Direct3DSwapChain8Port::GetBackBuffer)(UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer)
{
    HRESULT Result;
    IDirect3DSurface9 *BackBuffer9;
    Direct3DSurface8Port *BackBufferPort;

    Result = m_SwapChain->GetBackBuffer(iBackBuffer, Type, &BackBuffer9);
    if (FAILED(Result))
        return Result;

    BackBufferPort = new Direct3DSurface8Port(BackBuffer9, m_Device);
    if (BackBufferPort == NULL)
    {
        BackBuffer9->Release();
        return E_OUTOFMEMORY;
    }

    *ppBackBuffer = BackBufferPort;

    return S_OK;
}

STDMETHODIMPL(Direct3DSwapChain8Port::GetRasterStatus)(D3DRASTER_STATUS* pRasterStatus)
{
    return m_SwapChain->GetRasterStatus(pRasterStatus);
}

STDMETHODIMPL(Direct3DSwapChain8Port::GetDisplayMode)(D3DDISPLAYMODE* pMode)
{
    return m_SwapChain->GetDisplayMode(pMode);
}

STDMETHODIMPL(Direct3DSwapChain8Port::GetDevice)(IDirect3DDevice9** ppDevice)
{
    m_Device->AddRef();
    *ppDevice = m_Device;
    return S_OK;
}

STDMETHODIMPL(Direct3DSwapChain8Port::GetPresentParameters)(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    return m_SwapChain->GetPresentParameters(pPresentationParameters);
}

/************************************************************************
  Direct3DVolumeTexture8Port impl
************************************************************************/

STDMETHODIMPL(Direct3DVolumeTexture8Port::GetVolumeLevel8)(UINT Level, IDirect3DVolume8** ppVolumeLevel)
{
    HRESULT Result;
    IDirect3DVolume9 *VolumeLevel9;
    Direct3DVolume8Port *Port;

    Result = m_VolumeTexture->GetVolumeLevel(Level, &VolumeLevel9);
    if (FAILED(Result))
        return Result;

    Port = new Direct3DVolume8Port(VolumeLevel9, m_Device);
    if (Port == NULL)
    {
        VolumeLevel9->Release();
        return E_OUTOFMEMORY;
    }

    *(PVOID *)ppVolumeLevel = Port;

    return Result;
}

/************************************************************************
  Direct3DTexture8Port impl
************************************************************************/

STDMETHODIMPL(Direct3DTexture8Port::GetSurfaceLevel8)(UINT Level,IDirect3DSurface8** ppSurfaceLevel)
{
    HRESULT                  Result;
    IDirect3DSurface9       *Surface9;
    Direct3DSurface8Port    *SurfacePort;

    Result = m_Texture->GetSurfaceLevel(Level, &Surface9);
    if (FAILED(Result))
        return Result;

    SurfacePort = new Direct3DSurface8Port(Surface9, m_Device);
    if (SurfacePort == NULL)
    {
        Surface9->Release();
        return E_OUTOFMEMORY;
    }

    *(PVOID *)ppSurfaceLevel = SurfacePort;

    return Result;
}

STDMETHODIMPL(Direct3DTexture8Port::GetSurfaceLevel)(UINT Level,IDirect3DSurface9** ppSurfaceLevel)
{
    HRESULT                  Result;
    IDirect3DSurface9       *Surface9;
    Direct3DSurface8Port    *SurfacePort;

    Result = m_Texture->GetSurfaceLevel(Level, &Surface9);
    if (FAILED(Result))
        return Result;

    SurfacePort = new Direct3DSurface8Port(Surface9, m_Device);
    if (SurfacePort == NULL)
    {
        Surface9->Release();
        return E_OUTOFMEMORY;
    }

    *ppSurfaceLevel = SurfacePort;

    return Result;
}

/************************************************************************
  Direct3DSurface8Port impl
************************************************************************/

HRESULT Direct3DSurface8Port::QueryInterface8(REFIID riid, void** ppvObj)
{
    return m_Surface->QueryInterface(riid, ppvObj);
}

ULONG Direct3DSurface8Port::AddRef8()
{
    return m_Surface->AddRef();
}

ULONG Direct3DSurface8Port::Release8()
{
    return D3DAutoRelease(this, m_Surface);
}

/*** IDirect3DSurface8 methods ***/
HRESULT Direct3DSurface8Port::GetDevice8(IDirect3DDevice8** ppDevice)
{
    m_Device->AddRef();

    *(PVOID *)ppDevice = m_Device;

    return S_OK;
}

HRESULT Direct3DSurface8Port::SetPrivateData8(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
    return m_Surface->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

HRESULT Direct3DSurface8Port::GetPrivateData8(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
    return m_Surface->GetPrivateData(refguid, pData, pSizeOfData);
}

HRESULT Direct3DSurface8Port::FreePrivateData8(REFGUID refguid)
{
    return m_Surface->FreePrivateData(refguid);
}

HRESULT Direct3DSurface8Port::GetContainer8( REFIID riid,void** ppContainer)
{
    return m_Surface->GetContainer(riid, ppContainer);
}

HRESULT Direct3DSurface8Port::GetDesc8(D3D8SURFACE_DESC *pDesc)
{
    HRESULT         Result;
    D3DSURFACE_DESC Desc;
    D3DLOCKED_RECT  LockedRect;

    Result = m_Surface->GetDesc(&Desc);
    if (FAILED(Result))
        return Result;

    if (!FAILED(m_Surface->LockRect(&LockedRect, NULL, 0)))
    {
        m_Surface->UnlockRect();
    }
    else
    {
        LockedRect.Pitch = 0;
    }

    pDesc->Format           = Desc.Format;
    pDesc->Type             = Desc.Type;
    pDesc->Usage            = Desc.Usage;
    pDesc->Pool             = Desc.Pool;
    pDesc->Size             = LockedRect.Pitch * Desc.Height;
    pDesc->MultiSampleType  = Desc.MultiSampleType;
    pDesc->Width            = Desc.Width;
    pDesc->Height           = Desc.Height;

    return Result;
}

HRESULT Direct3DSurface8Port::LockRect8(D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags)
{
    return m_Surface->LockRect(pLockedRect, pRect, Flags);
}

HRESULT Direct3DSurface8Port::UnlockRect8()
{
    return m_Surface->UnlockRect();
}

#pragma pop_macro("STDMETHODIMPL")
#pragma pop_macro("STDMETHODIMPL_")

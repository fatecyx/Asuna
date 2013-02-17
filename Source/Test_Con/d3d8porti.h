#ifndef _D3D8PORTI_H_beae18ac_6c75_45b0_99dc_3801f74cd017_
#define _D3D8PORTI_H_beae18ac_6c75_45b0_99dc_3801f74cd017_

#include "d3d8port.h"

/************************************************************************
  interface definition
************************************************************************/

template<class ObjectType, class ReleaseObject>
inline ULONG D3DAutoRelease(ObjectType This, ReleaseObject *Object)
{
    ULONG RefCount;

    RefCount = Object->Release();
    if (RefCount == 0)
        delete This;

    return RefCount;
}

inline VOID D3DCaps9To8(D3DCAPS8 *Caps8, D3DCAPS9 *Caps9)
{
    *Caps8 = *(D3DCAPS8 *)Caps9;
}

inline VOID PresentParam8To9(D3D8PRESENT_PARAMETERS *PresentParameters8, D3DPRESENT_PARAMETERS *PresentParameters9, ULONG MultiSampleQuality = 0)
{
    CopyStruct(
        PresentParameters9,
        PresentParameters8,
        FIELD_OFFSET(D3DPRESENT_PARAMETERS, MultiSampleQuality)
    );

    CopyStruct(
        &PresentParameters9->SwapEffect,
        &PresentParameters8->SwapEffect,
        sizeof(*PresentParameters9) - FIELD_OFFSET(D3DPRESENT_PARAMETERS, SwapEffect)
    );

    PresentParameters9->MultiSampleQuality = MultiSampleQuality;
}

inline VOID SurfaceDesc9To8(D3D8SURFACE_DESC *Desc8, D3DSURFACE_DESC *Desc9, UINT SurfaceSize = 0)
{
    *Desc8 = *(D3D8SURFACE_DESC *)Desc9;
    Desc8->MultiSampleType = Desc9->MultiSampleType;
    Desc8->Size = SurfaceSize;
}

inline VOID VolumeDesc9To8(D3D8VOLUME_DESC *Desc8, D3DVOLUME_DESC *Desc9, UINT Size = 0)
{
    CopyStruct(Desc8, Desc9, FIELD_OFFSET(D3D8VOLUME_DESC, Size));
    CopyStruct(&Desc8->Width, &Desc9->Width, sizeof(*Desc8) - FIELD_OFFSET(D3D8VOLUME_DESC, Width));
    Desc8->Size = Size;
}

inline BOOL TextureStageState8ToSampleStage9(D3D8TEXTURESTAGESTATETYPE TextureType, D3DSAMPLERSTATETYPE *SampleType)
{
    switch (TextureType)
    {
        case D3D8TSS_ADDRESSW:      *SampleType = D3DSAMP_ADDRESSW;      break;
        case D3D8TSS_ADDRESSU:      *SampleType = D3DSAMP_ADDRESSU;      break;
        case D3D8TSS_ADDRESSV:      *SampleType = D3DSAMP_ADDRESSV;      break;
        case D3D8TSS_BORDERCOLOR:   *SampleType = D3DSAMP_BORDERCOLOR;   break;
        case D3D8TSS_MAGFILTER:     *SampleType = D3DSAMP_MAGFILTER;     break;
        case D3D8TSS_MINFILTER:     *SampleType = D3DSAMP_MINFILTER;     break;
        case D3D8TSS_MIPFILTER:     *SampleType = D3DSAMP_MIPFILTER;     break;
        case D3D8TSS_MIPMAPLODBIAS: *SampleType = D3DSAMP_MIPMAPLODBIAS; break;
        case D3D8TSS_MAXMIPLEVEL:   *SampleType = D3DSAMP_MAXMIPLEVEL;   break;
        case D3D8TSS_MAXANISOTROPY: *SampleType = D3DSAMP_MAXANISOTROPY; break;

        default:
            return FALSE;
    }

    return TRUE;
}

#define D3DDEVINFOID_TEXTUREMANAGER     1
#define D3DDEVINFOID_D3DTEXTUREMANAGER  2
#define D3DDEVINFOID_TEXTURING          3
#define D3DDEVINFOID_VCACHE             4
#define D3DDEVINFOID_RESOURCEMANAGER    5
#define D3DDEVINFOID_D3DVERTEXSTATS     6
#define D3DDEVINFOID_UNKNOWN            7

inline D3DQUERYTYPE DevInfoIdToQueryType(ULONG DevInfoId)
{
    D3DQUERYTYPE QueryType;

    QueryType = (D3DQUERYTYPE)-1;

    switch (DevInfoId)
    {
        case D3DDEVINFOID_TEXTUREMANAGER:       break;
        case D3DDEVINFOID_D3DTEXTUREMANAGER:    break;
        case D3DDEVINFOID_TEXTURING:            break;
        case D3DDEVINFOID_VCACHE:               QueryType = D3DQUERYTYPE_VCACHE;            break;
        case D3DDEVINFOID_RESOURCEMANAGER:      QueryType = D3DQUERYTYPE_RESOURCEMANAGER;   break;
        case D3DDEVINFOID_D3DVERTEXSTATS:       QueryType = D3DQUERYTYPE_VERTEXSTATS;       break;
        case D3DDEVINFOID_UNKNOWN:              break;
    }

    return QueryType;
}

DECLARE_INTERFACE(IPortUnknown)
{
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();
};

DECLARE_INTERFACE_(IDirect3D8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3D8 methods ***/
    STDMETHOD(RegisterSoftwareDevice8)(void* pInitializeFunction);
    STDMETHOD_(UINT, GetAdapterCount8)();
    STDMETHOD(GetAdapterIdentifier8)(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER8* pIdentifier);
    STDMETHOD_(UINT, GetAdapterModeCount8)(UINT Adapter);
    STDMETHOD(EnumAdapterModes8)(UINT Adapter,UINT Mode,D3DDISPLAYMODE* pMode);
    STDMETHOD(GetAdapterDisplayMode8)(UINT Adapter,D3DDISPLAYMODE* pMode);
    STDMETHOD(CheckDeviceType8)(UINT Adapter,D3DDEVTYPE CheckType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL Windowed);
    STDMETHOD(CheckDeviceFormat8)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat);
    STDMETHOD(CheckDeviceMultiSampleType8)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType);
    STDMETHOD(CheckDepthStencilMatch8)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat);
    STDMETHOD(GetDeviceCaps8)(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS8* pCaps);
    STDMETHOD_(HMONITOR, GetAdapterMonitor8)(UINT Adapter);
    STDMETHOD(CreateDevice8)(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3D8PRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice8** ppReturnedDeviceInterface);
};

DECLARE_INTERFACE_(IDirect3DPixelShader8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DPixelShader9 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice9** ppDevice);
    STDMETHOD(GetFunction8)(void*,UINT* pSizeOfData);
};

DECLARE_INTERFACE_(IDirect3DStateBlock8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DStateBlock9 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice9** ppDevice);
    STDMETHOD(Capture8)();
    STDMETHOD(Apply8)();
};

DECLARE_INTERFACE_(IDirect3DDevice8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DDevice8 methods ***/
    STDMETHOD(TestCooperativeLevel8)();
    STDMETHOD_(UINT, GetAvailableTextureMem8)();
    STDMETHOD(ResourceManagerDiscardBytes8)(DWORD Bytes);
    STDMETHOD(GetDirect3D8)(IDirect3D8** ppD3D8);
    STDMETHOD(GetDeviceCaps8)(D3DCAPS8* pCaps);
    STDMETHOD(GetDisplayMode8)(D3DDISPLAYMODE* pMode);
    STDMETHOD(GetCreationParameters8)(D3DDEVICE_CREATION_PARAMETERS *pParameters);
    STDMETHOD(SetCursorProperties8)(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface8* pCursorBitmap);
    STDMETHOD_(void, SetCursorPosition8)(int X,int Y,DWORD Flags);
    STDMETHOD_(BOOL, ShowCursor8)(BOOL bShow);
    STDMETHOD(CreateAdditionalSwapChain8)(D3D8PRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain8** pSwapChain);
    STDMETHOD(Reset8)(D3D8PRESENT_PARAMETERS* pPresentationParameters);
    STDMETHOD(Present8)(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion);
    STDMETHOD(GetBackBuffer8)(UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer);
    STDMETHOD(GetRasterStatus8)(D3DRASTER_STATUS* pRasterStatus);
    STDMETHOD_(void, SetGammaRamp8)(DWORD Flags,CONST D3DGAMMARAMP* pRamp);
    STDMETHOD_(void, GetGammaRamp8)(D3DGAMMARAMP* pRamp);
    STDMETHOD(CreateTexture8)(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture8** ppTexture);
    STDMETHOD(CreateVolumeTexture8)(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture8** ppVolumeTexture);
    STDMETHOD(CreateCubeTexture8)(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture8** ppCubeTexture);
    STDMETHOD(CreateVertexBuffer8)(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer8** ppVertexBuffer);
    STDMETHOD(CreateIndexBuffer8)(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer8** ppIndexBuffer);
    STDMETHOD(CreateRenderTarget8)(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,BOOL Lockable,IDirect3DSurface8** ppSurface);
    STDMETHOD(CreateDepthStencilSurface8)(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,IDirect3DSurface8** ppSurface);
    STDMETHOD(CreateImageSurface8)(UINT Width,UINT Height,D3DFORMAT Format,IDirect3DSurface8** ppSurface);
    STDMETHOD(CopyRects8)(IDirect3DSurface8* pSourceSurface,CONST RECT* pSourceRectsArray,UINT cRects,IDirect3DSurface8* pDestinationSurface,CONST POINT* pDestPointsArray);
    STDMETHOD(UpdateTexture8)(IDirect3DBaseTexture8* pSourceTexture,IDirect3DBaseTexture8* pDestinationTexture);
    STDMETHOD(GetFrontBuffer8)(IDirect3DSurface8* pDestSurface);
    STDMETHOD(SetRenderTarget8)(IDirect3DSurface8* pRenderTarget,IDirect3DSurface8* pNewZStencil);
    STDMETHOD(GetRenderTarget8)(IDirect3DSurface8** ppRenderTarget);
    STDMETHOD(GetDepthStencilSurface8)(IDirect3DSurface8** ppZStencilSurface);
    STDMETHOD(BeginScene8)();
    STDMETHOD(EndScene8)();
    STDMETHOD(Clear8)(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil);
    STDMETHOD(SetTransform8)(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix);
    STDMETHOD(GetTransform8)(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix);
    STDMETHOD(MultiplyTransform8)(D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*);
    STDMETHOD(SetViewport8)(CONST D3DVIEWPORT8* pViewport);
    STDMETHOD(GetViewport8)(D3DVIEWPORT8* pViewport);
    STDMETHOD(SetMaterial8)(CONST D3DMATERIAL8* pMaterial);
    STDMETHOD(GetMaterial8)(D3DMATERIAL8* pMaterial);
    STDMETHOD(SetLight8)(DWORD Index,CONST D3DLIGHT8*);
    STDMETHOD(GetLight8)(DWORD Index,D3DLIGHT8*);
    STDMETHOD(LightEnable8)(DWORD Index,BOOL Enable);
    STDMETHOD(GetLightEnable8)(DWORD Index,BOOL* pEnable);
    STDMETHOD(SetClipPlane8)(DWORD Index,CONST float* pPlane);
    STDMETHOD(GetClipPlane8)(DWORD Index,float* pPlane);
    STDMETHOD(SetRenderState8)(D3DRENDERSTATETYPE State,DWORD Value);
    STDMETHOD(GetRenderState8)(D3DRENDERSTATETYPE State,DWORD* pValue);
    STDMETHOD(BeginStateBlock8)();
    STDMETHOD(EndStateBlock8)(DWORD* pToken);
    STDMETHOD(ApplyStateBlock8)(DWORD Token);
    STDMETHOD(CaptureStateBlock8)(DWORD Token);
    STDMETHOD(DeleteStateBlock8)(DWORD Token);
    STDMETHOD(CreateStateBlock8)(D3DSTATEBLOCKTYPE Type,DWORD* pToken);
    STDMETHOD(SetClipStatus8)(CONST D3DCLIPSTATUS8* pClipStatus);
    STDMETHOD(GetClipStatus8)(D3DCLIPSTATUS8* pClipStatus);
    STDMETHOD(GetTexture8)(DWORD Stage,IDirect3DBaseTexture8** ppTexture);
    STDMETHOD(SetTexture8)(DWORD Stage,IDirect3DBaseTexture8* pTexture);
    STDMETHOD(GetTextureStageState8)(DWORD Stage,D3D8TEXTURESTAGESTATETYPE Type,DWORD* pValue);
    STDMETHOD(SetTextureStageState8)(DWORD Stage,D3D8TEXTURESTAGESTATETYPE Type,DWORD Value);
    STDMETHOD(ValidateDevice8)(DWORD* pNumPasses);
    STDMETHOD(GetInfo8)(DWORD DevInfoID,void* pDevInfoStruct,DWORD DevInfoStructSize);
    STDMETHOD(SetPaletteEntries8)(UINT PaletteNumber,CONST PALETTEENTRY* pEntries);
    STDMETHOD(GetPaletteEntries8)(UINT PaletteNumber,PALETTEENTRY* pEntries);
    STDMETHOD(SetCurrentTexturePalette8)(UINT PaletteNumber);
    STDMETHOD(GetCurrentTexturePalette8)(UINT *PaletteNumber);
    STDMETHOD(DrawPrimitive8)(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount);
    STDMETHOD(DrawIndexedPrimitive8)(D3DPRIMITIVETYPE,UINT minIndex,UINT NumVertices,UINT startIndex,UINT primCount);
    STDMETHOD(DrawPrimitiveUP8)(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
    STDMETHOD(DrawIndexedPrimitiveUP8)(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertexIndices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
    STDMETHOD(ProcessVertices8)(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer8* pDestBuffer,DWORD Flags);
    STDMETHOD(CreateVertexShader8)(CONST DWORD* pDeclaration,CONST DWORD* pFunction,DWORD* pHandle,DWORD Usage);
    STDMETHOD(SetVertexShader8)(DWORD Handle);
    STDMETHOD(GetVertexShader8)(DWORD* pHandle);
    STDMETHOD(DeleteVertexShader8)(DWORD Handle);
    STDMETHOD(SetVertexShaderConstant8)(DWORD Register,CONST void* pConstantData,DWORD ConstantCount);
    STDMETHOD(GetVertexShaderConstant8)(DWORD Register,void* pConstantData,DWORD ConstantCount);
    STDMETHOD(GetVertexShaderDeclaration8)(DWORD Handle,void* pData,DWORD* pSizeOfData);
    STDMETHOD(GetVertexShaderFunction8)(DWORD Handle,void* pData,DWORD* pSizeOfData);
    STDMETHOD(SetStreamSource8)(UINT StreamNumber,IDirect3DVertexBuffer8* pStreamData,UINT Stride);
    STDMETHOD(GetStreamSource8)(UINT StreamNumber,IDirect3DVertexBuffer8** ppStreamData,UINT* pStride);
    STDMETHOD(SetIndices8)(IDirect3DIndexBuffer8* pIndexData,UINT BaseVertexIndex);
    STDMETHOD(GetIndices8)(IDirect3DIndexBuffer8** ppIndexData,UINT* pBaseVertexIndex);
    STDMETHOD(CreatePixelShader8)(CONST DWORD* pFunction,DWORD* pHandle);
    STDMETHOD(SetPixelShader8)(DWORD Handle);
    STDMETHOD(GetPixelShader8)(DWORD* pHandle);
    STDMETHOD(DeletePixelShader8)(DWORD Handle);
    STDMETHOD(SetPixelShaderConstant8)(DWORD Register,CONST void* pConstantData,DWORD ConstantCount);
    STDMETHOD(GetPixelShaderConstant8)(DWORD Register,void* pConstantData,DWORD ConstantCount);
    STDMETHOD(GetPixelShaderFunction8)(DWORD Handle,void* pData,DWORD* pSizeOfData);
    STDMETHOD(DrawRectPatch8)(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo);
    STDMETHOD(DrawTriPatch8)(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo);
    STDMETHOD(DeletePatch8)(UINT Handle);
};

DECLARE_INTERFACE_(IDirect3DSwapChain8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DSwapChain8 methods ***/
    STDMETHOD(Present8)(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion);
    STDMETHOD(GetBackBuffer8)(UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer);
};

DECLARE_INTERFACE_(IDirect3DResource8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DResource8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice);
    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData8)(REFGUID refguid);
    STDMETHOD_(DWORD, SetPriority8)(DWORD PriorityNew);
    STDMETHOD_(DWORD, GetPriority8)();
    STDMETHOD_(void, PreLoad8)();
    STDMETHOD_(D3DRESOURCETYPE, GetType8)();
};

DECLARE_INTERFACE_(IDirect3DBaseTexture8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DResource8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice);
    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData8)(REFGUID refguid);
    STDMETHOD_(DWORD, SetPriority8)(DWORD PriorityNew);
    STDMETHOD_(DWORD, GetPriority8)();
    STDMETHOD_(void, PreLoad8)();
    STDMETHOD_(D3DRESOURCETYPE, GetType8)();
    STDMETHOD_(DWORD, SetLOD8)(DWORD LODNew);
    STDMETHOD_(DWORD, GetLOD8)();
    STDMETHOD_(DWORD, GetLevelCount8)();
};

DECLARE_INTERFACE_(IDirect3DTexture8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DBaseTexture8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice);
    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData8)(REFGUID refguid);
    STDMETHOD_(DWORD, SetPriority8)(DWORD PriorityNew);
    STDMETHOD_(DWORD, GetPriority8)();
    STDMETHOD_(void, PreLoad8)();
    STDMETHOD_(D3DRESOURCETYPE, GetType8)();
    STDMETHOD_(DWORD, SetLOD8)(DWORD LODNew);
    STDMETHOD_(DWORD, GetLOD8)();
    STDMETHOD_(DWORD, GetLevelCount8)();
    STDMETHOD(GetLevelDesc8)(UINT Level,D3D8SURFACE_DESC *pDesc);
    STDMETHOD(GetSurfaceLevel8)(UINT Level,IDirect3DSurface8** ppSurfaceLevel);
    STDMETHOD(LockRect8)(UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
    STDMETHOD(UnlockRect8)(UINT Level);
    STDMETHOD(AddDirtyRect8)(CONST RECT* pDirtyRect);
};

DECLARE_INTERFACE_(IDirect3DVolumeTexture8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DBaseTexture8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice);
    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData8)(REFGUID refguid);
    STDMETHOD_(DWORD, SetPriority8)(DWORD PriorityNew);
    STDMETHOD_(DWORD, GetPriority8)();
    STDMETHOD_(void, PreLoad8)();
    STDMETHOD_(D3DRESOURCETYPE, GetType8)();
    STDMETHOD_(DWORD, SetLOD8)(DWORD LODNew);
    STDMETHOD_(DWORD, GetLOD8)();
    STDMETHOD_(DWORD, GetLevelCount8)();
    STDMETHOD(GetLevelDesc8)(UINT Level,D3D8VOLUME_DESC *pDesc);
    STDMETHOD(GetVolumeLevel8)(UINT Level,IDirect3DVolume8** ppVolumeLevel);
    STDMETHOD(LockBox8)(UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
    STDMETHOD(UnlockBox8)(UINT Level);
    STDMETHOD(AddDirtyBox8)(CONST D3DBOX* pDirtyBox);
};

DECLARE_INTERFACE_(IDirect3DCubeTexture8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DBaseTexture8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice);
    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData8)(REFGUID refguid);
    STDMETHOD_(DWORD, SetPriority8)(DWORD PriorityNew);
    STDMETHOD_(DWORD, GetPriority8)();
    STDMETHOD_(void, PreLoad8)();
    STDMETHOD_(D3DRESOURCETYPE, GetType8)();
    STDMETHOD_(DWORD, SetLOD8)(DWORD LODNew);
    STDMETHOD_(DWORD, GetLOD8)();
    STDMETHOD_(DWORD, GetLevelCount8)();
    STDMETHOD(GetLevelDesc8)(UINT Level,D3D8SURFACE_DESC *pDesc);
    STDMETHOD(GetCubeMapSurface8)(D3DCUBEMAP_FACES FaceType,UINT Level,IDirect3DSurface8** ppCubeMapSurface);
    STDMETHOD(LockRect8)(D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
    STDMETHOD(UnlockRect8)(D3DCUBEMAP_FACES FaceType,UINT Level);
    STDMETHOD(AddDirtyRect8)(D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect);
};

DECLARE_INTERFACE_(IDirect3DVertexBuffer8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DResource8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice);
    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData8)(REFGUID refguid);
    STDMETHOD_(DWORD, SetPriority8)(DWORD PriorityNew);
    STDMETHOD_(DWORD, GetPriority8)();
    STDMETHOD_(void, PreLoad8)();
    STDMETHOD_(D3DRESOURCETYPE, GetType8)();
    STDMETHOD(Lock8)(UINT OffsetToLock,UINT SizeToLock,BYTE** ppbData,DWORD Flags);
    STDMETHOD(Unlock8)();
    STDMETHOD(GetDesc8)(D3DVERTEXBUFFER_DESC *pDesc);
};

DECLARE_INTERFACE_(IDirect3DIndexBuffer8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DResource8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice);
    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData8)(REFGUID refguid);
    STDMETHOD_(DWORD, SetPriority8)(DWORD PriorityNew);
    STDMETHOD_(DWORD, GetPriority8)();
    STDMETHOD_(void, PreLoad8)();
    STDMETHOD_(D3DRESOURCETYPE, GetType8)();
    STDMETHOD(Lock8)(UINT OffsetToLock,UINT SizeToLock,BYTE** ppbData,DWORD Flags);
    STDMETHOD(Unlock8)();
    STDMETHOD(GetDesc8)(D3DINDEXBUFFER_DESC *pDesc);
};

DECLARE_INTERFACE_(IDirect3DSurface8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DSurface8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice);
    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData8)(REFGUID refguid);
    STDMETHOD(GetContainer8)(REFIID riid,void** ppContainer);
    STDMETHOD(GetDesc8)(D3D8SURFACE_DESC *pDesc);
    STDMETHOD(LockRect8)(D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
    STDMETHOD(UnlockRect8)();
};

DECLARE_INTERFACE_(IDirect3DVolume8Port, IPortUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DVolume8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice);
    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData8)(REFGUID refguid);
    STDMETHOD(GetContainer8)(REFIID riid,void** ppContainer);
    STDMETHOD(GetDesc8)(D3D8VOLUME_DESC *pDesc);
    STDMETHOD(LockBox8)(D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
    STDMETHOD(UnlockBox8)();
};


/************************************************************************
  class definition
************************************************************************/

class Direct3DDevice8Port;
class Direct3DSurface8Port;

class Direct3D8Port : public IDirect3D8Port, public IDirect3D9
{
protected:
    IDirect3D9 *m_d3d9;
    ULONG       m_QualityLevel;

    static D3DFORMAT m_Format8[6];

public:
    Direct3D8Port(IDirect3D9 *d3d9);
    operator PDIRECT3D9();

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3D8 methods ***/
    STDMETHOD(RegisterSoftwareDevice8)(void* pInitializeFunction);
    STDMETHOD_(UINT, GetAdapterCount8)();
    STDMETHOD(GetAdapterIdentifier8)(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER8* pIdentifier);
    STDMETHOD_(UINT, GetAdapterModeCount8)(UINT Adapter);
    STDMETHOD(EnumAdapterModes8)(UINT Adapter,UINT Mode,D3DDISPLAYMODE* pMode);
    STDMETHOD(GetAdapterDisplayMode8)(UINT Adapter,D3DDISPLAYMODE* pMode);
    STDMETHOD(CheckDeviceType8)(UINT Adapter,D3DDEVTYPE CheckType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL Windowed);
    STDMETHOD(CheckDeviceFormat8)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat);
    STDMETHOD(CheckDeviceMultiSampleType8)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType);
    STDMETHOD(CheckDepthStencilMatch8)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat);
    STDMETHOD(GetDeviceCaps8)(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS8* pCaps);
    STDMETHOD_(HMONITOR, GetAdapterMonitor8)(UINT Adapter);
    STDMETHOD(CreateDevice8)(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3D8PRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice8** ppReturnedDeviceInterface);

    /************************************************************************
      d3d9 interface
    ************************************************************************/
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef)();
    STDMETHOD_(ULONG,Release)();

    /*** IDirect3D9 methods ***/
    STDMETHOD(RegisterSoftwareDevice)(void* pInitializeFunction);
    STDMETHOD_(UINT, GetAdapterCount)();
    STDMETHOD(GetAdapterIdentifier)(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier);
    STDMETHOD_(UINT, GetAdapterModeCount)(UINT Adapter,D3DFORMAT Format);
    STDMETHOD(EnumAdapterModes)(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode);
    STDMETHOD(GetAdapterDisplayMode)(UINT Adapter,D3DDISPLAYMODE* pMode);
    STDMETHOD(CheckDeviceType)(UINT Adapter,D3DDEVTYPE DevType,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed);
    STDMETHOD(CheckDeviceFormat)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat);
    STDMETHOD(CheckDeviceMultiSampleType)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels);
    STDMETHOD(CheckDepthStencilMatch)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat);
    STDMETHOD(CheckDeviceFormatConversion)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat);
    STDMETHOD(GetDeviceCaps)(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps);
    STDMETHOD_(HMONITOR, GetAdapterMonitor)(UINT Adapter);
    STDMETHOD(CreateDevice)(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface);
};

class Direct3DDevice8Port : public IDirect3DDevice8Port, public IDirect3DDevice9
{
protected:
    IDirect3DDevice9    *m_Device;
    Direct3D8Port       *m_d3d8;

public:
    Direct3DDevice8Port(IDirect3DDevice9 *Device9, Direct3D8Port *d3d8)
    {
        m_Device = Device9;
        m_d3d8   = d3d8;

        d3d8->AddRef();
    }

    ~Direct3DDevice8Port()
    {
        m_d3d8->Release();
    }

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DDevice8 methods ***/
    STDMETHOD(TestCooperativeLevel8)();
    STDMETHOD_(UINT, GetAvailableTextureMem8)();
    STDMETHOD(ResourceManagerDiscardBytes8)(DWORD Bytes);
    STDMETHOD(GetDirect3D8)(IDirect3D8** ppD3D8);
    STDMETHOD(GetDeviceCaps8)(D3DCAPS8* pCaps);
    STDMETHOD(GetDisplayMode8)(D3DDISPLAYMODE* pMode);
    STDMETHOD(GetCreationParameters8)(D3DDEVICE_CREATION_PARAMETERS *pParameters);
    STDMETHOD(SetCursorProperties8)(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface8* pCursorBitmap);
    STDMETHOD_(void, SetCursorPosition8)(int X,int Y,DWORD Flags);
    STDMETHOD_(BOOL, ShowCursor8)(BOOL bShow);
    STDMETHOD(CreateAdditionalSwapChain8)(D3D8PRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain8** pSwapChain);
    STDMETHOD(Reset8)(D3D8PRESENT_PARAMETERS* pPresentationParameters);
    STDMETHOD(Present8)(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion);
    STDMETHOD(GetBackBuffer8)(UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer);
    STDMETHOD(GetRasterStatus8)(D3DRASTER_STATUS* pRasterStatus);
    STDMETHOD_(void, SetGammaRamp8)(DWORD Flags,CONST D3DGAMMARAMP* pRamp);
    STDMETHOD_(void, GetGammaRamp8)(D3DGAMMARAMP* pRamp);
    STDMETHOD(CreateTexture8)(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture8** ppTexture);
    STDMETHOD(CreateVolumeTexture8)(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture8** ppVolumeTexture);
    STDMETHOD(CreateCubeTexture8)(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture8** ppCubeTexture);
    STDMETHOD(CreateVertexBuffer8)(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer8** ppVertexBuffer);
    STDMETHOD(CreateIndexBuffer8)(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer8** ppIndexBuffer);
    STDMETHOD(CreateRenderTarget8)(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,BOOL Lockable,IDirect3DSurface8** ppSurface);
    STDMETHOD(CreateDepthStencilSurface8)(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,IDirect3DSurface8** ppSurface);
    STDMETHOD(CreateImageSurface8)(UINT Width,UINT Height,D3DFORMAT Format,IDirect3DSurface8** ppSurface);
    STDMETHOD(CopyRects8)(IDirect3DSurface8* pSourceSurface,CONST RECT* pSourceRectsArray,UINT cRects,IDirect3DSurface8* pDestinationSurface,CONST POINT* pDestPointsArray);
    STDMETHOD(UpdateTexture8)(IDirect3DBaseTexture8* pSourceTexture,IDirect3DBaseTexture8* pDestinationTexture);
    STDMETHOD(GetFrontBuffer8)(IDirect3DSurface8* pDestSurface);
    STDMETHOD(SetRenderTarget8)(IDirect3DSurface8* pRenderTarget,IDirect3DSurface8* pNewZStencil);
    STDMETHOD(GetRenderTarget8)(IDirect3DSurface8** ppRenderTarget);
    STDMETHOD(GetDepthStencilSurface8)(IDirect3DSurface8** ppZStencilSurface);
    STDMETHOD(BeginScene8)();
    STDMETHOD(EndScene8)();
    STDMETHOD(Clear8)(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil);
    STDMETHOD(SetTransform8)(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix);
    STDMETHOD(GetTransform8)(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix);
    STDMETHOD(MultiplyTransform8)(D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*);
    STDMETHOD(SetViewport8)(CONST D3DVIEWPORT8* pViewport);
    STDMETHOD(GetViewport8)(D3DVIEWPORT8* pViewport);
    STDMETHOD(SetMaterial8)(CONST D3DMATERIAL8* pMaterial);
    STDMETHOD(GetMaterial8)(D3DMATERIAL8* pMaterial);
    STDMETHOD(SetLight8)(DWORD Index,CONST D3DLIGHT8*);
    STDMETHOD(GetLight8)(DWORD Index,D3DLIGHT8*);
    STDMETHOD(LightEnable8)(DWORD Index,BOOL Enable);
    STDMETHOD(GetLightEnable8)(DWORD Index,BOOL* pEnable);
    STDMETHOD(SetClipPlane8)(DWORD Index,CONST float* pPlane);
    STDMETHOD(GetClipPlane8)(DWORD Index,float* pPlane);
    STDMETHOD(SetRenderState8)(D3DRENDERSTATETYPE State,DWORD Value);
    STDMETHOD(GetRenderState8)(D3DRENDERSTATETYPE State,DWORD* pValue);
    STDMETHOD(BeginStateBlock8)();
    STDMETHOD(EndStateBlock8)(DWORD* pToken);
    STDMETHOD(ApplyStateBlock8)(DWORD Token);
    STDMETHOD(CaptureStateBlock8)(DWORD Token);
    STDMETHOD(DeleteStateBlock8)(DWORD Token);
    STDMETHOD(CreateStateBlock8)(D3DSTATEBLOCKTYPE Type,DWORD* pToken);
    STDMETHOD(SetClipStatus8)(CONST D3DCLIPSTATUS8* pClipStatus);
    STDMETHOD(GetClipStatus8)(D3DCLIPSTATUS8* pClipStatus);
    STDMETHOD(GetTexture8)(DWORD Stage,IDirect3DBaseTexture8** ppTexture);
    STDMETHOD(SetTexture8)(DWORD Stage,IDirect3DBaseTexture8* pTexture);
    STDMETHOD(GetTextureStageState8)(DWORD Stage,D3D8TEXTURESTAGESTATETYPE Type,DWORD* pValue);
    STDMETHOD(SetTextureStageState8)(DWORD Stage,D3D8TEXTURESTAGESTATETYPE Type,DWORD Value);
    STDMETHOD(ValidateDevice8)(DWORD* pNumPasses);
    STDMETHOD(GetInfo8)(DWORD DevInfoID,void* pDevInfoStruct,DWORD DevInfoStructSize);
    STDMETHOD(SetPaletteEntries8)(UINT PaletteNumber,CONST PALETTEENTRY* pEntries);
    STDMETHOD(GetPaletteEntries8)(UINT PaletteNumber,PALETTEENTRY* pEntries);
    STDMETHOD(SetCurrentTexturePalette8)(UINT PaletteNumber);
    STDMETHOD(GetCurrentTexturePalette8)(UINT *PaletteNumber);
    STDMETHOD(DrawPrimitive8)(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount);
    STDMETHOD(DrawIndexedPrimitive8)(D3DPRIMITIVETYPE,UINT minIndex,UINT NumVertices,UINT startIndex,UINT primCount);
    STDMETHOD(DrawPrimitiveUP8)(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
    STDMETHOD(DrawIndexedPrimitiveUP8)(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertexIndices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
    STDMETHOD(ProcessVertices8)(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer8* pDestBuffer,DWORD Flags);
    STDMETHOD(CreateVertexShader8)(CONST DWORD* pDeclaration,CONST DWORD* pFunction,DWORD* pHandle,DWORD Usage);
    STDMETHOD(SetVertexShader8)(DWORD Handle);
    STDMETHOD(GetVertexShader8)(DWORD* pHandle);
    STDMETHOD(DeleteVertexShader8)(DWORD Handle);
    STDMETHOD(SetVertexShaderConstant8)(DWORD Register,CONST void* pConstantData,DWORD ConstantCount);
    STDMETHOD(GetVertexShaderConstant8)(DWORD Register,void* pConstantData,DWORD ConstantCount);
    STDMETHOD(GetVertexShaderDeclaration8)(DWORD Handle,void* pData,DWORD* pSizeOfData);
    STDMETHOD(GetVertexShaderFunction8)(DWORD Handle,void* pData,DWORD* pSizeOfData);
    STDMETHOD(SetStreamSource8)(UINT StreamNumber,IDirect3DVertexBuffer8* pStreamData,UINT Stride);
    STDMETHOD(GetStreamSource8)(UINT StreamNumber,IDirect3DVertexBuffer8** ppStreamData,UINT* pStride);
    STDMETHOD(SetIndices8)(IDirect3DIndexBuffer8* pIndexData,UINT BaseVertexIndex);
    STDMETHOD(GetIndices8)(IDirect3DIndexBuffer8** ppIndexData,UINT* pBaseVertexIndex);
    STDMETHOD(CreatePixelShader8)(CONST DWORD* pFunction,DWORD* pHandle);
    STDMETHOD(SetPixelShader8)(DWORD Handle);
    STDMETHOD(GetPixelShader8)(DWORD* pHandle);
    STDMETHOD(DeletePixelShader8)(DWORD Handle);
    STDMETHOD(SetPixelShaderConstant8)(DWORD Register,CONST void* pConstantData,DWORD ConstantCount);
    STDMETHOD(GetPixelShaderConstant8)(DWORD Register,void* pConstantData,DWORD ConstantCount);
    STDMETHOD(GetPixelShaderFunction8)(DWORD Handle,void* pData,DWORD* pSizeOfData);
    STDMETHOD(DrawRectPatch8)(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo);
    STDMETHOD(DrawTriPatch8)(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo);
    STDMETHOD(DeletePatch8)(UINT Handle);

    /************************************************************************
      IDirect3DDevice9 interface
    ************************************************************************/
        /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef)();
    STDMETHOD_(ULONG,Release)();

    /*** IDirect3DDevice9 methods ***/
    STDMETHOD(TestCooperativeLevel)();
    STDMETHOD_(UINT, GetAvailableTextureMem)();
    STDMETHOD(EvictManagedResources)();
    STDMETHOD(GetDirect3D)(IDirect3D9** ppD3D9);
    STDMETHOD(GetDeviceCaps)(D3DCAPS9* pCaps);
    STDMETHOD(GetDisplayMode)(UINT iSwapChain,D3DDISPLAYMODE* pMode);
    STDMETHOD(GetCreationParameters)(D3DDEVICE_CREATION_PARAMETERS *pParameters);
    STDMETHOD(SetCursorProperties)(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap);
    STDMETHOD_(void, SetCursorPosition)(int X,int Y,DWORD Flags);
    STDMETHOD_(BOOL, ShowCursor)(BOOL bShow);
    STDMETHOD(CreateAdditionalSwapChain)(D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain);
    STDMETHOD(GetSwapChain)(UINT iSwapChain,IDirect3DSwapChain9** pSwapChain);
    STDMETHOD_(UINT, GetNumberOfSwapChains)();
    STDMETHOD(Reset)(D3DPRESENT_PARAMETERS* pPresentationParameters);
    STDMETHOD(Present)(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion);
    STDMETHOD(GetBackBuffer)(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer);
    STDMETHOD(GetRasterStatus)(UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus);
    STDMETHOD(SetDialogBoxMode)(BOOL bEnableDialogs);
    STDMETHOD_(void, SetGammaRamp)(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp);
    STDMETHOD_(void, GetGammaRamp)(UINT iSwapChain,D3DGAMMARAMP* pRamp);
    STDMETHOD(CreateTexture)(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle);
    STDMETHOD(CreateVolumeTexture)(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle);
    STDMETHOD(CreateCubeTexture)(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle);
    STDMETHOD(CreateVertexBuffer)(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle);
    STDMETHOD(CreateIndexBuffer)(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle);
    STDMETHOD(CreateRenderTarget)(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
    STDMETHOD(CreateDepthStencilSurface)(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
    STDMETHOD(UpdateSurface)(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint);
    STDMETHOD(UpdateTexture)(IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture);
    STDMETHOD(GetRenderTargetData)(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface);
    STDMETHOD(GetFrontBufferData)(UINT iSwapChain,IDirect3DSurface9* pDestSurface);
    STDMETHOD(StretchRect)(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter);
    STDMETHOD(ColorFill)(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color);
    STDMETHOD(CreateOffscreenPlainSurface)(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
    STDMETHOD(SetRenderTarget)(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget);
    STDMETHOD(GetRenderTarget)(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget);
    STDMETHOD(SetDepthStencilSurface)(IDirect3DSurface9* pNewZStencil);
    STDMETHOD(GetDepthStencilSurface)(IDirect3DSurface9** ppZStencilSurface);
    STDMETHOD(BeginScene)();
    STDMETHOD(EndScene)();
    STDMETHOD(Clear)(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil);
    STDMETHOD(SetTransform)(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix);
    STDMETHOD(GetTransform)(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix);
    STDMETHOD(MultiplyTransform)(D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*);
    STDMETHOD(SetViewport)(CONST D3DVIEWPORT9* pViewport);
    STDMETHOD(GetViewport)(D3DVIEWPORT9* pViewport);
    STDMETHOD(SetMaterial)(CONST D3DMATERIAL9* pMaterial);
    STDMETHOD(GetMaterial)(D3DMATERIAL9* pMaterial);
    STDMETHOD(SetLight)(DWORD Index,CONST D3DLIGHT9*);
    STDMETHOD(GetLight)(DWORD Index,D3DLIGHT9*);
    STDMETHOD(LightEnable)(DWORD Index,BOOL Enable);
    STDMETHOD(GetLightEnable)(DWORD Index,BOOL* pEnable);
    STDMETHOD(SetClipPlane)(DWORD Index,CONST float* pPlane);
    STDMETHOD(GetClipPlane)(DWORD Index,float* pPlane);
    STDMETHOD(SetRenderState)(D3DRENDERSTATETYPE State,DWORD Value);
    STDMETHOD(GetRenderState)(D3DRENDERSTATETYPE State,DWORD* pValue);
    STDMETHOD(CreateStateBlock)(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB);
    STDMETHOD(BeginStateBlock)();
    STDMETHOD(EndStateBlock)(IDirect3DStateBlock9** ppSB);
    STDMETHOD(SetClipStatus)(CONST D3DCLIPSTATUS9* pClipStatus);
    STDMETHOD(GetClipStatus)(D3DCLIPSTATUS9* pClipStatus);
    STDMETHOD(GetTexture)(DWORD Stage,IDirect3DBaseTexture9** ppTexture);
    STDMETHOD(SetTexture)(DWORD Stage,IDirect3DBaseTexture9* pTexture);
    STDMETHOD(GetTextureStageState)(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue);
    STDMETHOD(SetTextureStageState)(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value);
    STDMETHOD(GetSamplerState)(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue);
    STDMETHOD(SetSamplerState)(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value);
    STDMETHOD(ValidateDevice)(DWORD* pNumPasses);
    STDMETHOD(SetPaletteEntries)(UINT PaletteNumber,CONST PALETTEENTRY* pEntries);
    STDMETHOD(GetPaletteEntries)(UINT PaletteNumber,PALETTEENTRY* pEntries);
    STDMETHOD(SetCurrentTexturePalette)(UINT PaletteNumber);
    STDMETHOD(GetCurrentTexturePalette)(UINT *PaletteNumber);
    STDMETHOD(SetScissorRect)(CONST RECT* pRect);
    STDMETHOD(GetScissorRect)(RECT* pRect);
    STDMETHOD(SetSoftwareVertexProcessing)(BOOL bSoftware);
    STDMETHOD_(BOOL, GetSoftwareVertexProcessing)();
    STDMETHOD(SetNPatchMode)(float nSegments);
    STDMETHOD_(float, GetNPatchMode)();
    STDMETHOD(DrawPrimitive)(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount);
    STDMETHOD(DrawIndexedPrimitive)(D3DPRIMITIVETYPE,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
    STDMETHOD(DrawPrimitiveUP)(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
    STDMETHOD(DrawIndexedPrimitiveUP)(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
    STDMETHOD(ProcessVertices)(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags);
    STDMETHOD(CreateVertexDeclaration)(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl);
    STDMETHOD(SetVertexDeclaration)(IDirect3DVertexDeclaration9* pDecl);
    STDMETHOD(GetVertexDeclaration)(IDirect3DVertexDeclaration9** ppDecl);
    STDMETHOD(SetFVF)(DWORD FVF);
    STDMETHOD(GetFVF)(DWORD* pFVF);
    STDMETHOD(CreateVertexShader)(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader);
    STDMETHOD(SetVertexShader)(IDirect3DVertexShader9* pShader);
    STDMETHOD(GetVertexShader)(IDirect3DVertexShader9** ppShader);
    STDMETHOD(SetVertexShaderConstantF)(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);
    STDMETHOD(GetVertexShaderConstantF)(UINT StartRegister,float* pConstantData,UINT Vector4fCount);
    STDMETHOD(SetVertexShaderConstantI)(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount);
    STDMETHOD(GetVertexShaderConstantI)(UINT StartRegister,int* pConstantData,UINT Vector4iCount);
    STDMETHOD(SetVertexShaderConstantB)(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount);
    STDMETHOD(GetVertexShaderConstantB)(UINT StartRegister,BOOL* pConstantData,UINT BoolCount);
    STDMETHOD(SetStreamSource)(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride);
    STDMETHOD(GetStreamSource)(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride);
    STDMETHOD(SetStreamSourceFreq)(UINT StreamNumber,UINT Setting);
    STDMETHOD(GetStreamSourceFreq)(UINT StreamNumber,UINT* pSetting);
    STDMETHOD(SetIndices)(IDirect3DIndexBuffer9* pIndexData);
    STDMETHOD(GetIndices)(IDirect3DIndexBuffer9** ppIndexData);
    STDMETHOD(CreatePixelShader)(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader);
    STDMETHOD(SetPixelShader)(IDirect3DPixelShader9* pShader);
    STDMETHOD(GetPixelShader)(IDirect3DPixelShader9** ppShader);
    STDMETHOD(SetPixelShaderConstantF)(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);
    STDMETHOD(GetPixelShaderConstantF)(UINT StartRegister,float* pConstantData,UINT Vector4fCount);
    STDMETHOD(SetPixelShaderConstantI)(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount);
    STDMETHOD(GetPixelShaderConstantI)(UINT StartRegister,int* pConstantData,UINT Vector4iCount);
    STDMETHOD(SetPixelShaderConstantB)(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount);
    STDMETHOD(GetPixelShaderConstantB)(UINT StartRegister,BOOL* pConstantData,UINT BoolCount);
    STDMETHOD(DrawRectPatch)(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo);
    STDMETHOD(DrawTriPatch)(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo);
    STDMETHOD(DeletePatch)(UINT Handle);
    STDMETHOD(CreateQuery)(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery);
};

class Direct3DPixelShader8Port : public IDirect3DPixelShader8Port
{
protected:
    Direct3DDevice8Port     *m_Device;
    IDirect3DPixelShader9   *m_Shader;

public:
    Direct3DPixelShader8Port(IDirect3DPixelShader9 *Shader, Direct3DDevice8Port *Device)
    {
        m_Shader = Shader;
        m_Device = Device;

        Device->AddRef();
    }

    ~Direct3DPixelShader8Port()
    {
        m_Device->Release();
    }

    operator PDIRECT3DPIXELSHADER9()
    {
        return m_Shader;
    }

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj)
    {
        return m_Shader->QueryInterface(riid, ppvObj);
    }

    STDMETHOD_(ULONG,AddRef8)()
    {
        return m_Shader->AddRef();
    }

    STDMETHOD_(ULONG,Release8)()
    {
        return D3DAutoRelease(this, m_Shader);
    }

    /*** IDirect3DPixelShader9 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice9** ppDevice)
    {
        m_Device->AddRef();
        *ppDevice = m_Device;
        return S_OK;
    }

    STDMETHOD(GetFunction8)(void* pFunction,UINT* pSizeOfData)
    {
        return m_Shader->GetFunction(pFunction, pSizeOfData);
    }
};

class Direct3DStateBlock8Port : public IDirect3DStateBlock8Port
{
protected:
    Direct3DDevice8Port     *m_Device;
    IDirect3DStateBlock9    *m_Block;

public:
    Direct3DStateBlock8Port(IDirect3DStateBlock9 *Block, Direct3DDevice8Port *Device)
    {
        m_Block = Block;
        m_Device = Device;

        Device->AddRef();
    }

    ~Direct3DStateBlock8Port()
    {
        m_Device->Release();
    }

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj)
    {
        return m_Block->QueryInterface(riid, ppvObj);
    }

    STDMETHOD_(ULONG,AddRef8)()
    {
        return m_Block->AddRef();
    }

    STDMETHOD_(ULONG,Release8)()
    {
        return D3DAutoRelease(this, m_Block);
    }

    /*** IDirect3DStateBlock9 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice9** ppDevice)
    {
        m_Device->AddRef();
        *ppDevice = m_Device;
        return S_OK;
    }

    STDMETHOD(Capture8)()
    {
        return m_Block->Capture();
    }

    STDMETHOD(Apply8)()
    {
        return m_Block->Apply();
    }
};

class Direct3DSwapChain8Port : public IDirect3DSwapChain8Port, public IDirect3DSwapChain9
{
protected:
    IDirect3DSwapChain9 *m_SwapChain;
    Direct3DDevice8Port *m_Device;

public:
    Direct3DSwapChain8Port(IDirect3DSwapChain9 *SwapChain, Direct3DDevice8Port *Device)
    {
        m_SwapChain = SwapChain;
        m_Device    = Device;

        Device->AddRef();
    }

    ~Direct3DSwapChain8Port()
    {
        m_Device->Release();
    }

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DSwapChain8 methods ***/
    STDMETHOD(Present8)(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion);
    STDMETHOD(GetBackBuffer8)(UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer);

    /************************************************************************
      9
    ************************************************************************/
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef)();
    STDMETHOD_(ULONG,Release)();

    /*** IDirect3DSwapChain9 methods ***/
    STDMETHOD(Present)(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags);
    STDMETHOD(GetFrontBufferData)(IDirect3DSurface9* pDestSurface);
    STDMETHOD(GetBackBuffer)(UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer);
    STDMETHOD(GetRasterStatus)(D3DRASTER_STATUS* pRasterStatus);
    STDMETHOD(GetDisplayMode)(D3DDISPLAYMODE* pMode);
    STDMETHOD(GetDevice)(IDirect3DDevice9** ppDevice);
    STDMETHOD(GetPresentParameters)(D3DPRESENT_PARAMETERS* pPresentationParameters);
};

class Direct3DResource8Port : public IDirect3DResource8Port, public IDirect3DResource9
{
protected:
    IDirect3DResource9 *m_Resource;

public:
};

class Direct3DBaseTexture8Port : public IDirect3DBaseTexture8Port, public IDirect3DBaseTexture9
{
protected:
    IDirect3DBaseTexture9   *m_Texture;
    Direct3DDevice8Port     *m_Device;

public:
    Direct3DBaseTexture8Port(IDirect3DBaseTexture9 *Texture, Direct3DDevice8Port *Device)
    {
        m_Texture  = Texture;
        m_Device   = Device;

        Device->AddRef();
    }

    ~Direct3DBaseTexture8Port()
    {
        m_Device->Release();
    }

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj)
    {
        return m_Texture->QueryInterface(riid, ppvObj);
    }

    STDMETHOD_(ULONG,AddRef8)()
    {
        return m_Texture->AddRef();
    }

    STDMETHOD_(ULONG,Release8)()
    {
        return D3DAutoRelease(this, m_Texture);
    }

    /*** IDirect3DResource8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice)
    {
        m_Device->AddRef();
        *(PVOID *)ppDevice = m_Device;
        return S_OK;
    }

    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
    {
        return m_Texture->SetPrivateData(refguid, pData, SizeOfData, Flags);
    }

    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData)
    {
        return m_Texture->GetPrivateData(refguid, pData, pSizeOfData);
    }

    STDMETHOD(FreePrivateData8)(REFGUID refguid)
    {
        return m_Texture->FreePrivateData(refguid);
    }

    STDMETHOD_(DWORD, SetPriority8)(DWORD PriorityNew)
    {
        return m_Texture->SetPriority(PriorityNew);
    }

    STDMETHOD_(DWORD, GetPriority8)()
    {
        return m_Texture->GetPriority();
    }

    STDMETHOD_(void, PreLoad8)()
    {
        m_Texture->PreLoad();
    }

    STDMETHOD_(D3DRESOURCETYPE, GetType8)()
    {
        return m_Texture->GetType();
    }

    STDMETHOD_(DWORD, SetLOD8)(DWORD LODNew)
    {
        return m_Texture->SetLOD(LODNew);
    }

    STDMETHOD_(DWORD, GetLOD8)()
    {
        return m_Texture->GetLOD();
    }

    STDMETHOD_(DWORD, GetLevelCount8)()
    {
        return m_Texture->GetLevelCount();
    }

    /************************************************************************
      9
    ************************************************************************/
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj)
    {
        return m_Texture->QueryInterface(riid, ppvObj);
    }

    STDMETHOD_(ULONG,AddRef)()
    {
        return m_Texture->AddRef();
    }

    STDMETHOD_(ULONG,Release)()
    {
        return D3DAutoRelease(this, m_Texture);
    }

    /*** IDirect3DResource9 methods ***/
    STDMETHOD(GetDevice)(IDirect3DDevice9** ppDevice)
    {
        m_Device->AddRef();
        *ppDevice = m_Device;
        return S_OK;
    }

    STDMETHOD(SetPrivateData)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
    {
        return m_Texture->SetPrivateData(refguid, pData, SizeOfData, Flags);
    }

    STDMETHOD(GetPrivateData)(REFGUID refguid,void* pData,DWORD* pSizeOfData)
    {
        return m_Texture->GetPrivateData(refguid, pData, pSizeOfData);
    }

    STDMETHOD(FreePrivateData)(REFGUID refguid)
    {
        return m_Texture->FreePrivateData(refguid);
    }

    STDMETHOD_(DWORD, SetPriority)(DWORD PriorityNew)
    {
        return m_Texture->SetPriority(PriorityNew);
    }

    STDMETHOD_(DWORD, GetPriority)()
    {
        return m_Texture->GetPriority();
    }

    STDMETHOD_(void, PreLoad)()
    {
        m_Texture->PreLoad();
    }

    STDMETHOD_(D3DRESOURCETYPE, GetType)()
    {
        return m_Texture->GetType();
    }

    STDMETHOD_(DWORD, SetLOD)(DWORD LODNew)
    {
        return m_Texture->SetLOD(LODNew);
    }

    STDMETHOD_(DWORD, GetLOD)()
    {
        return m_Texture->GetLOD();
    }

    STDMETHOD_(DWORD, GetLevelCount)()
    {
        return m_Texture->GetLevelCount();
    }

    STDMETHOD(SetAutoGenFilterType)(D3DTEXTUREFILTERTYPE FilterType)
    {
        return m_Texture->SetAutoGenFilterType(FilterType);
    }

    STDMETHOD_(D3DTEXTUREFILTERTYPE, GetAutoGenFilterType)()
    {
        return m_Texture->GetAutoGenFilterType();
    }

    STDMETHOD_(void, GenerateMipSubLevels)()
    {
        return m_Texture->GenerateMipSubLevels();
    }
};

class Direct3DTexture8Port : public IDirect3DTexture8Port, public IDirect3DTexture9
{
protected:
    IDirect3DTexture9   *m_Texture;
    Direct3DDevice8Port *m_Device;

public:
    Direct3DTexture8Port(IDirect3DTexture9 *Texture, Direct3DDevice8Port *Device)
    {
        m_Texture   = Texture;
        m_Device    = Device;

        Device->AddRef();
    }

    ~Direct3DTexture8Port()
    {
        m_Device->Release();
    }

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj)
    {
        return m_Texture->QueryInterface(riid, ppvObj);
    }

    STDMETHOD_(ULONG,AddRef8)()
    {
        return m_Texture->AddRef();
    }

    STDMETHOD_(ULONG,Release8)()
    {
        return D3DAutoRelease(this, m_Texture);
    }

    /*** IDirect3DBaseTexture8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice)
    {
        m_Device->AddRef();
        *(PVOID *)ppDevice = m_Device;
        return S_OK;
    }

    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
    {
        return m_Texture->SetPrivateData(refguid, pData, SizeOfData, Flags);
    }

    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData)
    {
        return m_Texture->GetPrivateData(refguid, pData, pSizeOfData);
    }

    STDMETHOD(FreePrivateData8)(REFGUID refguid)
    {
        return m_Texture->FreePrivateData(refguid);
    }

    STDMETHOD_(DWORD, SetPriority8)(DWORD PriorityNew)
    {
        return m_Texture->SetPriority(PriorityNew);
    }

    STDMETHOD_(DWORD, GetPriority8)()
    {
        return m_Texture->GetPriority();
    }

    STDMETHOD_(void, PreLoad8)()
    {
        m_Texture->PreLoad();
    }

    STDMETHOD_(D3DRESOURCETYPE, GetType8)()
    {
        return m_Texture->GetType();
    }

    STDMETHOD_(DWORD, SetLOD8)(DWORD LODNew)
    {
        return m_Texture->SetLOD(LODNew);
    }

    STDMETHOD_(DWORD, GetLOD8)()
    {
        return m_Texture->GetLOD();
    }

    STDMETHOD_(DWORD, GetLevelCount8)()
    {
        return m_Texture->GetLevelCount();
    }

    STDMETHOD(GetLevelDesc8)(UINT Level,D3D8SURFACE_DESC *pDesc)
    {
        HRESULT         Result;
        D3DSURFACE_DESC Desc;
        D3DLOCKED_RECT  LockedRect;

        Result = m_Texture->GetLevelDesc(Level, &Desc);
        if (FAILED(Result))
            return Result;

        if (FAILED(m_Texture->LockRect(0, &LockedRect, NULL, 0)))
        {
            LockedRect.Pitch = 0;
        }
        else
        {
            m_Texture->UnlockRect(0);
            LockedRect.Pitch *= Desc.Height;
        }

        SurfaceDesc9To8(pDesc, &Desc, LockedRect.Pitch);

        return Result;
    }

    STDMETHOD(GetSurfaceLevel8)(UINT Level,IDirect3DSurface8** ppSurfaceLevel);

    STDMETHOD(LockRect8)(UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags)
    {
        return m_Texture->LockRect(Level, pLockedRect, pRect, Flags);
    }

    STDMETHOD(UnlockRect8)(UINT Level)
    {
        return m_Texture->UnlockRect(Level);
    }

    STDMETHOD(AddDirtyRect8)(CONST RECT* pDirtyRect)
    {
        return m_Texture->AddDirtyRect(pDirtyRect);
    }

    /************************************************************************
      9
    ************************************************************************/
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj)
    {
        return m_Texture->QueryInterface(riid, ppvObj);
    }

    STDMETHOD_(ULONG,AddRef)()
    {
        return m_Texture->AddRef();
    }

    STDMETHOD_(ULONG,Release)()
    {
        return D3DAutoRelease(this, m_Texture);
    }

    /*** IDirect3DBaseTexture9 methods ***/
    STDMETHOD(GetDevice)(IDirect3DDevice9** ppDevice)
    {
        m_Device->AddRef();
        *ppDevice = m_Device;
        return S_OK;
    }

    STDMETHOD(SetPrivateData)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
    {
        return m_Texture->SetPrivateData(refguid, pData, SizeOfData, Flags);
    }

    STDMETHOD(GetPrivateData)(REFGUID refguid,void* pData,DWORD* pSizeOfData)
    {
        return m_Texture->GetPrivateData(refguid, pData, pSizeOfData);
    }

    STDMETHOD(FreePrivateData)(REFGUID refguid)
    {
        return m_Texture->FreePrivateData(refguid);
    }

    STDMETHOD_(DWORD, SetPriority)(DWORD PriorityNew)
    {
        return m_Texture->SetPriority(PriorityNew);
    }

    STDMETHOD_(DWORD, GetPriority)()
    {
        return m_Texture->GetPriority();
    }

    STDMETHOD_(void, PreLoad)()
    {
        m_Texture->PreLoad();
    }

    STDMETHOD_(D3DRESOURCETYPE, GetType)()
    {
        return m_Texture->GetType();
    }

    STDMETHOD_(DWORD, SetLOD)(DWORD LODNew)
    {
        return m_Texture->SetLOD(LODNew);
    }

    STDMETHOD_(DWORD, GetLOD)()
    {
        return m_Texture->GetLOD();
    }

    STDMETHOD_(DWORD, GetLevelCount)()
    {
        return m_Texture->GetLevelCount();
    }

    STDMETHOD(SetAutoGenFilterType)(D3DTEXTUREFILTERTYPE FilterType)
    {
        return m_Texture->SetAutoGenFilterType(FilterType);
    }

    STDMETHOD_(D3DTEXTUREFILTERTYPE, GetAutoGenFilterType)()
    {
        return m_Texture->GetAutoGenFilterType();
    }

    STDMETHOD_(void, GenerateMipSubLevels)()
    {
        m_Texture->GenerateMipSubLevels();
    }

    STDMETHOD(GetLevelDesc)(UINT Level,D3DSURFACE_DESC *pDesc)
    {
        return m_Texture->GetLevelDesc(Level, pDesc);
    }

    STDMETHOD(GetSurfaceLevel)(UINT Level,IDirect3DSurface9** ppSurfaceLevel);

    STDMETHOD(LockRect)(UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags)
    {
        return m_Texture->LockRect(Level, pLockedRect, pRect, Flags);
    }

    STDMETHOD(UnlockRect)(UINT Level)
    {
        return m_Texture->UnlockRect(Level);
    }

    STDMETHOD(AddDirtyRect)(CONST RECT* pDirtyRect)
    {
        return m_Texture->AddDirtyRect(pDirtyRect);
    }
};

class Direct3DVolumeTexture8Port : public IDirect3DVolumeTexture8Port, public IDirect3DVolumeTexture9
{
protected:
    IDirect3DVolumeTexture9 *m_VolumeTexture;
    Direct3DDevice8Port     *m_Device;

public:
    Direct3DVolumeTexture8Port(IDirect3DVolumeTexture9 *VolumeTexture, Direct3DDevice8Port *Device)
    {
        m_VolumeTexture = VolumeTexture;
        m_Device = Device;

        Device->AddRef();
    }

    ~Direct3DVolumeTexture8Port()
    {
        m_Device->Release();
    }

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj)
    {
        return m_VolumeTexture->QueryInterface(riid, ppvObj);
    }

    STDMETHOD_(ULONG,AddRef8)()
    {
        return m_VolumeTexture->AddRef();
    }

    STDMETHOD_(ULONG,Release8)()
    {
        return D3DAutoRelease(this, m_VolumeTexture);
    }

    /*** IDirect3DBaseTexture8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice)
    {
        m_Device->AddRef();
        *(PVOID *)ppDevice = m_Device;
        return S_OK;
    }

    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
    {
        return m_VolumeTexture->SetPrivateData(refguid, pData, SizeOfData, Flags);
    }

    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData)
    {
        return m_VolumeTexture->GetPrivateData(refguid, pData, pSizeOfData);
    }

    STDMETHOD(FreePrivateData8)(REFGUID refguid)
    {
        return m_VolumeTexture->FreePrivateData(refguid);
    }

    STDMETHOD_(DWORD, SetPriority8)(DWORD PriorityNew)
    {
        return m_VolumeTexture->SetPriority(PriorityNew);
    }

    STDMETHOD_(DWORD, GetPriority8)()
    {
        return m_VolumeTexture->GetPriority();
    }

    STDMETHOD_(void, PreLoad8)()
    {
        m_VolumeTexture->PreLoad();
    }

    STDMETHOD_(D3DRESOURCETYPE, GetType8)()
    {
        return m_VolumeTexture->GetType();
    }

    STDMETHOD_(DWORD, SetLOD8)(DWORD LODNew)
    {
        return m_VolumeTexture->SetLOD(LODNew);
    }

    STDMETHOD_(DWORD, GetLOD8)()
    {
        return m_VolumeTexture->GetLOD();
    }

    STDMETHOD_(DWORD, GetLevelCount8)()
    {
        return m_VolumeTexture->GetLevelCount();
    }

    STDMETHOD(GetLevelDesc8)(UINT Level,D3D8VOLUME_DESC *pDesc)
    {
        HRESULT         Result;
        D3DVOLUME_DESC  Desc;
        D3DLOCKED_BOX   LockedBox;

        Result = m_VolumeTexture->GetLevelDesc(Level, &Desc);
        if (FAILED(Result))
            return Result;

        if (FAILED(m_VolumeTexture->LockBox(Level, &LockedBox, NULL, 0)))
        {
            LockedBox.SlicePitch = 0;
        }
        else
        {
            m_VolumeTexture->UnlockBox(Level);
            LockedBox.SlicePitch *= Desc.Height;
        }

        VolumeDesc9To8(pDesc, &Desc, LockedBox.SlicePitch);

        return Result;
    }

    STDMETHOD(GetVolumeLevel8)(UINT Level, IDirect3DVolume8** ppVolumeLevel);

    STDMETHOD(LockBox8)(UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags)
    {
        return m_VolumeTexture->LockBox(Level, pLockedVolume, pBox, Flags);
    }

    STDMETHOD(UnlockBox8)(UINT Level)
    {
        return m_VolumeTexture->UnlockBox(Level);
    }

    STDMETHOD(AddDirtyBox8)(CONST D3DBOX* pDirtyBox)
    {
        return m_VolumeTexture->AddDirtyBox(pDirtyBox);
    }
};

class Direct3DCubeTexture8Port : public IDirect3DCubeTexture8Port, public IDirect3DCubeTexture9
{
protected:
    IDirect3DCubeTexture9 *m_Cube;

public:
};

class Direct3DVertexBuffer8Port : public IDirect3DVertexBuffer8Port, public IDirect3DVertexBuffer9
{
protected:
    IDirect3DVertexBuffer9 *m_Vertex;

public:
};

class Direct3DIndexBuffer8Port : public IDirect3DIndexBuffer8Port, public IDirect3DIndexBuffer9
{
protected:
    IDirect3DIndexBuffer9 *m_Index;

public:
};

class Direct3DSurface8Port : public IDirect3DSurface8Port, public IDirect3DSurface9
{
protected:
    IDirect3DSurface9   *m_Surface;
    Direct3DDevice8Port *m_Device;

public:
    Direct3DSurface8Port(IDirect3DSurface9 *Surface, Direct3DDevice8Port *Device)
    {
        m_Surface   = Surface;
        m_Device    = Device;

        Device->AddRef();
    }

    ~Direct3DSurface8Port()
    {
        m_Device->Release();
    }

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef8)();
    STDMETHOD_(ULONG,Release8)();

    /*** IDirect3DSurface8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice);
    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData8)(REFGUID refguid);
    STDMETHOD(GetContainer8)(REFIID riid,void** ppContainer);
    STDMETHOD(GetDesc8)(D3D8SURFACE_DESC *pDesc);
    STDMETHOD(LockRect8)(D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
    STDMETHOD(UnlockRect8)();

    /************************************************************************
      IDirect3DSurface9
    ************************************************************************/
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj)
    {
        return m_Surface->QueryInterface(riid, ppvObj);
    }

    STDMETHOD_(ULONG,AddRef)()
    {
        return m_Surface->AddRef();
    }

    STDMETHOD_(ULONG,Release)()
    {
        return D3DAutoRelease(this, m_Surface);
    }

    /*** IDirect3DResource9 methods ***/
    STDMETHOD(GetDevice)(IDirect3DDevice9** ppDevice)
    {
        m_Device->AddRef();
        *ppDevice = m_Device;
        return S_OK;
    }

    STDMETHOD(SetPrivateData)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
    {
        return m_Surface->SetPrivateData(refguid, pData, SizeOfData, Flags);
    }

    STDMETHOD(GetPrivateData)(REFGUID refguid,void* pData,DWORD* pSizeOfData)
    {
        return m_Surface->GetPrivateData(refguid, pData, pSizeOfData);
    }

    STDMETHOD(FreePrivateData)(REFGUID refguid)
    {
        return m_Surface->FreePrivateData(refguid);
    }

    STDMETHOD_(DWORD, SetPriority)(DWORD PriorityNew)
    {
        return m_Surface->SetPriority(PriorityNew);
    }

    STDMETHOD_(DWORD, GetPriority)()
    {
        return m_Surface->GetPriority();
    }

    STDMETHOD_(void, PreLoad)()
    {
        return m_Surface->PreLoad();
    }

    STDMETHOD_(D3DRESOURCETYPE, GetType)()
    {
        return m_Surface->GetType();
    }

    STDMETHOD(GetContainer)(REFIID riid,void** ppContainer)
    {
        return m_Surface->GetContainer(riid, ppContainer);
    }

    STDMETHOD(GetDesc)(D3DSURFACE_DESC *pDesc)
    {
        return m_Surface->GetDesc(pDesc);
    }

    STDMETHOD(LockRect)(D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags)
    {
        return m_Surface->LockRect(pLockedRect, pRect, Flags);
    }

    STDMETHOD(UnlockRect)()
    {
        return m_Surface->UnlockRect();
    }

    STDMETHOD(GetDC)(HDC *phdc)
    {
        return m_Surface->GetDC(phdc);
    }

    STDMETHOD(ReleaseDC)(HDC hdc)
    {
        return m_Surface->ReleaseDC(hdc);
    }
};

class Direct3DVolume8Port : public IDirect3DVolume8Port, public IDirect3DVolume9
{
protected:
    IDirect3DVolume9    *m_Volume;
    Direct3DDevice8Port *m_Device;

public:
    Direct3DVolume8Port(IDirect3DVolume9 *Volume, Direct3DDevice8Port *Device)
    {
        m_Volume    = Volume;
        m_Device    = Device;

        Device->AddRef();
    }

    ~Direct3DVolume8Port()
    {
        m_Device->Release();
    }

public:
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface8)(REFIID riid, void** ppvObj)
    {
        return m_Volume->QueryInterface(riid, ppvObj);
    }

    STDMETHOD_(ULONG,AddRef8)()
    {
        return m_Volume->AddRef();
    }

    STDMETHOD_(ULONG,Release8)()
    {
        return D3DAutoRelease(this, m_Volume);
    }

    /*** IDirect3DVolume8 methods ***/
    STDMETHOD(GetDevice8)(IDirect3DDevice8** ppDevice)
    {
        m_Device->AddRef();
        *(PVOID *)ppDevice = m_Device;
        return S_OK;
    }

    STDMETHOD(SetPrivateData8)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
    {
        return m_Volume->SetPrivateData(refguid, pData, SizeOfData, Flags);
    }

    STDMETHOD(GetPrivateData8)(REFGUID refguid,void* pData,DWORD* pSizeOfData)
    {
        return m_Volume->GetPrivateData(refguid, pData, pSizeOfData);
    }

    STDMETHOD(FreePrivateData8)(REFGUID refguid)
    {
        return m_Volume->FreePrivateData(refguid);
    }

    STDMETHOD(GetContainer8)(REFIID riid,void** ppContainer)
    {
        return m_Volume->GetContainer(riid, ppContainer);
    }

    STDMETHOD(GetDesc8)(D3D8VOLUME_DESC *pDesc)
    {
        HRESULT         Result;
        D3DVOLUME_DESC  Desc;
        D3DLOCKED_BOX   LockedBox;

        Result = m_Volume->GetDesc(&Desc);
        if (FAILED(Result))
            return Result;

        if (FAILED(m_Volume->LockBox(&LockedBox, NULL, 0)))
        {
            LockedBox.SlicePitch = 0;
        }
        else
        {
            m_Volume->UnlockBox();
            LockedBox.SlicePitch *= Desc.Height;
        }

        VolumeDesc9To8(pDesc, &Desc, LockedBox.SlicePitch);

        return Result;
    }

    STDMETHOD(LockBox8)(D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags)
    {
        return m_Volume->LockBox(pLockedVolume, pBox, Flags);
    }

    STDMETHOD(UnlockBox8)()
    {
        return m_Volume->UnlockBox();
    }

    /************************************************************************
      9
    ************************************************************************/
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
    {
        return m_Volume->QueryInterface(riid, ppvObj);
    }

    STDMETHOD_(ULONG,AddRef)(THIS)
    {
        return m_Volume->AddRef();
    }

    STDMETHOD_(ULONG,Release)(THIS)
    {
        return D3DAutoRelease(this, m_Volume);
    }

    /*** IDirect3DVolume9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice)
    {
        m_Device->AddRef();
        *ppDevice = m_Device;
        return S_OK;
    }

    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
    {
        return m_Volume->SetPrivateData(refguid, pData, SizeOfData, Flags);
    }

    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData)
    {
        return m_Volume->GetPrivateData(refguid, pData, pSizeOfData);
    }

    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid)
    {
        return m_Volume->FreePrivateData(refguid);
    }

    STDMETHOD(GetContainer)(THIS_ REFIID riid,void** ppContainer)
    {
        return m_Volume->GetContainer(riid, ppContainer);
    }

    STDMETHOD(GetDesc)(THIS_ D3DVOLUME_DESC *pDesc)
    {
        return m_Volume->GetDesc(pDesc);
    }

    STDMETHOD(LockBox)(THIS_ D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags)
    {
        return m_Volume->LockBox(pLockedVolume, pBox, Flags);
    }

    STDMETHOD(UnlockBox)(THIS)
    {
        return m_Volume->UnlockBox();
    }
};

#endif // _D3D8PORTI_H_beae18ac_6c75_45b0_99dc_3801f74cd017_

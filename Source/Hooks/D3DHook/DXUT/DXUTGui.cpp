//--------------------------------------------------------------------------------------
// File: DXUTgui.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "DXUTgui.h"
#include "DXUTsettingsDlg.h"

#undef min // use __min instead
#undef max // use __max instead

#ifndef WM_XBUTTONDOWN
#define WM_XBUTTONDOWN 0x020B // (not always defined)
#endif
#ifndef WM_XBUTTONUP
#define WM_XBUTTONUP 0x020C // (not always defined)
#endif
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A // (not always defined)
#endif
#ifndef WHEEL_DELTA
#define WHEEL_DELTA 120 // (not always defined)
#endif

// Minimum scroll bar thumb size
#define SCROLLBAR_MINTHUMBSIZE 8

// Delay and repeat period when clicking on the scroll bar arrows
#define SCROLLBAR_ARROWCLICK_DELAY  0.33
#define SCROLLBAR_ARROWCLICK_REPEAT 0.05

#define DXUT_NEAR_BUTTON_DEPTH 0.6f
#define DXUT_FAR_BUTTON_DEPTH 0.8f

#define DXUT_MAX_GUI_SPRITES 500

D3DCOLORVALUE D3DCOLOR_TO_D3DCOLORVALUE( D3DCOLOR c )
{
    D3DCOLORVALUE cv = { ( ( c >> 16 ) & 0xFF ) / 255.0f,
            ( ( c >> 8 ) & 0xFF ) / 255.0f,
            ( c & 0xFF ) / 255.0f,
            ( ( c >> 24 ) & 0xFF ) / 255.0f };
    return cv;
}

#define UNISCRIBE_DLLNAME L"usp10.dll"

#define GETPROCADDRESS( Module, APIName, Temp ) \
    Temp = GetProcAddress( Module, #APIName ); \
    if( Temp ) \
        *(FARPROC*)&_##APIName = Temp

#define PLACEHOLDERPROC( APIName ) \
    _##APIName = Dummy_##APIName

#define IMM32_DLLNAME L"imm32.dll"
#define VER_DLLNAME L"version.dll"

CHAR g_strUIEffectFile[] = \
    "Texture2D g_Texture;"\
    ""\
    "SamplerState Sampler"\
    "{"\
    "    Filter = MIN_MAG_MIP_LINEAR;"\
    "    AddressU = Wrap;"\
    "    AddressV = Wrap;"\
    "};"\
    ""\
    "BlendState UIBlend"\
    "{"\
    "    AlphaToCoverageEnable = FALSE;"\
    "    BlendEnable[0] = TRUE;"\
    "    SrcBlend = SRC_ALPHA;"\
    "    DestBlend = INV_SRC_ALPHA;"\
    "    BlendOp = ADD;"\
    "    SrcBlendAlpha = ONE;"\
    "    DestBlendAlpha = ZERO;"\
    "    BlendOpAlpha = ADD;"\
    "    RenderTargetWriteMask[0] = 0x0F;"\
    "};"\
    ""\
    "BlendState NoBlending"\
    "{"\
    "    BlendEnable[0] = FALSE;"\
    "    RenderTargetWriteMask[0] = 0x0F;"\
    "};"\
    ""\
    "DepthStencilState DisableDepth"\
    "{"\
    "    DepthEnable = false;"\
    "};"\
    "DepthStencilState EnableDepth"\
    "{"\
    "    DepthEnable = true;"\
    "};"\
    "struct VS_OUTPUT"\
    "{"\
    "    float4 Pos : SV_POSITION;"\
    "    float4 Dif : COLOR;"\
    "    float2 Tex : TEXCOORD;"\
    "};"\
    ""\
    "VS_OUTPUT VS( float3 vPos : POSITION,"\
    "              float4 Dif : COLOR,"\
    "              float2 vTexCoord0 : TEXCOORD )"\
    "{"\
    "    VS_OUTPUT Output;"\
    ""\
    "    Output.Pos = float4( vPos, 1.0f );"\
    "    Output.Dif = Dif;"\
    "    Output.Tex = vTexCoord0;"\
    ""\
    "    return Output;"\
    "}"\
    ""\
    "float4 PS( VS_OUTPUT In ) : SV_Target"\
    "{"\
    "    return g_Texture.Sample( Sampler, In.Tex ) * In.Dif;"\
    "}"\
    ""\
    "float4 PSUntex( VS_OUTPUT In ) : SV_Target"\
    "{"\
    "    return In.Dif;"\
    "}"\
    ""\
    "technique10 RenderUI"\
    "{"\
    "    pass P0"\
    "    {"\
    "        SetVertexShader( CompileShader( vs_4_0, VS() ) );"\
    "        SetGeometryShader( NULL );"\
    "        SetPixelShader( CompileShader( ps_4_0, PS() ) );"\
    "        SetDepthStencilState( DisableDepth, 0 );"\
    "        SetBlendState( UIBlend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );"\
    "    }"\
    "}"\
    "technique10 RenderUIUntex"\
    "{"\
    "    pass P0"\
    "    {"\
    "        SetVertexShader( CompileShader( vs_4_0, VS() ) );"\
    "        SetGeometryShader( NULL );"\
    "        SetPixelShader( CompileShader( ps_4_0, PSUntex() ) );"\
    "        SetDepthStencilState( DisableDepth, 0 );"\
    "        SetBlendState( UIBlend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );"\
    "    }"\
    "}"\
    "technique10 RestoreState"\
    "{"\
    "    pass P0"\
    "    {"\
    "        SetDepthStencilState( EnableDepth, 0 );"\
    "        SetBlendState( NoBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );"\
    "    }"\
    "}";
const UINT              g_uUIEffectFileSize = sizeof( g_strUIEffectFile );


// DXUT_MAX_EDITBOXLENGTH is the maximum string length allowed in edit boxes,
// including the NULL terminator.
//
// Uniscribe does not support strings having bigger-than-16-bits length.
// This means that the string must be less than 65536 characters long,
// including the NULL terminator.
#define DXUT_MAX_EDITBOXLENGTH 0xFFFF


//double                  CDXUTDialog::s_fTimeRefresh = 0.0f;
//CDXUTControl*           CDXUTDialog::s_pControlFocus = NULL;        // The control which has focus
//CDXUTControl*           CDXUTDialog::s_pControlPressed = NULL;      // The control currently pressed


struct DXUT_SCREEN_VERTEX
{
    FLOAT x, y, z, h;
    D3DCOLOR color;
    FLOAT tu, tv;

    static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
};

struct DXUT_SCREEN_VERTEX_UNTEX
{
    FLOAT x, y, z, h;
    D3DCOLOR color;

    static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};


struct DXUT_SCREEN_VERTEX_10
{
    FLOAT x, y, z;
    D3DCOLORVALUE color;
    FLOAT tu, tv;
};


//--------------------------------------------------------------------------------------
// CDXUTDialog class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
CDXUTDialog::CDXUTDialog(CDXUTDialog *Parent /* = NULL */)
{
    m_x         = 0;
    m_y         = 0;
    m_width     = 0;
    m_height    = 0;

    m_pManager          = NULL;
    m_bVisible          = TRUE;
    m_bCaption          = FALSE;
    m_bMinimized        = FALSE;
    m_LButtonPressed    = FALSE;
    m_Drag              = FALSE;

    RtlInitEmptyUnicodeString(&m_CaptionText, NULL, 0);

    m_CaptionRect.left      = 0;
    m_CaptionRect.top       = 0;
    m_CaptionRect.right     = DXUT_SIZE_ADJUST;
    m_CaptionRect.bottom    = 18;

    m_colorTopLeft      = 0;
    m_colorTopRight     = 0;
    m_colorBottomLeft   = 0;
    m_colorBottomRight  = 0;

    m_pCallbackEvent            = NULL;
    m_pCallbackEventUserContext = NULL;

    m_fTimeLastRefresh = 0;

    m_pControlMouseOver = NULL;

    m_pNextDialog = this;
    m_pPrevDialog = this;

    m_nDefaultControlID = 0xFFFF;
    m_bNonUserEvents    = FALSE;
    m_bKeyboardInput    = FALSE;
    m_bMouseInput       = TRUE;

    m_FrameFlags.Flags  = 0;

    s_fTimeRefresh      = 0.;
    s_pControlFocus     = NULL;
    s_pControlPressed   = NULL;

    m_ParentDialog = Parent;
}


//--------------------------------------------------------------------------------------
CDXUTDialog::~CDXUTDialog()
{
    ULONG i = 0;

    RemoveAllControls();

    m_Fonts.RemoveAll();
    m_Textures.RemoveAll();

    for( i = 0; i < m_DefaultElements.GetSize(); i++ )
    {
        DXUTElementHolder* pElementHolder = m_DefaultElements.GetAt( i );
        SAFE_DELETE( pElementHolder );
    }

    m_DefaultElements.RemoveAll();
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::Init( CDXUTDialogResourceManager* pManager, BOOL bRegisterDialog )
{
    m_pManager = pManager;
    if( bRegisterDialog )
        pManager->RegisterDialog( this );

    SetTexture(0, MAKEINTRESOURCE(DXUT_DEFAULT_RESOURCE), (HMODULE)DXUT_DEFAULT_RESOURCE);
    InitDefaultElements();
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::Init( CDXUTDialogResourceManager* pManager, BOOL bRegisterDialog, LPCWSTR pszControlTextureFilename )
{
    m_pManager = pManager;
    if( bRegisterDialog )
        pManager->RegisterDialog( this );
    SetTexture( 0, pszControlTextureFilename );
    InitDefaultElements();
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::Init( CDXUTDialogResourceManager* pManager, BOOL bRegisterDialog,
                        LPCWSTR szControlTextureResourceName, HMODULE hControlTextureResourceModule )
{
    m_pManager = pManager;
    if( bRegisterDialog )
        pManager->RegisterDialog( this );

    SetTexture( 0, szControlTextureResourceName, hControlTextureResourceModule );
    InitDefaultElements();
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::SetCallback( PVOID pCallback, void* pUserContext )
{
    // If this assert triggers, you need to call CDXUTDialog::Init() first.  This change
    // was made so that the DXUT's GUI could become seperate and optional from DXUT's core.  The
    // creation and interfacing with CDXUTDialogResourceManager is now the responsibility
    // of the application if it wishes to use DXUT's GUI.
    assert( m_pManager != NULL && L"To fix call CDXUTDialog::Init() first.  See comments for details." );

    m_pCallbackEvent = (PCALLBACKDXUTGUIEVENT)pCallback;
    m_pCallbackEventUserContext = pUserContext;
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::RemoveControl( int ID )
{
    for( ULONG i = 0; i < m_Controls.GetSize(); i++ )
    {
        CDXUTControl* pControl = m_Controls.GetAt( i );
        if( pControl->GetID() == ID )
        {
            // Clean focus first
            ClearFocus();

            // Clear references to this control
            if( s_pControlFocus == pControl )
                s_pControlFocus = NULL;
            if( s_pControlPressed == pControl )
                s_pControlPressed = NULL;
            if( m_pControlMouseOver == pControl )
                m_pControlMouseOver = NULL;

            delete pControl;
            m_Controls.Remove( i );

            return;
        }
    }
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::RemoveAllControls()
{
    if( s_pControlFocus && s_pControlFocus->m_pDialog == this )
        s_pControlFocus = NULL;
    if( s_pControlPressed && s_pControlPressed->m_pDialog == this )
        s_pControlPressed = NULL;
    m_pControlMouseOver = NULL;

    for( ULONG i = 0; i < m_Controls.GetSize(); i++ )
    {
        CDXUTControl* pControl = m_Controls.GetAt( i );
        SAFE_DELETE( pControl );
    }

    m_Controls.RemoveAll();
}


//--------------------------------------------------------------------------------------
CDXUTDialogResourceManager::CDXUTDialogResourceManager()
{
    WCHAR DefTexturePath[MAX_NTPATH];

    RtlInitEmptyUnicodeString(&m_TexturePath, NULL, 0);

    GetDefTextureFullPath(DefTexturePath, countof(DefTexturePath));
    SetTexturePath(DefTexturePath);

    // Begin D3D9-specific
    m_pd3d9Device = NULL;
    m_pStateBlock = NULL;
    m_pSprite = NULL;
    // End D3D9-specific

    // Begin D3D10-specific
    m_pd3d10Device = NULL;
    m_pEffect10 = NULL;
    m_pTechRenderUI10 = NULL;
    m_pTechRenderUIUntex10 = NULL;
    m_pFxTexture10 = NULL;
    m_pInputLayout10 = NULL;
    m_pVBScreenQuad10 = NULL;
    m_pStateBlock10 = NULL;
    m_pSprite10 = NULL;
    m_nBackBufferWidth = m_nBackBufferHeight = 0;

    // End D3D10-specific
}


//--------------------------------------------------------------------------------------
CDXUTDialogResourceManager::~CDXUTDialogResourceManager()
{
    ULONG i;
    for( i = 0; i < m_FontCache.GetSize(); i++ )
    {
        DXUTFontNode* pFontNode = m_FontCache.GetAt( i );
        SAFE_DELETE( pFontNode );
    }
    m_FontCache.RemoveAll();

    for( i = 0; i < m_TextureCache.GetSize(); i++ )
    {
        DXUTTextureNode* pTextureNode = m_TextureCache.GetAt( i );
        SAFE_DELETE( pTextureNode );
    }
    m_TextureCache.RemoveAll();

    CUniBuffer::Uninitialize();

    RtlFreeUnicodeString(&m_TexturePath);
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialogResourceManager::OnD3D9CreateDevice( LPDIRECT3DDEVICE9 pd3dDevice )
{
    HRESULT hr = S_OK;
    ULONG i = 0;

    m_pd3d9Device = pd3dDevice;

    for( i = 0; i < m_FontCache.GetSize(); i++ )
    {
        hr = CreateFont9( i );
        if( FAILED( hr ) )
            return hr;
    }

    for( i = 0; i < m_TextureCache.GetSize(); i++ )
    {
        hr = CreateTexture9( i );
        if( FAILED( hr ) )
            return hr;
    }

    hr = D3DXCreateSprite( pd3dDevice, &m_pSprite );
    if( FAILED( hr ) )
        return DXUT_ERR( L"D3DXCreateSprite", hr );

    V_RETURN(m_pd3d9Device->CreateStateBlock(D3DSBT_ALL, &m_pStateBlock));

    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialogResourceManager::OnD3D9ResetDevice()
{
    HRESULT hr = S_OK;

    for( ULONG i = 0; i < m_FontCache.GetSize(); i++ )
    {
        DXUTFontNode* pFontNode = m_FontCache.GetAt( i );

        if( pFontNode->Font9 )
            pFontNode->Font9->OnResetDevice();
    }

    if( m_pSprite )
        m_pSprite->OnResetDevice();

    V_RETURN( m_pd3d9Device->CreateStateBlock( D3DSBT_ALL, &m_pStateBlock ) );

    return S_OK;
}

//--------------------------------------------------------------------------------------
BOOL CDXUTDialogResourceManager::MsgProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
{
    return FALSE;
}


//--------------------------------------------------------------------------------------
void CDXUTDialogResourceManager::OnD3D9LostDevice()
{
    for( ULONG i = 0; i < m_FontCache.GetSize(); i++ )
    {
        DXUTFontNode* pFontNode = m_FontCache.GetAt( i );

        if( pFontNode->Font9 )
            pFontNode->Font9->OnLostDevice();
    }

    if( m_pSprite )
        m_pSprite->OnLostDevice();

    SAFE_RELEASE( m_pStateBlock );
}


//--------------------------------------------------------------------------------------
void CDXUTDialogResourceManager::OnD3D9DestroyDevice()
{
    ULONG i = 0;

    m_pd3d9Device = NULL;

    // Release the resources but don't clear the cache, as these will need to be
    // recreated if the device is recreated
    for( i = 0; i < m_FontCache.GetSize(); i++ )
    {
        DXUTFontNode* pFontNode = m_FontCache.GetAt( i );
        SAFE_RELEASE( pFontNode->Font9 );
    }

    for( i = 0; i < m_TextureCache.GetSize(); i++ )
    {
        DXUTTextureNode* pTextureNode = m_TextureCache.GetAt( i );
        SAFE_RELEASE( pTextureNode->Texture9 );
    }

    SAFE_RELEASE( m_pSprite );
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialogResourceManager::OnD3D10CreateDevice( ID3D10Device* pd3dDevice )
{
    m_pd3d10Device = pd3dDevice;

    HRESULT hr = S_OK;

    // Create the UI effect object
    V_RETURN( D3DX10CreateEffectFromMemory( g_strUIEffectFile, g_uUIEffectFileSize, NULL, NULL,
                                            NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
                                            pd3dDevice, NULL, NULL, &m_pEffect10, NULL, NULL ) );

    m_pTechRenderUI10 = m_pEffect10->GetTechniqueByName( "RenderUI" );
    m_pTechRenderUIUntex10 = m_pEffect10->GetTechniqueByName( "RenderUIUntex" );
    m_pFxTexture10 = m_pEffect10->GetVariableByName( "g_Texture" )->AsShaderResource();

    // Create the font and texture objects in the cache arrays.
    ULONG i = 0;
    for( i = 0; i < m_FontCache.GetSize(); i++ )
    {
        hr = CreateFont10( i );
        if( FAILED( hr ) )
            return hr;
    }

    for( i = 0; i < m_TextureCache.GetSize(); i++ )
    {
        hr = CreateTexture10( i );
        if( FAILED( hr ) )
            return hr;
    }

    // Create input layout
    const D3D10_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,       0, 28, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        };

    D3D10_PASS_DESC PassDesc;
    V_RETURN( m_pTechRenderUI10->GetPassByIndex( 0 )->GetDesc( &PassDesc ) );
    V_RETURN( pd3dDevice->CreateInputLayout( layout, 3, PassDesc.pIAInputSignature,
                                             PassDesc.IAInputSignatureSize, &m_pInputLayout10 ) );
    DXUT_SetDebugName( m_pInputLayout10, "CDXUTDialogResourceManager" );

    // Create a vertex buffer quad for rendering later
    D3D10_BUFFER_DESC BufDesc;
    BufDesc.ByteWidth = sizeof( DXUT_SCREEN_VERTEX_10 ) * 4;
    BufDesc.Usage = D3D10_USAGE_DYNAMIC;
    BufDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    BufDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
    BufDesc.MiscFlags = 0;
    V_RETURN( pd3dDevice->CreateBuffer( &BufDesc, NULL, &m_pVBScreenQuad10 ) );
    DXUT_SetDebugName( m_pVBScreenQuad10, "CDXUTDialogResourceManager" );

    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialogResourceManager::OnD3D10ResizedSwapChain( ID3D10Device* pd3dDevice,
                                                             const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc )
{
    HRESULT hr = S_OK;

    m_nBackBufferWidth = pBackBufferSurfaceDesc->Width;
    m_nBackBufferHeight = pBackBufferSurfaceDesc->Height;

    hr = D3DX10CreateSprite( pd3dDevice, DXUT_MAX_GUI_SPRITES, &m_pSprite10 );
    if( FAILED( hr ) )
        return DXUT_ERR( L"D3DX10CreateSprite", hr );

    D3D10_STATE_BLOCK_MASK StateBlockMask;
    DXUT_Dynamic_D3D10StateBlockMaskEnableAll( &StateBlockMask );
    DXUT_Dynamic_D3D10StateBlockMaskDisableCapture( &StateBlockMask, D3D10_DST_OM_RENDER_TARGETS, 0, 1 );
    V_RETURN( DXUT_Dynamic_D3D10CreateStateBlock( pd3dDevice, &StateBlockMask, &m_pStateBlock10 ) );

    return hr;
}


//--------------------------------------------------------------------------------------
void CDXUTDialogResourceManager::OnD3D10ReleasingSwapChain()
{
    SAFE_RELEASE( m_pSprite10 );
    SAFE_RELEASE( m_pStateBlock10 );
}


//--------------------------------------------------------------------------------------
void CDXUTDialogResourceManager::OnD3D10DestroyDevice()
{
    ULONG i;

    m_pd3d10Device = NULL;

    // Release the resources but don't clear the cache, as these will need to be
    // recreated if the device is recreated
    for( i = 0; i < m_FontCache.GetSize(); i++ )
    {
        DXUTFontNode* pFontNode = m_FontCache.GetAt( i );
        SAFE_RELEASE( pFontNode->Font10 );
    }

    for( i = 0; i < m_TextureCache.GetSize(); i++ )
    {
        DXUTTextureNode* pTextureNode = m_TextureCache.GetAt( i );
        SAFE_RELEASE( pTextureNode->TexResView );
        SAFE_RELEASE( pTextureNode->Texture10 );
    }

    SAFE_RELEASE( m_pVBScreenQuad10 );
    SAFE_RELEASE( m_pStateBlock10 );
    SAFE_RELEASE( m_pSprite10 );
    SAFE_RELEASE( m_pInputLayout10 );
    SAFE_RELEASE( m_pEffect10 );
}


//--------------------------------------------------------------------------------------
BOOL CDXUTDialogResourceManager::RegisterDialog( CDXUTDialog* pDialog )
{
    // Check that the dialog isn't already registered.
    for( ULONG i = 0; i < m_Dialogs.GetSize(); ++i )
        if( m_Dialogs.GetAt( i ) == pDialog )
            return TRUE;

    // Add to the list.
    if( FAILED( m_Dialogs.Add( pDialog ) ) )
        return FALSE;

    // Set up next and prev pointers.
    if( m_Dialogs.GetSize() > 1 )
        m_Dialogs[m_Dialogs.GetSize() - 2]->SetNextDialog( pDialog );
    m_Dialogs[m_Dialogs.GetSize() - 1]->SetNextDialog( m_Dialogs[0] );

    return TRUE;
}


//--------------------------------------------------------------------------------------
void CDXUTDialogResourceManager::UnregisterDialog( CDXUTDialog* pDialog )
{
    // Search for the dialog in the list.
    for( ULONG i = 0; i < m_Dialogs.GetSize(); ++i )
        if( m_Dialogs.GetAt( i ) == pDialog )
        {
            m_Dialogs.Remove( i );
            if( m_Dialogs.GetSize() > 0 )
            {
                ULONG l, r;

                if( 0 == i )
                    l = m_Dialogs.GetSize() - 1;
                else
                    l = i - 1;

                if( m_Dialogs.GetSize() == i )
                    r = 0;
                else
                    r = i;

                m_Dialogs[l]->SetNextDialog( m_Dialogs[r] );
            }
            return;
        }
}


//--------------------------------------------------------------------------------------
void CDXUTDialogResourceManager::EnableKeyboardInputForAllDialogs()
{
    CDXUTDialog *Dialog, **Dialogs;

    Dialogs = m_Dialogs.GetData();
    for (ULONG Count = m_Dialogs.GetSize(); Count != 0; ++Dialogs, --Count)
    {
    	Dialog = *Dialogs;
        Dialog->EnableKeyboardInput(TRUE);
    }
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::Refresh()
{
    if( s_pControlFocus )
        s_pControlFocus->OnFocusOut();

    if( m_pControlMouseOver )
        m_pControlMouseOver->OnMouseLeave();

    s_pControlFocus = NULL;
    s_pControlPressed = NULL;
    m_pControlMouseOver = NULL;

    for( ULONG i = 0; i < m_Controls.GetSize(); i++ )
    {
        CDXUTControl* pControl = m_Controls.GetAt( i );
        pControl->Refresh();
    }

    if( m_bKeyboardInput )
        FocusDefaultControl();
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::OnRender(FLOAT ElapsedTime)
{
    RECT    ScreenRect;
    HRESULT Result;

    Result = m_pManager->GetD3D9Device() != NULL ? OnRender9(ElapsedTime) : OnRender10(ElapsedTime);

    return Result;
}

//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::OnRender9(FLOAT ElapsedTime)
{
    // If this assert triggers, you need to call CDXUTDialogResourceManager::On*Device() from inside
    // the application's device callbacks.  See the SDK samples for an example of how to do this.
    assert( m_pManager->GetD3D9Device() && m_pManager->m_pStateBlock &&
            L"To fix hook up CDXUTDialogResourceManager to device callbacks.  See comments for details" );

    // See if the dialog needs to be refreshed
    if( m_fTimeLastRefresh < s_fTimeRefresh )
    {
        m_fTimeLastRefresh = DXUTGetTime();
        Refresh();
    }

    // For invisible dialog, out now.
    if (!m_bVisible || (m_bMinimized && !m_bCaption))
        return S_OK;

    if (GetWidth() == 0 || GetHeight() == 0)
        return S_OK;

    IDirect3DDevice9* pd3dDevice = m_pManager->GetD3D9Device();

    // Set up a state block here and restore it when finished drawing all the controls
    if (GetParent() == NULL)
        m_pManager->m_pStateBlock->Capture();

    if (GetParent() == NULL)
    {
        pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
        pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
        pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
        pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
        pd3dDevice->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, FALSE );
        pd3dDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
        pd3dDevice->SetRenderState( D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_RED );
        pd3dDevice->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
        pd3dDevice->SetRenderState( D3DRS_FOGENABLE, FALSE );
        pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
        pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
        pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
    }

    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_RESULTARG, D3DTA_CURRENT );
    pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
    pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

    BOOL bBackgroundIsVisible;

    bBackgroundIsVisible = (m_colorTopLeft | m_colorTopRight | m_colorBottomRight | m_colorBottomLeft) & 0xff000000;

    if( !m_bMinimized && bBackgroundIsVisible )
    {
        RECT                rc;
        INT                 x, y, Width, Height;
        PDXUT_ELEMENT_INFO  Element;

        GetRectAbsolute(rc);
        AdjustChildRect(&rc);

        x       = rc.left;
        y       = rc.top + (m_bCaption ? GetCaptionHeightAboveFrame() : 0);
        Width   = m_width;
        Height  = m_height;

        DXUT_SCREEN_VERTEX_UNTEX vertices[4] =
        {
            (FLOAT)x,         (FLOAT)y,          0.5f, 1.0f, m_colorTopLeft,
            (FLOAT)x + Width, (FLOAT)y,          0.5f, 1.0f, m_colorTopRight,
            (FLOAT)x + Width, (FLOAT)y + Height, 0.5f, 1.0f, m_colorBottomRight,
            (FLOAT)x,         (FLOAT)y + Height, 0.5f, 1.0f, m_colorBottomLeft,
        };

        pd3dDevice->SetVertexShader(NULL);
        pd3dDevice->SetPixelShader(NULL);
        pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        pd3dDevice->SetFVF(DXUT_SCREEN_VERTEX_UNTEX::FVF);
        pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(vertices[0]));
    }

    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

    if (GetParent() == NULL)
        pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

    DXUTTextureNode* pTextureNode = GetTexture( 0 );
    pd3dDevice->SetTexture( 0, pTextureNode->Texture9 );

    if (GetParent() == NULL)
        m_pManager->m_pSprite->Begin( D3DXSPRITE_DONOTSAVESTATE );

    DrawDialogFrame9();

    // Render the caption if it's enabled.
    DrawCaption9();

    // If the dialog is minimized, skip rendering
    // its controls.
    if( !m_bMinimized )
    {
        CDXUTControl **Controls = m_Controls.GetData();

        for (ULONG Count = m_Controls.GetSize(); Count != 0; --Count)
        {
        	CDXUTControl* pControl = *Controls++;

            // Focused control is drawn last
            if( pControl == s_pControlFocus )
                continue;

            pControl->Render(ElapsedTime);
        }

        if( s_pControlFocus != NULL && s_pControlFocus->m_pDialog == this )
            s_pControlFocus->Render(ElapsedTime);
    }

    if (GetParent() == NULL)
    {
        m_pManager->m_pSprite->End();
        m_pManager->m_pStateBlock->Apply();
    }

    return S_OK;
}

HRESULT CDXUTDialog::DrawDialogFrame9()
{
    HRESULT             Result;
    PDXUT_ELEMENT_INFO  Element;
    DXUTTextureNode    *Node;
    PRECT               Rect;
    LONG                DlgWidth, DlgHeight;
    BOOL                TopCaptionOverlapped;
    SIZE                ElemSize;

    PDXUT_ELEMENT_INFO Left, Top, Right, Bottom;
    PDXUT_ELEMENT_INFO LeftTop, RightTop, RightBottom, LeftBottom;

    DlgWidth    = GetWidth();
    DlgHeight   = GetHeight();

    auto ElementSize =
    [] (PDXUT_ELEMENT_INFO e) -> SIZE
    {
        SIZE size;

        if (!IsElementValid(e->Element))
        {
            size.cx = 0;
            size.cy = 0;
        }
        else
        {
            size.cx = RectWidth(e->Position);
            size.cy = RectHeight(e->Position);
        }

        return size;
    };

    Left        = &m_FrameElement[DXUT_DIALOG_FRAME_LEFT];
    Top         = &m_FrameElement[DXUT_DIALOG_FRAME_TOP];
    Right       = &m_FrameElement[DXUT_DIALOG_FRAME_RIGHT];
    Bottom      = &m_FrameElement[DXUT_DIALOG_FRAME_BOTTOM];
    LeftTop     = &m_FrameElement[DXUT_DIALOG_FRAME_LEFT_TOP];
    RightTop    = &m_FrameElement[DXUT_DIALOG_FRAME_RIGHT_TOP];
    RightBottom = &m_FrameElement[DXUT_DIALOG_FRAME_RIGHT_BOTTOM];
    LeftBottom  = &m_FrameElement[DXUT_DIALOG_FRAME_LEFT_BOTTOM];

    RECT FramePos[] =
    {
        // left
        {
            -ElementSize(Left).cx,
            0,
            0,
            DlgHeight - ElementSize(RightBottom).cy + ElementSize(Bottom).cy,
        },

        // top
        {
            -ElementSize(Left).cx + ElementSize(LeftTop).cx,
            -ElementSize(Top).cy,
            DlgWidth - ElementSize(RightTop).cx + ElementSize(Right).cx,
            0,
        },

        // right
        {
            DlgWidth,
            0,
            DlgWidth + ElementSize(Right).cx,
            DlgHeight - ElementSize(RightBottom).cy + ElementSize(Bottom).cy,
        },

        // bottom
        {
            -ElementSize(Left).cx + ElementSize(RightBottom).cx,
            DlgHeight,
            DlgWidth - ElementSize(RightBottom).cx + ElementSize(Right).cx,
            DlgHeight + ElementSize(Bottom).cy,
        },

        // left-top
        {
            -ElementSize(Left).cx,
            -ElementSize(Top).cy,
            -ElementSize(Left).cx + ElementSize(LeftTop).cx,
            -ElementSize(Top).cy + ElementSize(LeftTop).cy,
        },

        // right-top
        {
            DlgWidth + ElementSize(Right).cx - ElementSize(RightTop).cx,
            -ElementSize(Top).cy,
            DlgWidth + ElementSize(Right).cx,
            -ElementSize(Top).cy + ElementSize(RightTop).cy,
        },

        // right-bottom
        {
            DlgWidth + ElementSize(Right).cx - ElementSize(RightBottom).cx,
            DlgHeight + ElementSize(Bottom).cy - ElementSize(RightBottom).cy,
            DlgWidth + ElementSize(Right).cx,
            DlgHeight + ElementSize(Bottom).cy,
        },

        // left-bottom
        {
            -ElementSize(Left).cx,
            DlgHeight + ElementSize(Bottom).cy - ElementSize(LeftBottom).cy,
            -ElementSize(Left).cx + ElementSize(LeftBottom).cx,
            DlgHeight + ElementSize(Bottom).cy,
        },

        { 0 },
    };

    TopCaptionOverlapped = FALSE;

    LOOP_ONCE
    {
        PRECT TopLeft   = &FramePos[DXUT_DIALOG_FRAME_TOP];
        PRECT TopRight  = &FramePos[DXUT_DIALOG_FRAME_ELEMENT_TOP_RIGHT_PART];

        if (!m_FrameFlags.DontDrawCaption)
            break;

        if (!IsElementValid(m_FrameElement[DXUT_DIALOG_FRAME_TOP].Element))
            break;

        if (GetCaptionHeightAboveFrame() <= 0)
            break;

        if (m_CaptionRect.left <= TopLeft->left)
            break;

        if (m_CaptionRect.right >= TopLeft->right)
            break;

        *TopRight = *TopLeft;

        TopLeft->right = m_CaptionRect.left;
        TopRight->left = m_CaptionRect.right;

        TopCaptionOverlapped = TRUE;
    }

    Result  = S_OK;
    Rect    = FramePos;
    Element = m_FrameElement;
    for (ULONG Count = ARRAYSIZE(m_FrameElement); Count; ++Rect, ++Element, --Count)
    {
        if (!IsElementValid(Element->Element))
            continue;

        Result = DrawSprite9(&Element->Element, Rect);
        if (FAILED(Result))
            break;
    }

    if (TopCaptionOverlapped && !FAILED(Result))
    {
        Result = DrawSprite9(&m_FrameElement[DXUT_DIALOG_FRAME_TOP].Element, &FramePos[DXUT_DIALOG_FRAME_ELEMENT_TOP_RIGHT_PART]);
    }

    return Result;
}

HRESULT CDXUTDialog::DrawCaption9()
{
    HRESULT             Result;
    PDXUT_ELEMENT_INFO  Element;

    if (!m_bCaption)
        return S_OK;

    RECT rc;

    Result = S_OK;

    Element = &m_CaptionElement[DXUT_CAPTION_MIDDLE];
    if (IsElementValid(Element->Element))
    {
        rc = GetCaptionRect();

        rc.left  += RectWidth(m_CaptionElement[DXUT_CAPTION_LEFT].Position);
        rc.right -= RectWidth(m_CaptionElement[DXUT_CAPTION_RIGHT].Position);

        OffsetRect(&rc, 0, -GetCaptionHeightAboveFrame());

        Result = DrawSprite9(&Element->Element, &rc);
        if (FAILED(Result))
            return Result;
    }

    Element = &m_CaptionElement[DXUT_CAPTION_LEFT];
    if (IsElementValid(Element->Element))
    {
        rc          = GetCaptionRect();
        rc.right    = rc.left + RectWidth(Element->Position);

        OffsetRect(&rc, 0, -GetCaptionHeightAboveFrame());

        Result = DrawSprite9(&Element->Element, &rc);
        if (FAILED(Result))
            return Result;
    }

    Element = &m_CaptionElement[DXUT_CAPTION_RIGHT];
    if (IsElementValid(Element->Element))
    {
        rc          = GetCaptionRect();
        rc.left     = rc.right - RectWidth(Element->Position);

        OffsetRect(&rc, 0, -GetCaptionHeightAboveFrame());

        Result = DrawSprite9(&Element->Element, &rc);
    }

    return Result;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::OnRender10(FLOAT ElapsedTime/* = FALSE */)
{
    // If this assert triggers, you need to call CDXUTDialogResourceManager::On*Device() from inside
    // the application's device callbacks.  See the SDK samples for an example of how to do this.
    assert( m_pManager->GetD3D10Device() &&
            L"To fix hook up CDXUTDialogResourceManager to device callbacks.  See comments for details" );

    // See if the dialog needs to be refreshed
    if( m_fTimeLastRefresh < s_fTimeRefresh )
    {
        m_fTimeLastRefresh = DXUTGetTime();
        Refresh();
    }

    // For invisible dialog, out now.
    if( !m_bVisible ||
        ( m_bMinimized && !m_bCaption ) )
        return S_OK;

    ID3D10Device* pd3dDevice = m_pManager->GetD3D10Device();

    // Set up a state block here and restore it when finished drawing all the controls
    m_pManager->m_pStateBlock10->Capture();

    BOOL bBackgroundIsVisible = ( m_colorTopLeft | m_colorTopRight | m_colorBottomRight | m_colorBottomLeft ) & 0xFF000000;

    if( !m_bMinimized && bBackgroundIsVisible )
    {
        // Convert the draw rectangle from screen coordinates to clip space coordinates.
        FLOAT Left, Right, Top, Bottom;

        Left    = m_x * 2.0f / m_pManager->m_nBackBufferWidth - 1.0f;
        Right   = ( m_x + m_width ) * 2.0f / m_pManager->m_nBackBufferWidth - 1.0f;
        Top     = 1.0f - m_y * 2.0f / m_pManager->m_nBackBufferHeight;
        Bottom  = 1.0f - ( m_y + m_height ) * 2.0f / m_pManager->m_nBackBufferHeight;

        DXUT_SCREEN_VERTEX_10 vertices[4] =
        {
            Left,  Top,    0.5f, D3DCOLOR_TO_D3DCOLORVALUE( m_colorTopLeft ), 0.0f, 0.0f,
            Right, Top,    0.5f, D3DCOLOR_TO_D3DCOLORVALUE( m_colorTopRight ), 1.0f, 0.0f,
            Left,  Bottom, 0.5f, D3DCOLOR_TO_D3DCOLORVALUE( m_colorBottomLeft ), 0.0f, 1.0f,
            Right, Bottom, 0.5f, D3DCOLOR_TO_D3DCOLORVALUE( m_colorBottomRight ), 1.0f, 1.0f,
        };

        DXUT_SCREEN_VERTEX_10* pVB;
        if( SUCCEEDED( m_pManager->m_pVBScreenQuad10->Map( D3D10_MAP_WRITE_DISCARD, 0, ( LPVOID* )&pVB ) ) )
        {
            CopyMemory( pVB, vertices, sizeof( vertices ) );
            m_pManager->m_pVBScreenQuad10->Unmap();
        }

        // Set the quad VB as current
        UINT stride = sizeof( DXUT_SCREEN_VERTEX_10 );
        UINT offset = 0;
        pd3dDevice->IASetVertexBuffers( 0, 1, &m_pManager->m_pVBScreenQuad10, &stride, &offset );
        pd3dDevice->IASetInputLayout( m_pManager->m_pInputLayout10 );
        pd3dDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

        // Draw dialog background
        D3D10_TECHNIQUE_DESC techDesc;
        m_pManager->m_pTechRenderUIUntex10->GetDesc( &techDesc );
        for( UINT p = 0; p < techDesc.Passes; ++p )
        {
            m_pManager->m_pTechRenderUIUntex10->GetPassByIndex( p )->Apply( 0 );
            pd3dDevice->Draw( 4, 0 );
        }
    }

    DXUTTextureNode* pTextureNode = GetTexture( 0 );
    m_pManager->m_pFxTexture10->SetResource( pTextureNode->TexResView );

    // Sort depth back to front
    m_pManager->m_pSprite10->Begin( 0 );

    m_pManager->m_pTechRenderUI10->GetPassByIndex( 0 )->Apply( 0 );
/*
    // Render the caption if it's enabled.
    if( m_bCaption )
    {
        // DrawSprite will offset the rect down by
        // m_nCaptionHeight, so adjust the rect higher
        // here to negate the effect.
        RECT rc = { 0, -GetCaptionHeight(), m_width, 0 };
        DrawSprite10( &m_CapElement, &rc, 0.99f );
        rc.left += 5; // Make a left margin
        WCHAR wszOutput[256];
        wcscpy_s( wszOutput, 256, m_wszCaption );
        if( m_bMinimized )
            wcscat_s( wszOutput, 256, L" (Minimized)" );
        DrawText10( wszOutput, &m_CapElement, &rc, TRUE );
    }
*/
    // If the dialog is minimized, skip rendering
    // its controls.
    if( !m_bMinimized )
    {
        for( ULONG i = 0; i < m_Controls.GetSize(); i++ )
        {
            CDXUTControl* pControl = m_Controls.GetAt( i );

            // Focused control is drawn last
            if( pControl == s_pControlFocus )
                continue;

            pControl->Render( ElapsedTime );
        }

        if( s_pControlFocus != NULL && s_pControlFocus->m_pDialog == this )
            s_pControlFocus->Render( ElapsedTime );
    }

    m_pManager->m_pSprite10->End();

    m_pManager->m_pStateBlock10->Apply();
    // Restore depth stencil state
    m_pManager->m_pEffect10->GetTechniqueByName( "RestoreState" )->GetPassByIndex( 0 )->Apply( 0 );

    return S_OK;
}

//--------------------------------------------------------------------------------------
VOID CDXUTDialog::SendEvent(UINT nEvent, BOOL bTriggeredByUser, CDXUTControl* pControl, CDXUTDialog *ChildEvent /* = NULL */)
{
    // If no callback has been registered there's nowhere to send the event to
    if( m_pCallbackEvent == NULL )
    {
        if (m_ParentDialog != NULL)
            m_ParentDialog->SendEvent(nEvent, bTriggeredByUser, pControl, this);

        return;
    }

    // Discard events triggered programatically if these types of events haven't been
    // enabled
    if( !bTriggeredByUser && !m_bNonUserEvents )
        return;

    m_pCallbackEvent(nEvent, pControl->GetID(), pControl, m_pCallbackEventUserContext);
}


//--------------------------------------------------------------------------------------
int CDXUTDialogResourceManager::AddFont( LPCWSTR strFaceName, LONG height, LONG weight )
{
    ULONG           Hash;
    HRESULT         Result;
    DXUTFontNode**  FontNodes = m_FontCache.GetData();

    Hash = HashUnicodeUpper(strFaceName);

    // See if this font already exists
    for (ULONG Count = m_FontCache.GetSize(); Count != 0; ++FontNodes, --Count)
    {
        DXUTFontNode* FontNode = *FontNodes;

        if (
            FontNode->FaceNameHash == Hash &&
            !_wcsicmp(FontNode->FaceName, strFaceName) &&
            FontNode->Height == height &&
            FontNode->Weight == weight
           )
        {
            return FontNodes - m_FontCache.GetData();
        }
    }

    // Add a new font and try to create it
    DXUTFontNode* NewFontNode = new DXUTFontNode;
    if (NewFontNode == NULL)
        return DXUT_INVALID_FONT_ID;

    wcscpy_s(NewFontNode->FaceName, sizeof(NewFontNode->FaceName), strFaceName);

    NewFontNode->FaceNameHash   = Hash;
    NewFontNode->Height         = height;
    NewFontNode->Weight         = weight;
    NewFontNode->Font9          = NULL;
    NewFontNode->Font10         = NULL;

    m_FontCache.Add(NewFontNode);

    LONG FontIndex = m_FontCache.GetSize() - 1;

    // If a device is available, try to create immediately

    Result = S_OK;
    if (m_pd3d9Device)
    {
        Result = CreateFont9(FontIndex);
    }
    else if (m_pd3d10Device)
    {
        Result = CreateFont10(FontIndex);
    }

    if (FAILED(Result))
    {
        m_FontCache.Remove(FontIndex);
        FontIndex = DXUT_INVALID_FONT_ID;
        delete NewFontNode;
    }

    return FontIndex;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::SetFont( UINT index, LPCWSTR strFaceName, LONG height, LONG weight )
{
    // If this assert triggers, you need to call CDXUTDialog::Init() first.  This change
    // was made so that the DXUT's GUI could become seperate and optional from DXUT's core.  The
    // creation and interfacing with CDXUTDialogResourceManager is now the responsibility
    // of the application if it wishes to use DXUT's GUI.
    assert( m_pManager != NULL && L"To fix call CDXUTDialog::Init() first.  See comments for details." );

    // Make sure the list is at least as large as the index being set
    UINT i;
    for( i = m_Fonts.GetSize(); i <= index; i++ )
    {
        m_Fonts.Add( -1 );
    }

    int iFont = m_pManager->AddFont( strFaceName, height, weight );
    m_Fonts.SetAt( index, iFont );

    return S_OK;
}


//--------------------------------------------------------------------------------------
DXUTFontNode* CDXUTDialog::GetFont( UINT index )
{
    if (index >= m_Fonts.GetSize() || m_pManager == NULL)
        return NULL;

    return m_pManager->GetFontNode(m_Fonts.GetAt(index));
}


//--------------------------------------------------------------------------------------
int CDXUTDialogResourceManager::AddTexture(LPCWSTR Filename)
{
    ULONG Hash;
    DXUTTextureNode **TextureNodes, *Node;

    Hash = HashUnicodeUpper(Filename);
    TextureNodes = m_TextureCache.GetData();

    for (ULONG Count = m_TextureCache.GetSize(); Count != 0; ++TextureNodes, --Count)
    {
    	Node = *TextureNodes;
        if (!Node->FileSource)
            continue;

        if (Node->FileNameHash != Hash)
            continue;

        if (_wcsicmp(Node->Filename, Filename))
            continue;

        return TextureNodes - m_TextureCache.GetData();
    }

    // Add a new texture and try to create it
    DXUTTextureNode* NewTextureNode = new DXUTTextureNode;
    if (NewTextureNode == NULL)
        return DXUT_INVALID_TEXTURE_ID;

    ZeroMemory(NewTextureNode, sizeof(*NewTextureNode));

    NewTextureNode->FileSource = TRUE;
    NewTextureNode->FileNameHash = Hash;
    wcscpy_s(NewTextureNode->Filename, sizeof(NewTextureNode->Filename), Filename);

    m_TextureCache.Add(NewTextureNode);

    LONG TextureIndex = m_TextureCache.GetSize() - 1;

    // If a device is available, try to create immediately
    if (m_pd3d9Device)
    {
        HRESULT Result;

        Result = CreateTexture9(TextureIndex);
        if (FAILED(Result))
        {
            m_TextureCache.Remove(TextureIndex);
            TextureIndex = DXUT_INVALID_TEXTURE_ID;
            delete NewTextureNode;
        }
    }

    return TextureIndex;
}


//--------------------------------------------------------------------------------------
int CDXUTDialogResourceManager::AddTexture(LPCWSTR ResourceName, HMODULE ResourceModule)
{
    ULONG Hash;
    DXUTTextureNode **TextureNodes, *Node;

    TextureNodes = m_TextureCache.GetData();

    if (IS_INTRESOURCE(ResourceName))
    {
        for (ULONG Count = m_TextureCache.GetSize(); Count != 0; ++TextureNodes, --Count)
        {
            Node = *TextureNodes;

            if (Node->FileSource || Node->ResourceModule != ResourceModule)
                continue;

            if ((ULONG_PTR)ResourceName != Node->ResourceID)
                continue;

            return TextureNodes - m_TextureCache.GetData();
        }
    }
    else
    {
        Hash = HashUnicodeUpper(ResourceName);
        for (ULONG Count = m_TextureCache.GetSize(); Count != 0; ++TextureNodes, --Count)
        {
            Node = *TextureNodes;

            if (Node->FileSource || Node->ResourceModule != ResourceModule)
                continue;

            if (Node->FileNameHash != Hash)
                continue;

            if (_wcsicmp(Node->Filename, ResourceName))
                continue;

            return TextureNodes - m_TextureCache.GetData();
        }
    }

    // Add a new texture and try to create it
    DXUTTextureNode* NewTextureNode = new DXUTTextureNode;
    if( NewTextureNode == NULL )
        return DXUT_INVALID_TEXTURE_ID;

    ZeroMemory(NewTextureNode, sizeof(*NewTextureNode));
    NewTextureNode->ResourceModule = ResourceModule;
    if (IS_INTRESOURCE(ResourceName))
    {
        NewTextureNode->ResourceID = (ULONG_PTR)ResourceName;
    }
    else
    {
        NewTextureNode->ResourceID = 0;
        NewTextureNode->FileNameHash = Hash;
        wcscpy_s(NewTextureNode->Filename, MAX_PATH, ResourceName);
    }

    m_TextureCache.Add(NewTextureNode);

    LONG TextureIndex;

    TextureIndex = m_TextureCache.GetSize() - 1;

    // If a device is available, try to create immediately
    if (m_pd3d9Device)
    {
        HRESULT Result = CreateTexture9(TextureIndex);
        if (FAILED(Result))
        {
            m_TextureCache.Remove(TextureIndex);
            TextureIndex = DXUT_INVALID_TEXTURE_ID;
            delete NewTextureNode;
        }
    }

    return TextureIndex;
}

ULONG CDXUTDialog::AddTexture(PWSTR FileName)
{
    ULONG Index, Texture, *TextureIndex;

    Texture = m_pManager->AddTexture(FileName);

    if (Texture == DXUT_INVALID_TEXTURE_ID)
        return DXUT_INVALID_TEXTURE_ID;

    TextureIndex = (PULONG)m_Textures.GetData();
    for (ULONG Count = m_Textures.GetSize(); Count; ++TextureIndex, --Count)
    {
        if (*TextureIndex == Texture)
        {
            return TextureIndex - (PULONG)m_Textures.GetData();
        }
    }

    Index = m_Textures.GetSize();
    m_Textures.Add(Texture);

    return Index;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::SetTexture( UINT index, LPCWSTR strFilename )
{
    // If this assert triggers, you need to call CDXUTDialog::Init() first.  This change
    // was made so that the DXUT's GUI could become seperate and optional from DXUT's core.  The
    // creation and interfacing with CDXUTDialogResourceManager is now the responsibility
    // of the application if it wishes to use DXUT's GUI.
    assert( m_pManager != NULL && L"To fix this, call CDXUTDialog::Init() first.  See comments for details." );

    // Make sure the list is at least as large as the index being set
    for( UINT i = m_Textures.GetSize(); i <= index; i++ )
    {
        m_Textures.Add( -1 );
    }

    int iTexture = m_pManager->AddTexture( strFilename );

    m_Textures.SetAt( index, iTexture );
    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::SetTexture( UINT index, LPCWSTR strResourceName, HMODULE hResourceModule )
{
    // If this assert triggers, you need to call CDXUTDialog::Init() first.  This change
    // was made so that the DXUT's GUI could become seperate and optional from DXUT's core.  The
    // creation and interfacing with CDXUTDialogResourceManager is now the responsibility
    // of the application if it wishes to use DXUT's GUI.
    assert( m_pManager != NULL && L"To fix this, call CDXUTDialog::Init() first.  See comments for details." );

    // Make sure the list is at least as large as the index being set
    for( UINT i = m_Textures.GetSize(); i <= index; i++ )
    {
        m_Textures.Add( -1 );
    }

    int iTexture = m_pManager->AddTexture( strResourceName, hResourceModule );

    m_Textures.SetAt( index, iTexture );
    return S_OK;
}


//--------------------------------------------------------------------------------------
DXUTTextureNode* CDXUTDialog::GetTexture( UINT index )
{
    if (index >= m_Textures.GetSize() || m_pManager == NULL)
        return NULL;

    return m_pManager->GetTextureNode(m_Textures.GetAt(index));
}



//--------------------------------------------------------------------------------------
BOOL CDXUTDialog::MsgProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
{
    BOOL bHandled;

    // For invisible dialog, do not handle anything.
    if( !m_bVisible )
        return FALSE;

    bHandled = FALSE;

    // If automation command-line switch is on, enable this dialog's keyboard input
    // upon any key press or mouse click.
    if(// DXUTGetAutomation() &&
        ( WM_LBUTTONDOWN == Message || WM_LBUTTONDBLCLK == Message || WM_KEYDOWN == Message ) )
    {
        m_pManager->EnableKeyboardInputForAllDialogs();
    }

    // If caption is enable, check for clicks in the caption area.
    if (m_bCaption)
    {
        HWND ParentWindow;
        RECT ParentRect;

        ParentWindow = DXUTGetHWND();

        if (ParentWindow != NULL)
        {
            POINT MousePoint = { LOWORD(lParam), HIWORD(lParam) };

            auto IsPointInCaption =
            [&] (POINT& pt) -> BOOL
            {
                RECT rc;

                rc = GetCaptionRect();
                OffsetRect(&rc, m_x, m_y);

                return pt.x >= rc.left &&
                       pt.x < rc.right &&
                       pt.y >= rc.top &&
                       pt.y < rc.bottom;
            };

            switch (Message)
            {
                case WM_LBUTTONDOWN:
//                case WM_LBUTTONDBLCLK:
                    if (!IsPointInCaption(MousePoint))
                        break;

                    NO_BREAK;

                case ~WM_NCLBUTTONDOWN:
                    m_LButtonPressed = TRUE;
                    LastMousePoint = MousePoint;
                    SetCapture(DXUTGetHWND());

                    return TRUE;

                case WM_LBUTTONUP:
                case ~WM_NCLBUTTONUP:
                    if (!m_LButtonPressed)
                        break;

                    ReleaseCapture();
                    m_LButtonPressed = FALSE;

                    if (m_Drag)
                        m_Drag = FALSE;
//                    else
//                        m_bMinimized = !m_bMinimized;

                    return TRUE;

                case WM_MOUSEMOVE:
                    if (!m_LButtonPressed)
                        break;

                    GetClientRect(ParentWindow, &ParentRect);

                    m_Drag = TRUE;

                    if (
                        MousePoint.x < 0                        ||
                        MousePoint.x > RectWidth(ParentRect)    ||
                        MousePoint.y < 0                        ||
                        MousePoint.y > RectHeight(ParentRect)
                       )
                    {
                        break;
                    }

                    m_x += MousePoint.x - LastMousePoint.x;
                    m_y += MousePoint.y - LastMousePoint.y;
                    LastMousePoint = MousePoint;
                    break;
            }
        }
    }

    // If the dialog is minimized, don't send any messages to controls.
    if( m_bMinimized )
        return FALSE;

    // If a control is in focus, it belongs to this dialog, and it's enabled, then give
    // it the first chance at handling the message.
    if( s_pControlFocus &&
        s_pControlFocus->m_pDialog == this &&
        s_pControlFocus->GetEnabled() )
    {
        // If the control MsgProc handles it, then we don't.
        if( s_pControlFocus->MsgProc(hWnd, Message, wParam, lParam ))
            return TRUE;
    }

    switch( Message )
    {
        case WM_SIZE:
        case WM_MOVE:
            {
                // Handle sizing and moving messages so that in case the mouse cursor is moved out
                // of an UI control because of the window adjustment, we can properly
                // unhighlight the highlighted control.
                POINT pt = { -1, -1 };
                OnMouseMove( pt );
                break;
            }

        case WM_ACTIVATEAPP:
            // Call OnFocusIn()/OnFocusOut() of the control that currently has the focus
            // as the application is activated/deactivated.  This matches the Windows
            // behavior.
            if( s_pControlFocus &&
                s_pControlFocus->m_pDialog == this &&
                s_pControlFocus->GetEnabled() )
            {
                if( wParam )
                    s_pControlFocus->OnFocusIn();
                else
                    s_pControlFocus->OnFocusOut();
            }
            break;

            // Keyboard messages
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            // If a control is in focus, it belongs to this dialog, and it's enabled, then give
            // it the first chance at handling the message.
            if( s_pControlFocus &&
                s_pControlFocus->m_pDialog == this &&
                s_pControlFocus->GetEnabled() )
            {
                if( s_pControlFocus->HandleKeyboard(hWnd, Message, wParam, lParam))
                    return TRUE;
            }

            // Not yet handled, see if this matches a control's hotkey
            // Activate the hotkey if the focus doesn't belong to an
            // edit box.
            if( Message == WM_KEYDOWN && ( !s_pControlFocus ||
                                        ( s_pControlFocus->GetType() != DXUT_CONTROL_EDITBOX
                                          && s_pControlFocus->GetType() != DXUT_CONTROL_IMEEDITBOX ) ) )
            {
                CDXUTControl **Controls = m_Controls.GetData();

                for (ULONG Count = m_Controls.GetSize(); Count != 0; ++Controls, --Count)
                {
                    CDXUTControl *Control = *Controls;

                    if (Control->GetHotkey() != wParam)
                        continue;

                    UINT Modifiers = Control->GetHotkeyModifiers();

                    if (FLAG_ON(Modifiers, MOD_ALT) && GetKeyState(VK_MENU) >= 0)
                        continue;

                    if (FLAG_ON(Modifiers, MOD_CONTROL) && GetKeyState(VK_CONTROL) >= 0)
                        continue;

                    if (FLAG_ON(Modifiers, MOD_SHIFT) && GetKeyState(VK_SHIFT) >= 0)
                        continue;

                    if (
                        FLAG_ON(Modifiers, MOD_WIN) &&
                        GetKeyState(VK_LWIN) >= 0 &&
                        GetKeyState(VK_RWIN) >= 0
                        )
                    {
                        continue;
                    }

                    Control->OnHotkey();

                    return TRUE;
                }
            }

            // Not yet handled, check for focus messages
            if( Message == WM_KEYDOWN )
            {
                // If keyboard input is not enabled, this message should be ignored
                if( !m_bKeyboardInput )
                    return FALSE;

                switch( wParam )
                {
                    case VK_RIGHT:
                    case VK_DOWN:
                        if( s_pControlFocus != NULL )
                        {
                            return OnCycleFocus( TRUE );
                        }
                        break;

                    case VK_LEFT:
                    case VK_UP:
                        if( s_pControlFocus != NULL )
                        {
                            return OnCycleFocus( FALSE );
                        }
                        break;

                    case VK_TAB:
                    {
                        BOOL bShiftDown = ( ( GetKeyState( VK_SHIFT ) & 0x8000 ) != 0 );
                        return OnCycleFocus( !bShiftDown );
                    }
                }
            }

            break;
        }


            // Mouse messages
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
        case WM_LBUTTONDBLCLK:
        case WM_MBUTTONDBLCLK:
        case WM_RBUTTONDBLCLK:
        case WM_XBUTTONDBLCLK:
        case WM_MOUSEWHEEL:
        {
            // If not accepting mouse input, return false to indicate the message should still
            // be handled by the application (usually to move the camera).
            if( !m_bMouseInput )
                return FALSE;

            POINT MousePoint = { LOWORD(lParam), HIWORD(lParam) };
            MousePoint.x -= m_x;
            MousePoint.y -= m_y;

            AdjustChildPoint(&MousePoint);

            // If caption is enabled, offset the Y coordinate by the negative of its height.
            if( m_bCaption )
                MousePoint.y -= GetCaptionHeightAboveFrame();

            AdjustParentCaptionPoint(&MousePoint);

            // If a control is in focus, it belongs to this dialog, and it's enabled, then give
            // it the first chance at handling the message.
            if( s_pControlFocus &&
                s_pControlFocus->m_pDialog == this &&
                s_pControlFocus->GetEnabled() )
            {
                if( s_pControlFocus->HandleMouse(hWnd, Message, MousePoint, wParam, lParam))
                    return TRUE;
            }

            // Not yet handled, see if the mouse is over any controls
            CDXUTControl* pControl = GetControlAtPoint( MousePoint );
            if( pControl != NULL) //  && pControl->GetEnabled() )
            {
                bHandled = pControl->HandleMouse(hWnd, Message, MousePoint, wParam, lParam);
                if( bHandled )
                    return TRUE;
            }
            else
            {
                // Mouse not over any controls in this dialog, if there was a control
                // which had focus it just lost it
/*
                if( Message == WM_LBUTTONDOWN &&
                    s_pControlFocus &&
                    s_pControlFocus->m_pDialog == this )
                {
                    s_pControlFocus->OnFocusOut();
                    s_pControlFocus = NULL;
                }
*/
            }

            // Still not handled, hand this off to the dialog. Return false to indicate the
            // message should still be handled by the application (usually to move the camera).
            switch (Message)
            {
                case WM_MOUSEMOVE:
                    OnMouseMove( MousePoint );
                    return FALSE;

                case WM_LBUTTONDOWN:
                case WM_LBUTTONUP:
                    if (MousePoint.x < 0)
                        break;
                    if (MousePoint.x > GetWidth())
                        break;
                    if (MousePoint.y < 0)
                        break;
                    if (MousePoint.y > GetHeight())
                        break;

                    if (MsgProc(hWnd, ~(Message + (WM_NCLBUTTONDOWN - WM_LBUTTONDOWN)), HTCAPTION, lParam))
                        return TRUE;

                    break;
            }

            break;
        }

        case WM_CAPTURECHANGED:
        {
            // The application has lost mouse capture.
            // The dialog object may not have received
            // a WM_MOUSEUP when capture changed. Reset
            // m_bDrag so that the dialog does not mistakenly
            // think the mouse button is still held down.
            if( ( HWND )lParam != hWnd )
                m_LButtonPressed = FALSE;
        }
    }

    return FALSE;
}

//--------------------------------------------------------------------------------------
CDXUTControl* CDXUTDialog::GetControlAtPoint( POINT pt )
{
    // Search through all child controls for the first one which
    // contains the mouse point
    for( ULONG i = 0; i < m_Controls.GetSize(); i++ )
    {
        CDXUTControl* pControl = m_Controls.GetAt( i );

        if( pControl == NULL )
        {
            continue;
        }

        // We only return the current control if it is visible
        // and enabled.  Because GetControlAtPoint() is used to do mouse
        // hittest, it makes sense to perform this filtering.
        if( pControl->ContainsPoint( pt ) && pControl->GetEnabled() && pControl->GetVisible() )
        {
            return pControl;
        }
    }

    return NULL;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTDialog::GetControlEnabled( int ID )
{
    CDXUTControl* pControl = GetControl( ID );
    if( pControl == NULL )
        return FALSE;

    return pControl->GetEnabled();
}



//--------------------------------------------------------------------------------------
void CDXUTDialog::SetControlEnabled( int ID, BOOL bEnabled )
{
    CDXUTControl* pControl = GetControl( ID );
    if( pControl == NULL )
        return;

    pControl->SetEnabled( bEnabled );
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::OnMouseUp( POINT pt )
{
    s_pControlPressed = NULL;
    m_pControlMouseOver = NULL;
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::OnMouseMove( POINT pt )
{
    // Figure out which control the mouse is over now
    CDXUTControl* pControl = GetControlAtPoint( pt );

    // If the mouse is still over the same control, nothing needs to be done
    if( pControl == m_pControlMouseOver )
        return;

    // Handle mouse leaving the old control
    if( m_pControlMouseOver )
        m_pControlMouseOver->OnMouseLeave();

    // Handle mouse entering the new control
    m_pControlMouseOver = pControl;
    if( pControl != NULL )
        m_pControlMouseOver->OnMouseEnter();
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::SetDefaultElement( UINT nControlType, UINT iElement, CDXUTElement* pElement )
{
    // If this Element type already exist in the list, simply update the stored Element
    for( ULONG i = 0; i < m_DefaultElements.GetSize(); i++ )
    {
        DXUTElementHolder* pElementHolder = m_DefaultElements.GetAt( i );

        if( pElementHolder->nControlType == nControlType &&
            pElementHolder->iElement == iElement )
        {
            pElementHolder->Element = *pElement;
            return S_OK;
        }
    }

    // Otherwise, add a new entry
    DXUTElementHolder* pNewHolder;
    pNewHolder = new DXUTElementHolder;
    if( pNewHolder == NULL )
        return E_OUTOFMEMORY;

    pNewHolder->nControlType = nControlType;
    pNewHolder->iElement = iElement;
    pNewHolder->Element = *pElement;

    HRESULT hr = m_DefaultElements.Add( pNewHolder );
    if( FAILED( hr ) )
    {
        delete pNewHolder;
    }
    return hr;
}


//--------------------------------------------------------------------------------------
CDXUTElement* CDXUTDialog::GetDefaultElement( UINT nControlType, UINT iElement )
{
    for( ULONG i = 0; i < m_DefaultElements.GetSize(); i++ )
    {
        DXUTElementHolder* pElementHolder = m_DefaultElements.GetAt( i );

        if( pElementHolder->nControlType == nControlType &&
            pElementHolder->iElement == iElement )
        {
            return &pElementHolder->Element;
        }
    }

    return NULL;
}



//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::AddStatic( int ID, LPCWSTR strText, int x, int y, int width, int height, BOOL bIsDefault,
                                CDXUTStatic** ppCreated )
{
    HRESULT hr = S_OK;

    CDXUTStatic* pStatic = new CDXUTStatic( this );

    if( pStatic == NULL )
        return E_OUTOFMEMORY;

    hr = AddControl( pStatic );
    if( FAILED( hr ) )
    {
        delete pStatic;
        return hr;
    }

    if( ppCreated != NULL )
        *ppCreated = pStatic;

    // Set the ID and list index
    pStatic->SetID( ID );
    pStatic->SetText( strText );
    pStatic->SetLocation( x, y );
    pStatic->SetSize( width, height );
    pStatic->m_bIsDefault = bIsDefault;

    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::AddButton( int ID, LPCWSTR strText, int x, int y, int width, int height, UINT nHotkey,
                                BOOL bIsDefault, CDXUTButton** ppCreated )
{
    HRESULT hr = S_OK;

    CDXUTButton* pButton = new CDXUTButton( this );

    if( pButton == NULL )
        return E_OUTOFMEMORY;

    hr = AddControl( pButton );
    if( FAILED( hr ) )
    {
        delete pButton;
        return hr;
    }

    if( ppCreated != NULL )
        *ppCreated = pButton;

    // Set the ID and list index
    pButton->SetID( ID );
    pButton->SetText( strText );
    pButton->SetLocation( x, y );
    pButton->SetSize( width, height );
    pButton->SetHotkey( nHotkey );
    pButton->m_bIsDefault = bIsDefault;

    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::AddCheckBox( int ID, LPCWSTR strText, int x, int y, int width, int height, BOOL bChecked,
                                  UINT nHotkey, BOOL bIsDefault, CDXUTCheckBox** ppCreated )
{
    HRESULT hr = S_OK;

    CDXUTCheckBox* pCheckBox = new CDXUTCheckBox( this );

    if( pCheckBox == NULL )
        return E_OUTOFMEMORY;

    hr = AddControl( pCheckBox );
    if( FAILED( hr ) )
    {
        delete pCheckBox;
        return hr;
    }

    if( ppCreated != NULL )
        *ppCreated = pCheckBox;

    // Set the ID and list index
    pCheckBox->SetID( ID );
    pCheckBox->SetText( strText );
    pCheckBox->SetLocation( x, y );
    pCheckBox->SetSize( width, height );
    pCheckBox->SetHotkey( nHotkey );
    pCheckBox->m_bIsDefault = bIsDefault;
    pCheckBox->SetChecked( bChecked );

    return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::AddRadioButton( int ID, UINT nButtonGroup, LPCWSTR strText, int x, int y, int width, int height,
                                     BOOL bChecked, UINT nHotkey, BOOL bIsDefault, CDXUTRadioButton** ppCreated )
{
    HRESULT hr = S_OK;

    CDXUTRadioButton* pRadioButton = new CDXUTRadioButton( this );

    if( pRadioButton == NULL )
        return E_OUTOFMEMORY;

    hr = AddControl( pRadioButton );
    if( FAILED( hr ) )
    {
        delete pRadioButton;
        return hr;
    }

    if( ppCreated != NULL )
        *ppCreated = pRadioButton;

    // Set the ID and list index
    pRadioButton->SetID( ID );
    pRadioButton->SetText( strText );
    pRadioButton->SetButtonGroup( nButtonGroup );
    pRadioButton->SetLocation( x, y );
    pRadioButton->SetSize( width, height );
    pRadioButton->SetHotkey( nHotkey );
    pRadioButton->SetChecked( bChecked );
    pRadioButton->m_bIsDefault = bIsDefault;
//    pRadioButton->SetChecked( bChecked );

    return S_OK;
}




//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::AddComboBox( int ID, int x, int y, int width, int height, UINT nHotkey, BOOL bIsDefault,
                                  CDXUTComboBox** ppCreated )
{
    HRESULT hr = S_OK;

    CDXUTComboBox* pComboBox = new CDXUTComboBox( this );

    if( pComboBox == NULL )
        return E_OUTOFMEMORY;

    hr = AddControl( pComboBox );
    if( FAILED( hr ) )
    {
        delete pComboBox;
        return hr;
    }

    if( ppCreated != NULL )
        *ppCreated = pComboBox;

    // Set the ID and list index
    pComboBox->SetID( ID );
    pComboBox->SetLocation( x, y );
    pComboBox->SetSize( width, height );
    pComboBox->SetHotkey( nHotkey );
    pComboBox->m_bIsDefault = bIsDefault;

    return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::AddSlider( int ID, int x, int y, int width, int height, int min, int max, int value,
                                BOOL bIsDefault, CDXUTSlider** ppCreated )
{
    HRESULT hr = S_OK;

    CDXUTSlider* pSlider = new CDXUTSlider( this );

    if( pSlider == NULL )
        return E_OUTOFMEMORY;

    hr = AddControl( pSlider );
    if( FAILED( hr ) )
    {
        delete pSlider;
        return hr;
    }

    if( ppCreated != NULL )
        *ppCreated = pSlider;

    // Set the ID and list index
    pSlider->SetID( ID );
    pSlider->SetLocation( x, y );
    pSlider->SetSize( width, height );
    pSlider->m_bIsDefault = bIsDefault;
    pSlider->SetRange( min, max );
    pSlider->SetValue( value );
    pSlider->UpdateRects();

    return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::AddEditBox( int ID, LPCWSTR strText, int x, int y, int width, int height, BOOL bIsDefault,
                                 CDXUTEditBox** ppCreated )
{
    HRESULT hr = S_OK;

    CDXUTEditBox* pEditBox = new CDXUTEditBox( this );

    if( pEditBox == NULL )
        return E_OUTOFMEMORY;

    hr = AddControl( pEditBox );
    if( FAILED( hr ) )
    {
        delete pEditBox;
        return hr;
    }

    if( ppCreated != NULL )
        *ppCreated = pEditBox;

    // Set the ID and position
    pEditBox->SetID( ID );
    pEditBox->SetLocation( x, y );
    pEditBox->SetSize( width, height );
    pEditBox->m_bIsDefault = bIsDefault;

    if( strText )
        pEditBox->SetText( strText );

    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::AddListBox( int ID, int x, int y, int width, int height, DWORD dwStyle, CDXUTListBox** ppCreated )
{
    HRESULT hr = S_OK;
    CDXUTListBox* pListBox = new CDXUTListBox( this );

    if( pListBox == NULL )
        return E_OUTOFMEMORY;

    hr = AddControl( pListBox );
    if( FAILED( hr ) )
    {
        delete pListBox;
        return hr;
    }

    if( ppCreated != NULL )
        *ppCreated = pListBox;

    // Set the ID and position
    pListBox->SetID( ID );
    pListBox->SetLocation( x, y );
    pListBox->SetSize( width, height );
    pListBox->SetStyle( dwStyle );

    return S_OK;
}

HRESULT
CDXUTDialog::
AddTabControl(
    INT                 ID,
    INT                 X,
    INT                 Y,
    INT                 Width,
    INT                 Height,
    ULONG               Style   /* = 0 */,
    CDXUTTabControl   **Created /* = NULL */
)
{
    HRESULT             Result;
    CDXUTTabControl    *TabCtrl;

    TabCtrl = new CDXUTTabControl(this);

    if(TabCtrl == NULL)
        return E_OUTOFMEMORY;

    Result = AddControl(TabCtrl);
    if(FAILED(Result))
    {
        delete TabCtrl;
        return Result;
    }

    if (Created != NULL)
        *Created = TabCtrl;

    TabCtrl->SetID(ID);
    TabCtrl->SetLocation(X, Y);
    TabCtrl->SetSize(Width, Height);
    TabCtrl->SetStyle(Style);

    return S_OK;
}

//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::InitControl(CDXUTControl* Control)
{
    HRESULT             hr;
    DXUTElementHolder **Holder;

    if(Control == NULL)
        return E_INVALIDARG;

    Holder = m_DefaultElements.GetData();
    Control->m_ControlListIndex = m_Controls.GetSize();

    // Look for a default Element entries
    for (ULONG Count = m_DefaultElements.GetSize(); Count; --Count)
    {
        DXUTElementHolder* pElementHolder = *Holder++;

        if (pElementHolder->nControlType == Control->GetType())
            Control->SetElement(pElementHolder->iElement, &pElementHolder->Element);
    }

    V_RETURN(Control->OnInit());

    return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::AddControl( CDXUTControl* pControl )
{
    HRESULT hr = S_OK;

    hr = InitControl( pControl );
    if( FAILED( hr ) )
        return DXTRACE_ERR( L"CDXUTDialog::InitControl", hr );

    // Add to the list
    hr = m_Controls.Add( pControl );
    if( FAILED( hr ) )
    {
        return DXTRACE_ERR( L"CGrowableArray::Add", hr );
    }

    return S_OK;
}


//--------------------------------------------------------------------------------------
CDXUTControl* CDXUTDialog::GetControl( int ID )
{
    // Try to find the control with the given ID
    for( ULONG i = 0; i < m_Controls.GetSize(); i++ )
    {
        CDXUTControl* pControl = m_Controls.GetAt( i );

        if( pControl->GetID() == ID )
        {
            return pControl;
        }
    }

    // Not found
    return NULL;
}



//--------------------------------------------------------------------------------------
CDXUTControl* CDXUTDialog::GetControl( int ID, UINT nControlType )
{
    // Try to find the control with the given ID
    for( ULONG i = 0; i < m_Controls.GetSize(); i++ )
    {
        CDXUTControl* pControl = m_Controls.GetAt( i );

        if( pControl->GetID() == ID && pControl->GetType() == nControlType )
        {
            return pControl;
        }
    }

    // Not found
    return NULL;
}

HRESULT
CDXUTDialog::
SetElementInfoByTexture(
    PDXUT_ELEMENT_INFO  Element,
    PDXUT_TEXTURE_INFO  Texture,
    ULONG               Count,
    D3DCOLOR            Color /* = D3DCOLOR_ARGB(255, 255, 255, 255) */
)
{
    HRESULT Result;
    ULONG   Index;

    Result = S_OK;

    for (; Count; ++Element, ++Texture, --Count)
    {
        if (Texture->Path == NULL)
        {
            Element->Element.iTexture = DXUT_INVALID_TEXTURE_ID;
            continue;
        }

        Index = AddTexture(Texture->Path);
        if (Index == DXUT_INVALID_TEXTURE_ID)
        {
            Result = E_FAIL;
            break;
        }

        Element->Position       = Texture->Rect;
        Element->ShadowWidth    = Texture->ShadowWidth;

        Element->Element.SetTexture(Index, &Texture->Rect);
        Element->Element.TextureColor.States[DXUT_STATE_NORMAL] = Color;
        Element->Element.TextureColor.Blend(DXUT_STATE_NORMAL, 10.0f);
    }

    return Result;
}

HRESULT
CDXUTDialog::
SetCaptionTexture(
    DXUT_TEXTURE_INFO   CaptionTexture[DXUT_CAPTION_ELEMENT_COUNT],
    D3DCOLOR            TextureColor /* = D3DCOLOR_ARGB(255, 255, 255, 255) */
)
{
    return SetElementInfoByTexture(m_CaptionElement, CaptionTexture, DXUT_CAPTION_ELEMENT_COUNT, TextureColor);
}

HRESULT
CDXUTDialog::
SetFrameTexture(
    DXUT_TEXTURE_INFO   FrmaeTexture[DXUT_DIALOG_FRAME_ELEMENT_COUNT],
    ULONG               Flags           /* = 0 */,
    D3DCOLOR            TextureColor    /* = D3DCOLOR_ARGB(255, 255, 255, 255) */
)
{
    m_FrameFlags.Flags |= Flags;
    return SetElementInfoByTexture(m_FrameElement, FrmaeTexture, DXUT_DIALOG_FRAME_ELEMENT_COUNT, TextureColor);
}

//--------------------------------------------------------------------------------------
CDXUTControl* CDXUTDialog::GetNextControl( CDXUTControl* pControl )
{
    ULONG Count, Index;
    CDXUTDialog* pDialog;

    pDialog = pControl->m_pDialog;
    Count   = pDialog->m_Controls.GetSize();
    if (Count == 0)
        return NULL;

    Index = pControl->m_ControlListIndex + 1;
    if (Index >= Count)
        Index = 0;

    // Cycle through dialogs in the loop to find the next control. Note
    // that if only one control exists in all looped dialogs it will
    // be the returned 'next' control.
//    while( index >= ( int )pDialog->m_Controls.GetSize() )
//    {
//        pDialog = pDialog->m_pNextDialog;
//        index = 0;
//    }

    return pDialog->m_Controls.GetAt(Index);
}

//--------------------------------------------------------------------------------------
CDXUTControl* CDXUTDialog::GetPrevControl( CDXUTControl* pControl )
{
    ULONG Count, Index;
    CDXUTDialog* pDialog;

    pDialog = pControl->m_pDialog;
    Count   = pDialog->m_Controls.GetSize();
    if (Count == 0)
        return NULL;

    Index = pControl->m_ControlListIndex;
    Index = Index == 0 ? (Count - 1) : (Index - 1);

    // Cycle through dialogs in the loop to find the next control. Note
    // that if only one control exists in all looped dialogs it will
    // be the returned 'previous' control.
//    while( index < 0 )
//    {
//        pDialog = pDialog->m_pPrevDialog;
//        if( pDialog == NULL )
//            pDialog = pControl->m_pDialog;
//
//        index = pDialog->m_Controls.GetSize() - 1;
//    }

    return pDialog->m_Controls.GetAt(Index);
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::ClearRadioButtonGroup( UINT nButtonGroup )
{
    // Find all radio buttons with the given group number
    for( ULONG i = 0; i < m_Controls.GetSize(); i++ )
    {
        CDXUTControl* pControl = m_Controls.GetAt( i );

        if( pControl->GetType() == DXUT_CONTROL_RADIOBUTTON )
        {
            CDXUTRadioButton* pRadioButton = ( CDXUTRadioButton* )pControl;

            if( pRadioButton->GetButtonGroup() == nButtonGroup )
                pRadioButton->SetChecked( FALSE, FALSE );
        }
    }
}



//--------------------------------------------------------------------------------------
void CDXUTDialog::ClearComboBox( int ID )
{
    CDXUTComboBox* pComboBox = GetComboBox( ID );
    if( pComboBox == NULL )
        return;

    pComboBox->RemoveAllItems();
}




//--------------------------------------------------------------------------------------
void CDXUTDialog::RequestFocus( CDXUTControl* pControl )
{
    if( s_pControlFocus == pControl )
        return;

    if( !pControl->CanHaveFocus() )
        return;

    if( s_pControlFocus )
        s_pControlFocus->OnFocusOut();

    pControl->OnFocusIn();
    s_pControlFocus = pControl;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::DrawRect( RECT* pRect, D3DCOLOR color )
{
    RECT rc = *pRect;

    AdjustChildRect(&rc);

    if( m_pManager->GetD3D9Device() )
        return DrawRect9( &rc, color );
    else
        return DrawRect10( &rc, color );
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::DrawRect9( RECT* pRect, D3DCOLOR color )
{
    RECT rcScreen = *pRect;

    OffsetRectAbsolute(rcScreen);

    // If caption is enabled, offset the Y position by its height.
    if( m_bCaption )
        OffsetRect( &rcScreen, 0, GetCaptionHeightAboveFrame() );

    DXUT_SCREEN_VERTEX vertices[4] =
    {
        ( FLOAT )rcScreen.left - 0.5f,  ( FLOAT )rcScreen.top - 0.5f,    0.5f, 1.0f, color, 0, 0,
        ( FLOAT )rcScreen.right - 0.5f, ( FLOAT )rcScreen.top - 0.5f,    0.5f, 1.0f, color, 0, 0,
        ( FLOAT )rcScreen.right - 0.5f, ( FLOAT )rcScreen.bottom - 0.5f, 0.5f, 1.0f, color, 0, 0,
        ( FLOAT )rcScreen.left - 0.5f,  ( FLOAT )rcScreen.bottom - 0.5f, 0.5f, 1.0f, color, 0, 0,
    };

    IDirect3DDevice9* pd3dDevice = m_pManager->GetD3D9Device();

    // Since we're doing our own drawing here we need to flush the sprites
    m_pManager->m_pSprite->Flush();
    IDirect3DVertexDeclaration9* pDecl = NULL;
    pd3dDevice->GetVertexDeclaration( &pDecl );  // Preserve the sprite's current vertex decl
    pd3dDevice->SetFVF( DXUT_SCREEN_VERTEX::FVF );

    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );

    pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, vertices, sizeof( DXUT_SCREEN_VERTEX ) );

    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

    // Restore the vertex decl
    pd3dDevice->SetVertexDeclaration( pDecl );
    pDecl->Release();

    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::DrawRect10( RECT* pRect, D3DCOLOR color )
{
    RECT rcScreen = *pRect;
    OffsetRectAbsolute(rcScreen);

    // If caption is enabled, offset the Y position by its height.
    if( m_bCaption )
        OffsetRect( &rcScreen, 0, GetCaptionHeightAboveFrame() );

    ID3D10Device* pd3dDevice = m_pManager->GetD3D10Device();

    // Convert the rect from screen coordinates to clip space coordinates.
    FLOAT Left, Right, Top, Bottom;
    Left = rcScreen.left * 2.0f / m_pManager->m_nBackBufferWidth - 1.0f;
    Right = rcScreen.right * 2.0f / m_pManager->m_nBackBufferWidth - 1.0f;
    Top = 1.0f - rcScreen.top * 2.0f / m_pManager->m_nBackBufferHeight;
    Bottom = 1.0f - rcScreen.bottom * 2.0f / m_pManager->m_nBackBufferHeight;
    DXUT_SCREEN_VERTEX_10 vertices[4] =
    {
        { Left,     Top, 0.5f, D3DCOLOR_TO_D3DCOLORVALUE( color ), 0.0f, 0.0f },
        { Right,    Top, 0.5f, D3DCOLOR_TO_D3DCOLORVALUE( color ), 1.0f, 0.0f },
        { Left,  Bottom, 0.5f, D3DCOLOR_TO_D3DCOLORVALUE( color ), 0.0f, 1.0f },
        { Right, Bottom, 0.5f, D3DCOLOR_TO_D3DCOLORVALUE( color ), 1.0f, 1.0f },
    };
    DXUT_SCREEN_VERTEX_10* pVB;
    if( SUCCEEDED( m_pManager->m_pVBScreenQuad10->Map( D3D10_MAP_WRITE_DISCARD, 0, ( LPVOID* )&pVB ) ) )
    {
        CopyMemory( pVB, vertices, sizeof( vertices ) );
        m_pManager->m_pVBScreenQuad10->Unmap();
    }

    // Since we're doing our own drawing here we need to flush the sprites
    m_pManager->m_pSprite10->Flush();

    ID3D10InputLayout* pOldLayout;
    D3D10_PRIMITIVE_TOPOLOGY OldTopology;

    pd3dDevice->IAGetInputLayout( &pOldLayout );
    pd3dDevice->IAGetPrimitiveTopology( &OldTopology );
    pd3dDevice->IASetInputLayout( m_pManager->m_pInputLayout10 );
    pd3dDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

    D3D10_TECHNIQUE_DESC techDesc;
    m_pManager->m_pTechRenderUI10->GetDesc( &techDesc );
    for( UINT p = 0; p < techDesc.Passes; ++p )
    {
        m_pManager->m_pTechRenderUI10->GetPassByIndex( p )->Apply( 0 );
        pd3dDevice->Draw( 4, 0 );
    }

    pd3dDevice->IASetInputLayout( pOldLayout );
    pd3dDevice->IASetPrimitiveTopology( OldTopology );
    SAFE_RELEASE( pOldLayout );

    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::DrawPolyLine( POINT* apPoints, UINT nNumPoints, D3DCOLOR color )
{
    DXUT_SCREEN_VERTEX* vertices = new DXUT_SCREEN_VERTEX[ nNumPoints ];
    if( vertices == NULL )
        return E_OUTOFMEMORY;

    RECT rc;
    DXUT_SCREEN_VERTEX* pVertex = vertices;
    POINT* pt = apPoints;

    GetRectAbsolute(rc);

    for( UINT i = 0; i < nNumPoints; i++ )
    {
        pVertex->x = rc.left + ( FLOAT )pt->x;
        pVertex->y = rc.top + ( FLOAT )pt->y;
        pVertex->z = 0.5f;
        pVertex->h = 1.0f;
        pVertex->color = color;
        pVertex->tu = 0.0f;
        pVertex->tv = 0.0f;

        pVertex++;
        pt++;
    }

    IDirect3DDevice9* pd3dDevice = m_pManager->GetD3D9Device();

    // Since we're doing our own drawing here we need to flush the sprites
    m_pManager->m_pSprite->Flush();
    IDirect3DVertexDeclaration9* pDecl = NULL;
    pd3dDevice->GetVertexDeclaration( &pDecl );  // Preserve the sprite's current vertex decl
    pd3dDevice->SetFVF( DXUT_SCREEN_VERTEX::FVF );

    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );

    pd3dDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, nNumPoints - 1, vertices, sizeof( DXUT_SCREEN_VERTEX ) );

    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

    // Restore the vertex decl
    pd3dDevice->SetVertexDeclaration( pDecl );
    pDecl->Release();

    SAFE_DELETE_ARRAY( vertices );
    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::DrawSprite( CDXUTElement* pElement, RECT* prcDest, FLOAT fDepth )
{
    RECT rc = *prcDest;

    AdjustChildRect(&rc);

    if( m_pManager->GetD3D9Device() )
        return DrawSprite9( pElement, &rc );
    else
        return DrawSprite10( pElement, &rc, fDepth );
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::DrawSprite9( CDXUTElement* pElement, RECT* prcDest )
{
    // No need to draw fully transparent layers
    if( pElement->TextureColor.Current.a == 0 )
        return S_OK;

    RECT rcTexture = pElement->rcTexture;

    RECT rcScreen = *prcDest;
    OffsetRectAbsolute(rcScreen);

    // If caption is enabled, offset the Y position by its height.
    if( m_bCaption )
        OffsetRect( &rcScreen, 0, GetCaptionHeightAboveFrame() );

    DXUTTextureNode* pTextureNode = GetTexture( pElement->iTexture );
    if( pTextureNode == NULL )
        return E_FAIL;

    FLOAT fScaleX = ( FLOAT )RectWidth( rcScreen ) / RectWidth( rcTexture );
    FLOAT fScaleY = ( FLOAT )RectHeight( rcScreen ) / RectHeight( rcTexture );

    D3DXMATRIXA16 matTransform;
    D3DXMatrixScaling( &matTransform, fScaleX, fScaleY, 1.0f );

    m_pManager->m_pSprite->SetTransform( &matTransform );

    D3DXVECTOR3 vPos( ( FLOAT )rcScreen.left, ( FLOAT )rcScreen.top, 0.0f );

    vPos.x /= fScaleX;
    vPos.y /= fScaleY;

    return m_pManager->m_pSprite->Draw( pTextureNode->Texture9, &rcTexture, NULL, &vPos,
                                        pElement->TextureColor.Current );
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::DrawSprite10( CDXUTElement* pElement, RECT* prcDest, FLOAT fDepth )
{
    // No need to draw fully transparent layers
    if( pElement->TextureColor.Current.a == 0 )
        return S_OK;

    RECT rcTexture = pElement->rcTexture;

    RECT rcScreen = *prcDest;
    OffsetRectAbsolute(rcScreen);
    OffsetRect( &rcScreen, RectWidth( rcScreen ) / 2, RectHeight( rcScreen ) / 2 );

    // If caption is enabled, offset the Y position by its height.
    if( m_bCaption )
        OffsetRect( &rcScreen, 0, GetCaptionHeightAboveFrame() );

    DXUTTextureNode* pTextureNode = GetTexture( pElement->iTexture );
    if( pTextureNode == NULL )
        return E_FAIL;

    FLOAT fBBWidth = ( FLOAT )m_pManager->m_nBackBufferWidth;
    FLOAT fBBHeight = ( FLOAT )m_pManager->m_nBackBufferHeight;
    FLOAT fScaleX = ( FLOAT )RectWidth( rcScreen );
    FLOAT fScaleY = ( FLOAT )RectHeight( rcScreen );

    D3DXVECTOR3 vPos( ( FLOAT )rcScreen.left, ( FLOAT )rcScreen.top, fDepth );

    D3DXMATRIXA16 matScaling;
    D3DXMATRIXA16 matTranslation;
    D3DXMatrixScaling( &matScaling, fScaleX, fScaleY, 1.0f );
    D3DXMatrixTranslation( &matTranslation, vPos.x, fBBHeight - vPos.y, vPos.z );

    D3DXMATRIXA16 matProjection;
    D3DXMatrixOrthoOffCenterLH( &matProjection, 0.0f, fBBWidth, 0.0f, fBBHeight, 0.1f, 10 );
    m_pManager->m_pSprite10->SetProjectionTransform( &matProjection );

    D3DX10_SPRITE Sprite;

    Sprite.matWorld = matScaling * matTranslation;
    Sprite.pTexture = pTextureNode->TexResView;
    FLOAT fTexWidth = ( FLOAT )pTextureNode->Width;
    FLOAT fTexHeight = ( FLOAT )pTextureNode->Height;
    Sprite.TexCoord.x = ( FLOAT )( rcTexture.left ) / fTexWidth;
    Sprite.TexCoord.y = ( FLOAT )( rcTexture.top ) / fTexHeight;
    Sprite.TexSize.x = ( FLOAT )( rcTexture.right - rcTexture.left ) / fTexWidth;
    Sprite.TexSize.y = ( FLOAT )( rcTexture.bottom - rcTexture.top ) / fTexHeight;
    Sprite.TextureIndex = 0;
    Sprite.ColorModulate = pElement->TextureColor.Current;

    return m_pManager->m_pSprite10->DrawSpritesBuffered( &Sprite, 1 );
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::CalcTextRect( LPCWSTR strText, CDXUTElement* pElement, RECT* prcDest, int nCount )
{
    HRESULT hr = S_OK;

    if (strText == NULL)
    {
        SetRect(prcDest, 0, 0, 0, 0);
        return hr;
    }

    DXUTFontNode* pFontNode = GetFont( pElement->iFont );
    if( pFontNode == NULL )
        return E_FAIL;

    DWORD dwTextFormat = pElement->dwTextFormat | DT_CALCRECT;
    // Since we are only computing the rectangle, we don't need a sprite.
    if( pFontNode->Font10 )
    {
        hr = pFontNode->Font10->DrawText( NULL, strText, nCount, prcDest, dwTextFormat, pElement->FontColor.Current );
        if( FAILED( hr ) )
            return hr;
    }
    else if( pFontNode->Font9 )
    {
        hr = pFontNode->Font9->DrawText( NULL, strText, nCount, prcDest, dwTextFormat, pElement->FontColor.Current );
        if( FAILED( hr ) )
            return hr;
    }

    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::DrawText( LPCWSTR strText, CDXUTElement* pElement, RECT* prcDest, BOOL bShadow, int nCount )
{
    if (strText == NULL)
        return S_OK;

    RECT rc = *prcDest;

    AdjustChildRect(&rc);

    if (m_pManager->GetD3D9Device())
        return DrawText9(strText, pElement, &rc, bShadow, nCount);
    else
        return DrawText10(strText, pElement, &rc, bShadow, nCount);
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::DrawText9( LPCWSTR strText, CDXUTElement* pElement, RECT* prcDest, BOOL bShadow, int nCount )
{
    HRESULT hr = S_OK;

    // No need to draw fully transparent layers
    if( pElement->FontColor.Current.a == 0 )
        return S_OK;

    RECT rcScreen = *prcDest;
    OffsetRectAbsolute(rcScreen);

    // If caption is enabled, offset the Y position by its height.
    if( m_bCaption )
        OffsetRect( &rcScreen, 0, GetCaptionHeightAboveFrame() );

    D3DXMATRIX matTransform;
    D3DXMatrixIdentity( &matTransform );
    m_pManager->m_pSprite->SetTransform( &matTransform );

    DXUTFontNode* pFontNode = GetFont( pElement->iFont );

    if( bShadow )
    {
        RECT rcShadow = rcScreen;
        OffsetRect( &rcShadow, 1, 1 );
        hr = pFontNode->Font9->DrawText( m_pManager->m_pSprite, strText, nCount, &rcShadow, pElement->dwTextFormat,
                                          D3DCOLOR_ARGB( DWORD( pElement->FontColor.Current.a * 255 ), 0, 0, 0 ) );
        if( FAILED( hr ) )
            return hr;
    }

    hr = pFontNode->Font9->DrawText( m_pManager->m_pSprite, strText, nCount, &rcScreen, pElement->dwTextFormat,
                                      pElement->FontColor.Current );
    if( FAILED( hr ) )
        return hr;

    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialog::DrawText10( LPCWSTR strText, CDXUTElement* pElement, RECT* prcDest, BOOL bShadow, int nCount )
{
    HRESULT hr = S_OK;

    // No need to draw fully transparent layers
    if( pElement->FontColor.Current.a == 0 )
        return S_OK;

    RECT rcScreen = *prcDest;
    OffsetRectAbsolute(rcScreen);

    // If caption is enabled, offset the Y position by its height.
    if( m_bCaption )
        OffsetRect( &rcScreen, 0, GetCaptionHeightAboveFrame() );

    FLOAT fBBWidth = ( FLOAT )m_pManager->m_nBackBufferWidth;
    FLOAT fBBHeight = ( FLOAT )m_pManager->m_nBackBufferHeight;

    D3DXMATRIX matProjection;
    D3DXMatrixOrthoOffCenterLH( &matProjection, 0.0f, fBBWidth, 0.0f, fBBHeight, 0.1f, 10 );
    m_pManager->m_pSprite10->SetProjectionTransform( &matProjection );

    DXUTFontNode* pFontNode = GetFont( pElement->iFont );

    if( bShadow )
    {
        RECT rcShadow = rcScreen;
        OffsetRect( &rcShadow, 1, 1 );
        hr = pFontNode->Font10->DrawText( m_pManager->m_pSprite10, strText, nCount, &rcShadow, pElement->dwTextFormat,
                                           D3DCOLOR_ARGB( DWORD( pElement->FontColor.Current.a * 255 ), 0, 0, 0 ) );
        if( FAILED( hr ) )
            return hr;
    }

    hr = pFontNode->Font10->DrawText( m_pManager->m_pSprite10, strText, nCount, &rcScreen, pElement->dwTextFormat,
                                       pElement->FontColor.Current );
    if( FAILED( hr ) )
        return hr;

    return S_OK;
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::SetBackgroundColors( D3DCOLOR colorTopLeft, D3DCOLOR colorTopRight, D3DCOLOR colorBottomLeft,
                                       D3DCOLOR colorBottomRight )
{
    m_colorTopLeft = colorTopLeft;
    m_colorTopRight = colorTopRight;
    m_colorBottomLeft = colorBottomLeft;
    m_colorBottomRight = colorBottomRight;
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::SetNextDialog( CDXUTDialog* pNextDialog )
{
    if( pNextDialog == NULL )
        pNextDialog = this;

    m_pNextDialog = pNextDialog;
    m_pNextDialog->m_pPrevDialog = this;
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::ClearFocus()
{
    if( s_pControlFocus )
    {
        s_pControlFocus->OnFocusOut();
        s_pControlFocus = NULL;
    }

    ReleaseCapture();
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::FocusDefaultControl()
{
    // Check for default control in this dialog
    for( ULONG i = 0; i < m_Controls.GetSize(); i++ )
    {
        CDXUTControl* pControl = m_Controls.GetAt( i );
        if( pControl->m_bIsDefault )
        {
            // Remove focus from the current control
            ClearFocus();

            // Give focus to the default control
            s_pControlFocus = pControl;
            s_pControlFocus->OnFocusIn();
            return;
        }
    }
}


//--------------------------------------------------------------------------------------
BOOL CDXUTDialog::OnCycleFocus(BOOL bForward)
{
    CDXUTControl* pControl = NULL;
    CDXUTDialog* pDialog = NULL; // pDialog and pLastDialog are used to track wrapping of
    CDXUTDialog* pLastDialog;    // focus from first control to last or vice versa.

    if (s_pControlFocus == NULL)
    {
        // If s_pControlFocus is NULL, we focus the first control of first dialog in
        // the case that bForward is true, and focus the last control of last dialog when
        // bForward is false.
        //
        if( bForward )
        {
            // Search for the first control from the start of the dialog
            // array.
            for( ULONG d = 0; d < m_pManager->m_Dialogs.GetSize(); ++d )
            {
                pDialog = pLastDialog = m_pManager->m_Dialogs.GetAt( d );
                if( pDialog && pDialog->m_Controls.GetSize() > 0 )
                {
                    pControl = pDialog->m_Controls.GetAt( 0 );
                    break;
                }
            }

            if( !pDialog || !pControl )
            {
                // No dialog has been registered yet or no controls have been
                // added to the dialogs. Cannot proceed.
                return TRUE;
            }
        }
        else
        {
            // Search for the first control from the end of the dialog
            // array.
            for( int d = m_pManager->m_Dialogs.GetSize() - 1; d >= 0; --d )
            {
                pDialog = pLastDialog = m_pManager->m_Dialogs.GetAt( d );
                if( pDialog && pDialog->m_Controls.GetSize() > 0 )
                {
                    pControl = pDialog->m_Controls.GetAt( pDialog->m_Controls.GetSize() - 1 );
                    break;
                }
            }

            if( !pDialog || !pControl )
            {
                // No dialog has been registered yet or no controls have been
                // added to the dialogs. Cannot proceed.
                return TRUE;
            }
        }
    }
    else if( s_pControlFocus->m_pDialog != this )
    {
        // If a control belonging to another dialog has focus, let that other
        // dialog handle this event by returning false.
        //
        return FALSE;
    }
    else
    {
        // Focused control belongs to this dialog. Cycle to the
        // next/previous control.

        switch (s_pControlFocus->GetType())
        {
            case DXUT_CONTROL_STATIC:
            case DXUT_CONTROL_TAB:
                return FALSE;
        }

        pLastDialog = s_pControlFocus->m_pDialog;
        pControl = bForward ? GetNextControl(s_pControlFocus) : GetPrevControl(s_pControlFocus);
        if (pControl == NULL)
            return FALSE;

        pDialog = pControl->m_pDialog;
    }

    for (ULONG Count = DXUT_MAXIMUN_CONTROL_ID; Count; --Count)
    {
        // If we just wrapped from last control to first or vice versa,
        // set the focused control to NULL. This state, where no control
        // has focus, allows the camera to work.
        int nLastDialogIndex = m_pManager->m_Dialogs.IndexOf( pLastDialog );
        int nDialogIndex = m_pManager->m_Dialogs.IndexOf( pDialog );
        if( ( !bForward && nLastDialogIndex < nDialogIndex ) ||
            ( bForward && nDialogIndex < nLastDialogIndex ) )
        {
            if( s_pControlFocus )
                s_pControlFocus->OnFocusOut();
            s_pControlFocus = NULL;
            return TRUE;
        }

        // If we've gone in a full circle then focus doesn't change
        if( pControl == s_pControlFocus )
            return TRUE;

        // If the dialog accepts keybord input and the control can have focus then
        // move focus

        switch (pControl->GetType())
        {
            case DXUT_CONTROL_STATIC:
            case DXUT_CONTROL_TAB:
                break;

            default:
                if (pControl->m_pDialog->m_bKeyboardInput && pControl->CanHaveFocus())
                {
                    if (s_pControlFocus)
                        s_pControlFocus->OnFocusOut();

                    s_pControlFocus = pControl;
                    s_pControlFocus->OnFocusIn();
                    return TRUE;
                }
        }

        pLastDialog = pDialog;
        pControl = bForward ? GetNextControl(pControl) : GetPrevControl(pControl);
        if (pControl == NULL)
            break;

        pDialog = pControl->m_pDialog;
    }

    // If we reached this point, the chain of dialogs didn't form a complete loop
    DXTRACE_ERR( L"CDXUTDialog: Multiple dialogs are improperly chained together", E_FAIL );
    return FALSE;
}

/************************************************************************
  CDXUTDialogResourceManager impl
************************************************************************/
NTSTATUS CDXUTDialogResourceManager::SetTexturePath(PWSTR Path)
{
    ULONG Length;
    WCHAR FullPath[MAX_NTPATH];

    Length = RtlGetFullPathName_U(Path, sizeof(FullPath), FullPath, NULL);
    if (Length == 0)
    {
        FullPath[Length] = 0;
        Length = sizeof(WCHAR);
    }
    else if (FullPath[Length / sizeof(WCHAR) - 1] != '\\')
    {
        FullPath[Length / sizeof(WCHAR)] = '\\';
        Length += sizeof(WCHAR);
    }

    return RtlSetUnicodeString(&m_TexturePath, FullPath);
}

ULONG CDXUTDialogResourceManager::GetTexturePath(PWSTR Path, ULONG BufferCount)
{
    BufferCount = __min(m_TexturePath.Length, BufferCount * sizeof(WCHAR));
    CopyMemory(Path, m_TexturePath.Buffer, BufferCount);
    return BufferCount / sizeof(WCHAR);
}

//--------------------------------------------------------------------------------------
HRESULT CDXUTDialogResourceManager::CreateFont9( UINT iFont )
{
    HRESULT hr = S_OK;

    DXUTFontNode* pFontNode = m_FontCache.GetAt( iFont );

    SAFE_RELEASE( pFontNode->Font9 );

    V_RETURN( D3DXCreateFont( m_pd3d9Device, pFontNode->Height, 0, pFontNode->Weight, 1, FALSE, DEFAULT_CHARSET,
                              OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                              pFontNode->FaceName, &pFontNode->Font9 ) );

    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialogResourceManager::CreateFont10( UINT iFont )
{
    HRESULT hr = S_OK;

    DXUTFontNode* pFontNode = m_FontCache.GetAt( iFont );

    SAFE_RELEASE( pFontNode->Font10 );

    V_RETURN( D3DX10CreateFont( m_pd3d10Device, pFontNode->Height, 0, pFontNode->Weight, 1, FALSE, DEFAULT_CHARSET,
                                OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                                pFontNode->FaceName, &pFontNode->Font10 ) );

    return S_OK;
}

ULONG CDXUTDialogResourceManager::GetTextureFilePath(PWSTR Buffer, ULONG BufferCount)
{
    ULONG Length;
    static WCHAR DefTextureFileName[] = L"TextureSrcData.dds";

    Length = GetTexturePath(Buffer, BufferCount);
    CopyStruct(Buffer + Length, DefTextureFileName, sizeof(DefTextureFileName));

    return Length + CONST_STRLEN(DefTextureFileName);
}

ULONG CDXUTDialogResourceManager::GetMeshFilePath(PWSTR Buffer, ULONG BufferCount)
{
    ULONG Length;
    static WCHAR DefMeshFileName[] = L"TextureSrcData.mesh";

    Length = GetTexturePath(Buffer, BufferCount);
    CopyStruct(Buffer + Length, DefMeshFileName, sizeof(DefMeshFileName));

    return Length + CONST_STRLEN(DefMeshFileName);
}

//-----------------------------------------------------------------------------
HRESULT
CDXUTDialogResourceManager::
DXUTCreateGUITextureFromInternalArray9(
    LPDIRECT3DDEVICE9   pd3dDevice,
    IDirect3DTexture9** ppTexture,
    D3DXIMAGE_INFO*     pInfo
)
{
    WCHAR TexturePath[MAX_NTPATH];

    GetTextureFilePath(TexturePath, countof(TexturePath));

    return D3DXCreateTextureFromFileExW(
                pd3dDevice,
                TexturePath,
                D3DX_DEFAULT,
                D3DX_DEFAULT,
                1,
                0,
                D3DFMT_UNKNOWN,
                D3DPOOL_MANAGED,
                D3DX_DEFAULT,
                D3DX_DEFAULT,
                0,
                pInfo,
                NULL,
                ppTexture
            );
}

//--------------------------------------------------------------------------------------
HRESULT
CDXUTDialogResourceManager::
DXUTCreateGUITextureFromInternalArray10(
    ID3D10Device*       pd3dDevice,
    ID3D10Texture2D**   ppTexture,
    D3DX10_IMAGE_INFO*  pInfo
)
{
    HRESULT hr;
    D3DX10_IMAGE_INFO SrcInfo;
    WCHAR TexturePath[MAX_NTPATH];

    GetTextureFilePath(TexturePath, countof(TexturePath));

    if( !pInfo )
    {
        D3DX10GetImageInfoFromFileW(
            TexturePath,
            NULL,
            &SrcInfo,
            NULL
        );
        pInfo = &SrcInfo;
    }

    ID3D10Resource *pRes;
    D3DX10_IMAGE_LOAD_INFO loadInfo;
    loadInfo.Width = D3DX10_DEFAULT;
    loadInfo.Height  = D3DX10_DEFAULT;
    loadInfo.Depth  = D3DX10_DEFAULT;
    loadInfo.FirstMipLevel = 0;
    loadInfo.MipLevels = 1;
    loadInfo.Usage = D3D10_USAGE_DEFAULT;
    loadInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE;
    loadInfo.CpuAccessFlags = 0;
    loadInfo.MiscFlags = 0;
    loadInfo.Format = MAKE_TYPELESS( pInfo->Format );
    loadInfo.Filter = D3DX10_FILTER_NONE;
    loadInfo.MipFilter = D3DX10_FILTER_NONE;
    loadInfo.pSrcInfo = pInfo;

    hr = D3DX10CreateTextureFromFileW(
            pd3dDevice,
            TexturePath,
            &loadInfo,
            NULL,
            &pRes,
            NULL
          );

    if( FAILED( hr ) )
        return hr;
    DXUT_SetDebugName( pRes, "DXUT" );

    hr = pRes->QueryInterface( __uuidof( ID3D10Texture2D ), (LPVOID*)ppTexture );
    SAFE_RELEASE( pRes );

    return S_OK;
}

//-----------------------------------------------------------------------------
HRESULT
CDXUTDialogResourceManager::
DXUTCreateArrowMeshFromInternalArray(
    LPDIRECT3DDEVICE9   pd3dDevice,
    ID3DXMesh**         ppMesh
)
{
    WCHAR MeshPath[MAX_NTPATH];

    GetMeshFilePath(MeshPath, countof(MeshPath));

    return D3DXLoadMeshFromXW(
                MeshPath,
                D3DXMESH_MANAGED,
                pd3dDevice,
                NULL,
                NULL,
                NULL,
                NULL,
                ppMesh
            );
}

//--------------------------------------------------------------------------------------
HRESULT CDXUTDialogResourceManager::CreateTexture9( UINT iTexture )
{
    HRESULT hr = S_OK;

    DXUTTextureNode* pTextureNode = m_TextureCache.GetAt( iTexture );
    D3DXIMAGE_INFO info;

    if( !pTextureNode->FileSource )
    {
        if (pTextureNode->ResourceID == DXUT_DEFAULT_RESOURCE && pTextureNode->ResourceModule == (HMODULE)DXUT_DEFAULT_RESOURCE)
        {
            hr = DXUTCreateGUITextureFromInternalArray9( m_pd3d9Device, &pTextureNode->Texture9, &info );
            if( FAILED( hr ) )
                return DXTRACE_ERR( L"D3DXCreateTextureFromFileInMemoryEx", hr );
            DXUT_SetDebugName( pTextureNode->Texture9, "DXUT GUI Texture" );
        }
        else
        {
            LPCWSTR pID = pTextureNode->ResourceID ? ( LPCWSTR )( size_t )pTextureNode->ResourceID :
                pTextureNode->Filename;

            // Create texture from resource
            hr = D3DXCreateTextureFromResourceEx(
                    m_pd3d9Device,
                    pTextureNode->ResourceModule,
                    pID,
                    D3DX_DEFAULT,
                    D3DX_DEFAULT,
                    1,
                    0,
                    D3DFMT_UNKNOWN,
                    D3DPOOL_MANAGED,
                    D3DX_DEFAULT,
                    D3DX_DEFAULT,
                    0,
                    &info,
                    NULL,
                    &pTextureNode->Texture9
                 );
            if(FAILED(hr))
                return DXTRACE_ERR(L"D3DXCreateTextureFromResourceEx", hr);
        }
    }
    else
    {
        // Make sure there's a texture to create
        if( pTextureNode->Filename[0] == 0 )
            return S_OK;

        WCHAR TexturePath[MAX_NTPATH];

        CopyMemory(TexturePath, m_TexturePath.Buffer, m_TexturePath.Length);
        wcscpy(TexturePath + m_TexturePath.Length / sizeof(WCHAR), pTextureNode->Filename);

        // Create texture from file
        hr = D3DXCreateTextureFromFileEx(
                m_pd3d9Device,
                TexturePath,
                D3DX_DEFAULT,
                D3DX_DEFAULT,
                1,
                0,
                D3DFMT_UNKNOWN,
                D3DPOOL_MANAGED,
                D3DX_DEFAULT,
                D3DX_DEFAULT,
                0,
                &info,
                NULL,
                &pTextureNode->Texture9
             );
        if(FAILED(hr))
        {
            return DXTRACE_ERR(L"D3DXCreateTextureFromFileEx", hr);
        }
    }

    // Store dimensions
    pTextureNode->Width = info.Width;
    pTextureNode->Height = info.Height;

    return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTDialogResourceManager::CreateTexture10( UINT iTexture )
{
    HRESULT hr = S_OK;

    DXUTTextureNode* pTextureNode = m_TextureCache.GetAt( iTexture );

    if( !pTextureNode->FileSource )
    {
        if (pTextureNode->ResourceID == DXUT_DEFAULT_RESOURCE && pTextureNode->ResourceModule == (HMODULE)DXUT_DEFAULT_RESOURCE)
        {
            hr = DXUTCreateGUITextureFromInternalArray10( m_pd3d10Device, &pTextureNode->Texture10, NULL );
            if( FAILED( hr ) )
                return DXTRACE_ERR( L"D3DX10CreateResourceFromFileInMemory", hr );
            DXUT_SetDebugName( pTextureNode->Texture10, "DXUT GUI Texture" );
        }
        else
        {
            LPCWSTR pID = pTextureNode->ResourceID ? ( LPCWSTR )( size_t )pTextureNode->ResourceID :
                pTextureNode->Filename;

            D3DX10_IMAGE_INFO SrcInfo;
            D3DX10GetImageInfoFromResource( NULL, pID, NULL, &SrcInfo, NULL );

            // Create texture from resource
            ID3D10Resource* pRes;
            D3DX10_IMAGE_LOAD_INFO loadInfo;
            loadInfo.Width = D3DX10_DEFAULT;
            loadInfo.Height = D3DX10_DEFAULT;
            loadInfo.Depth = D3DX10_DEFAULT;
            loadInfo.FirstMipLevel = 0;
            loadInfo.MipLevels = 1;
            loadInfo.Usage = D3D10_USAGE_DEFAULT;
            loadInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE;
            loadInfo.CpuAccessFlags = 0;
            loadInfo.MiscFlags = 0;
            loadInfo.Format = MAKE_TYPELESS( SrcInfo.Format );
            loadInfo.Filter = D3DX10_FILTER_NONE;
            loadInfo.MipFilter = D3DX10_FILTER_NONE;
            loadInfo.pSrcInfo = &SrcInfo;

            hr = D3DX10CreateTextureFromResource( m_pd3d10Device, pTextureNode->ResourceModule, pID, &loadInfo,
                                                  NULL, &pRes, NULL );
            if( FAILED( hr ) )
                return DXTRACE_ERR( L"D3DX10CreateResourceFromResource", hr );
            DXUT_SetDebugName( pRes, "DXUT GUI Texture" );
            hr = pRes->QueryInterface( __uuidof( ID3D10Texture2D ), ( LPVOID* )&pTextureNode->Texture10 );
            SAFE_RELEASE( pRes );
            if( FAILED( hr ) )
                return hr;
        }
    }
    else
    {
        // Make sure there's a texture to create
        if( pTextureNode->Filename[0] == 0 )
            return S_OK;

        D3DX10_IMAGE_INFO SrcInfo;
        D3DX10GetImageInfoFromFile( pTextureNode->Filename, NULL, &SrcInfo, NULL );

        // Create texture from file
        ID3D10Resource* pRes;
        D3DX10_IMAGE_LOAD_INFO loadInfo;
        loadInfo.Width = D3DX10_DEFAULT;
        loadInfo.Height = D3DX10_DEFAULT;
        loadInfo.Depth = D3DX10_DEFAULT;
        loadInfo.FirstMipLevel = 0;
        loadInfo.MipLevels = 1;
        loadInfo.Usage = D3D10_USAGE_DEFAULT;
        loadInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE;
        loadInfo.CpuAccessFlags = 0;
        loadInfo.MiscFlags = 0;
        loadInfo.Format = MAKE_TYPELESS( SrcInfo.Format );
        loadInfo.Filter = D3DX10_FILTER_NONE;
        loadInfo.MipFilter = D3DX10_FILTER_NONE;
        loadInfo.pSrcInfo = &SrcInfo;
        hr = D3DX10CreateTextureFromFile( m_pd3d10Device, pTextureNode->Filename, &loadInfo, NULL, &pRes, NULL );
        if( FAILED( hr ) )
        {
            return DXTRACE_ERR( L"D3DX10CreateResourceFromFileEx", hr );
        }
        DXUT_SetDebugName( pRes, "DXUT GUI Texture" );
        hr = pRes->QueryInterface( __uuidof( ID3D10Texture2D ), ( LPVOID* )&pTextureNode->Texture10 );
        SAFE_RELEASE( pRes );
        if( FAILED( hr ) )
            return hr;
    }

    // Store dimensions
    D3D10_TEXTURE2D_DESC desc;
    pTextureNode->Texture10->GetDesc( &desc );
    pTextureNode->Width = desc.Width;
    pTextureNode->Height = desc.Height;

    // Create resource view
    D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;
    SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
    SRVDesc.Format = MAKE_SRGB( desc.Format );
    SRVDesc.Texture2D.MipLevels = 1;
    SRVDesc.Texture2D.MostDetailedMip = 0;
    hr = m_pd3d10Device->CreateShaderResourceView( pTextureNode->Texture10, &SRVDesc, &pTextureNode->TexResView );
    DXUT_SetDebugName( pTextureNode->TexResView, "DXUT GUI Texture" );

    return hr;
}


//--------------------------------------------------------------------------------------
void CDXUTDialog::InitDefaultElements()
{
    SetFont( 0, L"Tahoma", 13, FW_NORMAL );

    RECT                rcTexture;
    CDXUTElement        Element;
    PDXUT_ELEMENT_INFO  ElementInfo;

    //-------------------------------------
    // Element for the caption
    //-------------------------------------

//    SetRect(&rcTexture, 17, 269, 241, 287);
    ElementInfo = m_CaptionElement;

    for (ULONG Count = ARRAYSIZE(m_CaptionElement); Count; ++ElementInfo, --Count)
        ElementInfo->Element.iTexture = DXUT_INVALID_TEXTURE_ID;

    ElementInfo = m_FrameElement;
    for (ULONG Count = ARRAYSIZE(m_FrameElement); Count; ++ElementInfo, --Count)
        ElementInfo->Element.iTexture = DXUT_INVALID_TEXTURE_ID;

    //-------------------------------------
    // CDXUTStatic
    //-------------------------------------
    Element.SetFont(0, ~0u, 0);
    Element.FontColor.States[ DXUT_STATE_DISABLED ] = D3DCOLOR_ARGB(200, 200, 200, 200);

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_STATIC, 0, &Element );


    //-------------------------------------
    // CDXUTButton - Button
    //-------------------------------------
    SetRect( &rcTexture, 0, 0, 136, 54 );
    Element.SetTexture( 0, &rcTexture );
    Element.SetFont( 0 );
    Element.TextureColor.States[DXUT_STATE_NORMAL]  = D3DCOLOR_ARGB( 150, 255, 255, 255 );
    Element.TextureColor.States[DXUT_STATE_PRESSED] = D3DCOLOR_ARGB( 200, 255, 255, 255 );
    Element.FontColor.States[DXUT_STATE_MOUSEOVER]  = D3DCOLOR_ARGB( 255, 0, 0, 0 );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_BUTTON, 0, &Element );


    //-------------------------------------
    // CDXUTButton - Fill layer
    //-------------------------------------
    SetRect( &rcTexture, 136, 0, 252, 54 );
    Element.SetTexture( 0, &rcTexture, D3DCOLOR_ARGB( 0, 255, 255, 255 ) );
    Element.TextureColor.States[ DXUT_STATE_MOUSEOVER ] = D3DCOLOR_ARGB( 160, 255, 255, 255 );
    Element.TextureColor.States[ DXUT_STATE_PRESSED ] = D3DCOLOR_ARGB( 60, 0, 0, 0 );
    Element.TextureColor.States[ DXUT_STATE_FOCUS ] = D3DCOLOR_ARGB( 30, 255, 255, 255 );


    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_BUTTON, 1, &Element );


    //-------------------------------------
    // CDXUTCheckBox - Box
    //-------------------------------------
    SetRect( &rcTexture, 0, 54, 27, 81 );
    Element.SetTexture( 0, &rcTexture );
    Element.SetFont( 0, D3DCOLOR_ARGB( 255, 255, 255, 255 ), DT_LEFT | DT_VCENTER );
    Element.FontColor.States[ DXUT_STATE_DISABLED ] = D3DCOLOR_ARGB( 200, 200, 200, 200 );
    Element.TextureColor.States[ DXUT_STATE_NORMAL ] = D3DCOLOR_ARGB( 150, 255, 255, 255 );
    Element.TextureColor.States[ DXUT_STATE_FOCUS ] = D3DCOLOR_ARGB( 200, 255, 255, 255 );
    Element.TextureColor.States[ DXUT_STATE_PRESSED ] = D3DCOLOR_ARGB( 255, 255, 255, 255 );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_CHECKBOX, 0, &Element );


    //-------------------------------------
    // CDXUTCheckBox - Check
    //-------------------------------------
    SetRect( &rcTexture, 27, 54, 54, 81 );
    Element.SetTexture( 0, &rcTexture );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_CHECKBOX, 1, &Element );


    //-------------------------------------
    // CDXUTRadioButton - Box
    //-------------------------------------
    SetRect( &rcTexture, 54, 54, 81, 81 );
    Element.SetTexture( 0, &rcTexture );
    Element.SetFont( 0, D3DCOLOR_ARGB( 255, 255, 255, 255 ), DT_LEFT | DT_VCENTER );
    Element.FontColor.States[ DXUT_STATE_DISABLED ] = D3DCOLOR_ARGB( 200, 200, 200, 200 );
    Element.TextureColor.States[ DXUT_STATE_NORMAL ] = D3DCOLOR_ARGB( 150, 255, 255, 255 );
    Element.TextureColor.States[ DXUT_STATE_FOCUS ] = D3DCOLOR_ARGB( 200, 255, 255, 255 );
    Element.TextureColor.States[ DXUT_STATE_PRESSED ] = D3DCOLOR_ARGB( 255, 255, 255, 255 );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_RADIOBUTTON, 0, &Element );


    //-------------------------------------
    // CDXUTRadioButton - Check
    //-------------------------------------
    SetRect( &rcTexture, 81, 54, 108, 81 );
    Element.SetTexture( 0, &rcTexture );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_RADIOBUTTON, 1, &Element );


    //-------------------------------------
    // CDXUTComboBox - Main
    //-------------------------------------
    SetRect( &rcTexture, 7, 81, 247, 123 );
    Element.SetTexture( 0, &rcTexture );
    Element.SetFont( 0 );
    Element.TextureColor.States[ DXUT_STATE_NORMAL ] = D3DCOLOR_ARGB( 150, 200, 200, 200 );
    Element.TextureColor.States[ DXUT_STATE_FOCUS ] = D3DCOLOR_ARGB( 170, 230, 230, 230 );
    Element.TextureColor.States[ DXUT_STATE_DISABLED ] = D3DCOLOR_ARGB( 70, 200, 200, 200 );
    Element.FontColor.States[ DXUT_STATE_MOUSEOVER ] = D3DCOLOR_ARGB( 255, 0, 0, 0 );
    Element.FontColor.States[ DXUT_STATE_PRESSED ] = D3DCOLOR_ARGB( 255, 0, 0, 0 );
    Element.FontColor.States[ DXUT_STATE_DISABLED ] = D3DCOLOR_ARGB( 200, 200, 200, 200 );


    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_COMBOBOX, 0, &Element );


    //-------------------------------------
    // CDXUTComboBox - Button
    //-------------------------------------
    SetRect( &rcTexture, 98, 189, 151, 238 );
    Element.SetTexture( 0, &rcTexture );
    Element.TextureColor.States[ DXUT_STATE_NORMAL ] = D3DCOLOR_ARGB( 150, 255, 255, 255 );
    Element.TextureColor.States[ DXUT_STATE_PRESSED ] = D3DCOLOR_ARGB( 255, 150, 150, 150 );
    Element.TextureColor.States[ DXUT_STATE_FOCUS ] = D3DCOLOR_ARGB( 200, 255, 255, 255 );
    Element.TextureColor.States[ DXUT_STATE_DISABLED ] = D3DCOLOR_ARGB( 70, 255, 255, 255 );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_COMBOBOX, 1, &Element );


    //-------------------------------------
    // CDXUTComboBox - Dropdown
    //-------------------------------------
    SetRect( &rcTexture, 13, 123, 241, 160 );
    Element.SetTexture( 0, &rcTexture );
    Element.SetFont( 0, D3DCOLOR_ARGB( 255, 0, 0, 0 ), DT_LEFT | DT_TOP );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_COMBOBOX, 2, &Element );


    //-------------------------------------
    // CDXUTComboBox - Selection
    //-------------------------------------
    SetRect( &rcTexture, 12, 163, 239, 183 );
    Element.SetTexture( 0, &rcTexture );
    Element.SetFont( 0, D3DCOLOR_ARGB( 255, 255, 255, 255 ), DT_LEFT | DT_TOP );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_COMBOBOX, 3, &Element );


    //-------------------------------------
    // CDXUTSlider - Track
    //-------------------------------------
    SetRect( &rcTexture, 1, 187, 93, 228 );
    Element.SetTexture( 0, &rcTexture );
    Element.TextureColor.States[ DXUT_STATE_NORMAL ] = D3DCOLOR_ARGB( 150, 255, 255, 255 );
    Element.TextureColor.States[ DXUT_STATE_FOCUS ] = D3DCOLOR_ARGB( 200, 255, 255, 255 );
    Element.TextureColor.States[ DXUT_STATE_DISABLED ] = D3DCOLOR_ARGB( 70, 255, 255, 255 );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_SLIDER, 0, &Element );

    //-------------------------------------
    // CDXUTSlider - Button
    //-------------------------------------
    SetRect( &rcTexture, 151, 193, 192, 234 );
    Element.SetTexture( 0, &rcTexture );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_SLIDER, 1, &Element );

    //-------------------------------------
    // CDXUTScrollBar - Track
    //-------------------------------------
    int nScrollBarStartX = 196;
    int nScrollBarStartY = 191;
    SetRect( &rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 21, nScrollBarStartX + 22, nScrollBarStartY + 32 );
    Element.SetTexture( 0, &rcTexture );
    Element.TextureColor.States[ DXUT_STATE_DISABLED ] = D3DCOLOR_ARGB( 255, 200, 200, 200 );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_SCROLLBAR, 0, &Element );

    //-------------------------------------
    // CDXUTScrollBar - Up Arrow
    //-------------------------------------
    SetRect( &rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 1, nScrollBarStartX + 22, nScrollBarStartY + 21 );
    Element.SetTexture( 0, &rcTexture );
    Element.TextureColor.States[ DXUT_STATE_DISABLED ] = D3DCOLOR_ARGB( 255, 200, 200, 200 );


    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_SCROLLBAR, 1, &Element );

    //-------------------------------------
    // CDXUTScrollBar - Down Arrow
    //-------------------------------------
    SetRect( &rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 32, nScrollBarStartX + 22, nScrollBarStartY + 53 );
    Element.SetTexture( 0, &rcTexture );
    Element.TextureColor.States[ DXUT_STATE_DISABLED ] = D3DCOLOR_ARGB( 255, 200, 200, 200 );


    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_SCROLLBAR, 2, &Element );

    //-------------------------------------
    // CDXUTScrollBar - Button
    //-------------------------------------
    SetRect( &rcTexture, 220, 192, 238, 234 );
    Element.SetTexture( 0, &rcTexture );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_SCROLLBAR, 3, &Element );


    //-------------------------------------
    // CDXUTEditBox
    //-------------------------------------
    // Element assignment:
    //   0 - text area
    //   1 - top left border
    //   2 - top border
    //   3 - top right border
    //   4 - left border
    //   5 - right border
    //   6 - lower left border
    //   7 - lower border
    //   8 - lower right border

    Element.SetFont( 0, D3DCOLOR_ARGB( 255, 0, 0, 0 ), DT_LEFT | DT_TOP );

    // Assign the style
    SetRect( &rcTexture, 14, 90, 241, 113 );
    Element.SetTexture( 0, &rcTexture );
    SetDefaultElement( DXUT_CONTROL_EDITBOX, 0, &Element );
    SetRect( &rcTexture, 8, 82, 14, 90 );
    Element.SetTexture( 0, &rcTexture );
    SetDefaultElement( DXUT_CONTROL_EDITBOX, 1, &Element );
    SetRect( &rcTexture, 14, 82, 241, 90 );
    Element.SetTexture( 0, &rcTexture );
    SetDefaultElement( DXUT_CONTROL_EDITBOX, 2, &Element );
    SetRect( &rcTexture, 241, 82, 246, 90 );
    Element.SetTexture( 0, &rcTexture );
    SetDefaultElement( DXUT_CONTROL_EDITBOX, 3, &Element );
    SetRect( &rcTexture, 8, 90, 14, 113 );
    Element.SetTexture( 0, &rcTexture );
    SetDefaultElement( DXUT_CONTROL_EDITBOX, 4, &Element );
    SetRect( &rcTexture, 241, 90, 246, 113 );
    Element.SetTexture( 0, &rcTexture );
    SetDefaultElement( DXUT_CONTROL_EDITBOX, 5, &Element );
    SetRect( &rcTexture, 8, 113, 14, 121 );
    Element.SetTexture( 0, &rcTexture );
    SetDefaultElement( DXUT_CONTROL_EDITBOX, 6, &Element );
    SetRect( &rcTexture, 14, 113, 241, 121 );
    Element.SetTexture( 0, &rcTexture );
    SetDefaultElement( DXUT_CONTROL_EDITBOX, 7, &Element );
    SetRect( &rcTexture, 241, 113, 246, 121 );
    Element.SetTexture( 0, &rcTexture );
    SetDefaultElement( DXUT_CONTROL_EDITBOX, 8, &Element );

    //-------------------------------------
    // CDXUTListBox - Main
    //-------------------------------------
    SetRect( &rcTexture, 13, 123, 241, 160 );
    Element.SetTexture( 0, &rcTexture );
    Element.SetFont( 0, D3DCOLOR_ARGB( 255, 0, 0, 0 ), DT_LEFT | DT_TOP );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_LISTBOX, 0, &Element );

    //-------------------------------------
    // CDXUTListBox - Selection
    //-------------------------------------

    SetRect( &rcTexture, 16, 166, 240, 183 );
    Element.SetTexture( 0, &rcTexture );
    Element.SetFont( 0, D3DCOLOR_ARGB( 255, 255, 255, 255 ), DT_LEFT | DT_TOP );

    // Assign the Element
    SetDefaultElement( DXUT_CONTROL_LISTBOX, 1, &Element );
}



//--------------------------------------------------------------------------------------
// CDXUTControl class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
CDXUTControl::CDXUTControl( CDXUTDialog* pDialog )
{
    m_Type = DXUT_CONTROL_BUTTON;
    m_pDialog = pDialog;
    m_ID = 0;
    m_ControlListIndex = 0;
    m_pUserData = NULL;

    m_bEnabled = TRUE;
    m_bVisible = TRUE;
    m_bMouseOver = FALSE;
    m_bHasFocus = FALSE;
    m_bIsDefault = FALSE;

//    m_pDialog = NULL;

    m_x = 0;
    m_y = 0;
    m_width = 0;
    m_height = 0;

    ZeroMemory( &m_rcBoundingBox, sizeof( m_rcBoundingBox ) );
}


CDXUTControl::~CDXUTControl()
{
    for( ULONG i = 0; i < m_Elements.GetSize(); ++i )
    {
        delete m_Elements[i];
    }
    m_Elements.RemoveAll();
}


//--------------------------------------------------------------------------------------
void CDXUTControl::SetTextColor( D3DCOLOR Color )
{
    CDXUTElement* pElement = m_Elements.GetAt( 0 );

    if( pElement )
        pElement->FontColor.States[DXUT_STATE_NORMAL] = Color;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTControl::SetElement( UINT iElement, CDXUTElement* pElement )
{
    HRESULT hr = S_OK;

    if( pElement == NULL )
        return E_INVALIDARG;

    // Make certain the array is this large
    for( UINT i = m_Elements.GetSize(); i <= iElement; i++ )
    {
        CDXUTElement* pNewElement = new CDXUTElement();
        if (pNewElement == NULL)
            return E_OUTOFMEMORY;

        hr = m_Elements.Add( pNewElement );
        if (FAILED(hr))
        {
            delete pNewElement;
            return hr;
        }
    }

    // Update the data
    CDXUTElement* pCurElement = m_Elements.GetAt( iElement );
    *pCurElement = *pElement;

    return S_OK;
}


//--------------------------------------------------------------------------------------
void CDXUTControl::Refresh()
{
    m_bMouseOver = FALSE;
    m_bHasFocus = FALSE;

    for( ULONG i = 0; i < m_Elements.GetSize(); i++ )
    {
        CDXUTElement* pElement = m_Elements.GetAt( i );
        pElement->Refresh();
    }
}


//--------------------------------------------------------------------------------------
void CDXUTControl::UpdateRects()
{
    SetRect( &m_rcBoundingBox, m_x, m_y, m_x + m_width, m_y + m_height );
}


//--------------------------------------------------------------------------------------
// CDXUTStatic class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
CDXUTStatic::CDXUTStatic( CDXUTDialog* pDialog )
{
    m_Type = DXUT_CONTROL_STATIC;
    m_pDialog = pDialog;

    RtlInitEmptyUnicodeString(&m_ButtonText, NULL, 0);

    for( ULONG i = 0; i < m_Elements.GetSize(); i++ )
    {
        CDXUTElement* pElement = m_Elements.GetAt( i );
        SAFE_DELETE( pElement );
    }

    m_Elements.RemoveAll();
}


//--------------------------------------------------------------------------------------
void CDXUTStatic::Render( FLOAT fElapsedTime )
{
    if( m_bVisible == FALSE )
        return;

    DXUT_CONTROL_STATE iState = DXUT_STATE_NORMAL;

    if( m_bEnabled == FALSE )
        iState = DXUT_STATE_DISABLED;

    CDXUTElement* pElement = m_Elements.GetAt( 0 );

    pElement->FontColor.Blend( iState, fElapsedTime );

    m_pDialog->DrawText(GetText(), pElement, &m_rcBoundingBox, TRUE);
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTStatic::GetTextCopy(PWSTR Buffer, UINT BufferCount)
{
    if (BufferCount == 0 || Buffer == NULL)
        return E_INVALIDARG;

    if (GetText() == NULL)
    {
        Buffer[0] = 0;
        return S_OK;
    }

    if (BufferCount * sizeof(WCHAR) <= m_ButtonText.Length)
        return E_OUTOFMEMORY;

    CopyMemory(Buffer, m_ButtonText.Buffer, m_ButtonText.Length);
    Buffer[m_ButtonText.Length] = 0;

    return S_OK;
}

//--------------------------------------------------------------------------------------
HRESULT CDXUTStatic::SetText(PCWSTR Text)
{
    return RtlSetUnicodeString(&m_ButtonText, Text);
}


//--------------------------------------------------------------------------------------
// CDXUTButton class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
CDXUTButton::CDXUTButton( CDXUTDialog* pDialog )
{
    m_Type = DXUT_CONTROL_BUTTON;
    m_pDialog = pDialog;

    m_bPressed = FALSE;
    m_nHotkey = 0;
    m_Modifiers = 0;
}

//--------------------------------------------------------------------------------------
BOOL CDXUTButton::HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    switch( Message )
    {
        case WM_KEYDOWN:
        {
            switch( wParam )
            {
                case VK_SPACE:
                    m_bPressed = TRUE;
                    return TRUE;
            }
        }

        case WM_KEYUP:
        {
            switch( wParam )
            {
                case VK_SPACE:
                    if( m_bPressed == TRUE )
                    {
                        m_bPressed = FALSE;
                        m_pDialog->SendEvent( EVENT_BUTTON_CLICKED, TRUE, this );
                    }
                    return TRUE;
            }
        }
    }
    return FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTButton::HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    switch( Message )
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            {
                if( ContainsPoint( pt ) )
                {
                    // Pressed while inside the control
                    m_bPressed = TRUE;
                    SetCapture( DXUTGetHWND() );

                    if( !m_bHasFocus )
                        m_pDialog->RequestFocus( this );

                    return TRUE;
                }

                break;
            }

        case WM_LBUTTONUP:
        {
            if( m_bPressed )
            {
                m_bPressed = FALSE;
                ReleaseCapture();

                if( !m_pDialog->m_bKeyboardInput )
                    m_pDialog->ClearFocus();

                // Button click
                if( ContainsPoint( pt ) )
                    m_pDialog->SendEvent( EVENT_BUTTON_CLICKED, TRUE, this );

                return TRUE;
            }

            break;
        }
    }

    return FALSE;
}

//--------------------------------------------------------------------------------------
void CDXUTButton::Render(FLOAT ElapsedTime)
{
    int nOffsetX = 0;
    int nOffsetY = 0;

    DXUT_CONTROL_STATE iState = DXUT_STATE_NORMAL;

    if( m_bVisible == FALSE )
    {
        iState = DXUT_STATE_HIDDEN;
    }
    else if( m_bEnabled == FALSE )
    {
        iState = DXUT_STATE_DISABLED;
    }
    else if( m_bPressed )
    {
        iState = DXUT_STATE_PRESSED;

        nOffsetX = 1;
        nOffsetY = 2;
    }
    else if( m_bMouseOver )
    {
        iState = DXUT_STATE_MOUSEOVER;

        nOffsetX = -1;
        nOffsetY = -2;
    }
    else if( m_bHasFocus )
    {
        iState = DXUT_STATE_FOCUS;
    }

    // Background fill layer
    CDXUTElement* pElement = m_Elements.GetAt( 0 );

    FLOAT fBlendRate = ( iState == DXUT_STATE_PRESSED ) ? 0.0f : 0.8f;

    RECT rcWindow = m_rcBoundingBox;
    OffsetRect( &rcWindow, nOffsetX, nOffsetY );

    // Blend current color
    pElement->TextureColor.Blend( iState, ElapsedTime, fBlendRate );
    pElement->FontColor.Blend( iState, ElapsedTime, fBlendRate );

    m_pDialog->DrawSprite( pElement, &rcWindow, DXUT_FAR_BUTTON_DEPTH );
    m_pDialog->DrawText( GetText(), pElement, &rcWindow );

    // Main button
    pElement = m_Elements.GetAt( 1 );

    // Blend current color
    pElement->TextureColor.Blend( iState, ElapsedTime, fBlendRate );
    pElement->FontColor.Blend( iState, ElapsedTime, fBlendRate );

    m_pDialog->DrawSprite( pElement, &rcWindow, DXUT_NEAR_BUTTON_DEPTH );
    m_pDialog->DrawText( GetText(), pElement, &rcWindow );
}



//--------------------------------------------------------------------------------------
// CDXUTCheckBox class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
CDXUTCheckBox::CDXUTCheckBox( CDXUTDialog* pDialog )
{
    m_Type = DXUT_CONTROL_CHECKBOX;
    m_pDialog = pDialog;

    m_bChecked = FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTCheckBox::HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    switch( Message )
    {
        case WM_KEYDOWN:
        {
            switch( wParam )
            {
                case VK_SPACE:
                    m_bPressed = TRUE;
                    return TRUE;
            }
        }

        case WM_KEYUP:
        {
            switch( wParam )
            {
                case VK_SPACE:
                    if( m_bPressed == TRUE )
                    {
                        m_bPressed = FALSE;
                        SetCheckedInternal( !m_bChecked, TRUE );
                    }
                    return TRUE;
            }
        }
    }
    return FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTCheckBox::HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    switch( Message )
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            {
                if( ContainsPoint( pt ) )
                {
                    // Pressed while inside the control
                    m_bPressed = TRUE;
                    SetCapture( DXUTGetHWND() );

                    if( !m_bHasFocus )
                        m_pDialog->RequestFocus( this );

                    return TRUE;
                }

                break;
            }

        case WM_LBUTTONUP:
        {
            if( m_bPressed )
            {
                m_bPressed = FALSE;
                ReleaseCapture();

                // Button click
                if( ContainsPoint( pt ) )
                    SetCheckedInternal( !m_bChecked, TRUE );

                return TRUE;
            }

            break;
        }
    };

    return FALSE;
}


//--------------------------------------------------------------------------------------
void CDXUTCheckBox::SetCheckedInternal( BOOL bChecked, BOOL bFromInput )
{
    m_bChecked = bChecked;

    m_pDialog->SendEvent( EVENT_CHECKBOX_CHANGED, bFromInput, this );
}


//--------------------------------------------------------------------------------------
BOOL CDXUTCheckBox::ContainsPoint( POINT pt )
{
    return ( PtInRect( &m_rcBoundingBox, pt ) ||
             PtInRect( &m_rcButton, pt ) );
}



//--------------------------------------------------------------------------------------
void CDXUTCheckBox::UpdateRects()
{
    CDXUTButton::UpdateRects();

    m_rcButton       = m_rcBoundingBox;
    m_rcButton.right = m_rcButton.left + RectHeight(m_rcButton);

    m_rcText        = m_rcBoundingBox;
    m_rcText.left  += (int)(1.25f * RectWidth(m_rcButton));
}

//--------------------------------------------------------------------------------------
void CDXUTCheckBox::Render( FLOAT fElapsedTime )
{
    DXUT_CONTROL_STATE iState = DXUT_STATE_NORMAL;

    if( m_bVisible == FALSE )
        iState = DXUT_STATE_HIDDEN;
    else if( m_bEnabled == FALSE )
        iState = DXUT_STATE_DISABLED;
    else if( m_bPressed )
        iState = DXUT_STATE_PRESSED;
    else if( m_bMouseOver )
        iState = DXUT_STATE_MOUSEOVER;
    else if( m_bHasFocus )
        iState = DXUT_STATE_FOCUS;

    CDXUTElement* pElement = m_Elements.GetAt( 0 );

    FLOAT fBlendRate = ( iState == DXUT_STATE_PRESSED ) ? 0.0f : 0.8f;

    pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
    pElement->FontColor.Blend( iState, fElapsedTime, fBlendRate );

    m_pDialog->DrawSprite( pElement, &m_rcButton, DXUT_NEAR_BUTTON_DEPTH );
    m_pDialog->DrawText( GetText(), pElement, &m_rcText, TRUE );

    if( !m_bChecked )
        iState = DXUT_STATE_HIDDEN;

    pElement = m_Elements.GetAt( 1 );

    pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
    m_pDialog->DrawSprite( pElement, &m_rcButton, DXUT_FAR_BUTTON_DEPTH );
}




//--------------------------------------------------------------------------------------
// CDXUTRadioButton class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
CDXUTRadioButton::CDXUTRadioButton( CDXUTDialog* pDialog )
{
    m_Type = DXUT_CONTROL_RADIOBUTTON;
    m_pDialog = pDialog;
}



//--------------------------------------------------------------------------------------
BOOL CDXUTRadioButton::HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    switch( Message )
    {
        case WM_KEYDOWN:
        {
            switch( wParam )
            {
                case VK_SPACE:
                    m_bPressed = TRUE;
                    return TRUE;
            }
        }

        case WM_KEYUP:
        {
            switch( wParam )
            {
                case VK_SPACE:
                    if( m_bPressed == TRUE )
                    {
                        m_bPressed = FALSE;

                        m_pDialog->ClearRadioButtonGroup( m_nButtonGroup );
                        m_bChecked = !m_bChecked;

                        m_pDialog->SendEvent( EVENT_RADIOBUTTON_CHANGED, TRUE, this );
                    }
                    return TRUE;
            }
        }
    }
    return FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTRadioButton::HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    switch( Message )
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            {
                if( ContainsPoint( pt ) )
                {
                    // Pressed while inside the control
                    m_bPressed = TRUE;
                    SetCapture( DXUTGetHWND() );

                    if( !m_bHasFocus )
                        m_pDialog->RequestFocus( this );

                    return TRUE;
                }

                break;
            }

        case WM_LBUTTONUP:
        {
            if( m_bPressed )
            {
                m_bPressed = FALSE;
                ReleaseCapture();

                // Button click
                if( ContainsPoint( pt ) )
                {
                    m_pDialog->ClearRadioButtonGroup( m_nButtonGroup );
                    m_bChecked = !m_bChecked;

                    m_pDialog->SendEvent( EVENT_RADIOBUTTON_CHANGED, TRUE, this );
                }

                return TRUE;
            }

            break;
        }
    };

    return FALSE;
}

//--------------------------------------------------------------------------------------
void CDXUTRadioButton::SetCheckedInternal( BOOL bChecked, BOOL bClearGroup, BOOL bFromInput )
{
    if( bChecked && bClearGroup )
        m_pDialog->ClearRadioButtonGroup( m_nButtonGroup );

    m_bChecked = bChecked;
    m_pDialog->SendEvent( EVENT_RADIOBUTTON_CHANGED, bFromInput, this );
}




//--------------------------------------------------------------------------------------
// CDXUTComboBox class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
CDXUTComboBox::CDXUTComboBox( CDXUTDialog* pDialog ) : m_ScrollBar( pDialog )
{
    m_Type = DXUT_CONTROL_COMBOBOX;
    m_pDialog = pDialog;

    m_nDropHeight = 100;

    m_nSBWidth = 16;
    m_bOpened = FALSE;
    m_Selected = ~0u;
    m_Focused = ~0u;
}


//--------------------------------------------------------------------------------------
CDXUTComboBox::~CDXUTComboBox()
{
    RemoveAllItems();
}


//--------------------------------------------------------------------------------------
void CDXUTComboBox::SetTextColor( D3DCOLOR Color )
{
    CDXUTElement* pElement = m_Elements.GetAt( 0 );

    if( pElement )
        pElement->FontColor.States[DXUT_STATE_NORMAL] = Color;

    pElement = m_Elements.GetAt( 2 );

    if( pElement )
        pElement->FontColor.States[DXUT_STATE_NORMAL] = Color;
}


//--------------------------------------------------------------------------------------
void CDXUTComboBox::UpdateRects()
{

    CDXUTButton::UpdateRects();

    m_rcButton = m_rcBoundingBox;
    m_rcButton.left = m_rcButton.right - RectHeight( m_rcButton );

    m_rcText = m_rcBoundingBox;
    m_rcText.right = m_rcButton.left;

    m_rcDropdown = m_rcText;
    OffsetRect( &m_rcDropdown, 0, ( int )( 0.90f * RectHeight( m_rcText ) ) );
    m_rcDropdown.bottom += m_nDropHeight;
    m_rcDropdown.right -= m_nSBWidth;

    m_rcDropdownText = m_rcDropdown;
    m_rcDropdownText.left += ( int )( 0.1f * RectWidth( m_rcDropdown ) );
    m_rcDropdownText.right -= ( int )( 0.1f * RectWidth( m_rcDropdown ) );
    m_rcDropdownText.top += ( int )( 0.1f * RectHeight( m_rcDropdown ) );
    m_rcDropdownText.bottom -= ( int )( 0.1f * RectHeight( m_rcDropdown ) );

    // Update the scrollbar's rects
    m_ScrollBar.SetLocation( m_rcDropdown.right, m_rcDropdown.top + 2 );
    m_ScrollBar.SetSize( m_nSBWidth, RectHeight( m_rcDropdown ) - 2 );
    DXUTFontNode* pFontNode = m_pDialog->GetManager()->GetFontNode( m_Elements.GetAt( 2 )->iFont );
    if( pFontNode && pFontNode->Height )
    {
        m_ScrollBar.SetPageSize( RectHeight( m_rcDropdownText ) / pFontNode->Height );

        // The selected item may have been scrolled off the page.
        // Ensure that it is in page again.
        m_ScrollBar.ShowItem( m_Selected );
    }
}


//--------------------------------------------------------------------------------------
void CDXUTComboBox::OnFocusOut()
{
    CDXUTButton::OnFocusOut();

    m_bOpened = FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTComboBox::HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    const DWORD REPEAT_MASK = ( 0x40000000 );

    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    // Let the scroll bar have a chance to handle it first
    if( m_ScrollBar.HandleKeyboard(hWnd, Message, wParam, lParam))
        return TRUE;

    switch( Message )
    {
        case WM_KEYDOWN:
        {
            switch( wParam )
            {
                case VK_RETURN:
                    if( m_bOpened )
                    {
                        if( m_Selected != m_Focused )
                        {
                            m_Selected = m_Focused;
                            m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, TRUE, this );
                        }
                        m_bOpened = FALSE;

                        if( !m_pDialog->m_bKeyboardInput )
                            m_pDialog->ClearFocus();

                        return TRUE;
                    }
                    break;

                case VK_F4:
                    // Filter out auto-repeats
                    if( lParam & REPEAT_MASK )
                        return TRUE;

                    m_bOpened = !m_bOpened;

                    if( !m_bOpened )
                    {
                        m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, TRUE, this );

                        if( !m_pDialog->m_bKeyboardInput )
                            m_pDialog->ClearFocus();
                    }

                    return TRUE;

                case VK_LEFT:
                case VK_UP:
                    if( m_Focused > 0 )
                    {
                        m_Focused--;
                        m_Selected = m_Focused;

                        if( !m_bOpened )
                            m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, TRUE, this );
                    }

                    return TRUE;

                case VK_RIGHT:
                case VK_DOWN:
                    if( m_Focused + 1 < ( int )GetNumItems() )
                    {
                        m_Focused++;
                        m_Selected = m_Focused;

                        if( !m_bOpened )
                            m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, TRUE, this );
                    }

                    return TRUE;
            }
            break;
        }
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTComboBox::HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    // Let the scroll bar handle it first.
    if( m_ScrollBar.HandleMouse(hWnd, Message, pt, wParam, lParam))
        return TRUE;

    switch( Message )
    {
        case WM_MOUSEMOVE:
        {
            if( m_bOpened && PtInRect( &m_rcDropdown, pt ) )
            {
                // Determine which item has been selected
                for( ULONG i = 0; i < m_Items.GetSize(); i++ )
                {
                    DXUTComboBoxItem* pItem = m_Items.GetAt( i );
                    if( pItem->bVisible &&
                        PtInRect( &pItem->rcActive, pt ) )
                    {
                        m_Focused = i;
                    }
                }
                return TRUE;
            }
            break;
        }

        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            {
                if( ContainsPoint( pt ) )
                {
                    // Pressed while inside the control
                    m_bPressed = TRUE;
                    SetCapture( DXUTGetHWND() );

                    if( !m_bHasFocus )
                        m_pDialog->RequestFocus( this );

                    // Toggle dropdown
                    if( m_bHasFocus )
                    {
                        m_bOpened = !m_bOpened;

                        if( !m_bOpened )
                        {
                            if( !m_pDialog->m_bKeyboardInput )
                                m_pDialog->ClearFocus();
                        }
                    }

                    return TRUE;
                }

                // Perhaps this click is within the dropdown
                if( m_bOpened && PtInRect( &m_rcDropdown, pt ) )
                {
                    // Determine which item has been selected
                    for( ULONG i = m_ScrollBar.GetTrackPos(); i < m_Items.GetSize(); i++ )
                    {
                        DXUTComboBoxItem* pItem = m_Items.GetAt( i );
                        if( pItem->bVisible &&
                            PtInRect( &pItem->rcActive, pt ) )
                        {
                            m_Focused = m_Selected = i;
                            m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, TRUE, this );
                            m_bOpened = FALSE;

                            if( !m_pDialog->m_bKeyboardInput )
                                m_pDialog->ClearFocus();

                            break;
                        }
                    }

                    return TRUE;
                }

                // Mouse click not on main control or in dropdown, fire an event if needed
                if( m_bOpened )
                {
                    m_Focused = m_Selected;

                    m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, TRUE, this );
                    m_bOpened = FALSE;
                }

                // Make sure the control is no longer in a pressed state
                m_bPressed = FALSE;

                // Release focus if appropriate
                if( !m_pDialog->m_bKeyboardInput )
                {
                    m_pDialog->ClearFocus();
                }

                break;
            }

        case WM_LBUTTONUP:
        {
            if( m_bPressed && ContainsPoint( pt ) )
            {
                // Button click
                m_bPressed = FALSE;
                ReleaseCapture();
                return TRUE;
            }

            break;
        }

        case WM_MOUSEWHEEL:
        {
            int zDelta = ( short )HIWORD( wParam ) / WHEEL_DELTA;
            if( m_bOpened )
            {
                UINT uLines;
                SystemParametersInfo( SPI_GETWHEELSCROLLLINES, 0, &uLines, 0 );
                m_ScrollBar.Scroll( -zDelta * uLines );
            }
            else
            {
                if( zDelta > 0 )
                {
                    if( m_Focused > 0 )
                    {
                        m_Focused--;
                        m_Selected = m_Focused;

                        if( !m_bOpened )
                            m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, TRUE, this );
                    }
                }
                else
                {
                    if( m_Focused + 1 < ( int )GetNumItems() )
                    {
                        m_Focused++;
                        m_Selected = m_Focused;

                        if( !m_bOpened )
                            m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, TRUE, this );
                    }
                }
            }
            return TRUE;
        }
    };

    return FALSE;
}


//--------------------------------------------------------------------------------------
void CDXUTComboBox::OnHotkey()
{
    if( m_bOpened )
        return;

    if( m_Selected == -1 )
        return;

    if( m_pDialog->IsKeyboardInputEnabled() )
        m_pDialog->RequestFocus( this );

    m_Selected++;

    if( m_Selected >= ( int )m_Items.GetSize() )
        m_Selected = 0;

    m_Focused = m_Selected;
    m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, TRUE, this );
}


//--------------------------------------------------------------------------------------
void CDXUTComboBox::Render( FLOAT fElapsedTime )
{
    DXUT_CONTROL_STATE iState = DXUT_STATE_NORMAL;

    if( !m_bOpened )
        iState = DXUT_STATE_HIDDEN;

    // Dropdown box
    CDXUTElement* pElement = m_Elements.GetAt( 2 );

    // If we have not initialized the scroll bar page size,
    // do that now.
    static BOOL bSBInit;
    if( !bSBInit )
    {
        // Update the page size of the scroll bar
        if( m_pDialog->GetManager()->GetFontNode( pElement->iFont )->Height )
            m_ScrollBar.SetPageSize( RectHeight( m_rcDropdownText ) /
                                     m_pDialog->GetManager()->GetFontNode( pElement->iFont )->Height );
        else
            m_ScrollBar.SetPageSize( RectHeight( m_rcDropdownText ) );
        bSBInit = TRUE;
    }

    // Scroll bar
    if( m_bOpened )
        m_ScrollBar.Render( fElapsedTime );

    // Blend current color
    pElement->TextureColor.Blend( iState, fElapsedTime );
    pElement->FontColor.Blend( iState, fElapsedTime );

    m_pDialog->DrawSprite( pElement, &m_rcDropdown, DXUT_NEAR_BUTTON_DEPTH );

    // Selection outline
    CDXUTElement* pSelectionElement = m_Elements.GetAt( 3 );
    pSelectionElement->TextureColor.Current = pElement->TextureColor.Current;
    pSelectionElement->FontColor.Current = pSelectionElement->FontColor.States[ DXUT_STATE_NORMAL ];

    DXUTFontNode* pFont = m_pDialog->GetFont( pElement->iFont );
    if( pFont )
    {
        int curY = m_rcDropdownText.top;
        int nRemainingHeight = RectHeight( m_rcDropdownText );
        //WCHAR strDropdown[4096] = {0};

        for( ULONG i = m_ScrollBar.GetTrackPos(); i < m_Items.GetSize(); i++ )
        {
            DXUTComboBoxItem* pItem = m_Items.GetAt( i );

            // Make sure there's room left in the dropdown
            nRemainingHeight -= pFont->Height;
            if( nRemainingHeight < 0 )
            {
                pItem->bVisible = FALSE;
                continue;
            }

            SetRect( &pItem->rcActive, m_rcDropdownText.left, curY, m_rcDropdownText.right, curY + pFont->Height );
            curY += pFont->Height;

            //debug
            //int blue = 50 * i;
            //m_pDialog->DrawRect( &pItem->rcActive, 0xFFFF0000 | blue );

            pItem->bVisible = TRUE;

            if( m_bOpened )
            {
                if( ( int )i == m_Focused )
                {
                    RECT rc;
                    SetRect( &rc, m_rcDropdown.left, pItem->rcActive.top - 2, m_rcDropdown.right,
                             pItem->rcActive.bottom + 2 );
                    m_pDialog->DrawSprite( pSelectionElement, &rc, DXUT_NEAR_BUTTON_DEPTH );
                    m_pDialog->DrawText( pItem->strText, pSelectionElement, &pItem->rcActive );
                }
                else
                {
                    m_pDialog->DrawText( pItem->strText, pElement, &pItem->rcActive );
                }
            }
        }
    }

    int nOffsetX = 0;
    int nOffsetY = 0;

    iState = DXUT_STATE_NORMAL;

    if( m_bVisible == FALSE )
        iState = DXUT_STATE_HIDDEN;
    else if( m_bEnabled == FALSE )
        iState = DXUT_STATE_DISABLED;
    else if( m_bPressed )
    {
        iState = DXUT_STATE_PRESSED;

        nOffsetX = 1;
        nOffsetY = 2;
    }
    else if( m_bMouseOver )
    {
        iState = DXUT_STATE_MOUSEOVER;

        nOffsetX = -1;
        nOffsetY = -2;
    }
    else if( m_bHasFocus )
        iState = DXUT_STATE_FOCUS;

    FLOAT fBlendRate = ( iState == DXUT_STATE_PRESSED ) ? 0.0f : 0.8f;

    // Button
    pElement = m_Elements.GetAt( 1 );

    // Blend current color
    pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );

    RECT rcWindow = m_rcButton;
    OffsetRect( &rcWindow, nOffsetX, nOffsetY );
    m_pDialog->DrawSprite( pElement, &rcWindow, DXUT_FAR_BUTTON_DEPTH );

    if( m_bOpened )
        iState = DXUT_STATE_PRESSED;

    // Main text box
    pElement = m_Elements.GetAt( 0 );

    // Blend current color
    pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
    pElement->FontColor.Blend( iState, fElapsedTime, fBlendRate );

    m_pDialog->DrawSprite( pElement, &m_rcText, DXUT_NEAR_BUTTON_DEPTH );

    if( m_Selected >= 0 && m_Selected < ( int )m_Items.GetSize() )
    {
        DXUTComboBoxItem* pItem = m_Items.GetAt( m_Selected );
        if( pItem != NULL )
        {
            m_pDialog->DrawText( pItem->strText, pElement, &m_rcText );

        }
    }
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTComboBox::AddItem( const WCHAR* strText, void* pData )
{
    // Validate parameters
    if( strText == NULL )
    {
        return E_INVALIDARG;
    }

    // Create a new item and set the data
    DXUTComboBoxItem* pItem = new DXUTComboBoxItem;
    if( pItem == NULL )
    {
        return DXTRACE_ERR_MSGBOX( L"new", E_OUTOFMEMORY );
    }

    ZeroMemory( pItem, sizeof( DXUTComboBoxItem ) );
    wcscpy_s( pItem->strText, 256, strText );
    pItem->pData = pData;

    m_Items.Add( pItem );

    // Update the scroll bar with new range
    m_ScrollBar.SetTrackRange( 0, m_Items.GetSize() );

    // If this is the only item in the list, it's selected
    if( GetNumItems() == 1 )
    {
        m_Selected = 0;
        m_Focused = 0;
        m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, FALSE, this );
    }

    return S_OK;
}


//--------------------------------------------------------------------------------------
void CDXUTComboBox::RemoveItem( UINT index )
{
    DXUTComboBoxItem* pItem = m_Items.GetAt( index );
    SAFE_DELETE( pItem );
    m_Items.Remove( index );
    m_ScrollBar.SetTrackRange( 0, m_Items.GetSize() );
    if( m_Selected >= m_Items.GetSize() )
        m_Selected = m_Items.GetSize() - 1;
}


//--------------------------------------------------------------------------------------
void CDXUTComboBox::RemoveAllItems()
{
    for( ULONG i = 0; i < m_Items.GetSize(); i++ )
    {
        DXUTComboBoxItem* pItem = m_Items.GetAt( i );
        SAFE_DELETE( pItem );
    }

    m_Items.RemoveAll();
    m_ScrollBar.SetTrackRange( 0, 1 );
    m_Focused = m_Selected = ~0u;
}



//--------------------------------------------------------------------------------------
BOOL CDXUTComboBox::ContainsItem( const WCHAR* strText, UINT iStart )
{
    return ( -1 != FindItem( strText, iStart ) );
}


//--------------------------------------------------------------------------------------
int CDXUTComboBox::FindItem( const WCHAR* strText, UINT iStart )
{
    if( strText == NULL )
        return -1;

    for( ULONG i = iStart; i < m_Items.GetSize(); i++ )
    {
        DXUTComboBoxItem* pItem = m_Items.GetAt( i );

        if( 0 == wcscmp( pItem->strText, strText ) )
        {
            return i;
        }
    }

    return -1;
}


//--------------------------------------------------------------------------------------
void* CDXUTComboBox::GetSelectedData()
{
    if( m_Selected < 0 )
        return NULL;

    DXUTComboBoxItem* pItem = m_Items.GetAt( m_Selected );
    return pItem->pData;
}


//--------------------------------------------------------------------------------------
DXUTComboBoxItem* CDXUTComboBox::GetSelectedItem()
{
    if( m_Selected < 0 )
        return NULL;

    return m_Items.GetAt( m_Selected );
}


//--------------------------------------------------------------------------------------
void* CDXUTComboBox::GetItemData( const WCHAR* strText )
{
    int index = FindItem( strText );
    if( index == -1 )
    {
        return NULL;
    }

    DXUTComboBoxItem* pItem = m_Items.GetAt( index );
    if( pItem == NULL )
    {
        DXTRACE_ERR( L"CGrowableArray::GetAt", E_FAIL );
        return NULL;
    }

    return pItem->pData;
}


//--------------------------------------------------------------------------------------
void* CDXUTComboBox::GetItemData( int nIndex )
{
    if( nIndex < 0 || nIndex >= (int)m_Items.GetSize() )
        return NULL;

    return m_Items.GetAt( nIndex )->pData;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTComboBox::SetSelectedByIndex( UINT index )
{
    if( index >= GetNumItems() )
        return E_INVALIDARG;

    m_Focused = m_Selected = index;
    m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, FALSE, this );

    return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT CDXUTComboBox::SetSelectedByText( const WCHAR* strText )
{
    if( strText == NULL )
        return E_INVALIDARG;

    int index = FindItem( strText );
    if( index == -1 )
        return E_FAIL;

    m_Focused = m_Selected = index;
    m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, FALSE, this );

    return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT CDXUTComboBox::SetSelectedByData( void* pData )
{
    for( ULONG i = 0; i < m_Items.GetSize(); i++ )
    {
        DXUTComboBoxItem* pItem = m_Items.GetAt( i );

        if( pItem->pData == pData )
        {
            m_Focused = m_Selected = i;
            m_pDialog->SendEvent( EVENT_COMBOBOX_SELECTION_CHANGED, FALSE, this );
            return S_OK;
        }
    }

    return E_FAIL;
}



//--------------------------------------------------------------------------------------
CDXUTSlider::CDXUTSlider( CDXUTDialog* pDialog )
{
    m_Type = DXUT_CONTROL_SLIDER;
    m_pDialog = pDialog;

    m_nMin = 0;
    m_nMax = 100;
    m_nValue = 50;

    m_bPressed = FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTSlider::ContainsPoint( POINT pt )
{
    return ( PtInRect( &m_rcBoundingBox, pt ) ||
             PtInRect( &m_rcButton, pt ) );
}


//--------------------------------------------------------------------------------------
void CDXUTSlider::UpdateRects()
{
    CDXUTControl::UpdateRects();

    m_rcButton = m_rcBoundingBox;
    m_rcButton.right = m_rcButton.left + RectHeight( m_rcButton );
    OffsetRect( &m_rcButton, -RectWidth( m_rcButton ) / 2, 0 );

    m_nButtonX = ( int )( ( m_nValue - m_nMin ) * ( FLOAT )RectWidth( m_rcBoundingBox ) / ( m_nMax - m_nMin ) );
    OffsetRect( &m_rcButton, m_nButtonX, 0 );
}

int CDXUTSlider::ValueFromPos( int x )
{
    FLOAT fValuePerPixel = ( FLOAT )( m_nMax - m_nMin ) / RectWidth( m_rcBoundingBox );
    return ( int )( 0.5f + m_nMin + fValuePerPixel * ( x - m_rcBoundingBox.left ) );
}

//--------------------------------------------------------------------------------------
BOOL CDXUTSlider::HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    switch( Message )
    {
        case WM_KEYDOWN:
        {
            switch( wParam )
            {
                case VK_HOME:
                    SetValueInternal( m_nMin, TRUE );
                    return TRUE;

                case VK_END:
                    SetValueInternal( m_nMax, TRUE );
                    return TRUE;

                case VK_LEFT:
                case VK_DOWN:
                    SetValueInternal( m_nValue - 1, TRUE );
                    return TRUE;

                case VK_RIGHT:
                case VK_UP:
                    SetValueInternal( m_nValue + 1, TRUE );
                    return TRUE;

                case VK_NEXT:
                    SetValueInternal( m_nValue - ( 10 > ( m_nMax - m_nMin ) / 10 ? 10 : ( m_nMax - m_nMin ) / 10 ),
                                      TRUE );
                    return TRUE;

                case VK_PRIOR:
                    SetValueInternal( m_nValue + ( 10 > ( m_nMax - m_nMin ) / 10 ? 10 : ( m_nMax - m_nMin ) / 10 ),
                                      TRUE );
                    return TRUE;
            }
            break;
        }
    }


    return FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTSlider::HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    switch (Message)
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            {
                if( PtInRect( &m_rcButton, pt ) )
                {
                    // Pressed while inside the control
                    m_bPressed = TRUE;
                    SetCapture( DXUTGetHWND() );

                    m_nDragX = pt.x;
                    //m_nDragY = pt.y;
                    m_nDragOffset = m_nButtonX - m_nDragX;

                    //m_nDragValue = m_nValue;

                    if( !m_bHasFocus )
                        m_pDialog->RequestFocus( this );

                    return TRUE;
                }

                if( PtInRect( &m_rcBoundingBox, pt ) )
                {
                    m_nDragX = pt.x;
                    m_nDragOffset = 0;
                    m_bPressed = TRUE;

                    if( !m_bHasFocus )
                        m_pDialog->RequestFocus( this );

                    if( pt.x > m_nButtonX + m_x )
                    {
                        SetValueInternal( m_nValue + 1, TRUE );
                        return TRUE;
                    }

                    if( pt.x < m_nButtonX + m_x )
                    {
                        SetValueInternal( m_nValue - 1, TRUE );
                        return TRUE;
                    }
                }

                break;
            }

        case WM_LBUTTONUP:
        {
            if( m_bPressed )
            {
                m_bPressed = FALSE;
                ReleaseCapture();
                m_pDialog->SendEvent( EVENT_SLIDER_VALUE_CHANGED, TRUE, this );

                return TRUE;
            }

            break;
        }

        case WM_MOUSEMOVE:
        {
            if( m_bPressed )
            {
                SetValueInternal( ValueFromPos( m_x + pt.x + m_nDragOffset ), TRUE );
                return TRUE;
            }

            break;
        }

        case WM_MOUSEWHEEL:
        {
            int nScrollAmount = int( ( short )HIWORD( wParam ) ) / WHEEL_DELTA;
            SetValueInternal( m_nValue - nScrollAmount, TRUE );
            return TRUE;
        }
    };

    return FALSE;
}


//--------------------------------------------------------------------------------------
void CDXUTSlider::SetRange( int nMin, int nMax )
{
    m_nMin = nMin;
    m_nMax = nMax;

    SetValueInternal( m_nValue, FALSE );
}


//--------------------------------------------------------------------------------------
void CDXUTSlider::SetValueInternal( int nValue, BOOL bFromInput )
{
    // Clamp to range
    nValue = __max( m_nMin, nValue );
    nValue = __min( m_nMax, nValue );

    if( nValue == m_nValue )
        return;

    m_nValue = nValue;
    UpdateRects();

    m_pDialog->SendEvent( EVENT_SLIDER_VALUE_CHANGED, bFromInput, this );
}


//--------------------------------------------------------------------------------------
void CDXUTSlider::Render( FLOAT fElapsedTime )
{
    int nOffsetX = 0;
    int nOffsetY = 0;

    DXUT_CONTROL_STATE iState = DXUT_STATE_NORMAL;

    if( m_bVisible == FALSE )
    {
        iState = DXUT_STATE_HIDDEN;
    }
    else if( m_bEnabled == FALSE )
    {
        iState = DXUT_STATE_DISABLED;
    }
    else if( m_bPressed )
    {
        iState = DXUT_STATE_PRESSED;

        nOffsetX = 1;
        nOffsetY = 2;
    }
    else if( m_bMouseOver )
    {
        iState = DXUT_STATE_MOUSEOVER;

        nOffsetX = -1;
        nOffsetY = -2;
    }
    else if( m_bHasFocus )
    {
        iState = DXUT_STATE_FOCUS;
    }

    FLOAT fBlendRate = ( iState == DXUT_STATE_PRESSED ) ? 0.0f : 0.8f;

    CDXUTElement* pElement = m_Elements.GetAt( 0 );

    // Blend current color
    pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
    m_pDialog->DrawSprite( pElement, &m_rcBoundingBox, DXUT_FAR_BUTTON_DEPTH );

    pElement = m_Elements.GetAt( 1 );

    // Blend current color
    pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
    m_pDialog->DrawSprite( pElement, &m_rcButton, DXUT_NEAR_BUTTON_DEPTH );
}


//--------------------------------------------------------------------------------------
// CDXUTScrollBar class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
CDXUTScrollBar::CDXUTScrollBar( CDXUTDialog* pDialog )
{
    m_Type = DXUT_CONTROL_SCROLLBAR;
    m_pDialog = pDialog;

    m_bShowThumb = TRUE;
    m_bDrag = FALSE;

    SetRect( &m_rcUpButton, 0, 0, 0, 0 );
    SetRect( &m_rcDownButton, 0, 0, 0, 0 );
    SetRect( &m_rcTrack, 0, 0, 0, 0 );
    SetRect( &m_rcThumb, 0, 0, 0, 0 );
    m_nPosition = 0;
    m_nPageSize = 1;
    m_nStart = 0;
    m_nEnd = 1;
    m_Arrow = CLEAR;
    m_dArrowTS = 0.0;
}


//--------------------------------------------------------------------------------------
CDXUTScrollBar::~CDXUTScrollBar()
{
}


//--------------------------------------------------------------------------------------
void CDXUTScrollBar::UpdateRects()
{
    CDXUTControl::UpdateRects();

    // Make the buttons square

    SetRect( &m_rcUpButton, m_rcBoundingBox.left, m_rcBoundingBox.top,
             m_rcBoundingBox.right, m_rcBoundingBox.top + RectWidth( m_rcBoundingBox ) );
    SetRect( &m_rcDownButton, m_rcBoundingBox.left, m_rcBoundingBox.bottom - RectWidth( m_rcBoundingBox ),
             m_rcBoundingBox.right, m_rcBoundingBox.bottom );
    SetRect( &m_rcTrack, m_rcUpButton.left, m_rcUpButton.bottom,
             m_rcDownButton.right, m_rcDownButton.top );
    m_rcThumb.left = m_rcUpButton.left;
    m_rcThumb.right = m_rcUpButton.right;

    UpdateThumbRect();
}


//--------------------------------------------------------------------------------------
// Compute the dimension of the scroll thumb
void CDXUTScrollBar::UpdateThumbRect()
{
    if( m_nEnd - m_nStart > m_nPageSize )
    {
        int nThumbHeight = __max( RectHeight( m_rcTrack ) * m_nPageSize / ( m_nEnd - m_nStart ),
                                  SCROLLBAR_MINTHUMBSIZE );
        int nMaxPosition = m_nEnd - m_nStart - m_nPageSize;
        m_rcThumb.top = m_rcTrack.top + ( m_nPosition - m_nStart ) * ( RectHeight( m_rcTrack ) - nThumbHeight )
            / nMaxPosition;
        m_rcThumb.bottom = m_rcThumb.top + nThumbHeight;
        m_bShowThumb = TRUE;

    }
    else
    {
        // No content to scroll
        m_rcThumb.bottom = m_rcThumb.top;
        m_bShowThumb = FALSE;
    }
}


//--------------------------------------------------------------------------------------
// Scroll() scrolls by nDelta items.  A positive value scrolls down, while a negative
// value scrolls up.
void CDXUTScrollBar::Scroll( int nDelta )
{
    // Perform scroll
    m_nPosition += nDelta;

    // Cap position
    Cap();

    // Update thumb position
    UpdateThumbRect();
}


//--------------------------------------------------------------------------------------
void CDXUTScrollBar::ShowItem( int nIndex )
{
    // Cap the index

    if( nIndex < 0 )
        nIndex = 0;

    if( nIndex >= m_nEnd )
        nIndex = m_nEnd - 1;

    // Adjust position

    if( m_nPosition > nIndex )
        m_nPosition = nIndex;
    else if( m_nPosition + m_nPageSize <= nIndex )
        m_nPosition = nIndex - m_nPageSize + 1;

    UpdateThumbRect();
}


//--------------------------------------------------------------------------------------
BOOL CDXUTScrollBar::HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTScrollBar::HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam)
{
    static int ThumbOffsetY;

    m_LastMouse = pt;
    switch( Message )
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            {
                // Check for click on up button

                if( PtInRect( &m_rcUpButton, pt ) )
                {
                    SetCapture( DXUTGetHWND() );
                    if( m_nPosition > m_nStart )
                        --m_nPosition;
                    UpdateThumbRect();
                    m_Arrow = CLICKED_UP;
                    m_dArrowTS = DXUTGetTime();
                    return TRUE;
                }

                // Check for click on down button

                if( PtInRect( &m_rcDownButton, pt ) )
                {
                    SetCapture( DXUTGetHWND() );
                    if( m_nPosition + m_nPageSize <= m_nEnd )
                        ++m_nPosition;
                    UpdateThumbRect();
                    m_Arrow = CLICKED_DOWN;
                    m_dArrowTS = DXUTGetTime();
                    return TRUE;
                }

                // Check for click on thumb

                if( PtInRect( &m_rcThumb, pt ) )
                {
                    SetCapture( DXUTGetHWND() );
                    m_bDrag = TRUE;
                    ThumbOffsetY = pt.y - m_rcThumb.top;
                    return TRUE;
                }

                // Check for click on track

                if( m_rcThumb.left <= pt.x &&
                    m_rcThumb.right > pt.x )
                {
                    SetCapture( DXUTGetHWND() );
                    if( m_rcThumb.top > pt.y &&
                        m_rcTrack.top <= pt.y )
                    {
                        Scroll( -( m_nPageSize - 1 ) );
                        return TRUE;
                    }
                    else if( m_rcThumb.bottom <= pt.y &&
                             m_rcTrack.bottom > pt.y )
                    {
                        Scroll( m_nPageSize - 1 );
                        return TRUE;
                    }
                }

                break;
            }

        case WM_LBUTTONUP:
        {
            m_bDrag = FALSE;
            ReleaseCapture();
            UpdateThumbRect();
            m_Arrow = CLEAR;
            break;
        }

        case WM_MOUSEMOVE:
        {
            if( m_bDrag )
            {
                m_rcThumb.bottom += pt.y - ThumbOffsetY - m_rcThumb.top;
                m_rcThumb.top = pt.y - ThumbOffsetY;
                if( m_rcThumb.top < m_rcTrack.top )
                    OffsetRect( &m_rcThumb, 0, m_rcTrack.top - m_rcThumb.top );
                else if( m_rcThumb.bottom > m_rcTrack.bottom )
                    OffsetRect( &m_rcThumb, 0, m_rcTrack.bottom - m_rcThumb.bottom );

                // Compute first item index based on thumb position

                int nMaxFirstItem = m_nEnd - m_nStart - m_nPageSize + 1;  // Largest possible index for first item
                int nMaxThumb = RectHeight( m_rcTrack ) - RectHeight( m_rcThumb );  // Largest possible thumb position from the top

                m_nPosition = m_nStart +
                    ( m_rcThumb.top - m_rcTrack.top +
                      nMaxThumb / ( nMaxFirstItem * 2 ) ) * // Shift by half a row to avoid last row covered by only one pixel
                    nMaxFirstItem / nMaxThumb;

                return TRUE;
            }

            break;
        }
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTScrollBar::MsgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    if (WM_CAPTURECHANGED == Message)
    {
        // The application just lost mouse capture. We may not have gotten
        // the WM_MOUSEUP message, so reset m_bDrag here.
        if ((HWND)lParam != DXUTGetHWND())
            m_bDrag = FALSE;
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
void CDXUTScrollBar::Render( FLOAT fElapsedTime )
{
    // Check if the arrow button has been held for a while.
    // If so, update the thumb position to simulate repeated
    // scroll.
    if( m_Arrow != CLEAR )
    {
        double dCurrTime = DXUTGetTime();
        if( PtInRect( &m_rcUpButton, m_LastMouse ) )
        {
            switch( m_Arrow )
            {
                case CLICKED_UP:
                    if( SCROLLBAR_ARROWCLICK_DELAY < dCurrTime - m_dArrowTS )
                    {
                        Scroll( -1 );
                        m_Arrow = HELD_UP;
                        m_dArrowTS = dCurrTime;
                    }
                    break;
                case HELD_UP:
                    if( SCROLLBAR_ARROWCLICK_REPEAT < dCurrTime - m_dArrowTS )
                    {
                        Scroll( -1 );
                        m_dArrowTS = dCurrTime;
                    }
                    break;
            }
        }
        else if( PtInRect( &m_rcDownButton, m_LastMouse ) )
        {
            switch( m_Arrow )
            {
                case CLICKED_DOWN:
                    if( SCROLLBAR_ARROWCLICK_DELAY < dCurrTime - m_dArrowTS )
                    {
                        Scroll( 1 );
                        m_Arrow = HELD_DOWN;
                        m_dArrowTS = dCurrTime;
                    }
                    break;
                case HELD_DOWN:
                    if( SCROLLBAR_ARROWCLICK_REPEAT < dCurrTime - m_dArrowTS )
                    {
                        Scroll( 1 );
                        m_dArrowTS = dCurrTime;
                    }
                    break;
            }
        }
    }

    DXUT_CONTROL_STATE iState = DXUT_STATE_NORMAL;

    if( m_bVisible == FALSE )
        iState = DXUT_STATE_HIDDEN;
    else if( m_bEnabled == FALSE || m_bShowThumb == FALSE )
        iState = DXUT_STATE_DISABLED;
    else if( m_bMouseOver )
        iState = DXUT_STATE_MOUSEOVER;
    else if( m_bHasFocus )
        iState = DXUT_STATE_FOCUS;


    FLOAT fBlendRate = ( iState == DXUT_STATE_PRESSED ) ? 0.0f : 0.8f;

    // Background track layer
    CDXUTElement* pElement = m_Elements.GetAt( 0 );

    // Blend current color
    pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
    m_pDialog->DrawSprite( pElement, &m_rcTrack, DXUT_FAR_BUTTON_DEPTH );

    // Up Arrow
    pElement = m_Elements.GetAt( 1 );

    // Blend current color
    pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
    m_pDialog->DrawSprite( pElement, &m_rcUpButton, DXUT_NEAR_BUTTON_DEPTH );

    // Down Arrow
    pElement = m_Elements.GetAt( 2 );

    // Blend current color
    pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
    m_pDialog->DrawSprite( pElement, &m_rcDownButton, DXUT_NEAR_BUTTON_DEPTH );

    // Thumb button
    pElement = m_Elements.GetAt( 3 );

    // Blend current color
    pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
    m_pDialog->DrawSprite( pElement, &m_rcThumb, DXUT_NEAR_BUTTON_DEPTH );

}


//--------------------------------------------------------------------------------------
void CDXUTScrollBar::SetTrackRange( int nStart, int nEnd )
{
    m_nStart = nStart; m_nEnd = nEnd;
    Cap();
    UpdateThumbRect();
}


//--------------------------------------------------------------------------------------
void CDXUTScrollBar::Cap()  // Clips position at boundaries. Ensures it stays within legal range.
{
    if( m_nPosition < m_nStart ||
        m_nEnd - m_nStart <= m_nPageSize )
    {
        m_nPosition = m_nStart;
    }
    else if( m_nPosition + m_nPageSize > m_nEnd )
        m_nPosition = m_nEnd - m_nPageSize + 1;
}

//--------------------------------------------------------------------------------------
// CDXUTListBox class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
CDXUTListBox::CDXUTListBox( CDXUTDialog* pDialog ) : m_ScrollBar( pDialog )
{
    m_Type = DXUT_CONTROL_LISTBOX;
    m_pDialog = pDialog;

    m_dwStyle = 0;
    m_nSBWidth = 16;
    m_nSelected = -1;
    m_nSelStart = 0;
    m_bDrag = FALSE;
    m_nBorder = 6;
    m_nMargin = 5;
    m_nTextHeight = 0;
}


//--------------------------------------------------------------------------------------
CDXUTListBox::~CDXUTListBox()
{
    RemoveAllItems();
}


//--------------------------------------------------------------------------------------
void CDXUTListBox::UpdateRects()
{
    CDXUTControl::UpdateRects();

    m_rcSelection = m_rcBoundingBox;
    m_rcSelection.right -= m_nSBWidth;
    InflateRect( &m_rcSelection, -m_nBorder, -m_nBorder );
    m_rcText = m_rcSelection;
    InflateRect( &m_rcText, -m_nMargin, 0 );

    // Update the scrollbar's rects
    m_ScrollBar.SetLocation( m_rcBoundingBox.right - m_nSBWidth, m_rcBoundingBox.top );
    m_ScrollBar.SetSize( m_nSBWidth, m_height );
    DXUTFontNode* pFontNode = m_pDialog->GetManager()->GetFontNode( m_Elements.GetAt( 0 )->iFont );
    if( pFontNode && pFontNode->Height )
    {
        m_ScrollBar.SetPageSize( RectHeight( m_rcText ) / pFontNode->Height );

        // The selected item may have been scrolled off the page.
        // Ensure that it is in page again.
        m_ScrollBar.ShowItem( m_nSelected );
    }
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTListBox::AddItem( const WCHAR* wszText, void* pData )
{
    DXUTListBoxItem* pNewItem = new DXUTListBoxItem;
    if( !pNewItem )
        return E_OUTOFMEMORY;

    wcscpy_s( pNewItem->strText, 256, wszText );
    pNewItem->pData = pData;
    SetRect( &pNewItem->rcActive, 0, 0, 0, 0 );
    pNewItem->bSelected = FALSE;

    HRESULT hr = m_Items.Add( pNewItem );
    if( FAILED( hr ) )
    {
        SAFE_DELETE( pNewItem );
    }
    else
    {
        m_ScrollBar.SetTrackRange( 0, m_Items.GetSize() );
    }

    return hr;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTListBox::InsertItem( int nIndex, const WCHAR* wszText, void* pData )
{
    DXUTListBoxItem* pNewItem = new DXUTListBoxItem;
    if( !pNewItem )
        return E_OUTOFMEMORY;

    wcscpy_s( pNewItem->strText, 256, wszText );
    pNewItem->pData = pData;
    SetRect( &pNewItem->rcActive, 0, 0, 0, 0 );
    pNewItem->bSelected = FALSE;

    HRESULT hr = m_Items.Insert( nIndex, pNewItem );
    if( SUCCEEDED( hr ) )
        m_ScrollBar.SetTrackRange( 0, m_Items.GetSize() );
    else
        SAFE_DELETE( pNewItem );

    return hr;
}


//--------------------------------------------------------------------------------------
void CDXUTListBox::RemoveItem( int nIndex )
{
    if( nIndex < 0 || nIndex >= ( int )m_Items.GetSize() )
        return;

    DXUTListBoxItem* pItem = m_Items.GetAt( nIndex );

    delete pItem;
    m_Items.Remove( nIndex );
    m_ScrollBar.SetTrackRange( 0, m_Items.GetSize() );
    if( m_nSelected >= ( int )m_Items.GetSize() )
        m_nSelected = m_Items.GetSize() - 1;

    m_pDialog->SendEvent( EVENT_LISTBOX_SELECTION, TRUE, this );
}


//--------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------
void CDXUTListBox::RemoveItemByData( void* pData )
{
}


//--------------------------------------------------------------------------------------
void CDXUTListBox::RemoveAllItems()
{
    for( ULONG i = 0; i < m_Items.GetSize(); ++i )
    {
        DXUTListBoxItem* pItem = m_Items.GetAt( i );
        delete pItem;
    }

    m_Items.RemoveAll();
    m_ScrollBar.SetTrackRange( 0, 1 );
}


//--------------------------------------------------------------------------------------
DXUTListBoxItem* CDXUTListBox::GetItem( int nIndex )
{
    if( nIndex < 0 || nIndex >= ( int )m_Items.GetSize() )
        return NULL;

    return m_Items[nIndex];
}


//--------------------------------------------------------------------------------------
// For single-selection listbox, returns the index of the selected item.
// For multi-selection, returns the first selected item after the nPreviousSelected position.
// To search for the first selected item, the app passes -1 for nPreviousSelected.  For
// subsequent searches, the app passes the returned index back to GetSelectedIndex as.
// nPreviousSelected.
// Returns -1 on error or if no item is selected.
int CDXUTListBox::GetSelectedIndex( int nPreviousSelected )
{
    if( nPreviousSelected < -1 )
        return -1;

    if( m_dwStyle & MULTISELECTION )
    {
        // Multiple selection enabled. Search for the next item with the selected flag.
        for( int i = nPreviousSelected + 1; i < ( int )m_Items.GetSize(); ++i )
        {
            DXUTListBoxItem* pItem = m_Items.GetAt( i );

            if( pItem->bSelected )
                return i;
        }

        return -1;
    }
    else
    {
        // Single selection
        return m_nSelected;
    }
}


//--------------------------------------------------------------------------------------
void CDXUTListBox::SelectItem( int nNewIndex )
{
    // If no item exists, do nothing.
    if( m_Items.GetSize() == 0 )
        return;

    int nOldSelected = m_nSelected;

    // Adjust m_nSelected
    m_nSelected = nNewIndex;

    // Perform capping
    if( m_nSelected < 0 )
        m_nSelected = 0;
    if( m_nSelected >= ( int )m_Items.GetSize() )
        m_nSelected = m_Items.GetSize() - 1;

    if( nOldSelected != m_nSelected )
    {
        if( m_dwStyle & MULTISELECTION )
        {
            m_Items[m_nSelected]->bSelected = TRUE;
        }

        // Update selection start
        m_nSelStart = m_nSelected;

        // Adjust scroll bar
        m_ScrollBar.ShowItem( m_nSelected );
    }

    m_pDialog->SendEvent( EVENT_LISTBOX_SELECTION, TRUE, this );
}


//--------------------------------------------------------------------------------------
BOOL CDXUTListBox::HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    // Let the scroll bar have a chance to handle it first
    if( m_ScrollBar.HandleKeyboard(hWnd, Message, wParam, lParam))
        return TRUE;

    switch( Message )
    {
        case WM_KEYDOWN:
            switch( wParam )
            {
                case VK_UP:
                case VK_DOWN:
                case VK_NEXT:
                case VK_PRIOR:
                case VK_HOME:
                case VK_END:
                    {
                        // If no item exists, do nothing.
                        if( m_Items.GetSize() == 0 )
                            return TRUE;

                        int nOldSelected = m_nSelected;

                        // Adjust m_nSelected
                        switch( wParam )
                        {
                            case VK_UP:
                                --m_nSelected; break;
                            case VK_DOWN:
                                ++m_nSelected; break;
                            case VK_NEXT:
                                m_nSelected += m_ScrollBar.GetPageSize() - 1; break;
                            case VK_PRIOR:
                                m_nSelected -= m_ScrollBar.GetPageSize() - 1; break;
                            case VK_HOME:
                                m_nSelected = 0; break;
                            case VK_END:
                                m_nSelected = m_Items.GetSize() - 1; break;
                        }

                        // Perform capping
                        if( m_nSelected < 0 )
                            m_nSelected = 0;
                        if( m_nSelected >= ( int )m_Items.GetSize() )
                            m_nSelected = m_Items.GetSize() - 1;

                        if( nOldSelected != m_nSelected )
                        {
                            if( m_dwStyle & MULTISELECTION )
                            {
                                // Multiple selection

                                // Clear all selection
                                for( int i = 0; i < ( int )m_Items.GetSize(); ++i )
                                {
                                    DXUTListBoxItem* pItem = m_Items[i];
                                    pItem->bSelected = FALSE;
                                }

                                if( GetKeyState( VK_SHIFT ) < 0 )
                                {
                                    // Select all items from m_nSelStart to
                                    // m_nSelected
                                    int nEnd = __max( m_nSelStart, m_nSelected );

                                    for( int n = __min( m_nSelStart, m_nSelected ); n <= nEnd; ++n )
                                        m_Items[n]->bSelected = TRUE;
                                }
                                else
                                {
                                    m_Items[m_nSelected]->bSelected = TRUE;

                                    // Update selection start
                                    m_nSelStart = m_nSelected;
                                }
                            }
                            else
                                m_nSelStart = m_nSelected;

                            // Adjust scroll bar

                            m_ScrollBar.ShowItem( m_nSelected );

                            // Send notification

                            m_pDialog->SendEvent( EVENT_LISTBOX_SELECTION, TRUE, this );
                        }
                        return TRUE;
                    }

                    // Space is the hotkey for double-clicking an item.
                    //
                case VK_SPACE:
                    m_pDialog->SendEvent( EVENT_LISTBOX_ITEM_DBLCLK, TRUE, this );
                    return TRUE;
            }
            break;
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTListBox::HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    // First acquire focus
    if( WM_LBUTTONDOWN == Message )
        if( !m_bHasFocus )
            m_pDialog->RequestFocus( this );

    // Let the scroll bar handle it first.
    if( m_ScrollBar.HandleMouse(hWnd, Message, pt, wParam, lParam))
        return TRUE;

    switch( Message )
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            // Check for clicks in the text area
            if( m_Items.GetSize() > 0 && PtInRect( &m_rcSelection, pt ) )
            {
                // Compute the index of the clicked item

                int nClicked;
                if( m_nTextHeight )
                    nClicked = m_ScrollBar.GetTrackPos() + ( pt.y - m_rcText.top ) / m_nTextHeight;
                else
                    nClicked = -1;

                // Only proceed if the click falls on top of an item.

                if( nClicked >= m_ScrollBar.GetTrackPos() &&
                    nClicked < ( int )m_Items.GetSize() &&
                    nClicked < m_ScrollBar.GetTrackPos() + m_ScrollBar.GetPageSize() )
                {
                    SetCapture( DXUTGetHWND() );
                    m_bDrag = TRUE;

                    // If this is a double click, fire off an event and exit
                    // since the first click would have taken care of the selection
                    // updating.
                    if( Message == WM_LBUTTONDBLCLK )
                    {
                        m_pDialog->SendEvent( EVENT_LISTBOX_ITEM_DBLCLK, TRUE, this );
                        return TRUE;
                    }

                    m_nSelected = nClicked;
                    if( !( wParam & MK_SHIFT ) )
                        m_nSelStart = m_nSelected;

                    // If this is a multi-selection listbox, update per-item
                    // selection data.

                    if( m_dwStyle & MULTISELECTION )
                    {
                        // Determine behavior based on the state of Shift and Ctrl

                        DXUTListBoxItem* pSelItem = m_Items.GetAt( m_nSelected );
                        if( ( wParam & ( MK_SHIFT | MK_CONTROL ) ) == MK_CONTROL )
                        {
                            // Control click. Reverse the selection of this item.

                            pSelItem->bSelected = !pSelItem->bSelected;
                        }
                        else if( ( wParam & ( MK_SHIFT | MK_CONTROL ) ) == MK_SHIFT )
                        {
                            // Shift click. Set the selection for all items
                            // from last selected item to the current item.
                            // Clear everything else.

                            int nBegin = __min( m_nSelStart, m_nSelected );
                            int nEnd = __max( m_nSelStart, m_nSelected );

                            for( int i = 0; i < nBegin; ++i )
                            {
                                DXUTListBoxItem* pItem = m_Items.GetAt( i );
                                pItem->bSelected = FALSE;
                            }

                            for( int i = nEnd + 1; i < ( int )m_Items.GetSize(); ++i )
                            {
                                DXUTListBoxItem* pItem = m_Items.GetAt( i );
                                pItem->bSelected = FALSE;
                            }

                            for( int i = nBegin; i <= nEnd; ++i )
                            {
                                DXUTListBoxItem* pItem = m_Items.GetAt( i );
                                pItem->bSelected = TRUE;
                            }
                        }
                        else if( ( wParam & ( MK_SHIFT | MK_CONTROL ) ) == ( MK_SHIFT | MK_CONTROL ) )
                        {
                            // Control-Shift-click.

                            // The behavior is:
                            //   Set all items from m_nSelStart to m_nSelected to
                            //     the same state as m_nSelStart, not including m_nSelected.
                            //   Set m_nSelected to selected.

                            int nBegin = __min( m_nSelStart, m_nSelected );
                            int nEnd = __max( m_nSelStart, m_nSelected );

                            // The two ends do not need to be set here.

                            BOOL bLastSelected = m_Items.GetAt( m_nSelStart )->bSelected;
                            for( int i = nBegin + 1; i < nEnd; ++i )
                            {
                                DXUTListBoxItem* pItem = m_Items.GetAt( i );
                                pItem->bSelected = bLastSelected;
                            }

                            pSelItem->bSelected = TRUE;

                            // Restore m_nSelected to the previous value
                            // This matches the Windows behavior

                            m_nSelected = m_nSelStart;
                        }
                        else
                        {
                            // Simple click.  Clear all items and select the clicked
                            // item.


                            for( int i = 0; i < ( int )m_Items.GetSize(); ++i )
                            {
                                DXUTListBoxItem* pItem = m_Items.GetAt( i );
                                pItem->bSelected = FALSE;
                            }

                            pSelItem->bSelected = TRUE;
                        }
                    }  // End of multi-selection case

                    m_pDialog->SendEvent( EVENT_LISTBOX_SELECTION, TRUE, this );
                }

                return TRUE;
            }
            break;

        case WM_LBUTTONUP:
        {
            ReleaseCapture();
            m_bDrag = FALSE;

            if( m_nSelected != -1 )
            {
                // Set all items between m_nSelStart and m_nSelected to
                // the same state as m_nSelStart
                int nEnd = __max( m_nSelStart, m_nSelected );

                for( int n = __min( m_nSelStart, m_nSelected ) + 1; n < nEnd; ++n )
                    m_Items[n]->bSelected = m_Items[m_nSelStart]->bSelected;
                m_Items[m_nSelected]->bSelected = m_Items[m_nSelStart]->bSelected;

                // If m_nSelStart and m_nSelected are not the same,
                // the user has dragged the mouse to make a selection.
                // Notify the application of this.
                if( m_nSelStart != m_nSelected )
                    m_pDialog->SendEvent( EVENT_LISTBOX_SELECTION, TRUE, this );

                m_pDialog->SendEvent( EVENT_LISTBOX_SELECTION_END, TRUE, this );
            }
            return FALSE;
        }

        case WM_MOUSEMOVE:
            if( m_bDrag )
            {
                // Compute the index of the item below cursor

                int nItem;
                if( m_nTextHeight )
                    nItem = m_ScrollBar.GetTrackPos() + ( pt.y - m_rcText.top ) / m_nTextHeight;
                else
                    nItem = -1;

                // Only proceed if the cursor is on top of an item.

                if( nItem >= ( int )m_ScrollBar.GetTrackPos() &&
                    nItem < ( int )m_Items.GetSize() &&
                    nItem < m_ScrollBar.GetTrackPos() + m_ScrollBar.GetPageSize() )
                {
                    m_nSelected = nItem;
                    m_pDialog->SendEvent( EVENT_LISTBOX_SELECTION, TRUE, this );
                }
                else if( nItem < ( int )m_ScrollBar.GetTrackPos() )
                {
                    // User drags the mouse above window top
                    m_ScrollBar.Scroll( -1 );
                    m_nSelected = m_ScrollBar.GetTrackPos();
                    m_pDialog->SendEvent( EVENT_LISTBOX_SELECTION, TRUE, this );
                }
                else if( nItem >= m_ScrollBar.GetTrackPos() + m_ScrollBar.GetPageSize() )
                {
                    // User drags the mouse below window bottom
                    m_ScrollBar.Scroll( 1 );
                    m_nSelected = __min( ( int )m_Items.GetSize(), m_ScrollBar.GetTrackPos() +
                                         m_ScrollBar.GetPageSize() ) - 1;
                    m_pDialog->SendEvent( EVENT_LISTBOX_SELECTION, TRUE, this );
                }
            }
            break;

        case WM_MOUSEWHEEL:
        {
            UINT uLines;
            SystemParametersInfo( SPI_GETWHEELSCROLLLINES, 0, &uLines, 0 );
            int nScrollAmount = int( ( short )HIWORD( wParam ) ) / WHEEL_DELTA * uLines;
            m_ScrollBar.Scroll( -nScrollAmount );
            return TRUE;
        }
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTListBox::MsgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    if (WM_CAPTURECHANGED == Message)
    {
        // The application just lost mouse capture. We may not have gotten
        // the WM_MOUSEUP message, so reset m_bDrag here.
        if ((HWND)lParam != DXUTGetHWND())
            m_bDrag = FALSE;
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
void CDXUTListBox::Render( FLOAT fElapsedTime )
{
    if( m_bVisible == FALSE )
        return;

    CDXUTElement* pElement = m_Elements.GetAt( 0 );
    pElement->TextureColor.Blend( DXUT_STATE_NORMAL, fElapsedTime );
    pElement->FontColor.Blend( DXUT_STATE_NORMAL, fElapsedTime );

    CDXUTElement* pSelElement = m_Elements.GetAt( 1 );
    pSelElement->TextureColor.Blend( DXUT_STATE_NORMAL, fElapsedTime );
    pSelElement->FontColor.Blend( DXUT_STATE_NORMAL, fElapsedTime );

    m_pDialog->DrawSprite( pElement, &m_rcBoundingBox, DXUT_FAR_BUTTON_DEPTH );

    // Render the text
    if( m_Items.GetSize() > 0 )
    {
        // Find out the height of a single line of text
        RECT rc = m_rcText;
        RECT rcSel = m_rcSelection;
        rc.bottom = rc.top + m_pDialog->GetManager()->GetFontNode( pElement->iFont )->Height;

        // Update the line height formation
        m_nTextHeight = rc.bottom - rc.top;

        static BOOL bSBInit;
        if( !bSBInit )
        {
            // Update the page size of the scroll bar
            if( m_nTextHeight )
                m_ScrollBar.SetPageSize( RectHeight( m_rcText ) / m_nTextHeight );
            else
                m_ScrollBar.SetPageSize( RectHeight( m_rcText ) );
            bSBInit = TRUE;
        }

        rc.right = m_rcText.right;
        for( int i = m_ScrollBar.GetTrackPos(); i < ( int )m_Items.GetSize(); ++i )
        {
            if( rc.bottom > m_rcText.bottom )
                break;

            DXUTListBoxItem* pItem = m_Items.GetAt( i );

            // Determine if we need to render this item with the
            // selected element.
            BOOL bSelectedStyle = FALSE;

            if( !( m_dwStyle & MULTISELECTION ) && i == m_nSelected )
                bSelectedStyle = TRUE;
            else if( m_dwStyle & MULTISELECTION )
            {
                if( m_bDrag &&
                    ( ( i >= m_nSelected && i < m_nSelStart ) ||
                      ( i <= m_nSelected && i > m_nSelStart ) ) )
                    bSelectedStyle = m_Items[m_nSelStart]->bSelected;
                else if( pItem->bSelected )
                    bSelectedStyle = TRUE;
            }

            if( bSelectedStyle )
            {
                rcSel.top = rc.top; rcSel.bottom = rc.bottom;
                m_pDialog->DrawSprite( pSelElement, &rcSel, DXUT_NEAR_BUTTON_DEPTH );
                m_pDialog->DrawText( pItem->strText, pSelElement, &rc );
            }
            else
                m_pDialog->DrawText( pItem->strText, pElement, &rc );

            OffsetRect( &rc, 0, m_nTextHeight );
        }
    }

    // Render the scroll bar

    m_ScrollBar.Render( fElapsedTime );
}


// Static member initialization
/*
HINSTANCE               CUniBuffer::s_hDll = NULL;
HRESULT ( WINAPI*CUniBuffer::_ScriptApplyDigitSubstitution )( const SCRIPT_DIGITSUBSTITUTE*, SCRIPT_CONTROL*,
                                                              SCRIPT_STATE* ) = Dummy_ScriptApplyDigitSubstitution;
HRESULT ( WINAPI*CUniBuffer::_ScriptStringAnalyse )( HDC, const void*, int, int, int, DWORD, int, SCRIPT_CONTROL*,
                                                     SCRIPT_STATE*, const int*, SCRIPT_TABDEF*, const BYTE*,
                                                     SCRIPT_STRING_ANALYSIS* ) = Dummy_ScriptStringAnalyse;
HRESULT ( WINAPI*CUniBuffer::_ScriptStringCPtoX )( SCRIPT_STRING_ANALYSIS, int, BOOL, int* ) = Dummy_ScriptStringCPtoX;
HRESULT ( WINAPI*CUniBuffer::_ScriptStringXtoCP )( SCRIPT_STRING_ANALYSIS, int, int*, int* ) = Dummy_ScriptStringXtoCP;
HRESULT ( WINAPI*CUniBuffer::_ScriptStringFree )( SCRIPT_STRING_ANALYSIS* ) = Dummy_ScriptStringFree;
const SCRIPT_LOGATTR*   ( WINAPI*CUniBuffer::_ScriptString_pLogAttr )( SCRIPT_STRING_ANALYSIS ) =
    Dummy_ScriptString_pLogAttr;
const int*              ( WINAPI*CUniBuffer::_ScriptString_pcOutChars )( SCRIPT_STRING_ANALYSIS ) =
    Dummy_ScriptString_pcOutChars;

*/

BOOL                    CDXUTEditBox::s_bHideCaret;   // If true, we don't render the caret.



//--------------------------------------------------------------------------------------
// CDXUTEditBox class
//--------------------------------------------------------------------------------------

// When scrolling, EDITBOX_SCROLLEXTENT is reciprocal of the amount to scroll.
// If EDITBOX_SCROLLEXTENT = 4, then we scroll 1/4 of the control each time.
#define EDITBOX_SCROLLEXTENT 4

//--------------------------------------------------------------------------------------
CDXUTEditBox::CDXUTEditBox( CDXUTDialog* pDialog )
{
    m_Type = DXUT_CONTROL_EDITBOX;
    m_pDialog = pDialog;

    m_nBorder = 5;  // Default border width
    m_nSpacing = 4;  // Default spacing

    m_bCaretOn = TRUE;
    m_dfBlink = GetCaretBlinkTime() * 0.001f;
    m_dfLastBlink = DXUTGetGlobalTimer()->GetAbsoluteTime();
    s_bHideCaret = FALSE;
    m_nFirstVisible = 0;
    m_TextColor = D3DCOLOR_ARGB( 255, 16, 16, 16 );
    m_SelTextColor = D3DCOLOR_ARGB( 255, 255, 255, 255 );
    m_SelBkColor = D3DCOLOR_ARGB( 255, 40, 50, 92 );
    m_CaretColor = D3DCOLOR_ARGB( 255, 0, 0, 0 );
    m_nCaret = m_nSelStart = 0;
    m_bInsertMode = TRUE;

    m_bMouseDrag = FALSE;
}


//--------------------------------------------------------------------------------------
CDXUTEditBox::~CDXUTEditBox()
{
}


//--------------------------------------------------------------------------------------
// PlaceCaret: Set the caret to a character position, and adjust the scrolling if
//             necessary.
//--------------------------------------------------------------------------------------
void CDXUTEditBox::PlaceCaret( int nCP )
{
    assert( nCP >= 0 && nCP <= m_Buffer.GetTextSize() );
    m_nCaret = nCP;

    // Obtain the X offset of the character.
    int nX1st, nX, nX2;
    m_Buffer.CPtoX( m_nFirstVisible, FALSE, &nX1st );  // 1st visible char
    m_Buffer.CPtoX( nCP, FALSE, &nX );  // LEAD
    // If nCP is the NULL terminator, get the leading edge instead of trailing.
    if( nCP == m_Buffer.GetTextSize() )
        nX2 = nX;
    else
        m_Buffer.CPtoX( nCP, TRUE, &nX2 );  // TRAIL

    // If the left edge of the char is smaller than the left edge of the 1st visible char,
    // we need to scroll left until this char is visible.
    if( nX < nX1st )
    {
        // Simply make the first visible character the char at the new caret position.
        m_nFirstVisible = nCP;
    }
    else // If the right of the character is bigger than the offset of the control's
    // right edge, we need to scroll right to this character.
    if( nX2 > nX1st + RectWidth( m_rcText ) )
    {
        // Compute the X of the new left-most pixel
        int nXNewLeft = nX2 - RectWidth( m_rcText );

        // Compute the char position of this character
        int nCPNew1st, nNewTrail;
        m_Buffer.XtoCP( nXNewLeft, &nCPNew1st, &nNewTrail );

        // If this coordinate is not on a character border,
        // start from the next character so that the caret
        // position does not fall outside the text rectangle.
        int nXNew1st;
        m_Buffer.CPtoX( nCPNew1st, FALSE, &nXNew1st );
        if( nXNew1st < nXNewLeft )
            ++nCPNew1st;

        m_nFirstVisible = nCPNew1st;
    }
}


//--------------------------------------------------------------------------------------
void CDXUTEditBox::ClearText()
{
    m_Buffer.Clear();
    m_nFirstVisible = 0;
    PlaceCaret( 0 );
    m_nSelStart = 0;
}


//--------------------------------------------------------------------------------------
void CDXUTEditBox::SetText( LPCWSTR wszText, BOOL bSelected )
{
    assert( wszText != NULL );

    m_Buffer.SetText( wszText );
    m_nFirstVisible = 0;
    // Move the caret to the end of the text
    PlaceCaret( m_Buffer.GetTextSize() );
    m_nSelStart = bSelected ? 0 : m_nCaret;
}


//--------------------------------------------------------------------------------------
HRESULT CDXUTEditBox::GetTextCopy( __out_ecount(bufferCount) LPWSTR strDest,
                                   UINT bufferCount )
{
    assert( strDest );

    wcscpy_s( strDest, bufferCount, m_Buffer.GetBuffer() );

    return S_OK;
}


//--------------------------------------------------------------------------------------
void CDXUTEditBox::DeleteSelectionText()
{
    int nFirst = __min( m_nCaret, m_nSelStart );
    int nLast = __max( m_nCaret, m_nSelStart );
    // Update caret and selection
    PlaceCaret( nFirst );
    m_nSelStart = m_nCaret;
    // Remove the characters
    for( int i = nFirst; i < nLast; ++i )
        m_Buffer.RemoveChar( nFirst );
}


//--------------------------------------------------------------------------------------
void CDXUTEditBox::UpdateRects()
{
    CDXUTControl::UpdateRects();

    // Update the text rectangle
    m_rcText = m_rcBoundingBox;
    // First inflate by m_nBorder to compute render rects
    InflateRect( &m_rcText, -m_nBorder, -m_nBorder );

    // Update the render rectangles
    m_rcRender[0] = m_rcText;
    SetRect( &m_rcRender[1], m_rcBoundingBox.left, m_rcBoundingBox.top, m_rcText.left, m_rcText.top );
    SetRect( &m_rcRender[2], m_rcText.left, m_rcBoundingBox.top, m_rcText.right, m_rcText.top );
    SetRect( &m_rcRender[3], m_rcText.right, m_rcBoundingBox.top, m_rcBoundingBox.right, m_rcText.top );
    SetRect( &m_rcRender[4], m_rcBoundingBox.left, m_rcText.top, m_rcText.left, m_rcText.bottom );
    SetRect( &m_rcRender[5], m_rcText.right, m_rcText.top, m_rcBoundingBox.right, m_rcText.bottom );
    SetRect( &m_rcRender[6], m_rcBoundingBox.left, m_rcText.bottom, m_rcText.left, m_rcBoundingBox.bottom );
    SetRect( &m_rcRender[7], m_rcText.left, m_rcText.bottom, m_rcText.right, m_rcBoundingBox.bottom );
    SetRect( &m_rcRender[8], m_rcText.right, m_rcText.bottom, m_rcBoundingBox.right, m_rcBoundingBox.bottom );

    // Inflate further by m_nSpacing
    InflateRect( &m_rcText, -m_nSpacing, -m_nSpacing );
}


void CDXUTEditBox::CopyToClipboard()
{
    // Copy the selection text to the clipboard
    if( m_nCaret != m_nSelStart && OpenClipboard( NULL ) )
    {
        EmptyClipboard();

        HGLOBAL hBlock = GlobalAlloc( GMEM_MOVEABLE, sizeof( WCHAR ) * ( m_Buffer.GetTextSize() + 1 ) );
        if( hBlock )
        {
            WCHAR* pwszText = ( WCHAR* )GlobalLock( hBlock );
            if( pwszText )
            {
                int nFirst = __min( m_nCaret, m_nSelStart );
                int nLast = __max( m_nCaret, m_nSelStart );
                if( nLast - nFirst > 0 )
                    CopyMemory( pwszText, m_Buffer.GetBuffer() + nFirst, ( nLast - nFirst ) * sizeof( WCHAR ) );
                pwszText[nLast - nFirst] = L'\0';  // Terminate it
                GlobalUnlock( hBlock );
            }
            SetClipboardData( CF_UNICODETEXT, hBlock );
        }
        CloseClipboard();
        // We must not free the object until CloseClipboard is called.
        if( hBlock )
            GlobalFree( hBlock );
    }
}


void CDXUTEditBox::PasteFromClipboard()
{
    DeleteSelectionText();

    if( OpenClipboard( NULL ) )
    {
        HANDLE handle = GetClipboardData( CF_UNICODETEXT );
        if( handle )
        {
            // Convert the ANSI string to Unicode, then
            // insert to our buffer.
            WCHAR* pwszText = ( WCHAR* )GlobalLock( handle );
            if( pwszText )
            {
                // Copy all characters up to null.
                if( m_Buffer.InsertString( m_nCaret, pwszText ) )
                    PlaceCaret( m_nCaret + lstrlenW( pwszText ) );
                m_nSelStart = m_nCaret;
                GlobalUnlock( handle );
            }
        }
        CloseClipboard();
    }
}


//--------------------------------------------------------------------------------------
BOOL CDXUTEditBox::HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    BOOL bHandled = FALSE;

    switch( Message )
    {
        case WM_KEYDOWN:
        {
            switch( wParam )
            {
                case VK_TAB:
                    // We don't process Tab in case keyboard input is enabled and the user
                    // wishes to Tab to other controls.
                    break;

                case VK_HOME:
                    PlaceCaret( 0 );
                    if( GetKeyState( VK_SHIFT ) >= 0 )
                        // Shift is not down. Update selection
                        // start along with the caret.
                        m_nSelStart = m_nCaret;
                    ResetCaretBlink();
                    bHandled = TRUE;
                    break;

                case VK_END:
                    PlaceCaret( m_Buffer.GetTextSize() );
                    if( GetKeyState( VK_SHIFT ) >= 0 )
                        // Shift is not down. Update selection
                        // start along with the caret.
                        m_nSelStart = m_nCaret;
                    ResetCaretBlink();
                    bHandled = TRUE;
                    break;

                case VK_INSERT:
                    if( GetKeyState( VK_CONTROL ) < 0 )
                    {
                        // Control Insert. Copy to clipboard
                        CopyToClipboard();
                    }
                    else if( GetKeyState( VK_SHIFT ) < 0 )
                    {
                        // Shift Insert. Paste from clipboard
                        PasteFromClipboard();
                    }
                    else
                    {
                        // Toggle caret insert mode
                        m_bInsertMode = !m_bInsertMode;
                    }
                    break;

                case VK_DELETE:
                    // Check if there is a text selection.
                    if( m_nCaret != m_nSelStart )
                    {
                        DeleteSelectionText();
                        m_pDialog->SendEvent( EVENT_EDITBOX_CHANGE, TRUE, this );
                    }
                    else
                    {
                        // Deleting one character
                        if( m_Buffer.RemoveChar( m_nCaret ) )
                            m_pDialog->SendEvent( EVENT_EDITBOX_CHANGE, TRUE, this );
                    }
                    ResetCaretBlink();
                    bHandled = TRUE;
                    break;

                case VK_LEFT:
                    if( GetKeyState( VK_CONTROL ) < 0 )
                    {
                        // Control is down. Move the caret to a new item
                        // instead of a character.
                        m_Buffer.GetPriorItemPos( m_nCaret, &m_nCaret );
                        PlaceCaret( m_nCaret );
                    }
                    else if( m_nCaret > 0 )
                        PlaceCaret( m_nCaret - 1 );
                    if( GetKeyState( VK_SHIFT ) >= 0 )
                        // Shift is not down. Update selection
                        // start along with the caret.
                        m_nSelStart = m_nCaret;
                    ResetCaretBlink();
                    bHandled = TRUE;
                    break;

                case VK_RIGHT:
                    if( GetKeyState( VK_CONTROL ) < 0 )
                    {
                        // Control is down. Move the caret to a new item
                        // instead of a character.
                        m_Buffer.GetNextItemPos( m_nCaret, &m_nCaret );
                        PlaceCaret( m_nCaret );
                    }
                    else if( m_nCaret < m_Buffer.GetTextSize() )
                        PlaceCaret( m_nCaret + 1 );
                    if( GetKeyState( VK_SHIFT ) >= 0 )
                        // Shift is not down. Update selection
                        // start along with the caret.
                        m_nSelStart = m_nCaret;
                    ResetCaretBlink();
                    bHandled = TRUE;
                    break;

                case VK_UP:
                case VK_DOWN:
                    // Trap up and down arrows so that the dialog
                    // does not switch focus to another control.
                    bHandled = TRUE;
                    break;

                default:
                    bHandled = wParam != VK_ESCAPE;  // Let the application handle Esc.
            }
        }
    }
    return bHandled;
}


//--------------------------------------------------------------------------------------
BOOL CDXUTEditBox::HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    switch( Message )
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            {
                if( !m_bHasFocus )
                    m_pDialog->RequestFocus( this );

                if( !ContainsPoint( pt ) )
                    return FALSE;

                m_bMouseDrag = TRUE;
                SetCapture( DXUTGetHWND() );
                // Determine the character corresponding to the coordinates.
                int nCP, nTrail, nX1st;
                m_Buffer.CPtoX( m_nFirstVisible, FALSE, &nX1st );  // X offset of the 1st visible char
                if( SUCCEEDED( m_Buffer.XtoCP( pt.x - m_rcText.left + nX1st, &nCP, &nTrail ) ) )
                {
                    // Cap at the NULL character.
                    if( nTrail && nCP < m_Buffer.GetTextSize() )
                        PlaceCaret( nCP + 1 );
                    else
                        PlaceCaret( nCP );
                    m_nSelStart = m_nCaret;
                    ResetCaretBlink();
                }
                return TRUE;
            }

        case WM_LBUTTONUP:
            ReleaseCapture();
            m_bMouseDrag = FALSE;
            break;

        case WM_MOUSEMOVE:
            if( m_bMouseDrag )
            {
                // Determine the character corresponding to the coordinates.
                int nCP, nTrail, nX1st;
                m_Buffer.CPtoX( m_nFirstVisible, FALSE, &nX1st );  // X offset of the 1st visible char
                if( SUCCEEDED( m_Buffer.XtoCP( pt.x - m_rcText.left + nX1st, &nCP, &nTrail ) ) )
                {
                    // Cap at the NULL character.
                    if( nTrail && nCP < m_Buffer.GetTextSize() )
                        PlaceCaret( nCP + 1 );
                    else
                        PlaceCaret( nCP );
                }
            }
            break;
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
void CDXUTEditBox::OnFocusIn()
{
    CDXUTControl::OnFocusIn();

    ResetCaretBlink();
}


//--------------------------------------------------------------------------------------
BOOL CDXUTEditBox::MsgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    if( !m_bEnabled || !m_bVisible )
        return FALSE;

    switch( Message )
    {
            // Make sure that while editing, the keyup and keydown messages associated with
            // WM_CHAR messages don't go to any non-focused controls or cameras
        case WM_KEYUP:
        case WM_KEYDOWN:
            return TRUE;

        case WM_CHAR:
        {
            switch( ( WCHAR )wParam )
            {
                    // Backspace
                case VK_BACK:
                {
                    // If there's a selection, treat this
                    // like a delete key.
                    if( m_nCaret != m_nSelStart )
                    {
                        DeleteSelectionText();
                        m_pDialog->SendEvent( EVENT_EDITBOX_CHANGE, TRUE, this );
                    }
                    else if( m_nCaret > 0 )
                    {
                        // Move the caret, then delete the char.
                        PlaceCaret( m_nCaret - 1 );
                        m_nSelStart = m_nCaret;
                        m_Buffer.RemoveChar( m_nCaret );
                        m_pDialog->SendEvent( EVENT_EDITBOX_CHANGE, TRUE, this );
                    }
                    ResetCaretBlink();
                    break;
                }

                case 24:        // Ctrl-X Cut
                case VK_CANCEL: // Ctrl-C Copy
                    {
                        CopyToClipboard();

                        // If the key is Ctrl-X, delete the selection too.
                        if( ( WCHAR )wParam == 24 )
                        {
                            DeleteSelectionText();
                            m_pDialog->SendEvent( EVENT_EDITBOX_CHANGE, TRUE, this );
                        }

                        break;
                    }

                    // Ctrl-V Paste
                case 22:
                {
                    PasteFromClipboard();
                    m_pDialog->SendEvent( EVENT_EDITBOX_CHANGE, TRUE, this );
                    break;
                }

                    // Ctrl-A Select All
                case 1:
                    if( m_nSelStart == m_nCaret )
                    {
                        m_nSelStart = 0;
                        PlaceCaret( m_Buffer.GetTextSize() );
                    }
                    break;

                case VK_RETURN:
                    // Invoke the callback when the user presses Enter.
                    m_pDialog->SendEvent( EVENT_EDITBOX_STRING, TRUE, this );
                    break;

                    // Junk characters we don't want in the string
                case 26:  // Ctrl Z
                case 2:   // Ctrl B
                case 14:  // Ctrl N
                case 19:  // Ctrl S
                case 4:   // Ctrl D
                case 6:   // Ctrl F
                case 7:   // Ctrl G
                case 10:  // Ctrl J
                case 11:  // Ctrl K
                case 12:  // Ctrl L
                case 17:  // Ctrl Q
                case 23:  // Ctrl W
                case 5:   // Ctrl E
                case 18:  // Ctrl R
                case 20:  // Ctrl T
                case 25:  // Ctrl Y
                case 21:  // Ctrl U
                case 9:   // Ctrl I
                case 15:  // Ctrl O
                case 16:  // Ctrl P
                case 27:  // Ctrl [
                case 29:  // Ctrl ]
                case 28:  // Ctrl '\'
                    break;

                default:
                {
                    // If there's a selection and the user
                    // starts to type, the selection should
                    // be deleted.
                    if( m_nCaret != m_nSelStart )
                        DeleteSelectionText();

                    // If we are in overwrite mode and there is already
                    // a char at the caret's position, simply replace it.
                    // Otherwise, we insert the char as normal.
                    if( !m_bInsertMode && m_nCaret < m_Buffer.GetTextSize() )
                    {
                        m_Buffer[m_nCaret] = ( WCHAR )wParam;
                        PlaceCaret( m_nCaret + 1 );
                        m_nSelStart = m_nCaret;
                    }
                    else
                    {
                        // Insert the char
                        if( m_Buffer.InsertChar( m_nCaret, ( WCHAR )wParam ) )
                        {
                            PlaceCaret( m_nCaret + 1 );
                            m_nSelStart = m_nCaret;
                        }
                    }
                    ResetCaretBlink();
                    m_pDialog->SendEvent( EVENT_EDITBOX_CHANGE, TRUE, this );
                }
            }
            return TRUE;
        }
    }
    return FALSE;
}


//--------------------------------------------------------------------------------------
void CDXUTEditBox::Render( FLOAT fElapsedTime )
{
    if( m_bVisible == FALSE )
        return;

    HRESULT hr;
    int nSelStartX = 0, nCaretX = 0;  // Left and right X cordinates of the selection region

    CDXUTElement* pElement = GetElement( 0 );
    if( pElement )
    {
        m_Buffer.SetFontNode( m_pDialog->GetFont( pElement->iFont ) );
        PlaceCaret( m_nCaret );  // Call PlaceCaret now that we have the font info (node),
        // so that scrolling can be handled.
    }

    // Render the control graphics
    for( int e = 0; e < 9; ++e )
    {
        pElement = m_Elements.GetAt( e );
        pElement->TextureColor.Blend( DXUT_STATE_NORMAL, fElapsedTime );

        m_pDialog->DrawSprite( pElement, &m_rcRender[e], DXUT_FAR_BUTTON_DEPTH );
    }

    //
    // Compute the X coordinates of the first visible character.
    //
    int nXFirst;
    m_Buffer.CPtoX( m_nFirstVisible, FALSE, &nXFirst );

    //
    // Compute the X coordinates of the selection rectangle
    //
    hr = m_Buffer.CPtoX( m_nCaret, FALSE, &nCaretX );
    if( m_nCaret != m_nSelStart )
        hr = m_Buffer.CPtoX( m_nSelStart, FALSE, &nSelStartX );
    else
        nSelStartX = nCaretX;

    //
    // Render the selection rectangle
    //
    RECT rcSelection;  // Make this available for rendering selected text
    if( m_nCaret != m_nSelStart )
    {
        int nSelLeftX = nCaretX, nSelRightX = nSelStartX;
        // Swap if left is bigger than right
        if( nSelLeftX > nSelRightX )
        {
            int nTemp = nSelLeftX; nSelLeftX = nSelRightX; nSelRightX = nTemp;
        }

        SetRect( &rcSelection, nSelLeftX, m_rcText.top, nSelRightX, m_rcText.bottom );
        OffsetRect( &rcSelection, m_rcText.left - nXFirst, 0 );
        IntersectRect( &rcSelection, &m_rcText, &rcSelection );

        IDirect3DDevice9* pd3dDevice = m_pDialog->GetManager()->GetD3D9Device();
        if( pd3dDevice )
            pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
        m_pDialog->DrawRect( &rcSelection, m_SelBkColor );
        if( pd3dDevice )
            pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
    }

    //
    // Render the text
    //
    // Element 0 for text
    m_Elements.GetAt( 0 )->FontColor.Current = m_TextColor;
    m_pDialog->DrawText( m_Buffer.GetBuffer() + m_nFirstVisible, m_Elements.GetAt( 0 ), &m_rcText );

    // Render the selected text
    if( m_nCaret != m_nSelStart )
    {
        int nFirstToRender = __max( m_nFirstVisible, __min( m_nSelStart, m_nCaret ) );
        int nNumChatToRender = __max( m_nSelStart, m_nCaret ) - nFirstToRender;
        m_Elements.GetAt( 0 )->FontColor.Current = m_SelTextColor;
        m_pDialog->DrawText( m_Buffer.GetBuffer() + nFirstToRender,
                             m_Elements.GetAt( 0 ), &rcSelection, FALSE, nNumChatToRender );
    }

    //
    // Blink the caret
    //
    if( DXUTGetGlobalTimer()->GetAbsoluteTime() - m_dfLastBlink >= m_dfBlink )
    {
        m_bCaretOn = !m_bCaretOn;
        m_dfLastBlink = DXUTGetGlobalTimer()->GetAbsoluteTime();
    }

    //
    // Render the caret if this control has the focus
    //
    if( m_bHasFocus && m_bCaretOn && !s_bHideCaret )
    {
        // Start the rectangle with insert mode caret
        RECT rcCaret = { m_rcText.left - nXFirst + nCaretX - 1, m_rcText.top,
                m_rcText.left - nXFirst + nCaretX + 1, m_rcText.bottom };

        // If we are in overwrite mode, adjust the caret rectangle
        // to fill the entire character.
        if( !m_bInsertMode )
        {
            // Obtain the right edge X coord of the current character
            int nRightEdgeX;
            m_Buffer.CPtoX( m_nCaret, TRUE, &nRightEdgeX );
            rcCaret.right = m_rcText.left - nXFirst + nRightEdgeX;
        }

        m_pDialog->DrawRect( &rcCaret, m_CaretColor );
    }
}


#define IN_FLOAT_CHARSET( c ) \
    ( (c) == L'-' || (c) == L'.' || ( (c) >= L'0' && (c) <= L'9' ) )

void CDXUTEditBox::ParseFloatArray( FLOAT* pNumbers, int nCount )
{
    int nWritten = 0;  // Number of floats written
    const WCHAR* pToken, *pEnd;
    WCHAR wszToken[60];

    pToken = m_Buffer.GetBuffer();
    while( nWritten < nCount && *pToken != L'\0' )
    {
        // Skip leading spaces
        while( *pToken == L' ' )
            ++pToken;

        if( *pToken == L'\0' )
            break;

        // Locate the end of number
        pEnd = pToken;
        while( IN_FLOAT_CHARSET( *pEnd ) )
            ++pEnd;

        // Copy the token to our buffer
        int nTokenLen = __min( sizeof( wszToken ) / sizeof( wszToken[0] ) - 1, int( pEnd - pToken ) );
        wcscpy_s( wszToken, nTokenLen, pToken );
        *pNumbers = ( FLOAT )wcstod( wszToken, NULL );
        ++nWritten;
        ++pNumbers;
        pToken = pEnd;
    }
}


void CDXUTEditBox::SetTextFloatArray( const FLOAT* pNumbers, int nCount )
{
    WCHAR wszBuffer[512] = {0};
    WCHAR wszTmp[64];

    if( pNumbers == NULL )
        return;

    for( int i = 0; i < nCount; ++i )
    {
        swprintf_s( wszTmp, 64, L"%.4f ", pNumbers[i] );
        wcscat_s( wszBuffer, 512, wszTmp );
    }

    // Don't want the last space
    if( nCount > 0 && wcslen( wszBuffer ) > 0 )
        wszBuffer[wcslen( wszBuffer ) - 1] = 0;

    SetText( wszBuffer );
}

//-----------------------------------------------------------------------------
// Tab control class
//-----------------------------------------------------------------------------
CDXUTTabControl::CDXUTTabControl(CDXUTDialog *Parent /* = NULL */) : CDXUTControl(Parent)
{
    m_Type                  = DXUT_CONTROL_TAB;
    m_Style                 = TabControlVerticalLeft;
    m_ActiveTabIndex        = m_kInvalidTabIndex;
    m_ButtonWidthOverride   = DXUT_SIZE_ADJUST;
    m_ButtonHeightOverride  = DXUT_SIZE_ADJUST;
}

CDXUTTabControl::~CDXUTTabControl()
{
    m_Buttons.RemoveAll();
}

VOID CDXUTTabControl::Render(FLOAT ElapsedTime)
{
    CDXUTTabItem *ActiveTab;

    if (m_ActiveTabIndex == m_kInvalidTabIndex)
        return;

    if (m_ActiveTabIndex >= m_Buttons.GetSize())
        return;

    ActiveTab = m_Buttons[m_ActiveTabIndex]->GetTabBinded();
    if (ActiveTab == NULL)
        return;

    ActiveTab->OnRender(ElapsedTime);
}

BOOL CDXUTTabControl::MsgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    CDXUTTabItem *Tab;

    Tab = GetActiveTab();

    if (Tab == NULL)
        return FALSE;

    return Tab->MsgProc(hWnd, Message, wParam, lParam);
}

/*
BOOL CDXUTTabControl::HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    CDXUTTabItem *Tab;

    Tab = GetActiveTab();

    if (Tab == NULL)
        return FALSE;

    if (Tab->s_pControlFocus == NULL)
        return FALSE;

    return Tab->MsgProc(hWnd, Message, wParam, lParam);
}
*/

ULONG CDXUTTabControl::SetStyle(ULONG Style)
{
    if (Style >= (ULONG)TabControlStyleMax)
        return ~0u;

    Swap(m_Style, Style);
    UpdateControlsPos();

    return Style;
}

ULONG CDXUTTabControl::GetStyle()
{
    return m_Style;
}

VOID CDXUTTabControl::UpdateControlsPos()
{
    ULONG           Count;
    LONG            ButtonX, ButtonY;
    CDXUTTabButton *Button, **AddedButton;
    CDXUTTabItem   *Tab;

    Count = m_Buttons.GetSize();
    if (Count == 0)
    {
        m_ButtonWidth   = 0;
        m_ButtonHeight  = 0;
        m_DialogWidth   = 0;

        return;
    }

    m_ButtonInterval    = __min(GetHeight() / Count / Count, 10);
    m_ButtonHeight      = m_ButtonHeightOverride != DXUT_SIZE_ADJUST ? m_ButtonHeightOverride : ((GetHeight() - 5 - m_ButtonInterval) / Count);
    m_ButtonWidth       = m_ButtonWidthOverride != DXUT_SIZE_ADJUST ? m_ButtonWidthOverride : GetWidth() / 4;

    switch (m_Style)
    {
        case TabControlVerticalLeft:
            m_TabRect.left      = m_x + m_ButtonWidth;
            m_TabRect.right     = m_x + GetWidth();
            m_TabRect.top       = m_y;
            m_TabRect.bottom    = m_TabRect.top + GetHeight();
            break;
    }

    ButtonX = m_x + m_kButtonLeftInterval;
    ButtonY = m_y + m_kButtonTopInterval;
    AddedButton = m_Buttons.GetData();
    for (ULONG Count = m_Buttons.GetSize(); Count; ++AddedButton, --Count)
    {
        Button = *AddedButton;
        switch (m_Style)
        {
            case TabControlVerticalLeft:
                Tab = Button->GetTabBinded();
                if (Tab != NULL)
                {
                    Tab->SetDialogRect(m_TabRect);
                }

                Button->SetLocation(ButtonX, ButtonY);
                Button->SetSize(m_ButtonWidth, m_ButtonHeight);
                ButtonY += m_ButtonHeight + m_ButtonInterval;
                break;
        }
    }
}

VOID CDXUTTabControl::UpdateRects()
{
    __super::UpdateRects();
    UpdateControlsPos();
}

CDXUTTabItem* CDXUTTabControl::GetActiveTab()
{
    if (m_ActiveTabIndex == m_kInvalidTabIndex)
        return NULL;

    return m_Buttons[m_ActiveTabIndex]->GetTabBinded();
}

HRESULT CDXUTTabControl::SetActiveTab(ULONG TabIndex)
{
    ULONG           MaxIndex;
    CDXUTTabItem*   Tab;
    CDXUTTabButton* Button;

    MaxIndex = m_Buttons.GetSize();

    if (m_ActiveTabIndex == TabIndex)
        return S_OK;

    if (MaxIndex <= TabIndex)
        return E_FAIL;
/*
    if (m_ActiveTabIndex != m_kInvalidTabIndex)
    {
        Button = m_Buttons[m_ActiveTabIndex];
        Tab = Button->GetTabBinded();
        if (Tab != NULL)
            Tab->Refresh();
    }
*/
    m_ActiveTabIndex = TabIndex;
    Button = m_Buttons[TabIndex];
    Button->SetChecked(TRUE);
    Tab = Button->GetTabBinded();
    if (Tab == NULL)
        return S_OK;

    Tab->SetLocation(m_TabRect.left, m_TabRect.top);
    Tab->SetSize(RectWidth(m_TabRect), RectHeight(m_TabRect));
    Tab->SetParent(m_pDialog);

    m_pDialog->RequestFocus(this);

    return S_OK;
}

HRESULT CDXUTTabControl::SetActiveTab(CDXUTTabItem* Tab)
{
    return SetActiveTab(GetTabIndex(Tab));
}

HRESULT CDXUTTabControl::AddTab(CDXUTTabItem* Tab, PWSTR TabName, PULONG AddedTabIndex /* = NULL */)
{
    HRESULT         Result;
    ULONG           Index;
    CDXUTTabButton *Button, **AddedButton;

    AddedButton = m_Buttons.GetData();

    for (ULONG Count = m_Buttons.GetSize(); Count; ++AddedButton, --Count)
    {
        if ((*AddedButton)->GetTabBinded() == Tab)
        {
            if (AddedTabIndex != NULL)
                *AddedTabIndex = AddedButton - m_Buttons.GetData();

            return S_OK;
        }
    }

    Result = AddTabButton(0, TabName, 0, 0, 0, 0, FALSE, 0, FALSE, &Button);
    if (FAILED(Result))
        return Result;

    Button->BindTab(Tab);
    Tab->BindButton(Button);

    Index = m_Buttons.GetSize();

    if (AddedTabIndex != NULL)
        *AddedTabIndex = Index;

    m_Buttons.Add(Button);
    UpdateControlsPos();

    return S_OK;
}

HRESULT
CDXUTTabControl::
AddTabButton(
    UINT                ButtonGroup,
    PWSTR               Text,
    INT                 X,
    INT                 Y,
    INT                 Width,
    INT                 Height,
    BOOL                Checked,
    UINT                Hotkey,
    BOOL                IsDefault,
    CDXUTTabButton**    Created
)
{
    HRESULT hr = S_OK;

    CDXUTTabButton* Button = new CDXUTTabButton(this, m_pDialog);

    if (Button == NULL)
        return E_OUTOFMEMORY;

    hr = m_pDialog->AddControl(Button);
    if (FAILED(hr))
    {
        delete Button;
        return hr;
    }

    if (Created != NULL)
        *Created = Button;

    Button->SetID(-1);
    Button->SetText(Text);
    Button->SetButtonGroup(ButtonGroup);
    Button->SetLocation(X, Y);
    Button->SetSize(Width, Height);
    Button->SetHotkey(Hotkey);
    Button->SetChecked(Checked);
    Button->m_bIsDefault = IsDefault;

    return S_OK;
}

//-----------------------------------------------------------------------------
// CDXUTTabButton impl
//-----------------------------------------------------------------------------

CDXUTTabButton::
CDXUTTabButton(
    CDXUTTabControl *TabControl,
    CDXUTDialog     *Dialog
) :
    CDXUTRadioButton(Dialog)
{
    m_TabControl    = TabControl;
    m_TabItemBinded = NULL;
    m_Type          = DXUT_CONTROL_TAB_BUTTON;

    SetID(-1);
}

CDXUTTabButton::~CDXUTTabButton()
{
}

CDXUTTabItem* CDXUTTabButton::GetTabBinded()
{
    return m_TabItemBinded;
}

CDXUTTabItem* CDXUTTabButton::BindTab(CDXUTTabItem *TabItem)
{
    Swap(m_TabItemBinded, TabItem);
    return TabItem;
}

HRESULT CDXUTTabButton::OnInit()
{
    m_Type = DXUT_CONTROL_RADIOBUTTON;

    return S_OK;
}

BOOL CDXUTTabButton::HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    BOOL Handled = __super::HandleKeyboard(hWnd, Message, wParam, lParam);

    if (!Handled)
        return Handled;

    switch (Message)
    {
        case WM_KEYUP:
            m_TabControl->SetActiveTab(GetTabBinded());
            break;
    }

    return Handled;
}

BOOL CDXUTTabButton::HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam)
{
    BOOL Handled = __super::HandleMouse(hWnd, Message, pt, wParam, lParam);

    if (!Handled)
        return Handled;

    switch (Message)
    {
        case WM_LBUTTONDOWN:
            m_TabControl->SetActiveTab(GetTabBinded());
            break;
    }

    return Handled;
}

VOID CDXUTTabButton::UpdateRects()
{
    __super::UpdateRects();

    m_rcButton = m_rcBoundingBox;
    m_rcText = m_rcBoundingBox;
}

VOID CDXUTTabButton::Render(FLOAT ElapsedTime)
{
    ULONG ElementIndex;
    DXUT_CONTROL_STATE State;

    if (m_Elements.GetSize() == 0)
        return;

    State           = DXUT_STATE_NORMAL;
    ElementIndex    = TABBTN_ELEMENT_NORMAL;

    if (!GetVisible())
    {
        State = DXUT_STATE_HIDDEN;
    }
    else if (!GetEnabled())
    {
        State = DXUT_STATE_DISABLED;
    }
    else if (m_bChecked)
    {
        ElementIndex = TABBTN_ELEMENT_PRESSED;
    }
    else if (m_bMouseOver)
    {
        ElementIndex = TABBTN_ELEMENT_MOUSEOVER;
    }
    else if (m_bHasFocus)
    {
        State = DXUT_STATE_FOCUS;
    }

    CDXUTElement* Element = m_Elements.GetAt(ElementIndex);

    FLOAT BlendRate = (State == DXUT_STATE_PRESSED) ? 0.0f : 0.8f;

    BlendRate = 0.f;

    Element->TextureColor.Blend(State, ElapsedTime, BlendRate);
    Element->FontColor.Blend(State, ElapsedTime, BlendRate);

    m_pDialog->DrawSprite(Element, &m_rcButton, DXUT_NEAR_BUTTON_DEPTH);
    m_pDialog->DrawText(GetText(), Element, &m_rcText, TRUE);
}

//-----------------------------------------------------------------------------
// end of control impl
//-----------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void CUniBuffer::Initialize()
{
/*
    if( s_hDll ) // Only need to do once
        return;

    s_hDll = LoadLibrary( UNISCRIBE_DLLNAME );
    if( s_hDll )
    {
        FARPROC Temp;
        GETPROCADDRESS( s_hDll, ScriptApplyDigitSubstitution, Temp );
        GETPROCADDRESS( s_hDll, ScriptStringAnalyse, Temp );
        GETPROCADDRESS( s_hDll, ScriptStringCPtoX, Temp );
        GETPROCADDRESS( s_hDll, ScriptStringXtoCP, Temp );
        GETPROCADDRESS( s_hDll, ScriptStringFree, Temp );
        GETPROCADDRESS( s_hDll, ScriptString_pLogAttr, Temp );
        GETPROCADDRESS( s_hDll, ScriptString_pcOutChars, Temp );
    }
*/
}


//--------------------------------------------------------------------------------------
void CUniBuffer::Uninitialize()
{
/*
    if( s_hDll )
    {
        PLACEHOLDERPROC( ScriptApplyDigitSubstitution );
        PLACEHOLDERPROC( ScriptStringAnalyse );
        PLACEHOLDERPROC( ScriptStringCPtoX );
        PLACEHOLDERPROC( ScriptStringXtoCP );
        PLACEHOLDERPROC( ScriptStringFree );
        PLACEHOLDERPROC( ScriptString_pLogAttr );
        PLACEHOLDERPROC( ScriptString_pcOutChars );

        FreeLibrary( s_hDll );
        s_hDll = NULL;
    }
*/
}


//--------------------------------------------------------------------------------------
BOOL CUniBuffer::SetBufferSize( int nNewSize )
{
    // If the current size is already the maximum allowed,
    // we can't possibly allocate more.
    if( m_nBufferSize == DXUT_MAX_EDITBOXLENGTH )
        return FALSE;

    int nAllocateSize = ( nNewSize == -1 || nNewSize < m_nBufferSize * 2 ) ? ( m_nBufferSize ? m_nBufferSize *
                                                                               2 : 256 ) : nNewSize * 2;

    // Cap the buffer size at the maximum allowed.
    if( nAllocateSize > DXUT_MAX_EDITBOXLENGTH )
        nAllocateSize = DXUT_MAX_EDITBOXLENGTH;

    WCHAR* pTempBuffer = new WCHAR[nAllocateSize];
    if( !pTempBuffer )
        return FALSE;

    ZeroMemory( pTempBuffer, sizeof( WCHAR ) * nAllocateSize );

    if( m_pwszBuffer )
    {
        CopyMemory( pTempBuffer, m_pwszBuffer, m_nBufferSize * sizeof( WCHAR ) );
        delete[] m_pwszBuffer;
    }

    m_pwszBuffer = pTempBuffer;
    m_nBufferSize = nAllocateSize;
    return TRUE;
}


//--------------------------------------------------------------------------------------
// Uniscribe -- Analyse() analyses the string in the buffer
//--------------------------------------------------------------------------------------
HRESULT CUniBuffer::Analyse()
{
    if( m_Analysis )
        ScriptStringFree( &m_Analysis );

    SCRIPT_CONTROL ScriptControl; // For uniscribe
    SCRIPT_STATE ScriptState;   // For uniscribe
    ZeroMemory( &ScriptControl, sizeof( ScriptControl ) );
    ZeroMemory( &ScriptState, sizeof( ScriptState ) );
    ScriptApplyDigitSubstitution( NULL, &ScriptControl, &ScriptState );

    if( !m_pFontNode )
        return E_FAIL;

    HDC hDC = m_pFontNode->Font10 ? m_pFontNode->Font10->GetDC() :
        ( m_pFontNode->Font9 ? m_pFontNode->Font9->GetDC() : NULL );
    HRESULT hr = ScriptStringAnalyse( hDC,
                                       m_pwszBuffer,
                                       lstrlenW( m_pwszBuffer ) + 1,  // NULL is also analyzed.
                                       lstrlenW( m_pwszBuffer ) * 3 / 2 + 16,
                                       -1,
                                       SSA_BREAK | SSA_GLYPHS | SSA_FALLBACK | SSA_LINK,
                                       0,
                                       &ScriptControl,
                                       &ScriptState,
                                       NULL,
                                       NULL,
                                       NULL,
                                       &m_Analysis );
    if( SUCCEEDED( hr ) )
        m_bAnalyseRequired = FALSE;  // Analysis is up-to-date
    return hr;
}


//--------------------------------------------------------------------------------------
CUniBuffer::CUniBuffer( int nInitialSize )
{
    CUniBuffer::Initialize();  // ensure static vars are properly init'ed first

    m_nBufferSize = 0;
    m_pwszBuffer = NULL;
    m_bAnalyseRequired = TRUE;
    m_Analysis = NULL;
    m_pFontNode = NULL;

    if( nInitialSize > 0 )
        SetBufferSize( nInitialSize );
}


//--------------------------------------------------------------------------------------
CUniBuffer::~CUniBuffer()
{
    delete[] m_pwszBuffer;
    if( m_Analysis )
        ScriptStringFree( &m_Analysis );
}


//--------------------------------------------------------------------------------------
WCHAR& CUniBuffer::operator[]( int n )  // No param checking
{
    // This version of operator[] is called only
    // if we are asking for write access, so
    // re-analysis is required.
    m_bAnalyseRequired = TRUE;
    return m_pwszBuffer[n];
}


//--------------------------------------------------------------------------------------
void CUniBuffer::Clear()
{
    *m_pwszBuffer = L'\0';
    m_bAnalyseRequired = TRUE;
}


//--------------------------------------------------------------------------------------
// Inserts the char at specified index.
// If nIndex == -1, insert to the end.
//--------------------------------------------------------------------------------------
BOOL CUniBuffer::InsertChar( int nIndex, WCHAR wChar )
{
    assert( nIndex >= 0 );

    if( nIndex < 0 || nIndex > lstrlenW( m_pwszBuffer ) )
        return FALSE;  // invalid index

    // Check for maximum length allowed
    if( GetTextSize() + 1 >= DXUT_MAX_EDITBOXLENGTH )
        return FALSE;

    if( lstrlenW( m_pwszBuffer ) + 1 >= m_nBufferSize )
    {
        if( !SetBufferSize( -1 ) )
            return FALSE;  // out of memory
    }

    assert( m_nBufferSize >= 2 );

    // Shift the characters after the index, start by copying the null terminator
    WCHAR* dest = m_pwszBuffer + lstrlenW( m_pwszBuffer ) + 1;
    WCHAR* stop = m_pwszBuffer + nIndex;
    WCHAR* src = dest - 1;

    while( dest > stop )
    {
        *dest-- = *src--;
    }

    // Set new character
    m_pwszBuffer[ nIndex ] = wChar;
    m_bAnalyseRequired = TRUE;

    return TRUE;
}


//--------------------------------------------------------------------------------------
// Removes the char at specified index.
// If nIndex == -1, remove the last char.
//--------------------------------------------------------------------------------------
BOOL CUniBuffer::RemoveChar( int nIndex )
{
    if( !lstrlenW( m_pwszBuffer ) || nIndex < 0 || nIndex >= lstrlenW( m_pwszBuffer ) )
        return FALSE;  // Invalid index

    MoveMemory( m_pwszBuffer + nIndex, m_pwszBuffer + nIndex + 1, sizeof( WCHAR ) *
                ( lstrlenW( m_pwszBuffer ) - nIndex ) );
    m_bAnalyseRequired = TRUE;
    return TRUE;
}


//--------------------------------------------------------------------------------------
// Inserts the first nCount characters of the string pStr at specified index.
// If nCount == -1, the entire string is inserted.
// If nIndex == -1, insert to the end.
//--------------------------------------------------------------------------------------
BOOL CUniBuffer::InsertString( int nIndex, const WCHAR* pStr, int nCount )
{
    assert( nIndex >= 0 );
    if( nIndex < 0 )
        return FALSE;

    if( nIndex > lstrlenW( m_pwszBuffer ) )
        return FALSE;  // invalid index

    if( -1 == nCount )
        nCount = lstrlenW( pStr );

    // Check for maximum length allowed
    if( GetTextSize() + nCount >= DXUT_MAX_EDITBOXLENGTH )
        return FALSE;

    if( lstrlenW( m_pwszBuffer ) + nCount >= m_nBufferSize )
    {
        if( !SetBufferSize( lstrlenW( m_pwszBuffer ) + nCount + 1 ) )
            return FALSE;  // out of memory
    }

    MoveMemory( m_pwszBuffer + nIndex + nCount, m_pwszBuffer + nIndex, sizeof( WCHAR ) *
                ( lstrlenW( m_pwszBuffer ) - nIndex + 1 ) );
    CopyMemory( m_pwszBuffer + nIndex, pStr, nCount * sizeof( WCHAR ) );
    m_bAnalyseRequired = TRUE;

    return TRUE;
}


//--------------------------------------------------------------------------------------
BOOL CUniBuffer::SetText( LPCWSTR wszText )
{
    assert( wszText != NULL );

    int nRequired = int( wcslen( wszText ) + 1 );

    // Check for maximum length allowed
    if( nRequired >= DXUT_MAX_EDITBOXLENGTH )
        return FALSE;

    while( GetBufferSize() < nRequired )
        if( !SetBufferSize( -1 ) )
            break;
    // Check again in case out of memory occurred inside while loop.
    if( GetBufferSize() >= nRequired )
    {
        wcscpy_s( m_pwszBuffer, GetBufferSize(), wszText );
        m_bAnalyseRequired = TRUE;
        return TRUE;
    }
    else
        return FALSE;
}


//--------------------------------------------------------------------------------------
HRESULT CUniBuffer::CPtoX( int nCP, BOOL bTrail, int* pX )
{
    assert( pX );
    *pX = 0;  // Default

    HRESULT hr = S_OK;
    if( m_bAnalyseRequired )
        hr = Analyse();

    if( SUCCEEDED( hr ) )
        hr = ScriptStringCPtoX( m_Analysis, nCP, bTrail, pX );

    return hr;
}


//--------------------------------------------------------------------------------------
HRESULT CUniBuffer::XtoCP( int nX, int* pCP, int* pnTrail )
{
    assert( pCP && pnTrail );
    *pCP = 0; *pnTrail = FALSE;  // Default

    HRESULT hr = S_OK;
    if( m_bAnalyseRequired )
        hr = Analyse();

    if( SUCCEEDED( hr ) )
        hr = ScriptStringXtoCP( m_Analysis, nX, pCP, pnTrail );

    // If the coordinate falls outside the text region, we
    // can get character positions that don't exist.  We must
    // filter them here and convert them to those that do exist.
    if( *pCP == -1 && *pnTrail == TRUE )
    {
        *pCP = 0; *pnTrail = FALSE;
    }
    else if( *pCP > lstrlenW( m_pwszBuffer ) && *pnTrail == FALSE )
    {
        *pCP = lstrlenW( m_pwszBuffer ); *pnTrail = TRUE;
    }

    return hr;
}


//--------------------------------------------------------------------------------------
void CUniBuffer::GetPriorItemPos( int nCP, int* pPrior )
{
    *pPrior = nCP;  // Default is the char itself

    if( m_bAnalyseRequired )
        if( FAILED( Analyse() ) )
            return;

    const SCRIPT_LOGATTR* pLogAttr = ScriptString_pLogAttr( m_Analysis );
    if( !pLogAttr )
        return;

    if( !ScriptString_pcOutChars( m_Analysis ) )
        return;
    int nInitial = *ScriptString_pcOutChars( m_Analysis );
    if( nCP - 1 < nInitial )
        nInitial = nCP - 1;
    for( int i = nInitial; i > 0; --i )
        if( pLogAttr[i].fWordStop ||       // Either the fWordStop flag is set
            ( !pLogAttr[i].fWhiteSpace &&  // Or the previous char is whitespace but this isn't.
              pLogAttr[i - 1].fWhiteSpace ) )
        {
            *pPrior = i;
            return;
        }
    // We have reached index 0.  0 is always a break point, so simply return it.
    *pPrior = 0;
}


//--------------------------------------------------------------------------------------
void CUniBuffer::GetNextItemPos( int nCP, int* pPrior )
{
    *pPrior = nCP;  // Default is the char itself

    HRESULT hr = S_OK;
    if( m_bAnalyseRequired )
        hr = Analyse();
    if( FAILED( hr ) )
        return;

    const SCRIPT_LOGATTR* pLogAttr = ScriptString_pLogAttr( m_Analysis );
    if( !pLogAttr )
        return;

    if( !ScriptString_pcOutChars( m_Analysis ) )
        return;
    int nInitial = *ScriptString_pcOutChars( m_Analysis );
    if( nCP + 1 < nInitial )
        nInitial = nCP + 1;

    int i = nInitial;
    int limit = *ScriptString_pcOutChars( m_Analysis );
    while( limit > 0 && i < limit - 1 )
    {
        if( pLogAttr[i].fWordStop )      // Either the fWordStop flag is set
        {
            *pPrior = i;
            return;
        }
        else if( pLogAttr[i].fWhiteSpace &&  // Or this whitespace but the next char isn't.
                 !pLogAttr[i + 1].fWhiteSpace )
        {
            *pPrior = i + 1;  // The next char is a word stop
            return;
        }

        ++i;
        limit = *ScriptString_pcOutChars( m_Analysis );
    }
    // We have reached the end. It's always a word stop, so simply return it.
    *pPrior = *ScriptString_pcOutChars( m_Analysis ) - 1;
}


//--------------------------------------------------------------------------------------
void CDXUTEditBox::ResetCaretBlink()
{
    m_bCaretOn = TRUE;
    m_dfLastBlink = DXUTGetGlobalTimer()->GetAbsoluteTime();
}


//--------------------------------------------------------------------------------------
void DXUTBlendColor::Init( D3DCOLOR defaultColor, D3DCOLOR disabledColor, D3DCOLOR hiddenColor )
{
    for( int i = 0; i < MAX_CONTROL_STATES; i++ )
    {
        States[ i ] = defaultColor;
    }

    States[ DXUT_STATE_DISABLED ] = disabledColor;
    States[ DXUT_STATE_HIDDEN ] = hiddenColor;
    Current = hiddenColor;
}


//--------------------------------------------------------------------------------------
void DXUTBlendColor::Blend( UINT iState, FLOAT fElapsedTime, FLOAT fRate )
{
    D3DXCOLOR destColor = States[ iState ];
    D3DXColorLerp( &Current, &Current, &destColor, 1.0f - powf( fRate, 30 * fElapsedTime ) );
}



//--------------------------------------------------------------------------------------
void CDXUTElement::SetTexture( UINT iTexture, RECT* prcTexture, D3DCOLOR defaultTextureColor )
{
    this->iTexture = iTexture;

    if( prcTexture )
        rcTexture = *prcTexture;
    else
        SetRectEmpty( &rcTexture );

    TextureColor.Init( defaultTextureColor );
}


//--------------------------------------------------------------------------------------
void CDXUTElement::SetFont( UINT iFont, D3DCOLOR defaultFontColor, DWORD dwTextFormat )
{
    this->iFont = iFont;
    this->dwTextFormat = dwTextFormat;

    FontColor.Init( defaultFontColor );
}


//--------------------------------------------------------------------------------------
void CDXUTElement::Refresh()
{
    TextureColor.Current = TextureColor.States[ DXUT_STATE_HIDDEN ];
    FontColor.Current = FontColor.States[ DXUT_STATE_HIDDEN ];
}



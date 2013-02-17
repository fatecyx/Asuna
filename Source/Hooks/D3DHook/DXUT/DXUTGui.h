//--------------------------------------------------------------------------------------
// File: DXUTgui.h
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#ifndef DXUT_GUI_H
#define DXUT_GUI_H

#include "../DXUTLite.h"
#include <usp10.h>
#include <dimm.h>

#pragma warning(disable:4201)

FORCEINLINE int RectWidth(RECT& rc)
{
    return rc.right - rc.left;
}

FORCEINLINE int RectHeight(RECT& rc)
{
    return rc.bottom - rc.top;
}

//--------------------------------------------------------------------------------------
// Defines and macros
//--------------------------------------------------------------------------------------
#define EVENT_BUTTON_CLICKED                0x0101
#define EVENT_COMBOBOX_SELECTION_CHANGED    0x0201
#define EVENT_RADIOBUTTON_CHANGED           0x0301
#define EVENT_CHECKBOX_CHANGED              0x0401
#define EVENT_SLIDER_VALUE_CHANGED          0x0501
#define EVENT_EDITBOX_STRING                0x0601
// EVENT_EDITBOX_CHANGE is sent when the listbox content changes
// due to user input.
#define EVENT_EDITBOX_CHANGE                0x0602
#define EVENT_LISTBOX_ITEM_DBLCLK           0x0701
// EVENT_LISTBOX_SELECTION is fired off when the selection changes in
// a single selection list box.
#define EVENT_LISTBOX_SELECTION             0x0702
#define EVENT_LISTBOX_SELECTION_END         0x0703


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
class CDXUTDialogResourceManager;
class CDXUTControl;
class CDXUTButton;
class CDXUTStatic;
class CDXUTCheckBox;
class CDXUTRadioButton;
class CDXUTComboBox;
class CDXUTSlider;
class CDXUTEditBox;
class CDXUTListBox;
class CDXUTScrollBar;
class CDXUTTabControl;
class CDXUTElement;
struct DXUTElementHolder;
struct DXUTTextureNode;
struct DXUTFontNode;

typedef
VOID
(CALLBACK
*PCALLBACKDXUTGUIEVENT)(
    ULONG_PTR       Event,
    LONG_PTR        ControlID,
    CDXUTControl*   Control,
    PVOID           UserContext
);


//--------------------------------------------------------------------------------------
// Enums for pre-defined control types
//--------------------------------------------------------------------------------------
enum DXUT_CONTROL_TYPE
{
    DXUT_CONTROL_BUTTON,
    DXUT_CONTROL_STATIC,
    DXUT_CONTROL_CHECKBOX,
    DXUT_CONTROL_RADIOBUTTON,
    DXUT_CONTROL_COMBOBOX,
    DXUT_CONTROL_SLIDER,
    DXUT_CONTROL_EDITBOX,
    DXUT_CONTROL_IMEEDITBOX,
    DXUT_CONTROL_LISTBOX,
    DXUT_CONTROL_SCROLLBAR,
    DXUT_CONTROL_TAB,
    DXUT_CONTROL_TAB_BUTTON,
};

enum DXUT_CONTROL_STATE
{
    DXUT_STATE_NORMAL = 0,
    DXUT_STATE_DISABLED,
    DXUT_STATE_HIDDEN,
    DXUT_STATE_FOCUS,
    DXUT_STATE_MOUSEOVER,
    DXUT_STATE_PRESSED,
};

enum
{
    DXUT_SIZE_ADJUST            = -1,
    DXUT_DEFAULT_RESOURCE       = 0xFFFF,
    DXUT_MAXIMUN_CONTROL_ID     = 0xFFFF,
    DXUT_CONTROL_ID_USER        = 0x4000,
};

enum
{
    DXUT_CAPTION_LEFT   = 0,
    DXUT_CAPTION_MIDDLE = 1,
    DXUT_CAPTION_RIGHT  = 2,

    DXUT_CAPTION_ELEMENT_COUNT,
};

enum
{
    DXUT_DIALOG_FRAME_LEFT          = 0,
    DXUT_DIALOG_FRAME_TOP           = 1,
    DXUT_DIALOG_FRAME_RIGHT         = 2,
    DXUT_DIALOG_FRAME_BOTTOM        = 3,
    DXUT_DIALOG_FRAME_LEFT_TOP      = 4,
    DXUT_DIALOG_FRAME_RIGHT_TOP     = 5,
    DXUT_DIALOG_FRAME_RIGHT_BOTTOM  = 6,
    DXUT_DIALOG_FRAME_LEFT_BOTTOM   = 7,

    DXUT_DIALOG_FRAME_ELEMENT_COUNT,
    DXUT_DIALOG_FRAME_ELEMENT_TOP_RIGHT_PART = 8,

    DXUT_FRAME_DONT_DRAW_CAPTION    = 1 << 0,
};

#define DXUT_INVALID_INDEX      ~0u
#define DXUT_INVALID_TEXTURE_ID ~0u
#define DXUT_INVALID_FONT_ID    ~0u

#define MAX_CONTROL_STATES 6

struct DXUTBlendColor
{
    void        Init( D3DCOLOR defaultColor, D3DCOLOR disabledColor = D3DCOLOR_ARGB( 200, 128, 128, 128 ),
                      D3DCOLOR hiddenColor = 0 );
    void        Blend( UINT iState, FLOAT fElapsedTime, FLOAT fRate = 0.7f );

    D3DCOLOR    States[ MAX_CONTROL_STATES ]; // Modulate colors for all possible control states
    D3DXCOLOR Current;
};


//-----------------------------------------------------------------------------
// Contains all the display tweakables for a sub-control
//-----------------------------------------------------------------------------
class DXUT_API CDXUTElement
{
public:
    void    SetTexture( UINT iTexture, RECT* prcTexture, D3DCOLOR defaultTextureColor = D3DCOLOR_ARGB( 255, 255, 255,
                                                                                                       255 ) );
    void    SetFont( UINT iFont, D3DCOLOR defaultFontColor = D3DCOLOR_ARGB( 255, 255, 255,
                                                                            255 ), DWORD dwTextFormat = DT_CENTER |
                     DT_VCENTER );

    void    Refresh();

    UINT iTexture;          // Index of the texture for this Element
    UINT iFont;             // Index of the font for this Element
    DWORD dwTextFormat;     // The format argument to DrawText

    RECT rcTexture;         // Bounding rect of this element on the composite texture

    DXUTBlendColor TextureColor;
    DXUTBlendColor FontColor;
};

typedef struct
{
    PWSTR       Path;
    RECT        Rect;
    LONG        ShadowWidth;
    D3DCOLOR    Color;

} DXUT_TEXTURE_INFO, *PDXUT_TEXTURE_INFO;

typedef struct
{
    CDXUTElement    Element;
    RECT            Position;
    LONG            ShadowWidth;

} DXUT_ELEMENT_INFO, *PDXUT_ELEMENT_INFO;

inline BOOL IsElementValid(CDXUTElement &Element)
{
    return Element.iTexture != DXUT_INVALID_TEXTURE_ID;
}

inline BOOL IsElementValid(CDXUTElement *Element)
{
    return Element->iTexture != DXUT_INVALID_TEXTURE_ID;
}

//-----------------------------------------------------------------------------
// All controls must be assigned to a dialog, which handles
// input and rendering for the controls.
//-----------------------------------------------------------------------------
class DXUT_API CDXUTDialog
{
    friend class CDXUTDialogResourceManager;

public:
    CDXUTDialog(CDXUTDialog *Parent = NULL);
    ~CDXUTDialog();

    // Need to call this now
    void                Init( CDXUTDialogResourceManager* pManager, BOOL bRegisterDialog = TRUE );
    void                Init( CDXUTDialogResourceManager* pManager, BOOL bRegisterDialog,
                              LPCWSTR pszControlTextureFilename );
    void                Init( CDXUTDialogResourceManager* pManager, BOOL bRegisterDialog,
                              LPCWSTR szControlTextureResourceName, HMODULE hControlTextureResourceModule );

    // Windows message handler
    BOOL                MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

    // Control creation
    HRESULT             AddStatic( int ID, LPCWSTR strText, int x, int y, int width, int height, BOOL bIsDefault=FALSE,
                                   CDXUTStatic** ppCreated=NULL );
    HRESULT             AddButton( int ID, LPCWSTR strText, int x, int y, int width, int height, UINT nHotkey=0,
                                   BOOL bIsDefault=FALSE, CDXUTButton** ppCreated=NULL );
    HRESULT             AddCheckBox( int ID, LPCWSTR strText, int x, int y, int width, int height, BOOL bChecked=FALSE,
                                     UINT nHotkey=0, BOOL bIsDefault=FALSE, CDXUTCheckBox** ppCreated=NULL );
    HRESULT             AddRadioButton( int ID, UINT nButtonGroup, LPCWSTR strText, int x, int y, int width,
                                        int height, BOOL bChecked=FALSE, UINT nHotkey=0, BOOL bIsDefault=FALSE,
                                        CDXUTRadioButton** ppCreated=NULL );
    HRESULT             AddComboBox( int ID, int x, int y, int width, int height, UINT nHotKey=0, BOOL bIsDefault=
                                     FALSE, CDXUTComboBox** ppCreated=NULL );
    HRESULT             AddSlider( int ID, int x, int y, int width, int height, int min=0, int max=100, int value=50,
                                   BOOL bIsDefault=FALSE, CDXUTSlider** ppCreated=NULL );
    //      AddIMEEditBox has been renamed into DXUTguiIME.cpp as CDXUTIMEEditBox::CreateIMEEditBox
    HRESULT             AddEditBox( int ID, LPCWSTR strText, int x, int y, int width, int height, BOOL bIsDefault=
                                    FALSE, CDXUTEditBox** ppCreated=NULL );
    HRESULT             AddListBox( int ID, int x, int y, int width, int height, DWORD dwStyle=0,
                                    CDXUTListBox** ppCreated=NULL );

    HRESULT
    AddTabControl(
        INT                 ID,
        INT                 X,
        INT                 Y,
        INT                 Width,
        INT                 Height,
        ULONG               Style = 0,
        CDXUTTabControl   **Created = NULL
    );

    HRESULT             AddControl( CDXUTControl* pControl );
    HRESULT             InitControl( CDXUTControl* pControl );

    // Control retrieval
    CDXUTDialog* SetParent(CDXUTDialog *Parent)
    {
        Swap(m_ParentDialog, Parent);
        return Parent;
    }

    CDXUTDialog* GetParent()
    {
        return m_ParentDialog;
    }

    CDXUTDialog* GetTopLevelParent()
    {
        CDXUTDialog *Parent = m_ParentDialog;

        if (Parent == NULL)
            return Parent;

        while (Parent->m_ParentDialog != NULL)
            Parent = Parent->m_ParentDialog;

        return Parent;
    }

    CDXUTStatic* GetStatic( int ID )
    {
        return ( CDXUTStatic* )GetControl( ID, DXUT_CONTROL_STATIC );
    }

    CDXUTButton* GetButton( int ID )
    {
        return ( CDXUTButton* )GetControl( ID, DXUT_CONTROL_BUTTON );
    }

    CDXUTCheckBox* GetCheckBox( int ID )
    {
        return ( CDXUTCheckBox* )GetControl( ID, DXUT_CONTROL_CHECKBOX );
    }

    CDXUTRadioButton* GetRadioButton( int ID )
    {
        return ( CDXUTRadioButton* )GetControl( ID, DXUT_CONTROL_RADIOBUTTON );
    }

    CDXUTComboBox* GetComboBox( int ID )
    {
        return ( CDXUTComboBox* )GetControl( ID, DXUT_CONTROL_COMBOBOX );
    }

    CDXUTSlider* GetSlider( int ID )
    {
        return ( CDXUTSlider* )GetControl( ID, DXUT_CONTROL_SLIDER );
    }

    CDXUTEditBox* GetEditBox( int ID )
    {
        return ( CDXUTEditBox* )GetControl( ID, DXUT_CONTROL_EDITBOX );
    }

    CDXUTListBox* GetListBox( int ID )
    {
        return ( CDXUTListBox* )GetControl( ID, DXUT_CONTROL_LISTBOX );
    }

    CDXUTControl* GetControl( int ID );
    CDXUTControl* GetControl( int ID, UINT nControlType );
    CDXUTControl* GetControlAtPoint( POINT pt );

    BOOL                GetControlEnabled( int ID );
    void                SetControlEnabled( int ID, BOOL bEnabled );

    void                ClearRadioButtonGroup( UINT nGroup );
    void                ClearComboBox( int ID );

    // Access the default display Elements used when adding new controls
    HRESULT             SetDefaultElement( UINT nControlType, UINT iElement, CDXUTElement* pElement );
    CDXUTElement*       GetDefaultElement( UINT nControlType, UINT iElement );

    // Methods called by controls
    void                SendEvent(UINT nEvent, BOOL bTriggeredByUser, CDXUTControl* pControl, CDXUTDialog *ChildEvent = NULL);
    void                RequestFocus( CDXUTControl* pControl );

    // Render helpers
    HRESULT             DrawRect( RECT* pRect, D3DCOLOR color );
    HRESULT             DrawRect9( RECT* pRect, D3DCOLOR color );
    HRESULT             DrawRect10( RECT* pRect, D3DCOLOR color );
    HRESULT             DrawPolyLine( POINT* apPoints, UINT nNumPoints, D3DCOLOR color );
    HRESULT             DrawSprite( CDXUTElement* pElement, RECT* prcDest, FLOAT fDepth );
    HRESULT             DrawSprite9( CDXUTElement* pElement, RECT* prcDest );
    HRESULT             DrawSprite10( CDXUTElement* pElement, RECT* prcDest, FLOAT fDepth );
    HRESULT             CalcTextRect( LPCWSTR strText, CDXUTElement* pElement, RECT* prcDest, int nCount = -1 );
    HRESULT             DrawText( LPCWSTR strText, CDXUTElement* pElement, RECT* prcDest, BOOL bShadow = FALSE,
                                  int nCount = -1 );
    HRESULT             DrawText9( LPCWSTR strText, CDXUTElement* pElement, RECT* prcDest, BOOL bShadow = FALSE,
                                   int nCount = -1 );
    HRESULT             DrawText10( LPCWSTR strText, CDXUTElement* pElement, RECT* prcDest, BOOL bShadow = FALSE,
                                    int nCount = -1 );

    // adjust the rect if parent's caption is enabled
    VOID AdjustChildRect(PRECT rc)
    {
        CDXUTDialog *Parent;

        Parent = GetParent();
        while (Parent != NULL)
        {
            if (Parent->IsCaptionEanbled())
                OffsetRect(rc, 0, Parent->GetCaptionHeightAboveFrame());
            Parent = Parent->GetParent();
        }
    }

    VOID AdjustChildPoint(PPOINT pt)
    {
        CDXUTDialog *Parent;

        Parent = GetParent();
        while (Parent != NULL)
        {
            pt->y -= Parent->m_y;
            pt->x -= Parent->m_x;
            Parent = Parent->GetParent();
        }
    }

    VOID AdjustParentCaptionPoint(PPOINT pt)
    {
        CDXUTDialog *Parent;

        Parent = GetParent();
        while (Parent != NULL)
        {
            if (Parent->IsCaptionEanbled())
                pt->y -= Parent->GetCaptionHeightAboveFrame();

            Parent = Parent->GetParent();
        }
    }

    // Attributes
    BOOL GetVisible()
    {
        return m_bVisible;
    }

    void SetVisible( BOOL bVisible )
    {
        m_bVisible = bVisible;
    }

    BOOL GetMinimized()
    {
        return m_bMinimized;
    }

    void SetMinimized( BOOL bMinimized )
    {
        m_bMinimized = bMinimized;
    }

    void SetBackgroundColors( D3DCOLOR colorAllCorners )
    {
        SetBackgroundColors( colorAllCorners, colorAllCorners, colorAllCorners, colorAllCorners );
    }

    void SetBackgroundColors( D3DCOLOR colorTopLeft, D3DCOLOR colorTopRight, D3DCOLOR colorBottomLeft,
                                             D3DCOLOR colorBottomRight );
    void EnableCaption(BOOL bEnable)
    {
        m_bCaption = bEnable;
    }

    BOOL IsCaptionEanbled()
    {
        return m_bCaption;
    }

    LONG GetCaptionWidth()
    {
        return m_CaptionRect.right == DXUT_SIZE_ADJUST ? (GetWidth() - m_CaptionRect.left) : RectWidth(m_CaptionRect);
    }

    LONG GetCaptionHeight()
    {
        return RectHeight(m_CaptionRect);
    }

    LONG GetCaptionHeightAboveFrame()
    {
        return GetCaptionHeight() - m_CaptionRect.top;
    }

    RECT GetCaptionRect()
    {
        RECT CaptionRect;

        CaptionRect = m_CaptionRect;
        CaptionRect.right = CaptionRect.left + GetCaptionWidth();

        return CaptionRect;
    }

    NoInline RECT GetCaptionRectAbsolute()
    {
        RECT CaptionRect = GetCaptionRect();

        OffsetRect(&CaptionRect, m_x, m_y);

        return CaptionRect;
    }

    void SetCaptionRect(RECT &CaptionRect)
    {
        m_CaptionRect = CaptionRect;
    }

    void SetCaptionText( const WCHAR* pwszText )
    {
        RtlSetUnicodeString(&m_CaptionText, pwszText);
    }

    HRESULT
    SetElementInfoByTexture(
        PDXUT_ELEMENT_INFO  Element,
        PDXUT_TEXTURE_INFO  Texture,
        ULONG               Count,
        D3DCOLOR            Color = D3DCOLOR_ARGB(255, 255, 255, 255)
    );

    PDXUT_ELEMENT_INFO GetCaptionTexture()
    {
        return m_CaptionElement;
    }

    HRESULT
    SetCaptionTexture(
        DXUT_TEXTURE_INFO   CaptionTexture[DXUT_CAPTION_ELEMENT_COUNT],
        D3DCOLOR            TextureColor = D3DCOLOR_ARGB(255, 255, 255, 255)
    );

    HRESULT DrawCaption9();

    PDXUT_ELEMENT_INFO GetFrameTexture()
    {
        return m_FrameElement;
    }

    HRESULT
    SetFrameTexture(
        DXUT_TEXTURE_INFO   FrmaeTexture[DXUT_DIALOG_FRAME_ELEMENT_COUNT],
        ULONG               Flags = 0,
        D3DCOLOR            TextureColor = D3DCOLOR_ARGB(255, 255, 255, 255)
    );

    HRESULT DrawDialogFrame9();

    void GetLocation( POINT& Pt ) const
    {
        Pt.x = m_x;
        Pt.y = m_y;
    }

    void SetLocation( int x, int y )
    {
        m_x = x;
        m_y = y;
    }

    void SetSize( int width, int height )
    {
        RECT    rc;
        LONG    CaptionWidth, CaptionHeight, OldCaptionHeight;
        double  WidthRate, HeightRate;

        WidthRate   = width / (DOUBLE)m_width;
        HeightRate  = height / (DOUBLE)m_height;

        m_width     = width;
        m_height    = height;

        rc = m_CaptionRect;

        WidthRate   /= 2;
        HeightRate  /= 2;

        rc.left     = (LONG)(rc.left * (1 - WidthRate));
        rc.right    = (LONG)(rc.right * (1 - WidthRate));

        SetCaptionRect(rc);
    }

    VOID SetSize(SIZE size)
    {
        return SetSize(size.cx, size.cy);
    }

    SIZE GetSize()
    {
        SIZE size = { GetWidth(), GetHeight() };
        return size;
    }

    void SetDialogRect(RECT &rc)
    {
        SetLocation(rc.left, rc.top);
        SetSize(RectWidth(rc), RectHeight(rc));
    }

    int GetWidth()
    {
        return m_width;
    }

    int GetHeight()
    {
        return m_height;
    }

    VOID GetRectClient(RECT &rc)
    {
        rc.left     = m_x;
        rc.top      = m_y;
        rc.right    = rc.left + GetWidth();
        rc.bottom   = rc.top + GetHeight();
    }

    VOID GetRectFrame(RECT &rc, BOOL IncludeCaption = FALSE)
    {
        LONG CaptionHeight;
        PDXUT_ELEMENT_INFO Element;

        GetRectClient(rc);

        Element = &m_FrameElement[DXUT_DIALOG_FRAME_BOTTOM];
        if (IsElementValid(Element->Element))
            rc.bottom += RectHeight(Element->Position);

        Element = &m_FrameElement[DXUT_DIALOG_FRAME_LEFT];
        if (IsElementValid(Element->Element))
            rc.left -= RectWidth(Element->Position);

        Element = &m_FrameElement[DXUT_DIALOG_FRAME_RIGHT];
        if (IsElementValid(Element->Element))
            rc.right += RectWidth(Element->Position);

        Element = &m_FrameElement[DXUT_DIALOG_FRAME_TOP];
        if (IsElementValid(Element->Element))
            rc.top -= RectHeight(Element->Position);

        if (!IncludeCaption || !m_bCaption)
            return;

        CaptionHeight = GetCaptionHeightAboveFrame();
        if (IsElementValid(Element->Element) && CaptionHeight <= RectHeight(Element->Position))
            return;
        else
            rc.top += RectHeight(Element->Position);

        rc.top -= CaptionHeight;
    }

    VOID GetRectAbsolute(RECT &rc)
    {
        CDXUTDialog *Parent;

        GetLocation(*(POINT *)&rc);
        rc.right    = GetWidth();
        rc.bottom   = GetHeight();

        Parent = m_ParentDialog;
        if (Parent == NULL)
            return;

        do
        {
            OffsetRect(&rc, Parent->m_x, Parent->m_y);
            Parent = Parent->m_ParentDialog;

        } while (Parent != NULL);
    }

    VOID OffsetRectAbsolute(RECT &rc)
    {
        RECT rc2;

        GetRectAbsolute(rc2);
        OffsetRect(&rc, rc2.left, rc2.top);
    }

    void SetRefreshTime( FLOAT fTime )
    {
        s_fTimeRefresh = fTime;
    }

    static CDXUTControl* GetNextControl( CDXUTControl* pControl );
    static CDXUTControl* GetPrevControl( CDXUTControl* pControl );

    void RemoveControl( int ID );
    void RemoveAllControls();

    // Sets the callback used to notify the app of control events
    void SetCallback( PVOID pCallback, void* pUserContext = NULL );
    void EnableNonUserEvents( BOOL bEnable )
    {
        m_bNonUserEvents = bEnable;
    }
    void EnableKeyboardInput( BOOL bEnable )
    {
        m_bKeyboardInput = bEnable;
    }
    void EnableMouseInput( BOOL bEnable )
    {
        m_bMouseInput = bEnable;
    }
    BOOL IsKeyboardInputEnabled() const
    {
        return m_bKeyboardInput;
    }

    // Device state notification
    void    Refresh();
    HRESULT OnRender(FLOAT ElapsedTime);

    // Shared resource access. Indexed fonts and textures are shared among
    // all the controls.
    ULONG           AddFont(PCWSTR FaceName, LONG Height, LONG Weight);
    HRESULT         SetFont(UINT index, LPCWSTR strFaceName, LONG height, LONG weight);
    DXUTFontNode*   GetFont(UINT index);

    ULONG               AddTexture(PWSTR FileName);
    HRESULT             SetTexture(UINT index, LPCWSTR strFilename);
    HRESULT             SetTexture(UINT index, LPCWSTR strResourceName, HMODULE hResourceModule);
    DXUTTextureNode*    GetTexture(UINT index);

    ULONG GetTextureCount()
    {
        return m_Textures.GetSize();
    }

    CDXUTDialogResourceManager* GetManager()
    {
        return m_pManager;
    }

    void ClearFocus();
    void FocusDefaultControl();

protected:
    HRESULT OnRender9(FLOAT ElapsedTime);
    HRESULT OnRender10(FLOAT ElapsedTime);

    // Initialize default Elements
    void InitDefaultElements();

    // Windows message handlers
    void OnMouseMove( POINT pt );
    void OnMouseUp( POINT pt );

    void SetNextDialog( CDXUTDialog* pNextDialog );

    // Control events
    BOOL OnCycleFocus( BOOL bForward );

public:
    BOOL m_bNonUserEvents;
    BOOL m_bKeyboardInput;
    BOOL m_bMouseInput;

protected:
    int m_nDefaultControlID;

    double s_fTimeRefresh;
    double m_fTimeLastRefresh;

    CDXUTControl* s_pControlFocus;        // The control which has focus
    CDXUTControl* s_pControlPressed;      // The control currently pressed

    CDXUTControl* m_pControlMouseOver;           // The control which is hovered over

    BOOL m_bVisible;
    BOOL m_bCaption;
    BOOL m_bMinimized;
    BOOL m_LButtonPressed, m_Drag;

    POINT LastMousePoint;

    UNICODE_STRING m_CaptionText;

    int m_x;
    int m_y;
    int m_width;
    int m_height;

    RECT m_CaptionRect;

    D3DCOLOR m_colorTopLeft;
    D3DCOLOR m_colorTopRight;
    D3DCOLOR m_colorBottomLeft;
    D3DCOLOR m_colorBottomRight;

    CDXUTDialogResourceManager* m_pManager;
    PCALLBACKDXUTGUIEVENT m_pCallbackEvent;
    void* m_pCallbackEventUserContext;

    CGrowableArray <int> m_Textures;   // Index into m_TextureCache;
    CGrowableArray <int> m_Fonts;      // Index into m_FontCache;

    CGrowableArray <CDXUTControl*> m_Controls;
    CGrowableArray <DXUTElementHolder*> m_DefaultElements;

    DXUT_ELEMENT_INFO m_CaptionElement[DXUT_CAPTION_ELEMENT_COUNT];

    DXUT_ELEMENT_INFO m_FrameElement[DXUT_DIALOG_FRAME_ELEMENT_COUNT];
    union
    {
        struct
        {
            UCHAR DontDrawCaption : 1;
        };

        ULONG Flags;

    } m_FrameFlags;

    CDXUTDialog* m_ParentDialog;
    CDXUTDialog* m_pNextDialog;
    CDXUTDialog* m_pPrevDialog;
};


//--------------------------------------------------------------------------------------
// Structs for shared resources
//--------------------------------------------------------------------------------------
struct DXUTTextureNode
{
    BOOL                        FileSource;  // True if this texture is loaded from a file. False if from resource.
    HMODULE                     ResourceModule;
    ULONG_PTR                   ResourceID;   // Resource ID. If 0, string-based ID is used and stored in strFilename.
    ULONG                       FileNameHash;
    WCHAR                       Filename[MAX_PATH];
    DWORD                       Width;
    DWORD                       Height;
    IDirect3DTexture9*          Texture9;
    ID3D10Texture2D*            Texture10;
    ID3D10ShaderResourceView*   TexResView;
};

struct DXUTFontNode
{
    ULONG           FaceNameHash;
    WCHAR           FaceName[MAX_PATH];
    LONG            Height;
    LONG            Weight;
    ID3DXFont*      Font9;
    ID3DX10Font*    Font10;
};


//-----------------------------------------------------------------------------
// Manages shared resources of dialogs
//-----------------------------------------------------------------------------
class DXUT_API CDXUTDialogResourceManager
{
public:
    CDXUTDialogResourceManager();
    ~CDXUTDialogResourceManager();

    NTSTATUS SetTexturePath(PWSTR Path);
    ULONG GetTexturePath(PWSTR Path, ULONG BufferCount);

    BOOL MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

    // D3D9 specific
    HRESULT OnD3D9CreateDevice( LPDIRECT3DDEVICE9 pd3dDevice );
    HRESULT OnD3D9ResetDevice();
    void    OnD3D9LostDevice();
    void    OnD3D9DestroyDevice();
    IDirect3DDevice9* GetD3D9Device()
    {
        return m_pd3d9Device;
    }

    // D3D10 specific
    HRESULT OnD3D10CreateDevice( ID3D10Device* pd3dDevice );
    HRESULT OnD3D10ResizedSwapChain( ID3D10Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc );
    void    OnD3D10ReleasingSwapChain();
    void    OnD3D10DestroyDevice();
    ID3D10Device* GetD3D10Device()
    {
        return m_pd3d10Device;
    }

    DXUTFontNode* GetFontNode( int iIndex )
    {
        return m_FontCache.GetAt( iIndex );
    }
    DXUTTextureNode* GetTextureNode( int iIndex )
    {
        return m_TextureCache.GetAt( iIndex );
    }

    int     AddFont( LPCWSTR strFaceName, LONG height, LONG weight );
    int     AddTexture( LPCWSTR strFilename );
    int     AddTexture( LPCWSTR strResourceName, HMODULE hResourceModule );

    BOOL    RegisterDialog( CDXUTDialog* pDialog );
    void    UnregisterDialog( CDXUTDialog* pDialog );
    void    EnableKeyboardInputForAllDialogs();

protected:
    ULONG GetTextureFilePath(PWSTR Buffer, ULONG BufferCount);
    ULONG GetMeshFilePath(PWSTR Buffer, ULONG BufferCount);

    HRESULT
    DXUTCreateGUITextureFromInternalArray9(
        LPDIRECT3DDEVICE9   pd3dDevice,
        IDirect3DTexture9** ppTexture,
        D3DXIMAGE_INFO*     pInfo
    );

    HRESULT
    DXUTCreateGUITextureFromInternalArray10(
        ID3D10Device*       pd3dDevice,
        ID3D10Texture2D**   ppTexture,
        D3DX10_IMAGE_INFO*  pInfo
    );

    HRESULT
    DXUTCreateArrowMeshFromInternalArray(
        LPDIRECT3DDEVICE9   pd3dDevice,
        ID3DXMesh**         ppMesh
    );

    HRESULT CreateFont9( UINT index );
    HRESULT CreateTexture9( UINT index );

    // D3D10 specific
    ID3D10Device* m_pd3d10Device;
    HRESULT CreateFont10( UINT index );
    HRESULT CreateTexture10( UINT index );

public:
    // Shared between all dialogs

    // D3D9
    IDirect3DStateBlock9* m_pStateBlock;
    ID3DXSprite* m_pSprite;          // Sprite used for drawing

    // D3D10
    ID3D10Effect* m_pEffect10;        // Effect used to render UI with D3D10
    ID3D10EffectTechnique* m_pTechRenderUI10;  // Technique: RenderUI
    ID3D10EffectTechnique* m_pTechRenderUIUntex10;  // Technique: RenderUI without texture
    ID3D10EffectShaderResourceVariable* m_pFxTexture10;
    ID3D10InputLayout* m_pInputLayout10;
    ID3D10Buffer* m_pVBScreenQuad10;
    ID3D10StateBlock* m_pStateBlock10;
    ID3DX10Sprite* m_pSprite10;
    UINT m_nBackBufferWidth;
    UINT m_nBackBufferHeight;

    CGrowableArray <CDXUTDialog*> m_Dialogs;            // Dialogs registered

protected:
    UNICODE_STRING m_TexturePath;

    // D3D9 specific
    IDirect3DDevice9* m_pd3d9Device;

    CGrowableArray <DXUTTextureNode*> m_TextureCache;   // Shared textures
    CGrowableArray <DXUTFontNode*> m_FontCache;         // Shared fonts
};


//-----------------------------------------------------------------------------
// Base class for controls
//-----------------------------------------------------------------------------
class DXUT_API CDXUTControl
{
public:
                    CDXUTControl( CDXUTDialog* pDialog = NULL );
    virtual         ~CDXUTControl();

    virtual HRESULT OnInit()
    {
        return S_OK;
    }

    virtual void Refresh();

    virtual void Render(FLOAT ElapsedTime)
    {
    }

    // Windows message handler
    virtual BOOL MsgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
        return FALSE;
    }

    virtual BOOL HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
        return FALSE;
    }

    virtual BOOL HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam)
    {
        return FALSE;
    }

    virtual BOOL    CanHaveFocus()
    {
        return FALSE;
    }
    virtual void    OnFocusIn()
    {
        m_bHasFocus = TRUE;
    }
    virtual void    OnFocusOut()
    {
        m_bHasFocus = FALSE;
    }
    virtual void    OnMouseEnter()
    {
        m_bMouseOver = TRUE;
    }
    virtual void    OnMouseLeave()
    {
        m_bMouseOver = FALSE;
    }
    virtual void    OnHotkey()
    {
    }

    virtual BOOL    ContainsPoint( POINT pt )
    {
        return PtInRect( &m_rcBoundingBox, pt );
    }

    virtual void    SetEnabled( BOOL bEnabled )
    {
        m_bEnabled = bEnabled;
    }
    virtual BOOL    GetEnabled()
    {
        return m_bEnabled;
    }
    virtual void    SetVisible( BOOL bVisible )
    {
        m_bVisible = bVisible;
    }
    virtual BOOL    GetVisible()
    {
        return m_bVisible;
    }

    UINT            GetType() const
    {
        return m_Type;
    }

    int             GetID() const
    {
        return m_ID;
    }
    void            SetID( int ID )
    {
        m_ID = ID;
    }

    VOID SetLocation(int x, int y)
    {
        m_x = x;
        m_y = y;
        UpdateRects();
    }

    VOID SetSize( int width, int height )
    {
        m_width = width;
        m_height = height;
        UpdateRects();
    }

    VOID SetSize(SIZE size)
    {
        return SetSize(size.cx, size.cy);
    }

    SIZE GetSize()
    {
        SIZE size = { GetWidth(), GetHeight() };
        return size;
    }

    VOID GetLocation(POINT &pt)
    {
        pt.x = m_x;
        pt.y = m_y;
    }

    INT GetWidth()
    {
        return m_width;
    }

    INT GetHeight()
    {
        return m_height;
    }

    //
    // The Modifiers parameter can be a combination of the following values.
    //
    // MOD_ALT
    // MOD_CONTROL
    // MOD_SHIFT
    // MOD_WIN
    //
    void SetHotkey( UINT nHotkey, UINT Modifiers = 0 )
    {
        m_nHotkey = nHotkey;
        m_Modifiers = Modifiers;
    }

    UINT GetHotkey()
    {
        return m_nHotkey;
    }

    UINT GetHotkeyModifiers()
    {
        return m_Modifiers;
    }

    void SetUserData( void* pUserData )
    {
        m_pUserData = pUserData;
    }

    void* GetUserData() const
    {
        return m_pUserData;
    }

    virtual void    SetTextColor( D3DCOLOR Color );
    CDXUTElement* GetElement( UINT iElement )
    {
        return m_Elements.GetAt( iElement );
    }
    HRESULT         SetElement( UINT iElement, CDXUTElement* pElement );

    BOOL m_bVisible;                // Shown/hidden flag
    BOOL m_bMouseOver;              // Mouse pointer is above control
    BOOL m_bHasFocus;               // Control has input focus
    BOOL m_bIsDefault;              // Is the default control

    // Size, scale, and positioning members
    int m_x, m_y;
    int m_width, m_height;

    // These members are set by the container
    CDXUTDialog* m_pDialog;    // Parent container
    UINT m_ControlListIndex;              // Index within the control list

    CGrowableArray <CDXUTElement*> m_Elements;  // All display elements

protected:
    virtual void    UpdateRects();

    int m_ID;                 // ID number
    DXUT_CONTROL_TYPE m_Type;  // Control type, set once in constructor
    UINT m_nHotkey;            // Virtual key code for this control's hotkey
    UINT m_Modifiers;
    void* m_pUserData;         // Data associated with this control that is set by user.

    BOOL m_bEnabled;           // Enabled/disabled flag

    RECT m_rcBoundingBox;      // Rectangle defining the active region of the control
};


//-----------------------------------------------------------------------------
// Contains all the display information for a given control type
//-----------------------------------------------------------------------------
struct DXUTElementHolder
{
    UINT nControlType;
    UINT iElement;

    CDXUTElement Element;
};


//-----------------------------------------------------------------------------
// Static control
//-----------------------------------------------------------------------------
class DXUT_API CDXUTStatic : public CDXUTControl
{
public:
    CDXUTStatic(CDXUTDialog* pDialog = NULL);

    virtual VOID Render( FLOAT fElapsedTime );
    virtual BOOL ContainsPoint(POINT pt)
    {
        return FALSE;
    }

    PCWSTR GetText()
    {
        return m_ButtonText.Buffer;
    }

    ULONG GetTextLength()
    {
        return m_ButtonText.Length;
    }

    HRESULT GetTextCopy(PWSTR Buffer, UINT BufferCount);

    HRESULT SetText(PCWSTR Text);

protected:
    UNICODE_STRING  m_ButtonText;
};


//-----------------------------------------------------------------------------
// Button control
//-----------------------------------------------------------------------------
class DXUT_API CDXUTButton : public CDXUTStatic
{
public:
                    CDXUTButton( CDXUTDialog* pDialog = NULL );

    virtual BOOL    HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    virtual BOOL    HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam);
    virtual void    OnHotkey()
    {
        if( m_pDialog->IsKeyboardInputEnabled() ) m_pDialog->RequestFocus( this );
        m_pDialog->SendEvent( EVENT_BUTTON_CLICKED, TRUE, this );
    }

    virtual BOOL    ContainsPoint( POINT pt )
    {
        return PtInRect( &m_rcBoundingBox, pt );
    }
    virtual BOOL    CanHaveFocus()
    {
        return ( m_bVisible && m_bEnabled );
    }

    virtual void    Render( FLOAT fElapsedTime );

protected:
    BOOL m_bPressed;
};


//-----------------------------------------------------------------------------
// CheckBox control
//-----------------------------------------------------------------------------
class DXUT_API CDXUTCheckBox : public CDXUTButton
{
public:
                    CDXUTCheckBox( CDXUTDialog* pDialog = NULL );

    virtual BOOL    HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    virtual BOOL    HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam);
    virtual void    OnHotkey()
    {
        if( m_pDialog->IsKeyboardInputEnabled() ) m_pDialog->RequestFocus( this );
        SetCheckedInternal( !m_bChecked, TRUE );
    }

    virtual BOOL    ContainsPoint( POINT pt );
    virtual void    UpdateRects();

    virtual void    Render( FLOAT fElapsedTime );

    BOOL            GetChecked()
    {
        return m_bChecked;
    }
    void            SetChecked( BOOL bChecked )
    {
        SetCheckedInternal( bChecked, FALSE );
    }

protected:
    virtual void    SetCheckedInternal( BOOL bChecked, BOOL bFromInput );

    BOOL m_bChecked;
    RECT m_rcButton;
    RECT m_rcText;
};


//-----------------------------------------------------------------------------
// RadioButton control
//-----------------------------------------------------------------------------
class DXUT_API CDXUTRadioButton : public CDXUTCheckBox
{
public:
                    CDXUTRadioButton( CDXUTDialog* pDialog = NULL );

    virtual BOOL    HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    virtual BOOL    HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam);
    virtual void    OnHotkey()
    {
        if( m_pDialog->IsKeyboardInputEnabled() ) m_pDialog->RequestFocus( this );
        SetCheckedInternal( TRUE, TRUE, TRUE );
    }

    void            SetChecked( BOOL bChecked, BOOL bClearGroup=TRUE )
    {
        SetCheckedInternal( bChecked, bClearGroup, FALSE );
    }
    void            SetButtonGroup( UINT nButtonGroup )
    {
        m_nButtonGroup = nButtonGroup;
    }
    UINT            GetButtonGroup()
    {
        return m_nButtonGroup;
    }

protected:
    virtual void    SetCheckedInternal( BOOL bChecked, BOOL bClearGroup, BOOL bFromInput );
    UINT m_nButtonGroup;
};


//-----------------------------------------------------------------------------
// Scrollbar control
//-----------------------------------------------------------------------------
class DXUT_API CDXUTScrollBar : public CDXUTControl
{
public:
                    CDXUTScrollBar( CDXUTDialog* pDialog = NULL );
    virtual         ~CDXUTScrollBar();

    virtual BOOL    HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    virtual BOOL    HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam);
    virtual BOOL    MsgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

    virtual void    Render( FLOAT fElapsedTime );
    virtual void    UpdateRects();

    void            SetTrackRange( int nStart, int nEnd );
    int             GetTrackPos()
    {
        return m_nPosition;
    }
    void            SetTrackPos( int nPosition )
    {
        m_nPosition = nPosition; Cap(); UpdateThumbRect();
    }
    int             GetPageSize()
    {
        return m_nPageSize;
    }
    void            SetPageSize( int nPageSize )
    {
        m_nPageSize = nPageSize; Cap(); UpdateThumbRect();
    }

    void            Scroll( int nDelta );    // Scroll by nDelta items (plus or minus)
    void            ShowItem( int nIndex );  // Ensure that item nIndex is displayed, scroll if necessary

protected:
    // ARROWSTATE indicates the state of the arrow buttons.
    // CLEAR            No arrow is down.
    // CLICKED_UP       Up arrow is clicked.
    // CLICKED_DOWN     Down arrow is clicked.
    // HELD_UP          Up arrow is held down for sustained period.
    // HELD_DOWN        Down arrow is held down for sustained period.
    enum ARROWSTATE
    {
        CLEAR,
        CLICKED_UP,
        CLICKED_DOWN,
        HELD_UP,
        HELD_DOWN
    };

    void            UpdateThumbRect();
    void            Cap();  // Clips position at boundaries. Ensures it stays within legal range.

    BOOL m_bShowThumb;
    BOOL m_bDrag;
    RECT m_rcUpButton;
    RECT m_rcDownButton;
    RECT m_rcTrack;
    RECT m_rcThumb;
    int m_nPosition;  // Position of the first displayed item
    int m_nPageSize;  // How many items are displayable in one page
    int m_nStart;     // First item
    int m_nEnd;       // The index after the last item
    POINT m_LastMouse;// Last mouse position
    ARROWSTATE m_Arrow; // State of the arrows
    double m_dArrowTS;  // Timestamp of last arrow event.
};


//-----------------------------------------------------------------------------
// ListBox control
//-----------------------------------------------------------------------------
struct DXUTListBoxItem
{
    WCHAR strText[256];
    void* pData;

    RECT rcActive;
    BOOL bSelected;
};

class DXUT_API CDXUTListBox : public CDXUTControl
{
public:
                    CDXUTListBox( CDXUTDialog* pDialog = NULL );
    virtual         ~CDXUTListBox();

    virtual HRESULT OnInit()
    {
        return m_pDialog->InitControl( &m_ScrollBar );
    }
    virtual BOOL    CanHaveFocus()
    {
        return ( m_bVisible && m_bEnabled );
    }
    virtual BOOL    HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    virtual BOOL    HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam);
    virtual BOOL    MsgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

    virtual void    Render( FLOAT fElapsedTime );
    virtual void    UpdateRects();

    DWORD           GetStyle() const
    {
        return m_dwStyle;
    }
    int             GetSize() const
    {
        return m_Items.GetSize();
    }
    void            SetStyle( DWORD dwStyle )
    {
        m_dwStyle = dwStyle;
    }
    int             GetScrollBarWidth() const
    {
        return m_nSBWidth;
    }
    void            SetScrollBarWidth( int nWidth )
    {
        m_nSBWidth = nWidth; UpdateRects();
    }
    void            SetBorder( int nBorder, int nMargin )
    {
        m_nBorder = nBorder; m_nMargin = nMargin;
    }
    HRESULT         AddItem( const WCHAR* wszText, void* pData );
    HRESULT         InsertItem( int nIndex, const WCHAR* wszText, void* pData );
    void            RemoveItem( int nIndex );
    void            RemoveItemByData( void* pData );
    void            RemoveAllItems();

    DXUTListBoxItem* GetItem( int nIndex );
    int             GetSelectedIndex( int nPreviousSelected = -1 );
    DXUTListBoxItem* GetSelectedItem( int nPreviousSelected = -1 )
    {
        return GetItem( GetSelectedIndex( nPreviousSelected ) );
    }
    void            SelectItem( int nNewIndex );

    enum STYLE
    {
        MULTISELECTION = 1
    };

protected:
    RECT m_rcText;      // Text rendering bound
    RECT m_rcSelection; // Selection box bound
    CDXUTScrollBar m_ScrollBar;
    int m_nSBWidth;
    int m_nBorder;
    int m_nMargin;
    int m_nTextHeight;  // Height of a single line of text
    DWORD m_dwStyle;    // List box style
    int m_nSelected;    // Index of the selected item for single selection list box
    int m_nSelStart;    // Index of the item where selection starts (for handling multi-selection)
    BOOL m_bDrag;       // Whether the user is dragging the mouse to select

    CGrowableArray <DXUTListBoxItem*> m_Items;
};


//-----------------------------------------------------------------------------
// ComboBox control
//-----------------------------------------------------------------------------
struct DXUTComboBoxItem
{
    WCHAR strText[256];
    void* pData;

    RECT rcActive;
    BOOL bVisible;
};


class DXUT_API CDXUTComboBox : public CDXUTButton
{
public:
                    CDXUTComboBox( CDXUTDialog* pDialog = NULL );
    virtual         ~CDXUTComboBox();

    virtual void    SetTextColor( D3DCOLOR Color );
    virtual HRESULT OnInit()
    {
        return m_pDialog->InitControl( &m_ScrollBar );
    }

    virtual BOOL    HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    virtual BOOL    HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam);
    virtual void    OnHotkey();

    virtual BOOL    CanHaveFocus()
    {
        return ( m_bVisible && m_bEnabled );
    }
    virtual void    OnFocusOut();
    virtual void    Render( FLOAT fElapsedTime );

    virtual void    UpdateRects();

    HRESULT         AddItem( const WCHAR* strText, void* pData );
    void            RemoveAllItems();
    void            RemoveItem( UINT index );
    BOOL            ContainsItem( const WCHAR* strText, UINT iStart=0 );
    int             FindItem( const WCHAR* strText, UINT iStart=0 );
    void* GetItemData( const WCHAR* strText );
    void* GetItemData( int nIndex );
    void            SetDropHeight( UINT nHeight )
    {
        m_nDropHeight = nHeight; UpdateRects();
    }
    int             GetScrollBarWidth() const
    {
        return m_nSBWidth;
    }
    void            SetScrollBarWidth( int nWidth )
    {
        m_nSBWidth = nWidth; UpdateRects();
    }

    int             GetSelectedIndex() const
    {
        return m_Selected;
    }
    void* GetSelectedData();
    DXUTComboBoxItem* GetSelectedItem();

    UINT            GetNumItems()
    {
        return m_Items.GetSize();
    }
    DXUTComboBoxItem* GetItem( UINT index )
    {
        return m_Items.GetAt( index );
    }

    HRESULT         SetSelectedByIndex( UINT index );
    HRESULT         SetSelectedByText( const WCHAR* strText );
    HRESULT         SetSelectedByData( void* pData );

protected:
    ULONG   m_Selected;
    ULONG   m_Focused;
    LONG    m_nDropHeight;
    LONG    m_nSBWidth;
    CDXUTScrollBar m_ScrollBar;

    BOOL m_bOpened;

    RECT m_rcText;
    RECT m_rcButton;
    RECT m_rcDropdown;
    RECT m_rcDropdownText;


    CGrowableArray <DXUTComboBoxItem*> m_Items;
};


//-----------------------------------------------------------------------------
// Slider control
//-----------------------------------------------------------------------------
class DXUT_API CDXUTSlider : public CDXUTControl
{
public:
                    CDXUTSlider( CDXUTDialog* pDialog = NULL );

    virtual BOOL    ContainsPoint( POINT pt );
    virtual BOOL    CanHaveFocus()
    {
        return ( m_bVisible && m_bEnabled );
    }
    virtual BOOL    HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    virtual BOOL    HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam);

    virtual void    UpdateRects();

    virtual void    Render( FLOAT fElapsedTime );

    void            SetValue( int nValue )
    {
        SetValueInternal( nValue, FALSE );
    }
    int             GetValue() const
    {
        return m_nValue;
    };

    void            GetRange( int& nMin, int& nMax ) const
    {
        nMin = m_nMin; nMax = m_nMax;
    }
    void            SetRange( int nMin, int nMax );

protected:
    void            SetValueInternal( int nValue, BOOL bFromInput );
    int             ValueFromPos( int x );

    int m_nValue;

    int m_nMin;
    int m_nMax;

    int m_nDragX;      // Mouse position at start of drag
    int m_nDragOffset; // Drag offset from the center of the button
    int m_nButtonX;

    BOOL m_bPressed;
    RECT m_rcButton;
};


//-----------------------------------------------------------------------------
// CUniBuffer class for the edit control
//-----------------------------------------------------------------------------
class DXUT_API CUniBuffer
{
public:
                            CUniBuffer( int nInitialSize = 1 );
                            ~CUniBuffer();

    static void WINAPI      Initialize();
    static void WINAPI      Uninitialize();

    int                     GetBufferSize()
    {
        return m_nBufferSize;
    }
    BOOL                    SetBufferSize( int nSize );
    int                     GetTextSize()
    {
        return lstrlenW( m_pwszBuffer );
    }
    const WCHAR* GetBuffer()
    {
        return m_pwszBuffer;
    }
    const WCHAR& operator[]( int n ) const
    {
        return m_pwszBuffer[n];
    }
    WCHAR& operator[]( int n );
    DXUTFontNode* GetFontNode()
    {
        return m_pFontNode;
    }
    void                    SetFontNode( DXUTFontNode* pFontNode )
    {
        m_pFontNode = pFontNode;
    }
    void                    Clear();

    BOOL                    InsertChar( int nIndex, WCHAR wChar ); // Inserts the char at specified index. If nIndex == -1, insert to the end.
    BOOL                    RemoveChar( int nIndex );  // Removes the char at specified index. If nIndex == -1, remove the last char.
    BOOL                    InsertString( int nIndex, const WCHAR* pStr, int nCount = -1 );  // Inserts the first nCount characters of the string pStr at specified index.  If nCount == -1, the entire string is inserted. If nIndex == -1, insert to the end.
    BOOL                    SetText( LPCWSTR wszText );

    // Uniscribe
    HRESULT                 CPtoX( int nCP, BOOL bTrail, int* pX );
    HRESULT                 XtoCP( int nX, int* pCP, int* pnTrail );
    void                    GetPriorItemPos( int nCP, int* pPrior );
    void                    GetNextItemPos( int nCP, int* pPrior );

private:
    HRESULT                 Analyse();      // Uniscribe -- Analyse() analyses the string in the buffer

    WCHAR* m_pwszBuffer;    // Buffer to hold text
    int m_nBufferSize;   // Size of the buffer allocated, in characters

    // Uniscribe-specific
    DXUTFontNode* m_pFontNode;          // Font node for the font that this buffer uses
    BOOL m_bAnalyseRequired;            // True if the string has changed since last analysis.
    SCRIPT_STRING_ANALYSIS m_Analysis;  // Analysis for the current string

private:
    // Empty implementation of the Uniscribe API

/*

    static HRESULT WINAPI   Dummy_ScriptApplyDigitSubstitution( const SCRIPT_DIGITSUBSTITUTE*, SCRIPT_CONTROL*,
                                                                SCRIPT_STATE* )
    {
        return E_NOTIMPL;
    }
    static HRESULT WINAPI   Dummy_ScriptStringAnalyse( HDC, const void*, int, int, int, DWORD, int, SCRIPT_CONTROL*,
                                                       SCRIPT_STATE*, const int*, SCRIPT_TABDEF*, const BYTE*,
                                                       SCRIPT_STRING_ANALYSIS* )
    {
        return E_NOTIMPL;
    }
    static HRESULT WINAPI   Dummy_ScriptStringCPtoX( SCRIPT_STRING_ANALYSIS, int, BOOL, int* )
    {
        return E_NOTIMPL;
    }
    static HRESULT WINAPI   Dummy_ScriptStringXtoCP( SCRIPT_STRING_ANALYSIS, int, int*, int* )
    {
        return E_NOTIMPL;
    }
    static HRESULT WINAPI   Dummy_ScriptStringFree( SCRIPT_STRING_ANALYSIS* )
    {
        return E_NOTIMPL;
    }
    static const SCRIPT_LOGATTR* WINAPI Dummy_ScriptString_pLogAttr( SCRIPT_STRING_ANALYSIS )
    {
        return NULL;
    }
    static const int* WINAPI Dummy_ScriptString_pcOutChars( SCRIPT_STRING_ANALYSIS )
    {
        return NULL;
    }

    // Function pointers
    static                  HRESULT( WINAPI* _ScriptApplyDigitSubstitution )( const SCRIPT_DIGITSUBSTITUTE*,
                                                                              SCRIPT_CONTROL*, SCRIPT_STATE* );
    static                  HRESULT( WINAPI* _ScriptStringAnalyse )( HDC, const void*, int, int, int, DWORD, int,
                                                                     SCRIPT_CONTROL*, SCRIPT_STATE*, const int*,
                                                                     SCRIPT_TABDEF*, const BYTE*,
                                                                     SCRIPT_STRING_ANALYSIS* );
    static                  HRESULT( WINAPI* _ScriptStringCPtoX )( SCRIPT_STRING_ANALYSIS, int, BOOL, int* );
    static                  HRESULT( WINAPI* _ScriptStringXtoCP )( SCRIPT_STRING_ANALYSIS, int, int*, int* );
    static                  HRESULT( WINAPI* _ScriptStringFree )( SCRIPT_STRING_ANALYSIS* );
    static const SCRIPT_LOGATTR* ( WINAPI*_ScriptString_pLogAttr )( SCRIPT_STRING_ANALYSIS );
    static const int* ( WINAPI*_ScriptString_pcOutChars )( SCRIPT_STRING_ANALYSIS );

    static HINSTANCE s_hDll;  // Uniscribe DLL handle

*/

};

//-----------------------------------------------------------------------------
// EditBox control
//-----------------------------------------------------------------------------
class DXUT_API CDXUTEditBox : public CDXUTControl
{
public:
                    CDXUTEditBox( CDXUTDialog* pDialog = NULL );
    virtual         ~CDXUTEditBox();

    virtual BOOL    HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    virtual BOOL    HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam);
    virtual BOOL    MsgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    virtual void    UpdateRects();
    virtual BOOL    CanHaveFocus()
    {
        return ( m_bVisible && m_bEnabled );
    }
    virtual void    Render( FLOAT fElapsedTime );
    virtual void    OnFocusIn();

    void            SetText( LPCWSTR wszText, BOOL bSelected = FALSE );
    LPCWSTR         GetText()
    {
        return m_Buffer.GetBuffer();
    }
    int             GetTextLength()
    {
        return m_Buffer.GetTextSize();
    }  // Returns text length in chars excluding NULL.
    HRESULT         GetTextCopy( __out_ecount(bufferCount) LPWSTR strDest,
                    UINT bufferCount );
    void            ClearText();
    virtual void    SetTextColor( D3DCOLOR Color )
    {
        m_TextColor = Color;
    }  // Text color
    void            SetSelectedTextColor( D3DCOLOR Color )
    {
        m_SelTextColor = Color;
    }  // Selected text color
    void            SetSelectedBackColor( D3DCOLOR Color )
    {
        m_SelBkColor = Color;
    }  // Selected background color
    void            SetCaretColor( D3DCOLOR Color )
    {
        m_CaretColor = Color;
    }  // Caret color
    void            SetBorderWidth( int nBorder )
    {
        m_nBorder = nBorder; UpdateRects();
    }  // Border of the window
    void            SetSpacing( int nSpacing )
    {
        m_nSpacing = nSpacing; UpdateRects();
    }
    void            ParseFloatArray( FLOAT* pNumbers, int nCount );
    void            SetTextFloatArray( const FLOAT* pNumbers, int nCount );

protected:
    void            PlaceCaret( int nCP );
    void            DeleteSelectionText();
    void            ResetCaretBlink();
    void            CopyToClipboard();
    void            PasteFromClipboard();

    CUniBuffer m_Buffer;     // Buffer to hold text
    int m_nBorder;      // Border of the window
    int m_nSpacing;     // Spacing between the text and the edge of border
    RECT m_rcText;       // Bounding rectangle for the text
    RECT            m_rcRender[9];  // Convenient rectangles for rendering elements
    double m_dfBlink;      // Caret blink time in milliseconds
    double m_dfLastBlink;  // Last timestamp of caret blink
    BOOL m_bCaretOn;     // Flag to indicate whether caret is currently visible
    int m_nCaret;       // Caret position, in characters
    BOOL m_bInsertMode;  // If true, control is in insert mode. Else, overwrite mode.
    int m_nSelStart;    // Starting position of the selection. The caret marks the end.
    int m_nFirstVisible;// First visible character in the edit control
    D3DCOLOR m_TextColor;    // Text color
    D3DCOLOR m_SelTextColor; // Selected text color
    D3DCOLOR m_SelBkColor;   // Selected background color
    D3DCOLOR m_CaretColor;   // Caret color

    // Mouse-specific
    BOOL m_bMouseDrag;       // True to indicate drag in progress

    // Static
    static BOOL s_bHideCaret;   // If true, we don't render the caret.
};

//-----------------------------------------------------------------------------
// Tab control
//-----------------------------------------------------------------------------
class CDXUTTabButton;

class NOVTABLE CDXUTTabItemBase : public CDXUTDialog
{
    friend class CDXUTTabControl;

private:
    CDXUTTabButton  *m_ButtonBinded;

protected:
    CDXUTTabItemBase()
    {
        m_ButtonBinded  = NULL;
    }

private:
    CDXUTTabButton* BindButton(CDXUTTabButton *Button)
    {
        Swap(m_ButtonBinded, Button);
        return Button;
    }

    CDXUTTabButton* GetButtonBinded()
    {
        return m_ButtonBinded;
    }
};

class CDXUTTabItem : public CDXUTTabItemBase
{
public:
    HRESULT OnInitialize()
    {
        return S_OK;
    }
};

template<class BaseType>
class CDXUTTabItemImpl : public CDXUTTabItem
{
public:
    HRESULT Init(CDXUTDialogResourceManager* pManager)
    {
        __super::Init(pManager, TRUE);
        return ((BaseType *)this)->OnInitialize();
    }
};

class CDXUTTabControl: public CDXUTControl
{
public:
    enum TabControlStyleClass
    {
        TabControlVerticalLeft,
        TabControlHorizonTop,
        TabControlHorizonBottom,
        TabControlVerticalRight,
        TabControlWizzard,
        TabControlStyleMax,
    };

protected:
    RECT    m_TabRect;
    LONG    m_ButtonWidth, m_ButtonHeight, m_DialogWidth, m_ButtonInterval;
    LONG    m_ButtonWidthOverride, m_ButtonHeightOverride;
    ULONG   m_ActiveTabIndex;
    ULONG   m_Style;

    CGrowableArray<CDXUTTabButton*> m_Buttons;

    static const ULONG m_kInvalidTabIndex       = ~0u;
    static const ULONG m_kButtonTopInterval     = 5;
    static const ULONG m_kButtonLeftInterval    = 5;

public:
    CDXUTTabControl(CDXUTDialog *Parent = NULL);
    ~CDXUTTabControl();

    virtual VOID Render(FLOAT ElapsedTime);

    virtual BOOL MsgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

    virtual BOOL HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
    {
        return FALSE;
    }

    virtual BOOL HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam)
    {
        return FALSE;
    }

    virtual BOOL CanHaveFocus()
    {
        return TRUE;
    }

    virtual BOOL ContainsPoint(POINT pt)
    {
        if (m_Buttons.GetSize() == 0)
            return FALSE;

        RECT rc;

        rc.left     = m_x + m_ButtonWidth + m_kButtonLeftInterval;
        rc.right    = m_rcBoundingBox.right;
        rc.top      = m_rcBoundingBox.top;
        rc.bottom   = m_rcBoundingBox.bottom;

        return PtInRect(&rc, pt);
    }

    //
    // Attributes
    //
    LONG SetButtonWidth(LONG Width)
    {
        Swap(m_ButtonWidthOverride, Width);
        return Width;
    }

    LONG SetButtonHeight(LONG Height)
    {
        Swap(m_ButtonHeightOverride, Height);
        return Height;
    }

    LONG GetButtonWidth()
    {
        return m_ButtonWidthOverride != DXUT_SIZE_ADJUST ? m_ButtonWidthOverride : m_ButtonWidth;
    }

    LONG GetButtonHeight()
    {
        return m_ButtonHeightOverride != DXUT_SIZE_ADJUST ? m_ButtonHeightOverride : m_ButtonHeight;
    }

    ULONG GetActiveTabIndex()
    {
        return m_ActiveTabIndex;
    }

    CDXUTTabItem* GetActiveTab();

    ULONG GetTabIndex(CDXUTTabItem* Tab)
    {
        CDXUTTabButton *Button, **AddedButton;

        Button = Tab->GetButtonBinded();
        if (Button == NULL)
            return DXUT_INVALID_INDEX;

        AddedButton = m_Buttons.GetData();
        for (ULONG Count = m_Buttons.GetSize(); Count; ++AddedButton, --Count)
        {
            if (*AddedButton != Button)
                continue;

            return AddedButton - m_Buttons.GetData();
        }

        return DXUT_INVALID_INDEX;
    }

    VOID AdjustSize()
    {
        LONG    Height;
        ULONG   Count;

        Count = m_Buttons.GetSize();
        if (Count == 0)
            return;

        Height = Count * (GetButtonHeight() + m_ButtonInterval) - m_ButtonInterval + m_kButtonTopInterval * 2;

        SetSize(m_ButtonWidth * 4, Height);
    }

    HRESULT SetActiveTab(ULONG TabIndex);
    HRESULT SetActiveTab(CDXUTTabItem* Tab);

    ULONG SetStyle(ULONG Style);
    ULONG GetStyle();

    //
    // Operations
    //
    HRESULT AddTab(CDXUTTabItem* Tab, PWSTR TabName, PULONG AddedTabIndex = NULL);
    HRESULT RemoveTab(CDXUTTabItem* Tab);
	HRESULT RemoveTab(LONG TabIndex);
    HRESULT PressButton(LONG TabIndex);

protected:

    virtual VOID UpdateRects();
    VOID UpdateControlsPos();

    HRESULT
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
    );
};

class CDXUTTabButton : public CDXUTRadioButton
{
protected:
    CDXUTTabControl *m_TabControl;
    CDXUTTabItem    *m_TabItemBinded;

public:
    enum
    {
        TABBTN_ELEMENT_NORMAL,
        TABBTN_ELEMENT_MOUSEOVER,
        TABBTN_ELEMENT_PRESSED,
    };

public:
    CDXUTTabButton(CDXUTTabControl *TabControl, CDXUTDialog *Dialog);
    ~CDXUTTabButton();

    CDXUTTabItem* GetTabBinded();
    CDXUTTabItem* BindTab(CDXUTTabItem *TabItem);

    virtual HRESULT OnInit();
    virtual BOOL    HandleKeyboard(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    virtual BOOL    HandleMouse(HWND hWnd, UINT Message, POINT pt, WPARAM wParam, LPARAM lParam);
    virtual VOID    UpdateRects();
    virtual VOID    Render(FLOAT ElapsedTime);
};


#endif // DXUT_GUI_H

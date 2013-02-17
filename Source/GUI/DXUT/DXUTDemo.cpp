//#pragma comment(linker, "/ENTRY:wWinMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "MyLibrary.cpp"
#include <DXUT.h>
#include <DXUTGui.h>

OVERLOAD_CPP_NEW_WITH_HEAP(MemoryAllocator::GetGlobalHeap())

#include "TextDef.h"

class LolBoxTabQuickMessage : public CDXUTTabItemImpl<LolBoxTabQuickMessage>
{
protected:

public:
    HRESULT OnInitialize()
    {
//        AddCheckBox(QUICK_MSG_ENABLE, CTRL_TEXT_QUICK_MSG_ENABLE, 50, 10, 150, 20);
//        AddStatic(QUICK_MSG_TIP, CTRL_TEXT_QUICK_MSG_TIP, 50, 60, 300, 100);

        LONG_PTR X, Y;

        static WCHAR *msg[] =
        {
            L"test1",
            L"≤‚ ‘2",
            L"test3",
            L"≤‚ ‘4",
            L"test5",
            L"≤‚ ‘6",
            L"test7",
            L"≤‚ ‘8",
            L"test9",
        };

        static UCHAR HotKey[]=
        {
            '1', '2', '3', '4', '5', '6', '7', '8', '9', 
        };

        X = 50;
        Y = 10;
        for (ULONG Index = 0, Id = QMSG_1; Id != QMSG_9 + 1; ++Id)
        {
            AddButton(QMSG_1, msg[Index++], X, Y, 150, 20, HotKey[Index]);
            Y += 20 + 5;
        }

        return S_OK;
    }
};

class LolBoxTabMonsterCountDown : public CDXUTTabItemImpl<LolBoxTabMonsterCountDown>
{
public:
    HRESULT OnInitialize()
    {
        AddCheckBox(MONSTER_COUNT_DOWN_ENABLE, CTRL_TEXT_MONSTER_COUNTDOWN_ENABLE, 50, 10, 150, 20);
            AddCheckBox(MONSTER_COUNTDOWN_MINIMAP_SIGNAL,   CTRL_TEXT_MONSTER_COUNTDOWN_MINIMAP_SIGNAL, 80, 40, 200, 20);
            AddCheckBox(MONSTER_COUNTDOWN_SCREEN_SIGNAL,    CTRL_TEXT_MONSTER_COUNTDOWN_SCREEN_SIGNAL,  80, 70, 150, 20);
            AddCheckBox(MONSTER_COUNTDOWN_TEAM_SIGNAL,      CTRL_TEXT_MONSTER_COUNTDOWN_TEAM_SIGNAL,    80, 100, 150, 20);

        AddStatic(MONSTER_COUNTDOWN_TIP, CTRL_TEXT_MONSTER_COUNTDOWN_TIP, 50, 130, 300, 100);

        return S_OK;
    }
};

class LolBoxTabWard : public CDXUTTabItemImpl<LolBoxTabWard>
{
public:
    HRESULT OnInitialize()
    {
        AddCheckBox(WARD_ENALBE, CRTL_TEXT_WARD_ENABLE, 50, 10, 150, 20);
            AddCheckBox(WARD_SAVE_COUNT,   CRTL_TEXT_WARD_SAVE_COUNT, 80, 40, 150, 20);

        AddStatic(WARD_TIP, CTRL_TEXT_WARD_TIP, 50, 70, 300, 100);

        return S_OK;
    }
};

class LolBoxTabZoom : public CDXUTTabItemImpl<LolBoxTabZoom>
{
public:
    HRESULT OnInitialize()
    {
        AddCheckBox(ZOOM_ENABLE, CRTL_TEXT_ZOOM_ENABLE, 50, 10, 150, 20);
        AddStatic(ZOOM_TIP, CTRL_TEXT_ZOOM_TIP, 50, 40, 300, 100);

        return S_OK;
    }
};

class LolBoxTabTurret : public CDXUTTabItemImpl<LolBoxTabTurret>
{
public:
    HRESULT OnInitialize()
    {
        AddCheckBox(TURRET_ENABLE, CRTL_TEXT_TURRET_ENABLE, 50, 10, 150, 20);
        AddStatic(TURRET_TIP, CTRL_TEXT_TURRET_TIP, 50, 40, 300, 100);

        return S_OK;
    }
};

class DXUTLolBox
{
public:
    CDXUTDialog                 m_Dialog, m_DlgBg;
    CDXUTDialogResourceManager  m_DialogResourceManager;
    CDXUTStatic                *m_DialogPos;
    CDXUTTabControl            *m_TabCtrl;
    CDXUTElement                m_BgElement;

    LolBoxTabQuickMessage       m_TabMessage;
    LolBoxTabMonsterCountDown   m_TabMonsterCD;
    LolBoxTabWard               m_TabWard;
    LolBoxTabZoom               m_TabZoom;
    LolBoxTabTurret             m_TabTurret;

public:
    HRESULT Initialize()
    {
        LONG            Width = 800;
        ULONG           Index;
        CDXUTButton*    Button;
        RECT            rc2, WorkArea;;
        CDXUTElement    Element;

        m_DialogPos = NULL;

        m_Dialog.Init(&m_DialogResourceManager);

        Index = m_Dialog.AddTexture(L"button.tga");

        Element.SetFont(0, D3DCOLOR_ARGB( 255, 255, 255, 255 ), DT_LEFT | DT_VCENTER | DT_CENTER);
        Element.FontColor.States[DXUT_STATE_MOUSEOVER]  = D3DCOLOR_ARGB(255, 0, 0, 0);
        Element.FontColor.States[DXUT_STATE_DISABLED]   = D3DCOLOR_ARGB(200, 200, 200, 200);
        Element.TextureColor.States[DXUT_STATE_NORMAL]  = D3DCOLOR_ARGB(150, 255, 255, 255);
        Element.TextureColor.States[DXUT_STATE_FOCUS]   = D3DCOLOR_ARGB(200, 255, 255, 255);
        Element.TextureColor.States[DXUT_STATE_PRESSED] = D3DCOLOR_ARGB(255, 255, 255, 255);

        SetRect(&rc2, 0, 0, 137, 41);
        Element.SetTexture(Index, &rc2);
        m_Dialog.SetDefaultElement(DXUT_CONTROL_TAB_BUTTON, CDXUTTabButton::TABBTN_ELEMENT_NORMAL, &Element);

        OffsetRect(&rc2, RectWidth(rc2) + 2, 0);
        Element.SetTexture(Index, &rc2);
        m_Dialog.SetDefaultElement(DXUT_CONTROL_TAB_BUTTON, CDXUTTabButton::TABBTN_ELEMENT_MOUSEOVER, &Element);

        OffsetRect(&rc2, RectWidth(rc2) + 2, 0);
        Element.SetTexture(Index, &rc2);
        m_Dialog.SetDefaultElement(DXUT_CONTROL_TAB_BUTTON, CDXUTTabButton::TABBTN_ELEMENT_PRESSED, &Element);

        m_Dialog.SetSize(Width, 600);
        m_Dialog.SetLocation(5, 0);

        m_Dialog.SetBackgroundColors(0x80000000);

        m_Dialog.SetCaptionText(L"Dialog");
        m_Dialog.EnableCaption(TRUE);

        m_Dialog.GetRectClient(rc2);

        m_Dialog.AddTabControl(MAIN_TAB, 0, 0, RectWidth(rc2), RectHeight(rc2), m_TabCtrl->TabControlVerticalLeft, &m_TabCtrl);

        m_TabCtrl->SetButtonHeight(41);
        m_TabCtrl->SetButtonWidth(137);

        m_TabMessage.Init(&m_DialogResourceManager);
        m_TabMonsterCD.Init(&m_DialogResourceManager);
        m_TabWard.Init(&m_DialogResourceManager);
        m_TabZoom.Init(&m_DialogResourceManager);
        m_TabTurret.Init(&m_DialogResourceManager);

        m_TabCtrl->AddTab(&m_TabMessage, TAB_NAME_QUICK_MESSAGE, &Index);
        m_TabCtrl->AddTab(&m_TabMonsterCD, TAB_NAME_MONSTER_COUNT_DOWN);
        m_TabCtrl->AddTab(&m_TabWard, TAB_NAME_WARD_POSITION);
        m_TabCtrl->AddTab(&m_TabZoom, TAB_NAME_UNLIMITED_ZOOM);
        m_TabCtrl->AddTab(&m_TabTurret, TAB_NAME_TURRET_COUNT_DOWN);

        m_TabCtrl->SetActiveTab(Index);

        DXUT_TEXTURE_INFO Caption[] =
        {
            { L"title_left.tga",    { 0, 0, 52, 45 } },
            { L"title_center.tga",  { 0, 0, 25, 45 } },
            { L"title_right.tga",   { 0, 0, 52, 45 } },
        };

        m_Dialog.SetCaptionTexture(Caption, D3DCOLOR_ARGB(180, 255, 255, 255));

        LONG off = 0;

        RECT rc = { Width / 2 - Width / 4, off, rc.left + Width / 2, 45 + off };
        m_Dialog.SetCaptionRect(rc);

        m_TabCtrl->AdjustSize();
        m_Dialog.SetSize(m_TabCtrl->GetSize());

        if (GetClientRect(DXUTGetHWND(), &WorkArea))
        {
            INT  X, Y;

            X = (RectWidth(WorkArea) - m_Dialog.GetWidth()) / 2;
            Y = (RectHeight(WorkArea) - m_Dialog.GetHeight()) / 2;

            m_Dialog.SetLocation(X, Y);
        }

        DXUT_TEXTURE_INFO Frame[DXUT_DIALOG_FRAME_ELEMENT_COUNT] =
        {
            { L"left.tga",          { 0, 0, 11, 42  }, 5 },
            { L"border.tga",        { 0, 5, 32, 27  }, 5 },
            { L"right.tga",         { 20, 0, 31, 42 }, 5 },
            { L"bottom.tga",        { 0, 11, 45, 22 }, 5 },

            { L"topleft.tga",       { 0, 0, 26, 22  }, 5 },
            { L"topright.tga",      { 6, 0, 32, 22  }, 5 },
            { L"bottomright.tga",   { 0, 0, 38, 42  }, 5 },
            { L"bottomleft.tga",    { 0, 0, 38, 42  }, 5 },
        };

        m_Dialog.SetFrameTexture(Frame, DXUT_FRAME_DONT_DRAW_CAPTION, D3DCOLOR_ARGB(180, 255, 255, 255));

        m_DlgBg.Init(&m_DialogResourceManager);
        m_DlgBg.SetLocation(0, 0);
        m_DlgBg.SetSize(1280, 960);

        Index = m_DlgBg.AddTexture(L"xnview_wallpaper_20100402.bmp");
        if (Index != DXUT_INVALID_TEXTURE_ID)
        {
            SetRect(&rc2, 0, 0, 1280, 960);
            m_BgElement.SetTexture(Index, &rc2);
            m_BgElement.TextureColor.Current = D3DCOLOR_ARGB(255, 255, 255, 255);
        }
        else
        {
            m_BgElement.iTexture = Index;
        }

        return S_OK;
    }

    HRESULT Render(FLOAT ElapsedTime)
    {
        return m_Dialog.OnRender(ElapsedTime);
    }
};

#if !DISABLE_DXUT_DEMO_MAIN

VOID CALLBACK OnFrameRender(IDirect3DDevice9 *Device, double Time, FLOAT ElapsedTime, DXUTLolBox *Dialog)
{
    ULONG   BkColor;
    RECT    rc;

    Device->BeginScene();

    SCOPE_EXIT
    {
        Device->EndScene();
    }
    SCOPE_EXIT_END;

    GetClientRect(DXUTGetHWND(), &rc);

    BkColor = D3DCOLOR_ARGB(0, 128, 0, 128);
//    Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BkColor, 1.0f, 0);


    if (Dialog->m_DialogPos != NULL)
    {
        WCHAR buf[0x100];
        POINT pt;

        Dialog->m_Dialog.GetLocation(pt);
        swprintf(buf, L"X = %d, Y = %d, W = %d, H = %d", pt, Dialog->m_Dialog.GetWidth(), Dialog->m_Dialog.GetHeight());
        Dialog->m_DialogPos->SetText(buf);
    }

    if (Dialog->m_BgElement.iTexture != DXUT_INVALID_TEXTURE_ID)
    {
        Dialog->m_DialogResourceManager.m_pSprite->Begin(D3DXSPRITE_DONOTSAVESTATE);
        Dialog->m_DlgBg.DrawSprite(&Dialog->m_BgElement, &rc, .6f);
        Dialog->m_DialogResourceManager.m_pSprite->End();
    }

    Dialog->Render(ElapsedTime);
}

HRESULT
CALLBACK
OnCreateDevice(
    IDirect3DDevice9*   Device,
    D3DSURFACE_DESC*    BackBufferSurfaceDesc,
    DXUTLolBox           *Dialog
)
{
    HRESULT Result;

    Result = Dialog->m_DialogResourceManager.OnD3D9CreateDevice(Device);
    if (!FAILED(Result))
        Result = Dialog->Initialize();

    return Result;
}

HRESULT
CALLBACK
OnResetDevice(
    IDirect3DDevice9    *Device,
    D3DSURFACE_DESC     *BackBufferSurfaceDesc,
    DXUTLolBox          *Dialog
)
{
    return Dialog->m_DialogResourceManager.OnD3D9ResetDevice();
}

VOID CALLBACK OnLostDevice(DXUTLolBox *Dialog)
{
    Dialog->m_DialogResourceManager.OnD3D9LostDevice();
}

VOID CALLBACK OnDestroyDevice(DXUTLolBox *Dialog)
{
    Dialog->m_DialogResourceManager.OnD3D9DestroyDevice();
}

LRESULT
CALLBACK
MsgProc(
    HWND        hWnd,
    UINT        Message,
    WPARAM      wParam,
    LPARAM      lParam,
    BOOL       &NoFurtherProcessing,
    DXUTLolBox   *Dialog
)
{
    NoFurtherProcessing = Dialog->m_Dialog.MsgProc(hWnd, Message, wParam, lParam);

    return 0;
}

VOID
CALLBACK
OnGUIEvent(
    UINT            Event,
    INT             ControlID,
    CDXUTControl   *Control,
    DXUTLolBox     *Dialog
)
{
    CDXUTButton *Button;

    switch (ControlID)
    {
        case QMSG_1:
        case QMSG_2:
        case QMSG_3:
        case QMSG_4:
        case QMSG_5:
        case QMSG_6:
        case QMSG_7:
        case QMSG_8:
        case QMSG_9:
            Button = (CDXUTButton *)Control;
            MessageBoxW(0, Button->GetText(), 0, 64);
            break;
    }
}

MemoryAllocator mem;

ForceInline ULONG WinMain2(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, LONG CmdShow)
{
    UNREFERENCED_PARAMETER(Instance);
    UNREFERENCED_PARAMETER(PrevInstance);
    UNREFERENCED_PARAMETER(CmdLine);
    UNREFERENCED_PARAMETER(CmdShow);

    DXUTLolBox  dxut;
    RECT        WorkArea;


    DXUTSetCallbackD3D9DeviceCreated(   OnCreateDevice,     &dxut);
    DXUTSetCallbackD3D9DeviceReset(     OnResetDevice,      &dxut);
    DXUTSetCallbackD3D9FrameRender(     OnFrameRender,      &dxut);
    DXUTSetCallbackD3D9DeviceLost(      OnLostDevice,       &dxut);
    DXUTSetCallbackD3D9DeviceDestroyed( OnDestroyDevice,    &dxut);
    DXUTSetCallbackMsgProc(             MsgProc,            &dxut);

    DXUTSetCursorSettings(TRUE, TRUE);

    dxut.m_Dialog.SetCallback(OnGUIEvent, &dxut);

    DXUTInit(FALSE, FALSE);
    DXUTSetHotkeyHandling(FALSE, TRUE, TRUE);
    DXUTCreateWindow(L"CustomUI");
    DXUTCreateDevice(TRUE, 1024, 768);

    if (SystemParametersInfoW(SPI_GETWORKAREA, 0, &WorkArea, 0))
    {
        INT  X, Y, W, H;
        HWND hWnd = DXUTGetHWND();
        RECT rc;

        GetWindowRect(hWnd, &rc);

        X = ((WorkArea.right - WorkArea.left) - RectWidth(rc)) / 2;
        Y = ((WorkArea.bottom - WorkArea.top) - RectHeight(rc)) / 2;

//        X = 0;
//        Y = 0;
        SetWindowPos(hWnd, NULL, X, Y, 0, 0, SWP_NOSIZE);
    }

    return DXUTMainLoop();
}

INT WINAPI wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, INT CmdShow)
{
    UNREFERENCED_PARAMETER(Instance);
    UNREFERENCED_PARAMETER(PrevInstance);
    UNREFERENCED_PARAMETER(CmdShow);

    WinMain2(Instance, PrevInstance, CmdLine, CmdShow);
}

#endif

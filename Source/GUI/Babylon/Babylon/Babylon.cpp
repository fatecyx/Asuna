#pragma comment(lib, "../XmlParser/XMLParser.lib")

#include "Babylon.h"
#include <windowsx.h>
#include "ScriptDialog.h"
#include "ID.h"
#include "CtrlText.h"
#include "my_mem.h"

CBabylon::CBabylon()
{
    ULong   Length;
    TChar   szConfigPath[MAX_PATH];

    m_hMenuMain          = NULL;
    m_hFont              = NULL;
    m_hAccel             = NULL;
    m_SizeInfo.rc.left   = 0;
    m_SizeInfo.rc.top    = 0;
    m_SizeInfo.rc.right  = 0;
    m_SizeInfo.rc.bottom = 0;

    Length = GetExecuteDirectory(szConfigPath, countof(szConfigPath));
    lstrcpy(szConfigPath + Length, BL_STRING_CONFIG_FILE_NAME);
    m_ScriptParser.Parse(szConfigPath, &m_Config, sizeof(m_Config));
}

CBabylon::~CBabylon()
{
    m_ScriptParser.FreeScriptInfo(&m_Config);
}

Bool CBabylon::CheckSystemEnvironment()
{
    int x, y;

    if ((Byte)GetVersion() < 5)
        return False;

    x = GetSystemMetrics(SM_CXFULLSCREEN);
    if (x < 640)
        return False;

    y = GetSystemMetrics(SM_CYFULLSCREEN);
    if (y < 480)
        return False;

    return True;
}

Bool CBabylon::PreTranslateMessage(LPMSG lpMsg)
{
    if (m_hAccel && TranslateAccelerator(*this, m_hAccel, lpMsg))
        return True;

    HWND hWnd[] = { RichEdit, Image, *this };

    for (UInt32 i = 0; i != countof(hWnd); ++i)
        if (::IsDialogMessage(hWnd[i], lpMsg))
            return True;

    return __super::PreTranslateMessage(lpMsg);
}

Bool CBabylon::InitControls()
{
    HWND hWnd;
    RECT rc, rcRichEdit, rcClient;
    Long h, w, x, y, len;
    Long lTreeViewLeft = 5, lTreeViewTop = 5;
    SIZE Size;

    // status bar
    m_hWndSB = CreateWindowEx(0, STATUSCLASSNAME, NULL,
        WS_VISIBLE|WS_CHILD, 0, 0, 0, 0, m_hWnd, 0, m_hInstance, NULL);
    if (m_hWndSB == NULL)
        return False;

    GetClientRect(&rcClient);
    rcClient.right  -= rcClient.left;
    rcClient.bottom -= rcClient.top;
    rcClient.left = 0;
    rcClient.top  = 0;

    rcRichEdit.right = rcClient.right - 10;

    {
        w = rcClient.right - rcClient.left;

        INT32 Parts[] = { w / 5, w / 5 + w * 70 / 100, w };

        ::SendMessage(m_hWndSB, SB_SETPARTS, countof(Parts), (LPARAM)Parts);
    }

    // check boxes
    {
        HDC hDC;
        Int c = g_dwCheckBox;

        ::GetWindowRect(m_hWndSB, &rc);
        ScreenToClient(&rc);
        x = 10;
        y = rc.top - 5 - tm.tmHeight;
        rcRichEdit.bottom = rc.top - 10;

        GetClientRect(&m_rc);
        m_rc.bottom = y;

        len = rcClient.right * 25 / 100;
        hDC = GetDC();
        while (c--)
        {
            TChar *name = g_ciCheckBox[c].name;

            MeasureString(hDC, name, StrLength(name), &Size);
            w = Size.cx + 18;
            if (w > len)
                len = w + 20;

            hWnd = CreateWindowEx(0, WC_BUTTON, name, WS_TABSTOP|WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX,
                x, y, w, tm.tmHeight, *this, (HMENU)g_ciCheckBox[c].id, m_hInstance, 0);
            if (hWnd == NULL)
                return False;

            SafeSetWindowFont(hWnd, m_hFont, True);
            y -= tm.tmHeight + 3;
        }

        ReleaseDC(hDC);
    }

    // tree view
    h = y - tm.tmHeight * 2 - 5 + 3;
    w = len;

    hWnd = TreeView.Create(m_hWnd, lTreeViewLeft, lTreeViewTop, w, h, m_hInstance);
    if (hWnd == NULL)
        return False;

    // buttons under the tree view
    {
        int c = g_dwLButton;

        y = h + lTreeViewTop + 5;
        h = tm.tmHeight * 2;
        w = w / c - 5;

        for (int i = 0; i != c; ++i)
        {
            TChar *name = g_ciLButton[i].name;

            hWnd = CreateWindowEx(0, WC_BUTTON, name, WS_TABSTOP|WS_CHILD|BS_CENTER|WS_VISIBLE|WS_CLIPSIBLINGS,
                x, y, w, h, m_hWnd, (HMENU)g_ciLButton[i].id, m_hInstance, NULL);
            if (hWnd == NULL)
                return False;

            SafeSetWindowFont(hWnd, m_hFont, True);
            x += w + 5;
        }
    }

    // button at the right of tree view
    {
        int c = g_dwRButton;

        w = len;
        x = w + lTreeViewLeft + 5;
        w = (rcClient.right - w - 10) / (c + 1) - 5;
        h = tm.tmHeight * 2;
        rcRichEdit.left = x + 5;

        for (int i = 0; i != c; ++i)
        {
            TChar *name = g_ciRButton[i].name;

            hWnd = CreateWindowEx(0, WC_BUTTON, name, WS_TABSTOP|WS_CHILD|BS_CENTER|WS_VISIBLE|WS_CLIPSIBLINGS,
                x, lTreeViewTop, w, h, m_hWnd, (HMENU)g_ciRButton[i].id, m_hInstance, NULL);
            if (hWnd == NULL)
                return False;

            SafeSetWindowFont(hWnd, m_hFont, True);
            x += w + 5;
        }

        hWnd = CreateWindowEx(0, WC_COMBOBOX, NULL,
                   WS_TABSTOP|WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
                   x, lTreeViewTop, w, 0, m_hWnd, (HMENU)IDL_EXPORT_TYPE, m_hInstance, NULL);
        if (hWnd == NULL)
            return False;

        // make combobox at the center of right buttons
        ::GetWindowRect(hWnd, &rc);
        y = lTreeViewTop + h / 2 - (rc.bottom - rc.top) / 2;
        ::SetWindowPos(hWnd, 0, x, y, 0, 0, SWP_NOSIZE);

        ::SendMessage(hWnd, WM_SETFONT, (WPARAM)m_hFont, True);

        ComboBox_AddString(hWnd, _T("BMP"));
        ComboBox_AddString(hWnd, _T("PNG"));
        ComboBox_AddString(hWnd, _T("JPG"));
        ComboBox_SetCurSel(hWnd, 0);
        ComboBox_SetItemData(hWnd, 0, BBL_EXPORT_IMAGE_BMP);
        ComboBox_SetItemData(hWnd, 1, BBL_EXPORT_IMAGE_PNG);
        ComboBox_SetItemData(hWnd, 2, BBL_EXPORT_IMAGE_JPG);
    }

    // rich edit
    rcRichEdit.top = lTreeViewTop + h + 5;

    hWnd = RichEdit.Create(&rcRichEdit, m_hWnd, NULL, m_hInstance);
    if (hWnd == NULL)
        return False;

    RichEdit.SetFont(m_hFont);
    RichEdit.SetEventMask(ENM_MOUSEEVENTS);
    RichEdit.Hide();

    hWnd = Image.Create(&rcRichEdit, m_hWnd, NULL, m_hInstance);
    if (hWnd == NULL)
        return False;

#if 1
    DWORD i;
    TCHAR test[MAX_PATH];
    i = GetExecuteDirectory(test, countof(test));
    lstrcpy(test + i, _T("normal.bmp"));
    if (Image.CreateImage(test))
        ImageOperation(IDM_FILE_OPENSCR);
#endif

//    Image.Hide();
//    RichEdit.Show();

    return True;
}

Bool CBabylon::InitMenuAndAccel()
{
    LPACCEL lpAccel;
    UInt32  uAccelCount;
    extern SMenuItem Menu_Main[];
    extern DWORD dwMenuCount;

    if (m_hMenuMain)
        DestroyMenu(m_hMenuMain);

    uAccelCount = GetMenuCount(Menu_Main, dwMenuCount);
    lpAccel = (LPACCEL)mem.Alloc(uAccelCount * sizeof(*lpAccel));
    m_hMenuMain = CreateCombinedMenuEx(Menu_Main, dwMenuCount, False, lpAccel, &uAccelCount);
    if (m_hMenuMain && SetMenu(m_hMenuMain))
    {
        m_dwLastError = NO_ERROR;
    }
    else
    {
        m_dwLastError = GetLastError();
        mem.Free(lpAccel);
        return False;
    }

    if (m_hAccel)
        DestroyAcceleratorTable(m_hAccel);

    m_hAccel = NULL;
    if (uAccelCount && lpAccel)
    {
        m_hAccel = CreateAcceleratorTable(lpAccel, uAccelCount);
        if (m_hAccel == NULL)
            m_dwLastError = GetLastError();
    }

    mem.Free(lpAccel);

    return !m_dwLastError;
}

Bool CBabylon::OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
    HDC     hDC;
    RECT    rcClient;
    LOGFONT lf;

    SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, 0);
    lf.lfQuality = PROOF_QUALITY;
    m_hFont = CreateFontIndirect(&lf);

    hDC = GetDC();

    SelectObject(hDC, m_hFont);
    GetTextMetrics(hDC, &tm);
    SetBkMode(hDC, TRANSPARENT);
    SetBkColor(hDC, COLOR_APPWORKSPACE);

    ReleaseDC(hDC);

    if (!InitMenuAndAccel() || !InitControls())
    {
        return False;
    }

    GetWindowRect(&rcClient);
    m_SizeInfo.MinSize.cx = rcClient.right - rcClient.left;
    m_SizeInfo.MinSize.cy = rcClient.bottom - rcClient.top;

    GetClientRect(&rcClient);
    m_SizeInfo.LastSize.cx = rcClient.right - rcClient.left;
    m_SizeInfo.LastSize.cy = rcClient.bottom - rcClient.top;

    ::SetFocus(m_hWndSB);

//    SendMessage(WM_COMMAND, IDM_FILE_SCRLIST);
//    CloseForm();

    return True;
}

Void CBabylon::OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    POINT pt[5000];
    HBRUSH hBrush;
    LOGBRUSH lb;

    UNREFERENCED_PARAMETER(pt);
    BeginPaint(&ps);

    WChar ch = 0x266A;

    LPVoid pMem;
    DWORD dwBitsCount = tm.tmAveCharWidth * (tm.tmHeight + tm.tmExternalLeading) * 32;

    pMem = mem.Alloc(dwBitsCount + sizeof(BITMAPINFO));

    BITMAPINFO bmi;
    BITMAPFILEHEADER*   pBMPHeader   =   (BITMAPFILEHEADER*)pMem;
    BITMAPINFOHEADER*   pInfoHeader   =   (BITMAPINFOHEADER*)((BYTE   *)pBMPHeader   +   sizeof(BITMAPFILEHEADER));
    BYTE*   pBits   =   (BYTE*)pInfoHeader   +   sizeof(BITMAPINFOHEADER);

    UNREFERENCED_PARAMETER(bmi);
    UNREFERENCED_PARAMETER(hBrush);
    UNREFERENCED_PARAMETER(lb);

    pBMPHeader-> bfType   =   TAG2('BM');
    pBMPHeader-> bfSize   =   sizeof(BITMAPFILEHEADER)   +   sizeof(BITMAPINFOHEADER)   +   dwBitsCount;
    pBMPHeader-> bfReserved1   =   0;
    pBMPHeader-> bfReserved2   =   0;
    pBMPHeader-> bfOffBits   =   sizeof(BITMAPFILEHEADER)   +   sizeof(BITMAPINFOHEADER);

    pInfoHeader-> biSize   =   sizeof(BITMAPINFOHEADER);
    pInfoHeader-> biWidth   =   tm.tmAveCharWidth;
    pInfoHeader-> biHeight   =   tm.tmHeight + tm.tmExternalLeading;
    pInfoHeader-> biPlanes   =   GetDeviceCaps(ps.hdc,   PLANES);     //调色板数
    pInfoHeader-> biBitCount   =   32;
    pInfoHeader-> biCompression   =   BI_RGB;
    pInfoHeader-> biSizeImage   =   dwBitsCount;
    pInfoHeader-> biXPelsPerMeter   =   GetDeviceCaps(ps.hdc,   LOGPIXELSX);
    pInfoHeader-> biYPelsPerMeter   =   GetDeviceCaps(ps.hdc,   LOGPIXELSY);
    pInfoHeader-> biClrUsed   =   0;
    pInfoHeader-> biClrImportant   =   0;

    m_hBitMap = CreateBitmap(tm.tmAveCharWidth, pInfoHeader-> biHeight, 1, 32, NULL);
    SelectObject(ps.hdc, m_hBitMap);
    GetDIBits(ps.hdc, m_hBitMap, 0, pInfoHeader-> biHeight, pBits, (BITMAPINFO *)pInfoHeader, DIB_RGB_COLORS);
    TextOutW(ps.hdc, 0, 0, &ch, 1);
    GetDIBits(ps.hdc, m_hBitMap, 0, pInfoHeader-> biHeight, pBits, (BITMAPINFO *)pInfoHeader, DIB_RGB_COLORS);
    GetBitmapBits(m_hBitMap, dwBitsCount + sizeof(BITMAPINFO), pMem);
    mem.Free(pMem);


//    GetClientRect(&ps.rcPaint);
/*
    lb.lbColor = RGB(255, 0, 0);
    lb.lbHatch = 0;
    lb.lbStyle = 0;
    hBrush = CreateBrushIndirect(&lb);
    FrameRect(ps.hdc, &m_rc, hBrush);
    DeleteObject(hBrush);
*/
    EndPaint(&ps);

    return;

//    MoveToEx(ps.hdc, 0, m_SizeInfo.LastSize.cy / 2, NULL);
//    LineTo(ps.hdc, m_SizeInfo.LastSize.cx, m_SizeInfo.LastSize.cy / 2);
/*
y=Asin(wt+α)
A幅值
W=角频率
α=初相位角
t=自变量
*/
/*
    for (Int i = 0; i != countof(pt); ++i)
    {
        pt[i].x = i * m_SizeInfo.LastSize.cx / countof(pt);
        pt[i].y = (LONG)(m_SizeInfo.LastSize.cy / 2 * (1 - sin(2 * PI * i / countof(pt))));
    }
*/
    HGDIOBJ hGdiObj;
    POINT p;
    Char buf[100];
    Int32 i;
    RECT rc = { 100, 100, 500, 500 };

    UNREFERENCED_PARAMETER(hGdiObj);
    SetViewportOrgEx(ps.hdc, 100, 100, 0);
    SetWindowOrgEx(ps.hdc, 100, 100, 0);
    GetWindowOrgEx(ps.hdc, &p);
    i = sprintf(buf, "fffffffffffffffffffffffffffffffffff");
    RECT rc2 = { 0, 0, i * tm.tmAveCharWidth, m_SizeInfo.rc.bottom };
//    DrawTextExA(ps.hdc, buf, i, &rc2, 0, 0);

    LOGFONTW lf;
    GetObjectW(GetStockObject(SYSTEM_FIXED_FONT), sizeof(lf), &lf);
    ExtTextOutW(ps.hdc, 0, 0, 0, 0, lf.lfFaceName, StrLengthW(lf.lfFaceName), 0);

    FrameRect(ps.hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));

//    SetROP2(ps.hdc, R2_WHITE);
//    Polyline(ps.hdc, pt, countof(pt));
//    Polygon(ps.hdc, pt, countof(pt));

//    Arc(ps.hdc, 0, 0, m_SizeInfo.LastSize.cx / 2, m_SizeInfo.LastSize.cy / 2, 0, 0, 0, 0);

//    SelectObject(ps.hdc, hGdiObj);
//    DeleteObject(hGdiObjNew);

    EndPaint(&ps);
}

Void CBabylon::MoveWindowByDiff(HWND hWnd, Int32 DiffX, Int32 DiffY, UInt32 uFlags /* = SWP_NOSIZE */)
{
    RECT rcWindow;

    if (hWnd == NULL)
        return;

    ::GetWindowRect(hWnd, &rcWindow);
    ScreenToClient(&rcWindow);
    rcWindow.right  += DiffX;
    rcWindow.bottom += DiffY;
    if ((uFlags & SWP_NOSIZE))
    {
        rcWindow.left += DiffX;
        rcWindow.top  += DiffY;
    }
    ::SetWindowPos(hWnd, NULL, rcWindow.left, rcWindow.top,
        rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top, uFlags);
}

// 944 660
Void CBabylon::OnSize(HWND hWnd, UInt state, Int cx, Int cy)
{
    Int32 x, w, h, diffw, diffh, count;
    RECT  rc;

    if (m_SizeInfo.LastSize.cx == 0)
        return;

    if (state == SIZE_MINIMIZED)
        return;

    w = cx;
    h = cy;
    FORWARD_WM_SIZE(m_hWndSB, state, cx, cy, ::SendMessage);

    diffw = w - m_SizeInfo.LastSize.cx;
    diffh = h - m_SizeInfo.LastSize.cy;

    if (diffh == 0 && diffw == 0)
        return;

    m_SizeInfo.LastSize.cx = w;
    m_SizeInfo.LastSize.cy = h;
    {
        Int32 Parts[] = { w / 5, w / 5 + w * 70 / 100, w };
        ::SendMessage(m_hWndSB, SB_SETPARTS, countof(Parts), (LPARAM)Parts);
    }

    count = g_dwLButton;
    while (count--)
        MoveWindowByDiff(GetDlgItem(g_ciLButton[count].id), 0, diffh);

    count = g_dwCheckBox;
    while (count--)
        MoveWindowByDiff(GetDlgItem(g_ciCheckBox[count].id), 0, diffh);

    MoveWindowByDiff(TreeView, 0, diffh, SWP_NOMOVE);
    MoveWindowByDiff(Image, diffw, diffh, SWP_NOMOVE);

    ::GetWindowRect(GetDlgItem(IDB_PREV_FRAME), &rc);
    ScreenToClient(&rc);

    count = g_dwRButton;
    w = w - rc.left;
    x = rc.left;
    w = w / (count + 1) - 5;
    h = rc.bottom - rc.top;
    for (UInt32 i = 0; i != count; ++i)
    {
        ::SetWindowPos(GetDlgItem(g_ciRButton[i].id), NULL, x, rc.top, w, h, 0);
        x += w + 5;
    }

    hWnd = GetDlgItem(IDL_EXPORT_TYPE);
    ::GetWindowRect(hWnd, &rc);
    ScreenToClient(&rc);
    ::SetWindowPos(hWnd, NULL, x, rc.top, w, 10, 0);
}

Void CBabylon::OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
    lpMinMaxInfo->ptMinTrackSize = *(LPPOINT)&m_SizeInfo.MinSize;
    lpMinMaxInfo->ptMaxTrackSize.x = INT_MAX;
    lpMinMaxInfo->ptMaxTrackSize.y = INT_MAX;
}

DWORD CBabylon::OnMenuChar(HWND hWnd, UInt ch, UInt flags, HMENU hMenu)
{
    return MNC_EXECUTE;
}

Void CBabylon::OnCommand(HWND hWnd, Int id, HWND hWndCtrl, UInt codeNotify)
{
    TChar szPath[MAX_PATH];

    hWnd = GetFocus();

    switch (id)
    {
        case IDM_FILE_OPENSCR:
            {
                OPENFILENAME ofn;

                szPath[0] = 0;
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = m_hWnd;
                ofn.lpstrInitialDir = 0;
                ofn.lpstrFilter = _T("*.*\0*.*\0");
                ofn.lpstrFile = szPath;
                ofn.nMaxFile = countof(szPath);
                ofn.Flags = OFN_ALLOWMULTISELECT|OFN_ENABLESIZING|OFN_HIDEREADONLY|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;

                if (GetOpenFileName(&ofn))
                {
                    if (Image.CreateImage(szPath) == False)
                        break;
                    ImageOperation(id);
                }
            }
            break;

        case IDM_FILE_SCRLIST:
            {
                SBLScriptGameInfo GameInfo;
                if (!SelectScript(&GameInfo))
                    break;
            }
            break;

        case IDB_PAUSE:
        case IDB_STOP:
        case IDB_PLAY:
            wsprintf(szPath, _T("%08X"), GetTickCount());
            ::SendMessage(m_hWndSB, SB_SETTEXT, 2, (LPARAM)szPath);
            break;

        case IDB_NEXT_FRAME:
        case IDB_PREV_FRAME:
            ImageOperation(id);
            break;

        case ID_ABOUT:
            MessageBox(BL_STRING_ABOUT_MESSAGE);
            break;

        case ID_EXIT:
            CloseForm();
            break;

        case IDM_FILE_CLOSE:
            Image.DestroyImage();
            Image.Hide();
            break;
    }

    ::SetFocus(hWnd);
}

HFONT CBabylon::OnGetFont(HWND hWnd)
{
    return m_hFont;
}

Void CBabylon::OnDrawItem(HWND hWnd, const DRAWITEMSTRUCT *lpDrawItemStruct)
{
    HBRUSH hBrush;
    const DRAWITEMSTRUCT *p = lpDrawItemStruct;

    SetMsgHandled(False);

    hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    FillRect(p->hDC, &p->rcItem, hBrush);
    FrameRect(p->hDC, &p->rcItem, hBrush);
    if (p->itemState & ODS_SELECTED)
        InvertRect(p->hDC, &p->rcItem);
    if (p->itemState & ODS_FOCUS)
        DrawFocusRect(p->hDC, &p->rcItem);

    return;
}

Void CBabylon::OnRButtonUp(HWND hWnd, Int x, Int y, UInt flags)
{
    POINT pt = { x, y };

    ClientToScreen(&pt);
}

Void CBabylon::OnLButtonUp(HWND hWnd, Int x, Int y, UInt keyFlags)
{
    SendMessage(WM_NCLBUTTONUP, HTCAPTION);
}

Void CBabylon::OnLButtonDown(HWND hWnd, Bool fDoubleClick, Int x, Int y, UInt keyFlags)
{
    SendMessage(WM_NCLBUTTONDOWN, HTCAPTION);
}

Void CBabylon::OnSetFocus(HWND hWnd, HWND hWndOldFocus)
{
    if (hWndOldFocus == m_hWnd || hWndOldFocus == NULL)
        ::SetFocus(m_hWndSB);
}

Void CBabylon::OnClose(HWND hWnd)
{
//    AnimateWindow(*this, 1000, AW_HIDE|AW_BLEND);
    DestroyWindow();
}

Bool CBabylon::OnQueryEndSession(HWND hWnd)
{
    return True;
}

Void CBabylon::OnDestroy(HWND hWnd)
{
    if (m_hMenuMain)
    {
        DestroyMenu(m_hMenuMain);
        m_hMenuMain = NULL;
    }

    if (m_hFont)
    {
        DeleteObject(m_hFont);
        m_hFont = NULL;
    }

    PostQuitMessage(0);
}

Void CBabylon::OnMouseWheel(HWND hWnd, Int xPos, Int yPos, Int zDelta, UInt fwKeys)
{
    POINT pt = { xPos, yPos };

    hWnd = WindowFromPoint(pt);
    if (hWnd != *this)
    {
        MapWindowPoints(hWnd, &pt, 1);
        FORWARD_WM_MOUSEWHEEL(hWnd, pt.x, pt.y, zDelta, fwKeys, ::SendMessage);
    }
}

Void CBabylon::ImageOperation(UInt32 nItemID)
{
    UInt32 ret;
    TChar  buf[20];

    switch (nItemID)
    {
        case IDB_NEXT_FRAME:
            ret = Image.NextFrame();
            break;

        case IDB_PREV_FRAME:
            ret = Image.PrevFrame();
            break;

        case IDM_FILE_OPENSCR:
            RichEdit.Hide();
            Image.Show();
            Image.ShowImage();
            ret = Image.GetFrameNum();
            if (ret + 1)
            {
                wsprintf(buf, _T("共%u帧"), ret);
                ::SendMessage(m_hWndSB, SB_SETTEXT, 1, (LPARAM)buf);
            }
            ret = Image.GetCurrentFrame();
            break;
    }

    if (ret == -1)
        return;

    wsprintf(buf, _T("当前第%u帧"), ret + 1);
    ::SendMessage(m_hWndSB, SB_SETTEXT, 0, (LPARAM)buf);
}

NoInline Bool CBabylon::SelectScript(SBLScriptGameInfo *pGameInfo)
{
    Bool  Result;
    ULong GameTypeCount, BlockSize;
    TChar szPath[MAX_PATH], *pszPath;

    CScriptDialog          ScriptDialog;
    SBLScriptGameList     *pGameList;
    SBLScriptGameTypeItem *pGameType;

    pszPath = szPath + GetExecuteDirectory(szPath, countof(szPath));

    BlockSize = m_Config.GameTypeCount * sizeof(*pGameList);
    pGameList = (SBLScriptGameList *)_alloca(BlockSize);
    ZeroMemory(pGameList, BlockSize);

    pGameType = m_Config.pGameType;
    GameTypeCount = 0;
    for (ULong i = m_Config.GameTypeCount; i; --i)
    {
        lstrcpy(pszPath, pGameType->ListScriptPath);
        if (BL_SUCCEEDED(m_ScriptParser.Parse(szPath, pGameList + GameTypeCount, sizeof(*pGameList))))
            ++GameTypeCount;
        ++pGameType;
    }

    Result = False;
    ScriptDialog.SetGameListInfo(&m_Config, pGameList, GameTypeCount);
    if (ScriptDialog.DoModal(*this, m_hInstance) == IDOK)
    {
        if (ScriptDialog.GetGameInfoSelected() != NULL)
        {
            *pGameInfo = *ScriptDialog.GetGameInfoSelected();
            Result = True;
        }
    }

    for (ULong i = m_Config.GameTypeCount; i; --i)
        m_ScriptParser.FreeScriptInfo(pGameList++);

    return Result;
}
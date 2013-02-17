#include "Packer2.h"
#include "my_api.h"
#include "my_crt.h"

OVERLOAD_OP_NEW

CPacker2::CPacker2()
{
    m_hAccel = NULL;
    m_hFont = NULL;
    m_MinSize.cx = 0;
    m_MinSize.cy = 0;
    m_ThreadLVInsertID = 0;
    m_pszDefExtension = NULL;
    m_LastClientSize.cx = 0;
    m_LastClientSize.cy = 0;
}

CPacker2::~CPacker2()
{
    ReleaseAll();
}

Bool CPacker2::UpdateSettings(LPCREATESTRUCT lpCreateStruct)
{
    UInt32 PathLength;
    TChar *pszBuffer, szBuffer[MAX_PATH], szExePath[MAX_PATH], szConfigPath[MAX_PATH];
    TChar *szKey[] = 
    {
        _T("Plugin"),
        _T("Param"),
        _T("Extension"),
    };
    CEditBox *pEdit[] = { &m_EditPlugin, &m_EditParam, NULL };

    static TChar szSection[] = _T("Amano");

    PathLength = GetExecuteDirectory(szExePath, countof(szExePath));
    lstrcpy(szConfigPath, szExePath);
    lstrcpy(szConfigPath + PathLength, _T("Packer.ini"));

    for (UInt32 i = 0; i != min(countof(szKey), countof(pEdit)); ++i)
    {
        UInt32 j = GetPrivateProfileString(szSection, szKey[i], _T(""), szBuffer, countof(szBuffer), szConfigPath);
        if (IsPathExists(szBuffer) || pEdit[i] == &m_EditParam)
        {
            pszBuffer = szBuffer;
        }
        else
        {
            lstrcpy(szExePath + PathLength, szBuffer);
            pszBuffer = szExePath;
        }

        if (pEdit[i])
        {
            pEdit[i]->SetText(pszBuffer);
        }
        else
        {
            if (m_pszDefExtension = new TChar[j + 1])
                lstrcpy(m_pszDefExtension, pszBuffer);
        }
    }
/*
    Int32  Width, Height;
    Width  = GetPrivateProfileInt(szSection, _T("Width"), CW_USEDEFAULT, szConfigPath);
    Height = GetPrivateProfileInt(szSection, _T("Height"), CW_USEDEFAULT, szConfigPath);
    if (Width != CW_USEDEFAULT && Height != CW_USEDEFAULT)
    {
        Width = Width == CW_USEDEFAULT ? m_LastClientSize.cx : Width;
        Height = Height == CW_USEDEFAULT ? m_LastClientSize.cy : Height;
        lpCreateStruct->cx = Width;
        lpCreateStruct->cy = Height;
    }
*/
    return True;
}

Void CPacker2::ReleaseAll()
{
    if (m_hFont)
    {
        DeleteObject(m_hFont);
        m_hFont = NULL;
    }
    if (m_hAccel)
    {
        DestroyAcceleratorTable(m_hAccel);
        m_hAccel = NULL;
    }
    safe_delete(m_pszDefExtension);
}

Bool CPacker2::PreTranslateMessage(LPMSG lpMsg)
{
    if (TranslateAccelerator(*this, m_hAccel, lpMsg))
        return True;

    if (IsDialogMessage(lpMsg))
        return True;

    return False;
}

Bool CPacker2::OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
    HDC hDC;
    Int cx, cy;
    Bool bRet;
    RECT rcWindow;
    ACCEL accel[] = { { FVIRTKEY, VK_ESCAPE, IDCANCEL } };

    ReleaseAll();

    GetWindowRect(&rcWindow);

    cx = (rcWindow.right  - rcWindow.left) / 8;
    cy = (rcWindow.bottom - rcWindow.top) / 8;
    rcWindow.left += cx;
    rcWindow.right -= cx;
    rcWindow.top += cy;
    rcWindow.bottom -= cy;
    m_MinSize.cx = rcWindow.right - rcWindow.left;
    m_MinSize.cy = rcWindow.bottom - rcWindow.top;
    SetWindowPos(0, &rcWindow, 0);

    m_hFont = CreateIconTitleFont();
    SetWindowFont(*this, m_hFont, True);

    hDC = GetDC();
    SelectObject(hDC, m_hFont);
    bRet = InitControls(hDC);
    ReleaseDC(hDC);

    if (bRet == False)
    {
        return False;
    }

    m_hAccel = CreateAcceleratorTable(accel, countof(accel));

    DragAcceptFiles();

    UpdateSettings(lpCreateStruct);

    return True;
}

Bool CPacker2::InitControls(HDC hDC)
{
    Int x, y, w, h;
    HWND hWnd;
    SIZE StringSize;
    RECT rcClient;

    CEditBox *pEditBox[] = { &m_EditOutPut, &m_EditPlugin, &m_EditParam };

    static TChar *szButtonText[] = 
    {
        _T("&Browse"),
        _T("B&rowse"),
        _T("&Update"),
    };
    static TChar *szButtonBottomText[] = 
    {
        _T("&All"),
        _T("&None"),
        _T("&Invert"),
        _T("&Remove"),
        _T("&Clear"),
        _T("&Pack"),
    };
    static TChar *szStaticText[] = 
    {
        _T("Output"),
        _T("Plugin"),
        _T("Parameter"),
    };

    GetClientRect(&rcClient);
    m_LastClientSize.cx = rcClient.right - rcClient.left;
    m_LastClientSize.cy = rcClient.bottom - rcClient.top;

    y = YStart;

    for (UInt32 i = 0; i != countof(pEditBox); ++i)
    {
        HMENU hMenuAsID;
        x = XStart;

        MeasureString(hDC, szStaticText[i], lstrlen(szStaticText[i]), &StringSize);
        hWnd = CreateWindowEx(0, WC_STATIC, szStaticText[i], WS_VISIBLE|WS_CHILD, 
                x, y, StringSize.cx, StringSize.cy, *this, 0, 0, 0);
        if (hWnd == NULL)
            return False;

        SetWindowFont(hWnd, m_hFont, True);

        y += StringSize.cy + 5;
        w = m_LastClientSize.cx - x - 10;
        h = StringSize.cy;

        MeasureString(hDC, szButtonText[i], lstrlen(szButtonText[i]), &StringSize);
        w -= StringSize.cx * 2 + 5;

        h = h * 3 / 2;
        hMenuAsID = (HMENU)(PAK2_ID_EDIT_FIRST + i);
        if (pEditBox[i]->CreateEx(*this, m_hInstance, hMenuAsID, NULL, x, y, w, h) == NULL)
            return False;

        pEditBox[i]->SetLimitText(MAX_PATH);
        pEditBox[i]->SetFont(m_hFont, True);

        x += w + 5;
        w = StringSize.cx * 2;
        w = m_LastClientSize.cx - x - XStart;

        hMenuAsID = (HMENU)(PAK2_ID_BTN_FIRST + i);
        hWnd = CreateWindowEx(0, WC_BUTTON, szButtonText[i], WS_VISIBLE|WS_CHILD|WS_TABSTOP, 
            x, y - 3, w, h + 6, *this, hMenuAsID, m_hInstance, 0);
        if (hWnd == NULL)
            return False;

        SetWindowFont(hWnd, m_hFont, True);
        y += h + 5;
    }

    x = XStart;
    y += 5;

    static TChar *szButtonTextMiddle[] = 
    {
        _T("&Encrypt"),
        _T("Co&mpress"),
    };

    w = 0;
    for (UInt32 i = 0; i != countof(szButtonTextMiddle); ++i)
    {
        MeasureString(hDC, szButtonTextMiddle[i], lstrlen(szButtonTextMiddle[i]), &StringSize);
        if (w < StringSize.cx)
            w = StringSize.cx;
    }

    w += 5;

    hWnd = CreateWindowEx(0, WC_BUTTON, _T("&Encrypt"), WS_CHILD|WS_VISIBLE|WS_TABSTOP, 
        x, y, w, h, *this, (HMENU)PAK2_ID_BTN_ENCRYPT, m_hInstance, 0);
    if (hWnd == NULL)
        return False;

    SetWindowFont(hWnd, m_hFont, True);

    x += w + 5;
    hWnd = CreateWindowEx(0, WC_BUTTON, _T("Co&mpress"), WS_CHILD|WS_VISIBLE|WS_TABSTOP, 
        x, y, w, h, *this, (HMENU)PAK2_ID_BTN_COMPRESS, m_hInstance, 0);
    if (hWnd == NULL)
        return False;

    SetWindowFont(hWnd, m_hFont, True);

    x += w + 5;
    w = m_LastClientSize.cx - x - XStart;

    hWnd = m_ProgessBar.CreateEx(*this, m_hInstance, (HMENU)-1, NULL, x, y, w, h);
    if (hWnd == NULL)
        return False;

    x = XStart;
    y += h + 10;
    w = m_LastClientSize.cx - XStart * 2;
    h = m_LastClientSize.cy - y - h * 2 - 6;

    hWnd = m_ListView.CreateEx(*this, m_hInstance, (HMENU)-1, NULL, x, y, w, h);
    if (hWnd == NULL)
        return False;

    m_ListView.SetFont(m_hFont);
    m_ListView.InsertColumn(0, _T("FileName"), 0);
//    m_ListView.AddExStyle(LVS_EX_CHECKBOXES);
    m_ListView.ModifyStyle(0, LVS_NOCOLUMNHEADER, 0);
    {
        LVCOLUMN lvColumn;

        lvColumn.mask = LVCF_WIDTH;
        lvColumn.cx = w - GetSystemMetrics(SM_CXVSCROLL) - 10;
        lvColumn.cxMin = 0;
        m_ListView.SetColumn(0, &lvColumn);
    }

    y += h;
    h = StringSize.cy * 3 / 2 + 6;
    y += h / 2 - 3;
    w = (m_LastClientSize.cx - XStart * 2) / (PAK2_ID_BTN_AT_BOTTOM_LAST - PAK2_ID_BTN_AT_BOTTOM_FIRST + 1);
    w -= SPACE_BETWEEN_BTN;

    for (UInt i = PAK2_ID_BTN_AT_BOTTOM_FIRST, j = 0; i != PAK2_ID_BTN_AT_BOTTOM_LAST + 1; ++i, ++j)
    {
        const UInt ButtonNum = PAK2_ID_BTN_AT_BOTTOM_LAST - PAK2_ID_BTN_AT_BOTTOM_FIRST + 1;

        hWnd = CreateWindowEx(0, WC_BUTTON, szButtonBottomText[j], 
                WS_CHILD|WS_VISIBLE|WS_TABSTOP, x, y, w, h, *this, (HMENU)i, m_hInstance, NULL);
        if (hWnd == NULL)
            return False;

        SetWindowFont(hWnd, m_hFont, True);
        x += w + SPACE_BETWEEN_BTN;
        if (j + 1 == ButtonNum / 2)
        {
            x = m_LastClientSize.cx - XStart;
            x -= (w + SPACE_BETWEEN_BTN) * (PAK2_ID_BTN_AT_BOTTOM_LAST - i);
            x += SPACE_BETWEEN_BTN;
        }
    }

    return True;
}

LRESULT CPacker2::OnButton(WORD wNotifyCode, WORD wID, HWND hWndCtl, Bool& bHandled)
{
    switch (wID)
    {
        case PAK2_ID_BTN_CLEAR:
            m_ListView.DeleteAllItem();
            break;

        case PAK2_ID_BTN_STOP_INSERT:
            if (m_ThreadLVInsertID)
            {
                PostThreadMessage(m_ThreadLVInsertID, WM_USER_INTERRUPT_INSERT, 0, 0);
                m_ThreadLVInsertID = 0;
            }
            break;
    }

    return NO_ERROR;
}

LRESULT CPacker2::OnInsertFinish(UInt uMsg, WPARAM wParam, LPARAM lParam, Bool &bHandled)
{
    return NO_ERROR;
}

Void CPacker2::OnCommand(HWND hWnd, Int id, HWND hWndCtl, UInt codeNotify)
{
    switch (id)
    {
        case IDCANCEL:
            CloseForm();
            break;
    }
}

Void CPacker2::OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
    lpMinMaxInfo->ptMinTrackSize = *(LPPOINT)&m_MinSize;
}

enum EDeltaWindowOrientation
{
    DWP_X_UNCHANGE      = 0x0000,
    DWP_X_CHANGE        = 0x0001,
    DWP_X_FLAG          = 0x000F,

    DWP_Y_UNCHANGE      = 0x0000,
    DWP_Y_CHANGE        = 0x0010,
    DWP_Y_FLAG          = 0x00F0,

    DWP_WIDTH_UNCHANGE  = 0x0000,
    DWP_WIDTH_CHANGE    = 0x0100,
    DWP_WIDTH_FLAG      = 0x0F00,

    DWP_HEIGHT_UNCHANGE = 0x0000,
    DWP_HEIGHT_CHANGE   = 0x1000,
    DWP_HEIGHT_FLAG     = 0xF000,
};

Bool CPacker2::DeltaWindowPos(HWND hWnd, Int deltaX, Int deltaY, LPCRECT lprcControl, UInt Flags, UInt Org)
{
    Int x, y, w, h;
    UInt org;
    RECT rcControl;

    rcControl = *lprcControl;
    ScreenToClient(&rcControl);

    x = rcControl.left;
    y = rcControl.top;
    w = rcControl.right  - rcControl.left;
    h = rcControl.bottom - rcControl.top;

    org = Org & DWP_X_FLAG;
    if (org)
    {
        if (org == DWP_X_CHANGE)
            x += deltaX;
    }

    org = Org & DWP_Y_FLAG;
    if (org)
    {
        if (org == DWP_Y_CHANGE)
            y += deltaY;
    }

    org = Org & DWP_WIDTH_FLAG;
    if (org)
    {
        if (org == DWP_WIDTH_CHANGE)
            w += deltaX;
    }

    org = Org & DWP_HEIGHT_FLAG;
    if (org)
    {
        if (org == DWP_HEIGHT_CHANGE)
            h += deltaY;
    }

    return ::SetWindowPos(hWnd, NULL, x, y, w, h, Flags);
}

Void CPacker2::OnSize(HWND hWnd, UInt state, Int cx, Int cy)
{
    if (m_LastClientSize.cx == 0 || state == SIZE_MINIMIZED)
        return;

    Int deltaX, deltaY;
    RECT rcControl;

    deltaX = cx - m_LastClientSize.cx;
    deltaY = cy - m_LastClientSize.cy;
    if (deltaY == 0 && deltaX == 0)
        return;

    CEditBox *pEditBox[] = { &m_EditOutPut, &m_EditPlugin, &m_EditParam };

    m_LastClientSize.cx = cx;
    m_LastClientSize.cy = cy;

    for (UInt32 i = PAK2_ID_BTN_OUTPUT, j = 0; i != PAK2_ID_BTN_PARAM + 1; ++i, ++j)
    {
        hWnd = GetDlgItem(i);
        ::GetWindowRect(hWnd, &rcControl);
        DeltaWindowPos(hWnd, deltaX, deltaY, &rcControl, SWP_NOSIZE, DWP_X_CHANGE);

        pEditBox[j]->GetWindowRect(&rcControl);
        DeltaWindowPos(*pEditBox[j], deltaX, deltaY, &rcControl, SWP_NOMOVE, DWP_WIDTH_CHANGE);
    }

    m_ProgessBar.GetWindowRect(&rcControl);
    DeltaWindowPos(m_ProgessBar, deltaX, deltaY, &rcControl, SWP_NOMOVE, DWP_WIDTH_CHANGE);
    m_ListView.GetWindowRect(&rcControl);
    DeltaWindowPos(m_ListView, deltaX, deltaY, &rcControl, SWP_NOMOVE, DWP_WIDTH_CHANGE|DWP_HEIGHT_CHANGE);

    Int w;
    const UInt ButtonNum = PAK2_ID_BTN_AT_BOTTOM_LAST - PAK2_ID_BTN_AT_BOTTOM_FIRST + 1;

    w = (m_LastClientSize.cx - XStart * 2) / ButtonNum;
    w -= SPACE_BETWEEN_BTN;
    cx = XStart;

    for (UInt i = PAK2_ID_BTN_AT_BOTTOM_FIRST; i != PAK2_ID_BTN_AT_BOTTOM_LAST + 1; ++i)
    {
        Int x, y, h;

        hWnd = GetDlgItem(i);
        ::GetWindowRect(hWnd, &rcControl);
        ScreenToClient(&rcControl);
        x = rcControl.left;
        y = rcControl.top + deltaY;
        h = rcControl.bottom - rcControl.top;
        if (i == PAK2_ID_BTN_AT_BOTTOM_LAST)
            x += deltaX;
        else if (i - PAK2_ID_BTN_AT_BOTTOM_FIRST == ButtonNum / 2)
        {
            cx = m_LastClientSize.cx - XStart;
            cx -= (w + SPACE_BETWEEN_BTN) * (PAK2_ID_BTN_AT_BOTTOM_LAST + 1 - i);
            cx += SPACE_BETWEEN_BTN;
        }

        ::SetWindowPos(hWnd, NULL, cx, y, w, h, 0);
        cx += w + SPACE_BETWEEN_BTN;
    }

    {
        LVCOLUMN lvColumn;

        lvColumn.mask = LVCF_WIDTH;
        lvColumn.cx = m_LastClientSize.cx - XStart * 2 - GetSystemMetrics(SM_CXVSCROLL) - 10;
        lvColumn.cxMin = 0;
        m_ListView.SetColumn(0, &lvColumn);
    }
}

Int32 STDCALL EnumFilesCallBack(LPVoid lpBuffer, LPWIN32_FIND_DATAW wfd, PVoid lpParam)
{
#if (defined(UNICODE) && defined(_UNICODE))
    lstrcpy((PWChar)lpBuffer, wfd->cFileName);
#else
    WideCharToMultiByte(CP_ACP, 0, wfd->cFileName, -1, (PChar)lpBuffer, MAX_PATH, 0, 0);
#endif

    return 1;
}

NoInline Bool CPacker2::GetRelativeWindowRect(HWND hWnd, LPRECT lpRect)
{
    if (::GetWindowRect(hWnd, lpRect) == False)
        return False;
    return ScreenToClient(lpRect);
}

DWORD CPacker2::ListViewAddItemThreadWorker(SLVAddFileInfo *pInfo)
{
    UInt  PathCount, FileCount;
    TChar szPath[MAX_PATH], szBtnPackText[0x100], szTitle[0x200];
    HDROP hDrop;
    MSG   msg;

    hDrop = pInfo->hDrop;

    _InterlockedExchange((PLong)&pInfo->bInit, True);

    PathCount = DragQueryFile(hDrop, -1, 0, 0);
    if (PathCount)
    {
        HWND hWnd;
        for (UInt32 i = PAK2_ID_BTN_FIRST; i != PAK2_ID_BTN_LAST; ++i)
        {
            hWnd = GetDlgItem(i);
            if (hWnd == NULL)
                continue;
            else if (i == PAK2_ID_BTN_PACK)
            {
                ::GetWindowText(hWnd, szBtnPackText, countof(szBtnPackText));
                ::SetWindowText(hWnd, _T("&Stop"));
                ::SetWindowLongPtr(hWnd, GWL_ID, PAK2_ID_BTN_STOP_INSERT);
            }
            else if (i != PAK2_ID_BTN_STOP_INSERT)
                ::EnableWindow(hWnd, False);
        }

        FileCount = 0;
        GetWindowText(szTitle, countof(szTitle));
        m_ListView.SetRedraw(False);
    }

    for (UInt i = 0; i != PathCount; ++i)
    {
        DragQueryFile(hDrop, i, szPath, countof(szPath));

        if ((GetFileAttributes(szPath) & FILE_ATTRIBUTE_DIRECTORY) == 0)
        {
            m_ListView.AddString(szPath);
            wsprintf(szPath, _T("%u"), ++FileCount);
            SetWindowText(szPath);
        }
        else
        {
            WChar *pszPath, (*szFileList)[MAX_PATH];
            Large_Integer Count;

#if (!defined(UNICODE) && !defined(_UNICODE))
            WChar szPathW[MAX_PATH];
            MultiByteToWideChar(CP_ACP, 0, szPath, -1, szPathW, countof(szPathW));
            pszPath = szPathW;
#else
            pszPath = szPath;
#endif
            do
            {
                if (!EnumDirectoryFiles(
                        (LPVoid *)&szFileList, 
                        L"*.*", 
                        sizeof(*szFileList), 
                        pszPath, 
                        &Count, 
                        EnumFilesCallBack,
                        NULL,
                        ENUM_DIRECTORY_FILES_FLAG_ENUMSUBDIR))
                {
                    break;
                }

                for (UInt i = 0; i != Count.LowPart; ++i)
                {
                    wsprintf(szPath, _T("%u"), ++FileCount);
                    SetWindowText(szPath);
                    m_ListView.AddString((PTChar)szFileList[i]);
                    if ((i & 0x3FF) == 0 && PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                    {
                        if (msg.message == WM_USER_INTERRUPT_INSERT)
                            goto INSERT_END;
                    }
                }

                EnumDirectoryFilesFree(szFileList);
            } while (0);
        }

        if ((i & 0x3FF) == 0 && PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_USER_INTERRUPT_INSERT)
                break;
        }
    }

INSERT_END:

    if (PathCount)
    {
        HWND hWnd;
        for (UInt32 i = PAK2_ID_BTN_FIRST; i != PAK2_ID_BTN_LAST; ++i)
        {
            hWnd = GetDlgItem(i);
            if (hWnd == NULL)
                continue;
            else if (i == PAK2_ID_BTN_STOP_INSERT)
            {
                ::SetWindowText(hWnd, szBtnPackText);
                ::SetWindowLongPtr(hWnd, GWL_ID, PAK2_ID_BTN_PACK);
            }
            else
                ::EnableWindow(hWnd, True);
        }

        m_ListView.SetRedraw(True);
        Sleep(3000);
        SetWindowText(szTitle);
    }

    DragFinish(hDrop);
    SendMessage(WM_USER_INSERTITEM_FINISH, 0, 0);

    return 0;
}

DWORD STDCALL CPacker2::ListViewAddItemThread(LPVoid lpParam)
{
    SLVAddFileInfo *pInfo = (SLVAddFileInfo *)lpParam;
    return pInfo->pThis->ListViewAddItemThreadWorker(pInfo);
}

Void CPacker2::OnDropFiles(HWND hWnd, HDROP hDrop)
{
    POINT pt;
    RECT  rcCtrl;
    TChar szPath[MAX_PATH];
    CEditBox *pEditBox[] = { &m_EditOutPut, &m_EditPlugin, &m_EditParam };

    DragQueryPoint(hDrop, &pt);

    GetRelativeWindowRect(m_ListView, &rcCtrl);
    if (PtInRect(&rcCtrl, pt))
    {
        HANDLE hThread;
        SLVAddFileInfo info;

        info.bInit = False;
        info.hDrop = hDrop;
        info.pThis = this;

        hThread = CreateThread(NULL, 0, ListViewAddItemThread, &info, 0, &m_ThreadLVInsertID);
        if (hThread == NULL)
        {
            MessageBox(_T("Add files to ListView failed"));
        }
        else
        {
            CloseHandle(hThread);
            while (info.bInit == False)
                Sleep(1);

            return;
        }
    }
    else for (UInt i = 0; i != countof(pEditBox); ++i)
    {
        GetRelativeWindowRect(*pEditBox[i], &rcCtrl);
        if (PtInRect(&rcCtrl, pt))
        {
            DragQueryFile(hDrop, 0, szPath, countof(szPath));
            pEditBox[i]->SetText(szPath);
        }
    }

    DragFinish(hDrop);
}

Void CPacker2::OnLButtonDown(HWND hWnd, Bool fDoubleClick, Int x, Int y, UInt keyFlags)
{
    FORWARD_WM_NCLBUTTONDOWN(hWnd, fDoubleClick, 0, 0, HTCAPTION, ::SendMessage);
}

Void CPacker2::OnLButtonUp(HWND hWnd, Int x, Int y, UInt keyFlags)
{
    FORWARD_WM_NCLBUTTONUP(hWnd, 0, 0, HTCAPTION, ::SendMessage);
}

Void CPacker2::OnClose(HWND hWnd)
{
    DestroyWindow();
}

Void CPacker2::OnDestroy(HWND hWnd)
{
    ReleaseAll();
    PostQuitMessage(0);
}
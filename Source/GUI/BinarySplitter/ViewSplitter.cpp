#include "ViewSplitter.h"
#include <commctrl.h>
#include "my_mem.h"

//OVERLOAD_OP_NEW

CViewSplitter::CViewSplitter() :
    m_DlgSplit(IDD_SPLIT),
    m_DlgMerge(IDD_MERGE),
    m_DlgAbout(IDD_ABOUT)
{
    m_hAccel            = NULL;
    m_hFont             = NULL;
    m_MinSize.cx        = 0;
    m_MinSize.cy        = 0;
    m_LastClientSize.cx = 0;
    m_LastClientSize.cy = 0;
    m_pCurrentDlg       = NULL;
    m_pController       = NULL;
    m_hWndFocusOld      = NULL;
}

CViewSplitter::~CViewSplitter()
{
    ReleaseAll();
}

VOID CViewSplitter::ReleaseAll()
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
}

INT CViewSplitter::Run(HINSTANCE hInstance)
{
    DWORD dwStyle, dwClsStyle;
    static TCHAR Title[] = _T("Binary Splitter - built on ")_T(__DATE__)_T(" ")_T(__TIME__);

    dwStyle    = (WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN) & ~(WS_MAXIMIZEBOX|WS_SIZEBOX);
    dwClsStyle = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    if (!CreateEx(
            Title,
            Title,
            NULL,
            hInstance,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            dwClsStyle,
            dwStyle))
    {
        return 1;
    }

    CenterWindow();
    Show();

    return Execute();
}

CControllerSplitter* CViewSplitter::SetController(CControllerSplitter *pController)
{
    RemoveController();
    m_pController = pController;
    return pController;
}

CControllerSplitter* CViewSplitter::RemoveController()
{
    CControllerSplitter *pController = m_pController;
    if (pController != NULL)
        m_pController = NULL;
    return pController;
}

INT CViewSplitter::ShowAskMessageV(LPCTSTR pszFormat, va_list args)
{
    TCHAR szBuffer[1024];

    FormatStringvn(szBuffer, countof(szBuffer), pszFormat, args);

    return MessageBox(szBuffer, NULL, MB_OKCANCEL|MB_ICONASTERISK);
}

INT CViewSplitter::ShowErrorMessageV(LPCTSTR pszFormat, va_list args)
{
    TCHAR szBuffer[1024];
    FormatStringvn(szBuffer, countof(szBuffer), pszFormat, args);
    return MessageBox(szBuffer);
}

INT CViewSplitter::ShowErrorMessageTimeoutV(DWORD MilliSeconds, LPCTSTR pszFormat, va_list args)
{
    TCHAR szBuffer[1024];
    FormatStringvn(szBuffer, countof(szBuffer), pszFormat, args);
    return MessageBoxTimeout(szBuffer, MilliSeconds);
}

INT CViewSplitter::ShowAskMessage(LPCTSTR pszFormat, ...)
{
    va_list args;
    va_start(args, pszFormat);
    return ShowAskMessageV(pszFormat, args);
}

INT CViewSplitter::ShowErrorMessage(LPCTSTR pszFormat, ...)
{
    va_list args;
    va_start(args, pszFormat);
    return ShowErrorMessageV(pszFormat, args);
}

INT CViewSplitter::ShowErrorMessageTimeout(DWORD MilliSeconds, LPCTSTR pszFormat, ...)
{
    va_list args;
    va_start(args, pszFormat);
    return ShowErrorMessageTimeoutV(MilliSeconds, pszFormat, args);
}

BOOL CViewSplitter::SetProgress(INT Percent)
{
    if (m_pCurrentDlg == NULL)
        return TRUE;

    m_pCurrentDlg->SetProgress(Percent);
    return !m_bForceStopped;
}

BOOL CViewSplitter::SetOperationComplete(BOOL bComplete)
{
    return m_pCurrentDlg == NULL ? FALSE : m_pCurrentDlg->ChangeDialogState(bComplete);
}

BOOL CViewSplitter::IsSaveOriginalFileName()
{
    if (m_pCurrentDlg == &m_DlgSplit)
        return m_DlgSplit.IsSaveOriginalFileName();
    else if (m_pCurrentDlg == &m_DlgMerge)
        return m_DlgMerge.IsRestoreOriginalFileName();

    return FALSE;
}

BOOL CViewSplitter::IsRestoreOriginalFileName()
{
    return IsSaveOriginalFileName();
}

BOOL CViewSplitter::HasPassword(BOOL bHas)
{
    if (m_pCurrentDlg != &m_DlgMerge)
        return FALSE;

    return m_DlgMerge.HasPassword(bHas);
}

BOOL CViewSplitter::HasOriginalFileName(BOOL bHas)
{
    if (m_pCurrentDlg != &m_DlgMerge)
        return FALSE;
    
    return m_DlgMerge.HasOriginalFileName(bHas);
}

BOOL CViewSplitter::IsOutputCompress()
{
    if (m_pCurrentDlg == &m_DlgSplit)
        return m_DlgSplit.IsOutputCompress();

    return FALSE;
}

BOOL CViewSplitter::IsOutputEncrypt()
{
    if (m_pCurrentDlg == &m_DlgSplit)
        return m_DlgSplit.IsOutputEncrypt();

    return FALSE;
}

INT CViewSplitter::GetInputFileName(LPTSTR pBuffer, DWORD BufferCount)
{
    return m_pCurrentDlg->GetInputFile(pBuffer, BufferCount);
}

INT CViewSplitter::GetOutputFileName(LPTSTR pBuffer, DWORD BufferCount)
{
    return m_pCurrentDlg->GetOutputFile(pBuffer, BufferCount);
}

INT CViewSplitter::GetPassword(LPTSTR pBuffer, DWORD BufferCount)
{
    return m_pCurrentDlg->GetPassword(pBuffer, BufferCount);
}

INT64 CViewSplitter::GetSliceSize()
{
    if (m_pCurrentDlg == &m_DlgSplit)
        return m_DlgSplit.GetSliceSize();

    return 0;
}

BOOL CViewSplitter::PreTranslateMessage(LPMSG lpMsg)
{
    if (TranslateAccelerator(*this, m_hAccel, lpMsg))
        return TRUE;

    if (m_pCurrentDlg && m_pCurrentDlg->IsDialogMessage(lpMsg))
        return TRUE;

    if (IsDialogMessage(lpMsg))
        return TRUE;

    return FALSE;
}

VOID CViewSplitter::SlideMoveWindow()
{
    LONG X, Unit;
    HWND hWndPrev, hWndCurr;
    CRectangle rcPrev, rcCurr;

    if (m_pCurrentDlg == m_pDlgToDisplay)
        return;

    hWndPrev = *m_pCurrentDlg;
    hWndCurr = *m_pDlgToDisplay;

    m_pCurrentDlg->GetWindowRect(rcPrev);
    ScreenToClient(rcPrev);

    rcCurr = rcPrev;

    X = rcCurr.Width();
    Unit = X / 50;

    if (GetRandom32() & 1)
    {
        X = -X;
        Unit = -Unit;
    }

    rcCurr.left  += X;
    rcCurr.right += X;

    ::SetWindowPos(hWndCurr, 0, rcCurr.left, rcCurr.top, rcCurr.Width(), rcCurr.Heigth(), 0);
    m_pDlgToDisplay->Show();

    do
    {
        rcPrev.left -= Unit;
        rcCurr.left -= Unit;
        ::SetWindowPos(hWndPrev, NULL, rcPrev.left, rcPrev.top, 0, 0, SWP_NOSIZE);
        ::SetWindowPos(hWndCurr, NULL, rcCurr.left, rcCurr.top, 0, 0, SWP_NOSIZE);
        SleepEx(1, FALSE);
        Unit = Unit < 0 ? max(Unit, rcCurr.left) : min(Unit, rcCurr.left);
    } while (rcCurr.left != 0);

    m_pCurrentDlg->Hide();
    m_pCurrentDlg = m_pDlgToDisplay;

    m_pCurrentDlg->Invalidate();
}

DWORD WINAPI CViewSplitter::SlideMoveWindowThread(LPVOID lpParam)
{
    CViewSplitter *This = (CViewSplitter *)lpParam;
    This->SlideMoveWindow();
    return 0;
}

VOID CViewSplitter::ChangeDialog(CDlgBase *pDlgToDisplay)
{
    if (m_pCurrentDlg == pDlgToDisplay)
        return;

#if 1
    m_pDlgToDisplay = pDlgToDisplay;
    QueueUserWorkItem(SlideMoveWindowThread, this, 0);
#else
    m_pCurrentDlg->Hide();

    m_pCurrentDlg = pDlgToDisplay;
    m_pCurrentDlg->Show();
    m_pCurrentDlg->SetFocus();
#endif
}

VOID CViewSplitter::OnCommand(HWND hWnd, INT ID, HWND hWndCtl, UINT codeNotify)
{
    UNUSED_VARIABLE(hWnd);
    UNUSED_VARIABLE(hWndCtl);
    UNUSED_VARIABLE(codeNotify);

    switch (ID)
    {
        case IDCANCEL:
            CloseForm();
            break;

        case BS_ID_TB_SPLIT:
            ChangeDialog(&m_DlgSplit);
            break;

        case BS_ID_TB_MERGE:
            ChangeDialog(&m_DlgMerge);
            break;

        case BS_ID_TB_ABOUT:
            ChangeDialog(&m_DlgAbout);
            break;
    }
}

LRESULT CViewSplitter::OnAppSplit(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    UNUSED_VARIABLE(hWnd);
    UNUSED_VARIABLE(Msg);
    UNUSED_VARIABLE(wParam);
    UNUSED_VARIABLE(lParam);

    m_bForceStopped = !m_pController->Split();

    return NO_ERROR;
}

LRESULT CViewSplitter::OnAppMerge(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    UNUSED_VARIABLE(hWnd);
    UNUSED_VARIABLE(Msg);
    UNUSED_VARIABLE(wParam);
    UNUSED_VARIABLE(lParam);

    m_bForceStopped = !m_pController->Merge();

    return m_bForceStopped ? ~NO_ERROR : NO_ERROR;
}

LRESULT CViewSplitter::OnAppOpen(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    UNUSED_VARIABLE(hWnd);
    UNUSED_VARIABLE(Msg);
    UNUSED_VARIABLE(wParam);
    UNUSED_VARIABLE(lParam);
    return m_pController->Open() ? NO_ERROR : ~NO_ERROR;
}

LRESULT CViewSplitter::OnAppForceStop(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    UNUSED_VARIABLE(hWnd);
    UNUSED_VARIABLE(Msg);
    UNUSED_VARIABLE(wParam);
    UNUSED_VARIABLE(lParam);

    m_bForceStopped = TRUE;

//    m_pCurrentDlg->ChangeDialogState(TRUE);
    return NO_ERROR;
}

BOOL CViewSplitter::OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
    HDC hDC;
    BOOL bRet;
    CRectangle rcWindow, rcToolbar;
    ACCEL accel[] = { { FVIRTKEY, VK_ESCAPE, IDCANCEL } };

    UNUSED_VARIABLE(hWnd);
    UNUSED_VARIABLE(lpCreateStruct);

    SetExecuteDirectoryAsCurrent();

    ReleaseAll();

    m_hFont = CreateIconTitleFont();
    SafeSetWindowFont(*this, m_hFont, TRUE);

    hDC = GetDC();
    SelectObject(hDC, m_hFont);
    bRet = InitControls(hDC);

    ReleaseDC(hDC);

    if (!bRet)
        return FALSE;

    m_hAccel = CreateAcceleratorTable(accel, countof(accel));

    ::GetWindowRect(GetDlgItem(BS_ID_TOOLBAR), rcToolbar);
    m_pCurrentDlg->GetWindowRect(rcWindow);

    AdjustWindowRect(rcWindow, GetStyle(), FALSE);

    rcWindow.bottom += rcToolbar.Heigth();

    SetWindowPos(0, rcWindow, 0);
    ::SetWindowPos(GetDlgItem(BS_ID_TOOLBAR), NULL, 0, 0, rcWindow.Width(), 0, SWP_NOMOVE);

    GetWindowRect(rcWindow);

    m_MinSize.cx = rcWindow.Width();
    m_MinSize.cy = rcWindow.Heigth();

    return TRUE;
}

BOOL CViewSplitter::InitControls(HDC hDC)
{
    HWND       hWnd;
    RECT       rcToolBar;
    TBBUTTON   tbButton[3];
    HIMAGELIST hImageList;

    UNUSED_VARIABLE(hDC);

    InitCommonControls();
    hWnd = CreateWindowEx(
               0,
               TOOLBARCLASSNAME,
               NULL,
               WS_CHILD|CCS_ADJUSTABLE|TBSTYLE_FLAT,
               0, 0, 0, 0,
               *this,
               (HMENU)BS_ID_TOOLBAR,
               m_hInstance,
               NULL);
    if (hWnd == NULL)
        return FALSE;

    SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG_PTR)(HBRUSH)(COLOR_BTNFACE + 1));

    ::SendMessage(hWnd, TB_BUTTONSTRUCTSIZE, sizeof(tbButton), 0);

    TCHAR *szTBText[] =
    {
        _T("Split"),
        _T("Merge"),
        _T("Options"),
    };

    hImageList = ImageList_Create(32, 32, ILC_COLOR32, 3, 4);
    if (hImageList == NULL)
        return FALSE;

    for (UINT i = 0; i != countof(tbButton); ++i)
    {
        HBITMAP hBitmap;
        tbButton[i].iBitmap = i;
        tbButton[i].idCommand = BS_ID_TB_SPLIT + i;
        tbButton[i].fsState = TBSTATE_ENABLED;
        tbButton[i].fsStyle = BTNS_BUTTON;
        tbButton[i].dwData = 0;
        tbButton[i].iString = (INT_PTR)szTBText[i] * 0;
        ::SendMessage(hWnd, TB_ADDBUTTONS, 1, (LPARAM)&tbButton[i]);
        hBitmap = LoadBitmap(m_hInstance, MAKEINTRES(IDB_SPLIT + i));
        ImageList_Add(hImageList, hBitmap, 0);
        DeleteObject(hBitmap);
    }

//    ::SendMessage(hWnd, TB_ADDBUTTONS, countof(tbButton), (LPARAM)tbButton);

    ::SendMessage(hWnd, TB_SETIMAGELIST , 0, (LPARAM)hImageList);
    ::SendMessage(hWnd, TB_AUTOSIZE, 0, 0);
    ::ShowWindow(hWnd, SW_SHOW);

    ::GetWindowRect(hWnd, &rcToolBar);
    ScreenToClient(&rcToolBar);
    if (!m_DlgSplit.CreateEx(*this, m_hInstance, (LPARAM)m_hFont) ||
        !m_DlgMerge.CreateEx(*this, m_hInstance, (LPARAM)m_hFont) ||
        !m_DlgAbout.CreateEx(*this, m_hInstance, (LPARAM)m_hFont))
        return NULL;

    m_DlgSplit.SetWindowPos(NULL, rcToolBar.left, rcToolBar.bottom, 0, 0, SWP_NOSIZE);
    m_DlgMerge.SetWindowPos(NULL, rcToolBar.left, rcToolBar.bottom, 0, 0, SWP_NOSIZE);
    m_DlgAbout.SetWindowPos(NULL, rcToolBar.left, rcToolBar.bottom, 0, 0, SWP_NOSIZE);

    SendMessageToDescendants(WM_SETFONT, (WPARAM)m_hFont, 0);

    m_pCurrentDlg = &m_DlgMerge;
    m_pCurrentDlg = &m_DlgSplit;
    m_pCurrentDlg->Show();
    m_pCurrentDlg->SetFocus();

    return TRUE;
}

VOID CViewSplitter::OnActivate(HWND hWnd, UINT State, HWND hWndActDeact, BOOL fMinimized)
{
    UNUSED_VARIABLE(hWnd);
    UNUSED_VARIABLE(hWndActDeact);
    UNUSED_VARIABLE(fMinimized);

    if (State == WA_INACTIVE)
    {
        m_hWndFocusOld = GetFocus();
        return;
    }

//    TChar buf[20];
//    FormatString(buf, _T("%08X"), GetTickCount());
//    SetWindowText(buf);
    if (fMinimized)
        return;

    if (m_hWndFocusOld != NULL)
        ::SetFocus(m_hWndFocusOld);
}

VOID CViewSplitter::OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
    UNUSED_VARIABLE(hWnd);
    lpMinMaxInfo->ptMinTrackSize = *(LPPOINT)&m_MinSize;
}

VOID CViewSplitter::OnSize(HWND hWnd, UINT state, INT cx, INT cy)
{
    UNUSED_VARIABLE(hWnd);
    if (m_LastClientSize.cx == 0 || state == SIZE_MINIMIZED)
        return;

    INT deltaX, deltaY;

    deltaX = cx - m_LastClientSize.cx;
    deltaY = cy - m_LastClientSize.cy;
    if (deltaY == 0 && deltaX == 0)
        return;
}

VOID CViewSplitter::OnDropFiles(HWND hWnd, HDROP hDrop)
{
    UNUSED_VARIABLE(hWnd);
    DragFinish(hDrop);
}

VOID CViewSplitter::OnLButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags)
{
    UNUSED_VARIABLE(x);
    UNUSED_VARIABLE(y);
    UNUSED_VARIABLE(keyFlags);
    FORWARD_WM_NCLBUTTONDOWN(hWnd, fDoubleClick, 0, 0, HTCAPTION, ::SendMessage);
}

VOID CViewSplitter::OnLButtonUp(HWND hWnd, INT x, INT y, UINT keyFlags)
{
    UNUSED_VARIABLE(x);
    UNUSED_VARIABLE(y);
    UNUSED_VARIABLE(keyFlags);
    FORWARD_WM_NCLBUTTONUP(hWnd, 0, 0, HTCAPTION, ::SendMessage);
}

VOID CViewSplitter::OnDestroy(HWND hWnd)
{
    UNUSED_VARIABLE(hWnd);
    ReleaseAll();
    PostQuitMessage(0);
}
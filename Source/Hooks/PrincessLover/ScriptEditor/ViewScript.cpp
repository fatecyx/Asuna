#include "ViewScript.h"
#include "OpenFileDialog.h"

CViewScriptEditor::CViewScriptEditor()
{
    m_hFont       = NULL;
    m_LastSize.cx = 0;
    m_LastSize.cy = 0;
    m_pController = NULL;
}

CViewScriptEditor::~CViewScriptEditor()
{
    if (m_hFont != NULL)
    {
        DeleteObject(m_hFont);
        m_hFont = NULL;
    }
}

Int CViewScriptEditor::Run()
{
    return DoModal(IDD_DIALOG_SCRIPTEDITOR, NULL);
}

Int CViewScriptEditor::ShowErrorMessage(PCTChar pszFormat, va_list ArgList)
{
    Int Length;
    TChar szBuffer[0x1000];

    Length = wvsprintf(szBuffer, pszFormat, ArgList);
    MessageBox(szBuffer);

    return Length;
}

Int CViewScriptEditor::ShowErrorMessage(PCTChar pszFormat, ...)
{
    va_list ArgList;

    va_start(ArgList, pszFormat);

    return ShowErrorMessage(pszFormat, ArgList);
}

CControllerScript* CViewScriptEditor::SetController(CControllerScript *pController)
{
    RemoveController();
    m_pController = pController;
    return pController;
}

CControllerScript* CViewScriptEditor::RemoveController()
{
    CControllerScript *pController = m_pController;
    if (pController != NULL)
        m_pController = NULL;
    return pController;
}

SizeT CViewScriptEditor::AddTextWorker(MyWindowClass::CListBox &ListBox, SizeT Index, PCWChar pszText)
{
    return ListBox.InsertString(Index, pszText);
}

SizeT CViewScriptEditor::AppendTextListOriginal(PCWChar pszText)
{
    return AddTextWorker(m_ListOriginal, -1, pszText);
}

SizeT CViewScriptEditor::InsertTextListOriginal(SizeT Index, PCWChar pszText)
{
    return AddTextWorker(m_ListOriginal, Index, pszText);
}

SizeT CViewScriptEditor::AppendTextListTranslation(PCWChar pszText)
{
    return AddTextWorker(m_ListTranslation, -1, pszText);
}

SizeT CViewScriptEditor::InsertTextListTranslation(SizeT Index, PCWChar pszText)
{
    return AddTextWorker(m_ListTranslation, Index, pszText);
}

SizeT CViewScriptEditor::UpdateTextWorker(MyWindowClass::CListBox &ListBox, SizeT Index, PCWChar pszText)
{
    if (Index > ListBox.GetCount())
        return 0;

    SizeT CurIndex = ListBox.GetCurrentSelection();

    ListBox.DeleteString(Index);
    Index = AddTextWorker(ListBox, Index, pszText);
    ListBox.SetCurrentSelection(CurIndex);

    return Index;
}

SizeT CViewScriptEditor::UpdateTextListOriginal(SizeT Index, PCWChar pszText)
{
    return UpdateTextWorker(m_ListOriginal, Index, pszText);
}

SizeT CViewScriptEditor::UpdateTextListTranslation(SizeT Index, PCWChar pszText)
{
    return UpdateTextWorker(m_ListTranslation, Index, pszText);
}

Void CViewScriptEditor::EmptyListBoxWorker(MyWindowClass::CListBox &ListBox)
{
    ListBox.ResetContent();
}

Void CViewScriptEditor::ClearTextListOriginal()
{
    EmptyListBoxWorker(m_ListOriginal);
}

Void CViewScriptEditor::ClearTextListTranslation()
{
    EmptyListBoxWorker(m_ListTranslation);
}

SizeT CViewScriptEditor::SetTextListSelection(SizeT Index)
{
    SizeT CurIndex = m_ListOriginal.GetCurrentSelection();

    if (Index == CurIndex || Index > m_ListOriginal.GetCount())
        return CurIndex;

    m_ListOriginal.SetCurrentSelection(Index);
    m_ListTranslation.SetCurrentSelection(Index);
//    SyncListBoxScrollBar(IDC_LIST_ORIGINAL);
    SelectText();

    return CurIndex;
}

Void CViewScriptEditor::OnAppendTextFinish(SizeT MaxLengthOrig, SizeT MaxLengthTrans)
{
    SizeT AvgCharWidth = m_TextMetric.tmAveCharWidth + 5;

    m_ListOriginal.SetHorizontalExtent(MaxLengthOrig * AvgCharWidth);
    m_ListTranslation.SetHorizontalExtent(MaxLengthTrans * AvgCharWidth);
}

SizeT CViewScriptEditor::GetTextTranslation(PWChar pszBuffer, SizeT BufferCount)
{
    return m_EditTranslation.GetText(pszBuffer, BufferCount);
}

SizeT CViewScriptEditor::GetTextTranslationLength()
{
    return m_EditTranslation.GetTextLength();
}

SizeT CViewScriptEditor::GetTextListCurrentSelection()
{
    return m_ListOriginal.GetCurrentSelection();
}

Void
CViewScriptEditor::
SetCurrentText(
    PCWChar pszOriginalName,
    PCWChar pszOriginalText,
    PCWChar pszTransName,
    PCWChar pszTransText,
    SizeT   TransTextBegin /* =  0 */,
    SizeT   TransTextEnd   /* = -1 */
)
{
    if (pszOriginalName != NULL)
    {
        m_EditOriginalName.SetText(pszOriginalName);
    }

    if (pszOriginalText != NULL)
    {
        m_EditOriginal.SetText(pszOriginalText);
    }

    if (pszTransName != NULL)
    {
        m_EditTranslationName.SetText(pszTransName);
    }

    if (pszTransText != NULL)
    {
        m_EditTranslation.SetText(pszTransText);
        m_EditTranslation.SetSelection(TransTextBegin, TransTextEnd);
    }

    m_EditTranslation.SetFocus();
}

Void CViewScriptEditor::SyncListBoxScrollBar(Int ID)
{
    SCROLLINFO ScrollInfoV, ScrollInfoH;

    ScrollInfoV.fMask = SIF_ALL;
    ScrollInfoH.fMask = SIF_ALL;
    if (ID == IDC_LIST_ORIGINAL)
    {
        m_ListTranslation.SetCurrentSelection(m_ListOriginal.GetCurrentSelection());
        return;
        m_ListOriginal.GetScrollInfo(SB_VERT, &ScrollInfoV);
        m_ListOriginal.GetScrollInfo(SB_HORZ, &ScrollInfoH);
        m_ListTranslation.SetScrollInfo(SB_VERT, &ScrollInfoV);
        m_ListTranslation.SetScrollInfo(SB_HORZ, &ScrollInfoH);
        m_ListTranslation.ScrollWindow(0, 0);
    }
    else
    {
        m_ListOriginal.SetCurrentSelection(m_ListTranslation.GetCurrentSelection());
        return;
        m_ListTranslation.GetScrollInfo(SB_VERT, &ScrollInfoV);
        m_ListTranslation.GetScrollInfo(SB_HORZ, &ScrollInfoH);
        m_ListOriginal.SetScrollInfo(SB_VERT, &ScrollInfoV);
        m_ListOriginal.SetScrollInfo(SB_HORZ, &ScrollInfoH);
    }
}

Void CViewScriptEditor::SelectText()
{
    m_pController->SelectText(m_ListOriginal.GetCurrentSelection());
}

Bool CViewScriptEditor::OpenScript(PCTChar pszScriptPath)
{
    if (!m_pController->OpenScript(pszScriptPath))
        return False;

    SetWindowText(pszScriptPath);
    return True;
}

Void CViewScriptEditor::OnCommand(HWND hWnd, Int ID, HWND hWndCtrl, UInt codeNotify)
{
    switch (ID)
    {
        case IDC_BUTTON_OPEN:
        {
#if 0
            OpenScript(_T("E:/Desktop/Source/Hooks/PrincessLover/ScriptEditor/op01.s"));
#else
            MyWindowClass::COpenFileDialog OpenFileDlg(*this);

            if (!OpenFileDlg.GetOpenFileName())
                break;

            OpenScript(OpenFileDlg.GetFileName());
#endif
        }
        break;

        case IDC_BUTTON_SAVE:
            m_pController->SaveTranslation();
            break;

        case IDC_BUTTON_SUBMIT:
            m_pController->SubmitAllTranslation();
            break;

        case IDC_LIST_ORIGINAL:
        case IDC_LIST_TRANSLATION:
            if (codeNotify == LBN_SELCHANGE)
            {
                SyncListBoxScrollBar(ID);
            }
            else if (codeNotify == LBN_DBLCLK)
            {
                SelectText();
            }
            break;

        case IDOK:
            hWnd = GetFocus();
            if (hWnd == m_EditTranslation || hWnd == m_EditOriginal)
            {
                Int MoveStep;

                if (GetKeyState(VK_CONTROL) < 0)
                    MoveStep = 0;
                else
                    MoveStep = GetKeyState(VK_SHIFT) < 0 ? -1 : 1;

                m_pController->SaveOneSentence(
                    m_ListOriginal.GetCurrentSelection(),
                    MoveStep);
            }
            else if (hWnd == m_ListOriginal || hWnd == m_ListTranslation)
            {
                SelectText();
            }
            break;

        case IDCANCEL:
            EndDialog(ID == IDOK);
                break;
    }
}

Void CViewScriptEditor::OnMouseWheel(HWND hWnd, Int xPos, Int yPos, Int zDelta, UInt fwKeys)
{
    POINT pt = { xPos, yPos };

    hWnd = WindowFromPoint(pt);
    if (hWnd != *this)
    {
        MapWindowPoints(hWnd, &pt, 1);
        FORWARD_WM_MOUSEWHEEL(hWnd, pt.x, pt.y, zDelta, fwKeys, ::SendMessage);
    }
}

Void CViewScriptEditor::OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
    lpMinMaxInfo->ptMinTrackSize = m_ptMinTrackSize;
}

Void CViewScriptEditor::OnSize(HWND hWnd, UInt state, Int cx, Int cy)
{
    Int  deltaX, deltaY;

    if (m_LastSize.cx == 0 || state == SIZE_MINIMIZED)
        return;

    deltaX = cx - m_LastSize.cx;
    deltaY = cy - m_LastSize.cy;

    if (deltaY == 0 && deltaX == 0)
        return;

    m_LastSize.cx = cx;
    m_LastSize.cy = cy;

    AdjustControlsPos(cx, cy, deltaX, deltaY);
}

Void CViewScriptEditor::OnLButtonUp(HWND hWnd, Int x, Int y, UInt keyFlags)
{
    SendMessage(WM_NCLBUTTONUP, HTCAPTION);
}

Void CViewScriptEditor::OnLButtonDown(HWND hWnd, Bool fDoubleClick, Int x, Int y, UInt keyFlags)
{
    SendMessage(WM_NCLBUTTONDOWN, HTCAPTION);
}

Bool CViewScriptEditor::OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
    HDC   hDC;
    HFONT hFont;
    RECT  rcWindow;
    TChar szConfig[MAX_PATH];

    SetIcon(LoadIcon(NULL, IDI_APPLICATION), True);

    hDC = GetDC();

    m_hFont = CreateIconTitleFont();
    hFont = (HFONT)SelectObject(hDC, m_hFont);
    GetTextMetrics(hDC, &m_TextMetric);
    SelectObject(hDC, hFont);

    ReleaseDC(hDC);

    m_ListOriginal.Attach(GetDlgItem(IDC_LIST_ORIGINAL));
    m_ListTranslation.Attach(GetDlgItem(IDC_LIST_TRANSLATION));

    m_EditOriginal.Attach(GetDlgItem(IDC_EDIT_ORIGINAL));
    m_EditTranslation.Attach(GetDlgItem(IDC_EDIT_TRANSLATION));
    m_EditOriginalName.Attach(GetDlgItem(IDC_EDIT_ORIGINAL_NAME));
    m_EditTranslationName.Attach(GetDlgItem(IDC_EDIT_TRANSLATION_NAME));

    m_ListOriginal.SetFont(m_hFont);
    m_ListTranslation.SetFont(m_hFont);

    m_EditOriginal.SetFont(m_hFont);
    m_EditTranslation.SetFont(m_hFont);
    m_EditOriginalName.SetFont(m_hFont);
    m_EditTranslationName.SetFont(m_hFont);

    m_EditOriginal.SetLimitText(0x1000);
    m_EditOriginalName.SetLimitText(0x1000);
    m_EditTranslation.SetLimitText(0x1000);
    m_EditTranslationName.SetLimitText(0x1000);

    GetWindowRect(&rcWindow);
    m_ptMinTrackSize.x = rcWindow.right - rcWindow.left;
    m_ptMinTrackSize.y = rcWindow.bottom - rcWindow.top;

    GetClientRect(&rcWindow);
    m_LastSize.cx = rcWindow.right - rcWindow.left;
    m_LastSize.cy = rcWindow.bottom - rcWindow.top;

    if (GetConfigPath(szConfig, countof(szConfig)))
    {
        Long w, h;
        m_ptMinTrackSize.x = GetPrivateProfileInt(CONFIG_SECTION, CONFIG_MIN_WIDTH,  m_ptMinTrackSize.x, szConfig);
        m_ptMinTrackSize.y = GetPrivateProfileInt(CONFIG_SECTION, CONFIG_MIN_HEIGHT, m_ptMinTrackSize.y, szConfig);
        w = GetPrivateProfileInt(CONFIG_SECTION, CONFIG_WIDTH,  m_ptMinTrackSize.x, szConfig);
        h = GetPrivateProfileInt(CONFIG_SECTION, CONFIG_HEIGHT, m_ptMinTrackSize.y, szConfig);
        if (w != m_ptMinTrackSize.x || h != m_ptMinTrackSize.y)
        {
            SetWindowPos(NULL, 0, 0, w, h, SWP_NOMOVE);
            CenterWindow();
        }
    }

    AdjustControlsPos(m_LastSize.cx, m_LastSize.cy, 0, 0);

    DragAcceptFiles();
    SetWindowText(_T("Script Editor"));

    SetExecuteDirectoryAsCurrent();

    Int   argc;
    TChar **argv;

    argv = CmdLineToArgv(GetCommandLine(), &argc);
    if (argc > 1)
        OpenScript(argv[1]);

    HeapFree(GetProcessHeap(), 0, argv);

    return True;
}

Void CViewScriptEditor::OnDestroy(HWND hWnd)
{
    SizeT Length;
    RECT  rcWindow;
    TChar szConfig[MAX_PATH];
    TChar szBuffer[0x100];
    CFileDisk file;

    if (!GetConfigPath(szConfig, countof(szConfig)))
        return;

    if (!file.Open(szConfig, file.FILE_ACCESS_WRITE, file.FILE_SHAREMODE_READ, file.FILE_CREATE_ALWAYS))
        return;

#if defined(UNICODE) || defined(_UNICODE)
    Length = BOM_UTF16_LE;
    if (!file.Write(&Length, 2))
        return;
#endif

    GetWindowRect(&rcWindow);
    Length = wsprintf(
                 szBuffer,
                 _T("[") CONFIG_SECTION _T("]\r\n")
                 CONFIG_WIDTH  _T("=%d\r\n")
                 CONFIG_HEIGHT _T("=%d\r\n")
                 CONFIG_MIN_WIDTH  _T("=%d\r\n")
                 CONFIG_MIN_HEIGHT _T("=%d"),
                 rcWindow.right - rcWindow.left,
                 rcWindow.bottom - rcWindow.top,
                 m_ptMinTrackSize.x,
                 m_ptMinTrackSize.y);

#if defined(UNICODE) || defined(_UNICODE)
    Length *= sizeof(*szBuffer);
#endif

    file.Write(szBuffer, Length);
}

Void CViewScriptEditor::OnDropFiles(HWND hWnd, HDROP hDrop)
{
    POINT ptDrop;
    TChar szPath[MAX_PATH];

    DragQueryPoint(hDrop, &ptDrop);
    ClientToScreen(&ptDrop);
    hWnd = WindowFromPoint(ptDrop);
    if (hWnd != m_ListOriginal && hWnd != m_ListTranslation)
        return;

    if (DragQueryFile(hDrop, 0, szPath, countof(szPath)) == 0)
        return;

    OpenScript(szPath);
}

Void CViewScriptEditor::AdjustControlsPos(Int cx, Int cy, Int deltaX, Int deltaY)
{
    Int  x, y, w, h;
    Int  EditHeight, EditWidth, ButtonHeight;
    UInt Flags;
    HWND hWndMerge, hWndOpen, hWndSave;

    x = 10;
    y = 10;
    w = (cx - 5 * 2) / 2 - 10;

    EditWidth    = cx - x * 2;
    EditHeight   = m_TextMetric.tmHeight + 5;
    ButtonHeight = m_TextMetric.tmHeight + 10;

    //  height - edit * 4 - btn * 1 - top_5px - list_edit_5px edit_btn_10px - btm_10px
    h = cy - (EditHeight) * 4 - (ButtonHeight) - 5 * 3 - 10 * 2;

    Flags = SWP_NOZORDER;
    m_ListOriginal.SetWindowPos(NULL, x, y, w, h, Flags);
    m_ListTranslation.SetWindowPos(NULL, cx - w - x, y, w, h, Flags);

    y += h + 5;
    w = EditWidth;
    h = EditHeight;
    m_EditOriginalName.SetWindowPos(NULL, x, y, w, h, Flags);
    y += h;
    m_EditOriginal.SetWindowPos(NULL, x, y, w, h, Flags);
    y += h;
    m_EditTranslationName.SetWindowPos(NULL, x, y, w, h, Flags);
    y += h;
    m_EditTranslation.SetWindowPos(NULL, x, y, w, h, Flags);

    hWndMerge = GetDlgItem(IDC_BUTTON_SUBMIT);
    hWndOpen  = GetDlgItem(IDC_BUTTON_OPEN);
    hWndSave  = GetDlgItem(IDC_BUTTON_SAVE);

    y += h + 10;
    w = EditWidth / 2 / 3 - 5;
    h = ButtonHeight;

    x += w + 5;
    x += w + 5;
    ::SetWindowPos(hWndMerge, NULL, x, y, w, h, Flags);
    x -= w + 5;
    ::SetWindowPos(hWndSave,  NULL, x, y, w, h, Flags);
    x -= w + 5;
    ::SetWindowPos(hWndOpen,  NULL, x, y, w, h, Flags);

    Invalidate();
}

Bool CViewScriptEditor::GetConfigPath(PTChar pszConfig, SizeT BufferCount)
{
    if (GetModuleFileName(NULL, pszConfig, BufferCount) == 0)
        return False;

    lstrcpy(findext(pszConfig), _T(".ini"));
    return True;
}
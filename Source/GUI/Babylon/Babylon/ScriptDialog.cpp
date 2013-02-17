#include "ScriptDialog.h"
#include "Mem.h"
#include "FileDisk.h"

CScriptDialog::CScriptDialog() : CDialogImpl2(IDD_DLG_SELECT_SCRIPT)
{
    m_LastSize.cx = 0;
    m_LastSize.cy = 0;
    m_pConfig     = NULL;
    m_pGameList   = NULL;
    m_pGameInfoSelected = NULL;
}

Bool
CScriptDialog::
SetGameListInfo(
    SBLScriptConfig   *pConfig,
    SBLScriptGameList *pGameList,
    ULong              GameTypeCount
)
{
    m_pConfig   = pConfig;
    m_pGameList = pGameList;
    m_GameTypeCount = GameTypeCount;

    return True;
}

SBLScriptGameInfo* CScriptDialog::GetGameInfoSelected()
{
    return m_pGameInfoSelected;
}

Void CScriptDialog::OnCommand(HWND hWnd, Int id, HWND hWndCtrl, UInt codeNotify)
{
    switch (id)
    {
        case IDC_SCRIPTDLG_COMBOBOX:
            if (codeNotify == CBN_SELCHANGE)
            {
                Int Index;
                SBLScriptGameList *pGameList;
                SBLScriptGameListGroup *pGroup;

                ListBox_ResetContent(m_hWndCompany);
                ListBox_ResetContent(m_hWndGame);

                Index = ComboBox_GetCurSel(hWndCtrl);
                pGameList = (SBLScriptGameList *)ComboBox_GetItemData(hWndCtrl, Index);
                if (pGameList == NULL)
                    break;

                Index = 0;
                pGroup = pGameList->pGameGroup;
                for (ULong i = pGameList->GroupCount; i; --i)
                {
                    ListBox_InsertString(m_hWndCompany, Index, pGroup->pszGroupName);
                    ListBox_SetItemData(m_hWndCompany, Index, pGroup);
                    ++Index;
                    ++pGroup;
                }
            }

            break;

        case IDC_SCRIPTDLG_LIST_COMPANY_NAME:
            if (codeNotify == LBN_SELCHANGE)
            {
                Int Index;
                SBLScriptGameListGroup *pGroup;
                SBLScriptGameInfo  *pGameInfo;

                ListBox_ResetContent(m_hWndGame);

                Index = ListBox_GetCurSel(hWndCtrl);
                pGroup = (SBLScriptGameListGroup *)ListBox_GetItemData(hWndCtrl, Index);
                if (pGroup == NULL)
                    break;

                pGameInfo = pGroup->pGameInfo;
                if (pGameInfo == NULL)
                    break;

                Index = 0;
                for (ULong i = pGroup->GameCount; i; --i)
                {
                    ListBox_InsertString(m_hWndGame, Index, pGameInfo->GameName);
                    ListBox_SetItemData(m_hWndGame, Index, pGameInfo);
                    ++pGameInfo;
                }

                ListBox_SetCurSel(m_hWndGame, 0);
            }

            break;

        case IDC_SCRIPTDLG_LIST_GAME_NAME:
            if (codeNotify != LBN_DBLCLK)
                break;

            id = IDOK;
            NO_BREAK;

        case IDOK:
        case IDCANCEL:
            if (id == IDOK)
            {
                m_pGameInfoSelected = (SBLScriptGameInfo *)ListBox_GetItemData(m_hWndGame, ListBox_GetCurSel(m_hWndGame));
            }
            EndDialog(id == IDOK);
            break;
    }
}

Void CScriptDialog::OnMouseWheel(HWND hWnd, Int xPos, Int yPos, Int zDelta, UInt fwKeys)
{
    POINT pt = { xPos, yPos };
    
    hWnd = WindowFromPoint(pt);
    if (hWnd != *this)
    {
        MapWindowPoints(hWnd, &pt, 1);
        FORWARD_WM_MOUSEWHEEL(hWnd, pt.x, pt.y, zDelta, fwKeys, ::SendMessage);
    }
}

Bool CScriptDialog::OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
    HDC   hDC;
    HFONT hFont;
    RECT  rcCtrl, rcButtonOK;
    Int   x, y, w, h;
    SIZE  StringSize;
    static TChar szStaticText[] = _T("ÓÎÏ·ÀàÐÍ");

    m_hWndCompany = GetDlgItem(IDC_SCRIPTDLG_LIST_COMPANY_NAME);
    m_hWndGame    = GetDlgItem(IDC_SCRIPTDLG_LIST_GAME_NAME);

    hFont = (HFONT)::SendMessage(m_hWndParent, WM_GETFONT, 0, 0);

    hDC = ::GetDC(m_hWndParent);

    ::GetWindowRect(GetDlgItem(IDOK), &rcButtonOK);
    ::GetWindowRect(GetDlgItem(IDC_SCRIPTDLG_LIST_COMPANY_NAME), &rcCtrl);
    ScreenToClient(&rcCtrl);
    ScreenToClient(&rcButtonOK);

    MeasureString(hDC, szStaticText, countof(szStaticText) - 1, &StringSize);

    x = rcCtrl.left;
    w = rcCtrl.right - (x + StringSize.cx + 5);
    h = StringSize.cy + 5;
    y = rcButtonOK.top;
    hWnd = CreateWindowEx(
               0,
               WC_COMBOBOX,
               NULL,
               WS_VISIBLE|WS_CHILD|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
               x + StringSize.cx + 5,
               y,
               w,
               h,
               *this,
               (HMENU)IDC_SCRIPTDLG_COMBOBOX,
               m_hInstance,
               NULL);

    m_hWndComboBox = hWnd;
    ::GetWindowRect(hWnd, &rcCtrl);
    ScreenToClient(&rcCtrl);
    SafeSetWindowFont(hWnd, hFont, True);

    SBLScriptGameTypeItem *pGameType = m_pConfig->pGameType;

    for (ULong i = m_pConfig->GameTypeCount; i; --i)
    {
        Int Index;

        Index = ComboBox_AddString(hWnd, pGameType->GameType);
        ComboBox_SetItemData(hWnd, Index, Index < (Int)m_GameTypeCount ? &m_pGameList[Index] : NULL);

        ++pGameType;
    }

    ComboBox_SetCurSel(hWnd, 0);
    OnCommand(*this, IDC_SCRIPTDLG_COMBOBOX, hWnd, CBN_SELCHANGE);

    y = rcCtrl.top + h / 2 - StringSize.cy / 2;
    w = StringSize.cx;
    h = StringSize.cy;
    hWnd = CreateWindowEx(
               0,
               WC_STATIC,
               szStaticText,
               WS_VISIBLE|WS_CHILD,
               x, y, w, h,
               *this,
               NULL,
               m_hInstance,
               NULL);

    SafeSetWindowFont(hWnd, hFont, True);
    SafeSetWindowFont(m_hWndCompany, hFont, True);
    SafeSetWindowFont(m_hWndGame, hFont, True);
    SafeSetWindowFont(GetDlgItem(IDOK), hFont, True);
    SafeSetWindowFont(GetDlgItem(IDCANCEL), hFont, True);

    ::SetFocus(GetDlgItem(IDC_SCRIPTDLG_LIST_COMPANY_NAME));

    ::ReleaseDC(m_hWndParent, hDC);

    GetWindowRect(&rcCtrl);
    m_ptMinTrackSize.x = rcCtrl.right - rcCtrl.left;
    m_ptMinTrackSize.y = rcCtrl.bottom - rcCtrl.top;

    GetClientRect(&rcCtrl);
    m_LastSize.cx = rcCtrl.right - rcCtrl.left;
    m_LastSize.cy = rcCtrl.bottom - rcCtrl.top;

    ::GetWindowRect(m_hWndParent, &rcCtrl);
    w = (rcCtrl.right - rcCtrl.left) * 100 / 111;
    h = (rcCtrl.bottom - rcCtrl.top) * 100 / 116;
    SetWindowPos(NULL, 0, 0, w, h, 0);

    CenterWindow(m_hWndParent);

    return True;
}

Void CScriptDialog::OnGetMinMaxInfo(HWND hWnd, LPMINMAXINFO lpMinMaxInfo)
{
    lpMinMaxInfo->ptMinTrackSize = m_ptMinTrackSize;
}

Void CScriptDialog::OnSize(HWND hWnd, UInt state, Int cx, Int cy)
{
    RECT rcCrtl;
    Int  w, h, deltaX, deltaY;
    HWND hWndCompany, hWndGame;

    if (m_LastSize.cx == 0 || state == SIZE_MINIMIZED)
        return;

    w = cx;
    h = cy;
    deltaX = w - m_LastSize.cx;
    deltaY = h - m_LastSize.cy;

    if (deltaY == 0 && deltaX == 0)
        return;

    m_LastSize.cx = w;
    m_LastSize.cy = h;

    hWndGame    = GetDlgItem(IDC_SCRIPTDLG_LIST_GAME_NAME);
    hWndCompany = GetDlgItem(IDC_SCRIPTDLG_LIST_COMPANY_NAME);

    if (deltaY != 0)
    {
        ::GetWindowRect(hWndCompany, &rcCrtl);
        DeltaWindowPos(hWndCompany, 0, deltaY, &rcCrtl, SWP_NOMOVE, DWP_HEIGHT_CHANGE);
    }

    ::GetWindowRect(hWndGame, &rcCrtl);
    DeltaWindowPos(hWndGame, deltaX, deltaY, &rcCrtl, SWP_NOMOVE, DWP_HEIGHT_CHANGE|DWP_WIDTH_CHANGE);

    if (deltaX != 0)
    {
        Int ButtonID[2];

        if (deltaX > 0)
        {
            ButtonID[0] = IDOK;
            ButtonID[1] = IDCANCEL;
        }
        else
        {
            ButtonID[0] = IDCANCEL;
            ButtonID[1] = IDOK;
        }

        for (Int i = countof(ButtonID); i--; )
        {
            hWnd = GetDlgItem(ButtonID[i]);
            ::GetWindowRect(hWnd, &rcCrtl);
            DeltaWindowPos(hWnd, deltaX, 0, &rcCrtl, SWP_NOSIZE, DWP_X_CHANGE);
        }
    }
}
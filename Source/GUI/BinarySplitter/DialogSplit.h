#ifndef _DIALOGSPLIT_H_
#define _DIALOGSPLIT_H_

#include "pragma_once.h"

#include "WindowBase.h"
#include "my_headers.h"
#include "EditBox.h"
#include "ProgressBar.h"
#include "OpenFileDialog.h"
#include "BinarySplitterMsg.h"
#include "resource.h"

EXTCPP class CControllerSplitter;
using namespace MyWindowClass;

class CDlgBase : public CDialogImpl2
{
public:
    CDlgBase(INT ID = 0) : CDialogImpl2(ID) {}

    virtual INT GetInputFile(LPTSTR lpBuffer, DWORD BufferCount)
    {
        if (lpBuffer != NULL && BufferCount > 0)
            lpBuffer[0] = 0;
        return 0;
    }

    virtual INT GetOutputFile(LPTSTR lpBuffer, DWORD BufferCount)
    {
        return CDlgBase::GetInputFile(lpBuffer, BufferCount);
    }

    virtual INT GetPassword(LPTSTR lpBuffer, DWORD BufferCount)
    {
        return CDlgBase::GetInputFile(lpBuffer, BufferCount);
    }

    virtual BOOL ChangeDialogState(BOOL bEnable)
    {
        UNUSED_VARIABLE(bEnable);
        return FALSE;
    }

    virtual BOOL SetProgress(INT Percent)
    {
        UNUSED_VARIABLE(Percent);
        return FALSE;
    }

protected:
    static BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
    {
        ::EnableWindow(hWnd, (BOOL)lParam);
        return TRUE;
    }

    BOOL EnableChildWindows(BOOL bEnable)
    {
        if (!EnumChildWindows(*this, EnumChildProc, bEnable))
            return FALSE;

        return TRUE;
    }
};

class CDlgAbout : public CDlgBase
{
public:
    CDlgAbout(INT ID = 0) : CDlgBase(ID)
    { }

protected:
    BEGIN_MSG_MAP(CDlgAbout)
        MSG_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
        MSG_HANDLER(WM_LBUTTONUP,   OnLButtonUp)
        MSG_HANDLER(WM_INITDIALOG,  OnInitDialog)
    END_MSG_MAP()

    VOID OnLButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UInt keyFlags)
    {
        UNUSED_VARIABLE(hWnd);
        UNUSED_VARIABLE(x);
        UNUSED_VARIABLE(y);
        UNUSED_VARIABLE(keyFlags);
        FORWARD_WM_NCLBUTTONDOWN(m_hWndParent, fDoubleClick, 0, 0, HTCAPTION, ::SendMessage);
    }

    VOID OnLButtonUp(HWND hWnd, INT x, INT y, UInt keyFlags)
    {
        UNUSED_VARIABLE(hWnd);
        UNUSED_VARIABLE(x);
        UNUSED_VARIABLE(y);
        UNUSED_VARIABLE(keyFlags);
        FORWARD_WM_NCLBUTTONUP(m_hWndParent, 0, 0, HTCAPTION, ::SendMessage);
    }

    BOOL OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
    {
        UNUSED_VARIABLE(hWnd);
        UNUSED_VARIABLE(hWndFocus);
        UNUSED_VARIABLE(lParam);

        InitControls((HFONT)lParam);

        return TRUE;
    }

    BOOL InitControls(HFONT hFont)
    {
        SendMessageToDescendants(WM_SETFONT, (WPARAM)hFont, 0);
        return TRUE;
    }
};

class CDlgMerge : public CDlgBase
{
protected:
    CEditBox        m_EditInput, m_EditOutput, m_EditPassword;
    CProgressBar    m_ProgressBar;
    HWND            m_hWndButton;
    enum
    {
        BTN_STATE_OPEN,
        BTN_STATE_MERGE,
        BTN_STATE_STOP,
    };

public:
    CDlgMerge(INT ID = 0) : CDlgBase(ID)
    { }

    INT GetInputFile(LPTSTR lpBuffer, DWORD BufferCount)
    {
        return m_EditInput.GetText(lpBuffer, BufferCount);
    }

    INT GetOutputFile(LPTSTR lpBuffer, DWORD BufferCount)
    {
        return m_EditOutput.GetText(lpBuffer, BufferCount);
    }

    INT GetPassword(LPTSTR lpBuffer, DWORD BufferCount)
    {
        if (lpBuffer && BufferCount > 0)
            lpBuffer[0] = 0;
        else
            return 0;

        return m_EditPassword.GetText(lpBuffer, BufferCount);
    }

    BOOL IsRestoreOriginalFileName()
    {
        return IsDlgButtonChecked(IDC_MERGE_CHECK_ORIGNAME);
    }

    BOOL HasPassword(BOOL bHas)
    {
        return m_EditPassword.EnableWindow(bHas);
    }

    BOOL HasOriginalFileName(BOOL bHas)
    {
        return ::EnableWindow(GetDlgItem(IDC_MERGE_CHECK_ORIGNAME), bHas);
    }

    BOOL ChangeDialogState(BOOL bEnable)
    {
        UINT IDSet, IDFind;

        if (bEnable)
        {
            IDSet  = IDC_MERGE_BUTTON_MERGE;
            IDFind = IDC_BUTTON_FORCE_STOP;
        }
        else
        {
            IDSet  = IDC_BUTTON_FORCE_STOP;
            IDFind = IDC_MERGE_BUTTON_OPEN;
        }

        EnableChildWindows(bEnable);

        SetButtonState(bEnable ? BTN_STATE_OPEN : BTN_STATE_STOP);

        return TRUE;
    }

    BOOL SetProgress(INT Percent)
    {
        m_ProgressBar.SetPosition(Percent);
        return TRUE;
    }

protected:
    VOID SetButtonState(ULONG State)
    {
        switch (State)
        {
            case BTN_STATE_OPEN:
                ::SetWindowLong(m_hWndButton, GWL_ID, IDC_MERGE_BUTTON_OPEN);
                ::Button_SetText(m_hWndButton, DLG_MERGE_STRING_BTN_OPEN);
                break;

            case BTN_STATE_MERGE:
                ::SetWindowLong(m_hWndButton, GWL_ID, IDC_MERGE_BUTTON_MERGE);
                ::Button_SetText(m_hWndButton, DLG_MERGE_STRING_BTN_MERGE);
                break;

            case BTN_STATE_STOP:
                ::SetWindowLong(m_hWndButton, GWL_ID, IDC_BUTTON_FORCE_STOP);
                ::Button_SetText(m_hWndButton, DLG_MERGE_STRING_BTN_STOP);
                break;
        }
    }

    BEGIN_MSG_MAP(CDlgMerge)
        MSG_HANDLER(WM_COMMAND,     OnCommand)
        MSG_HANDLER(WM_DROPFILES,   OnDropFiles)
        MSG_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
        MSG_HANDLER(WM_LBUTTONUP,   OnLButtonUp)
        MSG_HANDLER(WM_INITDIALOG,  OnInitDialog)
    END_MSG_MAP()

    VOID OnCommand(HWND hWnd, INT ID, HWND hWndCtrl, UINT codeNotify)
    {
        UNUSED_VARIABLE(hWnd);
        UNUSED_VARIABLE(hWndCtrl);
        UNUSED_VARIABLE(codeNotify);

        switch (ID)
        {
            case IDC_MERGE_BUTTON_INPUT_BROWSE:
            case IDC_MERGE_BUTTON_OUTPUT_BROWSE:
            {
                COpenFileDialog ofd(*this);

                if (!ofd.GetOpenFileName())
                    break;

                hWnd = ID == IDC_MERGE_BUTTON_INPUT_BROWSE ? m_EditInput : m_EditOutput;
                Edit_SetText(hWnd, ofd.GetFileName());

                break;
            }

            case IDC_MERGE_EDIT_INPUT:
                if (codeNotify == EN_CHANGE)
                {
                    SetButtonState(BTN_STATE_OPEN);
                }
                break;

            case IDC_BUTTON_FORCE_STOP:
                ::SendMessage(m_hWndParent, WM_APP_FORCE_STOP, 0, 0);
                break;

            case IDC_MERGE_BUTTON_OPEN:
                if (::SendMessage(m_hWndParent, WM_APP_VERIFY, 0, 0) != NO_ERROR)
                    break;

                SetButtonState(BTN_STATE_MERGE);
                break;

            case IDC_MERGE_BUTTON_MERGE:
                if (m_EditInput.GetTextLength() == 0)
                    break;
                if (m_EditPassword.IsWindowEnabled() && m_EditPassword.GetTextLength() == 0)
                {
                    MessageBox(_T("请输入有效的密码"));
                    m_EditPassword.SetFocus();
                    break;
                }

                if (::SendMessage(m_hWndParent, WM_APP_MERGE, 0, 0) != NO_ERROR)
                    break;

                SetButtonState(BTN_STATE_STOP);
                SetFocus();
                break;
        }
    }

    VOID OnDropFiles(HWND hWnd, HDROP hDrop)
    {
        TCHAR szPath[MAX_PATH];
        POINT ptDrop;

        DragQueryPoint(hDrop, &ptDrop);
        ClientToScreen(&ptDrop);
        hWnd = WindowFromPoint(ptDrop);

        if (hWnd == m_EditInput || hWnd == m_EditOutput)
        {
            if (DragQueryFile(hDrop, 0, szPath, countof(szPath)) != 0)
            {
                Edit_SetText(hWnd, szPath);
                Edit_SetSel(hWnd, StrLength(szPath), -1);
                ::SetFocus(hWnd);
            }
        }

        DragFinish(hDrop);
    }

    VOID OnLButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UInt keyFlags)
    {
        UNUSED_VARIABLE(hWnd);
        UNUSED_VARIABLE(x);
        UNUSED_VARIABLE(y);
        UNUSED_VARIABLE(keyFlags);
        FORWARD_WM_NCLBUTTONDOWN(m_hWndParent, fDoubleClick, 0, 0, HTCAPTION, ::SendMessage);
    }

    VOID OnLButtonUp(HWND hWnd, INT x, INT y, UInt keyFlags)
    {
        UNUSED_VARIABLE(hWnd);
        UNUSED_VARIABLE(x);
        UNUSED_VARIABLE(y);
        UNUSED_VARIABLE(keyFlags);
        FORWARD_WM_NCLBUTTONUP(m_hWndParent, 0, 0, HTCAPTION, ::SendMessage);
    }

    BOOL OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
    {
        UNUSED_VARIABLE(hWnd);
        UNUSED_VARIABLE(hWndFocus);
        UNUSED_VARIABLE(lParam);

        DragAcceptFiles();
        InitControls((HFONT)lParam);

        return TRUE;
    }

    BOOL InitControls(HFONT hFont)
    {
        m_hWndButton   = GetDlgItem(IDC_MERGE_BUTTON_OPEN);
        m_ProgressBar  = GetDlgItem(IDC_MERGE_PROGRESS);
        m_EditInput    = GetDlgItem(IDC_MERGE_EDIT_INPUT);
        m_EditOutput   = GetDlgItem(IDC_MERGE_EDIT_OUTPUT);
        m_EditPassword = GetDlgItem(IDC_MERGE_EDIT_PASSWORD);
        SendMessageToDescendants(WM_SETFONT, (WPARAM)hFont, 0);
        return TRUE;
    }

    static BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
    {
        ::EnableWindow(hWnd, (BOOL)lParam);
        return TRUE;
    }
};

class CDlgSplit : public CDlgBase
{
    enum ESizeUnitType
    {
        SIZE_UNIT_UNKNOWN,
        SIZE_UNIT_BYTE,
        SIZE_UNIT_KB,
        SIZE_UNIT_MB,
        SIZE_UNIT_GB,
    };
    typedef struct
    {
        ESizeUnitType SizeUnitType;
        union
        {
            INT64         SliceSize;
            LARGE_INTEGER liSizeValue;
        };
    } SLICE_SIZE_INFO;

protected:
    HWND            m_hWndComboBox;
    CEditBox        m_EditInput, m_EditOutput;
    CProgressBar    m_ProgressBar;
    SLICE_SIZE_INFO m_CurSliceInfo;

public:
    CDlgSplit(INT ID = 0) : CDlgBase(ID)
    {
        m_CurSliceInfo.SizeUnitType = SIZE_UNIT_UNKNOWN;
    }

    BOOL IsSaveOriginalFileName()
    {
        return IsDlgButtonChecked(IDC_SPLIT_CHECK_ORIGNAME);
    }

    BOOL IsOutputCompress()
    {
        return IsDlgButtonChecked(IDC_SPLIT_CHECK_COMPRESS);
    }

    BOOL IsOutputEncrypt()
    {
        return IsDlgButtonChecked(IDC_SPLIT_CHECK_ENCRYPT);
    }

    INT GetInputFile(LPTSTR lpBuffer, DWORD BufferCount)
    {
        return m_EditInput.GetText(lpBuffer, BufferCount);
    }

    INT GetOutputFile(LPTSTR lpBuffer, DWORD BufferCount)
    {
        return m_EditOutput.GetText(lpBuffer, BufferCount);
    }

    INT GetPassword(LPTSTR lpBuffer, DWORD BufferCount)
    {
        if (lpBuffer && BufferCount > 0)
            lpBuffer[0] = 0;
        else
            return 0;

        if (IsDlgButtonChecked(IDC_SPLIT_CHECK_ENCRYPT) == BST_UNCHECKED)
        {
            return 0;
        }

        return ::Edit_GetText(GetDlgItem(IDC_SPLIT_EDIT_PASSWORD), lpBuffer, BufferCount);
    }

    BOOL ChangeDialogState(BOOL bEnable)
    {
        HWND hWnd;
        UINT IDSet, IDFind;

        if (bEnable)
        {
            IDSet  = IDC_SPLIT_BUTTON_SPLIT;
            IDFind = IDC_BUTTON_FORCE_STOP;
        }
        else
        {
            IDSet  = IDC_BUTTON_FORCE_STOP;
            IDFind = IDC_SPLIT_BUTTON_SPLIT;
        }

        EnableChildWindows(bEnable);

        hWnd = GetDlgItem(IDFind);
        ::SetWindowLong(hWnd, GWL_ID, IDSet);
        ::EnableWindow(hWnd, TRUE);
        SetWindowText(hWnd, bEnable ? DLG_SPLIT_STRING_BTN_SPLIT : DLG_SPLIT_STRING_BTN_STOP);

        return TRUE;
    }

    BOOL SetProgress(INT Percent)
    {
        m_ProgressBar.SetPosition(Percent);
        return TRUE;
    }

    INT64 GetSliceSize()
    {
        INT     Length;
        UINT64  UnitSize;
        TCHAR   szSliceSizeBuf[64];

        if (ComboBox_GetCurSel(m_hWndComboBox) != CB_ERR)
            return m_CurSliceInfo.SliceSize;

        Length = ::ComboBox_GetText(m_hWndComboBox, szSliceSizeBuf, countof(szSliceSizeBuf));
        if (Length == 0)
            return 0;

        --Length;
        while (!IN_RANGE('0', szSliceSizeBuf[Length], '9'))
            if (Length-- == 0)
                return 0;

        ++Length;
        while (szSliceSizeBuf[Length] == ' ' || szSliceSizeBuf[Length] == '\t')
            ++Length;

        UnitSize = 1024;
        switch (CHAR_UPPER(szSliceSizeBuf[Length]))
        {
            default:
                return 0;

            case 0:
            case 'K':
                break;
            case 'B':
                UnitSize = 1;
                break;
            case 'M':
                UnitSize = 1024ll * 1024;
                break;
            case 'G':
                UnitSize = 1024ll * 1024 * 1024;
                break;
            case 'T':
                UnitSize = 1024ll * 1024 * 1024 * 1024;
                break;
            case 'P':
                UnitSize = 1024ll * 1024 * 1024 * 1024 * 1024;
                break;
            case 'E':
                UnitSize = 1024ll * 1024 * 1024 * 1024 * 1024 * 1024;
                break;
        }

        if (szSliceSizeBuf[Length] != 0 && szSliceSizeBuf[Length + 1] != 0)
        {
            if (szSliceSizeBuf[Length + 2] != 0 || (UnitSize != 1 && CHAR_UPPER(szSliceSizeBuf[Length + 1]) != 'B'))
            {
                return 0;
            }
        }

        return StringToInt64(szSliceSizeBuf) * UnitSize;
    }

protected:
    BEGIN_MSG_MAP(CDlgSplit)
        MSG_HANDLER(WM_COMMAND,     OnCommand)
        MSG_HANDLER(WM_DROPFILES,   OnDropFiles)
        MSG_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
        MSG_HANDLER(WM_LBUTTONUP,   OnLButtonUp)
        MSG_HANDLER(WM_INITDIALOG,  OnInitDialog)
    END_MSG_MAP()

    VOID OnCommand(HWND hWnd, INT ID, HWND hWndCtrl, UINT codeNotify)
    {
        UNUSED_VARIABLE(hWndCtrl);
        UNUSED_VARIABLE(codeNotify);

        switch (ID)
        {
            case IDC_SPLIT_BUTTON_INPUT_BROWSE:
            case IDC_SPLIT_BUTTON_OUTPUT_BROWSE:
            {
                COpenFileDialog ofd(*this);

                if (!ofd.GetOpenFileName())
                    break;

                hWnd = ID == IDC_SPLIT_BUTTON_INPUT_BROWSE ? m_EditInput : m_EditOutput;
                Edit_SetText(hWnd, ofd.GetFileName());
            }
            break;

            case IDC_SPLIT_COMBO_SLICE_SIZE:
                OnComboBoxSliceNotify(hWnd, codeNotify, ID, hWndCtrl);
                break;

            case IDC_SPLIT_CHECK_ENCRYPT:
                ::ShowWindow(GetDlgItem(IDC_SPLIT_EDIT_PASSWORD), Button_GetCheck(hWndCtrl) ? SW_SHOW : SW_HIDE);
                break;

            case IDC_BUTTON_FORCE_STOP:
                ::SendMessage(m_hWndParent, WM_APP_FORCE_STOP, 0, 0);
                break;

            case IDC_SPLIT_BUTTON_SPLIT:
#if 0
                m_EditInput.SetText(_T("test.bmp"));
                ::ComboBox_SetText(m_hWndComboBox, _T("255k"));
#endif
                if (m_EditInput.GetTextLength() == 0)
                    break;

                ::SendMessage(m_hWndParent, WM_APP_SPLIT, 0, 0);
                SetFocus();
                break;
        }
    }

    VOID OnComboBoxSliceNotify(HWND hWnd, UInt codeNofity, INT id, HWND hWndCtl)
    {
        SLICE_SIZE_INFO *pInfo;

        UNUSED_VARIABLE(id);
        UNUSED_VARIABLE(hWnd);

        switch (codeNofity)
        {
            case CBN_SELCHANGE:
                pInfo = (SLICE_SIZE_INFO *)ComboBox_GetItemData(hWndCtl, ComboBox_GetCurSel(hWndCtl));
                if (pInfo == NULL)
                    break;

                m_CurSliceInfo = *pInfo;
                ::SetFocus(hWndCtl);
                break;
        }
    }

    VOID OnDropFiles(HWND hWnd, HDROP hDrop)
    {
        TCHAR szPath[MAX_PATH];
        POINT ptDrop;

        DragQueryPoint(hDrop, &ptDrop);
        ClientToScreen(&ptDrop);
        hWnd = WindowFromPoint(ptDrop);

        if (hWnd == m_EditInput || hWnd == m_EditOutput)
        {
            if (DragQueryFile(hDrop, 0, szPath, countof(szPath)) != 0)
            {
                Edit_SetText(hWnd, szPath);
                Edit_SetSel(hWnd, StrLength(szPath), -1);
                ::SetFocus(hWnd);
            }
        }

        DragFinish(hDrop);
    }

    VOID OnLButtonDown(HWND hWnd, BOOL fDoubleClick, INT x, INT y, UInt keyFlags)
    {
        UNUSED_VARIABLE(hWnd);
        UNUSED_VARIABLE(x);
        UNUSED_VARIABLE(y);
        UNUSED_VARIABLE(keyFlags);
        FORWARD_WM_NCLBUTTONDOWN(m_hWndParent, fDoubleClick, 0, 0, HTCAPTION, ::SendMessage);
    }

    VOID OnLButtonUp(HWND hWnd, INT x, INT y, UInt keyFlags)
    {
        UNUSED_VARIABLE(hWnd);
        UNUSED_VARIABLE(x);
        UNUSED_VARIABLE(y);
        UNUSED_VARIABLE(keyFlags);
        FORWARD_WM_NCLBUTTONUP(m_hWndParent, 0, 0, HTCAPTION, ::SendMessage);
    }

    BOOL OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
    {
        UNUSED_VARIABLE(hWnd);
        UNUSED_VARIABLE(hWndFocus);
        UNUSED_VARIABLE(lParam);

        DragAcceptFiles();
        InitControls((HFONT)lParam);

        return TRUE;
    }

    BOOL InitControls(HFONT hFont)
    {
        HWND hWnd;
        TCHAR *szComboBuildInOption[] =
        {
            _T("3.5\":    1,457,664"),
            _T("Zip100:  98,078 KB"),
            _T("CD700:   700 MB"),
            _T("DVD+R:   4,481 MB"),
        };
        static SLICE_SIZE_INFO SizeInfo[] =
        {
            { SIZE_UNIT_BYTE, 1457664               },
            { SIZE_UNIT_KB,   98078 * 1024ll        },
            { SIZE_UNIT_MB,   700   * 1024 * 1024ll },
            { SIZE_UNIT_MB,   4481  * 1024 * 1024ll },
        };

        ::EnableWindow(GetDlgItem(IDC_SPLIT_CHECK_COMPRESS), FALSE);

        hWnd = GetDlgItem(IDC_SPLIT_PROGRESS);
        m_ProgressBar = hWnd;

        hWnd = GetDlgItem(IDC_SPLIT_EDIT_INPUT);
        m_EditInput = hWnd;
        Edit_LimitText(hWnd, MAX_PATH);

        hWnd = GetDlgItem(IDC_SPLIT_EDIT_OUTPUT);
        m_EditOutput = hWnd;
        Edit_LimitText(hWnd, MAX_PATH);

        hWnd = GetDlgItem(IDC_SPLIT_EDIT_PASSWORD);
        Edit_LimitText(hWnd, MAX_PASSWORD_LENGTH);
        ::ShowWindow(hWnd, SW_HIDE);

        hWnd = GetDlgItem(IDC_SPLIT_COMBO_SLICE_SIZE);
        m_hWndComboBox = hWnd;
        for (UInt i = 0; i != min(countof(szComboBuildInOption), countof(SizeInfo)); ++i)
        {
            ComboBox_InsertString(hWnd, i, szComboBuildInOption[i]);
            ComboBox_SetItemData(hWnd, i, (LPARAM)&SizeInfo[i]);
        }

        ComboBox_LimitText(hWnd, 15);
        SendMessageToDescendants(WM_SETFONT, (WPARAM)hFont, 0);

        return TRUE;
    }
};

#endif /* _DIALOGSPLIT_H_ */
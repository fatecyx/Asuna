#ifndef _SCRIPTDIALOG_H_
#define _SCRIPTDIALOG_H_

#include "WindowBase.h"
#include "common/my_xml.h"
#include "ScriptParser.h"
#include "resource.h"

class CScriptDialog : public MyWindowClass::CDialogImpl2
{
protected:
    HWND               m_hWndComboBox, m_hWndCompany, m_hWndGame;
    POINT              m_ptMinTrackSize;
    SIZE               m_LastSize;
    ULong              m_GameTypeCount;
    SBLScriptConfig   *m_pConfig;
    SBLScriptGameList *m_pGameList;
    SBLScriptGameInfo *m_pGameInfoSelected;

    enum { IDC_SCRIPTDLG_COMBOBOX = 0x8000 };

public:
    CScriptDialog();

    Bool SetGameListInfo(SBLScriptConfig *pConfig, SBLScriptGameList *pGameList, ULong GameTypeCount);
    SBLScriptGameInfo* GetGameInfoSelected();

protected:
    BEGIN_MSG_MAP(CScriptDialog)
        MSG_HANDLER(WM_COMMAND,       OnCommand)
        MSG_HANDLER(WM_MOUSEWHEEL,    OnMouseWheel)
        MSG_HANDLER(WM_SIZE,          OnSize)
        MSG_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
        MSG_HANDLER(WM_INITDIALOG,    OnInitDialog)
    END_MSG_MAP();

    DECL_MSG_HANDLER(WM_MOUSEWHEEL,    OnMouseWheel);
    DECL_MSG_HANDLER(WM_COMMAND,       OnCommand);
    DECL_MSG_HANDLER(WM_SIZE,          OnSize);
    DECL_MSG_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo);
    DECL_MSG_HANDLER(WM_INITDIALOG,    OnInitDialog);
};

#endif /* _SCRIPTDIALOG_H_ */
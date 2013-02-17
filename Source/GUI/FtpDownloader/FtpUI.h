#ifndef _FTPUI_H_
#define _FTPUI_H_

#include "pragma_once.h"
#include "FtpHelper.h"
#include "my_headers.h"
#include "WindowBase.h"
#include "resource.h"
#include "EditBox.h"
#include "ListView.h"

using namespace MyWindowClass;

#define FTP_REAL_FAILED(_Status) (((_Status) != FTPHLP_ERROR_PENDING) && FTPHLP_FAILED(_Status))
#define ANONYMOUS_USERNAME "anonymous"
#define ANONYMOUS_PASSWORD "Amano@Amano.com"

#define LV_FILE_NAME_INDEX 0
#define LV_FILE_SIZE_INDEX 1
#define LV_FILE_TYPE_INDEX 2
#define LV_FILE_TIME_INDEX 3

#define LV_DOWN_STATUS_INDEX    0
#define LV_DOWN_NAME_INDEX      1
#define LV_DOWN_SIZE_INDEX      2
#define LV_DOWN_RECVED_INDEX    3
#define LV_DOWN_PERCENT_INDEX   4
#define LV_DOWN_SPEED_INDEX     5

#define LV_LOG_TIME_INDEX 0
#define LV_LOG_MSG_INDEX 1

#define LV_FOLDER_ICON_INDEX 0
#define LV_DEFAULT_ICON_INDEX 1

#define DEFAULT_MAX_TASKS   2
#define MAX_LOG_LINES       0x100

#define MIN_KB_BYTES (1024ll)
#define MIN_MB_BYTES (MIN_KB_BYTES * 1024)
#define MIN_GB_BYTES (MIN_MB_BYTES * 1024)
#define MIN_TB_BYTES (MIN_GB_BYTES * 1024)

enum
{
    OP_RET_CONTINUE,
    OP_RET_FAILED,
    OP_RET_FINISH,

    OP_KEY_CONNECT = 0,
    OP_KEY_LOGIN,
    OP_KEY_LOGOUT,
    OP_KEY_GETDIRINFO,
    OP_KEY_CHANGEDIR,
};

enum
{
    IDM_DOWNLOAD = 20000,
    IDM_CLEAR_LIST_VIEW,
};

class CFtpUI : public CDialogImpl<CFtpUI>
{
    struct COMPLETION_ROUTINE_PARAM
    {
        CFtpUI *pThis;
        DIRECTORY_INFO *pDir;

        COMPLETION_ROUTINE_PARAM(CFtpUI *pThis)
        {
            this->pThis = pThis;
            pDir = NULL;
        }
    };

protected:
    CEditBox    m_EditAddr, m_EditUser, m_EditPwd, m_EditPort, m_EditPath;
    CListView   m_LvFile, m_LvDlList, m_LvLog;
    HMENU       m_hMenuLvFile, m_hMenuLvDlList, m_hMenuLvLog;
    HFONT       m_hFontUI;
    CFTPHelper  m_FtpHlp;
    HIMAGELIST  m_hImageListIcon;
    String      m_ExtensionList;
    DWORD       m_IconIndexBegin;

public:
    CFtpUI();
    ~CFtpUI();

    INT Run(HINSTANCE hInstance);

    FRIEND_OVERRIDE_DIALOG_METHOD(CFtpUI, CDialogImpl)
protected:
    static INT STDCALL ShowLog(ULONG_PTR CallerParam, LPCTSTR pszFormat, va_list args);
    INT ShowLogWoker(LPCTSTR pszFormat, va_list args);
    INT ShowLogInternal(LPCTSTR pszFormat, ...);

    static
    LONG_PTR
    STDCALL
    DownloadStatusCallback(
        DOWNLOAD_REQUEST_ENTRY *pDownReq,
        ULONG_PTR               Key,
        ULONG_PTR               CallerParam
    );

    LONG_PTR DownloadStatusInternal(DOWNLOAD_REQUEST_ENTRY *pDownReq, ULONG_PTR Key);

    VOID SetControlsState(BOOL bEnable);
    VOID ClearControlsContext();

    INT GetExtensionIndex(LPCTSTR pszExtensionList, LPCTSTR pszExtension);
    INT AddExtension(LPCTSTR pszExtension);

    LONG_PTR OnConnectDone      (COMPLETION_ROUTINE_PARAM *pParam, LONG FtpStatus, DWORD ErrorCode);
    LONG_PTR OnLoginDone        (COMPLETION_ROUTINE_PARAM *pParam, LONG FtpStatus, DWORD ErrorCode);
    LONG_PTR OnGetDirInfoDone   (COMPLETION_ROUTINE_PARAM *pParam, LONG FtpStatus, DWORD ErrorCode);
    LONG_PTR OnChangeDirDone    (COMPLETION_ROUTINE_PARAM *pParam, LONG FtpStatus, DWORD ErrorCode);

    BEGIN_MSG_MAP(CFtpUI)
        CMD_ID_HANDLER(IDOK,                OnBtnOK)
        CMD_ID_HANDLER(IDCANCEL,            OnBtnCancel)
        CMD_ID_HANDLER(IDC_BTN_LOGIN,       OnBtnLogin)
        CMD_ID_HANDLER(IDC_BTN_LOGOUT,      OnBtnLogout)
        CMD_ID_HANDLER(IDC_CHECK_ANONYMOUS, OnChkBtnAnonymous)

        MSG_HANDLER(WM_COMMAND,     OnCommand)
        MSG_HANDLER(WM_NOTIFY,      OnNotify)
        MSG_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
        MSG_HANDLER(WM_LBUTTONUP,   OnLButtonUp)
        MSG_HANDLER(WM_INITDIALOG,  OnInitDialog)
//        MSG_HANDLER(WM_DESTROY,     OnDestroy)
    END_MSG_MAP()

    DECL_ID_HANDLER(OnBtnOK);
    DECL_ID_HANDLER(OnBtnCancel);
    DECL_ID_HANDLER(OnBtnLogin);
    DECL_ID_HANDLER(OnBtnLogout);
    DECL_ID_HANDLER(OnChkBtnAnonymous);

    DECL_MSG_HANDLER(WM_COMMAND,        OnCommand);
    DECL_MSG_HANDLER(WM_NOTIFY,         OnNotify);
    DECL_MSG_HANDLER(WM_LBUTTONDOWN,    OnLButtonDown);
    DECL_MSG_HANDLER(WM_LBUTTONUP,      OnLButtonUp);
    DECL_MSG_HANDLER(WM_INITDIALOG,     OnInitDialog);
    DECL_MSG_HANDLER(WM_DESTROY,        OnDestroy);

    VOID OnLvDoubleClick(LPNMITEMACTIVATE lpnmitem);
    VOID OnLvRightClick(LPNMITEMACTIVATE lpnmitem);
    VOID OnDownloadSelected();

    static
    LONG_PTR
    STDCALL
    UICompletionRoutine(
        LONG      FtpStatus,
        DWORD     ErrorCode,
        DWORD     Flags,
        ULONG_PTR CompletionKey,
        ULONG_PTR CallerParam);

    LONG_PTR
    UICompletionRoutineInternal(
        LONG                        FtpStatus,
        DWORD                       ErrorCode,
        DWORD                       Flags,
        ULONG_PTR                   CompletionKey,
        COMPLETION_ROUTINE_PARAM   *pParam);
};


#endif // _FTPUI_H_
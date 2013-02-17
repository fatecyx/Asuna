#ifndef _BINARYSPLITTER_H_
#define _BINARYSPLITTER_H_

#include "WindowBase.h"
#include "resource.h"
#include "DialogSplit.h"
#include "ControllerSplitter.h"
#include "BinarySplitterMsg.h"

EXTCPP class CControllerSplitter;
using namespace MyWindowClass;

class CViewSplitter : public CWindowImpl<CViewSplitter>
//class CViewSplitter : public CWindowImpl2
{
    typedef struct
    {
        BOOL  bInit;
        HDROP hDrop;
        CViewSplitter *pThis;
    } SLVAddFileInfo;

protected:
    HACCEL    m_hAccel;
    SIZE      m_MinSize, m_LastClientSize;
    HFONT     m_hFont;
    CDlgSplit m_DlgSplit;
    CDlgMerge m_DlgMerge;
    CDlgAbout m_DlgAbout;
    CDlgBase *m_pCurrentDlg, *m_pDlgToDisplay;
    HWND      m_hWndFocusOld;
    BOOL      m_bForceStopped;

    CControllerSplitter *m_pController;

public:
    CViewSplitter();
    ~CViewSplitter();

    INT Run(HINSTANCE hInstance);
    CControllerSplitter* SetController(CControllerSplitter *pController);
    CControllerSplitter* RemoveController();

    INT ShowAskMessage(LPCTSTR pszFormat, ...);
    INT ShowErrorMessage(LPCTSTR pszFormat, ...);
    INT ShowErrorMessageTimeout(DWORD MilliSeconds, LPCTSTR pszFormat, ...);

    INT ShowAskMessageV(LPCTSTR pszFormat, va_list args);
    INT ShowErrorMessageV(LPCTSTR pszFormat, va_list args);
    INT ShowErrorMessageTimeoutV(DWORD MilliSeconds, LPCTSTR pszFormat, va_list args);

    // common
    BOOL SetProgress(INT Percent);
    BOOL SetOperationComplete(BOOL bComplete);
    INT  GetInputFileName(LPTSTR pBuffer, DWORD BufferCount);
    INT  GetOutputFileName(LPTSTR pBuffer, DWORD BufferCount);
    INT  GetPassword(LPTSTR pBuffer, DWORD BufferCount);

    // split
    BOOL  IsSaveOriginalFileName();
    BOOL  IsOutputCompress();
    BOOL  IsOutputEncrypt();
    INT64 GetSliceSize();

    // merge
    BOOL IsRestoreOriginalFileName();
    BOOL HasPassword(BOOL bHas);
    BOOL HasOriginalFileName(BOOL bHas);

protected:
    BEGIN_MSG_MAP(CViewSplitter)
        MSG_HANDLER(WM_COMMAND,         OnCommand)
        MSG_HANDLER(WM_ACTIVATE,        OnActivate)
//        MSG_HANDLER(WM_SETFOCUS,        OnSetFocus)
//        MSG_HANDLER(WM_KILLFOCUS,       OnKillFocus)
        MSG_HANDLER(WM_LBUTTONDOWN,     OnLButtonDown)
        MSG_HANDLER(WM_LBUTTONUP,       OnLButtonUp)
        MSG_HANDLER(WM_DESTROY,         OnDestroy)
        MSG_HANDLER(WM_CREATE,          OnCreate)

        MSG_CUSTOM_HANDLER(WM_APP_SPLIT,      OnAppSplit)
        MSG_CUSTOM_HANDLER(WM_APP_MERGE,      OnAppMerge)
        MSG_CUSTOM_HANDLER(WM_APP_VERIFY,     OnAppOpen)
        MSG_CUSTOM_HANDLER(WM_APP_FORCE_STOP, OnAppForceStop)
    END_MSG_MAP()

    FRIEND_OVERRIDE_WINDOW_METHOD(CViewSplitter, CWindowImpl);

protected:
    BOOL PreTranslateMessage(LPMSG lpMsg);
    VOID ReleaseAll();
    BOOL InitControls(HDC hDC);
    BOOL ChangeDialogState(BOOL bEnable);
    VOID ChangeDialog(CDlgBase *pDlgToDisplay);
    VOID SlideMoveWindow();

    static DWORD WINAPI SlideMoveWindowThread(LPVOID lpParam);

    DECL_MSG_CUSTOM_HANDLER(OnAppSplit);
    DECL_MSG_CUSTOM_HANDLER(OnAppMerge);
    DECL_MSG_CUSTOM_HANDLER(OnAppOpen);
    DECL_MSG_CUSTOM_HANDLER(OnAppForceStop);

    DECL_MSG_HANDLER(WM_CREATE,         OnCreate);
    DECL_MSG_HANDLER(WM_COMMAND,        OnCommand);
    DECL_MSG_HANDLER(WM_ACTIVATE,       OnActivate);
//    DECL_MSG_HANDLER(WM_KILLFOCUS,      OnKillFocus);
//    DECL_MSG_HANDLER(WM_SETFOCUS,       OnSetFocus);
    DECL_MSG_HANDLER(WM_GETMINMAXINFO,  OnGetMinMaxInfo);
    DECL_MSG_HANDLER(WM_SIZE,           OnSize);
    DECL_MSG_HANDLER(WM_DROPFILES,      OnDropFiles);
    DECL_MSG_HANDLER(WM_LBUTTONDOWN,    OnLButtonDown);
    DECL_MSG_HANDLER(WM_LBUTTONUP,      OnLButtonUp);
    DECL_MSG_HANDLER(WM_DESTROY,        OnDestroy);

    enum EBSControlID
    {
        BS_ID_TOOLBAR = 10000,
        BS_ID_TB_SPLIT,
        BS_ID_TB_MERGE,
        BS_ID_TB_ABOUT,
    };
};

#endif /* _BINARYSPLITTER_H_ */
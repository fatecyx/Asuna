#ifndef _PACKER2_H_
#define _PACKER2_H_

#include "WindowBase.h"
#include "ProgressBar.h"
#include "EditBox.h"
#include "ListView.h"

using namespace MyWindowClass;

class CPacker2 : public CWindowImpl<CPacker2>
//class CPacker2 : public CWindowImpl2
{
    typedef struct
    {
        Bool  bInit;
        HDROP hDrop;
        CPacker2 *pThis;
    } SLVAddFileInfo;

protected:
    HACCEL m_hAccel;
    CEditBox m_EditOutPut, m_EditPlugin, m_EditParam;
    MyWindowClass::CListView m_ListView;
    CProgressBar m_ProgessBar;
    SIZE m_MinSize, m_LastClientSize;
    HFONT m_hFont;
    PTChar m_pszDefExtension;
    DWORD m_ThreadLVInsertID;

public:
    CPacker2();
    ~CPacker2();

    BEGIN_MSG_MAP(CPacker2)
        COMMAND_RANGE_HANDLER(PAK2_ID_BTN_OUTPUT, PAK2_ID_BTN_LAST - 1, OnButton)

        MSG_HANDLER(WM_CREATE, OnCreate)
        MSG_HANDLER(WM_COMMAND, OnCommand)
        MSG_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
        MSG_HANDLER(WM_SIZE, OnSize)
        MSG_HANDLER(WM_DROPFILES, OnDropFiles)
        MSG_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
        MSG_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//        MSG_HANDLER(WM_CLOSE, OnClose)
        MSG_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_USER_INSERTITEM_FINISH, OnInsertFinish)
    END_MSG_MAP()

    Bool PreTranslateMessage(LPMSG lpMsg);

protected:
    Void ReleaseAll();
    Bool InitControls(HDC hDC);
    Bool UpdateSettings(LPCREATESTRUCT lpCreateStruct);
    Bool GetRelativeWindowRect(HWND hWnd, LPRECT lpRect);
    Bool DeltaWindowPos(HWND hWnd, Int deltaX, Int deltaY, LPCRECT rcControl, UInt Flags, UInt Org);
    DWORD ListViewAddItemThreadWorker(SLVAddFileInfo *pInfo);

    static DWORD STDCALL ListViewAddItemThread(LPVoid lpParam);

    DECL_MSG_HANDLER(WM_CREATE, OnCreate);
    DECL_MSG_HANDLER(WM_COMMAND, OnCommand);
    DECL_MSG_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo);
    DECL_MSG_HANDLER(WM_SIZE, OnSize);
    DECL_MSG_HANDLER(WM_DROPFILES, OnDropFiles);
    DECL_MSG_HANDLER(WM_LBUTTONDOWN, OnLButtonDown);
    DECL_MSG_HANDLER(WM_LBUTTONUP, OnLButtonUp);
    DECL_MSG_HANDLER(WM_CLOSE, OnClose);
    DECL_MSG_HANDLER(WM_DESTROY, OnDestroy);
    DECLARE_CMD_HANDLER(OnButton);
    DECLARE_MSG_HANDLER(OnInsertFinish);

    enum
    {
        XStart = 10,
        YStart = 5,
        SPACE_BETWEEN_BTN = 5,
        SPACE_AT_MIDDLE_OF_BTN = 10,
    };

    enum EPacker2ControlID
    {
        PAK2_ID_BTN_FIRST = 10000,
        PAK2_ID_BTN_OUTPUT = PAK2_ID_BTN_FIRST,
        PAK2_ID_BTN_PLUGIN,
        PAK2_ID_BTN_PARAM,
        PAK2_ID_BTN_ENCRYPT,
        PAK2_ID_BTN_COMPRESS,

        PAK2_ID_BTN_AT_BOTTOM_FIRST,

        PAK2_ID_BTN_SELALL = PAK2_ID_BTN_AT_BOTTOM_FIRST,
        PAK2_ID_BTN_SELNONE,
        PAK2_ID_BTN_INVERT,
        PAK2_ID_BTN_REMOVE,
        PAK2_ID_BTN_CLEAR,
        PAK2_ID_BTN_PACK,

        PAK2_ID_BTN_AT_BOTTOM_LAST = PAK2_ID_BTN_PACK,

        PAK2_ID_BTN_STOP_INSERT,
        PAK2_ID_BTN_STOP_PACK,

        PAK2_ID_BTN_LAST,

        PAK2_ID_EDIT_FIRST,

        PAK2_ID_EDIT_OUTPUT = PAK2_ID_EDIT_FIRST,
        PAK2_ID_EDIT_PLUGIN,
        PAK2_ID_EDIT_PARAM,

        PAK2_ID_EDIT_LAST,
    };

    enum EPacker2CustomMessage
    {
        WM_USER_FIRST = WM_USER,
        WM_USER_INSERTITEM_FINISH,
        WM_USER_INTERRUPT_INSERT,
    };
};

#endif /* _PACKER2_H_ */
#ifndef _BABYLON_H_
#define _BABYLON_H_

#include "WindowBase.h"
#include "RichEditCtl.h"
#include "ImageCtrl.h"
#include "TreeViewCtrl.h"
#include "FileDisk.h"
#include "Mem.h"
#include "bl_plugin.h"
#include "ScriptParser.h"

using namespace MyWindowClass;

enum EExportImageType { BBL_EXPORT_IMAGE_BMP, BBL_EXPORT_IMAGE_JPG, BBL_EXPORT_IMAGE_PNG };

typedef union
{
    RECT rc;
    struct
    {
        SIZE MinSize;
        SIZE LastSize;
    };
} USizeInfo;

class CBabylon : public CWindowImpl2
//class CBabylon : public CWindowImpl<CBabylon>
{
protected:

    // ui
    RECT m_rc;
    USizeInfo  m_SizeInfo;
    DWORD      m_dwLastError;
    HMENU      m_hMenuMain;
    HFONT      m_hFont;
    HWND       m_hWndSB;
    HWND       m_hWndTabCtrl;
    HACCEL     m_hAccel;
    HDC        m_hDC;
    HBITMAP    m_hBitMap;
    CTreeView  TreeView;
    CRichEdit  RichEdit;
    CImageCtrl Image;
    TEXTMETRIC tm;

    // logic
    CMem       mem;
    CBLScriptParser m_ScriptParser;
    SBLScriptConfig m_Config;

public:
    CBabylon();
    ~CBabylon();

    BEGIN_MSG_MAP(CBabylon)
//        MSG_HANDLER(WM_PAINT,           OnPaint)
        MSG_HANDLER(WM_COMMAND,         OnCommand)
        MSG_HANDLER(WM_SIZE,            OnSize)
        MSG_HANDLER(WM_GETMINMAXINFO,   OnGetMinMaxInfo)
        MSG_HANDLER(WM_LBUTTONDOWN,     OnLButtonDown)
        MSG_HANDLER(WM_LBUTTONUP,       OnLButtonUp)
        MSG_HANDLER(WM_MOUSEWHEEL,      OnMouseWheel)
//        MSG_HANDLER(WM_DRAWITEM,        OnDrawItem)
        MSG_HANDLER(WM_CREATE,          OnCreate)
        MSG_HANDLER(WM_GETFONT,         OnGetFont)
        MSG_HANDLER(WM_CLOSE,           OnClose)
        MSG_HANDLER(WM_QUERYENDSESSION, OnQueryEndSession)
        MSG_HANDLER(WM_DESTROY,         OnDestroy)
    END_MSG_MAP();

    Bool CheckSystemEnvironment();
    Bool PreTranslateMessage(LPMSG lpMsg);

protected:
    DECL_MSG_HANDLER(WM_CREATE,          OnCreate);
    DECL_MSG_HANDLER(WM_SIZE,            OnSize);
    DECL_MSG_HANDLER(WM_GETMINMAXINFO,   OnGetMinMaxInfo);
    DECL_MSG_HANDLER(WM_KEYDOWN,         OnKeyDown);
    DECL_MSG_HANDLER(WM_RBUTTONUP,       OnRButtonUp);
    DECL_MSG_HANDLER(WM_LBUTTONUP,       OnLButtonUp);
    DECL_MSG_HANDLER(WM_LBUTTONDOWN,     OnLButtonDown);
    DECL_MSG_HANDLER(WM_MENUCHAR,        OnMenuChar);
    DECL_MSG_HANDLER(WM_COMMAND,         OnCommand);
    DECL_MSG_HANDLER(WM_GETFONT,         OnGetFont);
    DECL_MSG_HANDLER(WM_PAINT,           OnPaint);
    DECL_MSG_HANDLER(WM_SETFOCUS,        OnSetFocus);
    DECL_MSG_HANDLER(WM_CLOSE,           OnClose);
    DECL_MSG_HANDLER(WM_QUERYENDSESSION, OnQueryEndSession);
    DECL_MSG_HANDLER(WM_DESTROY,         OnDestroy);
    DECL_MSG_HANDLER(WM_MOUSEWHEEL,      OnMouseWheel);
    DECL_MSG_HANDLER(WM_DRAWITEM,        OnDrawItem);

    Bool InitMenuAndAccel();
    Bool InitControls();
    Void MoveWindowByDiff(HWND hWnd, Int32 DiffX, Int32 DiffY, UInt32 uFlags = SWP_NOSIZE);
    Void ImageOperation(UInt32 nItemID);
    Bool SelectScript(SBLScriptGameInfo *pGameInfo);
    Bool OpenFileFromScript(SBLScriptGameInfo *pGameInfo);
};

typedef union
{
    typedef CBabylon Class;
    LRESULT (Class::*lpfn)     (UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled);

    LRESULT (Class::*OnCreate) (UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled);
    LRESULT (Class::*OnChar)   (UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled);
    LRESULT (Class::*OnCommand)(UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled);
    LRESULT (Class::*OnSize)   (UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled);
    LRESULT (Class::*OnPaint)  (UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled);
    LRESULT (Class::*OnVScroll)(UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled);
    LRESULT (Class::*OnDestroy)(UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled);
} MsgHandlers, MessageHandlers;

#pragma pack(1)

typedef struct
{
    MsgHandlers Handler;
    UINT        Message;
} THandlerArray;

#pragma pack()

#endif /* _BABYLON_H_ */
#ifndef _RICHEDITCTL_H_
#define _RICHEDITCTL_H_

#include "WindowBase.h"
#include <richedit.h>

using namespace MyWindowClass;

class CRichEdit : public CWindowImpl2
{
protected:
    DWORD   m_dwVersion, m_dwStartPos, m_dwEndPos;
    HMODULE m_hDll;
    HMENU   m_hMenu;
    HACCEL  m_hAccel;

    enum // ERichEditMsg
    {
        WM_RICHEDIT_CUT = WM_USER + 1,
        WM_RICHEDIT_COPY,
        WM_RICHEDIT_PASTE,
        WM_RICHEDIT_DELETE,
        WM_RICHEDIT_SELALL,
    };

public:
    CRichEdit(DWORD dwVersion = _RICHEDIT_VER);
    ~CRichEdit();

    BEGIN_MSG_MAP(CRichEdit)
        MSG_HANDLER(WM_COMMAND,         OnCommand)
//        MESSAGE_HANDLER(WM_COMMAND,   OnCommand)
//        MESSAGE_HANDLER(WM_SETFOCUS,  OnSetFocus)
        MESSAGE_HANDLER(WM_RBUTTONUP, OnMouseButton)
    END_MSG_MAP();

    HWND     Create(const LPRECT lpRect, HWND hWndParent = NULL, HMENU hMenu = NULL, HINSTANCE hInstance = NULL, LPVOID lpParam = NULL);
    DWORD    GetEventMask();
    DWORD    SetEventMask(DWORD dwEventMask);
    DWORD    AddEventMask(DWORD dwEventMask);
    DWORD    RemoveEventMask(DWORD dwEventMask);

    COLORREF SetBackgroundColor(LONG SystemColor, COLORREF Color = 0);
    Void     Replace(LPCSTR lpString = NULL, Bool bCanUndo = True);
    Void     SetSelectedSection(LONG Start = 0, LONG End = -1);
    DWORD    GetSelectedSection(LPLONG pStart = NULL, LPLONG pEnd = NULL);
    DWORD    GetSelectedText(LPVOID lpBuffer);
    DWORD    AddText(LPCWSTR lpText, SETTEXTEX *pSetTextEx = NULL);
    Bool     ClearText();
    DWORD    Cut();
    DWORD    Copy();
    DWORD    Paste();
    Void     Delete();
    LRESULT  DispatchMessage(CONST MSG *lpMsg);

protected:
    DECL_MSG_HANDLER(WM_COMMAND,         OnCommand);
//    DECLARE_MSG_HANDLER(OnCommand);
    DECLARE_MSG_HANDLER(OnSetFocus);
    DECLARE_MSG_HANDLER(OnMouseButton);

    Bool  Init();
};

#endif /* _RICHEDITCTL_H_ */
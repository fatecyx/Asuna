#ifndef _TREEVIEWCTRL_H_
#define _TREEVIEWCTRL_H_

#include "WindowBase.h"

class CTreeView : public MyWindowClass::CCommonControlBase<CTreeView>
{
protected:
    enum
    {
        TREE_VIEW_DEFAULT_STYLE = WS_TABSTOP|WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS,
        TREE_VIEW_DEFAULT_EX_STYLE = WS_EX_CLIENTEDGE,
    };

public:
    HWND
    Create(
        HWND      hWndParent,
        LONG      left,
        LONG      top,
        LONG      width,
        LONG      height,
        HINSTANCE hInstance = GetModuleHandle(0),
        DWORD     dwStyle   = TREE_VIEW_DEFAULT_STYLE,
        DWORD     dwExStyle = TREE_VIEW_DEFAULT_EX_STYLE
    );

    HWND
    Create(
        HWND         hWndParent,
        const LPRECT lpRect,
        HINSTANCE    hInstance = GetModuleHandle(0),
        DWORD        dwStyle   = TREE_VIEW_DEFAULT_STYLE,
        DWORD        dwExStyle = TREE_VIEW_DEFAULT_EX_STYLE
    );

    HTREEITEM
    Intert(
        LPTSTR    pszText,
        HTREEITEM hParent       = NULL,
        HTREEITEM hInsertParent = TVI_LAST,
        UINT      Mask          = TVIF_TEXT|TVIF_SELECTEDIMAGE|TVIF_PARAM
    );
};

#endif /* _TREEVIEWCTRL_H_ */
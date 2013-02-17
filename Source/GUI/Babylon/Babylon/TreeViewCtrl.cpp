#include "TreeViewCtrl.h"

HWND CTreeView::Create(HWND hWndParent, const LPRECT lpRect, HINSTANCE hInstance, DWORD dwStyle, DWORD dwExStyle)
{
    UInt32 l, t, w, h;

    l = lpRect->left;
    t = lpRect->top;
    w = lpRect->right - l;
    h = lpRect->bottom - t;

    return Create(hWndParent, l, t, w, h, hInstance, dwStyle, dwExStyle);
}

HWND CTreeView::Create(HWND hWndParent, Long left, Long top, Long width, Long height, HINSTANCE hInstance, DWORD dwStyle, DWORD dwExStyle)
{
//    dwStyle |= WS_SIZEBOX;
    m_hWnd = CreateWindowEx(dwExStyle, WC_TREEVIEW, NULL, dwStyle,
        left, top, width, height, hWndParent, NULL, hInstance, NULL);

    return m_hWnd;
}

HTREEITEM CTreeView::Intert(LPTSTR pszText, HTREEITEM hParent /* = NULL */, HTREEITEM hInsertParent /* = TVI_LAST */, UINT Mask /* = TVIF_TEXT|TVIF_SELECTEDIMAGE|TVIF_PARAM */)
{
    TVINSERTSTRUCT is;

    is.hParent = hParent;
    is.hInsertAfter = hInsertParent;
    is.item.pszText = pszText;
    is.item.mask = Mask;

    return TreeView_InsertItem(m_hWnd, &is);
}
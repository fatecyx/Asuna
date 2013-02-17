#ifndef _LISTBOX_H_
#define _LISTBOX_H_

#include "pragma_once.h"
#include "my_headers.h"
#include "WindowBase.h"

MY_NAMESPACE_BEGIN(MyWindowClass)

class CListBox : public CCommonControlBase<CListBox>
{
public:
    enum EListBoxDefaultStyle
    {
        DefStyle    = WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL|WS_HSCROLL|LBS_NOINTEGRALHEIGHT,
        DefExStyle  = WS_EX_CLIENTEDGE,
    };

    HWND
    CreateEx(
        HWND      hWndParent    = NULL,
        HINSTANCE hInstance     = NULL,
        HMENU     hMenu         = NULL,
        LPVOID    lpCreateParam = NULL,
        Int       x             = CW_USEDEFAULT,
        Int       y             = CW_USEDEFAULT,
        Int       cx            = CW_USEDEFAULT,
        Int       cy            = CW_USEDEFAULT,
        DWORD     dwStyle       = DefStyle,
        DWORD     dwExStyle     = DefExStyle
    )
    {
        return __super::CreateEx(
                            hWndParent,
                            hInstance,
                            hMenu,
                            lpCreateParam,
                            WC_LISTBOX,
                            x,
                            y,
                            cx,
                            cy,
                            dwStyle,
                            dwExStyle);
    }

    Bool Enable(Bool fEnable)
    {
        return ::ListBox_Enable(*this, fEnable);
    }

    Int GetCount()
    {
        return ListBox_GetCount(*this);
    }

    Bool ResetContent()
    {
        return ListBox_ResetContent(*this);
    }

    Int AddString(PCTChar pszText)
    {
        return ListBox_AddString(*this, pszText);
    }

    Int InsertString(Int Index, PCTChar pszText)
    {
        return ListBox_InsertString(*this, Index, pszText);
    }

    Int AddItemData(PVoid pData)
    {
        return ListBox_AddItemData(*this, pData);
    }

    Int InsertItemData(Int Index, PVoid pData)
    {
        return ListBox_InsertItemData(*this, Index, pData);
    }

    Int DeleteString(Int Index)
    {
        return ListBox_DeleteString(*this, Index);
    }

    Int GetTextLength(Int Index)
    {
        return ListBox_GetTextLen(*this, Index);
    }

    Int GetText(Int Index, PTChar pszBuffer)
    {
        return ListBox_GetText(*this, Index, pszBuffer);
    }

    LRESULT GetItemData(Int Index)
    {
        return ListBox_GetItemData(*this, Index);
    }

    Int SetItemData(Int Index, PVoid pData)
    {
        return ListBox_SetItemData(*this, Index, pData);
    }

#if (WINVER >= 0x030a)

    Int FindString(Int IndexStart, PCTChar pszFind)
    {
        return ListBox_FindString(*this, IndexStart, pszFind);
    }

    Int FindItemData(Int IndexStart, PVoid pData)
    {
        return ListBox_FindItemData(*this, IndexStart, pData);
    }

    Int SetSelelection(Int Index, Bool fSelect = True)
    {
        return ListBox_SetSel(*this, fSelect, Index);
    }

    Int SetItemRange(Int IndexFirst, Int IndexLast, Bool fSelect = True)
    {
        return ListBox_SelItemRange(*this, fSelect, IndexFirst, IndexLast);
    }

    Int GetCurrentSelection()
    {
        return ListBox_GetCurSel(*this);
    }

    Int SetCurrentSelection(Int Index)
    {
        return ListBox_SetCurSel(*this, Index);
    }

    Int SelectString(Int IndexStart, PCTChar pszFind)
    {
        return ListBox_SelectString(*this, IndexStart, pszFind);
    }

    Int SelectItemData(Int IndexStart, PVoid pData)
    {
        return ListBox_SelectItemData(*this, IndexStart, pData);
    }

    Int IsItemSelected(Int Index)
    {
        return ListBox_GetSel(*this, Index);
    }

    Int GetSelectedCount()
    {
        return ListBox_GetSelCount(*this);
    }

    Int GetTopIndex()
    {
        return ListBox_GetTopIndex(*this);
    }

    Int GetSelectedItems(Int ItemCount, PInt pItemStateBuffer)
    {
        return ListBox_GetSelItems(*this, ItemCount, pItemStateBuffer);
    }

    Int SetTopIndex(Int IndexTop)
    {
        return ListBox_SetTopIndex(*this, IndexTop);
    }

    Void SetColumnWidth(Int cxColumnWidth)
    {
        ListBox_SetColumnWidth(*this, cxColumnWidth);
    }

    Int GetHorizontalExtent()
    {
        return ListBox_GetHorizontalExtent(*this);
    }

    Void SetHorizontalExtent(Int cxExtent)
    {
        return ListBox_SetHorizontalExtent(*this, cxExtent);
    }

    Bool SetTabStops(Int TabsCount, PInt pTabs)
    {
        return ListBox_SetTabStops(*this, TabsCount, pTabs);
    }

    Int GetItemRect(Int Index, LPRECT lpRect)
    {
        return ListBox_GetItemRect(*this, Index, lpRect);
    }

    Int SetCaretIndex(Int Index)
    {
        return ListBox_SetCaretIndex(*this, Index);
    }

    Int GetCaretIndex()
    {
        return ListBox_GetCaretIndex(*this);
    }

    Int FindStringExact(Int Index, PCTChar pszFind)
    {
        return ListBox_FindStringExact(*this, Index, pszFind);
    }

    Int SetItemHeight(Int Index, Int cyHeight)
    {
        return ListBox_SetItemHeight(*this, Index, cyHeight);
    }

    Int GetItemHeight(Int Index)
    {
        return ListBox_GetItemHeight(*this, Index);
    }

#endif  /* WINVER >= 0x030a */

    Int Dir(UInt Attributes, PCTChar pszFileSpec)
    {
        return ListBox_Dir(*this, Attributes, pszFileSpec);
    }
};

MY_NAMESPACE_END

#endif /* _LISTBOX_H_ */
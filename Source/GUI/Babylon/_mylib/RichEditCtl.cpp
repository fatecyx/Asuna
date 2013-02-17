#include "RichEditCtl.h"
#include "my_headers.h"

using namespace MyWindowClass;

enum ERichEditID
{
    IDM_RE_UNDO,
    IDM_RE_CUT,
    IDM_RE_COPY,
    IDM_RE_PASTE,
    IDM_RE_DEL,
    IDM_RE_SELALL,
};

/************************************************************************/
/* Rich Edit ÓÒ¼ü²Ëµ¥                                                   */
/************************************************************************/
#define ____________________MENU_SEPARATOR____________________ { { 0 }, NULL, MF_SEPARATOR },
SMenuItem Menu_RichEdit[] =
{
//    { { FCONTROL|FVIRTKEY, 'Z', IDM_RE_UNDO   }, _T("³·Ïû(&U)") },
//        ____________________MENU_SEPARATOR____________________
//    { { FCONTROL|FVIRTKEY, 'X', IDM_RE_CUT    }, _T("¼ôÇÐ(&X)") },
    { { FCONTROL|FVIRTKEY, 'C', IDM_RE_COPY   }, _T("¸´ÖÆ(&C)") },
    { { FCONTROL|FVIRTKEY, 'V', IDM_RE_PASTE  }, _T("Õ³Ìù(&P)") },
//    { { FVIRTKEY,   VK_DELETE,  IDM_RE_DEL    }, _T("É¾³ý(&D)") },
        ____________________MENU_SEPARATOR____________________
    { { FCONTROL|FVIRTKEY, 'A', IDM_RE_SELALL }, _T("È«Ñ¡(&A)") },
};

#undef ____________________MENU_SEPARATOR____________________

DWORD dwMenuRiceEditCount = countof(Menu_RichEdit);

CRichEdit::CRichEdit(DWORD dwVersion /* = 0x300 */)
{
    m_hDll = NULL;
    m_dwStartPos = 0;
    m_dwEndPos   = 0;
    m_dwVersion = dwVersion;
}

CRichEdit::~CRichEdit()
{
    if (m_hDll)
        FreeLibrary(m_hDll);
}

Bool CRichEdit::Init()
{
    PCWChar szDll;

    switch (m_dwVersion)
    {
        case 0x100: szDll = L"RICHED32.dll"; break;
        case 0x200:
        case 0x210:
        case 0x300: szDll = L"RICHED20.DLL"; break;
        default:    szDll = L"MSFTEDIT.DLL";
    }

    m_hDll = LoadLibraryExW(szDll, 0, 0);

    return !!m_hDll;
}

HWND CRichEdit::Create(const LPRECT lpRect, HWND hWndParent /* = NULL */, HMENU hMenu /* = NULL */, HINSTANCE hInstance /* = NULL */, LPVOID lpParam /* = NULL */)
{
    DWORD dwStyle, dwExStyle;

    if (m_hDll == NULL && Init() == False)
        return NULL;

    dwStyle   = WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|
                WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|
                ES_MULTILINE|ES_MULTILINE|ES_AUTOHSCROLL|ES_WANTRETURN;//|ES_READONLY;

    dwExStyle = WS_EX_CLIENTEDGE;

    m_hWnd = CreateWindowEx(dwExStyle, RICHEDIT_CLASS, 0, dwStyle,
        lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top,
        hWndParent, 0, hInstance, lpParam);

//    SetWindowLong(WINDOW_LONG_CLASS_POINTER, (LONG_PTR)GetBaseClassPointer(this));
    SetWindowLongThisPointer();
    m_WndProc = (WNDPROC)SetWindowLong(GWL_WNDPROC, (LONG_PTR)StartWindowProc);

    UInt32 uAccelCount;
    LPACCEL lpAccel;
    CMem m;
    extern SMenuItem Menu_RichEdit[];
    extern DWORD dwMenuRiceEditCount;

    uAccelCount = GetMenuCount(Menu_RichEdit, dwMenuRiceEditCount);
    if (uAccelCount == 0)
        return m_hWnd;

    lpAccel = (LPACCEL)m.Alloc(uAccelCount * sizeof(*lpAccel));
    if (lpAccel)
    {
        m_hMenu = CreateCombinedMenuEx(Menu_RichEdit, dwMenuRiceEditCount, True, lpAccel, &uAccelCount);

        if (m_hAccel)
            DestroyAcceleratorTable(m_hAccel);

        m_hAccel = NULL;
        if (uAccelCount && lpAccel)
        {
            m_hAccel = CreateAcceleratorTable(lpAccel, uAccelCount);
        }

        m.Free(lpAccel);
    }

    return m_hWnd;
}

LRESULT CRichEdit::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled)
{
    if (m_dwStartPos == m_dwEndPos)
    {
        bHandled = False;
        return ERROR_INVALID_PARAMETER;
    }

    SetSelectedSection(m_dwStartPos, m_dwEndPos);

    return NO_ERROR;
}

Void CRichEdit::OnCommand(HWND hWnd, Int id, HWND hWndCtrl, UInt codeNotify)
{
    UINT uMsg;

    switch (id)
    {
        case IDM_RE_CUT:
            uMsg = WM_RICHEDIT_CUT;
            break;

        case IDM_RE_COPY:
            uMsg = WM_RICHEDIT_COPY;
            break;

        case IDM_RE_PASTE:
            uMsg = WM_RICHEDIT_PASTE;
            break;

        case IDM_RE_DEL:
            uMsg = WM_RICHEDIT_DELETE;
            break;

        case IDM_RE_SELALL:
            uMsg = WM_RICHEDIT_SELALL;
            break;
    }

    MSG msg = { *this, uMsg };
    DispatchMessage(&msg);
}

LRESULT CRichEdit::DispatchMessage(CONST MSG *lpMsg)
{
    Int nItemID, nMsgSrc;

    if (lpMsg->hwnd != *this)
        return 1;

    nItemID = LOWORD(lpMsg->wParam);
    nMsgSrc = HIWORD(lpMsg->wParam);

    switch (lpMsg->message)
    {
        case WM_RICHEDIT_CUT:
            Cut();
            break;

        case WM_RICHEDIT_COPY:
            Copy();
            break;

        case WM_RICHEDIT_PASTE:
            Paste();
            break;

        case WM_RICHEDIT_DELETE:
            Delete();
            break;

        case WM_RICHEDIT_SELALL:
            SetSelectedSection();
            break;

        default:
            return ERROR_INVALID_PARAMETER;
    }

    return NO_ERROR;
}

LRESULT CRichEdit::OnMouseButton(UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled)
{
    POINT pt;

    switch (uMsg)
    {
        case WM_RBUTTONUP:
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            ClientToScreen(&pt);
            TrackPopupMenuEx(m_hMenu, 0, pt.x, pt.y, *this, NULL);
            break;

        default:
            bHandled = False;
            return ERROR_INVALID_PARAMETER;
    }

    return NO_ERROR;
}

DWORD CRichEdit::GetEventMask()
{
    return SendMessage(EM_GETEVENTMASK);
}

DWORD CRichEdit::SetEventMask(DWORD dwEventMask)
{
    return SendMessage(EM_SETEVENTMASK, 0, dwEventMask);
}

DWORD CRichEdit::AddEventMask(DWORD dwEventMask)
{
    return SendMessage(EM_SETEVENTMASK, 0, dwEventMask | GetEventMask());
}

DWORD CRichEdit::RemoveEventMask(DWORD dwEventMask)
{
    return SendMessage(EM_SETEVENTMASK, 0, ~dwEventMask & GetEventMask());
}

COLORREF CRichEdit::SetBackgroundColor(LONG SystemColor, COLORREF Color /* = 0 */)
{
    return (COLORREF)SendMessage(EM_SETBKGNDCOLOR, (WPARAM)SystemColor, (LPARAM)Color);
}

Void CRichEdit::SetSelectedSection(LONG Start /* = 0 */, LONG End /* = -1 */)
{
    SendMessage(EM_SETSEL, (WPARAM)Start, (LPARAM)End);
    m_dwStartPos = Start;
    m_dwEndPos = End;
}

DWORD CRichEdit::GetSelectedSection(LPLONG pStart /* = NULL */, LPLONG pEnd /* = NULL */)
{
    return SendMessage(EM_GETSEL, (WPARAM)pStart, (LPARAM)pEnd);
}

DWORD CRichEdit::GetSelectedText(LPVOID lpBuffer)
{
    return SendMessage(EM_GETSELTEXT, 0, (LPARAM)lpBuffer);
}

Void CRichEdit::Replace(LPCSTR lpString /* = NULL */, Bool bCanUndo /* = True */)
{
    SendMessage(EM_REPLACESEL, True, (LPARAM)lpString);
}

DWORD CRichEdit::AddText(LPCWSTR lpText, SETTEXTEX *pSetTextEx /* = NULL */)
{
    SETTEXTEX st, *pst;

    if (pSetTextEx == NULL)
    {
        st.codepage = CP_UTF16_LE;
        st.flags = ST_SELECTION;
        pst = &st;
    }
    else
        pst = pSetTextEx;

    return SendMessage(EM_SETTEXTEX, (WPARAM)pst, (LPARAM)lpText);
}

Bool CRichEdit::ClearText()
{
    SetSelectedSection();
    Replace();
    return 0;
}

DWORD CRichEdit::Cut()
{
    DWORD v;

    v = Copy();
    if (v)
        Delete();

    return v;
}

DWORD CRichEdit::Copy()
{
    HANDLE  hMem;
    LPVOID  lpMem;
    HGLOBAL hGlobal;
    LONG Start, End, Length;

    GetSelectedSection(&Start, &End);
    if (Start == End)
        return 0;

    hGlobal = GlobalAlloc(GHND, (End - Start + 3) * 2);
    if (hGlobal == NULL)
        return 0;

    do
    {
        lpMem = GlobalLock(hGlobal);
        if (lpMem == NULL)
            break;

        GetSelectedText(lpMem);
        GlobalUnlock(hGlobal);

        if (OpenClipboard() == False)
            break;

        EmptyClipboard();
        hMem = SetClipboardData(CF_UNICODETEXT, lpMem);
        CloseClipboard();
        if (hMem == NULL)
            break;

        Length = End - Start;
        return Length;

    } while (0);

    GlobalFree(hGlobal);

    return 0;
}

DWORD CRichEdit::Paste()
{
    return AddText(L"\r\npaste");
}

Void CRichEdit::Delete()
{
    Replace();
}

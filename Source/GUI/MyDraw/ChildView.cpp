// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MyDraw.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "MyDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum
{
    NONE, 
    ELLIPSE_MP, 
    LINE_DEFAULT, 
    LINE_DDA, 
    LINE_MP, 
    LINE_BH, 
    FILL_RECT, 
    CROP_ENCODE, 
    _3D_DIMETRIC, 
    _3D_CABINET, 
    _3D_LOOKAT, 
};

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
    m_uiShape         = LINE_DDA;
    m_bMouseMove      = FALSE;
    m_bLeftButtonDown = FALSE;
    m_crColor         = RGB(243, 123, 58);
    m_uiClipCnt       = 0;
    QueryPerformanceFrequency(&m_lFrequency);
}

BEGIN_MESSAGE_MAP(CChildView,CWnd)
//{{AFX_MSG_MAP(CChildView)
ON_WM_PAINT()
ON_COMMAND(ID_COLOR_EDIT, OnColorEdit)
//}}AFX_MSG_MAP
ON_WM_SETCURSOR()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_WM_LBUTTONDOWN()
ON_COMMAND_RANGE(ID_CIRCLE_MP, ID_3D_LOOKAT, OnSetShape)
ON_UPDATE_COMMAND_UI_RANGE(ID_CIRCLE_MP, ID_3D_LOOKAT, OnUpdateMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CWnd::PreCreateWindow(cs))
        return FALSE;

    m_hCursor = LoadCursor(NULL, IDC_ARROW);
    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
        m_hCursor, HBRUSH(COLOR_WINDOW+1), NULL);
    m_hCursor = LoadCursor(NULL, IDC_ARROW);

    return TRUE;
}

void CChildView::OnColorEdit()
{
    CColorDialog ColorDlg(m_crColor, CC_FULLOPEN);

    if (ColorDlg.DoModal() == IDOK)
    {
        m_crColor = ColorDlg.GetColor();
        Invalidate();
    }
}

enum { LEFT = 1, TOP = 2, RIGHT = 4, BOTTOM = 8 };

NOINLINE int EncodePoint(LPPOINT lptPoint, LPRECT lpRect)
{
    int c = 0;

    if (lptPoint->x < lpRect->left)       c |= LEFT;
    else if (lptPoint->x > lpRect->right) c |= RIGHT;

    if (lptPoint->y > lpRect->bottom)     c |= BOTTOM;
    else if (lptPoint->y < lpRect->top)   c |= TOP;

    return c;
}

BOOL CChildView::EncodeCrop(LPPOINT lptStart, LPPOINT lptEnd, LPRECT lpRect)
{
    int x, y, c1, c2, c;
    double slope;

    c1 = EncodePoint(lptStart, lpRect);
    c2 = EncodePoint(lptEnd  , lpRect);

    if (c1 & c2)
        return FALSE;

    if (lptStart->x == lptEnd->x)
    {
        if (c1 & BOTTOM) lptStart->y = lpRect->bottom;
        else if (c1 & TOP) lptStart->y = lpRect->top;
        if (c2 & BOTTOM) lptEnd->y = lpRect->bottom;
        else if (c2 & TOP) lptEnd->y = lpRect->top;
        return TRUE;
    }

    slope = (double)(lptEnd->y - lptStart->y) / (double)(lptEnd->x - lptStart->x);

    while (c1 | c2)
    {
        if (c1)
            c = c1;
        else
            c = c2;

        if (c & LEFT)
        {
            x = lpRect->left;
            y = (int)(lptStart->y + slope * (lpRect->left - lptStart->x));
        }
        else if (c & TOP)
        {
            y = lpRect->top;
            x = (int)(lptStart->x + (lpRect->top - lptStart->y) / slope);
        }
        else if (c & RIGHT)
        {
            x = lpRect->right;
            y = (int)(lptStart->y + slope * (lpRect->right - lptStart->x));
        }
        else if (c & BOTTOM)
        {
            y = lpRect->bottom;
            x = (int)(lptStart->x + (lpRect->bottom - lptStart->y) / slope);
        }

        if (c == c1)
        {
            lptStart->x = x;
            lptStart->y = y;
            c1 = EncodePoint(lptStart, lpRect);
        }
        else
        {
            lptEnd->x = x;
            lptEnd->y = y;
            c2 = EncodePoint(lptEnd, lpRect);
        }
    }

    return TRUE;
}

void CChildView::OnPaint()
{
    CWnd::OnPaint();
    if (m_uiShape == CROP_ENCODE)
    {
        CMyDC *dc;
        RECT   rcClient;
        LONG   lHalfHeight, lHalfWidth;

        dc = (CMyDC *)GetDC();
        GetWindowRect(&rcClient);
        lHalfWidth  = (rcClient.right - rcClient.left) >> 1;
        lHalfHeight = (rcClient.bottom - rcClient.top) >> 1;
        rcClient.bottom -= lHalfHeight >> 1;
        rcClient.top += lHalfHeight >> 1;
        rcClient.right -= lHalfWidth >> 1;
        rcClient.left += lHalfWidth >> 1;
        ScreenToClient(&rcClient);
        dc->Rectangle(&rcClient);

        if (m_uiClipCnt)
        {
            CPen *pOldPen, pen;

            pen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
            pOldPen = dc->SelectObject(&pen);
            for (UINT i = 0; i != m_uiClipCnt; ++i)
            {
                dc->MoveTo(m_ptCrop[i]);
                dc->LineTo(m_ptCrop[i]);
            }
            dc->SelectObject(pOldPen);
        }

        if (m_uiClipCnt == 2)
        {
            if (EncodeCrop(&m_ptCrop[0], &m_ptCrop[1], &rcClient))
            {
                dc->MoveTo(m_ptCrop[0]);
                dc->LineTo(m_ptCrop[1]);
            }
            m_uiClipCnt = 0;
        }

        ::ReleaseDC(m_hWnd, dc->m_hDC);
    }
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    if ((nFlags & MK_LBUTTON) && m_bLeftButtonDown && m_uiShape != NONE)
    {
        RECT rcClient;
        LARGE_INTEGER lStartCounter, lStopCounter;
        CMyDC *dc;

        dc = (CMyDC *)GetDC();
        GetWindowRect(&rcClient);
        rcClient.left += 2;
        rcClient.top  += 2;
        --rcClient.right;
        --rcClient.bottom;
        ClipCursor(&rcClient);
        SetROP2(dc->m_hDC, R2_NOTXORPEN);
        dc->SetColor(m_crColor);

        QueryPerformanceCounter(&lStartCounter);

        switch (m_uiShape)
        {
        case ELLIPSE_MP:
            if (m_bMouseMove)
            {
                dc->MPDrawCircle(&m_rcEllipse);
            }
            m_rcEllipse.left   = m_ptClickDown.x;
            m_rcEllipse.right  = point.x;
            m_rcEllipse.top    = m_ptClickDown.y;
            m_rcEllipse.bottom = point.y;
            dc->MPDrawCircle(&m_rcEllipse);
            break;

        case FILL_RECT:
            rcClient.left   = m_ptClickDown.x;
            rcClient.top    = m_ptClickDown.y;
            if (m_bMouseMove)
            {
                rcClient.right  = m_ptOld.x;
                rcClient.bottom = m_ptOld.y;
                dc->Rectangle(&rcClient);
            }
            rcClient.right  = point.x;
            rcClient.bottom = point.y;
            dc->Rectangle(&rcClient);
            m_rcFill = rcClient;
            break;

        case LINE_DEFAULT:
            {
                CPen *pOldPen, pen;

                pen.CreatePen(PS_SOLID, 1, m_crColor);
                pOldPen = (CPen *)dc->SelectObject(pen);
                if (m_bMouseMove)
                {
                    dc->MoveTo(m_ptClickDown);
                    dc->LineTo(m_ptOld);
                }
                dc->MoveTo(m_ptClickDown);
                dc->LineTo(point);
//                dc->SelectObject(pOldPen);
            }
            break;

        case LINE_DDA:
            if (m_bMouseMove)
            {
                dc->MoveTo(m_ptClickDown);
                dc->DDADrawLine(m_ptOld);
            }
            dc->MoveTo(m_ptClickDown);
            dc->DDADrawLine(point);
            break;

        case LINE_MP:
            if (m_bMouseMove)
            {
                dc->MoveTo(m_ptClickDown);
                dc->MPDrawLine(m_ptOld);
            }
            dc->MoveTo(m_ptClickDown);
            dc->MPDrawLine(point);
            break;

        case LINE_BH:
            if (m_bMouseMove)
            {
                dc->MoveTo(m_ptClickDown);
                dc->BHDrawLine(m_ptOld);
            }
            dc->MoveTo(m_ptClickDown);
            dc->BHDrawLine(point);
            break;

        case _3D_DIMETRIC:
            rcClient.left   = m_ptClickDown.x;
            rcClient.top    = m_ptClickDown.y;
            if (m_bMouseMove)
            {
                rcClient.right  = m_ptOld.x;
                rcClient.bottom = m_ptOld.y;
                dc->Draw3DDimetric(&rcClient);
            }
            rcClient.right  = point.x;
            rcClient.bottom = point.y;
            dc->Draw3DDimetric(&rcClient);
            break;
        }

        QueryPerformanceCounter(&lStopCounter);
        ((CMainFrame*)GetParentFrame())->ShowElapsedTime(
            (lStopCounter.QuadPart - lStartCounter.QuadPart) * 1000.0 / m_lFrequency.QuadPart);

        m_ptOld = point;
        m_bMouseMove = TRUE;
        ::ReleaseDC(m_hWnd, dc->m_hDC);
    }

    CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    SetCapture();
    m_bLeftButtonDown = TRUE;
    m_ptOld = m_ptClickDown = point;
    if (m_uiShape == CROP_ENCODE)
    {
        if (m_uiClipCnt != 2)
        {
            m_ptCrop[m_uiClipCnt++] = point;
        }
        Invalidate();
    }
    else
        m_uiClipCnt = 0;
    CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (GetCapture() == this)
    {
        ReleaseCapture();
    }

    if (m_bLeftButtonDown)
    {
        m_bMouseMove      = FALSE;
        m_bLeftButtonDown = FALSE;
        ClipCursor(NULL);
    }

    if (m_uiShape != NONE)
    {
        CMyDC *dc = (CMyDC *)GetDC();
        LARGE_INTEGER lStartCounter, lStopCounter;

        QueryPerformanceCounter(&lStartCounter);

        switch (m_uiShape)
        {
        case FILL_RECT:
            dc->FenceFillRectangle(&m_rcFill);
            break;
        }

        QueryPerformanceCounter(&lStopCounter);
        ((CMainFrame*)GetParentFrame())->ShowElapsedTime(
            (lStopCounter.QuadPart - lStartCounter.QuadPart) * 1000.0 / m_lFrequency.QuadPart);

        ::ReleaseDC(m_hWnd, dc->m_hDC);
    }

    CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnUpdateMenu(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck((pCmdUI->m_nID - ID_CIRCLE_MP + 1) == m_uiShape);
}

void CChildView::OnSetShape(UINT nID)
{
    m_uiShape = nID - ID_CIRCLE_MP + 1;
    if (m_uiShape != CROP_ENCODE)
    {
        m_uiClipCnt = 0;
    }

    Invalidate();
}

BOOL CChildView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
    SetCursor(m_hCursor);
    return TRUE;
}
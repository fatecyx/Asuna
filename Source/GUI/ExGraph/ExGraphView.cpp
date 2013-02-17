// ExGraphView.cpp : implementation of the CExGraphView class
//

#include "stdafx.h"
#include "ExGraph.h"

#include "ExGraphDoc.h"
#include "ExGraphView.h"
#include "Ellipse.h"
#include "Shape.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum
{
	PENCIL,
	LINE,
	ELLIPSE,
	POLY,
	CLEAR,
	NONE
};

/////////////////////////////////////////////////////////////////////////////
// CExGraphView

IMPLEMENT_DYNCREATE(CExGraphView, CView)

BEGIN_MESSAGE_MAP(CExGraphView, CView)
	//{{AFX_MSG_MAP(CExGraphView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_DRAW_CLEAR, OnDrawClear)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND_RANGE(ID_DRAW_PENCIL, ID_DRAW_POLY, CExGraphView::OnMyDraw)
	ON_UPDATE_COMMAND_UI_RANGE(ID_DRAW_PENCIL, ID_DRAW_POLY, CExGraphView::OnUpdateDrawMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExGraphView construction/destruction

CExGraphView::CExGraphView()
{
	// TODO: add construction code here
	m_uiShape		= NONE;
	m_bPolyStart	=
	m_bPolyEnd		=
	m_bLBnDown		=
	m_bMouseMove	= false;
}

CExGraphView::~CExGraphView()
{
}

BOOL CExGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExGraphView drawing

void CExGraphView::OnDraw(CDC* pDC)
{
	CExGraphDoc* pDoc = GetDocument();
	CPen	*pOldPen, cpPen;
	CBrush	cbBrush, *pOldBrush;

	cpPen.CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
	cbBrush.CreateSolidBrush(RGB(0, 255, 0));
	pOldPen = (CPen *)pDC->SelectObject(&cpPen);
	pOldBrush = (CBrush *)pDC->SelectObject(&cbBrush);

//	pOldBrush = (CBrush *)pDC->SelectStockObject(HOLLOW_BRUSH);

	for (INT_PTR ix = 0, iSize = pDoc->m_oaShapes.GetSize(); ix != iSize; ++ix)
	{
		((CShape *)pDoc->m_oaShapes[ix])->DrawAll(pDC);
	}

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

/////////////////////////////////////////////////////////////////////////////
// CExGraphView printing

BOOL CExGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExGraphView message handlers

void CExGraphView::OnMyDraw(UINT nID)
{
	switch (nID)
	{
	case LINE:
		break;
	case ELLIPSE:
		break;
	}
	m_uiShape = nID - ID_DRAW_PENCIL;
}

void CExGraphView::OnUpdateDrawMenu(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID - ID_DRAW_PENCIL == m_uiShape);
}

void CExGraphView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_uiShape >= PENCIL && m_uiShape < NONE && (nFlags & MK_LBUTTON || m_bPolyStart))
	{
//		CDC			MemDC;
		CRect		crcRect;
		CBitmap		MemBitmap;
		CClientDC	dc(this), MemDC(this);

		CPen	cpPen;

		GetWindowRect(&crcRect);
		crcRect.left += 2;
		crcRect.top  += 2;
		--crcRect.right;
		--crcRect.bottom;
		ClipCursor(&crcRect);

		MemDC.CreateCompatibleDC(NULL);
		MemBitmap.CreateCompatibleBitmap(&dc, crcRect.Width(), crcRect.Height());
		MemDC.SelectObject(&MemBitmap);
		MemDC.BitBlt(0, 0, crcRect.Width(), crcRect.Height(), &dc, 0, 0, SRCCOPY);

		cpPen.CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
		MemDC.SelectObject(&cpPen);

		MemDC.SelectStockObject(HOLLOW_BRUSH);
		SetROP2(MemDC, R2_NOTXORPEN);

		if (nFlags & MK_LBUTTON && m_cpOldPoint != point)
		{
			switch (m_uiShape)
			{
			case PENCIL:
				MemDC.MoveTo(m_cpOldPoint);
				MemDC.LineTo(point);
				GetDocument()->m_Pencils.Add(point);
				break;
			case LINE:
				if (m_bMouseMove)
				{
					MemDC.MoveTo(m_cpClickDown);
					MemDC.LineTo(m_cpOldPoint);
				}
				MemDC.MoveTo(m_cpClickDown);
				MemDC.LineTo(point);
				break;
			case ELLIPSE:
				if (m_bMouseMove)
				{
					MemDC.Ellipse(&m_crcRect);
				}
				m_crcRect = CRect(m_cpClickDown.x, m_cpClickDown.y, point.x, point.y);
				MemDC.Ellipse(&m_crcRect);
				break;
			}
		}
/*		else if (!nFlags)
		{
			if (m_uiShape == POLY)
			{
				MemDC.MoveTo(m_cpPriorClickDown);
				MemDC.LineTo(m_cpOldPoint);
			}
		}
*/
		dc.BitBlt(0, 0, crcRect.Width(), crcRect.Height(), &MemDC, 0, 0, SRCCOPY);
		MemBitmap.DeleteObject();
		MemDC.DeleteDC();
		m_cpOldPoint = point;
		m_bMouseMove = true;
	} // m_uiShape in range
	CView::OnMouseMove(nFlags, point);
}

void CExGraphView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_cpOldPoint = m_cpClickDown = point;
	m_bLBnDown = true;
	switch (m_uiShape)
	{
/*	case POLY:
		if (m_bPolyEnd == false)
			m_cpPriorClickDown = point;
		break;
*/	case PENCIL:
		GetDocument()->m_Pencils.Add(point);
		break;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CExGraphView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (GetCapture() == this)
	{
		ReleaseCapture();
	}
	ClipCursor(NULL);
	if (m_bLBnDown)
	{
		m_bLBnDown = false;
		m_bMouseMove = false;

		switch (m_uiShape)
		{
		case ELLIPSE:
			if (!((CExGraphDoc *)m_pDocument)->m_Ellipses.Add(m_crcRect))
			{
				MessageBoxA("Add Ellipse failed.", 0, 0x40);
			}
			break;
		case LINE:
			GetDocument()->m_Lines.Add(m_cpClickDown, point);
			break;
		case PENCIL:
			GetDocument()->m_Pencils.Add(CPoint(-1, -1));
			break;
//		case POLY:
//			m_bPolyEnd = point == m_cpClickDown;
		}
//		Invalidate();
		CRgn rgn;
		GetUpdateRgn(&rgn, TRUE);
		InvalidateRgn(&rgn);
	}
	CView::OnLButtonUp(nFlags, point);
}

void CExGraphView::OnDrawClear()
{
	for (INT_PTR ix = 0, iSize = GetDocument()->m_oaShapes.GetSize(); ix != iSize; ++ix)
	{
		((CShape *)GetDocument()->m_oaShapes[ix])->Clear();
	}
	Invalidate();
}
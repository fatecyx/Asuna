// ExGraphView.h : interface of the CExGraphView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXGRAPHVIEW_H__56DD01AA_BB72_4F8B_B2A8_3208B849BEC7__INCLUDED_)
#define AFX_EXGRAPHVIEW_H__56DD01AA_BB72_4F8B_B2A8_3208B849BEC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CExGraphView : public CView
{
protected: // create from serialization only
	CExGraphView();
	DECLARE_DYNCREATE(CExGraphView)

// Attributes
public:
	CExGraphDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExGraphView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExGraphView();

protected:
	BOOL m_bLBnDown, m_bMouseMove, m_bPolyEnd, m_bPolyStart;
	UINT m_uiShape;
	CRect m_crcRect;
	CPoint m_cpClickDown, m_cpOldPoint, m_cpPriorClickDown;

// Generated message map functions
protected:
	//{{AFX_MSG(CExGraphView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateDrawMenu(CCmdUI* pCmdUI);
	afx_msg void OnDrawClear();
	//}}AFX_MSG
	afx_msg void OnMyDraw(UINT nID);
	DECLARE_MESSAGE_MAP()
};

inline CExGraphDoc* CExGraphView::GetDocument()
{
	return (CExGraphDoc*)m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXGRAPHVIEW_H__56DD01AA_BB72_4F8B_B2A8_3208B849BEC7__INCLUDED_)

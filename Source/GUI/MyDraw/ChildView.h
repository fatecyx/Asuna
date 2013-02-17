// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__BD1E65B6_CB7D_45E2_A535_594468D3F161__INCLUDED_)
#define AFX_CHILDVIEW_H__BD1E65B6_CB7D_45E2_A535_594468D3F161__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

protected:
	BOOL          m_bLeftButtonDown, m_bMouseMove;
	UINT          m_uiShape, m_uiClipCnt;
	RECT          m_rcEllipse, m_rcFill;
	POINT         m_ptClickDown, m_ptOld, m_ptCrop[2];
	HCURSOR       m_hCursor;
	COLORREF      m_crColor;
	LARGE_INTEGER m_lFrequency;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnExit();
	afx_msg void OnColorEdit();
	//}}AFX_MSG
	afx_msg void OnSetShape(UINT nID);
	afx_msg void OnUpdateMenu(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);

protected:
    BOOL EncodeCrop(LPPOINT lptStart, LPPOINT lptEnd, LPRECT lpRect);


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__BD1E65B6_CB7D_45E2_A535_594468D3F161__INCLUDED_)

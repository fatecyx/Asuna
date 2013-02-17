// ExGraph.h : main header file for the EXGRAPH application
//

#if !defined(AFX_EXGRAPH_H__80475910_F174_430F_8CC4_8792D3566FB6__INCLUDED_)
#define AFX_EXGRAPH_H__80475910_F174_430F_8CC4_8792D3566FB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExGraphApp:
// See ExGraph.cpp for the implementation of this class
//

class CExGraphApp : public CWinApp
{
public:
	CExGraphApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExGraphApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CExGraphApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXGRAPH_H__80475910_F174_430F_8CC4_8792D3566FB6__INCLUDED_)

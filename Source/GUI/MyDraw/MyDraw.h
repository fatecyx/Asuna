// MyDraw.h : main header file for the MYDRAW application
//

#if !defined(AFX_MYDRAW_H__06144F79_BAEF_438F_A181_C0C08F52F066__INCLUDED_)
#define AFX_MYDRAW_H__06144F79_BAEF_438F_A181_C0C08F52F066__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyDrawApp:
// See MyDraw.cpp for the implementation of this class
//

class CMyDrawApp : public CWinApp
{
public:
	CMyDrawApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDrawApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CMyDrawApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDRAW_H__06144F79_BAEF_438F_A181_C0C08F52F066__INCLUDED_)

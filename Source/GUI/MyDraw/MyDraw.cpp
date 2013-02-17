// MyDraw.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MyDraw.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDrawApp

BEGIN_MESSAGE_MAP(CMyDrawApp, CWinApp)
	//{{AFX_MSG_MAP(CMyDrawApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDrawApp construction

CMyDrawApp::CMyDrawApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyDrawApp object

CMyDrawApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMyDrawApp initialization

BOOL CMyDrawApp::InitInstance()
{
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	pFrame->SetWindowText(_T("Kaede"));
	pFrame->CenterWindow();
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMyDrawApp message handlers

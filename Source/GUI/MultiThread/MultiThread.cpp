// MultiThread.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MultiThread.h"
#include "MultiThreadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiThreadApp

BEGIN_MESSAGE_MAP(CMultiThreadApp, CWinApp)
	//{{AFX_MSG_MAP(CMultiThreadApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiThreadApp construction

CMultiThreadApp::CMultiThreadApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMultiThreadApp object

CMultiThreadApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMultiThreadApp initialization

BOOL CMultiThreadApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

	CMultiThreadDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

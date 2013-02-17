// MultiThreadDlg.cpp : implementation file
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
// CMultiThreadDlg dialog

CMultiThreadDlg::CMultiThreadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiThreadDlg::IDD, pParent), m_calc(this), m_display(this), m_sLock(&m_cEvent)
{
	//{{AFX_DATA_INIT(CMultiThreadDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_cEvent.SetEvent();
	m_ul64Number = 0;
}

void CMultiThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiThreadDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CalcThread::InitInstance()
{
	return TRUE;
}

BOOL DisplayThread::InitInstance()
{
	return TRUE;
}

int CalcThread::Run()
{
	bool	bSync;
	CSingleLock sLock(&(m_pParent->m_cEvent));

	while (1)
	{
		bSync = (m_pParent->IsDlgButtonChecked(IDC_SYNC) == BST_CHECKED);
		if (bSync)
		{
			sLock.Lock();
		}
		++m_pParent->m_ul64Number;
		if (m_pParent->IsDlgButtonChecked(IDC_INC) == BST_CHECKED)
		{
			m_pParent->m_ListBox->InsertString(0, TEXT("Increment"));
		}
		Sleep(0);
		if (bSync)
		{
			m_pParent->m_cEvent.SetEvent();
			sLock.Unlock();
		}
	}
	return 0;
}

int DisplayThread::Run()
{
	bool	bSync;
	CString strNumber;
	CSingleLock sLock(&(m_pParent->m_cEvent));

	while (1)
	{
		bSync = (m_pParent->IsDlgButtonChecked(IDC_SYNC) == BST_CHECKED);
		if (bSync)
		{
			sLock.Lock();
		}
		strNumber.Format("%I64u", m_pParent->m_ul64Number);
		m_pParent->m_ListBox->InsertString(0, strNumber);
		m_pParent->m_ListBox->DeleteString(50);
		Sleep(100);
		if (bSync)
		{
			m_pParent->m_cEvent.SetEvent();
			sLock.Unlock();
		}
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CMultiThreadDlg, CDialog)
	//{{AFX_MSG_MAP(CMultiThreadDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_PAUSE, IDC_SYNC, CMultiThreadDlg::OnButtonPause)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiThreadDlg message handlers

BOOL CMultiThreadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_ListBox = (CListBox *)GetDlgItem(IDC_LIST1);
	m_calc.CreateThread();
	m_display.CreateThread();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMultiThreadDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMultiThreadDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMultiThreadDlg::OnButtonPause(UINT nID)
{
	switch (nID)
	{
	case IDC_PAUSE:
		if (IsDlgButtonChecked(nID) == BST_CHECKED)
		{
			m_calc.SuspendThread();
			m_display.SuspendThread();
		}
		else
		{
			m_display.ResumeThread();
			m_calc.ResumeThread();
		}
		break;
	}
}
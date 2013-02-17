// MultiThreadDlg.h : header file
//

#if !defined(AFX_MULTITHREADDLG_H__CE315956_B935_47EE_A03F_F8D7509DCFEF__INCLUDED_)
#define AFX_MULTITHREADDLG_H__CE315956_B935_47EE_A03F_F8D7509DCFEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>

/////////////////////////////////////////////////////////////////////////////
// CMultiThreadDlg dialog

class CMultiThreadDlg;
class CalcThread : public CWinThread
{
public:
	CalcThread(CMultiThreadDlg *Parent) {m_pParent = Parent;}

protected:
	CMultiThreadDlg *m_pParent;

protected:
	virtual int Run();
	virtual BOOL InitInstance();
};

class DisplayThread : public CWinThread
{
public:
	DisplayThread(CMultiThreadDlg *Parent) {m_pParent = Parent;}

protected:
	CMultiThreadDlg *m_pParent;

protected:
	virtual int Run();
	virtual BOOL InitInstance();
};

class CMultiThreadDlg : public CDialog
{
// Construction
public:
	CMultiThreadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMultiThreadDlg)
	enum { IDD = IDD_MULTITHREAD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiThreadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

public:
	ULONG64		m_ul64Number;
	CEvent		m_cEvent;
	CListBox	*m_ListBox;
	CSingleLock	m_sLock;

protected:
	HICON m_hIcon;
	CalcThread		m_calc;
	DisplayThread	m_display;

	// Generated message map functions
	//{{AFX_MSG(CMultiThreadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonPause(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTITHREADDLG_H__CE315956_B935_47EE_A03F_F8D7509DCFEF__INCLUDED_)

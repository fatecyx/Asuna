#if !defined(AFX_SARCALCDLG_H__39841C54_08F7_4C95_B9A2_51A4ED0A7E62__INCLUDED_)
#define AFX_SARCALCDLG_H__39841C54_08F7_4C95_B9A2_51A4ED0A7E62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CSarCalcDlg : public CDialog
{
public:
	CSarCalcDlg(CWnd* pParent = NULL);
	enum { IDD = IDD_SARCALC_DIALOG };
	
protected:
//	HICON m_hIcon;
	int srcx,srcy,dstx,dsty,
		Status1,Status2,Status3,Status4;

//	virtual void DoDataExchange(CDataExchange* pDX);
//	virtual BOOL OnInitDialog();
//	afx_msg void On_start();
//	afx_msg void OnTimer(UINT nIDEvent);
//	afx_msg void OnPaint();
//	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	DECLARE_MESSAGE_MAP()
};

#endif

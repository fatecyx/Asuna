// 3rdDlg.h : header file
//

#include "afxwin.h"
#if !defined(AFX_3RDDLG_H__0D66488D_68E1_47F6_B55C_13C14338CA96__INCLUDED_)
#define AFX_3RDDLG_H__0D66488D_68E1_47F6_B55C_13C14338CA96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CMy3rdDlg : public CDialog
{
public:
	CMy3rdDlg(CWnd* pParent = NULL);
	enum { IDD = IDD_MY3RD_DIALOG };
	void GetHeroName();

protected:
	virtual BOOL OnInitDialog();
	afx_msg void On_start();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void On_stop();
//	void OnDestroy();
	HANDLE hProcess;
	bool AddedName,Ready_To_Get;
	WORD HeroID,HeroNum;
	DWORD NameAdd,NameAdd_Tmp,MovNameAdd;
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnCbnSelchangeHeronames();
//	afx_msg void OnCbnSelchangeSkill_1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedWriteSkillData();
};

#endif

// 3rdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "3rd.h"
#include "3rdDlg.h"
#include "Name.h"

#pragma comment(linker,"/ALIGN:4096")

CMy3rdDlg::CMy3rdDlg(CWnd* pParent)
: CDialog(CMy3rdDlg::IDD, pParent)
{
}

BEGIN_MESSAGE_MAP(CMy3rdDlg, CDialog)
ON_WM_TIMER()
//ON_WM_DESTROY()
ON_CBN_SELCHANGE(HeroNames, CMy3rdDlg::OnCbnSelchangeHeronames)
ON_BN_CLICKED(ReadSkillData, CMy3rdDlg::OnBnClickedButton1)
ON_BN_CLICKED(WriteSkillData, CMy3rdDlg::OnBnClickedWriteSkillData)
END_MESSAGE_MAP()

BOOL CMy3rdDlg::OnInitDialog()
{
	NameAdd = 0xFFFFFFFF;
	Ready_To_Get = FALSE;
	HeroNum = 0;
	AddedName = 0;
	HeroID =  0xFFFF;
	CComboBox *pCtrl;
	for(int Skill_ID = 1011;Skill_ID != 1019;++Skill_ID)
	{
		pCtrl = (CComboBox *)GetDlgItem(Skill_ID);
		for(BYTE ix = 0;ix != 0x1D;++ix)
		{
			pCtrl->AddString(_T(Name[ix].c_str()));
		}
		pCtrl = (CComboBox *)GetDlgItem(Skill_ID + 20);
		pCtrl->AddString(_T(" "));
		pCtrl->AddString(_T("初级"));
		pCtrl->AddString(_T("中级"));
		pCtrl->AddString(_T("高级"));
	}
	On_start();
	return TRUE;
}

void CMy3rdDlg::On_start()
{
	SetTimer(1,50,NULL);
	SetTimer(2,500,NULL);
}

void CMy3rdDlg::OnTimer(UINT nIDEvent)
{
	HWND hWnd =::FindWindow("魔法门之英雄无敌III",NULL);
	if(hWnd == NULL) hWnd =::FindWindow("Heroes III",NULL);
	DWORD openProcId;
	GetWindowThreadProcessId(hWnd,&openProcId);	
	hProcess = OpenProcess(PROCESS_ALL_ACCESS|PROCESS_TERMINATE|PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE,FALSE,openProcId);
	if(hWnd != NULL)
	{
		switch(nIDEvent)
		{
		case 1:((CComboBox *)GetDlgItem(HeroNames))->EnableWindow(1);
		       ((CComboBox *)GetDlgItem(ReadSkillData))->EnableWindow(1);
			   ((CComboBox *)GetDlgItem(WriteSkillData))->EnableWindow(1);
			   {
				   for(int itemix = 0;itemix != 8;++itemix)
				   {
					   ((CComboBox *)GetDlgItem(Skill_1 + itemix))->EnableWindow(1);
					   ((CComboBox *)GetDlgItem(SkillLevel_1 + itemix))->EnableWindow(1);
				   }
			   }
			   if(AddedName == 0 && Ready_To_Get)
			   {
				   GetHeroName();
			   }
			   break;
		case 2:ReadProcessMemory(hProcess,LPVOID(0x56C39A),&MovNameAdd,0x4,NULL);
		       if(MovNameAdd == 0xCCCCCCCC)
			   {
				   WriteProcessMemory(hProcess,(void*)(0x56C555),(void*)&(MovNameAdd = 0xFFFE40E9),4,NULL);
				   WriteProcessMemory(hProcess,(void*)(0x56C558),(void*)&(MovNameAdd = 0x9090FFFF),4,NULL);
				   WriteProcessMemory(hProcess,(void*)(0x56C39A),(void*)&(MovNameAdd = 0xFF2242C6),4,NULL);
				   WriteProcessMemory(hProcess,(void*)(0x56C39E),(void*)&(MovNameAdd = 0x84B000A3),4,NULL);
				   WriteProcessMemory(hProcess,(void*)(0x56C3A2),(void*)&(MovNameAdd = 0x01B4E900),4,NULL);
				   WriteProcessMemory(hProcess,(void*)(0x56C3A6),(void*)&(MovNameAdd = 0),2,NULL);
			   }
			   ReadProcessMemory(hProcess,LPVOID(0x84B000),&NameAdd_Tmp,0x4,NULL);
			   if(NameAdd_Tmp != 0 && NameAdd != NameAdd_Tmp)
				   NameAdd = NameAdd_Tmp;
			   else if(NameAdd_Tmp != 0)
			   {
				   NameAdd -= 0x2C564;
				   Ready_To_Get = TRUE;
				   KillTimer(2);
			   }
		}
	}
	else
	{
		((CComboBox *)GetDlgItem(ReadSkillData))->EnableWindow(0);
		((CComboBox *)GetDlgItem(WriteSkillData))->EnableWindow(0);
		while(HeroNum)
			((CComboBox *)GetDlgItem(HeroNames))->DeleteString(--HeroNum);
		if(Ready_To_Get == TRUE)
		{
			SetTimer(2,500,NULL);
			Ready_To_Get = FALSE;
		}
		AddedName = 0;
		NameAdd = 0xFFFFFFFF;
		HeroID = 0xFFFF;
	}
	CDialog::OnTimer(nIDEvent);
}

void CMy3rdDlg::GetHeroName()
{
	size_t ix = 0;
	CComboBox *pCtrl = (CComboBox *)GetDlgItem(HeroNames);
	for(ix = 0;;++ix)
	{
		char *HeroName=new char[0x0D];
		ReadProcessMemory(hProcess,LPVOID(NameAdd + 0x492 * ix),HeroName,0x0D,NULL);
		if(*HeroName == 0)
		{
			delete []HeroName;
			if(ix == 0)	return;
			else
			{
				pCtrl->DeleteString(ix - 1);
				break;
			}
		}
		pCtrl->AddString(_T(HeroName));
		++HeroNum;
		delete []HeroName;
	}
	AddedName = 1;
}
/*
void CMy3rdDlg::OnDestroy() 
{
	CDialog::OnDestroy();	
}
*/
void CMy3rdDlg::OnCbnSelchangeHeronames()
{
	HeroID=((CComboBox *)GetDlgItem(HeroNames))->GetCurSel();
}

void CMy3rdDlg::OnBnClickedButton1()
{
	if(HeroID == 0xFFFF) return;
	SetWindowText("Damn You!");
	BYTE Skill_ID,Skill_Level,HeroLevel,HeroJob;
	CComboBox *pCtrl;
	for(BYTE itemix = 0;itemix != 8;++itemix)
	{
		pCtrl = (CComboBox *)GetDlgItem(Skill_1 + itemix);
		pCtrl->SetCurSel(0);
		pCtrl = (CComboBox *)GetDlgItem(SkillLevel_1 + itemix);
		pCtrl->SetCurSel(0);
	}
	for(BYTE ix = 0;ix != 0x1C;++ix)
	{
		ReadProcessMemory(hProcess,LPVOID(NameAdd + HeroID * 0x492 + 0xC2 + ix),&Skill_ID,1,NULL);
		ReadProcessMemory(hProcess,LPVOID(NameAdd + HeroID * 0x492 + 0xA6 + ix),&Skill_Level,1,NULL);
		if(Skill_ID > 0 && Skill_ID < 9)
		{
			pCtrl = (CComboBox *)GetDlgItem(Skill_1 + Skill_ID - 1);
			pCtrl->SetCurSel(ix + 1);
			pCtrl = (CComboBox *)GetDlgItem(SkillLevel_1 + Skill_ID - 1);
			pCtrl->SetCurSel(Skill_Level);
		}
	}
	ReadProcessMemory(hProcess,LPVOID(NameAdd + HeroID * 0x492 + 0x32),&HeroLevel,1,NULL);
	ReadProcessMemory(hProcess,LPVOID(NameAdd + HeroID * 0x492 + 0x0D),&HeroJob,1,NULL);
	SetDlgItemInt(Hero_Level,HeroLevel);
	if(HeroJob < 12)
		SetDlgItemText(Hero_Job,Job[HeroJob].c_str());
}

void CMy3rdDlg::OnBnClickedWriteSkillData()
{
	if(HeroID == 0xFFFF) return;
	string zero (0x37,0);
	BYTE SelSkill,SelSkillLv,SkillNum = 0,SkillLocate,HeroLevel;
//	CString a;
	WriteProcessMemory(hProcess,(void *)(NameAdd + HeroID * 0x492 + 0xA6),
		               (void*)zero.c_str(),zero.size(),NULL);
	for(size_t ix = 0;ix != 8;++ix)
	{
		SelSkill=((CComboBox *)GetDlgItem(Skill_1 + ix))->GetCurSel();
		SelSkillLv=((CComboBox *)GetDlgItem(SkillLevel_1 + ix))->GetCurSel();
		if(SelSkill == 0) continue;
/*		a.Format("%X---%s\n技能位置:%X=%X\n技能等级:%X=%X",
			     SelSkill,Name[SelSkill].c_str(),
			     NameAdd + HeroID * 0x492 + 0xC2 + SelSkill - 1,ix+1,
				 NameAdd + HeroID * 0x492 + 0xA6 + SelSkill - 1,SelSkillLv);
		MessageBox(a);
*/		++SkillNum;
		WriteProcessMemory(hProcess,(void*)(NameAdd + HeroID * 0x492 + 0xC2 + SelSkill - 1),
			(void*)&(SkillLocate = ix+1),1,NULL);
		WriteProcessMemory(hProcess,(void*)(NameAdd + HeroID * 0x492 + 0xA6 + SelSkill - 1),
			(void*)&SelSkillLv,1,NULL);
	}
//	a.Format("技能数量:%X",SkillNum);
//	MessageBox(a);
	HeroLevel = GetDlgItemInt(Hero_Level,NULL);
	if(HeroLevel > 99) HeroLevel = 99;
	WriteProcessMemory(hProcess,(void*)(NameAdd + HeroID * 0x492 + 0xDE),(void*)&SkillNum,1,NULL);
	WriteProcessMemory(hProcess,(void*)(NameAdd + HeroID * 0x492 + 0x32),(void*)&HeroLevel,1,NULL);
}
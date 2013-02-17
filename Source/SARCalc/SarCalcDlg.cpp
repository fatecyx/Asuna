#include "stdafx.h"
#include "SarCalc.h"
#include "SarCalcDlg.h"

#pragma comment(linker,"/ALIGN:4096")


/////////////////////////////////////////////////////////////////////////////

CSarCalcDlg::CSarCalcDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSarCalcDlg::IDD, pParent)
{
}
BEGIN_MESSAGE_MAP(CSarCalcDlg, CDialog)
ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

void CSarCalcDlg::OnButton1() 
{
	srcx=GetDlgItemInt(SrcX,&Status1);
	srcy=GetDlgItemInt(SrcY,&Status2);
	dstx=GetDlgItemInt(DstX,&Status3);
	dsty=GetDlgItemInt(DstY,&Status4);
	if(Status1&&Status2&&Status3&&Status4&&srcx&&srcy&&dstx&&dsty)
	{
		dstx *= srcy,dsty *= srcx;
		int temp1 = dstx,temp2 = dsty;
		while(temp2)
		{
			int temp = temp2;
			temp2 = temp1 % temp2;
			temp1 = temp;
		}
		dstx /= temp1;
		dsty /= temp1;
		SetDlgItemInt(SarX,dstx);
		SetDlgItemInt(SarY,dsty);
	}
}

#include<windows.h>
#include<string>
using namespace std;
#include"plugin.h"
#include"resource.h"

#define CPUDUMP 0
#define CPUSTACK 1
#define WM_MOUSEWHEEL 0x020A 

static HINSTANCE hin;
static HWND hwnd,edhwnd;
static char name[]="OllyGal";
static char classname[32];
char note[64];
DWORD pagecode;
DWORD changetype;
WNDPROC OldListProc,OldEditProc1,OldEditProc2;

HWND odghwnd;

void GetCallAddress(HWND hWnd)
{
	DWORD addr = Plugingetvalue(VAL_CPUDASM);
	addr = *(int*)(addr+0x385);
	DWORD mask=0xffff0000;
	DWORD base = addr&mask;
	IMAGE_DOS_HEADER dosh;
	char s[64];
	Readmemory(&dosh,base,sizeof(IMAGE_DOS_HEADER),MM_RESTORE | MM_SILENT);
	while(dosh.e_magic!=IMAGE_DOS_SIGNATURE||mask==0)
	{		
		mask<<=1;
		base = addr&mask;
		Readmemory(&dosh,base,sizeof(IMAGE_DOS_HEADER),MM_SILENT);
	}
	if(base==0) return;

	DWORD pebase = base;
	
	base+=dosh.e_lfanew+sizeof(IMAGE_NT_SIGNATURE)+sizeof(IMAGE_FILE_HEADER)+sizeof(IMAGE_OPTIONAL_HEADER);
	IMAGE_SECTION_HEADER sh;
	Readmemory(&sh,base,sizeof(IMAGE_SECTION_HEADER),MM_SILENT);
	while(sh.VirtualAddress!=0)
	{
		if( sh.VirtualAddress+pebase<addr&&sh.VirtualAddress+sh.SizeOfRawData+pebase>addr)
			break;
		base+=sizeof(IMAGE_SECTION_HEADER);
		Readmemory(&sh,base,sizeof(IMAGE_SECTION_HEADER),MM_SILENT);
	}
	if(sh.VirtualAddress==0)return;
	base = pebase+sh.VirtualAddress;
	DWORD size = sh.SizeOfRawData;
	char *data = new char [size];
	Readmemory(data,base,size,MM_SILENT);
	//				sprintf(s,"0x%08x 0x%08x 0x%08x",base,pebase,addr);
//				MessageBox(hWnd,s,s,0);
	for(int i=0,j=0;i<size;i++)
	{
//		if(data[i]==0xe8)
//		{
//			sprintf(s,"0x%08x 0x%08x 0x%08x",*(DWORD*)(data+i+1),pebase,addr);
//				MessageBox(hWnd,s,s,0);
		if(*(DWORD*)(data+i) == (addr-base-i-4))
		{
				
			if(data[i-1]==0xe8||data[i-1]==0xcc)
			{
				DWORD target = base+i-1;
				sprintf(s,"0x%08x",target);
				if(data[i-1]==0xcc)
					target|=0x80000000;
				
				SendMessage(hWnd,LB_INSERTSTRING,j,(LPARAM)s);
				SendMessage(hWnd,LB_SETITEMDATA,j++,target);
				i+=3;

			}
		}
	}
	sprintf(s,"调用0x%08x的参考",addr);
	SetWindowText((HWND)GetWindowLong(hWnd,GWL_HWNDPARENT),s);
	delete []data;
}


void SetEditText(HWND hWnd,DWORD type)
{
	DWORD  temp,t1,t2,i;
	char *info;
	wchar_t *winfo;
	if(type == CPUDUMP)
	{
		__try
		{
			temp = Plugingetvalue(VAL_CPUDDUMP);
			t1=*(DWORD*)(temp+0x385);
			t2=*(DWORD*)(temp+0x389);
			temp=t2-t1;
			info = new char [temp+2];
			winfo = new wchar_t [temp+2];
			RtlZeroMemory(info,(temp+2)*sizeof(char));
			RtlZeroMemory(winfo,(temp+2)*sizeof(wchar_t));
			Readmemory(info,(DWORD)t1,temp,MM_SILENT);
			for(i=0;i<temp;i++)
			{
				if(info[i]==0)
				{
					if(info[i+1]==0)
					{
					info[i]=0x0d;
					info[++i]=0x0a;
					}
					else
						info[i]=' ';
				}
			}
			MultiByteToWideChar(pagecode,0,info,-1,winfo,temp+2);
			SetWindowTextW(hWnd,winfo);
			delete []info;
			delete []winfo;
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			return;
		}
	}
	else
	{
		temp = Plugingetvalue(VAL_CPUDSTACK	);
		t1 = *(DWORD*)(temp+0x385);
		char tempchar;
		__try
		{
			Readmemory(&t2,t1,4,MM_SILENT);
/*			char s[128] = {0};
			sprintf(s,"0x%08x 0x%08x",t2,info);
			MessageBox(hWnd,s,s,0);*/
			t1 = t2;
			temp=0;
			do
			{
				Readmemory(&tempchar,t2++,1,MM_SILENT);
				++temp;
			}while( tempchar != 0 );
			if(temp==1)
				return;
			info = new char [temp];
			Readmemory(info,t1,temp,MM_SILENT);
			winfo = new wchar_t [temp];
			MultiByteToWideChar(pagecode,0,info,-1,winfo,temp);
			SetWindowTextW(hWnd,winfo);
			delete [] winfo;
			delete [] info;
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			return;
		}
	}
}

void MySetBreakpoint(HWND hWnd,BOOL type)
{
	if(type)
	{
		int index = SendMessage(hWnd,LB_GETCURSEL,0,0);
		int addr  = SendMessage(hWnd,LB_GETITEMDATA,index,0);
		if((addr&0x80000000)==0)
		{
			addr |= 0x80000000;
			SendMessage(hWnd,LB_SETITEMDATA,index,addr);
			Manualbreakpoint(addr&0x7fffffff,VK_F2,0,0,FIXEDFONT);
		}
	}
	else
	{
		int count = SendMessage(hWnd,LB_GETCOUNT,0,0);
		for(int i=0;i<count;i++)
		{
			int addr = SendMessage(hWnd,LB_GETITEMDATA,i,0);
			if((addr&0x80000000) == 0)
			{
				addr |= 0x80000000;
				SendMessage(hWnd,LB_SETITEMDATA,i,addr);
				Manualbreakpoint(addr&0x7fffffff,VK_F2,0,0,FIXEDFONT);
			}
		}
	}
}

void MyDeleteBreakpoint(HWND hWnd,BOOL type)
{
	if(type)
	{
		int index = SendMessage(hWnd,LB_GETCURSEL,0,0);
		int addr = SendMessage(hWnd,LB_GETITEMDATA,index,0);
		if((addr&0x80000000)!=0)
		{
			addr &= 0x7fffffff;
			SendMessage(hWnd,LB_SETITEMDATA,index,addr);
			Manualbreakpoint(addr&0x7fffffff,VK_F2,0,0,FIXEDFONT);
		}
	}
	else
	{
		int count = SendMessage(hWnd,LB_GETCOUNT,0,0);
		for(int i=0;i<count;i++)
		{
			int addr = SendMessage(hWnd,LB_GETITEMDATA,i,0);
			if((addr&0x80000000)!=0)
			{
				addr &= 0x7fffffff;
				SendMessage(hWnd,LB_SETITEMDATA,i,addr);
				Manualbreakpoint(addr&0x7fffffff,VK_F2,0,0,FIXEDFONT);
			}
		}
	}
}


int CALLBACK NewNoteProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,khdc;
	HBITMAP oldbmp,editbmp;
	RECT rect;
	switch(msg)
	{
	case WM_ERASEBKGND:
		hdc=(HDC)wParam;
		editbmp = LoadBitmap(hin,MAKEINTRESOURCE(IDB_BITMAP2));		
		GetClientRect(hWnd,&rect);
		khdc = CreateCompatibleDC( hdc );
		oldbmp = (HBITMAP)SelectObject(khdc,(HGDIOBJ)editbmp);
		BitBlt(hdc,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,khdc,rect.left,rect.top,SRCCOPY);
		SelectObject(khdc,(HGDIOBJ)oldbmp);
		DeleteObject(khdc);
		DeleteObject((HGDIOBJ)editbmp);
		return TRUE;
		break;
	case WM_KEYDOWN:
		if(wParam == VK_RETURN)
		{
			GetWindowText(hWnd,note,64);
			EndDialog((HWND)GetWindowLong(hWnd,GWL_HWNDPARENT),1);
		}
		break;
	case WM_LBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_VSCROLL:
		InvalidateRect(hWnd,NULL,TRUE);
		
	}
	return CallWindowProc(OldEditProc2,hWnd,msg,wParam,lParam);
	
}


int CALLBACK NewEditWindowProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,khdc;
	HBITMAP oldbmp,editbmp;
	RECT rect;
	switch(msg)
	{
	case WM_ERASEBKGND:
		hdc=(HDC)wParam;
		editbmp = LoadBitmap(hin,MAKEINTRESOURCE(IDB_BITMAP2));		
		GetClientRect(hWnd,&rect);
		khdc = CreateCompatibleDC( hdc );
		oldbmp = (HBITMAP)SelectObject(khdc,(HGDIOBJ)editbmp);
		BitBlt(hdc,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,khdc,rect.left,rect.top,SRCCOPY);
		SelectObject(khdc,(HGDIOBJ)oldbmp);
		DeleteObject(khdc);
		DeleteObject((HGDIOBJ)editbmp);
		return TRUE;
	case WM_LBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_VSCROLL:
		InvalidateRect(hWnd,NULL,TRUE);
		
	}
	return CallWindowProc(OldEditProc1,hWnd,msg,wParam,lParam);
	
}

int CALLBACK DlgEditProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,khdc;
	HBITMAP oldbmp,editbmp;
	PAINTSTRUCT paint;
	RECT rect;
	int x,y;
	switch(msg)
	{
	case WM_INITDIALOG:
		GetWindowRect(hWnd,&rect);
		x=GetSystemMetrics(SM_CXMAXIMIZED);
		y=GetSystemMetrics(SM_CYMAXIMIZED);
		MoveWindow(hWnd,(x-rect.right+rect.left)/2,(y-rect.bottom+rect.top)/2,rect.right-rect.left,rect.bottom-rect.top,TRUE);
		OldEditProc1 = (WNDPROC)SetWindowLong(GetDlgItem(hWnd,IDC_EDIT1),GWL_WNDPROC,(long)NewEditWindowProc);
		
		ShowWindow(hWnd,SW_SHOW);
		SetEditText(GetDlgItem(hWnd,IDC_EDIT1),changetype);
		break;
	case WM_CLOSE:
		
		EndDialog(hWnd,0);
		break;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&paint);
		GetClientRect(hWnd,&rect);
		editbmp = LoadBitmap(hin,MAKEINTRESOURCE(IDB_BITMAP2));		
		khdc = CreateCompatibleDC( hdc );
		oldbmp = (HBITMAP)SelectObject(khdc,(HGDIOBJ)editbmp);
		BitBlt(hdc,0,0,rect.right-rect.left,rect.bottom-rect.top,khdc,0,0,SRCCOPY);
		SelectObject(khdc,(HGDIOBJ)oldbmp);
		DeleteObject(khdc);
		DeleteObject((HGDIOBJ)editbmp);
		EndPaint(hWnd,&paint);
		break;
	case WM_CTLCOLOREDIT:
		hdc=(HDC)wParam;
		::SetBkMode(hdc,TRANSPARENT);
		SetTextColor(hdc,RGB(64,32,0));
		return (int)GetStockObject(HOLLOW_BRUSH);
	case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
			case EN_VSCROLL:
			case EN_CHANGE:
				InvalidateRect((HWND)lParam,NULL,TRUE);
				DefWindowProc(hWnd,msg,wParam,lParam);
			}
		}
		break;
	}
	return 0;
}


int CALLBACK NameDlgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,khdc;
	HBITMAP oldbmp,editbmp;
	PAINTSTRUCT paint;
	RECT rect;
	int x,y;
	switch(msg)
	{
	case WM_INITDIALOG:
		GetWindowRect(hWnd,&rect);
		x=GetSystemMetrics(SM_CXMAXIMIZED);
		y=GetSystemMetrics(SM_CYMAXIMIZED);
		MoveWindow(hWnd,(x-rect.right+rect.left)/2,(y-rect.bottom+rect.top)/2,rect.right-rect.left,rect.bottom-rect.top,TRUE);
		OldEditProc2 = (WNDPROC)SetWindowLong(GetDlgItem(hWnd,IDC_EDIT1),GWL_WNDPROC,(long)NewNoteProc);
		
		ShowWindow(hWnd,SW_SHOW);
		SetEditText(GetDlgItem(hWnd,IDC_EDIT1),changetype);
		break;
	case WM_CLOSE:
		
		EndDialog(hWnd,0);
		break;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&paint);
		GetClientRect(hWnd,&rect);
		editbmp = LoadBitmap(hin,MAKEINTRESOURCE(IDB_BITMAP2));		
		khdc = CreateCompatibleDC( hdc );
		oldbmp = (HBITMAP)SelectObject(khdc,(HGDIOBJ)editbmp);
		BitBlt(hdc,0,0,rect.right-rect.left,rect.bottom-rect.top,khdc,0,0,SRCCOPY);
		SelectObject(khdc,(HGDIOBJ)oldbmp);
		DeleteObject(khdc);
		DeleteObject((HGDIOBJ)editbmp);
		EndPaint(hWnd,&paint);
		break;
	case WM_CTLCOLOREDIT:
		hdc=(HDC)wParam;
		::SetBkMode(hdc,TRANSPARENT);
		SetTextColor(hdc,RGB(64,32,0));
		return (int)GetStockObject(HOLLOW_BRUSH);
	case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
			case EN_VSCROLL:
			case EN_CHANGE:
				InvalidateRect((HWND)lParam,NULL,TRUE);
				DefWindowProc(hWnd,msg,wParam,lParam);
			}
		}
		break;
		
	}
	return 0;
}

HMENU MyCreatMenu()
{
	HMENU pophm;
	pophm = CreatePopupMenu();
	AppendMenu(pophm,MF_STRING,200,"转到原地址");
	AppendMenu(pophm,MF_STRING,201,"转到当前参考的地址");
	AppendMenu(pophm,MF_MENUBARBREAK,250,NULL);
	AppendMenu(pophm,MF_STRING,203,"在当前参考上添加断点");
	AppendMenu(pophm,MF_STRING,204,"在当前参考上添加注释");
	AppendMenu(pophm,MF_STRING,205,"删除当前参考上的断点");
	AppendMenu(pophm,MF_STRING,206,"删除当前参考上的注释");
	AppendMenu(pophm,MF_MENUBARBREAK,250,NULL);
	AppendMenu(pophm,MF_STRING,207,"在所有参考上添加断点");
	AppendMenu(pophm,MF_STRING,208,"在所有参考上添加注释");
	AppendMenu(pophm,MF_STRING,209,"删除所有参考上的断点");
	AppendMenu(pophm,MF_STRING,210,"删除所有参考上的注释");
	return pophm;
}

void ShowDisasmAddr(HWND hWnd)
{
	DWORD addr,index;
	index = SendMessage(hWnd,LB_GETCURSEL,0,0);
	addr = SendMessage(hWnd,LB_GETITEMDATA,index,0);
	Setcpu(0,addr&0x7fffffff,0,0,CPU_ASMFOCUS);
	HWND  phWnd = (HWND)GetWindowLong(hWnd,GWL_HWNDPARENT);
	ShowWindow(phWnd,SW_SHOWMINIMIZED);
	SetFocus(odghwnd);
}

void ShowOriAddr(HWND hWnd)
{
	DWORD addr,index,data;
	index = SendMessage(hWnd,LB_GETCURSEL,0,0);
	addr = SendMessage(hWnd,LB_GETITEMDATA,index,0);
	addr &= 0x7fffffff;
	Readmemory(&data,addr+1,4,MM_SILENT);
	addr = data+addr+5;
	Setcpu(0,addr,0,0,CPU_ASMFOCUS);
	HWND  phWnd = (HWND)GetWindowLong(hWnd,GWL_HWNDPARENT);
	ShowWindow(phWnd,SW_SHOWMINIMIZED);
	SetFocus(odghwnd);
}

void FlashListBox(HWND hWnd)
{
	DWORD i,count,addr;
	char data;
	count = SendMessage(hWnd,LB_GETCOUNT,0,0);
	for(i=0;i<count;i++)
	{
		addr = SendMessage(hWnd,LB_GETITEMDATA,i,0);
		Readmemory(&data,addr&0x7fffffff,1,MM_SILENT);
		if(data == 0xcc)
		{
			addr|=0x80000000;
			SendMessage(hWnd,LB_SETITEMDATA,i,addr);
		}
		else
		{
			addr&=0x7fffffff;
			SendMessage(hWnd,LB_SETITEMDATA,i,addr);
		}
	}
}

int CALLBACK NewWindowProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam )
{
	HDC hdc,khdc;
	HBITMAP oldbmp,newbmp;
	RECT rect;
	POINT p;
	HMENU hmenu;
	DWORD addr,index,i,count;
	switch(Msg)
	{
	case WM_ERASEBKGND:
		hdc=(HDC)wParam;
		newbmp = LoadBitmap(hin,MAKEINTRESOURCE(IDB_BITMAP1));	
		GetClientRect(hWnd,&rect);
		khdc = CreateCompatibleDC( hdc );
		oldbmp = (HBITMAP)SelectObject(khdc,(HGDIOBJ)newbmp);
		BitBlt(hdc,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,khdc,rect.left,rect.top,SRCCOPY);
		SelectObject(khdc,(HGDIOBJ)oldbmp);
		DeleteObject(khdc);
		DeleteObject((HGDIOBJ)newbmp);
		FlashListBox(hWnd);
		return TRUE;
	case WM_KEYDOWN:
		if(wParam == VK_RETURN)
			ShowDisasmAddr(hWnd);
		else if(wParam == VK_F2)
		{
			index = SendMessage(hWnd,LB_GETCURSEL,0,0);
			addr = SendMessage(hWnd,LB_GETITEMDATA,index,0);
			addr ^= 0x80000000;
			SendMessage(hWnd,LB_SETITEMDATA,index,addr);
			Manualbreakpoint(addr&0x7fffffff,VK_F2,0,0,FIXEDFONT);
		}
		break;
	case WM_RBUTTONDOWN:
		p.x = lParam&0x0000ffff;
		p.y = lParam>>16;
		ClientToScreen(hWnd,&p);
		hmenu = MyCreatMenu();
		TrackPopupMenu(hmenu,TPM_RIGHTBUTTON,p.x,p.y,0,hWnd,NULL);
		DestroyMenu(hmenu);
		break;
	case WM_LBUTTONDBLCLK:
		ShowDisasmAddr(hWnd);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case 200:
			ShowOriAddr(hWnd);
			break;
		case 201:
			ShowDisasmAddr(hWnd);
			break;
		case 203:
			MySetBreakpoint(hWnd,TRUE);
			break;
		case 204:
			index = SendMessage(hWnd,LB_GETCURSEL,0,0);
			addr = SendMessage(hWnd,LB_GETITEMDATA,index,0);
			if(DialogBox(hin,MAKEINTRESOURCE(IDD_DIALOG4),NULL,NameDlgProc)==1)
			{
				Insertname(addr&0x7fffffff,NM_COMMENT,note);
			}
			break;
		case 205:
			MyDeleteBreakpoint(hWnd,TRUE);
			break;
		case 206:
			index = SendMessage(hWnd,LB_GETCURSEL,0,0);
			addr = SendMessage(hWnd,LB_GETITEMDATA,index,0);
			RtlZeroMemory(note,64);
			Insertname(addr&0x7fffffff,NM_COMMENT,note);
			break;
		case 207:
			MySetBreakpoint(hWnd,FALSE);
			break;
		case 208:
			count = SendMessage(hWnd,LB_GETCOUNT,0,0);
			if(DialogBox(hin,MAKEINTRESOURCE(IDD_DIALOG4),NULL,NameDlgProc)==1)
			{
				for(i=0;i<count;i++)
				{
					addr = SendMessage(hWnd,LB_GETITEMDATA,i,0);
					Insertname(addr&0x7fffffff,NM_COMMENT,note);
				}
			}
			break;
		case 209:
			MyDeleteBreakpoint(hWnd,FALSE);
			break;
		case 210:
			count = SendMessage(hWnd,LB_GETCOUNT,0,0);
			RtlZeroMemory(note,64);
			for(i=0;i<count;i++)
			{
				addr = SendMessage(hWnd,LB_GETITEMDATA,i,0);
				Insertname(addr&0x7fffffff,NM_COMMENT,note);
			}
			break;
		}
	case WM_LBUTTONUP:
	case WM_VSCROLL:
	case WM_MOUSEWHEEL:
		InvalidateRect(hWnd,NULL,TRUE);
	}
	return CallWindowProc(OldListProc,hWnd,Msg,wParam,lParam);
}


int CALLBACK DlgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,khdc;
	HBITMAP oldbmp,newbmp;
	PAINTSTRUCT paint;
	RECT rect;
	char s[32];
	LPDRAWITEMSTRUCT dw;
	int i=0;
	HBRUSH hb;

	switch(msg)
	{
	case WM_INITDIALOG:

		ShowWindow(hWnd,SW_SHOW);
		OldListProc = (WNDPROC)SetWindowLong(GetDlgItem(hWnd,IDC_LIST1),GWL_WNDPROC,(long)NewWindowProc);
//		for(i=0;i<50;i++)
//			SendMessage(GetDlgItem(hWnd,IDC_LIST1),LB_ADDSTRING,0,(LPARAM)s);
//		GetWindowRect(GetDlgItem(hWnd,IDC_LIST1),&rect);
//		InvalidateRect(GetDlgItem(hWnd,IDC_LIST1),&rect,TRUE);
		GetCallAddress(GetDlgItem(hWnd,IDC_LIST1));
		if(SendMessage(GetDlgItem(hWnd,IDC_LIST1),LB_GETCOUNT,wParam,lParam)>0)
			SendMessage(GetDlgItem(hWnd,IDC_LIST1),LB_SETCURSEL,0,0);

		
		break;

	case WM_CLOSE:
		
		EndDialog(hWnd,0);
		break;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&paint);
		newbmp = LoadBitmap(hin,MAKEINTRESOURCE(IDB_BITMAP1));		
		GetClientRect(hWnd,&rect);
		khdc = CreateCompatibleDC( hdc );
		oldbmp = (HBITMAP)SelectObject(khdc,(HGDIOBJ)newbmp);
		BitBlt(hdc,0,0,rect.right-rect.left,rect.bottom-rect.top,khdc,0,0,SRCCOPY);
		SelectObject(khdc,(HGDIOBJ)oldbmp);
		DeleteObject(khdc);
		DeleteObject((HGDIOBJ)newbmp);
		EndPaint(hWnd,&paint);
		
		break;
	case WM_DRAWITEM:
		if(wParam == IDC_LIST1)
		{
			dw = (LPDRAWITEMSTRUCT) lParam;
			SendMessage(dw->hwndItem,LB_GETITEMRECT,dw->itemID,(WPARAM)&rect);
			if(dw->itemState & ODS_SELECTED||dw->itemState)
			{
				hb = CreateSolidBrush(RGB(0xff,0xff,0xff));
				FillRect(dw->hDC,&rect,hb);
				DeleteObject(hb);
			}

//			SendMessage(hWnd,LB_GETITEMDATA,dw->itemID,(LPARAM)s);
			sprintf(s,"0x%08x",(dw->itemData)&0x7fffffff);
			if((dw->itemData&0x80000000)==0)
				SetTextColor(dw->hDC,RGB(0,0,0));
			else
				SetTextColor(dw->hDC,RGB(0xff,0,0));
			TextOut(dw->hDC,rect.left+2,rect.top+2,s,lstrlen(s));

		}

		else		return DefWindowProc(hWnd,msg,wParam,lParam);
		break;
	case WM_CTLCOLORLISTBOX:
		hdc=(HDC)wParam;
		::SetBkMode(hdc,TRANSPARENT);
		SetTextColor(hdc,RGB(64,32,0));
		return (int)GetStockObject(HOLLOW_BRUSH);
		break;
	}
	return 0;
}


int CALLBACK AboutDlgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,khdc;
	HBITMAP aboutbmp,oldbmp;
	PAINTSTRUCT paint;
	RECT rect;
	int x,y;
	switch(msg)
	{
	case WM_INITDIALOG:
		GetWindowRect(hWnd,&rect);
		x=GetSystemMetrics(SM_CXMAXIMIZED);
		y=GetSystemMetrics(SM_CYMAXIMIZED);
		MoveWindow(hWnd,(x-rect.right+rect.left)/2,(y-rect.bottom+rect.top)/2,rect.right-rect.left,rect.bottom-rect.top,TRUE);		
		ShowWindow(hWnd,SW_SHOW);
		break;
	case WM_CLOSE:
		
		EndDialog(hWnd,0);
		break;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&paint);
		aboutbmp=LoadBitmap(hin,MAKEINTRESOURCE(IDB_BITMAP3));
		GetClientRect(hWnd,&rect);
		khdc = CreateCompatibleDC( hdc );
		oldbmp = (HBITMAP)SelectObject(khdc,(HGDIOBJ)aboutbmp);
		BitBlt(hdc,0,0,rect.right-rect.left,rect.bottom-rect.top,khdc,0,0,SRCCOPY);
		SelectObject(khdc,(HGDIOBJ)oldbmp);
		DeleteObject(khdc);
		DeleteObject((HGDIOBJ)aboutbmp);
		EndPaint(hWnd,&paint);
		break;
	case WM_LBUTTONDOWN:
		EndDialog(hWnd,0);
	}
	return 0;
}

BOOL APIENTRY DllMain(HINSTANCE hInstance,DWORD dwReason,LPVOID lpReserved)
{
	if( dwReason == DLL_PROCESS_ATTACH )
	{
		hin=hInstance;

	}
	return TRUE;
}

extc _export cdecl int ODBG_Plugindata(char *shortname)
{
	strcpy(shortname,name);
	return PLUGIN_VERSION;
}



extc _export cdecl int ODBG_Plugininit(int ollydbgversion,HWND hw,ulong *features)
{
	if( ollydbgversion < PLUGIN_VERSION )
		return -1;
	odghwnd = hw;
	Addtolist(0,0,"OllyGAL ver 0.1 powered by fenchang2047");
	return 0;
}

extc _export cdecl int ODBG_Pluginmenu(int origin, char *data, void *item)
{
	switch(origin)
	{
	case PM_MAIN:
		strcpy(data,"0 About");
		return 1;
	case PM_DISASM:
		strcpy(data,"0 查找当前地址的调用");
		return 1;
	case PM_CPUDUMP:
		sprintf(data,
			"0 编码转换{"
            "0 日文编码|1 中文编码|2 About"
             "}");
		return 1;
	case PM_CPUSTACK:
		sprintf(data,
			"0 编码转换{"
            "0 日文编码|1 中文编码|2 About"
             "}");
		return 1;
	}
	return 0;
	
}

extc _export cdecl void ODBG_Pluginaction(int origin, int action, void *item)
{
	
	switch(origin)
	{
	case PM_MAIN:
		switch(action)
		{
		case 0:
			
			DialogBox(hin,MAKEINTRESOURCE(IDD_DIALOG3),NULL,AboutDlgProc);
		}
		break;
	case PM_DISASM:
		switch(action)
		{
		case 0:
			CreateDialog(hin,MAKEINTRESOURCE(IDD_DIALOG1),NULL,DlgProc);
		}
		break;
	case PM_CPUDUMP:
		changetype = CPUDUMP;
		switch(action)
		{
		case 0:
			pagecode = 932;		
			CreateDialog(hin,MAKEINTRESOURCE(IDD_DIALOG2),hwnd,DlgEditProc);
			break;
		case 1:
			pagecode = 936;
			CreateDialog(hin,MAKEINTRESOURCE(IDD_DIALOG2),hwnd,DlgEditProc);
			break;
		case 2:
			DialogBox(hin,MAKEINTRESOURCE(IDD_DIALOG3),NULL,AboutDlgProc);
		}
		break;
	case  PM_CPUSTACK:
		changetype = CPUSTACK;
		switch(action)
		{
		case 0:
			pagecode = 932;		
			CreateDialog(hin,MAKEINTRESOURCE(IDD_DIALOG2),hwnd,DlgEditProc);
			break;
		case 1:
			pagecode = 936;
			CreateDialog(hin,MAKEINTRESOURCE(IDD_DIALOG2),hwnd,DlgEditProc);
			break;
		case 2:
			DialogBox(hin,MAKEINTRESOURCE(IDD_DIALOG3),NULL,AboutDlgProc);
		}
	}
}

extc void _export cdecl ODBG_Plugindestroy(void)
{
    Unregisterpluginclass(classname);
}


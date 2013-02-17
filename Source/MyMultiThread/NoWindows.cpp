/*******************************************************************
	作用	:	让Windows不再Windows
	出处	:	http://bbs.pediy.com/showthread.php?t=84639
	文件名	: 	NoWindows.cpp
	创建时间:	2009-4-7   17:21
	最后修改:	2009-4-8   13:43

	更新历史:	2009-4-7	创建文件
				2009-4-8	WaitForMultipleObjectsEx的第2个参数从CWinThread改成HANDLE
*********************************************************************/

#pragma comment(linker, "/ENTRY:WinMain")
#pragma comment(linker, "/MERGE:.text=.Rimi /SECTION:.Rimi,ERW")
#pragma comment(linker, "/MERGE:.rdata=.Rimi")
#pragma comment(linker, "/MERGE:.data=.Rimi")
#define _AFXDLL

#include <afxwin.h>
#include <afxmt.h>
#include <vector>
using std::vector;

bool bRepeat = true;
HANDLE hEvent[2];

enum
{
	HIDE,
	TIMER,
};

UINT Thread(LPVOID lpParam)
{
	if ( (DWORD)lpParam == HIDE )
	{
		size_t i;
		HWND hWnd;
		vector<HWND> hWndVec;

		while (bRepeat)
		{
			if (hWnd = GetForegroundWindow())		// 获取在最前的窗口句柄
			{
				if (IsWindowVisible(hWnd) && ShowWindow(hWnd, SW_HIDE))			// 如果该窗口可见
				{
					hWndVec.push_back(hWnd);		// 保存该窗口的句柄
//					ShowWindow(hWnd, SW_HIDE);		// 隐藏之
				}
			}
			Sleep(200);
		}
/*		i = hWndVec.size();

		while (i--)
		{
			ShowWindow(hWndVec[i], SW_SHOW);		// 把隐藏过的窗口全部恢复
		}
*/
		for (vector<HWND>::iterator it = hWndVec.begin(); it != hWndVec.end(); ++it)
		{
			ShowWindow(*it, SW_SHOW);
		}
	}
	else
	{
		DWORD dwTimeElapsed = GetTickCount();
		do {}
		while (GetTickCount() - dwTimeElapsed < 30000);		// 30秒后结束
		bRepeat = false;
	}
	SetEvent(hEvent[(DWORD)lpParam]);						// 将对应的事件设为有信号
	return 0;
}

int WINAPI WinMain ( HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nShowCmd )
{
	if (IDOK == MessageBoxA(NULL,
			"Please keep calm, it's just a joke.\n"
			"All will be back after about 30 seconds.",
			"Tip",
			MB_OKCANCEL|MB_ICONASTERISK))
	{
		CWinThread *hThread[2];
		for (BYTE index = 0; index != 1; ++index)
		{
			hEvent[index] = CreateEvent(NULL, TRUE, FALSE, NULL);
			hThread[index] = AfxBeginThread(Thread, LPVOID(index + HIDE));
		}
		WaitForMultipleObjectsEx(sizeof(hEvent) / sizeof(HANDLE), hEvent, TRUE, INFINITE, FALSE);
		MessageBoxA(NULL,
			"I come back, Just a joke, Don't be serious.",
			"Tip",
			MB_ICONASTERISK);
	}
	return 0;
}
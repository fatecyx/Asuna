#pragma comment(linker, "/ENTRY:DllEntryPoint")
#pragma comment(linker,"/MERGE:.text=.Sharu /SECTION:.Sharu,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Sharu")
#pragma comment(linker,"/MERGE:.data=.Sharu")
#pragma comment(lib, "d3d9.lib")

#include <Windows.h>
#include <d3d9.h>
#include "th105.h"

WNDPROC g_lpfnWndFunc;

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	static bool bWrite = false;
	
	if (bWrite == false)
	{
		DWORD dwOld;
		bWrite = true;

		if (VirtualProtect((LPVOID)0x401000, 0x2AC000, PAGE_READWRITE, &dwOld) == FALSE)
		{
			return TRUE;
		}

		*(DWORD *)0x6AC224 = (DWORD)MyShowWindow;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN)
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return CallWindowProc(g_lpfnWndFunc, hWnd, uMsg, wParam, lParam);
}

BOOL MyShowWindow(HWND hWnd, int nCmdShow)
{
	RECT rcClient, rcWindow;
//	g_lpfnWndFunc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)WndProc);
	GetClientRect(hWnd, &rcClient);
	GetWindowRect(hWnd, &rcWindow);
/*	SetWindowPos(hWnd, HWND_TOP, 0, 0, 
		(rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left) + 800, 
		(rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top) + 600, 
		SWP_NOMOVE);
*/	CenterWindow(hWnd);
	return ShowWindow(hWnd, nCmdShow);
}

void CenterWindow(HWND hWnd)
{
	int		x, y;
	RECT	rcGame, rcSys;
	
	SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcSys, 0);
	GetWindowRect(hWnd, &rcGame);
	x = ((rcSys.right - rcSys.left) - (rcGame.right - rcGame.left)) >> 1;
    y = ((rcSys.bottom - rcSys.top) - (rcGame.bottom - rcGame.top)) >> 1;
	SetWindowPos(hWnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
}
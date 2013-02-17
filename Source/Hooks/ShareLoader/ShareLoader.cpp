#pragma comment(linker,"/ENTRY:wWinMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"

/*
DWORD dwAddress[] =
{
	0x509D19,
	0x509D82,
	0x51D51A,
	0x51D633,
	0x508A20,
	0x49B47C,
};
*/
//BYTE bWrite = 0xC3;
PROCESS_INFORMATION pi;
/*
BOOL CALLBACK EnumWindowsProc(HWND hWnd,LPARAM lParam)
{
	if (GetWindowThreadProcessId(hWnd, NULL) == pi.dwThreadId)
	{
		hShareWnd = hWnd;
	}
	return TRUE;
}
*/

Int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWChar lpCmdLine, Int nCmdShow)
{
	HWND hShareWnd;
    STARTUPINFOW si;
    ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(STARTUPINFO);
	if (CreateProcessW(L"Share.exe", NULL, NULL, NULL, 0, 0, NULL, NULL, &si, &pi ))
	{
//		EnumWindows(&EnumWindowsProc,0);
//		SendMessage(hShareWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
//		Sleep(500);
		while (1)
		{
            hShareWnd = FindWindowW(NULL, L"Share EX2" );
			if (hShareWnd != NULL)
				break;

			SleepEx(1, FALSE);
		}
//		for (DWORD dwWriteTimes = sizeof(dwAddress) / 4; dwWriteTimes; bWrite = 0)
//		{
//			WriteProcessMemory(pi.hProcess,
//				(void *)dwAddress[--dwWriteTimes], (void*)&bWrite, 1, NULL);
//		}
		PostMessageW(hShareWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
	}
	return 0;


/*		HWND hWnd;
		DWORD openProcId, Write = 0xC3;
		HANDLE hProcess;
		while (1)
		{
			hWnd =::FindWindow(NULL,"Share EX2");
			GetWindowThreadProcessId(hWnd,&openProcId);
			hProcess = OpenProcess(PROCESS_ALL_ACCESS|PROCESS_TERMINATE|PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE,FALSE,openProcId);
			if (hWnd)
			{
				for (DWORD dwWriteTimes = sizeof(dwAddress) / 4; dwWriteTimes; Write = 0)
				{
					WriteProcessMemory(hProcess,
						(void *)dwAddress[--dwWriteTimes], (void*)&Write, 1, NULL);
				}
				SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
				return 0;
			}
		}
	}
	return 0;

*/
}
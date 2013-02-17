
#pragma comment(linker, "/MERGE:.text=.Rimi /SECTION:.Rimi,ERW")
#pragma comment(linker, "/MERGE:.data=.Rimi")
#pragma comment(linker, "/MERGE:.rdata=.Rimi")
#pragma comment(linker, "/ENTRY:WinMain")
#pragma comment(lib, "ws2_32.lib")

#include <Windows.h>
#include <WinSock.h>
#include "resource.h"

#define WM_SOCKET_NOTIFY WM_USER + 1

char	Buff[16];
HWND	hText, hLog;
enum
{
	ADDLOG,
	ADDTEXT,
};

int CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
int Print(const int iType, const char *szFormat, ...);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmd, int nCmdShow)
{
//	OPENFILENAME ofn = {0};
//	ofn.lStructSize=sizeof(OPENFILENAME);
	// 为什么要调用这个才能正常运行? 不用manifest又正常? 莫名其妙.....
	// 而且只要有一个控件就不能运行...
	GetSaveFileName(0);

	ExitProcess( DialogBox(GetModuleHandle(NULL), 
				MAKEINTRESOURCE(IDD_DIALOG), 
				NULL, 
				DialogProc) );
}

int CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int					iError;
	WORD				wEvent, wError;
	WSADATA				wsaData;
	static HWND			hwndBn;
	static SOCKET		Sock;
	static SOCKADDR_IN	sa = {0};

	switch (uMsg)
	{
	case WM_INITDIALOG:
		hLog   = GetDlgItem(hwndDlg, IDC_LOG);
		hText  = GetDlgItem(hwndDlg, IDC_TEXT);
		hwndBn = GetDlgItem(hwndDlg, IDC_START);
		SendMessage(hwndDlg, WM_SETICON, ICON_BIG,
			(LPARAM)LoadIcon(NULL, IDI_APPLICATION));
		SendMessage(hwndDlg, WM_COMMAND, IDC_START, lParam);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			PostMessage(hwndDlg, WM_CLOSE, wParam, lParam);
			return TRUE;

		case IDC_CLEAR_LOG:
			SendMessage(hLog, LB_RESETCONTENT, 0, 0);
			return TRUE;

		case IDC_CLEAR_TEXT:
			SendMessage(hText, EM_SETSEL, 0, -1);
			SendMessage(hText, EM_REPLACESEL, false, (LPARAM)"");
			return TRUE;

		case IDC_START:
			if (iError = WSAStartup(2, &wsaData))
			{
				Print(ADDLOG, "Startup error. Error code: %i", iError);
				return TRUE;
			}

			Print(ADDLOG, "%s", wsaData.szDescription);
			Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (Sock == INVALID_SOCKET)
			{
				Print(ADDLOG, "Socket createtion error. Error code: %i", WSAGetLastError());
				WSACleanup();
				return TRUE;
			}

			sa.sin_family		= AF_INET;
			sa.sin_port			= htons(23);
			sa.sin_addr.s_addr	= htons(INADDR_ANY);

			if ( bind(Sock, (PSOCKADDR)&sa, sizeof(sa)) )
			{
				Print(ADDLOG, "Bind error. Error code: %i", WSAGetLastError());
				closesocket(Sock);
				WSACleanup();
				return TRUE;
			}

			if (listen(Sock, SOMAXCONN))
			{
				Print(ADDLOG, "Listen error. Error code: %i", WSAGetLastError());
				closesocket(Sock);
				WSACleanup();
				return TRUE;
			}

			if ( WSAAsyncSelect(Sock,
							   hwndDlg,
							   WM_SOCKET_NOTIFY,
							   FD_ACCEPT | FD_READ | FD_CLOSE) )
			{
				Print(ADDLOG, "WSAAsyncSelect error. Error code: %i", WSAGetLastError());
				closesocket(Sock);
				WSACleanup();
				return TRUE;
			}

			SetDlgItemText(hwndDlg, IDC_START, "&Stop");
			SetWindowLong(hwndBn, GWL_ID, IDC_STOP);
			return TRUE;

		case IDC_STOP:
			closesocket(Sock);
			WSACleanup();
			*(DWORD *)(sa.sin_zero)     = 0;
			*(DWORD *)(sa.sin_zero + 4) = 0;
			Print(ADDLOG, "Sock is closed.");
			SetDlgItemText(hwndDlg, IDC_STOP, "&Start");
			SetWindowLong(hwndBn, GWL_ID, IDC_START);
			return TRUE;
		}
		break;

	case WM_SOCKET_NOTIFY:
		wError = WSAGETSELECTERROR(lParam);		// HIWORD
		wEvent = WSAGETSELECTEVENT(lParam);		// LOWORD

		switch (wEvent)
		{
		case FD_ACCEPT:
			if (wError)
			{
				Print(ADDLOG, "Accept error. Error code: %i", WSAGetLastError());
				return TRUE;
			}

			{
				int			iAddrLen;
				SOCKET		client;
				SOCKADDR_IN	saAddrIn;

				client = accept(Sock, (PSOCKADDR)&saAddrIn, &iAddrLen);
				if (client == SOCKET_ERROR)
				{
					Print(ADDLOG, "accept error. Error code: %i", WSAGetLastError());
					return TRUE;
				}

				Print(ADDLOG, "%i connected.", client);
//				recv(wParam, Buff, 1, MSG_PEEK);
			}
			return TRUE;

		case FD_READ:
			if (wError)
			{
				Print(ADDLOG, "Read error. Error code: %u", wError);
//				SendMessage(hwndDlg, WM_COMMAND, IDC_STOP, 0);
				return TRUE;
			}

			{
				int  iRecvSize;
				iRecvSize = recv(wParam, Buff, sizeof(Buff), 0);
				if (iRecvSize == SOCKET_ERROR)
				{
					Print(ADDLOG, "Read error. Error code: %i", WSAGetLastError());
//					SendMessage(hwndDlg, WM_COMMAND, IDC_STOP, 0);
					return TRUE;
				}

				Buff[iRecvSize] = 0;
				Print(ADDTEXT, Buff);
				Print(ADDLOG, "%i type %s", wParam, Buff);
				send(wParam, Buff, iRecvSize, 0);
			}
			return TRUE;

		case FD_CLOSE:
//			SendMessage(hwndDlg, WM_COMMAND, IDC_STOP, 0);
			Print(ADDLOG, "%i closed.", wParam);
			return TRUE;
		}
		break;

	case WM_CLOSE:
		closesocket(Sock);
		WSACleanup();
		EndDialog(hwndDlg, 0);
		return TRUE;
	}
	return FALSE;
}

int Print(const int iType, const char *szFormat, ...)
{
	int			iRet = 0;
	char	   *pBuff, szBuffer[1024];
	va_list		pArgList;
//	static bool bLBCountMax = false;
//	static int	iLBCount = 0;

	if (iType == ADDLOG)
	{
		SYSTEMTIME	stTime;
		GetLocalTime(&stTime);
		iRet = wsprintf(szBuffer, "%.2u:%.2u:%.2u: ",
						stTime.wHour, stTime.wMinute, stTime.wSecond);
	}
	pBuff = szBuffer + iRet;

	va_start(pArgList, szFormat);
	iRet += wvsprintfA(pBuff, szFormat, pArgList);
	va_end(pArgList);

	switch (iType)
	{
	case ADDTEXT:
		SendMessage(hText, EM_SETSEL, -1, -1);
		SendMessage(hText, EM_REPLACESEL, FALSE, (LPARAM)szBuffer);
		SendMessage(hText, EM_SCROLLCARET, 0, 0);
		break;

	case ADDLOG:
		SendMessage(hLog, LB_INSERTSTRING, 0, (LPARAM)szBuffer);
		SendMessage(hLog, LB_DELETESTRING, 19, 0);
//		SendMessage(hLog, LB_ADDSTRING, 0, (LPARAM)szBuffer);
//		SendMessage(hLog, LB_SETTOPINDEX, SendMessage(hLog, LB_GETCOUNT, 0, 0) - 1, 0);
	}

	return iRet;
}

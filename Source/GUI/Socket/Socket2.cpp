#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(linker, "/ENTRY:WinMain")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "comctl32.lib")

#include <Windows.h>
#include <WinSock.h>
#include <commctrl.h>
#include "resource.h"

#define WM_SOCKET_NOTIFY WM_USER + 1
#define PORT 23
#define RECV_BUFF_SIZE 16

char	Buff[RECV_BUFF_SIZE];
HWND	hText, hLog, hIPAddr, hBnStart, hBnSend;

TCHAR *szButtonName[] =
{
	TEXT("&Start"),
	TEXT("Co&nnect"),
	TEXT("&Stop"),
	TEXT("&Disconnect"),
};

enum {ADDLOG, ADDTEXT};

enum
{
	SERVER,
	CLIENT,
	TCP,
	UDP,
};

int CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
int Print(const int iType, const char *szFormat, ...);
void PrintMessage(const LPSTR szText, DWORD dwMsgID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmd, int nCmdShow)
{
    InitCommonControls();
	DialogBoxParam(GetModuleHandle(NULL), (LPSTR)IDD_DIALOG, NULL, DialogProc, 0);
	ExitProcess(0);
}

int CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int					iError;
	WORD				wError, wEvent, wPort;
	WSADATA				wsaData;

	static int			iType, iProtocol;
	static SOCKET		sListenSocket;
	static SOCKADDR_IN	saSvr = {0};

	switch (uMsg)
	{
	case WM_INITDIALOG:
		hLog		= GetDlgItem(hwndDlg, IDC_LOG);
		hText		= GetDlgItem(hwndDlg, IDC_TEXT);
		hIPAddr		= GetDlgItem(hwndDlg, IDC_IP);
		hBnStart	= GetDlgItem(hwndDlg, IDC_START);
		hBnSend		= GetDlgItem(hwndDlg, IDC_SEND);

		SetWindowTextA(GetDlgItem(hwndDlg, IDC_IP), "127.0.0.1");
		SetDlgItemInt(hwndDlg, IDC_PORT, 23, FALSE);
		SendDlgItemMessage(hwndDlg, IDC_TCP, BM_CLICK, 0, 0);
		SendDlgItemMessage(hwndDlg, IDC_SERVER, BM_CLICK, 0, 0);
		SendDlgItemMessage(hwndDlg, IDC_PORT, EM_LIMITTEXT, 5, 0);

		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_START:
		case IDC_CONNECT:
			SetWindowText(hBnStart, szButtonName[wParam - IDC_START + (IDC_STOP - IDC_START)]);
			SetWindowLong(hBnStart, GWL_ID, wParam + IDC_STOP - IDC_START);

            iError = WSAStartup(MAKEWORD(2, 2), &wsaData);
            if (iError != NO_ERROR)
            {
                MessageBox(hwndDlg, TEXT("WSAStartup() failed."), 0, 0x40);
                EndDialog(hwndDlg, 1);
                return TRUE;
            }

			Print(ADDLOG, "%s", wsaData.szDescription);

			sListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (sListenSocket == INVALID_SOCKET)
			{
				PrintMessage("socket() failed", WSAGetLastError());
				SendMessage(hwndDlg, WM_COMMAND, wParam + IDC_STOP - IDC_START, 0);
				return TRUE;
			}

			if (SOCKET_ERROR == WSAAsyncSelect(sListenSocket, hwndDlg,
				WM_SOCKET_NOTIFY,
				FD_ACCEPT | FD_CONNECT | FD_CLOSE | FD_READ))
			{
				PrintMessage("WSAAsyncSelect() failed", WSAGetLastError());
				SendMessage(hwndDlg, WM_COMMAND, wParam + IDC_STOP - IDC_START, 0);
				return TRUE;
			}

			wPort = GetDlgItemInt(hwndDlg, IDC_PORT, NULL, FALSE);
			saSvr.sin_family	= AF_INET;
//			saSvr.sin_port		= htons(PORT);
			saSvr.sin_port		= htons(wPort);
			Print(ADDLOG, "Port: %u", wPort);

			switch (iProtocol)
			{
			case TCP:
				if (iType == SERVER)
				{
					saSvr.sin_addr.s_addr	= htonl(INADDR_ANY);

					if (SOCKET_ERROR == bind(sListenSocket,
						(LPSOCKADDR)&saSvr, sizeof(SOCKADDR_IN)))
					{
						PrintMessage("bind() failed", WSAGetLastError());
						SendMessage(hwndDlg, WM_COMMAND, wParam + IDC_STOP - IDC_START, 0);
						return TRUE;
					}

					if (listen(sListenSocket, SOMAXCONN) == SOCKET_ERROR)
					{
						PrintMessage("listen() failed", WSAGetLastError());
						SendMessage(hwndDlg, WM_COMMAND, wParam + IDC_STOP - IDC_START, 0);
						return TRUE;
					}
				}		// iType == Server
				else
				{
					char szIP[0x10];
					GetWindowTextA(hIPAddr, szIP, sizeof(szIP));
					saSvr.sin_addr.s_addr = inet_addr(szIP);

                    connect(sListenSocket, (LPSOCKADDR)&saSvr, sizeof(SOCKADDR_IN));
				}		// iType == Client
				break;	// iProtocol == TCP

			case UDP:
				break;
			}
			return TRUE;

		case IDC_STOP:
		case IDC_DISCONNECT:
			SetWindowText(hBnStart, szButtonName[wParam - IDC_STOP]);
			SetWindowLong(hBnStart, GWL_ID, wParam - (IDC_STOP - IDC_START));

			closesocket(sListenSocket);
			PrintMessage("closesocket()", WSAGetLastError());
			WSACleanup();
			PrintMessage("WSACleanup()", WSAGetLastError());
			return TRUE;

		case IDC_SEND:
			if (iType == CLIENT && GetDlgCtrlID(hBnStart) == IDC_DISCONNECT)
			{
				int iBuffLen;
				char Buffer[512];
				iBuffLen = GetWindowText(hText, Buffer, sizeof(Buffer));
				Buffer[iBuffLen] = 0;
				Print(ADDLOG, "Send %d byte to server.",
					send(sListenSocket, Buffer, iBuffLen, 0));
			}
			return TRUE;

		case IDC_CLEAR_LOG:
			SendMessage(hLog, LB_RESETCONTENT, 0, 0);
			return TRUE;

		case IDC_CLEAR_TEXT:
			SendMessage(hText, EM_SETSEL, 0, -1);
			SendMessage(hText, EM_REPLACESEL, false, (LPARAM)"");
			return TRUE;

		case IDCANCEL:
			EndDialog(hwndDlg, 0);
			return TRUE;

		case IDC_TCP:
		case IDC_UDP:
			iProtocol = wParam - IDC_TCP + TCP;
			return TRUE;

		case IDC_SERVER:
		case IDC_CLIENT:
			{
				UINT nID;
				iType = wParam - IDC_SERVER;

				switch (nID = GetDlgCtrlID(hBnStart))
				{
				case IDC_STOP:
				case IDC_DISCONNECT:
					SendMessage(hwndDlg, WM_COMMAND, nID, 0);
				}

				ShowWindow(hBnSend, SW_SHOW & int(iType == CLIENT));
				SetWindowLong(hBnStart, GWL_ID, IDC_START + iType);
				SetWindowText(hBnStart, szButtonName[iType]);
			}
			return TRUE;
		}
		break;

	case WM_SOCKET_NOTIFY:
		wError	= WSAGETSELECTERROR(lParam);	// HIWORD
		wEvent	= WSAGETSELECTEVENT(lParam);	// LOWORD

		switch (wEvent)
		{
		case FD_ACCEPT:
			if (wError)
			{
				PrintMessage("Accept failed", WSAGetLastError());
			}
			else
			{
				int				iLen = sizeof(SOCKADDR_IN);
				SOCKET			sClient;
				SOCKADDR_IN		saCli;

				sClient = accept(sListenSocket, (LPSOCKADDR)&saCli, &iLen);
                PrintMessage("accept()", WSAGetLastError());
                Print(ADDLOG, "%i connected.", sClient);
/*
                if (sClient == INVALID_SOCKET)
				{
					PrintMessage("accept() failed", WSAGetLastError());
					return TRUE;
				}
*/
			}

			return TRUE;

		case FD_READ:
			if (wError)
			{
				PrintMessage("Read error", wError);
				return TRUE;
			}

			{
				int  iRecvSize;

				iRecvSize = recv(wParam, Buff, sizeof(Buff), 0);
				if (iRecvSize == SOCKET_ERROR)
				{
					PrintMessage("recv() error", WSAGetLastError());
				}
				else
				{
					Buff[iRecvSize] = 0;
					Print(ADDTEXT, Buff);
                    Print(ADDLOG, "recv %i bytes(%s) from %i", iRecvSize, Buff, wParam);
				}
			}
			return TRUE;

		case FD_CONNECT:
            PrintMessage("connect()", wError);
			return TRUE;

		case FD_CLOSE:
			Print(ADDLOG, "%i closed.", wParam);
            closesocket((SOCKET)wParam);
            if (iType == CLIENT)
            {
                SendMessage(hwndDlg, WM_COMMAND, IDC_DISCONNECT, 0);
            }
			return TRUE;
		}

	case WM_CLOSE:
		UINT nID;

		switch (nID = GetDlgCtrlID(hBnStart))
		{
		case IDC_STOP:
		case IDC_DISCONNECT:
			SendMessage(hwndDlg, WM_COMMAND, nID, 0);
		}
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

	if (iType == ADDLOG)
	{
		SYSTEMTIME	stTime;
		GetLocalTime(&stTime);
		iRet = wsprintf(szBuffer, "%.2u:%.2u:%.2u: ",
			stTime.wHour, stTime.wMinute, stTime.wSecond);
	}
	pBuff = szBuffer + iRet;

	va_start(pArgList, szFormat);
	iRet += wvsprintf(pBuff, szFormat, pArgList);
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
	}

	return iRet;
}

void PrintMessage(const LPSTR szText, DWORD dwMsgID)
{
    LPVOID lpMsgBuf;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, dwMsgID, 0, (LPTSTR)&lpMsgBuf, 0, NULL);
    
    Print(ADDLOG, "%s: %s", szText, lpMsgBuf);
    LocalFree(lpMsgBuf);
}

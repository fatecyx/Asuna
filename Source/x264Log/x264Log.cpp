#pragma comment(linker,"/ENTRY:main")

#pragma comment(lib, "Shlwapi.lib")
#pragma warning(disable:4273)
#pragma comment(linker,"/MERGE:.text=Ami /SECTION:Ami,ERW")
#pragma comment(linker,"/MERGE:.rdata=Ami")
#pragma comment(linker,"/MERGE:.data=Ami")

#include <Windows.h>
#include <Shlwapi.h>
#include <tchar.h>
//#include <stdio.h>

BOOL bCtrlC;

BOOL CALLBACK HandlerRoutine(DWORD dwCtrlType)
{
	switch(dwCtrlType)
	{
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		bCtrlC = 1;
		return TRUE;
	}
	return FALSE;
}

int main(int argc, wchar_t **argv)
{
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
	argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	TCHAR buff[1024];
	HANDLE hFile = INVALID_HANDLE_VALUE;
	DWORD dwBuffSize = sizeof(buff), dwTotal = GetTickCount();
	DWORD nBytesWritten, nBytesRead, dwWritten;
	SYSTEMTIME time;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE),
		   hStdErr = GetStdHandle(STD_ERROR_HANDLE),
		   hStdIn  = GetStdHandle(STD_INPUT_HANDLE);

	if (argc != 1)
	{
		hFile = CreateFileW( argv[1],
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			0,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL );
		if (hFile != INVALID_HANDLE_VALUE)
		{
//			memset(buff, 0, dwBuffSize);
			SetFilePointer(hFile, 0, 0, FILE_END);
			GetLocalTime(&time);
			memset(buff, '-', 50);
//			for (SHORT i = 0; i != 50; ++i)
//			{
//				buff[i] = '-';
//			}
			WriteFile(hFile, buff, 50, &dwWritten, 0);
			WriteFile( hFile, buff,
				sprintf( buff, "\r\nStartTime: %d-%d-%d %.2d:%.2d:%.2d\r\n\r\n",
						time.wYear, time.wMonth, time.wDay,
						time.wHour, time.wMinute, time.wSecond ),
				&dwWritten,
				0 );
		}
	}

	double dTemp;
	buff[0] = 0;

	while (!bCtrlC && (ReadFile(hStdErr, buff, dwBuffSize, &nBytesRead, NULL),nBytesRead ||
		ReadFile(hStdIn, buff, dwBuffSize, &nBytesRead, NULL) ))
	{
		WriteFile(hStdOut, buff, nBytesRead, &nBytesWritten, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			if (sscanf(buff, "[%ld%%]", &dTemp) != 1 &&
				sscanf(buff, "%u frames", &dTemp) != 1)
			{
				WriteFile(hFile, buff, nBytesWritten, &dwWritten, 0);
			}
		}
		buff[0] = 0;
	}

	{
		DWORD dwTime = (dwTotal = GetTickCount() - dwTotal) / 1000;
		GetLocalTime(&time);
		WriteFile(hFile, buff,
			sprintf(buff, "\r\nEndTime: %d-%d-%d %.2d:%.2d:%.2d\r\n",
					time.wYear, time.wMonth, time.wDay, time.wHour,
					time.wMinute, time.wSecond),
			&dwWritten,
			0);
		WriteFile(hFile, buff,
				sprintf(buff, "Total: %.2d:%.2d:%.2d.%.3d\r\n",
						dwTotal / 1000 / 3600, dwTime % 3600 /60,
						dwTime % 3600 % 60, dwTotal % 1000),
				&dwWritten,
				0);
	}

	return 0;
}
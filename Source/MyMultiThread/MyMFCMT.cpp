
#pragma comment(linker, "/MERGE:.text=.Rimi /SECTION:.Rimi,ERW")
#pragma comment(linker, "/MERGE:.rdata=.Rimi")
#pragma comment(linker, "/MERGE:.data=.Rimi")

#define _AFXDLL

#include <afxwin.h>
#include <conio.h>

UINT MT1(LPVOID lpParamenter)
{
	int a = 0;
	while (true)
		printf("\r%d", a++), Sleep(100);
	return 0;
}

UINT MT2(LPVOID lpParamenter)
{
	int i = 0;
	TCHAR buff[32];
	while (true)
	{
		itoa(i++, buff, 10);
		SetConsoleTitle(buff);
		Sleep(100);
	}
	return 0;
}

void main()
{
	CWinThread hMT1(MT1, NULL);
	CWinThread hMT2(MT2, NULL);
	hMT1.CreateThread();
	hMT2.CreateThread();
	while (!kbhit());
}
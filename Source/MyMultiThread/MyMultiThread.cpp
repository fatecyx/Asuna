#pragma comment(lib, "msvcrt6.lib")
#pragma comment(linker, "/MERGE:.text=.Rimi /SECTION:.Rimi,ERW")
#pragma comment(linker, "/MERGE:.rdata=.Rimi")
#pragma comment(linker, "/MERGE:.data=.Rimi")
#pragma pack(1)

#include <Windows.h>
#include <tchar.h>
#include <process.h>    /* _beginthreadex, _endthreadex */
#include <stdio.h>
#include <conio.h>

#define GetRandom(min, max) \
			max < min  ? 0 : \
			max == min ? min : (rand() % (max + 1 - min) + min)

unsigned int __stdcall Rain(void *param);
unsigned int __stdcall Joy(void *param);

bool	bStart, bRainExit;
HANDLE	hStdOut;
SHORT	sRowNum, sColNum;
COORD	coord = {0, 0}, coordDest = {0, coord.Y + 1};

static const char *szStrings[] =
{
	"Chaos Head",
	"Maria Holic",
	"Kara no kyoukai",
	"Elfen Lied",
	"Fate／stay night",
	"Shakugan no Shana",
	"Tsukihime",
	"Toradora",
};

void main()
{
	HANDLE hThread[2];
	CONSOLE_CURSOR_INFO cci = {1, FALSE};
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	srand(GetTickCount());
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);				// 获取标准输出句柄
	GetConsoleScreenBufferInfo(hStdOut, &csbi);				// 获取控制台信息
	SetConsoleCursorInfo(hStdOut, &cci);					// 隐藏光标

	// 设置标准输出字符属性(绿色加亮)
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN|FOREGROUND_INTENSITY);

	sColNum = csbi.dwMaximumWindowSize.X;					// 宽
	sRowNum = csbi.srWindow.Bottom - csbi.srWindow.Top;		// 高

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, Rain, NULL, 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, Joy,  NULL, 0, NULL);

	WaitForMultipleObjectsEx(sizeof(hThread) / sizeof(HANDLE), hThread, TRUE, INFINITE, FALSE);
}

unsigned int __stdcall Rain(void *param)
{
	DWORD		dwRead;
	SMALL_RECT	srcScrollRect;
	char		*bLengthOfRain, *bIsSpace, *buff;
	COORD		coordLine0 = {0, 0}, coordLine2 = {0, 2};
	CHAR_INFO	char_info = {' ', FOREGROUND_GREEN|FOREGROUND_INTENSITY};

	// 设置要移动的范围
//	srcScrollRect.Top		= coord.Y;
	srcScrollRect.Left		= 0;
	srcScrollRect.Right		= sColNum - 1;
	srcScrollRect.Bottom	= sRowNum - 1;

	buff			= (char *)malloc(sColNum);
	bIsSpace		= (char *)malloc(sColNum);
	bLengthOfRain	= (char *)malloc(sColNum);
	memset(bIsSpace, 0, sColNum);
	memset(bLengthOfRain, 0, sColNum);

	do
	{
		Sleep(50);
/*		if (bStart)	coord.Y = 2;
		else coord.Y = 0;
*/
		// 上面的if...else...简化如下
		coord.Y = bStart << 1;
		coordDest.Y = coord.Y + 1;
		srcScrollRect.Top = coord.Y;

		// 移动一块字符, 并用 char_info 填充空出来的区域
		ScrollConsoleScreenBuffer(hStdOut, &srcScrollRect, 0, coordDest, &char_info);

		// 输出一行字符
		for (char index = 0; index != sColNum; ++index)
		{
			if (!bLengthOfRain[index]--)
			{
				bIsSpace[index]			= GetRandom(0, 4);		// 25% 概率出字符
				bLengthOfRain[index]	= GetRandom(10, 25);	// 每列最短10, 最长25
			}
			buff[index] = bIsSpace[index] ? ' ' : GetRandom(0x30, 0x7E);
		}
		WriteConsoleOutputCharacter(hStdOut, buff, sColNum, coord, NULL);
		if (bStart)			// 读取第3行的内容并写到第1行
		{
			ReadConsoleOutputCharacter(hStdOut,  buff, sColNum, coordLine2, &dwRead);
			WriteConsoleOutputCharacter(hStdOut, buff, dwRead,  coordLine0, NULL);
		}
	} while (!kbhit());

	bRainExit = true;
	free(bLengthOfRain);
	free(bIsSpace);
	free(buff);
//	MessageBox(NULL, _T("t1 free success"), NULL, 0x40);
	return 0;
}

unsigned int __stdcall Joy(void *param)
{
	DWORD dwRead, dwStrLen;
	const char *szStr;
	char *buff	= (char *)malloc(sColNum);
	char *space = (char *)malloc(sColNum);
	COORD coordLine1 = {0, 0},
		  coordLine2 = {0, 1},
		  coordMid	 = {sColNum / 3, 1},
		  coordStr;

	coordStr.Y = 1;
	memset(space, 0x20, sColNum);

	do
	{
		szStr = szStrings[GetRandom(0, sizeof(szStrings) / 4 - 1)];		// 随机选取一个字符串
		dwStrLen = lstrlenA(szStr);
		coordStr.X = sColNum / 2 - (SHORT)dwStrLen / 2 - 1;					// 计算中间位置
		Sleep(GetRandom(1000, 1000));
		bStart = true;
		Sleep(100);			// 确保另一个线程已完成转换
		if (bRainExit)
			break;

		// 用空格填充第2行
		WriteConsoleOutputCharacter(hStdOut, space, sColNum, coordLine2, NULL);

		for (byte index = 0; index != 15; ++index)
		{
			for (byte ix = 0; ix != coordMid.X; ix += 1)
				buff[ix] = GetRandom('A', 'z');
			WriteConsoleOutputCharacter(hStdOut, buff, coordMid.X, coordMid, NULL);
			Sleep(20);
		}

		WriteConsoleOutputCharacter(hStdOut, space, sColNum, coordLine2, NULL);
		WriteConsoleOutputCharacter(hStdOut, szStr, dwStrLen, coordStr, NULL);
		Sleep(GetRandom(1000, 1000));

		ReadConsoleOutputCharacter(hStdOut,  buff, sColNum, coordLine1, &dwRead);
		WriteConsoleOutputCharacter(hStdOut, buff, dwRead,  coordLine2, NULL);
		bStart = false;
	} while (!kbhit());

	free(space);
	free(buff);
//	MessageBox(NULL, _T("t2 free success"), NULL, 0x40);
	return 0;
}
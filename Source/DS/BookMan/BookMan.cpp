#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=Ami /SECTION:Ami,ERW")
#pragma comment(linker,"/MERGE:.rdata=Ami")
#pragma comment(linker,"/MERGE:.data=Ami")
#pragma comment(lib,"msvcrt6.lib")

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "BookMan.h"

bool isSort;
int ErrorCode;
HANDLE hStdOut;

int Search(BOOK *Book)
{
	if (Book->BookNum == 0)
	{
		return ERR_NOBOOK;
	}
	int searchtype, searchmethod;
	char buff[128];buff[0] = 0;
	SHORT ShiftRight;
	COORD coord = {0, 2}, move;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!isSort)
	{
		Sort(Book);
	}
	printf("1.按书号查找\n"
		   "2.按书名查找\n"
		   "3.返回\n\n"

		   "请选择: ");
	searchtype = fgetc(stdin) - 0x31;
	fflush(stdin);
	switch (searchtype)
	{
	case ISBN:
		searchmethod = BINCHOP;
		break;
	case NAME:
		searchmethod = SEQS;
		break;
	case CANCEL:
		return ERR_NORMAL;
	default:
		printf("未知选项.\n");
		return ERR_NORMAL;
	}

	printf("请输入要查找的%s: ", Tip[searchtype]);
	fgets(buff, sizeof(buff), stdin);
	fflush(stdin);

	ClearScreen();
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	coord.X = csbi.dwMaximumWindowSize.X / Book->TipNum / 2 - 1;
	ShiftRight = coord.X * 2;
	
	Print(Tip, Book->TipNum, coord, &ShiftRight);
	++coord.Y;
	move = coord;
	for (SHORT i = 0; i != Book->TipNum; ++i)
	{
		move.X = coord.X - strlen(Separator) / 2 + 2;
		SetConsoleCursorPosition(hStdOut, move);
		printf(Separator);
		coord.X += ShiftRight;
	}
	printf("\n");
	++coord.Y;
	coord.X = csbi.dwMaximumWindowSize.X / Book->TipNum / 2 - 1;

	switch (searchmethod)
	{
	case BINCHOP:
		{
			DWORD left = 0, right = Book->BookNum - 1, mid;
			int flag1, flag2, found;
			flag1 = lstrcmp(buff, Book->pNode[0].BookInfo[0]);
			flag2 = lstrcmp(buff, Book->pNode[right].BookInfo[0]);
			if (flag1 > 0 && flag2 < 0)
			{
				while (left <= right)
				{
					mid = (left + right) / 2;
					found = lstrcmp(buff, Book->pNode[mid].BookInfo[0]);
					if (found < 0)
					{
						right = mid - 1;
					}
					else if (found > 0)
					{
						left = mid + 1;
					}
					else
					{
						Print(Book->pNode[mid].BookInfo, Book->TipNum, coord, &ShiftRight);
						break;
					}
				}
			}
			else if (!flag1)
			{
				Print(Book->pNode[0].BookInfo, Book->TipNum, coord, &ShiftRight);
			}
			else if (!flag2)
			{
				Print(Book->pNode[right].BookInfo, Book->TipNum, coord, &ShiftRight);
			}
		}
		break;
	case SEQS:
		for (DWORD i = 0; i != Book->BookNum; ++i)
		{
			if (!lstrcmp(Book->pNode[i].BookInfo[1], buff))
			{
				printf("\rNo.%d", i + 1);
				Print(Book->pNode[i].BookInfo, Book->TipNum, coord, &ShiftRight);
				++coord.Y;
			}
		}
	}
	return ERR_SUCCESS;
}

int Menu(BOOK *Book)
{
	char c;
	while (1)
	{
		ClearScreen();
		printf("*****************************************\n"
			   "	1.图书入库\n"
			   "	2.将图书按书号升序排列\n"
			   "	3.按书名,书号查找图书\n"
			   "	4.查看现存图书\n"
			   "	5.删除指定(书号,书名)图片\n"
			   "	6.退出\n"
			   "*****************************************\n\n"

			   "请选择: ");
		c= _getch();
		ClearScreen();
		switch(c)
		{
		case '1':
			if (ErrorCode = AddBook(Book))
			{
				return ErrorCode;
			}
			break;
		case '2':
			if (!Sort(Book))
			{
				printf("排序完成, ");
			}
			else
			{
				printf("无书.\n");
			}
			break;
		case '3':
			if ((ErrorCode = Search(Book)) == ERR_NOBOOK)
			{
				printf("无书.");
			}
			else if (!ErrorCode)
			{
				printf("\n\n\n");
				printf("查找完毕, ");
			}
			break;
		case '4':
			List(Book);
			printf("\n\n\n");
			break;
		case '5':
			Delete(Book);
			break;
		case '6':
			return ERR_SUCCESS;
		default:continue;
		}
		printf("按任意键返回...");
		_getch();
	}
}

int main()
{
	BOOK Book;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("Kawashima Ami");
	if (ErrorCode = Initialization(&Book))
	{
		printf("Memory allocation failed.\n");
		return ErrorCode;
	}
	if (ErrorCode = Menu(&Book))
	{
		printf("Add book failed.\n");
		return ErrorCode;
	}
	return ERR_SUCCESS;
}

void ClearScreen()
{
	COORD coord = {0, 0};
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, NULL);
	SetConsoleCursorPosition(hStdOut, coord);
}

int Initialization(BOOK *Book)
{
	DWORD dwMemSize = sizeof(BOOKNODE) * INITSIZE;
	Book->pNode = (BOOKNODE *)malloc(dwMemSize);
	if (Book->pNode == NULL)
	{
		return ERR_INIT;
	}
	memset(Book->pNode, 0, dwMemSize);
	Book->MaxNum = INITSIZE;
	Book->BookNum = 0;
	Book->TipNum = sizeof(Tip) / 4;
	return ERR_SUCCESS;
}

int AddBook(BOOK *Book)
{
	COORD coord = {0, 2};
	DWORD ix = 0;
	TCHAR buff[128];buff[0] = 0;
	
	printf("请输入以下信息:\n\n");
	for (SHORT i = 0; i != Book->TipNum; ++i)
	{
		printf("%s:\n", Tip[i]);
	}
	
	for (SHORT i = 0; i != Book->TipNum; ++i, ++coord.Y)
	{
		coord.X = strlen(Tip[ix++]) + 2;
		SetConsoleCursorPosition(hStdOut, coord);
		fgets(buff, sizeof(buff), stdin);
		fflush(stdin);
		Book->pNode[Book->BookNum].BookInfo[i] = (TCHAR *)malloc(strlen(buff) + 1);
		if (Book->pNode[Book->BookNum].BookInfo[i] == NULL)
		{
			return ERR_ADDBOOK;
		}
		lstrcpy(Book->pNode[Book->BookNum].BookInfo[i], buff);
	}
	
	if (Book->BookNum && 
		lstrcmp(Book->pNode[Book->BookNum].BookInfo[0], 
				Book->pNode[Book->BookNum - 1].BookInfo[0]) < 0)		//最后一个不是最大的
		{
			isSort = 0;
		}
	++Book->BookNum;
	
	printf("\n添加完毕.");
	return ERR_SUCCESS;
}

void _Delete (BOOK *Book, DWORD sn)
{
	for (DWORD ix = sn; ix != Book->BookNum; ++ix)
	{
		Book->pNode[ix] = Book->pNode[ix + 1];
	}
	--Book->BookNum;
}

inline int __cdecl IntSort(const void *elem1, const void *elem2)
{
	DWORD n1, n2;
	n1 = _wtoi(*(wchar_t **)elem1);
	n2 = _wtoi(*(wchar_t **)elem2);
	return  n1 - n2;
}

int Delete(BOOK *Book)
{
	int argc;
	wchar_t buff[1024], **argv;
	List(Book);
	printf("\n\n输入要删除的书的序号(No.XX),删除多个以空格分隔: ");
	fgetws(buff, sizeof(buff), stdin);
	fflush(stdin);
	argv = CommandLineToArgvW(buff, &argc);
	qsort(argv, argc, sizeof(wchar_t *),IntSort);
	for (DWORD sn; argc; --argc)
	{
		sn = _wtoi(argv[argc - 1]);
		if (sn && sn <= Book->BookNum)
		{
			_Delete(Book, sn - 1);
		}
		else
		{
			printf("错误的序号 \"%d\" !", sn);
		}
	}
	return ERR_SUCCESS;
}

void Print(TCHAR **String, 
		   SHORT n, 
		   COORD coord, 
		   const SHORT *ShiftRight)
{
	COORD move = coord;
	for (SHORT i = 0; i != n; ++i)
	{
		move.X = coord.X - strlen(String[i]) / 2 + 2;
		SetConsoleCursorPosition(hStdOut, move);
		printf(String[i]);
		coord.X += *ShiftRight;
	}
}

int List(const BOOK *Book)
{
	SHORT ShiftRight;
	COORD coord = {0, 0}, move;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	SetConsoleCursorPosition(hStdOut, coord);
	coord.X = csbi.dwMaximumWindowSize.X / Book->TipNum / 2 - 1;
	ShiftRight = coord.X * 2;
	coord.Y += 2;
	
	printf("现存%d本.", Book->BookNum);
	Print(Tip, Book->TipNum, coord, &ShiftRight);
	++coord.Y;
	move = coord;
	for (SHORT i = 0; i != Book->TipNum; ++i)
	{
		move.X = coord.X - strlen(Separator) / 2 + 2;
		SetConsoleCursorPosition(hStdOut, move);
		printf(Separator);
		coord.X += ShiftRight;
	}
	printf("\n");
	
	++coord.Y;
	coord.X = csbi.dwMaximumWindowSize.X / Book->TipNum / 2 - 1;
	for (DWORD ix = 0; ix != Book->BookNum; ++ix)
	{
		printf("\rNo.%d", ix + 1);
		Print(Book->pNode[ix].BookInfo, Book->TipNum, coord, &ShiftRight);
		++coord.Y;
	}
	
	return ERR_SUCCESS;
}

inline int __cdecl _strcmp(const void *ptr1, const void *ptr2)
{
	DWORD n1, n2;
	n1 = _ttoi(*(TCHAR **)ptr1);
	n2 = _ttoi(*(TCHAR **)ptr2);
	return  n1 - n2;
}

int Sort(BOOK *Book)
{
	if (Book->BookNum)
	{
		qsort(Book->pNode, Book->BookNum, sizeof(BOOKNODE), _strcmp);
		isSort = 1;
		return ERR_SUCCESS;
	}
	else
	{
		isSort = 0;
		return ERR_NORMAL;
	}
}
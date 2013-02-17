/********************************************************************
	作用	:	提亚拉之泪PC版解包器
	文件名	: 	TTTExtract.cpp
	创建时间:	2009-6-2   14:30
	最后修改:	2009-6-4   20:53

	更新历史:	2009-6-2	创建文件
				2009-6-3	记录消耗时间,添加命令行提示,
							支持输出OGG,Ctrl+C不会直接退出
				2009-6-4	修正修改pbDest导致无法正常调用HeapReAlloc的BUG
							修改PakFileInfo第一个成员为bIsCompressed
*********************************************************************/
#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/MERGE:.text=.Hiromi /SECTION:.Hiromi,ERW")
//#pragma comment(linker, "/MERGE:.data=.Hiromi")
#pragma comment(linker, "/MERGE:.rdata=.Hiromi")
#pragma comment(lib, "shlwapi.lib")

#include <Windows.h>
#include "getmainargs.h"
#include <Shlwapi.h>
#include <stdio.h>
#include <conio.h>

enum FILETYPE
{
	DATA,
	SOUND,
	UNKNOWN,
};

typedef struct _tagPakFileInfo
{
	BOOL	bIsCompressed;
	TCHAR	szFileName[0x18];
	DWORD	dwFileOffset;
	DWORD	dwFileSize;
} PakFileInfo;

typedef struct _tagSeFileInfo
{
	TCHAR	szUnknown[0x20];
	DWORD	dwFileSize;
	DWORD	dwFileOffset;
} SeFileInfo;

bool bCtrlC;
BYTE Buffer[0x1000];

DWORD Decode(PBYTE pbSrc, PBYTE pbDest, DWORD dwSrcLen, DWORD dwDestLen);

BOOL CALLBACK HandlerRoutine(DWORD dwCtrlType)
{
	switch(dwCtrlType)
	{
	case CTRL_C_EVENT:
		bCtrlC = true;
		printf("User abort.\n");
		return TRUE;
	}
	return FALSE;
}

void main(int argc, char **argv)
{
	getargs(&argc, &argv);
	if (argc < 2)
	{
		printf("Usage: %s *.pak\n", PathFindFileName(argv[0]));
		return;
	}

	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
	HANDLE	hInFile = CreateFile(argv[1],
						GENERIC_READ,
						FILE_SHARE_READ,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
	if (hInFile == INVALID_HANDLE_VALUE)
	{
		printf("Open src file \"%s\" error.\n", argv[1]);
		return;
	}

	BYTE	byFileType;
	TCHAR	szFileName[0x20];
	PBYTE	pbSrc, pbDest, pbOutBuffer;
	DWORD	dwRead, dwWritten;
	DWORD	dwNextFilePos, dwSize, dwFileHeader, dwFileNum;
	DWORD	dwDestLen, dwCurFileIndex = 0, dwPrevSrcLen = 0, dwPrevDestLen = 0;
	DWORD	dwFileSize, dwFileOffset, dwTimeElapsed, dwSucess = 0;
	HANDLE	hHeap, hOutFile;

	LPVOID		lpFileInfo;
	PakFileInfo	pfi;
	SeFileInfo	sfi;
	const DWORD dwSizeOfInfo[2] = {sizeof(PakFileInfo), sizeof(SeFileInfo)};

	ReadFile(hInFile, &dwFileHeader, 4, &dwRead, NULL);
	switch (dwFileHeader)
	{
	case 'PACK':
		byFileType = DATA;
		dwNextFilePos = 0x8;
		lpFileInfo = (LPVOID)&pfi;
		break;
	case 'CAL':
		byFileType = SOUND;
		dwNextFilePos = 0x8;
		lpFileInfo = (LPVOID)&sfi;
		break;
	default:
		printf("Input file format error.\n");
		CloseHandle(hInFile);
		return;
	}

	SetFilePointer(hInFile, 0x24 + (byFileType << 3), 0, FILE_BEGIN);
	ReadFile(hInFile, &dwFileNum, 4, &dwRead, NULL);
	dwFileNum = (dwFileNum - dwNextFilePos) / dwSizeOfInfo[byFileType];

	hHeap	= GetProcessHeap();
	pbSrc	= (PBYTE)HeapAlloc(hHeap, 0, 0);
	pbDest	= (PBYTE)HeapAlloc(hHeap, 0, 0);

	{
		TCHAR szCurDir[_MAX_FNAME];
		TCHAR *pDot = PathFindExtension(argv[1]);

		GetModuleFileName(GetModuleHandle(NULL), szCurDir, sizeof(szCurDir));
		*PathFindFileName(szCurDir) = 0;
		SetCurrentDirectory(szCurDir);

		if (*pDot == '.')
		{
			TCHAR *szDir = PathFindFileName(argv[1]);
			*pDot = 0;
			CreateDirectory(szDir, NULL);
			SetCurrentDirectory(szDir);
			*pDot = '.';
		}
	}

	SetConsoleTitle(argv[1]);
	dwTimeElapsed = GetTickCount();
	while (bCtrlC == false && dwCurFileIndex < dwFileNum)
	{
		++dwCurFileIndex;
		SetFilePointer(hInFile, dwNextFilePos, NULL, FILE_BEGIN);
		ReadFile(hInFile, lpFileInfo, dwSizeOfInfo[byFileType], &dwRead, NULL);

		dwNextFilePos = SetFilePointer(hInFile, 0, 0, FILE_CURRENT);

		if (byFileType == DATA)
		{
			dwFileSize		= ((PakFileInfo *)lpFileInfo)->dwFileSize;
			dwFileOffset	= ((PakFileInfo *)lpFileInfo)->dwFileOffset;
			__asm
			{
				mov ecx, 0x6;
				lea esi, pfi.szFileName;
				lea edi, szFileName;
				rep movsd;
			}
		}
		else
		{
			dwFileSize		= ((SeFileInfo *)lpFileInfo)->dwFileSize;
			dwFileOffset	= ((SeFileInfo *)lpFileInfo)->dwFileOffset;
			sprintf(szFileName, "%.6u.wav", dwCurFileIndex);
		}

		printf("Extracting \"%s\" ...... ", szFileName);
		if (dwFileSize == 0 ||
			SetFilePointer(hInFile, dwFileOffset, NULL, FILE_BEGIN) == HFILE_ERROR)
		{
			printf("failed\t(%u/%u) @ SetFilePointer()\n", dwCurFileIndex, dwFileNum);
			continue;
		}

		if (dwFileSize > dwPrevSrcLen)
		{
			pbSrc = (PBYTE)HeapReAlloc(hHeap, 0, pbSrc, dwFileSize);
		}
		dwPrevSrcLen = dwFileSize;
		if (pbSrc == NULL)
		{
			printf("failed\t(%u/%u) @ pbSrc == NULL\n", dwCurFileIndex, dwFileNum);
			continue;
		}

		ReadFile(hInFile, pbSrc, dwFileSize, &dwRead, NULL);

		dwDestLen = *(DWORD *)(pbSrc + 4);

		if (dwDestLen && byFileType == DATA && pfi.bIsCompressed == 1)
		{
			if (dwDestLen > dwPrevDestLen)
			{
				pbDest = (PBYTE)HeapReAlloc(hHeap, 8, pbDest, dwDestLen);
				pbOutBuffer = pbDest;
			}
			dwPrevDestLen = dwDestLen;
		}
		else
		{
			if (byFileType == SOUND)
			{
				TCHAR *szExtension;
				if (*(DWORD *)pbSrc == 'FFIR')
				{
					szExtension = "wav";
				}
				else
				{
					szExtension = "ogg";
				}
				sprintf(szFileName, "%.6u.%s", dwCurFileIndex, szExtension);
			}
			dwSize = dwFileSize;
			pbOutBuffer = pbSrc;
			dwPrevDestLen = 0;
		}
		if (pbOutBuffer == NULL)
		{
			dwPrevDestLen = 0;
			printf("failed\t(%u/%u) @ pbOutBuffer == NULL\n", dwCurFileIndex, dwFileNum);
			continue;
		}

		if (dwDestLen && byFileType == DATA)
		{
			dwSize = Decode(pbSrc + 8, pbOutBuffer, dwFileSize - 8, dwDestLen);
		}

		if (dwSize != 0)
		{
			hOutFile = CreateFile(szFileName,
					GENERIC_WRITE,
					FILE_SHARE_WRITE,
					NULL,
					CREATE_ALWAYS,
					FILE_ATTRIBUTE_NORMAL,
					NULL);
			if (hOutFile != INVALID_HANDLE_VALUE)
			{
				++dwSucess;
				printf("OK\t(%u/%u)\n", dwCurFileIndex, dwFileNum);
				WriteFile(hOutFile, pbOutBuffer, dwSize, &dwWritten, NULL);
				CloseHandle(hOutFile);
				continue;
			}
		}
		printf("failed\t(%u/%u) @ dwSize == 0\n", dwCurFileIndex, dwFileNum);
	}
	dwTimeElapsed = GetTickCount() - dwTimeElapsed;

	HeapFree(hHeap, 0, pbSrc);
	HeapFree(hHeap, 0, pbDest);
	CloseHandle(hInFile);

	printf("\nTook %u ms.\n", dwTimeElapsed);
	printf("Successd: %u, Failed: %u, Total: %u\n",
		dwSucess, dwFileNum - dwSucess, dwFileNum);
	_getch();
	return;
}

DWORD Decode(PBYTE pbSrc, PBYTE pbDest, DWORD dwSrcLen, DWORD dwDestLen)
{
	DWORD	dwData;
	DWORD	dwVal1 = 0, dwVal2 = 0, dwArrSize = 0xFEE;
	DWORD	dwRead = 0, dwWritten = 0;

	__asm
	{
		mov eax, 20202020h;
		mov ecx, 0FF0h >> 2;
		lea edi, Buffer;
		rep stosd;
	}

	while (dwRead <= dwSrcLen)
	{
		if ((dwVal1 & 0x100) == 0)
		{
			if (dwRead >= dwSrcLen)
			{
				// 1
				break;
			}

			dwVal1 = *pbSrc++;
			dwVal1 |= 0xFF00;
			++dwRead;
		}

		if (dwRead >= dwSrcLen)
		{
			// 2
			break;
		}

		dwData = *pbSrc++;
		++dwRead;

		if ((LOBYTE(dwVal1) & 1) != 0)
		{
			*pbDest++ = (BYTE)dwData;
			Buffer[dwArrSize & 0x0FFF] = (BYTE)dwData;
			++dwArrSize;
			++dwWritten;
			if (dwWritten > dwDestLen)
			{
				// 出错
				break;
			}

			dwVal1 >>= 1;
		}
		else
		{
			if (dwRead >= dwSrcLen)
			{
				// 3
				break;
			}

			int iTemp, nBytesRead;

			iTemp = *pbSrc++;
			++dwRead;
			dwData |= (iTemp & 0xF0) << 4;

			if (!((nBytesRead = (iTemp & 0x0F) + 2) < 0))
			{
				do
				{
					if (dwWritten > dwDestLen)
					{
						dwVal2 = 1;
						break;
					}
					else
					{
						*pbDest = Buffer[dwArrSize & 0xFFF] = Buffer[dwData & 0xFFF];
						++pbDest;
						++dwArrSize;
						++dwData;
						++dwWritten;
						--nBytesRead;
					}
				} while (nBytesRead >= 0);
			}

			if (dwWritten > dwDestLen)
			{
				// 出错
				break;
			}

			dwVal1 >>= 1;
		}
	}

	return dwWritten;
}
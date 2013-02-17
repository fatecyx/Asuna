#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/MERGE:.text=.Rimi /SECTION:.Rimi,ERW")
#pragma comment(linker, "/MERGE:.rdata=.Rimi")
#pragma comment(linker, "/MERGE:.data=.Rimi")
#pragma comment(linker, "/MERGE:.data1=.Rimi")

#pragma comment(lib, "LB.lib")

#include <Windows.h>

extern "C"
{
	_CRTIMP int __cdecl vsprintf( char *buffer, const char *format, va_list argptr);
	size_t __stdcall ED6Compress(void *dst, size_t dstsize, void *src, size_t srcsize);
}

BOOL		bError;		// unused
const DWORD	dwSizeofSrcBlock = 0xE380;
const DWORD dwSizeofDstBlock = dwSizeofSrcBlock << 2;
HANDLE		hSrcFile, hDstFile, hStdOut, hHeap;

static const char szUsage[] =
"Syntax: ED6Compress.exe [options] <inputfile>\n\
\n\
Options:\n\
\n\
  -o <string>			Specify output file\n\
  -t <integer>			Parallel encoding [2]\n";

struct _tag
{
	HANDLE	*hEvent;
	DWORD	dwSrcSize;
	WORD	wThreadNum;
	wchar_t *szInputName;
	wchar_t *szOutputName;
} tag;

int printf(const char *format, ...)
{
	DWORD	dwPrinted;
	char	buffer[1024];
	va_list	arglist;
	va_start(arglist, format);
	WriteFile(hStdOut, buffer, vsprintf(buffer, format, arglist), &dwPrinted, NULL);
	return dwPrinted;
}

DWORD WINAPI Thread(LPVOID lpParam)
{
	PBYTE pbSrc, pbDst;
	DWORD dwFileOffset, dwRead, nBytesToWrite, dwWritten;

	// 每个线程都要有自己的句柄, 否则有可能同时调用SetFilePointer
	HANDLE hFile = CreateFileW(tag.szInputName, GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		bError = TRUE;
		return FALSE;
	}

	// 根据传过来的参数设置文件指针
	dwFileOffset = (WORD)lpParam * dwSizeofSrcBlock;
	pbSrc = (PBYTE)HeapAlloc(hHeap, 0, dwSizeofSrcBlock);
	pbDst = (PBYTE)HeapAlloc(hHeap, 0, dwSizeofDstBlock);
	printf("Thread No.%d ", lpParam);
	printf("is starting.\n");

	while (dwFileOffset < tag.dwSrcSize)
	{
		SetFilePointer(hFile, dwFileOffset, 0, FILE_BEGIN);

		// 读取一块
		ReadFile(hFile, pbSrc, dwSizeofSrcBlock, &dwRead, NULL);

		// 压缩
		nBytesToWrite = ED6Compress(pbDst, dwSizeofDstBlock, pbSrc, dwRead);

		// 将文件指针设置到下一块数据开始
		dwFileOffset += tag.wThreadNum * dwSizeofSrcBlock;

		// 压缩后的数据以0x01结尾
		pbDst[nBytesToWrite - 1] = 1;

		// 等待前一个线程写入结束
		WaitForSingleObjectEx(tag.hEvent[(WORD)lpParam], INFINITE, FALSE);

		WriteFile(hDstFile, pbDst, nBytesToWrite, &dwWritten, NULL);
		printf("Thread No.%d ", lpParam);
		printf("has written 0x%X bytes\n", nBytesToWrite);

		// CreateEvent时已经设置bManualReset为FALSE, 所以这里可以省去
//		ResetEvent(tag.hEvent[(WORD)lpParam]);

		// 将下一个线程对应的事件设置为有信号
		SetEvent( tag.hEvent[ ( (WORD)lpParam + 1 ) % tag.wThreadNum ] );
	}

	// 若不执行上面的循环或循环结束则将下一线程对应的事件设为有信号
	SetEvent( tag.hEvent[ ( (WORD)lpParam + 1 ) % tag.wThreadNum ] );
	printf("Thread No.%d ", lpParam);
	printf("is exiting.\n");
	HeapFree(hHeap, 0, pbSrc);
	HeapFree(hHeap, 0, pbDst);
	CloseHandle(hFile);
	return TRUE;
}

int main(int argc, wchar_t **argv)
{
	bool   bWrongOpt = false;
	HANDLE *hThread;
	DWORD  dwWritten, dwParam, dwTimeElapsed;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	argv    = CommandLineToArgvW(GetCommandLineW(), &argc);

	if (argc < 3)
	{
		printf(szUsage);
		return -1;
	}

	// 分析命令行参数
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			dwParam = (char)argv[i][1];
			for (int j = 2; argv[i][j]; ++j)
			{
				// 将字符串变成'xxx'的形式, 如"mt"变为'mt', 最大四字节
				dwParam = dwParam << 8 | (char)argv[i][j];
			}
			switch (dwParam)
			{
			case 'o':
				if (++i >= argc) break;
				tag.szOutputName = argv[i];
				break;
			case 't':
				if (++i >= argc) break;
				tag.wThreadNum = _wtoi(argv[i]);
				break;
			default:
				printf("Unknown option [%d]\n"
						"%s", (i >> 1) + 1, szUsage);
				return -1;
			}
		}
		else
		{
			tag.szInputName = argv[i];
		}
	}

	if (tag.szOutputName == NULL)
	{
		printf("Please specify a output file.\n");
		return -1;
	}

	hSrcFile = CreateFileW(tag.szInputName, GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hSrcFile == INVALID_HANDLE_VALUE)
	{
		printf("Open input file faild.\n");
		return -1;
	}

	hDstFile = CreateFileW(tag.szOutputName, GENERIC_WRITE,
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hDstFile == INVALID_HANDLE_VALUE)
	{
		printf("Open output file faild.\n");
		return -1;
	}

	tag.dwSrcSize = GetFileSize(hSrcFile, NULL);
	CloseHandle(hSrcFile);

	// 若未在参数中指定线程数, 则从系统环境变量中获取, 若获取失败则默认设置为2
	if (!tag.wThreadNum)
	{
		if (!GetEnvironmentVariable( "NUMBER_OF_PROCESSORS",
									(LPSTR)&tag.wThreadNum,
									sizeof(tag.wThreadNum)) )
		{
			tag.wThreadNum = 2;
		}
		else
		{
			tag.wThreadNum -= '0';
		}
	}

//	tag.wThreadNum <<= 5;
	hHeap		= HeapCreate(0, tag.wThreadNum * sizeof(HANDLE), 0);
	hThread 	= (HANDLE *)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, tag.wThreadNum * sizeof(HANDLE));
	tag.hEvent	= (HANDLE *)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, tag.wThreadNum * sizeof(HANDLE));

	// 记录开始时间
	dwTimeElapsed = GetTickCount();
	for (WORD ix = 0; ix != tag.wThreadNum; ++ix)
	{
		tag.hEvent[ix] = CreateEvent(NULL,			// lpEventAttributes
									 FALSE,			// bManualReset
									 FALSE,			// bInitialState
									 NULL);			// lpName
		hThread[ix]	   = CreateThread(NULL, 0, Thread, (LPVOID)ix, 0, NULL);
	}

	SetEvent(tag.hEvent[0]);
	WaitForMultipleObjectsEx(tag.wThreadNum, hThread, TRUE, INFINITE, FALSE);

	// 这里得到从启动到现在经过的时间
	dwTimeElapsed = GetTickCount() - dwTimeElapsed;
	printf("Encoding took %u millisecond(s).\n", dwTimeElapsed);

	// 将0写到文件最后一字节
	SetFilePointer(hDstFile, -1, 0, FILE_END);
	WriteFile(hDstFile, "\x00", 1, &dwWritten, NULL);
	HeapFree(hHeap, 0, tag.hEvent);
	HeapFree(hHeap, 0, hThread);
	HeapDestroy(hHeap);
	CloseHandle(hStdOut);
	CloseHandle(hDstFile);
	return 0;
}


//	CRITICAL_SECTION g_cs;
//	InitializeCriticalSection(&g_cs);
//	DeleteCriticalSection(&g_cs);
//	EnterCriticalSection(&g_cs);
//	LeaveCriticalSection(&g_cs);
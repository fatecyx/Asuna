#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Amano /SECTION:.Amano,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Amano")
#pragma comment(linker,"/MERGE:.data=.Amano")
#pragma comment(linker,"/MERGE:.CRT=.Amano")
#pragma comment(lib, "msvcrt.lib")
#pragma comment(lib, "libcmt.lib")

#include <Windows.h>
#include <PsApi.h>
#include <stdio.h>
#include "getmainargs.h"

#define MOD

typedef void* (__stdcall *TInitDShowGraphFromFile)
(const wchar_t *szFileName, GUID MediaType, DWORD dwVideoID, DWORD dwAudioID, void *pVideoCallback, void *pAudioCallback, void *pdwVideoInfo, DWORD *pdwAudioInfo);

typedef int (__stdcall *TGraphOperate)(void *pdgi);
typedef int (__stdcall *TSeekGraph)(void *pdgi,LONGLONG timestamp);

typedef struct
{
	DWORD RIFF,size,WAVE,fmt,format_length;
	SHORT format_tag,channels;
	DWORD sample_rate,avg_bytes_sec;
	SHORT block_align,bits_per_sample;
	DWORD id,data_size;
} TWaveHeader;

TWaveHeader waveheader = {'FFIR',36,'EVAW',' tmf',0x10,	WAVE_FORMAT_PCM,2,48000,48000*4,4,16,'atad',0};
const GUID MEDIASUBTYPE_None = {0xe436eb8e, 0x524f, 0x11ce, 0x9f, 0x53, 0x00, 0x20, 0xaf, 0x0b, 0xa7, 0x70};

#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM 1
#endif

#if !defined(MOD)
    TInitDShowGraphFromFile InitDShowGraphFromFile;
    TGraphOperate StartGraph, StopGraph, DestroyGraph;
    TSeekGraph SeekGraph;
#endif

HANDLE StdOut,hEvent;
DWORD dwWritten,ctrlc = 0;
#if !defined(MOD)
    void *g_pdgi;
#endif

#ifdef MOD
LONG64 starttime = 0, endtime = -1;
#endif

BOOL CALLBACK HandlerRoutine(DWORD dwCtrlType)
{
	switch(dwCtrlType)
	{
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
		ctrlc=1;
		return TRUE;
	}
	return FALSE;
}

int __stdcall CallBackProc(PBYTE pData, LONG iLen, LONGLONG i64TimeStamp)
{
	if (pData && !ctrlc 
#ifdef MOD
        && (endtime == -1 || i64TimeStamp <= endtime)
#endif
        )
	{
		WriteFile(StdOut,pData,iLen,&dwWritten,NULL);
		return 1;
	}
	else
	{
		SetEvent(hEvent);
		return 0;
	}
}

FORCEINLINE int main2(int argc, wchar_t **argv)
{
	int i, j;
	wchar_t *input = NULL;
	DWORD   aid = 0, dwAudioInfo, dwParam = 0;
    HMODULE hDLL;

#if defined(MOD)
    void *g_pdgi;
    TInitDShowGraphFromFile InitDShowGraphFromFile;
    TGraphOperate StartGraph, StopGraph, DestroyGraph;
    TSeekGraph SeekGraph;
#endif

	if (argc < 2)
	{
		return 0;
	}

	for (i = 1; i < argc; ++i)
	{
		if (argv[i][0] && argv[i][0] != '-')
		{
			input = argv[i];
			continue;
		}

		dwParam = 0;
		wcslwr(argv[i]);

		for (j = 1; argv[i][j]; ++j)
		{
			dwParam = dwParam << 8 | (char)argv[i][j];
		}

		switch (dwParam)
		{
		case 'aid':
			if (++i < argc)
				aid = _wtoi(argv[i]);
			break;
#ifdef MOD
        case 'l':
		case 's':
		case 'e':
			if (++i < argc)
			{
				int h, m;
				double s;
				if (swscanf(argv[i], L"%d:%d:%lf", &h, &m, &s) == 3)
				{
					PLONG64 time;

					if (dwParam == 's') time = &starttime;
					else time = &endtime;

					*time = (LONG64)(s * 10000000)
						  + (LONG64)m * 600000000ll
						  + (LONG64)h * 36000000000ll;
                    if (dwParam == 'l') endtime += starttime;
				}
			}
			break;
#endif
		}
	}

    hDLL = LoadLibraryExW(L"dump.ax", 0, 0);
	if (hDLL == NULL)
	{
		return 0;
	}

	InitDShowGraphFromFile	= (TInitDShowGraphFromFile)GetProcAddress(hDLL,"InitDShowGraphFromFileW");
	StartGraph				= (TGraphOperate)GetProcAddress(hDLL,"StartGraph");
	StopGraph				= (TGraphOperate)GetProcAddress(hDLL,"StopGraph");
	DestroyGraph			= (TGraphOperate)GetProcAddress(hDLL,"DestroyGraph");
	SeekGraph				= (TSeekGraph)GetProcAddress(hDLL,"SeekGraph");

	if (!(g_pdgi = InitDShowGraphFromFile(input,MEDIASUBTYPE_None,-1,aid,NULL,CallBackProc,NULL,&dwAudioInfo)))
	{
		return 0;
	}

	waveheader.channels = (SHORT)((dwAudioInfo >> 24) & 0xF);
	waveheader.sample_rate = (dwAudioInfo & 0xFFFFFF);
	waveheader.bits_per_sample = (SHORT)((dwAudioInfo >> 25) & 0xF8);
	waveheader.block_align = waveheader.channels * waveheader.bits_per_sample / 8;
	waveheader.avg_bytes_sec = waveheader.block_align * waveheader.sample_rate;
	StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteFile(StdOut,&waveheader,sizeof(TWaveHeader),&dwWritten,NULL);
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
	hEvent = CreateEventA(NULL,FALSE,FALSE,NULL);

#ifdef MOD
	if (starttime != 0)
	{
        SeekGraph(g_pdgi, starttime);
        if (endtime != -1)
            endtime -= starttime;
//        endtime == -1 ? 0 : endtime -= starttime;
	}
#endif
	StartGraph(g_pdgi);
	WaitForSingleObject(hEvent,INFINITE);
	StopGraph(g_pdgi);
	DestroyGraph(g_pdgi);
	if (GetFileType(StdOut) == FILE_TYPE_DISK)
	{
		waveheader.data_size = GetFileSize(StdOut,NULL) - sizeof(TWaveHeader);
		waveheader.size = waveheader.data_size + sizeof(TWaveHeader) - 8;
		SetFilePointer(StdOut,0,NULL,FILE_BEGIN);
		WriteFile(StdOut,&waveheader,sizeof(TWaveHeader),&dwWritten,NULL);
	}
	CloseHandle(StdOut);
	CoUninitialize();
    FreeLibrary(hDLL);
	return 1;
}

int __cdecl main(int argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
	ExitProcess(main2(argc, argv));
}
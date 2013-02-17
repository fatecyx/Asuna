#pragma comment(linker, "/ENTRY:DllEntryPoint")
#pragma comment(linker,"/MERGE:.text=.Nagisa /SECTION:.Nagisa,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Nagisa")
//#pragma comment(linker,"/MERGE:.data=.Nagisa")
#pragma comment(lib, "d3d9.lib")

#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include "nt_fileio.h"

BOOL  WINAPI MyShowWindow(HWND hWnd, int nCmdShow);
HFONT WINAPI MyCreateFont(int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet, DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality, DWORD fdwPitchAndFamily, LPCTSTR lpszFace);

int WINAPI DllEntryPoint(HINSTANCE hInstance, unsigned long reason, void* lpReserved)
{
	static  bool bWritten = false;

	if (bWritten == false)
	{
		DWORD dwOldProtect;

		bWritten = true;
		if (VirtualProtect((LPVOID)0x401000, 0x421000, PAGE_READWRITE, &dwOldProtect))
		{
			static const PBYTE   pbBounder       = (PBYTE)0x4124BB;
			static const LPDWORD lpdwShowWindow  = (LPDWORD)0x8211DC,
								 lpdwCreateFontA = (LPDWORD)0x821014;

			if ( *pbBounder       == 0xA0 &&
				 *lpdwShowWindow  == (DWORD)ShowWindow &&
				 *lpdwCreateFontA == (DWORD)CreateFontA )
			{
//				*(PBYTE)0x44F5DC = 0;
				*pbBounder       = 0xFF;
				*lpdwShowWindow  = (DWORD)MyShowWindow;
				*lpdwCreateFontA = (DWORD)MyCreateFont;
			}
		}
	}
	return TRUE;
}

void WINAPI CenterWindow(HWND hWnd)
{
	int  x, y;
	RECT rcGame, rcSys;

	SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcSys, 0);
	GetWindowRect(hWnd, &rcGame);
	x = ((rcSys.right - rcSys.left) - (rcGame.right - rcGame.left)) >> 1;
    y = ((rcSys.bottom - rcSys.top) - (rcGame.bottom - rcGame.top)) >> 1;
	SetWindowPos(hWnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
}

BOOL WINAPI MyShowWindow(HWND hWnd, int nCmdShow)
{
	CenterWindow(hWnd);
	return ShowWindow(hWnd, nCmdShow);
}

ASM HFONT WINAPI MyCreateFont(int nHeight,
							  int nWidth,
							  int nEscapement,
							  int nOrientation,
							  int fnWeight,
							  DWORD fdwItalic,
							  DWORD fdwUnderline,
							  DWORD fdwStrikeOut,
							  DWORD fdwCharSet,
							  DWORD fdwOutputPrecision,
							  DWORD fdwClipPrecision,
							  DWORD fdwQuality,
							  DWORD fdwPitchAndFamily,
							  LPCTSTR lpszFace)
{
	static const char szFace[] = "ºÚÌå";

/*	return CreateFontA(nHeight,
			nWidth,
			nEscapement,
			nOrientation,
			fnWeight,
			fdwItalic,
			fdwUnderline,
			fdwStrikeOut,
			GB2312_CHARSET,
			fdwOutputPrecision,
			fdwClipPrecision,
			fdwQuality,
			fdwPitchAndFamily,
			"ºÚÌå");
*/
	__asm
	{
		mov dword ptr [esp+24h], GB2312_CHARSET;
		lea eax, szFace;
		mov dword ptr [esp+38h], eax;
		jmp dword ptr [CreateFontA];
	}
}
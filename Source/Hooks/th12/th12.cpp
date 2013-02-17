#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker,"/MERGE:.text=.Nagisa /SECTION:.Nagisa,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Nagisa")
#pragma comment(linker,"/MERGE:.data=.Nagisa")
#pragma comment(lib, "d3d9.lib")

#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <Windows.h>
#include <dinput.h>
#include "my_common.h"

HRESULT WINAPI KeyStateModify(PBYTE pbKeyState);
BOOL    WINAPI MyShowWindow(HWND hWnd, int nCmdShow);
HWND    WINAPI MyCreateWindowExA(IN DWORD dwExStyle, IN LPCSTR lpClassName, IN LPCSTR lpWindowName, IN DWORD dwStyle, IN int X, IN int Y, IN int nWidth, IN int nHeight, IN HWND hWndParent, IN HMENU hMenu, IN HINSTANCE hInstance, IN LPVOID lpParam);
HFONT   WINAPI MyCreateFont(int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet, DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality, DWORD fdwPitchAndFamily, LPCTSTR lpszFace);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hwndGame;
WNDPROC g_lpfnWndFunc;

typedef struct
{
	BYTE orig;
	BYTE mod;
} sKeyMod;

sKeyMod km[6] =
{
//	{DIK_UP,    DIK_W},
//	{DIK_DOWN,  DIK_S},
//	{DIK_LEFT,  DIK_A},
//	{DIK_RIGHT, DIK_D},
//	{DIK_Z,     DIK_J},
//	{DIK_X,     DIK_K},
};

int WINAPI DllMain(HINSTANCE hInstance, unsigned long reason, void* lpReserved)
{
	static  bool bWritten = false;

	if (bWritten == false)
	{
		DWORD dwOldProtect;

		bWritten = true;
		if (VirtualProtect((LPVOID)0x401000, 0x97300, PAGE_READWRITE, &dwOldProtect))
		{
			static const PBYTE   pbBounder           = (PBYTE)  0x4124BB,
								 pbKeyStateMod       = (PBYTE)  0x46304C;
			static const LPDWORD lpdwCreateWindowExA = (LPDWORD)0x498250,
								 lpdwShowWindow      = (LPDWORD)0x8211DC,
								 lpdwTranslateMsg    = (LPDWORD)0x49823C,
								 lpdwCreateFontA     = (LPDWORD)0x498034;

			if ( 1
				&& *pbKeyStateMod == 0x68
				&& *lpdwCreateWindowExA == (DWORD)CreateWindowExA
//				&& *lpdwShowWindow  == (DWORD)ShowWindow
//				&& *lpdwCreateFontA == (DWORD)CreateFontA
				)
			{
				int i;
				const char *szConfig = ".\\thxlc.ini";
				const char *orig_key[] = {"UP", "DOWN", "LEFT", "RIGHT", "Z", "X"};
				const BYTE orig[] = {DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT, DIK_Z, DIK_X};

//				*(PBYTE)0x44F5DC = 0;
//				*pbBounder       = 0xFF;
//				*lpdwShowWindow  = (LPDWORD)MyShowWindow;
//				*lpdwCreateFontA = (LPDWORD)MyCreateFont;
				if (GetPrivateProfileIntA("Keyboard", "Center", 0, szConfig) == 1)
					*lpdwCreateWindowExA = (DWORD)MyCreateWindowExA;

				for (i = 0; i != countof(orig_key); ++i)
				{
					km[i].mod = GetPrivateProfileIntA("Keyboard", orig_key[i], orig[i], szConfig);
					km[i].orig = orig[i];
				}

				for (i = 0; i != countof(km); ++i)
				{
					if (km[i].orig != km[i].mod)
						break;
				}

				if (i != countof(km))
				{
					*(PBYTE)pbKeyStateMod = 0xE8;
					*(LPDWORD)(pbKeyStateMod + 1) = (DWORD)KeyStateModify - DWORD(pbKeyStateMod + 5);
				}
			}
		}
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
//		MessageBox(hWnd, 0, 0, 64);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return CallWindowProc(g_lpfnWndFunc, hWnd, uMsg, wParam, lParam);
}

HRESULT KeyStateModify(PBYTE pbKeyState)
{
	HRESULT hr;
	LPDIRECTINPUTDEVICE lpKeyboard;

	__asm mov lpKeyboard, eax;
	*(LPDWORD)(&pbKeyState - 1) += 3;

	hr = lpKeyboard->GetDeviceState(256, pbKeyState);

	if (hr)
	{
		return hr;
	}

	for (int i = 0; i != countof(km); ++i)
	{
		pbKeyState[km[i].orig] = pbKeyState[km[i].mod];
	}

	return hr;
}

HWND WINAPI MyCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	HWND hWnd;
	RECT rcSys;

	SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcSys, 0);
	X = ((rcSys.right - rcSys.left) - nWidth) >> 1;
    Y = ((rcSys.bottom - rcSys.top) - nHeight) >> 1;
	hWnd = CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
//	g_lpfnWndFunc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)WndProc);
	return hwndGame = hWnd;
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
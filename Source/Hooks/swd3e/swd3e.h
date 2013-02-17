#ifndef _SWD3E_H_
#define _SWD3E_H_

#include "MyLibrary.h"
#include <ddraw.h>

#define PATCH_WINDOW_MODE 0

VOID FixTextOut();
VOID _ConvertSurface1();
VOID _ConvertSurface2();
VOID _ConvertSurface3();
VOID _ConvertSurface4();

VOID  STDCALL SetMonsterFlag();
VOID  STDCALL FixVideoPath(LPSTR lpPath, LPCSTR lpDrive);
VOID  STDCALL BufferTo16(LPDWORD lpSurface, int w, int h);
BOOL  STDCALL ConvertSurface(LPDIRECTDRAWSURFACE lpDDSurface);
VOID  STDCALL ColorConvert32(DWORD dwPixel, LPDWORD lpPixel1, LPDWORD lpPixel2);
VOID  CDECL   SaveScreenShot(LPDWORD pbSurface, DWORD dwWidth, DWORD dwHeight, LPCSTR lpFileName);

BOOL    WINAPI MySetWindowPos(IN HWND hWnd, IN OPTIONAL HWND hWndInsertAfter, IN int X, IN int Y, IN int cx, IN int cy, IN UINT uFlags);
INT_PTR WINAPI MyDialogBoxParamA(IN OPTIONAL HINSTANCE hInstance, IN LPCSTR lpTemplateName, IN OPTIONAL HWND hWndParent, IN OPTIONAL DLGPROC lpDialogFunc, IN LPARAM dwInitParam);
HWND    WINAPI MyCreateWindowExA(IN DWORD dwExStyle, IN LPCSTR lpClassName, IN LPCSTR lpWindowName, IN DWORD dwStyle, IN int X, IN int Y, IN int nWidth, IN int nHeight, IN HWND hWndParent, IN HMENU hMenu, IN HINSTANCE hInstance, IN LPVOID lpParam);


#define szFont (DWORD)&"MingLiu"
#define szTitle (DWORD)&"ÜŽÞ@„¦…¢ Íâ‚÷"

#endif // _SWD3E_H_
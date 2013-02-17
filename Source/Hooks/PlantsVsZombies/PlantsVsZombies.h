#ifndef _PLANTSVSZOMBIES_H_
#define _PLANTSVSZOMBIES_H_

#include "my_common.h"
#include "nt_api.h"

DWORD WINAPI MyThread(LPVOID lpParam);
BOOL  WINAPI MyGetMessageA (OUT LPMSG lpMsg, IN OPTIONAL HWND hWnd, IN UINT wMsgFilterMin, IN UINT wMsgFilterMax);
BOOL  WINAPI MyPeekMessageA(OUT LPMSG lpMsg, IN OPTIONAL HWND hWnd, IN UINT wMsgFilterMin, IN UINT wMsgFilterMax, IN UINT wRemoveMsg);
HWND  WINAPI MyCreateWindowExA(IN DWORD dwExStyle, IN LPCSTR lpClassName, IN LPCSTR lpWindowName, IN DWORD dwStyle, IN int X, IN int Y, IN int nWidth, IN int nHeight, IN HWND hWndParent, IN HMENU hMenu, IN HINSTANCE hInstance, IN LPVOID lpParam);

TPatch patch[] =
{
    {(DWORD)MyGetMessageA,  4, 0x252398},
    {(DWORD)MyPeekMessageA, 4, 0x252328},
};

TFuncPatch func[] = 
{
    { CALL, 0x150C3B, (DWORD)MyCreateWindowExA, 0x01 }, // main window
};

#endif /* _PLANTSVSZOMBIES_H_ */
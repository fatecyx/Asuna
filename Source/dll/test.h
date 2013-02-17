#ifndef _TEST_H_
#define _TEST_H_

#include "my_common.h"
#include <Windows.h>

BOOL WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
HWND WINAPI MyCreateWindowExA(IN DWORD dwExStyle, IN LPCSTR lpClassName, IN LPCSTR lpWindowName, IN DWORD dwStyle, IN int X, IN int Y, IN int nWidth, IN int nHeight, IN HWND hWndParent, IN HMENU hMenu, IN HINSTANCE hInstance, IN LPVOID lpParam);

TPatch p[] = 
{
    {(DWORD)MyPeekMessageA, 0x04, 0x862AC },
};

TFuncPatch f[] = 
{
    {CALL, 0x7EAD5, (DWORD)MyPeekMessageA,    1},
    {CALL, 0x7544E, (DWORD)MyCreateWindowExA, 1},
};

#endif /* _TEST_H_ */
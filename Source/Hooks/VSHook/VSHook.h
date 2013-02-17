#ifndef _VSHOOK_H_
#define _VSHOOK_H_

#include <Windows.h>
#include <stdio.h>
#include "my_common.h"

FILE*  CDECL  myfopen(char * _Filename, const char * _Mode);
BOOL   WINAPI MyRegisterHotKey(HWND hWnd, int id, UINT fsModifiers, UINT vk);
HANDLE WINAPI MyCreateFileA(LPSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

TPatch patch_VSClient[] =
{
    {(DWORD)MyCreateFileA    , 4, 0x14EAEC},
    {(DWORD)myfopen          , 4, 0x14F624},
    {(DWORD)MyRegisterHotKey , 4, 0x14F924},
    {0x0000                  , 2, 0x05262E},    // anti-od
    {0xE990                  , 2, 0x052741},    // anti-od
    {0xEB                    , 1, 0x06EF7D},    // anti-od
    {0xEB                    , 1, 0x075990},    // ie
    {0x00                    , 1, 0x033D8D},    // 多开
    {0xEB                    , 1, 0x033DA8},    // 多开
    {0xEB                    , 1, 0x069C44},    // 多开
};

#endif /* _VSHOOK_H_ */
#ifndef _WINHEX_H_
#define _WINHEX_H_

#include <Windows.h>
#include "my_common.h"

typedef struct
{
    DWORD dwData;
    DWORD dwSize;
    DWORD dwAddress;
} TPatch;

typedef struct
{
    BYTE  byFlag;
    DWORD dwAddress;
    DWORD dwFunc;
    BYTE  nNop;
} TFuncPatch;

VOID ConvertAnsiStringToUnicodeString();
VOID ConvertUnicodeStringToAnsiString();
//VOID STDCALL ConvertAnsiStringToUnicodeString(LPCSTR lpSrc, LPWSTR lpDest, PBYTE pbLength);

#define NOP  0x90
#define CALL 0xE8
#define JUMP 0xE9

TFuncPatch func[] =
{
    {CALL, 0x4367E8, (DWORD)ConvertAnsiStringToUnicodeString, 0x6}, 
    {CALL, 0x547FD9, (DWORD)ConvertUnicodeStringToAnsiString, 0x12}, 
};

TPatch patch[] =
{
    {936, 2, 0x546C42},	// CodePage
};

#endif /* _WINHEX_H_ */
#ifndef _ASAIRO_H_
#define _ASAIRO_H_

#include <Windows.h>
#include "my_common.h"

#pragma pack(1)

typedef struct
{
    HANDLE hFile;
    Bool   bPack;
    Long   lOffset;
    UInt32 uSize;
} SFileInfo;

typedef struct
{
    PByte pbBuffer;
    ULong dwSize;
    ULong dwMaxSize;
    ULong dwWaste;
    ULong dwOffset;
    Char  szName[MAX_PATH];
} SCacheIndex;

#pragma pack()

UInt64 WINAPI GetDecodedSizeNative(LPVoid lpBuffer, LPCSTR lpFileName, Int32 iOffset);

#endif /* _ASAIRO_H_ */
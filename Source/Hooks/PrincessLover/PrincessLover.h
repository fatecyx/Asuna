#ifndef _PRINCESSLOVER_H_
#define _PRINCESSLOVER_H_

#include <Windows.h>
#include "MyLibraryUser.h"
//#include "gal_common.h"

#define STR STRTOULONG

#pragma pack(1)

typedef struct
{
    PVOID vtable;
    union
    {
        PVOID lpBuffer;
        PBYTE  pbBuffer;
    };
    ULONG Size;
    ULONG Offset;
    ULONG MaxSize;
} MEMORY_STREAM;

typedef struct
{
    Large_Integer Offset;
    ULONG crc;
    WCHAR Name[MAX_PATH];
} MY_PACK_INDEX;

#pragma warning(disable:4200)
#pragma warning(disable:94)

typedef struct
{
    ULONG RefCount;
    ULONG Length;
    CHAR  Buffer[0];
} DELPHI_STRING;

#define DELPHI_CONST_STRING(str) { ~0, countof(str) - sizeof(*str), str }

#pragma warning(default:4200)
#pragma warning(default:94)

#pragma pack()

#endif /* _PRINCESSLOVER_H_ */

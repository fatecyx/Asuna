#ifndef _QLIE_H_
#define _QLIE_H_

#include <Windows.h>
#include "my_headers.h"
#include "../plugin_common.h"

#define QLIE_COMP_MAGIC 0xFF435031

enum
{
    FLAG_ENTRY_8BIT_LENGTH  = 0,
    FLAG_ENTRY_16BIT_LENGTH = 1,
};

#pragma pack(1)

typedef struct
{
    Char   Seed[32];
    UInt32 HashTableSize;
    Char   Data[256];
    UInt32 arr[192];
    Char   tag[16];
    UInt32 FileNum;
    Large_Integer IndexOffset;
} SPackHeader;

typedef struct
{
    UInt32  Magic;
    UInt32  Flag;
    UInt32  DecompressSize;
    Byte    Data[1];
} SPackEntryCompressedData;

typedef struct
{
    Char   HashVer[16];
    UInt32 SubTableNum;
    UInt32 FileNum;
    UInt32 FileIndexSize;
    UInt32 CompressedSize;
    SPackEntryCompressedData Data;
} SPackHashTableHeader;

typedef struct
{
    Large_Integer Offset;
    UInt32 CompressedSize;
    UInt32 DecompressSize;
    Bool   bCompressed;
    Bool   bEncrypted;
    UInt32 Hash;
    WChar FileName[MAX_PATH];
} SMyPackIndex;

typedef struct
{
    UInt32 back;
    Byte   dict_820C[0x2000];

    union
    {
        PVoid pvBuffer;
        PByte pbBuffer;
    };
    union
    {
        PVoid pvEnd;
        PByte pbEnd;
    };

    ULong DictLength;

    Byte dict_6200[0x100];
    Byte dict_6100[0x100];
    Byte dict_6000[0x2000];
    Byte dict_4000[0x2000];
    Byte dict_2000[0x2000];
} SQLIECompressInfo;

#pragma pack()

#endif /* _QLIE_H_ */
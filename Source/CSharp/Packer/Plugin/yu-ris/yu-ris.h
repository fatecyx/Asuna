#ifndef _YU_RIS_H_
#define _YU_RIS_H_

#include <Windows.h>
#include "my_headers.h"
#include "../plugin_common.h"

#pragma pack(1)

typedef struct
{
    UInt32 tag;
    UInt32 ver; // ??
    UInt32 filenum;
    UInt32 entrysize;
} SPacHeader;

typedef struct
{
    Byte len;
    Char name[1];
} SPacFileHeader;

typedef struct
{
    Char   cFileType;
    bool   bComp;
    UInt32 decompsize;
    UInt32 compsize;
    UInt32 offset;
    UInt32 hash;
} SPacFileInfo;

typedef struct
{
    Bool   cFileType;
    Bool   bCompress;
    UInt32 uDecompSize;
    UInt32 uCompSize;
    UInt32 uOffset;
    UInt32 uHash1;
    UInt32 uHash2;
    WChar  szFileName[MAX_PATH];
} SMyPacFileInfo;

#pragma pack()

extern Byte LengthTable_107[256];
extern Byte LengthTable_122[256];
extern UInt32 HashTable[256];

#endif /* _YU_RIS_H_ */
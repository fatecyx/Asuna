#ifndef _KRKR2_XP3_H_
#define _KRKR2_XP3_H_

#include <Windows.h>
#include "my_headers.h"

#pragma pack(1)

typedef struct
{
    Byte          tag[0xB];
    LARGE_INTEGER IndexOffset;
} SXP3Header;

typedef struct
{
    Byte          bZlib;
    LARGE_INTEGER CompSize;
    LARGE_INTEGER DecompSize;
} SXP3DataHeader;

typedef struct
{
    SXP3DataHeader header;
    Byte           Index[1];
} SXP3Index;

typedef struct
{
    UInt32        tag;     // 'File'
    LARGE_INTEGER size;
} SXP3InfoFile;

typedef struct
{
    UInt32        tag;     // 'info'
    LARGE_INTEGER size;
    UInt32        encrypted;
    LARGE_INTEGER origsize;
    LARGE_INTEGER compsize;
    UInt16        namelen;
    WChar         filename[1];
} SXP3InfoInfo;

typedef struct
{
    UInt32        tag;     // 'info'
    LARGE_INTEGER size;
    UInt32        encrypted;
    LARGE_INTEGER origsize;
    LARGE_INTEGER compsize;
    UInt16        namelen;
    PWChar        filename;
} SXP3InfoInfo2;

typedef struct
{    
    Bool          bZlib;     // bZlib & 7 -> 1: compressed  0: raw  other: error
    LARGE_INTEGER offset;
    LARGE_INTEGER origsize;
    LARGE_INTEGER compsize;
} SXP3InfoSegmData;

typedef struct
{
    UInt32        tag;     // 'segm'
    LARGE_INTEGER size;
    SXP3InfoSegmData segm[1];
} SXP3InfoSegm;

typedef struct
{
    UInt32        tag; // 'adlr'
    LARGE_INTEGER size;
    UInt32        hash;
} SXP3InfoAdlr;

typedef struct
{
    SXP3InfoFile  file;
    SXP3InfoInfo2 info;
    SXP3InfoSegm  segm;
    SXP3InfoAdlr  adlr;
} SMyXP3Index;

typedef struct
{
    SXP3InfoFile *file;
    SXP3InfoInfo *info;
    SXP3InfoSegm *segm;
    SXP3InfoAdlr *adlr;
} SMyXP3Info;

typedef struct
{
    UInt32      uCount;
    LPVoid      buffer;
    SMyXP3Info *pInfo;
} SMyXP3Entry;
/*
typedef struct
{
    Int32   Encrypt;
    Int32   Compress;
    PCWChar pFileName;
} SPackFileInfo;
*/
typedef struct
{
    UInt32        SizeOfSelf;      // structure size of tTVPXP3ExtractionFilterInfo itself
    LARGE_INTEGER Offset;          // offset of the buffer data in uncompressed stream position
    LPVoid        Buffer;          // target data buffer
    UInt32        BufferSize;      // buffer size in bytes pointed by "Buffer"
    UInt32        FileHash;        // hash value of the file (since inteface v2)
} SXP3ExtractionInfo;

typedef Bool (STDCALL *FDecrypt)(const SXP3ExtractionInfo *pInfo, LPVoid lpExtraInfo);

typedef struct
{
    PWChar   param;
    FDecrypt func;
    LPVoid   extrainfo;
} SParam;

#pragma pack()

Void ReleaseGlobalData();

Bool STDCALL Decrypt_FateSN(const SXP3ExtractionInfo *pInfo, LPVoid lpExtraInfo);
Bool STDCALL Decrypt_Dynamic(const SXP3ExtractionInfo *pInfo, LPVoid lpExtraInfo);

#endif /* _KRKR2_XP3_H_ */
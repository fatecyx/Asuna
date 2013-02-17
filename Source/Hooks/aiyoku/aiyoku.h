#ifndef _AIYOKU_H_e449fbc8_f868_4fa3_912d_668d75f3c9e1
#define _AIYOKU_H_e449fbc8_f868_4fa3_912d_668d75f3c9e1

#include "pragma_once.h"
#include <Windows.h>
#include "my_headers.h"

#define BGI_DECOMPRESS_BUFFER_SIZE  0x4000000
#define MY_BURIKO_SCRIPT_MAGIC      "UCLCompressLE32"
#define BGI_WINDOW_CLASS            "BGI - Main Window SC"
#define BGI_FONT_1                  "ºÚÌå"
#define BGI_FONT_2                  "ËÎÌå"

#pragma pack(1)

typedef struct
{
    CHAR    FileName[0x10];
    ULONG   Offset;
    ULONG   Size;
    ULONG   Unknown1;
    ULONG   DataSize;
} BGI_ARC_ENTRY;

typedef struct
{
    ULONG cbSize;
    ULONG Magic;            // == TAG4('bw  ')
    ULONG OggSteamSize;
    ULONG Samples;
    ULONG Rate;
    ULONG Channels;
    BYTE  Unknown1[0x18];
    ULONG State;
    BYTE  Unknown2[0xC];
} BGI_SOUND_HEADER;

typedef struct
{
    PVOID           pVTable;
    BOOL            bInit;
    ULONG           Unknown;
    CHAR            FileName[MAX_PATH];
    ULONG           FileCount;
    ULONG           BeginOffset;
    BGI_ARC_ENTRY  *pEntries;
} BGI_ARC_INFO;

typedef struct
{
    PVOID vtbl;
    ULONG Unknown[3];
    ULONG State;
    PVOID pvBuffer;
    ULONG Size;
    ULONG Offset;
} BGI_MEMORY_STREAM;

#pragma pack()

#endif // _AIYOKU_H_e449fbc8_f868_4fa3_912d_668d75f3c9e1
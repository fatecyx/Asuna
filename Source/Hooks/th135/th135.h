#ifndef _TH135_H_a65cd04b_f9a5_442f_aef7_dd7d4c111ca3_
#define _TH135_H_a65cd04b_f9a5_442f_aef7_dd7d4c111ca3_

#include "MyLibrary.h"

#pragma pack(push, 1)

class PakFileObject
{
public:
    BYTE    PakBuffer[0x10000]; // 0x00004

    ULONG   BufferSize;         // 0x10004
    ULONG   Size;               // 0x10008
    HANDLE  FileHandle;         // 0x1000C
    ULONG   CurrentOffset;      // 0x10010

    struct
    {
        ULONG   Offset;             // 0x10014
        ULONG   Size;               // 0x10018
        ULONG   Hash;               // 0x1001C
        ULONG   Unknown;            // 0x10020
        ULONG   DecKeyIndex;        // 0x10024
        BYTE    DecryptKey[0x10];   // 0x10028
        BYTE    DecryptKeyPad[0x4]; // 0x10038

    } FileInfo;

public:

    virtual ~PakFileObject();
    virtual BOOLEAN THISCALL OpenX(PVOID Stl6String);
    virtual BOOLEAN THISCALL Open(PCSTR FileName);
    virtual VOID    THISCALL Unknown();
    virtual BOOLEAN THISCALL DecRead(PVOID Buffer, ULONG Size);
    virtual ULONG   THISCALL Seek(ULONG Offset, ULONG Origin);
};

class PakFileObject2
{
public:
    PakFileObject Pak;

public:
    virtual ~PakFileObject2();
};

typedef struct
{
    ULONG Hash;
    ULONG Offset;
    ULONG Size;
    ULONG Reserve;
    BYTE  Key[0x10];

} TH135_PAKCN_ENTRY, *PTH135_PAKCN_ENTRY;

typedef struct
{
    ULONG Count;
    ULONG Reserve[3];
    TH135_PAKCN_ENTRY Entry[1];

} TH135_PAKCN, *PTH135_PAKCN;

#pragma pack(pop)

#pragma pack(push, 4)

typedef struct
{
    BYTE    Bpp;
    ULONG   PadWidth;
    ULONG   Height;
    ULONG   Width;
    PVOID   Buffer;

} TH135_IMAGE_OBJECT, *PTH135_IMAGE_OBJECT;

#pragma pack(pop)

typedef
BOOL
(STDCALL
*ReadTFBMRoutine)(
    PVOID               Unknown,
    PakFileObject*      Pak,
    PULONG              Width,
    PULONG              Height,
    PTH135_IMAGE_OBJECT ImageObject,
    PULONG              FileNameHash
);

typedef
BOOLEAN
(FASTCALL
*UncompressTFBMRoutine)(
    PakFileObject*      Pak,
    PVOID,
    PTH135_IMAGE_OBJECT ImageObject,
    PULONG              FileMagic
);

#endif // _TH135_H_a65cd04b_f9a5_442f_aef7_dd7d4c111ca3_

#ifndef _TCM_H_ee5a064d_bcf3_46f2_ab84_5bdcad5e0c2f_
#define _TCM_H_ee5a064d_bcf3_46f2_ab84_5bdcad5e0c2f_

#include "MyLibrary.h"

typedef struct StlString
{
    ULONG _;

    union
    {
        CHAR LocalBuffer[0x10];
        PSTR Buffer;
    };

    ULONG Length;
    ULONG MaximumLength;

    PSTR GetBuffer()
    {
        return Length > countof(LocalBuffer) - 1 ? Buffer : LocalBuffer;
    }

} StlString, *PStlString;

typedef struct
{
    PVOID Reserved;
    PBYTE Begin;
    PBYTE End;
    PBYTE _End;

    ULONG Hash; // extended

} MemoryStream, *PMemoryStream;

typedef struct
{
    DUMMY_STRUCT(0x20);

    PMemoryStream Stream;

} FileObject, *PFileObject;

typedef struct FileObject2
{
    DUMMY_STRUCT(0xC);

    FileObject File;

} FileObject2, *PFileObject2;

class ClassMethodWrapper
{
public:
    VOID THISCALL CacheFile(PMemoryStream *Stream, PStlString Name);
};

typedef struct TEXTBIN_ENTRY
{
    ULONG Offset    : 31;
    ULONG Decrypted : 1;
    ULONG Length;
    CHAR  Text[1];

    TEXTBIN_ENTRY* Next()
    {
        return PtrAdd(this, ROUND_UP(Length + 1, 4) + sizeof(ULONG) + sizeof(Length));
    }

} *PTEXTBIN_ENTRY;

typedef struct
{
    ULONG           Count;
    ULONG           Hash;
    TEXTBIN_ENTRY   Entry[1];

} *PTEXTBIN_HEADER;

#endif // _TCM_H_ee5a064d_bcf3_46f2_ab84_5bdcad5e0c2f_

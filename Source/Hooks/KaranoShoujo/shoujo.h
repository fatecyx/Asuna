#ifndef _SHOUJO_H_
#define _SHOUJO_H_

#include "my_headers.h"
#include "gal_common.h"

#pragma pack(1)

typedef struct
{
    UInt32 Reserve;
    PChar  pszString;
    UInt32 Length;
    UInt32 MaxLength;
} SKaraString;

typedef struct
{
    DUMMY_STRUCT(0x20);
    UInt32 Offset;
    UInt32 EncryptFlags;
    UInt32 Size;
    UInt32 EncryptSize;
} SKaraFindFileInfo;

typedef struct
{
    LPVoid  lpVTable;
    HGLOBAL hGlobal;
    UInt32  FileSize;
    UInt32  Reserve;
    LPVoid  lpUnknown;
    PChar   pszFileName;
} SKaraMemoryStream;

#pragma pack()

#endif /* _SHOUJO_H_ */
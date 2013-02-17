#ifndef _GIFT_H_
#define _GIFT_H_

#include "my_common.h"

#pragma pack(1)

typedef struct
{
    Char   magic[8];
    Char   unknown[0x30];
    UInt32 FileNum;
    Char   unknown1[4];
} SGiftPakHeader;

typedef struct
{
    Char   name[0x30];
    UInt32 unknown;
    UInt32 offset;
    UInt32 size;
    UInt32 unknown1;
} SGiftPakIndex;

#pragma pack()

#endif /* _GIFT_H_ */
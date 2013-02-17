#ifndef SHA2_H
#define SHA2_H

#include "my_types.h"

_MY_C_HEAD_

Void STDCALL sha256(PByte message, UInt len, PByte digest);

_MY_C_TAIL_

#endif /* !SHA2_H */
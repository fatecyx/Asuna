#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "NativeApi.h"

_MY_C_HEAD_

VOID
NTAPI
RegisterSystemThread(
    ULONG Flags,
    ULONG Reserve       // must be zero
)
{
}

_MY_C_TAIL_
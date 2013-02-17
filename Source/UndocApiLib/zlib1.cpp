#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "MyLibraryUser.h"

_MY_C_HEAD_

LONG
CDECL
uncompress(
    PBYTE   Destination,
    PULONG  DestinationLength,
    PBYTE   Source,
    ULONG   SourceLength
)
{
    return 0;
}

LONG
CDECL
compress2(
    PBYTE   Destination,
    PULONG  DestinationLength,
    PBYTE   Source,
    ULONG   SourceLength,
    LONG    Level
)
{
    return 0;
}

_MY_C_TAIL_

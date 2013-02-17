#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "MyLibraryUser.h"

_MY_C_HEAD_

int STDCALL UCIDecode(const void *src, int srclen, void** dst, int* stride, int* w, int* h, int* bpp)
{
    return 0;
}

int STDCALL UCIFree(void* p)
{
    return 0;
}

BOOL STDCALL IsSupported(PSTR FileName, ULONG_PTR Flags)
{
    return 0;
}

LONG STDCALL GetPluginInfo(LONG InfoIndex, PSTR Buffer, LONG BufferLength)
{
    return 0;
}

int
STDCALL
GetPicture(
    LPSTR buf,
    long len,
    unsigned int flag,
    HANDLE *pHBInfo,
    HANDLE *pHBm,
    FARPROC lpPrgressCallback,
    long lData
)
{
    return 0;
}

_MY_C_TAIL_

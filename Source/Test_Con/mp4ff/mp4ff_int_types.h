#ifndef _MP4FF_INT_TYPES_H_
#define _MP4FF_INT_TYPES_H_

#if defined (_WIN32)

#include "my_headers.h"

#define malloc(n)       HeapAlloc(CMem::GetGlobalHeap(), 0, n)
#define realloc(p, n)   HeapReAlloc(CMem::GetGlobalHeap(), 0, p, n)
#define free(p)         HeapFree(CMem::GetGlobalHeap(), 0, p)

#ifdef __MINGW32__
#include <stdlib.h>
#endif /* #ifdef __MINGW32__ */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed long int32_t;
typedef unsigned long uint32_t;

typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;

#else

#include <stdint.h>

#endif


#endif

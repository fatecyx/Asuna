#ifndef _MY_MEM_H_
#define _MY_MEM_H_

#include "my_common.h"
#if !defined(_MY_NTLIB_DLL_) && !defined(_MY_NTLIB_)
    #pragma comment(lib, "MyLib.lib")
#else
    #include <memory.h>
//    #include "nt_defs.h"
#endif

_MY_C_HEAD_

FORCEINLINE void* STDCALL memcpy_inline(void *dst, const void *src, size_t count)
{
	__asm
	{
		mov  edi, dst;
		mov  esi, src;
		mov  ecx, count;
		mov  edx, ecx;
		shr  ecx, 2;
		rep  movsd;
		mov  ecx, edx;
		and  ecx, 3;
		rep  movsb;
	}

	return dst;
}

FORCEINLINE void * STDCALL memset_inline(void* dest, byte_t c, size_t count)
{
	uint_32 c1;

	c1 = c | (uint_32)(c << 8) | (uint_32)(c << 16) | (uint_32)(c << 24);

	__asm
	{
		mov  edi, dest;
		mov  eax, c1;
		mov  ecx, count;
		mov  edx, ecx;
		shr  ecx, 2;
		rep  stosd;
		mov  ecx, edx;
		and  ecx, 3;
		rep  stosb;
	}

	return dest;
}

FORCEINLINE bool STDCALL memcmp_inline(const void *m1, const void *m2, size_t n)
{
	bool r;

	if (!n) return 0;

	__asm
	{
		mov   ecx, n;
		mov   edx, ecx;
		mov   edi, m1;
		mov   esi, m2;
		shr   ecx, 2;
		repe  cmpsd;
		jnz   _end;
		mov   ecx, edx;
		and   ecx, 3;
		repe  cmpsb;
		setne r;
_end:
	}

	return r;
}

_MY_C_TAIL_

#ifdef memcpy
    #undef memcpy
#endif /* memcpy */

//#ifdef memcpy
//    #undef memcpy
//#endif /* memcpy */

#ifdef memset
    #undef memset
#endif /* memset */

//#define memcmp memcmp_inlineine
#define memcpy memcpy_inline
#define memset memset_inline
#ifdef ZeroMemory
    #undef ZeroMemory
#endif /* ZeroMemory */
#ifdef CopyMemory
#undef CopyMemory
#endif /* CopyMemory */
#ifdef RtlCopyMemory
    #undef RtlCopyMemory
#endif /* RtlCopyMemory */

#define ZeroMemory(Destination, Length) memset((void *)(Destination), 0, (Length))
#define CopyMemory(Destination, Source, Length) memcpy((void *)(Destination), (void *)(Source), (size_t)(Length))
#define RtlCopyMemory CopyMemory

#endif /* _MY_MEM_H_ */
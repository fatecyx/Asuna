#ifndef _MY_MEM_H_
#define _MY_MEM_H_

#include "my_types.h"
#include "my_crt.h"
//#include "nt_api.h"

#if !defined(_MY_NTLIB_DLL_) && !defined(_MY_NTLIB_)
//    #pragma comment(lib, "MyLib.lib")
#else
    #include <memory.h>
    #include "nt_defs.h"
#endif

#pragma warning(disable:4127)

_MY_C_HEAD_

inline LPVoid FASTCALL my_memcpy_x86(LPVoid lpDest, LPVoid lpSrc, UInt32 nByteToCopy);
inline LPVoid my_memcpy_mmx(LPVoid lpDest, LPVoid lpSrc, UInt32 nByteToCopy);
inline LPVoid my_memcpy_sse(void *Dest, const void *Src, size_t nBytes);
inline LPVoid my_memcpy_detect(LPVoid lpDest, LPVoid lpSrc, UInt32 nByteToCopy);

ForceInline LPVoid CDECL memxor(LPVoid dst, Byte c, size_t count)
{
    UInt32 c1;
    PByte pDest = (PByte)dst;

	c1 = c | (UInt32)(c << 8) | (UInt32)(c << 16) | (UInt32)(c << 24);
    while (count & 3)
        pDest[--count] ^= c1;
    while (count)
        *(PUInt32)&pDest[count -= 4] ^= c1;
    return dst;
}

ForceInline LPVoid CDECL memxor4(LPVoid dst, UInt32 c, size_t count)
{
    PByte pDest = (PByte)dst;

    while (count & 3)
        pDest[--count] ^= c;
    while (count)
        *(PUInt32)&pDest[count -= 4] ^= c;

    return dst;
}

ForceInline LPVoid CDECL memand(LPVoid dst, Byte c, size_t count)
{
    UInt32 c1;
    PByte pDest = (PByte)dst;

    c1 = c | (UInt32)(c << 8) | (UInt32)(c << 16) | (UInt32)(c << 24);
    while (count & 3)
        pDest[--count] &= c1;
    while (count--)
        *(PUInt32)&pDest[count -= 4] &= c1;
    return dst;
}

ForceInline LPVoid CDECL memor(LPVoid dst, Byte c, size_t count)
{
    UInt32 c1;
    PByte pDest = (PByte)dst;

    c1 = c | (UInt32)(c << 8) | (UInt32)(c << 16) | (UInt32)(c << 24);
    while (count & 3)
        pDest[--count] |= c1;
    while (count--)
        *(PUInt32)&pDest[count -= 4] |= c1;
    return dst;
}

ForceInline LPVoid CDECL my_memcpy_inline(void *dst, const void *src, size_t count)
{
#if 0 || defined(MY_COMPILER_INTEL)
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
#else
    __movsd(dst, src, count >> 2);
    INLINE_ASM
    {
        mov ecx, count;
        and ecx, 3;
        rep movsb;
    }
/*
    if (count & 3)
    {
        size_t count_mod4 = count & ~3;
        __movsb((PByte)dst + count_mod4, (PByte)src + count_mod4, count & 3);
    }
*/
#endif

	return dst;
}

ForceInline LPVoid CDECL my_memset_inline(void* dest, Byte c, size_t count)
{
    UInt32 c1 = c | (UInt32)(c << 8) | (UInt32)(c << 16) | (UInt32)(c << 24);
#if defined(MY_COMPILER_INTEL) || !defined(MY_COMPILER_MSC)
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
#else
    __stosd(dest, c1, count >> 2);
    INLINE_ASM
    {
        mov ecx, count;
        and ecx, 3;
        rep stosb;
    }
/*
    if (count & 3)
    {
        size_t count_mod4 = count & ~3;
        __stosb((PByte)dest + count_mod4, (Byte)c1, count & 3);
    }
*/
#endif

	return dest;
}

ForceInline LPVoid CDECL memset4(void* dest, UInt32 c, size_t count)
{
#if defined(MY_COMPILER_INTEL) || !defined(MY_COMPILER_MSC)
    __asm
    {
        mov  edi, dest;
        mov  eax, c;
        mov  ecx, count;
        mov  edx, ecx;
        shr  ecx, 2;
        rep  stosd;
        mov  ecx, edx;
        and  ecx, 3;
        rep  stosb;
    }
    return dest;
#else
    __stosd(dest, c, count >> 2);
    return dest;
#endif
}

ForceInline LPVoid CDECL memset2(void* dest, UInt16 c, size_t count)
{
    UInt32 c1 = c | (c << 16);
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

ForceInline LPVoid FASTCALL ZeroMemoryMMX(void *__Dest__, size_t nBytes)
{
    __asm
    {
            mov     edi, __Dest__
            mov     ecx, nBytes
            shr     ecx, 6                  ; nBytes / 64
            jz      Memset_FinishLoop

            pxor    mm0, mm0;
            pxor    mm1, mm1;
            pxor    mm2, mm2;
            pxor    mm3, mm3;
            pxor    mm4, mm4;
            pxor    mm5, mm5;
            pxor    mm6, mm6;
            pxor    mm7, mm7;

Memset_Loop:
            movq    qword ptr[edi], mm0
            movq    qword ptr[edi+8*1], mm1
            movq    qword ptr[edi+8*2], mm2
            movq    qword ptr[edi+8*3], mm3
            movq    qword ptr[edi+8*4], mm4
            movq    qword ptr[edi+8*5], mm5
            movq    qword ptr[edi+8*6], mm6
            movq    qword ptr[edi+8*7], mm7
            add     esi, 64
            add     edi, 64
            dec     ecx
            jnz     Memset_Loop
            emms

Memset_FinishLoop:
            xor     eax, eax;
            mov     ecx, nBytes
            and     ecx, 63
            shr     ecx, 2
            jz      Memset_End
            rep     stosd;
            mov     ecx, nBytes
            and     ecx, 3;
            jz      Memset_End;
            rep     stosb;

Memset_End:
    }

    return __Dest__;
}

#pragma intrinsic(memcmp, memcpy, memset)

_MY_C_TAIL_

#pragma warning(default:4127)

#if !defined(NOT_USE_CUSTOM_MEMFUNC)

#ifdef memcpy
    #undef memcpy
#endif /* memcpy */

#ifdef memset
    #undef memset
#endif /* memset */

//    #define memcpy my_memcpy_detect
    #define memcpy my_memcpy_inline
    #define memset my_memset_inline
#endif // NOT_USE_CUSTOM_MEMFUNC

#ifdef ZeroMemory
    #undef ZeroMemory
#endif /* ZeroMemory */
#ifdef CopyMemory
    #undef CopyMemory
#endif /* CopyMemory */
#ifdef RtlCopyMemory
    #undef RtlCopyMemory
#endif /* RtlCopyMemory */

#define CompareMemory(Buffer1, Buffer2, SizeInBytes) memcmp((void *)(Buffer1), (void *)(Buffer2), (size_t)(SizeInBytes))
#define ZeroMemory(Destination, Length) memset((void *)(Destination), 0, (Length))
#define CopyMemory(Destination, Source, Length) memcpy((void *)(Destination), (void *)(Source), (size_t)(Length))
#define RtlCopyMemory CopyMemory
#undef RtlMoveMemory

//EXTC DECL_IMPORT PVoid STDCALL RtlCopyMappedMemory(PVOID Destination, PVOID Source, SIZE_T Length);
EXTC DECL_IMPORT Void STDCALL RtlMoveMemory(PVOID Destination, PVOID Source, SIZE_T Length);

#endif /* _MY_MEM_H_ */
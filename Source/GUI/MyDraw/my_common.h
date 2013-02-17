#ifndef _MY_COMMON_H_
#define _MY_COMMON_H_


/************************************************************************/
/*  编译器设定                                                   */
/************************************************************************/
#if _MSC_VER < 1300
    #define for if(1) for
#endif /* fix vc6 for bug */

#ifndef EXTC
    #ifdef __cplusplus
        #define EXTC extern "C"
        #define extc EXTC __declspec(dllimport)
    #else
        #define EXTC 
        #define extc 
    #endif
#endif /* EXTC */

#ifndef ASM
    #define ASM __declspec(naked)
#endif /* ASM */

#ifdef _MY_NTLIB_DLL_
    #define MY_DLL_EXPORT __declspec(dllexport)
#else
    #define MY_DLL_EXPORT 
#endif  // _MY_NTLIB_DLL_

#ifndef DLL_IMPORT
    #define DLL_IMPORT __declspec(dllimport)
#endif /* DLL_IMPORT */

/* C++ 下的函数修饰 */
#ifdef  __cplusplus
    #define _MY_C_HEAD_     extern "C" {
    #define _MY_C_TAIL_     }
#else
    #define _MY_C_HEAD_ 
    #define _MY_C_TAIL_ 
#endif /* _MY_C_HEAD_ */

#ifndef FORCEINLINE
    #define FORCEINLINE __forceinline
#endif /* FORCEINLINE */

#ifndef NOINLINE
    #define NOINLINE __declspec(noinline)
#endif /* NOINLINE */

#ifdef CDECL
    #undef CDECL
#endif /* CDECL */
#define CDECL __cdecl

#ifdef STDCALL
    #undef STDCALL
#endif /* STDCALL */
#define STDCALL __stdcall

#ifdef VOID
    #undef VOID
#endif /* VOID */
typedef void VOID;

/************************************************************************/
/*  有用的宏                                                     */
/************************************************************************/
#ifndef countof
    #define countof(x) sizeof((x)) / sizeof(*(x))
#endif /* countof */

typedef char                int_8;
typedef unsigned char   uint_8, byte_t;
typedef char                int_8;
typedef unsigned short  uint_16;

#ifdef WIN32
typedef long                int_32;
typedef unsigned long   uint_32;

#else
typedef int                 int_32;
typedef unsigned int     uint_32;
#endif /* WIN32 */

#ifndef __cplusplus
    typedef unsigned char bool;
#endif /* __cplusplus */

typedef struct
{
    uint_32 dwData;
    uint_32 dwSize;
    uint_32 dwOffset;
} TPatch;

#define NOP  0x90
#define CALL 0xE8
#define JUMP 0xE9

typedef struct
{
    byte_t  byFlag;
    uint_32 dwOffset;
    uint_32 dwFunc;
    byte_t  nNop;
} TFuncPatch;

#ifndef PATCH_FRAME
    #define PATCH_FRAME(patch, patch_count, func, func_count, base_address) \
        if (patch != NULL) \
            for (int i = 0; i != patch_count; ++i) \
            { \
                if (base_address != 0) (((TPatch *)patch)[i]).dwOffset += ((uint_32)base_address); \
                memcpy((void *)(((TPatch *)patch)[i]).dwOffset, \
                       &(((TPatch *)patch)[i]).dwData, \
                       (((TPatch *)patch)[i]).dwSize); \
            } \
        if (func != NULL) \
            for (int i = 0; i != func_count; ++i) \
            { \
                if (base_address != 0) (((TFuncPatch *)func)[i]).dwOffset += ((uint_32)base_address); \
                *(PBYTE)(((TFuncPatch *)func)[i]).dwOffset = (((TFuncPatch *)func)[i]).byFlag; \
                *(LPDWORD)((((TFuncPatch *)func)[i]).dwOffset + 1) = \
                    (((TFuncPatch *)func)[i]).dwFunc - ((((TFuncPatch *)func)[i]).dwOffset + 5); \
                memset((void *)((((TFuncPatch *)func)[i]).dwOffset + 5), \
                        (byte_t)NOP, (((TFuncPatch *)func)[i]).nNop); \
            }

#endif // PATCH_FRAME


#if !defined(_WIN32_WINNT)
    #define _WIN32_WINNT 0x0502
#endif /* _WIN32_WINNT */

#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && defined(_M_IX86)
    #define _X86_
#endif

#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && defined(_M_AMD64)
    #define _AMD64_
#endif

#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && defined(_M_M68K)
    #define _68K_
#endif

#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && defined(_M_MPPC)
    #define _MPPC_
#endif

#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_M_IX86) && !defined(_AMD64_) && defined(_M_IA64)
#if !defined(_IA64_)
    #define _IA64_
#endif /* !_IA64_ */
#endif

#ifndef _MAC
#if defined(_68K_) || defined(_MPPC_)
    #define _MAC
#endif
#endif

#endif /* _MY_COMMON_H_ */
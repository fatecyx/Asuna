#ifndef _MY_COMMON_H_
#define _MY_COMMON_H_

#if defined(__INTEL_COMPILER)
    #define MY_COMPILER_INTEL __INTEL_COMPILER
    #define MY_COMPILER_MSC 1500
#elif defined(_MSC_VER)
    #define MY_COMPILER_MSC _MSC_VER
#endif // compiler

/************************************************************************/
/*  编译器设定                                                          */
/************************************************************************/
#pragma warning(disable:4530)

#if MY_COMPILER_MSC < 1300
    #define for if(1) for
#endif /* fix vc6 for bug */

#ifndef CPP_DEFINED
    #ifdef __cplusplus
        #define CPP_DEFINED 1
    #else
        #define CPP_DEFINED 0
    #endif
#endif // CPP_DEFINED

#define USE_STACK_FRAME_POINTER   "y", off
#define UNUSE_STACK_FRAME_POINTER "y", on

#if !defined(IF_EXIST)
    #define IF_EXIST __if_exists
#endif /* IF_EXIST */

#if !defined(IF_NOT_EXIST)
    #define IF_NOT_EXIST __if_not_exists
#endif /* IF_NOT_EXIST */

#if !defined(typedef_s)
    #define typedef_s(s, d) IF_NOT_EXIST(d) { typedef s d; }
    #define typedef_s2(s, ...) IF_NOT_EXIST(d) { typedef s __VA_ARGS__; }
#endif /* typedef_s */

#ifndef EXTCPP
    #ifdef __cplusplus
        #define EXTCPP extern "C++"
    #else
        #define EXTCPP
    #endif
#endif /* EXTCPP */

#ifndef NOVTABLE
    #define NOVTABLE __declspec(novtable)
#endif /* NOVTABLE */

#ifndef ASM
    #define ASM __declspec(naked)
#endif /* ASM */

#if !defined(INLINE_ASM)
    #define INLINE_ASM __asm
#endif /* INLINE_ASM */

#ifndef MY_DLL_EXPORT
    #define MY_DLL_EXPORT __declspec(dllexport)
#endif  /* MY_DLL_EXPORT */

#ifdef _MY_NTLIB_DLL_
    #define MY_NTLIB_DLL_EXPORT __declspec(dllexport)
#else
    #define MY_NTLIB_DLL_EXPORT
#endif  /* _MY_NTLIB_DLL_ */

#ifndef MY_DLL_IMPORT
    #define MY_DLL_IMPORT __declspec(dllimport)
#endif /* MY_DLL_IMPORT */

#if !defined(MY_CRT_IMPORT)
    #if defined(_DLL)
        #define MY_IMPORT MY_DLL_IMPORT
    #else
        #define MY_IMPORT
    #endif
#endif /* MY_CRT_IMPORT */

#define MY_LIB_NAME MY_LIB

/* C++ 下的函数修饰 */
#ifdef  __cplusplus
    #define _MY_C_HEAD_     extern "C" {
    #define _MY_C_TAIL_     }
    #define MY_NAMESPACE_BEGIN(name) namespace name {
    #define MY_NAMESPACE_END }
    #define DEFAULT_VALUE(type, var, value) type var = value
#else
    #define _MY_C_HEAD_
    #define _MY_C_TAIL_
    #define MY_NAMESPACE_BEGIN(name)
    #define MY_NAMESPACE_END
    #define DEFAULT_VALUE(type, var, value) type var
#endif /* _MY_C_HEAD_ */

#ifndef ForceInline
    #if (MY_COMPILER_MSC >= 1200)
        #define ForceInline __forceinline
    #else
        #define ForceInline __inline
    #endif
#endif /* ForceInline */

#ifndef NoInline
    #if (MY_COMPILER_MSC >= 1300)
        #define NoInline __declspec(noinline)
    #else
        #define NoInline
    #endif
#endif /* NoInline */

#if (defined(_M_IX86) || defined(_M_IA64) || defined(_M_AMD64)) && !defined(MIDL_PASS)
    #define DECL_IMPORT __declspec(dllimport)
    #define DECL_EXPORT __declspec(dllexport)
#else
    #define DECL_IMPORT
    #define DECL_EXPORT
#endif

#if !defined(DISABLE_SEH)
    #define SEH_TRY     __try
    #define SEH_FINALLY __finally
    #define SEH_EXCEPT(...)  __except(__VA_ARGS__)
#else
    #define SEH_TRY
    #define SEH_FINALLY
    #define SEH_EXCEPT(...) for (int __c_false = 0; __c_false; )
#endif // DISABLE_SEH

#ifndef EXTC
    #ifdef __cplusplus
        #define EXTC extern "C"
        #define EXTC_IMPORT EXTC __declspec(dllimport)
        #define EXTC_EXPORT EXTC DECL_EXPORT
    #else
        #define EXTC
        #define EXTC_IMPORT __declspec(dllimport)
    #endif
#endif /* EXTC */

#ifndef DECL_NORETURN
    #if (MY_COMPILER_MSC >= 1200) && !defined(MIDL_PASS)
        #define DECL_NORETURN   __declspec(noreturn)
    #else
        #define DECL_NORETURN
    #endif
#endif

#ifndef DECL_NOTHROW
    #if (MY_COMPILER_MSC >= 1200) && !defined(MIDL_PASS)
        #define DECL_NOTHROW   __declspec(nothrow)
    #else
        #define DECL_NOTHROW
    #endif
#endif

#ifndef DECL_ALIGN
    #if (MY_COMPILER_MSC >= 1300) && !defined(MIDL_PASS)
        #define DECL_ALIGN(x)   __declspec(align(x))
    #else
        #define DECL_ALIGN(x)
    #endif
#endif

#ifndef SYSTEM_CACHE_ALIGNMENT_SIZE
    #if defined(_AMD64_) || defined(_X86_)
        #define SYSTEM_CACHE_ALIGNMENT_SIZE 64
    #else
        #define SYSTEM_CACHE_ALIGNMENT_SIZE 128
    #endif
#endif

#ifndef DECL_CACHEALIGN
    #define DECL_CACHEALIGN DECL_ALIGN(SYSTEM_CACHE_ALIGNMENT_SIZE)
#endif

#ifndef DECL_UUID
    #if (MY_COMPILER_MSC >= 1100) && defined (__cplusplus)
        #define DECL_UUID(x)    __declspec(uuid(x))
    #else
        #define DECL_UUID(x)
    #endif
#endif

#ifndef DECL_NOVTABLE
    #if (MY_COMPILER_MSC >= 1100) && defined(__cplusplus)
        #define DECL_NOVTABLE   __declspec(novtable)
    #else
        #define DECL_NOVTABLE
    #endif
#endif

#ifndef DECL_SELECTANY
    #if (MY_COMPILER_MSC >= 1100)
        #define DECL_SELECTANY  __declspec(selectany)
    #else
        #define DECL_SELECTANY
    #endif
#endif

#ifndef NOP_FUNCTION
    #if (MY_COMPILER_MSC >= 1210)
        #define NOP_FUNCTION __noop
    #else
        #define NOP_FUNCTION (void)0
    #endif
#endif

#ifndef DECL_ADDRSAFE
    #if (MY_COMPILER_MSC >= 1200) && (defined(_M_ALPHA) || defined(_M_AXP64))
        #define DECL_ADDRSAFE  __declspec(address_safe)
    #else
        #define DECL_ADDRSAFE
    #endif
#endif

#ifndef DECL_DEPRECATED
    #if (MY_COMPILER_MSC >= 1300) && !defined(MIDL_PASS)
        #define DECL_DEPRECATED   __declspec(deprecated)
        #define DEPRECATE_SUPPORTED
    #else
        #define DECL_DEPRECATED
        #undef  DEPRECATE_SUPPORTED
    #endif
#endif

#if !defined(DECL_THREAD) && (defined(MY_COMPILER_MSC) || defined(__INTEL_COMPILER))
    #define DECL_THREAD __declspec(thread)
#endif // DECL_THREAD

#ifndef UNUSED_VARIABLE
    #define UNUSED_VARIABLE(Var) IF_EXIST(Var) { (Var); }
#endif // UNUSED_VARIABLE

#ifndef True
    #define True 1l
#endif /* True */

#ifndef False
    #define False 0l
#endif /* False */

#ifndef NULL
    #define NULL 0l
#endif /* NULL */

#ifdef CDECL
    #undef CDECL
#endif /* CDECL */
#define CDECL __cdecl

#ifdef STDCALL
    #undef STDCALL
#endif /* STDCALL */
#define STDCALL __stdcall

#ifdef FASTCALL
    #undef FASTCALL
#endif /* STDCALL */
#define FASTCALL __fastcall

#ifdef THISCALL
    #undef THISCALL
#endif
#ifdef MY_COMPILER_MSC
    #define THISCALL __thiscall
#else
    #define THISCALL
#endif

#ifndef OPTIONAL
    #define OPTIONAL
#endif /* OPTIONAL */

#if !defined(INTEL_STATIC)
    #if defined(__INTEL_COMPILER)
        #define INTEL_STATIC static
    #else
        #define INTEL_STATIC 
    #endif
#endif /* INTEL_STATIC */

#if !defined(DEBUG_BREAK_POINT)
#if defined(MY_DEBUG)
    #define DEBUG_BREAK_POINT() __asm int 3
#else
    #define DEBUG_BREAK_POINT()
#endif /* MY_DEBUG */
#endif /* DebugBreakPoint */

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
#endif /* _MAC */

#if (defined(_AMD64_) || defined(_IA64_))
    #define MY_X64
#endif

#endif /* _MY_COMMON_H_ */
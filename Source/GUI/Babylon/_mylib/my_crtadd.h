#ifndef _MY_CRTADD_H_
#define _MY_CRTADD_H_

#define _CRT_SECURE_NO_WARNINGS

#include "crt_h.h"
#include "my_types.h"
#include "my_macros.h"
#include "my_algo.h"

#pragma warning(disable:4127)
#pragma warning(disable:4047)
#pragma warning(disable:4706)

_MY_C_HEAD_

#define CopyStruct(dest, src, size) \
    { \
        typedef DECL_ALIGN(1) struct { Byte b[size]; } _SDummy; \
        *(_SDummy *)(dest) = *(_SDummy *)(src); \
    } 
#if 0
    else \
    { \
        memcpy(dest, src, size); \
    }
#endif

#define ZeroStruct(dest) ZeroMemory((dest), sizeof(*(dest)));

ForceInline void* AllocStack(size_t Size)
{
    return _alloca(ROUND_UP(Size, 16));
}

inline HANDLE GetHandleFromFP(const FILE *fp)
{
    return (HANDLE)_get_osfhandle(fp->_file);
/*

typedef struct
{
    Long   osfhnd;  // underlying OS file HANDLE
    Char   osfile;  // attributes of file (e.g., open in text mode?)
    Char   pipech;  // one   char buffer for handles opened on pipes
#ifdef _MT
    Int   lockinitflag;
    CRITICAL_SECTION   lock;
#endif
}ioinfo;

#define IOINFO_L2E 5
#define IOINFO_ARRAY_ELTS (1 << IOINFO_L2E)

EXTC_IMPORT ioinfo *__pioinfo[];
    Int fd;
    ioinfo *pioinfo;
    HANDLE hFile;

    fd = fp->_file;
    pioinfo = __pioinfo[fd >> IOINFO_L2E] + (fd & (IOINFO_ARRAY_ELTS - 1));
    hFile = (HANDLE)pioinfo->osfhnd;

    return hFile;
*/
}

/*
inline long STDCALL fsize(const FILE *fp)
{
    int fd;
    ioinfo *pioinfo;
    HANDLE hFile;

    fd = fp->_file;
    pioinfo = __pioinfo[fd >> IOINFO_L2E] + (fd & (IOINFO_ARRAY_ELTS - 1));
    hFile = (HANDLE)pioinfo->osfhnd;

    return Nt_GetFileSize(hFile, NULL);
}
*/

inline Long FASTCALL fsize(FILE *fp)
{
    fseek(fp, 0, SEEK_CUR);
    return _filelength(_fileno(fp));
}

inline Int64 FASTCALL fsize64(FILE *fp)
{
    fseek(fp, 0, SEEK_CUR);
    return _filelengthi64(_fileno(fp));
}

inline Int64 FASTCALL my_fseek64(FILE *fp, Int64 offset, Int origin)
{
    Int64 ret;

    ret = fseek(fp, 0, SEEK_CUR);
    ret = _lseeki64(_fileno(fp), offset, origin);

    return ret == -1 ? 1 : 0;
/*
    HANDLE hFile;
    LARGE_INTEGER liOffset;
    hFile = GetHandleFromFP(fp);
    fseek(fp, 0, SEEK_CUR);

    liOffset.QuadPart = offset;

    if (SetFilePointer(hFile, liOffset.LowPart, &liOffset.HighPart, origin) != -1 ||
        GetLastError() == NO_ERROR)
        return 0;

    return 1;
*/
}

inline Int64 FASTCALL my_ftell64(FILE *fp)
{
    int ret;
    fpos_t pos;

    ret = fseek(fp, 0, SEEK_CUR);
    ret = fgetpos(fp, &pos);

    return ret ? ret : pos;
/*
    HANDLE hFile;
    DWORD  dwErr;
    LARGE_INTEGER liOffset;

    hFile = GetHandleFromFP(fp);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        errno = 9;
        return -1i64;
    }

    fseek(fp, 0, SEEK_CUR);
    liOffset.HighPart = 0;
    liOffset.LowPart = SetFilePointer(hFile, 0, &liOffset.HighPart, FILE_CURRENT);
    if (liOffset.LowPart == -1 && (dwErr = GetLastError()) != NO_ERROR)
    {
//        _dosmaperr(dwErr);
        return -1i64;
    }

    return liOffset.QuadPart;
*/
}

PChar FASTCALL findexta(PCChar lpFileName);
PWChar FASTCALL findextw(PCWChar lpFileName);

inline PTChar findext(LPVoid lpFileName)
{
    return sizeof(*(PTChar)lpFileName) == sizeof(Char) ? (PTChar)findexta((PCChar)lpFileName) : (PTChar)findextw((PCWChar)lpFileName);
}

PChar FASTCALL findnamea(PCChar lpFileName);
PWChar FASTCALL findnamew(PCWChar lpFileName);

inline PTChar findname(PCTChar lpFileName)
{
    return sizeof(*(PTChar)lpFileName) == 1 ? (PTChar)findnamea((PCChar)lpFileName) : (PTChar)findnamew((PCWChar)lpFileName);
}



inline PChar FASTCALL findpath(PCChar szPath)
{
    PChar path;

    path = (PChar)strrchr(szPath, '\\');
    return path;
}

inline PWChar FASTCALL findpathw(PCWChar szPath)
{
    PWChar path;

    path = (PWChar)wcsrchr(szPath, '\\');
    return path;
}

inline PChar FASTCALL rmexta(PChar pszPath)
{
    *findexta(pszPath) = 0;
    return pszPath;
}

inline PWChar FASTCALL rmextw(PWChar pszPath)
{
    *findextw(pszPath) = 0;
    return pszPath;
}

inline PTChar FASTCALL rmext(PTChar pszPath)
{
    if (sizeof(*pszPath) == sizeof(Char))
        return (PTChar)rmexta((PChar)pszPath);
    else
        return (PTChar)rmextw((PWChar)pszPath);
}

inline Void FASTCALL chext(Char *szFileName, Char *pExt)
{
    strcpy(findexta(szFileName), pExt);
}

inline Void FASTCALL chextw(WChar *szFileName, WChar *pExt)
{
    wcscpy(findextw(szFileName), pExt);
}

inline PChar FASTCALL rmname(PChar pszPath)
{
    *findnamea(pszPath) = 0;
    return pszPath;
}

inline PWChar FASTCALL rmnamew(PWChar pszPath)
{
    *findnamew(pszPath) = 0;
    return pszPath;
}

PChar StringUpperA(PChar pszString, DEFAULT_VALUE(ULong, Length, -1));
Int FASTCALL StrLengthA(PCChar pString);
Int FASTCALL SSE2_StrLengthA(PCChar pString);
Int FASTCALL StrLengthW(PCWChar pString);

inline Int FASTCALL StrLength(PCTChar pString)
{
    if (sizeof(TChar) == sizeof(Char))
        return StrLengthA((PCChar)pString);
    else
        return StrLengthW((PCWChar)pString);
}

Int FASTCALL StrNICompareA(PCChar pString1, PCChar pString2, SizeT LengthToCompare);

inline Int FASTCALL StrICompareA(PCChar pString1, PCChar pString2)
{
    return StrNICompareA(pString1, pString2, (SizeT)-1);
}

Int FASTCALL StrNICompareW(PCWChar pString1, PCWChar pString2, SizeT LengthToCompare);

inline Int FASTCALL StrICompareW(PCWChar pString1, PCWChar pString2)
{
    return StrNICompareW(pString1, pString2, (SizeT)-1);
}

inline Int FASTCALL StrNICompare(PCTChar pString1, PCTChar pString2, SizeT LengthToCompare)
{
    if (sizeof(*pString1) == sizeof(Char))
    {
        return StrNICompareA((PCChar)pString1, (PCChar)pString2, LengthToCompare);
    }
    else if (sizeof(*pString1) == sizeof(WChar))
    {
        return StrNICompareW((PCWChar)pString1, (PCWChar)pString2, LengthToCompare);
    }

    return 0;
}

inline Int FASTCALL StrICompare(PCTChar pString1, PCTChar pString2)
{
    return StrNICompare(pString1, pString2, (SizeT)-1);
}

Int FASTCALL StrNCompareA(PCChar pString1, PCChar pString2, SizeT LengthToCompare);

inline Int FASTCALL StrCompareA(PCChar pString1, PCChar pString2)
{
    return StrNCompareA(pString1, pString2, (SizeT)-1);
}

Int FASTCALL StrNCompareW(PCWChar pString1, PCWChar pString2, SizeT LengthToCompare);

inline Int FASTCALL StrCompareW(PCWChar pString1, PCWChar pString2)
{
    return StrNCompareW(pString1, pString2, (SizeT)-1);
}

inline Int FASTCALL StrNCompare(PCTChar pString1, PCTChar pString2, SizeT LengthToCompare)
{
    if (sizeof(*pString1) == sizeof(Char))
    {
//        return StrNCompareA((PCChar)pString1, (PCChar)pString2, LengthToCompare);
    }
    else if (sizeof(*pString1) == sizeof(WChar))
    {
        return StrNCompareW((PCWChar)pString1, (PCWChar)pString2, LengthToCompare);
    }

    return 0;
}

inline Int FASTCALL StrCompare(PCTChar pString1, PCTChar pString2)
{
    return StrNCompare(pString1, pString2, (SizeT)-1);
}

PWChar StrFindCharW(PCWChar lpString, WChar CharMatch);

inline Int32 WINAPI ASMStrLenA(const Char *String)
{
    __asm
    {
        xor  eax, eax;
        lea  ecx, [eax-1];
        mov  edi, String;
        repne scasb;
        lea  eax, dword ptr [ecx+1];
        not  eax;
    }
}

inline Int32 WINAPI ASMStrLenW(const WChar *String)
{
    __asm
    {
        xor  eax, eax;
        lea  ecx, [eax-1];
        mov  edi, String;
        repne scasw;
        lea  eax, dword ptr [ecx+1];
        not  eax;
    }
}

inline PChar SubStrA(const Char *_Src, const Char *_Sub)
{
    return (Char *)KMP(_Src, StrLengthA(_Src), _Sub, StrLengthA(_Sub));
}

inline PWChar SubStrW(const WChar *_Src, const WChar *_Sub)
{
    return (PWChar)KMP(_Src, StrLengthW(_Src) * sizeof(WChar), _Sub, StrLengthW(_Sub) * sizeof(WChar));
}

Int32 fgetsW(PWChar pszOutBuffer, UInt32 cchWideChar, FILE *fp, DEFAULT_VALUE(Bool, bRemoveLinefeed, True));
PWChar PeekLineW(PVoid pBuffer, PVoid pEndOfBuffer, PVoid pOutBuffer, PSizeT pcbOutBuffer);

ForceInline UInt32 FASTCALL Bswap(UInt32 v)
{
    INLINE_ASM
    {
        mov eax, v;
        bswap eax;
    }
}

ForceInline UInt32 FASTCALL GetEfFlags()
{
    INLINE_ASM
    {
        pushfd;
        pop eax;
    }
}

ForceInline UInt32 FASTCALL SetEfFlags(UInt32 EfFlags)
{
    INLINE_ASM
    {
        push EfFlags;
        popfd;
    }
}

ForceInline Void SetDirectionFlag()
{
    INLINE_ASM std;
}

ForceInline Void ClearDirectionFlag()
{
    INLINE_ASM cld;
}

#if !defined(ReadTimeStampCounter)

ForceInline UInt64 ReadTimeStampCounter()
{
    __asm rdtsc;
}

#endif

UInt64 GetRandom64();
UInt32 GetRandom32();
UInt32 GetRandom32Range(UInt32 Min, UInt32 Max);
Int32 StringToInt32A(PCChar pszString);
Int32 StringToInt32W(PCWChar pszString);

inline Int32 StringToInt32(PCTChar pszString)
{
    if (sizeof(*pszString) == sizeof(Char))
        return StringToInt32A((PChar)pszString);
    else
        return StringToInt32W((PWChar)pszString);
}

Int32 StringToInt32HexW(PWChar pszString);
Int64 StringToInt64HexW(PWChar pszString);
Int64 StringToInt64A(PChar pszString);
Int64 StringToInt64W(PCWChar pszString);

inline Int64 FASTCALL StringToInt64(PTChar pszString)
{
    if (sizeof(TChar) == sizeof(Char))
        return StringToInt64A((PChar)pszString);
    else if (sizeof(TChar) == sizeof(WChar))
        return StringToInt64W((PWChar)pszString);

    return 0;
}

inline Bool IsCPUIDValid()
{
    __asm
    {
        pushfd;
        pop eax;
        or eax, 1 << 21;
        push eax;
        popfd;
        pushfd;
        pop eax;
        shr eax, 21;
        and eax, 1;
    }
}

_MY_C_TAIL_

#pragma warning(default:4047)
#pragma warning(default:4127)
#pragma warning(default:4706)

#if CPP_DEFINED

EXTCPP template<class T> ForceInline Void FASTCALL Swap(T &t1, T &t2)
{
    T t;
    t = t1;
    t1 = t2;
    t2 = t;
}

#endif /* __cplusplus */


#if defined(UNICODE) || defined(_UNICODE)

//#define StrLen StrLengthW
#define SubStr SubStrW

#else

//#define StrLen StrLengthA
#define SubStr SubStrA

#endif /* UNICODE */

#endif /* _MY_CRTADD_H_ */
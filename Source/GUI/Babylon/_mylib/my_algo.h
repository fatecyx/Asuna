#ifndef _MY_ALGO_H_
#define _MY_ALGO_H_

#include "my_types.h"
#include <malloc.h>

_MY_C_HEAD_

/************************************************************************/
/* KMP                                                                  */
/************************************************************************/
inline UInt32 FASTCALL InitNext(const Void *lpKeyWord, UInt32 KeyWordLen, Int *piNext)
{
    UInt32 i, j;
    const Char *pDest;

    pDest = (const Char *)lpKeyWord;

    piNext[0] = -1;
    i = 0;
    j = (UInt32)-1;

    while (i < KeyWordLen)
    {
        if (j == -1 || pDest[i] == pDest[j])
            if (pDest[++i] != pDest[++j]) piNext[i] = j;
            else piNext[i] = piNext[j];
            else j = piNext[j];
    }

    return KeyWordLen;
}

inline Void* FASTCALL KMP(const Void *_Src, UInt32 SrcLength, const Void *_KeyWord, UInt32 KeyWordLen)
{
    UInt32 i, j;
    Int32  *Next;//[100];
    PInt32 pNext;
    const Char *pSrc, *pKeyWord;

    Next = (PInt32)_alloca((KeyWordLen + 1) * sizeof(*pNext));
    pNext  = Next;
    pSrc  = (const Char *)_Src;
    pKeyWord = (const Char *)_KeyWord;
    InitNext(_KeyWord, KeyWordLen, pNext);
    i = 0;
    j = 0;
    while (i != SrcLength && j != KeyWordLen)
    {
        if (j == -1 || pSrc[i] == pKeyWord[j])
        {
            ++i;
            ++j;
        }
        else
            j = pNext[j];
    }

    if (i == SrcLength && j != KeyWordLen)
        return NULL;

    return (Void *)(pSrc + i - KeyWordLen);
}

_MY_C_TAIL_

#endif /* _MY_ALGO_H_ */
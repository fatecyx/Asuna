#ifndef _MEMORY_H_1156cf20_60dc_4662_a49d_90980595456c
#define _MEMORY_H_1156cf20_60dc_4662_a49d_90980595456c

#include "pragma_once.h"
#include "../Internal/CG_Memory.h"

class CCGMemory
{
protected:
    HANDLE m_HeapHandle;

public:
    CCGMemory();

    PVOID       Alloc   (SIZE_T Size, ULONG Flags = 0);
    PVOID       ReAlloc (PVOID pMemory, SIZE_T Size, ULONG Flags = 0);
    CGSTATUS    Free    (PVOID pMemory, ULONG Flags = 0);

    CGSTATUS MemoryCopy (PVOID Destination, PVOID Source, SIZE_T Length);
    CGSTATUS MemoryMove (PVOID Destination, PVOID Source, SIZE_T Length);
    CGSTATUS MemoryAnd  (PVOID pBuffer, SIZE_T Length, BYTE AndValue);
    CGSTATUS MemoryOr   (PVOID pBuffer, SIZE_T Length, BYTE OrValue);
    CGSTATUS MemoryXor  (PVOID pBuffer, SIZE_T Length, BYTE XorValue);
    CGSTATUS MemoryAnd4 (PVOID pBuffer, SIZE_T Length, ULONG AndValue);
    CGSTATUS MemoryOr4  (PVOID pBuffer, SIZE_T Length, ULONG OrValue);
    CGSTATUS MemoryXor4 (PVOID pBuffer, SIZE_T Length, ULONG XorValue);

    VOID MemoryAndWorker  (PVOID pBuffer, SIZE_T Length, BYTE AndValue);
    VOID MemoryOrWorker   (PVOID pBuffer, SIZE_T Length, BYTE OrValue);
    VOID MemoryXorWorker  (PVOID pBuffer, SIZE_T Length, BYTE XorValue);
    VOID MemoryAnd4Worker (PVOID pBuffer, SIZE_T Length, ULONG AndValue);
    VOID MemoryOr4Worker  (PVOID pBuffer, SIZE_T Length, ULONG OrValue);
    VOID MemoryXor4Worker (PVOID pBuffer, SIZE_T Length, ULONG XorValue);
};

#endif // _MEMORY_H_1156cf20_60dc_4662_a49d_90980595456c

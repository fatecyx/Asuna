#ifndef _MEMORYI_H_f2c9fa62_7ff0_4b08_a70b_d96fa3250f7c
#define _MEMORYI_H_f2c9fa62_7ff0_4b08_a70b_d96fa3250f7c

#include "pragma_once.h"
#include "../Internal/CG_Headers.h"
#include "Memory.h"

//class CCGMemoryI :  public CCGUnknownImpl<CCGMemoryI>,
//                                public ICelestialGlobeMemory

CG_INTERFACE_FROM_CLASS(CCGMemory, ICGMemory)
{
protected:
    CCGMemory m_Memory;

public:
    CCGMemoryI(ICGUnknown *pUnknownOuter);

    CG_METHOD_TYPE(PVOID, Alloc)    (SIZE_T Size, ULONG Flags = 0);
    CG_METHOD_TYPE(PVOID, ReAlloc)  (PVOID pMemory, SIZE_T Size, ULONG Flags = 0);
    CG_METHOD(Free)                 (PVOID pMemory, ULONG Flags = 0);
    
    CG_METHOD(MemoryCopy)   (PVOID Destination, PVOID Source, SIZE_T Length);
    CG_METHOD(MemoryMove)   (PVOID Destination, PVOID Source, SIZE_T Length);
    CG_METHOD(MemoryAnd)    (PVOID pBuffer, SIZE_T Length, BYTE AndValue);
    CG_METHOD(MemoryOr)     (PVOID pBuffer, SIZE_T Length, BYTE OrValue);
    CG_METHOD(MemoryXor)    (PVOID pBuffer, SIZE_T Length, BYTE XorValue);
    CG_METHOD(MemoryAnd4)   (PVOID pBuffer, SIZE_T Length, ULONG AndValue);
    CG_METHOD(MemoryOr4)    (PVOID pBuffer, SIZE_T Length, ULONG OrValue);
    CG_METHOD(MemoryXor4)   (PVOID pBuffer, SIZE_T Length, ULONG XorValue);
    
    CGSTATUS CG_METHOD_CALLTYPE QueryInterface0(REFIID iid, PVOID *ppvObject);

    CG_IUNKNOWN_IMPLEMENT(CCGMemoryI);
};

#endif // _MEMORYI_H_f2c9fa62_7ff0_4b08_a70b_d96fa3250f7c

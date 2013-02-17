#ifndef _CG_MEMORY_H_99e92e69_0435_453b_b131_44d142b39032
#define _CG_MEMORY_H_99e92e69_0435_453b_b131_44d142b39032

#include "pragma_once.h"
#include "CG_Interface.h"

CG_INTERFACE(ICGMemoryBase)
{
    CG_METHOD_TYPE(PVOID, Alloc)    (THIS_ SIZE_T Size, ULONG Flags = 0) PURE;
    CG_METHOD_TYPE(PVOID, ReAlloc)  (THIS_ PVOID pMemory, SIZE_T Size, ULONG Flags = 0) PURE;
    CG_METHOD(Free)                 (THIS_ PVOID pMemory, ULONG Flags = 0) PURE;

    CG_METHOD(MemoryCopy)   (THIS_ PVOID Destination, PVOID Source, SIZE_T Length) PURE;
    CG_METHOD(MemoryMove)   (THIS_ PVOID Destination, PVOID Source, SIZE_T Length) PURE;
    CG_METHOD(MemoryAnd)    (THIS_ PVOID pBuffer, SIZE_T Length, BYTE AndValue) PURE;
    CG_METHOD(MemoryOr)     (THIS_ PVOID pBuffer, SIZE_T Length, BYTE OrValue) PURE;
    CG_METHOD(MemoryXor)    (THIS_ PVOID pBuffer, SIZE_T Length, BYTE XorValue) PURE;
    CG_METHOD(MemoryAnd4)   (THIS_ PVOID pBuffer, SIZE_T Length, ULONG AndValue) PURE;
    CG_METHOD(MemoryOr4)    (THIS_ PVOID pBuffer, SIZE_T Length, ULONG OrValue) PURE;
    CG_METHOD(MemoryXor4)   (THIS_ PVOID pBuffer, SIZE_T Length, ULONG XorValue) PURE;
};

CG_INTERFACE_(ICGMemory, ICGUnknown, ICGMemoryBase)
{
    // ICGUnknown
    CG_METHOD(QueryInterface)       (THIS_ REFIID iid, PVOID *ppvObject) PURE;
    CG_METHOD_TYPE(ULONG, AddRef)   (THIS) PURE;
    CG_METHOD_TYPE(ULONG, Release)  (THIS) PURE;

    // ICelestialGlobeMemoryBase
    CG_METHOD_TYPE(PVOID, Alloc)    (THIS_ SIZE_T Size, ULONG Flags = 0) PURE;
    CG_METHOD_TYPE(PVOID, ReAlloc)  (THIS_ PVOID pMemory, SIZE_T Size, ULONG Flags = 0) PURE;
    CG_METHOD(Free)                 (THIS_ PVOID pMemory, ULONG Flags = 0) PURE;

    CG_METHOD(MemoryCopy)           (THIS_ PVOID Destination, PVOID Source, SIZE_T Length) PURE;
    CG_METHOD(MemoryMove)           (THIS_ PVOID Destination, PVOID Source, SIZE_T Length) PURE;
    CG_METHOD(MemoryAnd)            (THIS_ PVOID pBuffer, SIZE_T Length, BYTE AndValue) PURE;
    CG_METHOD(MemoryOr)             (THIS_ PVOID pBuffer, SIZE_T Length, BYTE OrValue) PURE;
    CG_METHOD(MemoryXor)            (THIS_ PVOID pBuffer, SIZE_T Length, BYTE XorValue) PURE;
    CG_METHOD(MemoryAnd4)           (THIS_ PVOID pBuffer, SIZE_T Length, ULONG AndValue) PURE;
    CG_METHOD(MemoryOr4)            (THIS_ PVOID pBuffer, SIZE_T Length, ULONG OrValue) PURE;
    CG_METHOD(MemoryXor4)           (THIS_ PVOID pBuffer, SIZE_T Length, ULONG XorValue) PURE;
};

#endif // _CG_MEMORY_H_99e92e69_0435_453b_b131_44d142b39032

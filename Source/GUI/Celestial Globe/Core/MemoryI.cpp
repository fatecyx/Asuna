#include "MemoryI.h"

CCGMemoryI::
CCGMemoryI(
    ICGUnknown *pUnknownOuter
) :
    CCGUnknownImpl<CCGMemoryI>(pUnknownOuter)
{
}

CGSTATUS CCGMemoryI::QueryInterface0(REFIID iid, PVOID *ppvObject)
{
    if (iid == IID_Memory)
    {
        *ppvObject = (ICGMemory *)this;
    }
    else if (iid == IID_IUnknown)
    {
        *ppvObject = (ICGNonDelegatingUnknown *)this;
    }
    else
    {
        return STATUS_NOINTERFACE;
    }

    AddRef();

    return STATUS_SUCCESS;
}

PVOID CCGMemoryI::Alloc(SIZE_T Size, ULONG Flags)
{
    return m_Memory.Alloc(Size, Flags);
}

PVOID CCGMemoryI::ReAlloc(PVOID pMemory, SIZE_T Size, ULONG Flags /* = 0 */)
{
    return m_Memory.ReAlloc(pMemory, Size, Flags);
}

CGSTATUS CCGMemoryI::Free(PVOID pMemory, ULONG Flags /* = 0 */)
{
    return m_Memory.Free(pMemory, Flags);
}

CGSTATUS CCGMemoryI::MemoryCopy(PVOID Destination, PVOID Source, SIZE_T Length)
{
    return m_Memory.MemoryCopy(Destination, Source, Length);
}

CGSTATUS CCGMemoryI::MemoryMove(PVOID Destination, PVOID Source, SIZE_T Length)
{
    return m_Memory.MemoryMove(Destination, Source, Length);
}

CGSTATUS CCGMemoryI::MemoryAnd(PVOID pBuffer, SIZE_T Length, BYTE AndValue)
{
    return m_Memory.MemoryAnd(pBuffer, Length, AndValue);
}

CGSTATUS CCGMemoryI::MemoryOr(PVOID pBuffer, SIZE_T Length, BYTE OrValue)
{
    return m_Memory.MemoryOr(pBuffer, Length, OrValue);
}

CGSTATUS CCGMemoryI::MemoryXor(PVOID pBuffer, SIZE_T Length, BYTE XorValue)
{
    return m_Memory.MemoryXor(pBuffer, Length, XorValue);
}

CGSTATUS CCGMemoryI::MemoryAnd4(PVOID pBuffer, SIZE_T Length, ULONG AndValue)
{
    return m_Memory.MemoryAnd4(pBuffer, Length, AndValue);
}

CGSTATUS CCGMemoryI::MemoryOr4(PVOID pBuffer, SIZE_T Length, ULONG OrValue)
{
    return m_Memory.MemoryOr4(pBuffer, Length, OrValue);
}

CGSTATUS CCGMemoryI::MemoryXor4(PVOID pBuffer, SIZE_T Length, ULONG XorValue)
{
    return m_Memory.MemoryXor4(pBuffer, Length, XorValue);
}

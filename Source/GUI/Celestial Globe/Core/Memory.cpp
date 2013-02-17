#include "Memory.h"
#include "../Internal/CG_GUID.c"

extern HANDLE g_HeapHandle;

CCGMemory::CCGMemory()
{
    m_HeapHandle = g_HeapHandle;
}

PVOID CCGMemory::Alloc(SIZE_T Size, ULONG Flags)
{
    return RtlAllocateHeap(m_HeapHandle, Flags, Size);
}

PVOID CCGMemory::ReAlloc(PVOID pMemory, SIZE_T Size, ULONG Flags /* = 0 */)
{
    PVOID pRealloc;

    pRealloc = RtlReAllocateHeap(m_HeapHandle, Flags, pMemory, Size);
    if (pRealloc == NULL)
    {
        RtlFreeHeap(m_HeapHandle, 0, pMemory);
    }

    return pRealloc;
}

CGSTATUS CCGMemory::Free(PVOID pMemory, ULONG Flags /* = 0 */)
{
    BOOL Result = RtlFreeHeap(m_HeapHandle, Flags, pMemory);

    return Result ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
}

CGSTATUS CCGMemory::MemoryCopy(PVOID Destination, PVOID Source, SIZE_T Length)
{
    SEH_TRY
    {
        CopyMemory(Destination, Source, Length);
    }
    SEH_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        return GetExceptionCode();
    }

    return STATUS_SUCCESS;
}

CGSTATUS CCGMemory::MemoryMove(PVOID Destination, PVOID Source, SIZE_T Length)
{
    SEH_TRY
    {
        RtlMoveMemory(Destination, Source, Length);
    }
    SEH_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        return GetExceptionCode();
    }

    return STATUS_SUCCESS;
}

CGSTATUS CCGMemory::MemoryAnd(PVOID pBuffer, SIZE_T Length, BYTE AndValue)
{
    SEH_TRY
    {
        MemoryAndWorker(pBuffer, Length, AndValue);
    }
    SEH_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        return GetExceptionCode();
    }

    return STATUS_SUCCESS;
}

VOID CCGMemory::MemoryAndWorker(PVOID pBuffer, SIZE_T Length, BYTE AndValue)
{
    ULONG v;
    PBYTE Buffer;

    v = AndValue | ((ULONG)AndValue << 8);
    v = v | (v << 16);
    Buffer = (PBYTE)pBuffer;
    for (; Length != 0 && (ULONG_PTR)Buffer & 3; --Length)
    {
        *Buffer++ &= v;
    }

    for (ULONG Count = Length / 4; Count; --Count)
    {
        *(PULONG)Buffer &= v;
        Buffer += 4;
    }

    for (; Length != 0; --Length)
        *Buffer++ &= v;
}

CGSTATUS CCGMemory::MemoryOr(PVOID pBuffer, SIZE_T Length, BYTE OrValue)
{
    SEH_TRY
    {
        MemoryOrWorker(pBuffer, Length, OrValue);
    }
    SEH_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        return GetExceptionCode();
    }

    return STATUS_SUCCESS;
}

VOID CCGMemory::MemoryOrWorker(PVOID pBuffer, SIZE_T Length, BYTE OrValue)
{
    ULONG v;
    PBYTE Buffer;

    v = OrValue | ((ULONG)OrValue << 8);
    v = v | (v << 16);
    Buffer = (PBYTE)pBuffer;
    for (; Length != 0 && (ULONG_PTR)Buffer & 3; --Length)
    {
        *Buffer++ |= v;
    }

    for (ULONG Count = Length / 4; Count; --Count)
    {
        *(PULONG)Buffer |= v;
        Buffer += 4;
    }

    for (; Length != 0; --Length)
        *Buffer++ |= v;
}

CGSTATUS CCGMemory::MemoryXor(PVOID pBuffer, SIZE_T Length, BYTE XorValue)
{
    SEH_TRY
    {
        MemoryXorWorker(pBuffer, Length, XorValue);
    }
    SEH_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        return GetExceptionCode();
    }

    return STATUS_SUCCESS;
}

VOID CCGMemory::MemoryXorWorker(PVOID pBuffer, SIZE_T Length, BYTE XorValue)
{
    ULONG v;
    PBYTE Buffer;

    v = XorValue | ((ULONG)XorValue << 8);
    v = v | (v << 16);
    Buffer = (PBYTE)pBuffer;
    for (; Length != 0 && (ULONG_PTR)Buffer & 3; --Length)
    {
        *Buffer++ ^= v;
    }

    for (ULONG Count = Length / 4; Count; --Count)
    {
        *(PULONG)Buffer ^= v;
        Buffer += 4;
    }

    for (; Length != 0; --Length)
        *Buffer++ ^= v;
}

CGSTATUS CCGMemory::MemoryAnd4(PVOID pBuffer, SIZE_T Length, ULONG AndValue)
{
    SEH_TRY
    {
        MemoryAnd4Worker(pBuffer, Length, AndValue);
    }
    SEH_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        return GetExceptionCode();
    }

    return STATUS_SUCCESS;
}

VOID CCGMemory::MemoryAnd4Worker(PVOID pBuffer, SIZE_T Length, ULONG AndValue)
{
    PBYTE Buffer = (PBYTE)pBuffer;
    for (; Length >= 4; Length -= 4)
    {
        *(PULONG)Buffer &= AndValue;
        Buffer += 4;
    }
}

CGSTATUS CCGMemory::MemoryOr4(PVOID pBuffer, SIZE_T Length, ULONG OrValue)
{
    SEH_TRY
    {
        MemoryOr4Worker(pBuffer, Length, OrValue);
    }
    SEH_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        return GetExceptionCode();
    }

    return STATUS_SUCCESS;
}

VOID CCGMemory::MemoryOr4Worker(PVOID pBuffer, SIZE_T Length, ULONG OrValue)
{
    PBYTE Buffer = (PBYTE)pBuffer;
    for (; Length >= 4; Length -= 4)
    {
        *(PULONG)Buffer |= OrValue;
        Buffer += 4;
    }
}

CGSTATUS CCGMemory::MemoryXor4(PVOID pBuffer, SIZE_T Length, ULONG XorValue)
{
    SEH_TRY
    {
        MemoryXor4Worker(pBuffer, Length, XorValue);
    }
    SEH_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        return GetExceptionCode();
    }

    return STATUS_SUCCESS;
}

VOID CCGMemory::MemoryXor4Worker(PVOID pBuffer, SIZE_T Length, ULONG XorValue)
{
    PBYTE Buffer = (PBYTE)pBuffer;
    for (; Length >= 4; Length -= 4)
    {
        *(PULONG)Buffer ^= XorValue;
        Buffer += 4;
    }
}

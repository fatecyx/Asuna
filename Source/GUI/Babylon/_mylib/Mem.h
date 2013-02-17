#ifndef _MEM_H_
#define _MEM_H_

#include <Windows.h>
#include "my_headers.h"

#if CPP_DEFINED

class NOVTABLE CMem
{
protected:
    HANDLE m_hHeap, m_hHeapPrivate;
    static HANDLE m_hHeapGlobal;
    static ULong  m_ObjectCount;

protected:
    NoInline static HANDLE CreateGlobalHeapInternal(DWORD flOptions = 0, SIZE_T dwInitialSize = 0, SIZE_T dwMaximumSize = 0)
    {
        if (m_hHeapGlobal == NULL)
            m_hHeapGlobal = MYAPI(HeapCreate)(flOptions, dwInitialSize, dwMaximumSize);

        return m_hHeapGlobal;
    }

    ForceInline static ULong AddObject()
    {
        return _InterlockedIncrement((PLong)&m_ObjectCount);
    }

    ForceInline static ULong RemoveObject()
    {
        return _InterlockedDecrement((PLong)&m_ObjectCount);
    }

    NoInline Void DestroyGlobal()
    {
        if (m_hHeap == NULL)
            return;

        DestroyGlobalHeap();
    }

public:
    NoInline CMem(HANDLE hHeap = NULL)
    {
        if (hHeap != NULL)
        {
            m_hHeapPrivate = hHeap;
        }
        else
        {
            if (AddObject() == 1)
            {
                hHeap = CreateGlobalHeapInternal();
                if (hHeap == NULL)
                    RemoveObject();
            }
            else
            {
                hHeap = m_hHeapGlobal;
            }

            m_hHeapPrivate = NULL;
        }

        m_hHeap = hHeap;
    }

    CMem(const CMem &mem)
    {
        *this = mem;
    }

    NoInline ~CMem()
    {
        if (m_hHeapPrivate != NULL)
        {
            if (m_hHeapPrivate != MYAPI(GetProcessHeap)())
                MYAPI(HeapDestroy)(m_hHeapPrivate);
        }
        else
        {
            DestroyGlobal();
        }
    }

    CMem& operator= (const CMem &mem)
    {
        if (&mem == this)
            return *this;

        if (mem.m_hHeapPrivate != NULL)
        {
            DestroyHeap();
            m_hHeapPrivate = mem.m_hHeapPrivate;
            m_hHeap = m_hHeapPrivate;
        }
        else
        {
            DestroyGlobal();
            m_hHeapGlobal = mem.m_hHeapGlobal;
            if (m_hHeapGlobal != NULL)
                AddObject();
        }

        return *this;
    }

    HANDLE GetHeap() const
    {
        return m_hHeap;
    }

    static HANDLE CreateGlobalHeap(DWORD flOptions = 0)
    {
        HANDLE hHeap = CreateGlobalHeapInternal(flOptions);
        if (hHeap != NULL)
            AddObject();
        return hHeap;
    }

    static Bool DestroyGlobalHeap()
    {
        if (m_hHeapGlobal && RemoveObject() == 0)
        {
            if (MYAPI(HeapDestroy(m_hHeapGlobal)))
            {
                m_hHeapGlobal = NULL;
                return True;
            }
        }
        
        return False;
    }

    static HANDLE GetGlobalHeap()
    {
        return m_hHeapGlobal;
    }

    HANDLE CreateHeap(DWORD flOptions = 0, SIZE_T dwInitialSize = 0, SIZE_T dwMaximumSize = 0)
    {
        if (m_hHeapPrivate != NULL)
            MYAPI(HeapDestroy)(m_hHeapPrivate);

        m_hHeapPrivate = MYAPI(HeapCreate)(flOptions, dwInitialSize, dwMaximumSize);
        m_hHeap = m_hHeapPrivate;

        return m_hHeap;
    }

    Bool DestroyHeap()
    {
        Bool Result = True;

        if (m_hHeapPrivate != NULL && m_hHeapPrivate != MYAPI(GetProcessHeap)())
        {
            Result = MYAPI(HeapDestroy)(m_hHeapPrivate);
            if (Result)
            {
                m_hHeap = NULL;
                m_hHeapPrivate = NULL;
            }
        }

        return Result;
    }

    PVoid Alloc(SizeT Size, ULong Flags = 0)
    {
        return MYAPI(HeapAlloc)(m_hHeap, Flags, Size);
    }

    PVoid ReAlloc(PVoid pBuffer, SizeT Size, ULong Flags = 0)
    {
        PVoid pRealloc;

        pRealloc = MYAPI(HeapReAlloc)(m_hHeap, Flags, pBuffer, Size);
        if (pRealloc == NULL)
        {
            Free(pBuffer);
        }

        return pRealloc;
    }

    Bool Free(PVoid pBuffer, ULong Flags = 0)
    {
        return pBuffer == NULL ? False : MYAPI(HeapFree)(m_hHeap, Flags, pBuffer);
    }

    Bool SafeFree(LPVoid pBuffer)
    {
        LPVoid **pt = (LPVoid **)pBuffer;
        if (*pt == NULL)
            return False;

        Bool Result = MYAPI(HeapFree)(m_hHeap, 0, *pt);
        if (Result)
            *pt = NULL;

        return Result;
    }
};

#endif // CPP_DEFINED

#endif /* _MEM_H_ */
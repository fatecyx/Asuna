#ifndef _MYLIST_H_
#define _MYLIST_H_

#include "pragma_once.h"
#include <Windows.h>
#include "my_headers.h"

//MY_NAMESPACE_BEGIN(MY_LIB_NAME)

template<class Elem>
class CList
{
public:
    static const SizeT InvalidPosition = (SizeT)-1;

protected:
    Elem *m_pElemList;
    SizeT m_ElemCount, m_MaxCount;
    SizeT m_HeadIndex, m_TailIndex;
    CMem  m_mem;
    CRITICAL_SECTION m_cs;

    static const SizeT m_kElemSize = sizeof(Elem);
    static const SizeT m_kInvalidIndex = InvalidPosition;

public:
    CList<Elem>()
    {
        m_pElemList = NULL;
        m_ElemCount = 0;
        InitializeCriticalSectionAndSpinCount(&m_cs, 4000);
    }

    ~CList()
    {
        Empty();
        DeleteCriticalSection(&m_cs);
    }

    Bool Empty()
    {
        Bool Result;

        Lock();
        Result = m_mem.SafeFree(&m_pElemList);
        Unlock();
        return Result;
    }

    Bool IsEmpty()
    {
        Bool bIsEmpty;

        Lock();

        bIsEmpty = m_pElemList == NULL || m_ElemCount == 0;

        Unlock();

        return bIsEmpty;
    }

    SizeT GetCount() const
    {
        return m_ElemCount;
    }

    SizeT AddHead(const Elem &newElement)
    {
        SizeT Position;

        Lock();

        DecrementIndex(m_HeadIndex);
        Position = SetAtNoLock(0, newElement);
        if (Position != m_kInvalidIndex)
            IncrementElementCount();
        else
            IncrementIndex(m_HeadIndex);

        Unlock();

        return Position;
    }

    SizeT AddTail(const Elem &newElement)
    {
        SizeT Position;

        Lock();

        Position = SetAtNoLock(m_ElemCount, newElement);
        if (Position != m_kInvalidIndex)
        {
            IncrementElementCount();
            IncrementIndex(m_TailIndex);
        }

        Unlock();

        return Position;
    }

    Bool GetHead(Elem &Element)
    {
        return GetAt(0, Element);
    }

    Bool GetTail(Elem &Element)
    {
        return GetAt(m_ElemCount - 1, Element);
    }

    Bool RemoveHead()
    {
        Bool Result;
        Lock();
        Result = RemoveHeadNoLock();
        Unlock();
        return Result;
    }

    Bool RemoveTail()
    {
        Bool Result;
        Lock();
        Result = RemoveTailNoLock();
        Unlock();
        return Result;
    }

    Bool GetAt(SizeT Position, Elem &Element)
    {
        Bool  Result;
        Lock();
        Result = GetAtNoLock(Position, Element);
        Unlock();
        return Result;
    }

	SizeT SetAt(SizeT Position, const Elem &newElement)
    {
        Lock();
        Position = SetAtNoLock(Position, newElement);
        Unlock();
        return Position;
    }

protected:
    Bool RemoveHeadNoLock()
    {
        if (!IsListValid())
            return False;
        if (m_ElemCount == 0)
            return False;

        DecrementElementCount();
        IncrementIndex(m_HeadIndex);

        return True;
    }

    Bool RemoveTailNoLock()
    {
        if (!IsListValid())
            return False;
        if (m_ElemCount == 0)
            return False;

        DecrementElementCount();
        DecrementIndex(m_TailIndex);

        return True;
    }

    Bool GetAtNoLock(SizeT Position, Elem &Element)
    {
        SizeT RealPos;

        if (!IsListValid())
            return False;
        if (!IsPositionValid(Position))
            return False;

        RealPos = m_HeadIndex + Position;
        if (RealPos >= m_MaxCount)
            RealPos -= m_MaxCount;

        Element = m_pElemList[RealPos];

        return True;
    }

	SizeT SetAtNoLock(SizeT Position, const Elem &newElement)
    {
        Elem *pElem;
        SizeT RealPos;

        pElem = AllocBuffer();
        if (pElem == NULL)
            return m_kInvalidIndex;

        if (Position >= m_MaxCount)
            return m_kInvalidIndex;

        RealPos = m_HeadIndex + Position;
        if (RealPos >= m_MaxCount)
            RealPos -= m_MaxCount;

        m_pElemList[RealPos] = newElement;

        return Position;
    }

    Bool IsListValid()
    {
        return m_pElemList != NULL;
    }

    Bool IsPositionValid(SizeT Position)
    {
        return Position < m_ElemCount;
    }

    SizeT IncrementIndex(SizeT &Index)
    {
        Index = Index == m_MaxCount ? 0 : Index + 1;
        return Index;
    }

    SizeT DecrementIndex(SizeT &Index)
    {
        Index = Index == 0 ? m_MaxCount - 1 : Index - 1;
        return Index;
    }

    SizeT IncrementElementCount()
    {
        return ++m_ElemCount;
//        return _InterlockedIncrement((PLong)&m_ElemCount);
    }

    SizeT DecrementElementCount()
    {
        return --m_ElemCount;
//        return _InterlockedDecrement((PLong)&m_ElemCount);
    }

    Void FixIndex(SizeT OriginalCount)
    {
        Elem *pOrig, *pNew;
        SizeT Count;

        if (m_HeadIndex == 0)
            return;

        if (m_HeadIndex == OriginalCount)
        {
            m_HeadIndex = 0;
            return;
        }

// 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
//     ¡ü
        Count = OriginalCount - m_HeadIndex;
        if (m_HeadIndex + 1 < Count)
        {
            Count = m_HeadIndex + 1;
            pOrig = m_pElemList;
            pNew  = &m_pElemList[m_HeadIndex] + OriginalCount - m_HeadIndex;
            m_TailIndex = m_HeadIndex + OriginalCount;
        }
        else
        {
            pOrig = &m_pElemList[m_HeadIndex];
            m_HeadIndex = m_MaxCount - Count;
            pNew = &m_pElemList[m_HeadIndex];
        }

        if (pOrig + Count >= pNew)
        {
            pNew  += Count;
            pOrig += Count;
            while (Count--)
                *pNew-- = *pOrig--;
        }
        else
        {
            while (Count--)
                *pNew++ = *pOrig++;
        }
    }

    Elem* AllocBuffer()
    {
        Elem *pList;

        if (m_pElemList == NULL)
        {
            m_HeadIndex = 0;
            m_TailIndex = 0;
            m_ElemCount = 0;
            m_MaxCount  = 10;
            m_pElemList = (Elem *)m_mem.Alloc(m_kElemSize * m_MaxCount, HEAP_ZERO_MEMORY);
            if (m_pElemList == NULL)
                return m_pElemList;
        }
        else if (m_ElemCount == m_MaxCount)
        {
            m_MaxCount = m_MaxCount * 3 / 2;
            m_pElemList = (Elem *)m_mem.ReAlloc(m_pElemList, m_kElemSize * m_MaxCount, HEAP_ZERO_MEMORY);
            if (m_pElemList == NULL)
                return m_pElemList;

            FixIndex(m_ElemCount);
        }

        pList = &m_pElemList[m_TailIndex];

        return pList;
    }

    Void Lock()
    {
        EnterCriticalSection(&m_cs);
    }

    Void Unlock()
    {
        LeaveCriticalSection(&m_cs);
    }
};

//MY_NAMESPACE_END

#endif // _MYLIST_H_
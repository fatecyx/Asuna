#include "ClassFactory.h"
#include "../Internal/CG_GUID.c"
#include "MemoryI.h"
#include "FileIoI.h"

CCGClassFactory::
CCGClassFactory(
    ICGUnknown *pUnknownOuter
) :
    CCGUnknownImpl<CCGClassFactory>(pUnknownOuter)
{
}

CGSTATUS CCGClassFactory::QueryInterface0(REFIID iid, PVOID *ppvObject)
{
    if (iid == IID_IClassFactory)
    {
        *ppvObject = this;
        AddRef();
    }
    else if (iid == IID_IUnknown)
    {
        *ppvObject = (ICGUnknown *)this;
        AddRef();
    }
    else
    {
        return STATUS_NOINTERFACE;
    }

    return STATUS_SUCCESS;
}

CGSTATUS CCGClassFactory::CreateInstance(ICGUnknown *pUnknownOuter, REFIID iid, PVOID *ppvObject)
{
    union
    {
        CCGMemoryI  *Memory;
        CCGFileIoI  *FileIo;
        ICGUnknown  *Unknown;
    };

    if (ppvObject == NULL)
        return STATUS_INVALID_PARAMETER_3;

    *ppvObject = NULL;

    if (pUnknownOuter != NULL && iid != IID_IUnknown)
        return STATUS_INVALID_PARAMETER;

    if (iid == IID_Memory)
    {
        Memory = new CCGMemoryI(pUnknownOuter);
    }
    else if (iid == IID_FileIo)
    {
        FileIo = new CCGFileIoI(pUnknownOuter);
    }
    else if (iid == IID_IUnknown)
    {
        if (pUnknownOuter == m_pUnknownOuter)
        {
            Unknown = (ICGUnknown *)this;
            AddRef();
        }
        else
        {
            Unknown = new CCGClassFactory(pUnknownOuter);
        }
    }
    else
    {
        return STATUS_NOINTERFACE;
    }

    if (Unknown == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    *ppvObject = Unknown;

    return STATUS_SUCCESS;
}

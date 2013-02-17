#include "Core.h"
#include "../Internal/CG_GUID.c"
#include "../Internal/CG_UI.h"

HANDLE g_HeapHandle;

CCGCore::
CCGCore(
    ICGUnknown *pUnknwonOuter
) :
    CCGUnknownImpl<CCGCore>(pUnknwonOuter)
{
    m_pMemoryI = NULL;
}

CCGCore::~CCGCore()
{
    if (m_pMemoryI != NULL)
        m_pMemoryI->Release();
}

CGSTATUS CCGCore::Run()
{
    CGSTATUS    Status;
    ICGUnknown *pUnknownOuter;

    pUnknownOuter = (ICGUnknown *)(ICGCore *)this;

    Status = CreateInterface(
                (ICGCoreBase *)this,
                pUnknownOuter,
                IID_IUnknown,
                (PVOID *)&m_pUiInner
             );

    if (!CG_SUCCESS(Status))
        return Status;

    Status = m_pUiInner->QueryInterface(IID_UIMain, (PVOID *)&m_pUI);
    if (!CG_SUCCESS(Status))
    {
        m_pUiInner->Release();
        return Status;
    }

    m_pUI->Create(-1, -1, 0, 0);
    m_pUI->Show();
    m_pUI->Execute();

    m_pUI->Release();
    m_pUiInner->Release();

    return STATUS_SUCCESS;
}

CGSTATUS CCGCore::GetInterface(REFIID iid, PVOID *ppvObject)
{
    union
    {
        ICGCore                 *Core;
        ICGMemory               *Memory;
        ICGFileIo               *FileIo;
        ICGNonDelegatingUnknown *Unknown;
    };

    if (ppvObject == NULL)
        return STATUS_INVALID_PARAMETER_2;

    *ppvObject = NULL;

    if (iid == IID_Core)
    {
        Core = (ICGCore *)this;
    }
    else if (iid == IID_Memory)
    {
        if (m_pMemoryI == NULL)
        {
            m_pMemoryI = new CCGMemoryI(NULL);
            if (m_pMemoryI == NULL)
                return STATUS_INSUFFICIENT_RESOURCES;
        }

        Memory = m_pMemoryI;
        m_pMemoryI->AddRef();
    }
    else if (iid == IID_FileIo)
    {
        FileIo = new CCGFileIoI(NULL);
    }
    else if (iid == IID_UI)
    {
        return m_pUiInner->QueryInterface(iid, ppvObject);
    }
    else if (iid == IID_IUnknown)
    {
        Unknown = (ICGNonDelegatingUnknown *)this;
        AddRef();
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

CGSTATUS CCGCore::StringCreate(PUNICODE_STRING DestinationString, LPCWSTR SourceString)
{
    return RtlCreateUnicodeString(DestinationString, SourceString) ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
}

CGSTATUS CCGCore::StringFree(PUNICODE_STRING UnicodeString)
{
    RtlFreeUnicodeString(UnicodeString);
    return STATUS_SUCCESS;
}

LONG CCGCore::StringCompare(PUNICODE_STRING String1, PUNICODE_STRING String2, BOOL CaseInSensitive)
{
    if (CaseInSensitive)
        return StrICompareW(String1->Buffer, String2->Buffer);
    else
        return StrCompareW(String1->Buffer, String2->Buffer);
}

CGSTATUS CCGCore::ProfileReadString(LPCWSTR KeyName, PUNICODE_STRING Buffer, BOOL AllocateBuffer)
{
    return STATUS_NOT_IMPLEMENTED;
}

CGSTATUS CCGCore::ProfileReadInt(LPCWSTR KeyName, PLONG64 Buffer)
{
    return STATUS_NOT_IMPLEMENTED;
}

CGSTATUS CCGCore::ProfileSaveString(LPCWSTR KeyName, LPCWSTR Value)
{
    return STATUS_NOT_IMPLEMENTED;
}

CGSTATUS CCGCore::ProfileSaveInt(LPCWSTR KeyName, LONG64 Value)
{
    return STATUS_NOT_IMPLEMENTED;
}


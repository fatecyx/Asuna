#pragma warning(disable:4355)

#include "Core.h"

CGSTATUS CCGCore::QueryInterface0(REFIID iid, PVOID *ppvObject)
{
    if (iid == IID_Core)
    {
        *ppvObject = (ICGCore *)this;
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

CGSTATUS CCGCore::CreateString(PUNICODE_STRING DestinationString, LPCWSTR SourceString)
{
    return CreateString(DestinationString, SourceString);
}

CGSTATUS CCGCore::FreeString(PUNICODE_STRING UnicodeString)
{
    return FreeString(UnicodeString);
}

LONG CCGCore::CompareString(PUNICODE_STRING String1, PUNICODE_STRING String2, BOOL CaseInSensitive)
{
    return CompareString(String1, String2, CaseInSensitive);
}

CGSTATUS CCGCore::ReadProfileString(LPCWSTR KeyName, PUNICODE_STRING Buffer, BOOL AllocateBuffer)
{
    return ReadProfileString(KeyName, Buffer, AllocateBuffer);
}

CGSTATUS CCGCore::ReadProfileInt(LPCWSTR KeyName, PLONG64 Buffer)
{
    return ReadProfileInt(KeyName, Buffer);
}

CGSTATUS CCGCore::SaveProfileString(LPCWSTR KeyName, LPCWSTR Value)
{
    return SaveProfileString(KeyName, Value);
}

CGSTATUS CCGCore::SaveProfileInt(LPCWSTR KeyName, LONG64 Value)
{
    return SaveProfileInt(KeyName, Value);
}

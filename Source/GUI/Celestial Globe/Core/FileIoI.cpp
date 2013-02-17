#include "FileIoI.h"

CCGFileIoI::
CCGFileIoI(
    ICGUnknown *pUnknwonOuter
) :
    CCGUnknownImpl<CCGFileIoI>(pUnknwonOuter)
{
}

CGSTATUS CCGFileIoI::QueryInterface0(REFIID iid, PVOID *ppvObject)
{
    if (iid == IID_FileIo)
    {
        *ppvObject = (ICGFileIo *)this;
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

CGSTATUS CCGFileIoI::Close()
{
    return m_File.Close();
}

CGSTATUS CCGFileIoI::Open(
    LPCWSTR         FileName,
    FileShareMode   ShareMode  /* = FileShareRead */,
    FileAccess      Access     /* = FileGenericRead */
)
{
    return m_File.Open(FileName, ShareMode, Access);
}

CGSTATUS
CCGFileIoI::
Create(
    LPCWSTR         FileName,
    FileShareMode   ShareMode  /* = FileShareRead */,
    FileAccess      Access     /* = FileGenericWrite */
)
{
    return m_File.Create(FileName, ShareMode, Access);
}

CGSTATUS CCGFileIoI::GetSize(PLARGE_INTEGER pFileSize)
{
    return m_File.GetSize(pFileSize);
}

CGSTATUS CCGFileIoI::GetPosition(PLARGE_INTEGER pPosition)
{
    return m_File.GetPosition(pPosition);
}

CGSTATUS
CCGFileIoI::
Seek(
    LARGE_INTEGER   Offset,
    ULONG           MoveMethod,
    PLARGE_INTEGER  pNewPosition /* = NULL */
)
{
    return m_File.Seek(Offset, MoveMethod, pNewPosition);
}

CGSTATUS CCGFileIoI::Read(PVOID Buffer, ULONG Size, PLARGE_INTEGER pBytesRead /* = NULL */)
{
    return m_File.Read(Buffer, Size, pBytesRead);
}

CGSTATUS CCGFileIoI::Write(PVOID Buffer, ULONG Size, PLARGE_INTEGER pBytesWritten /* = NULL */)
{
    return m_File.Write(Buffer, Size, pBytesWritten);
}

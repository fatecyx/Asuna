#ifndef _FILEIOI_H_d35f959b_a0ba_416d_8ef6_06ece52f79a2
#define _FILEIOI_H_d35f959b_a0ba_416d_8ef6_06ece52f79a2

#include "pragma_once.h"
#include "../Internal/CG_Headers.h"
#include "FileIo.h"

CG_INTERFACE_FROM_CLASS(CCGFileIo, ICGFileIo)
{
protected:
    CCGFileIo m_File;

public:
    CCGFileIoI(ICGUnknown *pUnknwonOuter);

    CG_METHOD(Open)(
        LPCWSTR         FileName,
        FileShareMode   ShareMode   = FileShareRead,
        FileAccess      Access      = FileGenericRead
    );

    CG_METHOD(Create)(
        LPCWSTR         FileName,
        FileShareMode   ShareMode   = FileShareRead,
        FileAccess      Access      = FileGenericWrite
    );

    CG_METHOD(GetSize)      (PLARGE_INTEGER pFileSize);
    CG_METHOD(GetPosition)  (PLARGE_INTEGER pPosition);
    CG_METHOD(Seek)         (LARGE_INTEGER Offset, ULONG MoveMethod, PLARGE_INTEGER pNewPosition = NULL);
    CG_METHOD(Read)         (PVOID Buffer, ULONG Size, PLARGE_INTEGER pBytesRead = NULL);
    CG_METHOD(Write)        (PVOID Buffer, ULONG Size, PLARGE_INTEGER pBytesWritten = NULL);
    CG_METHOD(Close)        ();

    CGSTATUS CG_METHOD_CALLTYPE QueryInterface0(REFIID iid, PVOID *ppvObject);

    CG_IUNKNOWN_IMPLEMENT(CCGFileIoI);
};

#endif // _FILEIOI_H_d35f959b_a0ba_416d_8ef6_06ece52f79a2

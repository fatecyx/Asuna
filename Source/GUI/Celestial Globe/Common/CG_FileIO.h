#ifndef _CG_FILEIO_H_bb75dd77_12fa_4f27_b635_42d9f8f17750
#define _CG_FILEIO_H_bb75dd77_12fa_4f27_b635_42d9f8f17750

#include "pragma_once.h"
#include "CG_Interface.h"

enum FileShareMode
{
    FileShareRead       = FILE_SHARE_READ,
    FileShareWrite      = FILE_SHARE_WRITE,
    FileShareDelete     = FILE_SHARE_DELETE,
};

enum FileAccess
{
    FileGenericRead     = GENERIC_READ,
    FileGenericWrite    = GENERIC_WRITE,
    FileGenericAll      = GENERIC_ALL,
};

CG_INTERFACE(ICGFileIoBase)
{
    CG_METHOD(Open)(
        THIS_
        LPCWSTR         FileName,
        FileShareMode   ShareMode   = FileShareRead,
        FileAccess      Access      = FileGenericRead
    ) PURE;

    CG_METHOD(Create)(
        THIS_
        LPCWSTR         FileName,
        FileShareMode   ShareMode   = FileShareRead,
        FileAccess      Access      = FileGenericWrite
    ) PURE;

    CG_METHOD(GetSize)      (THIS_ PLARGE_INTEGER pFileSize) PURE;

    CG_METHOD(Seek)(
        THIS_
        LARGE_INTEGER   Offset,
        ULONG           MoveMethod,
        PLARGE_INTEGER  pNewPosition = NULL
    ) PURE;

    CG_METHOD(GetPosition)  (THIS_ PLARGE_INTEGER pPosition);
    CG_METHOD(Read)         (THIS_ PVOID Buffer, ULONG Size, PLARGE_INTEGER pBytesRead = NULL) PURE;
    CG_METHOD(Write)        (THIS_ PVOID Buffer, ULONG Size, PLARGE_INTEGER pBytesWritten = NULL) PURE;
    CG_METHOD(Close)        (THIS) PURE;
};

CG_INTERFACE_(ICGFileIo, ICGUnknown, ICGFileIoBase)
{
};

#endif // _CG_FILEIO_H_bb75dd77_12fa_4f27_b635_42d9f8f17750

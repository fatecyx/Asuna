#ifndef _FILEIO_H_9999daa8_30c4_4a59_8a91_d535e5c523da
#define _FILEIO_H_9999daa8_30c4_4a59_8a91_d535e5c523da

#include "pragma_once.h"
#include "../Internal/CG_FileIO.h"

class CCGFileIo
{
protected:
    HANDLE          m_FileHandle;
    LARGE_INTEGER   m_FileSize, m_Position;

public:
    CCGFileIo();

    
    CGSTATUS Open(
        LPCWSTR         FileName,
        FileShareMode   ShareMode   = FileShareRead,
        FileAccess      Access      = FileGenericRead
    );

    CGSTATUS Create(
        LPCWSTR         FileName,
        FileShareMode   ShareMode   = FileShareRead,
        FileAccess      Access      = FileGenericWrite
    );

    CGSTATUS GetSize       (PLARGE_INTEGER pFileSize);
    CGSTATUS GetPosition   (PLARGE_INTEGER pPosition);
    CGSTATUS Seek          (LARGE_INTEGER Offset, ULONG MoveMethod, PLARGE_INTEGER pNewPosition = NULL);
    CGSTATUS Read          (PVOID Buffer, ULONG Size, PLARGE_INTEGER pBytesRead = NULL);
    CGSTATUS Write         (PVOID Buffer, ULONG Size, PLARGE_INTEGER pBytesWritten = NULL);
    CGSTATUS Close         ();

protected:
    CGSTATUS CreateFileInternal(
        LPCWSTR         FileName,
        FileShareMode   ShareMode,
        FileAccess      Access,
        ULONG           CreationDisposition
    );

    CGSTATUS GetSizeInternal(PLARGE_INTEGER pFileSize);
};

#endif // _FILEIO_H_9999daa8_30c4_4a59_8a91_d535e5c523da

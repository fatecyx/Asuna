#ifndef _FILEDISK_H_
#define _FILEDISK_H_

#include "pragma_once.h"

#if CPP_DEFINED

#include <Windows.h>
#include "FileBase.h"

class CFileDisk : public CFileBase<CFileDisk>
{
protected:
    HANDLE m_hFile;
    ULong m_access;

public:
    enum DesiredAccess
    {
        FILE_ACCESS_NONE  = 0,
        FILE_ACCESS_READ = 0x1,
        FILE_ACCESS_WRITE = 0x2,
        A_R = FILE_ACCESS_READ,
        A_W = FILE_ACCESS_WRITE
    };
    enum ShareMode
    {
        FILE_SHAREMODE_READ = 0x1,
        FILE_SHAREMODE_WRITE = 0x2,
        FILE_SHAREMODE_DELETE = 0x4
    };
    enum CreationDisposition
    {
        FILE_CREATE_FIRST,

        FILE_CREATE_NEW = FILE_CREATE_FIRST,
        FILE_CREATE_ALWAYS,
        FILE_OPEN_EXIST,
        FILE_OPEN_ALWAYS,

        FILE_CREATE_LAST,

        C_N = FILE_CREATE_NEW,
        C_A = FILE_CREATE_ALWAYS
    };

    CFileDisk()
    {
        m_access = FILE_ACCESS_NONE;
        m_hFile  = INVALID_HANDLE_VALUE;
    }

    ~CFileDisk()
    {
        Close();
    }

public:
    Bool
    Open(
        PCChar pszFile,
        ULong  access = FILE_ACCESS_READ,
        ULong  share  = FILE_SHAREMODE_READ,
        ULong  dispos = FILE_OPEN_EXIST
    )
    {
        WChar szFileName[MAX_PATH];
        NTSTATUS Status;
        UNICODE_STRING ustrFile;

        if (AnsiToUnicode(&ustrFile, pszFile, szFileName, countof(szFileName)) == False)
            return False;

        Status = Open(ustrFile.Buffer, access, share, dispos);

        return Status;
    }

    Bool
    Create(
        PCWChar pszFile,
        ULong   access = FILE_ACCESS_WRITE,
        ULong   share  = FILE_SHAREMODE_READ,
        ULong   dispos = FILE_CREATE_ALWAYS
    )
    {
        return Open(pszFile, access, share, dispos);
    }

    Bool
    Open(
        PCWChar pszFile,
        ULong   access = FILE_ACCESS_READ,
        ULong   share  = FILE_SHAREMODE_READ,
        ULong   dispos = FILE_OPEN_EXIST
    )
    {
        DWORD dwDesiredAccess, dwShareMode;
        DWORD dwCreationDisposition[] =
        {
            CREATE_NEW,
            CREATE_ALWAYS,
            OPEN_EXISTING,
            OPEN_ALWAYS,
        };

        if (!IN_RANGE(FILE_CREATE_FIRST, dispos, FILE_CREATE_LAST - 1))
            return False;

        Close();

        dwDesiredAccess = 0;
        dwShareMode = 0;
        if (access & FILE_ACCESS_READ)
            dwDesiredAccess |= GENERIC_READ;

        if (access & FILE_ACCESS_WRITE)
            dwDesiredAccess |= GENERIC_WRITE;

        if (share & FILE_SHAREMODE_READ)
            dwShareMode |= FILE_SHARE_READ;

        if (share & FILE_SHAREMODE_WRITE)
            dwShareMode |= FILE_SHARE_WRITE;

        m_hFile = CreateFileW(pszFile,
                      dwDesiredAccess,
                      dwShareMode,
                      NULL,
                      dwCreationDisposition[dispos],
                      FILE_ATTRIBUTE_NORMAL,
                      NULL);

        if (m_hFile == INVALID_HANDLE_VALUE)
            return False;

        m_access = access;
        m_Offset.QuadPart = 0;
        if (dispos != FILE_CREATE_NEW && dispos != FILE_CREATE_ALWAYS)
        {
            GetFileSizeEx(m_hFile, (PLARGE_INTEGER)&m_FileSize);
        }
        else
        {
            m_FileSize.QuadPart = 0;
        }

        return True;
    }

    Void Close()
    {
        if (m_hFile != INVALID_HANDLE_VALUE)
        {
            CloseHandle(m_hFile);
            m_hFile = INVALID_HANDLE_VALUE;
        }
    }

    Bool IsInit()
    {
        return m_hFile != INVALID_HANDLE_VALUE;
    }

    Bool Seek(Long uMethod, Long iOffset, PLong pOffsetHigh = NULL)
    {
        m_Offset.LowPart = SetFilePointer(m_hFile, iOffset, pOffsetHigh, uMethod);

        if (m_Offset.LowPart == -1 && GetLastError() != NO_ERROR)
            return False;

        if (pOffsetHigh)
            m_Offset.HighPart = *pOffsetHigh;
        else
            m_Offset.HighPart = 0;

        return True;
    }

    Bool SeekEx(Long Method, Large_Integer DistanceToMove, PLarge_Integer pNewFilePointer = NULL)
    {
        Bool Result;
        LARGE_INTEGER _DistanceToMove;

        _DistanceToMove.QuadPart = DistanceToMove.QuadPart;
        Result = SetFilePointerEx(m_hFile, _DistanceToMove, (PLARGE_INTEGER)&m_Offset, Method);
        if (!Result)
            return Result;

        if (pNewFilePointer != NULL)
            *pNewFilePointer = m_Offset;

        return Result;
    }

    Bool
    Read(
        PVoid           lpBuffer,
        SizeT           Size        = 0,
        PULong          pBytesRead = NULL
    )
    {
        if ((m_access & FILE_ACCESS_READ) == 0)
            return False;

        Bool  bResult;
        DWORD dwRead;

        bResult = ReadFile(m_hFile, lpBuffer, Size ? Size : GetSize(), &dwRead, NULL);
        if (bResult == False)
            return False;

        if (pBytesRead)
            *pBytesRead = dwRead;

        m_Offset.QuadPart += dwRead;

        return bResult;
    }

    Bool Write(Void *lpBuffer, ULong uSize, OPTIONAL PULong pBytesWritten = NULL)
    {
        if ((m_access & FILE_ACCESS_WRITE) == 0 || lpBuffer == NULL)
            return False;

        Bool  bResult;
        DWORD dwWritten;

        bResult = WriteFile(m_hFile, lpBuffer, uSize, &dwWritten, NULL);
        if (bResult == False)
            return False;

        if (dwWritten + m_Offset.QuadPart > m_FileSize.QuadPart)
        {
            m_FileSize.QuadPart = m_Offset.QuadPart + dwWritten;
//            GetFileSizeEx(m_hFile, (PLARGE_INTEGER)&m_FileSize);
        }

        if (pBytesWritten) *pBytesWritten = dwWritten;

        m_Offset.QuadPart += dwWritten;

        return True;
    }

    Bool Delete()
    {
        NTSTATUS Status;
        IO_STATUS_BLOCK  IoStatusBlock;
        FILE_DISPOSITION_INFORMATION FileInformation;

        FileInformation.DeleteFile = True;
        Status = ZwSetInformationFile(
                     m_hFile,
                     &IoStatusBlock,
                     &FileInformation,
                     sizeof(FileInformation),
                     FileDispositionInformation);
        return NT_SUCCESS(Status);
    }

    ULong GetCurrentPos()
    {
        return (ULong)m_Offset.LowPart;
    }

    UInt64 GetCurrentPos64()
    {
        return m_Offset.QuadPart;
    }

    Bool Rewind()
    {
        return Seek(FILE_SEEK_BEGIN, 0);
    }

    Bool SetEndOfFile()
    {
        return ::SetEndOfFile(m_hFile);
    }

    HANDLE GetHandle() const
    {
        return m_hFile;
    }
};

#endif // CPP_DEFINED

#endif /* _FILEDISK_H_ */
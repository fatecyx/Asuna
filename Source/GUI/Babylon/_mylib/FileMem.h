#ifndef _FILEMEM_H_
#define _FILEMEM_H_

#include "pragma_once.h"

#if CPP_DEFINED

#include "FileBase.h"
#include <Windows.h>
#include "Mem.h"

class CFileMem : public CFileBase<CFileMem>
{
public:
    CFileMem();
    ~CFileMem();    
    enum DesiredAccess { NONE  = 0, READ  = 0x1,  WRITE = 0x2 };
    enum CreationDisposition { NEW, EXIST, ALWAYS };

public:
    Bool Open(const Char *szFile, DWORD dwSize, DesiredAccess access = READ, CreationDisposition dispos = EXIST);
    Void Close();
    Bool IsInit();

    Bool Seek(u32 uMethod, s32 iOffset, ps32 pOffsetHigh = NULL);
    Bool Read(Void *lpBuffer, u32 uSize, OPTIONAL pu32 pBytesRead = NULL);
    Bool Write(Void *lpBuffer, u32 uSize, OPTIONAL pu32 pBytesWritten = NULL);
    u32  GetCurrentPos();
    Bool Rewind();
    u32 GetSize(OPTIONAL pu32 puSizeHigh = NULL) const;

protected:
    Bool SetMemSize(DWORD dwSize);

protected:
    CMem   mem;
    DWORD  m_dwMemSize, m_dwOffset, m_dwSize;
    PBYTE  m_pbFile;
    HANDLE m_hFile, m_hHeap;
    DesiredAccess m_access;
};

#endif // CPP_DEFINED

#endif /* _FILEMEM_H_ */
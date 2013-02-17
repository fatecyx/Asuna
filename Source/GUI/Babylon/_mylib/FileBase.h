#ifndef _FILEBASE_H_
#define _FILEBASE_H_

#include "my_types.h"
#include "nt_api.h"

class NOVTABLE __CFileBase
{
public:
    enum SeekMethod
    {
        FILE_SEEK_BEGIN   = FILE_BEGIN,
        FILE_SEEK_CURRENT = FILE_CURRENT,
        FILE_SEEK_END     = FILE_END,
    };

public:
    Bool Seek(ULong uMethod, s32 iOffset, ps32 pOffsetHigh = NULL)
    {
        UNUSED_VARIABLE(uMethod);
        UNUSED_VARIABLE(iOffset);
        UNUSED_VARIABLE(pOffsetHigh);
        return False;
    }

    Bool Read(Void *lpBuffer, SizeT Size, OPTIONAL PULong pBytesRead = NULL)
    {
        UNUSED_VARIABLE(lpBuffer);
        UNUSED_VARIABLE(Size);
        UNUSED_VARIABLE(pBytesRead);
        return False;
    }

    Bool Write(Void *lpBuffer, SizeT Size, OPTIONAL PULong pBytesWritten = NULL)
    {
        UNUSED_VARIABLE(lpBuffer);
        UNUSED_VARIABLE(Size);
        UNUSED_VARIABLE(pBytesWritten);
        return False;
    }

    SizeT  ReadByte() { return 0; }
    SizeT  ReadWord() { return 0; }
    SizeT  ReadDword() { return 0; }
    Bool    WriteByte(u8) { return 0; }
    Bool    WriteWord(u16) { return False; }
    Bool    WriteDword(ULong) { return False; }
    SizeT  GetCurrentPos() { return m_Offset.LowPart; }
    Int64   GetCurrentPos64() { return m_Offset.QuadPart; }
    Bool    Rewind() { return False; };

    inline Bool IsEof()
    {
        return GetCurrentPos64() >= m_FileSize.QuadPart;
    }

    inline SizeT SetSection(SizeT uHead, SizeT uTail)
    {
        if (uTail < uHead)
            return 0;
        m_dwHead = uHead;
        m_dwTail = uTail;
        m_dwSize = uTail - uHead;
        return m_dwSize;
    }

    inline SizeT GetHead() const { return m_dwHead; }
    inline SizeT GetTail() const { return m_dwTail; }
    inline UInt64 GetSize64() const { return m_FileSize.QuadPart; }
    inline SizeT GetSize(OPTIONAL PULong puSizeHigh = NULL) const
    {
        if (puSizeHigh)
            *puSizeHigh = m_FileSize.HighPart;

        return m_FileSize.LowPart;
    }

    static
    inline
    Bool
    AnsiToUnicode(
        PUNICODE_STRING pUnicodeString, 
        PCChar          lpFileName, 
        PWChar          pszBuffer = NULL, 
        UInt            cbSize = 0
    )
    {
        NTSTATUS Status;
        ANSI_STRING ansi;

        RtlInitAnsiString(&ansi, lpFileName);
        if (pszBuffer)
        {
            pUnicodeString->Buffer = pszBuffer;
            pUnicodeString->MaximumLength = (UShort)cbSize;
        }
        Status = RtlAnsiStringToUnicodeString(pUnicodeString, &ansi, pszBuffer == NULL);

        return NT_SUCCESS(Status);
    }

    static
    inline
    Bool
    UnicodeToAnsi(
        PANSI_STRING pAnsiString, 
        PCWChar      lpFileName, 
        PChar        pszBuffer = NULL, 
        UInt         cbSize = 0)
    {
        NTSTATUS Status;
        UNICODE_STRING ustr;

        RtlInitUnicodeString(&ustr, lpFileName);
        if (pszBuffer)
        {
            pAnsiString->Buffer = pszBuffer;
            pAnsiString->MaximumLength = (UShort)cbSize;
        }
        Status = RtlUnicodeStringToAnsiString(pAnsiString, &ustr, pszBuffer == NULL);

        return NT_SUCCESS(Status);
    }

protected:
    Large_Integer m_FileSize, m_Offset;             // absolute
    SizeT m_dwHead, m_dwTail, m_dwSize, m_dwPos;    // relative
};

template<class TBase = __CFileBase>
class NOVTABLE CFileBase : public __CFileBase
{
public:
    Bool Seek(Long uMethod, Long iOffset, PLong pOffsetHigh = NULL)
    {
        TBase *p = (TBase *)this;
        return p->Seek(uMethod, iOffset, pOffsetHigh);
    }

    Bool Read(PVoid lpBuffer, SizeT Size, OPTIONAL PULong pBytesRead = NULL, LPOVERLAPPED lpOverlapped = NULL)
    {
        TBase *p = (TBase *)this;
        return p->Read(lpBuffer, Size, pBytesRead, lpOverlapped);
    }

    Bool Write(Void *lpBuffer, SizeT Size, OPTIONAL PULong pBytesWritten = NULL)
    {
        TBase *p = (TBase *)this;
        return p->Write(lpBuffer, Size, pBytesWritten);
    }

    SizeT ReadByte()
    {
        TBase *p = (TBase *)this;
        return p->ReadByte();
    }

    SizeT ReadWord()
    {
        TBase *p = (TBase *)this;
        return p->ReadWord();
    }

    SizeT ReadDword()
    {
        TBase *p = (TBase *)this;
        return p->ReadDword();
    }

    Bool WriteByte(u8 v)
    {
        TBase *p = (TBase *)this;
        return p->WriteByte(v);
    }

    Bool WriteWord(u16 v)
    {
        TBase *p = (TBase *)this;
        return p->WriteWord(v);
    }

    Bool WriteDword(ULong v)
    {
        TBase *p = (TBase *)this;
        return p->WriteDword(v);
    }

    SizeT GetCurrentPos()
    {
        TBase *p = (TBase *)this;
        return p->GetCurrentPos();
    }

    UInt64 GetCurrentPos64()
    {
        TBase *p = (TBase *)this;
        return p->GetCurrentPos64();
    }

    Bool Rewind()
    {
        TBase *p = (TBase *)this;
        return p->Rewind();
    }

    Bool SetEndOfFile()
    {
        TBase *p = (TBase *)this;
        return p->SetEndOfFile();
    }
};

#endif /* _FILEBASE_H_ */
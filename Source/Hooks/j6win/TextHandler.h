#ifndef _TEXTHANDLER_H_
#define _TEXTHANDLER_H_

#include <Windows.h>
#include "my_headers.h"

#pragma pack(1)

typedef struct
{
    UInt32  Hash[4];
    UInt32 Length;
} STextHeader;

#pragma pack()

class CTextHandler
{
public:
    CTextHandler();
    ~CTextHandler();

    Bool         Init(PVoid lpBuffer, UInt32 dwBufferSize);
    Int          GetText(PVoid pvOutBuffer, Int32 BufferSize, PCChar lpSrcText, Int32 SrcLength);
    STextHeader* RemoveText(PCChar lpSrcText, Int32 SrcLength);

protected:
    Int          GetTextInternal(PVoid pvOutBuffer, Int32 BufferSize, PCChar lpSrcText, Int32 SrcLength, Bool bRemove);
    STextHeader* FindTextPos(UInt32 dwHash[4], Bool bRemove = False);

protected:
    PByte         m_pbBuffer;
    STextHeader **m_pIndex;
    UInt32        m_BufferSize, m_Key, m_IndexCount, m_MaxIndexCount;
    CMem          m_mem;
};

#endif /* _TEXTHANDLER_H_ */
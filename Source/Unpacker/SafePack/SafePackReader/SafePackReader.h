#ifndef _SAFEPACKREADER_H_b1f323e8_670a_4883_8549_098b0c4596e4
#define _SAFEPACKREADER_H_b1f323e8_670a_4883_8549_098b0c4596e4

#include "pragma_once.h"
#include "my_headers.h"
#include "../SafePacker.h"

#define SAFE_PACK_XOR     0x83AC429E

#pragma pack(1)

typedef struct
{
    LARGE_INTEGER   Offset;
    ULONG           Size;
    ULONG           Flags;
    ULONG           Hash[8];
} SAFE_PACK_FILE_INFO;

#pragma pack()

class CSafePackReader : public CUnpackerImpl<CSafePackReader>
{
protected:
    PVOID               m_CompressedBuffer;
    ULONG               m_CompressedBufferSize;
    LARGE_INTEGER       m_EntryCount;
    SAFE_PACK_ENTRY    *m_Entry;
    CNtFileDisk         file;

public:
    CSafePackReader();
    ~CSafePackReader();

    NTSTATUS Open(PCWSTR FileName);
    NTSTATUS ReleaseAll();
    NTSTATUS GetFileInfo(PCSTR FileName, SAFE_PACK_FILE_INFO *Info);
    NTSTATUS Read(SAFE_PACK_FILE_INFO *Info, PVOID Buffer, ULONG BufferSize);

protected:
    SAFE_PACK_ENTRY* FindFile(SAFE_PACK_ENTRY *EntryBase, ULONG EntryCount, PULONG Hash);
};

#endif // _SAFEPACKREADER_H_b1f323e8_670a_4883_8549_098b0c4596e4

#ifndef _XAR_H_3b78de46_8d01_4885_a9db_51bbbcf81a50
#define _XAR_H_3b78de46_8d01_4885_a9db_51bbbcf81a50

#include "pragma_once.h"
#include <Windows.h>
#include "my_headers.h"
#include "upk_common.h"

#pragma pack(1)

#define XAR_SIGNATURE "XLARCHIVE"

typedef struct
{
    CHAR    Signature[0xA];
    USHORT  Unknown;
    CHAR    Hansom[0x7];    // ?

    DUMMY_STRUCT(0xD);      // fill with ' '

    ULONG   Offset;
    ULONG   Size;
    ULONG   Crc;            // byte crc32 sum
    ULONG   Unknown2;
    ULONG   Unknown3;
    ULONG   Unknown4;

    DUMMY_STRUCT(0x30);
} XAR_HEADER;

#pragma pack()

class CXar : public CUnpackerImpl<CXar>
{
protected:
    CNtFileDisk file;
    ULONG       m_BeginOffset;

public:
    BOOL Open(LPCWSTR FileName);
    BOOL GetFileData(UNPACKER_FILE_INFO *FileInfo, const MY_FILE_ENTRY_BASE *BaseEntry, BOOL SaveRawData);

protected:
    VOID DecryptHeader(XAR_HEADER *Header);
    VOID DecryptData(ULONG Unknown3, PVOID Buffer, ULONG Size, ULONG Offset);
    BOOL ValidateXar(XAR_HEADER *Header);
};

#endif // _XAR_H_3b78de46_8d01_4885_a9db_51bbbcf81a50

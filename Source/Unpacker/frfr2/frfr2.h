#ifndef _FRFR2_H_a9bfe0e8_1bb3_4928_a420_5ead9bc81ff7
#define _FRFR2_H_a9bfe0e8_1bb3_4928_a420_5ead9bc81ff7

#include <Windows.h>
#include "my_headers.h"
#include "upk_common.h"

#define FRFR2_IGA_MAGIC TAG4('IGA0')

#pragma pack(1)

typedef struct
{
    ULONG   Magic;
    ULONG   Crc;
    USHORT  Version;
    USHORT  Reserve;
    ULONG   Reserve2;
} FRFR2_IGA_HEADER;

typedef struct
{
    ULONG FileNameOffset;
    ULONG Offset;
    ULONG Size;
} FRFR2_IGA_ENTRY;

#pragma pack()

class CFrfr2 : public CUnpackerImpl<CFrfr2>
{
protected:
    CNtFileDisk file;

public:
    BOOL Open(PCWSTR FileName);
    BOOL GetFileData(UNPACKER_FILE_INFO *FileInfo, const MY_FILE_ENTRY_BASE *BaseEntry, BOOL SaveRawData = FALSE);

protected:
    ULONG GetCompactInteger(PBYTE &Buffer, PULONG Length = NULL);
    BOOL
    InitIndex(
        FRFR2_IGA_HEADER   *Header,
        PBYTE               EntryBuffer,
        ULONG               EntrySize,
        PBYTE               FileNameBuffer,
        ULONG               FileNameSize
    );
};

#endif // _FRFR2_H_a9bfe0e8_1bb3_4928_a420_5ead9bc81ff7

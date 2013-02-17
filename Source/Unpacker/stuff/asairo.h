#ifndef _ASAIRO_H_
#define _ASAIRO_H_

#include <Windows.h>
#include "my_headers.h"
#include "upk_common.h"

#pragma pack(1)

typedef struct
{
    UInt32 uIndexOffset;
    UInt32 FileNum;
} SMpkHeader;

typedef struct
{
    Char   szFileName[0x20];
    UInt32 uOffset;
    UInt32 uSize;
} MPK_ENTRY;

typedef struct
{
    UInt32     uCount;
    MPK_ENTRY *pIndex;
} SMyMpkEntry;

typedef struct
{
    UInt32 uDecompSize;
    UInt32 uCompSize;
    Byte   byData[1];
} SMgrFile;

struct MY_MPK_ENTRY : public MY_FILE_ENTRY_BASE
{
};

#pragma pack()

class CAsairo : public CUnpackerImpl<CAsairo>
{
protected:
    CFileDisk f;

public:
    Bool   Open(PWChar szFileName);
    Bool   GetFileData(SFileInfo *pFileInfo, const MY_FILE_ENTRY_BASE *pInfo);
    UInt32 Pack(PCWChar szPath);

protected:
    UInt32 Decompress(PByte pbBuffer, UInt32 uBufferSize, PByte pbOutput, UInt32 uOutBufferSize);
    Bool   InitIndex();
};

#endif /* _ASAIRO_H_ */
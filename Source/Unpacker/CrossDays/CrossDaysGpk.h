#ifndef _CROSSDAYSGPK_H_
#define _CROSSDAYSGPK_H_

#include <Windows.h>
#include "my_common.h"
#include "FileDisk.h"
#include "Mem.h"

#pragma pack(1)

typedef struct
{
    USHORT usNameLength;
    WCHAR  szName[0x20];
    DWORD  v1;
    USHORT v2;
    DWORD  dwOffset;
    DWORD  dwSize;
    DWORD  dwTag;
    DWORD  dwUncompressSize;
    BYTE   byHeadLength;
    BYTE   head[0x8];
} TGpkIndexInFile;

typedef struct
{
    CHAR   tag1[0xC];
    DWORD  uiIndexSize;
    CHAR   tag2[0x10];
} TGpkTail;

typedef struct
{
    DWORD  v1;
    USHORT v2;
    DWORD  dwOffset;
    DWORD  dwSize;
    DWORD  dwTag;
    DWORD  dwUncompressSize;
    DWORD  dwHeadLength;
    PBYTE  pbHead;
    WCHAR  szName[MAX_PATH];
} TMyGpkIndex;

#pragma pack()

#define ZLIB_COMP 'TLFD'
#define NO_COMP   '    '

enum CDG_Status
{
    CDG_SUCCESS, 
    CDG_EGENERAL, 
    CDG_EOPEN,       // open failed
    CDG_ESEEK,       // seek failed
    CDG_EREAD,       // read failed
    CDG_EFORMAT,     // invalid GPK file
    CDG_EMEMORY,     // allocate memory failed
    CDG_EDECOMP,     // uncompress failed
};

class CCrossDaysGpk : public CMem
{
public:
    CCrossDaysGpk();
    ~CCrossDaysGpk();

public:
    LONG  Open(WChar *szFile);
    Void  Close();
    DWORD GetFileCount();
    LONG  GetFileData(TMyGpkIndex *pIndex, PBYTE *pbOut, LPDWORD pdwFileSize);
    DWORD ExtractAll(LPWSTR lpOutDirectory);
    LONG  ExtractFile(TMyGpkIndex *pIndex, LPWSTR lpOutDirectory);
    TMyGpkIndex* GetIndexPointer(DWORD dwIndex);

protected:
    Void  Reset();

    LONG InitIndex(PBYTE pbBuffer, DWORD dwSize);

protected:
    DWORD  m_dwFiles;
    CFileDisk FileDisk;
    TMyGpkIndex *m_pIndex;
};

#endif /* _CROSSDAYSGPK_H_ */
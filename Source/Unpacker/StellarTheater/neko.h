#ifndef _NEKO_H_
#define _NEKO_H_

#include "my_common.h"
#include "FileDisk.h"
#include "Mem.h"

#pragma pack(1)

typedef struct
{
    Char   tag[8];
    UInt32 hash;
    UInt32 ver;
} SNekoHeader;

typedef struct
{
    UInt32 hash;
    UInt32 size;
} SDataEntry;

typedef struct
{
    UInt32 hash;
    UInt32 size;
    UInt32 offset;
} SNekoFileIndex;

typedef struct
{
    UInt32      hash;
    UInt32      filenum;
    SNekoFileIndex *pIndex;
} SNekoDirIndex;

typedef struct
{
    UInt32    hash;
    UInt32    ver;
    UInt32    dirNum;
    SNekoDirIndex *pDir;
} SNekoPack;

#pragma pack()

class CNekoPack
{
public:
    CNekoPack();
    ~CNekoPack();

    Bool   Open(Char *szFile);
    UInt32 ExtractFile(PChar szFile, PChar szOutPath = NULL);
    UInt32 ExtractAll (PChar szOutPath = NULL);

protected:
    Void Destroy();
    Bool CheckParity(UInt32 hash, UInt32 IndexSize);
    Bool GetKey(PULARGE_INTEGER pKey, UInt32 seed);
    Bool Decrypt(LPVoid lpInput, LPVoid lpOutput, UInt32 uSize, UInt32 seed);
    Bool Decrypt(LPVoid lpInput, LPVoid lpOutput, UInt32 uSize, PULARGE_INTEGER pKey);
    Bool InitIndex(LPVoid lpBuffer, UInt32 uSize);

    PChar  GuessExt(LPVoid lpBuffer);
    UInt32 HashName(PChar szFile, UInt32 seed);
    SNekoDirIndex*  FindDir(PChar szFile);
    SNekoFileIndex* FindFile(PChar szFile, SNekoDirIndex *pDirEntry);

protected:
    CMem m;
    CFileDisk file;
    SNekoPack m_neko;
};

#endif /* _NEKO_H_ */
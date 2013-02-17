#ifndef _YSTB_H_
#define _YSTB_H_

#include <Windows.h>
#include "my_headers.h"

#pragma pack(1)

typedef struct
{
    UInt32 magic;       // YSXX
    UInt32 ver;         // 0x04
    UInt32 PartCount;   // 0x08
    UInt32 PartSize;    // 0x0C
    UInt32 OPCodeSize;  // 0x10
    UInt32 DataSize;    // 0x14
    UInt32 IndexTable;  // 0x18
    UInt32 reserve;
} SYSHeader;

typedef struct
{
//    UInt32 op;
    Byte   op;
    Byte   reserve;
    Byte   flag1;
    Byte   flag2;
    UInt32 Length;
    UInt32 Offset;
} SYSOPCode;

typedef struct
{
    Byte   op;
    Byte   count;
    UInt16 reserve;
} SYSOPInfo;

typedef struct
{
    UInt32       PartCount;
    SYSOPInfo   *pOPInfo;
    SYSOPCode  **ppOPCode;
    PByte        pbOPCode;
    PByte        pbData;
    PUInt32      pIndexTable;
} SYSTBInfo;

#pragma pack()

enum ESymbol
{
    SYM_IMAGE = 0x01, 
    SYM_SE    = 0x0E, 
};

enum EScrType
{
    SCR_INVALID, 
    SCR_YSTB, 
    SCR_YSCM, 
    SCR_YSCF, 
    SCR_YSER, 
    SCR_YSLB, 
    SCR_YSTD, 
    SCR_YSTL, 
};

class CYurisScriptParser
{
protected:
    CMem      m;
    CFileDisk file;

public:
    CYurisScriptParser();
    ~CYurisScriptParser();

    Bool Auto  (PWChar pszFile);
    Bool Parse (PWChar pszFile);
    Bool Import(PWChar pszText);

protected:
    Bool   ParseB(LPVoid lpBuffer, UInt32 BufferSize, PWChar pszInputFile);
    UInt32 ImportYSTB(LPVoid lpBuffer, UInt32 ScriptSize, UInt32 BufferSize, FILE *fText);

    Void UpdateOffset(PUInt32 *pOffsetIndex, UInt32 Count, Int32 Diff, UInt32 ModifiedOffset, SYSTBInfo *pTBInfo);

    Bool   IsAnsi(PCChar p, UInt32 len);
    UInt32 WriteToFile(FILE *fp, LPVoid lpBuffer, UInt32 Len, SYSOPInfo *pOPInfo, SYSOPCode *pOPCode);
};

#endif /* _YSTB_H_ */
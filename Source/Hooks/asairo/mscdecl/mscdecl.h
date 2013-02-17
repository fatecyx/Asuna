#ifndef _MSCDECL_H_
#define _MSCDECL_H_

#pragma warning(disable:4530)

#include "my_common.h"
#include "Mem.h"
#include "FileDisk.h"
#include <vector>

using std::vector;

#pragma pack(1)

/* file struct

  SMscHeader UInt32_Index1_Size SMscIndex1 UInt32_Index2_Size SMscIndex2 op_code ...
*/

typedef struct
{
    Byte   unk;
    UInt32 id;
    UInt32 offset;
} SMscIndex;

typedef struct
{
    UInt32 num;
    SMscIndex *index;
} SMyMscIndex;

typedef struct
{
    UInt16 unknown;
    UInt32 uBegOffset;
} SMscHeader;

typedef struct
{
    UInt32 len;
    Char   text[1];
} SMscText;

typedef struct
{
    UInt32    op;
    UInt32    offset;
    UInt32    len;
    PByte     param;
    UInt32    textnum;
    SMscText *pText;
    UInt32    next;
    Byte      reserve[4];   // mod 16
} SCode;

typedef struct
{
    UInt32 num;
    UInt32 max;
    UInt32 next_index;
    SCode *pCode;
} SScriptData;

#pragma pack()

class CMscDecl : public CMem
{
public:
    CMscDecl();
    ~CMscDecl();

    Bool DecompileFile(PCWChar lpMscFile, PCWChar lpOutputFile = NULL);
    Void Close();

    Bool PeekText(PCWChar lpMscFile, PCWChar lpOutputFile = NULL);

protected:
    Bool Decompile(LPCVoid lpBuffer, Int32 iLength);
    UInt32 DecompileCode(PByte &pbBuffer, LPCVoid lpBuffer);

    UInt32 GetCode00(PByte &pbBuffer, SCode *pCode);
    UInt32 GetCode01(PByte &pbBuffer, SCode *pCode);
    UInt32 GetCode02(PByte &pbBuffer, SCode *pCode);
    UInt32 GetCode03(PByte &pbBuffer, SCode *pCode);
    UInt32 GetCode04(PByte &pbBuffer, SCode *pCode);
    UInt32 GetCode05(PByte &pbBuffer, SCode *pCode);
    UInt32 GetCode06(PByte &pbBuffer, SCode *pCode);
    Void   GetParam(SCode *pCode, PByte pbCode, UInt32 uTextOffset = -1, UInt32 uTextNum = 1);

    Bool  IsOutOfBound(PByte pbBuffer, LPCVoid lpBuffer);
    Bool  IsTextValid(SMscText *pText);
    Int32 FindNearestOffset(Int32 pos);
    Int32 FindOffsetByID(Int32 id);

protected:
    SScriptData m_scr;
    SMyMscIndex m_index[2];
    Int32 m_jump1, m_jump2;
};

enum ESymbol00
{
    SYM_00_JUMP_OFFSET = 2,
    SYM_00_JUMP_ID = 3,
    SYM_00_LOAD_SCRIPT = 8,
};

enum ESymbol01
{
    SYM_01_SET_TITLE   = 0,
    SYM_01_LOAD_SCRIPT = 1,
    SYM_01_CHAR_INFO   = 3,
    SYM_01_LOAD_SOUND  = 4,
    SYM_01_UNKNOWN_CHARNAME = 0x18,
};

#endif /* _MSCDECL_H_ */
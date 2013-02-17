#ifndef _YBN2LUA_H_
#define _YBN2LUA_H_

#include "pragma_once.h"
#include <Windows.h>
#include "my_headers.h"

#pragma pack(1)

/************************************************************************
  7990 InstructionIndex
  7994 pFuncTable
  7998 ParamCountTable
  799C ParamTable
  79A0 pParamData
************************************************************************/

typedef struct
{
    PCHAR  VariableName;
    ULONG  Hash;
    ULONG  Unknown1;
    USHORT Value;
    BYTE   Unknown2;
    BYTE   Unknown3;
} YU_RIS_VARIABLE;

/************************************************************************
  header                    0x20
  Instruction section       InstructionCount * 4
  Instruction param section InstructionCount * 0xC
  Instruction data section  ...
  unknown index table       UnknownIndexSize
************************************************************************/

#define YBN_MAGIC TAG4('YSTB')

typedef struct
{
    ULONG Magic;
    ULONG Version;
    ULONG FunctionCount;
    ULONG FunctionSize;
    ULONG FunctionParamSize;
    ULONG ParamDataSize;
    ULONG UnknownIndexSize;
    ULONG Reserve;
} YU_RIS_YBN_HEADER;

typedef struct
{
    BYTE    FuncID;
    BYTE    ParamCount;
    USHORT  Reserve;
} YU_RIS_YBN_FUNCTION;

typedef struct
{
    BYTE Option[4];

    union
    {
        ULONG DataLength;
/*
        struct
        {
            ULONG Length : 28;
            BYTE  Flags  : 4;   // IsRelocaed
        } u1;
*/
    };
    ULONG DataOffset;         // begin from data section
} YU_RIS_YBN_FUNCTION_PARAM;

// escape char  `#$

enum
{
    DATA_21              = 0x21,
    DATA_25              = 0x25,     // div int64
    DATA_26              = 0x26,
    DATA_29              = 0x29,     // len = 1, data = 0
    DATA_2A              = 0x2A,     // len = 0, Int64 Mul
    DATA_2B              = 0x2B,     // len = 0, mov ??
    DATA_2C              = 0x2C,     // len = 0, NOP
    DATA_2D              = 0x2D,     // sub int64
    DATA_2F              = 0x2F,     // div int64
    DATA_3C              = 0x3C,
    DATA_3D              = 0x3D,
    DATA_3E              = 0x3E,
    DATA_41              = 0x41,     // and int64
    DATA_CHAR            = 0x42,     // byte to int64
    DATA_46              = 0x46,     // len = 8, int64 ?
    DATA_USHORT          = 0x48,     // byte ??, WORD Value
    DATA_LONG            = 0x49,     // len = 4, int to int64
    DATA_INT64           = 0x4C,     // 8 byte int64
    DATA_STRING          = 0x4D,     // 'sep' string 'sep'
    DATA_4F              = 0x4F,     // or int64
    DATA_52              = 0x52,
    DATA_53              = 0x53,
    DATA_56              = 0x56,     // ec + byte
    DATA_SHORT           = 0x57,     // word to int64
    DATA_5A              = 0x5A,     // len = 0, no data  cmp ??
    DATA_5E              = 0x5E,     // xor int64
    DATA_69              = 0x69,
    DATA_73              = 0x73,
    DATA_76              = 0x76,     // ec + word
    DATA_7C              = 0x7C,

    DATA_LAST,
};

typedef struct
{
    BYTE    Type;
    USHORT  Length;
    BYTE    Data[1];
} *PYU_RIS_FUNCTION_DATA;

typedef struct
{
    YU_RIS_YBN_HEADER         *pYbn;
    YU_RIS_YBN_FUNCTION       *pFunc;
    YU_RIS_YBN_FUNCTION_PARAM *pParam;
    PYU_RIS_FUNCTION_DATA      pData;
    PULONG                     pUnknown;

    YU_RIS_YBN_FUNCTION       *pCurFunc;
    YU_RIS_YBN_FUNCTION_PARAM *pCurParam;
    PYU_RIS_FUNCTION_DATA      pCurData;
} YU_RIS_YBN_INFO;

enum
{
    YURIS_OP_SWITCH_YBN = 0x1C,   // keep ins index
};

enum
{
    YURIS_FUNC_1E       = 0x1E,
    YURIS_FUNC_29       = 0x29,
    YURIS_FUNC_SETTEXT  = 0x5B,
};

#pragma pack()

#define DECL_YBN_HANDLER(func) \
            BOOL\
            (func)(\
                CFileDisk                   &file, \
                PCHAR                        Buffer, \
                struct YBN_FUNCTION_INFO    *pFuncInfo, \
                YU_RIS_YBN_INFO             *pYbnInfo, \
                YU_RIS_YBN_FUNCTION         *pFunc, \
                YU_RIS_YBN_FUNCTION_PARAM   *pParam \
            )

#define WriteScr(...) { if (!WriteText(file, Buffer, __VA_ARGS__)) return FALSE; }

class CYBNToLua
{
protected:
    CMem                         m_mem;
    YU_RIS_YBN_INFO              m_YbnInfo;
    struct YBN_PARAM_DATA_INFO  *m_pParamDataInfo;
    struct YBN_FUNCTION_INFO    *m_pFuncInfo;

public:
    CYBNToLua();
    ~CYBNToLua();

    BOOL ConvertYbnToLua(PCWCHAR pszFileName);

    DECL_YBN_HANDLER(Func1E);
    DECL_YBN_HANDLER(Func29);
    DECL_YBN_HANDLER(SetText);

protected:
    VOID Reset();

    BOOL ParseYbn(YU_RIS_YBN_INFO *pYbn, ULONG BufferSize);
    BOOL ConvertToLua(YU_RIS_YBN_INFO *pYbnInfo, PCWCHAR pszYbnName);
    BOOL CreateBaseScript(PWCHAR pszFileName, PCHAR Buffer);

    BOOL
    WriteParam(
        YU_RIS_YBN_INFO             *pYbnInfo,
        YU_RIS_YBN_FUNCTION         *pFunc,
        YU_RIS_YBN_FUNCTION_PARAM   *pParam,
        YBN_FUNCTION_INFO           *pFuncInfo,
        CFileDisk                   &file,
        PCHAR                        Buffer
    );

    BOOL WriteData (PYU_RIS_FUNCTION_DATA pData, ULONG DataLength, CFileDisk &file, PCHAR Buffer);
    BOOL WriteText (CFileDisk &file, PCHAR pBuffer, LPCSTR pszFormat, ...);
};

typedef DECL_YBN_HANDLER(CYBNToLua::*FFuncHandler);

#endif // _YBN2LUA_H_

/******************* DataType *************************
0x21: 41BDC0
0x25: 41C328
0x26: 41C430
0x29: 41B4E4
0x2A: 41C1FC
0x2B: 41BB20
0x2C: 41C5D0
0x2D: 41C198
0x2F: 41C274
0x3C: 41BFCC
0x3D: 41BC50
0x3E: 41BF30
0x41: 41C3A0
0x42: 41B710
0x46: 41B8D4
0x48: 41A678
0x49: 41B800
0x4C: 41B868
0x4D: 41A46C
0x4F: 41C3E8
0x52: 41B95C
0x53: 41C0FC
0x56: 41B348
0x57: 41B788
0x5A: 41C064
0x5E: 41C588
0x69: 41BAD8
0x73: 41B9B8
0x76: 41B42C
0x7C: 41C4DC
*********************************************************/
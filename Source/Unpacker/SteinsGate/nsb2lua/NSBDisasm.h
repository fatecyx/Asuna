#ifndef _NSBDISASM_H_
#define _NSBDISASM_H_

#include "pragma_once.h"
#include <Windows.h>
#include "my_headers.h"

#pragma pack(1)

typedef struct
{
    USHORT Length;
    CHAR   Buffer[1];
} N2_ANSI_STRING;

typedef struct
{
    LONG Length;
    CHAR Buffer[1];
} N2_ANSI_STRING_L;

typedef struct
{
    ULONG  Offset;
    N2_ANSI_STRING FuncName;
} *PN2_FUNCTION_MAP;

typedef struct
{
    ULONG            Index;
    USHORT           OP;
    USHORT           ParamCount;
    N2_ANSI_STRING_L Param[1];
} *PN2_INSTRUCTION_INFO;

typedef struct
{
    ULONG               Count;
    ULONG               MaxCount;
    PN2_FUNCTION_MAP   *pMap;
} N2_FUNCTION_MAP_RECORD;

typedef struct
{
    ULONG Offset;
    PN2_INSTRUCTION_INFO pInstruction;
} INSTRUCTION_ENTRY;

typedef struct
{
    ULONG               Count;
    ULONG               MaxCount;
    INSTRUCTION_ENTRY  *pInstruction;
} N2_SCRIPT_BINARY_RECORD;

#pragma pack()

struct INSTRUCTION_INFO;
#define DECL_HANDLER(_Handler) BOOL (CNsbDisassembler::_Handler)(CFileDisk &file, PCHAR Buffer, PCHAR Buffer2, INSTRUCTION_ENTRY *pInstruction, INSTRUCTION_INFO *pInfo)

class CNsbDisassembler
{
protected:
    N2_FUNCTION_MAP_RECORD  m_FuncRecord;
    N2_SCRIPT_BINARY_RECORD m_NsbRecord;
    INSTRUCTION_INFO       *m_pInfoMap;
    CMem m_mem;

public:
    CNsbDisassembler();
    ~CNsbDisassembler();

    BOOL DisassembleFile(PWCHAR pszNsbFile, PWCHAR pszScriptFile = NULL);

protected:
    VOID Reset();

    BOOL WriteText(CFileDisk &file, PCHAR pBuffer, LPCSTR pszFormat, ...);

    BOOL ParseFunctionMap(PVOID pvBuffer, ULONG BufferSize);
    BOOL ParseN2ScriptBin(PVOID pvBuffer, ULONG BufferSize);
    BOOL CreateBaseScript(PWCHAR pszFileName, PCHAR Buffer2);
    BOOL DumpToScript(PWCHAR pszScriptName);

public:
    DECL_HANDLER(SetText);
};

struct INSTRUCTION_INFO
{
    ULONG OP;
    PCHAR pszName;
    PCHAR pszFunction;
    DECL_HANDLER(*pfHandler);
};

#endif // _NSBDISASM_H_
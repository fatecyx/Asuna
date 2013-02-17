#ifndef _BGISCRIPT2LUA_H_67799d17_aa05_4199_ad08_6c801b29ba4a
#define _BGISCRIPT2LUA_H_67799d17_aa05_4199_ad08_6c801b29ba4a

#include "pragma_once.h"
#include "my_headers.h"

#pragma pack(1)

#define BGI_BP_MAX_OP   0xFF

#define BGI_BURIKO_SCRIPT_MAGIC "BurikoCompiledScriptVer1.00"

typedef struct
{
    ULONG   HeaderSize;
    ULONG   InstructionSize;
    ULONG   Reserve[2];
} BGI_BP_HEADER;

typedef struct
{
    CHAR  Magic[0x1C];
    ULONG HeaderSize;
    ULONG Reserve;
} BGI_BURIKO_SCRIPT_HEADER;

typedef struct
{
    ULONG   OP;
    PBYTE   pbParam;
    ULONG   Flags;
    ULONG   Offset;
} INSTRUCTION_RECORD;

typedef struct
{
    PCHAR               FuncName;
    ULONG               RecordCount;
    ULONG               MaxRecordCount;
    INSTRUCTION_RECORD *pRecord;
} BGI_BURIKO_SCRIPT_RECORD;

typedef struct
{
    union
    {
        BGI_BP_HEADER               *pBpHeader;
        BGI_BURIKO_SCRIPT_HEADER    *pBurikoHeader;
        PVOID                        pvScriptBuffer;
        PBYTE                        pbScriptBuffer;
    };

    PBYTE pbBuffer;
    PBYTE pbBegin;
    PBYTE pbEnd;
    ULONG FileSize;
    ULONG RecordCount;
    ULONG MaxRecordCount;

    struct
    {
        INSTRUCTION_RECORD  *pBpRecord;
        PBYTE                pbMask;
    } bp;

    struct
    {
        BGI_BURIKO_SCRIPT_RECORD *pScriptRecord;
        PBYTE pbMask;
    } scr;

} BGI_SCRIPT_INFO;

#pragma pack()

#define DECL_HANDLER(name) \
            HRESULT \
            (FASTCALL \
            CBGIScript2Lua:: \
            name)( \
                BGI_SCRIPT_INFO    *pScrInfo, \
                INSTRUCTION_RECORD &InsRecord, \
                BOOL bParser \
            )

struct BGI_BP_INSTRUCTION;
struct BGI_BURIKO_SCRIPT_INSTRUCTION;

class CCRTFile
{
protected:
    FILE *fp;

public:
    enum
    {
        FILE_SEEK_BEGIN     = SEEK_SET,
        FILE_SEEK_CURRENT   = SEEK_CUR,
        FILE_SEEK_END       = SEEK_END,
    };

public:
    CCRTFile()
    {
        fp = NULL;
    }

    ~CCRTFile()
    {
        Close();
    }

    BOOL Open(PWCHAR pszFileName)
    {
        Close();

        fp = _wfopen(pszFileName, L"rb+");
        return fp != NULL;
    }

    BOOL Create(PWCHAR pszFileName)
    {
        Close();

        fp = _wfopen(pszFileName, L"wb+");
        return fp != NULL;
    }

    BOOL Close()
    {
        if (fp != NULL)
        {
            fclose(fp);
            fp = NULL;
        }

        return TRUE;
    }

    BOOL Read(PVOID pvBuffer, ULONG Size)
    {
        return fread(pvBuffer, Size, 1, fp);
    }

    BOOL Write(PVOID pvBuffer, ULONG Size)
    {
        return fwrite(pvBuffer, Size, 1, fp);
    }

    ULONG GetSize()
    {
        return fsize(fp);
    }

    BOOL Seek(ULONG Method, ULONG Position)
    {
        return !fseek(fp, Position, Method);
    }
};

#define CFileDisk CCRTFile

class CBGIScript2Lua
{
protected:
    CMem                    m;
    CFileDisk               file;
    BGI_SCRIPT_INFO         m_Info;
    BGI_BP_INSTRUCTION     *m_pInstructionMap;
    BGI_BURIKO_SCRIPT_INSTRUCTION *m_pScriptInfoMap;

public:
    CBGIScript2Lua();
    ~CBGIScript2Lua();

    HRESULT ConvertScript(PWCHAR pszScriptFile);

protected:
    VOID Release();
    HRESULT Initialize();

    HRESULT ParseBPScript (BGI_SCRIPT_INFO *pScrInfo,BGI_BP_HEADER *pHeader);
    HRESULT DisaseembleBP(BGI_SCRIPT_INFO *pScrInfo);

    HRESULT
    SetBPRecord(
        BGI_SCRIPT_INFO     *pScrInfo,
        PBYTE                pbParam,
        BGI_BP_INSTRUCTION  *pIns,
        INSTRUCTION_RECORD  *pRecord
    );

    HRESULT ParseBPParam(BGI_SCRIPT_INFO *pScrInfo, INSTRUCTION_RECORD *pRecord);
    HRESULT AddBPInstruction(BGI_SCRIPT_INFO *pScrInfo, INSTRUCTION_RECORD *pInsRecord);
    HRESULT ConvertBPToLua(BGI_SCRIPT_INFO *pScrInfo, PWCHAR pszLuaFile);
    HRESULT CreateBaseBPLua(PWCHAR pszLuaFile, PCHAR Buffer);
    HRESULT WriteString(CFileDisk &file, PCHAR Buffer, PCHAR pString);

    HRESULT ParseBurikoScript(BGI_SCRIPT_INFO *pScrInfo, BGI_BURIKO_SCRIPT_HEADER *pHeader);
    HRESULT DisaseembleScrFunc(BGI_SCRIPT_INFO *pScrInfo);

    HRESULT
    AddFunction(
        BGI_SCRIPT_INFO            *pScrInfo,
        PCHAR                       pszFuncName,
        BGI_BURIKO_SCRIPT_RECORD  **ppScriptRecord
    );

    HRESULT
    SetScriptRecord(
        BGI_SCRIPT_INFO                 *pScrInfo,
        PBYTE                            pbParam,
        BGI_BURIKO_SCRIPT_INSTRUCTION   *pInfo,
        INSTRUCTION_RECORD              *pRecord
    );

    HRESULT ParseScriptParam(BGI_SCRIPT_INFO *pScrInfo, INSTRUCTION_RECORD *pRecord);
    HRESULT AddScriptInstruction(BGI_BURIKO_SCRIPT_RECORD *pScriptRecord, INSTRUCTION_RECORD *pInsRecord);
    HRESULT ConvertScriptToLua(BGI_SCRIPT_INFO *pScrInfo, PWCHAR pszLuaFile);
    HRESULT CreateBaseScrLua(PWCHAR pszLuaFile, PCHAR Buffer);
    PCHAR   IsLabelFunction(BGI_SCRIPT_INFO *pScrInfo, ULONG Offset);
    HRESULT ExScriptOPHandler(BGI_SCRIPT_INFO *pScrInfo, INSTRUCTION_RECORD *pRecord, PCHAR Buffer);

    HRESULT WriteText(CFileDisk &file, PCHAR pBuffer, LPCSTR pszFormat, ...);

public:
    DECL_HANDLER(PushProcAddrHandler);
};

#endif // _BGISCRIPT2LUA_H_67799d17_aa05_4199_ad08_6c801b29ba4a

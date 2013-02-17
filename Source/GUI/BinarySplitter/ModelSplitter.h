#ifndef _MODELSPLITTER_H_
#define _MODELSPLITTER_H_

#include "pragma_once.h"
#include "WindowBase.h"
#include "MyString.h"
#include "aes.h"
#include "IOCP.h"

using namespace MY_LIB_NAME;

OVERLOAD_OP_NEW

enum
{
    BSERR_SUCCESS = 0,

    BSERR_FIRST = 0x80000000,

    BSERR_NORMAL = BSERR_FIRST,
    BSERR_FILE_NOT_FOUND,
    BSERR_OPEN_FILE,
    BSERR_CREATE_FILE,
    BSERR_GET_FILE_SIZE,
    BSERR_READ_FILE,
    BSERR_WRITE_FILE,
    BSERR_CLOSE_FILE,
    BSERR_IOCP_CREATE,
    BSERR_IOCP_ASSOCIATE_DEVICE,
    BSERR_IOCP_GET_STATUS,
    BSERR_QUEUE_USER_WORD_ITEM,
    BSERR_OUT_OF_MEMORY,
    BSERR_INVALID_PARAM,
    BSERR_ZERO_FILE_SIZE,
    BSERR_INVALID_SLICE_SIZE,
    BSERR_INVALID_FILE_SIZE,
    BSERR_INVALID_FORMAT,

    BSERR_MERGE_NOT_FIRST,
    BSERR_MERGE_INVALID_PASSWORD,
    BSERR_MERGE_PART_FILE_CORRUPT,

    BSERR_LAST,
};

#define BS_FAILED(ErrCode)  ((Bool)((Long)(ErrCode) < 0))
#define BS_SUCCESS(ErrCode) !BS_FAILED(ErrCode)

enum
{
    BS_IOCP_KEY_READ,
    BS_IOCP_KEY_WRITE,
};

#define BS_FILE_HEADER_MAGIC TAG8('BINS', 'PLIT')
#define BS_INTERNAL_ENCRYPT_KEY L"AmanoTooko"

#pragma pack(1)

#define SPLIT_FLAG_FIRST_FILE       (Int32)0x00000001
#define SPLIT_FLAG_LAST_FILE        (Int32)0x00000002
#define SPLIT_FLAG_COMPRESS         (Int32)0x00000004
#define SPLIT_FLAG_ENCRYPT          (Int32)0x00000008
#define SPLIT_FLAG_SAVE_ORIG_NAME   (Int32)0x00000010

#define MERGE_FLAG_RESTORE_NAME     (Int32)0x00000001

typedef struct
{
    Int64  Magic;
    Int32  Flags;
    UInt32 Index;
    Int64  PartOriginalSize;
    UInt32 DataHash[8];
} BS_PART_FILE_HEADER;

struct BS_PART_FILE_HEADER_FIRST : public BS_PART_FILE_HEADER
{
    UInt32 Parts;
    Int64  FileSize;
    UInt32 PasswordHash[4];
    UInt16 FileNameLength;
    WChar  OriginalFileName[MAX_PATH];
};

typedef struct
{
    Int32 BlockSize;
    Byte  Data[1];
} *PBS_BLOCK_DATA;

typedef struct
{
    UInt16 Length;
    WChar  FileName[1];
} *PPART_FILE_NAME_INFO;

typedef struct
{
    UInt32 Hash[8];
} BS_HASH_TABLE;

#pragma pack()

typedef Bool (STDCALL *FShowStatus)(ULong_Ptr Param, PULarge_Integer pBytesProcessed, PULarge_Integer pFileSize);
typedef Bool (CDECL   *FShowErrorMessage)(ULong_Ptr Param, PCTChar pszFormat, ...);
typedef Bool (CDECL   *FShowAskMessage)(ULong_Ptr Param, PCTChar pszFormat, ...);
typedef Bool (STDCALL *FShowErrMsgByStatus)(ULong_Ptr Param, Long Status, PCTChar pszInfo);

class CModelSplitter;

typedef struct
{
    Bool                fRestoreFileName;
    String              Password;
    String              InputFile;
    String              OutputFile;
    ULong_Ptr           CallbackParam;
    FShowStatus         pfShowStatus;
    FShowErrorMessage   pfShowErrorMessage;
    FShowErrMsgByStatus pfShowStatusMessage;
    FShowAskMessage     pfShowAskMessage;
} MERGE_OPTION;

typedef struct
{
    Int32               Flags;
    String              InputFile;
    String              OutputFile;
    StringW             Password;
    ULong_Ptr           CallbackParam;
    FShowStatus         pfShowStatus;
    FShowErrorMessage   pfShowErrorMessage;
    FShowErrMsgByStatus pfShowStatusMessage;
    FShowAskMessage     pfShowAskMessage;
    CModelSplitter     *This;
} MERGE_WORK_THREAD_INFO;

typedef struct
{
    Bool                fCompress;
    Bool                fEncrypt;
    Bool                fSaveFileName;
    ULarge_Integer      SpliceSizeInByte;
    String              Password;
    String              InputFile;
    String              OutputFile;
    ULong_Ptr           CallbackParam;
    FShowStatus         pfShowStatus;
    FShowErrorMessage   pfShowErrorMessage;
    FShowErrMsgByStatus pfShowStatusMessage;
    FShowAskMessage     pfShowAskMessage;
} SPLIT_OPTION;

typedef struct
{
    Int32               Flags;
    ULarge_Integer      SpliceSizeInByte;
    StringW             Password;
    String              InputFile;
    String              OutputFile;
    ULong_Ptr           CallbackParam;
    FShowStatus         pfShowStatus;
    FShowErrorMessage   pfShowErrorMessage;
    FShowErrMsgByStatus pfShowStatusMessage;
    FShowAskMessage     pfShowAskMessage;
    CModelSplitter     *This;
} SPLIT_WORK_THREAD_INFO;

class CIoRequest : public OVERLAPPED
{
};

class CModelSplitter : public MyWindowClass::CModelBase
{
protected:
    CMem m_mem;

public:
    Long VerifyIsOutputFileExist(PCTChar pszInFile, PTChar pszOutFile, SizeT BufferCount, Int64 SliceSizeInByte);
    Long Split(SPLIT_OPTION *pSplitOption);
    Long Merge(MERGE_OPTION *pMergeOption);
    Long VeirfyIsFirstFile(PCTChar pszFile, PInt32 pFlags);

protected:
    Void  InitKey(aes_encrypt_ctx *aes_context, UInt32 (Key)[8], UInt32 (PwdHash)[4], UInt32 Index, PCWChar pszPassword, SizeT cbSize);
    Void  Encrypt(aes_encrypt_ctx *aes_context, PVoid pvBuffer, SizeT Size, PVoid pvKey);
    Void  Decrypt(aes_encrypt_ctx *aes_context, PVoid pvBuffer, SizeT Size, PVoid pvKey);
    Void  EncryptHeader2(BS_PART_FILE_HEADER *pHeader, UInt32 (PrevPartHash)[8]);
    Void  DecryptHeader2(BS_PART_FILE_HEADER *pHeader, UInt32 (PrevPartHash)[8]);
    Void  EncryptHeader(BS_PART_FILE_HEADER *pHeader, UInt32 Index);
    Void  DecryptHeader(BS_PART_FILE_HEADER *pHeader, UInt32 Index);
    Int   GenerateOutputFileName(PCTChar pszOutFile, PTChar pszBuffer, Int64 Index);

    ULong SplitWorkerNT5(SPLIT_WORK_THREAD_INFO *pInfo);
    ULong SplitWorkerNT6(SPLIT_WORK_THREAD_INFO *pInfo);

    ULong MergeWorkerNT5(MERGE_WORK_THREAD_INFO *pInfo);
    ULong MergeWorkerNT6(MERGE_WORK_THREAD_INFO *pInfo);
    Bool  IsAllPartsExists(MERGE_WORK_THREAD_INFO *pInfo, const BS_PART_FILE_HEADER_FIRST *pHeaderFirst);

    static ULong STDCALL SplitWorkerCallback(SPLIT_WORK_THREAD_INFO *pInfo);
    static ULong STDCALL MergeWorkerCallback(MERGE_WORK_THREAD_INFO *pInfo);
};

#endif /* _MODELSPLITTER_H_ */
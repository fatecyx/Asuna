#ifndef _DAITEIKOKU_H_
#define _DAITEIKOKU_H_

#include "pragma_once.h"
#include "my_headers.h"
#include "gal_common.h"

#pragma pack(1)

/************************************************************************
  UInt24 TableOffset
  UInt24 Offsets[ROUND_UP(sizeof(UInt24) * FileCount, 0x100)] ...
  UInt24 OffsetsValidTable[(FirstFileOffset - TableOffset) / 3] // bool bValid; UInt16 IndexInOffsets
************************************************************************/

/************************************************************************
  ALD
************************************************************************/
typedef struct
{
    UInt24 Offsets[1];
} ALICE_ALD_OFFSET_TABLE;

typedef struct
{
    bool    bValid;
    UInt16  IndexInOffsetTable;
} ALICE_ALD_OFFSET_INDEX;

typedef struct
{
    UInt32 MaxLength;
    UInt32 FileSize;
    UInt64 MaybeHash;
    Char   FileName[1];
} ALICE_ALD_FILE_INFO;

struct MY_ALICE_ALD_ENTRY : public MY_FILE_ENTRY_BASE
{
    UInt32 OriginalIndex;
    UInt32 MaybeHash[2];
};

/************************************************************************
  AFA
************************************************************************/
#define ALICE_AFA_MAGIC         TAG4('AFAH')
#define ALICE_AFA_HEADER_TAG    TAG8('Alic', 'Arch')
#define ALICE_AFA_INDEX_TAG     TAG4('INFO')
#define ALICE_QNT_MAGIC         TAG3('QNT')

typedef struct
{
    UInt32 Magic;
    UInt32 HeaderSize;
    UInt64 Tag;
    UInt32 MustBeTrue;
    UInt32 Flags;
    UInt32 DataOffset;
} ALICE_AFA_HEADER;

typedef struct
{
    UInt32 Tag;
    UInt32 IndexSize;
    UInt32 DecompressSize;
    UInt32 EntryCount;
} ALICE_AFA_INDEX_HEADER;

typedef struct
{
    UInt32 Length;
    UInt32 MaxLength;
    Char   FileName[1];
} *PALICE_AFA_ENTRY_NAME;

typedef struct
{
    UInt32 Unknown;
    UInt32 Hash[2];
    UInt32 Offset;
    UInt32 Size;
} ALICE_AFA_ENTRY_INFO;

struct MY_ALICE_AFA_ENTRY : public MY_FILE_ENTRY_BASE
{
    UInt32 Unknown;
    UInt32 Hash[2];
};

typedef struct            // length always == 0x30
{
    UInt32 unk[2];
    UInt32 Width;
    UInt32 Height;
    UInt32 BitsPerPixel;
    UInt32 unk2;
    UInt32 RGBLength;
    UInt32 AlphaLength;
} ALICE_QNT_INFO_V1;

typedef struct
{
    UInt32 HeaderSize;
    UInt32 unk[2];
    UInt32 Width;
    UInt32 Height;
    UInt32 BitsPerPixel;
    UInt32 unk2;
    UInt32 RGBLength;
    UInt32 AlphaLength;
    Byte   Extra[1];
} ALICE_QNT_INFO_V2;

typedef struct
{
    UInt32 Magic;       // QNT
    UInt32 Version;
    union
    {
        ALICE_QNT_INFO_V1 v1;
        ALICE_QNT_INFO_V2 v2;
    };
} ALICE_QNT_HEADER;

/************************************************************************
  AIN
************************************************************************/
#define ALICE_AIN_MAGIC TAG3('AI2')

typedef struct
{
    UInt32 Magic;   // TAG3('AI2')
    UInt32 AlwaysZero;
    UInt32 DecompressedSize;
    UInt32 CompressedSize;
} ALICE_AIN_HEADER;

/************************************************************************
  ALK
************************************************************************/
#define ALICE_ALK_MAGIC TAG4('ALK0')
typedef struct
{
    UInt32 Magic;
    UInt32 EntryCount;
} ALICE_ALK_HEADER;

typedef struct
{
    UInt32 Offset;
    UInt32 Size;
} ALICE_ALK_ENTRY;

/************************************************************************
  FNL
************************************************************************/
#define ALICE_FNL_MAGIC TAG3('FNA')

typedef struct
{
    UInt32 Magic;
    UInt32 AlwaysZero;
    UInt32 FileSize;
    UInt32 IndexSize;
} ALICE_FNL_HEADER;

typedef struct
{
    UInt32 Loop1;
    UInt32 Loop2;
} ALICE_FNL_INDEX_HEADER;

typedef struct          // Daiteikoku 0x24
{
    UInt16 WidthAndHeight;
    UInt32 Offset;
    UInt32 Size;
} ALICE_FNL_ENTRY;

#pragma pack()

class CDaiteikoku : public CUnpackerImpl<CDaiteikoku>
{
protected:
    CFileDisk m_file;

public:
    Bool Open(PCWChar pszFileName);
    Bool GetFileData(SFileInfo *pFileInfo, const MY_FILE_ENTRY_BASE *pBaseEntry, Bool bConvert = False);

    DEFINE_AUTO_METHOD();

protected:
    Bool InitIndexALD();
    Bool InitIndexAFA();
    Bool InitIndexALK();
    Bool ExtractAIN(PCWChar pszFileName);
    Bool CompressAI2(PCWChar pszFileName);

    Bool DecodeQNT(PVoid pvQNT, SizeT Size, SFileInfo *pFileInfo);
    Bool DecodeQNTV1(ALICE_QNT_INFO_V1 *pHeader, SFileInfo *pFileInfo);
    Bool DecodeQNTV2(ALICE_QNT_INFO_V2 *pHeader, SFileInfo *pFileInfo);
};

#endif // _DAITEIKOKU_H_
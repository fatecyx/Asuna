#ifndef _BGI_H_90470562_fe49_4f23_b4b0_ef97a891700c
#define _BGI_H_90470562_fe49_4f23_b4b0_ef97a891700c

#include "pragma_once.h"
#include <Windows.h>
#include "my_headers.h"
#include "upk_common.h"

#pragma pack(1)

#define BGI_ARC_MAGIC           "PackFile    "
#define BGI_DSC_MAGIC           "DSC FORMAT 1.00"
#define BGI_SDC_MAGIC           "SDC FORMAT 1.00"
#define BGI_BG_MAGIC            "CompressedBG___"
#define BGI_BURIKO_SCRIPT_MAGIC "BurikoCompiledScriptVer1.00"
#define MY_MAGIC                "UCLCompressLE32"
#define BGI_SND_MAGIC           TAG4('bw  ')

/*********************
bp op: ~80
bp 80 func: 172
*********************/

typedef struct
{
    CHAR    Magic[0xC];    // "PackFile    "
    ULONG   FileCount;
} BGI_ARC_HEADER;

typedef struct
{
    CHAR    FileName[0x10];
    ULONG   Offset;
    ULONG   Size;
    ULONG   Unknown1;
    ULONG   DataSize;
} BGI_ARC_ENTRY;

typedef struct
{
    CHAR    Magic[0x10];  // "DSC FORMAT 1.00"
    ULONG   Key;
    ULONG   DecompressSize;
    LONG    DataSize;
    ULONG   Unknown;
    BYTE    Dict[0x200];
} BGI_DSC_FORMAT_HEADER;

typedef struct
{
    CHAR    Magic[0x10];  // "SDC FORMAT 1.00"
    ULONG   Key;
    ULONG   CompressedSize;
    ULONG   DecompressedSize;
    USHORT  CheckSum;
    USHORT  CheckXor;
} BGI_SDC_FORMAT_HEADER;

typedef struct
{
    CHAR    Magic[0x10];  // "CompressedBG___"
    USHORT  Width;
    USHORT  Height;
    USHORT  BitsPerPixel;
    ULONG   Reserve[2];
    ULONG   Unknown;
    ULONG   Key;
    ULONG   CompressedSize;
    BYTE    CheckSum;
    BYTE    CheckXor;
    USHORT  _Pad;
} BGI_COMPRESSED_BG_HEADER;

typedef struct
{
    BOOL    bUnknown;
    ULONG   NodeIndex;
    ULONG   Index[2];
} BGI_DSC_FORMAT_TREE_NODE;

typedef struct
{
    USHORT Width;
    USHORT Height;
    USHORT BitsPerPixel;
    USHORT Unknown;
    USHORT BppIndex;
    USHORT Unknown2;
    USHORT Unknown3;
    USHORT Unknown4;
} BGI_GRP_HEADER;

typedef struct
{
    ULONG cbSize;
    ULONG Magic;            // == TAG4('bw  ')
    ULONG AudioSteamSize;
    ULONG Samples;
    ULONG Rate;
    ULONG Channels;
    BYTE  Unknown1[0x18];
    ULONG State;
    BYTE  Unknown2[0xC];
} BGI_SOUND_HEADER;

/************************************************************************
  crass
************************************************************************/

typedef struct {
    unsigned int valid;				/* 是否有效的标记 */
    unsigned int weight;			/* 权值 */
    unsigned int is_parent;			/* 是否是父节点 */
    unsigned int parent_index;		/* 父节点索引 */
    unsigned int left_child_index;	/* 左子节点索引 */
    unsigned int right_child_index;	/* 右子节点索引 */
} bg_huffman_node;

typedef struct {
    s8 magic[16];			/* "CompressedBG___" */
    u16 width;
    u16 height;
    u32 color_depth;
    u32 reserved0[2];
    u32 zero_comprlen;		/* huffman解压后的0值字节压缩的数据长度 */
    u32 key;				/* 解密叶节点权值段用key */
    u32 encode_length;		/* 加密了的叶节点权值段的长度 */
    u8 sum_check;
    u8 xor_check;
    u16 reserved1;
} bg_header_t;

#pragma pack()

#pragma pack(4)

struct bits {
    unsigned long curbits;
    unsigned long curbyte;
    unsigned char cache;
    unsigned char *stream;
    unsigned long stream_length;
};

#pragma pack()

class CBGIUnpacker : public CUnpackerImpl<CBGIUnpacker>
{
protected:
    CFileDisk m_file;

public:
    BOOL  Open(PCWCHAR pszFileName);
    BOOL  GetFileData(UNPACKER_FILE_INFO *pFileInfo, const MY_FILE_ENTRY_BASE *pBaseEntry, BOOL SaveRawData = FALSE);
    ULONG Pack(PCWChar pszPath);

protected:
    ULONG   UpdateKey(ULONG &OldKey);
    VOID    InitTree(BGI_DSC_FORMAT_TREE_NODE *pDict, PVOID pvDscBuffer);
    ULONG   DecompressBG(PVOID pvCompressed, ULONG CompressedSize, PVOID *pvDecompressed);
    ULONG   DecompressDSC(PVOID pvCompressed, ULONG CompressedSize, PVOID *pvDecompressed);

    ULONG   DecompressSDC(PVOID pvCompressed, ULONG CompressedSize, PVOID *pvDecompressed);
    BOOL    DecryptSDC(BGI_SDC_FORMAT_HEADER *pSdc, PVOID pvDecryptBuffer);

    static ULONG FASTCALL UCL_NRV2E_DecompressASMFast32(PVOID pvInput, PVOID pvOutput);

    // crass
    void
    decode_bg(
        unsigned char *enc_buf,
        unsigned int enc_buf_len,
        unsigned int key,
        unsigned char *ret_sum,
        unsigned char *ret_xor
    );

    unsigned int bg_create_huffman_tree(bg_huffman_node *nodes, u32 *leaf_nodes_weight);

    ULONG
    bg_huffman_decompress(
        bg_huffman_node *huffman_nodes,
        unsigned int root_node_index,
        unsigned char *uncompr,
        unsigned int uncomprlen,
        unsigned char *compr,
        unsigned int comprlen
    );

    ULONG
    zero_decompress(
        unsigned char *uncompr,
        unsigned int uncomprlen,
        unsigned char *compr,
        unsigned int comprlen
    );

    void
    bg_average_defilting(
        unsigned char *dib_buf,
        unsigned int width,
        unsigned int height,
        unsigned int bpp
    );

    ULONG
    bg_decompress(
        bg_header_t *bg_header,
        unsigned int bg_len,
        unsigned char *image_buf,
        unsigned int image_size
    );
};

#endif // _BGI_H_90470562_fe49_4f23_b4b0_ef97a891700c

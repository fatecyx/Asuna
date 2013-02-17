#ifndef _MAGUSTALE_H_
#define _MAGUSTALE_H_

#include <Windows.h>
#include "my_headers.h"
#include "gal_common.h"

#pragma pack(1)

#define YURIS_YPF_HEADER_OVERHEAD   0x10
#define YURIS_YPF_MAGIC             TAG3('YPF')
#define YURIS_YBN_MAGIC             TAG4('YSTB')
#define YURIS_YPF_EXTENSION         L".ypf"

typedef struct
{
    UInt32 Magic;
    UInt32 Version; // ??
    UInt32 FileCount;
    UInt32 EntrySize;
} YURIS_YPF_HEADER;

typedef struct
{
    Byte len;
    Char name[1];
} SPacFileHeader;

typedef struct
{
    BYTE   FileType;    // ?
    bool   bComp;
    UInt32 decompsize;
    UInt32 compsize;
    UInt32 offset;
    UInt32 hash;
} YURIS_YPF_FILE_INFO;
/*
typedef struct
{
    Bool   bEncrypt;    // ?
    Bool   bCompress;
    UInt32 uDecompSize;
    UInt32 uCompSize;
    UInt32 uOffset;
    UInt32 uHash1;
    UInt32 uHash2;
    WChar  szFileName[MAX_PATH];
} SMyPacFileInfo;
*/
struct YURIS_YPF_ENTRY : public MY_FILE_ENTRY_BASE
{
    UInt32 Hash1;
    UInt32 FileHash;
    UInt32 FileType;
};

typedef struct
{
    UInt32 version;
    UInt32 uCount;
    YURIS_YPF_ENTRY *pIndex;
} SMyPacEntry;
/*
typedef struct
{
    PByte data;
    UInt32 size;
} SFileInfo;
*/
#pragma pack()

class CYuris : public CUnpackerImpl<CYuris>
{
public:
    Bool    Open(PCWChar szFileName);
    Bool    GetFileData(SFileInfo *pFileInfo, const MY_FILE_ENTRY_BASE *pEntry);
    SizeT   Pack(PCWChar pszPath);

protected:
    Bool    InitIndex(PByte pbBuffer, UInt32 uSize, const YURIS_YPF_HEADER *pHeader);
    Void    DecryptFileName(PByte pbBuffer, UInt32 uSize, Byte Key);
    PWChar  GetExtensionByFileType(UInt32 FileType);
    HRESULT EncryptScript(PVOID pvBuffer, ULONG BufferSize, ULONG Version);

    ULONG   GetYpfFileType(PWChar pszFileName);
    ULONG   CalcYpfIndexSize(YURIS_YPF_ENTRY *pFileList, LARGE_INTEGER FileCount);

    ULONG
    GenerateYpfIndex(
        YURIS_YPF_ENTRY *pFileList,
        LARGE_INTEGER    FileCount,
        PVOID            pvPacIndexBuffer,
        ULONG            BufferSize
    );

    static int CDECL compare(YURIS_YPF_ENTRY *p1, YURIS_YPF_ENTRY *p2);
    static UInt32 HashFileName(LPVoid lpFileName, Int32 Length);

protected:
    CMem m;
    CFileDisk f;
    UInt32 m_YpfVersion;
//    SMyPacEntry m_entry;
    static const Byte LengthTable_107[256];
    static const Byte LengthTable_122[256];
    static const Byte LengthTable_1C2[256];
    static const UInt32 HashTable[256];
};

#endif /* _MAGUSTALE_H_ */
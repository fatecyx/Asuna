#ifndef _CG_PLUGIN_H_c7e5034e_bd98_457a_8c98_4936ce220ea1
#define _CG_PLUGIN_H_c7e5034e_bd98_457a_8c98_4936ce220ea1

#include "pragma_once.h"
#include "CG_Types.h"
#include "CG_Memory.h"
#include "CG_FileIO.h"
#include "CG_Core.h"

enum ExtractFileType
{
    CG_FILE_TYPE_UNKNOWN,
    CG_FILE_TYPE_IMAGE,
    CG_FILE_TYPE_AUDIO,
    CG_FILE_TYPE_TEXT,
    CG_FILE_TYPE_BINARY,
    CG_FILE_TYPE_PACKAGE,
};

#define CG_PLUGIN_FLAG_AUTO_FREE 0x00000001

#pragma pack(1)

typedef struct
{
    ULONG   Type;
    ULONG   Caps;
    LPCWSTR PluginName;
    LPCWSTR Author;
    LPCWSTR Version;
    LPCWSTR Date;
    LPCWSTR SystemName;
    LPCWSTR Extension;
    union
    {
        DECL_ALIGN(1) struct
        {
            BYTE SupportMemoryFile : 1;
        };
        ULONG Flags;
    } Capability;
} CG_PLUGIN_INFO;


#define CG_ENTRY_FLAG_COMPRESSED 0x00000001
#define CG_ENTRY_FLAG_ENCRYPTED  0x00000002

struct CG_FILE_ENTRY_BASE
{
    ULONG         Flags;
    LARGE_INTEGER Offset;
    LARGE_INTEGER CompressedSize;
    LARGE_INTEGER Size;
    WCHAR         FileName[MAX_PATH];
};

struct CG_FILE_INDEX_BASE
{
    LARGE_INTEGER       FileCount;
    LARGE_INTEGER       cbEntrySize;
    MY_FILE_ENTRY_BASE *pEntry;
};

typedef struct
{
    PBYTE           Buffer;
    LARGE_INTEGER   BufferSize;
} CG_BINARY_DATA;

typedef struct
{
    PBYTE           Buffer;
    LARGE_INTEGER   BufferSize;
    LONG            Width;
    LONG            Heigth;
    LONG            BitsPerPixel;
} CG_IMAGE_DATA;

struct CG_UNPACK_DATA_INFO
{
    ULONG           FileType;
    LARGE_INTEGER   FileCount;
    PVOID           pExtraData;
    LARGE_INTEGER   ExtraSize;
    union
    {
        UNPACKER_BINARY_DATA  BinaryData;
        UNPACKER_IMAGE_DATA   ImageData;
        UNPACKER_IMAGE_DATA  *pImageData;
    };

    UNICODE_STRING  Description;

#define InitializeDataInfo(info) \
            (info)->pExtraData                  = NULL; \
            (info)->BinaryData.pbBuffer         = NULL; \
            (info)->ImageData.pbBuffer          = NULL; \
            (info)->pImageData                  = NULL; \
            (info)->FileCount.QuadPart          = 1; \
            (info)->Description.Length          = 0; \
            (info)->Description.MaximumLength   = 0; \
            (info)->Description.Buffer          = NULL
};

struct CG_OPEN_FILE_INFO
{
    ULONG                   FileType;
    LARGE_INTEGER           FileSize;
    PVOID                   Context;
    ULONG                   Flags;
    CG_FILE_INDEX_BASE     *Index;
};

typedef struct
{
    PVOID           PluginContext;
    PVOID           ExtraData;
    LARGE_INTEGER   ExtraDataSize;
    PVOID           ExtraParameter;
    LARGE_INTEGER   ExtraParameterSize;

    union
    {
        struct
        {
            PWCHAR          FileName;
            UNICODE_STRING  FullPath;
        } FileInfo;

        struct
        {
            CG_UNPACK_DATA_INFO UnpackInfo;

            union
            {
                CG_FILE_ENTRY_BASE *pEntry;
                struct
                {
                    PVOID           MemoryBuffer;
                    LARGE_INTEGER   InputSize;
                };
            };

            DECL_ALIGN(1) struct
            {
                BYTE KeepRawFormat      : 1;
                BYTE MemoryFile         : 1;
            } Options;

        } FileData;

        struct
        {
            UNICODE_STRING FullInputPath;
            UNICODE_STRING FullOutputPath;
        } Extract;
        
        struct
        {
            UNICODE_STRING PathToPackage;
        } Package;

        struct
        {
            PVOID PluginContext;
        } ReleaseResource;

    } Parameters;

    struct
    {
        ICGCoreBase     *Core;
        ICGFileIoBase   *File;
        ICGMemoryBase   *Memory;
//        ICGUIBase       *UI;
    } Interface;

} CG_IRP, *PCG_IRP;

#pragma pack()


CG_INTERFACE_(ICGPlugin, ICGUnknown)
{
    CG_METHOD(QueryInterface)       (THIS_ REFIID iid, PVOID *ppvObject) PURE;
    CG_METHOD_TYPE(ULONG, AddRef)   (THIS) PURE;
    CG_METHOD_TYPE(ULONG, Release)  (THIS) PURE;

    CG_METHOD(GetPluginInfo)    (THIS_ OUT CG_PLUGIN_INFO *PluginInfo) PURE;
    CG_METHOD(GetFileInfo)      (THIS_ IN PCG_IRP Irp, OUT CG_OPEN_FILE_INFO *FileInfo) PURE;
    CG_METHOD(GetFileData)      (THIS_ IN PCG_IRP Irp, OUT CG_UNPACK_DATA_INFO *pUnpackInfo) PURE;
    CG_METHOD(SetFileData)      (THIS_ IN PCG_IRP Irp, IN  CG_UNPACK_DATA_INFO *pFileName) PURE;
    CG_METHOD(Package)          (THIS) PURE;    // reserve
    CG_METHOD(FreeFileData)     (THIS_ IN PCG_IRP Irp) PURE;
    CG_METHOD(ExtractFile)      (THIS_ IN PCG_IRP Irp) PURE;
    CG_METHOD(ReleaseAll)       (THIS_ IN PCG_IRP Irp) PURE;
};

#endif // _CG_PLUGIN_H_c7e5034e_bd98_457a_8c98_4936ce220ea1

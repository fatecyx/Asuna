#ifndef _KRKR2_H_ea198a88_e7cb_4be4_aefd_74de9efb3f65
#define _KRKR2_H_ea198a88_e7cb_4be4_aefd_74de9efb3f65

#include "pragma_once.h"
#include "my_headers.h"

enum
{
    DLL_INIT_HOOKS  = -1,
};

#pragma pack(1)

typedef struct
{
    PVOID OriginalBase;
    PVOID MappedBase;
    ULONG SizeOfImage;
    PCSTR ModuleName;
} MODULE_MAP_ENTRY;

typedef struct
{
    ULONG Count;
    MODULE_MAP_ENTRY *Entry;
} MODULE_MAP;

#define THREAD_START_PARAMETER_MAGIC  TAG4('TSPM')

struct THREAD_START_PARAMETER : public RTL_THREAD_FRAME
{
    PVOID ThreadStartRoutine;
    PVOID Parameter;

    THREAD_START_PARAMETER()
    {
        Context = THREAD_START_PARAMETER_MAGIC;
    }
};

typedef struct
{
    LARGE_INTEGER   DataOffset;
    LARGE_INTEGER   Unknown;
    LARGE_INTEGER   OriginalSize;
    LARGE_INTEGER   CompressedSize;

    DUMMY_STRUCT(0x1C);

} TJSBINSTREAM_SEGM_INFO;

typedef struct
{
    PVOID   VirtualTable;
    HANDLE  FileHandle;
} MEMORY_STREAM;

typedef struct
{
    MEMORY_STREAM  *StreamInfo;         // 0x10
    LARGE_INTEGER   FileSize;           // 0x14
    PVOID           Unknown1;           // 0x1C
    TJSBINSTREAM_SEGM_INFO *SegmentInfo;// 0x20
    ULONG           Unknown2;           // 0x1C
    LARGE_INTEGER   Offset;             // 0x28
    LARGE_INTEGER   FileBufferSize;     // 0x30
    LARGE_INTEGER   FileBufferOffset;   // 0x38
    PVOID           FileBuffer;         // 0x40
} TJSBINSTREAM_FILE_INFO;

DECLARE_INTERFACE(IKrkr2TJSBinaryStream)
{
    STDMETHODV_(ULONG64, Seek)           (LONG64 Offset, LONG MoveMethod)    PURE;
    STDMETHODV_(ULONG, Read)             (PVOID Buffer, ULONG Size)          PURE;
    STDMETHODV_(ULONG, Write)            (PVOID Buffer, ULONG Size)          PURE;
    STDMETHODV_(VOID, SetEndOfStorage)()                                     PURE;
    STDMETHODV_(ULONG64, GetSize)()                                          PURE;

    DUMMY_STRUCT(0xC);

    union
    {
        TJSBINSTREAM_FILE_INFO m_FileInfo;

#pragma warning(push, 0)
        struct
        {
            PVOID           m_StreamInfo;       // 0x10
            LARGE_INTEGER   m_FileSize;         // 0x14
            PVOID           m_Unknown[3];       // 0x1C
            LARGE_INTEGER   m_Offset;           // 0x28
            LARGE_INTEGER   m_FileBufferSize;   // 0x30
            LARGE_INTEGER   m_FileBufferOffset; // 0x38
            PVOID           m_FileBuffer;       // 0x40
        };
#pragma warning(pop)

    };
};

typedef ULONG (CDECL *Krkr2TJSBinaryStreamReadRoutine)(IKrkr2TJSBinaryStream *Stream, PVOID Buffer, ULONG Size);

typedef struct
{
    PVOID ReturnAddress;
    PVOID BaseAddress;
    ULONG Reason;
    PVOID Reserved;
} DLL_MAIN_PARAMETERS;

struct Krkr2String
{
    ULONG   RefCount;
    PWSTR   Buffer;
    WCHAR   String[1];

    PWSTR GetBuffer()
    {
        return Buffer == NULL ? String : Buffer;
    }
};

typedef struct
{
    ULONG           SizeOfSelf;      // structure size of tTVPXP3ExtractionFilterInfo itself
    LARGE_INTEGER   Offset;          // offset of the buffer data in uncompressed stream position
    PVOID           Buffer;          // target data buffer
    ULONG           BufferSize;      // buffer size in bytes pointed by "Buffer"
    ULONG           FileHash;        // hash value of the file (since inteface v2)
} XP3_EXTRACTION_INFO;

#pragma pack()

typedef BOOL (WINAPI *DllMainRoutine)(HINSTANCE hInstance, ULONG Reason, PVOID Reserved);

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, PVOID Reserved);
BOOL WINAPI TrueDllEntry(HINSTANCE hInstance, ULONG Reason, PVOID Reserved);
NTSTATUS HookModuleIAT(MODULE_MAP *ModuleMap, PVOID ModuleToRedirect);

#endif // _KRKR2_H_ea198a88_e7cb_4be4_aefd_74de9efb3f65

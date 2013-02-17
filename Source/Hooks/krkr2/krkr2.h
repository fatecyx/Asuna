#ifndef _KRKR2_H_4010a8e6_2e32_46df_8ebe_dd6d2a664ef9_
#define _KRKR2_H_4010a8e6_2e32_46df_8ebe_dd6d2a664ef9_

#include "MyLibraryUser.h"

#define SC_XP3_SUFFIX       L"_sc.xp3"

#if MAHOYO

#define DATA_XP3_FILE_NAME  L"mahoyo.xp3"

#elif TENSHIN

#define DATA_XP3_FILE_NAME  L"tenshin_sc.xp3"

#endif // DATA_XP3_FILE_NAME

/************************************************************************
  krkr2 base type
************************************************************************/

#pragma pack(1)

typedef struct
{
    ULONG           SizeOfSelf;      // structure size of tTVPXP3ExtractionFilterInfo itself
    LARGE_INTEGER   Offset;          // offset of the buffer data in uncompressed stream position
    PVOID           Buffer;          // target data buffer
    ULONG           BufferSize;      // buffer size in bytes pointed by "Buffer"
    ULONG           FileHash;        // hash value of the file (since inteface v2)
} XP3_EXTRACTION_INFO, *PXP3_EXTRACTION_INFO;

typedef struct
{
    ULONG RefCount;
    PWSTR Buffer;
    WCHAR String[1];

} *PSttstr;

//---------------------------------------------------------------------------
// iTVPFunctionExporter, exporting main module's functions
//---------------------------------------------------------------------------
interface ITVPFunctionExporter
{
    STDMETHODV_(BOOLEAN, QueryFunctions)(
        PWSTR *FunctionName,
        PVOID *Function,
        ULONG  FunctionCount
    ) PURE;

    STDMETHODV_(BOOLEAN, QueryFunctionsByNarrowString)(
        PSTR  *FunctionName,
        PVOID *Function,
        ULONG  FunctionCount
    ) PURE;
};

typedef
VOID
(STDCALL
*TVP_XP3_EXCTRACTION_FILTER)(
    IN PXP3_EXTRACTION_INFO Info
);

DECLARE_INTERFACE_(ITSSStorageProvider, IUnknown)
{
    STDMETHOD(GetStreamForRead)(
        IN  PWSTR     Url,
        OUT IUnknown**Stream
    ) PURE;

    STDMETHOD(GetStreamForWrite)(
        IN  PWSTR     Url,
        OUT IUnknown**Stream
    ) PURE;

    STDMETHOD(GetStreamForUpdate)(
        IN  PWSTR     Url,
        OUT IUnknown**Stream
    ) PURE;
};

DECLARE_INTERFACE_(ITSSMediaBaseInfo, IUnknown)
{
    STDMETHOD(GetMediaType)(
        IN PWSTR ShortName,
        IN PWSTR Description,
        IN ULONG DescriptionLength
    ) PURE;

    STDMETHOD(GetLength)(
        OUT PULONG Length
    ) PURE;

    STDMETHOD(GetTitle)(
        IN PWSTR Buffer,
        IN ULONG BufferSize
    ) PURE;

    STDMETHOD(GetCopyright)(
        IN PWSTR Buffer,
        IN ULONG BufferSize
    ) PURE;

    STDMETHOD(GetComment)(
        IN PWSTR Buffer,
        IN ULONG BufferSize
    ) PURE;

    STDMETHOD(GetArtist)(
        IN PWSTR Buffer,
        IN ULONG BufferSize
    ) PURE;
};

DECLARE_INTERFACE_(ITSSModule, IUnknown)
{
    STDMETHOD(GetModuleCopyright)(
        IN PWSTR Buffer,
        IN ULONG BufferSize
    ) PURE;

    STDMETHOD(GetModuleDescription)(
        IN PWSTR Buffer,
        IN ULONG BufferSize
    ) PURE;

    STDMETHOD(GetSupportExts)(
        IN ULONG Index,
        IN PWSTR MediaShortName,
        IN PWSTR Buffer,
        IN ULONG BufferSize
    ) PURE;

    STDMETHOD(GetMediaInfo)(
        IN  PWSTR              Url,
        OUT ITSSMediaBaseInfo**Info
    ) PURE;

    STDMETHOD(GetMediaSupport)(
        IN  PWSTR Url
    ) PURE;

    STDMETHOD(GetMediaInstance)(
        IN  PWSTR     Url,
        OUT IUnknown**Instance
    ) PURE;
};

typedef struct
{
    ULONG   SamplesPerSec;
    ULONG   Channels;
    ULONG   BitsPerSample;
    ULONG   Seekable;
    ULONG64 TotalSamples;
    ULONG   TotalTime;
    ULONG   Reserved1;
    ULONG   Reserved2;

} TSSWaveFormat;

DECLARE_INTERFACE_(ITSSWaveDecoder, IUnknown)
{
    STDMETHOD(GetFormat)(
        TSSWaveFormat *format
    ) PURE;

    STDMETHOD(Render)(
        IN  PVOID   Buffer,
        IN  ULONG   BufferSampleLength,
        OUT PULONG  Rendered,
        OUT PULONG  Status
    ) PURE;

    STDMETHOD(SetPosition)(
        IN  ULONG64 SamplepPosition
    ) PURE;
};

#pragma pack()

/************************************************************************
  main module
************************************************************************/
VOID LoadTpmPlugin();

TYPE_OF(NtQueryDirectoryFile)       HookNtQueryDirectoryFile;
TYPE_OF(NtQueryAttributesFile)      HookNtQueryAttributesFile;
TYPE_OF(NtCreateFile)               HookNtCreateFile;
TYPE_OF(LdrLoadDll)                 HookLdrLoadDll;
TYPE_OF(CreateFontIndirectExW)      HookCreateFontIndirectExW;
TYPE_OF(GetGlyphOutlineW)           HookGetGlyphOutlineW;

extern TYPE_OF(NtQueryDirectoryFile)        *StubNtQueryDirectoryFile;
extern TYPE_OF(NtQueryAttributesFile)       *StubNtQueryAttributesFile;
extern TYPE_OF(NtCreateFile)                *StubNtCreateFile;
extern TYPE_OF(LdrLoadDll)                  *StubLdrLoadDll;
extern TYPE_OF(HookCreateFontIndirectExW)   *StubCreateFontIndirectExW;
extern TYPE_OF(GetGlyphOutlineW)            *StubGetGlyphOutlineW;

/************************************************************************
  hook
************************************************************************/
BOOL    InitializeHook(PVOID BaseAddress);
PVOID   FindTVPGetPlacedPath(ITVPFunctionExporter *Exporter);

/************************************************************************
  extension
************************************************************************/
LONG STDCALL GetPluginInfo(LONG InfoIndex, PSTR Buffer, LONG BufferLength);

#endif // _KRKR2_H_4010a8e6_2e32_46df_8ebe_dd6d2a664ef9_

#ifndef _REALSISTER_H_
#define _REALSISTER_H_

#if defined(__INTEL_COMPILER)
    #pragma warning(disable:1090)
#endif

#include <Windows.h>
#include "my_headers.h"
#include "krkr2/tjs2/tjsCommHead.h"
//#include "krkr2/core/base/PluginImpl.h"
//#include "krkr2/core/base/XP3Archive.h"
#include "krkr2/core/visual/GraphicsLoaderIntf.h"

#pragma pack(1)

typedef struct
{
    ULONG           SizeOfSelf;      // structure size of tTVPXP3ExtractionFilterInfo itself
    LARGE_INTEGER   Offset;          // offset of the buffer data in uncompressed stream position
    PVOID           Buffer;          // target data buffer
    ULONG           BufferSize;      // buffer size in bytes pointed by "Buffer"
    ULONG           FileHash;        // hash value of the file (since inteface v2)
} XP3_EXTRACTION_INFO;

typedef struct
{
    Int RefCount;
    PWChar pszBuffer;
    WChar szString[1];
} *PSttstr;

typedef struct
{
    PSttstr pStrExtention;
    PVOID  handler;
	void *  FormatData;
} SGraphicHandler;

typedef struct
{
    ULONG           MaxSize;
    SGraphicHandler *pBegin;
    SGraphicHandler *pEnd;
} SGraphicHandlerVector;

typedef struct
{
    ULONG unknown[4];
    UInt16 word;
    UInt16 unknown2;
    ULONG unknown3;
    ULONG unknown4;
} SUnknownAtGraphicHandler;

interface iTVPFunctionExporter
{
    virtual bool TJS_INTF_METHOD QueryFunctions(const tjs_char **name, void **function, tjs_uint count) = 0;
    virtual bool TJS_INTF_METHOD QueryFunctionsByNarrowString(const char **name, void **function, tjs_uint count) = 0;
};

typedef Void    (STDCALL *tTVPXP3ArchiveExtractionFilter)(XP3_EXTRACTION_INFO *info);
typedef Void    (STDCALL *F_TVPSetXP3ArchiveExtractionFilter)(tTVPXP3ArchiveExtractionFilter);
//typedef PSttstr (STDCALL *F_GameNewttstr)(PCWChar pszString);
typedef Void    (STDCALL *F_TVPBLConvert24BitTo8Bit)(tjs_uint8 * dest , const tjs_uint8 * buf , tjs_int len);
typedef Void    (STDCALL *F_TVPBLConvert24BitTo32Bit)(tjs_uint32 * dest , const tjs_uint8 * buf , tjs_int len);
typedef Void    (STDCALL *F_TVPBLConvert32BitTo8Bit)(tjs_uint8 * dest , const tjs_uint32 * buf , tjs_int len);
typedef Void    (STDCALL *F_TVPBLConvert32BitTo32Bit_NoneAlpha)(tjs_uint8 * dest , const tjs_uint32 * buf , tjs_int len);
typedef Void    (STDCALL *F_TVPBLConvert32BitTo32Bit_MulAddAlpha)(tjs_uint8 * dest , const tjs_uint32 * buf , tjs_int len);
typedef Void    (STDCALL *F_TVPBLConvert32BitTo32Bit_AddAlpha)(tjs_uint8 * dest , const tjs_uint32 * buf , tjs_int len);
typedef Void    (STDCALL *F_tTJSStringConstructionFromConstChar)(tTJSString_S *, PCChar);

#pragma pack()

EXTC Void STDCALL XP3ArchiveAttractFilter_v2(ULONG hash, LARGE_INTEGER offset, PVOID buffer, Long bufferlen);
BOOL STDCALL Decrypt(const XP3_EXTRACTION_INFO *Info);
EXTC HRESULT STDCALL V2Link(iTVPFunctionExporter *exporter);
EXTC HRESULT STDCALL V2Unlink();
HFONT WINAPI MyCreateFontIndirectA(LOGFONTA *lplf);

// game functions

PVOID WINAPI ScanLineCallback(PVOID scanlinecallback, PVOID callbackdata, Int y);
Void   WINAPI SizeCallback(PVOID sizecallback, PVOID callbackdata, Int32 w, Int32 h);
Void   WINAPI MetaInfoPushCallback(PVOID metainfopushcallback, PVOID callbackdata, 
                                   const tTJSString_S &name, const tTJSString_S &value);

UInt64 WINAPI GetSize(tTJSBinaryStream *src);
UInt64 WINAPI GetPosition(tTJSBinaryStream *src);
Void   WINAPI SetPosition(tTJSBinaryStream *src, tjs_uint64 pos);   // always from begin
Void   WINAPI ReadBuffer(tTJSBinaryStream *src, PVOID buffer, tjs_uint read_size);

// hooks

PSttstr WINAPI GameNewttstr(PCWChar pszString);
PSttstr WINAPI Newttstr();
Void    WINAPI AddGraphicHandler(SGraphicHandlerVector *pVector, SUnknownAtGraphicHandler *pUnknown);
Void
WINAPI
LoadUCI(
    tTVPGraphicLoadMode mode,
    tjs_int32 keyidx,
    tTJSBinaryStream *src,
#if !defined(FATE_STAY_NIGHT)
    tTVPMetaInfoPushCallback metainfopushcallback,
#endif
    tTVPGraphicScanLineCallback scanlinecallback
);

#endif /* _REALSISTER_H_ */
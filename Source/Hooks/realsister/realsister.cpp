#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.CRT=.text /MERGE:.data1=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano /MERGE:.data=.Amano")
#pragma warning(disable:4530)
#pragma comment(lib, "delayimp.lib")
#pragma comment(lib, "msvcrt.lib")

#if defined(MY_DEBUG)
#pragma comment(linker,"/ENTRY:DllMain")
#endif

// ttstr ::TVPGetPlacedPath(const ttstr &)

#if defined(REAL_SISTER)

#define SUPPORT_AAC_DECODE
#define USE_DECYPT_FUNCTION
#define USE_CXDEC

#define FUNC_GAME_NEW_TTSTR 0x408C54
#define FUNC_GET_SIZE       0x43860C
#define FUNC_GET_POS        0x438654
#define FUNC_SET_POS        0x438664
#define FUNC_READ_BUFFER    0x4386A4

#define pGraphicHandlerVector 0x7273E0

#elif defined(FATE_STAY_NIGHT)

#define SUPPORT_AAC_DECODE
#define USE_DECYPT_FUNCTION
#define TJS_INTF_METHOD STDCALL

#define FUNC_GAME_NEW_TTSTR 0x4082F8
#define FUNC_GET_SIZE       0x433038
#define FUNC_GET_POS        0x43307C
#define FUNC_SET_POS        0x433088
#define FUNC_READ_BUFFER    0x4330C4

#define pGraphicHandlerVector 0x69D43C

#elif defined(FATE_HA)

#define SUPPORT_AAC_DECODE
#define USE_DECYPT_FUNCTION
#define USE_CXDEC

#define FUNC_GAME_NEW_TTSTR 0x408A98
#define FUNC_GET_SIZE       0x45360C
#define FUNC_GET_POS        0x453654
#define FUNC_SET_POS        0x453664
#define FUNC_READ_BUFFER    0x4536A4

#define pGraphicHandlerVector 0x6F8B8C

#elif defined(GSTRING)

#define SUPPORT_AAC_DECODE

#define FUNC_GAME_NEW_TTSTR 0x408C54
#define FUNC_GET_SIZE       0x43B8BC
#define FUNC_GET_POS        0x43B904
#define FUNC_SET_POS        0x43B914
#define FUNC_READ_BUFFER    0x43B954

#define pGraphicHandlerVector 0x729DA8

#elif defined(NATSU_ZORA)

#define USE_DECYPT_FUNCTION
#define USE_CXDEC

#define FUNC_GAME_NEW_TTSTR 0x408C54
#define FUNC_GET_SIZE       0x438820
#define FUNC_GET_POS        0x438868
#define FUNC_SET_POS        0x438878
#define FUNC_READ_BUFFER    0x4388B8

#define pGraphicHandlerVector 0x727C20

#elif defined(TENSHIN)

#define USE_DECYPT_FUNCTION
#define USE_CXDEC

#define FUNC_GAME_NEW_TTSTR 0x408C54
#define FUNC_GET_SIZE       0x438858
#define FUNC_GET_POS        0x4388A0
#define FUNC_SET_POS        0x4388B0
#define FUNC_READ_BUFFER    0x4388F0

#define pGraphicHandlerVector 0x726238

#endif

#include "realsister.h"
#include <delayimp.h>
#include "Mem.cpp"
#include "AACWaveDecoder.h"
#include "AACWaveDecoder.cpp"

#if defined(USE_CXDEC)

#include "cxdec.h"
#include "cxdec.cpp"

CCxdec *g_cxdec;

#endif

OVERLOAD_CPP_NEW_WITH_HEAP(CMem::GetGlobalHeap())

static union
{
    PVOID lpFunction[8];
    struct
    {
        F_TVPSetXP3ArchiveExtractionFilter     TVPSetXP3ArchiveExtractionFilter;
        F_TVPBLConvert24BitTo8Bit              TVPBLConvert24BitTo8Bit;
        F_TVPBLConvert24BitTo32Bit             TVPBLConvert24BitTo32Bit;
        F_TVPBLConvert32BitTo8Bit              TVPBLConvert32BitTo8Bit;
        F_TVPBLConvert32BitTo32Bit_NoneAlpha   TVPBLConvert32BitTo32Bit_NoneAlpha;
        F_TVPBLConvert32BitTo32Bit_MulAddAlpha TVPBLConvert32BitTo32Bit_MulAddAlpha;
        F_TVPBLConvert32BitTo32Bit_AddAlpha    TVPBLConvert32BitTo32Bit_AddAlpha;
        F_tTJSStringConstructionFromConstChar  tTJSStringConstructionFromConstChar;
    };
};

NoInline BOOL InitMetaInfo(PVOID lpMeta, Int32 MetaSize, tTVPMetaInfoPushCallback metainfopushcallback, PVOID callbackdata)
{
    PByte pbMeta, pbMetaEnd;
    ULONG chunksize, chunkname;

    if (metainfopushcallback == NULL)
        return False;

    pbMeta = (PByte)_alloca(MetaSize + 1);
    memcpy(pbMeta, lpMeta, MetaSize);
    pbMeta[MetaSize] = 0;

    pbMetaEnd = pbMeta + MetaSize - 4;
    while (pbMeta < pbMetaEnd)
    {
        chunkname = *(PUInt32)pbMeta;
        pbMeta += 4;

        chunksize = *(PUInt32)pbMeta;
        pbMeta += 4;

        if (chunkname == TAG4('tags'))
        {
            // tag information
            PChar pTag, pName, pValue, tagp, tagp_lim;
//            UInt32 namelen;

            pTag = (PChar)pbMeta;

            tagp = pTag;
            tagp_lim = pTag + chunksize;
            pbMeta += chunksize;
            while(tagp < tagp_lim)
            {
                ULONG namelen = 0;

                while(*tagp >= '0' && *tagp <= '9')
                    namelen = namelen * 10 + *tagp++ - '0';

                RETURN_IF(*tagp != ':', False);

                ++tagp;
                pName = tagp;
                tagp += namelen;
                RETURN_IF(*tagp != '=', False);
                pName[namelen] = 0;

                ULONG valuelen = 0;

                tagp++;
                while(*tagp >= '0' && *tagp <= '9')
                    valuelen = valuelen * 10 + *tagp++ - '0';

                RETURN_IF(*tagp != ':', False);

                tagp++;
                pValue = tagp;
                tagp += valuelen;
                RETURN_IF(*tagp != ',', False);
                pValue[valuelen] = 0;

                tagp++;

                tTJSString_S strname, strval;
                // insert into name-value pairs ... TODO: utf-8 decode
                tTJSStringConstructionFromConstChar(&strname, pName);
                tTJSStringConstructionFromConstChar(&strval, pValue);
                MetaInfoPushCallback(metainfopushcallback, callbackdata, strname, strval);
            }
        }
        else
        {
            // skip the chunk
            pbMeta += chunksize;
        }
    } // while

    return True;
}

void
(WINAPI *FTVPLoadBMP)(
    void                        *formatdata,
    void                        *callbackdata,
    tTVPGraphicSizeCallback      sizecallback,
    tTVPGraphicScanLineCallback  scanlinecallback,

#if !defined(FATE_STAY_NIGHT)
    tTVPMetaInfoPushCallback     metainfopushcallback,
#endif

    tTJSBinaryStream            *src,
    tjs_int                      keyidx,
    tTVPGraphicLoadMode          mode
);

Void
WINAPI
LoadUCI(
    tTVPGraphicLoadMode         mode,
    tjs_int32                   keyidx,
    tTJSBinaryStream           *src,
#if !defined(FATE_STAY_NIGHT)
    tTVPMetaInfoPushCallback    metainfopushcallback,
#endif
    tTVPGraphicScanLineCallback scanlinecallback
)
{
    void  *formatdata, *callbackdata;
    tTVPGraphicSizeCallback sizecallback;

    BOOL   bFindMeta;
    Int32  y, w, header, strideOut, alphatype;
    PByte  pbBuffer;
    PVOID lpBuffer;
    UCIInfo uci;

    INLINE_ASM
    {
        mov formatdata,   eax;
        mov callbackdata, edx;
        mov sizecallback, ecx;
    }

    UInt64 (TJS_INTF_METHOD *F_GetSize)(tTJSBinaryStream *src) = (UInt64 (TJS_INTF_METHOD *)(tTJSBinaryStream*))FUNC_GET_SIZE;

    ReadBuffer(src, &header, 4);
    if ((header & 0xFFFFFF) != TAG3('UCI'))
    {
        SetPosition(src, GetPosition(src) - 4);
        if (FTVPLoadBMP == NULL)
            return;

        INLINE_ASM
        {
            mov  eax, formatdata;
            mov  edx, callbackdata;
            mov  ecx, sizecallback;
            push scanlinecallback;
        }

        IF_EXIST(metainfopushcallback)
        {
            INLINE_ASM push metainfopushcallback;
        }

        INLINE_ASM
        {
            push src;
            push keyidx;
            push mode;
            call FTVPLoadBMP;
        }

        return;
    }

    CMem mem;
    w = (Int32)F_GetSize(src);
    lpBuffer = mem.Alloc(w);
    if (lpBuffer == NULL)
        return;

    ReadBuffer(src, (PByte)lpBuffer + 4, w - 4);
    *(PUInt32)lpBuffer = header;

    do
    {
        bFindMeta = False;
        IF_EXIST(metainfopushcallback)
        {
            bFindMeta = True;
        }

        if (UCIDecodeEx(lpBuffer, w, &uci, bFindMeta) < 0)
            break;

        IF_EXIST(metainfopushcallback)
        {
            if (uci.lpExtraInfo)
                InitMetaInfo(uci.lpExtraInfo, uci.ExtraInfoSize, metainfopushcallback, callbackdata);
        }

        SizeCallback(sizecallback, callbackdata, uci.Width, uci.Height);

        w = uci.Width;
        y = uci.Height - 1;
        alphatype = batMulAlpha;
        pbBuffer = uci.pbBuffer + y * uci.Stride;
        strideOut = (w * uci.BitsPerPixel / 8 + 3) & ~3;
        for (Int32 i = 0; i != uci.Height; ++i, pbBuffer -= uci.Stride)
        {
            PUInt32 scanline = (PUInt32)ScanLineCallback(scanlinecallback, callbackdata, y--);

            switch (uci.BitsPerPixel)
            {
                case 24:
                    if(mode == glmGrayscale)
                    {
                        TVPBLConvert24BitTo8Bit((tjs_uint8*)scanline, pbBuffer, w);
                    }
                    else
                    {
                        TVPBLConvert24BitTo32Bit(scanline, pbBuffer, w);
                    }
                    break;

                case 32:
                    if(mode == glmGrayscale)
                    {
                        TVPBLConvert32BitTo8Bit((tjs_uint8*)scanline, (PUInt32)pbBuffer, w);
                    }
                    else
                    {
                        if(alphatype == batNone)
                        {
                            // alpha channel is not given by the bitmap.
                            // destination alpha is filled with 255.
                            TVPBLConvert32BitTo32Bit_NoneAlpha((PUInt8)scanline, (PUInt32)pbBuffer, w);
                        }
                        else if(alphatype == batMulAlpha)
                        {
                            // this is the TVP native representation of the alpha channel.
                            // simply copy from the buffer.
                            TVPBLConvert32BitTo32Bit_MulAddAlpha((PUInt8)scanline, (PUInt32)pbBuffer, w);
                        }
                        else if(alphatype == batAddAlpha)
                        {
                            // this is alternate representation of the alpha channel,
                            // this must be converted to TVP native representation.
                            TVPBLConvert32BitTo32Bit_AddAlpha((PUInt8)scanline, (PUInt32)pbBuffer, w);
                        }
                    }
                    break;
            }

            ScanLineCallback(scanlinecallback, callbackdata, -1); // image was written
        }

        UCIFreeEx(&uci);
    } while (0);

    mem.Free(lpBuffer);
}

Void WINAPI AddGraphicHandler(SGraphicHandlerVector *pVector, SUnknownAtGraphicHandler *pUnknown)
{
    SGraphicHandler *pHandler;

    *(PVOID *)&FTVPLoadBMP = pVector->pBegin->handler;
    pVector->pBegin->handler = LoadUCI;
//    return;

#if 1
    pHandler = pVector->pBegin;
    *pVector->pEnd++ = *pHandler;
#else
    pHandler = pVector->pEnd++;
#endif
    pHandler->FormatData = NULL;
    pHandler->pStrExtention = GameNewttstr(L".uci");
    ++pHandler->pStrExtention->RefCount;
    pHandler->handler = LoadUCI;
}

ASM Void FASTCALL OldTVPGetPlacedPath(PSttstr *ppFindName, PSttstr *ppFindResult)
{
    INLINE_ASM mov eax, ecx;
    ASM_DUMMY_AUTO();
}

Void FASTCALL TVPGetPlacedPathInternal(PSttstr *ppFindName, PSttstr *ppFindResult)
{
    ULONG  FileType;
    UInt64  Extension;
    PSttstr pFindName;
    PWChar  pszExtension;

    OldTVPGetPlacedPath(ppFindName, ppFindResult);
    if (ppFindResult == NULL || *ppFindResult != NULL || ppFindName == NULL)
    {
        return;
    }

    pFindName = *ppFindName;
    if (pFindName == NULL)
        return;

    pszExtension = findextw(pFindName->pszBuffer ? pFindName->pszBuffer : pFindName->szString);
    if (*pszExtension != '.')
        return;

    ++pszExtension;
    Extension = *(PUInt64)pszExtension;
    switch (Extension & 0xFFFFFFDFFFDFFFDF)
    {
        case TAG3W('WAV'):
        case TAG3W('OGG'):
            *(PUInt64)pszExtension = TAG3W('uca');
            OldTVPGetPlacedPath(ppFindName, ppFindResult);
            if (*ppFindResult != NULL)
                return;

            *(PUInt64)pszExtension = TAG3W('m4a');
            break;

        case TAG3W('BMP'):
            *(PUInt64)pszExtension = TAG3W('uci');
            break;

        case TAG3W('MPG'):
            *(PUInt64)pszExtension = TAG3W('avi');
            break;

        default:
            return;
    }

    OldTVPGetPlacedPath(ppFindName, ppFindResult);

    if (*ppFindResult == NULL)
        *(PUInt64)pszExtension = Extension;
}

ASM Void FASTCALL TVPGetPlacedPath(PSttstr *ppFindName, PSttstr *ppFindResult)
{
    INLINE_ASM
    {
        mov ecx, eax;
        jmp TVPGetPlacedPathInternal;
    }
}

ASM PSttstr WINAPI GameNewttstr(PCWChar pszString)
{
    INLINE_ASM
    {
        mov  eax, dword ptr [esp+4];
        mov  ecx, FUNC_GAME_NEW_TTSTR;
        call ecx;
        ret  4;
    }
}

ASM PSttstr WINAPI Newttstr()
{
    INLINE_ASM
    {
        push eax;
        push ebx;
        push pGraphicHandlerVector;
        call AddGraphicHandler;
        pop  eax;
        mov ecx, FUNC_GAME_NEW_TTSTR;
        jmp ecx;
    }
}

ASM PVOID WINAPI ScanLineCallback(PVOID scanlinecallback, PVOID callbackdata, Int y)
{
    INLINE_ASM
    {
        mov eax, [esp+8];
        mov edx, [esp+0Ch];
        call [esp+4];
        ret 0Ch;
    }
}

ASM VOID WINAPI SizeCallback(PVOID sizecallback, PVOID callbackdata, Int32 w, Int32 h)
{
    INLINE_ASM
    {
        mov     eax, [esp+8];
        mov     edx, [esp+0Ch];
        mov     ecx, [esp+10h];
        call    [esp+4];
        ret     10h;
    }
}

ASM Void WINAPI MetaInfoPushCallback(PVOID metainfopushcallback, PVOID callbackdata, const tTJSString_S &name, const tTJSString_S &value)
{
    INLINE_ASM
    {
        mov eax, [esp+8];
        mov edx, [esp+0Ch];
        mov ecx, [esp+10h];
        call [esp+4];
        ret 10h;
    }
}

ASM UInt64 WINAPI GetSize(tTJSBinaryStream *src)
{
    INLINE_ASM
    {
        mov eax, FUNC_GET_SIZE;
        jmp eax;
    }
}

ASM UInt64 WINAPI GetPosition(tTJSBinaryStream *src)
{
    INLINE_ASM
    {
        pop eax;
        xchg eax, [esp];
        mov ecx, FUNC_GET_POS;
        jmp ecx;
    }
}

ASM Void WINAPI SetPosition(tTJSBinaryStream *src, tjs_uint64 pos)
{
    INLINE_ASM
    {
        pop eax;
        xchg eax, [esp];
        mov ecx, FUNC_SET_POS;
        jmp ecx;
    }
}

ASM Void WINAPI ReadBuffer(tTJSBinaryStream *src, PVOID buffer, tjs_uint read_size)
{
    INLINE_ASM
    {
        pop  ecx;
        pop  eax;
        pop  edx;
        xchg ecx, [esp];
        push FUNC_READ_BUFFER;
        ret;
    }
}

#if defined(USE_CXDEC)

BOOL DecryptCxdecInternal(ULONG Hash, LARGE_INTEGER Offset, PVOID lpBuffer, ULONG BufferSize)
{
    PBYTE           pbBuffer;
    ULONG           Mask, Mask2;
    LARGE_INTEGER   CurrentPos;
    CCxdec         *pCxdec;

    pCxdec = g_cxdec;
    if (pCxdec == NULL)
    {
        pCxdec = g_cxdec = new CCxdec;
    }

    pbBuffer = (PBYTE)lpBuffer;
    Mask = pCxdec->GetMask(Hash);

    Mask2 = LOWORD(Mask);
    CurrentPos.QuadPart = Offset.QuadPart + BufferSize;

    if (Mask2 >= Offset.QuadPart && Mask2 < CurrentPos.QuadPart)
    {
        *(pbBuffer + Mask2 - Offset.LowPart) ^= Hash >> 16;
    }

    Mask2 = HIWORD(Mask);
    if (Mask2 >= Offset.QuadPart && Mask2 < CurrentPos.QuadPart)
    {
        *(pbBuffer + Mask2 - Offset.LowPart) ^= Hash >> 8;
    }

    memxor(pbBuffer, Hash, BufferSize);

    return TRUE;
}

#endif /* DYNAMIC_CODE */

BOOL STDCALL Decrypt(const XP3_EXTRACTION_INFO *pInfo)
{
    ULONG SegmLength, Hash;
    LARGE_INTEGER CurrentPos, Offset2;
    XP3_EXTRACTION_INFO Info;

    Info = *pInfo;

#if defined(FATE_STAY_NIGHT)

    PBYTE pbBuffer;

    pbBuffer = (PBYTE)Info.Buffer;

    if (Info.Offset.QuadPart <= 0x13 && Info.Offset.QuadPart + Info.BufferSize > 0x13)
    {
        pbBuffer[0x13 - Info.Offset.LowPart] ^= 1;
    }
    if (Info.Offset.QuadPart <= 0x2EA29 && Info.Offset.QuadPart + Info.BufferSize > 0x2EA29)
    {
        pbBuffer[0x2EA29 - Info.Offset.LowPart] ^= 3;
    }

    memxor4(pbBuffer, 0x36363636, Info.BufferSize);

#elif defined(USE_CXDEC)

#if defined(REAL_SISTER)
    SegmLength = (Info.FileHash & 0x2B2) + 0x2E6;       // real sister
#elif defined(FATE_HA)
    SegmLength = (Info.FileHash & 0x143) + 0x787;       // fate ha
#elif defined(NATSU_ZORA)
    SegmLength = (Info.FileHash & 0x2F5) + 0x6F0;       // natsuzora
#elif defined(TENSHIN)
    SegmLength = (Info.FileHash & 0x167) + 0x498;       // ten shin
#elif defined(IMOUTO_STYLE)
    SegmLength = (Info.FileHash & 0x278) + 0xD7;        // imouto style
#endif

    Offset2.QuadPart = SegmLength;
    CurrentPos.QuadPart = Info.Offset.QuadPart + Info.BufferSize;
    if (Info.Offset.QuadPart < Offset2.QuadPart && CurrentPos.QuadPart > Offset2.QuadPart)
    {
        Hash = Info.FileHash;
        SegmLength = Offset2.LowPart - Info.Offset.LowPart;
        DecryptCxdecInternal(Hash, Info.Offset, Info.Buffer, SegmLength);

        Hash = (Info.FileHash >> 16) ^ Info.FileHash;
        Info.Buffer = (PBYTE)Info.Buffer + SegmLength;
        DecryptCxdecInternal(Hash, Offset2, Info.Buffer, Info.BufferSize - SegmLength);
    }
    else
    {
        if (Info.Offset.QuadPart < Offset2.LowPart)
        {
            Hash = Info.FileHash;
        }
        else
        {
            Hash = (Info.FileHash >> 16) ^ Info.FileHash;
        }

        DecryptCxdecInternal(Hash, Info.Offset, Info.Buffer, Info.BufferSize);
    }

#endif

    return TRUE;
}

EXTC HRESULT STDCALL V2Link(iTVPFunctionExporter *exporter)
{
    static PCChar funcname[] =
    {
        "void ::TVPSetXP3ArchiveExtractionFilter(tTVPXP3ArchiveExtractionFilter)",
        "void ::TVPBLConvert24BitTo8Bit(tjs_uint8 *,const tjs_uint8 *,tjs_int)",
        "void ::TVPBLConvert24BitTo32Bit(tjs_uint32 *,const tjs_uint8 *,tjs_int)",
        "void ::TVPBLConvert32BitTo8Bit(tjs_uint8 *,const tjs_uint32 *,tjs_int)",
        "void ::TVPBLConvert32BitTo32Bit_NoneAlpha(tjs_uint32 *,const tjs_uint32 *,tjs_int)",
        "void ::TVPBLConvert32BitTo32Bit_MulAddAlpha(tjs_uint32 *,const tjs_uint32 *,tjs_int)",
        "void ::TVPBLConvert32BitTo32Bit_AddAlpha(tjs_uint32 *,const tjs_uint32 *,tjs_int)",
        "tTJSString::tTJSString(const tjs_nchar *)",
    };

#if 0
    const char *func = "ttstr ::TVPGetPlacedPath(const ttstr &)";
    exporter->QueryFunctionsByNarrowString(&func, lpFunction, 1);
#endif

    exporter->QueryFunctionsByNarrowString(funcname, lpFunction, countof(funcname));

#if defined(FATE_STAY_NIGHT)
    HMODULE hKrMovie;

    hKrMovie = LoadLibraryExW(L"krmovie.dll", 0, 0);
    if (hKrMovie)
    {
        typedef HRESULT (STDCALL *FV2Link)(iTVPFunctionExporter *exporter);
        FV2Link V2Link = (FV2Link)GetProcAddress(hKrMovie, "V2Link");
        if (V2Link) do
        {
            V2Link(exporter);

            if ((*(PUInt32)((PByte)hKrMovie + 0x10AFA) & 0xFFFFFF) != 0x10C483 ||
                (*(PUInt32)((PByte)hKrMovie + 0x10B1A) & 0xFFFFFF) != 0x10C483 )
                break;

            MEMORY_PATCH p[] =
            {
                { 0x408D, 3, 0x10AFA },  // add esp, 10  -> lea eax, [eax+0]
                { 0x408D, 3, 0x10B1A },  // add esp, 10  -> lea eax, [eax+0]
            };
            PatchMemory(p, countof(p), 0, 0, hKrMovie);
        } while (0);
    }
#endif

#if defined(USE_DECYPT_FUNCTION)

    if (TVPSetXP3ArchiveExtractionFilter)
    {
        TVPSetXP3ArchiveExtractionFilter((tTVPXP3ArchiveExtractionFilter)Decrypt);

#if defined(USE_CXDEC)
        if (g_cxdec == NULL)
            g_cxdec = new CCxdec;
#endif
    }

#endif

    return S_OK;
}

EXTC HRESULT STDCALL V2Unlink()
{
#if defined(USE_DECYPT_FUNCTION)
    if (TVPSetXP3ArchiveExtractionFilter)
        TVPSetXP3ArchiveExtractionFilter(NULL);
#if defined(USE_CXDEC)
    SAFE_DELETE(g_cxdec);
#endif
#endif /* USE_DECYPT_FUNCTION */

    return S_OK;
}

EXTC
HRESULT
STDCALL
GetModuleInstance(
    ITSSModule **out,
    ITSSStorageProvider *provider,
    IStream * config,
    HWND mainwin
)
{
    // GetModuleInstance function (exported)

    *out = new CAACModule(provider);
    return S_OK;
}

DWORD WINAPI MyGetFileAttributesW(LPCWSTR lpFileName)
{
    WChar szFile[MAX_PATH];
    Int32 Length, dwAttr;

    dwAttr = GetFileAttributesW(lpFileName);
    if (dwAttr != -1)
        return dwAttr;

    Length = StrLengthW(lpFileName);
    if (Length < 5 ||
        lpFileName[Length - 4]         != '.' ||
        (*(PUInt64)&lpFileName[Length - 3] & 0xFFFFFFFFFFDFFFDF) != TAG3W('XP3'))
    {
        return dwAttr;
    }

    Length -= 4;
    memcpy(szFile, lpFileName, Length * 2);
    *(PUInt64)&szFile[Length + 0] = TAG4W('_sc.');
    *(PUInt64)&szFile[Length + 4] = TAG3W('xp3');
    lpFileName = szFile;

    return GetFileAttributesW(lpFileName);
}

HANDLE WINAPI MyCreateFileW(LPWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    WChar  szFile[MAX_PATH];
    DWORD dwLength;

    do
    {
        dwLength = StrLengthW(lpFileName);
        if (dwLength < 5 ||
            lpFileName[dwLength - 4]         != '.' ||
            (*(PUInt64)&lpFileName[dwLength - 3] & 0xFFFFFFFFFFDFFFDF) != TAG3W('XP3') ||
            IsPathExistsW(lpFileName))
        {
            break;
        }

        dwLength -= 4;
        memcpy(szFile, lpFileName, dwLength * 2);
        *(PUInt64)&szFile[dwLength + 0] = TAG4W('_sc.');
        *(PUInt64)&szFile[dwLength + 4] = TAG3W('xp3');
        lpFileName = szFile;

    } while (0);

    return CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HFONT WINAPI MyCreateFontIndirectA(LOGFONTA *lplf)
{
    LOGFONTW lf;

    CopyStruct(&lf, lplf, GetStructMemberOffset(LOGFONTA, lfHeight, lfFaceName));
    lf.lfCharSet = GB2312_CHARSET;
    MultiByteToWideChar(CP_ACP, 0, lplf->lfFaceName, sizeof(lplf->lfFaceName), lf.lfFaceName, countof(lf.lfFaceName));

    return CreateFontIndirectW(&lf);
}

ASM DWORD WINAPI OldGetGlyphOutlineW(HDC hDC, UINT uChar, UINT uFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpvBuffer, CONST MAT2 *lpmat2)
{
    ASM_DUMMY_AUTO();
/*
    __asm
    {
        mov  eax, 1;
        mov  eax, 1;
#if defined(__INTEL_COMPILER)
        mov  eax, offset GetGlyphOutlineW;
        jmp  [eax];
#else
        jmp dword ptr [GetGlyphOutlineW];
#endif
    }
*/
}

DWORD WINAPI MyGetGlyphOutlineW(HDC hDC, UINT uChar, UINT uFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpvBuffer, CONST MAT2 *lpmat2)
{
    HFONT  hFontGB;
    ULONG RecvSize;
    LOGFONTW lf;

    switch (uChar)
    {
        default:
            hFontGB = NULL;
            break;

        case 0x30FB:    // ·
        case 0x266A:    // eighth note
            hFontGB = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
            GetObjectW(hFontGB, sizeof(lf), &lf);
            lf.lfCharSet = SHIFTJIS_CHARSET;
            hFontGB = (HFONT)SelectObject(hDC, CreateFontIndirectW(&lf));
            break;
    }

    RecvSize = OldGetGlyphOutlineW(hDC, uChar, uFormat, lpgm, cbBuffer, lpvBuffer, lpmat2);
    if (hFontGB)
        DeleteObject(SelectObject(hDC, hFontGB));

    return RecvSize;
}

Void AnsiWin32FindDataToUnicode(LPWIN32_FIND_DATAW pwfdW, LPWIN32_FIND_DATAA pwfdA)
{
    pwfdA->dwFileAttributes = pwfdW->dwFileAttributes;
    pwfdA->ftCreationTime   = pwfdW->ftCreationTime;
    pwfdA->ftLastAccessTime = pwfdW->ftLastAccessTime;
    pwfdA->ftLastWriteTime  = pwfdW->ftLastWriteTime;
    pwfdA->nFileSizeHigh    = pwfdW->nFileSizeHigh;
    pwfdA->nFileSizeLow     = pwfdW->nFileSizeLow;
    pwfdA->dwReserved0      = pwfdW->dwReserved0;
    pwfdA->dwReserved1      = pwfdW->dwReserved1;
    WideCharToMultiByte(CP_ACP, 0, pwfdW->cFileName, -1, pwfdA->cFileName, sizeof(pwfdA->cFileName), 0, 0);
}

HANDLE WINAPI MyFindFirstFileA(LPSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
    Int32  Length;
    UInt64 Extention;
    WChar  szDllFileName[MAX_PATH], szFileName[MAX_PATH];
    HANDLE hFind;
    WIN32_FIND_DATAW FindFileData;

    Length = MultiByteToWideChar(CP_ACP, 0, lpFileName, -1, szFileName, countof(szFileName));
    hFind  = FindFirstFileW(szFileName, &FindFileData);
    if (hFind != INVALID_HANDLE_VALUE)
        AnsiWin32FindDataToUnicode(&FindFileData, lpFindFileData);

    do
    {
        --Length;
        if (Length < 5 || szFileName[Length - 4] != '.')
            break;

        Extention = *(PUInt64)&szFileName[Length - 3];
        if ((Extention & 0xFFFFFFDFFFDFFFDF) != TAG3W('TPM'))
        {
            if (hFind != INVALID_HANDLE_VALUE ||
                (Extention & 0xFFFFFFFFFFDFFFDF) != TAG3W('XP3'))
            {
                break;
            }

            *(PUInt64)&szFileName[Length - 4] = TAG4W('_sc.');
            *(PUInt64)&szFileName[Length - 0] = TAG3W('xp3');

            hFind = FindFirstFileW(szFileName, &FindFileData);
            if (hFind != INVALID_HANDLE_VALUE)
                AnsiWin32FindDataToUnicode(&FindFileData, lpFindFileData);

            break;
        }

        if ((*(PUInt64)&szFileName[Length - 5] & 0xFFDFFFDFFFFFFFFF) != TAG4W('*.TP'))
            break;

        Length = GetModuleFileNameW((HMODULE)&__ImageBase, szDllFileName, countof(szDllFileName));
        while (szDllFileName[--Length] != '\\');
        ++Length;
        if ((*(PUInt64)&szFileName[Length] & 0xFFDFFFDFFFFFFFFF) != TAG4W('*.TP'))
            break;

        if (hFind != INVALID_HANDLE_VALUE)
            hFind = (HANDLE)((ULONG)hFind | 1);
        else
        {
            hFind = (HANDLE)1;
            lpFindFileData->dwFileAttributes = ~FILE_ATTRIBUTE_DIRECTORY;
            WideCharToMultiByte(
                CP_ACP,
                0,
                szDllFileName + Length,
                -1,
                lpFindFileData->cFileName,
                sizeof(lpFindFileData->cFileName),
                NULL,
                NULL);
        }

    } while (0);

    return hFind;
}

BOOL WINAPI MyFindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
{
    BOOL  Result, bExtraFlag;
    DWORD dwAttribute = ~FILE_ATTRIBUTE_DIRECTORY;

    bExtraFlag = (Int_Ptr)hFindFile & 1;
    hFindFile  = (HANDLE)((Int_Ptr)hFindFile & ~1);
    if (hFindFile && lpFindFileData->dwFileAttributes != dwAttribute)
    {
        WIN32_FIND_DATAW wfd;
        Result = FindNextFileW(hFindFile, &wfd);
        if (Result)
        {
            AnsiWin32FindDataToUnicode(&wfd, lpFindFileData);
        }
    }
    else
    {
        Result = False;
    }

    if (!Result && bExtraFlag)
    {
        if (lpFindFileData->dwFileAttributes == dwAttribute)
            return False;

        if (hFindFile != NULL)
        {
            WChar szDllFileName[MAX_PATH];
            DWORD dwLength;

            lpFindFileData->dwFileAttributes = dwAttribute;
            dwLength = GetModuleFileNameW((HMODULE)&__ImageBase, szDllFileName, countof(szDllFileName));
            while (szDllFileName[--dwLength] != '\\');
            WideCharToMultiByte(CP_ACP, 0, &szDllFileName[++dwLength], -1, lpFindFileData->cFileName, sizeof(lpFindFileData->cFileName), 0, 0);
        }

        return True;
    }

    return Result;
}

BOOL WINAPI MyFindClose(HANDLE hFindFile)
{
    hFindFile = (HANDLE)((Int_Ptr)hFindFile & ~1);
    if (hFindFile == NULL)
        return True;

    return FindClose(hFindFile);
}

HMODULE WINAPI MyLoadLibraryA(LPCSTR lpLibFileName)
{
    Int32   Length;
    HMODULE hModule;
    WChar   szLibFileName[MAX_PATH];
    static WChar szWuVorbisPlugin[] = L"wuvorbis.dll";

    Length = MultiByteToWideChar(
                 CP_ACP,
                 0,
                 lpLibFileName,
                 -1,
                 szLibFileName,
                 countof(szLibFileName));
    hModule = LoadLibraryExW(szLibFileName, NULL, 0);

    if (hModule != NULL &&
        Length > countof(szWuVorbisPlugin) &&
        !StrICompareW(szLibFileName + Length - countof(szWuVorbisPlugin), szWuVorbisPlugin))
    {
//        ULong Flags = GET_MODULE_HANDLE_EX_FLAG_PIN | GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS;
//        GetModuleHandleExW(Flags, (PWChar)hModule, &hModule);
        hModule = (HMODULE)&__ImageBase;
    }

    return hModule;
}

FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    if ((int)lpProcName > 0xFFFF)
    {
        switch (HashAPI(lpProcName))
        {
            case 0xB231F013: return (FARPROC)MyCreateFileW;
            case 0x3C133E3B: return (FARPROC)MyGetFileAttributesW;
            case 0xA1A757E4: return (FARPROC)MyGetGlyphOutlineW;
        }
    }

    return GetProcAddress(hModule, lpProcName);
}

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    static BOOL b;
    WChar buf[MAX_PATH];

    if (_InterlockedCompareExchange((PLong)&b, True, False) == False) do
    {
        HMODULE hModule;
        HANDLE hFile;
        DWORD dwWritten;
        SYSTEMTIME st;

        hFile = CreateFileW(L"Log.txt", GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
            break;

        if (SetFilePointer(hFile, 0, 0, FILE_END) == 0)
        {
            *(PUInt16)buf = 0xFEFF;
            WriteFile(hFile, buf, 2, &dwWritten, NULL);
        }

        GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPWSTR)ExceptionInfo->ExceptionRecord->ExceptionAddress, &hModule);
        dwWritten = GetModuleFileNameW(hModule, buf, countof(buf));
        WriteFile(hFile, buf, dwWritten * 2, &dwWritten, NULL);

        GetLocalTime(&st);
        dwWritten = wsprintfW(
            buf,
            L"\n"
            L"%02d:%02d:%02d\n"
            L"ThreadID = %X\n"
            L"code = %X\n"
            L"addr = %p\n\n",
            st.wHour, st.wMinute, st.wSecond,
            GetCurrentThreadId(),
            ExceptionInfo->ExceptionRecord->ExceptionCode,
            ExceptionInfo->ExceptionRecord->ExceptionAddress);

        WriteFile(hFile, buf, dwWritten * 2, &dwWritten, NULL);
        CloseHandle(hFile);

        _InterlockedCompareExchange((PLong)&b, False, True);

    } while (0);

    return EXCEPTION_CONTINUE_SEARCH;
}

Void Init()
{
    HANDLE hFind;
    WIN32_FIND_DATAW wfd;

//    AddVectoredExceptionHandler(True, VectoredHandler);

    MEMORY_FUNCTION_PATCH api_f[] =
    {
        { JUMP, (ULong)GetGlyphOutlineW, MyGetGlyphOutlineW, 0, OldGetGlyphOutlineW },
    };

#if defined(REAL_SISTER)
    /************************************************************************/
    /* リアル妹がいる大泉くんのばあい                                       */
    /************************************************************************/
    INTEL_STATIC MEMORY_PATCH p[] =
    {
        { 0xEB                       , 1, 0x261F97 },  // font filter
        { 0xC08B                     , 2, 0x0B04D9
        },  // force WaitMessage
        { (DWORD)&"realsister_sc.xp3", 4, 0x210510 },
//        { (DWORD)MyFindFirstFileA,      4, 0x3D63DC },

#if defined(MY_DEBUG)
        { (DWORD)MyCreateFontIndirectA, 4, 0x3D6888 },
#endif
    };

    INTEL_STATIC MEMORY_FUNCTION_PATCH f[] =
    {
        { CALL, 0x154643, Newttstr,         0 },
        { CALL, 0x0023A9, MyGetProcAddress, 0 },
        { CALL, 0x2182C6, MyLoadLibraryA,   0 },    // 4th from the last
        { CALL, 0x0EEB3B, MyFindFirstFileA, 0 },    // first
        { CALL, 0x21738C, MyFindFirstFileA, 0 },
        { CALL, 0x2174BA, MyFindNextFileA,  0 },
        { CALL, 0x2174C8, MyFindClose,      0 },
//        { JUMP, 0x1FD8B0, TVPIsExistentStorage, 1, (PByte)OldTVPIsExistentStorage + 2 },
        { JUMP, 0x1FCB10, TVPGetPlacedPath, 1, (PByte)OldTVPGetPlacedPath + 2 },
    };

#elif defined(FATE_STAY_NIGHT)
    /************************************************************************/
    /* Fate/Stay Night                                                      */
    /************************************************************************/
    INTEL_STATIC MEMORY_PATCH p[] =
    {
        { 0xEB, 1, 0x177226 },  // check krmovie version
        { (ULong)&"fsn_sc.xp3", 4, 0x1C25F2 },

#if defined(MY_DEBUG)
        { (ULong)MyCreateFontIndirectA, 4, 0x3097D4 },
#endif
    };

    INTEL_STATIC MEMORY_FUNCTION_PATCH f[] =
    {
        { CALL, 0x14D302, Newttstr,         0 },
        { CALL, 0x0021BD, MyGetProcAddress, 0 },
        1{ CALL, 0x217D32, MyLoadLibraryA,   0 },    // 4th from the last
        1{ CALL, 0x0EED87, MyFindFirstFileA, 0 },    // first
        { CALL, 0x1CAD1C, MyFindFirstFileA, 0 },
        { CALL, 0x1CAE4A, MyFindNextFileA,  0 },
        { CALL, 0x1CAE58, MyFindClose,      0 },
        1{ JUMP, 0x1FCB10, TVPGetPlacedPath, 1, (PByte)OldTVPGetPlacedPath + 2 },
    };

#elif defined(FATE_HA)
    /************************************************************************/
    /* Fate／hollow ataraxia                                                */
    /************************************************************************/
    INTEL_STATIC MEMORY_PATCH p[] =
    {
        { (ULong)&"fha_sc.xp3", 4, 0x1FD327 },
        { (ULong)MyFindFirstFileA,  4, 0x3A43B4 },
#if defined(MY_DEBUG)
        { (ULong)MyCreateFontIndirectA, 4, 0x3A482C },
#endif
    };

    INTEL_STATIC MEMORY_FUNCTION_PATCH f[] =
    {
        { CALL, 0x17AF32, Newttstr,             0 },
        { CALL, 0x0021ED, MyGetProcAddress,     0 },
        { CALL, 0x204DDE, MyLoadLibraryA,       0 },    // 4th from the last
//        { CALL, 0x0F613B, MyFindFirstFileA,     0 },    // first
//        { CALL, 0x203EA4, MyFindFirstFileA,     0 },
        { CALL, 0x203FD2, MyFindNextFileA,      0 },
        { CALL, 0x203FE0, MyFindClose,          0 },
//        { JUMP, 0x1EC9A8, TVPIsExistentStorage, 1, (PByte)OldTVPIsExistentStorage + 2 },
        { JUMP, 0x1EBC08, TVPGetPlacedPath, 1, (PByte)OldTVPGetPlacedPath + 2 },
    };

#elif defined(GSTRING)
    /************************************************************************/
    /* Ｇ線上の魔王                                                         */
    /************************************************************************/
    INTEL_STATIC MEMORY_PATCH p[] =
    {
//        { 0xEB,                     1, 0x262653 },
        { (ULong)&"gstring_sc.xp3", 4, 0x2181EA },

#if defined(MY_DEBUG)
        { (ULong)MyCreateFontIndirectA, 4, 0x3D5870 },
#endif
    };

    INTEL_STATIC MEMORY_FUNCTION_PATCH f[] =
    {
        { CALL, 0x18205F, Newttstr,         0 },
        { CALL, 0x0023A9, MyGetProcAddress, 0 },
        { CALL, 0x21FDDA, MyLoadLibraryA,   0 },    // 4th from the last
        { CALL, 0x0F5A77, MyFindFirstFileA, 0 },    // first
        { CALL, 0x21EEA0, MyFindFirstFileA, 0 },
        { CALL, 0x21EFCE, MyFindNextFileA,  0 },
        { CALL, 0x21EFDC, MyFindClose,      0 },
        { JUMP, 0x2049C8, TVPGetPlacedPath, 1, (PByte)OldTVPGetPlacedPath + 2 },
    };

#elif defined(NATSU_ZORA)
    /************************************************************************/
    /* 夏空カナタ                                                           */
    /************************************************************************/
    INTEL_STATIC MEMORY_PATCH p[] =
    {
        { (ULong)&"natsuzora_sc.xp3", 4, 0x2122F2 },

#if defined(MY_DEBUG)
        //        { (ULong)MyCreateFontIndirectA, 4, 0x3D6870 },
#endif
    };

    INTEL_STATIC MEMORY_FUNCTION_PATCH f[] =
    {
        { CALL, 0x157017, Newttstr,     0 },
        { CALL, 0x0023A9, MyGetProcAddress, 0 },
        { CALL, 0x218FA8, MyFindFirstFileA, 0 },
        { CALL, 0x2190D6, MyFindNextFileA,  0 },
        { CALL, 0x2190E4, MyFindClose,      0 },
    };

#elif defined(TENSHIN)
    /************************************************************************/
    /* 天神乱漫                                                             */
    /************************************************************************/
    INTEL_STATIC MEMORY_PATCH p[] =
    {
        { (ULong)&"tenshin_sc.xp3", 4, 0x2100F8 },
    //    { 0xEB                    , 1, 0x261A2B },  // font filter

#if defined(MY_DEBUG)
        { (ULong)MyCreateFontIndirectA, 4, 0x3D5884 },
#endif
        //    { 0, 0, 0 },
    };

    INTEL_STATIC MEMORY_FUNCTION_PATCH f[] =
    {
        { CALL, 0x15482F, Newttstr,         0 },
        { CALL, 0x0023A9, MyGetProcAddress, 0 },
        { CALL, 0x217D32, MyLoadLibraryA,   0 },    // 4th from the last
        { CALL, 0x0EED87, MyFindFirstFileA, 0 },    // first
        { CALL, 0x216DF8, MyFindFirstFileA, 0 },
        { CALL, 0x216F26, MyFindNextFileA,  0 },
        { CALL, 0x216F34, MyFindClose,      0 },
//        { JUMP, 0x1FD4A4, TVPIsExistentStorage, 1, (PByte)OldTVPIsExistentStorage + 2 },
        { JUMP, 0x1FC704, TVPGetPlacedPath, 1, (PByte)OldTVPGetPlacedPath + 2 },

        /*********************************************

        mov     word [ebp+const], 44
        lea     edx, dword ptr [ebp-const]
        mov     eax, r32
        call    const

        **********************************************/
    };

#endif

#if defined(MY_DEBUG)
    PatchMemory(p, countof(p), f, countof(f), GetModuleHandleW(0));
    IF_EXIST(api_f)
    {
        PatchMemory(0, 0, api_f, countof(api_f), 0);
    }
#else
    PatchMemoryNoVP(p, countof(p), f, countof(f), GetModuleHandleW(0));
#endif

    GetExecuteDirectoryW(wfd.cFileName, countof(wfd.cFileName));
    SetCurrentDirectoryW(wfd.cFileName);

    hFind = FindFirstFileW(L"*.tt?", &wfd);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
            AddFontResourceExW(wfd.cFileName, FR_PRIVATE, 0);
        while (FindNextFileW(hFind, &wfd));
        FindClose(hFind);
    }
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULong Reason, LPVOID lpReserved)
{
    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            CMem::CreateGlobalHeap();
            Init();

#if defined(USE_CXDEC)
            if (g_cxdec == NULL)
                g_cxdec = new CCxdec;
#endif
            break;

        case DLL_PROCESS_DETACH:
#if defined(USE_CXDEC)
            SAFE_DELETE(g_cxdec);
#endif
            CMem::DestroyGlobalHeap();
            break;
    }

    return TRUE;
}

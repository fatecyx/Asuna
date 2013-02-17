// 殻ノ少女
#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#pragma comment(lib, "vfw32.lib")

#include <Windows.h>
#include "shoujo.h"
#include "vorbishook.h"

HANDLE
WINAPI
MyCreateFileA(
    LPCSTR                lpFileName,
    DWORD                 dwDesiredAccess,
    DWORD                 dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD                 dwCreationDisposition,
    DWORD                 dwFlagsAndAttributes,
    HANDLE                hTemplateFile
)
{
    Int32 Length;
    WChar szFileName[MAX_PATH];

    do
    {
        Length = MultiByteToWideChar(CP_ACP, 0, lpFileName, -1, szFileName, countof(szFileName));
        --Length;
        if (Length < 5                           ||
            GetFileAttributesW(szFileName) != -1 ||
            szFileName[Length - 4] != '.'        ||
            (*(PInt64)&szFileName[Length - 3] & 0xFFFFFFDFFFDFFFDF) != TAG3W('DAT'))
            break;

        *(PInt64)&szFileName[Length - 4] = TAG4W('_sc.');
        *(PInt64)&szFileName[Length - 0] = TAG3W('dat');

    } while (0);

    return CreateFileW(
               szFileName,
               dwDesiredAccess,
               dwShareMode,
               lpSecurityAttributes,
               dwCreationDisposition,
               dwFlagsAndAttributes,
               hTemplateFile);
}

ASM HANDLE CDECL OldFindFile(SKaraString *pFileName, SKaraFindFileInfo *pFindInfo)
{
    ASM_DUMMY(6);
    ASM_UNIQUE();
}

HANDLE CDECL FindFile(SKaraString *pFileName, SKaraFindFileInfo *pFindInfo)
{
    HANDLE hResult;
    PChar  pszExtension;
    UInt32 Extension;

    do
    {
        hResult = OldFindFile(pFileName, pFindInfo);
        if (hResult != NULL)
            break;

        if (pFileName == NULL ||
            pFileName->pszString == NULL ||
            pFileName->Length < 4)
        {
            break;
        }

        pszExtension = findexta(pFileName->pszString);
        if (*pszExtension != '.')
            break;

        ++pszExtension;
        Extension = *(PUInt32)pszExtension;
        switch (Extension & 0xFFDFDFDF)
        {
            case TAG3('BMP'):
                Extension = TAG3('uci');
                break;

            case TAG3('OGG'):
                Extension = TAG3('uca');
                break;

            default:
                return hResult;
        }

        *(PUInt32)pszExtension = Extension;
        pFindInfo->EncryptFlags = 0;
        hResult = OldFindFile(pFileName, pFindInfo);
        if (hResult != NULL || Extension != TAG3('uca'))
            break;

        pFindInfo->EncryptFlags = 0;
        *(PUInt32)pszExtension = TAG3('m4a');
        hResult = OldFindFile(pFileName, pFindInfo);

    } while (0);

    return hResult;
}

LRESULT
FASTCALL
CompareFileName(
    SKaraString *pNameInDat,
    Int,
    Int          StartPos,
    UInt32       LengthInDat,
    PChar        pszNameToFind,
    UInt32       LengthFind
)
{
    if (pNameInDat            == NULL ||
        pszNameToFind         == NULL ||
        pNameInDat->pszString == NULL ||
        LengthInDat != LengthFind)
    {
        return -1;
    }

    LRESULT Result;
    PChar   pszExtension;
    UInt32  Extension;

    do
    {
        Result = memcmp(pNameInDat->pszString, pszNameToFind, LengthInDat);
        if (Result == NO_ERROR)
            break;

        pszExtension = findexta(pszNameToFind);
        if (*pszExtension != '.')
            break;

        ++pszExtension;
        Extension = *(PUInt32)pszExtension;
        switch (Extension & 0xFFDFDFDF)
        {
            case TAG3('BMP'):
                Extension = TAG3('uci');
                break;

            case TAG3('OGG'):
                Extension = TAG3('uca');
                break;

            default:
                return Result;
        }

        *(PUInt32)pszExtension = Extension;
        Result = memcmp(pNameInDat->pszString, pszNameToFind, LengthInDat);
        if (Result == NO_ERROR || Extension != TAG3('uca'))
            break;

        *(PUInt32)pszExtension = TAG3('m4a');
        Result = memcmp(pNameInDat->pszString, pszNameToFind, LengthInDat);

    } while (0);

    return Result;
}

#define CallOldLoadFile(pStream, pFileName) OldLoadFile(pStream, 0, pFileName)

ASM Long FASTCALL OldLoadFile(SKaraMemoryStream *pStream, Int32, SKaraString *pFileName)
{
    ASM_DUMMY(5);
    ASM_UNIQUE();
}

Long FASTCALL LoadFile(SKaraMemoryStream *pStream, Int32, SKaraString *pFileName)
{
    Long    Result, BitmapSize, BitmapStride;
    UCIInfo uci;
    HGLOBAL hGlobalImage;
    PByte   pbSrc, pbDest;
    SBitMapHeader *pHeader;

    Result = CallOldLoadFile(pStream, pFileName);
    if (Result != NO_ERROR)
        return Result;

    if (pStream->hGlobal == NULL ||
        pStream->FileSize < 4 ||
        (*(PUInt32)pStream->hGlobal & 0xFFFFFF) != TAG3('UCI'))
    {
        return Result;
    }

    if (UCIDecodeEx(pStream->hGlobal, pStream->FileSize, &uci, False) < 0)
        return Result;

    do
    {
        BitmapStride = (uci.Width * uci.BitsPerPixel / 8 + 3) & ~3;
        BitmapSize = uci.Height * BitmapStride + sizeof(*pHeader);
        hGlobalImage = GlobalAlloc(GMEM_FIXED, BitmapSize);
        if (hGlobalImage == NULL)
            break;

        pHeader = (SBitMapHeader *)hGlobalImage;
        InitBitmapHeader(pHeader, uci.Width, uci.Height, uci.BitsPerPixel, NULL);
        pbSrc = uci.pbBuffer + uci.Stride * (uci.Height - 1);
        pbDest = (PByte)hGlobalImage + sizeof(*pHeader);
        while (uci.Height--)
        {
            memcpy(pbDest, pbSrc, uci.Stride);
            pbSrc  -= uci.Stride;
            pbDest += BitmapStride;
        }

        GlobalFree(pStream->hGlobal);
        pStream->hGlobal = hGlobalImage;
        pStream->FileSize = BitmapSize;

    } while (0);

    UCIFreeEx(&uci);

    return Result;
}

ASM
int
CDECL
old_ov_open_callbacks(
    void *f,
    OggVorbis_File *vf,
    char *initial,
    long ibytes,
    ov_callbacks callbacks
)
{
    ASM_DUMMY(5);
    ASM_UNIQUE();
}

ASM
long
CDECL
old_ov_read(
    OggVorbis_File *vf,
    char *buffer,
    int length,
    int bigendianp,
    int word,
    int sgned,
    int *bitstream
)
{
    ASM_DUMMY(5);
    ASM_DUMMY(1);
    ASM_UNIQUE();
}

ASM int CDECL old_ov_pcm_seek(OggVorbis_File *vf, ogg_int64_t pos)
{
    // 8 + 5
    ASM_DUMMY(7);
    ASM_DUMMY(1);
    ASM_UNIQUE();
}

ASM int CDECL old_ov_clear(OggVorbis_File *vf)
{
    // 5 + 5
    ASM_DUMMY(5);
    ASM_UNIQUE();
}

Void Init()
{
    INTEL_STATIC SPatch p[] =
    {
        // init
        { 0xFF80, 4, 0x112440 },
        { 0x7BEB,   2, 0xC4391 },    // nocd

        // check
        { 0xEB,   1, 0x43BF },
        { 0xEB,   1, 0x5F33 },
        { 0xEB,   1, 0x5F9E },
        { 0xEB,   1, 0x66ED },
        { 0xEB,   1, 0x6738 },
        { 0xEB,   1, 0x71B4 },
        { 0xEB,   1, 0x7429 },
        { 0x3BEB, 2, 0x36B30 },

        // char
        { 0xA1A1, 4, 0x26C6E },

        { 0xA1E7, 4, 0x78E64 },
        { 0xA1E7, 4, 0x7D8F7 },
        { 0xA1E7, 4, 0x7DC93 },
        { 0xA1E7, 4, 0x7E001 },
        { 0xA1E7, 4, 0x7E2C5 },
        { 0xA1E7, 4, 0x7E6A4 },
        { 0xA1E7, 4, 0x7FA46 },
        { 0xA1E7, 4, 0x7FEFD },
        { 0xA1E7, 4, 0x802D1 },
        { 0xA1E7, 4, 0x807C4 },
        { 0xA1E7, 4, 0x817EF },
        { 0xA1E7, 4, 0x81A82 },

        { GB2312_CHARSET, 4, 0x263E5 },
        { GB2312_CHARSET, 4, 0x2640B },
        { STRTOUINT32("@黑体"), 4, 0x263D8 },
        { STRTOUINT32("黑体"),  4, 0x263FE },

//        { STRTOUINT32("壳之少女 Ver.1.01"),  4, 0xC4355 },

        { STRTOUINT32("save_sc\\Config.dat"),  4, 0x1FDD5 },
        { STRTOUINT32("save_sc\\Config.dat"),  4, 0x1FF0A },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x33686 },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x33F4E },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x3412C },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x34305 },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x34644 },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x34BCA },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x35D34 },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x364B8 },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x5CDB6 },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x5D783 },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x5D95C },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x5DC9C },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x5E222 },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x5F29F },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x5F66F },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x5FD28 },
        { STRTOUINT32("save_sc\\savefile%02d.sav"),  4, 0x5FE88 },
        { STRTOUINT32("\\save_sc"),                  4, 0xC441A },
    };

    INTEL_STATIC SFuncPatch f[] =
    {
        // api
        { CALL, 0x421B, MyCreateFileA, 1 },

        // general
        { CALL, 0x43FA, CompareFileName, 0 },
//        { JUMP, 0x3FF0, FindFile, 1, OldFindFile },

        // image
        { JUMP, 0x47A0, LoadFile, 0, OldLoadFile },

        // audio
        { JUMP, 0xD43C0, my_ov_open_callbacks, 0, old_ov_open_callbacks },
        { JUMP, 0xD6690, my_ov_read,           1, old_ov_read },
        { JUMP, 0xD5CF0, my_ov_pcm_seek,       3, old_ov_pcm_seek },
        { JUMP, 0xD42C0, my_ov_clear,          0, old_ov_clear },
    };

    PatchMemory(p, countof(p), f, countof(f), GetModuleHandleW(NULL));

    vorbis_func.ov_open_callbacks = old_ov_open_callbacks;
    vorbis_func.ov_read           = old_ov_read;
    vorbis_func.ov_pcm_seek       = old_ov_pcm_seek;
    vorbis_func.ov_clear          = old_ov_clear;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    if (ulReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hInstance);
        Init();
    }

    return True;
}
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "vorbisfile.lib")

#include <Windows.h>

#include "piano.h"
#include "my_api.cpp"
#include "Mem.cpp"

SPianoFunction g_func;

#define USE_CACHE

#if defined(USE_CACHE)

#include "ImageCache.h"

UInt32              g_UCIReadCount, g_CacheHitCount, g_CacheCount;
CImageCahce<61, 3>  g_ImageCache;

#endif

enum
{
    BGM,
    SE,
    VOICE = TAG4('RIFF'),
};

/*
#include "AudioPlayback.h"
#include "AudioPlayback.cpp"
*/

#define SUPPORT_AAC_DECODE
#define DEFAULT_STRUCT_ALIGN 8

#include "vorbishook.cpp"

OVERLOAD_CPP_NEW_WITH_HEAP(CMem::GetGlobalHeap())

Bool FASTCALL InitFunctionBaseUser32(SFunctionBaseUser32 *f, SFunctionBaseKernel32 *k)
{
    if (!k || !k->GetModuleHandleExW || !k->LoadLibraryExA)
        return False;

    HMODULE hUser32;

    hUser32 = k->LoadStayedLibraryA("USER32.dll", k);

    GetFuncAddress(f->MessageBoxA,      hUser32, "MessageBoxA");
    GetFuncAddress(f->MessageBoxW,      hUser32, "MessageBoxW");
    GetFuncAddress(f->GetMessageA,      hUser32, "GetMessageA");
    GetFuncAddress(f->GetMessageW,      hUser32, "GetMessageW");
    GetFuncAddress(f->PeekMessageA,     hUser32, "PeekMessageA");
    GetFuncAddress(f->PeekMessageW,     hUser32, "PeekMessageW");
    GetFuncAddress(f->wsprintfA,        hUser32, "wsprintfA");
    GetFuncAddress(f->wsprintfW,        hUser32, "wsprintfW");
    GetFuncAddress(f->GetKeyState,      hUser32, "GetKeyState");
    GetFuncAddress(f->GetAsyncKeyState, hUser32, "GetAsyncKeyState");

    return True;
}

Bool FASTCALL InitFunctionBaseGdi32(SFunctionBaseGdi32 *f, SFunctionBaseKernel32 *k)
{
    if (!k || !k->GetModuleHandleExW || !k->LoadLibraryExA)
        return False;

    HMODULE hGdi32;

    hGdi32 = k->LoadStayedLibraryA("GDI32.dll", k);

    GetFuncAddress(f->GetTextMetricsA,     hGdi32, "GetTextMetricsA");
    GetFuncAddress(f->GetTextMetricsW,     hGdi32, "GetTextMetricsW");
    GetFuncAddress(f->SelectObject,        hGdi32, "SelectObject");
    GetFuncAddress(f->CreateFontIndirectA, hGdi32, "CreateFontIndirectA");
    GetFuncAddress(f->CreateFontIndirectW, hGdi32, "CreateFontIndirectW");
    GetFuncAddress(f->GetGlyphOutlineW,    hGdi32, "GetGlyphOutlineW");

    return True;
}

HMODULE WINAPI LoadStayedLibraryA(LPCSTR lpLibFileName, SFunctionBaseKernel32 *k)
{
    HMODULE hModule;
    DWORD   dwFlags;
    dwFlags = GET_MODULE_HANDLE_EX_FLAG_PIN|GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS;

    hModule = k->LoadLibraryExA(lpLibFileName, 0, 0);
    k->GetModuleHandleExW(dwFlags, (LPCWSTR)hModule, &hModule);

    return hModule;
}

Bool FASTCALL InitFunctionBaseKernel32(SFunctionBaseKernel32 *f)
{
    if (!f)
        return False;

    HMODULE hKernel32 = GetKernel32Handle();

    f->LoadStayedLibraryA = LoadStayedLibraryA;
    GetFuncAddress(f->CreateMutexA,                 hKernel32, "CreateMutexA");
    GetFuncAddress(f->CreateMutexW,                 hKernel32, "CreateMutexW");
    GetFuncAddress(f->GlobalAlloc,                  hKernel32, "GlobalAlloc");
    GetFuncAddress(f->GetFileAttributesA,           hKernel32, "GetFileAttributesA");
    GetFuncAddress(f->GetFileAttributesW,           hKernel32, "GetFileAttributesW");
    GetFuncAddress(f->CreateFileA,                  hKernel32, "CreateFileA");
    GetFuncAddress(f->CreateFileW,                  hKernel32, "CreateFileW");
    GetFuncAddress(f->SetFilePointer,               hKernel32, "SetFilePointer");
    GetFuncAddress(f->ReadFile,                     hKernel32, "ReadFile");
    GetFuncAddress(f->CloseHandle,                  hKernel32, "CloseHandle");
    GetFuncAddress(f->GetModuleHandleA,             hKernel32, "GetModuleHandleA");
    GetFuncAddress(f->GetModuleHandleW,             hKernel32, "GetModuleHandleW");
    GetFuncAddress(f->GetModuleHandleExA,           hKernel32, "GetModuleHandleExA");
    GetFuncAddress(f->GetModuleHandleExW,           hKernel32, "GetModuleHandleExW");
    GetFuncAddress(f->GetModuleFileNameA,           hKernel32, "GetModuleFileNameA");
    GetFuncAddress(f->GetModuleFileNameW,           hKernel32, "GetModuleFileNameW");
    GetFuncAddress(f->MultiByteToWideChar,          hKernel32, "MultiByteToWideChar");
    GetFuncAddress(f->GetLastError,                 hKernel32, "GetLastError");
    GetFuncAddress(f->CreateDirectoryA,             hKernel32, "CreateDirectoryA");
    GetFuncAddress(f->CreateDirectoryW,             hKernel32, "CreateDirectoryW");
    GetFuncAddress(f->lstrcpyA,                     hKernel32, "lstrcpyA");
    GetFuncAddress(f->lstrcpyW,                     hKernel32, "lstrcpyW");
    GetFuncAddress(f->lstrlenA,                     hKernel32, "lStrLengthA");
    GetFuncAddress(f->lstrlenW,                     hKernel32, "lstrlenW");
    GetFuncAddress(f->lstrcmpA,                     hKernel32, "lstrcmpA");
    GetFuncAddress(f->lstrcmpW,                     hKernel32, "lstrcmpW");
    GetFuncAddress(f->lstrcmpiA,                    hKernel32, "lstrcmpiA");
    GetFuncAddress(f->lstrcmpiW,                    hKernel32, "lstrcmpiW");
    GetFuncAddress(f->GetProcessHeap,               hKernel32, "GetProcessHeap");
    GetFuncAddress(f->HeapCreate,                   hKernel32, "HeapCreate");
    GetFuncAddress(f->HeapDestroy,                  hKernel32, "HeapDestroy");
    GetFuncAddress(f->HeapAlloc,                    hKernel32, "HeapAlloc");
    GetFuncAddress(f->HeapReAlloc,                  hKernel32, "HeapReAlloc");
    GetFuncAddress(f->HeapFree,                     hKernel32, "HeapFree");
    GetFuncAddress(f->Sleep,                        hKernel32, "Sleep");
    GetFuncAddress(f->InitializeCriticalSection,    hKernel32, "InitializeCriticalSection");
    GetFuncAddress(f->EnterCriticalSection,         hKernel32, "EnterCriticalSection");
    GetFuncAddress(f->LeaveCriticalSection,         hKernel32, "LeaveCriticalSection");
    GetFuncAddress(f->DeleteCriticalSection,        hKernel32, "DeleteCriticalSection");
    GetFuncAddress(f->CreateEventA,                 hKernel32, "CreateEventA");
    GetFuncAddress(f->CreateEventW,                 hKernel32, "CreateEventW");
    GetFuncAddress(f->SetEvent,                     hKernel32, "SetEvent");
    GetFuncAddress(f->ResetEvent,                   hKernel32, "ResetEvent");
    GetFuncAddress(f->WaitForSingleObject,          hKernel32, "WaitForSingleObject");
    GetFuncAddress(f->WaitForSingleObjectEx,        hKernel32, "WaitForSingleObjectEx");
    GetFuncAddress(f->TerminateThread,              hKernel32, "TerminateThread");
//    GetFuncAddress(f->InterlockedIncrement,         hKernel32, "InterlockedIncrement");
//    GetFuncAddress(f->InterlockedDecrement,         hKernel32, "InterlockedDecrement");
//    GetFuncAddress(f->InterlockedExchange,          hKernel32, "InterlockedExchange");
//    GetFuncAddress(f->InterlockedCompareExchange,   hKernel32, "InterlockedCompareExchange");
    GetFuncAddress(f->LoadLibraryW,                 hKernel32, "LoadLibraryW");
    GetFuncAddress(f->LoadLibraryA,                 hKernel32, "LoadLibraryA");
    GetFuncAddress(f->LoadLibraryW,                 hKernel32, "LoadLibraryW");
    GetFuncAddress(f->LoadLibraryExA,               hKernel32, "LoadLibraryExA");
    GetFuncAddress(f->LoadLibraryExW,               hKernel32, "LoadLibraryExW");
    GetFuncAddress(f->FreeLibrary,                  hKernel32, "FreeLibrary");
    GetFuncAddress(f->VirtualProtectEx,             hKernel32, "VirtualProtectEx");
    GetFuncAddress(f->FlushInstructionCache,        hKernel32, "FlushInstructionCache");

    return True;
}

Bool FASTCALL InitFunction(SPianoFunction *f)
{
    if (!InitFunctionBaseKernel32(f) || 
        !InitFunctionBaseGdi32(f, f) || 
#if defined(USE_CACHE)
        !InitFunctionBaseUser32(f, f) ||
#endif
        0 )
    {
        return False;
    }

    HMODULE hUCIDec     = f->LoadStayedLibraryA("ucidec.dll", f);
    HMODULE hUCADec     = f->LoadStayedLibraryA("ucadec.dll", f);
    HMODULE hBASS       = f->LoadStayedLibraryA("bass.dll", f);
    HMODULE hBASSAAC    = f->LoadStayedLibraryA("bass_aac.dll", f);

    // ucidec.dll
    GetFuncAddress(f->UCIDecode,  hUCIDec, "UCIDecode");
    GetFuncAddress(f->UCIFree,    hUCIDec, "UCIFree");

    // ucadec.dll
    GetFuncAddress(f->UCADecode,  hUCADec, "UCADecode");
    GetFuncAddress(f->UCADecode2, hUCADec, "UCADecode2");
    GetFuncAddress(f->UCAFree,    hUCADec, "UCAFree");

    // bass_aac.dll
    GetFuncAddress(f->BASS_MP4_StreamCreateFile,  hBASSAAC, "BASS_MP4_StreamCreateFile");

    // bass.dll
    GetFuncAddress(f->BASS_SetConfig,             hBASS, "BASS_SetConfig");
    GetFuncAddress(f->BASS_ChannelGetLength,      hBASS, "BASS_ChannelGetLength");
    GetFuncAddress(f->BASS_StreamFree,            hBASS, "BASS_StreamFree");
    GetFuncAddress(f->BASS_ChannelBytes2Seconds,  hBASS, "BASS_ChannelBytes2Seconds");
    GetFuncAddress(f->BASS_ChannelSetPosition,    hBASS, "BASS_ChannelSetPosition");
    GetFuncAddress(f->BASS_ChannelGetData,        hBASS, "BASS_ChannelGetData");
    GetFuncAddress(f->BASS_Free,                  hBASS, "BASS_Free");
    GetFuncAddress(f->BASS_ChannelGetInfo,        hBASS, "BASS_ChannelGetInfo");
    GetFuncAddress(f->BASS_ChannelGetPosition,    hBASS, "BASS_ChannelGetPosition");
    GetFuncAddress(f->BASS_Init,                  hBASS, "BASS_Init");
    GetFuncAddress(f->BASS_ChannelPause,          hBASS, "BASS_ChannelPause");
    GetFuncAddress(f->BASS_ChannelPlay,           hBASS, "BASS_ChannelPlay");
    GetFuncAddress(f->BASS_ChannelStop,           hBASS, "BASS_ChannelStop");
    GetFuncAddress(f->BASS_ChannelIsActive,       hBASS, "BASS_ChannelIsActive");
    GetFuncAddress(f->BASS_ErrorGetCode,          hBASS, "BASS_ErrorGetCode");
    GetFuncAddress(f->BASS_ChannelUpdate,         hBASS, "BASS_ChannelUpdate");
    GetFuncAddress(f->BASS_ChannelGetAttribute,   hBASS, "BASS_ChannelGetAttribute");

    GetFuncAddress(f->BASS_ChannelSlideAttribute, hBASS, "BASS_ChannelSlideAttribute");
    GetFuncAddress(f->BASS_ChannelSetAttribute,   hBASS, "BASS_ChannelSetAttribute");
/*
    // vorbisfile.dll
    GetFuncAddress(f->ov_clear,          hVorbisfile, "ov_clear");
    GetFuncAddress(f->ov_open_callbacks, hVorbisfile, "ov_open_callbacks");
    GetFuncAddress(f->ov_test_callbacks, hVorbisfile, "ov_test_callbacks");
    GetFuncAddress(f->ov_pcm_seek,       hVorbisfile, "ov_pcm_seek");
    GetFuncAddress(f->ov_pcm_total,      hVorbisfile, "ov_pcm_total");
    GetFuncAddress(f->ov_read,           hVorbisfile, "ov_read");
    GetFuncAddress(f->ov_time_total,     hVorbisfile, "ov_time_total");
*/
    return True;
}

#if 0

long CDECL my_ov_read(OggVorbis_File *vf, char *buffer, int length,
                      int bigendianp, int word, int sgned, int *bitstream)
{
    if ((Int32)vf->datasource >= 0)
        return MYAPI(ov_read)(vf, buffer, length, bigendianp, word, sgned, bitstream);

    long len;
    CAudioPlayback *ap = (CAudioPlayback *)((Int32)vf->datasource & 0x7FFFFFFF);
    if (ap == NULL)
        return length;
    else if (vf->seekable != VOICE)
    {
        len = ap->GetData(buffer, length);
        if (len == BASS_ERROR_UNKNOWN)
            len = 0;
    }
    else
    {
        if ((Int32)vf->offset >= (Int32)vf->end)
            return 0;

        if (length + (Int32)vf->offset > (Int32)vf->end)
        {
            len = (Int32)vf->end - (Int32)vf->offset;
            len = min(len, length);
        }
        else
            len = length;
        memcpy(buffer, (PChar)ap + vf->offset, len);
        *(PInt32)&vf->offset += len;
    }

    return len;
}

int CDECL my_ov_pcm_seek(OggVorbis_File *vf, ogg_int64_t pos)
{
    if ((Int32)vf->datasource >= 0)
        return MYAPI(ov_pcm_seek)(vf, pos);

    Large_Integer liPos;
    CAudioPlayback *ap = (CAudioPlayback *)((Int32)vf->datasource & 0x7FFFFFFF);

    if (ap == NULL)
        return 0;
    else if (0)
    {
        liPos.QuadPart = pos;
        ap->Seek(&liPos);
    }
    else if (vf->seekable == VOICE)
        *(PInt32)&vf->offset = (Int32)pos;

    return 0;
}

double CDECL my_ov_time_total(OggVorbis_File *vf, int i)
{
    if ((Int32)vf->datasource >= 0)
        return MYAPI(ov_time_total)(vf, i);

    SWaveHeader *h;
    CAudioPlayback *ap = (CAudioPlayback *)((Int32)vf->datasource & 0x7FFFFFFF);

    if (ap == NULL)
        return 0;
    else if (vf->seekable != VOICE)
        return ap->GetTimeTotal();

    h = (SWaveHeader *)ap;
    return (double)h->dwDataSize / h->dwAvgBytesPerSec;
}

int CDECL my_ov_clear(OggVorbis_File *vf)
{
    Int32 v = (Int32)vf->datasource;
    if (v >= 0)
        return MYAPI(ov_clear)(vf);

    CAudioPlayback *ap = (CAudioPlayback *)(v & 0x7FFFFFFF);
    if (ap)
    {
        if (vf->seekable == VOICE)
            MYAPI(UCAFree)(ap);
        else
            delete ap;
        ZeroMemory(vf->vi, sizeof(*vf->vi));
        vf->vi = NULL;
        vf->datasource = NULL;
    }

    return 0;
}

int CDECL my_ov_test_callbacks(void *f, OggVorbis_File *vf, char *initial,
                               long ibytes, ov_callbacks callbacks)
{
    Bool    bRet;
    DWORD   dwRead, header[2];
    HANDLE  hFile;
    PUInt32 p;
    SFileInfo *info;

    p = (PUInt32)f;
    info = (SFileInfo *)p[1];
    hFile = info->hFile;

    bRet = MYAPI(ReadFile)(hFile, header, sizeof(header), &dwRead, NULL);
    if (bRet != False && dwRead == sizeof(header) &&
        ((header[0] & 0xFFFFFF) == TAG3('UCA')) || header[1] == TAG4('ftyp'))
    {
        if ((Int32)vf->datasource < 0)
            my_ov_clear(vf);

        vf->datasource = (LPVoid)(0x80000000);
        return 0;
    }

    MYAPI(SetFilePointer)(hFile, -(Long)dwRead, 0, FILE_CURRENT);

    return MYAPI(ov_test_callbacks)(f,vf,initial,ibytes,callbacks);
}

int CDECL my_ov_open_callbacks(void *f, OggVorbis_File *vf, char *initial,
                               long ibytes, ov_callbacks callbacks)
{
    if ((Int32)vf->datasource >= 0)
        return MYAPI(ov_open_callbacks)(f, vf, initial, ibytes, callbacks);

    PByte   pbBuffer;
    DWORD   dwRead, dwSize;
    HANDLE  hFile, hHeap;
    PUInt32 p;
    Large_Integer li;
    vorbis_info *vi;
    CAudioPlayback *ap;
    SFileInfo *info;
    const BASS_CHANNELINFO *ci;

    p = (PUInt32)f;
    info = (SFileInfo *)p[1];
    hFile = info->hFile;

    hHeap = CMem::GetGlobalHeap();
    dwSize = info->uSize;
    pbBuffer = (PByte)MYAPI(HeapAlloc)(hHeap, 0, dwSize);
    if (pbBuffer == NULL)
        return 0;
    do
    {
        ZeroMemory(&vf->seekable, sizeof(*vf) - sizeof(vf->datasource));
        if (!MYAPI(ReadFile)(hFile,  pbBuffer, dwSize, &dwRead, NULL) || dwRead != dwSize)
            break;

        if ((*(PUInt32)pbBuffer & 0xFFFFFF) == TAG3('UCA'))
        {
            SWaveHeader *h;
            if (MYAPI(UCADecode2)(pbBuffer, dwRead, &vf->datasource, (int *)&vf->end, 44100) < 0)
                break;

            vf->seekable = VOICE;
            h = (SWaveHeader *)vf->datasource;
            *(PInt32)&vf->datasource |= 0x80000000;
            *(PInt32)&vf->offset = sizeof(*h);
            vi = (vorbis_info *)&vf->current_serialno;
            vf->vi = vi;
            vi->channels = h->wChannels;
            vi->rate = h->dwSamplesPerSec;
        }
        else
        {
            ap = new CAudioPlayback;
            if (ap == NULL)
                break;

            li.QuadPart = dwSize;
            if (!ap->Open(pbBuffer, True, &li, True))
            {
                delete ap;
                break;
            }

            vf->datasource = (LPVoid)((Int32)ap | 0x80000000);
            vi = (vorbis_info *)&vf->current_serialno;
            vf->vi = vi;
            ci = ap->GetChannelInfo();
            vi->channels = ci->chans;
            vi->rate = ci->freq;
        }
    } while (0);

    MYAPI(HeapFree)(hHeap, 0, pbBuffer);

    return 0;
}

#endif

size_t CDECL read_func(void *ptr, size_t size, size_t nmemb, void *datasource)
{
    Bool bRet;
    DWORD dwSize;
    PIANO_FILE_INFO *info = (PIANO_FILE_INFO *)datasource;

    dwSize = size * nmemb;
    if (info->dwRead >= info->uSize)
        return 0;
    else if (info->dwRead + dwSize > info->uSize)
        dwSize = info->uSize - info->dwRead;

    bRet = MYAPI(ReadFile)(info->hFile, ptr, dwSize, &dwSize, NULL);
    if (!bRet)
        return 0;

    info->dwRead += dwSize;
    return dwSize / size;
}

int CDECL seek_func(void *datasource, ogg_int64_t offset, int whence)
{
    PIANO_FILE_INFO *info = (PIANO_FILE_INFO *)datasource;
    Long lOffset = (Long)offset;

    switch (whence)
    {
        case FILE_BEGIN:
            lOffset += info->lOffset;
            break;

        case FILE_CURRENT:
            if (lOffset + info->dwRead > info->uSize)
                lOffset = info->uSize;
            break;

        case FILE_END:
            lOffset = info->lOffset + info->uSize + lOffset;
            whence = FILE_BEGIN;
            break;
    }

    lOffset = MYAPI(SetFilePointer)(info->hFile, lOffset, 0, whence);
    if (lOffset == -1 && MYAPI(GetLastError)() != NO_ERROR)
        return -1;
    info->dwRead = lOffset - info->lOffset;
    return 0;
}

long CDECL tell_func(void *datasource)
{
    PIANO_FILE_INFO *info = (PIANO_FILE_INFO *)datasource;
    return MYAPI(SetFilePointer)(info->hFile, 0, 0, FILE_CURRENT) - info->lOffset;
}

UInt32 CDECL GetSeSize(PIANO_FILE_INFO *info)   // game native support wav se only
{
    Bool   bRet;
    DWORD  dwSize, header;
    HANDLE hHeap;
    PByte  pbBuffer;
    SWaveHeader *h;
    OggVorbis_File vf;

    do
    {
        info->dwRead = 0;
        bRet = MYAPI(ReadFile)(info->hFile, &header, sizeof(header), &dwSize, NULL);
        MYAPI(SetFilePointer)(info->hFile, info->lOffset, 0, FILE_BEGIN);
        if (!bRet || dwSize != sizeof(header) || header != TAG4('OggS'))
            break;

        ov_callbacks oc = { read_func, seek_func, 0, tell_func };
        ZeroMemory(&vf, sizeof(vf));
        if (vorbis_func.ov_open_callbacks(info, &vf, NULL, 0, oc))
            break;

        hHeap = CMem::GetGlobalHeap();
        dwSize = (DWORD)vorbis_func.ov_pcm_total(&vf, -1) * vf.vi->channels * 2 + sizeof(*h);  // ogg always 16 bits
        h = (SWaveHeader *)MYAPI(HeapAlloc)(hHeap, 0, dwSize);
        if (h == NULL)
        {
            vorbis_func.ov_clear(&vf);
            break;
        }

        pbBuffer = (PByte)h + sizeof(*h);
        header = dwSize - sizeof(*h);
        while (bRet = vorbis_func.ov_read(&vf, (PChar)pbBuffer, header, 0, 2, 1, NULL))
        {
            header -= bRet;
            pbBuffer += bRet;
        }

        InitWaveHeader(h, vf.vi->channels, vf.vi->rate, 16, dwSize - sizeof(*h));

        info->dwRead = (DWORD)h | 0x80000000;
        return dwSize;

    } while (0);

    return info->uSize;
}

Bool CDECL ReadSe(PIANO_FILE_INFO *info, LPVoid lpBuffer)
{
    Int32 v;
    SWaveHeader *h;

    v = info->dwRead;
    if (v >= 0)
    {
        if (info->hFile == NULL)
            return False;

        return MYAPI(ReadFile)(info->hFile, lpBuffer, info->uSize, &info->dwRead, NULL);
    }

    h = (SWaveHeader *)(v & 0x7FFFFFFF);
    info->dwRead = h->dwSize + 8;
    CopyMemory(lpBuffer, h, info->dwRead);
    MYAPI(HeapFree)(CMem::GetGlobalHeap(), 0, h);

    return True;
}

PByte CDECL DecodeImage(PByte pbImage, PUInt32 puWidth, PUInt32 puHeight, PUInt32 puBitPerPixel)
{
    Int32  uWidth, uHeight, uBpp, uStride, uStrideRaw, Size;
    PByte  pbDecode, pbDest, pbSrc;

#if defined(USE_CACHE)
    Char   szFullPath[MAX_PATH];
    PChar  name, fmt, path, dir;
    SCacheIndex *pCache;

    __asm
    {
        mov name, ebx;
    }
#endif

    do
    {
        if ((*(PUInt32)pbImage & 0xFFFFFF) != TAG3('UCI'))
            break;

#if defined(USE_CACHE)

        __asm
        {
            mov fmt, 0x45B6D8;
            mov path, 0x4EF150;
            mov eax, 0x46335C;
            mov eax, [eax];
            mov dir, eax;
        }

        ++g_UCIReadCount;
        MYAPI(wsprintfA)(szFullPath, fmt, path, dir, name);
        pCache = g_ImageCache.Find(szFullPath);
        if (pCache->pbBuffer && !StrICompareA(pCache->FileName, szFullPath))
        {
            ++g_CacheHitCount;
            pbImage = (PByte)MYAPI(GlobalAlloc)(GPTR, pCache->Size);
            if (pbImage == NULL)
            {
                goto DEFAULT_PROC;
            }

            CopyMemory(pbImage, pCache->pbBuffer, pCache->Size);
            if (puWidth       != NULL) *puWidth = pCache->Width;
            if (puHeight      != NULL) *puHeight = pCache->Height;
            if (puBitPerPixel != NULL) *puBitPerPixel = pCache->BitPerPixel;

            return pbImage;
        }

#endif

        if (MYAPI(UCIDecode)(pbImage, INT_MAX, (LPVoid *)&pbDecode, &uStrideRaw, &uWidth, &uHeight, &uBpp) < 0)
            break;

        Size = uHeight * uWidth * 4;
        pbImage = (PByte)MYAPI(GlobalAlloc)(GPTR, Size);
        if (pbImage == NULL)
        {
        	MYAPI(UCIFree)(pbDecode);
            break;
        }

//        uStride = (uWidth * uBpp / 8 + 3) & ~3;
        pbSrc  = pbDecode;
        pbDest = pbImage;

        if (puWidth)       *puWidth = uWidth;
        if (puHeight)      *puHeight = uHeight;
        if (puBitPerPixel) *puBitPerPixel = uBpp;

        if (uBpp == 32)
        {
            ULONG Stride = uWidth * 4;
            for (ULONG Height = uHeight; Height; --Height)
            {
                CopyMemory(pbDest, pbSrc, Stride);
                pbDest += Stride;
                pbSrc  += uStrideRaw;
            }
        }
        else
        {
            for (Int32 h = uHeight; h--; )
            {
                PByte src = pbSrc;
                for (Int32 w = 0; w != uWidth; ++w)
                {
                    *(PUInt32)pbDest = *(PUInt32)src | 0xFF000000;
                    pbDest += 4;
                    src += 3;
                }
                pbSrc += uStrideRaw;
            }
        }

        MYAPI(UCIFree)(pbDecode);

#if defined(USE_CACHE)
        if (pCache->pbBuffer == NULL)
            ++g_CacheCount;
        g_ImageCache.Add(pCache, pbImage, Size, uWidth, uHeight, uBpp, szFullPath);
#endif

        return pbImage;

    } while (0);

DEFAULT_PROC:

    F_DecodeImage OldDecodeImage = (F_DecodeImage)0x42E120;
    return OldDecodeImage(pbImage, puWidth, puHeight, puBitPerPixel);
}

NoInline Bool IsPureBlack(LPVoid lpBitmapToCmp, UInt32 h, UInt32 stride, UInt32 stride_raw, UInt32 bpp)
{
    PByte pbTempRow, pbTemp, pbInput;

    pbTempRow = (PByte)AllocStack(stride);
    if (bpp == 32)
        memset4(pbTempRow, RGBA(1, 1, 1, 255), stride);
    else if (bpp == 24)
        memset(pbTempRow, 1, stride);
    else
        return False;

    pbTemp = (PByte)lpBitmapToCmp;

    for (Int32 i = h; i; --i, pbTemp += stride_raw)
        if (memcmp(pbTemp, pbTempRow, stride))
            return False;

    return True;
}

HANDLE WINAPI MyCreateFileA(LPSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    WCHAR szFile[MAX_PATH];
    DWORD dwLength;

    dwLength = StrLengthA(lpFileName);
    dwLength = MYAPI(MultiByteToWideChar)(CP_ACP, 0, lpFileName, dwLength + 1, szFile, countof(szFile)) - 1;

    do if ((dwDesiredAccess & GENERIC_WRITE) == 0)
    {
        if (dwLength < 3 ||
            szFile[dwLength - 4] != '.' ||
            (CHAR_UPPER3W(*(PULONG64)(&szFile[dwLength - 3]))) != TAG3W('DAT'))
        {
            break;
        }

        if (MYAPI(GetFileAttributesW)(szFile) != -1)
            break;

        dwLength -= 4;
        *(PULONG64)(szFile + dwLength) = TAG4W('_sc.');
        *(PULONG64)(szFile + dwLength + 4) = TAG3W('dat');

    } while (0);

    return MYAPI(CreateFileW)(szFile, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HFONT WINAPI MyCreateFontIndirectA(LOGFONTA *lplf)
{
    Char *szFaceName;

    switch (lplf->lfPitchAndFamily >> 4)
    {
        case FF_MODERN >> 4:
            szFaceName = "黑体";
            break;

        case FF_ROMAN >> 4:
            szFaceName = "楷体";
            break;
    }

    lplf->lfCharSet = GB2312_CHARSET;
    MYAPI(lstrcpyA)(lplf->lfFaceName, szFaceName);
    return MYAPI(CreateFontIndirectA)(lplf);
}

DWORD WINAPI MyGetGlyphOutlineA(HDC hDC, UINT uChar, UINT uFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpvBuffer, CONST MAT2 *lpmat2)
{
    CHAR cHighByte;
    UINT CodePage, wChar;
    HFONT hFont = NULL;
    DWORD dwIndex;
    TEXTMETRICW tm;

    do
    {
        uChar &= 0xFFFF;
        cHighByte = HIBYTE(uChar);
        CodePage = 936;

        if (cHighByte < 0)
        {
            if (IsShiftJISChar(uChar))
            {
                MYAPI(GetTextMetricsW)(hDC, &tm);
                dwIndex = tm.tmHeight > 10;
                CodePage = 932;
//                hFont = g_hFontJP[dwIndex];
                if (hFont)
                    hFont = (HFONT)MYAPI(SelectObject)(hDC, hFont);
            }
            uChar = HIBYTE(uChar)|(LOBYTE(uChar) << 8);
        }

        MYAPI(MultiByteToWideChar)(CodePage, 0, (LPCSTR)&uChar, 2, (LPWSTR)&wChar, 1);

    } while (0);

    CodePage = MYAPI(GetGlyphOutlineW)(hDC, wChar, uFormat, lpgm, cbBuffer, lpvBuffer, lpmat2);
/*
    if (hFont)
    {
        SelectObject(hDC, hFont);
    }
*/
    return CodePage;
}

Int32 WINAPI MylstrcmpA(LPCSTR lpString1, LPCSTR lpString2)
{
    return MylstrcmpiA(lpString1, lpString2);
}

Int32 WINAPI MylstrcmpiA(LPCSTR lpString1, LPCSTR lpString2)
{
    Int32  ret, bOgg;
    UInt32 Length, tag;
    Char   szFileName[MAX_PATH];

    ret = StrICompareA(lpString1, lpString2);
    if (!ret)
        return ret;

    Length = StrLengthA(lpString2);
    if (Length < 4 && Length != StrLengthA(lpString1))
        return ret;

    bOgg = False;
    Length -= 3;
    switch ((*(PUInt32)&lpString2[Length] & 0xDFDFDF))
    {
        case TAG3('EPA'):
            tag = TAG3('uci');
            break;

        case TAG3('OGG'):
            bOgg = True;
            tag = TAG3('m4a');
            break;

        case TAG3('WAV'):
            tag = TAG3('ogg');
            break;

        default:
            return ret;
    }

    MYAPI(lstrcpyA)(szFileName, lpString2);
    *(PUInt32)&szFileName[Length] = tag;

    ret = StrICompareA(lpString1, szFileName);
    if (ret && bOgg)
    {
        *(PUInt32)&szFileName[Length] = TAG3('uca');
        ret = StrICompareA(lpString1, szFileName);
    }

    return ret;
}

BOOL WINAPI MyGetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
    LONG Result = MYAPI(GetMessageA)(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);

    if (Result <= 0)
        return Result;

    switch (lpMsg->message)
    {
    case WM_KEYDOWN:
        switch (lpMsg->wParam)
        {
            case VK_ESCAPE:
                lpMsg->message = WM_RBUTTONUP;
                lpMsg->wParam = 0;
                lpMsg->lParam = 0;
                break;

            case VK_F4:
                if (MYAPI(GetKeyState)(VK_MENU) < 0)
                    lpMsg->wParam = VK_ESCAPE;
                break;

            case VK_PRIOR:
            case VK_NEXT:
                lpMsg->message = WM_MOUSEWHEEL;
                lpMsg->wParam  = MAKEWPARAM(0, lpMsg->wParam == VK_PRIOR ? WHEEL_DELTA : -WHEEL_DELTA);
                lpMsg->lParam  = 0;
                break;

#if defined(USE_CACHE)
        case VK_DELETE:
            if (MYAPI(MessageBoxW)(lpMsg->hwnd, L"确定要清空所有CG缓存吗?", NULL, MB_OKCANCEL|MB_ICONASTERISK) == IDOK)
            {
                g_ImageCache.Clear();
                g_UCIReadCount  = 0;
                g_CacheCount    = 0;
                g_CacheHitCount = 0;
            }
            break;

        case VK_HOME:
            {
                WCHAR szBuffer[200];
                DWORD dwCacheSize;

                dwCacheSize = g_ImageCache.GetTotalSpace() / 1024 / 1024;

                MYAPI(wsprintfW)(
                    szBuffer,
                    L"Cache总数量: %u\n"
                    L"当前cache数: %u\n"
                    L"读取UCI次数: %u\n"
                    L"命中cache数: %u\n"
                    L"cache命中率: %u%%\n"
                    L"cache总大小: %u MB\n",
                    g_ImageCache.GetMaxCacheCount(), g_CacheCount,
                    g_UCIReadCount, g_CacheHitCount,
                    g_UCIReadCount ? g_CacheHitCount * 100 / g_UCIReadCount : 0,
                    dwCacheSize
                );

                MYAPI(MessageBoxW)(lpMsg->hwnd, szBuffer, NULL, 64);
        }
        break;
#endif
        }
        break;
    }

    return Result;
}

HANDLE WINAPI MyCreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName)
{
    Init();
    return MYAPI(CreateMutexA)(lpMutexAttributes, bInitialOwner, lpName);
}

FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    static HMODULE hModuleKernel32;

    if (hModuleKernel32 == NULL)
    {
        Init();
        hModuleKernel32 = GetKernel32Handle();
    }

    if ((ULONG_PTR)lpProcName & 0xFFFF0000)
    {
        switch (HashAPI(lpProcName))
        {
            case 0xB231F005: return (FARPROC)MyCreateFileA;
#if defined(USE_CACHE)
//            case 0xFFADBAB0: return (FARPROC)MyPeekMessageA;
            case 0xFF85A538: return (FARPROC)MyGetMessageA;
#endif
            case 0xA1A757F2: return (FARPROC)MyGetGlyphOutlineA;
            case 0xC8E4BFAB: return (FARPROC)MyCreateFontIndirectA;
#if defined(NULL_IAT)
            case 0xD424F9FF: return (FARPROC)GetFunctionAddress;
#endif
//            case 0xD332F12B:
//            case 0x5E207A27: return (FARPROC)MylstrcmpiA;
            case 0x91E7D989: return (FARPROC)my_ov_read;
            case 0x1F24078F: return (FARPROC)my_ov_pcm_seek;
            case 0x41EE3F2A: return (FARPROC)my_ov_time_total;
            case 0xEA2196CE: return (FARPROC)my_ov_clear;
            case 0xCE40594F: return (FARPROC)my_ov_test_callbacks;
            case 0x9E4B6F26: return (FARPROC)my_ov_open_callbacks;
        }
    }

    if (hModule == (HMODULE)&__ImageBase)
        hModule = hModuleKernel32;

#if defined(NULL_IAT)
    return GetFunctionAddress(hModule, lpProcName);
#else
    return GetProcAddress(hModule, lpProcName);
#endif
}

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    Char buf[200];

    if (ExceptionInfo->ExceptionRecord->ExceptionCode == 0x40010006)
        return EXCEPTION_CONTINUE_SEARCH;

    wsprintfA(
        buf,
        "code = %X\n"
        "addr = %p\n",
        ExceptionInfo->ExceptionRecord->ExceptionCode,
        ExceptionInfo->ExceptionRecord->ExceptionAddress);
    MessageBoxA(0, buf, 0, 64);
    return EXCEPTION_CONTINUE_SEARCH;
}

Void Init()
{
#if defined(NULL_IAT)
    if (!InitFunction(&g_func))
        DebugException();
#endif

    CMem::CreateGlobalHeap();
//    AddVectoredExceptionHandler(True, VectoredHandler);

    INTEL_STATIC SPatch p[] =
    {
        { 0xB8,          1, 0x3B98C },   // 验证
//        { 0x24EB,        2, 0x4B14F },   // 边界
//        { 0xD5EB,        2, 0x4B17E },   // 边界
        { 0xEB,          1, 0x4B14F },   // 边界
        { 0xEB,          1, 0x4B17E },   // 边界
        { 0xEB,          1, 0x483D1 },   // 边界
        { 0xEB,          1, 0x4AADA },   // 边界
        { 0xEB,          1, 0x4AB12 },   // 边界
        { SWAP2('【'),   4, 0x49C7B },
        { SWAP2('【'),   4, 0x49CA0 },
        { SWAP2('】'),   4, 0x49EF6 },
        { SWAP2('】'),   4, 0x49F1B },

#if defined (MY_DEBUG)
        { (UInt32)MyCreateFontIndirectA, 4, 0x5B044 },
        { (UInt32)MyGetGlyphOutlineA,    4, 0x5B04C },
#endif
    };

    INTEL_STATIC SFuncPatch f[] =
    {
        { CALL, 0x2F2E1, DecodeImage,   0x00 },
        { CALL, 0x23EAA, MylstrcmpiA,   0x01 },
//        { CALL, 0x2F065, MylstrcmpA,    0x01 },
        { CALL, 0x43904, GetSeSize,     0x00 },
        { CALL, 0x4392D, ReadSe,        0x00 },
    };

    WChar szPath[MAX_PATH];
    DWORD i;
#if defined (MY_DEBUG)
    PatchMemory(p, countof(p), f, countof(f), MYAPI(GetModuleHandleW)(0));
#else
    PatchMemoryNoVP(p, countof(p), f, countof(f), MYAPI(GetModuleHandleW)(0));
#endif

#if defined(NULL_IAT)
    HMODULE hVorbisfile = g_func.LoadStayedLibraryA("vorbisfile.dll", &g_func);
#else
    HMODULE hVorbisfile = LoadLibraryExW(L"vorbisfile.dll", NULL, 0);
#endif

    GetFuncAddress(vorbis_func.ov_clear,          hVorbisfile, "ov_clear");
    GetFuncAddress(vorbis_func.ov_open_callbacks, hVorbisfile, "ov_open_callbacks");
    GetFuncAddress(vorbis_func.ov_test_callbacks, hVorbisfile, "ov_test_callbacks");
    GetFuncAddress(vorbis_func.ov_pcm_seek,       hVorbisfile, "ov_pcm_seek");
    GetFuncAddress(vorbis_func.ov_pcm_total,      hVorbisfile, "ov_pcm_total");
    GetFuncAddress(vorbis_func.ov_read,           hVorbisfile, "ov_read");
    GetFuncAddress(vorbis_func.ov_time_total,     hVorbisfile, "ov_time_total");

    i = MYAPI(GetModuleFileNameW)(NULL, szPath, countof(szPath));
    while (szPath[--i] != '\\');
    ++i;
    *(PULONG64)&szPath[i] = TAG4W('save');
    szPath[i + 4] = 0;
    MYAPI(CreateDirectoryW)(szPath, NULL);

#if defined(USE_CACHE)
    g_ImageCache.Init();
#endif
}
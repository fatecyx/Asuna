#ifndef _PIANO_H_
#define _PIANO_H_

#define NULL_IAT

#if defined(NULL_IAT)
#undef API
#undef MYAPI
#define API(funcname) (g_func.funcname)
#define MYAPI API
#endif

#include <Windows.h>
#include "bass/bass_aac.h"

#include "crt_h.h"
#include "nt_api.h"

struct SFunctionBASSAAC
{
    // bass_aac.dll
    HSTREAM (BASSAACDEF(*BASS_MP4_StreamCreateFile))(BOOL mem, const void *file, QWORD offset, QWORD length, DWORD flags);
};

struct SFunctionBASS
{
    // bass.dll
    BOOL    (BASSDEF(*BASS_SetConfig))(DWORD option, DWORD value);
    QWORD   (BASSDEF(*BASS_ChannelGetLength))(DWORD handle, DWORD mode);
    BOOL    (BASSDEF(*BASS_StreamFree))(HSTREAM handle);
    double  (BASSDEF(*BASS_ChannelBytes2Seconds))(DWORD handle, QWORD pos);
    BOOL    (BASSDEF(*BASS_ChannelSetPosition))(DWORD handle, QWORD pos, DWORD mode);
    DWORD   (BASSDEF(*BASS_ChannelGetData))(DWORD handle, void *buffer, DWORD length);
    BOOL    (BASSDEF(*BASS_Free))();
    BOOL    (BASSDEF(*BASS_ChannelGetInfo))(DWORD handle, BASS_CHANNELINFO *info);
    QWORD   (BASSDEF(*BASS_ChannelGetPosition))(DWORD handle, DWORD mode);
    BOOL    (BASSDEF(*BASS_Init))(int device, DWORD freq, DWORD flags, HWND win, const GUID *dsguid);
    BOOL    (BASSDEF(*BASS_ChannelPause))(DWORD handle);
    BOOL    (BASSDEF(*BASS_ChannelPlay))(DWORD handle, BOOL restart);
    BOOL    (BASSDEF(*BASS_ChannelStop))(DWORD handle);
    DWORD   (BASSDEF(*BASS_ChannelIsActive))(DWORD handle);
    int     (BASSDEF(*BASS_ErrorGetCode))();
    BOOL    (BASSDEF(*BASS_ChannelUpdate))(DWORD handle, DWORD length);
    BOOL    (BASSDEF(*BASS_ChannelGetAttribute))(DWORD handle, DWORD attrib, float *value);
    BOOL    (BASSDEF(*BASS_ChannelSlideAttribute))(DWORD handle, DWORD attrib, float value, DWORD time);
    BOOL    (BASSDEF(*BASS_ChannelSetAttribute))(DWORD handle, DWORD attrib, float value);
};
/*
struct SFunctionvorbisfile
{
    // vorbisfile.dll
    int (__cdecl *ov_clear)(OggVorbis_File *vf);
    int (__cdecl *ov_open_callbacks)(void *datasource, OggVorbis_File *vf, char *initial, long ibytes, ov_callbacks callbacks);
    int (__cdecl *ov_test_callbacks)(void *datasource, OggVorbis_File *vf, char *initial, long ibytes, ov_callbacks callbacks);
    int (__cdecl *ov_pcm_seek)(OggVorbis_File *vf,ogg_int64_t pos);
    ogg_int64_t (__cdecl *ov_pcm_total)(OggVorbis_File *vf,int i);
    long (__cdecl *ov_read)(OggVorbis_File *vf,char *buffer,int length, int bigendianp,int word,int sgned,int *bitstream);
    double (__cdecl *ov_time_total)(OggVorbis_File *vf,int i);
};
*/
struct SPianoFunction : 
    public SFunctionBaseKernel32, 
    public SFunctionBaseUser32, 
    public SFunctionBaseGdi32, 
//    public SFunctionvorbisfile, 
    public SFunctionBASS, 
    public SFunctionBASSAAC, 
    public SFunctionUCI
{};

extern SPianoFunction g_func;

#include "my_headers.h"
#include "gal_common.h"

typedef struct
{
    Bool   b;
    HANDLE hFile;
    Long   lOffset;
    UInt32 uSize;
    UInt32 unk;
    DWORD  dwRead;
} PIANO_FILE_INFO;

typedef PByte (CDECL *F_DecodeImage)(PByte pbImage, PUInt32 puWidth, PUInt32 puHeight, PUInt32 puBitPerPixel);

Void Init();

UInt32 CDECL  GetSeSize(PIANO_FILE_INFO *info);
Bool   CDECL  ReadSe(PIANO_FILE_INFO *info, LPVoid lpBuffer);
Void   WINAPI FreeSound();
bool   WINAPI GamePlaySound(LPCSTR lpFileName);
Void   WINAPI GameStopSound();
Void   WINAPI SetBGMVolume(Long Volume);
bool   WINAPI InitLoopSrc(THIS_ LPCSTR lpFullPath, LPCSTR lpPackFile);
PByte  CDECL  DecodeImage(PByte pbImage, PUInt32 puWidth, PUInt32 puHeight, PUInt32 puBitPerPixel);

Int32  WINAPI MylstrcmpiA(LPCSTR lpString1, LPCSTR lpString2);
HFONT  WINAPI MyCreateFontIndirectA(LOGFONTA *lplf);
DWORD  WINAPI MyGetGlyphOutlineA(HDC hDC, UINT uChar, UINT uFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpvBuffer, CONST MAT2 *lpmat2);
HANDLE WINAPI MyCreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName);

#endif /* _PIANO_H_ */
#ifndef _EDEN_H_
#define _EDEN_H_

#include <Windows.h>
#include <Shlwapi.h>
#include <dsound.h>
#include "my_headers.h"
#include "libvorbis/vorbisfile.h"
#include "AudioPlayback.h"

#pragma pack(1)

typedef struct
{
    DWORD dwWidth;
    DWORD dwHeight;
    DWORD dwBitsPerPixel;
    DWORD dwBytesPerPixel;
    DWORD unknown;
    DWORD dwImageSize;
    DWORD unknown2;
    DWORD dwAllocSize;
    PByte pbBuffer;
} unname;

typedef struct
{
    USHORT unknown1;    // always == 0x100 ?
    USHORT usEntryCount;
    DWORD  unknown2;
} SANIHeader;

typedef struct
{
//  CHAR szName[];
    WORD wWidth;
    WORD wHeight;
    WORD wBPP;
    WORD wOffsetX;
    WORD wOffsetY;
} SANIEntry;

typedef struct
{
    Char unknown[0x570];
    vorbis_info vi;
} abcd;

typedef struct
{
    Bool   bInit;
    UInt32 Key;
} SDynamicKey;

typedef struct
{
    DWORD dwAllocteType;    // 1 = malloc 2 = HeapAlloc
    DWORD dwBufferSize;
    PByte pbBuffer;
    DWORD unknown;
} SMinoriMemory;

typedef struct
{
    LPVoid reserve;
    PChar  pszString;
    UInt32 Length;
    UInt32 MaxLength;
} SMinoriString;

typedef struct
{
    LPVoid unknown[5];
    LPVoid Read;
    LPVoid unknown2[4];
    LPVoid GetSize;
} SEfFirstMemoryStreamVirtualTable;

typedef struct
{
    SEfFirstMemoryStreamVirtualTable *VirtualTable;
    DUMMY_STRUCT(0x20);
#if defined(EF_LATTER)
    DUMMY_STRUCT(0x10);
#endif
    UInt           Size;            // 0x24   
    UInt           Position;        // 0x28
    SMinoriMemory *MemoryBuffer;    // 0x2C
} SEfFirstMemoryStream;

typedef struct
{
    LPVoid lpUnknown;
    IDirectSoundBuffer *pDSBuffer;
    DUMMY_STRUCT(0xC);
    bool bWhatIsThis;                   // 0x14
    DUMMY_STRUCT(3);
    DUMMY_STRUCT(0x10);
#if defined(EF_LATTER)
    DUMMY_STRUCT(4);
#endif
    Int  IntUnknown;                    // 0x28( + 4)
    DUMMY_STRUCT(0x24);                 // 0x2C( + 4)
    Long  IntUnknown1;                  // 0x50( + 4)
    Long  IntUnknown2;                  // 0x54( + 4)
    DUMMY_STRUCT(0x1C);                 // 0x58( + 4)
    Long  IntUnknown3;                  // 0x74( + 4)
} SEfFirstDirectSound;

typedef struct
{
    HANDLE hThreadCurrent;
    SEfFirstDirectSound *DirectSoundObject;
    DUMMY_STRUCT(4);
    PChar pszSoundName;
    DUMMY_STRUCT(8);
    UInt SampleRateInitial;
    DUMMY_STRUCT(0xC);
    SEfFirstMemoryStream *pStreamPrimary;       // 0x28
    SEfFirstMemoryStream *pStreamSecondary;     // 0x2C
    DUMMY_STRUCT(4);                    // 0x30
    bool bStopped;                      // 0x34
    DUMMY_STRUCT(3);
    Long IsPlaying;                     // 0x38
    Long ErrorCode;                     // 0x3C
    bool bForceStop;                    // 0x40
    bool bFadeOut;                      // 0x41
    DUMMY_STRUCT(2);                    // 0x42
    Bool fWhat;                         // 0x44
    DUMMY_STRUCT(8);                    // 0x48
    Bool fInit;                         // 0x50
    DUMMY_STRUCT(8);                    // 0x54
    Long   BufferLength;                // 0x5C
    Long   Channels;                    // 0x60
    Long   SampleRate;                  // 0x64
    Long   AlwaysEqu16;                 // 0x68
    Byte   ogg_sync_state[0x1C];        // 0x6C
    Byte   ogg_stream_state[0x168];     // 0x88
    Byte   ogg_page[0x10];              // 0x1F0
    Byte   ogg_packet[0x10];            // 0x200
    Byte   vorbis_info[0x30];           // 0x220
    Byte   vorbis_comment[0x10];        // 0x240
    Byte   vorbis_dsp_state[0x70];      // 0x250
    Byte   vorbis_block[0x70];          // 0x2C0
    LPVoid lpWaveBuffer;                // 0x330
    ULong  BufferOffset;                // 0x334
    PLong  pLongUnknown;                // 0x338
} SEfFirstVorbisPlayer;

typedef struct
{
    PChar NameShiftJIS;
    PChar NameJPInGB;
    PChar NameCN;
} SCharNameMap;

typedef struct
{
    UInt32 HashShiftJIS;
    UInt32 HashJPInGB;
    UInt32 HashCN;
} SCharNameHashMap;

#pragma pack()

Void Init();

typedef Bool (CDECL  *F_DecodePng)(LPVOID lpThis, LPVOID lpThis2, DWORD dwVal);
typedef Bool (WINAPI *F_AllocateMemoryForImage)(DWORD dwWidth, DWORD dwHeight, DWORD dwBpp);
typedef SMinoriMemory* (WINAPI *F_AllocMemory)(DWORD dwSize, DWORD dwAllocateType);
typedef Void (WINAPI *F_FreeMemory)();
typedef LONG (CDECL *F_GetVolume)(LONG lVolume);

// libvorbis

typedef int  (CDECL *F_ov_clear)(OggVorbis_File *vf);
typedef int  (CDECL *F_ov_open_callbacks)(void *datasource, OggVorbis_File *vf, char *initial, long ibytes, ov_callbacks callbacks);
typedef int  (CDECL *F_ov_pcm_seek)(OggVorbis_File *vf,ogg_int64_t pos);
typedef int  (CDECL *F_ov_pcm_seek_lap)(OggVorbis_File *vf,ogg_int64_t pos);
typedef long (CDECL *F_ov_read)(OggVorbis_File *vf,char *buffer,int length, int bigendianp,int word,int sgned,int *bitstream);
typedef bool (CDECL *F_get_vorbis_info)(SEfFirstMemoryStream *pStream, vorbis_info *vi);

DWORD   WINAPI MyGetGlyphOutlineA(HDC hDC, UINT uChar, UINT uFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpvBuffer, CONST MAT2 *lpmat2);
LSTATUS WINAPI MyRegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
LSTATUS WINAPI MyRegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
LSTATUS WINAPI MyRegCloseKey(HKEY hKey);
HRESULT WINAPI MySHGetPathFromIDListA(PCIDLIST_ABSOLUTE pidl, LPTSTR pszPath);
HANDLE  WINAPI MyCreateFileA(LPSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

Bool    CDECL   DecodePng(LPVOID lpThis, LPVOID lpThis2, DWORD dwVal);
bool    CDECL   OldDecodePng(LPVOID lpThis, LPVOID lpThis2, DWORD dwVal);
LPVOID  STDCALL AllocateImage(LPVOID lpThis, DWORD dwWidth, DWORD dwHeight);

Bool    FASTCALL ReadFileFromPaz(LPVoid lpThis, Int, LPSTR lpFileName);
bool    FASTCALL OldReadFileFromPaz(LPVoid lpThis, Int, LPSTR lpFileName);
Bool    ConvertUNIToANI(LPVOID lpThis, LPSTR lpFileName);

bool FASTCALL OldPlayGameSound(LPVoid This);
bool CDECL OldDecodePng(LPVOID lpThis, LPVOID lpThis2, DWORD dwVal);

Bool    WINAPI PlayVoice(LPVOID lpThis);

Void    WINAPI FixGlyphAlpha();
DWORD   WINAPI DynamicReadMask();

Void    WINAPI StopBGMBeforeChange();
Void    WINAPI StopBGMBeforeReturn();
Void    WINAPI StopBGMBeforeConfig();

Void    WINAPI StopVoiceBeforeNext();
Void    WINAPI FixWaitForVoiceStop();
Void    WINAPI AutoModeWaitForVoice();

LRESULT FASTCALL CompareCharNameEfFirst(SMinoriString *pNameInScript, Int, LPVoid, UInt32 LenInScript, PChar pszNameInANI, UInt32 LenInANI);
LRESULT FASTCALL CompareCharName(SMinoriString *pNameInScript, Int, SMinoriString *pNameInANI);

Void    WINAPI RederChar(int x, int y, int, int, PByte pbBuffer, Bool);

Void    WINAPI OnAccelerateKey(DWORD dwID);


#define szMutex      STRTOULONG("minori eden_sc for Windows")
#define szFont       (DWORD)g_szDefFaceName
#define szSaveFolder (DWORD)&"save_sc\\"
#define szGameName   (DWORD)&""

#endif /* _EDEN_H_ */
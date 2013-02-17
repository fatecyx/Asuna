#ifndef _EF_H_
#define _EF_H_

#include <Windows.h>
#include "my_common.h"
#include "crt_h.h"

#pragma pack(1)

typedef struct 
{
    UCHAR unknown[0x20];
    DWORD dwEntrySize;
} TPAZHeader;

typedef struct
{
//  CHAR   szName[];
    LONG64 l64Offset;
    DWORD  dwCompSize;
    DWORD  dwUncompSize;
    DWORD  dwDecryptSize;
    USHORT usFlags;
    USHORT reserved;
} TPAZEntry;

typedef struct
{
    LPSTR lpFileName;
    BYTE  IndexKey[0x20];
    BYTE  DataKey[0x20];
} TKeyInfo;

typedef struct
{
    CHAR *png;
    CHAR *ogg;
    CHAR *scr;
    CHAR *avi; 
} TCrudInfo;

typedef struct
{
    TCrudInfo CrudInfo;
    TKeyInfo  key[17];   // 最多32个封包
} TGameInfo;

typedef struct  
{
    USHORT unknown1;    // always == 0x100 ?
    USHORT usEntryCount;
    DWORD  unknown2;
} TANIHeader;

typedef struct
{
//  CHAR szName[];
    WORD wWidth;
    WORD wHeight;
    WORD wBPP;
    WORD wOffsetX;
    WORD wOffsetY;
} TANIEntry;

typedef struct
{
    CHAR szName[MAX_PATH];
    WORD wWidth;
    WORD wHeight;
    WORD wBPP;
    WORD wOffsetX;
    WORD wOffsetY;
} TMyANIEntry;

#pragma pack()

extern TGameInfo GameInfo[];

BOOL CALLBACK HandlerRoutine(DWORD dwCtrlType);
BOOL   WINAPI IsAudio(LPCSTR lpFileName);
BOOL   WINAPI IsMovie(LPCSTR lpFileName);
LPCSTR WINAPI GetCrud(LPCSTR lpExt, TGameInfo *pGameInfo);
DWORD  WINAPI GetKeyIndex(LPCSTR lpFileName, TGameInfo *pGameInfo);
VOID   WINAPI Decrypt(PBYTE pbSeed, DWORD dwSeedLength, PBYTE pbBuffer, DWORD dwSize);
void   WINAPI DecryptMovie(const PBYTE pbMovieSeed, const PBYTE pbSeed, DWORD dwSeedLength, PBYTE pbBuffer, DWORD dwBufferSize);
DWORD  WINAPI ReadDecrypt(FILE *fp, DWORD dwKey, LPVOID lpBuffer, DWORD dwSize);
VOID   WINAPI InitRC4Table(PBYTE pbRC4Table, const PBYTE key);
VOID   WINAPI GenerateBlock(PBYTE pbBlock, DWORD dwBlockSize, PBYTE pbRC4Key, DWORD dwKeySize);

#endif /* _EF_H_ */
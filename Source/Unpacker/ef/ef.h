#ifndef _EF_H_
#define _EF_H_

#include "MyLibraryUser.h"

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
    Bool   bIsComp;
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

#pragma pack()

extern TGameInfo GameInfo[];

Bool   CALLBACK HandlerRoutine(DWORD dwCtrlType);
Bool   WINAPI IsAudio(LPCSTR lpFileName);
Bool   WINAPI IsMovie(LPCSTR lpFileName);
LPSTR  WINAPI GetCrud(LPCSTR lpExt, TGameInfo *pGameInfo);
DWORD  WINAPI GetKeyIndex(LPSTR lpFileName, TGameInfo *pGameInfo);
Void   WINAPI Decrypt(PBYTE pbSeed, DWORD dwSeedLength, PBYTE pbBuffer, DWORD dwSize);
void   WINAPI DecryptMovie(PBYTE pbMovieSeed, const PBYTE pbSeed, DWORD dwSeedLength, PBYTE pbBuffer, DWORD dwBufferSize);
DWORD  WINAPI ReadDecrypt(FILE *fp, DWORD dwKey, LPVOID lpBuffer, DWORD dwSize);
Void   WINAPI InitRC4Table(PBYTE pbRC4Table, const PBYTE key);
Void   WINAPI InitDict(PBYTE pbBlock, DWORD dwBlockSize, PBYTE pbRC4Key, DWORD dwKeySize);

#endif /* _EF_H_ */
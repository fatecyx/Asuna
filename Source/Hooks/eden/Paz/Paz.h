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
    Bool   bIsComp;
} TPAZEntry;

typedef struct 
{
    CHAR   szName[MAX_PATH];
    LONG64 l64Offset;
    DWORD  dwCompSize;
    DWORD  dwUncompSize;
    DWORD  dwDecryptSize;
    Bool   bIsComp;
} TMyPAZEntry;

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

#pragma pack()

enum PAZTYPE
{
    NONE = -1,
    SCR  , BGM , BG  , ST  , SYS  , VOICE  , SE  , MOV,
    PMSCR, PMBGM,PMBG, PMST, PMSYS, PMVOICE, PMSE, PMMOV
};

extern TGameInfo GameInfo[];

PAZTYPE WINAPI GetPazTypeFromFileName(LPSTR lpFileName);
DWORD   WINAPI GenerateEntry(TMyPAZEntry **ppMyPAZEntry);
Void    WINAPI WriteEntry(HANDLE hFile, TMyPAZEntry *pEntry, DWORD dwCount, Bool bEncrypt);
Bool    WINAPI WriteFileToPaz(HANDLE hFile, TMyPAZEntry *pEntry, DWORD dwCount, PAZTYPE PazType);
DWORD   WINAPI Encrypt(PBYTE pbBuffer, TMyPAZEntry *pEntry);
Bool  CALLBACK HandlerRoutine(DWORD dwCtrlType);
Bool    WINAPI IsAudio(LPCSTR lpFileName);
Bool    WINAPI IsMovie(LPCSTR lpFileName);
LPCSTR  WINAPI GetCrud(LPCSTR lpExt, TGameInfo *pGameInfo);
DWORD   WINAPI GetKeyIndex(LPSTR lpFileName, TGameInfo *pGameInfo);
Void    WINAPI Xor(PBYTE pbBuffer, DWORD dwSize);
Void    WINAPI Decrypt(PBYTE pbSeed, DWORD dwSeedLength, PBYTE pbBuffer, DWORD dwSize);
void    WINAPI DecryptMovie(const PBYTE pbMovieSeed, const PBYTE pbSeed, DWORD dwSeedLength, PBYTE pbBuffer, DWORD dwBufferSize);
DWORD   WINAPI ReadDecrypt(FILE *fp, DWORD dwKey, LPVOID lpBuffer, DWORD dwSize);
Void    WINAPI InitRC4Table(PBYTE pbRC4Table, const PBYTE key);
Void    WINAPI GenerateBlock(PBYTE pbBlock, DWORD dwBlockSize, PBYTE pbRC4Key, DWORD dwKeySize);

#endif /* _EF_H_ */
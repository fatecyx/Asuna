#ifndef _FATE_H_
#define _FATE_H_

#include "my_common.h"
#include "BASS/bass.h"
#include "BASS/BASS_AAC.h"

//    00 I N
//    ~T T T
//     | | +-- N : Normal,  M : Multi-picture
//     | +---- I : Import filter, X : Export filter, A : Archive extractor
//     +------ Virsion No.
//   00 是版本， A 表示多文件档， M 表示多个图形。

#pragma pack(push, 1)

typedef struct
{
    DWORD dwTag;
    DWORD dwIndexOffset;
    DWORD dwIndexSize;
    DWORD dwFileNumber;
} TUCXPHeader;

typedef struct
{
    CHAR  cTag[3];
    BYTE  byOpt;
    DWORD dwStreamLength; // header isn't included
} TUCAHeader;

typedef struct
{
    HSTREAM hStream;
    PBYTE   outBuffer;
    DWORD   dwDataSize;
} TAACDecodeParam;

#pragma pack(pop)

enum FILE_TYPE { UCA, UCI, AAC, M4A, UNKNOWN };

DWORD WINAPI AACDecodeThread(LPVOID lpParam);
extc int WINAPI UCADecode(const void *src, int srclen, void** dst, int* dstlen);
extc int WINAPI UCAFree(void* p);
extc int WINAPI UCIDecode(const void *src, int srclen, void** dst, int* stride, int* w, int* h, int* b);
extc int WINAPI UCIFree(void* p);

//#define IsUCA(p) (BOOL)(memcmp((p), "UCA", 3) == 0)
//#define IsUCI(p) (BOOL)(memcmp((p), "UCI", 3) == 0)
#define IsUCA(p) (BOOL)(*(PBYTE)(p) == 'U' && *(PBYTE)((p) + 1) == 'C' && *(PBYTE)((p) + 2) == 'I')
#define IsUCI(p) (BOOL)(*(PBYTE)(p) == 'U' && *(PBYTE)((p) + 1) == 'C' && *(PBYTE)((p) + 2) == 'A')
#define IsAAC(p) (BOOL)(*(LPWORD)(p) == 0xF1FF)
#define IsM4A(p) (BOOL)(*(LPDWORD)((p) + 4) == 'pytf')

FORCEINLINE FILE_TYPE CheckFileType(PBYTE pbFile)
{
    if (*pbFile == 'U' && *(pbFile + 1) == 'C')
    {
        if (*(pbFile + 2) == 'I') return UCI;
        else if (*(pbFile + 2) == 'A') return UCA;
        else return UNKNOWN;
    }
    else if (IsAAC(pbFile)) return AAC;
    else if (IsM4A(pbFile)) return M4A;
    else return UNKNOWN;
}

#ifdef Fate_EXPORTS

VOID  WINAPI RenderAWord();
VOID  WINAPI ChangeFont(HWND hWnd);
BOOL  WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
int   WINAPI LZMADecode(PBYTE inBuffer, DWORD inSize, PBYTE *outBuffer, LPDWORD outSize);
int   WINAPI MyMultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
HFONT WINAPI MyCreateFontIndirectA(LOGFONTA *lplf);

TFuncPatch func_fsn[] =
{
    {CALL, 0x093127, (DWORD)MyPeekMessageA, 0x00}, 
    {CALL, 0x16D761, (DWORD)MyMultiByteToWideChar, 0x00}, 
};

TFuncPatch func_fha[] =
{
    {CALL, 0x055A01, (DWORD)MyMultiByteToWideChar, 0x00}, 
    {CALL, 0x0B71EB, (DWORD)MyPeekMessageA, 0x00}, 
    {CALL, 0x129601, (DWORD)MyCreateFontIndirectA, 0x00}, 
    {CALL, 0x13FD52, (DWORD)RenderAWord, 0x00}, 
};

#endif /* Fate_EXPORTS */

/*
tlg > png > jpg > bmp
*/
#endif /* _FATE_H_ */
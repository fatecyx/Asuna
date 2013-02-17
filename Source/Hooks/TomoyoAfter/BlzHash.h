#ifndef _MPQHASH_H_
#define _MPQHASH_H_

#include <Windows.h>
#include "my_common.h"

enum ERROR_CODE
{
    ERR_OUTOFMEM  = -3,
    ERR_NOT_INIT  = -2,
    ERR_NOT_FOUND = -1, 
    ERR_SUCCESS   =  0, 
    ERR_MAX_POS   =  0x7FFFFFFF,
};

#define CBH_SUCCESSED(Status) (BOOL)(Status < ((DWORD)ERR_MAX_POS + 1))

typedef struct
{
    DWORD dwHashA;
    DWORD dwHashB;
    PBYTE pbBuffer;
    DWORD dwSize;
    DWORD dwBufferSize;
//    CHAR  szFileName[MAX_PATH];
} TBlzHashTable;

class CBlzHash
{
public:
    CBlzHash();
    ~CBlzHash();

public:
    BOOL  STDCALL Init(DWORD dwTableLength);
    DWORD STDCALL GetHashTablePos(LPCSTR lpszFileName);
    DWORD STDCALL SetHashTablePos(LPCSTR lpszFileName);
    DWORD STDCALL GetTableLength();
    DWORD STDCALL SetTableLength(DWORD dwTableSize);

    DWORD STDCALL GetItemCount() { return m_dwItemCount; }
    void  STDCALL SetItemCount(DWORD dwCount) { m_dwItemCount = dwCount; }
    TBlzHashTable* STDCALL GetHashTable() { return m_pHashTable; }

private:
    DWORD STDCALL HashString(LPCSTR lpszFileName, DWORD dwHashType);

private:
    HANDLE m_hHeap;
    DWORD  m_dwItemCount, m_dwTableLength, *m_pdwCryptTalbe;
    TBlzHashTable *m_pHashTable;
};

#endif /* _MPQHASH_H_ */
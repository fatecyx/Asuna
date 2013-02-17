#include "BlzHash.h"

CBlzHash::CBlzHash()
{
    m_dwItemCount = 0;
    m_dwTableLength = 0;
    m_pHashTable = NULL;
    m_pdwCryptTalbe = NULL;
    m_hHeap = GetProcessHeap();
}

CBlzHash::~CBlzHash()
{
    if (m_pHashTable) HeapFree(m_hHeap, 0, m_pHashTable);
}

BOOL STDCALL CBlzHash::Init(DWORD dwTableLength)
{
    DWORD dwSeed;

    if (dwTableLength == 0 || dwTableLength > -10)
        return False;

    m_dwTableLength = 0;
    m_pHashTable = (TBlzHashTable *)HeapAlloc(m_hHeap, HEAP_ZERO_MEMORY, dwTableLength * sizeof(*m_pHashTable));
    if (m_pHashTable == NULL)
        return False;

    m_pdwCryptTalbe = (LPDWORD)HeapAlloc(m_hHeap, 0, 0x500 * sizeof(*m_pdwCryptTalbe));
    if (m_pdwCryptTalbe == NULL)
    {
        HeapFree(m_hHeap, 0, m_pHashTable);
        m_pHashTable = NULL;
        return False;
    }

    m_dwTableLength = dwTableLength;

    dwSeed = 0x00100001;
    for (int index1 = 0; index1 != 0x100; index1++)
    {
        for(int index2 = index1, i = 0; i != 5; i++, index2 += 0x100)
        {
            DWORD temp1, temp2;
            dwSeed = (dwSeed * 125 + 3) % 0x2AAAAB;
            temp1 = (dwSeed & 0xFFFF) << 0x10;
            dwSeed = (dwSeed * 125 + 3) % 0x2AAAAB;
            temp2 = (dwSeed & 0xFFFF);
            m_pdwCryptTalbe[index2] = temp1|temp2;
        }
    }

    return True;
}

DWORD STDCALL CBlzHash::HashString(LPCSTR lpszFileName, DWORD dwHashType)
{
    DWORD dwSeed1, dwSeed2;
    int ch;

    if (m_dwTableLength == 0)
        return ERR_NOT_INIT;

    dwSeed1 = 0x7FED7FED;
    dwSeed2 = 0xEEEEEEEE;
    while(ch = toupper(*lpszFileName++))
    {
        dwSeed1 = m_pdwCryptTalbe[(dwHashType << 8) + ch] ^ (dwSeed1 + dwSeed2);
        dwSeed2 = ch + dwSeed1 + dwSeed2 + (dwSeed2 << 5) + 3;
    }

    return dwSeed1;
}

DWORD STDCALL CBlzHash::GetHashTablePos(LPCSTR lpszFileName)
{
    DWORD dwStartPos, dwCurrentPos, dwHash, dwHashA, dwHashB;

    if (m_dwTableLength == 0)
        return ERR_NOT_INIT;

    dwHash  = HashString(lpszFileName, 0);
    dwHashA = HashString(lpszFileName, 1);
    dwHashB = HashString(lpszFileName, 2);

    dwStartPos = dwHash % m_dwTableLength;
    dwCurrentPos = dwStartPos;

    while (1)
    {
        TBlzHashTable *pTable = &m_pHashTable[dwCurrentPos];

        if (
               pTable->dwHashA == dwHashA 
            && pTable->dwHashB == dwHashB 
//            && !lstrcmpA(pTable->szFileName, lpszFileName)
            )
            break;
        else
        {
            dwCurrentPos = ERR_NOT_FOUND;
            break;
        }
/*
        dwCurrentPos = ++dwCurrentPos % m_dwTableLength;
        if (dwCurrentPos == dwStartPos)
        {
            dwCurrentPos = ERR_NOT_FOUND;
            break;
        }
*/
    }

    return dwCurrentPos;
}

DWORD STDCALL CBlzHash::SetHashTablePos(LPCSTR lpszFileName)
{
    TBlzHashTable *pTable;
    DWORD dwStartPos, dwCurrentPos, dwHash, dwHashA, dwHashB;

    if (m_dwTableLength == 0)
        return ERR_NOT_INIT;

    dwHash  = HashString(lpszFileName, 0);
    dwHashA = HashString(lpszFileName, 1);
    dwHashB = HashString(lpszFileName, 2);

    dwStartPos = dwHash % m_dwTableLength;
    dwCurrentPos = dwStartPos;

    pTable = &m_pHashTable[dwCurrentPos];
    while (0)
    {
        pTable = &m_pHashTable[dwCurrentPos];

        if (pTable->pbBuffer == NULL)
            break;

        dwCurrentPos = ++dwCurrentPos % m_dwTableLength;
        if (dwCurrentPos == dwStartPos)
        {
            dwCurrentPos = dwStartPos;
            break;
        }
    }

    pTable->dwHashA = dwHashA;
    pTable->dwHashB = dwHashB;
//    lstrcpyA(pTable->szFileName, lpszFileName);
    if (pTable->pbBuffer == NULL)
        ++m_dwItemCount;

    return dwCurrentPos;
}

DWORD STDCALL CBlzHash::GetTableLength()
{
    return m_dwTableLength;
}

DWORD STDCALL CBlzHash::SetTableLength(DWORD dwTableSize)
{
    TBlzHashTable *pTable;

    if (dwTableSize == m_dwTableLength)
        return dwTableSize;

    pTable = (TBlzHashTable *)HeapAlloc(m_hHeap, HEAP_ZERO_MEMORY, dwTableSize * sizeof(*pTable));
    if (pTable == NULL)
        return ERR_OUTOFMEM;

    memcpy(pTable, m_pHashTable, min(dwTableSize, m_dwTableLength) * sizeof(*pTable));
    
    if (m_dwItemCount == m_dwTableLength)
        m_dwItemCount = dwTableSize;

    m_dwTableLength = dwTableSize;

    HeapFree(m_hHeap, 0, m_pHashTable);

    return dwTableSize;
}
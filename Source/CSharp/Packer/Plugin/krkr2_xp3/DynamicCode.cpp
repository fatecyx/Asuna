#include <Windows.h>
#include "DynamicCode.h"
#include "my_crt.h"
#include "my_mem.h"

CDynamicCodeBase::CDynamicCodeBase()
{
    m_pbFunction = NULL;
    m_pEncryptBlock = NULL;
}

CDynamicCodeBase::~CDynamicCodeBase()
{
    Release();
}

Void CDynamicCodeBase::Release()
{
    if (m_pbFunction)
    {
        VirtualFreeEx(NtCurrentProcess(), m_pbFunction, FuncSize * FuncCount, MEM_DECOMMIT);
        m_pbFunction = NULL;
    }
}

UInt32 CDynamicCodeBase::GetMask(UInt32 &Hash)
{
    UInt32 Index, h1, h2;
    F_GetMask pfnGetMask;

    h2 = Hash;
    Index = h2 % FuncCount;
    if (m_pbFunction == NULL)
    {
        m_pbFunction = (PByte)VirtualAllocEx(NtCurrentProcess(), 0,
            FuncSize * FuncCount, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (m_pbFunction == NULL)
            return False;
    }

    pfnGetMask = (F_GetMask)(m_pbFunction + Index * FuncSize);
    if (*(PByte)pfnGetMask == 0 && GenerateCode(Index) == False)
        return 1;

    h2 >>= 7;
    h1 = pfnGetMask(h2);
    h2 = pfnGetMask(~h2);
    if (!(h1 & 0xFF)) ++h1;
    if (LoWord(h2) == HiWord(h2))
    {
        h2 = MakeDword(LoWord(h2) + 1, HiWord(h2));     // modified @ 2010-11-20, game @ tenshin
    }
    
    Hash = h1;
    return h2;
}

Bool CDynamicCodeBase::HasEnoughSpace(UInt32 uSizeToAppend)
{
    return (UInt32)(m_Info.pbBufferCur - m_Info.pbBuffer + uSizeToAppend) <= FuncSize;
}

Bool CDynamicCodeBase::AppendBytes(UInt32 uCount, LPVoid lpBytes)
{
    if (HasEnoughSpace(uCount) == False)
        return False;

    memcpy(m_Info.pbBufferCur, lpBytes, uCount);
    m_Info.pbBufferCur += uCount;

    return True;
}

Bool CDynamicCodeBase::GenerateFunction(UInt32 uLoop)
{
    //  generate function head
    {
        Byte bytes[] = { 0x57, 0x56, 0x53, 0x51, 0x52 };
        if (AppendBytes(sizeof(bytes), bytes) == False)
            return False;
    }

    {
        Byte bytes[] = { 0x8B, 0x7C, 0x24, 0x18 };
        if (AppendBytes(sizeof(bytes), bytes) == False)
            return False;
    }

    if (GenerateBody(uLoop) == False)
        return False;

    {
        Byte bytes[] = { 0x5A, 0x59, 0x5B, 0x5E, 0x5F };
        if (AppendBytes(sizeof(bytes), bytes) == False)
            return False;
    }

    Byte bytes[] = { 0xC3 };
    return AppendBytes(sizeof(bytes), bytes);
}

Bool CDynamicCodeBase::GenerateBody(UInt32 uLoop)
{
    return True;
}

Bool CDynamicCodeBase::GenerateBody2(UInt32 uLoop)
{
    return True;
}

Bool CDynamicCodeBase::GenerateTail()
{
    return True;
}

UInt32 CDynamicCodeBase::GenerateSeed()
{
    UInt32 v1, v2;

    v1 = m_Info.Hash;
    m_Info.Hash = m_Info.Hash * 0x41C64E6D + 0x3039;
    v2 = (v1 << 16) ^ (v1 >> 16);

    return v2 ^ m_Info.Hash;
}

Bool CDynamicCodeBase::GenerateCode(UInt32 Index)
{
    m_Info.pbBuffer = m_pbFunction + Index * FuncSize;
    m_Info.BufferSize = FuncSize;
    m_Info.Hash = Index;

    for (UInt32 i = 5; i; --i)
    {
        m_Info.pbBufferCur = m_Info.pbBuffer;
        if (GenerateFunction(i))
            return True;
    }

    return False;
}
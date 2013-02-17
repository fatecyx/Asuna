#include "TextHandler.h"
#include "my_mem.h"
#include "EncryptText/aes.h"
#include "EncryptText/sha2.h"

CTextHandler::CTextHandler()
{
    m_pbBuffer = NULL;
    m_pIndex   = NULL;
    m_BufferSize = 0;
    m_IndexCount = 0;
    m_MaxIndexCount = 8000;
    m_Key = (UInt32)ReadTimeStampCounter();
}

CTextHandler::~CTextHandler()
{
    m_mem.Free(m_pbBuffer);
    m_mem.Free(m_pIndex);
}

Bool CTextHandler::Init(PVoid lpBuffer, UInt32 BufferSize)
{
    UInt32 TextLength;
    STextHeader *h;

    if (BufferSize == 0)
        return False;

    m_pbBuffer = (PByte)m_mem.Alloc(BufferSize);
    if (m_pbBuffer == NULL)
        return False;
    m_pIndex = (STextHeader **)m_mem.Alloc(m_MaxIndexCount * sizeof(*m_pIndex));
    if (m_pIndex == NULL)
        return False;

    m_BufferSize = BufferSize;
    memcpy(m_pbBuffer, lpBuffer, BufferSize);

    for (UInt32 i = 0, j = BufferSize; i < j; )
    {
        h = (STextHeader *)&m_pbBuffer[i];
        TextLength = h->Hash[2] ^ h->Hash[0] ^ h->Length;
        if (m_IndexCount == m_MaxIndexCount)
        {
            m_MaxIndexCount += m_MaxIndexCount / 2;
            m_pIndex = (STextHeader **)m_mem.ReAlloc(m_pIndex, m_MaxIndexCount * sizeof(*m_pIndex));
            if (m_pIndex == NULL)
                return False;
        }

        m_pIndex[m_IndexCount] = (STextHeader *)_rotl((Int_Ptr)h ^ m_Key, m_IndexCount + 1);

        ++m_IndexCount;
        i += ((TextLength + 3) & ~3) + sizeof(*h);
    }

    return True;
}

Int CTextHandler::GetText(PVoid pvOutBuffer, Int32 BufferSize, PCChar lpSrcText, Int32 SrcLength)
{
    return GetTextInternal(pvOutBuffer, BufferSize, lpSrcText, SrcLength, False);
}

STextHeader* CTextHandler::RemoveText(PCChar lpSrcText, Int32 SrcLength)
{
    return (STextHeader *)GetTextInternal(NULL, 0, lpSrcText, SrcLength, True);
}

Int CTextHandler::GetTextInternal(PVoid pvOutBuffer, Int32 BufferSize, PCChar lpSrcText, Int32 SrcLength, Bool bRemove)
{
    PByte   pbOutBuffer;
    Int32   TextLength, Length;
    UInt32  Hash[4], SrcTextHash[8];
    PUInt32 pEncryptedText;
    STextHeader *pHeader;
    aes_encrypt_ctx ctx;

    sha256((PByte)lpSrcText, SrcLength, (PByte)SrcTextHash);
    Hash[0] = SrcTextHash[0] ^ SrcTextHash[4];
    Hash[1] = SrcTextHash[1] ^ SrcTextHash[5];
    Hash[2] = SrcTextHash[2] ^ SrcTextHash[6];
    Hash[3] = SrcTextHash[3] ^ SrcTextHash[7];

    pHeader = FindTextPos(Hash);
    if (pHeader == NULL || bRemove)
        return (Int)pHeader;

    TextLength = pHeader->Length ^ pHeader->Hash[0] ^ pHeader->Hash[2];
    aes_encrypt_key128(&SrcTextHash[4], &ctx);

    pbOutBuffer = (PByte)pvOutBuffer;
    pEncryptedText = (PUInt32)(pHeader + 1);

    Length = TextLength;
    while (Length >= 16 && BufferSize >= 16)
    {
        Length -= 16;
        BufferSize -= 16;

        aes_encrypt(SrcTextHash, SrcTextHash, &ctx);
        *((PUInt32)pbOutBuffer + 0) = pEncryptedText[0] ^ SrcTextHash[0];
        *((PUInt32)pbOutBuffer + 1) = pEncryptedText[1] ^ SrcTextHash[1];
        *((PUInt32)pbOutBuffer + 2) = pEncryptedText[2] ^ SrcTextHash[2];
        *((PUInt32)pbOutBuffer + 3) = pEncryptedText[3] ^ SrcTextHash[3];

        SrcTextHash[0] = pEncryptedText[0];
        SrcTextHash[1] = pEncryptedText[1];
        SrcTextHash[2] = pEncryptedText[2];
        SrcTextHash[3] = pEncryptedText[3];

        pbOutBuffer    += 16;
        pEncryptedText += 4;
    }

    if (Length != 0 && BufferSize >= Length)
    {
        UInt32 DecryptBuffer[4];

        aes_encrypt(SrcTextHash, SrcTextHash, &ctx);
        DecryptBuffer[0] = pEncryptedText[0] ^ SrcTextHash[0];
        DecryptBuffer[1] = pEncryptedText[1] ^ SrcTextHash[1];
        DecryptBuffer[2] = pEncryptedText[2] ^ SrcTextHash[2];
        DecryptBuffer[3] = pEncryptedText[3] ^ SrcTextHash[3];

        memcpy(pbOutBuffer, DecryptBuffer, min(Length, BufferSize));

        pbOutBuffer += Length;
        BufferSize -= Length;
    }
/*
    if (BufferSize > 0)
        *pbOutBuffer++ = 0;
*/
    return pbOutBuffer - (PByte)pvOutBuffer;
}

STextHeader* CTextHandler::FindTextPos(UInt32 dwHash[4], Bool bRemove /* = False */)
{
    UInt32 l, r, m;
    STextHeader *h;

    l = 0;
    r = m_IndexCount;

    while (l < r)
    {
        m = (l + r) / 2;

        h = (STextHeader *)(_rotr((Int_Ptr)m_pIndex[m], m + 1) ^ m_Key);

        if (h == NULL)
            return NULL;

        if (h->Hash[0] < dwHash[0])
        {
            l = m + 1;
            continue;
        }
        else if (h->Hash[0] > dwHash[0])
        {
            r = m;
            continue;
        }

        if (h->Hash[1] < dwHash[1])
        {
            l = m + 1;
            continue;
        }
        else if (h->Hash[1] > dwHash[1])
        {
            r = m;
            continue;
        }

        if (h->Hash[2] < dwHash[2])
        {
            l = m + 1;
            continue;
        }
        else if (h->Hash[2] > dwHash[2])
        {
            r = m;
            continue;
        }

        if (h->Hash[3] < dwHash[3])
        {
            l = m + 1;
            continue;
        }
        else if (h->Hash[3] > dwHash[3])
        {
            r = m;
            continue;
        }

        if (bRemove)
            m_pIndex[m] = NULL;

        return h;

    }

    return NULL;
}
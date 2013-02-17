#include "BMP2G00.h"
#include "my_crtadd.h"
#include "my_mem.h"
#include "nt_api.h"

G00::G00()
{
    m_hHeap = GetProcessHeap();
}

G00::~G00()
{
    Free();
}

void G00::Reset()
{
    m_szInFile      = NULL;
    m_szOutFile     = NULL;
    m_pInBuffer     = NULL;
    m_pOutBuffer    = NULL;
    m_pMyRegion     = NULL;
    m_pBitMapHeader = NULL;
    m_uiRegionSize  = 0;
    m_uiInBufSize   = 0;
    m_uiOutBufSize  = 0;
}

void G00::Free()
{
    if (m_pMyRegion) HeapFree(m_hHeap, 0, m_pMyRegion);
}

BOOL G00::Open(char *pData, TBitMapHeader *pBitMapHeader, uint_32 uiInputBufferSize)
{
    if (pData == NULL || pBitMapHeader == NULL)
        return False;

    Reset();
    m_pBitMapHeader = (TBitMapHeader *)pBitMapHeader;
    m_pInBuffer     = pData;
    m_uiInBufSize   = uiInputBufferSize;

    return True;
}

uint_32 G00::ConvertToG00(char **ppOutBuffer)
{
    if (ppOutBuffer == NULL)
        return 0;

    TBitMapHeader *h;

    h = m_pBitMapHeader;
    *ppOutBuffer = NULL;

    if (h->Info.wBit == 24)   // 24 bit BMP
    {
        return ConvertToG00_0(ppOutBuffer);     // convert to G00 type 0
    }
    else if (h->Info.wBit == 32) // 32 bit BMP
    {
        return ConvertToG00_2(ppOutBuffer);     // convert to G00 type 2
    }
    else                        // unsupported format
    {
        return 0;
    }
}

uint_32 G00::ConvertToG00_2(char **ppOutBuffer)
{
    TRegion          *pRegion;
    TBlockIndex      *pBlockIndex;
    TG00Header_2     *pgh;
    TBitMapHeader    *h;
    TPartDataHeader  *pPartDataHeader;
    TBlockDataHeader *pBlockDataHeader;

    char   *pOutBuffer, *pDest, *pSrc, *pTemp;
    uint_32 nBlocks, uiTailSize, uiRegionCount, uiFileSize, uiStride, *pUncompSize;
    static const uint_32 uiBytePerPixel = 4;
    static const uint_32 uiBlockSize    = 8;

    h = m_pBitMapHeader;
    uiRegionCount = m_uiRegionSize / sizeof(TMyRegion);
    uiRegionCount == 0 ? ++uiRegionCount : 0;

    // calculate g00 size
    uiFileSize = 1 + 2 + 2 + 4; // sizeof(id + sWidth + sWidth + uiRegionCount)
    uiFileSize += sizeof(TRegion) * uiRegionCount;
    uiFileSize += 4 + 4;        // uiCompressedSize + uiUncompressedSize
    uiFileSize += 4 + sizeof(TBlockIndex) * uiRegionCount;  // BlockCount + index

    if (m_pMyRegion)
    {
        for (uint_32 i = 0; i != uiRegionCount; ++i)
        {
            uiFileSize += sizeof(TBlockDataHeader) + sizeof(TPartDataHeader);
            uiFileSize += uiBytePerPixel *
                          (m_pMyRegion[i].usRight - m_pMyRegion[i].usLeft + 1) *
                          (m_pMyRegion[i].usBottom - m_pMyRegion[i].usTop + 1);
        }
    }
    else
    {
        uiRegionCount = 1;
        uiFileSize += sizeof(TBlockDataHeader) + sizeof(TPartDataHeader);
        uiFileSize += uiBytePerPixel * h->Info.dwHeight * h->Info.dwWidth;
    }

    nBlocks = uiFileSize - 9 - sizeof(TRegion) * uiRegionCount - 8;
    uiTailSize = nBlocks % uiBlockSize;
    nBlocks /= uiBlockSize;
    uiFileSize += nBlocks + (uiTailSize != 0);

    pOutBuffer = (char *)HeapAlloc(m_hHeap, 0, uiFileSize);
    if (pOutBuffer == NULL)
    {
        return 0;
    }

    pDest = pOutBuffer;
    pgh = (TG00Header_2 *)pDest;
    pgh->id = 2;
    pgh->usWidth  = (uint_16)h->Info.dwWidth;
    pgh->usHeight = (uint_16)h->Info.dwHeight;
    pgh->uiRegionCount = uiRegionCount;

    pRegion = (TRegion *)(pDest + 9);
    pDest += 9;
    pDest += sizeof(TRegion) * uiRegionCount;
    *(puint_32)pDest = uiFileSize - 9 - sizeof(TRegion) * uiRegionCount; // uiCompressedSize;
    pDest += 4;
    pUncompSize = (puint_32)pDest;
    *pUncompSize = 0;
    pDest += 4;     // skip uiUncompressedSize

    if (m_pMyRegion)
    {
        TMyRegion *p = m_pMyRegion;
        for (uint_32 i = 0; i != uiRegionCount; ++i)
        {
            pRegion[i].uiOriginX       = p[i].uiOriginX;
            pRegion[i].uiOriginY       = p[i].uiOriginY;
            pRegion[i].rcRegion.left   = p[i].usLeft;
            pRegion[i].rcRegion.top    = p[i].usTop;
            pRegion[i].rcRegion.right  = p[i].usRight;
            pRegion[i].rcRegion.bottom = p[i].usBottom;
        }
    }
    else if (uiRegionCount == 1)
    {
        pRegion->uiOriginX       = 0;
        pRegion->uiOriginY       = 0;
        pRegion->rcRegion.left   = 0;
        pRegion->rcRegion.top    = 0;
        pRegion->rcRegion.right  = h->Info.dwWidth - 1;
        pRegion->rcRegion.bottom = h->Info.dwHeight - 1;
    }
    else
    {
        HeapFree(m_hHeap, 0, pOutBuffer);
        return 0;
    }

    *(puint_32)pDest = uiRegionCount;   // uiBlockCount;
    pDest += 4;
    pBlockIndex = (TBlockIndex *)pDest;
    pDest += sizeof(TBlockIndex) * uiRegionCount;

    pBlockIndex[0].uiOffset = sizeof(TBlockIndex) * uiRegionCount + 4;
    *pUncompSize += pBlockIndex[0].uiSize =
                            sizeof(TBlockDataHeader) + sizeof(TPartDataHeader) +
                            uiBytePerPixel *
                            (pRegion[0].rcRegion.right - pRegion[0].rcRegion.left + 1) *
                            (pRegion[0].rcRegion.bottom - pRegion[0].rcRegion.top + 1);

    for (uint_32 i = 1; i != uiRegionCount; ++i)
    {
        pBlockIndex[i].uiOffset = pBlockIndex[i - 1].uiOffset + pBlockIndex[i - 1].uiSize;
        *pUncompSize += pBlockIndex[i].uiSize =
                                sizeof(TBlockDataHeader) + sizeof(TPartDataHeader) +
                                uiBytePerPixel *
                                (pRegion[i].rcRegion.right - pRegion[i].rcRegion.left + 1) *
                                (pRegion[i].rcRegion.bottom - pRegion[i].rcRegion.top + 1);
    }

    *pUncompSize += sizeof(TBlockIndex) * uiRegionCount + 4; // uiBlockCount
    uiStride = h->Info.dwWidth * uiBytePerPixel;
    pSrc = m_pInBuffer;
    for (uint_32 i = 0; i != uiRegionCount; ++i)
    {
        uint_32 uiWidth, uiHeight, uiTop;

        pBlockDataHeader = (TBlockDataHeader *)pDest;
        pDest += sizeof(TBlockDataHeader);
        pBlockDataHeader->unknown = 1;
        pBlockDataHeader->usPartCount = 1;
        pBlockDataHeader->uiBlockX = 0;
        pBlockDataHeader->uiBlockY = 0;
        uiWidth  = pRegion[i].rcRegion.right  - pRegion[i].rcRegion.left + 1;
        uiHeight = pRegion[i].rcRegion.bottom - pRegion[i].rcRegion.top  + 1;
        pBlockDataHeader->uiBlockHeight = uiHeight;
        pBlockDataHeader->uiBlockWidth  = uiWidth;
        pBlockDataHeader->uiOriginX = pRegion[i].uiOriginX;
        pBlockDataHeader->uiOriginY = pRegion[i].uiOriginY;
        pBlockDataHeader->uiSthHeight = uiHeight;
        pBlockDataHeader->uiSthWidth  = uiWidth;
        memset(pBlockDataHeader->zero, 0, sizeof(pBlockDataHeader->zero));

        pPartDataHeader = (TPartDataHeader *)pDest;
        pDest += sizeof(TPartDataHeader);
        pPartDataHeader->usPartX = 0;
        pPartDataHeader->usPartY = 0;
        pPartDataHeader->usTrans = 1;
        pPartDataHeader->usPartHeight = (uint_16)uiHeight;
        pPartDataHeader->usPartWidth  = (uint_16)uiWidth;
        pPartDataHeader->unknown = 0;
        memset(pPartDataHeader->zero, 0, sizeof(pPartDataHeader->zero));

        if (pRegion[i].rcRegion.left == 0 && pRegion[i].rcRegion.top == 0 &&
            pRegion[i].rcRegion.right == 0 && pRegion[i].rcRegion.bottom == 0)
            continue;

        int stride = (uiWidth) * uiBytePerPixel;
        uiTop = pRegion[i].rcRegion.top;
        for (uint_32 height = uiTop; height != uiHeight + uiTop; ++height)
        {
            memcpy(pDest,
                pSrc + height * uiStride + pRegion[i].rcRegion.left * uiBytePerPixel,
                stride);
            pDest += stride;
        }
    }

    pTemp = (char *)HeapAlloc(m_hHeap, 0, uiFileSize);
    if (pTemp == NULL)
    {
        HeapFree(m_hHeap, 0, pOutBuffer);
        return 0;
    }

    pSrc  = pOutBuffer;
    pDest = pTemp;
    memcpy(pDest, pSrc, 9);
    pSrc  += 9;
    pDest += 9;
    uiStride = sizeof(TRegion) * uiRegionCount + 8;
    memcpy(pDest, pSrc, uiStride);
    pSrc  += uiStride;
    pDest += uiStride;

    for (uint_32 i = 0; i != nBlocks; ++i)
    {
        *pDest++ = -1;
        memcpy(pDest, pSrc, uiBlockSize);
        pSrc  += uiBlockSize;
        pDest += uiBlockSize;
    }
    if (uiTailSize)
    {
        *pDest++ = -1;
        memcpy(pDest, pSrc, uiTailSize);
    }

    HeapFree(m_hHeap, 0, pOutBuffer);
    *ppOutBuffer = pTemp;

    return uiFileSize;
}

uint_32 G00::ConvertToG00_0(char **ppOutBuffer)
{
    TG00Header_0 gh;
    TBitMapHeader *h;
    uint_32 uiBytePerPixel, nBlocks, uiTailSize;
    char *pOutBuffer, *pDest, *pSrc;

    h = m_pBitMapHeader;
    uiBytePerPixel = 3;
    gh.id = 0;
    gh.usWidth  = (uint_16)h->Info.dwWidth;
    gh.usHeight = (uint_16)h->Info.dwHeight;
    gh.uiCompressedSize = h->Info.dwWidth * h->Info.dwHeight * uiBytePerPixel + 8;
    gh.uiUncompressedSize = h->Info.dwHeight * h->Info.dwWidth * 4;

    nBlocks = gh.uiCompressedSize - 8;
    uiTailSize = nBlocks % 0x18;
    nBlocks /= 0x18;
    gh.uiCompressedSize += nBlocks + (uiTailSize != 0);

    pOutBuffer = (char *)HeapAlloc(m_hHeap, 0, gh.uiCompressedSize + 5);
    if (pOutBuffer == NULL)
        return 0;

    *ppOutBuffer = pOutBuffer;
    *(TG00Header_0 *)pOutBuffer = gh;

    pSrc = m_pInBuffer;
    pDest = pOutBuffer + sizeof(gh);
    for (uint_32 i = 0; i != nBlocks; ++i)
    {
        *pDest++ = -1;
        memcpy(pDest, pSrc, 0x18);
        pSrc  += 0x18;
        pDest += 0x18;
    }
    if (uiTailSize)
    {
        *pDest++ = -1;
        memcpy(pDest, pSrc, uiTailSize);
        pDest += uiTailSize;
    }

    return pDest - pOutBuffer;
}

void G00::FreeBuffer(char *pBuffer)
{
    HeapFree(m_hHeap, 0, pBuffer);
}

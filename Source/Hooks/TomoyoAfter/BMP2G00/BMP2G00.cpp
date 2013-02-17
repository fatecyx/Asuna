#include "BMP2G00.h"
#include "my_crtadd.h"
#include "my_mem.h"

G00::G00()
{
    Reset();
}

G00::G00(Char *szFileName)
{
    if (Open(szFileName) == FALSE)
    {
        Close();
    }
}

G00::G00(Char *pData, UInt32 uiInputBufferSize)
{
    if (Open(pData, uiInputBufferSize) == FALSE)
    {
        Close();
    }
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
    m_fInput        = NULL;
    m_fOutput       = NULL;
    m_pMyRegion     = NULL;
    m_pBitMapHeader = NULL;
    m_uiRegionSize  = 0;
    m_uiInBufSize   = 0;
    m_uiOutBufSize  = 0;
}

void G00::Free()
{
    if (m_fInput)
    {
        fclose(m_fInput);
        if (m_pBitMapHeader)
        {
            free(m_pBitMapHeader);
        }
    }

    if (m_fOutput) fclose(m_fOutput);
    if (m_pMyRegion) free(m_pMyRegion);

}

void G00::Close()
{
    Free();
    Reset();
}

BOOL G00::Open(Char *szFileName)
{
    if (szFileName == NULL)
        return FALSE;

    Close();
    m_fInput = fopen(szFileName, "rb");
    if (m_fInput == NULL)
    {
        return FALSE;
    }

    UInt32 uiBmpSize;
    TBitMapHeader h;

    if (fread(&h, sizeof(h), 1, m_fInput) != 1)
        return FALSE;

    if (h.wTag != 'MB')
        return FALSE;

    m_uiInBufSize = fsize(m_fInput);
    uiBmpSize = (h.Info.dwWidth * h.Info.wBit / 8 + (h.Info.wBit == 0x18 ? (h.Info.dwWidth & 3) : 0)) * h.Info.dwHeight + h.dwRawOffset;
    if (m_uiInBufSize < uiBmpSize)
        return FALSE;

    fseek(m_fInput, 0, SEEK_SET);
    m_uiInBufSize = uiBmpSize;
    m_szInFile = szFileName;

    return TRUE;
}

BOOL G00::Open(Char *pData, UInt32 uiInputBufferSize)
{
    if (pData == NULL || uiInputBufferSize < sizeof(TBitMapHeader))
        return FALSE;

    Close();
    m_pBitMapHeader = (TBitMapHeader *)pData;
    m_pInBuffer     = pData + ((TBitMapHeader *)pData)->dwRawOffset;
    m_uiInBufSize   = uiInputBufferSize - m_pBitMapHeader->dwRawOffset;

    return TRUE;
}

BOOL G00::Open(Char *pData, TBitMapHeader *pBitMapHeader, UInt32 uiInputBufferSize)
{
    if (pData == NULL || pBitMapHeader == NULL)
        return FALSE;

    Close();
    m_pBitMapHeader = (TBitMapHeader *)pBitMapHeader;
    m_pInBuffer     = pData;
    m_uiInBufSize   = uiInputBufferSize;

    return TRUE;
}

UInt32 G00::ConvertToG00(Char *szFileName)
{
    if (szFileName == NULL)
        return 0;

    m_fOutput = fopen(szFileName, "wb");
    if (m_fOutput == NULL)
        return 0;

    m_szOutFile = szFileName;
    if (m_fInput)   // file input transform to memory input
    {
        m_pInBuffer = (Char *)malloc(m_uiInBufSize);
        if (m_pInBuffer == NULL)
            return 0;

        if (fread(m_pInBuffer, m_uiInBufSize, 1, m_fInput) != 1)
        {
            free(m_pInBuffer);
            m_pInBuffer = NULL;
            return 0;
        }

        m_pBitMapHeader = (TBitMapHeader *)m_pInBuffer;
        m_pInBuffer    += m_pBitMapHeader->dwRawOffset;
        m_uiInBufSize  -= m_pBitMapHeader->dwRawOffset;
    }

    if (m_pInBuffer)    // memory input
    {
        Char   *pOutBuffer;
        UInt32 uiG00Size;

        uiG00Size = ConvertToG00(&pOutBuffer);
        if (pOutBuffer == NULL || uiG00Size == 0)
            return 0;

        fwrite(pOutBuffer, uiG00Size, 1, m_fOutput);
        fflush(m_fOutput);
        FreeBuffer(pOutBuffer);

        return uiG00Size;
    }
    else    // no input
    {
        return 0;
    }
}

UInt32 G00::ConvertToG00(Char **ppOutBuffer)
{
    if (ppOutBuffer == NULL)
        return 0;

    TBitMapHeader *h;

    h = m_pBitMapHeader;
    *ppOutBuffer = NULL;

    if (h->Info.wBit == 24)   // 24 bit BMP
    {
        return ConvertToG00_0(ppOutBuffer);     // convert to G00 format 0
    }
    else if (h->Info.wBit == 32) // 32 bit BMP
    {
        return ConvertToG00_2(ppOutBuffer);     // convert to G00 format 2
    }
    else                        // unsupported format
    {
        return 0;
    }
}

UInt32 G00::ConvertToG00_2(Char **ppOutBuffer)
{
    int i, j;
    new Char[j];
    return 0;
}

UInt32 G00::ConvertToG00_0(Char **ppOutBuffer)
{
    TG00Header_0 gh;
    TBitMapHeader *h;
    UInt32 uiBytePerPixel, nBlocks, uiTailSize;
    Char *pOutBuffer, *pDest, *pSrc, *pFlipVertical;

    h = m_pBitMapHeader;
    uiBytePerPixel = 3;
    gh.id = 0;
    gh.usWidth  = (UInt16)h->Info.dwWidth;
    gh.usHeight = (UInt16)h->Info.dwHeight;
    gh.uiCompressedSize = h->Info.dwWidth * h->Info.dwHeight * uiBytePerPixel + 8;
    gh.uiUncompressedSize = h->Info.dwHeight * h->Info.dwWidth * 4;

    nBlocks = gh.uiCompressedSize - 8;
    uiTailSize = nBlocks % 0x18;
    nBlocks /= 0x18;
    gh.uiCompressedSize += nBlocks + (uiTailSize != 0);

    pOutBuffer = (Char *)malloc(gh.uiCompressedSize + 5);
    if (pOutBuffer == NULL)
        return 0;

    pFlipVertical = (Char *)malloc(m_uiInBufSize - h->dwRawOffset);
    if (pFlipVertical == NULL)
    {
        free(pOutBuffer);
        return 0;
    }

    // flip vertical
    BMPFlipVertical(pFlipVertical,
                    m_pInBuffer,
                    h->Info.dwWidth,
                    h->Info.dwHeight,
                    uiBytePerPixel);

    *ppOutBuffer = pOutBuffer;
    *(TG00Header_0 *)pOutBuffer = gh;

    pSrc = pFlipVertical;
    pDest = pOutBuffer + sizeof(gh);
    for (UInt32 i = 0; i != nBlocks; ++i)
    {
        *pDest++ = -1;              // insert a 0xFF every 0x18 bytes ?
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

    free(pFlipVertical);
    return pDest - pOutBuffer;
}

Char* G00::BMPFlipVertical(Char *pDest, Char *pSrc, UInt32 uiWidth, UInt32 uiHeight, UInt32 uiBPP)
{
    Char *pDst;
    UInt32 uiStride, nPixelToPad;

    pDst = pDest;
    uiStride = uiWidth * uiBPP + (uiWidth & 3);

    memcpy(pDest, pSrc, uiStride * uiWidth);
    return pDest;

    while (uiHeight--)
    {
        memcpy(pDest, pSrc + uiStride * uiHeight, uiStride);
        pDest += uiStride;
        printf("%p\t", pDest - pDst);
    }

    return pDst;
}

void G00::FreeBuffer(Char *pBuffer)
{
    free(pBuffer);
}

void G00::SetRegionInfo(TMyRegion *pMyRegionInfo, UInt32 uiRegionSize)
{
    m_uiRegionSize = uiRegionSize;
    if (uiRegionSize == 0)
    {
        m_pMyRegion = NULL;
    }
    else
    {
        Char *p;
        m_pMyRegion = (TMyRegion *)malloc(uiRegionSize);
        if (m_pMyRegion == NULL)
        {
            m_uiRegionSize = 0;
            return;
        }

        p = (Char *)m_pMyRegion;
        memcpy(m_pMyRegion, pMyRegionInfo, uiRegionSize);
        m_uiRegionSize = uiRegionSize;
        m_pMyRegion->pRegion = (TRegion *)(p + sizeof(m_pMyRegion->h) - sizeof(TRegion));
        m_pMyRegion->pBlock = (TBlockDataHeader *)((Char *)m_pMyRegion->pRegion + sizeof(TRegion) * m_pMyRegion->h.uiRegionCount);
    }
}
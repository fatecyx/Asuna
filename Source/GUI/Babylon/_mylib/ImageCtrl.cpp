#pragma comment(lib, "../Image/Image.lib")

#include "ImageCtrl.h"
#include "my_mem.h"
#include "my_image.h"

CImageCtrl::CImageCtrl() : m_pImage(NULL)
{
    pixel = (SPixel (*)[BlockSize])m.Alloc(ImageBufferSize);
}

CImageCtrl::~CImageCtrl()
{
    if (m_pImage != NULL)
        ImageDestroy(m_pImage);

    m.Free(pixel);
}

HWND CImageCtrl::Create(const LPRECT lpRect, HWND hWndParent, HMENU hMenu /* = NULL */, HINSTANCE hInstance /* = NULL */, LPVOID lpParam /* = NULL */)
{
    DWORD dwStyle, dwExStyle, dwClsStyle;
    RECT  rcClient;
    CREATE_WINDOW_PARAM Param;
    static TChar szClass[] = _T("MY_IMAGE_CTRL");

    if (lpRect == NULL)
    {
        return 0;
    }

    dwStyle    = WS_TABSTOP|WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|
                 WS_VISIBLE|WS_VSCROLL|WS_HSCROLL;
    dwExStyle  = 0;
    dwClsStyle = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;

    rcClient = *lpRect;
    rcClient.right  -= rcClient.left;
    rcClient.bottom -= rcClient.top;
    rcClient.left = 0;
    rcClient.top = 0;

    int cx, cy, x, y;
    WNDCLASSEX wndclsex =
    {
        sizeof(WNDCLASSEX),
        dwClsStyle,
        WndProc,
        0,
        0,
        hInstance,
        0,
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_BTNFACE + 1),
        szClass,
        szClass,
        NULL,
    };

    if (RegisterClassEx(&wndclsex) == 0 && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return NULL;

    x  = lpRect->left;
    y  = lpRect->top;
    cx = rcClient.right;
    cy = rcClient.bottom;

    Param.lpCreateParam = NULL;
    Param.pThis = GetThisPointer();

    m_hInstance = hInstance;
    m_hWnd = ::CreateWindowEx(
                   dwExStyle,
                   szClass,
                   NULL,
                   dwStyle,
                   x, y, cx, cy,
                   hWndParent,
                   hMenu,
                   hInstance,
                   &Param);

    return m_hWnd;
}

Bool CImageCtrl::CreateImage(LPCTSTR lpFileName)
{
    Bool bRet;
    CFileDisk file;

    if (file.Open(lpFileName))
    {
        CMem mem;
        DWORD dwSize = file.GetSize();
        LPVOID lpMem = mem.Alloc(dwSize);

        if (lpMem)
        {
            file.Read(lpMem);
            bRet = CreateImage(lpMem, dwSize);
            mem.Free(lpMem);
            return bRet;
        }
    }

    return False;
}

Bool CImageCtrl::CreateImage(LPVOID lpData, DWORD dwSize)
{
    DestroyImage();
    m_pImage = ImageDecode((PByte)lpData, dwSize);
    if (m_pImage == NULL)
        return False;

    SetCurrentFrame(0);
//    ApplyAlphaChannel();

    return True;
}

UInt32 CImageCtrl::GetFrameNum()
{
    return m_pImage ? m_pImage->FrameNum : -1;
}

UInt32 CImageCtrl::NextFrame()
{
    UInt32 i = SetCurrentFrame(m_uiCurrentFrame + 1);
    if (i != -1)
        Refresh();
    return i;
}

UInt32 CImageCtrl::PrevFrame()
{
    UInt32 i = SetCurrentFrame(m_uiCurrentFrame - 1);
    if (i != -1)
        Refresh();
    return i;
}

UInt32 CImageCtrl::SetCurrentFrame(UInt32 nFrame)
{
    if (m_pImage == NULL || nFrame >= m_pImage->FrameNum)
        return -1;

    SBitMapHeader *pHeader;

    pHeader = (SBitMapHeader *)m_pImage->pFrame[nFrame].buffer;
    if (pHeader == NULL)
        return -1;

    m_uiCurrentFrame = nFrame;
    ZeroMemory(&m_bmpInfo, sizeof(m_bmpInfo));
    m_bmpInfo.bmiHeader.biSize = sizeof(m_bmpInfo.bmiHeader);
    m_bmpInfo.bmiHeader.biWidth  = pHeader->Info.dwWidth;
    m_bmpInfo.bmiHeader.biHeight = pHeader->Info.dwHeight;
    m_bmpInfo.bmiHeader.biPlanes = 1;
    m_bmpInfo.bmiHeader.biBitCount = pHeader->Info.wBit;

    return nFrame;
}

UInt32 CImageCtrl::GetCurrentFrame()
{
    return m_pImage ? m_uiCurrentFrame : -1;
}

PBITMAPINFO CImageCtrl::GetBits(PUInt32 pSize)
{
    if (m_pImage == NULL)
        return NULL;

    if (pSize)
        *pSize = m_pImage->pFrame[m_uiCurrentFrame].size;

    return (PBITMAPINFO)&((SBitMapHeader *)m_pImage->pFrame[m_uiCurrentFrame].buffer)->Info;
}

Bool CImageCtrl::ShowImage()
{
    if (m_pImage == NULL)
        return False;

    return Invalidate();
}

Bool CImageCtrl::Refresh()
{
    return ShowImage();
}

Bool CImageCtrl::DestroyImage()
{
    if (m_pImage == NULL)
        return False;

    Bool ret;

    ImageDestroy(m_pImage);
    m_pImage = NULL;
    OnSize(WM_SIZE, 0, MAKELPARAM(m_CliSize.cx, m_CliSize.cy), ret);
    m_iVSPos = m_iHSPos = 0;

    return True;
}

#define BLEND(c1,c2,a)  ( ( (c1)*(255-(a)) + (c2)*(a) ) /255)
Void CImageCtrl::ApplyAlphaChannel(SPixel *pDest, SPixelA *pSrc, UInt32 uSize)
{
    SBitMapHeader *h;
    struct _PIXELA
    {
        Byte r, g, b, a;
    } *pPixelA;

    for (UInt32 f = 0; f != m_pImage->FrameNum; ++f)
    {
        h = (SBitMapHeader *)m_pImage->pFrame[f].buffer;
        if (h->Info.wBit != 32)
            continue;

        pPixelA = (_PIXELA *)((PByte)h + h->dwRawOffset);
        for (UInt32 i = h->Info.dwWidth * h->Info.dwHeight; i; --i)
        {
            Byte a = pPixelA->a;

            *(LPCOLORREF)pPixelA = RGB(BLEND(GetRValue(m_bkColor), pPixelA->r, a),
                BLEND(GetGValue(m_bkColor), pPixelA->g, a),
                BLEND(GetBValue(m_bkColor), pPixelA->b, a));
            ++pPixelA;
        }
    }
}

HRESULT CImageCtrl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled)
{
    HDC hDC;
    TEXTMETRIC tm;

//    m_hComDC = CreateCompatibleDC(0);
    hDC = GetDC();

    m_bkColor = GetSysColor(COLOR_BTNFACE);
    SetBkMode(hDC, TRANSPARENT);
    SetStretchBltMode(hDC, COLORONCOLOR);
    GetTextMetrics(hDC, &tm);
    m_iHSPos = 0;
    m_iVSPos = 0;
/*
    cxChar = tm.tmAveCharWidth;
    cyChar = tm.tmHeight + tm.tmExternalLeading;
    cxCap  = (tm.tmPitchAndFamily & 1) ? (int)(cxChar + cxChar / 2) : cxChar;
*/
    ReleaseDC(hDC);

    return NO_ERROR;
}

HRESULT CImageCtrl::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled)
{
    HDC hDC;
    Bool b;
    PAINTSTRUCT ps;

    hDC = BeginPaint(&ps);

    if (m_pImage == NULL)
    {
        EndPaint(&ps);
        return NO_ERROR;
    }

    OnSize(WM_SIZE, 0, MAKELPARAM(m_CliSize.cx, m_CliSize.cy), b);

    PByte  pbBits;
    LPCOLORREF palette;
    SBitMapHeader *header;
    UInt32 xSrc, xDest, ySrc, yDest;
    Int32 width, height, Bpp, stride;

#if 1

    BITMAPINFO bmpInfo = m_bmpInfo;

    Bpp = m_pImage->pFrame[m_uiCurrentFrame].bpp / 8;
    header = (SBitMapHeader *)m_pImage->pFrame[m_uiCurrentFrame].buffer;
    width = header->Info.dwWidth;
    stride = width * Bpp + (Bpp == 3 ? width & 3 : 0);

    xSrc = m_iHSPos;
    if (xSrc && xSrc + m_CliSize.cx > header->Info.dwWidth)
        xSrc = header->Info.dwWidth - m_CliSize.cx;

    ySrc = m_iVSPos;
    if (ySrc && ySrc + m_CliSize.cy > header->Info.dwHeight)
        ySrc = header->Info.dwHeight - m_CliSize.cy;

    xDest = 0;
    yDest = 0;
    width  = min(m_CliSize.cx, (Int32)header->Info.dwWidth);
    height = min(m_CliSize.cy, (Int32)header->Info.dwHeight);
    pbBits = (PByte)header + header->dwRawOffset + (header->Info.dwHeight - ySrc) * stride;
    if (Bpp == 1)
    {
        palette = (LPCOLORREF)((PByte)header + sizeof(*header));
    }
    bmpInfo.bmiHeader.biBitCount = 24;
    while (height > 0)
    {
        Int32 h, w, dstsr, srcsr;
        PByte pbSrc, pbDest;

        h = min(height, BlockSize);
        pbBits -= h * stride;
        pbSrc = pbBits + xSrc * Bpp;
        for (Int32 i = width; i > 0; i -= BlockSize)
        {
            w = min(i, BlockSize);
            dstsr = w * 3 + (w & 3);
            srcsr = w * Bpp + ((Bpp & 1) ? w & 3 : 0);
            pbDest = (PByte)pixel;
            if (Bpp == 3)
            {
                PByte src = pbSrc;
                for (Int32 j = 0; j != h; ++j)
                {
                    memcpy(pbDest, src, srcsr);
                    pbDest += dstsr;
                    src += stride;
                }
            }
            else if (Bpp == 4)
            {
                SPixel  *p, *pDest = (SPixel *)pixel;
                SPixelA *p1, *pSrc  = (SPixelA *)pbSrc;
                for (Int32 j = 0; j != h; ++j)
                {
                    p = pDest;
                    p1 = pSrc;
                    pSrc = (SPixelA *)((PByte)pSrc + stride);
                    pDest = (SPixel *)((PByte)pDest + dstsr);
                    for (Int32 k = 0; k != w; ++k)
                    {
                        Byte a = p1->a;
                        *(LPCOLORREF)p++ = RGB(BLEND(GetRValue(m_bkColor), p1->r, a),
                                               BLEND(GetGValue(m_bkColor), p1->g, a),
                                               BLEND(GetBValue(m_bkColor), p1->b, a));
                        ++p1;
                    }
                }
            }
            else if (Bpp == 1)
            {
                PByte   p2, pSrc = pbSrc;
                SPixel *p, *pDest = (SPixel *)pixel;
                for (Int32 j = 0; j != h; ++j)
                {
                    p = pDest;
                    p2 = pSrc;
                    pSrc = (PByte)pSrc + stride;
                    pDest = (SPixel *)((PByte)pDest + dstsr);
                    for (Int32 k = 0; k != w; ++k)
                    {
                        *(LPCOLORREF)p++ = palette[*p2++];
                    }
                }
            }

            bmpInfo.bmiHeader.biWidth  = w;
            bmpInfo.bmiHeader.biHeight = h;
            StretchDIBits(hDC, xDest, yDest, w, h,
                0, 0, w, h, pixel, &bmpInfo, DIB_RGB_COLORS, SRCCOPY);
            xDest += w;
            pbSrc += w * Bpp;
        }

        height -= BlockSize;
        xDest = 0;
        yDest += BlockSize;
    }

#else
    LPVoid lpBits;
    if (m_bmpInfo.bmiHeader.biHeight <= m_CliSize.cy)
    {
        ySrc = 0;
        yDest = m_bmpInfo.bmiHeader.biHeight - m_CliSize.cy;
    }
    else
    {
        ySrc = m_bmpInfo.bmiHeader.biHeight - m_CliSize.cy - m_iVSPos;
        yDest = 0;
    }

    header = (SBitMapHeader *)m_pImage->pFrame[m_uiCurrentFrame].buffer;
    lpBits = (PByte)header + header->dwRawOffset;
    StretchDIBits(hDC, 0, yDest, m_CliSize.cx, m_CliSize.cy, m_iHSPos, ySrc,
        m_CliSize.cx, m_CliSize.cy, lpBits, &m_bmpInfo, DIB_RGB_COLORS, SRCCOPY);
#endif

    EndPaint(&ps);

    return NO_ERROR;
}

HRESULT CImageCtrl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled)
{
    int cxClient, cyClient;
    SCROLLINFO siv, sih;

    cxClient = LOWORD(lParam);
    cyClient = HIWORD(lParam);
    m_CliSize.cx = cxClient;
    m_CliSize.cy = cyClient;

    siv.cbSize = sizeof(siv);
    siv.nMin   = 0;
    siv.fMask  = SIF_RANGE|SIF_PAGE;
    sih = siv;

    if (m_pImage)
    {
        UInt32 w, h;
        h = m_bmpInfo.bmiHeader.biHeight;
        w = m_bmpInfo.bmiHeader.biWidth;
        siv.nMax  = h;
        siv.nPage = cyClient;
        sih.nMax  = w;
        sih.nPage = cxClient;
    }
    else
    {
        siv.nMax = sih.nMax = 0;
    }

    SetScrollInfo(SB_VERT, &siv, True);
    SetScrollInfo(SB_HORZ, &sih, True);
    siv.fMask = sih.fMask = SIF_POS;
    GetScrollInfo(SB_VERT, &siv);
    GetScrollInfo(SB_HORZ, &sih);
    m_iHSPos = sih.nPos;
    m_iVSPos = siv.nPos;

    return NO_ERROR;
}

HRESULT CImageCtrl::OnScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled)
{
    int nBar;
    SCROLLINFO si;

    if (m_pImage == NULL)
        return NO_ERROR;

    si.cbSize = sizeof(si);
    si.fMask  = SIF_ALL;
    nBar = uMsg == WM_VSCROLL ? SB_VERT : SB_HORZ;
    GetScrollInfo(nBar, &si);

    switch (LOWORD(wParam))
    {
        case SB_THUMBTRACK:
        case SB_THUMBPOSITION:
            si.nPos = HIWORD(wParam);
            break;

        case SB_PAGEDOWN:
            si.nPos += si.nPage;
            break;

        case SB_PAGEUP:
            si.nPos -= si.nPage;
            break;

        case SB_LINEUP:
            si.nPos -= 10;
            break;

        case SB_LINEDOWN:
            si.nPos += 10;
            break;
    }

    si.fMask = SIF_POS;
    SetScrollInfo(nBar, &si, True);
    GetScrollInfo(nBar, &si);
    if (uMsg == WM_VSCROLL)
    {
        if (m_iVSPos != si.nPos)
        {
            int delta = m_iVSPos - si.nPos;
            m_iVSPos = si.nPos;
            ScrollWindow(0, delta);
        }
    }
    else if (m_iHSPos != si.nPos)
    {
        int delta = m_iHSPos - si.nPos;
        m_iHSPos = si.nPos;
        ScrollWindow(delta, 0);
    }

    return NO_ERROR;
}

HRESULT CImageCtrl::OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled)
{
    INT16 iScroll = HIWORD(wParam);
    INT32 nBar;
    SCROLLINFO si;

//    nBar = GetAsyncKeyState(VK_CONTROL) < 0 ? SB_HORZ : SB_VERT;
    nBar = GetKeyState(VK_CONTROL) < 0 ? SB_HORZ : SB_VERT;
    si.cbSize = sizeof(si);
    si.fMask  = SIF_POS;
    GetScrollInfo(nBar, &si);
    si.nPos -= iScroll / (INT16)WHEEL_DELTA * 60;
    SetScrollInfo(nBar, &si, True);
    GetScrollInfo(nBar, &si);
    if (nBar == SB_VERT)
    {
        if (m_iVSPos != si.nPos)
        {
            int delta = m_iVSPos - si.nPos;
            m_iVSPos = si.nPos;
            ScrollWindow(0, delta);
        }
    }
    else if (m_iHSPos != si.nPos)
    {
        int delta = m_iHSPos - si.nPos;
        m_iHSPos = si.nPos;
        ScrollWindow(delta, 0);
    }

    return NO_ERROR;
}
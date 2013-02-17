#ifndef _IMAGECTRL_H_
#define _IMAGECTRL_H_

#include "WindowBase.h"
#include "FileDisk.h"
#include "Mem.h"
#include "../Image/Image.h"

using namespace MyWindowClass;

static const ULong BlockSize = 256;
static const ULong ImageBufferSize = BlockSize * BlockSize * sizeof(SPixel) + 16;

class CImageCtrl : public CWindowImpl2
{
protected:
    CMem       m;
    SIZE       m_CliSize;
    Int32      m_iVSPos, m_iHSPos/*, cxCap, cxChar, cyChar*/;
    UInt32     m_uiImgWidth, m_uiImgHeight, m_uiCurrentFrame;
    BITMAPINFO m_bmpInfo;
    SImage    *m_pImage;
    COLORREF   m_bkColor;
    SPixel    (*pixel)[BlockSize];

public:
    CImageCtrl();
    ~CImageCtrl();

    BEGIN_MSG_MAP(CImageCtrl)
        MESSAGE_HANDLER(WM_CREATE,     OnCreate)
        MESSAGE_HANDLER(WM_PAINT,      OnPaint)
        MESSAGE_HANDLER(WM_SIZE,       OnSize)
//        MESSAGE_HANDLER(WM_COMMAND,    OnCommand)
        MESSAGE_HANDLER(WM_VSCROLL,    OnScroll)
        MESSAGE_HANDLER(WM_HSCROLL,    OnScroll)
        MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
    END_MSG_MAP();

    HWND Create(const LPRECT lpRect, HWND hWndParent, HMENU hMenu = NULL, HINSTANCE hInstance = NULL, LPVOID lpParam = NULL);

    Bool   CreateImage(LPCTSTR lpFileName);
    Bool   CreateImage(LPVOID lpData, DWORD dwSize);
    Bool   ShowImage();
    Bool   Refresh();
    Bool   HideImage();
    Bool   DestroyImage();

    UInt32 GetFrameNum();
    UInt32 NextFrame();
    UInt32 PrevFrame();
    UInt32 SetCurrentFrame(UInt32 nFrame);
    UInt32 GetCurrentFrame();
    PBITMAPINFO GetBits(PUInt32 pSize);

protected:
    DECLARE_MSG_HANDLER(OnCreate);
    DECLARE_MSG_HANDLER(OnPaint);
    DECLARE_MSG_HANDLER(OnSize);
//    DECLARE_MSG_HANDLER(OnCommand);
    DECLARE_MSG_HANDLER(OnScroll);
    DECLARE_MSG_HANDLER(OnMouseWheel);

    Void ApplyAlphaChannel(SPixel *pDest, SPixelA *pSrc, UInt32 uSize);
};

#endif /* _IMAGECTRL_H_ */
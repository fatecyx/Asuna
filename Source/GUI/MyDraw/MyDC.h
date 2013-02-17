// MyDC.h: interface for the CMyDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDC_H__B94B44D7_417B_4BC4_9B15_7C3D22FEB640__INCLUDED_)
#define AFX_MYDC_H__B94B44D7_417B_4BC4_9B15_7C3D22FEB640__INCLUDED_

#include "my_common.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyDC : public CClientDC
{
public:
    typedef struct 
    {
        FLOAT X;
        FLOAT Y;
        FLOAT Z;
        FLOAT _X;
    } HOCOORD;
public:
	CMyDC(CWnd *pWnd) : CClientDC(pWnd) {}

public:
	FORCEINLINE COLORREF SetColor(COLORREF crColor);
	BOOL MPDrawLine        (POINT ptEnd);
	BOOL BHDrawLine        (POINT ptEnd);
	BOOL DDADrawLine       (POINT ptEnd);
	BOOL MPDrawCircle      (const LPRECT lpRect);
	VOID DrawPoints        (const LPPOINT lptCenter, LONG x, LONG y);
	BOOL FenceFillRectangle(const LPRECT lpRect);
    BOOL Draw3DDimetric(const LPRECT lpRect);

protected:
	FORCEINLINE COLORREF SetPixel(POINT point, COLORREF crColor);
	FORCEINLINE COLORREF SetPixel(int x, int y, COLORREF crColor);

protected:
	COLORREF m_crColor;
};

FORCEINLINE COLORREF CMyDC::SetColor(COLORREF crColor)
{
	COLORREF crOldColor = m_crColor;
	m_crColor = crColor;
	return crOldColor;
}

FORCEINLINE COLORREF CMyDC::SetPixel(POINT point, COLORREF crColor)
{
	return SetPixel(point.x, point.y, crColor);
}

FORCEINLINE COLORREF CMyDC::SetPixel(int x, int y, COLORREF crColor)
{
	return ::SetPixel(m_hDC, x, y, crColor);
}

#endif // !defined(AFX_MYDC_H__B94B44D7_417B_4BC4_9B15_7C3D22FEB640__INCLUDED_)
// MyDC.cpp: implementation of the CMyDC class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MyDraw.h"
#include "MyDC.h"
#include "Matrix.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

FORCEINLINE int lrintf(float x) // ËÄÉáÎåÈë
{
    __asm cvtss2si eax, x;
}

BOOL CMyDC::DDADrawLine(POINT ptEnd)
{
    LONG x, y;
    float k, yf, xf;
    POINT ptStart;

    GetCurrentPositionEx(m_hDC, &ptStart);

    if (ptStart.x == ptEnd.x && ptStart.y != ptEnd.y)
    {
        int y1, y2;

        if (ptStart.y > ptEnd.y)
        {
            y1 = ptEnd.y;
            y2 = ptStart.y;
        }
        else
        {
            y1 = ptStart.y;
            y2 = ptEnd.y;
        }

        for (int y = y1; y != y2; ++y)
            SetPixel(ptStart.x, y, m_crColor);

        return TRUE;
    }

    k = (float)(ptEnd.y - ptStart.y) / (ptEnd.x - ptStart.x);

    if (k < -1 || k > 1)
    {
        if (ptStart.y > ptEnd.y)
        {
            POINT p = ptEnd;
            ptEnd = ptStart;
            ptStart = p;
        }

        x = ptStart.x;
        y = ptStart.y;
        k = 1 / k;
        xf = (float)x;
        for (; y != ptEnd.y; ++y)
        {
            SetPixel(lrintf(xf), y, m_crColor);
            xf += k;
        }
    }
    else
    {
        if (ptStart.x > ptEnd.x)
        {
            POINT p = ptEnd;
            ptEnd = ptStart;
            ptStart = p;
        }

        x = ptStart.x;
        y = ptStart.y;
        yf = (float)y;
        for (; x != ptEnd.x; ++x)
        {
            SetPixel(x, lrintf(yf), m_crColor);
            yf += k;
        }
    }

    return TRUE;
}

BOOL CMyDC::MPDrawLine(POINT ptEnd)	// -1 < k < 0
{
    LONG x, y, a, b, d, d1, d2;
    POINT ptStart;

    GetCurrentPositionEx(m_hDC, &ptStart);
    if (ptStart.x > ptEnd.x)
    {
        POINT p = ptEnd;
        ptEnd = ptStart;
        ptStart = p;
    }

    x = ptStart.x;
    y = ptStart.y;
    a = y - ptEnd.y;
    b = ptEnd.x - x;
    d = (a << 1) + b;
    d1 = a << 1;
    d2 = (a + b) << 1;

    SetPixel(x, y, m_crColor);
    for (; x <= ptEnd.x; ++x)
    {
        d += d < 0 ? ++y, d2 : d1;
        SetPixel(x, y, m_crColor);
    }

    return TRUE;
}

BOOL CMyDC::BHDrawLine(POINT ptEnd)	// 0 < k < 1
{
    LONG x, y, dx, dy, dk;
    POINT pStart;

    GetCurrentPositionEx(m_hDC, &pStart);
    x = pStart.x;
    y = pStart.y;
    dx = ptEnd.x - x;
    dy = ptEnd.y - y;
    dk = (dy << 1) - dx;

    for (; x <= ptEnd.x; ++x)
    {
        SetPixel(x, y, m_crColor);
        dk += dy << 1;
        if (dk >=0)
        {
            ++y;
            dx -= dx << 1;
        }
    }

    return TRUE;
}

VOID CMyDC::DrawPoints(const LPPOINT lptCenter, LONG x, LONG y)
{
    POINT points[] =
    {
        { lptCenter->x + x, lptCenter->y + y },
        { lptCenter->x - x, lptCenter->y + y },
        { lptCenter->x + x, lptCenter->y - y },
        { lptCenter->x - x, lptCenter->y - y },
        { lptCenter->x + y, lptCenter->y + x },
        { lptCenter->x - y, lptCenter->y + x },
        { lptCenter->x + y, lptCenter->y - x },
        { lptCenter->x - y, lptCenter->y - x },
    };

    for (int i = 0; i != countof(points); ++i)
    {
        SetPixel(points[i].x, points[i].y, m_crColor);
    }
}

BOOL CMyDC::MPDrawCircle(LPRECT lpRect)
{
    LONG  lWidght, lHeight, lRadius, x, y, d;
    POINT ptCenter;

    if (lpRect->left > lpRect->right)
    {
        LONG temp = lpRect->left;
        lpRect->left = lpRect->right;
        lpRect->right = temp;
    }
    if (lpRect->bottom < lpRect->top)
    {
        LONG temp = lpRect->bottom;
        lpRect->bottom = lpRect->top;
        lpRect->top = temp;
    }

    lWidght = lpRect->right  - lpRect->left;
    lHeight = lpRect->bottom - lpRect->top;

    if (lWidght < lHeight)	// square
    {
        lpRect->bottom = lpRect->top + lWidght;
    }
    else if (lWidght > lHeight)
    {
        lpRect->right = lpRect->left + lHeight;
    }

    lRadius = (lpRect->right - lpRect->left) >> 1;
    ptCenter.x = lpRect->left + lRadius;
    ptCenter.y = lpRect->top  + lRadius;
    x = 0;
    y = lRadius;
    d = 1 - lRadius;

    DrawPoints(&ptCenter, x, y);

    while (x <= y)
    {
        ++x;
        d += (x << 1) + 3;
        if (d >= 0)
        {
            d += 2 - (y << 1);
            --y;
        }
        DrawPoints(&ptCenter, x, y);
    }

    return TRUE;
}

BOOL CMyDC::FenceFillRectangle(const LPRECT lpRect)
{
    LONG lMidX, lLeft, lTop, lRight, lBottom;

    lLeft   = min(lpRect->left, lpRect->right);
    lRight  = max(lpRect->left, lpRect->right);
    lTop    = min(lpRect->top,  lpRect->bottom);
    lBottom = max(lpRect->top,  lpRect->bottom);

    lMidX = ((lRight - lLeft) >> 1) + lLeft;

    for (LONG y = lTop; y <= lBottom; ++y)
    {
        for (LONG x1 = lLeft, x2 = lMidX; x1 <= lMidX && x2 <= lRight; ++x1, ++x2)
        {
            SetPixel(x1, y, m_crColor);
            SetPixel(x2, y, m_crColor);
        }
    }

    return TRUE;
}

BOOL CMyDC::Draw3DDimetric(const LPRECT lpRect)
{
    LONG lHeight = lpRect->bottom - lpRect->top;

    HOCOORD hocoord[] = 
    {
        lpRect->left,  lpRect->top,    0,       1, 
        lpRect->right, lpRect->top,    0,       1, 
        lpRect->left,  lpRect->bottom, 0,       1, 
        lpRect->right, lpRect->bottom, 0,       1, 
        lpRect->left,  lpRect->top,    lHeight, 1, 
        lpRect->right, lpRect->top,    lHeight, 1, 
        lpRect->left,  lpRect->bottom, lHeight, 1, 
        lpRect->right, lpRect->bottom, lHeight, 1, 
    };
    CMatrix DimetricMatrix(4, 4, 
                           0.935, 0, -0.118, 0, 
                          -0.354, 0, -0.312, 0, 
                           0,     0,  0.943, 0, 
                           0,     0,  0,     1), 
            RectMatrix(4, 8, 
                       hocoord[0].X, hocoord[0].Y, hocoord[0].Z, hocoord[0]._X, 
                       hocoord[1].X, hocoord[1].Y, hocoord[1].Z, hocoord[1]._X, 
                       hocoord[2].X, hocoord[2].Y, hocoord[2].Z, hocoord[2]._X, 
                       hocoord[3].X, hocoord[3].Y, hocoord[3].Z, hocoord[3]._X, 
                       hocoord[4].X, hocoord[4].Y, hocoord[4].Z, hocoord[4]._X, 
                       hocoord[5].X, hocoord[5].Y, hocoord[5].Z, hocoord[5]._X, 
                       hocoord[6].X, hocoord[6].Y, hocoord[6].Z, hocoord[6]._X, 
                       hocoord[7].X, hocoord[7].Y, hocoord[7].Z, hocoord[7]._X);

    CMatrix m(RectMatrix * DimetricMatrix);
    PFLOAT *pf = (PFLOAT *)m.GetMatrixPointer();

    for (UINT32 l = 0; l != m.GetLineNumber() - 1; ++l)
    {
        POINT p1 = {pf[l][0], pf[l][2]}, 
              p2 = {pf[l + 1][0], pf[l + 1][2]};
        MoveTo(p1);
        LineTo(p2);
    }

    return TRUE;
}
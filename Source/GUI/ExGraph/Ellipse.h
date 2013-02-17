// Ellipse.h: interface for the CEllipse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELLIPSE_H__AABD2509_3DDB_463E_B11E_D4A94D417D86__INCLUDED_)
#define AFX_ELLIPSE_H__AABD2509_3DDB_463E_B11E_D4A94D417D86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <set>
#include "Shape.h"
using std::set;

typedef struct _tagEllipse
{
	DWORD		dwID;
	CRect		rect;
	COLORREF	crFrame;
	COLORREF	crFill;
	WORD		wLineWide;
} tagEllipse;

typedef set<CRect> EllipseInfo;

class CEllipse : public CShape
{
public:
	CEllipse();
	virtual ~CEllipse();

public:
	EllipseInfo::iterator begin();
	EllipseInfo::iterator end();
	EllipseInfo::size_type GetCount();

	virtual void Clear();
	virtual bool DrawAll(CDC *pDC);
	virtual void Serialize(CArchive &ar);

	bool Add(const CRect &Rect);
	bool Add(int left, int top, int right, int bottom);
	bool Add(const CPoint &cpCenter, const DWORD &dwRadius);

protected:
	EllipseInfo m_setEllipses;
	DECLARE_SERIAL(CEllipse)
};

inline EllipseInfo::iterator CEllipse::begin()
{
	return m_setEllipses.begin();
}

inline EllipseInfo::iterator CEllipse::end()
{
	return m_setEllipses.end();
}

inline void CEllipse::Clear()
{
	m_setEllipses.clear();
}

#endif // !defined(AFX_ELLIPSE_H__AABD2509_3DDB_463E_B11E_D4A94D417D86__INCLUDED_)

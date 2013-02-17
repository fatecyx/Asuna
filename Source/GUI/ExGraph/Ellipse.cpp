// Ellipse.cpp: implementation of the CEllipse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExGraph.h"
#include "Ellipse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CEllipse, CObject, 1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEllipse::CEllipse()
{
}

CEllipse::~CEllipse()
{
	m_setEllipses.clear();
}

EllipseInfo::size_type CEllipse::GetCount()
{
	return m_setEllipses.size();
}

bool CEllipse::Add(const CRect &Rect)
{
	return m_setEllipses.insert(Rect).second;
}

bool CEllipse::Add(const CPoint &cpCenter, const DWORD &dwRadius)
{
	return m_setEllipses.insert(CRect(cpCenter.x - dwRadius,	// Left
									 cpCenter.y - dwRadius,		// Top
									 cpCenter.x + dwRadius,		// Right
									 cpCenter.y + dwRadius)		// Bottom
									 ).second;
}

bool CEllipse::Add(int left, int top, int right, int bottom)
{
	return m_setEllipses.insert(CRect(left, top, right, bottom)).second;
}

void CEllipse::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_setEllipses.size();
		for (EllipseInfo::iterator it = begin(); it != end(); ++it)
			ar << *it;
	}
	else
	{
		CRect rect;
		EllipseInfo::size_type size;
		ar >> size;
		while (size--)
		{
			ar >> rect;
			m_setEllipses.insert(rect);
		}
	}
}

bool CEllipse::DrawAll(CDC *pDC)
{
	for (EllipseInfo::iterator it = begin(); it != end(); ++it)
	{
		pDC->Ellipse(&*it);
	}
	return true;
}
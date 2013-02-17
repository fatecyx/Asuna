// Pencil.cpp: implementation of the CPencil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExGraph.h"
#include "Pencil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CPencil, CObject, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPencil::CPencil()
{

}

CPencil::~CPencil()
{
	m_vecPencils.clear();
}

bool CPencil::Add(const CPoint &point)
{
	if ((point.x < 1 && point.x > -1) || (point.y < 1 && point.y > -1)) return false;
	tagPencil pencil = {point};
	m_vecPencils.push_back(pencil);
	return true;
}

bool CPencil::DrawAll(CDC *pDC)
{
	PencilInfo::iterator it = begin();

	if (it == end() || it + 1 == end())
		return false;

	for (; it <= end() - 1; ++it)
	{
		if ((it + 1)->point.x != -1)
		{
			pDC->MoveTo(it->point);
			pDC->LineTo((it + 1)->point);
		}
		else
		{
			++it;			// it += 2;
		}
	}

	return true;
}

void CPencil::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_vecPencils.size();
		for (PencilInfo::iterator it = begin(); it != end(); ++it)
		{
			ar << it->point;
		}
	}
	else
	{
		tagPencil pencil;
		PencilInfo::size_type size;
		ar >> size;
		while (size--)
		{
			ar >> pencil.point;
			m_vecPencils.push_back(pencil);
		}
	}
}
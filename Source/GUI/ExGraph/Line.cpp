// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExGraph.h"
#include "Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CLine, CObject, 1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{

}

CLine::~CLine()
{
	m_vecLines.clear();
}

bool CLine::Add(const tagLine &line)
{
	m_vecLines.push_back(line);
	return true;
}

bool CLine::Add(const CPoint &cpStart, 
				const CPoint &cpEnd, 
				const COLORREF &crFrame /* = 0 */, 
				const COLORREF &crFill /* = 0 */, 
				const WORD &wLineWidth /* = 3 */)
{
	tagLine line = {cpStart, cpEnd, crFrame, crFill, wLineWidth};
	m_vecLines.push_back(line);
	return true;
}

bool CLine::DrawAll(CDC *pDC)
{
	for (LineInfo::iterator it = begin(); it != end(); ++it)
	{
		pDC->MoveTo(it->cpStart);
		pDC->LineTo(it->cpEnd);
	}

	return true;
}

void CLine::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_vecLines.size();
		for (LineInfo::iterator it = begin(); it != end(); ++it)
			ar << (*it).cpStart << (*it).cpEnd << (*it).crFrame 
			   << (*it).crFill << (*it).wLineWidth;
	}
	else
	{
		tagLine line = {0};
		LineInfo::size_type size;
		ar >> size;
		while (size--)
		{
			ar >> line.cpStart >> line.cpEnd >> line.crFrame 
			   >> line.crFill >> line.wLineWidth;
			m_vecLines.push_back(line);
		}
	}
}
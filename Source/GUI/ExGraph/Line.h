// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__9137288D_998A_477C_A727_14075B8A0BFC__INCLUDED_)
#define AFX_LINE_H__9137288D_998A_477C_A727_14075B8A0BFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "Shape.h"
using std::vector;

typedef struct _tagLine
{
	CPoint		cpStart;
	CPoint		cpEnd;
	COLORREF	crFrame;
	COLORREF	crFill;
	WORD		wLineWidth;
} tagLine;

typedef vector<tagLine> LineInfo;

class CLine : public CShape  
{
public:
	CLine();
	virtual ~CLine();

public:
	LineInfo::iterator begin();
	LineInfo::iterator end();
	LineInfo::size_type GetCount();

	virtual void Clear();
	virtual bool DrawAll(CDC *pDC);
	virtual void Serialize(CArchive &ar);

	bool Add(const tagLine &line);
	bool Add(const CPoint &cpStart, 
			 const CPoint &cpEnd, 
			 const COLORREF &crFrame	= 0, 
			 const COLORREF &crFill		= 0,
			 const WORD &wLineWidth		= 3);

protected:
	LineInfo m_vecLines;
	DECLARE_SERIAL(CLine)
};

inline LineInfo::iterator CLine::begin()
{
	return m_vecLines.begin();
}

inline LineInfo::iterator CLine::end()
{
	return m_vecLines.end();
}

inline void CLine::Clear()
{
	m_vecLines.clear();
}

#endif // !defined(AFX_LINE_H__9137288D_998A_477C_A727_14075B8A0BFC__INCLUDED_)

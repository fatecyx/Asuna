// Pencil.h: interface for the CPencil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PENCIL_H__4A8CA1B0_A5BC_4F10_91CA_6E51B2DC38C6__INCLUDED_)
#define AFX_PENCIL_H__4A8CA1B0_A5BC_4F10_91CA_6E51B2DC38C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "Shape.h"
using std::vector;

typedef struct _tagPencil
{
	POINT	point;
} tagPencil;

typedef vector<tagPencil> PencilInfo;

class CPencil : public CShape
{
public:
	CPencil();
	virtual ~CPencil();

public:
	PencilInfo::iterator begin() { return m_vecPencils.begin(); }
	PencilInfo::iterator end()   { return m_vecPencils.end(); }
	PencilInfo::size_type GetCount() { return m_vecPencils.size(); }

	virtual void Clear() { m_vecPencils.clear(); }

	virtual bool DrawAll(CDC *pDC);
	virtual void Serialize(CArchive &ar);

	bool Add(const CPoint &point);

protected:
	PencilInfo m_vecPencils;
	DECLARE_SERIAL(CPencil)

};

#endif // !defined(AFX_PENCIL_H__4A8CA1B0_A5BC_4F10_91CA_6E51B2DC38C6__INCLUDED_)

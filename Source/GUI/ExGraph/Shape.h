// Shape.h: interface for the CShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPE_H__29AC7B8D_C862_495E_B3D5_2A8C6DDC25D6__INCLUDED_)
#define AFX_SHAPE_H__29AC7B8D_C862_495E_B3D5_2A8C6DDC25D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <set>
using std::set;

class CShape : public CObject  
{
public:
	CShape();
	virtual ~CShape();

public:
	virtual void Clear() = 0;
	virtual bool DrawAll(CDC *pDC) = 0;
	virtual void Serialize(CArchive &ar) = 0;
};

#endif // !defined(AFX_SHAPE_H__29AC7B8D_C862_495E_B3D5_2A8C6DDC25D6__INCLUDED_)

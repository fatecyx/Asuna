// ExGraphDoc.h : interface of the CExGraphDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXGRAPHDOC_H__F8E04951_C0A6_4B63_B6E6_AA2049B4D235__INCLUDED_)
#define AFX_EXGRAPHDOC_H__F8E04951_C0A6_4B63_B6E6_AA2049B4D235__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Pencil.h"
#include "Line.h"
#include "Ellipse.h"

class CExGraphDoc : public CDocument
{
protected: // create from serialization only
	CExGraphDoc();
	DECLARE_DYNCREATE(CExGraphDoc)

// Attributes
public:
	CObArray	m_oaShapes;
	CPencil		m_Pencils;
	CLine		m_Lines;
	CEllipse	m_Ellipses;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExGraphDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExGraphDoc();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExGraphDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXGRAPHDOC_H__F8E04951_C0A6_4B63_B6E6_AA2049B4D235__INCLUDED_)

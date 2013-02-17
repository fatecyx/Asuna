// ExGraphDoc.cpp : implementation of the CExGraphDoc class
//

#include "stdafx.h"
#include "ExGraph.h"

#include "ExGraphDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum
{
	PENCIL,
	LINE,
	ELLIPSE,
	POLY,
	CLEAR,
	NONE
};

/////////////////////////////////////////////////////////////////////////////
// CExGraphDoc

IMPLEMENT_DYNCREATE(CExGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CExGraphDoc, CDocument)
	//{{AFX_MSG_MAP(CExGraphDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExGraphDoc construction/destruction

CExGraphDoc::CExGraphDoc()
{
	m_oaShapes.Add(&m_Pencils);
	m_oaShapes.Add(&m_Lines);
	m_oaShapes.Add(&m_Ellipses);
}

CExGraphDoc::~CExGraphDoc()
{
}

BOOL CExGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExGraphDoc serialization

void CExGraphDoc::Serialize(CArchive& ar)
{
	for (INT_PTR ix = 0, iSize = m_oaShapes.GetSize(); ix != iSize; ++ix)
	{
		m_oaShapes[ix]->Serialize(ar);
	}
}
/////////////////////////////////////////////////////////////////////////////
// CExGraphDoc commands

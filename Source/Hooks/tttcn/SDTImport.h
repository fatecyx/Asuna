#ifndef _SDTIMPORT_H_
#define _SDTIMPORT_H_


#include "TtTSDT.h"

class SDTImport : public TtTSDT
{
public:
	SDTImport(PBYTE pbSDT, DWORD dwSize);
	~SDTImport();

public:
	BOOL Init();
	INT32 ImportLine(LPCSTR lpText, ULONG dwOffSet);

private:
	LONG   m_lChangeSize;
	PBYTE  m_pbSDT;
	DWORD  m_dwCurOffset, m_dwFileSize, m_dwMaxPointers, m_dwPointers;
	PULONG *m_pulPointers;
};

#endif /* _SDTIMPORT_H_ */
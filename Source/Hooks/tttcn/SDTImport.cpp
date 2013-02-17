
#include "SDTImport.h"
#include "my_mem.h"

SDTImport::SDTImport(PBYTE pbSDT, DWORD dwSize) : m_pbSDT(pbSDT), m_dwFileSize(dwSize)
{
	m_pulPointers     = NULL;
	m_lChangeSize     = 0;
	m_dwCurOffset    = BEGIN_OFFSET;
}

SDTImport::~SDTImport()
{
	if (m_pulPointers)
		free(m_pulPointers);
}

BOOL SDTImport::Init()
{
	if (m_pbSDT == NULL)
		return FALSE;

	BYTE  byte;
	PBYTE pbSDT, pbEnd;

	pbSDT = m_pbSDT;
	pbEnd = pbSDT + m_dwFileSize;
	pbSDT += BEGIN_OFFSET;
	
	m_dwPointers = 0;
	m_dwMaxPointers = 10;
	m_pulPointers = (PULONG *)calloc(m_dwMaxPointers * sizeof(*m_pulPointers), 1);
	if (m_pulPointers == NULL)
		return FALSE;

	while (pbSDT <= pbEnd)
	{
		switch (*(PWORD)pbSDT)
		{
		case TEXT_DIALOG:
		case TEXT_DIALOG_CONTINUE:
			pbSDT += *(PWORD)(pbSDT + 2) + 2;
			continue;

		case TEXT_MENU:
		case TEXT_NAME:
			pbSDT += *(pbSDT + 2) + 1;
			continue;

		case POINTER_06:
			byte = *(pbSDT + 4);
			if (byte != 0x09 && byte != 0x01)
			{
				++pbSDT;
				continue;
			}
			pbSDT += 5;
			break;

		case POINTER_07:
			if (*(WORD *)(pbSDT + 3) != 0x0904 && *(WORD *)(pbSDT + 3) != 0x0205)
			{
				++pbSDT;
				continue;
			}
			pbSDT += 8;
			break;

		default:
			++pbSDT;
			continue;
		}

		if (m_dwPointers == m_dwMaxPointers)
		{
			m_dwMaxPointers += m_dwMaxPointers - (m_dwMaxPointers >> 1);
			m_pulPointers = (PULONG *)realloc(m_pulPointers, m_dwMaxPointers);
		}
		if (*(LPDWORD)pbSDT >= BEGIN_OFFSET && *(LPDWORD)pbSDT != -1)
		{
			m_pulPointers[m_dwPointers++] = (PULONG)pbSDT;
		}
		pbSDT += 4;
	}

	return TRUE;
}

INT32 SDTImport::ImportLine(LPCSTR lpText, ULONG ulOffSet)
{
	INT32 iChange, iNewLength, iOldLength;
	DWORD dwSizeToMove;
	PBYTE pbSDT, pbEnd;

	ulOffSet += m_lChangeSize;
	pbSDT = m_pbSDT + ulOffSet;
	pbEnd = m_pbSDT + m_dwFileSize;
	iNewLength = iChange = 0;

	while (*lpText != '\n' && *lpText)
	{
		++lpText;
		++iNewLength;
	}

	lpText -= iNewLength;

	switch (*(PWORD)pbSDT)
	{
	case TEXT_DIALOG:
	case TEXT_DIALOG_CONTINUE:
		pbSDT += 2;
		iOldLength = (INT32)*(PWORD)pbSDT;
		*(PWORD)pbSDT = iNewLength;
		pbSDT += 2;
		break;

	case TEXT_MENU:
	case TEXT_NAME:
		pbSDT += 2;
		iOldLength = (INT32)*(PBYTE)pbSDT;
		*(PBYTE)pbSDT = iNewLength;
		++pbSDT;
		break;

	default:
		return 0;
	}

	iChange = iNewLength - iOldLength;
	m_lChangeSize += iChange;
	dwSizeToMove = m_dwFileSize - (pbSDT + iOldLength - m_pbSDT);
	memmove(pbSDT + iNewLength, pbSDT + iOldLength, dwSizeToMove);
	memcpy(pbSDT, lpText, iNewLength);
	m_dwFileSize += iChange;
	*(LPDWORD)(m_pbSDT + 4) = m_dwFileSize;

	if (iChange)
	{
		for (UINT i = 0; i != m_dwPointers; ++i)
		{
			PULONG *p = m_pulPointers + i;

			*(PBYTE *)p += iChange;
			if (**p > ulOffSet || *(LPWORD)((PBYTE)*p - 5) == 0x205)
				**p += iChange;
		}
	}
	
	return iNewLength;
}
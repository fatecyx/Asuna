// MTwistEngine
#pragma comment(lib, "shlwapi.lib")

#include "thFXTPacker.h"
#include <Shlwapi.h>
#include <tchar.h>
#include <stdio.h>
#include "my_mem.h"

bool WINAPI thFXTPacker::Init()
{
	TCHAR *szFileName;
	DWORD dwRead;

	if (m_byMode == ERR)
	{
		return false;
	}

	if (m_byMode == DEC)
	{
		m_hFile = CreateFile(m_szName, 
			GENERIC_READ, 
			FILE_SHARE_READ, 
			NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			NULL);
		if (m_hFile == INVALID_HANDLE_VALUE)
		{
			_tprintf(_T("Can't open \"%s\".\n"), m_szName);
			return false;
		}
		ReadFile(m_hFile, &m_wFileNum, 2, &dwRead, NULL);
		ReadFile(m_hFile, &m_dwHeaderSize, 4, &dwRead, NULL);
		m_pbHeader = (PBYTE)HeapAlloc(m_hHeap, 0, m_dwHeaderSize);
		ReadFile(m_hFile, m_pbHeader, m_dwHeaderSize, &dwRead, NULL);
		DecodeFileName(m_pbHeader, m_dwHeaderSize);
		
		szFileName = PathFindFileName(m_szName);
		if (szFileName != m_szName)
		{
			TCHAR c;
			c = *szFileName;
			*szFileName = 0;
			SetCurrentDirectory(m_szName);
			*szFileName = c;
		}
	}
	else
	{
		SetCurrentDirectory(m_szName);
	}

	return true;
}

void WINAPI thFXTPacker::Pack()
{
	int iLength;
	TCHAR szFile[MAX_PATH];

	if (m_byMode != ENC)
	{
		_tprintf(_T("\"%s\" isn't a directory.\n"));
		return;
	}

	iLength = wsprintf(szFile, _T("%s"), PathFindFileName(m_szName)) - 1;
	if (szFile[iLength] == '\\' || szFile[iLength] == '/')
	{
		szFile[iLength] = 0;
	}
	lstrcat(szFile, _T(".dat"));
	m_hFile = CreateFile(szFile, 
					GENERIC_READ|GENERIC_WRITE, 
					FILE_SHARE_READ|FILE_SHARE_WRITE, 
					NULL, 
					CREATE_ALWAYS, 
					FILE_ATTRIBUTE_NORMAL, 
					NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf("CreateFile() failed: \"%s\".\n", szFile);
		return;
	}

	SetConsoleTitle(m_szName);

	// reserve 6 bytes for file number and size of file names
	WriteFile(m_hFile, &iLength, 6, (LPDWORD)&iLength, NULL);
	m_dwVectorSize = 1000;
	m_phInFiles = (HANDLE *)HeapAlloc(m_hHeap, 0, m_dwVectorSize * sizeof(*m_phInFiles));
	WritePackageHeader(m_hFile, PathFindFileName(m_szName), _T("*.*"));
	WritePackageData(m_hFile, &m_opt);

	_tprintf(_T("total: %d\n"), m_wFileNum);
}

void PrintErrMsg(DWORD dwMsgID)
{
	LPSTR lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dwMsgID, 0, (LPTSTR)&lpMsgBuf, 0, NULL);
	
	printf("%s\n", lpMsgBuf);
	LocalFree(lpMsgBuf);
}

bool WINAPI thFXTPacker::WritePackageData(HANDLE hFile, sDecOpt *opt)
{
	BYTE   c, byMode;
	PBYTE  pbHeader, pbFile, pbBuffer, pbByte, pExt;
	DWORD  dwOffset, dwWritten, dwMaxSize;
	HANDLE hMap;
	thFileName *s;

	dwMaxSize      = 0;
	m_dwHeaderSize = SetFilePointer(hFile, 0, 0, FILE_CURRENT);
	pbBuffer        = (PBYTE)HeapAlloc(m_hHeap, 0, 0);
	pbHeader       = (PBYTE)HeapAlloc(m_hHeap, 0, m_dwHeaderSize);
	SetFilePointer(hFile, 0, 0, FILE_BEGIN);
	ReadFile(hFile, pbHeader, m_dwHeaderSize, &dwOffset, NULL);

	*(LPWORD)pbHeader = m_wFileNum;
	*(LPDWORD)(pbHeader + 2) = m_dwHeaderSize - 6;
	pbByte = pbHeader + 6;
	for (WORD i = 0; i != m_wFileNum; ++i)
	{
		s = (thFileName *)pbByte;
		s->dwOffset = dwOffset;
		pbByte += sizeof(*s) - sizeof(s->cName) + s->byLength;
		hMap = CreateFileMapping(m_phInFiles[i], NULL, PAGE_READONLY, 0, s->dwSize, NULL);
		if (hMap == NULL)
		{
#ifdef DEBUG
			PrintErrMsg(GetLastError());
#endif
			*pbByte = 0;
			_tprintf(_T("CreateFileMapping() failed at \"%s\"\n"), &s->cName);
			return false;
		}

		pbFile = (PBYTE)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
		CloseHandle(hMap);
		if (pbFile == NULL)
		{
#ifdef DEBUG
			PrintErrMsg(GetLastError());
#endif
			*pbByte = 0;
			_tprintf(_T("MapViewOfFile() failed at \"%s\"\n"), &s->cName);
			return false;
		}

		if (s->dwSize > dwMaxSize)
		{
			dwMaxSize = s->dwSize;
			pbBuffer = (PBYTE)HeapReAlloc(m_hHeap, 0, pbBuffer, dwMaxSize);
		}
		memcpy(pbBuffer, pbFile, s->dwSize);
		UnmapViewOfFile(pbFile);
		c = (&s->cName)[s->byLength];
		pExt = (PBYTE)&s->cName + s->byLength - 4;
		(&s->cName)[s->byLength] = 0;
		if (*(DWORD *)pExt == '0vc.' && opt->bDecodeCv0)
		{
			byMode = CV0;
		}
		else if (*(DWORD *)pExt == '1vc.' && opt->bDecodeCv1)
		{
			byMode = CV1;
		}
		else if (*(DWORD *)pExt == 'pmb.' && opt->bDecodeCv2)
		{
			byMode = DISABLE;
		}
		else if (*(DWORD *)pExt == '3vc.' && opt->bDecodeCv3)
		{
			byMode = CV3;
		}
		else
		{
			byMode = DISABLE;
		}

		if (byMode != DISABLE)
			EncodeCvFile(pbBuffer, &s->dwSize, byMode);

		EncodeFile(pbBuffer, s->dwOffset, s->dwSize);
		WriteFile(hFile, pbBuffer, s->dwSize, &dwWritten, NULL);
		dwOffset += dwWritten;
	}

	EncodeFileName(pbHeader + 6, m_dwHeaderSize - 6);
	SetFilePointer(hFile, 0, 0, FILE_BEGIN);
	WriteFile(hFile, pbHeader, m_dwHeaderSize, &dwWritten, NULL);
	HeapFree(m_hHeap, 0, pbHeader);
	HeapFree(m_hHeap, 0, pbBuffer);

	return true;
}

bool WINAPI thFXTPacker::WritePackageHeader(HANDLE hFile, LPCTSTR lpDirectory, LPCTSTR lpFileName)
{
	CHAR     szFile[MAX_PATH];
	DWORD    dwSize, dwSizeHigh, dwRead, dwAttribute;
	HANDLE   hFind, hInFile;
	thHeader header;
	WIN32_FIND_DATA wfd;

	hFind = FindFirstFile(lpFileName, &wfd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	do
	{
		if (wfd.cFileName[0] == '.')
			continue;

		dwAttribute = GetFileAttributes(wfd.cFileName);
		if (dwAttribute == 0xFFFFFFFF)
			continue;
		
		wsprintf(szFile, "%s\\%s", lpDirectory, wfd.cFileName);
		if (dwAttribute & FILE_ATTRIBUTE_DIRECTORY)
		{
			SetCurrentDirectoryA(wfd.cFileName);
			WritePackageHeader(hFile, szFile, lpFileName);
			SetCurrentDirectoryA("..");
			continue;
		}
		ReplaceBackSlash(szFile);
		_tprintf(_T("%s ... "), szFile);
		hInFile = CreateFile(wfd.cFileName, 
					GENERIC_READ, 
					FILE_SHARE_READ, 
					NULL, 
					OPEN_EXISTING, 
					FILE_ATTRIBUTE_NORMAL, 
					NULL);
		if (hInFile == INVALID_HANDLE_VALUE)
		{
			_tprintf(_T("failed\n"));
			continue;
		}
		dwSize = GetFileSize(hInFile, &dwSizeHigh);
		if (dwSizeHigh)
		{
			_tprintf(_T("too big\n"));
			CloseHandle(hInFile);
		}
		else
		{
			header.dwSize = dwSize;
			header.byLength = lstrlen(szFile);
			lstrcpyA(header.szName, szFile);
			WriteFile(hFile, &header, 
				sizeof(header) - sizeof(header.szName) + header.byLength, &dwRead, NULL);
			_tprintf(_T("OK\n"));
			++m_wFileNum;
			if (m_wFileNum > m_dwVectorSize)
			{
				m_dwVectorSize += m_wFileNum >> 1;
				m_phInFiles = (HANDLE *)HeapReAlloc(m_hHeap, 
									0, m_phInFiles, m_dwVectorSize * sizeof(*m_phInFiles));
			}
			m_phInFiles[m_wFileNum - 1] = hInFile;
		}
	} while (FindNextFile(hFind, &wfd));

	return true;
}

void WINAPI thFXTPacker::ReplaceBackSlash(LPTSTR lpFileName)
{
	DWORD i, j;

	for (i = 0, j = 0; lpFileName[i]; ++j, ++i)
	{
		if (lpFileName[i] == '\\' || lpFileName[i] == '/')
		{
			lpFileName[j] = '/';
			++i;
			if (lpFileName[i])
			{
				while (lpFileName[i] == '\\' || lpFileName[i] == '/') ++i;
				--i;
			}
		}
		else
		{
			lpFileName[j] = lpFileName[i];
		}
	}
	lpFileName[j] = 0;
}

void WINAPI thFXTPacker::EncodeFileName(PBYTE pbBuffer, DWORD dwBufSize)
{
	DecodeFileName(pbBuffer, dwBufSize);
}

void WINAPI thFXTPacker::DecodeFileName(PBYTE pbBuffer, DWORD dwBufSize)
{
	CHAR c, u;
	DWORD dwCount, *p;
	const static DWORD dwSize = 624;

	p = (DWORD *)HeapAlloc(m_hHeap, 0, dwSize * sizeof(*p));
	dwCount = InitMask(p, dwBufSize + 6, dwSize);

	for (DWORD i = 0; i != dwBufSize; ++i)
	{
		pbBuffer[i] ^= GetMask(p, &dwCount, dwSize);
	}
	c = (CHAR)0xC5;
	u = (CHAR)0x83;
	for (DWORD i = 0; i != dwBufSize; ++i)
	{
		pbBuffer[i] ^= c;
		c += u;
		u += 0x53;
	}

	HeapFree(m_hHeap, 0, p);
}

void WINAPI thFXTPacker::ExtractAllFiles()
{
	WORD wCurFile = 1;
	thFileName *s;

	SetConsoleTitle(m_szName);
	for (PBYTE p = m_pbHeader; wCurFile <= m_wFileNum; ++wCurFile)
	{
		_tprintf(_T("(%d/%d): "), wCurFile, m_wFileNum);
		s = (thFileName *)p;
		ExtractFileByHeader(m_hFile, s, &m_opt);
		p += 8 + s->byLength + 1;
	}
}

void WINAPI thFXTPacker::ExtractFileByHeader(HANDLE hFile, thFileName *s, sDecOpt *opt, TCHAR *szOutFile)
{
	DWORD  dwRead;
	HANDLE hOutFile;
	CHAR  c, *pExt;
	BYTE  byMode;
	PBYTE pbBuffer;

	if (s->dwSize == 0)
	{
		c = (&s->cName)[s->byLength];
		(&s->cName)[s->byLength] = 0;
		_tprintf(_T("Empty file \"%s\"\n"), &s->cName);
		(&s->cName)[s->byLength] = c;
		return;
	}

	pbBuffer = (PBYTE)HeapAlloc(m_hHeap, 0, s->dwSize);
	if (pbBuffer == NULL)
	{
		return;
	}

	SetFilePointer(hFile, s->dwOffset, NULL, FILE_BEGIN);
	ReadFile(hFile, pbBuffer, s->dwSize, &dwRead, NULL);

	DecodeFile(pbBuffer, s->dwOffset, s->dwSize);
	for (CHAR *p = &s->cName + s->byLength - 1; p != &s->cName; --p)
	{
		if (*p == '\\' || *p == '/')
		{
			c = *p;
			*p = 0;
			MyCreateDirectory(&s->cName);
			*p = c;
			break;
		}
	}

	c = (&s->cName)[s->byLength];
	pExt = &s->cName + s->byLength - 4;
	(&s->cName)[s->byLength] = 0;
	if (*(DWORD *)pExt == '0vc.' && opt->bDecodeCv0)
	{
		byMode = CV0;
	}
	else if (*(DWORD *)pExt == '1vc.' && opt->bDecodeCv1)
	{
		byMode = CV1;
	}
	else if (*(DWORD *)pExt == '2vc.' && opt->bDecodeCv2)
	{
		if (*pbBuffer < 0x18)
		{
			byMode = DISABLE;
		}
		else
		{
			byMode = CV2;
			*(DWORD *)pExt = 'pmb.';
		}
	}
	else if (*(DWORD *)pExt == '3vc.' && opt->bDecodeCv3)
	{
		byMode = CV3;
	}
	else
	{
		byMode = DISABLE;
	}

	hOutFile = CreateFile(szOutFile ? szOutFile : &s->cName, 
					GENERIC_WRITE, 
					FILE_SHARE_WRITE, 
					NULL, 
					CREATE_ALWAYS, 
					FILE_ATTRIBUTE_NORMAL, 
					NULL);
	if (hOutFile != INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("\"%s\"\n"), &s->cName);

		if (byMode != DISABLE)
		{
			pbBuffer = DecodeCvFile(pbBuffer, &s->dwSize, byMode);
		}
		WriteFile(hOutFile, pbBuffer, s->dwSize, &dwRead, NULL);
		CloseHandle(hOutFile);
	}
	(&s->cName)[s->byLength] = c;
	HeapFree(m_hHeap, 0, pbBuffer);
}

void WINAPI thFXTPacker::DecodeFile(PBYTE pbBuffer, DWORD dwOffset, DWORD dwSize)
{
	CHAR xor;
	xor = (CHAR)((dwOffset >> 1) | 0x23);
	for (DWORD i = 0; i != dwSize; ++i)
	{
		pbBuffer[i] ^= xor;
	}
}

void WINAPI thFXTPacker::EncodeFile(PBYTE pbBuffer, DWORD dwOffset, DWORD dwSize)
{
	DecodeFile(pbBuffer, dwOffset, dwSize);
}

PBYTE WINAPI thFXTPacker::EncodeCvFile(PBYTE pbBuffer, DWORD *pdwSize, BYTE byMode)
{
	switch (byMode)
	{
	case CV0:
	case CV1:
		pbBuffer = DecodeCvFile(pbBuffer, pdwSize, byMode);
		break;
	}

	return pbBuffer;
}

PBYTE WINAPI thFXTPacker::DecodeCvFile(PBYTE pbBuffer, DWORD *pdwSize, BYTE byMode)
{
	CHAR xor, u;

	switch (byMode)
	{
	case CV0:
	case CV1:
		u   = (CHAR)0x71;
		xor = (CHAR)0x8B;
		for (DWORD i = 0; i != *pdwSize; ++i)
		{
			pbBuffer[i] ^= xor;
			xor += u;
			u += 0x95;
		}
		break;

	case CV2:
		{
			PBYTE pbBitmap;
			BYTE  byBpp;
			DWORD dwWidth, dwHeight, dwTrueWidth;

			byBpp = *pbBuffer < 0x18 ? 1 : 4;
			dwWidth     = *(DWORD *)(pbBuffer + 1);
			dwHeight    = *(DWORD *)(pbBuffer + 5);
			dwTrueWidth = *(DWORD *)(pbBuffer + 9);
			*pdwSize = 0x36 + dwWidth * dwHeight * byBpp;
			pbBitmap = (PBYTE)HeapAlloc(m_hHeap, 0, *pdwSize);
			for (DWORD i = 0; i != dwHeight; ++i)
			{
				memcpy(pbBitmap + 0x36 + (dwHeight - i - 1) * dwWidth * byBpp, pbBuffer + 0x11 + i * dwTrueWidth * byBpp, dwWidth * byBpp);
			}

			HeapFree(m_hHeap, 0, pbBuffer);
			pbBuffer = pbBitmap;

			memset(pbBitmap, 0, 0x36);
			*(DWORD *)pbBitmap = 'MB';
			*(DWORD *)(pbBitmap + 0x02) = *pdwSize;
			*(DWORD *)(pbBitmap + 0x0A) = 0x36;
			*(DWORD *)(pbBitmap + 0x0E) = 0x28;
			*(DWORD *)(pbBitmap + 0x12) = dwWidth;
			*(DWORD *)(pbBitmap + 0x16) = dwHeight;
			*(DWORD *)(pbBitmap + 0x1A) = 1;
			*(DWORD *)(pbBitmap + 0x1C) = byBpp == 4 ? 32 : 8;
		}
		break;
	}

	return pbBuffer;
}

BYTE WINAPI thFXTPacker::GetMask(DWORD *p, DWORD *pdwCount, DWORD dwArraySize)
{
	DWORD i, val;
	int mask[] = {0, 0x9908B0DF};

	if (*pdwCount >= 0x270)
	{
		if (*pdwCount == 0x271)
			InitMask(p, 0x1571, dwArraySize);

		for (i = 0; i != 0xE3; ++i)
		{
			val = p[i + 1];
			val = (val ^ p[i]) & INT_MAX;
			val ^= p[i];
			val = (val >> 1) ^ mask[val & 1];
			val ^= p[396 + i + 1];
			p[i] = val;
		}

		if (i < 0x26F)
		{
			while (i != dwArraySize - 1)
			{
				val = (p[i] ^ p[i + 1]) & INT_MAX;
				val ^= p[i];
				val = (val >> 1) ^ (mask[val & 1] ^ p[i - 0xE4 + 1]);
				p[i++] = val;
			}
		}

		val = p[0] ^ p[dwArraySize - 1];
		val &= INT_MAX;
		val ^= p[dwArraySize - 1];
		val = (val >> 1) ^ mask[val & 1];
		p[dwArraySize - 1] = val ^ p[396];
		i = 0;
	}
	else
	{
		i = *pdwCount;
	}

	val = p[i++];
	*pdwCount = i;
	val = val ^ (val >> 0x0B);
	val = ((val & 0xFF3A58AD) << 7) ^ val;
	val = ((val & 0xFFFFDF8C) << 0x0F) ^ val;
	val = val ^ (val >> 0x12);

	return (BYTE)val;
}

DWORD WINAPI thFXTPacker::InitMask(DWORD *p, DWORD dwSize, DWORD dwArraySize)
{
	DWORD dwCount = 1;

	p[0] = dwSize;
	for (DWORD i = 0; i != dwArraySize - 1; ++i)
	{
		p[i + 1] = ((p[i] >> 0x1E) ^ p[i]) * 0x6C078965 + dwCount++;
	}

	return dwCount;
}

thFXTPacker::thFXTPacker(TCHAR *szName, sDecOpt *opt) : m_szName(szName)
{
	DWORD dwAtt;

	m_phInFiles = NULL;
	m_pbHeader = m_pbData = NULL;

	if (opt)
	{
		m_opt = *opt;
	}
	else
	{
		*(DWORD *)&m_opt = 0x01010101;
	}

	m_wFileNum = 0;
	m_hHeap = GetProcessHeap();
	dwAtt = GetFileAttributes(szName);
	if (dwAtt == 0xFFFFFFFF)
	{
		m_byMode = ERR;
	}
	else if (dwAtt & FILE_ATTRIBUTE_DIRECTORY)
	{
		m_byMode = ENC;
	}
	else
	{
		m_byMode = DEC;
	}
}

thFXTPacker::~thFXTPacker()
{
	if (m_hFile != INVALID_HANDLE_VALUE)
		CloseHandle(m_hFile);

	if (m_pbHeader)
		HeapFree(m_hHeap, 0, m_pbHeader);

	if (m_phInFiles)
	{
		for (WORD i = 0; i != m_wFileNum; ++i)
			CloseHandle(m_phInFiles[i]);
		HeapFree(m_hHeap, 0, m_phInFiles);
	}

	if (m_pbData)
		HeapFree(m_hHeap, 0, m_pbData);

}

BOOL WINAPI thFXTPacker::MyCreateDirectory(LPCTSTR lpPathName)
{
	LPTSTR lpPath = (LPTSTR)lpPathName;

	if (*lpPath == 0)
	{
		return FALSE;
	}

	do
	{
		if (*lpPath == '\\' || *lpPath == '/')
		{
			if (*(lpPath + 1) == 0)
			{
				break;
			}

			TCHAR c = *lpPath;
			*lpPath = 0;
			CreateDirectory(lpPathName, NULL);
			*lpPath = c;
		}
		++lpPath;
	} while (*lpPath);

	return CreateDirectory(lpPathName, NULL);
}

void thFXTPacker::Help_Unpack(TCHAR *szName)
{
	printf("Usage:Drag file(s) to me\n"
		   "or    %s x.dat /n0 xx.dat /n1 xxx.dat\n\n"
		   "说明: \n"
		   "解包时会自动解密cv0,cv1和部分cv2文件,\n"
		   "在每个文件名后加上/n0,/n1,/n2即可禁用相应文件的自动解密. \n", 
		   PathFindFileName(szName));
}

void thFXTPacker::Help_Pack(TCHAR *szName)
{
	printf("Usage:Drag directory(ies) to me\n"
		   "or    %s x /n0 xx /n1 xxx\n\n"
		   "说明: \n"
		   "封包时会自动加密cv0,cv1和bmp文件,\n"
		   "在每个文件名后加上/n0,/n1,/n2即可禁用相应文件的自动加密. \n", 
		   PathFindFileName(szName));
}
#ifndef _thFXTPacker_h_
#define _thFXTPacker_h_

#include <Windows.h>
#include "my_common.h"

#undef WINAPI
#define WINAPI 

class thFXTPacker
{
public:
	enum mode {ENC, DEC, ERR};
	enum dec_opt {DISABLE, CV0, CV1, CV2, CV3};

#pragma pack(1)
	typedef struct
	{
		DWORD dwOffset;
		DWORD dwSize;
		BYTE  byLength;
		CHAR  cName;
	} thFileName;

	typedef struct
	{
		DWORD dwOffset;
		DWORD dwSize;
		BYTE  byLength;
		CHAR  szName[UCHAR_MAX];
	} thHeader;
#pragma pack()

	typedef struct
	{
		bool bDecodeCv0;
		bool bDecodeCv1;
		bool bDecodeCv2;
		bool bDecodeCv3;
	} sDecOpt;

public:
	thFXTPacker(TCHAR *szName, sDecOpt *opt = NULL);
	~thFXTPacker();

public:
	void  WINAPI ExtractAllFiles();
	void  WINAPI ExtractFileByName(CHAR *szName);
	void  WINAPI ExtractFileByIndex(WORD wIndex);
	void  WINAPI Pack();
	bool  WINAPI Init();
	static void WINAPI Help_Pack(TCHAR *szName);
	static void WINAPI Help_Unpack(TCHAR *szName);

private:
	PBYTE WINAPI DecodeCvFile(PBYTE pbBuffer, DWORD *pdwSize, BYTE byMode);
	void  WINAPI DecodeFile(PBYTE pbBuffer, DWORD dwOffset, DWORD dwSize);
	void  WINAPI DecodeFileName(PBYTE pbBuffer, DWORD dwBufSize);
	PBYTE WINAPI EncodeCvFile(PBYTE pbBuffer, DWORD *pdwSize, BYTE byMode);
	void  WINAPI EncodeFile(PBYTE pbBuffer, DWORD dwOffset, DWORD dwSize);
	void  WINAPI EncodeFileName(PBYTE pbBuffer, DWORD dwBufSize);
	void  WINAPI ExtractFileByHeader(HANDLE hFile, thFileName *s, sDecOpt *opt, TCHAR *szOutFile = NULL);
	BYTE  WINAPI GetMask(DWORD *p, DWORD *pdwCount, DWORD dwArraySize);
	DWORD WINAPI InitMask(DWORD *p, DWORD dwSize, DWORD dwArraySize);
	BOOL  WINAPI MyCreateDirectory(LPCTSTR lpPathName);
	void  WINAPI ReplaceBackSlash(LPTSTR lpFileName);
	bool  WINAPI WritePackageData(HANDLE hFile, sDecOpt *opt);
	bool  WINAPI WritePackageHeader(HANDLE hFile, LPCTSTR lpDirectory, LPCTSTR lpFileName);

private:
	BYTE    m_byMode;
	WORD    m_wFileNum;
	DWORD   m_dwHeaderSize, m_dwVectorSize;
	TCHAR  *m_szName;
	HANDLE  m_hFile, m_hHeap, *m_phInFiles;
	PBYTE   m_pbHeader, m_pbData;
	sDecOpt m_opt;
};

#endif /* _thFXTPacker_h_ */
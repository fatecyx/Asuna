#ifndef _CFONT_SUB_SET_
#define _CFONT_SUB_SET_

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "FontSub.h"
#include "my_headers.h"

#define CRT_ALLOC 1
#define alloc_zero			HEAP_ZERO_MEMORY

#if (CRT_ALLOC == 0)
    #define my_malloc(f, s)		HeapAlloc(m_hHeap, f, s)
    #define my_realloc(f, p, s)	HeapReAlloc(m_hHeap, f, p, s)
    #define my_free(p)			HeapFree(m_hHeap, 0, p)
#else
    #define my_malloc(f, s)		(f == alloc_zero ? calloc(1, s) : malloc(s))
    #define my_realloc(f, p, s)	realloc(p, s)
    #define my_free(p)			free(p)
#endif

class CFontSubSet
{
public:
	CFontSubSet(int argc = 0, WCHAR **argv = NULL);
	~CFontSubSet();

public:
	BOOL SubSet();
	BOOL ParseAss();
	BOOL ParseCmdLine();

private:
	WCHAR  *SkipStr(WCHAR *p, WCHAR sep = L',');
	FILE   *my_fopen(WCHAR *szFileName, WCHAR *szMode, LPDWORD dwSize = NULL);
	DWORD   ReadLine(FILE *fp, WCHAR *&szLine, DWORD &dwMaxLength);
	void    PrintHelp(PWChar *argv);
	WCHAR  *SkipEffect(WCHAR *p);
	BOOL    IsTextUTF8(FILE *fp, DWORD dwLen);
	PWCHAR *GetKeepList(FILE *fp, WCHAR **pKeepList, DWORD dwKeepList, DWORD dwVersion, DWORD dwSize);
	LPWSTR  MByteToWChar(UINT CodePage, LPCSTR lpMBStr, DWORD &dwStrlen);
	BOOL    ParseCmdLine(int argc, WCHAR **argv);
	DWORD   GetStyleNames(FILE *fp, DWORD dwMaxStyles, DWORD dwSize);
	TCHAR  *GetErrorString(ULONG ulErrCode);
	DWORD   CheckAssVersion(FILE *fp, DWORD dwSize);
	WCHAR  *GetDefaultFileName(WCHAR *szDest, WCHAR *szInput, DWORD index);
	int     GetStyleIndexByName(WCHAR *pStyle);
	void    FontSubSet(WCHAR *szInFont, WCHAR *pKeepList, USHORT dwCount, WCHAR *szOutFont);
	UCHAR   CheckFontType(WCHAR *szFont, FILE **f);

private:
	int		m_argc;
	BOOL	m_bMerge;
	WORD	**m_wWords;
	USHORT	*m_usWordCount;
	DWORD	m_dwInFonts, m_dwOutFonts, CodePage, m_dwMaxStyles, m_dwKeepList;
	WCHAR	**m_argv, *m_szInSub;
	WCHAR	**m_szStyle, **m_pKeepList, **m_szInFont, **m_szOutFont;
#if (CRT_ALLOC == 0)
	HANDLE	m_hHeap;
#endif
};

static TCHAR *szErrorString[] = 
{
	_T("ERR_GENERIC"),
	_T("ERR_READOUTOFBOUNDS\ntrying to read from memory not allowed - data error?"),
	_T("ERR_WRITEOUTOFBOUNDS\ntrying to write to memory not allowed - data error?"),
	_T("ERR_READCONTROL\nread control structure does not match data"), 
	_T("ERR_WRITECONTROL\nwrite control structure does not match data"), 
	_T("ERR_MEM\nerror allocating memory"), 
	_T("ERR_FORMAT\ninput data format error"), 
	_T("ERR_WOULD_GROW\naction would cause data to grow. use original data"), 
	_T("ERR_VERSION 1008\nmajor dttf.version of the input data is greater than the version this program can read"), 
	_T("ERR_NO_GLYPHS"), 
	_T("ERR_INVALID_MERGE_FORMATS\ntrying to merge fonts with the wrong dttf formats"), 
	_T("ERR_INVALID_MERGE_CHECKSUMS\ntrying to merge 2 fonts from different mother font"), 
	_T("ERR_INVALID_MERGE_NUMGLYPHS\ntrying to merge 2 fonts from different mother font"), 
	_T("ERR_INVALID_DELTA_FORMAT\ntrying to subset a format 1 or 2 font"), 
	_T("ERR_NOT_TTC"), 
	_T("ERR_INVALID_TTC_INDEX"), 
	_T("ERR_MISSING_CMAP"), 
	_T("ERR_MISSING_GLYF"), 
	_T("ERR_MISSING_HEAD"), 
	_T("ERR_MISSING_HHEA"), 
	_T("ERR_MISSING_HMTX"), 
	_T("ERR_MISSING_LOCA"), 
	_T("ERR_MISSING_MAXP"), 
	_T("ERR_MISSING_NAME"), 
	_T("ERR_MISSING_POST"), 
	_T("ERR_MISSING_OS2"), 
	_T("ERR_MISSING_VHEA"), 
	_T("ERR_MISSING_VMTX"), 
	_T("ERR_MISSING_HHEA_OR_VHEA"), 
	_T("ERR_MISSING_HMTX_OR_VMTX"), 
	_T("ERR_MISSING_EBDT"), 
	_T("ERR_INVALID_CMAP"), 
	_T("ERR_INVALID_GLYF"), 
	_T("ERR_INVALID_HEAD"), 
	_T("ERR_INVALID_HHEA"), 
	_T("ERR_INVALID_HMTX"), 
	_T("ERR_INVALID_LOCA"), 
	_T("ERR_INVALID_MAXP"), 
	_T("ERR_INVALID_NAME"), 
	_T("ERR_INVALID_POST"), 
	_T("ERR_INVALID_OS2"), 
	_T("ERR_INVALID_VHEA"), 
	_T("ERR_INVALID_VMTX"), 
	_T("ERR_INVALID_HHEA_OR_VHEA"), 
	_T("ERR_INVALID_HMTX_OR_VMTX"), 
	_T("ERR_INVALID_TTO"), 
	_T("ERR_INVALID_GSUB"), 
	_T("ERR_INVALID_GPOS"), 
	_T("ERR_INVALID_GDEF"), 
	_T("ERR_INVALID_JSTF"), 
	_T("ERR_INVALID_BASE"), 
	_T("ERR_INVALID_EBLC"), 
	_T("ERR_INVALID_LTSH"), 
	_T("ERR_INVALID_VDMX"), 
	_T("ERR_INVALID_HDMX"), 
	_T("ERR_PARAMETER0\ncalling function argument 0 is invalid"), 
	_T("ERR_PARAMETER1\ncalling function argument 1 is invalid"), 
	_T("ERR_PARAMETER2\ncalling function argument 2 is invalid"), 
	_T("ERR_PARAMETER3\ncalling function argument 3 is invalid"), 
	_T("ERR_PARAMETER4\ncalling function argument 4 is invalid"), 
	_T("ERR_PARAMETER5\ncalling function argument 5 is invalid"), 
	_T("ERR_PARAMETER6\ncalling function argument 6 is invalid"), 
	_T("ERR_PARAMETER7\ncalling function argument 7 is invalid"), 
	_T("ERR_PARAMETER8\ncalling function argument 8 is invalid"), 
	_T("ERR_PARAMETER9\ncalling function argument 9 is invalid"), 
	_T("ERR_PARAMETER10\ncalling function argument 10 is invalid"), 
	_T("ERR_PARAMETER11\ncalling function argument 11 is invalid"), 
	_T("ERR_PARAMETER12\ncalling function argument 12 is invalid"), 
	_T("ERR_PARAMETER13\ncalling function argument 13 is invalid"), 
	_T("ERR_PARAMETER14\ncalling function argument 14 is invalid"), 
	_T("ERR_PARAMETER15\ncalling function argument 15 is invalid"), 
	_T("ERR_PARAMETER16\ncalling function argument 16 is invalid"), 
};

#endif /* _CFONT_SUB_SET_ */
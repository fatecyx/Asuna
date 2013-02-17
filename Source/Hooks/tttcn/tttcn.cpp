#pragma comment(linker, "/ENTRY:DllEntryPoint")
#pragma comment(linker, "/MERGE:.text=.Sharu /SECTION:.Sharu,ERW")
#pragma comment(linker, "/MERGE:.rdata=.Sharu")
#pragma comment(linker, "/MERGE:.data=.Sharu")
#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "shlwapi.lib")

#include "tttcn.h"
#include <Shlwapi.h>

const DWORD dwProtectSize = 0x65000;
char *szFontPakName = "font";
char data[] = "\x80\xFE\xA1\x72\x41\x80\xFE\xF7\x77\x3C\x80\xFA\xA1\x72\x37\x80\xFA\xFF\x74\x32\x8A\xCE\x80\xE9\xA1\x33\xFF\x6B\xF9\x5E\x80\xEA\xA1\x81\xE2\xFF\x00\x00\x00\x03\xFA\x89\x7C\x24\x10\xEB\x17";

enum GameVersion {VER100, VER101, UNKNOWN};

BYTE byGameVer;
READPAKFILE lpfnReadPakFile;

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	static bool bWrite = false;
	DWORD	dwOldProtect;
	const DWORD dwAddress = 0x401C00;
	LPVOID	lpReadFileFromPak;

	if (bWrite == false)
	{
		CHAR szPath[MAX_PATH];
		GetModuleFileNameA(NULL, szPath, sizeof(szPath));
		*PathFindFileNameA(szPath) = 0;
		SetCurrentDirectoryA(szPath);

		bWrite = true;

		if (*(WORD  *)0x401C5F == 0xD3FF &&
			*(DWORD *)0x401C69 == 0x00000273)
		{
			byGameVer = VER100;
		}
		else if (*(WORD  *)0x401C5E == 0xD7FF &&
			*(DWORD *)0x401C68 == 0x00000294)
		{
			byGameVer = VER101;
		}
		else
		{
			return TRUE;
		}

		lpReadFileFromPak = ReadFileFromPak;

		if (TRUE == VirtualProtect((LPVOID)dwAddress,
			dwProtectSize,
			PAGE_EXECUTE_READWRITE,
			&dwOldProtect))
		{
			if (byGameVer == VER100)
			{
				DWORD dwCallToMyFunc = (DWORD)lpReadFileFromPak;
				dwCallToMyFunc -= 0x401C69 + 4;
				*(WORD  *)0x401C5F = 0x9090;
				*(DWORD *)0x401C69 = dwCallToMyFunc;

				*(BYTE *)0x461C7A = 0xEB;
				*(WORD *)0x461C59 = 0x13EB;
				__asm
				{
					mov		edi, 0x40AC41;
					lea		esi, data;
					mov		ecx, 0Ch;
					rep		movsd;
				}
				*(char **)0x538930 = szFontPakName;
				lpfnReadPakFile = (READPAKFILE)0x401EE0;
			}
			else
			{
				DWORD dwCallToMyFunc = (DWORD)lpReadFileFromPak;
				dwCallToMyFunc -= 0x401C68 + 4;
				*(WORD  *)0x401C5E = 0x9090;
				*(DWORD *)0x401C68 = dwCallToMyFunc;

				*(BYTE *)0x461E82 = 0xEB;
				*(WORD *)0x461E61 = 0x13EB;
				__asm
				{
					mov		edi, 0x40AC61;
					lea		esi, data;
					mov		ecx, 0Ch;
					rep		movsd;
				}
				*(char **)0x539938 = szFontPakName;
				lpfnReadPakFile = (READPAKFILE)0x401F00;
			}
		}
	}
	return TRUE;
}

DWORD ReadFileFromPak(LPSTR lpszPak,
					  LPSTR lpszFile,
					  PBYTE *ppbOutBuffer,
					  LPSTR lpszPakNameBuffer,
					  LPSTR lpszFormat,
					  ...)
{
	DWORD dwUnPakSize = 0;

	wsprintfA(lpszPakNameBuffer, "sc.pak");
	dwUnPakSize = lpfnReadPakFile(lpszPak, lpszFile, ppbOutBuffer);
/*
	if (dwUnPakSize == 0)
	{
		wsprintfA(lpszPakNameBuffer, "fnt.pak");
		dwUnPakSize = lpfnReadPakFile(lpszPak, lpszFile, ppbOutBuffer);
	}
*/
	if (dwUnPakSize == 0 && byGameVer == VER100)
	{
		LPSTR lpszPakName = *(&lpszFormat + 1);
		wsprintfA(lpszPakNameBuffer, lpszFormat, lpszPakName);
		dwUnPakSize = lpfnReadPakFile(lpszPak, lpszFile, ppbOutBuffer);
	}

	return dwUnPakSize;
}

DWORD __stdcall ReadPakFile(LPSTR lpszPak, LPSTR lpszFile, PBYTE *ppbOutBuffer)
{
	HANDLE hFile = CreateFileA(lpszPak,
							GENERIC_READ,
							FILE_SHARE_READ,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	BOOL	bIsComp;
	PBYTE	pbDest, pbSrc;
	DWORD	dwHeader, dwRead, dwFileNum, dwSrcSize, dwDestSize, dwOffset, dwSize;
	TCHAR	szFileName[0x1D];szFileName[0x1C] = 0;

	ReadFile(hFile, &dwHeader, 4, &dwRead, NULL);
	if (dwHeader != 'PACK')
	{
		return 0;
	}

	SetFilePointer(hFile, 0x24, 0, FILE_BEGIN);
	ReadFile(hFile, &dwFileNum, 4, &dwRead, NULL);
	dwFileNum = (dwFileNum - 8) / 0x24;

	if (dwFileNum ==0)
	{
		return 0;
	}

	SetFilePointer(hFile, 0x8, 0, FILE_BEGIN);

	do
	{
		ReadFile(hFile, szFileName, sizeof(szFileName) - 1, &dwRead, NULL);
		if (lstrcmpiA(szFileName + 4, lpszFile) == 0)
		{
			break;
		}
		SetFilePointer(hFile, 0x8, 0, FILE_CURRENT);

	} while (--dwFileNum);

	if (dwFileNum == 0)
	{
		return 0;
	}

	bIsComp = *(BOOL *)szFileName;
	ReadFile(hFile, szFileName, 8, &dwRead, NULL);
	dwOffset	= *(DWORD *)szFileName;
	dwSrcSize	= *(DWORD *)(szFileName + 4);
	pbSrc = (PBYTE)GlobalAlloc(GMEM_FIXED, dwSrcSize);
	if (pbSrc == NULL)
	{
		return 0;
	}

	SetFilePointer(hFile, dwOffset, 0, FILE_BEGIN);
	ReadFile(hFile, pbSrc, dwSrcSize, &dwRead, NULL);
	CloseHandle(hFile);

	if (bIsComp != TRUE)
	{
		*ppbOutBuffer = pbSrc;
		return dwRead;
	}

	dwDestSize = *(DWORD *)(pbSrc + 4);
	if (dwDestSize == 0)
	{
		return 0;
	}

	pbDest = (PBYTE)GlobalAlloc(GMEM_FIXED, dwDestSize);
	if (pbDest == NULL)
	{
		return 0;
	}

	dwSize = Decode(pbSrc + 8, pbDest, dwSrcSize - 8, dwDestSize);
	GlobalFree(pbSrc);
	if (dwSize == 0)
	{
		GlobalFree(pbDest);
		return 0;
	}

	*ppbOutBuffer = pbDest;
	return dwSize;
}

DWORD __stdcall Decode(PBYTE pbSrc, PBYTE pbDest, DWORD dwSrcLen, DWORD dwDestLen)
{
	BYTE	Buffer[0x1000];
	DWORD	dwData;
	DWORD	dwVal1 = 0, dwVal2 = 0, dwArrSize = 0xFEE;
	DWORD	dwRead = 0, dwWritten = 0;

	__asm
	{
		mov eax, 20202020h;
		mov ecx, 0FF0h >> 2;
		lea edi, Buffer;
		rep stosd;
	}

	while (dwRead <= dwSrcLen)
	{
		if ((dwVal1 & 0x100) == 0)
		{
			if (dwRead >= dwSrcLen)
			{
				// 1
				break;
			}

			dwVal1 = *pbSrc++;
			dwVal1 |= 0xFF00;
			++dwRead;
		}

		if (dwRead >= dwSrcLen)
		{
			// 2
			break;
		}

		dwData = *pbSrc++;
		++dwRead;

		if ((LOBYTE(dwVal1) & 1) != 0)
		{
			*pbDest++ = (BYTE)dwData;
			Buffer[dwArrSize & 0x0FFF] = (BYTE)dwData;
			++dwArrSize;
			++dwWritten;
			if (dwWritten > dwDestLen)
			{
				// ³ö´í
				break;
			}

			dwVal1 >>= 1;
		}
		else
		{
			if (dwRead >= dwSrcLen)
			{
				// 3
				break;
			}

			int iTemp, nBytesRead;

			iTemp = *pbSrc++;
			++dwRead;
			dwData |= (iTemp & 0xF0) << 4;

			if (!((nBytesRead = (iTemp & 0x0F) + 2) < 0))
			{
				do
				{
					if (dwWritten > dwDestLen)
					{
						dwVal2 = 1;
						break;
					}
					else
					{
						*pbDest = Buffer[dwArrSize & 0xFFF] = Buffer[dwData & 0xFFF];
						++pbDest;
						++dwArrSize;
						++dwData;
						++dwWritten;
						--nBytesRead;
					}
				} while (nBytesRead >= 0);
			}

			if (dwWritten > dwDestLen)
			{
				// ³ö´í
				break;
			}

			dwVal1 >>= 1;
		}
	}

	return dwWritten;
}
#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/MERGE:.text=.Hiromi /SECTION:.Hiromi,ERW")
#pragma comment(linker, "/MERGE:.rdata=.Hiromi")
#pragma comment(lib, "msvcrt.lib")


#include "SDTImport.h"
#include <getmainargs.h>
#include <stdio.h>

size_t __stdcall fsize(FILE *fp);
size_t __stdcall safe_gets(FILE *fp);
BOOL   __stdcall Import(PBYTE pbSDT, DWORD dwSize, PBYTE pbText, DWORD dwTextSize);

void __cdecl main(int argc, char **argv)
{
	getargs(&argc, &argv);
	if (argc < 3)
	{
		char *fn;
		fn = strrchr(argv[0], '\\');
		printf("Usage: %s src.sdt dest.sdt\n", fn ? ++fn : argv[0]);
		return;
	}

	char *p, szTextName[MAX_PATH];
	FILE  *fInput, *fOutput, *fText;
	PBYTE  pbSDT, pbText;
	DWORD  dwSDTSize, dwTextSize;

	fInput = fopen(argv[1], "rb");
	if (fInput == NULL)
	{
		printf("Can't open input SDT file \"%s\".\n", argv[1]);
		return;
	}

	p = argv[1];
	strcpy(szTextName, p);
	p = strrchr(szTextName, '.');
	if (p)
	{
		*p = 0;
	}
	strcat(szTextName, ".txt");
	fText = fopen(szTextName, "rb");
	if (fText == NULL)
	{
		printf("Can't open text file \"%s\".\n", szTextName);
		fclose(fInput);
		return;
	}

	fOutput = fopen(argv[2], "wb");
	if (fOutput == NULL)
	{
		printf("Can't open output SDT file \"%s\".\n", argv[2]);
		fclose(fInput);
		fclose(fText);
		return;
	}

	dwTextSize = fsize(fText);
	dwSDTSize  = fsize(fInput);
	pbSDT = (PBYTE)malloc(dwSDTSize + dwTextSize);
	if (pbSDT == NULL)
	{
		printf("Can't allocate memory for \"%s\".\n", argv[1]);
		fclose(fInput);
		fclose(fOutput);
		return;
	}

	pbText = (PBYTE)malloc(dwTextSize);
	if (pbText == NULL)
	{
		printf("Can't allocate memory for \"%s\".\n", szTextName);
		free(pbSDT);
		fclose(fInput);
		fclose(fOutput);
		return;
	}

	fread(pbText, dwTextSize, 1, fText);
	fread(pbSDT, dwSDTSize, 1, fInput);
	fclose(fText);
	fclose(fInput);

	printf("Importing \"%s\" ... ", argv[1]);
//	try
	{
		printf("%s\n", Import(pbSDT, dwSDTSize, pbText, dwTextSize) ? "OK" : "failed");
	}
//	catch(...)
	{
//		printf("failed\n");
	}
	fwrite(pbSDT, *(LPDWORD)(pbSDT + 4), 1, fOutput);
	fclose(fOutput);

	free(pbSDT);
	free(pbText);
}

PBYTE __stdcall SkipLine(PBYTE pbText, PBYTE pbEnd, uint_32 uiSkip)
{
	while (uiSkip--)
	{
		while (*pbText++ != '\n')
		{
			if (pbText > pbEnd)
				return NULL;
		}
	}

	return pbText;
}

BOOL __stdcall Import(PBYTE pbSDT, DWORD dwSDTSize, PBYTE pbText, DWORD dwTextSize)
{
	if (dwSDTSize == 0 || dwTextSize == 0)
		return FALSE;

	ULONG ulOffset;
	PBYTE pbText2, pbEnd;
	SDTImport sdtimport(pbSDT, dwSDTSize);

	if (sdtimport.Init() == FALSE)
		return FALSE;

	pbText2 = pbText;
	pbEnd = pbText + dwTextSize;
	while (pbText2 < pbEnd)
	{
		if (*pbText2 != '=')
			break;

		while (*pbText2 == '=')
		{
			if (pbText2 >= pbEnd)
				break;
			++pbText2;
		}

		if (pbText2 >= pbEnd)
			break;

		ulOffset = strtoul((char *)pbText2, NULL, 16);

		pbText2 = SkipLine(pbText2, pbEnd, 3);
		if (pbText2 == NULL)
			break;

		pbText2 += sdtimport.ImportLine((LPCSTR)pbText2, ulOffset) + 1;
	}

	return TRUE;
}

size_t __stdcall fsize(FILE *fp)
{
	size_t size;
	long pos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, pos, SEEK_SET);
	return size;
}
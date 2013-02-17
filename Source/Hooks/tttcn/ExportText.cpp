#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/MERGE:.text=.Hiromi /SECTION:.Hiromi,ERW")
#pragma comment(linker, "/MERGE:.rdata=.Hiromi")

#include <Windows.h>
#include <getmainargs.h>
#include <stdio.h>
#include "SDTText.h"

void __stdcall PrintFile(FILE *fp, char *pText, DWORD dwOffet, DWORD dwTextLen)
{
	char text[1000];
	memcpy(text, pText, dwTextLen);
	text[dwTextLen] = 0;
	fprintf(fp, "==================================================%X\n"
				  "%s\n"
				  "--------------------------------------\n%s\n",
				  dwOffet, text, text);
}

void main(int argc, char **argv)
{
	getargs(&argc, &argv);
	if (argc < 2) return;

	FILE *fOut, *fp = fopen(argv[1], "rb");
	if (fp == NULL)
	{
		printf("Can't open \"%s\".\n");
		return;
	}

	char	*pBuffer, *pText, *pEnd, *pExt, *p;
	DWORD	dwSize, dwTextLen, dwOffset;

	pExt = strrchr(argv[1], '.');
	if (pExt == NULL)
	{
		strcat(argv[1], ".txt");
	}
	else
	{
		*(DWORD *)pExt = 'txt.';
	}

	fOut = fopen(argv[1], "wb");
	if (fOut == NULL)
	{
		printf("Can't open \"%s\".\n");
		fclose(fp);
		return;
	}

	fseek(fp, 0, SEEK_END);
	dwSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	pBuffer = (char *)malloc(dwSize);
	fread(pBuffer, dwSize, 1, fp);
	fclose(fp);

	p = pBuffer + BEGIN_OFFSET;
	pEnd = pBuffer + dwSize;
	while (p <= pEnd)
	{
		switch (*(PWORD)p)
		{
		case TEXT_DIALOG:
		case TEXT_DIALOG_CONTINUE:
			dwOffset = p - pBuffer;
			p += 2;
			dwTextLen = *(PWORD)p;
			pText = p + 2;
			break;
		case TEXT_NAME:
		case TEXT_MENU:
			dwOffset = p - pBuffer;
			p += 2;
			dwTextLen = *(PBYTE)p;
			pText = p + 1;
			break;
		default:
			++p;
			continue;
		}
		if (pText + dwTextLen >= pEnd || strlen(pText) < dwTextLen)
		{
			--p;
			continue;
		}

		PrintFile(fOut, pText, dwOffset, dwTextLen);
		p = pText + dwTextLen;
	}

	free(pBuffer);
	fclose(fOut);
}
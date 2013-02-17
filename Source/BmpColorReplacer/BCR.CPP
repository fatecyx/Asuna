#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Hiromi /SECTION:.Hiromi,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Hiromi")
#pragma comment(lib, "msvcrt6.lib")

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <getmainargs.h>

void main(int argc, char **argv)
{
	char *szUsage = "bcr.exe input.bmp R,G,B(source) R,G,B(dest)\n";
	getmainargs(&argc, &argv);
	if (argc != 4)
	{
		printf(szUsage);
		return;
	}

	FILE			*fp;
	char			*cBuffer, *pEnd;
	unsigned long	ulRed, ulGreen, ulBlue;
	unsigned long	ulFileSize, ulBytesPerPixel, ulOffsetOfRaw;
	unsigned long	ulSrcRGB, ulDestRGB, ulCurRGB;

	fp = fopen(argv[1], "rb+");
	if (fp == NULL)
	{
		printf("Can't open \"%s\".\n", argv[1]);
		return;
	}

	if (sscanf(argv[2], "%d, %d, %d", &ulRed, &ulGreen, &ulBlue) != 3)
	{
		printf("Error source color.\n%s", szUsage);
		fclose(fp);
		return;
	}
	ulSrcRGB = ((ulRed << 16) | (ulGreen << 8) | (ulBlue)) & 0x00FFFFFF;

	if (sscanf(argv[3], "%d, %d, %d", &ulRed, &ulGreen, &ulBlue) != 3)
	{
		printf("Error destination color.\n%s", szUsage);
		fclose(fp);
		return;
	}
	ulDestRGB = ((ulRed << 16) | (ulGreen << 8) | (ulBlue)) & 0x00FFFFFF;

	fread(&ulFileSize, 2, 1, fp);
	if ((unsigned short)ulFileSize != 'MB')
	{
		printf("Invalid Bitmap file.\n");
		fclose(fp);
		return;
	}

	fseek(fp, 0, SEEK_END);
	ulFileSize = ftell(fp);

	cBuffer = (char *)malloc(ulFileSize);
	if (cBuffer == NULL)
	{
		printf("Can't allocate memory for input file.\n");
		fclose(fp);
		return;
	}

	fseek(fp, 0, SEEK_SET);
	if (fread(cBuffer, ulFileSize, 1, fp) == 0)
	{
		printf("Can't read \"%s\".\n", argv[1]);
		free(cBuffer);
		fclose(fp);
		return;
	}

	ulBytesPerPixel = *(unsigned long *)(cBuffer + 0x1C) / 8;
	if (ulBytesPerPixel != 4)
	{
		printf("32-bit Bitmap only.\n");
		free(cBuffer);
		fclose(fp);
		return;
	}

	ulOffsetOfRaw = *(unsigned long *)(cBuffer + 0xA);

	pEnd = cBuffer + ulFileSize;
	for (char *p = cBuffer + ulOffsetOfRaw; p <= pEnd; p += 4)
	{
		ulCurRGB = *(unsigned long *)p;
		if ((ulCurRGB & 0x00FFFFFF) == ulSrcRGB)
		{
			ulDestRGB = (ulDestRGB & 0x00FFFFFF) | (ulCurRGB & 0xFF000000);
			*(unsigned long *)p = ulDestRGB;
		}
	}

	fseek(fp, 0, SEEK_SET);
	fwrite(cBuffer, ulFileSize, 1, fp);
	free(cBuffer);
	fclose(fp);
}
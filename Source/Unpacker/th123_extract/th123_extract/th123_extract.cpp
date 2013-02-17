#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Nagisa /SECTION:.Nagisa,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Nagisa")
#pragma comment(linker,"/MERGE:.data=.Nagisa")

#include "th123_extract.h"
#include <time.h>
#include <direct.h>
#include "getmainargs.h"

enum { DISABLE, CV0, CV1, CV2, CV3 };

void __cdecl main(int argc, char **argv)
{
	getargs(&argc, &argv);
	if (argc < 2)
	{
		printf("Usage: Drag file(s) to me.\n"
//			   "说明: \n"
//				"解包时会自动解密cv0,cv1和部分cv2文件,\n"
//			   "在命令行最后加上/n0,/n1,/n2即可禁用相应文件的自动解密.\n"
			   );
		return;
	}

	char *pFileNameBuf;
	uint_16 usFileNum;
	uint_32 uiFNameSize;
	FILE *fp;
	thFileName *s;
	sDecOpt opt = {true, true, true, true};

	while (argv[argc - 1][0] == '/')
	{
		uint_32 p = *(uint_16 *)(argv[argc - 1] + 1);

		if (p == '0n')
		{
			--argc;
			opt.bDecodeCv0 = false;
		}
		else if (p == '1n')
		{
			--argc;
			opt.bDecodeCv1 = false;
		}
		else if (p == '2n')
		{
			--argc;
			opt.bDecodeCv2 = false;
		}
		else if (p == '3n')
		{
			--argc;
			opt.bDecodeCv3 = false;
		}
		else
		{
			break;
		}
	}

	while(--argc)
	{
		fp = fopen(argv[argc], "rb");
		if (fp == NULL)
		{
			printf("Can't open \"%s\".\n", argv[argc]);
			continue;
		}

		{
			char *pFileName;

			pFileName = strrchr(argv[argc], '\\');
			if (pFileName == NULL)
			{
				pFileName = strrchr(argv[argc], '/');
			}
			if (pFileName)
			{
				char c = *pFileName;
				*pFileName = 0;
				chdir(argv[argc]);
				*pFileName = c;
			}
		}

		fread(&usFileNum, 2, 1, fp);
		fread(&uiFNameSize, 4, 1, fp);
		pFileNameBuf = (char *)malloc(uiFNameSize);
		if (pFileNameBuf == NULL)
		{
			printf("Can't allocate memory.\n");
			fclose(fp);
			continue;
		}
		fread(pFileNameBuf, uiFNameSize, 1, fp);
		DecodeFileName(pFileNameBuf, uiFNameSize);
		DecodeFileName(pFileNameBuf, uiFNameSize);

		uint_16 usCurFile = 1;
		for (char *p = pFileNameBuf; usCurFile <= usFileNum; ++usCurFile)
		{
			printf("(%d/%d): ", usCurFile, usFileNum);
			s = (thFileName *)p;
			Extract(fp, s, &opt);
			p += 8 + s->byLength + 1;
		}

		printf("\nElapsed time: %d ms\n", clock());

		fclose(fp);
		free(pFileNameBuf);
	}
}

void __stdcall Extract(FILE *fp, thFileName *s, sDecOpt *opt)
{
	FILE *fOut;
	uint_8 byMode;
	char c, xor, *pFileBuffer, *pExt;

	if (s->uiSize == 0)
	{
		return;
	}
	pFileBuffer = (char *)malloc(s->uiSize);
	if (pFileBuffer == NULL)
	{
		return;
	}

	fseek(fp, s->uiOffset, SEEK_SET);
	fread(pFileBuffer, s->uiSize, 1, fp);

	xor = (char)((s->uiOffset >> 1) | 0x23);
	for (uint_32 i = 0; i != s->uiSize; ++i)
	{
		pFileBuffer[i] ^= xor;
	}

	for (char *p = &s->cName + s->byLength - 1; p != &s->cName; --p)
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
		if (*pFileBuffer < 0x18)
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
	fOut = fopen(&s->cName, "wb");
	if (fOut)
	{
		printf("\"%s\"\n", &s->cName);

		if (byMode != DISABLE)
		{
			pFileBuffer = DecodeCvFile(pFileBuffer, &s->uiSize, byMode);
		}
		fwrite(pFileBuffer, s->uiSize, 1, fOut);
		fclose(fOut);
	}
	(&s->cName)[s->byLength] = c;
	free(pFileBuffer);
}

char *__stdcall DecodeCvFile(char *pBuffer, uint_32 *uiSize, uint_8 byMode)
{
	char xor, u;

	switch (byMode)
	{
	case CV0:
	case CV1:
		u   = (char)0x71;
		xor = (char)0x8B;
		for (uint_32 i = 0; i != *uiSize; ++i)
		{
			pBuffer[i] ^= xor;
			xor += u;
			u += 0x95;
		}
		break;

	case CV2:
		{
			char *pBitmap;
			uint_8  byBpp;
			uint_32 uiWidth, uiHeight, uiTrueWidth;

			byBpp = *pBuffer < 0x18 ? 1 : 4;
			uiWidth     = *(DWORD *)(pBuffer + 1);
			uiHeight    = *(DWORD *)(pBuffer + 5);
			uiTrueWidth = *(DWORD *)(pBuffer + 9);
			*uiSize = 0x36 + uiWidth * uiHeight * byBpp;
			pBitmap = (char *)malloc(*uiSize);
			for (int i = 0; i != uiHeight; ++i)
			{
				memcpy(pBitmap + 0x36 + (uiHeight - i - 1) * uiWidth * byBpp, pBuffer + 0x11 + i * uiTrueWidth * byBpp, uiWidth * byBpp);
			}

			free(pBuffer);
			pBuffer = pBitmap;

			memset(pBitmap, 0, 0x36);
			*(DWORD *)pBitmap = 'MB';
			*(DWORD *)(pBitmap + 0x02) = *uiSize;
			*(DWORD *)(pBitmap + 0x0A) = 0x36;
			*(DWORD *)(pBitmap + 0x0E) = 0x28;
			*(DWORD *)(pBitmap + 0x12) = uiWidth;
			*(DWORD *)(pBitmap + 0x16) = uiHeight;
			*(DWORD *)(pBitmap + 0x1A) = 1;
			*(DWORD *)(pBitmap + 0x1C) = byBpp == 4 ? 32 : 8;
		}
		break;
	}

	return pBuffer;
}

void __stdcall DecodeFileName(char *pFileBuf, uint_32 iBufSize)
{
	char c, u;
	uint_32 uiCount, *p;
	const static uint_32 uiSize = 624;

	p = (uint_32 *)malloc(uiSize * sizeof(*p));
	uiCount = GenerateArray(p, iBufSize + 6, uiSize);

	for (int i = 0; i != iBufSize; ++i)
	{
		pFileBuf[i] ^= GetXorByte(p, &uiCount, uiSize);
	}
	c = (char)0xC5;
	u = (char)0x83;
	for (int i = 0; i != iBufSize; ++i)
	{
		pFileBuf[i] ^= c;
		c += u;
		u += 0x53;
	}

	free(p);
}

byte_t __stdcall GetXorByte(uint_32 *p, uint_32 *uiCount, uint_32 ui_Array_Size)
{
	uint_32 i, val;
	int mask[] = {0, 0x9908B0DF};

	if (*uiCount >= 0x270)
	{
		if (*uiCount == 0x271)
			GenerateArray(p, 0x1571, ui_Array_Size);

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
			while (i != ui_Array_Size - 1)
			{
				val = (p[i] ^ p[i + 1]) & INT_MAX;
				val ^= p[i];
				val = (val >> 1) ^ (mask[val & 1] ^ p[i - 0xE4 + 1]);
				p[i++] = val;
			}
		}

		val = p[0] ^ p[ui_Array_Size - 1];
		val &= INT_MAX;
		val ^= p[ui_Array_Size - 1];
		val = (val >> 1) ^ mask[val & 1];
		p[ui_Array_Size - 1] = val ^ p[396];
		i = 0;
	}
	else
	{
		i = *uiCount;
	}

	val = p[i++];
	*uiCount = i;
	val = val ^ (val >> 0x0B);
	val = ((val & 0xFF3A58AD) << 7) ^ val;
	val = ((val & 0xFFFFDF8C) << 0x0F) ^ val;
	val = val ^ (val >> 0x12);

	return (byte_t)val;
}

uint_32 __stdcall GenerateArray(uint_32 *p, uint_32 uiSize, uint_32 ui_Array_Size)
{
	uint_32 uiCount = 1;

	p[0] = uiSize;
	for (uint_32 i = 0; i != ui_Array_Size - 1; ++i)
	{
		p[i + 1] = ((p[i] >> 0x1E) ^ p[i]) * 0x6C078965 + uiCount++;
	}

	return uiCount;
}

BOOL WINAPI MyCreateDirectory(LPCTSTR lpPathName)
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
//			CreateDirectory(lpPathName, NULL);
			mkdir(lpPathName);
			*lpPath = c;
		}
		++lpPath;
	} while (*lpPath);

//	return CreateDirectory(lpPathName, NULL);
	return mkdir(lpPathName);
}
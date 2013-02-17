
#include <Windows.h>
#include <stdio.h>
#include "my_common.h"

#pragma pack(1)
typedef struct _tagthFileName
{
	uint_32 uiOffset;
	uint_32 uiSize;
	uint_8  byLength;
	char    cName;
} thFileName;
#pragma pack()

typedef struct _tagOpt
{
	bool bDecodeCv0;
	bool bDecodeCv1;
	bool bDecodeCv2;
	bool bDecodeCv3;
} sDecOpt;

void    __stdcall Extract(FILE *fp, thFileName *s, sDecOpt *opt);
char   *__stdcall DecodeCvFile(char *pBuffer, uint_32 *uiSize, uint_8 byMode);
void    __stdcall DecodeFileName(char *pFileBuf, uint_32 iBufSize);
byte_t  __stdcall GetXorByte(uint_32 *p, uint_32 *uiCount, uint_32 ui_Array_Size);
uint_32 __stdcall GenerateArray(uint_32 *p, uint_32 uiSize, uint_32 ui_Array_Size);
BOOL WINAPI MyCreateDirectory(LPCTSTR lpPathName);
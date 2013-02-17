
#include <Windows.h>

typedef struct _tagPatch
{
	CHAR *pData;
	DWORD dwSize;
	DWORD dwAddress;
} sPatch;

typedef struct _tagFuncPatch
{
	DWORD dwAddress;
	DWORD dwFunc;
} sFuncPatch;

void s_CreateFile();

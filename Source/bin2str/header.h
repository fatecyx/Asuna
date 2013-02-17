#pragma warning(disable:4309)

#include "inc_header.h"

typedef struct _tagArray_of_Data
{
	char *data;
	size_t nSize;
} tagArray_of_Data;

tagArray_of_Data Array_of_Data[] = 
{
	{_BIN2STR_OPT_, sizeof(_BIN2STR_OPT_)},
	
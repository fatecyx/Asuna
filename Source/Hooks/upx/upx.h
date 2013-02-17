#ifndef _UPX_H_
#define _UPX_H_

#include <Windows.h>
#include "my_common.h"

char* CDECL strcpy_hook(char *dst, char *src);
int   CDECL write_hook(void *This, char *buf, int n);
int   CDECL write_peheader(char *buf, int n);
void  CDECL modify_peoffset();

#endif /* _UPX_H_ */
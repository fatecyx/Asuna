#ifndef _TEST_LIB_H_
#define _TEST_LIB_H_

#include "pragma_once.h"
#include <Windows.h>
#include <delayimp.h>
#include "my_headers.h"

EXTC FARPROC STDCALL __delayLoadHelper2(PCImgDelayDescr pidd, FARPROC *ppfnIATEntry);

#endif // _TEST_LIB_H_
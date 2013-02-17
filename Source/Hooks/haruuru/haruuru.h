#ifndef _HARUURU_H_
#define _HARUURU_H_

#include <Windows.h>
#include "my_common.h"

HFONT WINAPI MyCreateFontIndirectA(LPLOGFONTA lplf);

/*
TFuncPatch f[] =
{
    {CALL, 0x40F98, (DWORD)HookDecodePng,       0x00},    // 标题画面解码
};


TPatch p[] =
{
    {FW_NORMAL,     0x04,   0x5CFC8}, // fnWeight
};
*/

#endif /* _HARUURU_H_ */
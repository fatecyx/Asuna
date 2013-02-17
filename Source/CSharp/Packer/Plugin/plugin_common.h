#ifndef _PLUGIN_COMMON_H_
#define _PLUGIN_COMMON_H_

#include "my_common.h"

typedef struct
{
    Int32   Encrypt;
    Int32   Compress;
    PCWChar pFileName;
} SPackFileInfo;

typedef Bool (STDCALL *FShowStatus)(PCWChar pszString, Int32 Percent);

interface ICallBacks
{
    FShowStatus ShowStatus;
};

#endif /* _PLUGIN_COMMON_H_ */
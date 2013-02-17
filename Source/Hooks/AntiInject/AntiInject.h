#ifndef _ANTIINJECT_H_48bb5445_9dc9_45ad_8585_eee1cab11e88
#define _ANTIINJECT_H_48bb5445_9dc9_45ad_8585_eee1cab11e88

#include "MyLibraryUser.h"

EXTC_IMPORT PVOID InitializeAntiInject;

#define THREAD_START_PARAMETER_MAGIC    TAG4('TSPM')
#define LOAD_DLL_FRAME_MAGIC            TAG4('LDFM')

struct THREAD_START_PARAMETER : public RTL_THREAD_FRAME
{
    PVOID ThreadStartRoutine;
    PVOID Parameter;

    THREAD_START_PARAMETER()
    {
        Context = THREAD_START_PARAMETER_MAGIC;
    }
};

#endif // _ANTIINJECT_H_48bb5445_9dc9_45ad_8585_eee1cab11e88

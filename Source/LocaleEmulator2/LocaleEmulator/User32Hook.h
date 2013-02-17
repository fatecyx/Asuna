#ifndef _USER32HOOK_H_ee384c3a_e8ce_4599_b8e6_cb1d8367dd05_
#define _USER32HOOK_H_ee384c3a_e8ce_4599_b8e6_cb1d8367dd05_

#include "LocaleEmulator.h"

#define CBT_PROC_PARAM_CONTEXT  TAG4('CPPC')

typedef struct CBT_PROC_PARAM : public TEB_ACTIVE_FRAME
{
    HHOOK Hook;
    PLeGlobalData GlobalData;

    CBT_PROC_PARAM()
    {
        this->Context = CBT_PROC_PARAM_CONTEXT;
        Hook = NULL;
    }

} CBT_PROC_PARAM, *PCBT_PROC_PARAM;

typedef union
{
    USHORT  BufferSize;
    WCHAR   UnicodeBuffer[1];
    CHAR    AnsiBuffer[1];

} MSG_INPUT_COUNT_OUPUT_STRING, *PMSG_INPUT_COUNT_OUPUT_STRING;

#endif // _USER32HOOK_H_ee384c3a_e8ce_4599_b8e6_cb1d8367dd05_

#ifndef _CG_CORE_H_82d307cb_3fb5_4f4b_8d0a_13546b2c018f
#define _CG_CORE_H_82d307cb_3fb5_4f4b_8d0a_13546b2c018f

#include "pragma_once.h"
#include "../Common/CG_Core.h"
#include "CG_Interface.h"

DECL_ALIGN(1) struct CG_CORE_OPTION
{
    union
    {
        ULONG Data;
        DECL_ALIGN(1) struct
        {
            BYTE Reserve : 1;
        } Flags;
    };
};

#endif // _CG_CORE_H_82d307cb_3fb5_4f4b_8d0a_13546b2c018f

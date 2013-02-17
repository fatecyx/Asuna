#ifndef _CG_INTERFACE_H_df567f21_c83e_432a_9faf_5fa015e40cc2
#define _CG_INTERFACE_H_df567f21_c83e_432a_9faf_5fa015e40cc2

#include "pragma_once.h"
#include "../Common/CG_Interface.h"

#define CG_INTERFACE_FROM_CLASS(cls, iface) \
            class cls##I :  public CCGUnknownImpl<cls##I>, \
                            public iface

#endif // _CG_INTERFACE_H_df567f21_c83e_432a_9faf_5fa015e40cc2

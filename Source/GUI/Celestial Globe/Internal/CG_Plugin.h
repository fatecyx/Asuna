#ifndef _CG_PLUGIN_H_0a52d788_5b3c_48af_b734_d428957624b1
#define _CG_PLUGIN_H_0a52d788_5b3c_48af_b734_d428957624b1

#include "pragma_once.h"
#include "../Common/CG_Plugin.h"
#include "CG_Interface.h"

CG_INTERFACE_(ICGPluginManager, ICGUnknown)
{
    CG_METHOD_TYPE(ULONG, GetPluginCount)(THIS);
    CG_METHOD(GetPluginByID)(THIS_ ULONG ID, ICGPlugin **ppPlugin);
};

#endif // _CG_PLUGIN_H_0a52d788_5b3c_48af_b734_d428957624b1

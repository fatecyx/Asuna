#ifndef _CLASSFACTORY_H_11613e77_998f_4fa9_9b42_5cc9a038fcd7
#define _CLASSFACTORY_H_11613e77_998f_4fa9_9b42_5cc9a038fcd7

#include "pragma_once.h"
#include "../Internal/CG_Headers.h"

class CCGClassFactory : public ICGUnknown, public CCGUnknownImpl<CCGClassFactory>
{
protected:

public:
    CCGClassFactory(ICGUnknown *pUnknownOuter);

    CGSTATUS CreateInstance(ICGUnknown *pUnknownOuter, REFIID iid, PVOID *ppvObject);

    CGSTATUS QueryInterface0(REFIID iid, PVOID *ppvObject);
    CG_IUNKNOWN_IMPLEMENT(CCGClassFactory);
};

#endif // _CLASSFACTORY_H_11613e77_998f_4fa9_9b42_5cc9a038fcd7

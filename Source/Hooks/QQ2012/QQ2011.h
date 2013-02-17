#ifndef _QQ2011_H_
#define _QQ2011_H_

#define CINTERFACE 1

#include "MyLibraryUser.h"

DECLARE_INTERFACE_(IQQGetConfigData, IUnknown)
{
    STDMETHOD(Dummy1)();
    STDMETHOD(Dummy2)();
    STDMETHOD(Dummy3)();
    STDMETHOD(Dummy4)();
    STDMETHOD(Dummy5)();
    STDMETHOD(Dummy6)();
    STDMETHOD(Dummy7)();
    STDMETHOD(Dummy8)();
    STDMETHOD(Dummy9)();
    STDMETHOD(Dummy10)();
    STDMETHOD(Dummy11)();
    STDMETHOD(Dummy12)();

    STDMETHOD(GetConfigByName)(PWSTR ConfigName, PVOID ConfigData);
};

typedef struct
{
	PWSTR                   DllName;
	PMEMORY_PATCH           Patch;
	ULONG                   PatchCount;
	PMEMORY_FUNCTION_PATCH  Function;
	ULONG                   FunctionCount;

} PATCH_SET;

// contracts.dll 61948343 age

#endif /* _QQ2011_H_ */
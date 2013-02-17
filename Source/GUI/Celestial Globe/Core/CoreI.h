#ifndef _COREI_H_35482582_6281_4e01_be9f_dbf8620a5bab
#define _COREI_H_35482582_6281_4e01_be9f_dbf8620a5bab

#include "pragma_once.h"
//#include "../Internal/CG_Headers.h"
#include "../Internal/CG_Core.h"
#include "Core.h"

CG_INTERFACE_FROM_CLASS(CCGCore, ICGCore)
{
protected:
    CCGCore *m_pCore;

public:
    CCGCoreI(ICGUnknown *pUnknwonOuter, CCGCore *pCore);

    CGSTATUS CG_METHOD_CALLTYPE QueryCoreInterface  (REFIID iid, PVOID *ppvObject);

    CGSTATUS CG_METHOD_CALLTYPE CreateString       (PUNICODE_STRING DestinationString, LPCWSTR SourceString);
    CGSTATUS CG_METHOD_CALLTYPE FreeString         (PUNICODE_STRING UnicodeString);
    LONG     CG_METHOD_CALLTYPE CompareString      (PUNICODE_STRING String1, PUNICODE_STRING String2, BOOL CaseInSensitive);

    CGSTATUS CG_METHOD_CALLTYPE ReadProfileString  (LPCWSTR KeyName, PUNICODE_STRING Buffer, BOOL AllocateBuffer);
    CGSTATUS CG_METHOD_CALLTYPE ReadProfileInt     (LPCWSTR KeyName, PLONG64 Buffer);
    CGSTATUS CG_METHOD_CALLTYPE SaveProfileString  (LPCWSTR KeyName, LPCWSTR Value);
    CGSTATUS CG_METHOD_CALLTYPE SaveProfileInt     (LPCWSTR KeyName, LONG64 Value);

    CG_IUNKNOWN_IMPLEMENT(CCGCoreI);
};

#endif // _COREI_H_35482582_6281_4e01_be9f_dbf8620a5bab

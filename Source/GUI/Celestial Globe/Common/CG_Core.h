#ifndef _CG_CORE_H_7116b5f1_7a4d_4960_b1f9_e90ae3ae9834
#define _CG_CORE_H_7116b5f1_7a4d_4960_b1f9_e90ae3ae9834

#include "pragma_once.h"
#include "CG_Common.h"
#include "CG_Types.h"
#include "CG_Interface.h"
#include "CG_Memory.h"
#include "CG_FileIO.h"

enum
{
    CompareCaseInSensitive  = FALSE,
    CompareCaseSensitive    = TRUE,
};

CG_INTERFACE(ICGCoreBase)
{
    CG_METHOD(GetInterface)(THIS_ REFIID iid, PVOID *ppvObject) PURE;

    // string
    CG_METHOD(CreateString)     (THIS_ PUNICODE_STRING DestinationString, LPCWSTR SourceString) PURE;
    CG_METHOD(FreeString)       (THIS_ PUNICODE_STRING UnicodeString) PURE;
    CG_METHOD_TYPE(LONG, CompareString)(THIS_ PUNICODE_STRING String1, PUNICODE_STRING String2, BOOL CaseInSensitive) PURE;

    // profile
    CG_METHOD(ReadProfileString)(THIS_ LPCWSTR KeyName, PUNICODE_STRING Buffer, BOOL AllocateBuffer) PURE;
    CG_METHOD(ReadProfileInt)   (THIS_ LPCWSTR KeyName, PLONG64 Buffer) PURE;
    CG_METHOD(SaveProfileString)(THIS_ LPCWSTR KeyName, LPCWSTR Value) PURE;
    CG_METHOD(SaveProfileInt)   (THIS_ LPCWSTR KeyName, LONG64 Value) PURE;
};

CG_INTERFACE_(ICGCore, ICGUnknown, ICGCoreBase)
{
    // ICGUnknown
    CG_METHOD(QueryInterface)       (THIS_ REFIID iid, PVOID *ppvObject) PURE;
    CG_METHOD_TYPE(ULONG, AddRef)   (THIS) PURE;
    CG_METHOD_TYPE(ULONG, Release)  (THIS) PURE;
};

#endif // _CG_CORE_H_7116b5f1_7a4d_4960_b1f9_e90ae3ae9834

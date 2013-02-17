#ifndef _CG_UI_H_55fd1f23_f9c9_4f1e_b76b_147779641bfa
#define _CG_UI_H_55fd1f23_f9c9_4f1e_b76b_147779641bfa

#include "pragma_once.h"
#include "CG_Interface.h"

enum MessageBoxButton
{
    ButtonOk        = 0x00000001,
    ButtonCancel    = 0x00000002,
    ButtonYes       = 0x00000004,
    ButtonNo        = 0x00000008,
    ButtonRetry     = 0x00000010,
};

CG_INTERFACE(ICGUIBase)
{
    CG_METHOD(MessageBox)(LPCWSTR Text, LPCWSTR Caption, MessageBoxButton Buttons);
};

CG_INTERFACE_(ICGUI, ICGUnknown, ICGUIBase)
{
    CG_METHOD(QueryInterface)       (THIS_ REFIID iid, PVOID *ppvObject) PURE;
    CG_METHOD_TYPE(ULONG, AddRef)   (THIS) PURE;
    CG_METHOD_TYPE(ULONG, Release)  (THIS) PURE;
};

#endif // _CG_UI_H_55fd1f23_f9c9_4f1e_b76b_147779641bfa

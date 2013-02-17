#ifndef _CG_UI_H_a6ba9ab6_58df_4cc7_af99_4868df696ae6
#define _CG_UI_H_a6ba9ab6_58df_4cc7_af99_4868df696ae6

#include "pragma_once.h"
#include "../Common/CG_UI.h"
#include "CG_Interface.h"

CG_INTERFACE_(ICGUIMain, ICGUnknown)
{
    CG_METHOD(QueryInterface)       (THIS_ REFIID iid, PVOID *ppvObject) PURE;
    CG_METHOD_TYPE(ULONG, AddRef)   (THIS) PURE;
    CG_METHOD_TYPE(ULONG, Release)  (THIS) PURE;

    CG_METHOD(Create)               (THIS_ ULONG X, ULONG Y, ULONG Width, ULONG Height) PURE;
    CG_METHOD(Show)                 (THIS) PURE;
    CG_METHOD(Execute)              (THIS) PURE;
    CG_METHOD(Destroy)              (THIS) PURE;
};

#endif // _CG_UI_H_a6ba9ab6_58df_4cc7_af99_4868df696ae6

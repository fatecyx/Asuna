#ifndef _CG_COMMON_H_10b2aeca_2767_49a3_9be5_d0f965b8d8fa
#define _CG_COMMON_H_10b2aeca_2767_49a3_9be5_d0f965b8d8fa

#include "pragma_once.h"
#include <Windows.h>
#include "my_headers.h"

#define CG_SUCCESS(_status)  (((CGSTATUS)(_status)) >= 0)

#if defined(CG_IMPLEMENT)

#define CG_API EXTC
 // EXTC_EXPORT

#else   // CG_IMPLEMENT

#define CG_API EXTC
// EXTC_IMPORT

#endif  // CG_IMPLEMENT

#endif // _CG_COMMON_H_10b2aeca_2767_49a3_9be5_d0f965b8d8fa

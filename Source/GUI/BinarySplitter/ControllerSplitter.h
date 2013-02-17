#ifndef _CONTROLLERSPLITTER_H_
#define _CONTROLLERSPLITTER_H_

#include "pragma_once.h"
#include "my_headers.h"
#include "WindowBase.h"
#include "ViewSplitter.h"
#include "ModelSplitter.h"

EXTCPP class CModelSplitter;
EXTCPP class CViewSplitter;

class CControllerSplitter : public MyWindowClass::CControllerBase<CViewSplitter, CModelSplitter>
{
protected:
    CRITICAL_SECTION m_csSetProgress;

public:
    Int  Execute(HINSTANCE hInstance = NULL);
    Bool Split();
    Bool Merge();
    Bool Open();

protected:
    PCTChar MapModelErrorToControllerMessage(Long ErrorCode);

    Bool ShowStatusInternal(PULarge_Integer pBytesProcessed, PULarge_Integer pFileSize);
    Bool ShowErrorMessageInternal(PCTChar pszFormat, va_list args);
    Bool ShowErrMsgWithStatusInternal(Long Status, PCTChar pszInfo);

    static Bool STDCALL ShowStatus(ULong_Ptr Param, PULarge_Integer pBytesProcessed, PULarge_Integer pFileSize);
    static Bool CDECL   ShowErrorMessage(ULong_Ptr Param, PCTChar pszFormat, ...);
    static Bool CDECL   ShowAskMessage(ULong_Ptr Param, PCTChar pszFormat, ...);
    static Bool STDCALL ShowErrorMessageByStatus(ULong_Ptr Param, Long Status, PCTChar pszInfo);
};

#endif /* _CONTROLLERSPLITTER_H_ */
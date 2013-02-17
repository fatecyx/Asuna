#ifndef _CONTROLLERSCRIPT_H_
#define _CONTROLLERSCRIPT_H_

#include "pragma_once.h"
#include "WindowBase.h"
#include "ViewScript.h"
#include "ModelScript.h"
#include "resource.h"

EXTCPP class CViewScriptEditor;
EXTCPP class CModelScript;

enum
{
    CTRL_ERROR_SUCCESS,
    CRTL_ERROR_OPEN_SCRIPT_FAILED,
    CTRL_ERROR_SHOW_TEXT,
    CTRL_ERROR_SELECT_TEXT_NO_ORIG_TEXT,
    CTRL_ERROR_SELECT_TEXT_NO_TRANS_TEXT,
    CTRL_ERROR_SAVE_CURRENT_SENTENCE,
    CTRL_ERROR_SUBMIT_FAILED,
};

class CControllerScript : public MyWindowClass::CControllerBase<CViewScriptEditor, CModelScript>
{
protected:

public:
    CControllerScript();
    ~CControllerScript();

    Int  Execute();
    Bool OpenScript(PCTChar pszScriptPath);
    Bool SelectText(SizeT Index);
    Bool SaveOneSentence(SizeT Index, Int MoveStep);
    Bool SaveTranslation();
    Bool SubmitAllTranslation();

protected:
    Void  ShowError(PCTChar pszFormat, ...);
    Bool  ShowText();
    SizeT FormatText(PWChar pszBuffer, SScriptText *pScriptText, Bool bTranslation);
};

#endif /* _CONTROLLERSCRIPT_H_ */
#ifndef _VIEWSCRIPT_H_
#define _VIEWSCRIPT_H_

#include "pragma_once.h"
#include "WindowBase.h"
#include "ControllerScript.h"
#include "ListBox.h"
#include "EditBox.h"
#include "resource.h"

EXTCPP class CControllerScript;

#define CONFIG_SECTION     _T("Amano")
#define CONFIG_WIDTH       _T("Width")
#define CONFIG_HEIGHT      _T("Height")
#define CONFIG_MIN_WIDTH   _T("MinWidth")
#define CONFIG_MIN_HEIGHT  _T("MinHeight")

class CViewScriptEditor : public MyWindowClass::CDialogImpl2
{
protected:
    CControllerScript *m_pController;
    MyWindowClass::CEditBox m_EditOriginal, m_EditTranslation, m_EditOriginalName, m_EditTranslationName;
    MyWindowClass::CListBox m_ListOriginal, m_ListTranslation;

    HFONT m_hFont;
    POINT m_ptMinTrackSize;
    SIZE  m_LastSize;
    TEXTMETRIC m_TextMetric;

public:
    CViewScriptEditor();
    ~CViewScriptEditor();

    Int Run();
    Int ShowErrorMessage(PCTChar pszFormat, ...);
    Int ShowErrorMessage(PCTChar pszFormat, va_list ArgList);

    CControllerScript* SetController(CControllerScript *pController);
    CControllerScript* RemoveController();
    
    SizeT AppendTextListOriginal(PCWChar pszText);
    SizeT InsertTextListOriginal(SizeT Index, PCWChar pszText);
    SizeT UpdateTextListOriginal(SizeT Index, PCWChar pszText);
    SizeT AppendTextListTranslation(PCWChar pszText);
    SizeT InsertTextListTranslation(SizeT Index, PCWChar pszText);
    SizeT UpdateTextListTranslation(SizeT Index, PCWChar pszText);
    Void  ClearTextListOriginal();
    Void  ClearTextListTranslation();
    SizeT SetTextListSelection(SizeT Index);

    Void  OnAppendTextFinish(SizeT MaxLengthOrig, SizeT MaxLengthTrans);

    SizeT GetTextTranslation(PWChar pszBuffer, SizeT BufferCount);
    SizeT GetTextTranslationLength();

    SizeT GetTextListCurrentSelection();

    Void
    SetCurrentText(
        PCWChar pszOriginalName,
        PCWChar pszOriginalText,
        PCWChar pszTransName,
        PCWChar pszTransText,
        SizeT   TransTextBegin = 0,
        SizeT   TransTextEnd   = -1
    );

protected:
    BEGIN_MSG_MAP(CViewScriptEditor)
        MSG_HANDLER(WM_COMMAND,       OnCommand)
        MSG_HANDLER(WM_MOUSEWHEEL,    OnMouseWheel)
        MSG_HANDLER(WM_SIZE,          OnSize)
        MSG_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
        MSG_HANDLER(WM_DROPFILES,     OnDropFiles)
        MSG_HANDLER(WM_LBUTTONDOWN,   OnLButtonDown)
        MSG_HANDLER(WM_LBUTTONUP,     OnLButtonUp)
        MSG_HANDLER(WM_INITDIALOG,    OnInitDialog)
        MSG_HANDLER(WM_DESTROY,       OnDestroy)
    END_MSG_MAP();

    DECL_MSG_HANDLER(WM_COMMAND,       OnCommand);
    DECL_MSG_HANDLER(WM_MOUSEWHEEL,    OnMouseWheel);
    DECL_MSG_HANDLER(WM_SIZE,          OnSize);
    DECL_MSG_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo);
    DECL_MSG_HANDLER(WM_DROPFILES,     OnDropFiles);
    DECL_MSG_HANDLER(WM_LBUTTONUP,     OnLButtonUp);
    DECL_MSG_HANDLER(WM_LBUTTONDOWN,   OnLButtonDown);
    DECL_MSG_HANDLER(WM_INITDIALOG,    OnInitDialog);
    DECL_MSG_HANDLER(WM_DESTROY,       OnDestroy);

    Bool  OpenScript(PCTChar pszScriptPath);
    SizeT AddTextWorker(MyWindowClass::CListBox &ListBox, SizeT Index, PCWChar pszText);
    SizeT UpdateTextWorker(MyWindowClass::CListBox &ListBox, SizeT Index, PCWChar pszText);
    Void  EmptyListBoxWorker(MyWindowClass::CListBox &ListBox);
    Void  SyncListBoxScrollBar(Int ID);
    Void  SyncTextToEditBox();
    Void  SelectText();
    Void  AdjustControlsPos(Int cx, Int cy, Int deltaX, Int deltaY);

    Bool  GetConfigPath(PTChar pszConfig, SizeT BufferCount);
};

#endif /* _VIEWSCRIPT_H_ */
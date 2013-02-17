#include "ControllerScript.h"

#define SHOW_ERROR_AND_RETURN(...) \
            { \
                ShowError(__VA_ARGS__); \
                return False; \
            }

CControllerScript::CControllerScript()
{
}

CControllerScript::~CControllerScript()
{
}

Int CControllerScript::Execute()
{
    if (!IsViewAttached() || !IsModelAttached())
        return -1;

    m_pView->SetController(this);

    return m_pView->Run();
}

Void CControllerScript::ShowError(PCTChar pszFormat, ...)
{
    va_list ArgList;

    va_start(ArgList, pszFormat);
    m_pView->ShowErrorMessage(pszFormat, ArgList);
}

SizeT CControllerScript::FormatText(PWChar pszBuffer, SScriptText *pScriptText, Bool bTranslation)
{
    SizeT Length;
    PWChar pszText;

    if (bTranslation)
        pszText = m_pModel->GetCharNameTranslationByIndex(pScriptText->CharNameIndex);
    else
        pszText = m_pModel->GetCharNameOriginalByIndex(pScriptText->CharNameIndex);

    Length = pszText != NULL ? wsprintfW(pszBuffer, L"%s\t", pszText) : 0;    

    pszText = pScriptText->Text.GetBuffer();
    Length += wsprintfW(pszBuffer + Length, L"%s", pszText);

    return Length;
}

Bool CControllerScript::ShowText()
{
    SizeT OriginalCount, TransCount, MaxLengthOrig, MaxLengthTrans;
    SScriptText *pOriginalText, *pTransText;

    OriginalCount = m_pModel->GetTextListOriginal(&pOriginalText);
    TransCount = m_pModel->GetTextListTranslation(&pTransText);

    if (OriginalCount == 0)
        return False;

    MaxLengthOrig  = 0;
    MaxLengthTrans = 0;
    m_pView->ClearTextListOriginal();
    m_pView->ClearTextListTranslation();
    for (SizeT Index = 0; OriginalCount; --OriginalCount, ++pOriginalText, ++Index)
    {
        SizeT Length;
        WChar szBuffer[0x1000];
        SScriptText *pScriptText;

        Length = FormatText(szBuffer, pOriginalText, False);
        MaxLengthOrig = MY_MAX(Length, MaxLengthOrig);
        m_pView->AppendTextListOriginal(szBuffer);

        if (pTransText == NULL ||
            TransCount == 0 ||
            pOriginalText->LogicalLine != pTransText->LogicalLine)
        {
            pScriptText = pOriginalText;
        }
        else
        {
            --TransCount;
            pScriptText = pTransText++;
        }

        Length = FormatText(szBuffer, pScriptText, True);
        MaxLengthTrans = MY_MAX(Length, MaxLengthTrans);
        m_pView->AppendTextListTranslation(szBuffer);
    }

    m_pView->OnAppendTextFinish(MaxLengthOrig, MaxLengthTrans);

    return True;
}

Bool CControllerScript::OpenScript(PCTChar pszScriptPath)
{
    Long Result;

    Result = m_pModel->ParseScript(pszScriptPath);
    if (SCR_FAILED(Result))
        SHOW_ERROR_AND_RETURN(
            _T("%s :\n")
            _T("Open script failed.\n")
            _T("%s"),
            pszScriptPath,
            m_pModel->GetErrorString(Result));

    if (!ShowText())
        SHOW_ERROR_AND_RETURN(_T("Show script text failed"));

    m_pView->SetTextListSelection(0);
    return True;
}

Bool CControllerScript::SelectText(SizeT Index)
{
    SizeT Start, End;
    SScriptText *pTextOrig, *pTextTrans;

    pTextOrig = m_pModel->GetTextOriginal(Index);
    if (pTextOrig == NULL)
        return False;

    pTextTrans = m_pModel->GetTextTranslation(Index);
    if (pTextTrans == NULL)
        return False;

    m_pModel->GetTextSelectionRange(pTextTrans, &Start, &End);
    m_pView->SetCurrentText(
        m_pModel->GetCharNameOriginalByIndex(pTextOrig->CharNameIndex),
        pTextOrig->Text,
        m_pModel->GetCharNameTranslationByIndex(pTextTrans->CharNameIndex),
        pTextTrans->Text,
        Start,
        End);

    return True;
}

Bool CControllerScript::SaveOneSentence(SizeT Index, Int MoveStep)
{
    WChar szBuffer[0x1000], szText[0x1000];
    SScriptText *pText;

    if (m_pView->GetTextTranslation(szBuffer, countof(szBuffer)) == 0)
        SHOW_ERROR_AND_RETURN(_T("Fail to get current translation when press enter"));

    if (m_pModel->UpdateTextTranslation(Index, szBuffer, &pText))
    {
        FormatText(szText, pText, True);
        m_pView->UpdateTextListTranslation(Index, szText);
    }

    if (MoveStep == 0)
        return True;

    if (Index == 0 && MoveStep < 0)
    {
        Index = m_pModel->GetTextListOriginalCount() - 1;
    }
    else
    {
        Index += MoveStep;
        if (Index >= m_pModel->GetTextListOriginalCount())
            Index = 0;
    }

    m_pView->SetTextListSelection(Index);

    return True;
}

Bool CControllerScript::SaveTranslation()
{
    return SCR_SUCCESS(m_pModel->SaveTranslationToFile());
}

Bool CControllerScript::SubmitAllTranslation()
{
    if (!SaveOneSentence(m_pView->GetTextListCurrentSelection(), 0))
        SHOW_ERROR_AND_RETURN(_T("Save current text failed"));

    if (SCR_FAILED(m_pModel->SubmitAllTranslation()))
        return False;

    return ShowText();
}
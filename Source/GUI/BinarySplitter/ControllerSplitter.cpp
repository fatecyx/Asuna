#include "ControllerSplitter.h"

Int CControllerSplitter::Execute(HINSTANCE hInstance /* = NULL */)
{
    Int Result;

    if (!IsViewAttached() || !IsModelAttached())
        return -1;

    InitializeCriticalSectionAndSpinCount(&m_csSetProgress, 4000);

    m_pView->SetController(this);
    Result = m_pView->Run(hInstance);

    DeleteCriticalSection(&m_csSetProgress);

    return Result;
}

Bool CDECL CControllerSplitter::ShowErrorMessage(ULong_Ptr Param, PCTChar pszFormat, ...)
{
    va_list args;
    CControllerSplitter *This;

    va_start(args, Param);
    This = (CControllerSplitter *)Param;
    return This->ShowErrorMessageInternal(pszFormat, args);
}

Bool CDECL CControllerSplitter::ShowAskMessage(ULong_Ptr Param, PCTChar pszFormat, ...)
{
    va_list args;
    CControllerSplitter *This;

    va_start(args, pszFormat);
    This = (CControllerSplitter *)Param;
    return This->m_pView->ShowAskMessageV(pszFormat, args) == IDOK;
}

Bool CControllerSplitter::ShowErrorMessageInternal(PCTChar pszFormat, va_list args)
{
    m_pView->ShowErrorMessageV(pszFormat, args);
    return True;
}

Bool STDCALL CControllerSplitter::ShowErrorMessageByStatus(ULong_Ptr Param, Long Status, PCTChar pszInfo)
{
    CControllerSplitter *This;
    This = (CControllerSplitter *)Param;
    return This->ShowErrMsgWithStatusInternal(Status, pszInfo);
}

Bool CControllerSplitter::ShowErrMsgWithStatusInternal(Long Status, PCTChar pszInfo)
{
    if (pszInfo != NULL)
        m_pView->ShowErrorMessage(_T("%s\n%s"), pszInfo, MapModelErrorToControllerMessage(Status));
    else
        m_pView->ShowErrorMessage(_T("%s"), MapModelErrorToControllerMessage(Status));
    return True;
}

Bool
STDCALL
CControllerSplitter::
ShowStatus(
    ULong_Ptr      Param,
    PULarge_Integer pBytesProcessed,
    PULarge_Integer pFileSize
)
{
    CControllerSplitter *This = (CControllerSplitter *)Param;
    return This->ShowStatusInternal(pBytesProcessed, pFileSize);
}

Bool
CControllerSplitter::
ShowStatusInternal(
    PULarge_Integer pBytesProcessed,
    PULarge_Integer pFileSize
)
{
    if (pBytesProcessed == NULL || pFileSize == NULL)
        return m_pView->SetOperationComplete(True);

    return m_pView->SetProgress((pBytesProcessed->QuadPart - 1) * 100 / pFileSize->QuadPart + 1);
}

Bool CControllerSplitter::Split()
{
    Long  Status;
    union
    {
        TChar szInptut[MAX_PATH + 20];
        TChar szOutput[MAX_PATH + 20];
        TChar szPassword[MAX_PASSWORD_LENGTH];
    };

    SPLIT_OPTION option;

    option.SpliceSizeInByte.QuadPart = m_pView->GetSliceSize();

    option.fSaveFileName        = m_pView->IsSaveOriginalFileName();
    option.fCompress            = m_pView->IsOutputCompress();
    option.fEncrypt             = m_pView->IsOutputEncrypt();
    option.pfShowStatus         = ShowStatus;
    option.pfShowErrorMessage   = ShowErrorMessage;
    option.pfShowAskMessage     = ShowAskMessage;
    option.pfShowStatusMessage  = ShowErrorMessageByStatus;
    option.CallbackParam        = (ULong_Ptr)this;

    if (m_pView->GetInputFileName(szInptut, countof(szInptut)) != 0)
        option.InputFile = szInptut;

    if (m_pView->GetOutputFileName(szOutput, countof(szOutput)) != 0)
        option.OutputFile = szOutput;

    if (option.fEncrypt && m_pView->GetPassword(szPassword, countof(szPassword)) != 0)
        option.Password = szPassword;

    Status = m_pModel->Split(&option);
    if (BS_FAILED(Status))
    {
        m_pView->ShowErrorMessage(_T("%s"), MapModelErrorToControllerMessage(Status));
        return False;
    }

    m_pView->SetOperationComplete(False);

    return True;
}

Bool CControllerSplitter::Merge()
{
    Long Status;
    union
    {
        TChar szInptut[MAX_PATH + 20];
        TChar szOutput[MAX_PATH + 20];
        TChar szPassword[MAX_PASSWORD_LENGTH];
    };

    if (m_pView->GetInputFileName(szInptut, countof(szInptut)) == 0 || GetFileAttributes(szInptut) == -1)
    {
        m_pView->ShowErrorMessage(CTRL_ERR_STRING_INVALID_INPUT_NAME);
        return False;
    }

    MERGE_OPTION option;

    option.InputFile = szInptut;

    if (m_pView->GetOutputFileName(szOutput, countof(szOutput)) != 0)
        option.OutputFile = szOutput;

    if (m_pView->GetPassword(szPassword, countof(szPassword)) != 0)
        option.Password = szPassword;

    option.fRestoreFileName     = m_pView->IsRestoreOriginalFileName();
    option.pfShowStatus         = ShowStatus;
    option.pfShowErrorMessage   = ShowErrorMessage;
    option.pfShowAskMessage     = ShowAskMessage;
    option.pfShowStatusMessage  = ShowErrorMessageByStatus;
    option.CallbackParam        = (ULong_Ptr)this;

    Status = m_pModel->Merge(&option);
    if (BS_FAILED(Status))
    {
        m_pView->ShowErrorMessage(_T("%s"), MapModelErrorToControllerMessage(Status));
        return False;
    }

    m_pView->SetOperationComplete(False);
    return True;
}

Bool CControllerSplitter::Open()
{
    Long  Status;
    Int32 Flags;
    TChar szPath[MAX_PATH];

    if (m_pView->GetInputFileName(szPath, countof(szPath)) == 0)
        return False;

    Status = m_pModel->VeirfyIsFirstFile(szPath, &Flags);
    if (BS_FAILED(Status))
    {
        m_pView->ShowErrorMessage(_T("%s"), MapModelErrorToControllerMessage(Status));
        return False;
    }

    m_pView->HasPassword(TEST_BITS(Flags, SPLIT_FLAG_ENCRYPT));
    m_pView->HasOriginalFileName(TEST_BITS(Flags, SPLIT_FLAG_SAVE_ORIG_NAME));

    return True;
}

PCTChar CControllerSplitter::MapModelErrorToControllerMessage(Long ErrorCode)
{
    static TChar *s_szErrMsg[] =
    {
        CTRL_ERR_STRING_UNKNOWN_ERROR,
        CTRL_ERR_STRING_FAILED_FILE_NOT_FOUND,
        CTRL_ERR_STRING_FAILED_OPEN_FILE,
        CTRL_ERR_STRING_FAILED_CREATE_FILE,
        CTRL_ERR_STRING_FAILED_GET_SIZE,
        CTRL_ERR_STRING_FAILED_READ_FILE,
        CTRL_ERR_STRING_FAILED_WRITE_FILE,
        CTRL_ERR_STRING_FAILED_CLOSE_FILE,
        CTRL_ERR_STRING_FAILED_IOCP_CREATE,
        CTRL_ERR_STRING_FAILED_IOCP_BIND_DEVICE,
        CTRL_ERR_STRING_FAILED_IOCP_GET_STATUS,
        CTRL_ERR_STRING_FAILED_QUEUE_ITEM,
        CTRL_ERR_STRING_FAILED_OUT_OF_MEMORY,
        CTRL_ERR_STRING_FAILED_INVALID_PARAM,
        CTRL_ERR_STRING_FAILED_FILE_SIZE_ZERO,
        CTRL_ERR_STRING_FAILED_INVALID_SLICE_SIZE,
        CTRL_ERR_STRING_FAILED_INVALID_FILE_SIZE,
        CTRL_ERR_STRING_FAILED_INVALID_FORMAT,
        CTRL_ERR_STRING_FAILED_NOT_FIRST,
        CTRL_ERR_STRING_FAILED_INVALID_PASSWORD,
        CTRL_ERR_STRING_FAILED_PART_FILE_CORRUPT,
    };

    if (ErrorCode == BSERR_SUCCESS)
        return CTRL_ERR_STRING_NO_ERROR;

    ErrorCode -= BSERR_FIRST;
    if (ErrorCode >= countof(s_szErrMsg))
        return _T("");

    return s_szErrMsg[ErrorCode];
}
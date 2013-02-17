#pragma comment(lib, "comctl32.lib")

#include "FtpUI.h"
#include "FolderDialog.h"
#include "OpenFileDialog.h"

SMenuItem Menu_FileList[] =
{
    { { FCONTROL|FVIRTKEY, 'T', IDM_DOWNLOAD }, _T("下载(&D)") },
};

SMenuItem Menu_Log[] =
{
    { { FVIRTKEY, 0, IDM_CLEAR_LIST_VIEW }, _T("清空(&C)") },
};

CFtpUI::CFtpUI()
{
    CoInitialize(NULL);
    m_hFontUI       = NULL;
    m_hMenuLvFile   = NULL;
    m_hMenuLvDlList = NULL;
    m_hMenuLvLog    = NULL;
}

CFtpUI::~CFtpUI()
{
    CoUninitialize();

    if (m_hFontUI != NULL)
        DeleteObject(m_hFontUI);
    if (m_hMenuLvFile != NULL)
        DestroyMenu(m_hMenuLvFile);
    if (m_hMenuLvDlList != NULL)
        DestroyMenu(m_hMenuLvDlList);
    if (m_hMenuLvLog != NULL)
        DestroyMenu(m_hMenuLvLog);
}

INT CFtpUI::Run(HINSTANCE hInstance)
{
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = 0xFFFF;
    InitCommonControlsEx(&icex);
    m_FtpHlp.SetShowLogCallback(ShowLog, (ULONG_PTR)this);
    return DoModal(IDD_DIALOG_MAIN, NULL, hInstance, NULL);
}

INT STDCALL CFtpUI::ShowLog(ULONG_PTR CallerParam, LPCTSTR pszFormat, va_list args)
{
    CFtpUI *pThis = (CFtpUI *)CallerParam;
    return pThis->ShowLogWoker(pszFormat, args);
}

LPCWSTR NextLineW(LPCWSTR pszText, DWORD Length = -1);

INT CFtpUI::ShowLogWoker(LPCTSTR pszFormat, va_list args)
{
    INT         Count;
    TCHAR       Buffer[1024];
    SYSTEMTIME  LocalTime;

    GetLocalTime(&LocalTime);
    wsprintf(Buffer, _T("%02d:%02d:%02d"), LocalTime.wHour, LocalTime.wMinute, LocalTime.wSecond);
    m_LvLog.InsertRow(Buffer, 0);

    wvsprintf(Buffer, pszFormat, args);
    Count = m_LvLog.GetItemCount();
    if (Count > MAX_LOG_LINES)
        m_LvLog.DeleteItem(Count - 1);

    m_LvLog.SetItemText(0, LV_LOG_MSG_INDEX, Buffer);

    return 0;
}

INT CFtpUI::ShowLogInternal(LPCTSTR pszFormat, ...)
{
    va_list args;
    va_start(args, pszFormat);
    return ShowLogWoker(pszFormat, args);
}

INT FormatFileSize(LPTSTR pszBuffer, ULARGE_INTEGER FileSize)
{
    ULONG   SizeInt, SizeReal;
    LPCTSTR pszUnit, pszFormat;

    pszFormat = _T("%u.%02u %s");
    if (FileSize.QuadPart >= MIN_TB_BYTES)
    {
        SizeInt  = FileSize.QuadPart / MIN_TB_BYTES;
        SizeReal = FileSize.QuadPart - SizeInt;
        pszUnit = _T("TB");
    }
    else if (FileSize.QuadPart >= MIN_GB_BYTES)
    {
        SizeInt = FileSize.QuadPart / MIN_GB_BYTES;
        SizeReal = FileSize.QuadPart - SizeInt;
        pszUnit = _T("GB");
    }
    else if (FileSize.LowPart >= MIN_MB_BYTES)
    {
        SizeInt = FileSize.LowPart / MIN_MB_BYTES;
        SizeReal = FileSize.LowPart - SizeInt;
        pszUnit = _T("MB");
    }
    else if (FileSize.LowPart >= MIN_KB_BYTES)
    {
        SizeInt = FileSize.LowPart / MIN_KB_BYTES;
        SizeReal = FileSize.LowPart - SizeInt;
        pszUnit = _T("KB");
    }
    else
    {
        SizeInt  = FileSize.LowPart;
        pszUnit  = _T("B");
        SizeReal = (ULONG)pszUnit;
        pszFormat = _T("%u %s");
    }

    if (SizeReal != (ULONG)pszUnit)
    while (SizeReal > 100)
        SizeReal /= 10;

    return wsprintf(pszBuffer, pszFormat, SizeInt, SizeReal, pszUnit);
}

LONG_PTR
STDCALL
CFtpUI::
DownloadStatusCallback(
    DOWNLOAD_REQUEST_ENTRY *pDownReq,
    ULONG_PTR               Key,
    ULONG_PTR               CallerParam
)
{
    CFtpUI *pThis = (CFtpUI *)CallerParam;
    return pThis->DownloadStatusInternal(pDownReq, Key);
}

FORCEINLINE LONG_PTR CFtpUI::DownloadStatusInternal(DOWNLOAD_REQUEST_ENTRY *pDownReq, ULONG_PTR Key)
{
    LVITEM lv;
    TCHAR  Buffer[200];

    if (pDownReq->UserData == 2)
        return 0;

    switch (pDownReq->Status)
    {
        case DOWNLOAD_STATUS_FAILED:
        case DOWNLOAD_STATUS_DELETE:
            if (pDownReq->UserData == 0)
                return 0;

            pDownReq->UserData = 2;

            lv.mask     = LVIF_TEXT;
            lv.iItem    = Key;
            lv.iSubItem = LV_DOWN_STATUS_INDEX;
            lv.pszText  = (LPWSTR)"\x18\x27\x00\x00";
            m_LvDlList.SetItem(&lv);

            return 0;
    }

    if (pDownReq->Status == DOWNLOAD_STATUS_DONE)
    {
        pDownReq->UserData = 2;
        lv.mask     = LVIF_TEXT;
        lv.iItem    = Key;
        lv.iSubItem = LV_DOWN_STATUS_INDEX;
        lv.pszText  = (LPWSTR)"\x14\x27\x00\x00";
        m_LvDlList.SetItem(&lv);
    }
    else if (pDownReq->UserData == 0)
    {
        pDownReq->UserData = 1;
        pDownReq->Key = m_LvDlList.GetItemCount();
        lv.mask = LVIF_TEXT|LVIF_PARAM;
        lv.lParam = pDownReq->Key;
        lv.pszText = (LPWSTR)"\xBB\x00\x00\x00"; // >>
        lv.iSubItem = LV_DOWN_STATUS_INDEX;
        lv.iItem = lv.lParam;

        m_LvDlList.InsertItem(&lv);

        FormatFileSize(Buffer, pDownReq->FileSize);
        lv.mask = LVIF_TEXT;
        lv.iSubItem = LV_DOWN_SIZE_INDEX;
        lv.pszText = Buffer;
        m_LvDlList.SetItem(&lv);
    }
    else
    {
        lv.iItem = Key;
    }

    lv.mask = LVIF_TEXT;
    lv.iSubItem = LV_DOWN_NAME_INDEX;
    lv.pszText = pDownReq->SavePath.FindFileName();
    m_LvDlList.SetItem(&lv);

    lv.pszText = Buffer;

    FormatFileSize(Buffer, pDownReq->BytesTransfered);
    lv.iSubItem = LV_DOWN_RECVED_INDEX;
    m_LvDlList.SetItem(&lv);

    wsprintf(Buffer, _T("%u%%"), (ULONG)(pDownReq->BytesTransfered.QuadPart * 100 / pDownReq->FileSize.QuadPart));
    lv.iSubItem = LV_DOWN_PERCENT_INDEX;
    m_LvDlList.SetItem(&lv);

    wsprintf(Buffer, _T("%u KB/S"), pDownReq->TransferSpeed / 1024);
    lv.iSubItem = LV_DOWN_SPEED_INDEX;
    m_LvDlList.SetItem(&lv);

    return 0;
}

INT CFtpUI::AddExtension(LPCTSTR pszExtension)
{
    DWORD_PTR Result;
    SHFILEINFO ShellFileInfo;

    if (*pszExtension == 0)
        return m_IconIndexBegin > LV_DEFAULT_ICON_INDEX ? LV_DEFAULT_ICON_INDEX : -1;

    Result = SHGetFileInfo(
                pszExtension,
                FILE_ATTRIBUTE_NORMAL,
                &ShellFileInfo,
                sizeof(ShellFileInfo),
                SHGFI_USEFILEATTRIBUTES|SHGFI_ICON);
    if (Result == 0)
        return -1;

    Result = ImageList_AddIcon(m_hImageListIcon, ShellFileInfo.hIcon);
    DestroyIcon(ShellFileInfo.hIcon);

    m_ExtensionList.Concatenate(pszExtension, StrLength(pszExtension) + 1);

    return Result;
}

INT CFtpUI::GetExtensionIndex(LPCTSTR pszExtensionList, LPCTSTR pszExtension)
{
    SIZE_T Length;
    INT    Index;

    if (pszExtension == NULL || *pszExtension == 0)
        return m_IconIndexBegin > LV_DEFAULT_ICON_INDEX ? LV_DEFAULT_ICON_INDEX : -1;

    if (pszExtensionList == NULL)
        return -1;

    Length = StrLength(pszExtension) + 1;
    Length *= sizeof(*pszExtension);
    for (Index = 0; ; ++Index)
    {
        if (*pszExtensionList == 0)
            return -1;

        if (!memcmp(pszExtensionList, pszExtension, Length))
            break;

        pszExtensionList += StrLength(pszExtensionList) + 1;
    }

    return Index + m_IconIndexBegin;
}

LONG_PTR
STDCALL
CFtpUI::
UICompletionRoutine(
    LONG      FtpStatus,
    DWORD     ErrorCode,
    DWORD     Flags,
    ULONG_PTR CompletionKey,
    ULONG_PTR CallerParam
)
{
    COMPLETION_ROUTINE_PARAM *pParam = (COMPLETION_ROUTINE_PARAM *)CallerParam;
    return pParam->pThis->UICompletionRoutineInternal(FtpStatus, ErrorCode, Flags, CompletionKey, pParam);
}

FORCEINLINE
LONG_PTR
CFtpUI::
UICompletionRoutineInternal(
    LONG                        FtpStatus,
    DWORD                       ErrorCode,
    DWORD                       Flags,
    ULONG_PTR                   CompletionKey,
    COMPLETION_ROUTINE_PARAM   *pParam
)
{
    LONG_PTR Ret;

    UNREFERENCED_PARAMETER(Flags);

    Ret = OP_RET_FINISH;
    switch (CompletionKey)
    {
        case OP_KEY_CONNECT:
            Ret = OnConnectDone(pParam, FtpStatus, ErrorCode);
            break;

        case OP_KEY_LOGIN:
            Ret = OnLoginDone(pParam, FtpStatus, ErrorCode);
            break;

        case OP_KEY_GETDIRINFO:
            Ret = OnGetDirInfoDone(pParam, FtpStatus, ErrorCode);
            break;

        case OP_KEY_CHANGEDIR:
            Ret = OnChangeDirDone(pParam, FtpStatus, ErrorCode);
            break;

        case OP_KEY_LOGOUT:
            ClearControlsContext();
            SetControlsState(TRUE);
            break;
    }

    switch (Ret)
    {
        case OP_RET_FAILED:
            m_FtpHlp.Logout(OP_KEY_LOGOUT, (ULONG_PTR)pParam, UICompletionRoutine);
            break;

        case OP_RET_FINISH:
            delete pParam;
            break;
    }

    return Ret;
}

LONG_PTR CFtpUI::OnConnectDone(COMPLETION_ROUTINE_PARAM *pParam, LONG FtpStatus, DWORD ErrorCode)
{
    LONG   Status;
    SIZE_T Length;
    LPSTR  pszUserNameA, pszPasswordA;
    LPWSTR pszUserNameW, pszPasswordW;

    UNREFERENCED_PARAMETER(ErrorCode);

    if (FTPHLP_FAILED(FtpStatus))
        return OP_RET_FAILED;

    if (IsDlgButtonChecked(IDC_CHECK_ANONYMOUS))
    {
        pszUserNameA = ANONYMOUS_USERNAME;
        pszPasswordA = ANONYMOUS_PASSWORD;
    }
    else
    {
        Length = ::GetWindowTextLength(m_EditUser) + 1;
        Length *= sizeof(WCHAR);
        pszUserNameW = (LPWSTR)_alloca(Length);
        ::GetWindowText(m_EditUser, pszUserNameW, Length / sizeof(WCHAR));
        pszUserNameA = (LPSTR)_alloca(Length);
        WideCharToMultiByte(CP_ACP, 0, pszUserNameW, -1, pszUserNameA, Length, NULL, NULL);

        Length = ::GetWindowTextLength(m_EditPwd) + 1;
        Length *= sizeof(WCHAR);
        pszPasswordW = (LPWSTR)_alloca(Length);
        ::GetWindowText(m_EditPwd, pszPasswordW, Length / sizeof(WCHAR));
        pszPasswordA = (LPSTR)_alloca(Length);
        WideCharToMultiByte(CP_ACP, 0, pszPasswordW, -1, pszPasswordA, Length, NULL, NULL);
    }

    Status = m_FtpHlp.Login(pszUserNameA, pszPasswordA, OP_KEY_LOGIN, (ULONG_PTR)pParam, UICompletionRoutine);

    return FTP_REAL_FAILED(Status) ? OP_RET_FINISH : OP_RET_CONTINUE;
}

LONG_PTR CFtpUI::OnLoginDone(COMPLETION_ROUTINE_PARAM *pParam, LONG FtpStatus, DWORD ErrorCode)
{
    LONG Status;

    UNREFERENCED_PARAMETER(ErrorCode);

    if (FTPHLP_FAILED(FtpStatus))
        return OP_RET_FAILED;

    Status = m_FtpHlp.GetCurrentDirectoryInfo(
                &pParam->pDir,
                FALSE,
                OP_KEY_GETDIRINFO,
                (ULONG_PTR)pParam,
                UICompletionRoutine);

    if (FTPHLP_SUCCESS(Status))
        return OnGetDirInfoDone(pParam, Status, NO_ERROR);

    return FTP_REAL_FAILED(Status) ? OP_RET_FINISH : OP_RET_CONTINUE;
}

LONG_PTR CFtpUI::OnGetDirInfoDone(COMPLETION_ROUTINE_PARAM *pParam, LONG FtpStatus, DWORD ErrorCode)
{
    INT             Index;
    LVITEM          LvItem;
    LPTSTR          pszExtension;
    DIRECTORY_INFO *pDir;

    UNREFERENCED_PARAMETER(ErrorCode);

    if (FTPHLP_FAILED(FtpStatus))
        return OP_RET_FAILED;

    pDir = pParam->pDir->pFiles;
    if (pDir == NULL)
        return OP_RET_FINISH;

    String FullPath;

    m_FtpHlp.GetDirectoryFullPath(pDir, FullPath);
    FullPath.RemoveFileName();
    ::SendMessageW(m_EditPath, WM_SETTEXT, 0, (LPARAM)(LPWSTR)FullPath);

    LvItem.iSubItem = LV_FILE_NAME_INDEX;
    Index = 0;
    m_LvFile.DeleteAllItem();

    m_LvFile.InsertRow(NULL, Index);

    LvItem.iItem    = Index;
    LvItem.lParam   = Index;
    LvItem.lParam   = Index;
    LvItem.pszText  = _T("..");
    LvItem.mask     = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;

    if (m_IconIndexBegin > LV_FOLDER_ICON_INDEX)
        LvItem.iImage = LV_FOLDER_ICON_INDEX;
    else
        LvItem.mask &= ~LVIF_IMAGE;

    m_LvFile.SetItem(&LvItem);

    ++Index;
    for (SIZE_T Count = pParam->pDir->FileCount; Count; ++pDir, --Count)
    {
        UINT  Mask;
        TCHAR Buffer[100];
        SYSTEMTIME ModifiedTime;
/*
        if (pDir->Name.IsEmpty())
            continue;
*/
        LvItem.lParam   = Index;
        LvItem.iItem    = Index;
        LvItem.pszText  = pDir->Name;
        Mask            = LVIF_TEXT|LVIF_IMAGE;

        if (pDir->CheckAttribute(FILE_ATTRIBUTE_DIRECTORY))
        {
            if (m_IconIndexBegin > LV_FOLDER_ICON_INDEX)
                LvItem.iImage = LV_FOLDER_ICON_INDEX;
            else
                Mask &= ~LVIF_IMAGE;

            Buffer[0] = 0;
            pszExtension = _T("Folder");
        }
        else
        {
            INT IconIndex;

            FormatFileSize(Buffer, pDir->FileSize);
            pszExtension = pDir->Name.FindExtension();
            IconIndex = GetExtensionIndex(m_ExtensionList, pszExtension);
            if (IconIndex == -1)
            {
                IconIndex = AddExtension(pszExtension);
                if (IconIndex == -1)
                    Mask &= ~LVIF_IMAGE;
            }

            LvItem.iImage = IconIndex;
            if (pszExtension != NULL && *pszExtension != 0)
                ++pszExtension;
        }

        m_LvFile.InsertRow(NULL, Index, Mask);
        m_LvFile.SetItemText(Index, LV_FILE_SIZE_INDEX, Buffer);
        m_LvFile.SetItemText(Index, LV_FILE_TYPE_INDEX, pszExtension);

        LvItem.mask = Mask | LVIF_PARAM;
        m_LvFile.SetItem(&LvItem);

        FileTimeToSystemTime(&pDir->LastWriteTime, &ModifiedTime);
        wsprintf(
            Buffer,
            _T("%04d-%02d-%02d   %02d:%02d:%02d"),
            ModifiedTime.wYear, ModifiedTime.wMonth, ModifiedTime.wDay,
            ModifiedTime.wHour, ModifiedTime.wMinute, ModifiedTime.wSecond);
        m_LvFile.SetItemText(Index, LV_FILE_TIME_INDEX, Buffer);

        ++Index;
    }

    m_LvFile.SetFocus();
    return OP_RET_FINISH;
}

LONG_PTR CFtpUI::OnChangeDirDone(COMPLETION_ROUTINE_PARAM *pParam, LONG FtpStatus, DWORD ErrorCode)
{
    LONG Status;

    UNREFERENCED_PARAMETER(ErrorCode);

    if (FTPHLP_FAILED(FtpStatus))
        return OP_RET_FAILED;

    Status = m_FtpHlp.GetCurrentDirectoryInfo(&pParam->pDir, FALSE, OP_KEY_GETDIRINFO, (ULONG_PTR)pParam, UICompletionRoutine);
    if (FTPHLP_SUCCESS(Status))
        return OnGetDirInfoDone(pParam, Status, NO_ERROR);

    return OP_RET_CONTINUE;
}

VOID CFtpUI::SetControlsState(BOOL bEnable)
{
    m_EditAddr.EnableWindow(bEnable);
    m_EditUser.EnableWindow(bEnable);
    m_EditPwd.EnableWindow(bEnable);
    m_EditPort.EnableWindow(bEnable);
    ::EnableWindow(GetDlgItem(IDC_BTN_LOGIN),  bEnable);
    ::EnableWindow(GetDlgItem(IDC_BTN_LOGOUT), !bEnable);
    ::EnableWindow(GetDlgItem(IDC_CHECK_ANONYMOUS), bEnable);
//    ::EnableWindow(GetDlgItem(IDC_EDIT_TASKS), bEnable);
}

VOID CFtpUI::ClearControlsContext()
{
    m_LvFile.DeleteAllItem();
}

VOID CFtpUI::OnLvDoubleClick(LPNMITEMACTIVATE lpnmitem)
{
    LONG Status;
    LVITEM LvItem;
    COMPLETION_ROUTINE_PARAM *pParam;

    if (lpnmitem->hdr.hwndFrom != m_LvFile)
        return;

    LvItem.mask  = LVIF_PARAM;
    LvItem.iItem = lpnmitem->iItem;
    if (!m_LvFile.GetItem(&LvItem))
        return;

    pParam = new COMPLETION_ROUTINE_PARAM(this);
    if (pParam == NULL)
        return;

    Status = m_FtpHlp.ChangeDirectory(
                LvItem.lParam - 1,
                OP_KEY_CHANGEDIR,
                (ULONG_PTR)pParam,
                UICompletionRoutine);
    if (FTPHLP_SUCCESS(Status))
        OnChangeDirDone(pParam, Status, NO_ERROR);
    else if (FTP_REAL_FAILED(Status))
        delete pParam;
}

VOID CFtpUI::OnLvRightClick(LPNMITEMACTIVATE lpnmitem)
{
    DWORD Pos;
    HMENU hMenu;

    if (lpnmitem->hdr.hwndFrom == m_LvLog)
        hMenu = m_hMenuLvLog;
    else if (lpnmitem->hdr.hwndFrom == m_LvFile)
        hMenu = m_hMenuLvFile;
    else
        return;

    if (hMenu == NULL)
        return;

    Pos = GetMessagePos();
    TrackPopupMenu(hMenu, 0, LOWORD(Pos), HIWORD(Pos), 0, *this, NULL);
}

LRESULT CFtpUI::OnNotify(HWND hWnd, INT IdFrom, LPNMHDR pnmhdr)
{
    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(IdFrom);

    switch (pnmhdr->code)
    {
        case NM_DBLCLK:
        case NM_RETURN:
            OnLvDoubleClick((LPNMITEMACTIVATE)pnmhdr);
            break;

        case NM_RCLICK:
            OnLvRightClick((LPNMITEMACTIVATE)pnmhdr);
            break;

        default:
            SetMsgHandled(FALSE);
    }

    return NO_ERROR;
}

VOID CFtpUI::OnDownloadSelected()
{
    INT             Count, Index;
    BOOL            bUserSamePath;
    LVITEM          LvItem;
    LPCWSTR         pszPath;
    DIRECTORY_INFO *pDir, *pFile;

    if (FTPHLP_FAILED(m_FtpHlp.GetCurrentDirectoryInfo(&pDir, FALSE, 0, 0, NULL)))
        return;

    CFolderDialog fd;
    COpenFileDialog ofd;

    LvItem.mask = LVIF_PARAM;
    bUserSamePath = FALSE;

    Index = -1;
    Count = 0;
    for (;;)
    {
        Index = m_LvFile.GetNextItem(Index, LVNI_SELECTED);
        if (Index == -1)
            break;

        if (Index == 0)
            continue;

        LvItem.iItem = Index;
        if (!m_LvFile.GetItem(&LvItem))
            continue;

        if (LvItem.lParam - 1 >= pDir->FileCount)
            continue;

        pFile = &pDir->pFiles[LvItem.lParam - 1];
        if (pFile->CheckAttribute(FILE_ATTRIBUTE_DIRECTORY))
        {

            if (!bUserSamePath)
            {
                if (!fd.DoModule(pFile->Name))
                    continue;
                if (GetAsyncKeyState(VK_CONTROL) < 0)
                    bUserSamePath = TRUE;
            }
            pszPath = fd.GetPathName();
        }
        else
        {
            if (!bUserSamePath)
            {
                ofd.SetOpenFileParam(*this, NULL, pFile->Name);
                ofd.SetDefaultFileName(pFile->Name);
                if (!ofd.GetSaveFileName())
                    continue;
                if (GetAsyncKeyState(VK_CONTROL) < 0)
                    bUserSamePath = TRUE;
            }

            pszPath = ofd.GetFileName();
        }

        m_FtpHlp.DownloadFile(LvItem.lParam - 1, pszPath, Count++, (ULONG_PTR)this, DownloadStatusCallback);
    }
}

VOID CFtpUI::OnCommand(HWND hWnd, INT ID, HWND hWndCtl, UINT codeNotify)
{
    BOOL  bTransfered;
    DWORD Value;

    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(hWndCtl);

    switch (ID)
    {
        case IDM_CLEAR_LIST_VIEW:
            m_LvLog.DeleteAllItem();
            break;

        case IDM_DOWNLOAD:
            OnDownloadSelected();
            break;

        case IDC_EDIT_TASKS:
//        case IDC_EDIT_TIMEOUT_CONNECT:
            switch (codeNotify)
            {
                case EN_MAXTEXT:
                    SetDlgItemInt(ID, 9);
                    break;

                case EN_CHANGE:
                    Value = GetDlgItemInt(ID, &bTransfered);
                    if (!bTransfered)
                        break;
                    m_FtpHlp.SetMaxConcurrentTask(Value);
            }
            break;

        default:
            SetMsgHandled(FALSE);
    }
}

BOOL CFtpUI::OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    UNREFERENCED_PARAMETER(hWndFocus);

    m_EditAddr.Attach(GetDlgItem(IDC_EDIT_ADDR));
    m_EditUser.Attach(GetDlgItem(IDC_EDIT_USERNAME));
    m_EditPwd.Attach(GetDlgItem(IDC_EDIT_PASSWORD));
    m_EditPort.Attach(GetDlgItem(IDC_EDIT_PORT));
    m_EditPath.Attach(GetDlgItem(IDC_EDIT_PATH));

    m_LvFile.Attach(GetDlgItem(IDC_LIST_FILE));
    m_LvLog.Attach(GetDlgItem(IDC_LIST_LOG));
    m_LvDlList.Attach(GetDlgItem(IDC_LIST_DLLIST));

    m_EditAddr.SetLimitText(4096);
    m_EditUser.SetLimitText(20);
    m_EditPwd.SetLimitText(1024);

    Edit_LimitText(GetDlgItem(IDC_EDIT_TASKS), 1);
    SetDlgItemInt(IDC_EDIT_TASKS, DEFAULT_MAX_TASKS);

    hWnd = GetDlgItem(IDC_EDIT_TIMEOUT_CONNECT);
    Edit_LimitText(hWnd, 3);
    ::EnableWindow(hWnd, FALSE);

    m_EditAddr.SetText(_T("127.0.0.1"));
//    m_EditAddr.SetText(_T("180.140.35.116"));
    m_EditUser.SetText(_T("FTPHelper"));
    m_EditPwd.SetText(_T("123456"));
    m_EditPort.SetText(_T("21"));

//    m_EditAddr.SetText(_T("www6.subdomain.com"));
//    m_EditUser.SetText(_T("user704819"));

    ::EnableWindow(GetDlgItem(IDC_BTN_LOGOUT), FALSE);

    m_IconIndexBegin = 0;
    m_hImageListIcon = ImageList_Create(17, 17, ILC_COLOR32, 4, 4);
    if (m_hImageListIcon != NULL)
    {
        DWORD_PTR  Result;
        SHFILEINFO ShellFileInfo;
        TCHAR szPath[MAX_PATH];

        GetExecuteDirectory(szPath, countof(szPath));
        m_LvFile.SetImageList(m_hImageListIcon, LVSIL_SMALL);
        Result = SHGetFileInfo(
                    szPath,
                    FILE_ATTRIBUTE_DIRECTORY,
                    &ShellFileInfo,
                    sizeof(ShellFileInfo),
                    SHGFI_USEFILEATTRIBUTES|SHGFI_ICON);
        if (Result != 0)
        {
            ++m_IconIndexBegin;
            ImageList_AddIcon(m_hImageListIcon, ShellFileInfo.hIcon);
            DestroyIcon(ShellFileInfo.hIcon);
        }
        Result = SHGetFileInfo(
                    _T("CON"),
                    FILE_ATTRIBUTE_NORMAL,
                    &ShellFileInfo,
                    sizeof(ShellFileInfo),
                    SHGFI_USEFILEATTRIBUTES|SHGFI_ICON);
        if (Result != 0)
        {
            ++m_IconIndexBegin;
            ImageList_AddIcon(m_hImageListIcon, ShellFileInfo.hIcon);
            DestroyIcon(ShellFileInfo.hIcon);
        }
    }

    m_LvLog.InsertColumn(LV_LOG_TIME_INDEX, _T("Time"), 0, 80);
    m_LvLog.InsertColumn(LV_LOG_MSG_INDEX, _T("Message"), 0, 750);
    m_LvLog.AddExStyle(LVS_EX_FULLROWSELECT);

    m_LvFile.InsertColumn(LV_FILE_NAME_INDEX, _T("File Name"), 0, 160);
    m_LvFile.InsertColumn(LV_FILE_SIZE_INDEX, _T("Size"), 0, 64);
    m_LvFile.InsertColumn(LV_FILE_TYPE_INDEX, _T("Type"), 0, 64);
    m_LvFile.InsertColumn(LV_FILE_TIME_INDEX, _T("Modified"), 0, 128);
    m_LvFile.AddExStyle(LVS_EX_FULLROWSELECT);

    m_LvDlList.InsertColumn(LV_DOWN_STATUS_INDEX,   _T("Status"),       0, 20);
    m_LvDlList.InsertColumn(LV_DOWN_NAME_INDEX,     _T("Name"),         0, 160);
    m_LvDlList.InsertColumn(LV_DOWN_SIZE_INDEX,     _T("Size"),         0, 64);
    m_LvDlList.InsertColumn(LV_DOWN_RECVED_INDEX,   _T("Completed"),    0, 64);
    m_LvDlList.InsertColumn(LV_DOWN_PERCENT_INDEX,  _T("Percent"),      0, 64);
    m_LvDlList.InsertColumn(LV_DOWN_SPEED_INDEX,    _T("Speed"),        0, 48);
    m_LvDlList.AddExStyle(LVS_EX_FULLROWSELECT);

    m_hMenuLvFile = CreateCombinedMenu(Menu_FileList, countof(Menu_FileList), TRUE);
    m_hMenuLvLog  = CreateCombinedMenu(Menu_Log, countof(Menu_Log), TRUE);

    m_hFontUI = CreateIconTitleFont();
    if (m_hFontUI != NULL)
        SendMessageToDescendants(WM_SETFONT, (WPARAM)m_hFontUI, TRUE);

    return TRUE;
}

VOID CFtpUI::OnDestroy(HWND hWnd)
{
    UNREFERENCED_PARAMETER(hWnd);
    ImageList_Destroy(m_hImageListIcon);
}

VOID CFtpUI::OnLButtonUp(HWND hWnd, Int x, Int y, UInt keyFlags)
{
    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(x);
    UNREFERENCED_PARAMETER(y);
    UNREFERENCED_PARAMETER(keyFlags);
    SendMessage(WM_NCLBUTTONUP, HTCAPTION);
}

VOID CFtpUI::OnLButtonDown(HWND hWnd, Bool fDoubleClick, Int x, Int y, UInt keyFlags)
{
    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(fDoubleClick);
    UNREFERENCED_PARAMETER(x);
    UNREFERENCED_PARAMETER(y);
    UNREFERENCED_PARAMETER(keyFlags);
    SendMessage(WM_NCLBUTTONDOWN, HTCAPTION);
}

VOID CFtpUI::OnChkBtnAnonymous(HWND hWnd, UINT codeNotify, UINT ID, HWND hWndCtl)
{
    UNREFERENCED_PARAMETER(hWndCtl);
    UNREFERENCED_PARAMETER(ID);
    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(codeNotify);

    if (!IsDlgButtonChecked(IDC_CHECK_ANONYMOUS))
        return;

    m_EditUser.SetText(_T(ANONYMOUS_USERNAME));
    m_EditPwd.SetText(NULL);
}

VOID CFtpUI::OnBtnLogin(HWND hWnd, UINT codeNotify, UINT ID, HWND hWndCtl)
{
    BOOL    bTranslated;
    LONG    Status;
    SIZE_T  Length;
    DWORD   Port;
    LPSTR   pszAddressA;
    LPWSTR  pszAddressW;
    COMPLETION_ROUTINE_PARAM *pParam;

    UNREFERENCED_PARAMETER(hWndCtl);
    UNREFERENCED_PARAMETER(ID);
    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(codeNotify);

    Port = GetDlgItemInt(IDC_EDIT_PORT, &bTranslated, FALSE);
    if (bTranslated == FALSE)
        return;

    if (!IsDlgButtonChecked(IDC_CHECK_ANONYMOUS))
    {
        Length = ::GetWindowTextLength(m_EditUser);
        if (Length == 0)
            return;

        Length = ::GetWindowTextLength(m_EditPwd);
        if (Length == 0)
            return;

        Length = ::GetWindowTextLength(m_EditAddr);
        if (Length == 0)
            return;

        ++Length;
        Length *= sizeof(WCHAR);
        pszAddressW = (LPWSTR)_alloca(Length);
        ::GetWindowText(m_EditAddr, pszAddressW, Length / sizeof(WCHAR));

        pszAddressA = (LPSTR)_alloca(Length);
        WideCharToMultiByte(CP_ACP, 0, pszAddressW, -1, pszAddressA, Length, NULL, NULL);
    }
    else
    {
        pszAddressA = ANONYMOUS_USERNAME;
    }

    pParam = new COMPLETION_ROUTINE_PARAM(this);
    if (pParam == NULL)
        return;

    if (!m_FtpHlp.IsInitialized())
    {
        Status = m_FtpHlp.Initialize();
        if (FTP_REAL_FAILED(Status))
        {
            delete pParam;
            return;
        }
    }

    Status = m_FtpHlp.Connect(pszAddressA, Port, OP_KEY_CONNECT, (ULONG_PTR)pParam, UICompletionRoutine);
    if (FTP_REAL_FAILED(Status))
    {
        delete pParam;
        return;
    }

    SetControlsState(FALSE);
    ShowLogInternal(_T("正在连接 %S"), pszAddressA);
}

VOID CFtpUI::OnBtnLogout(HWND hWnd, UINT codeNotify, UINT ID, HWND hWndCtl)
{
    UNREFERENCED_PARAMETER(hWndCtl);
    UNREFERENCED_PARAMETER(ID);
    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(codeNotify);

    m_FtpHlp.Logout(OP_KEY_LOGOUT, (ULONG_PTR)(new COMPLETION_ROUTINE_PARAM(this)), UICompletionRoutine);
}

VOID CFtpUI::OnBtnOK(HWND hWnd, UINT codeNotify, UINT ID, HWND hWndCtl)
{
    UNREFERENCED_PARAMETER(hWndCtl);
    UNREFERENCED_PARAMETER(ID);
    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(codeNotify);
}

VOID CFtpUI::OnBtnCancel(HWND hWnd, UINT codeNotify, UINT ID, HWND hWndCtl)
{
    UNREFERENCED_PARAMETER(hWndCtl);
    UNREFERENCED_PARAMETER(ID);
    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(codeNotify);
}
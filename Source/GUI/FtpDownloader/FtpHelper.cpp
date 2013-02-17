#pragma comment(lib, "WS2_32.lib")

#include "FtpHelper.h"
#include "IOCP.h"

OVERLOAD_CPP_NEW_WITH_HEAP(CMem::GetGlobalHeap())

CFTPHelper::CFTPHelper()
{
    m_pfShowLog         = NULL;
    m_pCurrentReq       = NULL;
    m_msTimeout         = 10 * 1000;
    m_msTimeout         = INFINITE;
    m_msTimeoutConnect  = 30 * 1000;
    m_MaxConcurrentTask = 1;
    Reset();
}

CFTPHelper::~CFTPHelper()
{
    UnInitialize();
}

VOID CFTPHelper::Reset()
{
    m_bInitialized      = FALSE;
    m_SockCtrl          = INVALID_SOCKET;
    m_SockData          = INVALID_SOCKET;
    m_hWnd              = NULL;
    m_hThreadWnd        = NULL;
    m_hThreadDownload   = NULL;
    m_DownloadThreadId  = 0;
    m_hEventWaitWnd     = NULL;
    m_pRootDir          = NULL;
    m_pCurrentReq       = NULL;
}

VOID CFTPHelper::SetTimeout(DWORD msConnectTimeout)
{
    this->m_msTimeoutConnect = msConnectTimeout;
}

DWORD CFTPHelper::SetMaxConcurrentTask(DWORD Number)
{
    m_MaxConcurrentTask = Number;
    return Number;
}

LONG_PTR
STDCALL
CFTPHelper::
CompletionRoutineInternal(
    LONG      FtpStatus,
    DWORD     Reserve,
    DWORD     Flags,
    ULONG_PTR CompletionKey,
    ULONG_PTR CallerParam
)
{
    CFTPHelper *pThis = (CFTPHelper *)CallerParam;

    UNREFERENCED_PARAMETER(Reserve);
    UNREFERENCED_PARAMETER(Flags);

    if ((PLONG)CompletionKey != NULL)
        *(PLONG)CompletionKey = FtpStatus;

    pThis->SetAsyncWaitEvent();

    return 0;
}

PVOID CFTPHelper::AllocaMemory(DWORD Size)
{
    return m_mem.Alloc(Size);
}

BOOL CFTPHelper::FreeMemory(PVOID pMemory)
{
    return m_mem.Free(pMemory);
}

HANDLE CFTPHelper::CreateAsyncWaitEvent()
{
    CloseAsyncWaitEvent();
    m_hEventWaitWnd = CreateEvent(NULL, FALSE, FALSE, NULL);
    return m_hEventWaitWnd;
}

BOOL CFTPHelper::CloseAsyncWaitEvent()
{
    BOOL Result;
    if (m_hEventWaitWnd != NULL)
    {
        Result = CloseHandle(m_hEventWaitWnd);
        m_hEventWaitWnd = NULL;
    }
    else
    {
        Result = FALSE;
    }

    return Result;
}

BOOL CFTPHelper::ResetAsyncWaitEvent()
{
    return ResetEvent(m_hEventWaitWnd);
}

BOOL CFTPHelper::SetAsyncWaitEvent()
{
    return SetEvent(m_hEventWaitWnd);
}

DWORD CFTPHelper::WaitAsyncWaitEvent(DWORD Milliseconds)
{
    return WaitForSingleObjectEx(m_hEventWaitWnd, Milliseconds, FALSE);
}

FShowLog CFTPHelper::SetShowLogCallback(FShowLog pfShowLog, ULONG_PTR CallerParam)
{
    m_ShowLogCallerParam = CallerParam;
    Swap(pfShowLog, m_pfShowLog);
    return pfShowLog;
}

INT CFTPHelper::ShowLog(LPCTSTR pszFormat, ...)
{
    if (m_pfShowLog == NULL)
        return 0;

    va_list args;
    va_start(args, pszFormat);
    return m_pfShowLog(m_ShowLogCallerParam, pszFormat, args);
}

BOOL CFTPHelper::IsInitialized()
{
    return m_bInitialized;
}

LONG CFTPHelper::UnInitialize()
{
    FTP_METHOD_ENTER();

    if (!m_bInitialized)
        return FTPHLP_ERROR_SUCCESS;

    if (m_SockCtrl != INVALID_SOCKET)
        closesocket(m_SockCtrl);
    if (m_SockData != INVALID_SOCKET)
        closesocket(m_SockData);

    if (m_hThreadWnd != NULL)
    {
        PostMessage(m_hWnd, WM_SOCKET_FORCE_QUIT, 0, 0);
        if (WaitForSingleObjectEx(m_hThreadWnd, m_msTimeout, FALSE) == WAIT_TIMEOUT)
        {
            if (TerminateThread(m_hThreadWnd, FTPHLP_ERROR_SUCCESS))
                WaitForSingleObjectEx(m_hThreadWnd, m_msTimeout, FALSE);
        }

        CloseHandle(m_hThreadWnd);
    }

    if (m_hThreadDownload != NULL)
    {
        PostThreadMessage(m_DownloadThreadId, WM_SOCKET_FORCE_QUIT, 0, 0);
        if (WaitForSingleObjectEx(m_hThreadDownload, m_msTimeout, FALSE) == WAIT_TIMEOUT)
        {
            if (TerminateThread(m_hThreadDownload, FTPHLP_ERROR_SUCCESS))
                WaitForSingleObjectEx(m_hThreadDownload, m_msTimeout, FALSE);
        }

        CloseHandle(m_hThreadDownload);
    }

    if (m_pRootDir != NULL)
        FreeDirectoryInfo(m_pRootDir);

    CloseAsyncWaitEvent();

    WSACleanup();

    Reset();
    m_bInitialized = FALSE;

    return FTPHLP_ERROR_SUCCESS;
}

LONG CFTPHelper::Initialize()
{
    LONG    Status;
    DWORD   ErrorCode;
    WSADATA Data;

    FTP_METHOD_ENTER();

    if (m_bInitialized)
        return FTPHLP_ERROR_SUCCESS;

    m_bInitialized = TRUE;
    Status = FTPHLP_ERROR_INITIALIZE_FAILED;

    LOOP_ONCE()
    {
        ErrorCode = WSAStartup(m_kWinSockVersion, &Data);
        SetLastError(ErrorCode);
        if (ErrorCode != NO_ERROR)
            break;

        if (CreateAsyncWaitEvent() == NULL)
            break;

        m_hThreadWnd = CreateThread(NULL, 0, WindowThread, this, 0, NULL);
        if (m_hThreadWnd == NULL)
            break;

        if (WaitAsyncWaitEvent(m_msTimeout) == WAIT_FAILED)
            break;

        SleepEx(0, FALSE);
        if (!GetExitCodeThread(m_hThreadWnd, &ErrorCode))
            break;

        if (ErrorCode != STILL_ACTIVE && FTPHLP_FAILED(ErrorCode))
        {
            Status = ErrorCode;
            break;
        }

        m_hThreadDownload = CreateThread(NULL, 0, DownloadThread, this, 0, &m_DownloadThreadId);
        if (m_hThreadDownload == NULL)
            break;

        if (WaitAsyncWaitEvent(m_msTimeout) == WAIT_FAILED)
            break;

        SleepEx(0, FALSE);
        if (!GetExitCodeThread(m_hThreadDownload, &ErrorCode))
            break;

        if (ErrorCode != STILL_ACTIVE && FTPHLP_FAILED(ErrorCode))
        {
            Status = ErrorCode;
            break;
        }

        Status = FTPHLP_ERROR_SUCCESS;
    }

    if (FTPHLP_FAILED(Status))
        UnInitialize();

    return Status;
}

LPCSTR NextLineA(LPCSTR pszText, DWORD Length = -1)
{
    while (*pszText != '\n')
    {
        if (*pszText == 0 || Length == 0)
            return NULL;

        if (*pszText < 0 && (--Length == 0 || *++pszText == 0))
            break;

        --Length;
        ++pszText;
    }

    return ++pszText;
}

LPCWSTR NextLineW(LPCWSTR pszText, DWORD Length = -1)
{
    while (*pszText != '\n')
    {
        if (*pszText == 0 || Length == 0)
            return NULL;

        if (*pszText < 0 && (--Length == 0 || *++pszText == 0))
            break;

        --Length;
        ++pszText;
    }

    return ++pszText;
}

LPCSTR CFTPHelper::IsRecvAllReplyText(LPCSTR pszReplyText, DWORD Length)
{
    LPCSTR pszLastLine, pszEnd;

    if (pszReplyText == NULL || Length < 3)
        return NULL;

    pszEnd = pszReplyText + Length;
    if (pszReplyText[3] == ' ')
    {
        pszLastLine = NextLineA(pszReplyText, Length);
        if (pszLastLine == NULL     ||
            pszLastLine > pszEnd    ||
            pszLastLine[-1] != '\n' ||
            pszLastLine[-2] != '\r')
        {
            return NULL;
        }

        return pszLastLine;
    }
    else if (pszReplyText[3] != '-')
    {
        return pszEnd;  // let GetServerReplyCode return error
    }

    pszLastLine = pszReplyText;
    for (;;)
    {
        pszLastLine = NextLineA(pszLastLine, pszEnd - pszLastLine);
        if (pszLastLine == NULL || pszLastLine[0] == 0 || pszLastLine > pszEnd)
            return NULL;
        if (pszLastLine[0] == ' ')
            continue;
        if (pszLastLine[3] != ' ')
            continue;

        pszLastLine = NextLineA(pszLastLine, pszEnd - pszLastLine);
        break;
    }

    return pszLastLine;
}

LONG CFTPHelper::GetServerReplyCode(LPCSTR pszReplyText, DWORD Length)
{
    LPCSTR pszText, pszEnd;

    FTP_METHOD_ENTER();

    if (pszReplyText[3] == ' ')
        return pszReplyText[0] * 100 + pszReplyText[1] * 10 + pszReplyText[2] - '0' * (100 + 10 + 1);
    else if (pszReplyText[3] != '-')
        return REPLY_CODE_INVALID;

    pszEnd = pszReplyText + Length;
    pszText = pszReplyText;
    for (;;)
    {
        pszText = NextLineA(pszText, pszEnd - pszText);
        if (pszText == NULL || pszText[0] == 0 || pszText > pszEnd)
            return REPLY_CODE_INVALID;
        if (pszText[0] == ' ')
            continue;
        if (pszText[3] == ' ')
            break;
    }

    if (!IN_RANGE('0', pszReplyText[0], '9') ||
        !IN_RANGE('0', pszReplyText[1], '9') ||
        !IN_RANGE('0', pszReplyText[2], '9'))
    {
        return REPLY_CODE_INVALID;
    }

    if ((*(PLONG)pszReplyText & 0x00FFFFFF) != (*(PLONG)pszText & 0x00FFFFFF))
        return REPLY_CODE_INVALID;

    return pszReplyText[0] * 100 + pszReplyText[1] * 10 + pszReplyText[2] - '0' * (100 + 10 + 1);
}

LPCSTR CFTPHelper::GetFTPCommandByID(FTP_COMMAND Command)
{
    static LPCSTR szFtpCommand[] =
    {
        // Access Control Commands
        "USER",
        "PASS",
        "ACCT",
        "CWD",
        "CDUP",
        "SMNT",
        "REIN",
        "QUIT",

        // Transfer Parameter Commands
        "PORT",
        "PASV",
        "TYPE",
        "STRU",
        "MODE",

        // FTP Service Commands
        "RETR",
        "STOR",
        "STOU",
        "APPE",
        "ALLO",
        "REST",
        "RNFR",
        "RNTO",
        "ABOR",
        "DELE",
        "RMD",
        "MKD",
        "PWD",
        "LIST",
        "NLST",

        // less common
        "SYST",
        "FEAT",
        "MLSD",
        "MLST",
    };

    ULONG_PTR _Command = (ULONG_PTR)Command;

    _Command -= (ULONG_PTR)FTP_COMMAND_BASE;
    if (_Command < (ULONG_PTR)FTP_COMMAND_MAX)
        return szFtpCommand[_Command];

    return NULL;
}

LONG CFTPHelper::GetDefFtpStatusFromRequest(ASYNC_REQUEST_ENTRY *pAsyncRequest)
{
    LONG Status;

    switch (pAsyncRequest->Type)
    {
        default:                Status = FTPHLP_ERROR_UNKNOWN; break;
        case ASYNC_REQ_LOGIN:   Status = FTPHLP_ERROR_LOGIN;   break;
    }

    return Status;
}

DWORD CFTPHelper::ParseFtpFeature(ASYNC_REQUEST_ENTRY *pAsyncRequest)
{
    DWORD  Features = 0;
    LPCSTR pszFeature;

    pszFeature = pAsyncRequest->ReplyText;
    for (;;)
    {
        pszFeature = NextLineA(pszFeature);
        if (pszFeature == NULL || *pszFeature == 0)
            break;

        while (*pszFeature == ' ')
            ++pszFeature;

        switch (CHAR_UPPER4(*(PDWORD)pszFeature))
        {
            case TAG4('OPTS'):
                if (StringA::Find(pszFeature, -1, "UTF8", NULL) != NULL)
                    Features |= FEATURE_UTF8;
                break;

            case TAG4('MLST'):
                Features |= FEATURE_MLST;
                break;

            case TAG4('MLSD'):
                Features |= FEATURE_MLSD;
                break;

            case TAG4('REST'):
                Features |= FEATURE_RESET;
                break;
        }
    }

    pAsyncRequest->RequestData.Login.FtpFeatures = Features;
    return Features;
}

WORD CFTPHelper::GetDataConnectPort(LPCSTR pszReplyText, DWORD Length)
{
    DWORD  Port;
    LPCSTR pszPort;

    // 227 Entering Passive Mode (127,0,0,1,173,167)

    Port = -1;
    LOOP_ONCE()
    {
        if (Length <= 4)
            break;

        --Length;
        pszPort = pszReplyText + Length;
        while (*pszPort-- != ')' && --Length != 0);
        if (Length == 0)
            break;

        while (*pszPort-- != ',' && --Length != 0);
        if (Length == 0)
            break;

        Port = StringToInt32A(pszPort + 2);
        while (*pszPort-- != ',' && --Length != 0);
        if (Length == 0)
        {
            Port = -1;
            break;
        }

        Port = StringToInt32A(pszPort + 2) | (Port << 8);
    }

    return (WORD)Port;
}

BOOL GetModifiedTime(LPCWSTR pszTime, PSYSTEMTIME pModifiedTime)
{
    DWORD *pLength, FieldLength[] = { 4, 2, 2, 2, 2, 2 };
    PWORD *pValue;
    PWORD Value[] =
    {
        &pModifiedTime->wYear,
        &pModifiedTime->wMonth,
        &pModifiedTime->wDay,
        &pModifiedTime->wHour,
        &pModifiedTime->wMinute,
        &pModifiedTime->wSecond
    };

    ZeroMemory(pModifiedTime, sizeof(*pModifiedTime));
    pValue = Value;
    pLength = FieldLength;
    for (DWORD i = countof(FieldLength); i; --i)
    {
        for (DWORD i = *pLength; i; --i)
        {
            if (*pszTime == ';' || *pszTime == 0 || !IN_RANGE('0', *pszTime, '9'))
                return FALSE;

            **pValue = **pValue * 10 + *pszTime - '0';
            ++pszTime;
        }

        ++pLength;
        ++pValue;
    }

    return TRUE;
}

LONG
CFTPHelper::
UpdateDirectoryInfo(
    DIRECTORY_INFO *pDirectoryInfo,
    LPCWSTR         pszDirectoryInfo,
    DWORD           Length
)
{
    SIZE_T FileCount;
    LPCWSTR pszEntryInfo, pszNextEntry, pszEnd;
    DIRECTORY_INFO *pInfo;

    if (pDirectoryInfo == NULL)
        return FTPHLP_ERROR_INVALID_PARAMETER;

    pDirectoryInfo->Free();
    pDirectoryInfo->SetAttribute(FILE_ATTRIBUTE_DIRECTORY);

    FileCount = 0;
    pszEntryInfo = pszDirectoryInfo;
    pszEnd = pszDirectoryInfo + Length;
    while (pszEntryInfo != NULL && *pszEntryInfo != 0)
    {
        pszEntryInfo = NextLineW(pszEntryInfo, pszEnd - pszEntryInfo);
        ++FileCount;
    }

    if (FileCount == 0)
        return FTPHLP_ERROR_INVALID_PARAMETER;

    pDirectoryInfo->pFiles = new DIRECTORY_INFO[FileCount];
    if (pDirectoryInfo->pFiles == NULL)
        return FTPHLP_ERROR_OUT_OF_MEMORY;

    ++FileCount;
    pDirectoryInfo->bCached   = TRUE;
    pDirectoryInfo->FileCount = 0;
    pInfo = pDirectoryInfo->pFiles;
    pszEntryInfo = pszDirectoryInfo;
    while (--FileCount && pszEntryInfo != NULL && *pszEntryInfo != 0)
    {
        pInfo->pParent = pDirectoryInfo;
        pszNextEntry = NextLineW(pszEntryInfo, pszEnd - pszEntryInfo);
        for (;;)
        {
            ULONG64    FileType;
            SYSTEMTIME ModifiedTime;

            switch (CHAR_UPPER4W(*(PULONG64)pszEntryInfo))
            {
                case TAG4W('TYPE'):
                    if (pszEntryInfo[4] != '=')
                        break;

                    pszEntryInfo += 5;
                    FileType = CHAR_UPPER4W(*(PULONG64)pszEntryInfo);
                    if (FileType == TAG4W('FILE'))
                    {
                        pInfo->SetAttribute(FILE_ATTRIBUTE_NORMAL);
                    }
                    else if ((FileType & 0x0000FFFFFFFFFFFF) == TAG3W('DIR'))
                    {
                        pInfo->SetAttribute(FILE_ATTRIBUTE_DIRECTORY);
                    }
                    else
                    {
                        goto L_INVALID_FILE_TYPE;
                    }
                    break;

                case TAG4W('SIZE'):
                    if (pszEntryInfo[4] != '=')
                        break;

                    pszEntryInfo += 5;
                    pInfo->FileSize.QuadPart = StringToInt64W(pszEntryInfo);
                    break;

                case TAG4W('MODI'):
                    if (CHAR_UPPER2W(*(PDWORD)&pszEntryInfo[4]) != TAG2W('FY') || pszEntryInfo[6] != '=')
                        break;

                    pszEntryInfo += 7;
                    if (GetModifiedTime(pszEntryInfo, &ModifiedTime))
                    {
                        SystemTimeToFileTime(&ModifiedTime, &pInfo->LastWriteTime);
                    }
                    else
                    {
                        pInfo->LastWriteTime.dwLowDateTime  = 0;
                        pInfo->LastWriteTime.dwHighDateTime = 0;
                    }
                    break;

                default:
                    if (*pszEntryInfo != ' ')
                        break;

                    Length = 0;
                    ++pszEntryInfo;
                    while (//*pszEntryInfo != ';'  &&
                           *pszEntryInfo != '\r' &&
                           *pszEntryInfo != '\n' &&
                           *pszEntryInfo != 0)
                    {
                        ++pszEntryInfo;
                        ++Length;
                    }

#if defined(UNICODE)
                    pInfo->Name.CopyFrom(pszEntryInfo - Length, Length);
#else
#endif
                    break;
            }

            while (*pszEntryInfo != ';' && *pszEntryInfo != 0 && *pszEntryInfo != '\n')
                ++pszEntryInfo;

            if (*pszEntryInfo == 0 || *pszEntryInfo == '\n')
                break;

            ++pszEntryInfo;
        }

        ++pInfo;
        ++pDirectoryInfo->FileCount;
L_INVALID_FILE_TYPE:
        pszEntryInfo = pszNextEntry;
    }

    return FTPHLP_ERROR_SUCCESS;
}

// Type=file;Size=70109;Modify=2011-02-27@13:53:51.217; 选课.mht\r\n
// Type=dir;Modify=20110217133501.461; 项目实践_III\r\n

LONG CFTPHelper::GetDirectoryFullPath(DIRECTORY_INFO *pDir, String &FullPath)
{
    LONG Status;
    if (pDir->pParent != NULL)
    {
        Status = GetDirectoryFullPath(pDir->pParent, FullPath);
        if (FTPHLP_FAILED(Status))
            return Status;
    }

    if (!FullPath.IsEmpty() && FullPath[FullPath.GetLength() - 1] != '/')
        FullPath += '/';

    FullPath += pDir->Name;
    return FTPHLP_ERROR_SUCCESS;
}

LONG CFTPHelper::ClearDirectoryCache(DIRECTORY_INFO *pDir)
{
    DIRECTORY_INFO *p;

    pDir->bCached = FALSE;
    p = pDir->pFiles;
    if (p == NULL)
        return FTPHLP_ERROR_SUCCESS;

    for (SIZE_T FileCount = pDir->FileCount; FileCount; ++p, --FileCount)
    {
        if (!p->CheckAttribute(FILE_ATTRIBUTE_DIRECTORY))
            continue;
        p->bCached = FALSE;
        ClearDirectoryCache(p);
    }

    return FTPHLP_ERROR_SUCCESS;
}

LONG CFTPHelper::QueryDirectoryFiles(DIRECTORY_INFO *pDir)
{
    LONG Status;
    DIRECTORY_INFO *p;

    p = pDir->pFiles;
    if (p == NULL)
    {
        Status = GetDirectoryInfoInternal(pDir, NULL, TRUE, 0, 0, NULL, TRUE);
        return Status;
    }

    for (SIZE_T FileCount = pDir->FileCount; FileCount; ++p, --FileCount)
    {
        if (!p->CheckAttribute(FILE_ATTRIBUTE_DIRECTORY))
            continue;

        if (!p->bCached)
        {
            Status = GetDirectoryInfoInternal(p, NULL, TRUE, 0, 0, NULL, TRUE);
            if (FTPHLP_FAILED(Status))
                return Status;
        }

        Status = QueryDirectoryFiles(p);
        if (FTPHLP_FAILED(Status))
            return Status;
    }

    return FTPHLP_ERROR_SUCCESS;
}

LONG_PTR
CFTPHelper::
CallRequestCompletionRoutine(
    ASYNC_REQUEST_ENTRY *pAsyncRequest,
    LONG  ReplyCode,
    DWORD BytesTransfered
)
{
    if (pAsyncRequest->pfCompletionRoutine == NULL)
        return FTPHLP_ERROR_INVALID_PARAMETER;

    return pAsyncRequest->pfCompletionRoutine(
                ReplyCode,
                BytesTransfered,
                m_pCurrentReq->Flags,
                m_pCurrentReq->CompletionKey,
                m_pCurrentReq->RoutineParam);
}

LONG CFTPHelper::CallDownloadStatusCallback(DOWNLOAD_REQUEST_ENTRY *pRequest)
{
    if (pRequest == NULL || pRequest->pfStatusCallback == NULL)
        return FTPHLP_ERROR_INVALID_PARAMETER;

    return pRequest->pfStatusCallback(
                pRequest,
                pRequest->Key,
                pRequest->CallerParam);
}

ASYNC_REQUEST_ENTRY* CFTPHelper::AllocAsyncRequest(DWORD EntrySize /* = sizeof */)
{
    UNREFERENCED_PARAMETER(EntrySize);
    return new ASYNC_REQUEST_ENTRY;
}

BOOL CFTPHelper::FreeAsyncRequest(ASYNC_REQUEST_ENTRY *pAsyncReqEntry)
{
    if (pAsyncReqEntry == NULL)
        return FALSE;

    switch (pAsyncReqEntry->Type)
    {
        case ASYNC_REQ_CONNECT:
            delete pAsyncReqEntry->RequestData.Connect.Address;
            break;

        case ASYNC_REQ_LOGIN:
            delete pAsyncReqEntry->RequestData.Login.UserName;
            delete pAsyncReqEntry->RequestData.Login.Password;
            break;

        case ASYNC_REQ_DOWNLOAD:
            delete pAsyncReqEntry->RequestData.Download.PathLocal;
            break;
    }

    delete pAsyncReqEntry;
    return TRUE;
}

LONG CFTPHelper::PostAsyncRequest(ASYNC_REQUEST_ENTRY *pAsyncRequest, BOOL bInsertFirst /* = FALSE */)
{
    SIZE_T Pos;
    ASYNC_REQUEST_ENTRY *pReqToPost;

    if (pAsyncRequest->cbSize < sizeof(*pAsyncRequest))
        return FTPHLP_ERROR_INVALID_PARAMETER;

    pReqToPost = AllocAsyncRequest(pAsyncRequest->cbSize);
    if (pReqToPost == NULL)
        return FTPHLP_ERROR_OUT_OF_MEMORY;

    *pReqToPost = *pAsyncRequest;
    pReqToPost->SetStatus(ASYNC_STATUS_READY);

    Pos = bInsertFirst ? m_AsyncQueue.AddHead(pReqToPost) : m_AsyncQueue.AddTail(pReqToPost);
    if (Pos == m_AsyncQueue.InvalidPosition)
    {
        FreeAsyncRequest(pReqToPost);
        return FTPHLP_ERROR_POST_ASYNC_REQUEST;
    }

    return FTPHLP_ERROR_PENDING;
}

BOOL CFTPHelper::IsRequestTimeout(ASYNC_REQUEST_ENTRY *pAsyncRequest)
{
    if (pAsyncRequest->BeginTimeStamp == INFINITE || m_msTimeout == INFINITE)
        return FALSE;

    return GetTickCount() - pAsyncRequest->BeginTimeStamp > m_msTimeout;
}

LONG CFTPHelper::SendFTPCommandByID(FTP_COMMAND Command, LPCSTR pszParameter)
{
    return SendFTPCommandInternal(m_SockCtrl, GetFTPCommandByID(Command), pszParameter);
}

LONG CFTPHelper::SendDownloadCommandByID(SOCKET Socket, FTP_COMMAND Command, LPCSTR pszParameter)
{
    return SendDownloadCommand(Socket, GetFTPCommandByID(Command), pszParameter);
}

LONG
CFTPHelper::
SendDownloadCommand(
    SOCKET Socket,
    LPCSTR pszCommand,
    LPCSTR pszParameter /* = NULL */
)
{
    return SendFTPCommandInternal(Socket, pszCommand, pszParameter, TRUE);
}

LONG
CFTPHelper::
SendFTPCommandInternal(
    SOCKET Socket,
    LPCSTR pszCommand,
    LPCSTR pszParameter /* = NULL */,
    BOOL   bIsDownloadThread /* = FALSE */
)
{
    LONG   Status;
    DWORD  BytesSent;
    WSABUF WSABuffer;
    StringA CmdBuffer, *pCmdBuffer;

    if (pszCommand == NULL)
        return FTPHLP_ERROR_INVALID_PARAMETER;

    if (!bIsDownloadThread)
    {
        pCmdBuffer = &m_FtpCmdBuffer;
        if (pCmdBuffer->GetLength() != 0)
            return FTPHLP_ERROR_SENDCMD_LAST_NOT_COMPLETE;
    }
    else
    {
        pCmdBuffer = &CmdBuffer;
    }

    *pCmdBuffer = pszCommand;
    if (pszParameter != 0)
    {
        pCmdBuffer->RemoveLineFeed();
        *pCmdBuffer += " ";
        *pCmdBuffer += pszParameter;
    }
    pCmdBuffer->RemoveLineFeed();
    *pCmdBuffer += "\r\n";

    WSABuffer.buf = pCmdBuffer->GetBuffer();
    WSABuffer.len = pCmdBuffer->GetLength();

    ShowLog(_T("[S] %S"), CHAR_UPPER4(*(PDWORD)pszCommand) == TAG4('PASS') ? pszCommand : WSABuffer.buf);

    Status = WSASend(Socket, &WSABuffer, 1, &BytesSent, 0, NULL, NULL);
    if (Status == NO_ERROR)
    {
        if (!bIsDownloadThread)
            pCmdBuffer->Empty();
        return FTPHLP_ERROR_SUCCESS;
    }

    Status = WSAGetLastError();
    if (Status != WSAEWOULDBLOCK)
    {
        return FTPHLP_ERROR_UNKNOWN;
    }

    return FTPHLP_ERROR_PENDING;
}

LONG
CFTPHelper::
ChangeDirectoryInternal(
    DIRECTORY_INFO     *pDirInfo,
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine,
    BOOL                bInsertFirst
)
{
    if (!pDirInfo->CheckAttribute(FILE_ATTRIBUTE_DIRECTORY))
        return FTPHLP_ERROR_NOT_DIRECTORY;

    ASYNC_REQUEST_ENTRY AsyncChangePath(ASYNC_REQ_CHANGEPATH, CompletionKey, RoutineParam, pfCompletionRoutine);
    AsyncChangePath.RequestData.ChangePath.pNewCurDir = pDirInfo;
    return PostAsyncRequest(&AsyncChangePath, bInsertFirst);
}

LONG CFTPHelper::PostFTPCommand(FTP_COMMAND Command, LPCSTR pszParameter)
{
    FTPHLP_RETURN_IF_NOT_INIT();
    return SendFTPCommandByID(Command, pszParameter);
}

LONG CFTPHelper::PostUserCommand(LPCSTR pszCommand)
{
    FTPHLP_RETURN_IF_NOT_INIT();
    return SendFTPCommandInternal(m_SockCtrl, pszCommand, NULL);
}

BOOL CFTPHelper::IsDownloadListEmpty()
{
    return m_DownloadQueue.IsEmpty();
}

LONG
CFTPHelper::
Connect(
    LPCSTR              pszAddress,
    DWORD               Port,
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine
)
{
    FTPHLP_RETURN_IF_NOT_INIT();
    FTP_METHOD_ENTER();
    return ConnectInternal(pszAddress, Port, CompletionKey, RoutineParam, pfCompletionRoutine, FALSE);
}

LONG
CFTPHelper::
Disconnect(
    ULONG_PTR          CompletionKey,
    ULONG_PTR          RoutineParam,
    FCompletionRoutine pfCompletionRoutine
)
{
    FTPHLP_RETURN_IF_NOT_INIT();
    FTP_METHOD_ENTER();
    return DisconnectInternal(CompletionKey, RoutineParam, pfCompletionRoutine, FALSE);
}

LONG
CFTPHelper::
Login(
    LPCSTR             pszUserName,
    LPCSTR             pszPassword,
    ULONG_PTR          CompletionKey,
    ULONG_PTR          RoutineParam,
    FCompletionRoutine pfCompletionRoutine
)
{
    FTPHLP_RETURN_IF_NOT_INIT();
    FTP_METHOD_ENTER();
    return LoginInternal(pszUserName, pszPassword, CompletionKey, RoutineParam, pfCompletionRoutine, FALSE);
}

LONG
CFTPHelper::
Logout(
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine
)
{
    FTPHLP_RETURN_IF_NOT_INIT();
    FTP_METHOD_ENTER();
    return LogoutInternal(CompletionKey, RoutineParam, pfCompletionRoutine, FALSE);
}

LONG
CFTPHelper::
Refresh(
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine
)
{
    FTP_METHOD_ENTER();
    return GetCurrentDirectoryInfo(NULL, TRUE, CompletionKey, RoutineParam, pfCompletionRoutine);
}

LONG
CFTPHelper::
GetCurrentDirectoryInfo(
    DIRECTORY_INFO    **pDirectoryInfo,
    BOOL                bForceRefresh,
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine
)
{
    return GetDirectoryInfo(m_pCurrentDir, pDirectoryInfo, bForceRefresh, CompletionKey, RoutineParam, pfCompletionRoutine);
}

LONG
CFTPHelper::
GetDirectoryInfo(
    DIRECTORY_INFO     *pDirectoryToQuery,
    DIRECTORY_INFO    **pDirectoryInfo,
    BOOL                bForceRefresh,
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine
)
{
    FTPHLP_RETURN_IF_NOT_INIT();
    FTP_METHOD_ENTER();
    return GetDirectoryInfoInternal(pDirectoryToQuery, pDirectoryInfo, bForceRefresh, CompletionKey, RoutineParam, pfCompletionRoutine, FALSE);
}

LONG
CFTPHelper::
ChangeDirectory(
    SIZE_T              PathIndex,
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine
)
{
    FTPHLP_RETURN_IF_NOT_INIT();
    FTP_METHOD_ENTER();

    if (m_pCurrentDir == NULL || m_pCurrentDir->pFiles == NULL)
        return FTPHLP_ERROR_UNKNOWN;

    if (PathIndex == m_pCurrentDir->PARENT_DIRECTORY_INDEX)
    {
        if (m_pCurrentDir->pParent == NULL)
            return FTPHLP_ERROR_TOP_DIRECTORY;

        m_pCurrentDir = m_pCurrentDir->pParent;
        return FTPHLP_ERROR_SUCCESS;
    }

    if (PathIndex > m_pCurrentDir->FileCount)
        return FTPHLP_ERROR_INVALID_PARAMETER;

    return ChangeDirectoryInternal(
                &m_pCurrentDir->pFiles[PathIndex],
                CompletionKey,
                RoutineParam,
                pfCompletionRoutine,
                FALSE);
}

LONG
CFTPHelper::
DownloadFile(
    SIZE_T                  PathIndex,
    LPCTSTR                 pszSavePath,
    ULONG_PTR               Key,
    ULONG_PTR               Param,
    FDownloadStatusCallback pfCallback
)
{
    FTPHLP_RETURN_IF_NOT_INIT();
    FTP_METHOD_ENTER();

    DIRECTORY_INFO *pDirInfo;

    if (m_pCurrentDir == NULL || m_pCurrentDir->pFiles == NULL)
        return FTPHLP_ERROR_UNKNOWN;

    if (PathIndex == m_pCurrentDir->PARENT_DIRECTORY_INDEX && m_pCurrentDir->pParent != NULL)
        pDirInfo = m_pCurrentDir->pParent;
    else if (PathIndex > m_pCurrentDir->FileCount)
        return FTPHLP_ERROR_INVALID_PARAMETER;

    pDirInfo = &m_pCurrentDir->pFiles[PathIndex];
/*
    if (pDirInfo->CheckAttribute(FILE_ATTRIBUTE_DIRECTORY) && pDirInfo->pFiles == NULL)
    {
        LONG Status;
        Status = GetDirectoryInfo(pDirInfo, NULL, TRUE, (ULONG_PTR)&Status, (ULONG_PTR)this, CompletionRoutineInternal);
        if (Status != FTPHLP_ERROR_PENDING && FTPHLP_FAILED(Status))
            return Status;
        WaitAsyncWaitEvent(INFINITE);
        if (FTPHLP_FAILED(Status))
            return Status;
    }
*/
    return DownloadFileInternal(pDirInfo, pszSavePath, Key, Param, pfCallback, FALSE);
}

LONG
CFTPHelper::
ConnectInternal(
    LPCSTR              pszAddress,
    DWORD               Port,
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine,
    BOOL                bInsertFirst
)
{
    ASYNC_REQUEST_ENTRY AsyncConnect(ASYNC_REQ_CONNECT, CompletionKey, RoutineParam, pfCompletionRoutine, 0);
    AsyncConnect.RequestData.Connect.Port    = Port;
    AsyncConnect.RequestData.Connect.Address = new StringA(pszAddress);
    return PostAsyncRequest(&AsyncConnect, bInsertFirst);
}

LONG
CFTPHelper::
LoginInternal(
    LPCSTR              pszUserName,
    LPCSTR              pszPassword,
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine,
    BOOL                bInsertFirst
)
{
    ASYNC_REQUEST_ENTRY AsyncLogin(ASYNC_REQ_LOGIN, CompletionKey, RoutineParam, pfCompletionRoutine, 0);
    AsyncLogin.RequestData.Login.FtpFeatures = 0;
    AsyncLogin.RequestData.Login.UserName = new StringA(pszUserName);
    AsyncLogin.RequestData.Login.Password = new StringA(pszPassword);
    return PostAsyncRequest(&AsyncLogin, bInsertFirst);
}

LONG
CFTPHelper::
LogoutInternal(
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine,
    BOOL                bInsertFirst
)
{
    ASYNC_REQUEST_ENTRY AsyncLogout(ASYNC_REQ_LOGOUT, CompletionKey, RoutineParam, pfCompletionRoutine, 0);
    return PostAsyncRequest(&AsyncLogout, bInsertFirst);
}

LONG
CFTPHelper::
DisconnectInternal(
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine,
    BOOL                bInsertFirst
)
{
    ASYNC_REQUEST_ENTRY AsyncLogout(ASYNC_REQ_DISCONNECT, CompletionKey, RoutineParam, pfCompletionRoutine, 0);
    return PostAsyncRequest(&AsyncLogout, bInsertFirst);
}

LONG
CFTPHelper::
GetDirectoryInfoInternal(
    DIRECTORY_INFO     *pDirectoryToQuery,
    DIRECTORY_INFO    **pDirectoryInfo,
    BOOL                bForceRefresh,
    ULONG_PTR           CompletionKey,
    ULONG_PTR           RoutineParam,
    FCompletionRoutine  pfCompletionRoutine,
    BOOL                bInsertFirst
)
{
    if (pDirectoryToQuery == NULL)
        return FTPHLP_ERROR_INVALID_PARAMETER;

    if (pDirectoryInfo != NULL)
        *pDirectoryInfo = NULL;

    if (!bForceRefresh && pDirectoryToQuery->bCached)
    {
        if (pDirectoryInfo != NULL)
            *pDirectoryInfo = pDirectoryToQuery;
        return FTPHLP_ERROR_SUCCESS;
    }

    ASYNC_REQUEST_ENTRY AsyncGetDirInfo(ASYNC_REQ_GETDIRINFO, CompletionKey, RoutineParam, pfCompletionRoutine);
    AsyncGetDirInfo.RequestData.GetDirInfo.bForceRefresh = bForceRefresh;
    AsyncGetDirInfo.RequestData.GetDirInfo.pDirInfo      = pDirectoryInfo;
    AsyncGetDirInfo.RequestData.GetDirInfo.pDirToQuery   = pDirectoryToQuery;
    AsyncGetDirInfo.RequestData.GetDirInfo.Flags         = 0;
    AsyncGetDirInfo.RequestData.GetDirInfo.PrevType      = ASYNC_REQ_NULL;
    return PostAsyncRequest(&AsyncGetDirInfo, bInsertFirst);
}

LONG
CFTPHelper::
DownloadFileInternal(
    DIRECTORY_INFO         *pDirInfo,
    LPCTSTR                 pszSavePath,
    ULONG_PTR               Key,
    ULONG_PTR               Param,
    FDownloadStatusCallback pfCallback,
    BOOL                    bInsertFirst
)
{
    if (pszSavePath == NULL || pDirInfo == NULL)
        return FTPHLP_ERROR_INVALID_PARAMETER;

    ASYNC_REQUEST_ENTRY AsyncGetDirInfo(ASYNC_REQ_DOWNLOAD, 0, 0, NULL);
    AsyncGetDirInfo.RequestData.Download.pServerPath        = pDirInfo;
    AsyncGetDirInfo.RequestData.Download.PathLocal          = new String(pszSavePath);
    AsyncGetDirInfo.RequestData.Download.CallerParam        = Param;
    AsyncGetDirInfo.RequestData.Download.Key                = Key;
    AsyncGetDirInfo.RequestData.Download.pfStatusCallback   = (FARPROC)pfCallback;
    return PostAsyncRequest(&AsyncGetDirInfo, bInsertFirst);
}

LONG CFTPHelper::FreeDirectoryInfo(DIRECTORY_INFO *pDirectoryInfo)
{
    if (pDirectoryInfo == NULL)
        return FTPHLP_ERROR_INVALID_PARAMETER;

    delete pDirectoryInfo;
    return FTPHLP_ERROR_SUCCESS;
}

VOID CFTPHelper::OnConnect(SOCKET Socket, DWORD ErrorCode)
{
    WriteLog(_T("FD_CONNECT: SOCKET = %08X, ErrorCode = %08X\n"), Socket, ErrorCode);

    if (ErrorCode != NO_ERROR)
    {
        if (m_pCurrentReq != NULL)
            m_pCurrentReq->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_CONNECT, ErrorCode);
        return;
    }

    if (m_pCurrentReq->Type != ASYNC_REQ_LOGIN &&
        m_pCurrentReq->Type != ASYNC_REQ_CONNECT)
    {
        m_pCurrentReq->SetFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY);
    }
}

VOID CFTPHelper::OnRead(SOCKET Socket, DWORD ErrorCode)
{
    DWORD  BytesRecv, Flags;
    CHAR   Buffer[1024];
    WSABUF WSABuffer;
    StringA *pReplyText;

    pReplyText = NULL;

    if (m_pCurrentReq == NULL)
        m_FtpReplyText.Empty();
    else if (!m_pCurrentReq->CheckFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY))
    {
        if (Socket == m_SockData)
            pReplyText = &m_pCurrentReq->DataReplyText;
        else
            pReplyText = &m_FtpReplyText;
    }

    FTP_METHOD_ENTER();

    if (ErrorCode != NO_ERROR)
        return;

    Buffer[0] = 0;
    WSABuffer.buf = Buffer;
    WSABuffer.len = sizeof(Buffer) - sizeof(Buffer[0]);
    for (;;)
    {
        Flags = 0;
        if (WSARecv(Socket, &WSABuffer, 1, &BytesRecv, &Flags, NULL, NULL) != NO_ERROR)
            break;
        if (BytesRecv == 0)
            break;

        WSABuffer.buf[BytesRecv] = 0;
        if (pReplyText != NULL)
            pReplyText->Concatenate(WSABuffer.buf, BytesRecv);

        if (Socket != m_SockData)
#if defined(UNICODE)
            ShowLog(_T("[R] %S"), WSABuffer.buf);
#else
            ShowLog(_T("[R] %s"), WSABuffer.buf);
#endif
    }

#if 0
    LPCSTR pszNextReplyText;

    if (pReplyText == NULL)
        return;

    pszNextReplyText = IsRecvAllReplyText(*pReplyText, pReplyText->GetLength());
    if (pszNextReplyText == NULL)
        return;

    m_pCurrentReq->ReplyText = m_FtpReplyText;
    m_pCurrentReq->ReplyCode = GetServerReplyCode(m_FtpReplyText, m_FtpReplyText.GetLength());
    if (pszNextReplyText[0] != 0)
    {
        m_pCurrentReq->SetFlags(FTPHLP_ASYNC_REQ_FLAG_MULTI_LINE_REPLY);
        m_FtpReplyText = pszNextReplyText;
    }
    else
    {
        m_FtpReplyText.Empty();
    }

    m_pCurrentReq->SetFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY);
#endif
}

VOID CFTPHelper::OnWrite(SOCKET Socket, DWORD ErrorCode)
{
    LONG   FtpStatus;
    DWORD  BytesSent;
    WSABUF WSABuffer;

    FTP_METHOD_ENTER();

    if (m_FtpCmdBuffer.GetLength() == 0)
    {
//        if (m_pCurrentReq != NULL && m_pCurrentReq->Type != ASYNC_REQ_CONNECT)
//            m_pCurrentReq->SetFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY);
        return;
    }

    WSABuffer.buf = m_FtpCmdBuffer;
    WSABuffer.len = m_FtpCmdBuffer.GetBufferSize();
    ErrorCode = WSASend(Socket, &WSABuffer, 1, &BytesSent, 0, NULL, NULL);
    if (ErrorCode == WSAEWOULDBLOCK)
        return;

    if (m_pCurrentReq == NULL)
        return;

    FtpStatus = GetDefFtpStatusFromRequest(m_pCurrentReq);
    m_pCurrentReq->ErrorCode = ErrorCode;
    if (ErrorCode != NO_ERROR)
    {
        m_pCurrentReq->SetStatus(ASYNC_STATUS_FAILED, FtpStatus, ErrorCode);
        return;
    }

    if (ErrorCode != NO_ERROR)
    {
        m_pCurrentReq->SetStatus(ASYNC_STATUS_FAILED, FtpStatus, ErrorCode);
        return;
    }
}

VOID CFTPHelper::OnClose(SOCKET Socket, DWORD ErrorCode)
{
    FTP_METHOD_ENTER();

    UNREFERENCED_PARAMETER(Socket);
    UNREFERENCED_PARAMETER(ErrorCode);

    if (m_pCurrentReq == NULL && Socket == m_SockCtrl)
    {
        closesocket(Socket);
        m_SockCtrl = NULL;
        ShowLog(_T("Connection has been closed by server"));
    }
}

SOCKET CFTPHelper::CreateSocket(LPSOCKADDR_IN pSockAddrIn, BOOL bDownloadThread /* = FALSE */)
{
    BOOL   bKeepAlive;
    LONG   Result;
    SOCKET Socket;

    Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (Socket == INVALID_SOCKET)
        return Socket;

    bKeepAlive = TRUE;
    setsockopt(Socket, SOL_SOCKET, SO_KEEPALIVE, (PCHAR)&bKeepAlive, sizeof(bKeepAlive));

    Result = NO_ERROR;
    LOOP_ONCE
    {
        if (bDownloadThread)
        {
            bKeepAlive = TRUE;
            Result = ioctlsocket(Socket, FIONBIO, (PULONG)&bKeepAlive);
        }
        else
        {
            Result = WSAAsyncSelect(
                    Socket,
                    m_hWnd,
                    WM_SOCKET_EVENT_CONTROL,
                    FD_CONNECT|FD_WRITE|FD_READ|FD_CLOSE);
        }
        if (Result != NO_ERROR)
            break;

        Result = WSAConnect(Socket, (PSOCKADDR)pSockAddrIn, sizeof(*pSockAddrIn), NULL, NULL, NULL, NULL);
        if (Result == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
            Result = NO_ERROR;
    }

    if (Result != NO_ERROR)
    {
        closesocket(Socket);
        Socket = INVALID_SOCKET;
    }

    return Socket;
}

VOID CFTPHelper::OnGetHost(HANDLE hAsync, DWORD ErrorCode, DWORD BufferLength)
{
    LONG        FtpStatus;

    FTP_METHOD_ENTER();

    if (m_pCurrentReq == NULL || m_pCurrentReq->Type != ASYNC_REQ_CONNECT)
        return;

    WriteLog(
        _T("MSG = %s\n")
        _T("HANDLE = %08X, Error = %08X, BufLen = %08X\n"),
        _T("WM_SOCKET_ASYNC_GET_HOST"),
        hAsync,
        ErrorCode,
        BufferLength);

    FtpStatus = GetDefFtpStatusFromRequest(m_pCurrentReq);
    if (ErrorCode != NO_ERROR)
    {
        m_pCurrentReq->SetStatus(ASYNC_STATUS_FAILED, FtpStatus, ErrorCode);
        return;
    }

    CopyMemory(
        &m_SockAddrIn.sin_addr,
        m_pCurrentReq->RequestData.Connect.HostEntry.Entry.h_addr_list[0],
        m_pCurrentReq->RequestData.Connect.HostEntry.Entry.h_length);
    ZeroMemory(&m_SockAddrIn.sin_zero, sizeof(m_SockAddrIn.sin_zero));
    m_SockAddrIn.sin_family = m_pCurrentReq->RequestData.Connect.HostEntry.Entry.h_addrtype;
    m_SockAddrIn.sin_port = UInt16BE(m_pCurrentReq->RequestData.Connect.Port);

    m_SockCtrl = CreateSocket(&m_SockAddrIn);
    if (m_SockCtrl == INVALID_SOCKET)
    {
        m_pCurrentReq->SetStatus(ASYNC_STATUS_FAILED, FtpStatus, WSAGetLastError());
        return;
    }

    m_pCurrentReq->SetStatus(ASYNC_STATUS_PROCESSING);
}

ForceInline LRESULT CFTPHelper::WndProcInternal(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT Result = NO_ERROR;

    FTP_METHOD_ENTER();

    switch (Msg)
    {
        default:
            return DefWindowProc(hWnd, Msg, wParam, lParam);

        case WM_SOCKET_EVENT_CONTROL:
            switch (WSAGETSELECTEVENT(lParam))
            {
                HANDLE_WM_SOCKET(FD_CONNECT,    OnConnect);
                HANDLE_WM_SOCKET(FD_READ,       OnRead);
                HANDLE_WM_SOCKET(FD_WRITE,      OnWrite);
                HANDLE_WM_SOCKET(FD_CLOSE,      OnClose);
            }
            break;

        case WM_SOCKET_ASYNC_GET_HOST:
            OnGetHost((HANDLE)wParam, WSAGETASYNCERROR(lParam), WSAGETASYNCBUFLEN(lParam));
            break;
    }

    return Result;
}

LRESULT WINAPI CFTPHelper::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
//    CFTPHelper *pThis = (CFTPHelper *)GetProp(hWnd, FTP_HELPER_CLASS_NAME);
    CFTPHelper *pThis = (CFTPHelper *)GetWindowLongPtr(hWnd, GWL_USERDATA);
    return pThis == NULL ? DefWindowProc(hWnd, Msg, wParam, lParam) : pThis->WndProcInternal(hWnd, Msg, wParam, lParam);
}

ForceInline DWORD CFTPHelper::WindowThreadWorker()
{
    LONG Status;
    MSG  Message;

    FTP_METHOD_ENTER();

    PeekMessage(&Message, NULL, WM_USER, WM_USER, PM_NOREMOVE);

    LPCTSTR lpClassName = FTP_HELPER_CLASS_NAME, lpWindowName = lpClassName;
    WNDCLASSEX wndclsex =
    {
        sizeof(wndclsex),
        0,
        this->WndProc,
        0,
        0,
        GetModuleHandle(NULL),
        NULL,
        NULL,
        NULL,
        lpClassName,
        lpWindowName,
        NULL
    };

    if (RegisterClassEx(&wndclsex) == NULL && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return FTPHLP_ERROR_WND_INITIALIZE_FAILED;

    m_hWnd = CreateWindowEx(
                 0,
                 lpClassName,
                 lpWindowName,
                 0,
                 0, 0, 0, 0,
                 NULL,
                 NULL,
                 NULL,
                 NULL);
    if (m_hWnd == NULL)
        return FTPHLP_ERROR_WND_INITIALIZE_FAILED;

    SetWindowLongPtr(m_hWnd, GWL_USERDATA, (LONG_PTR)this);
    if (GetLastError() != NO_ERROR)
//    if (!SetProp(m_hWnd, FTP_HELPER_CLASS_NAME, (HANDLE)this))
    {
        DestroyWindow(m_hWnd);
        m_hWnd = NULL;
        return FTPHLP_ERROR_WND_INITIALIZE_FAILED;
    }

    SetAsyncWaitEvent();
    LOOP_ALWAYS()
    {
        BOOL Result;

        Result = PeekMessage(&Message, NULL, WM_SOCKET_FIRST + 1, WM_SOCKET_LAST - 1, PM_REMOVE);
        if (!Result)
        {
            Status = DispatchAsyncRequest();
            switch (Status)
            {
                case FTPHLP_ERROR_EMPTY_ASYNC_REQUEST:
                case FTPHLP_ERROR_PENDING:
                    SleepEx(10, FALSE);
                    break;
            }
        }
        else
        {
            if (Message.message == WM_SOCKET_FORCE_QUIT)
                break;

            DispatchMessage(&Message);
        }
    }

    DestroyWindow(m_hWnd);
    m_hWnd = NULL;

    return FTPHLP_ERROR_SUCCESS;
}

DWORD WINAPI CFTPHelper::WindowThread(LPVOID lpParam)
{
    CFTPHelper *pThis = (CFTPHelper *)lpParam;
    return pThis->WindowThreadWorker();
}

LONG CFTPHelper::DispatchAsyncRequest()
{
    LONG Status;

    if (m_pCurrentReq != NULL && m_pCurrentReq->ReqStatus == ASYNC_STATUS_WOULDDELETE)
    {
        CallRequestCompletionRoutine(m_pCurrentReq, m_pCurrentReq->FtpStatus, 0);
        FreeAsyncRequest(m_pCurrentReq);
        m_pCurrentReq = NULL;
        m_AsyncQueue.RemoveHead();
    }

    if (m_AsyncQueue.IsEmpty())
        return FTPHLP_ERROR_EMPTY_ASYNC_REQUEST;

    if (!m_AsyncQueue.GetHead(m_pCurrentReq))
        return FTPHLP_ERROR_PEEK_ASYCN_REQUEST;

    if (m_pCurrentReq == NULL)
        return FTPHLP_ERROR_INVALID_REQUEST;

    if (!m_FtpReplyText.IsEmpty())
    {
        LPCSTR pszNextReplyText;

        pszNextReplyText = IsRecvAllReplyText(m_FtpReplyText, m_FtpReplyText.GetLength());
        if (pszNextReplyText != NULL)
        {
            m_pCurrentReq->ReplyText = m_FtpReplyText;
            m_pCurrentReq->ReplyCode = GetServerReplyCode(m_FtpReplyText, m_FtpReplyText.GetLength());
            if (pszNextReplyText[0] != 0)
            {
//                m_pCurrentReq->SetFlags(FTPHLP_ASYNC_REQ_FLAG_MULTI_LINE_REPLY);
                m_FtpReplyText = pszNextReplyText;
            }
            else
            {
                m_FtpReplyText.Empty();
            }

            m_pCurrentReq->SetFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY);
        }
    }

    switch (m_pCurrentReq->Type)
    {
        default:
            Status = FTPHLP_ERROR_UNKNOWN_ASYNC_REQUEST_TYPE;
            m_pCurrentReq->SetStatus(ASYNC_STATUS_FAILED, Status, ERROR_INVALID_PARAMETER);
            break;

        HANDLE_ASYCN_REQUEST(Status, ASYNC_REQ_CONNECT,     OnAsyncConnect);
        HANDLE_ASYCN_REQUEST(Status, ASYNC_REQ_LOGIN,       OnAsyncLogin);
        HANDLE_ASYCN_REQUEST(Status, ASYNC_REQ_LOGOUT,      OnAsyncLogout);
        HANDLE_ASYCN_REQUEST(Status, ASYNC_REQ_DISCONNECT,  OnAsyncDisconnect);
        HANDLE_ASYCN_REQUEST(Status, ASYNC_REQ_GETDIRINFO,  OnAsyncGetDirInfo);
        HANDLE_ASYCN_REQUEST(Status, ASYNC_REQ_CHANGEPATH,  OnAsyncChangeDirectory);
        HANDLE_ASYCN_REQUEST(Status, ASYNC_REQ_DOWNLOAD,    OnAsyncDownload);
    }

    switch (m_pCurrentReq->ReqStatus)
    {
        case ASYNC_STATUS_FAILED:
        case ASYNC_STATUS_DONE:
            m_pCurrentReq->SetStatus(ASYNC_STATUS_WOULDDELETE, m_pCurrentReq->FtpStatus, m_pCurrentReq->ErrorCode);
            break;
/*
        default:
            if (m_pCurrentReq->CheckFlags(FTPHLP_ASYNC_REQ_FLAG_SOCKET_CLOSED) && 
                m_pCurrentReq->Type != ASYNC_REQ_LOGOUT &&
                m_pCurrentReq->Type != ASYNC_REQ_DISCONNECT)
            {
                m_pCurrentReq->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_SERVER_DISCONNECT);
            }
            break;
*/
    }

    return Status;
}

LONG CFTPHelper::OnAsyncConnect(ASYNC_REQUEST_ENTRY *pAsyncReqEntry)
{
    LONG   FtpStatus;
    HANDLE hAsync;

    FtpStatus = GetDefFtpStatusFromRequest(pAsyncReqEntry);
    if (pAsyncReqEntry->ReqStatus == ASYNC_STATUS_READY)
    {
        if (m_pRootDir != NULL)
        {
            FreeDirectoryInfo(m_pRootDir);
            m_pRootDir = NULL;
            m_pCurrentDir = NULL;
        }

        if (pAsyncReqEntry->ReqStatus == ASYNC_STATUS_PROCESSING)
            return FTPHLP_ERROR_SUCCESS;

        if (pAsyncReqEntry->ReqStatus != ASYNC_STATUS_READY)
            return FTPHLP_ERROR_INVALID_REQUEST;

        hAsync = WSAAsyncGetHostByName(
                    m_hWnd,
                    WM_SOCKET_ASYNC_GET_HOST,
                    *pAsyncReqEntry->RequestData.Connect.Address,
                    pAsyncReqEntry->RequestData.Connect.HostEntry.Buffer,
                    sizeof(pAsyncReqEntry->RequestData.Connect.HostEntry.Buffer));

        if (hAsync == NULL)
        {
            pAsyncReqEntry->SetStatus(
                ASYNC_STATUS_FAILED,
                FTPHLP_ERROR_ASYNCGETHOSTNAME,
                WSAGetLastError());
            return FTPHLP_ERROR_ASYNCGETHOSTNAME;
        }

        pAsyncReqEntry->ResetTimeStamp();
        pAsyncReqEntry->SetStatus(ASYNC_STATUS_PROCESSING);
    }
    else if (pAsyncReqEntry->CheckFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY))
    {
        pAsyncReqEntry->ResetTimeStamp();
        pAsyncReqEntry->RemoveFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY);
        if (pAsyncReqEntry->ReqStatus == ASYNC_STATUS_PROCESSING)
        {
            LONG Status, ErrorCode;

            if (pAsyncReqEntry->ReplyCode == REPLY_SERVICE_READY_FOR_USER)
            {
                Status    = ASYNC_STATUS_DONE;
                FtpStatus = FTPHLP_ERROR_SUCCESS;
                ErrorCode = NO_ERROR;
            }
            else
            {
                Status    = ASYNC_STATUS_FAILED;
                ErrorCode = pAsyncReqEntry->ErrorCode;
            }
            pAsyncReqEntry->SetStatus(Status, FtpStatus, ErrorCode);
        }
    }
    else if (IsRequestTimeout(pAsyncReqEntry))
    {
        pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_CONNECT, ERROR_TIMEOUT);
    }

    return FTPHLP_ERROR_PENDING;
}

LONG CFTPHelper::OnAsyncLogin(ASYNC_REQUEST_ENTRY *pAsyncReqEntry)
{
    LONG Status;

    if (m_SockCtrl == INVALID_SOCKET)
        return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_LOGIN);

    Status = FTPHLP_ERROR_PENDING;
    if (pAsyncReqEntry->ReqStatus == ASYNC_STATUS_READY)
    {
        m_CodePage = CP_ACP;
        pAsyncReqEntry->ResetTimeStamp();
        Status = SendFTPCommandByID(CMD_UserName, *pAsyncReqEntry->RequestData.Login.UserName);
        if (Status != FTPHLP_ERROR_PENDING && FTPHLP_FAILED(Status))
        {
            pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_LOGIN, WSAGetLastError());
        }
        else
        {
            pAsyncReqEntry->SetStatus(ASYNC_STATUS_PROCESSING);
        }
    }
    else if (pAsyncReqEntry->CheckFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY))
    {
        pAsyncReqEntry->ResetTimeStamp();
        pAsyncReqEntry->RemoveFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY);
        if (pAsyncReqEntry->ReqStatus == ASYNC_STATUS_PROCESSING)
        {
            LONG ReplyCode;
            REQUEST_DATA_GETDIRINFO *pReqData;

            ReplyCode = 0;
            Swap(pAsyncReqEntry->ReplyCode, ReplyCode);
            switch (ReplyCode)
            {
                case REPLY_USER_NAME_OK_NEED_PASSWORD:
                    Status = SendFTPCommandByID(CMD_Password, *pAsyncReqEntry->RequestData.Login.Password);
                    break;

                case REPLY_USER_LOGGED_IN:
                    SendFTPCommandByID(CMD_ReturnSystemType);
                    break;

                case REPLY_NAME_SYS_TYPE:
                    SendFTPCommandByID(CMD_Feature);
                    break;

                case REPLY_SYS_STATUS_OR_HELP_REPLY:
                    m_FtpFeatures = ParseFtpFeature(pAsyncReqEntry);
                    if (!TEST_BITS(m_FtpFeatures, FEATURE_MLSD) &&
                        !TEST_BITS(m_FtpFeatures, FEATURE_MLST))
                    {
                        ShowLog(_T("[E] Server doesn't support command \"MLST\" and \"MLSD\" "));
                        goto DEFAULT_ERROR_PROC;
                    }

                    SendFTPCommandByID(CMD_RepresentationType, "A");
                    break;

                case REPLY_COMMAND_OK:
                    if (TEST_BITS(pAsyncReqEntry->RequestData.Login.FtpFeatures, FEATURE_UTF8))
                    {
                        SendFTPCommandInternal(m_SockCtrl, "OPTS UTF8 ON", NULL);
                        pAsyncReqEntry->RequestData.Login.FtpFeatures &= ~FEATURE_UTF8;
                        m_CodePage = CP_UTF8;
                    }
                    else
                    {
                        pAsyncReqEntry->RequestData.Login.FtpFeatures = 0;
                        SendFTPCommandByID(CMD_PrintWorkingDirectory);
                    }
                    break;

                case REPLY_PATH_CREATED:
                    ShowLog(_T("%S"), (LPCSTR)pAsyncReqEntry->ReplyText);
                    Status = FTPHLP_ERROR_SUCCESS;

                    m_UserName = *pAsyncReqEntry->RequestData.Login.UserName;
                    m_Password = *pAsyncReqEntry->RequestData.Login.Password;
                    delete pAsyncReqEntry->RequestData.Login.UserName;
                    delete pAsyncReqEntry->RequestData.Login.Password;

                    m_pRootDir = new DIRECTORY_INFO(FILE_ATTRIBUTE_DIRECTORY);
                    if (m_pRootDir == NULL)
                        return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_OUT_OF_MEMORY, ERROR_OUTOFMEMORY);

                    m_pRootDir->Name            = _T("/");
                    m_pCurrentDir               = m_pRootDir;
                    pReqData                    = &pAsyncReqEntry->RequestData.GetDirInfo;
                    pReqData->pDirInfo          = &m_pRootDir;
                    pReqData->pDirToQuery       = m_pRootDir;
                    pReqData->bForceRefresh     = FALSE;
                    pReqData->Flags             = pReqData->FLAG_INTERNAL_CHANGE_TYPE;
                    pReqData->PrevType          = pAsyncReqEntry->Type;
                    pAsyncReqEntry->Type        = ASYNC_REQ_GETDIRINFO;
                    pAsyncReqEntry->ReqStatus   = ASYNC_STATUS_READY;
                    break;

DEFAULT_ERROR_PROC:
                default:
                    pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_LOGIN, pAsyncReqEntry->ErrorCode);
                    break;
            }
        }
    }
    else if (IsRequestTimeout(pAsyncReqEntry))
    {
        pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_LOGIN, ERROR_TIMEOUT);
    }

    return Status;
}

LONG CFTPHelper::OnAsyncLogout(ASYNC_REQUEST_ENTRY *pAsyncReqEntry)
{
    LONG Status;

    if (m_SockCtrl == INVALID_SOCKET)
        return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_LOGOUT);

    Status = FTPHLP_ERROR_PENDING;
    if (pAsyncReqEntry->ReqStatus == ASYNC_STATUS_READY)
    {
        Status = SendFTPCommandByID(CMD_Logout, NULL);
        if (Status != FTPHLP_ERROR_PENDING && FTPHLP_FAILED(Status))
        {
            pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, Status, WSAGetLastError());
        }
        else
        {
            pAsyncReqEntry->ResetTimeStamp();
            pAsyncReqEntry->SetStatus(ASYNC_STATUS_PROCESSING);
        }
    }
    else if (pAsyncReqEntry->CheckFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY))
    {
        pAsyncReqEntry->ResetTimeStamp();
        pAsyncReqEntry->RemoveFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY);
        if (pAsyncReqEntry->ReqStatus == ASYNC_STATUS_PROCESSING)
        {
            Status = pAsyncReqEntry->ReplyCode == REPLY_SERVICE_CLOSING_CTRL_CONN ? ASYNC_STATUS_DONE : ASYNC_STATUS_FAILED;
            pAsyncReqEntry->SetStatus(Status);
            closesocket(m_SockCtrl);
            m_SockCtrl = INVALID_SOCKET;
        }
    }
    else if (IsRequestTimeout(pAsyncReqEntry))
    {
        pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_LOGOUT, ERROR_TIMEOUT);
    }

    return Status;
}

LONG CFTPHelper::OnAsyncDisconnect(ASYNC_REQUEST_ENTRY *pAsyncReqEntry)
{
    return OnAsyncLogout(pAsyncReqEntry);
}

LONG CFTPHelper::OnAsyncGetDirInfo(ASYNC_REQUEST_ENTRY *pAsyncReqEntry)
{
    LONG Status;
    REQUEST_DATA_GETDIRINFO *pReqData;

    if (m_SockCtrl == INVALID_SOCKET)
        return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_LOGOUT);

    Status = FTPHLP_ERROR_PENDING;
    if (pAsyncReqEntry->ReqStatus == ASYNC_STATUS_READY)
    {
        pReqData = &pAsyncReqEntry->RequestData.GetDirInfo;
        if (!pReqData->pDirToQuery->CheckAttribute(FILE_ATTRIBUTE_DIRECTORY))
        {
            Status = FTPHLP_ERROR_NOT_DIRECTORY;
            pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, Status);
            return Status;
        }

        if (!pReqData->bForceRefresh && pReqData->pDirToQuery->bCached)
        {
            if (pReqData->pDirInfo != NULL)
                *pReqData->pDirInfo = pReqData->pDirToQuery;
            return pAsyncReqEntry->SetStatus(ASYNC_STATUS_DONE);
        }

        pAsyncReqEntry->ResetTimeStamp();
        Status = SendFTPCommandByID(CMD_Passive);
        if (Status != FTPHLP_ERROR_PENDING && FTPHLP_FAILED(Status))
        {
            pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, Status, WSAGetLastError());
        }
        else
        {
            pAsyncReqEntry->SetStatus(ASYNC_STATUS_PROCESSING);
        }
    }
    else if (pAsyncReqEntry->CheckFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY))
    {
        pAsyncReqEntry->ResetTimeStamp();
        pAsyncReqEntry->RemoveFlags(FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY);
        if (pAsyncReqEntry->ReqStatus == ASYNC_STATUS_PROCESSING)
        {
            LONG ReplyCode;
            SOCKADDR_IN SockAddrIn;
            DIRECTORY_INFO *pDirInfo;

            ReplyCode = 0;
            Swap(pAsyncReqEntry->ReplyCode, ReplyCode);
            switch (ReplyCode)
            {
                case REPLY_ENTERING_PASV_MODE:
                    if (m_SockData != INVALID_SOCKET)
                    {
                        if (pAsyncReqEntry->RequestData.GetDirInfo.pDirToQuery == NULL)
                        {
                            pAsyncReqEntry->RequestData.GetDirInfo.pDirToQuery = m_pCurrentDir;
                            SendFTPCommandByID(CMD_MachineListDirectory);
                            break;
                        }

                        DWORD   Length;
                        StringA Path;
                        String  FullPath;

                        Status = GetDirectoryFullPath(
                                    pAsyncReqEntry->RequestData.GetDirInfo.pDirToQuery,
                                    FullPath);
                        if (FTPHLP_FAILED(Status))
                            return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, Status);

                        Length = WideCharToMultiByte(
                                    m_CodePage,
                                    0,
                                    FullPath,
                                    FullPath.GetLength(),
                                    NULL,
                                    0,
                                    NULL,
                                    NULL);
                        if (Path.AssignBuffer(Length) == NULL)
                            return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_OUT_OF_MEMORY, ERROR_OUTOFMEMORY);

                        Length = WideCharToMultiByte(
                                    m_CodePage,
                                    0,
                                    FullPath,
                                    FullPath.GetLength(),
                                    Path,
                                    Length,
                                    NULL,
                                    NULL);
                        Path[Length] = 0;
                        Path.SetLength(Length);
                        SendFTPCommandByID(CMD_MachineListDirectory, Path);
                        break;
                    }

                    pAsyncReqEntry->ReplyCode = ReplyCode;
                    SockAddrIn = m_SockAddrIn;
                    SockAddrIn.sin_port = GetDataConnectPort(pAsyncReqEntry->ReplyText, pAsyncReqEntry->ReplyText.GetLength());
                    m_SockData = CreateSocket(&SockAddrIn);
                    if (m_SockData == INVALID_SOCKET)
                        goto DEFAULT_FAIL_PROC;

                    break;

                case REPLY_FILE_STATUS_OK:
                    break;

                case REPLY_CLOSING_DATA_CONN:
                    closesocket(m_SockData);
                    m_SockData = INVALID_SOCKET;

                    pReqData = &pAsyncReqEntry->RequestData.GetDirInfo;

                    {
                        SIZE_T  Length;
                        StringW DataReplyW;

                        Length = pAsyncReqEntry->DataReplyText.GetLength();
                        Length = MultiByteToWideChar(
                                    m_CodePage,
                                    0,
                                    pAsyncReqEntry->DataReplyText,
                                    Length,
                                    NULL,
                                    NULL);
                        if (DataReplyW.AssignBuffer(Length) == NULL)
                        {
                            return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_OUT_OF_MEMORY, ERROR_OUTOFMEMORY);
                        }

                        Length = MultiByteToWideChar(
                                    m_CodePage,
                                    0,
                                    pAsyncReqEntry->DataReplyText,
                                    pAsyncReqEntry->DataReplyText.GetLength(),
                                    DataReplyW,
                                    Length);

                        DataReplyW[Length] = 0;
                        DataReplyW.SetLength(Length);
                        Status = UpdateDirectoryInfo(
                                    pReqData->pDirToQuery,
                                    DataReplyW,
                                    Length);
                        if (FTPHLP_FAILED(Status))
                            return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, Status);

                        pDirInfo = pReqData->pDirToQuery;
                    }

                    if (!TEST_BITS(pReqData->Flags, pReqData->FLAG_INTERNAL_CHANGE_TYPE))
                    {
                        if (pReqData->pDirInfo != NULL)
                            *pReqData->pDirInfo = pDirInfo;
                        pAsyncReqEntry->SetStatus(ASYNC_STATUS_DONE, Status);
                        break;
                    }

                    switch (pReqData->PrevType)
                    {
                        case ASYNC_REQ_LOGIN:
                        case ASYNC_REQ_CHANGEPATH:
                            if (pReqData->pDirInfo != NULL)
                                *pReqData->pDirInfo = pDirInfo;
                            break;
                    }

                    pAsyncReqEntry->SetStatus(ASYNC_STATUS_DONE);
                    break;

DEFAULT_FAIL_PROC:
                default:
                    pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_GETDIRINFO, pAsyncReqEntry->ErrorCode);
                    break;
            }
        }
    }
    else if (IsRequestTimeout(pAsyncReqEntry))
    {
        pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_GETDIRINFO, ERROR_TIMEOUT);
    }

    return Status;
}

LONG CFTPHelper::OnAsyncChangeDirectory(ASYNC_REQUEST_ENTRY *pAsyncReqEntry)
{
    LONG Status;

    if (m_SockCtrl == INVALID_SOCKET)
        return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_LOGOUT);

    Status = FTPHLP_ERROR_PENDING;
    if (pAsyncReqEntry->ReqStatus == ASYNC_STATUS_READY)
    {
        DIRECTORY_INFO *pDirInfo;
        REQUEST_DATA_GETDIRINFO *pReqData;

        pDirInfo = pAsyncReqEntry->RequestData.ChangePath.pNewCurDir;

        if (m_pCurrentDir == NULL)
        {
            Status = FTPHLP_ERROR_UNKNOWN;
        }
        else if (!pDirInfo->CheckAttribute(FILE_ATTRIBUTE_DIRECTORY))
        {
            Status = FTPHLP_ERROR_NOT_DIRECTORY;
        }

        if (Status != FTPHLP_ERROR_PENDING)
        {
            return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, Status);
        }

        if (pDirInfo->bCached)
        {
            m_pCurrentDir = pDirInfo;
            return pAsyncReqEntry->SetStatus(ASYNC_STATUS_DONE);
        }

        pReqData                    = &pAsyncReqEntry->RequestData.GetDirInfo;
        pReqData->pDirInfo          = &m_pCurrentDir;
        pReqData->pDirToQuery       = pDirInfo;
        pReqData->bForceRefresh     = FALSE;
        pReqData->Flags             = pReqData->FLAG_INTERNAL_CHANGE_TYPE;
        pReqData->PrevType          = pAsyncReqEntry->Type;
        pAsyncReqEntry->Type        = ASYNC_REQ_GETDIRINFO;
        pAsyncReqEntry->ReqStatus   = ASYNC_STATUS_READY;
    }
    else
    {
        Status = FTPHLP_ERROR_CHANGEDIR;
        pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_CHANGEDIR, ERROR_TIMEOUT);
    }

    return Status;
}

LONG CFTPHelper::QueueDownloadEntry(ASYNC_REQUEST_ENTRY *pAsyncReqEntry, DIRECTORY_INFO *pFileInfo, LPCTSTR pszSavePath, BOOL bBatch)
{
    DOWNLOAD_REQUEST_ENTRY *pDownReq;

    if (pFileInfo->CheckAttribute(FILE_ATTRIBUTE_DIRECTORY))
    {
        LONG Status;
        DIRECTORY_INFO *pSubFile;

        Status = QueryDirectoryFiles(pFileInfo);
        if (FTPHLP_FAILED(Status))
            return Status;

        pSubFile = pFileInfo->pFiles;
        if (pSubFile == NULL)
            return FTPHLP_ERROR_SUCCESS;

        for (SIZE_T Count = pFileInfo->FileCount; Count; ++pSubFile, --Count)
        {
            Status = QueueDownloadEntry(pAsyncReqEntry, pSubFile, pszSavePath, TRUE);
        }

        return FTPHLP_ERROR_SUCCESS;
    }

    pDownReq = new DOWNLOAD_REQUEST_ENTRY;
    if (pDownReq == NULL)
        return FTPHLP_ERROR_OUT_OF_MEMORY;

    GetDirectoryFullPath(pFileInfo, pDownReq->ServerPath);
    pDownReq->SavePath = pszSavePath;
    if (bBatch)
    {
//        if (pDownReq->SavePath[pDownReq->SavePath.GetLength() - 1] != '/')
//            pDownReq->SavePath += '/';
        pDownReq->SavePath += pDownReq->ServerPath;
    }

    pDownReq->Flags      = 0;
    pDownReq->SockAddrIn = m_SockAddrIn;
    pDownReq->UserName   = m_UserName;
    pDownReq->Password   = m_Password;

    pDownReq->Key = pAsyncReqEntry->RequestData.Download.Key;
    pDownReq->CallerParam = pAsyncReqEntry->RequestData.Download.CallerParam;
    *(FARPROC *)&pDownReq->pfStatusCallback = pAsyncReqEntry->RequestData.Download.pfStatusCallback;

    pDownReq->FileSize.QuadPart = pFileInfo->FileSize.QuadPart;

    m_DownloadQueue.AddTail(pDownReq);

    return FTPHLP_ERROR_SUCCESS;
}

LONG CFTPHelper::OnAsyncDownload(ASYNC_REQUEST_ENTRY *pAsyncReqEntry)
{
    LONG Status;
    DIRECTORY_INFO *pServerPath;

    FTP_METHOD_ENTER();

    if (m_SockCtrl == INVALID_SOCKET)
        return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_LOGOUT);

    pServerPath = pAsyncReqEntry->RequestData.Download.pServerPath;
    if (pServerPath == NULL)
        return pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, FTPHLP_ERROR_INVALID_PARAMETER);

    if (pAsyncReqEntry->ReqStatus == ASYNC_STATUS_READY)
    {
        ClearDirectoryCache(pServerPath);
        pAsyncReqEntry->SetStatus(ASYNC_STATUS_PROCESSING);
    }

    if (pServerPath->CheckAttribute(FILE_ATTRIBUTE_DIRECTORY))
    {
        Status = QueueDownloadEntry(
                    pAsyncReqEntry,
                    pServerPath,
                    *pAsyncReqEntry->RequestData.Download.PathLocal,
                    TRUE);
    }
    else
    {
        Status = QueueDownloadEntry(
                    pAsyncReqEntry,
                    pServerPath,
                    *pAsyncReqEntry->RequestData.Download.PathLocal,
                    FALSE);
    }

    if (FTPHLP_SUCCESS(Status))
    {
        pAsyncReqEntry->SetStatus(ASYNC_STATUS_DONE);
        pAsyncReqEntry->pfCompletionRoutine = NULL;
    }
    else if (Status != FTPHLP_ERROR_PENDING)
    {
        pAsyncReqEntry->SetStatus(ASYNC_STATUS_FAILED, Status);
    }

    return Status;
}

DWORD CFTPHelper::DownloadThread(PVOID lpParam)
{
    DWORD Status;
    CFTPHelper *pThis = (CFTPHelper *)lpParam;
    Status = pThis->DownloadThreadWorker();
    return Status;
}

FORCEINLINE DWORD CFTPHelper::DownloadThreadWorker()
{
    MSG                     Message;
    CHAR                    Buffer[1024];
    DWORD                   ThreadStatus, Result, BytesTransfered, Flags;
    ULONG_PTR               CompletionKey;
    timeval                 timeout;
    fd_set                  fdset;
    WSABUF                  WSABuffer;
    CIoCompletionPort       IoCP;
    DOWNLOAD_REQUEST_ENTRY *pDownReq, *pDownComp;

    ThreadStatus = FTPHLP_ERROR_DOWNLOAD_THREAD_INIT;

    PeekMessage(&Message, NULL, WM_USER, WM_USER, PM_NOREMOVE);
    if (!IoCP.Create())
        goto _Exit;

    SetAsyncWaitEvent();

    timeout.tv_sec  = 0;
    timeout.tv_usec = 1;
    WSABuffer.buf   = Buffer;
    WSABuffer.len   = sizeof(Buffer);

    for (SIZE_T Index = 0; ; ++Index, SleepEx(1, FALSE))
    {
        if (PeekMessage(&Message, NULL, WM_SOCKET_FIRST + 1, WM_SOCKET_LAST - 1, PM_REMOVE))
        {
            if (Message.message == WM_SOCKET_FORCE_QUIT)
            {
                while (!m_DownloadQueue.IsEmpty())
                    RemoveDownloadEntry(0);
                break;
            }
        }

        if (m_DownloadQueue.IsEmpty())
        {
            Index = 0;
            continue;
        }

        if (IoCP.GetStatus(&CompletionKey, &BytesTransfered, (LPOVERLAPPED *)&pDownComp, 1))
        {
            HANDLE hFile = pDownComp->hFile;

            if (hFile == INVALID_HANDLE_VALUE)
            {
                WCHAR szPath[MAX_PATH];

                pDownComp->SavePath.CopyTo(szPath, countof(szPath));
                rmnamew(szPath);
                MyCreateDirectoryW(szPath);
                hFile = CreateFileW(
                            pDownComp->SavePath,
                            GENERIC_WRITE,
                            FILE_SHARE_READ,
                            NULL,
                            CREATE_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);
                if (hFile == INVALID_HANDLE_VALUE)
                {
                    pDownComp->SetStatus(DOWNLOAD_STATUS_FAILED, GetLastError());
                    goto END_OF_IOCP_GET_STATUS;
                }

                pDownComp->hFile = hFile;
            }

            pDownComp->TransferSpeed = BytesTransfered / (GetTickCount() - pDownComp->LastTimeStamp + 1);
            pDownComp->ClearFlags(DOWNLOAD_FLAG_BUFFER_INUSE);
            WriteFile(hFile, pDownComp->pvBuffer, BytesTransfered, &BytesTransfered, NULL);
            if (!pDownComp->Update(BytesTransfered))
            {
                pDownComp->ClearFlags(DOWNLOAD_FLAG_CAN_RECV);
                pDownComp->SetFlags(DOWNLOAD_FLAG_RECV_FINISH);
            }

            pDownComp->ResetTimeStamp();
            CallDownloadStatusCallback(pDownComp);
        }
        else
        {
//            Result = GetLastError();
//            if (Result != WAIT_TIMEOUT);
        }

END_OF_IOCP_GET_STATUS:

        if (Index >= m_DownloadQueue.GetCount() || Index >= m_MaxConcurrentTask)
            Index = 0;

        if (!m_DownloadQueue.GetAt(Index, pDownReq))
            continue;

        if (pDownReq == NULL)
            continue;

        LOOP_ONCE
        {
            switch (pDownReq->Status)
            {
                default:
                    continue;

                case DOWNLOAD_STATUS_LOGIN:
                case DOWNLOAD_STATUS_DOWNLOAD:
                case DOWNLOAD_STATUS_LOGOUT:
                    break;
            }

            if (pDownReq->SockCtrl == INVALID_SOCKET)
                break;

            fdset.fd_count  = 1;
            fdset.fd_array[0] = pDownReq->SockCtrl;
            Result = select(0, &fdset, NULL, NULL, &timeout);
            if (Result == SOCKET_ERROR)
                break;
            else if (Result == 0)
                break;

            LOOP_ALWAYS
            {
                Flags = 0;
                WSABuffer.buf = Buffer;
                WSABuffer.len = sizeof(Buffer);
                Result = WSARecv(pDownReq->SockCtrl, &WSABuffer, 1, &BytesTransfered, &Flags, NULL, NULL);
                if (Result == SOCKET_ERROR || BytesTransfered == 0)
                    break;
                pDownReq->ReplyText.Concatenate(Buffer, BytesTransfered);
                Buffer[BytesTransfered] = 0;
                ShowLog(_T("[R] %S"), Buffer);
            }
        }

        Result = FTPHLP_ERROR_SUCCESS;
        switch (pDownReq->Status)
        {
            case DOWNLOAD_STATUS_NULL:
                Result = OnDownloadBegin(pDownReq);
                break;

            case DOWNLOAD_STATUS_CONNECT:
                Result = OnDownloadConnect(pDownReq);
                break;

            case DOWNLOAD_STATUS_LOGIN:
                Result = OnDownloadLogin(pDownReq);
                break;

            case DOWNLOAD_STATUS_LOGIN_DONE:
                Result = OnDownloadLoginDone(pDownReq);
                break;

            case DOWNLOAD_STATUS_DOWNLOAD:
                if (pDownReq->CheckFlags(DOWNLOAD_FLAG_CAN_RECV))
                {
                    DWORD  Flags;
                    WSABUF buf;

                    if (pDownReq->CheckFlags(DOWNLOAD_FLAG_BUFFER_INUSE))
                        break;

                    Flags = 0;
                    buf.buf = (PCHAR)pDownReq->pvBuffer;
                    buf.len = pDownReq->BufferSize;
                    WSARecv(pDownReq->SockData, &buf, 1, NULL, &Flags, (LPWSAOVERLAPPED)pDownReq, NULL);
                    pDownReq->SetFlags(DOWNLOAD_FLAG_BUFFER_INUSE);
                    break;
                }
                else if (pDownReq->CheckFlags(DOWNLOAD_FLAG_RECV_FINISH) &&
                         pDownReq->CheckFlags(DOWNLOAD_FLAG_SERVER_CLOSED))
                {
                    pDownReq->SetStatus(DOWNLOAD_STATUS_LOGOUT);
                    SendDownloadCommandByID(pDownReq->SockCtrl, CMD_Logout);
                    pDownReq->ReplyCode = 0;
                    break;
                }

                Result = OnDownloadDownload(pDownReq);
                if (FTPHLP_SUCCESS(Result))
                {
                    if (IoCP.AssociateSocket(pDownReq->SockData, (ULONG_PTR)pDownReq))
                        break;

                    // WSASetLastError(GetLastError());
                    Result = FTPHLP_ERROR_ASSOCIATE_TO_IOCP;
                }
                break;

            case DOWNLOAD_STATUS_LOGOUT:
                if (!IsRecvAllReplyText(pDownReq->ReplyText, pDownReq->ReplyText.GetLength()))
                    break;

                if (GetServerReplyCode(pDownReq->ReplyText, pDownReq->ReplyText.GetLength()) == REPLY_SERVICE_CLOSING_CTRL_CONN &&
                    pDownReq->CheckFlags(DOWNLOAD_FLAG_RECV_FINISH) &&
                    pDownReq->CheckFlags(DOWNLOAD_FLAG_SERVER_CLOSED))
                {
                    pDownReq->SetStatus(DOWNLOAD_STATUS_DONE);
                }
                else
                {
                    pDownReq->SetStatus(DOWNLOAD_STATUS_FAILED);
                }

                break;

            case DOWNLOAD_STATUS_FAILED:
            case DOWNLOAD_STATUS_DONE:
            case DOWNLOAD_STATUS_DELETE:
                RemoveDownloadEntry(Index);
                continue;
        }

        if (Result == FTPHLP_ERROR_PENDING)
        {
            if (pDownReq->IsTimeout(m_msTimeoutConnect))
            {
                ShowLog(_T("%08X, %08X, %08X\n"), pDownReq->LastTimeStamp, GetTickCount(), m_msTimeoutConnect);
                pDownReq->SetStatus(DOWNLOAD_STATUS_FAILED, ERROR_TIMEOUT, FTPHLP_ERROR_TIMEOUT);
            }
        }
        else if (FTPHLP_FAILED(Result))
        {
            pDownReq->SetStatus(DOWNLOAD_STATUS_FAILED, WSAGetLastError(), Result);
        }
        else
        {
//            pDownReq->ResetTimeStamp();
//            CallDownloadStatusCallback(pDownReq);
        }
    }

    ThreadStatus = FTPHLP_ERROR_SUCCESS;

_Exit:

    if (FTPHLP_FAILED(ThreadStatus))
        SetAsyncWaitEvent();

    return ThreadStatus;
}

LONG CFTPHelper::RemoveDownloadEntry(SIZE_T Index)
{
    DOWNLOAD_REQUEST_ENTRY *pEntry;

    m_DownloadQueue.GetAt(Index, pEntry);

    pEntry->SetEndTime();
    CallDownloadStatusCallback(pEntry);

    delete pEntry;

    m_DownloadQueue.GetHead(pEntry);
    m_DownloadQueue.SetAt(Index, pEntry);
    m_DownloadQueue.RemoveHead();

    return FTPHLP_ERROR_SUCCESS;
}

LONG CFTPHelper::OnDownloadBegin(DOWNLOAD_REQUEST_ENTRY *pReq)
{
    BOOL    bNonBlock;
    DWORD   Result;
    SOCKET  Socket;

    ShowLog(_T("Downloading %s"), pReq->ServerPath);

    Socket = WSASocket(
                AF_INET,
                SOCK_STREAM,
                IPPROTO_TCP,
                NULL,
                0,
                WSA_FLAG_OVERLAPPED);
    if (Socket == INVALID_SOCKET)
        return FTPHLP_ERROR_CREATESOCKET;

    pReq->SockCtrl = Socket;

    bNonBlock = TRUE;
    Result = ioctlsocket(Socket, FIONBIO, (PULONG)&bNonBlock);
    if (Result == SOCKET_ERROR)
        return FTPHLP_ERROR_UNKNOWN;

    Result = WSAConnect(
                pReq->SockCtrl,
                (PSOCKADDR)&pReq->SockAddrIn,
                sizeof(pReq->SockAddrIn),
                NULL,
                NULL,
                NULL,
                NULL);
    if (Result != NO_ERROR && (Result != SOCKET_ERROR || WSAGetLastError() != WSAEWOULDBLOCK))
        return FTPHLP_ERROR_UNKNOWN;

    pReq->SetStatus(DOWNLOAD_STATUS_CONNECT);
    pReq->SetBeginTime();

    return FTPHLP_ERROR_SUCCESS;
}

LONG CFTPHelper::OnDownloadConnect(DOWNLOAD_REQUEST_ENTRY *pReq)
{
    LONG    Status;
    DWORD   Result;
    timeval timeout;
    fd_set  fdset;

    Status = FTPHLP_ERROR_UNKNOWN;

    fdset.fd_count    = 1;
    fdset.fd_array[0] = pReq->SockCtrl;
    Result = select(0, NULL, &fdset, NULL, &timeout);
    if (Result == SOCKET_ERROR)
        return Status;
    else if (Result == 0)
        return FTPHLP_ERROR_PENDING;

    Result = SendDownloadCommandByID(pReq->SockCtrl, CMD_UserName, pReq->UserName);
    if (FTPHLP_FAILED(Result))  // include FTPHLP_ERROR_PENDING
        return Status;

    pReq->SetStatus(DOWNLOAD_STATUS_LOGIN);

    return FTPHLP_ERROR_SUCCESS;
}

LONG CFTPHelper::OnDownloadLogin(DOWNLOAD_REQUEST_ENTRY *pReq)
{
    LONG        DefStatus;
    DWORD       Result;
    SOCKET      Socket;
    LPCSTR      pszNextReply;
    SOCKADDR_IN SockAddrIn;

    DefStatus = FTPHLP_ERROR_UNKNOWN;

    if (pReq->SockData != INVALID_SOCKET)
    {
        fd_set  fdset;
        timeval timeout;

        timeout.tv_sec  = 0;
        timeout.tv_usec = 1;
        fdset.fd_count = 1;
        fdset.fd_array[0] = pReq->SockData;
        Result = select(0, NULL, &fdset, NULL, &timeout);
        if (Result == SOCKET_ERROR)
            return DefStatus;
        else if (Result == 0)
            return FTPHLP_ERROR_PENDING;

        pReq->SetStatus(DOWNLOAD_STATUS_LOGIN_DONE);
        return FTPHLP_ERROR_SUCCESS;
    }

    pszNextReply = IsRecvAllReplyText(pReq->ReplyText, pReq->ReplyText.GetLength());
    if (pszNextReply == NULL)
        return FTPHLP_ERROR_PENDING;

    pReq->ReplyCode = GetServerReplyCode(pReq->ReplyText, pReq->ReplyText.GetLength());

    Socket = pReq->SockCtrl;
    Result = FTPHLP_ERROR_SUCCESS;
    switch (pReq->ReplyCode)
    {
        case REPLY_SERVICE_READY_FOR_USER:
            break;

        case REPLY_USER_NAME_OK_NEED_PASSWORD:
            Result = SendDownloadCommandByID(Socket, CMD_Password, pReq->Password);
            break;

        case REPLY_USER_LOGGED_IN:
            Result = SendDownloadCommandByID(Socket, CMD_RepresentationType, "I");
            break;

        case REPLY_COMMAND_OK:
        {
            SIZE_T  Length;
            StringA ServerPathA;

            Length = WideCharToMultiByte(
                        m_CodePage,
                        0,
                        pReq->ServerPath,
                        pReq->ServerPath.GetLength(),
                        NULL,
                        0,
                        NULL,
                        NULL);
            if (ServerPathA.AssignBuffer(Length) == NULL)
            {
                Result = FTPHLP_ERROR_OUT_OF_MEMORY;
                break;
            }

            Length = WideCharToMultiByte(
                        m_CodePage,
                        0,
                        pReq->ServerPath,
                        pReq->ServerPath.GetLength(),
                        ServerPathA,
                        Length,
                        NULL,
                        NULL);
            ServerPathA[Length] = 0;
            ServerPathA.SetLength(Length);

            Result = SendDownloadCommandByID(Socket, CMD_MachineList, ServerPathA);
            break;
        }

        case REPLY_REQUEST_FILE_OK:
        {
            SIZE_T  Length, FileInfoLength;
            StringW DataReplyW;
            DIRECTORY_INFO FileInfo, *pInfo;

            pszNextReply = NextLineA(pReq->ReplyText, pReq->ReplyText.GetLength());
            while (*pszNextReply == ' ')
                ++pszNextReply;

            FileInfoLength = NextLineA(pszNextReply) - pszNextReply;
            if ((LONG_PTR)FileInfoLength == -(LONG_PTR)pszNextReply)
                FileInfoLength = -1;

            Length = MultiByteToWideChar(
                        m_CodePage,
                        0,
                        pszNextReply,
                        FileInfoLength,
                        NULL,
                        NULL);
            if (DataReplyW.AssignBuffer(Length) == NULL)
            {
                Result = FTPHLP_ERROR_OUT_OF_MEMORY;
                break;
            }

            Length = MultiByteToWideChar(
                        m_CodePage,
                        0,
                        pszNextReply,
                        FileInfoLength,
                        DataReplyW,
                        Length);

            DataReplyW[Length] = 0;
            DataReplyW.SetLength(Length);
            Result = UpdateDirectoryInfo(
                        &FileInfo,
                        DataReplyW,
                        Length);
            if (FTPHLP_FAILED(Result))
                break;

            pszNextReply = NULL;
            pInfo = &FileInfo.pFiles[0];
            pReq->FileSize.QuadPart = pInfo->FileSize.QuadPart;
            Result = SendDownloadCommandByID(Socket, CMD_Passive);
            break;
        }

        case REPLY_ENTERING_PASV_MODE:
            if (pReq->SockData == INVALID_SOCKET)
            {
                SockAddrIn = m_SockAddrIn;
                SockAddrIn.sin_port = GetDataConnectPort(pReq->ReplyText, pReq->ReplyText.GetLength());
                pReq->SockData = CreateSocket(&SockAddrIn, TRUE);
//                ShowLog(_T("Sock = %08X, %S"), pReq->SockData, (LPCSTR)pReq->ReplyText);                
                ShowLog(_T("%s\n"), pReq->ServerPath);
                if (pReq->SockData == INVALID_SOCKET)
                    Result = FTPHLP_ERROR_CREATESOCKET;

                break;
            }
            break;

        default:
            Result = FTPHLP_ERROR_DOWNLOAD_FILE;
    }

    if (pszNextReply != NULL && *pszNextReply != 0)
        pReq->ReplyText = pszNextReply;
    else
        pReq->ReplyText.Empty();

    return Result;
}

LONG CFTPHelper::OnDownloadLoginDone(DOWNLOAD_REQUEST_ENTRY *pReq)
{
    LONG    Status;
    DWORD   Result;
    SIZE_T  Length;
    StringA ServerPathA;

    Status = FTPHLP_ERROR_UNKNOWN;

    Length = WideCharToMultiByte(
                m_CodePage,
                0,
                pReq->ServerPath,
                pReq->ServerPath.GetLength(),
                NULL,
                0,
                NULL,
                NULL);
    if (ServerPathA.AssignBuffer(Length) == NULL)
        return FTPHLP_ERROR_OUT_OF_MEMORY;

    Length = WideCharToMultiByte(
                m_CodePage,
                0,
                pReq->ServerPath,
                pReq->ServerPath.GetLength(),
                ServerPathA,
                Length,
                NULL,
                NULL);
    ServerPathA[Length] = 0;
    ServerPathA.SetLength(Length);

    Result = SendDownloadCommandByID(pReq->SockCtrl, CMD_Retrieve, ServerPathA);
    if (FTPHLP_FAILED(Result))
        return Result;

    pReq->ReplyText.Empty();
    pReq->SetStatus(DOWNLOAD_STATUS_DOWNLOAD);

    return FTPHLP_ERROR_SUCCESS;
}

LONG CFTPHelper::OnDownloadDownload(DOWNLOAD_REQUEST_ENTRY *pReq)
{
    LONG        DefStatus;
    LPCSTR      pszNextReply;

    DefStatus = FTPHLP_ERROR_PENDING;

    pszNextReply = IsRecvAllReplyText(pReq->ReplyText, pReq->ReplyText.GetLength());
    if (pszNextReply == NULL)
        return FTPHLP_ERROR_PENDING;

    pReq->ReplyCode = GetServerReplyCode(pReq->ReplyText, pReq->ReplyText.GetLength());
    if (*pszNextReply != 0)
        pReq->ReplyText = pszNextReply;
    else
        pReq->ReplyText.Empty();

    switch (pReq->ReplyCode)
    {
        case REPLY_CLOSING_DATA_CONN:
            pReq->SetFlags(DOWNLOAD_FLAG_SERVER_CLOSED);
            break;

        case REPLY_FILE_STATUS_OK:
            if (pReq->AllocBuffer(64 * MEMORY_PAGE_SIZE) == NULL)
            {
                DefStatus = FTPHLP_ERROR_OUT_OF_MEMORY;
                break;
            }

            DefStatus = pReq->BufferSize;
            setsockopt(pReq->SockData, SOL_SOCKET, SO_RCVBUF, (PCHAR)&DefStatus, sizeof(DefStatus));
            pReq->SetFlags(DOWNLOAD_FLAG_CAN_RECV);
            DefStatus = FTPHLP_ERROR_SUCCESS;
            break;

        default:
            DefStatus = FTPHLP_ERROR_DOWNLOAD_FILE;
    }

    return DefStatus;
}

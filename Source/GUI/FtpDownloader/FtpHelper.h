#ifndef _FTPHELPER_H_
#define _FTPHELPER_H_

//#define MY_FTPHLP_DEBUG

#if !defined(UNICODE) || !defined(_UNICODE)
    #error non-unicode version is unsupported
#endif

#include "pragma_once.h"
#include <WinSock2.h>
#include <Windows.h>
#include "my_headers.h"
#include "FtpHelperDef.h"

#define InitRequestEntry(pEntry, _Type, _Key, _Param, _Routine, _Flags) \
        { \
            (pEntry)->cbSize                = sizeof(*(pEntry)); \
            (pEntry)->Type                  = (_Type); \
            (pEntry)->FtpStatus             = FTPHLP_ERROR_PENDING; \
            (pEntry)->ErrorCode             = NO_ERROR; \
            (pEntry)->Flags                 = (_Flags); \
            (pEntry)->LastTimeStamp        = INFINITE; \
            (pEntry)->CompletionKey         = (_Key); \
            (pEntry)->RoutineParam          = (_Param); \
            (pEntry)->pfCompletionRoutine   = (_Routine); \
        }

#define FTP_ASYNC_REQUEST_METHOD(_Method, ...) \
            LONG \
            _Method( \
                __VA_ARGS__ \
                ULONG_PTR           CompletionKey, \
                ULONG_PTR           RoutineParam, \
                FCompletionRoutine  pfCompletionRoutine)

#define ASYNC_REQ_METHOD_INTERNAL(_Method, ...) \
            LONG \
            _Method( \
                __VA_ARGS__ \
                ULONG_PTR           CompletionKey, \
                ULONG_PTR           RoutineParam, \
                FCompletionRoutine  pfCompletionRoutine, \
                BOOL                bInsertFirst)

#define ASSERT_REQUEST_TYPE(_ReqType) if (m_pCurrentReq->Type != (_ReqType))

class CFTPHelper
{
protected:
    SOCKET              m_SockCtrl, m_SockData;
    HWND                m_hWnd;
    DWORD               m_DownloadThreadId;
    HANDLE              m_hThreadWnd, m_hThreadDownload;
    HANDLE              m_hEventWaitWnd;
    BOOL                m_bInitialized;
    CMem                m_mem;

    // window data
    StringA                 m_FtpCmdBuffer, m_FtpReplyText;
    StringA                 m_UserName, m_Password;
    DWORD                   m_msTimeout, m_msTimeoutConnect;
    DWORD                   m_MaxConcurrentTask;
    DWORD                   m_FtpFeatures, m_CodePage;
    SOCKADDR_IN             m_SockAddrIn;
    ULONG_PTR               m_ShowLogCallerParam;
    FShowLog                m_pfShowLog;

    DIRECTORY_INFO         *m_pRootDir, *m_pCurrentDir;
    ASYNC_REQUEST_QUEUE     m_AsyncQueue;
    ASYNC_REQUEST_ENTRY    *m_pCurrentReq;
    DOWNLOAD_REQUEST_QUEUE  m_DownloadQueue;

    const static DWORD m_kWinSockVersion = 0x202;

public:
    CFTPHelper();
    ~CFTPHelper();

    FShowLog SetShowLogCallback(FShowLog pfShowLog, ULONG_PTR CallerParam);

    LONG Initialize();
    LONG UnInitialize();
    BOOL IsInitialized();
    BOOL IsDownloadListEmpty();

    FTP_ASYNC_REQUEST_METHOD(Connect, LPCSTR pszAddress, DWORD Port, );
    FTP_ASYNC_REQUEST_METHOD(Disconnect);
    FTP_ASYNC_REQUEST_METHOD(Login, LPCSTR pszUserName, LPCSTR pszPassword, );
    FTP_ASYNC_REQUEST_METHOD(Logout);
    FTP_ASYNC_REQUEST_METHOD(GetDirectoryInfo, DIRECTORY_INFO *pDirectoryToQuery, DIRECTORY_INFO **pDirectoryInfo, BOOL bForceRefresh, );
    FTP_ASYNC_REQUEST_METHOD(GetCurrentDirectoryInfo, DIRECTORY_INFO **pDirectoryInfo, BOOL bForceRefresh, );
    FTP_ASYNC_REQUEST_METHOD(ChangeDirectory, SIZE_T PathIndex, );
    FTP_ASYNC_REQUEST_METHOD(Refresh);
//    FTP_ASYNC_REQUEST_METHOD(DownloadFile, SIZE_T PathIndex, LPCTSTR pszSavePath, );
    LONG
    DownloadFile(
        SIZE_T                  PathIndex,
        LPCTSTR                 pszSavePath,
        ULONG_PTR               Key,
        ULONG_PTR               Param,
        FDownloadStatusCallback pfCallback
    );

    LONG PostFTPCommand(FTP_COMMAND Command, LPCSTR pszParameter);
    LONG PostUserCommand(LPCSTR pszCommand);
    LONG GetDirectoryFullPath(DIRECTORY_INFO *pDir, String &FullPath);

    VOID  SetTimeout(DWORD msConnectTimeout);
    DWORD SetMaxConcurrentTask(DWORD Number);

    INT ShowLog(LPCTSTR pszFormat, ...);

protected:
    VOID Reset();

    HANDLE  CreateAsyncWaitEvent();
    BOOL    CloseAsyncWaitEvent();
    BOOL    ResetAsyncWaitEvent();
    BOOL    SetAsyncWaitEvent();
    DWORD   WaitAsyncWaitEvent(DWORD Milliseconds);

    LPCSTR  IsRecvAllReplyText(LPCSTR pszReplyText, DWORD Length);
    LONG    GetServerReplyCode(LPCSTR pszReplyText, DWORD Length);
    LPCSTR  GetFTPCommandByID(FTP_COMMAND Command);
    LONG    SendFTPCommandByID(FTP_COMMAND Command, LPCSTR pszParameter = NULL);
    LONG    SendFTPCommandInternal(SOCKET Socket, LPCSTR pszCommand, LPCSTR pszParameter = NULL, BOOL bIsDownloadThread = FALSE);
    LONG    SendDownloadCommandByID(SOCKET Socket, FTP_COMMAND Command, LPCSTR pszParameter = NULL);
    LONG    SendDownloadCommand(SOCKET Socket, LPCSTR pszCommand, LPCSTR pszParameter = NULL);

    DWORD   WindowThreadWorker();

    LRESULT WndProcInternal(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
    VOID    OnAccept(SOCKET Socket, DWORD ErrorCode);
    VOID    OnConnect(SOCKET Socket, DWORD ErrorCode);
    VOID    OnRead(SOCKET Socket, DWORD ErrorCode);
    VOID    OnWrite(SOCKET Socket, DWORD ErrorCode);
    VOID    OnClose(SOCKET Socket, DWORD ErrorCode);
    VOID    OnGetHost(HANDLE hSync, DWORD ErrorCode, DWORD BufferLength);

    SOCKET  CreateSocket(LPSOCKADDR_IN pSockAddrIn, BOOL bDownloadThread = FALSE);

    static DWORD    WINAPI WindowThread(PVOID lpParam);
    static LRESULT  WINAPI WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    PVOID AllocaMemory(DWORD Size);
    BOOL  FreeMemory(PVOID pMemory);
    
    LONG  DispatchAsyncRequest();
    ASYNC_REQUEST_ENTRY* AllocAsyncRequest(DWORD EntrySize = sizeof(ASYNC_REQUEST_ENTRY));
    BOOL  FreeAsyncRequest (ASYNC_REQUEST_ENTRY *pAsyncReqEntry);
    LONG  PostAsyncRequest(ASYNC_REQUEST_ENTRY *pAsyncRequest, BOOL bInsertFirst);
    LONG  ChangeRequestType(ASYNC_REQUEST_ENTRY *pAsyncRequest);
    BOOL  IsRequestTimeout(ASYNC_REQUEST_ENTRY *pAsyncRequest);

    LONG  GetDefFtpStatusFromRequest(ASYNC_REQUEST_ENTRY *pAsyncRequest);
    DWORD ParseFtpFeature(ASYNC_REQUEST_ENTRY *pAsyncRequest);
    WORD  GetDataConnectPort(LPCSTR pszReplyText, DWORD Length);
    
    LONG  UpdateDirectoryInfo(DIRECTORY_INFO *pDirInfo, LPCWSTR pszDirectoryInfo, DWORD Length);
    LONG  ClearDirectoryCache(DIRECTORY_INFO *pDir);
    LONG  QueryDirectoryFiles(DIRECTORY_INFO *pDir);
    LONG  FreeDirectoryInfo(DIRECTORY_INFO *pDirectoryInfo);

    LONG  QueueDownloadEntry(ASYNC_REQUEST_ENTRY *pAsyncReqEntry, DIRECTORY_INFO *pFileInfo, LPCTSTR pszSavePath, BOOL bBatch);
    LONG  RemoveDownloadEntry(SIZE_T Index);

    ASYNC_REQ_METHOD_INTERNAL(ConnectInternal, LPCSTR pszAddress, DWORD Port, );
    ASYNC_REQ_METHOD_INTERNAL(DisconnectInternal);
    ASYNC_REQ_METHOD_INTERNAL(LoginInternal, LPCSTR pszUserName, LPCSTR pszPassword, );
    ASYNC_REQ_METHOD_INTERNAL(LogoutInternal);
    ASYNC_REQ_METHOD_INTERNAL(GetDirectoryInfoInternal, DIRECTORY_INFO *pDirectoryToQuery, DIRECTORY_INFO **pDirectoryInfo, BOOL bForceRefresh, );
    ASYNC_REQ_METHOD_INTERNAL(ChangeDirectoryInternal, DIRECTORY_INFO *pDirInfo, );
    ASYNC_REQ_METHOD_INTERNAL(RefreshInternal);
//    ASYNC_REQ_METHOD_INTERNAL(DownloadFileInternal, DIRECTORY_INFO *pDirInfo, LPCTSTR pszSavePath, );
    LONG
    DownloadFileInternal(
        DIRECTORY_INFO         *pDirInfo,
        LPCTSTR                 pszSavePath,
        ULONG_PTR               Key,
        ULONG_PTR               Param,
        FDownloadStatusCallback pfCallback,
        BOOL                    bInsertFirst
    );

    static
    LONG_PTR
    STDCALL
    CompletionRoutineInternal(
        LONG      FtpStatus,
        DWORD     Reserve,
        DWORD     Flags,
        ULONG_PTR CompletionKey,
        ULONG_PTR CallerParam
    );

    LONG_PTR
    CallRequestCompletionRoutine(
        ASYNC_REQUEST_ENTRY *pAsyncRequest,
        LONG                 Status,
        DWORD                BytesTransfered
    );

    LONG CallDownloadStatusCallback(DOWNLOAD_REQUEST_ENTRY *pRequest);

    LONG OnAsyncConnect         (ASYNC_REQUEST_ENTRY *pAsyncReqEntry);
    LONG OnAsyncLogin           (ASYNC_REQUEST_ENTRY *pAsyncReqEntry);
    LONG OnAsyncLogout          (ASYNC_REQUEST_ENTRY *pAsyncReqEntry);
    LONG OnAsyncDisconnect      (ASYNC_REQUEST_ENTRY *pAsyncReqEntry);
    LONG OnAsyncGetDirInfo      (ASYNC_REQUEST_ENTRY *pAsyncReqEntry);
    LONG OnAsyncChangeDirectory (ASYNC_REQUEST_ENTRY *pAsyncReqEntry);
    LONG OnAsyncDownload        (ASYNC_REQUEST_ENTRY *pAsyncReqEntry);

    static DWORD WINAPI DownloadThread(PVOID lpParam);
    DWORD DownloadThreadWorker();
    LONG  OnDownloadBegin       (DOWNLOAD_REQUEST_ENTRY *pReq);
    LONG  OnDownloadConnect     (DOWNLOAD_REQUEST_ENTRY *pReq);
    LONG  OnDownloadLogin       (DOWNLOAD_REQUEST_ENTRY *pReq);
    LONG  OnDownloadLoginDone   (DOWNLOAD_REQUEST_ENTRY *pReq);
    LONG  OnDownloadDownload    (DOWNLOAD_REQUEST_ENTRY *pReq);
    LONG  OnDownloadDelete      (DOWNLOAD_REQUEST_ENTRY *pReq);
};

class CAutoWriteLog
{
public:
    PTChar m_pszFunction;
    CFTPHelper *m_pThis;
    CAutoWriteLog(PTChar pszFunction, CFTPHelper *pThis)
    {
        m_pszFunction = pszFunction;
        m_pThis = pThis;
        m_pThis->ShowLog(_T("Enter: %s\n"), pszFunction);
    }

    ~CAutoWriteLog()
    {
        m_pThis->ShowLog(_T("Leave: %s\n"), m_pszFunction);
    }
};

#endif /* _FTPHELPER_H_ */

/*
[R] 正在连接到 www6.subdomain.com -> DNS=www6.subdomain.com IP=78.46.102.43 PORT=21
[R] 已连接到 www6.subdomain.com
[R] 220---------- Welcome to Pure-FTPd [privsep] [TLS] ----------
[R] 220-You are user number 16 of 500 allowed.
[R] 220-Local time is now 04:34. Server port: 21.
[R] 220-This is a private system - No anonymous login
[R] 220-IPv6 connections are also welcome on this server.
[R] 220 You will be disconnected after 15 minutes of inactivity.
[R] USER user704819
[R] 331 User user704819 OK. Password required
[R] PASS (hidden)
[R] 230-Your bandwidth usage is restricted
[R] 230-User user704819 has group access to:  www-data
[R] 230-OK. Current restricted directory is /
[R] 230 576 Kbytes used (0%) - authorized: 10485760 Kb
[R] SYST
[R] 215 UNIX Type: L8
[R] FEAT
[R] 211-Extensions supported:
[R]  EPRT
[R]  IDLE
[R]  MDTM
[R]  SIZE
[R]  REST STREAM
[R]  MLST type*;size*;sizd*;modify*;UNIX.mode*;UNIX.uid*;UNIX.gid*;unique*;
[R]  MLSD
[R]  TVFS
[R]  ESTP
[R]  PASV
[R]  EPSV
[R]  SPSV
[R]  ESTA
[R]  AUTH TLS
[R]  PBSZ
[R]  PROT
[R] 211 End.
[R] PWD
[R] 257 "/" is your current location
[R] TYPE A
[R] 200 TYPE is now ASCII
[R] PASV
[R] 227 Entering Passive Mode (78,46,102,43,99,160)
[R] 正在打开数据连接 IP: 78.46.102.43 端口: 25504
[R] MLSD
[R] 150 Accepted data connection
[R] 226-Options: -a -l
[R] 226 5 matches total
[R] 列表完成: 558 字节 用时 20.62 秒 (0.0 KB/s)
[R] QUIT
[R] 221-Goodbye. You uploaded 0 and downloaded 0 kbytes.
[R] 221 Logout.
[R] 已注销: www6.subdomain.com
*/

/************************************************************************

ctrl:
  socket
  bind
  connect
  ....

  ctrl->send(PASV)
  crtl->recv("227 Entering pasv mode")
  socket(data)
  bind(data)
  connect(data)
  ctrl->send(MLSD)
  ctrl->recv("150 open...226 Tran....")
  data->recv(file_list)
  closesocket(data)

************************************************************************/

/************************************************************************
[R] TYPE I
[R] 200 Type set to I.
[R] PASV
[R] 227 Entering Passive Mode (127,0,0,1,28,171)
[R] 正在打开数据连接 IP: 127.0.0.1 端口: 7339
[R] RETR 校内赤线区中文化补丁v1.0.rar
[R] 150 Opening BINARY mode data connection for 校内赤线区中文化补丁v1.0.rar (14207859 Bytes).
[R] 226 Transfer complete. 14,207,859 bytes transferred. 55,72From FTP sit
************************************************************************/

/************************************************************************
[S] MLST Anime.txt
[R] 250-Listing /Anime.txt
Type=file;Size=2872;Modify=20110427233214.058; Anime.txt
250 End
MLST EnterAwayMode.bat
[S] MLST EnterAwayMode.bat
[R] 250-Listing /EnterAwayMode.bat
Type=file;Size=269;Modify=20110427131552.854; EnterAwayMode.bat
250 End
************************************************************************/

// MLST Type*;Size*;Create;Modify*;Perm;Win32.ea;Win32.dt;Win32.dl
// Type=file;Size=173056;Modify=20110314065131.892; 2006论文报告、表格范例.doc
// MLST type*;size*;sizd*;modify*;UNIX.mode*;UNIX.uid*;UNIX.gid*;unique*;
// type=file;size=424;modify=20101013104112;UNIX.mode=0644;UNIX.uid=200;UNIX.gid=200;unique=903g8149d2d9; backup-db704819-main-20101013124112.sql.gz

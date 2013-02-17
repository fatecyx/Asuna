#ifndef _FTPHELPERDEF_H_
#define _FTPHELPERDEF_H_

#include "pragma_once.h"
#include "my_headers.h"
#include "MyString.h"
#include "MyList.h"

using namespace MY_LIB_NAME;

/************************************************************************/
/* macro                                                                */
/************************************************************************/

#define FTP_HELPER_CLASS_NAME _T("FTP HELPER CLASS")


#define FTPHLP_FAILED(ErrorCode) ((BOOL)((LONG)(ErrorCode) < 0))
#define FTPHLP_SUCCESS(ErrorCode) !FTPHLP_FAILED(ErrorCode)

#define FTPHLP_RETURN_IF_NOT_INIT() if (!IsInitialized()) return FTPHLP_ERROR_NOT_INITIALIZED
#define FTPHLP_METHOD_SETSTATUS(Status, FTPHLPMethod) ((Status) = (FTPHLPMethod))
#define FTPHLP_IF_FAIL_BREAK(Status, FTPHLPMethod) \
                if (FTPHLP_FAILED(FTPHLP_METHOD_SETSTATUS(Status, FTPMethod))) \
                     break;

#define FTPHLP_RETURN_IF_FAIL(FTPHLPMethod) \
                { \
                     LONG __Status; \
                     FTPHLP_METHOD_SETSTATUS(__Status, FTPHLPMethod); \
                     if (FTPHLP_FAILED(__Status)) \
                          return __Status; \
                }

#define HANDLE_WM_SOCKET(msg, fn) \
                case msg: \
                { \
                     Result = ((fn)((SOCKET)wParam, WSAGETSELECTERROR(lParam)), 0); \
                     break; \
                }

#define HANDLE_ASYCN_REQUEST(s, req, fn) \
                case req: \
                { \
                    (s) = (fn)(m_pCurrentReq); \
                    break; \
                }

#if defined(MY_FTPHLP_DEBUG)
     #define WriteLog(...) ShowLog(__VA_ARGS__)
    #define FTP_METHOD_ENTER() CAutoWriteLog _autowritelog(_T(__FUNCTION__), this)
#else
     #define WriteLog(...) (__VA_ARGS__)
    #define  FTP_METHOD_ENTER()
#endif

#define FTP_METHOD_LEAVE()

/************************************************************************/
/* error code                                                           */
/************************************************************************/
enum
{
     FTPHLP_ERROR_SUCCESS,

     FTPHLP_ERROR_FIRST = 0x80000000,

     // init
     FTPHLP_ERROR_INITIALIZE_FAILED = FTPHLP_ERROR_FIRST,
     FTPHLP_ERROR_WND_INITIALIZE_FAILED,
     FTPHLP_ERROR_NOT_INITIALIZED,

     // common
     FTPHLP_ERROR_PENDING,
     FTPHLP_ERROR_UNKNOWN,
     FTPHLP_ERROR_OUT_OF_MEMORY,
     FTPHLP_ERROR_INVALID_PARAMETER,
     FTPHLP_ERROR_NOT_IMPLEMENTED,
     FTPHLP_ERROR_WAITFAIL,
     FTPHLP_ERROR_TIMEOUT,
     FTPHLP_ERROR_CANCELASYNC,
     FTPHLP_ERROR_EMPTY_ASYNC_REQUEST,
     FTPHLP_ERROR_SERVER_DISCONNECT,

     // connect
     FTPHLP_ERROR_ASYNCGETHOSTNAME,
     FTPHLP_ERROR_ASYNCSELECT,
     FTPHLP_ERROR_CREATESOCKET,
     FTPHLP_ERROR_CONNECT,

     // disconnect
     FTPHLP_ERROR_DISCONNECT,

     // send cmd
     FTPHLP_ERROR_SENDCMD_LAST_NOT_COMPLETE,

     // login
     FTPHLP_ERROR_LOGIN,

     // logout
     FTPHLP_ERROR_LOGOUT,

     // get dir info
     FTPHLP_ERROR_GETDIRINFO,

     // change path
     FTPHLP_ERROR_CHANGEDIR,
     FTPHLP_ERROR_NOT_DIRECTORY,
     FTPHLP_ERROR_TOP_DIRECTORY,

     // download
     FTPHLP_ERROR_DOWNLOAD_FILE,
     FTPHLP_ERROR_DOWNLOAD_THREAD_INIT,
     FTPHLP_ERROR_NOT_FILE,
     FTPHLP_ERROR_ASSOCIATE_TO_IOCP,

     // async request
     FTPHLP_ERROR_POST_ASYNC_REQUEST,
     FTPHLP_ERROR_PEEK_ASYCN_REQUEST,
     FTPHLP_ERROR_INVALID_REQUEST,
     FTPHLP_ERROR_UNKNOWN_ASYNC_REQUEST_TYPE,
};

enum FTP_COMMAND
{
     FTP_COMMAND_BASE,

     // Access Control Commands
     CMD_UserName = FTP_COMMAND_BASE,
     CMD_Password,
     CMD_Account,
     CMD_ChangeWorkingDirectory,
     CMD_ChangeToParentDirectory,
     CMD_StructureMount,
     CMD_ReInitialize,
     CMD_Logout,

     // Transfer Parameter Commands
     CMD_DataPort,
     CMD_Passive,
     CMD_RepresentationType,
     CMD_FileStructure,
     CMD_TransferMode,

     // FTP Service Commands
     CMD_Retrieve,
     CMD_Store,
     CMD_StoreUnique,
     CMD_Append,
     CMD_Allocate,
     CMD_Restart,
     CMD_RenameFrom,
     CMD_RenameTo,
     CMD_Abort,
     CMD_Delete,
     CMD_DeleteDirectory,
     CMD_MakeDirectory,
     CMD_PrintWorkingDirectory,
     CMD_List,
     CMD_NameList,

     // less common
     CMD_ReturnSystemType,
     CMD_Feature,
     CMD_MachineListDirectory,  // MLSD is intended to be a replacement for the LIST command, where a data connection is established between the client and the server for the purpose of sending a directory listing.
     CMD_MachineList,           // MLST, on the other hand, is intended to give listing information for a single file or folder without establishing a data connection, which is required by similar commands like LIST, NLST, RETR, STOR, STOU, and MLSD. Instead the information returned is a single line containing the listing for the requested path.

     FTP_COMMAND_MAX,
};

/************************************************************************

  http://www.altools.com/image/support/alftp/ALFTP_35_help/FTP_response_codes_rfc_959_messages.htm

  FTP Response codes (defined in RFC 959)

  1yz    Positive Preliminary reply
  2yz    Positive Completion reply
  3yz    Positive Intermediate reply
  4yz    Transient Negative Completion reply
  5yz    Permanent Negative Completion reply

  x0z    Syntax - These replies refer to syntax errors, syntactically correct commands that don't fit any functional category, unimplemented or superfluous commands.
  x1z    Information - These are replies to requests for information, such as status or help.
  x2z    Connections - Replies referring to the control and data connections.
  x3z    Authentication and accounting - Replies for the login process and accounting procedures.
  x4z    Unspecified as yet.
  x5z    File system - These replies indicate the status of the Server file system vis-a-vis the requested transfer or other file system action.

  110	Restart marker reply.
        In this case, the text is exact and not left to the particular implementation; it must read:
        MARK yyyy = mmmm
        Where yyyy is User-process data stream marker, and mmmm server's equivalent marker (note the spaces between markers and "=").
  120	Service ready in nnn minutes.
  125	Data connection already open; transfer starting.
  150	File status okay; about to open data connection.
  200	Command okay.
  202	Command not implemented, superfluous at this site.
  211	System status, or system help reply.
  212	Directory status.
  213	File status.
  214	Help message. On how to use the server or the meaning of a particular non-standard command.
        This reply is useful only to the human user.
  215	NAME system type. Where NAME is an official system name from the list
        in the Assigned Numbers document.
  220	Service ready for new user.
  221	Service closing control connection. Logged out if appropriate.
  225	Data connection open; no transfer in progress.
  226	Closing data connection. Requested file action successful
        (for example, file transfer or file abort).
  227	Entering Passive Mode (h1,h2,h3,h4,p1,p2).
  230	User logged in, proceed.
  250	Requested file action okay, completed.
  257	"PATHNAME" created.
  331	User name okay, need password.
  332	Need account for login.
  350	Requested file action pending further information.
  421	Service not available, closing control connection.
        This may be a reply to any command if the service knows it must shut down.
  425	Can't open data connection.
  426	Connection closed; transfer aborted.
  450	Requested file action not taken. File unavailable (e.g., file busy).
  451	Requested action aborted: local error in processing.
  452	Requested action not taken. Insufficient storage space in system.
  500	Syntax error, command unrecognized. This may include errors such as command line too long
  501	Syntax error in parameters or arguments.
  502	Command not implemented.
  503	Bad sequence of commands.
  504	Command not implemented for that parameter.
  530	Not logged in.
  532	Need account for storing files.
  550	Requested action not taken. File unavailable (e.g., file not found, no access).
  551	equested action aborted: page type unknown.
  552	Requested file action aborted. Exceeded storage allocation (for current directory or dataset).
  553	Requested action not taken. File name not allowed.

************************************************************************/

enum FTP_SERVER_REPLY_CODE
{
    REPLY_CODE_INVALID                        = -1,
    REPLY_RESTART_MARKER_REPLY                = 110,
    REPLY_SERVICE_READY                       = 120,
    REPLY_DATA_CONN_READY                     = 125,
    REPLY_FILE_STATUS_OK                      = 150,
    REPLY_COMMAND_OK                          = 200,
    REPLY_COMMAND_NOT_IMPL                    = 202,
    REPLY_SYS_STATUS_OR_HELP_REPLY            = 211,
    REPLY_DIRECTORY_STATUS                    = 212,
    REPLY_FILE_STATUS                         = 213,
    REPLY_HELP_MSG                            = 214,
    REPLY_NAME_SYS_TYPE                       = 215,
    REPLY_SERVICE_READY_FOR_USER              = 220,
    REPLY_SERVICE_CLOSING_CTRL_CONN           = 221,
    REPLY_DATA_CONN_OPEN                      = 225,
    REPLY_CLOSING_DATA_CONN                   = 226,
    REPLY_ENTERING_PASV_MODE                  = 227,
    REPLY_USER_LOGGED_IN                      = 230,
    REPLY_REQUEST_FILE_OK                     = 250,
    REPLY_PATH_CREATED                        = 257,
    REPLY_USER_NAME_OK_NEED_PASSWORD          = 331,
    REPLY_NEED_ACCOUNT_FOR_LOGIN              = 332,
    REPLY_REQUEST_FILE_PENDING                = 350,
    REPLY_SERVIDE_INVALID_CLOSING_CTRL_CONN   = 421,
    REPLY_CANNT_OPEN_DATA_CONN                = 425,
    REPLY_CONN_CLOSED                         = 426,
//    REPLY_REQUEST_FILE_UNAVAILABLE            = 450,
    REPLY_REQUEST_ACTION_LOCAL_ERROR          = 451,
    REPLY_REQUEST_ACTION_NOT_ENOUGN_SPACE     = 452,
    REPLY_SYNTAX_UNKNOWN_CMD                  = 500,
    REPLY_SYNTAX_INVALID_PARAM                = 501,
    REPLY_COMMAND_NOT_IMPL2                   = 502,
    REPLY_BAD_COMMAND_SEQUENCE                = 503,
    REPLY_CMD_NOT_IMPL_FOR_PARAM              = 504,
    REPLY_NOT_LOGGED_IN                       = 530,
    REPLY_NEED_ACCOUT_FOR_STORING             = 532,
    REPLY_REQUEST_FILE_UNAVAILABLE            = 550,
    REPLY_EQUESTED_ACTION_ABORT               = 551,
    REPLY_REQUEST_FILE_INVALID_NAME           = 552,
};

/************************************************************************/
/* flags                                                                */
/************************************************************************/

#define FTPHLP_ASYNC_REQ_FLAG_SERVER_REPLY      0x00000001L
#define FTPHLP_ASYNC_REQ_FLAG_MULTI_LINE_REPLY  0x00000002L
#define FTPHLP_ASYNC_REQ_FLAG_SOCKET_CLOSED     0x00000004L

/************************************************************************/
/* struct                                                               */
/************************************************************************/
typedef INT (STDCALL *FShowLog)(ULONG_PTR CallerParam, LPCTSTR pszFormat, va_list args);
typedef
LONG_PTR
(STDCALL
*FCompletionRoutine)(
    LONG      FtpStatus,
    DWORD     ErrorCode,
    DWORD     Flags,
    ULONG_PTR CompletionKey,
    ULONG_PTR CallerParam
);

struct DIRECTORY_INFO
{
    enum
    {
        PARENT_DIRECTORY_INDEX  = -1,
    };

    BOOL            bCached;
    DWORD           Attributes;
    ULARGE_INTEGER  FileSize;
    FILETIME        LastWriteTime;
    SIZE_T          FileCount;
    DIRECTORY_INFO *pFiles;
    DIRECTORY_INFO *pParent;
    String          Name;

    DIRECTORY_INFO(
        DWORD   Attributes  = 0,
        SIZE_T  FileCount   = 0,
        LPCTSTR pszName     = NULL
    ) : Name(pszName)
    {
        Reset();
        this->Attributes    = Attributes;
        this->FileCount     = FileCount;
    }

    ~DIRECTORY_INFO()
    {
        Free();
    }

    VOID Reset()
    {
        bCached                         = FALSE;
        Attributes                      = 0;
        FileSize.QuadPart               = 0;
        LastWriteTime.dwHighDateTime    = 0;
        LastWriteTime.dwLowDateTime     = 0;
        FileCount                       = 0;
        pFiles                          = NULL;
        pParent                         = NULL;
    }

    VOID Free()
    {
        if (pFiles != NULL)
            delete[] pFiles;

        DIRECTORY_INFO *pParent = this->pParent;
        Reset();
        this->pParent = pParent;
    }

    BOOL CheckAttribute(DWORD Attributes)
    {
        return TEST_BITS(this->Attributes, Attributes);
    }

    DWORD SetAttribute(DWORD Attributes)
    {
        this->Attributes |= Attributes;
        return this->Attributes;
    }

    DWORD ClearAttribute(DWORD Attributes)
    {
        this->Attributes &= ~Attributes;
        return this->Attributes;
    }
};

struct PER_IO_REQUEST : public WSAOVERLAPPED
{
    ULONG_PTR CompletionKey;
    ULONG_PTR CallerParam;
};

typedef struct
{
    StringA *Address;
    DWORD    Port;
    union
    {
        HOSTENT Entry;
        CHAR    Buffer[0x100];
//        CHAR    Buffer[MAXGETHOSTSTRUCT];
    } HostEntry;
} REQUEST_DATA_CONNECT;

enum EFtpSupportFeature
{
    FEATURE_UTF8    = 0x00000001,
    FEATURE_MLST    = 0x00000002,
    FEATURE_MLSD    = 0x00000004,
    FEATURE_RESET   = 0x00000008,
};

typedef struct
{
    StringA *UserName;
    StringA *Password;
    DWORD    FtpFeatures;
} REQUEST_DATA_LOGIN;

typedef struct
{
    BOOL             bForceRefresh;
    DIRECTORY_INFO **pDirInfo, *pDirToQuery;
    DWORD            Flags;
    LONG             PrevType;

    enum
    {
        FLAG_INTERNAL_CHANGE_TYPE = 0x00000001,
    };
} REQUEST_DATA_GETDIRINFO;

typedef struct
{
    DIRECTORY_INFO *pNewCurDir;
} REQUEST_DATA_CHANGEPATH;

typedef struct
{
    String         *PathLocal;
    DIRECTORY_INFO *pServerPath;
    ULONG_PTR       Key;
    ULONG_PTR       CallerParam;
    FARPROC         pfStatusCallback;
} REQUEST_DATA_DOWNLOAD;

enum
{
    WM_SOCKET_FIRST = WM_USER,

    WM_SOCKET_FORCE_QUIT,
    WM_SOCKET_ASYNC_GET_HOST,
    WM_SOCKET_EVENT_CONTROL,

    WM_SOCKET_LAST,
};

enum FTP_ASYNC_REQUEST
{
    ASYNC_REQ_NULL,
    ASYNC_REQ_CONNECT,
    ASYNC_REQ_LOGIN,
    ASYNC_REQ_LOGOUT,
    ASYNC_REQ_DISCONNECT,
    ASYNC_REQ_GETDIRINFO,
    ASYNC_REQ_CHANGEPATH,
    ASYNC_REQ_DOWNLOAD,
};

enum FTP_ASYNC_REQUEST_STATUS
{
    ASYNC_STATUS_READY,
    ASYNC_STATUS_PROCESSING,
    ASYNC_STATUS_DONE,
    ASYNC_STATUS_FAILED,
    ASYNC_STATUS_WOULDDELETE,
};

struct ASYNC_REQUEST_ENTRY
{
    ULONG               cbSize;
    LONG                Type;
    LONG                ReqStatus;
    LONG                FtpStatus;
    DWORD               ErrorCode;
    DWORD               Flags;
    LONG                ReplyCode;
    StringA             ReplyText;
    StringA             DataReplyText;
    DWORD               BeginTimeStamp;
    ULONG_PTR           CompletionKey;
    ULONG_PTR           RoutineParam;
    FCompletionRoutine  pfCompletionRoutine;
    union
    {
        REQUEST_DATA_CONNECT    Connect;
        REQUEST_DATA_LOGIN      Login;
        REQUEST_DATA_GETDIRINFO GetDirInfo;
        REQUEST_DATA_CHANGEPATH ChangePath;
        REQUEST_DATA_DOWNLOAD   Download;
    } RequestData;

    ASYNC_REQUEST_ENTRY(
        LONG                Type                = 0,
        ULONG_PTR           CompletionKey       = 0,
        ULONG_PTR           RoutineParam        = 0,
        FCompletionRoutine  pfCompletionRoutine = NULL,
        DWORD               Flags               = 0
    )
    {
        this->cbSize                = sizeof(*this);
        this->Type                  = Type;
        this->ReqStatus             = ASYNC_STATUS_READY;
        this->FtpStatus             = FTPHLP_ERROR_PENDING;
        this->ErrorCode             = NO_ERROR;
        this->Flags                 = Flags;
        this->BeginTimeStamp        = INFINITE;
        this->CompletionKey         = CompletionKey;
        this->RoutineParam          = RoutineParam;
        this->pfCompletionRoutine   = pfCompletionRoutine;
    }

    LONG
    SetStatus(
        LONG ReqStatus,
        LONG FtpStatus = FTPHLP_ERROR_SUCCESS,
        LONG ErrorCode = NO_ERROR)
    {
        this->ReqStatus = ReqStatus;
        this->FtpStatus = FtpStatus;
        this->ErrorCode = ErrorCode;
        return ReqStatus;
    }

    BOOL CheckFlags(DWORD Flags)
    {
        return TEST_BITS(this->Flags, Flags);
    }

    DWORD SetFlags(DWORD Flags)
    {
        this->Flags |= Flags;
        return this->Flags;
    }

    DWORD RemoveFlags(DWORD Flags)
    {
        this->Flags &= ~Flags;
        return this->Flags;
    }

    DWORD ResetTimeStamp()
    {
        return BeginTimeStamp = GetTickCount();
    }
};

typedef CList<ASYNC_REQUEST_ENTRY *> ASYNC_REQUEST_QUEUE;

enum
{
    DOWNLOAD_STATUS_NULL,
    DOWNLOAD_STATUS_CONNECT,
    DOWNLOAD_STATUS_LOGIN,
    DOWNLOAD_STATUS_LOGIN_DONE,
    DOWNLOAD_STATUS_DOWNLOAD,
    DOWNLOAD_STATUS_LOGOUT,
    DOWNLOAD_STATUS_FAILED,
    DOWNLOAD_STATUS_DELETE,
    DOWNLOAD_STATUS_DONE,
};

enum
{
    DOWNLOAD_FLAG_BATCH         = 0x00000001,
    DOWNLOAD_FLAG_BLOCK         = 0x00000002,
    DOWNLOAD_FLAG_REPLY         = 0x00000004,
    DOWNLOAD_FLAG_SERVER_CLOSED = 0x00000008,
    DOWNLOAD_FLAG_CAN_RECV      = 0x00000010,
    DOWNLOAD_FLAG_RECV_FINISH   = 0x00000020,
    DOWNLOAD_FLAG_BUFFER_INUSE  = 0x00000040,
};

struct DOWNLOAD_REQUEST_ENTRY;

typedef
LONG_PTR
(STDCALL
*FDownloadStatusCallback)(
    DOWNLOAD_REQUEST_ENTRY *pDownReq,
    ULONG_PTR               Key,
    ULONG_PTR               CallerParam
);

struct DOWNLOAD_REQUEST_ENTRY : public WSAOVERLAPPED
{
    DWORD               Index;
    DWORD               Flags;
    LONG                Status;
    LONG                FtpStatus;
    DWORD               ErrorCode;
    DWORD               ErrorTimes;
    SOCKET              SockCtrl;
    SOCKET              SockData;
    SOCKADDR_IN         SockAddrIn;
    StringW             ServerPath;
    StringW             SavePath;
    StringA             UserName;
    StringA             Password;
    StringA             ReplyText;
    LONG                ReplyCode;
    HANDLE              hFile;
    PVOID               pvBuffer;
    DWORD               BufferSize;

    DWORD               LastTimeStamp;
    DWORD               TransferSpeed;
    FILETIME            BeginTime;
    FILETIME            EndTime;
    ULARGE_INTEGER      BytesTransfered;
    ULARGE_INTEGER      FileSize;

    ULONG_PTR               Key;
    ULONG_PTR               UserData;
    ULONG_PTR               CallerParam;
    FDownloadStatusCallback pfStatusCallback;

//    ULONG_PTR           RoutineParam;
//    FCompletionRoutine  pfCompletionRoutine;

    DOWNLOAD_REQUEST_ENTRY()
    {
        Reset();
    }

    ~DOWNLOAD_REQUEST_ENTRY()
    {
        Release();
    }

    VOID Reset()
    {
        Offset                      = 0;
        OffsetHigh                  = 0;
        hEvent                      = NULL;
        Flags                       = 0;
        Status                      = DOWNLOAD_STATUS_NULL;
        ErrorTimes                  = 0;
        SockCtrl                    = INVALID_SOCKET;
        SockData                    = INVALID_SOCKET;
        hFile                       = INVALID_HANDLE_VALUE;
        pvBuffer                    = NULL;
        BufferSize                  = 0;
        TransferSpeed               = 0;
        LastTimeStamp               = INFINITE;
        BeginTime.dwLowDateTime     = 0;
        BeginTime.dwHighDateTime    = 0;
        EndTime.dwLowDateTime       = 0;
        EndTime.dwHighDateTime      = 0;
        BytesTransfered.QuadPart    = 0;
        FileSize.QuadPart           = 0;
        UserData                    = 0;
        pfStatusCallback            = NULL;
        ZeroMemory(&SockAddrIn, sizeof(SockAddrIn));
    }

    VOID Release()
    {
        FreeBuffer();
        if (hFile != INVALID_HANDLE_VALUE)
            CloseHandle(hFile);
        if (SockCtrl != INVALID_SOCKET)
            closesocket(SockCtrl);
        if (SockData != INVALID_SOCKET)
            closesocket(SockData);
    }

    BOOL Update(DWORD BytesTransfered)
    {
        this->BytesTransfered.QuadPart += BytesTransfered;
        Offset     = this->BytesTransfered.LowPart;
        OffsetHigh = this->BytesTransfered.HighPart;

        return this->BytesTransfered.QuadPart < FileSize.QuadPart;
    }

    PVOID AllocBuffer(DWORD Size)
    {
        if (pvBuffer != NULL)
            return pvBuffer;

        Size = ROUND_UP(Size, MEMORY_PAGE_SIZE);
        BufferSize = Size;
        pvBuffer = VirtualAllocEx(NtCurrentProcess(), NULL, Size, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
        return pvBuffer;
    }

    BOOL FreeBuffer()
    {
        if (pvBuffer == NULL)
            return FALSE;

        if (!VirtualFreeEx(NtCurrentProcess(), pvBuffer, 0, MEM_RELEASE))
            return FALSE;

        pvBuffer = NULL;
        return TRUE;
    }

    LONG SetStatus(LONG Status, DWORD ErrorCode = NO_ERROR, LONG FtpStatus = FTPHLP_ERROR_SUCCESS)
    {
        this->Status    = Status;
        this->ErrorCode = ErrorCode;
        this->FtpStatus = FtpStatus;
        return Status;
    }

    VOID SetBeginTime()
    {
        SYSTEMTIME LocalTime;
        GetLocalTime(&LocalTime);
        SystemTimeToFileTime(&LocalTime, &BeginTime);
        ResetTimeStamp();
    }

    VOID SetEndTime()
    {
        SYSTEMTIME LocalTime;
        GetLocalTime(&LocalTime);
        SystemTimeToFileTime(&LocalTime, &EndTime);
    }

    DWORD ResetTimeStamp()
    {
        LastTimeStamp = GetTickCount();
        return LastTimeStamp;
    }

    BOOL IsTimeout(DWORD msTimeout)
    {
        if (msTimeout == INFINITE || LastTimeStamp == INFINITE)
            return FALSE;

        return GetTickCount() - LastTimeStamp >= msTimeout;
    }

    DWORD SetFlags(DWORD Flags)
    {
        this->Flags |= Flags;
        return this->Flags;
    }

    DWORD ClearFlags(DWORD Flags)
    {
        this->Flags &= ~Flags;
        return this->Flags;
    }

    BOOL CheckFlags(DWORD Flags)
    {
        return TEST_BITS(this->Flags, Flags);
    }
};

typedef CList<DOWNLOAD_REQUEST_ENTRY *> DOWNLOAD_REQUEST_QUEUE;

template<class Elem>
class IntBigEndianT
{
protected:
     Elem m_Value;

public:
     IntBigEndianT<Elem>()
     { }

     IntBigEndianT<Elem>(Elem Value)
     {
          if (IsType32Bit())
                m_Value = Bswap(Value);
          else
                m_Value = SWAP2(Value);
     }

     IntBigEndianT& operator= (Elem Value)
     {
          if (IsType32Bit())
                m_Value = Bswap(Value);
          else
                m_Value = SWAP2(Value);

          return *this;
     }

     operator Elem()
     {
          return m_Value;
//          return IsType32Bit() ? Bswap(m_Value) : SWAP2(m_Value);;
     }

protected:
     Bool IsType32Bit()
     {
          return sizeof(Elem) == 4;
     }
};

typedef IntBigEndianT<Int16>  Int16BE;
typedef IntBigEndianT<UInt16> UInt16BE;
typedef IntBigEndianT<Int32>  Int32BE;
typedef IntBigEndianT<UInt32> UInt32BE;

#endif // _FTPHELPERDEF_H_
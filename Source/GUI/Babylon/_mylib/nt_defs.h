#if !defined(_NT_DEFS_H_)
#define _NT_DEFS_H_

#include <Windows.h>
#include "my_types.h"

//#if defined(__AFX_H__)
typedef LONG NTSTATUS;
//#endif

#pragma warning(disable:4201)
#pragma pack(4)

/************************************************************************
  mine defs
************************************************************************/

#define RTL_CONST_STRING(_str, _string) \
            (_str).Length = sizeof(_string) - sizeof((_str).Buffer[0]); \
            (_str).MaximumLength = sizeof(_string); \
            (_str).Buffer = (_string);

/************************************************************************/
/* enums                                                                */
/************************************************************************/

//
// Define the create disposition values
//

enum SYSDBG_COMMAND
{
    //以下5个在Windows NT各个版本上都有
    SysDbgGetTraceInformation = 1,
    SysDbgSetInternalBreakpoint = 2,
    SysDbgSetSpecialCall = 3,
    SysDbgClearSpecialCalls = 4,
    SysDbgQuerySpecialCalls = 5, 

    // 以下是NT 5.1 新增的
    SysDbgDbgBreakPointWithStatus = 6, 

    //获取KdVersionBlock
    SysDbgSysGetVersion = 7, 

    //从内核空间拷贝到用户空间，或者从用户空间拷贝到用户空间
    //但是不能从用户空间拷贝到内核空间
    SysDbgCopyMemoryChunks_0 = 8,
    //SysDbgReadVirtualMemory = 8, 

    //从用户空间拷贝到内核空间，或者从用户空间拷贝到用户空间
    //但是不能从内核空间拷贝到用户空间
    SysDbgCopyMemoryChunks_1 = 9,
    //SysDbgWriteVirtualMemory = 9, 

    //从物理地址拷贝到用户空间，不能写到内核空间
    SysDbgCopyMemoryChunks_2 = 10,
    //SysDbgReadVirtualMemory = 10, 

    //从用户空间拷贝到物理地址，不能读取内核空间
    SysDbgCopyMemoryChunks_3 = 11,
    //SysDbgWriteVirtualMemory = 11, 

    //读写处理器相关控制块
    SysDbgSysReadControlSpace = 12,
    SysDbgSysWriteControlSpace = 13, 

    //读写端口
    SysDbgSysReadIoSpace = 14,
    SysDbgSysWriteIoSpace = 15, 

    //分别调用RDMSR@4和_WRMSR@12
    SysDbgSysReadMsr = 16,
    SysDbgSysWriteMsr = 17, 

    //读写总线数据
    SysDbgSysReadBusData = 18,
    SysDbgSysWriteBusData = 19, 

    SysDbgSysCheckLowMemory = 20, 

    // 以下是NT 5.2 新增的 

    //分别调用_KdEnableDebugger@0和_KdDisableDebugger@0
    SysDbgEnableDebugger = 21,
    SysDbgDisableDebugger = 22, 

    //获取和设置一些调试相关的变量
    SysDbgGetAutoEnableOnEvent = 23,
    SysDbgSetAutoEnableOnEvent = 24,
    SysDbgGetPitchDebugger = 25,
    SysDbgSetDbgPrintBufferSize = 26,
    SysDbgGetIgnoreUmExceptions = 27,
    SysDbgSetIgnoreUmExceptions = 28
};


enum SYSTEM_INFORMATION_CLASS
{
    SystemBasicInformation                  = 0x00,
    SystemProcessorInformation              = 0x01,
    SystemPerformanceInformation            = 0x02,
    SystemTimeInformation                   = 0x03,
    SystemPathInformation                   = 0x04,
    SystemProcessThreadInformation          = 0x05,
    SystemServiceDescriptorTableInformation = 0x06,
    SystemIoConfigInformation               = 0x07,
    SystemProcessorTimeInformation          = 0x08,
    SystemNtGlobalFlagInformation           = 0x09,
    SystemModuleInformation                 = 0x0B,
    SystemResourceLockInformation           = 0x0C,
    SystemHandleInformation                 = 0x10,
    SystemObjectInformation                 = 0x11,
    SystemPageFileInformation               = 0x12,
    SystemInstructionEmulationInformation   = 0x13,
    SystemCacheInformation                  = 0x15,
    SystemPoolTagInformation                = 0x16,
    SystemProcessorScheduleInformation      = 0x17,
    SystemDpcInformation                    = 0x18,
    SystemLoadSystemImage                   = 0x1A,
    SystemUnloadSystemImage                 = 0x1B,
    SystemTimerInformation                  = 0x1C,
    SystemCrashDumpSectionInformation       = 0x20,
    SystemProcessorFaultCountInformation    = 0x21,
    SystemCrashDumpStateInformation         = 0x22,
    SystemDebuggerInformation               = 0x23,
    SystemThreadSwitchCounters              = 0x24,
    SystemQuotaInformation                  = 0x25,
    SystemLoadDriverInformation             = 0x26,
    SystemPrioritySeparation                = 0x27,
    SystemTimeZoneInformation               = 0x2C,
    SystemLookasideInformation              = 0x2D,
};

enum FILE_INFORMATION_CLASS
{
    FileDirectoryInformation = 1,
    FileFullDirectoryInformation = 2,
    FileBothDirectoryInformation = 3,
    FileBasicInformation = 4,
    FileStandardInformation = 5,
    FileInternalInformation = 6,
    FileEaInformation = 7,
    FileAccessInformation = 8,
    FileNameInformation = 9,
    FileRenameInformation = 10,
    FileLinkInformation = 11,
    FileNamesInformation = 12,
    FileDispositionInformation = 13,
    FilePositionInformation = 14,
    FileFullEaInformation = 15,
    FileModeInformation = 16,
    FileAlignmentInformation = 17,
    FileAllInformation = 18,
    FileAllocationInformation = 19,
    FileEndOfFileInformation = 20,
    FileAlternateNameInformation = 21,
    FileStreamInformation = 22,
    FilePipeInformation = 23,
    FilePipeLocalInformation = 24, 
    FilePipeRemoteInformation = 25,
    FileMailslotQueryInformation = 26,
    FileMailslotSetInformation = 27,
    FileCompressionInformation = 28,
    FileObjectIdInformation = 29,
    FileCompletionInformation = 30,
    FileMoveClusterInformation = 31,
    FileQuotaInformation = 32,
    FileReparsePointInformation = 33,
    FileNetworkOpenInformation = 34,
    FileAttributeTagInformation = 35,
    FileTrackingInformation = 36,
    FileIdBothDirectoryInformation = 37,
    FileIdFullDirectoryInformation = 38,
    FileValidDataLengthInformation = 39,
    FileShortNameInformation = 40,
    FileIoCompletionNotificationInformation = 41,
    FileIoStatusBlockRangeInformation = 42,
    FileIoPriorityHintInformation = 43,
    FileSfioReserveInformation = 44,
    FileSfioVolumeInformation = 45,
    FileHardLinkInformation = 46,
    FileProcessIdsUsingFileInformation = 47,
    FileNormalizedNameInformation = 48,
    FileNetworkPhysicalNameInformation = 49,
    FileMaximumInformation = 50
};


#if !defined(_MY_NTLIB_) && !defined(_MY_NTLIB_DLL_)

/************************************************************************/
/* NTSTATUS                                                             */
/************************************************************************/
#include "nt_status.h"

//
// These must be converted to LUIDs before use.
//

#define SE_MIN_WELL_KNOWN_PRIVILEGE         (2L)
#define SE_CREATE_TOKEN_PRIVILEGE           (2L)
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE     (3L)
#define SE_LOCK_MEMORY_PRIVILEGE            (4L)
#define SE_INCREASE_QUOTA_PRIVILEGE         (5L)

#define SE_MACHINE_ACCOUNT_PRIVILEGE        (6L)
#define SE_TCB_PRIVILEGE                    (7L)
#define SE_SECURITY_PRIVILEGE               (8L)
#define SE_TAKE_OWNERSHIP_PRIVILEGE         (9L)
#define SE_LOAD_DRIVER_PRIVILEGE            (10L)
#define SE_SYSTEM_PROFILE_PRIVILEGE         (11L)
#define SE_SYSTEMTIME_PRIVILEGE             (12L)
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE    (13L)
#define SE_INC_BASE_PRIORITY_PRIVILEGE      (14L)
#define SE_CREATE_PAGEFILE_PRIVILEGE        (15L)
#define SE_CREATE_PERMANENT_PRIVILEGE       (16L)
#define SE_BACKUP_PRIVILEGE                 (17L)
#define SE_RESTORE_PRIVILEGE                (18L)
#define SE_SHUTDOWN_PRIVILEGE               (19L)
#define SE_DEBUG_PRIVILEGE                  (20L)
#define SE_AUDIT_PRIVILEGE                  (21L)
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE     (22L)
#define SE_CHANGE_NOTIFY_PRIVILEGE          (23L)
#define SE_REMOTE_SHUTDOWN_PRIVILEGE        (24L)
#define SE_UNDOCK_PRIVILEGE                 (25L)
#define SE_SYNC_AGENT_PRIVILEGE             (26L)
#define SE_ENABLE_DELEGATION_PRIVILEGE      (27L)
#define SE_MANAGE_VOLUME_PRIVILEGE          (28L)
#define SE_IMPERSONATE_PRIVILEGE            (29L)
#define SE_CREATE_GLOBAL_PRIVILEGE          (30L)
#define SE_TRUSTED_CREDMAN_ACCESS_PRIVILEGE (31L)
#define SE_RELABEL_PRIVILEGE                (32L)
#define SE_INC_WORKING_SET_PRIVILEGE        (33L)
#define SE_TIME_ZONE_PRIVILEGE              (34L)
#define SE_CREATE_SYMBOLIC_LINK_PRIVILEGE   (35L)
#define SE_MAX_WELL_KNOWN_PRIVILEGE         (SE_CREATE_SYMBOLIC_LINK_PRIVILEGE)


/************************************************************************/
/* string                                                               */
/************************************************************************/


typedef struct _STRING {
    USHORT Length;
    USHORT MaximumLength;
	PCHAR Buffer;
} STRING;

typedef STRING *PSTRING;
typedef STRING ANSI_STRING;
typedef PSTRING PANSI_STRING;

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWCH   Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

#ifdef __cplusplus
extern "C++"
{
char _RTL_CONSTANT_STRING_type_check(const char *s);
char _RTL_CONSTANT_STRING_type_check(const WCHAR *s);
// __typeof would be desirable here instead of sizeof.
template <size_t N> class _RTL_CONSTANT_STRING_remove_const_template_class;
template <> class _RTL_CONSTANT_STRING_remove_const_template_class<sizeof(char)>  {public: typedef  char T; };
template <> class _RTL_CONSTANT_STRING_remove_const_template_class<sizeof(WCHAR)> {public: typedef WCHAR T; };
#define _RTL_CONSTANT_STRING_remove_const_macro(s) \
    (const_cast<_RTL_CONSTANT_STRING_remove_const_template_class<sizeof((s)[0])>::T*>(s))
}
#else
char _RTL_CONSTANT_STRING_type_check(const void *s);
#define _RTL_CONSTANT_STRING_remove_const_macro(s) (s)
#endif
#define RTL_CONSTANT_STRING(s) \
{ \
    sizeof( s ) - sizeof( (s)[0] ), \
    sizeof( s ) / sizeof(_RTL_CONSTANT_STRING_type_check(s)), \
    _RTL_CONSTANT_STRING_remove_const_macro(s) \
}

#define MAXIMUM_LEADBYTES   12

typedef struct _CPTABLEINFO {
    USHORT CodePage;                    // code page number
    USHORT MaximumCharacterSize;        // max length (bytes) of a char
    USHORT DefaultChar;                 // default character (MB)
    USHORT UniDefaultChar;              // default character (Unicode)
    USHORT TransDefaultChar;            // translation of default char (Unicode)
    USHORT TransUniDefaultChar;         // translation of Unic default char (MB)
    USHORT DBCSCodePage;                // Non 0 for DBCS code pages
    UCHAR  LeadByte[MAXIMUM_LEADBYTES]; // lead byte ranges
    PUSHORT MultiByteTable;             // pointer to MB translation table
    PVOID   WideCharTable;              // pointer to WC translation table
    PUSHORT DBCSRanges;                 // pointer to DBCS ranges
    PUSHORT DBCSOffsets;                // pointer to DBCS offsets
} CPTABLEINFO, *PCPTABLEINFO;

typedef struct _NLSTABLEINFO {
    CPTABLEINFO OemTableInfo;
    CPTABLEINFO AnsiTableInfo;
    PUSHORT UpperCaseTable;             // 844 format upcase table
    PUSHORT LowerCaseTable;             // 844 format lower case table
} NLSTABLEINFO, *PNLSTABLEINFO;

typedef struct _OBJECT_ATTRIBUTES {
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
    PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;
typedef CONST OBJECT_ATTRIBUTES *PCOBJECT_ATTRIBUTES;

typedef enum _SECTION_INHERIT { ViewShare = 1, ViewUnmap = 2 } SECTION_INHERIT;

#ifndef OBJ_INHERIT
    #define OBJ_INHERIT             0x00000002L
    #define OBJ_PERMANENT           0x00000010L
    #define OBJ_EXCLUSIVE           0x00000020L
    #define OBJ_CASE_INSENSITIVE    0x00000040L
    #define OBJ_OPENIF              0x00000080L
    #define OBJ_OPENLINK            0x00000100L
    #define OBJ_KERNEL_HANDLE       0x00000200L
    #define OBJ_FORCE_ACCESS_CHECK  0x00000400L
    #define OBJ_VALID_ATTRIBUTES    0x000007F2L
#endif // OBJ_INHERIT

#ifndef InitializeObjectAttributes
    #define InitializeObjectAttributes( p, n, a, r, s ) { \
        (p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
        (p)->RootDirectory = r;                             \
        (p)->Attributes = a;                                \
        (p)->ObjectName = n;                                \
        (p)->SecurityDescriptor = s;                        \
        (p)->SecurityQualityOfService = NULL;               \
    }
#endif

/* Threads */
typedef struct _USER_STACK {
	PVOID  FixedStackBase;
	PVOID  FixedStackLimit;
	PVOID  ExpandableStackBase;
	PVOID  ExpandableStackLimit;
	PVOID  ExpandableStackBottom;
} USER_STACK, *PUSER_STACK;

typedef struct _CLIENT_ID {
	HANDLE  UniqueProcess;
	HANDLE  UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _INITIAL_TEB{ 	
	PVOID OldStabckBase;
	PVOID OldStackLimit;
	PVOID StackBase;
	PVOID StackLimit;
	PVOID StackAllocationBase;
} INITIAL_TEB, *PINITIAL_TEB;

typedef struct _PORT_MESSAGE
{
    union
    {
        struct
        {
            SHORT DataLength;
            SHORT TotalLength;
        } s1;
        ULONG Length;
    } u1;
    union
    {
        struct
        {
            SHORT Type;
            SHORT DataInfoOffset;
        } s2;
        ULONG ZeroInit;
    } u2;
    union
    {
        CLIENT_ID ClientId;
        double    DoNotUseThisField;
    };
    ULONG MessageId;
    union
    {
        SIZE_T ClientViewSize;
        ULONG CallbackId;
    };
} PORT_MESSAGE, *PPORT_MESSAGE;

typedef struct _CSR_CONNECTION_INFO
{
    ULONG Unknown[2];
    HANDLE ObjectDirectory;
    PVOID SharedSectionBase;
    PVOID SharedSectionHeap;
    PVOID SharedSectionData;
    ULONG DebugFlags;
    ULONG Unknown2[3];
    HANDLE ProcessId;
} CSR_CONNECTION_INFO, *PCSR_CONNECTION_INFO;

typedef struct _CSR_CLIENT_CONNECT
{
    ULONG ServerId;
    PVOID ConnectionInfo;
    ULONG ConnectionInfoSize;
} CSR_CLIENT_CONNECT, *PCSR_CLIENT_CONNECT;

typedef ULONG CSR_API_NUMBER;

typedef struct _CSR_API_MESSAGE
{
    PORT_MESSAGE Header;
    union
    {
        CSR_CONNECTION_INFO ConnectionInfo;
        struct
        {
            PVOID CsrCaptureData;
            CSR_API_NUMBER Opcode;
            ULONG Status;
            ULONG Reserved;
            union
            {
                CSR_CLIENT_CONNECT CsrClientConnect;
            };
        };
    };
} CSR_API_MESSAGE, *PCSR_API_MESSAGE;

typedef struct _CSR_CAPTURE_BUFFER
{
    ULONG Size;
    struct _CSR_CAPTURE_BUFFER *PreviousCaptureBuffer;
    ULONG PointerCount;
    ULONG_PTR BufferEnd;
} CSR_CAPTURE_BUFFER, *PCSR_CAPTURE_BUFFER;

#if 0
typedef struct _PEB {

    BOOLEAN                 InheritedAddressSpace;
    BOOLEAN                 ReadImageFileExecOptions;
    BOOLEAN                 BeingDebugged;
    BOOLEAN                 Spare;
    HANDLE                  Mutant;
    PVOID                   ImageBaseAddress;
    PPEB_LDR_DATA           LoaderData;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    PVOID                   SubSystemData;
    PVOID                   ProcessHeap;
    PVOID                   FastPebLock;
    PPEBLOCKROUTINE         FastPebLockRoutine;
    PPEBLOCKROUTINE         FastPebUnlockRoutine;
    ULONG                   EnvironmentUpdateCount;
    PPVOID                  KernelCallbackTable;
    PVOID                   EventLogSection;
    PVOID                   EventLog;
    PPEB_FREE_BLOCK         FreeList;
    ULONG                   TlsExpansionCounter;
    PVOID                   TlsBitmap;
    ULONG                   TlsBitmapBits[0x2];
    PVOID                   ReadOnlySharedMemoryBase;
    PVOID                   ReadOnlySharedMemoryHeap;
    PVOID                  *ReadOnlyStaticServerData;
    PVOID                   AnsiCodePageData;
    PVOID                   OemCodePageData;
    PVOID                   UnicodeCaseTableData;
    ULONG                   NumberOfProcessors;
    ULONG                   NtGlobalFlag;
    BYTE                    Spare2[0x4];
    LARGE_INTEGER           CriticalSectionTimeout;
    ULONG                   HeapSegmentReserve;
    ULONG                   HeapSegmentCommit;
    ULONG                   HeapDeCommitTotalFreeThreshold;
    ULONG                   HeapDeCommitFreeBlockThreshold;
    ULONG                   NumberOfHeaps;
    ULONG                   MaximumNumberOfHeaps;
    PVOID                 **ProcessHeaps;
    PVOID                   GdiSharedHandleTable;
    PVOID                   ProcessStarterHelper;
    PVOID                   GdiDCAttributeList;
    PVOID                   LoaderLock;
    ULONG                   OSMajorVersion;
    ULONG                   OSMinorVersion;
    ULONG                   OSBuildNumber;
    ULONG                   OSPlatformId;
    ULONG                   ImageSubSystem;
    ULONG                   ImageSubSystemMajorVersion;
    ULONG                   ImageSubSystemMinorVersion;
    ULONG                   GdiHandleBuffer[0x22];
    ULONG                   PostProcessInitRoutine;
    ULONG                   TlsExpansionBitmap;
    BYTE                    TlsExpansionBitmapBits[0x80];
    ULONG                   SessionId;
} PEB, *PPEB;
#else
//    typedef PVOID PPEB;
#endif

typedef struct _tagTEB
{
    NT_TIB                  Tib;
    PVOID                   EnvironmentPointer;
    CLIENT_ID               Cid;
    PVOID                   ActiveRpcInfo;
    PVOID                   ThreadLocalStoragePointer;
    PVOID                   ProcessEnvironmentBlock;
    ULONG                   LastErrorValue;
    ULONG                   CountOfOwnedCriticalSections;
    PVOID                   CsrClientThread;
    PVOID                   Win32ThreadInfo;
    ULONG                   Win32ClientInfo[0x1F];
    PVOID                   WOW32Reserved;
    ULONG                   CurrentLocale;
    ULONG                   FpSoftwareStatusRegister;
    PVOID                   SystemReserved1[0x36];
    PVOID                   Spare1;
    ULONG                   ExceptionCode;
    ULONG                   SpareBytes1[0x28];
    PVOID                   SystemReserved2[0xA];
    ULONG                   GdiRgn;
    ULONG                   GdiPen;
    ULONG                   GdiBrush;
    CLIENT_ID               RealClientId;
    PVOID                   GdiCachedProcessHandle;
    ULONG                   GdiClientPID;
    ULONG                   GdiClientTID;
    PVOID                   GdiThreadLocaleInfo;
    PVOID                   UserReserved[5];
    PVOID                   GlDispatchTable[0x118];
    ULONG                   GlReserved1[0x1A];
    PVOID                   GlReserved2;
    PVOID                   GlSectionInfo;
    PVOID                   GlSection;
    PVOID                   GlTable;
    PVOID                   GlCurrentRC;
    PVOID                   GlContext;
    NTSTATUS                LastStatusValue;
    UNICODE_STRING          StaticUnicodeString;
    WCHAR                   StaticUnicodeBuffer[0x105];
    PVOID                   DeallocationStack;
    PVOID                   TlsSlots[0x40];
    LIST_ENTRY              TlsLinks;
    PVOID                   Vdm;
    PVOID                   ReservedForNtRpc;
    PVOID                   DbgSsReserved[0x2];
    ULONG                   HardErrorDisabled;
    PVOID                   Instrumentation[0x10];
    PVOID                   WinSockData;
    ULONG                   GdiBatchCount;
    ULONG                   Spare2;
    ULONG                   Spare3;
    ULONG                   Spare4;
    PVOID                   ReservedForOle;
    ULONG                   WaitingOnLoaderLock;
    PVOID                   StackCommit;
    PVOID                   StackCommitMax;
    PVOID                   StackReserved;
} TEB, *PTEB;


/************************************************************************/
/* file                                                                 */
/************************************************************************/



/************************************************************************/
/* FILE FLAGS                                                           */
/************************************************************************/

//
// Define the access check value for any access
//
//
// The FILE_READ_ACCESS and FILE_WRITE_ACCESS constants are also defined in
// ntioapi.h as FILE_READ_DATA and FILE_WRITE_DATA. The values for these
// constants *MUST* always be in sync.
//
//
// FILE_SPECIAL_ACCESS is checked by the NT I/O system the same as FILE_ANY_ACCESS.
// The file systems, however, may add additional access checks for I/O and FS controls
// that use this value.
//

#define FILE_ANY_ACCESS                 0
#define FILE_SPECIAL_ACCESS    (FILE_ANY_ACCESS)
#define FILE_READ_ACCESS          ( 0x0001 )    // file & pipe
#define FILE_WRITE_ACCESS         ( 0x0002 )    // file & pipe



//
// Define access rights to files and directories
//

//
// The FILE_READ_DATA and FILE_WRITE_DATA constants are also defined in
// devioctl.h as FILE_READ_ACCESS and FILE_WRITE_ACCESS. The values for these
// constants *MUST* always be in sync.
// The values are redefined in devioctl.h because they must be available to
// both DOS and NT.
//

#define FILE_READ_DATA            ( 0x0001 )    // file & pipe
#define FILE_LIST_DIRECTORY       ( 0x0001 )    // directory

#define FILE_WRITE_DATA           ( 0x0002 )    // file & pipe
#define FILE_ADD_FILE             ( 0x0002 )    // directory

#define FILE_APPEND_DATA          ( 0x0004 )    // file
#define FILE_ADD_SUBDIRECTORY     ( 0x0004 )    // directory
#define FILE_CREATE_PIPE_INSTANCE ( 0x0004 )    // named pipe


#define FILE_READ_EA              ( 0x0008 )    // file & directory

#define FILE_WRITE_EA             ( 0x0010 )    // file & directory

#define FILE_EXECUTE              ( 0x0020 )    // file
#define FILE_TRAVERSE             ( 0x0020 )    // directory

#define FILE_DELETE_CHILD         ( 0x0040 )    // directory

#define FILE_READ_ATTRIBUTES      ( 0x0080 )    // all

#define FILE_WRITE_ATTRIBUTES     ( 0x0100 )    // all

#define FILE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)

#define FILE_GENERIC_READ         (STANDARD_RIGHTS_READ     |\
                                   FILE_READ_DATA           |\
                                   FILE_READ_ATTRIBUTES     |\
                                   FILE_READ_EA             |\
                                   SYNCHRONIZE)


#define FILE_GENERIC_WRITE        (STANDARD_RIGHTS_WRITE    |\
                                   FILE_WRITE_DATA          |\
                                   FILE_WRITE_ATTRIBUTES    |\
                                   FILE_WRITE_EA            |\
                                   FILE_APPEND_DATA         |\
                                   SYNCHRONIZE)


#define FILE_GENERIC_EXECUTE      (STANDARD_RIGHTS_EXECUTE  |\
                                   FILE_READ_ATTRIBUTES     |\
                                   FILE_EXECUTE             |\
                                   SYNCHRONIZE)




//
// Define share access rights to files and directories
//

#define FILE_SHARE_READ                 0x00000001  
#define FILE_SHARE_WRITE                0x00000002  
#define FILE_SHARE_DELETE               0x00000004  
#define FILE_SHARE_VALID_FLAGS          0x00000007

//
// Define the file attributes values
//
// Note:  0x00000008 is reserved for use for the old DOS VOLID (volume ID)
//        and is therefore not considered valid in NT.
//
// Note:  Note also that the order of these flags is set to allow both the
//        FAT and the Pinball File Systems to directly set the attributes
//        flags in attributes words without having to pick each flag out
//        individually.  The order of these flags should not be changed!
//

#define FILE_ATTRIBUTE_READONLY             0x00000001  
#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
//OLD DOS VOLID                             0x00000008

#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
#define FILE_ATTRIBUTE_DEVICE               0x00000040  
#define FILE_ATTRIBUTE_NORMAL               0x00000080  

#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  

#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000  
#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000  

#define FILE_ATTRIBUTE_VIRTUAL              0x00010000  

#define FILE_ATTRIBUTE_VALID_FLAGS          0x00007fb7
#define FILE_ATTRIBUTE_VALID_SET_FLAGS      0x000031a7

#define FILE_SUPERSEDE                  0x00000000
#define FILE_OPEN                       0x00000001
#define FILE_CREATE                     0x00000002
#define FILE_OPEN_IF                    0x00000003
#define FILE_OVERWRITE                  0x00000004
#define FILE_OVERWRITE_IF               0x00000005
#define FILE_MAXIMUM_DISPOSITION        0x00000005

//
// Define the create/open option flags
//

#define FILE_DIRECTORY_FILE                     0x00000001
#define FILE_WRITE_THROUGH                      0x00000002
#define FILE_SEQUENTIAL_ONLY                    0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING          0x00000008

#define FILE_SYNCHRONOUS_IO_ALERT               0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT            0x00000020
#define FILE_NON_DIRECTORY_FILE                 0x00000040
#define FILE_CREATE_TREE_CONNECTION             0x00000080

#define FILE_COMPLETE_IF_OPLOCKED               0x00000100
#define FILE_NO_EA_KNOWLEDGE                    0x00000200
#define FILE_OPEN_REMOTE_INSTANCE               0x00000400
#define FILE_RANDOM_ACCESS                      0x00000800

#define FILE_DELETE_ON_CLOSE                    0x00001000
#define FILE_OPEN_BY_FILE_ID                    0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT             0x00004000
#define FILE_NO_COMPRESSION                     0x00008000

#if (NTDDI_VERSION >= NTDDI_WIN7)
#define FILE_OPEN_REQUIRING_OPLOCK              0x00010000
#define FILE_DISALLOW_EXCLUSIVE                 0x00020000
#endif /* NTDDI_VERSION >= NTDDI_WIN7 */

#define FILE_RESERVE_OPFILTER                   0x00100000
#define FILE_OPEN_REPARSE_POINT                 0x00200000
#define FILE_OPEN_NO_RECALL                     0x00400000
#define FILE_OPEN_FOR_FREE_SPACE_QUERY          0x00800000


#define FILE_VALID_OPTION_FLAGS                 0x00ffffff
#define FILE_VALID_PIPE_OPTION_FLAGS            0x00000032
#define FILE_VALID_MAILSLOT_OPTION_FLAGS        0x00000032
#define FILE_VALID_SET_FLAGS                    0x00000036

//
// Define the I/O status information return values for NtCreateFile/NtOpenFile
//

#define FILE_SUPERSEDED                 0x00000000
#define FILE_OPENED                     0x00000001
#define FILE_CREATED                    0x00000002
#define FILE_OVERWRITTEN                0x00000003
#define FILE_EXISTS                     0x00000004
#define FILE_DOES_NOT_EXIST             0x00000005

//
// Define special ByteOffset parameters for read and write operations
//

#define FILE_WRITE_TO_END_OF_FILE       0xffffffff
#define FILE_USE_FILE_POINTER_POSITION  0xfffffffe

//
// Define alignment requirement values
//

#define FILE_BYTE_ALIGNMENT             0x00000000
#define FILE_WORD_ALIGNMENT             0x00000001
#define FILE_LONG_ALIGNMENT             0x00000003
#define FILE_QUAD_ALIGNMENT             0x00000007
#define FILE_OCTA_ALIGNMENT             0x0000000f
#define FILE_32_BYTE_ALIGNMENT          0x0000001f
#define FILE_64_BYTE_ALIGNMENT          0x0000003f
#define FILE_128_BYTE_ALIGNMENT         0x0000007f
#define FILE_256_BYTE_ALIGNMENT         0x000000ff
#define FILE_512_BYTE_ALIGNMENT         0x000001ff

//
// Define the maximum length of a filename string
//

#define MAXIMUM_FILENAME_LENGTH         256

//
// Define the various device characteristics flags
//

#define FILE_REMOVABLE_MEDIA                    0x00000001
#define FILE_READ_ONLY_DEVICE                   0x00000002
#define FILE_FLOPPY_DISKETTE                    0x00000004
#define FILE_WRITE_ONCE_MEDIA                   0x00000008
#define FILE_REMOTE_DEVICE                      0x00000010
#define FILE_DEVICE_IS_MOUNTED                  0x00000020
#define FILE_VIRTUAL_VOLUME                     0x00000040
#define FILE_AUTOGENERATED_DEVICE_NAME          0x00000080
#define FILE_DEVICE_SECURE_OPEN                 0x00000100
#define FILE_CHARACTERISTIC_PNP_DEVICE          0x00000800
#define FILE_CHARACTERISTIC_TS_DEVICE           0x00001000
#define FILE_CHARACTERISTIC_WEBDAV_DEVICE       0x00002000

typedef struct _FILE_BASIC_INFORMATION {
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    ULONG FileAttributes;
} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

typedef struct _FILE_EA_INFORMATION {
    ULONG EaSize;
} FILE_EA_INFORMATION, *PFILE_EA_INFORMATION;

typedef struct _FILE_POSITION_INFORMATION
{
    LARGE_INTEGER CurrentByteOffset;
} FILE_POSITION_INFORMATION, *PFILE_POSITION_INFORMATION;

typedef struct _FILE_END_OF_FILE_INFORMATION
{
    LARGE_INTEGER EndOfFile;
} FILE_END_OF_FILE_INFORMATION, *PFILE_END_OF_FILE_INFORMATION;

typedef struct _FILE_DISPOSITION_INFORMATION {
    BOOLEAN  DeleteFile;
} FILE_DISPOSITION_INFORMATION;

typedef struct _FILE_STANDARD_INFORMATION {
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG NumberOfLinks;
    BOOLEAN DeletePending;
    BOOLEAN Directory;
} FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;

typedef struct _FILE_ALLOCATION_INFORMATION {
    LARGE_INTEGER AllocationSize;
} FILE_ALLOCATION_INFORMATION, *PFILE_ALLOCATION_INFORMATION;

#ifndef FILE_BEGIN
    enum FILE_MOVE_METHOD { FILE_BEGIN, FILE_CURRENT, FILE_END };
#endif /* FILE_BEGIN */

typedef struct _IO_STATUS_BLOCK {
    union
    {
        NTSTATUS Status;
        PVOID Pointer;
    };
    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef
VOID
(NTAPI *PIO_APC_ROUTINE)(
    IN PVOID ApcContext,
    IN PIO_STATUS_BLOCK IoStatusBlock,
    IN ULONG Reserved
);

/************************************************************************/
/* memory                                                               */
/************************************************************************/
typedef
NTSTATUS
(NTAPI *PRTL_HEAP_COMMIT_ROUTINE)(
    IN     PVOID Base,
    IN OUT PVOID *CommitAddress,
    IN OUT PSIZE_T CommitSize
);

typedef struct _RTL_HEAP_PARAMETERS {
    ULONG Length;
    SIZE_T SegmentReserve;
    SIZE_T SegmentCommit;
    SIZE_T DeCommitFreeBlockThreshold;
    SIZE_T DeCommitTotalFreeThreshold;
    SIZE_T MaximumAllocationSize;
    SIZE_T VirtualMemoryThreshold;
    SIZE_T InitialCommit;
    SIZE_T InitialReserve;
    PRTL_HEAP_COMMIT_ROUTINE CommitRoutine;
    SIZE_T Reserved[ 2 ];
} RTL_HEAP_PARAMETERS, *PRTL_HEAP_PARAMETERS;

/************************************************************************/
/* others                                                               */
/************************************************************************/

#if !defined(NtCurrentProcess)
    #define NtCurrentProcess() (HANDLE)-1
#endif /* NtCurrentProcess */

#if !defined(NtCurrentThread)
    #define NtCurrentThread() (HANDLE)-2
#endif /* NtCurrentThread */

#ifndef NT_SUCCESS
    #define NT_SUCCESS(Status)  (((NTSTATUS)(Status)) >= 0)
#endif /* NT_SUCCESS */

#if !defined(RT_MESSAGETABLE)
    #define RT_MESSAGETABLE 0x0B
#endif

#else /* _MY_NTLIB_ */

#include <ntifs.h>
#include <ntdef.h>
#include <ntintsafe.h>

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE (HANDLE)-1
#endif /* INVALID_HANDLE_VALUE */

typedef void    *LPVOID;
typedef BYTE    *PBYTE;
typedef int      BOOL;
typedef WORD    *PWORD;
typedef DWORD   *LPDWORD, *PDWORD;
typedef HANDLE   HMODULE;
typedef HANDLE   HWND;
typedef struct _MESSAGE_RESOURCE_ENTRY
{
    WORD   Length;
    WORD   Flags;
    BYTE  Text[ 1 ];
} MESSAGE_RESOURCE_ENTRY, *PMESSAGE_RESOURCE_ENTRY;

typedef struct _COORD {
    SHORT X;
    SHORT Y;
} COORD, *PCOORD;

typedef struct _KEY_EVENT_RECORD {
    BOOL bKeyDown;
    WORD wRepeatCount;
    WORD wVirtualKeyCode;
    WORD wVirtualScanCode;
    union {
        WCHAR UnicodeChar;
        CHAR   AsciiChar;
    } uChar;
    DWORD dwControlKeyState;
} KEY_EVENT_RECORD, *PKEY_EVENT_RECORD;

typedef struct _MOUSE_EVENT_RECORD {
    COORD dwMousePosition;
    DWORD dwButtonState;
    DWORD dwControlKeyState;
    DWORD dwEventFlags;
} MOUSE_EVENT_RECORD, *PMOUSE_EVENT_RECORD;

typedef struct _WINDOW_BUFFER_SIZE_RECORD {
    COORD dwSize;
} WINDOW_BUFFER_SIZE_RECORD, *PWINDOW_BUFFER_SIZE_RECORD;

typedef struct _MENU_EVENT_RECORD {
    UINT dwCommandId;
} MENU_EVENT_RECORD, *PMENU_EVENT_RECORD;

typedef struct _FOCUS_EVENT_RECORD {
    BOOL bSetFocus;
} FOCUS_EVENT_RECORD, *PFOCUS_EVENT_RECORD;

typedef struct _INPUT_RECORD {
    WORD EventType;
    union {
        KEY_EVENT_RECORD KeyEvent;
        MOUSE_EVENT_RECORD MouseEvent;
        WINDOW_BUFFER_SIZE_RECORD WindowBufferSizeEvent;
        MENU_EVENT_RECORD MenuEvent;
        FOCUS_EVENT_RECORD FocusEvent;
    } Event;
} INPUT_RECORD, *PINPUT_RECORD;

typedef struct
{
    DWORD dwUnknown1;
    ULONG uKeMaximumIncrement;
    ULONG uPageSize;
    ULONG uMmNumberOfPhysicalPages;
    ULONG uMmLowestPhysicalPage;
    ULONG uMmHighestPhysicalPage;
    ULONG uAllocationGranularity;
    PVOID pLowestUserAddress;
    PVOID pMmHighestUserAddress;
    ULONG uKeActiveProcessors;
    BYTE  bKeNumberProcessors;
    BYTE  bUnknown2;
    WORD  wUnknown3;
} SYSTEM_BASIC_INFORMATION;

typedef struct
{
    LARGE_INTEGER liIdleTime;
    DWORD         dwSpare[76];
} SYSTEM_PERFORMANCE_INFORMATION;

typedef struct
{
    LARGE_INTEGER liKeBootTime;
    LARGE_INTEGER liKeSystemTime;
    LARGE_INTEGER liExpTimeZoneBias;
    ULONG         uCurrentTimeZoneId;
    DWORD         dwReserved;
} SYSTEM_TIME_INFORMATION;

#ifndef _SECURITY_ATTRIBUTES_
#define _SECURITY_ATTRIBUTES_
typedef struct _SECURITY_ATTRIBUTES
{
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} 	SECURITY_ATTRIBUTES;

typedef struct _SECURITY_ATTRIBUTES *PSECURITY_ATTRIBUTES;

typedef struct _SECURITY_ATTRIBUTES *LPSECURITY_ATTRIBUTES;

#endif // !_SECURITY_ATTRIBUTES_

//
//  EventType flags:
//

#define KEY_EVENT         0x0001 // Event contains key event record
#define MOUSE_EVENT       0x0002 // Event contains mouse event record
#define WINDOW_BUFFER_SIZE_EVENT 0x0004 // Event contains window change event record
#define MENU_EVENT 0x0008 // Event contains menu event record
#define FOCUS_EVENT 0x0010 // event contains focus change

#endif /* _MY_NTLIB_ */

#pragma pack()
#pragma warning(default:4201)

#endif /* _NT_DEFS_H_ */
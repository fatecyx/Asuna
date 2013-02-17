#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <winsock2.h>
#include "my_headers.h"

#undef WINSOCK_API_LINKAGE
#define WINSOCK_API_LINKAGE
#undef WSPAPI
#define WSPAPI __stdcall
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x700

_MY_C_HEAD_

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
__checkReturn
SOCKET
WSAAPI
accept(
    __in SOCKET s,
    __out_bcount_opt(*addrlen) struct sockaddr FAR * addr,
    __inout_opt int FAR * addrlen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
__checkReturn
SOCKET
(WSAAPI * LPFN_ACCEPT)(
    __in SOCKET s,
    __out_bcount_opt(*addrlen) struct sockaddr FAR * addr,
    __inout_opt int FAR * addrlen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
bind(
    __in SOCKET s,
    __in_bcount(namelen) const struct sockaddr FAR * name,
    __in int namelen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_BIND)(
    __in SOCKET s,
    __in_bcount(namelen) const struct sockaddr FAR * name,
    __in int namelen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
closesocket(
    __in SOCKET s
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_CLOSESOCKET)(
    __in SOCKET s
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
connect(
    __in SOCKET s,
    __in_bcount(namelen) const struct sockaddr FAR * name,
    __in int namelen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_CONNECT)(
    __in SOCKET s,
    __in_bcount(namelen) const struct sockaddr FAR * name,
    __in int namelen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
ioctlsocket(
    __in SOCKET s,
    __in long cmd,
    __inout u_long FAR * argp
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_IOCTLSOCKET)(
    __in SOCKET s,
    __in long cmd,
    __inout u_long FAR * argp
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
getpeername(
    __in SOCKET s,
    __out_bcount_part(*namelen,*namelen) struct sockaddr FAR * name,
    __inout int FAR * namelen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_GETPEERNAME)(
    __in SOCKET s,
    __out_bcount_part(*namelen,*namelen) struct sockaddr FAR * name,
    __inout int FAR * namelen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
getsockname(
    __in SOCKET s,
    __out_bcount_part(*namelen,*namelen) struct sockaddr FAR * name,
    __inout int FAR * namelen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_GETSOCKNAME)(
    __in SOCKET s,
    __out_bcount_part(*namelen,*namelen) struct sockaddr FAR * name,
    __inout int FAR * namelen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
getsockopt(
    __in SOCKET s,
    __in int level,
    __in int optname,
    __out_bcount(*optlen) char FAR * optval,
    __inout int FAR * optlen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_GETSOCKOPT)(
    __in SOCKET s,
    __in int level,
    __in int optname,
    __out_bcount(*optlen) char FAR * optval,
    __inout int FAR * optlen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
u_long
WSAAPI
htonl(
    __in u_long hostlong
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
u_long
(WSAAPI * LPFN_HTONL)(
    __in u_long hostlong
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
u_short
WSAAPI
htons(
    __in u_short hostshort
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
u_short
(WSAAPI * LPFN_HTONS)(
    __in u_short hostshort
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
unsigned long
WSAAPI
inet_addr(
    __in IN const char FAR * cp
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
unsigned long
(WSAAPI * LPFN_INET_ADDR)(
    __in const char FAR * cp
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
char FAR *
WSAAPI
inet_ntoa(
    __in struct in_addr in
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
char FAR *
(WSAAPI * LPFN_INET_NTOA)(
    __in struct in_addr in
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
listen(
    __in SOCKET s,
    __in int backlog
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_LISTEN)(
    __in SOCKET s,
    __in int backlog
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
u_long
WSAAPI
ntohl(
    __in u_long netlong
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
u_long
(WSAAPI * LPFN_NTOHL)(
    __in u_long netlong
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
u_short
WSAAPI
ntohs(
    __in u_short netshort
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
u_short
(WSAAPI * LPFN_NTOHS)(
    __in u_short netshort
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
recv(
    __in SOCKET s,
    __out_bcount_part(len, return) __out_data_source(NETWORK) char FAR * buf,
    __in int len,
    __in int flags
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_RECV)(
    __in SOCKET s,
    __out_bcount_part(len, return) char FAR * buf,
    __in int len,
    __in int flags
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
int
WSAAPI
recvfrom(
    __in SOCKET s,
    __out_bcount_part(len, return) __out_data_source(NETWORK) char FAR * buf,
    __in int len,
    __in int flags,
    __out_bcount_part_opt(*fromlen, *fromlen) struct sockaddr FAR * from,
    __inout_opt int FAR * fromlen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_RECVFROM)(
    __in SOCKET s,
    __out_bcount_part(len, return) char FAR * buf,
    __in int len,
    __in int flags,
    __out_bcount_part_opt(*fromlen, *fromlen) struct sockaddr FAR * from,
    __inout_opt int FAR * fromlen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
select(
    __in int nfds,
    __inout_opt fd_set FAR * readfds,
    __inout_opt fd_set FAR * writefds,
    __inout_opt fd_set FAR * exceptfds,
    __in_opt const struct timeval FAR * timeout
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_SELECT)(
    __in int nfds,
    __inout_opt fd_set FAR * readfds,
    __inout_opt fd_set FAR * writefds,
    __inout_opt fd_set FAR *exceptfds,
    __in_opt const struct timeval FAR * timeout
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
send(
    __in SOCKET s,
    __in_bcount(len) const char FAR * buf,
    __in int len,
    __in int flags
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_SEND)(
    __in SOCKET s,
    __in_bcount(len) const char FAR * buf,
    __in int len,
    __in int flags
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
sendto(
    __in SOCKET s,
    __in_bcount(len) const char FAR * buf,
    __in int len,
    __in int flags,
    __in_bcount(tolen) const struct sockaddr FAR * to,
    __in int tolen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_SENDTO)(
    __in SOCKET s,
    __in_bcount(len) const char FAR * buf,
    __in int len,
    __in int flags,
    __in_bcount(tolen) const struct sockaddr FAR * to,
    __in int tolen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
setsockopt(
    __in SOCKET s,
    __in int level,
    __in int optname,
    __in_bcount_opt(optlen) const char FAR * optval,
    __in int optlen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_SETSOCKOPT)(
    __in SOCKET s,
    __in int level,
    __in int optname,
    __in_bcount(optlen) const char FAR * optval,
    __in int optlen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
shutdown(
    __in SOCKET s,
    __in int how
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_SHUTDOWN)(
    __in SOCKET s,
    __in int how
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
__checkReturn
SOCKET
WSAAPI
socket(
    __in int af,
    __in int type,
    __in int protocol
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
__checkReturn
SOCKET
(WSAAPI * LPFN_SOCKET)(
    __in int af,
    __in int type,
    __in int protocol
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

/* Database function prototypes */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
struct hostent FAR *
WSAAPI
gethostbyaddr(
    __in_bcount(len) const char FAR * addr,
    __in int len,
    __in int type
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
struct hostent FAR *
(WSAAPI * LPFN_GETHOSTBYADDR)(
    __in_bcount(len) const char FAR * addr,
    __in int len,
    __in int type
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
struct hostent FAR *
WSAAPI
gethostbyname(
    __in const char FAR * name
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
struct hostent FAR *
(WSAAPI * LPFN_GETHOSTBYNAME)(
    __in const char FAR * name
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
gethostname(
    __out_bcount(namelen) char FAR * name,
    __in int namelen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_GETHOSTNAME)(
    __out_bcount(namelen) char FAR * name,
    __in int namelen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
struct servent FAR *
WSAAPI
getservbyport(
    __in int port,
    __in_z const char FAR * proto
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
struct servent FAR *
(WSAAPI * LPFN_GETSERVBYPORT)(
    __in int port,
    __in_z const char FAR * proto
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
struct servent FAR *
WSAAPI
getservbyname(
    __in_z const char FAR * name,
    __in_z const char FAR * proto
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
struct servent FAR *
(WSAAPI * LPFN_GETSERVBYNAME)(
    __in_z const char FAR * name,
    __in_z const char FAR * proto
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
struct protoent FAR *
WSAAPI
getprotobynumber(
    __in int number
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
struct protoent FAR *
(WSAAPI * LPFN_GETPROTOBYNUMBER)(
    __in int number
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
struct protoent FAR *
WSAAPI
getprotobyname(
    __in_z const char FAR * name
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
struct protoent FAR *
(WSAAPI * LPFN_GETPROTOBYNAME)(
    __in_z const char FAR * name
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

/* Microsoft Windows Extension function prototypes */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
__checkReturn
int
WSAAPI
WSAStartup(
    __in WORD wVersionRequested,
    __out LPWSADATA lpWSAData
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
__checkReturn
int
(WSAAPI * LPFN_WSASTARTUP)(
    __in WORD wVersionRequested,
    __out LPWSADATA lpWSAData
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSACleanup(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSACLEANUP)(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
void
WSAAPI
WSASetLastError(
    __in int iError
    ){ }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
void
(WSAAPI * LPFN_WSASETLASTERROR)(
    int iError
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSAGetLastError(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSAGETLASTERROR)(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
BOOL
WSAAPI
WSAIsBlocking(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
BOOL
(WSAAPI * LPFN_WSAISBLOCKING)(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSAUnhookBlockingHook(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSAUNHOOKBLOCKINGHOOK)(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
FARPROC
WSAAPI
WSASetBlockingHook(
    __in FARPROC lpBlockFunc
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
FARPROC
(WSAAPI * LPFN_WSASETBLOCKINGHOOK)(
    __in FARPROC lpBlockFunc
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSACancelBlockingCall(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSACANCELBLOCKINGCALL)(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
HANDLE
WSAAPI
WSAAsyncGetServByName(
    __in HWND hWnd,
    __in u_int wMsg,
    __in const char FAR * name,
    __in const char FAR * proto,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
HANDLE
(WSAAPI * LPFN_WSAASYNCGETSERVBYNAME)(
    __in HWND hWnd,
    __in u_int wMsg,
    __in const char FAR * name,
    __in const char FAR * proto,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
HANDLE
WSAAPI
WSAAsyncGetServByPort(
    __in HWND hWnd,
    __in u_int wMsg,
    __in int port,
    __in const char FAR * proto,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
HANDLE
(WSAAPI * LPFN_WSAASYNCGETSERVBYPORT)(
    __in HWND hWnd,
    __in u_int wMsg,
    __in int port,
    __in const char FAR * proto,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
HANDLE
WSAAPI
WSAAsyncGetProtoByName(
    __in HWND hWnd,
    __in u_int wMsg,
    __in const char FAR * name,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
HANDLE
(WSAAPI * LPFN_WSAASYNCGETPROTOBYNAME)(
    __in HWND hWnd,
    __in u_int wMsg,
    __in const char FAR * name,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
HANDLE
WSAAPI
WSAAsyncGetProtoByNumber(
    __in HWND hWnd,
    __in u_int wMsg,
    __in int number,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
HANDLE
(WSAAPI * LPFN_WSAASYNCGETPROTOBYNUMBER)(
    __in HWND hWnd,
    __in u_int wMsg,
    __in int number,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
HANDLE
WSAAPI
WSAAsyncGetHostByName(
    __in HWND hWnd,
    __in u_int wMsg,
    __in const char FAR * name,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
HANDLE
(WSAAPI * LPFN_WSAASYNCGETHOSTBYNAME)(
    __in HWND hWnd,
    __in u_int wMsg,
    __in const char FAR * name,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
HANDLE
WSAAPI
WSAAsyncGetHostByAddr(
    __in HWND hWnd,
    __in u_int wMsg,
    __in_bcount(len) const char FAR * addr,
    __in int len,
    __in int type,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
HANDLE
(WSAAPI * LPFN_WSAASYNCGETHOSTBYADDR)(
    __in HWND hWnd,
    __in u_int wMsg,
    __in_bcount(len) const char FAR * addr,
    __in int len,
    __in int type,
    __out_bcount(buflen) char FAR * buf,
    __in int buflen
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
int
WSAAPI
WSACancelAsyncRequest(
    __in HANDLE hAsyncTaskHandle
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSACANCELASYNCREQUEST)(
    __in HANDLE hAsyncTaskHandle
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
int
WSAAPI
WSAAsyncSelect(
    __in SOCKET s,
    __in HWND hWnd,
    __in u_int wMsg,
    __in long lEvent
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSAASYNCSELECT)(
    __in SOCKET s,
    __in HWND hWnd,
    __in u_int wMsg,
    __in long lEvent
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

/* WinSock 2 API new function prototypes */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
__checkReturn
SOCKET
WSAAPI
WSAAccept(
    __in SOCKET s,
    __out_bcount_part_opt(*addrlen,*addrlen) struct sockaddr FAR * addr,
    __inout_opt LPINT addrlen,
    __in_opt LPCONDITIONPROC lpfnCondition,
    __in_opt DWORD_PTR dwCallbackData
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
__checkReturn
SOCKET
(WSAAPI * LPFN_WSAACCEPT)(
    __in SOCKET s,
    __out_bcount_part_opt(*addrlen,*addrlen) struct sockaddr FAR * addr,
    __inout_opt LPINT addrlen,
    __in_opt LPCONDITIONPROC lpfnCondition,
    __in_opt DWORD_PTR dwCallbackData
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
BOOL
WSAAPI
WSACloseEvent(
    __in WSAEVENT hEvent
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
BOOL
(WSAAPI * LPFN_WSACLOSEEVENT)(
    __in WSAEVENT hEvent
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSAConnect(
    __in SOCKET s,
    __in_bcount(namelen) const struct sockaddr FAR * name,
    __in int namelen,
    __in_opt LPWSABUF lpCallerData,
    __out_opt LPWSABUF lpCalleeData,
    __in_opt LPQOS lpSQOS,
    __in_opt LPQOS lpGQOS
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_PROTOTYPES

#ifdef UNICODE
#define WSAConnectByName    WSAConnectByNameW
#else
#define WSAConnectByName    WSAConnectByNameA
#endif


__data_entrypoint(Network)
BOOL
PASCAL
WSAConnectByNameW(
    __in SOCKET s,
    __in_z LPWSTR nodename,
    __in_z LPWSTR servicename,
    __inout LPDWORD LocalAddressLength,
    __out_bcount_part(*LocalAddressLength,*LocalAddressLength) LPSOCKADDR LocalAddress,
    __inout LPDWORD RemoteAddressLength,
    __out_bcount_part(*RemoteAddressLength,*RemoteAddressLength) LPSOCKADDR RemoteAddress,
    __in const struct timeval * timeout,
    __in_opt LPWSAOVERLAPPED Reserved){ return 0; }


__data_entrypoint(Network)
BOOL
PASCAL
WSAConnectByNameA(
    __in SOCKET s,
    __in_z LPCSTR nodename,
    __in_z LPCSTR servicename,
    __inout LPDWORD LocalAddressLength,
    __out_bcount_part(*LocalAddressLength,*LocalAddressLength) LPSOCKADDR LocalAddress,
    __inout LPDWORD RemoteAddressLength,
    __out_bcount_part(*RemoteAddressLength,*RemoteAddressLength) LPSOCKADDR RemoteAddress,
    __in const struct timeval * timeout,
    __in_opt LPWSAOVERLAPPED Reserved){ return 0; }


__data_entrypoint(Network)
BOOL
PASCAL
WSAConnectByList(
    __in SOCKET s,
    __in PSOCKET_ADDRESS_LIST SocketAddress,
    __inout LPDWORD LocalAddressLength,
    __out_bcount_part(*LocalAddressLength,*LocalAddressLength) LPSOCKADDR LocalAddress,
    __inout LPDWORD RemoteAddressLength,
    __out_bcount_part(*RemoteAddressLength,*RemoteAddressLength) LPSOCKADDR RemoteAddress,
    __in const struct timeval * timeout,
    __in_opt LPWSAOVERLAPPED Reserved){ return 0; }
#endif

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSACONNECT)(
    __in SOCKET s,
    __in_bcount(namelen) const struct sockaddr FAR * name,
    __in int namelen,
    __in_opt LPWSABUF lpCallerData,
    __out_opt LPWSABUF lpCalleeData,
    __in_opt LPQOS lpSQOS,
    __in_opt LPQOS lpGQOS
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
WSAEVENT
WSAAPI
WSACreateEvent(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
WSAEVENT
(WSAAPI * LPFN_WSACREATEEVENT)(
    void
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
int
WSAAPI
WSADuplicateSocketA(
    __in SOCKET s,
    __in DWORD dwProcessId,
    __out LPWSAPROTOCOL_INFOA lpProtocolInfo
    ){ return 0; }

WINSOCK_API_LINKAGE
int
WSAAPI
WSADuplicateSocketW(
    __in SOCKET s,
    __in DWORD dwProcessId,
    __out LPWSAPROTOCOL_INFOW lpProtocolInfo
    ){ return 0; }
#ifdef UNICODE
#define WSADuplicateSocket  WSADuplicateSocketW
#else
#define WSADuplicateSocket  WSADuplicateSocketA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSADUPLICATESOCKETA)(
    __in SOCKET s,
    __in DWORD dwProcessId,
    __out LPWSAPROTOCOL_INFOA lpProtocolInfo
    ){ return 0; }
typedef
int
(WSAAPI * LPFN_WSADUPLICATESOCKETW)(
    __in SOCKET s,
    __in DWORD dwProcessId,
    __out LPWSAPROTOCOL_INFOW lpProtocolInfo
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSADUPLICATESOCKET  LPFN_WSADUPLICATESOCKETW
#else
#define LPFN_WSADUPLICATESOCKET  LPFN_WSADUPLICATESOCKETA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
int
WSAAPI
WSAEnumNetworkEvents(
    __in SOCKET s,
    __in WSAEVENT hEventObject,
    __out LPWSANETWORKEVENTS lpNetworkEvents
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSAENUMNETWORKEVENTS)(
    __in SOCKET s,
    __in WSAEVENT hEventObject,
    __out LPWSANETWORKEVENTS lpNetworkEvents
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSAEnumProtocolsA(
    __in_opt LPINT lpiProtocols,
    __out_bcount_part_opt(*lpdwBufferLength,*lpdwBufferLength) LPWSAPROTOCOL_INFOA lpProtocolBuffer,
    __inout LPDWORD lpdwBufferLength
    ){ return 0; }
WINSOCK_API_LINKAGE
int
WSAAPI
WSAEnumProtocolsW(
    __in_opt LPINT lpiProtocols,
    __out_bcount_part_opt(*lpdwBufferLength,*lpdwBufferLength) LPWSAPROTOCOL_INFOW lpProtocolBuffer,
    __inout LPDWORD lpdwBufferLength
    ){ return 0; }
#ifdef UNICODE
#define WSAEnumProtocols  WSAEnumProtocolsW
#else
#define WSAEnumProtocols  WSAEnumProtocolsA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSAENUMPROTOCOLSA)(
    __in_opt LPINT lpiProtocols,
    __out_bcount_part_opt(*lpdwBufferLength,*lpdwBufferLength) LPWSAPROTOCOL_INFOA lpProtocolBuffer,
    __inout LPDWORD lpdwBufferLength
    ){ return 0; }
typedef
int
(WSAAPI * LPFN_WSAENUMPROTOCOLSW)(
    __in_opt LPINT lpiProtocols,
    __out_bcount_part_opt(*lpdwBufferLength,*lpdwBufferLength) LPWSAPROTOCOL_INFOW lpProtocolBuffer,
    __inout LPDWORD lpdwBufferLength
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSAENUMPROTOCOLS  LPFN_WSAENUMPROTOCOLSW
#else
#define LPFN_WSAENUMPROTOCOLS  LPFN_WSAENUMPROTOCOLSA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSAEventSelect(
    __in SOCKET s,
    __in WSAEVENT hEventObject,
    __in long lNetworkEvents
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSAEVENTSELECT)(
    __in SOCKET s,
    __in WSAEVENT hEventObject,
    __in long lNetworkEvents
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
BOOL
WSAAPI
WSAGetOverlappedResult(
    __in SOCKET s,
    __in LPWSAOVERLAPPED lpOverlapped,
    __out LPDWORD lpcbTransfer,
    __in BOOL fWait,
    __out LPDWORD lpdwFlags
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
BOOL
(WSAAPI * LPFN_WSAGETOVERLAPPEDRESULT)(
    __in SOCKET s,
    __in LPWSAOVERLAPPED lpOverlapped,
    __out LPDWORD lpcbTransfer,
    __in BOOL fWait,
    __out LPDWORD lpdwFlags
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
BOOL
WSAAPI
WSAGetQOSByName(
    __in SOCKET s,
    __in LPWSABUF lpQOSName,
    __out LPQOS lpQOS
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
BOOL
(WSAAPI * LPFN_WSAGETQOSBYNAME)(
    __in SOCKET s,
    __in LPWSABUF lpQOSName,
    __out LPQOS lpQOS
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
int
WSAAPI
WSAHtonl(
    __in IN SOCKET s,
    __in IN u_long hostlong,
    __out OUT u_long FAR * lpnetlong
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSAHTONL)(
    __in SOCKET s,
    __in u_long hostlong,
    __out u_long FAR * lpnetlong
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
int
WSAAPI
WSAHtons(
    __in IN SOCKET s,
    __in IN u_short hostshort,
    __out OUT u_short FAR * lpnetshort
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSAHTONS)(
    __in SOCKET s,
    __in u_short hostshort,
    __out u_short FAR * lpnetshort
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
int
WSAAPI
WSAIoctl(
    __in SOCKET s,
    __in DWORD dwIoControlCode,
    __in_bcount_opt(cbInBuffer) LPVOID lpvInBuffer,
    __in DWORD cbInBuffer,
    __out_bcount_part_opt(cbOutBuffer, *lpcbBytesReturned) LPVOID lpvOutBuffer,
    __in DWORD cbOutBuffer,
    __out LPDWORD lpcbBytesReturned,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSAIOCTL)(
    __in SOCKET s,
    __in DWORD dwIoControlCode,
    __in_bcount_opt(cbInBuffer) LPVOID lpvInBuffer,
    __in DWORD cbInBuffer,
    __out_bcount_part_opt(cbOutBuffer, *lpcbBytesReturned) LPVOID lpvOutBuffer,
    __in DWORD cbOutBuffer,
    __out LPDWORD lpcbBytesReturned,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
SOCKET
WSAAPI
WSAJoinLeaf(
    __in SOCKET s,
    __in_bcount(namelen) const struct sockaddr FAR * name,
    __in int namelen,
    __in_opt LPWSABUF lpCallerData,
    __out_opt LPWSABUF lpCalleeData,
    __in_opt LPQOS lpSQOS,
    __in_opt LPQOS lpGQOS,
    __in DWORD dwFlags
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
SOCKET
(WSAAPI * LPFN_WSAJOINLEAF)(
    __in SOCKET s,
    __in_bcount(namelen) const struct sockaddr FAR * name,
    __in int namelen,
    __in_opt LPWSABUF lpCallerData,
    __out_opt LPWSABUF lpCalleeData,
    __in_opt LPQOS lpSQOS,
    __in_opt LPQOS lpGQOS,
    __in DWORD dwFlags
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
int
WSAAPI
WSANtohl(
    __in SOCKET s,
    __in u_long netlong,
    __out u_long FAR * lphostlong
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSANTOHL)(
    __in SOCKET s,
    __in u_long netlong,
    __out u_long FAR * lphostlong
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
int
WSAAPI
WSANtohs(
    __in SOCKET s,
    __in u_short netshort,
    __out u_short FAR * lphostshort
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSANTOHS)(
    __in SOCKET s,
    __in u_short netshort,
    __out u_short FAR * lphostshort
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSARecv(
    __in SOCKET s,
    __in_ecount(dwBufferCount) __out_data_source(NETWORK) LPWSABUF lpBuffers,
    __in DWORD dwBufferCount,
    __out_opt LPDWORD lpNumberOfBytesRecvd,
    __inout LPDWORD lpFlags,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSARECV)(
    __in SOCKET s,
    __in_ecount(dwBufferCount) LPWSABUF lpBuffers,
    __in DWORD dwBufferCount,
    __out_opt LPDWORD lpNumberOfBytesRecvd,
    __inout LPDWORD lpFlags,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSARecvDisconnect(
    __in SOCKET s,
    __in_opt __out_data_source(NETWORK) LPWSABUF lpInboundDisconnectData
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSARECVDISCONNECT)(
    __in SOCKET s,
    __out_data_source(NETWORK) LPWSABUF lpInboundDisconnectData
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSARecvFrom(
    __in SOCKET s,
    __in_ecount(dwBufferCount) __out_data_source(NETWORK) LPWSABUF lpBuffers,
    __in DWORD dwBufferCount,
    __out_opt LPDWORD lpNumberOfBytesRecvd,
    __inout LPDWORD lpFlags,
    __out_bcount_part_opt(*lpFromlen,*lpFromlen) struct sockaddr FAR * lpFrom,
    __inout_opt LPINT lpFromlen,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSARECVFROM)(
    __in SOCKET s,
    __in_ecount(dwBufferCount) LPWSABUF lpBuffers,
    __in DWORD dwBufferCount,
    __out_opt LPDWORD lpNumberOfBytesRecvd,
    __inout LPDWORD lpFlags,
    __out_bcount_part_opt(*lpFromlen,*lpFromLen) struct sockaddr FAR * lpFrom,
    __inout_opt LPINT lpFromlen,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
BOOL
WSAAPI
WSAResetEvent(
    __in WSAEVENT hEvent
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
BOOL
(WSAAPI * LPFN_WSARESETEVENT)(
    __in WSAEVENT hEvent
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSASend(
    __in SOCKET s,
    __in_ecount(dwBufferCount) LPWSABUF lpBuffers,
    __in DWORD dwBufferCount,
    __out_opt LPDWORD lpNumberOfBytesSent,
    __in DWORD dwFlags,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSASEND)(
    __in SOCKET s,
    __in_ecount(dwBufferCount) LPWSABUF lpBuffers,
    __in DWORD dwBufferCount,
    __out_opt LPDWORD lpNumberOfBytesSent,
    __in  DWORD dwFlags,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if(_WIN32_WINNT >= 0x0600)
#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int 
WSAAPI 
WSASendMsg(
    __in SOCKET Handle,
    __in LPWSAMSG lpMsg,
    __in DWORD dwFlags,
    __out_opt LPDWORD lpNumberOfBytesSent,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */
#endif // (_WIN32_WINNT >= 0x0600)

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
int
WSAAPI
WSASendDisconnect(
    __in SOCKET s,
    __in_opt LPWSABUF lpOutboundDisconnectData
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSASENDDISCONNECT)(
    __in SOCKET s,
    __in_opt LPWSABUF lpOutboundDisconnectData
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
int
WSAAPI
WSASendTo(
    __in SOCKET s,
    __in_ecount(dwBufferCount) LPWSABUF lpBuffers,
    __in DWORD dwBufferCount,
    __out_opt LPDWORD lpNumberOfBytesSent,
    __in DWORD dwFlags,
    __in_bcount_opt(iTolen) const struct sockaddr FAR * lpTo,
    __in int iTolen,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
int
(WSAAPI * LPFN_WSASENDTO)(
    __in SOCKET s,
    __in_ecount(dwBufferCount) LPWSABUF lpBuffers,
    __in DWORD dwBufferCount,
    __out_opt LPDWORD lpNumberOfBytesSent,
    __in DWORD dwFlags,
    __in_bcount_opt(iTolen) const struct sockaddr FAR * lpTo,
    __in int iTolen,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
BOOL
WSAAPI
WSASetEvent(
    __in WSAEVENT hEvent
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
BOOL
(WSAAPI * LPFN_WSASETEVENT)(
    __in WSAEVENT hEvent
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
__checkReturn
SOCKET
WSAAPI
WSASocketA(
    __in int af,
    __in int type,
    __in int protocol,
    __in_opt LPWSAPROTOCOL_INFOA lpProtocolInfo,
    __in GROUP g,
    __in DWORD dwFlags
    ){ return 0; }


WINSOCK_API_LINKAGE
__checkReturn
SOCKET
WSAAPI
WSASocketW(
    __in int af,
    __in int type,
    __in int protocol,
    __in_opt LPWSAPROTOCOL_INFOW lpProtocolInfo,
    __in GROUP g,
    __in DWORD dwFlags
    ){ return 0; }
#ifdef UNICODE
#define WSASocket  WSASocketW
#else
#define WSASocket  WSASocketA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
__checkReturn
SOCKET
(WSAAPI * LPFN_WSASOCKETA)(
    __in int af,
    __in int type,
    __in int protocol,
    __in_opt LPWSAPROTOCOL_INFOA lpProtocolInfo,
    __in GROUP g,
    __in DWORD dwFlags
    ){ return 0; }

typedef
__checkReturn
SOCKET
(WSAAPI * LPFN_WSASOCKETW)(
    __in int af,
    __in int type,
    __in int protocol,
    __in_opt LPWSAPROTOCOL_INFOW lpProtocolInfo,
    __in GROUP g,
    __in DWORD dwFlags
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSASOCKET  LPFN_WSASOCKETW
#else
#define LPFN_WSASOCKET  LPFN_WSASOCKETA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
DWORD
WSAAPI
WSAWaitForMultipleEvents(
    __in DWORD cEvents,
    __in_ecount(cEvents) const WSAEVENT FAR * lphEvents,
    __in BOOL fWaitAll,
    __in DWORD dwTimeout,
    __in BOOL fAlertable
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
DWORD
(WSAAPI * LPFN_WSAWAITFORMULTIPLEEVENTS)(
    __in DWORD cEvents,
    __in_ecount(cEvents) const WSAEVENT FAR * lphEvents,
    __in BOOL fWaitAll,
    __in DWORD dwTimeout,
    __in BOOL fAlertable
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
INT
WSAAPI
WSAAddressToStringA(
    __in_bcount(dwAddressLength) LPSOCKADDR lpsaAddress,
    __in     DWORD               dwAddressLength,
    __in_opt LPWSAPROTOCOL_INFOA lpProtocolInfo,
    __out_ecount_part(*lpdwAddressStringLength,*lpdwAddressStringLength) LPSTR lpszAddressString,
    __inout  LPDWORD             lpdwAddressStringLength
    ){ return 0; }
WINSOCK_API_LINKAGE
INT
WSAAPI
WSAAddressToStringW(
    __in_bcount(dwAddressLength) LPSOCKADDR lpsaAddress,
    __in     DWORD               dwAddressLength,
    __in_opt LPWSAPROTOCOL_INFOW lpProtocolInfo,
    __out_ecount_part(*lpdwAddressStringLength,*lpdwAddressStringLength) LPWSTR lpszAddressString,
    __inout  LPDWORD             lpdwAddressStringLength
    ){ return 0; }
#ifdef UNICODE
#define WSAAddressToString  WSAAddressToStringW
#else
#define WSAAddressToString  WSAAddressToStringA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSAADDRESSTOSTRINGA)(
    __in_bcount(dwAddressLength) LPSOCKADDR lpsaAddress,
    __in     DWORD               dwAddressLength,
    __in_opt LPWSAPROTOCOL_INFOA lpProtocolInfo,
    __out_ecount_part(*lpdwAddressStringLength,*lpdwAddressStringLength) LPSTR lpszAddressString,
    __inout  LPDWORD             lpdwAddressStringLength
    ){ return 0; }
typedef
INT
(WSAAPI * LPFN_WSAADDRESSTOSTRINGW)(
    __in_bcount(dwAddressLength) LPSOCKADDR lpsaAddress,
    __in     DWORD               dwAddressLength,
    __in_opt LPWSAPROTOCOL_INFOW lpProtocolInfo,
    __out_ecount_part(*lpdwAddressStringLength,*lpdwAddressStringLength) LPWSTR lpszAddressString,
    __inout  LPDWORD             lpdwAddressStringLength
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSAADDRESSTOSTRING  LPFN_WSAADDRESSTOSTRINGW
#else
#define LPFN_WSAADDRESSTOSTRING  LPFN_WSAADDRESSTOSTRINGA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
INT
WSAAPI
WSAStringToAddressA(
    __in    LPSTR               AddressString,
    __in    INT                 AddressFamily,
    __in_opt LPWSAPROTOCOL_INFOA lpProtocolInfo,
    __out_bcount_part(*lpAddressLength,*lpAddressLength) LPSOCKADDR lpAddress,
    __inout LPINT               lpAddressLength
    ){ return 0; }
 WINSOCK_API_LINKAGE
INT
WSAAPI
WSAStringToAddressW(
    __in    LPWSTR             AddressString,
    __in    INT                AddressFamily,
    __in_opt LPWSAPROTOCOL_INFOW lpProtocolInfo,
    __out_bcount_part(*lpAddressLength,*lpAddressLength) LPSOCKADDR lpAddress,
    __inout LPINT              lpAddressLength
    ){ return 0; }
#ifdef UNICODE
#define WSAStringToAddress  WSAStringToAddressW
#else
#define WSAStringToAddress  WSAStringToAddressA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSASTRINGTOADDRESSA)(
    __in    LPSTR              AddressString,
    __in    INT                AddressFamily,
    __in_opt LPWSAPROTOCOL_INFOA lpProtocolInfo,
    __out_bcount_part(*lpAddressLength,*lpAddressLength) LPSOCKADDR lpAddress,
    __inout LPINT              lpAddressLength
    ){ return 0; }
typedef
INT
(WSAAPI * LPFN_WSASTRINGTOADDRESSW)(
    __in    LPWSTR             AddressString,
    __in    INT                AddressFamily,
    __in_opt LPWSAPROTOCOL_INFOW lpProtocolInfo,
    __out_bcount_part(*lpAddressLength,*lpAddressLength) LPSOCKADDR lpAddress,
    __inout LPINT              lpAddressLength
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSASTRINGTOADDRESS  LPFN_WSASTRINGTOADDRESSW
#else
#define LPFN_WSASTRINGTOADDRESS  LPFN_WSASTRINGTOADDRESSA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_TYPEDEFS */

/* Registration and Name Resolution API functions */


#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
INT
WSAAPI
WSALookupServiceBeginA(
    __in LPWSAQUERYSETA lpqsRestrictions,
    __in DWORD          dwControlFlags,
    __out LPHANDLE       lphLookup
    ){ return 0; }

WINSOCK_API_LINKAGE
INT
WSAAPI
WSALookupServiceBeginW(
    __in LPWSAQUERYSETW lpqsRestrictions,
    __in DWORD          dwControlFlags,
    __out LPHANDLE       lphLookup
    ){ return 0; }
#ifdef UNICODE
#define WSALookupServiceBegin  WSALookupServiceBeginW
#else
#define WSALookupServiceBegin  WSALookupServiceBeginA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSALOOKUPSERVICEBEGINA)(
    __in  LPWSAQUERYSETA lpqsRestrictions,
    __in  DWORD          dwControlFlags,
    __out LPHANDLE       lphLookup
    ){ return 0; }
typedef
INT
(WSAAPI * LPFN_WSALOOKUPSERVICEBEGINW)(
    __in  LPWSAQUERYSETW lpqsRestrictions,
    __in  DWORD          dwControlFlags,
    __out LPHANDLE       lphLookup
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSALOOKUPSERVICEBEGIN  LPFN_WSALOOKUPSERVICEBEGINW
#else
#define LPFN_WSALOOKUPSERVICEBEGIN  LPFN_WSALOOKUPSERVICEBEGINA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
INT
WSAAPI
WSALookupServiceNextA(
    __in HANDLE           hLookup,
    __in DWORD            dwControlFlags,
    __inout LPDWORD       lpdwBufferLength,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSAQUERYSETA lpqsResults
    ){ return 0; }
 WINSOCK_API_LINKAGE
INT
WSAAPI
WSALookupServiceNextW(
    __in HANDLE           hLookup,
    __in DWORD            dwControlFlags,
    __inout LPDWORD       lpdwBufferLength,
    __out_bcount_part_opt(*lpdwBufferLength,*lpdwBufferLength) LPWSAQUERYSETW lpqsResults
    ){ return 0; }
#ifdef UNICODE
#define WSALookupServiceNext  WSALookupServiceNextW
#else
#define WSALookupServiceNext  WSALookupServiceNextA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSALOOKUPSERVICENEXTA)(
    __in   HANDLE           hLookup,
    __in   DWORD            dwControlFlags,
    __inout LPDWORD         lpdwBufferLength,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSAQUERYSETA   lpqsResults
    ){ return 0; }
typedef
INT
(WSAAPI * LPFN_WSALOOKUPSERVICENEXTW)(
    __in   HANDLE           hLookup,
    __in   DWORD            dwControlFlags,
    __inout LPDWORD         lpdwBufferLength,
    __out_bcount_part_opt(*lpdwBufferLength,*lpdwBufferLength) LPWSAQUERYSETW   lpqsResults
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSALOOKUPSERVICENEXT  LPFN_WSALOOKUPSERVICENEXTW
#else
#define LPFN_WSALOOKUPSERVICENEXT  LPFN_WSALOOKUPSERVICENEXTA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if(_WIN32_WINNT >= 0x0501)
#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
INT
WSAAPI
WSANSPIoctl(
    __in HANDLE           hLookup,
    __in DWORD            dwControlCode,
    __in_bcount_opt(cbInBuffer) LPVOID lpvInBuffer,
    __in DWORD            cbInBuffer,
    __out_bcount_part_opt(cbOutBuffer, *lpcbBytesReturned) LPVOID lpvOutBuffer,
    __in DWORD            cbOutBuffer,
    __out LPDWORD        lpcbBytesReturned,
    __in_opt LPWSACOMPLETION lpCompletion
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSANSPIOCTL)(
    IN  HANDLE           hLookup,
    IN  DWORD            dwControlCode,
    __in_bcount_opt(cbInBuffer) LPVOID lpvInBuffer,
    IN  DWORD            cbInBuffer,
    __out_bcount_part_opt(cbOutBuffer, *lpcbBytesReturned) LPVOID lpvOutBuffer,
    IN  DWORD            cbOutBuffer,
    __out LPDWORD        lpcbBytesReturned,
    __in_opt LPWSACOMPLETION lpCompletion
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */
#endif //(_WIN32_WINNT >= 0x0501)

#if INCL_WINSOCK_API_PROTOTYPES
 WINSOCK_API_LINKAGE
INT
WSAAPI
WSALookupServiceEnd(
    __in HANDLE  hLookup
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSALOOKUPSERVICEEND)(
    __in HANDLE  hLookup
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
INT
WSAAPI
WSAInstallServiceClassA(
    __in  LPWSASERVICECLASSINFOA   lpServiceClassInfo
    ){ return 0; }

WINSOCK_API_LINKAGE
INT
WSAAPI
WSAInstallServiceClassW(
    __in  LPWSASERVICECLASSINFOW   lpServiceClassInfo
    ){ return 0; }
#ifdef UNICODE
#define WSAInstallServiceClass  WSAInstallServiceClassW
#else
#define WSAInstallServiceClass  WSAInstallServiceClassA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSAINSTALLSERVICECLASSA)(
    __in  LPWSASERVICECLASSINFOA   lpServiceClassInfo
    ){ return 0; }
typedef
INT
(WSAAPI * LPFN_WSAINSTALLSERVICECLASSW)(
    __in  LPWSASERVICECLASSINFOW   lpServiceClassInfo
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSAINSTALLSERVICECLASS  LPFN_WSAINSTALLSERVICECLASSW
#else
#define LPFN_WSAINSTALLSERVICECLASS  LPFN_WSAINSTALLSERVICECLASSA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
INT
WSAAPI
WSARemoveServiceClass(
    __in  LPGUID  lpServiceClassId
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSAREMOVESERVICECLASS)(
    __in  LPGUID  lpServiceClassId
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
INT
WSAAPI
WSAGetServiceClassInfoA(
    __in  LPGUID  lpProviderId,
    __in  LPGUID  lpServiceClassId,
    __inout LPDWORD  lpdwBufSize,
    __out_bcount_part(*lpdwBufSize,*lpdwBufSize) LPWSASERVICECLASSINFOA lpServiceClassInfo
    ){ return 0; }
WINSOCK_API_LINKAGE
INT
WSAAPI
WSAGetServiceClassInfoW(
    __in  LPGUID  lpProviderId,
    __in  LPGUID  lpServiceClassId,
    __inout LPDWORD  lpdwBufSize,
    __out_bcount_part(*lpdwBufSize,*lpdwBufSize) LPWSASERVICECLASSINFOW lpServiceClassInfo
    ){ return 0; }
#ifdef UNICODE
#define WSAGetServiceClassInfo  WSAGetServiceClassInfoW
#else
#define WSAGetServiceClassInfo  WSAGetServiceClassInfoA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSAGETSERVICECLASSINFOA)(
    __in  LPGUID  lpProviderId,
    __in  LPGUID  lpServiceClassId,
    __inout LPDWORD  lpdwBufSize,
    __out_bcount_part(*lpdwBufSize,*lpdwBufSize) LPWSASERVICECLASSINFOA lpServiceClassInfo
    ){ return 0; }
typedef
INT
(WSAAPI * LPFN_WSAGETSERVICECLASSINFOW)(
    __in  LPGUID  lpProviderId,
    __in  LPGUID  lpServiceClassId,
    __inout LPDWORD  lpdwBufSize,
    __out_bcount_part(*lpdwBufSize,*lpdwBufSize) LPWSASERVICECLASSINFOW lpServiceClassInfo
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSAGETSERVICECLASSINFO  LPFN_WSAGETSERVICECLASSINFOW
#else
#define LPFN_WSAGETSERVICECLASSINFO  LPFN_WSAGETSERVICECLASSINFOA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
INT
WSAAPI
WSAEnumNameSpaceProvidersA(
    __inout LPDWORD             lpdwBufferLength,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSANAMESPACE_INFOA lpnspBuffer
    ){ return 0; }
WINSOCK_API_LINKAGE
INT
WSAAPI
WSAEnumNameSpaceProvidersW(
    __inout LPDWORD             lpdwBufferLength,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSANAMESPACE_INFOW lpnspBuffer
    ){ return 0; }

#ifdef UNICODE
#define WSAEnumNameSpaceProviders   WSAEnumNameSpaceProvidersW
#else
#define WSAEnumNameSpaceProviders   WSAEnumNameSpaceProvidersA
#endif /* !UNICODE */

#if(_WIN32_WINNT >= 0x0600 )
WINSOCK_API_LINKAGE
INT
WSAAPI
WSAEnumNameSpaceProvidersExA(
    __inout LPDWORD             lpdwBufferLength,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSANAMESPACE_INFOEXA lpnspBuffer
    ){ return 0; }
WINSOCK_API_LINKAGE
INT
WSAAPI
WSAEnumNameSpaceProvidersExW(
    __inout LPDWORD             lpdwBufferLength,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSANAMESPACE_INFOEXW lpnspBuffer
    ){ return 0; }

#ifdef UNICODE
#define WSAEnumNameSpaceProvidersEx WSAEnumNameSpaceProvidersExW
#else
#define WSAEnumNameSpaceProvidersEx WSAEnumNameSpaceProvidersExA
#endif /* !UNICODE */

#endif //(_WIN32_WINNT >= 0x0600 )


#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSAENUMNAMESPACEPROVIDERSA)(
    __inout LPDWORD              lpdwBufferLength,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSANAMESPACE_INFOA lpnspBuffer
    ){ return 0; }
typedef
INT
(WSAAPI * LPFN_WSAENUMNAMESPACEPROVIDERSW)(
    __inout LPDWORD              lpdwBufferLength,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSANAMESPACE_INFOW lpnspBuffer
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSAENUMNAMESPACEPROVIDERS  LPFN_WSAENUMNAMESPACEPROVIDERSW
#else
#define LPFN_WSAENUMNAMESPACEPROVIDERS  LPFN_WSAENUMNAMESPACEPROVIDERSA
#endif /* !UNICODE */

#if (_WIN32_WINNT >= 0x0600)
typedef
INT
(WSAAPI * LPFN_WSAENUMNAMESPACEPROVIDERSEXA)(
    __inout LPDWORD              lpdwBufferLength,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSANAMESPACE_INFOEXA lpnspBuffer
    ){ return 0; }
typedef
INT
(WSAAPI * LPFN_WSAENUMNAMESPACEPROVIDERSEXW)(
    __inout LPDWORD              lpdwBufferLength,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSANAMESPACE_INFOEXW lpnspBuffer
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSAENUMNAMESPACEPROVIDERSEX  LPFN_WSAENUMNAMESPACEPROVIDERSEXW
#else
#define LPFN_WSAENUMNAMESPACEPROVIDERSEX  LPFN_WSAENUMNAMESPACEPROVIDERSEXA
#endif /* !UNICODE */

#endif //(_WIN32_WINNT >= 0x600)

#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES
WINSOCK_API_LINKAGE
__success(return == 0) INT
WSAAPI
WSAGetServiceClassNameByClassIdA(
    __in       LPGUID  lpServiceClassId,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPSTR lpszServiceClassName,
    __inout LPDWORD lpdwBufferLength
    ){ return 0; }
WINSOCK_API_LINKAGE
__success(return == 0) INT
WSAAPI
WSAGetServiceClassNameByClassIdW(
    __in       LPGUID  lpServiceClassId,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSTR lpszServiceClassName,
    __inout LPDWORD lpdwBufferLength
    ){ return 0; }
#ifdef UNICODE
#define WSAGetServiceClassNameByClassId  WSAGetServiceClassNameByClassIdW
#else
#define WSAGetServiceClassNameByClassId  WSAGetServiceClassNameByClassIdA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDA)(
    __in      LPGUID  lpServiceClassId,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPSTR lpszServiceClassName,
    __inout LPDWORD lpdwBufferLength
    ){ return 0; }
typedef
INT
(WSAAPI * LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDW)(
    __in      LPGUID  lpServiceClassId,
    __out_bcount_part(*lpdwBufferLength,*lpdwBufferLength) LPWSTR lpszServiceClassName,
    __inout LPDWORD lpdwBufferLength
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSAGETSERVICECLASSNAMEBYCLASSID  LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDW
#else
#define LPFN_WSAGETSERVICECLASSNAMEBYCLASSID  LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
INT
WSAAPI
WSASetServiceA(
    __in LPWSAQUERYSETA lpqsRegInfo,
    __in WSAESETSERVICEOP essoperation,
    __in DWORD dwControlFlags
    ){ return 0; }

WINSOCK_API_LINKAGE
INT
WSAAPI
WSASetServiceW(
    __in LPWSAQUERYSETW lpqsRegInfo,
    __in WSAESETSERVICEOP essoperation,
    __in DWORD dwControlFlags
    ){ return 0; }
#ifdef UNICODE
#define WSASetService  WSASetServiceW
#else
#define WSASetService  WSASetServiceA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSASETSERVICEA)(
    __in LPWSAQUERYSETA lpqsRegInfo,
    __in WSAESETSERVICEOP essoperation,
    __in DWORD dwControlFlags
    ){ return 0; }
typedef
INT
(WSAAPI * LPFN_WSASETSERVICEW)(
    __in LPWSAQUERYSETW lpqsRegInfo,
    __in WSAESETSERVICEOP essoperation,
    __in DWORD dwControlFlags
    ){ return 0; }
#ifdef UNICODE
#define LPFN_WSASETSERVICE  LPFN_WSASETSERVICEW
#else
#define LPFN_WSASETSERVICE  LPFN_WSASETSERVICEA
#endif /* !UNICODE */
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
INT
WSAAPI
WSAProviderConfigChange(
    __deref_inout_opt LPHANDLE lpNotificationHandle,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */

#if INCL_WINSOCK_API_TYPEDEFS
typedef
INT
(WSAAPI * LPFN_WSAPROVIDERCONFIGCHANGE)(
    __deref_inout_opt LPHANDLE lpNotificationHandle,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ){ return 0; }
#endif /* INCL_WINSOCK_API_TYPEDEFS */

#if(_WIN32_WINNT >= 0x0600)
#if INCL_WINSOCK_API_PROTOTYPES

WINSOCK_API_LINKAGE
int
WSAAPI
WSAPoll(
    __inout LPWSAPOLLFD fdArray,
    __in ULONG fds,
    __in INT timeout
    ){ return 0; }
#endif /* INCL_WINSOCK_API_PROTOTYPES */
#endif // (_WIN32_WINNT >= 0x0600)

int
WSPAPI
WSCEnumProtocols(
                 __in_opt LPINT lpiProtocols,
                 __out_bcount_part_opt(*lpdwBufferLength, *lpdwBufferLength) LPWSAPROTOCOL_INFOW lpProtocolBuffer,
                 __inout LPDWORD lpdwBufferLength,
                 __out   LPINT lpErrno
    ){ return 0;}

int
WSPAPI
WSCEnumProtocols32(
    __in_opt LPINT   lpiProtocols,
    __out_bcount(*lpdwBufferLength) LPWSAPROTOCOL_INFOW lpProtocolBuffer,
    __inout  LPDWORD lpdwBufferLength,
    __out    LPINT   lpErrno
    ){ return 0; }


int
WSPAPI
WSCDeinstallProvider(
    __in LPGUID lpProviderId,
    __out LPINT lpErrno
    ){ return 0; }


int
WSPAPI
WSCDeinstallProvider32(
    __in   LPGUID lpProviderId,
    __out  LPINT lpErrno
    ){ return 0; }


int
WSPAPI
WSCInstallProvider(
    __in LPGUID lpProviderId,
    __in_z const WCHAR FAR * lpszProviderDllPath,
    __in_ecount(dwNumberOfEntries) const LPWSAPROTOCOL_INFOW lpProtocolInfoList,
    __in  DWORD dwNumberOfEntries,
    __out LPINT lpErrno
    ){ return 0; }

/*
 * This API manipulates 64-bit and 32-bit catalogs simulteneously.
 * It is needed to guarantee the same catalog IDs for provider catalog
 * entries in both 64-bit and 32-bit catalogs.
 */

int
WSPAPI
WSCInstallProvider64_32(
    __in LPGUID lpProviderId,
    __in_z const WCHAR FAR * lpszProviderDllPath,
    __in_ecount(dwNumberOfEntries) const LPWSAPROTOCOL_INFOW lpProtocolInfoList,
    __in DWORD dwNumberOfEntries,
    __out LPINT lpErrno
    ){ return 0; }


int
WSPAPI
WSCGetProviderPath(
    __in LPGUID lpProviderId,
    __out_ecount_part(*lpProviderDllPathLen, *lpProviderDllPathLen) WCHAR FAR * lpszProviderDllPath,
    __inout LPINT lpProviderDllPathLen,
    __out LPINT lpErrno
    ){ return 0; }


#if(_WIN32_WINNT >= 0x0501)


int
WSPAPI
WSCGetProviderPath32(
    __in LPGUID lpProviderId,
    __out_ecount_part(*lpProviderDllPathLen, *lpProviderDllPathLen) WCHAR FAR * lpszProviderDllPath,
    __inout LPINT lpProviderDllPathLen,
    __out LPINT lpErrno
    ){ return 0; }



int
WSPAPI
WSCUpdateProvider(
    __in  LPGUID lpProviderId,
    __in_z const WCHAR FAR * lpszProviderDllPath,
    __in_ecount(dwNumberOfEntries) const LPWSAPROTOCOL_INFOW lpProtocolInfoList,
    __in  DWORD dwNumberOfEntries,
    __out LPINT lpErrno
    ){ return 0; }



int
WSPAPI
WSCUpdateProvider32(
    __in  LPGUID lpProviderId,
    __in_z  const WCHAR FAR * lpszProviderDllPath,
    __in_ecount(dwNumberOfEntries) const LPWSAPROTOCOL_INFOW lpProtocolInfoList,
    __in  DWORD dwNumberOfEntries,
    __out LPINT lpErrno
    ){ return 0; }

#endif //(_WIN32_WINNT >= 0x0501)

int
WSPAPI
WSCInstallQOSTemplate (
    __in  const LPGUID    Guid,
    __in  LPWSABUF        QosName,
    __in  LPQOS           Qos
    ){ return 0; }

typedef
int
(WSPAPI * LPWSCINSTALLQOSTEMPLATE)(
    __in const LPGUID    Guid,
    __in LPWSABUF        QosName,
    __in LPQOS           Qos
    );

int
WSPAPI
WSCRemoveQOSTemplate (
    __in  const LPGUID    Guid,
    __in  LPWSABUF        QosName
    ){ return 0; }

typedef
int
(WSPAPI * LPWSCREMOVEQOSTEMPLATE)(
    __in const LPGUID    Guid,
    __in LPWSABUF        QosName
    );


#if(_WIN32_WINNT >= 0x0600)

//
// LSP Categorization
//

#define LSP_SYSTEM             0x80000000
#define LSP_INSPECTOR          0x00000001
#define LSP_REDIRECTOR         0x00000002
#define LSP_PROXY              0x00000004
#define LSP_FIREWALL           0x00000008
#define LSP_INBOUND_MODIFY     0x00000010
#define LSP_OUTBOUND_MODIFY    0x00000020
#define LSP_CRYPTO_COMPRESS    0x00000040
#define LSP_LOCAL_CACHE        0x00000080

//
// Provider Information APIs
//

typedef enum _WSC_PROVIDER_INFO_TYPE {
//  InfoType is:                  Info points to:
    ProviderInfoLspCategories, // DWORD (LspCategories)
    ProviderInfoAudit,         // struct WSC_PROVIDER_AUDIT_INFO
} WSC_PROVIDER_INFO_TYPE ;

typedef struct _WSC_PROVIDER_AUDIT_INFO {
    DWORD   RecordSize;     // Size of this audit record, in bytes (includes this field)
    PVOID   Reserved;       // Reserved
    // Install Time (GMT)
    // User SID of account performing install
    // Length (in characters) of Full Path
    // Full Path of EXE performing install
} WSC_PROVIDER_AUDIT_INFO;


int
WSPAPI
WSCSetProviderInfo( 
    __in LPGUID lpProviderId,
    __in WSC_PROVIDER_INFO_TYPE InfoType,
    __in_bcount(InfoSize) PBYTE Info,
    __in size_t InfoSize,
    __in DWORD Flags,
    __out LPINT lpErrno
    ){ return 0; }


int
WSPAPI
WSCGetProviderInfo( 
    __in LPGUID lpProviderId,
    __in WSC_PROVIDER_INFO_TYPE InfoType,
    __out_bcount_part(*InfoSize, *InfoSize) PBYTE Info,
    __inout size_t *InfoSize,
    __in DWORD Flags,
    __out LPINT lpErrno
    ){ return 0; }

#if defined(_WIN64)


int
WSPAPI
WSCSetProviderInfo32( 
    __in LPGUID lpProviderId,
    __in WSC_PROVIDER_INFO_TYPE InfoType,
    __in_bcount(InfoSize) PBYTE Info,
    __in size_t InfoSize,
    __in DWORD Flags,
    __out LPINT lpErrno
    ){ return 0; }


int
WSPAPI
WSCGetProviderInfo32( 
    __in LPGUID lpProviderId,
    __in WSC_PROVIDER_INFO_TYPE InfoType,
    __out_bcount_part(*InfoSize, *InfoSize) PBYTE Info,
    __inout size_t *InfoSize,
    __in DWORD Flags,
    __out LPINT lpErrno
    ){ return 0; }

#endif // (_WIN64)

//
// App Permitted LSP Categorization APIs
//


int
WSPAPI
WSCSetApplicationCategory(
    __in_ecount(PathLength) LPCWSTR Path,
    __in DWORD PathLength,
    __in_ecount_opt(ExtraLength) LPCWSTR Extra,
    __in DWORD ExtraLength,
    __in DWORD PermittedLspCategories,
    __out_opt DWORD * pPrevPermLspCat,
    __out LPINT lpErrno
    ){ return 0; }


int
WSPAPI
WSCGetApplicationCategory(
    __in_ecount(PathLength) LPCWSTR Path,
    __in DWORD PathLength,
    __in_ecount_opt(ExtraLength) LPCWSTR Extra,
    __in DWORD ExtraLength,
    __out DWORD * pPermittedLspCategories,
    __out LPINT lpErrno
    ){ return 0; }

#endif //(_WIN32_WINNT >= 0x0600)


/*
 *  The following upcall function prototypes are only used by WinSock 2 DLL and
 *  should not be used by any service providers.
 */

BOOL
WSPAPI
WPUCloseEvent(
    __in WSAEVENT hEvent,
    __out LPINT lpErrno
    ){ return 0; }

int
WSPAPI
WPUCloseSocketHandle(
    __in SOCKET s,
    __out LPINT lpErrno
    ){ return 0; }

WSAEVENT
WSPAPI
WPUCreateEvent(
    __out LPINT lpErrno
    ){ return 0; }

SOCKET
WSPAPI
WPUCreateSocketHandle(
    __in DWORD dwCatalogEntryId,
    __in DWORD_PTR dwContext,
    __out LPINT lpErrno
    ){ return 0; }


int
WSPAPI
WPUFDIsSet(
    __in SOCKET s,
    __in fd_set FAR * fdset
    ){ return 0; }

int
WSPAPI
WPUGetProviderPath(
    __in LPGUID lpProviderId,
    __out_ecount(*lpProviderDllPathLen) WCHAR FAR * lpszProviderDllPath,
    __inout LPINT lpProviderDllPathLen,
    __out LPINT lpErrno
    ){ return 0; }

SOCKET
WSPAPI
WPUModifyIFSHandle(
    __in DWORD dwCatalogEntryId,
    __in SOCKET ProposedHandle,
    __out LPINT lpErrno
    ){ return 0; }


BOOL
WSPAPI
WPUPostMessage(
    __in HWND hWnd,
    __in UINT Msg,
    __in WPARAM wParam,
    __in LPARAM lParam
    ){ return 0; }

typedef
BOOL
(CALLBACK FAR * LPBLOCKINGCALLBACK)(
                                    DWORD_PTR dwContext
    );

int
WSPAPI
WPUQueryBlockingCallback(
    __in DWORD dwCatalogEntryId,
    __out LPBLOCKINGCALLBACK FAR * lplpfnCallback,
    __out PDWORD_PTR lpdwContext,
    __out LPINT lpErrno
    ){ return 0; }

int
WSPAPI
WPUQuerySocketHandleContext(
    __in SOCKET s,
    __out PDWORD_PTR lpContext,
    __out LPINT lpErrno
    ){ return 0; }

typedef struct _WSATHREADID {
    HANDLE      ThreadHandle;
    DWORD_PTR    Reserved;
} WSATHREADID, FAR * LPWSATHREADID;

typedef
VOID
(CALLBACK FAR * LPWSAUSERAPC)(
                              DWORD_PTR dwContext
    );

int
WSPAPI
WPUQueueApc(
    __in LPWSATHREADID lpThreadId,
    __in LPWSAUSERAPC lpfnUserApc,
    __in DWORD_PTR dwContext,
    __out LPINT lpErrno
    ){ return 0; }

BOOL
WSPAPI
WPUResetEvent(
    __in WSAEVENT hEvent,
    __out LPINT lpErrno
    ){ return 0; }

BOOL
WSPAPI
WPUSetEvent(
    __in WSAEVENT hEvent,
    __out LPINT lpErrno
    ){ return 0; }


int
WSPAPI
WPUCompleteOverlappedRequest (
    __in SOCKET s, 	
    __inout LPWSAOVERLAPPED lpOverlapped, 	
    __in DWORD dwError, 	
    __in DWORD cbTransferred, 	
    __out LPINT lpErrno
){ return 0; }

#if(_WIN32_WINNT >= 0x0501)

int
WSPAPI
WPUOpenCurrentThread(
    __out LPWSATHREADID lpThreadId,
    __out LPINT lpErrno
    ){ return 0; }


int
WSPAPI
WPUCloseThread(
    __in LPWSATHREADID lpThreadId,
    __out LPINT lpErrno
    ){ return 0; }
#endif //(_WIN32_WINNT >= 0x0501)

/*
 * Installing and uninstalling name space providers.
 */

#if(_WIN32_WINNT >= 0x0501)
/*
 * SPI and API for enumerating name space providers are
 * currently equivalent since there is no concept of a hidden
 * name space provider
 */
#define WSCEnumNameSpaceProviders WSAEnumNameSpaceProvidersW
#define LPFN_WSCENUMNAMESPACEPROVIDERS LPFN_WSAENUMNAMESPACEPROVIDERSW

INT
WSAAPI
WSCEnumNameSpaceProviders32(
    __inout LPDWORD             lpdwBufferLength,
    __out_bcount(*lpdwBufferLength) LPWSANAMESPACE_INFOW lpnspBuffer
    ){ return 0; }

#endif //(_WIN32_WINNT >= 0x0501)

#if(_WIN32_WINNT >= 0x0600)
#define WSCEnumNameSpaceProvidersEx WSAEnumNameSpaceProvidersExW
#define LPFN_WSCENUMNAMESPACEPROVIDERSEX LPFN_WSAENUMNAMESPACEPROVIDERSEXW

INT
WSAAPI
WSCEnumNameSpaceProvidersEx32(
    __inout LPDWORD     lpdwBufferLength,
    __out_bcount(*lpdwBufferLength) LPWSANAMESPACE_INFOEXW lpnspBuffer
    ){ return 0; }
#endif //(_WIN32_WINNT >= 0x0600)

INT
WSPAPI
WSCInstallNameSpace (
    __in LPWSTR lpszIdentifier,
    __in LPWSTR lpszPathName,
    __in DWORD dwNameSpace,
    __in DWORD dwVersion,
    __in LPGUID lpProviderId
    ){ return 0; }


INT
WSPAPI
WSCInstallNameSpace32 (
    __in LPWSTR lpszIdentifier,
    __in LPWSTR lpszPathName,
    __in DWORD dwNameSpace,
    __in DWORD dwVersion,
    __in LPGUID lpProviderId
    ){ return 0; }

INT
WSPAPI
WSCUnInstallNameSpace (
    __in LPGUID lpProviderId
    ){ return 0; }


#if (_WIN32_WINNT >= 0x0600 )
INT
WSPAPI
WSCInstallNameSpaceEx(
    __in LPWSTR lpszIdentifier,
    __in LPWSTR lpszPathName,
    __in DWORD dwNameSpace,
    __in DWORD dwVersion,
    __in LPGUID lpProviderId,
    __in LPBLOB lpProviderSpecific
    ){ return 0; }
#endif //(defined(_WIN32_WINNT >= 0x0600)

INT
WSPAPI
WSCInstallNameSpaceEx32(
    __in LPWSTR lpszIdentifier,
    __in LPWSTR lpszPathName,
    __in DWORD dwNameSpace,
    __in DWORD dwVersion,
    __in LPGUID lpProviderId,
    __in LPBLOB lpProviderSpecific
    ){ return 0; }

INT
WSPAPI
WSCUnInstallNameSpace32 (
    __in LPGUID lpProviderId
    ){ return 0; }

INT
WSPAPI
WSCEnableNSProvider (
    __in LPGUID lpProviderId,
    __in BOOL fEnable
    ){ return 0; }


INT
WSPAPI
WSCEnableNSProvider32 (
    __in LPGUID lpProviderId,
    __in BOOL fEnable
    ){ return 0; }


int WSPAPI WSCInstallProviderAndChains(
    __in LPGUID lpProviderId,
    __in const LPWSTR lpszProviderDllPath,
    __in const LPWSTR lpszLspName,
    __in DWORD dwServiceFlags,
    __inout_ecount(dwNumberOfEntries) LPWSAPROTOCOL_INFOW lpProtocolInfoList,
    __in DWORD dwNumberOfEntries,
    __out_opt LPDWORD lpdwCatalogEntryId,
    __out LPINT lpErrno){ return 0; }



/*
 * Pointers to the individual entries in the namespace proc table.
 */

typedef
INT
(WSAAPI * LPNSPCLEANUP)(
    __in LPGUID lpProviderId
    );

typedef
INT
(WSAAPI * LPNSPLOOKUPSERVICEBEGIN)(
    __in LPGUID lpProviderId,
    __in LPWSAQUERYSETW lpqsRestrictions,
    __in LPWSASERVICECLASSINFOW lpServiceClassInfo,
    __in DWORD dwControlFlags,
    __out LPHANDLE lphLookup
    );

typedef
INT
(WSAAPI * LPNSPLOOKUPSERVICENEXT)(
    __in HANDLE hLookup,
    __in DWORD dwControlFlags,
    __inout LPDWORD lpdwBufferLength,
    __out_bcount_part(*lpdwBufferLength, *lpdwBufferlength) LPWSAQUERYSETW lpqsResults
    );

#if(_WIN32_WINNT >= 0x0501)
typedef
INT
(WSAAPI * LPNSPIOCTL)(
    __in     HANDLE          hLookup,
    __in     DWORD           dwControlCode,
    __in_bcount(cbInBuffer) LPVOID          lpvInBuffer,
    __in     DWORD           cbInBuffer,
    __out_bcount_part(cbOutBuffer, *lpcbBytesreturned) LPVOID          lpvOutBuffer,
    __in     DWORD           cbOutBuffer,
    __out    LPDWORD         lpcbBytesReturned,
    __in_opt LPWSACOMPLETION lpCompletion,
    __in     LPWSATHREADID   lpThreadId
    );
#endif //(_WIN32_WINNT >= 0x0501)

typedef
INT
(WSAAPI * LPNSPLOOKUPSERVICEEND)(
    __in HANDLE hLookup
    );

typedef
INT
(WSAAPI * LPNSPSETSERVICE)(
    __in LPGUID lpProviderId,
    __in LPWSASERVICECLASSINFOW lpServiceClassInfo,
    __in LPWSAQUERYSETW lpqsRegInfo,
    __in WSAESETSERVICEOP essOperation,
    __in DWORD dwControlFlags
    );

typedef
INT
(WSAAPI * LPNSPINSTALLSERVICECLASS)(
    __in LPGUID lpProviderId,
    __in LPWSASERVICECLASSINFOW lpServiceClassInfo
    );

typedef
INT
(WSAAPI * LPNSPREMOVESERVICECLASS)(
    __in LPGUID lpProviderId,
    __in LPGUID lpServiceClassId
    );

typedef
INT
(WSAAPI * LPNSPGETSERVICECLASSINFO)(
    __in LPGUID lpProviderId,
    __in LPDWORD lpdwBufSize,
    __in LPWSASERVICECLASSINFOW lpServiceClassInfo
    );

/*
 * The name space service provider procedure table.
 */

typedef struct _NSP_ROUTINE {

    /* Structure version information: */
    DWORD           cbSize;
    DWORD           dwMajorVersion;
    DWORD           dwMinorVersion;

    /* Procedure-pointer table: */

    LPNSPCLEANUP             NSPCleanup;
    LPNSPLOOKUPSERVICEBEGIN  NSPLookupServiceBegin;
    LPNSPLOOKUPSERVICENEXT   NSPLookupServiceNext;
    LPNSPLOOKUPSERVICEEND    NSPLookupServiceEnd;
    LPNSPSETSERVICE          NSPSetService;
    LPNSPINSTALLSERVICECLASS NSPInstallServiceClass;
    LPNSPREMOVESERVICECLASS  NSPRemoveServiceClass;
    LPNSPGETSERVICECLASSINFO NSPGetServiceClassInfo;

#if(_WIN32_WINNT >= 0x0501)
    // These APIs were added later, so must appear here
    // to keep the pointers in the structure in order.
    // Namespaces unaware of these APIs will set cbSize
    // to match the size of FIELD_OFFSET(NSP_ROUTINE, NSPIoctl).
    LPNSPIOCTL               NSPIoctl;
#endif //(_WIN32_WINNT >= 0x0501)

} NSP_ROUTINE, FAR * LPNSP_ROUTINE;

/*
 * Startup procedures.
 */

__checkReturn
INT
WSAAPI
NSPStartup(
    __in LPGUID lpProviderId,
    __inout LPNSP_ROUTINE lpnspRoutines
    ){ return 0; }

typedef
__checkReturn
INT
(WSAAPI * LPNSPSTARTUP)(
    __in LPGUID lpProviderId,
    __inout LPNSP_ROUTINE lpnspRoutines
    );

typedef
__checkReturn
INT
(WSAAPI * LPNSPV2STARTUP)(
    __in LPGUID lpProviderId,
    __deref_out LPVOID * ppvClientSessionArg
    );

typedef
INT
(WSAAPI * LPNSPV2CLEANUP)(
    __in LPGUID lpProviderId,
    __in LPVOID pvClientSessionArg
    );

typedef
INT
(WSAAPI * LPNSPV2LOOKUPSERVICEBEGIN)(
    __in LPGUID lpProviderId,
    __in LPWSAQUERYSET2W lpqsRestrictions,
    __in DWORD dwControlFlags,
    __in LPVOID lpvClientSessionArg,
    __out LPHANDLE lphLookup
    );

typedef
VOID
(WSAAPI * LPNSPV2LOOKUPSERVICENEXTEX)(
    __in HANDLE hAsyncCall,
    __in HANDLE hLookup,
    __in DWORD dwControlFlags,
    __in LPDWORD lpdwBufferLength,
    __out LPWSAQUERYSET2W lpqsResults
    );

typedef
INT
(WSAAPI * LPNSPV2LOOKUPSERVICEEND)(
    __in HANDLE hLookup
    );

typedef
VOID
(WSAAPI * LPNSPV2SETSERVICEEX)(
    __in HANDLE hAsyncCall,
    __in LPGUID lpProviderId,
    __in LPWSAQUERYSET2W lpqsRegInfo,
    __in WSAESETSERVICEOP essOperation,
    __in DWORD dwControlFlags,
    __in LPVOID lpvClientSessionArg 
    );

typedef
VOID
(WSAAPI * LPNSPV2CLIENTSESSIONRUNDOWN)(
    __in LPGUID lpProviderId,
    __in LPVOID pvClientSessionArg
    );

typedef struct _NSPV2_ROUTINE {  
    DWORD cbSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    LPNSPV2STARTUP NSPv2Startup;
    LPNSPV2CLEANUP NSPv2Cleanup;
    LPNSPV2LOOKUPSERVICEBEGIN NSPv2LookupServiceBegin;  
    LPNSPV2LOOKUPSERVICENEXTEX NSPv2LookupServiceNextEx;
    LPNSPV2LOOKUPSERVICEEND NSPv2LookupServiceEnd;  
    LPNSPV2SETSERVICEEX NSPv2SetServiceEx;
    LPNSPV2CLIENTSESSIONRUNDOWN NSPv2ClientSessionRundown;
} NSPV2_ROUTINE, *PNSPV2_ROUTINE, *LPNSPV2_ROUTINE;
typedef const NSPV2_ROUTINE * PCNSPV2_ROUTINE, * LPCNSPV2_ROUTINE;


INT WSAAPI WSAAdvertiseProvider(
        __in                const GUID *                    puuidProviderId,
        __in                const LPCNSPV2_ROUTINE          pNSPv2Routine){ return 0; }

INT WSAAPI WSAUnadvertiseProvider(
        __in                const GUID *                    puuidProviderId){ return 0; }

INT WSAAPI WSAProviderCompleteAsyncCall(
        __in                HANDLE                          hAsyncCall,
        __in                INT                             iRetCode){ return 0; }

int
WSPAPI
WSCWriteProviderOrder (
                       IN LPDWORD lpwdCatalogEntryId,
                       IN DWORD dwNumberOfEntries
                       ){return 0;}

int
 WSPAPI
__WSAFDIsSet(
    SOCKET fd,
    fd_set *set
)
{
    return 0;
}

VOID
WSAAPI
freeaddrinfo(
             __in_opt        PADDRINFOA      pAddrInfo
    )
{
}

INT
WSAAPI
getaddrinfo(
    __in_opt        PCSTR               pNodeName,
    __in_opt        PCSTR               pServiceName,
    __in_opt        const ADDRINFOA *   pHints,
    __deref_out     PADDRINFOA *        ppResult
    )
{
    return 0;
}

_MY_C_TAIL_

#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "Config.h"

#pragma warning(push, 0)

_MY_C_HEAD_

BOOL
WINAPI
CreateProcessInternalA(
    HANDLE                  Token,
    LPCSTR                  ApplicationName,
    LPSTR                   CommandLine,
    LPSECURITY_ATTRIBUTES   ProcessAttributes,
    LPSECURITY_ATTRIBUTES   ThreadAttributes,
    BOOL                    InheritHandles,
    DWORD                   CreationFlags,
    LPVOID                  Environment,
    LPCSTR                  CurrentDirectory,
    LPSTARTUPINFOA          StartupInfo,
    LPPROCESS_INFORMATION   ProcessInformation,
    PHANDLE                 NewToken
)
{
    return 0;
}

BOOL
WINAPI
CreateProcessInternalW(
    HANDLE                  Token,
    PCWSTR                  ApplicationName,
    PCWSTR                  CommandLine,
    LPSECURITY_ATTRIBUTES   ProcessAttributes,
    LPSECURITY_ATTRIBUTES   ThreadAttributes,
    BOOL                    InheritHandles,
    DWORD                   CreationFlags,
    LPVOID                  Environment,
    PCWSTR                  CurrentDirectory,
    LPSTARTUPINFOW          StartupInfo,
    LPPROCESS_INFORMATION   ProcessInformation,
    PHANDLE                 NewToken
)
{
    return 0;
}

_MY_C_TAIL_


#pragma warning(pop)

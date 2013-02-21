#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(linker, "/EXPORT:WTSFreeMemory=_PWTSFreeMemory@4")
#pragma comment(linker, "/EXPORT:WTSQuerySessionInformationW=_PWTSQuerySessionInformationW@0")
#pragma comment(linker, "/EXPORT:WTSUnRegisterSessionNotification=_PWTSUnRegisterSessionNotification@4")
#pragma comment(linker, "/EXPORT:WTSRegisterSessionNotification=_PWTSRegisterSessionNotification@8")

#include "MyLibrary.cpp"
#include "WtsApi32.h"
#include "resource.h"

LPWSTR g_pCmdLineW;
LPSTR  g_pCmdLineA;

TYPE_OF(WTSFreeMemory)*                     StubWTSFreeMemory;
TYPE_OF(WTSQuerySessionInformationW)*       StubWTSQuerySessionInformationW;
TYPE_OF(WTSRegisterSessionNotification)*    StubWTSRegisterSessionNotification;
TYPE_OF(WTSUnRegisterSessionNotification)*  StubWTSUnRegisterSessionNotification;
TYPE_OF(LoadAcceleratorsW)*                 StubLoadAcceleratorsW;

EXTC VOID WINAPI PWTSFreeMemory(PVOID Memory)
{
    return StubWTSFreeMemory(Memory);
}

EXTC BOOL WINAPI PWTSQuerySessionInformationW()
{
    return ((TYPE_OF(PWTSQuerySessionInformationW) *)StubWTSQuerySessionInformationW)();
}

EXTC LONG WINAPI PWTSRegisterSessionNotification(HWND hWnd, DWORD Flags)
{
    return StubWTSRegisterSessionNotification(hWnd, Flags);
}

EXTC LONG WINAPI PWTSUnRegisterSessionNotification(HWND hWnd)
{
    return StubWTSUnRegisterSessionNotification(hWnd);
}

LPCWSTR MyGetCommandLineW()
{
    return g_pCmdLineW;
}

LPCSTR MyGetCommandLineA()
{
    return g_pCmdLineA;
}

HACCEL WINAPI MyLoadAcceleratorsW(HINSTANCE hInstance, LPCWSTR lpTableName)
{
    if (lpTableName == MAKEINTRESOURCEW(0x65) && hInstance == Nt_GetModuleHandle(L"chrome.dll"))
    {
        hInstance = (HINSTANCE)&__ImageBase;
        lpTableName = MAKEINTRESOURCEW(IDR_ACCELERATOR);
    }

    return StubLoadAcceleratorsW(hInstance, lpTableName);
}

BOOL UnInitialize(PVOID BaseAddress)
{
    return FALSE;
}

BOOL Initialize(PVOID BaseAddress)
{
    PVOID   hModule;
    SizeT   Length, Length2;
    LPWSTR  lpCmdLineW, pCmdLine;
    WChar   end, szCmdLine[MAX_PATH + 40];

    static WChar AddCmdLineHeadW[] = L" --user-data-dir=\"";
    static WChar AddCmdLineTailW[] = L"UserData\" --purge-memory-button";
    
    LdrDisableThreadCalloutsForDll(BaseAddress);

    Length = Nt_GetSystemDirectory(szCmdLine, countof(szCmdLine));
    CopyStruct(szCmdLine + Length, L"wtsapi32.dll", sizeof(L"wtsapi32.dll"));
    hModule = Ldr::LoadDll(szCmdLine);

    *(PVOID *)&StubWTSFreeMemory                    = GetRoutineAddress(hModule, "WTSFreeMemory");
    *(PVOID *)&StubWTSQuerySessionInformationW      = GetRoutineAddress(hModule, "WTSQuerySessionInformationW");
    *(PVOID *)&StubWTSUnRegisterSessionNotification = GetRoutineAddress(hModule, "WTSUnRegisterSessionNotification");
    *(PVOID *)&StubWTSRegisterSessionNotification   = GetRoutineAddress(hModule, "WTSRegisterSessionNotification");

    lpCmdLineW = Ps::GetCommandLine();

    Length = StrLengthW(lpCmdLineW);

    pCmdLine = szCmdLine;
    StrCopyW(pCmdLine, AddCmdLineHeadW);
    pCmdLine += countof(AddCmdLineHeadW) - 1;
    pCmdLine += Nt_GetExeDirectory(pCmdLine, countof(szCmdLine) - (pCmdLine - szCmdLine));
    StrCopyW(pCmdLine, AddCmdLineTailW);
    pCmdLine += countof(AddCmdLineTailW);
    Length2 = pCmdLine - szCmdLine;

    g_pCmdLineW = (PWChar)AllocateMemory(Length * 2 + Length2 * 2 + 2);

    pCmdLine = lpCmdLineW;
    end = *pCmdLine++ == '\"' ? '\"' : ' ';
    while (*pCmdLine && *pCmdLine != end) ++pCmdLine;
    ++pCmdLine;
/*
    if (*++pCmdLine)
    {
        while (*pCmdLine == ' ' || *pCmdLine == '\t') ++pCmdLine;
    }
*/
    end = *pCmdLine;
    *pCmdLine = 0;
    StrCopyW(g_pCmdLineW, lpCmdLineW);
    *pCmdLine = end;

    lpCmdLineW = g_pCmdLineW + (pCmdLine - lpCmdLineW);
    StrCopyW(lpCmdLineW, szCmdLine);
    lpCmdLineW += Length2 - 1;
    StrCopyW(lpCmdLineW, pCmdLine);

    Length = StrLengthW(g_pCmdLineW);
    g_pCmdLineA = (PChar)AllocateMemory(Length * 2);
//    WideCharToMultiByte(CP_ACP, 0, g_pCmdLineW, -1, g_pCmdLineA, Length * 2, NULL, NULL);
    UnicodeToAnsi(g_pCmdLineA, Length * 2, g_pCmdLineW, -1);

    hModule = Nt_GetModuleHandle(L"chrome.dll");

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_JUMP_NULL(::GetCommandLineW, MyGetCommandLineW),
        INLINE_HOOK_JUMP_NULL(::GetCommandLineA, MyGetCommandLineA),

        INLINE_HOOK_JUMP(LoadAcceleratorsW, MyLoadAcceleratorsW, StubLoadAcceleratorsW),
    };

    Nt_PatchMemory(0, 0, f, countof(f), 0);    

    return TRUE;
}

BOOL WINAPI DllMain(PVOID BaseAddress, ULONG Reason, PVOID Reserved)
{
    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Initialize(BaseAddress) || UnInitialize(BaseAddress);

        case DLL_PROCESS_DETACH:
            UnInitialize(BaseAddress);
            break;
    }

    return TRUE;
}
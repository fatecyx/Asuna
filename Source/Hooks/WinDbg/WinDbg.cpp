#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(linker, "/EXPORT:DragAcceptFiles=SHELL32.DragAcceptFiles")

#include <Windows.h>
#include "my_headers.h"
#include "my_commsrc.h"

BOOL CDECL DbgEng_PrintValue(int c)
{
    static BOOL IsLastCharLeadByte;

    if (IsLastCharLeadByte)
    {
        IsLastCharLeadByte = FALSE;
        return TRUE;
    }

    IsLastCharLeadByte = IsDBCSLeadByte(c);
    if (IsLastCharLeadByte)
        return IsLastCharLeadByte;

    return isprint(c);
}

VOID FASTCALL WinDBG_CPFormatMemory(PWCHAR Unicode, PCHAR Ansi)
{
    static BOOL   IsLastCharLeadByte;
    static PWCHAR LastUnicode;

    if (IsLastCharLeadByte)
    {
        IsLastCharLeadByte = FALSE;
        return;
    }

    if (LastUnicode == NULL)
    {
        LastUnicode =  Unicode + 1;
    }
    else
    {
        Unicode = LastUnicode;
        ++LastUnicode;
    }

    IsLastCharLeadByte = IsDBCSLeadByte(*Ansi);
    RtlMultiByteToUnicodeN(
        Unicode,
        2,
        NULL,
        Ansi,
        IsLastCharLeadByte ? 2 : 1
    );

    Unicode[1] = '.';
}

NTSTATUS Init()
{
    ULONG_PTR       Offset;
    NTSTATUS        Status;
    PVOID           DebugEngineModule, ExeModule;
    UNICODE_STRING  DebugEngine;

    RTL_CONST_STRING(DebugEngine, L"dbgeng.dll");
    Status = LdrGetDllHandle(NULL, NULL, &DebugEngine, &DebugEngineModule);
    if (!NT_SUCCESS(Status))
        return Status;

    ExeModule = Nt_GetExeModuleHandle();
    Offset = (ULONG_PTR)ExeModule - (ULONG_PTR)DebugEngineModule;

    MEMORY_PATCH p[] =
    {
        { -1,   4, 0x1431A0 },
        { 'X',  1, 0x003ABC + Offset },
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        { CALL, 0x1C8DC7, DbgEng_PrintValue, 1 },
//        { CALL, 0x02CBEF + Offset, WinDBG_CPFormatMemory, 0x28 },
    };

    Nt_PatchMemory(p, countof(p), f, countof(f), DebugEngineModule);

    LdrLoadDll(NULL, 0, &WCharToUnicodeString(L"ColorWindbg.dll", CONST_STRLEN(L"ColorWindbg.dll")), &DebugEngineModule);

    Nt_SetExeDirectoryAsCurrent();

    return STATUS_SUCCESS;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            LdrDisableThreadCalloutsForDll(hInstance);
            setlocale(LC_ALL, ".936");
            Init();
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

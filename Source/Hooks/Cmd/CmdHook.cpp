#pragma comment(linker,"/MERGE:.text=.Amano /SECTION:.Amano,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Amano")
#pragma comment(linker,"/MERGE:.data=.Amano")
#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(lib, "WINBRAND.lib")

#include "my_headers.h"
#include "my_commsrc.h"

VOID WINAPI GetDir(LPWSTR Path, ULONG Size, WCHAR EnvVar)
{
    if (__argc == 1)
    {
        StrCopyW(Path, L"G:\\x");
        Nt_SetCurrentDirectory(Path);
    }
    else
    {
        Nt_GetCurrentDirectory(Size, Path);
    }
}

BOOL Init(PVOID BaseAddress)
{
    PVOID Wow64Information;

    LdrDisableThreadCalloutsForDll(BaseAddress);
    NtQueryInformationProcess(NtCurrentProcess(), ProcessWow64Information, &Wow64Information, sizeof(Wow64Information), NULL);

    ULONG Count;
    MEMORY_FUNCTION_PATCH *pf;

    if (Wow64Information)
    {
        MEMORY_FUNCTION_PATCH f[] =
        {
            PATCH_FUNCTION(CALL, 0, 0x8582, GetDir),
        };

        pf = f;
        Count = countof(f);
    }
    else
    {
        MEMORY_FUNCTION_PATCH f[] =
        {
            PATCH_FUNCTION(CALL, 0, 0x8582, GetDir),
        };

        pf = f;
        Count = countof(f);
    }

    Nt_PatchMemory(0, 0, pf, Count, Nt_GetExeModuleHandle());

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, PVOID Reserved)
{
    UNREFERENCED_PARAMETER(Reserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Init(hInstance);

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

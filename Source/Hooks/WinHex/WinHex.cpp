#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "my_commsrc.h"

VOID FASTCALL ConvertAnsiToUnicode(PVOID, PCSTR Source)
{
    PWSTR Destination;

    INLINE_ASM mov Destination, ebx;

    Nt_AnsiToUnicode(Destination, 0x40, Source);

    INLINE_ASM xor eax, eax;
}

ULONG FASTCALL ConvertUnicodeToAnsi()
{
    return 1;
}

BOOL Init(HINSTANCE hInstance)
{
    ULONG_PTR BaseAddress;

    MEMORY_FUNCTION_PATCH f[] =
    {
        PATCH_FUNCTION(CALL, 0, 0x1111E4, ConvertAnsiToUnicode),
//        PATCH_FUNCTION(CALL, 0, 0x1111E4, ConvertUnicodeToAnsi),
    };

    BaseAddress = (ULONG_PTR)Nt_GetExeModuleHandle();

    Nt_PatchMemory(0, 0, f, countof(f), (PVOID)BaseAddress);

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID Reserved)
{
    UNREFERENCED_PARAMETER(Reserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            LdrDisableThreadCalloutsForDll(hInstance);
            return Init(hInstance);

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

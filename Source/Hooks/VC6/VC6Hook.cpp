#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "my_api.cpp"
#include "my_crtadd.cpp"
#include "Mem.cpp"

VOID FASTCALL WriteLinkerTempFile(PVOID pThis, PVOID, PCHAR pszText)
{
    PWCHAR pszUnicode;
    ULONG  Length;
    FILE  *fp;

    Length = StrLengthA(pszText);
    if (*(PULONG)pszText == TAG4('@ech'))
    {
        pszUnicode = (PWCHAR)pszText;
    }
    else
    {
        pszUnicode = (PWCHAR)AllocStack(Length * 2 + 2);
        *(PUSHORT)pszUnicode = BOM_UTF16_LE;
        Length = MultiByteToWideChar(CP_GB2312, 0, pszText, Length, pszUnicode + 1, Length);
        Length = Length * 2 + 2;
    }

    fp = *(FILE **)((ULONG_PTR)pThis + 0x10);
    _setmode(_fileno(fp), _O_BINARY);
    fwrite(pszUnicode, Length, 1, fp);
}

VOID FASTCALL Init2(HMODULE hModule)
{
    MEMORY_FUNCTION_PATCH f[] =
    {
        { CALL, 0xE160, WriteLinkerTempFile },
    };

    PatchMemory(NULL, 0, f, countof(f), hModule);
}

ASM VOID LoadDevBldFinished()
{
    INLINE_ASM
    {
        mov  ecx, [esp + 4];
        push eax;
        call Init2;
        pop  eax;
        test eax, eax;
        ret  0x10;
    }
}

VOID Init()
{
    setlocale(LC_ALL, ".936");

    HMODULE hModule = GetModuleHandleW(L"devshl.dll");
    MEMORY_FUNCTION_PATCH f[] =
    {
        { CALL, 0x380DB, LoadDevBldFinished },
    };

    PatchMemory(NULL, 0, f, countof(f), hModule);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            Init();
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}
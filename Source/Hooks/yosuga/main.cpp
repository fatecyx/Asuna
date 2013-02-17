#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")
#pragma comment(linker,"/ENTRY:DllMain")

#include <Windows.h>
#include "my_common.h"
#include "my_mem.h"

typedef struct
{
    LPVoid *vtable;
    PWChar  pszText;
    UInt32  uLength;
    UInt32  uMaxLenth;
} SYSGText;

LPVoid STDCALL HookShowText(LPVoid Pointer, PWChar pszCharName, Int32 unknown)
{
    LPVoid    r;
    SYSGText  *pText, OrigText;
    static WChar test[] = L"Hook by Kanade";
    static WChar orig[] = L"蔚蓝的天空让人觉得异常的清澈。";

    __asm mov pText, ecx;
    OrigText = *pText;

    if (!memcmp(pText->pszText, orig, sizeof(orig) - 2))
    {
        pText->pszText = test;
        pText->uLength = countof(test) - 1;
        pText->uMaxLenth = pText->uLength + 1;
    }

    __asm
    {
        push unknown;
        push pszCharName;
        push Pointer;
        mov  ecx, pText;
        mov  eax, 4A4E20h;
        call eax;
        mov  r, eax;
    }

    *pText = OrigText;

    return r;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    static Bool bInit = False;

    if (bInit == False)
    {
        bInit = True;

        SFuncPatch f[] = 
        {
            { CALL, 0x9B943, HookShowText, 0 }, 
        };

        PatchMemory(0, 0, f, countof(f), GetModuleHandleW(0));
    }

    return True;
}
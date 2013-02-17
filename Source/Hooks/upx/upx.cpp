#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(lib, "msvcrt.lib")

#include "upx.h"
#include "my_mem.h"

int WINAPI DllMain(HINSTANCE hInst, unsigned long reason, void* lpReserved)
{
	static BOOL bWritten = False;

	if (bWritten == False)
    {
        SPatch patch[] =
        {
            { 9,    4, 0x1575A }, // -9
            // 3.07
            { 0x80C181,    4, 0x3A96B },
            { 0xEB,        1, 0x3AB0C },
        };

        SFuncPatch func[] =
        {
/*
            // 3.05
            { CALL, 0x44DEF, (DWORD)strcpy_hook,     0 },
            { CALL, 0x450B1, (DWORD)write_hook,      7 },
            { CALL, 0x1A429, (DWORD)write_peheader,  2 },
            { CALL, 0x43A5F, (DWORD)modify_peoffset, 0 },

            // 3.06
            { CALL, 0x3A884, strcpy_hook,     0 },
            { CALL, 0x3AB46, write_hook,      7 },
            { CALL, 0x3FBA9, write_peheader,  2 },
            { CALL, 0x19B80, modify_peoffset, 0 },
*/
            // 3.07
            { CALL, 0x3A8B6, strcpy_hook,     0 },
            { CALL, 0x3AB78, write_hook,      7 },
            { CALL, 0x3FBD9, write_peheader,  2 },
            { CALL, 0x19B80, modify_peoffset, 0 },
        };
        bWritten = True;
        PatchMemory(patch, countof(patch), func, countof(func), GetModuleHandleA(NULL));
	}

	return True;
}

void STDCALL section_name(char *sec1, char *sec2, char *sec3)
{
    static const char *szSectionName = ".Amano";
    lstrcpy(sec1, szSectionName);
    lstrcpy(sec2, szSectionName);
    lstrcpy(sec3, szSectionName);
}

ASM char* CDECL strcpy_hook(char *dst, char *src)
{
    __asm
    {
        pushad;
        lea  eax, dword ptr [ebp-11Ch];
        push eax;
        lea  eax, dword ptr [eax-28h];
        push eax;
        lea  eax, dword ptr [eax-28h];
        push eax;
        call section_name;
        popad;
        ret;
    }
}

ASM int CDECL write_hook(void *This, char *buf, int n)
{
    __asm
    {
        mov  dword ptr [ebp-1FCh], 1;
        pushad;
        mov  edi, dword ptr [esp+28h];
        mov  ecx, dword ptr [esp+2Ch];
        xor  eax, eax;
        rep  stosb;
        popad;
        jmp  eax;
    }
}

ASM int CDECL write_peheader(char *buf, int n)
{
    __asm
    {
        cmp dword ptr [esp+4h], 80h;
        jle LES80;
        mov dword ptr [esp+4h], 80h;
        mov ecx, dword ptr [ebp-54h];
        mov dword ptr [ecx+3Ch], 80h;
LES80:
        pop  ecx;
        push dword ptr [ebp-54h];
        push edx;
        push ecx;
        jmp  dword ptr [eax+24h];
    }
}

ASM void CDECL modify_peoffset()
{
    __asm
    {
        push eax;
        mov  edx, 80h;
        lea  eax, dword ptr [ecx+104h];
        cmp  dword ptr [eax], edx;
        jle  LES80;
        mov  dword ptr [eax], edx;
LES80:
        pop  eax;
        cmp  eax, 10000h;
        ret;
    }
}
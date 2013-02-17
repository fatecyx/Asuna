#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker,"/MERGE:.text=.Nagisa /SECTION:.Nagisa,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Nagisa")
#pragma comment(linker,"/MERGE:.data=.Nagisa")
#pragma comment(lib,"ntdll.lib")

#include "MyLibrary.cpp"
#include "Share.h"

Void NTAPI NtSleep(DWORD dwMilliseconds)
{
    return Nt_Sleep(dwMilliseconds);
}

ASM void s_CreateFile()
{
	__asm
	{
		push  487AB8h;
		push  eax;
		push  ecx;
		push  edi;
		xor   eax, eax;
		mov   edi, ecx;
		or    ecx, -1;
		repne scasw;
		mov   byte ptr [edi-4], 5Fh;
		pop   edi;
		pop   ecx;
		pop   eax;
		ret;
	}
}

BOOL WINAPI HookCryptGetHashParam(HCRYPTHASH hHash, DWORD Param, PBYTE Data, PULONG DataLen, ULONG Flags)
{
    ULONG RSAHashData[] = { 0x90f03661, 0xdb42ffc1, 0x125bb3c7, 0xf1043aa8, 0x29bb9296 };

    CopyStruct(Data, RSAHashData, sizeof(RSAHashData));
    *DataLen = sizeof(RSAHashData);

    return TRUE;
}

int WINAPI DllMain(HINSTANCE hInstance, unsigned long reason, void* lpReserved)
{
    if (reason != DLL_PROCESS_ATTACH)
        return TRUE;

    MEMORY_PATCH p[] =
    {
        /************************************************************************/
        /* 去自校验                                                             */
        /************************************************************************/
        PATCH_MEMORY(0xB8,      0x1, 0xB06B1),    // CreateMutex detect
        PATCH_MEMORY(0xEB,      0x1, 0xB06C4),    // CreateMutex detect
        PATCH_MEMORY(0xEB,      0x1, 0xB0743),    // CreateMutex detect
        PATCH_MEMORY(0xEB,      0x1, 0xB0785),    // CreateMutex detect
        PATCH_MEMORY(0xEB,      0x1, 0xB0821),    // CreateMutex detect

        //  { "\x00",               0x1, 0x49CCB8 },
        PATCH_MEMORY(0x00,      0x1, 0x9CCB8),
        PATCH_MEMORY(0xEB,      0x1, 0x9B4B4),
        PATCH_MEMORY(0xEB,      0x1, 0x9D011),
        PATCH_MEMORY(0xEB,      0x1, 0x9D0E8),
        PATCH_MEMORY(0xEB,      0x1, 0x9D152),
        PATCH_MEMORY(0xEB,      0x1, 0x9D1B8),
        PATCH_MEMORY(0xEB,      0x1, 0x9B508),
        PATCH_MEMORY(0xEB,      0x1, 0x9B523),
        PATCH_MEMORY(0x00,      0x1, 0xD4FBF),
        PATCH_MEMORY(0xEB,      0x1, 0xE8ACC),
        PATCH_MEMORY(0xEB,      0x1, 0xE8C7E),
        PATCH_MEMORY(0xEB,      0x1, 0xE9488),
        PATCH_MEMORY(0xEB,      0x1, 0xEB12F),
        PATCH_MEMORY(0xEB,      0x1, 0xEBB21),
        PATCH_MEMORY(0x00,      0x2, 0xEF031),
        PATCH_MEMORY(0x00,      0x1, 0xEF14F),
        PATCH_MEMORY(0xEB,      0x1, 0xEFB56),
        //  { "\xEB",               0x1, 0x4F4196 },
        PATCH_MEMORY(0xEB,      0x1, 0xF7888),
        PATCH_MEMORY(0xEB,      0x1, 0x10596B),
        PATCH_MEMORY(0x03EB,    0x2, 0x107AF6),
        PATCH_MEMORY(0x00,      0x4, 0x12F864),

        /************************************************************************/
        /* 去上传速度限制                                                       */
        /************************************************************************/

        PATCH_MEMORY(0x00,      0x1, 0x109D19),
        PATCH_MEMORY(0x00,      0x1, 0x109D82),
        PATCH_MEMORY(0x00,      0x1, 0x11D51A),
        PATCH_MEMORY(0x00,      0x1, 0x11D633),
        PATCH_MEMORY(0x00,      0x1, 0x108A17),
        PATCH_MEMORY(0x00,      0x1, 0x108A20),

        /************************************************************************/
        /* 去LogCacheEraser      自动删除执行缓存                               */
        /* 去LogCacheEraseResult 删除%d个缓存文件                               */
        /************************************************************************/
        PATCH_MEMORY(0x31,      0x1, 0xE46D0),        // LogCacheEraseResult
        PATCH_MEMORY(0xBA,      0x1, 0xE3C47),        // LogCacheEraser
        //	{ "\xEB",	0x1, 0x4E3C2D },	// LogCacheEraser
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        // INLINE_HOOK_CALL_RVA_NULL(0x9CB31, s_CreateFile),
        INLINE_HOOK_CALL_RVA_NULL(0x9CC8C, HookCryptGetHashParam),
        INLINE_HOOK_CALL_RVA_NULL(IMAGE_INVALID_RVA, NULL),
    };

    Nt_PatchMemory(p, countof(p), f, countof(f), Nt_GetExeModuleHandle());

	return TRUE;
}

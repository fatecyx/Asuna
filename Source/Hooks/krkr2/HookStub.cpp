#include "krkr2.h"

TYPE_OF(NtQueryAttributesFile)      *StubNtQueryAttributesFile;
TYPE_OF(NtQueryDirectoryFile)       *StubNtQueryDirectoryFile;
TYPE_OF(NtCreateFile)               *StubNtCreateFile;
TYPE_OF(LdrLoadDll)                 *StubLdrLoadDll;
TYPE_OF(CreateFontIndirectExW)      *StubCreateFontIndirectExW;
TYPE_OF(GetGlyphOutlineW)           *StubGetGlyphOutlineW;

BOOL InitializeHook(PVOID BaseAddress)
{
    MEMORY_PATCH p[] =
    {
//        PATCH_MEMORY(0xB8,                  1, 0x21BC9D),
//        PATCH_MEMORY(0xB8,                  1, 0x21BCF6),
        PATCH_MEMORY(DATA_XP3_FILE_NAME,    4, 0x2129EC)
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
//        PATCH_FUNCTION(CALL, 0, 0x21BC64, LoadTpmPlugin),

        INLINE_HOOK_JUMP(NtQueryDirectoryFile,  HookNtQueryDirectoryFile,   StubNtQueryDirectoryFile),
        INLINE_HOOK_JUMP(NtQueryAttributesFile, HookNtQueryAttributesFile,  StubNtQueryAttributesFile),
        INLINE_HOOK_JUMP(NtCreateFile,          HookNtCreateFile,           StubNtCreateFile),
        INLINE_HOOK_JUMP(LdrLoadDll,            HookLdrLoadDll,             StubLdrLoadDll),
        INLINE_HOOK_JUMP(CreateFontIndirectExW, HookCreateFontIndirectExW,  StubCreateFontIndirectExW),
        INLINE_HOOK_JUMP(GetGlyphOutlineW,      HookGetGlyphOutlineW,       StubGetGlyphOutlineW),
    };

    return NT_SUCCESS(Nt_PatchMemory(p, countof(p)*0, f, countof(f), Nt_GetExeModuleHandle()));
}

PVOID FindTVPGetPlacedPath(ITVPFunctionExporter *Exporter)
{
    static WCHAR *Function[] =
    {
        L"ttstr ::TVPGetPlacedPath(const ttstr &)",
    };

    PBYTE TVPGetPlacedPathWrap, CallTVPGetPlacedPath;

    if (!Exporter->QueryFunctions(Function, (PVOID *)&TVPGetPlacedPathWrap, 1))
        return NULL;

    CallTVPGetPlacedPath = NULL;
    for (LONG Size = 0x60; ; )
    {
        ULONG Length;

        if (*TVPGetPlacedPathWrap == CALL)
        {
            if (CallTVPGetPlacedPath != NULL)
                return NULL;

            CallTVPGetPlacedPath = TVPGetPlacedPathWrap;
        }
        else if (
                 *TVPGetPlacedPathWrap == 0xC2 &&
                 *(PUSHORT)&TVPGetPlacedPathWrap[1] == 8
                )
        {
            break;
        }

        Length = GetOpCodeSize(TVPGetPlacedPathWrap);

        TVPGetPlacedPathWrap += Length;
        Size -= Length;
        if (Size <= 0)
            return NULL;
    }

    return GetCallDestination(CallTVPGetPlacedPath);
}

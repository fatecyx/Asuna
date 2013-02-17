#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(linker, "/EXPORT:GetSaveFileNameW=COMDLG32.GetSaveFileNameW")
#pragma comment(linker, "/EXPORT:CommDlgExtendedError=COMDLG32.CommDlgExtendedError")
#pragma comment(linker, "/EXPORT:GetOpenFileNameW=COMDLG32.GetOpenFileNameW")

#include "MyLibrary.cpp"
#include "mlns.h"

#define ST_VERSION 3

#if ST_VERSION == 2
    typedef WCHAR ACP_TEXT;
#elif ST_VERSION == 3
    typedef CHAR ACP_TEXT;
#endif

enum
{
    STCP_Hexadecimal    = 0x1D,
    STCP_UTF_16_BE      = 0x1E,
    STCP_UTF_16_BE_BOM  = 0x1F,
    STCP_UTF_16_LE      = 0x20,
    STCP_UTF_16_LE_BOM  = 0x21,
    STCP_UTF_8_LE_BOM   = 0x22,
    STCP_UTF_8_BOM      = 0x23,

    STCP_ACP            = ~0u,
};

typedef struct
{
    PWSTR Begin;
    PWSTR End;

    ULONG_PTR Length()
    {
        return End - Begin;
    }

} SUBLIME_TEXT_WSTRING, *PSUBLIME_TEXT_WSTRING;

PSUBLIME_TEXT_WSTRING (CDECL *StubGetEncodingByIndex)(PSUBLIME_TEXT_WSTRING Encoding, ULONG CpIndex);
ULONG (*StubACPToUnicode)();
ULONG (CDECL *StubUnicodeToACP)(ULONG CpIndex, PSUBLIME_TEXT_WSTRING Unicode, PSTR Ansi, LONG AnsiSize);

ACP_TEXT Acp[10];

PSUBLIME_TEXT_WSTRING CDECL GetEncodingByIndex(PSUBLIME_TEXT_WSTRING Encoding, ULONG CpIndex)
{
    if (CpIndex != STCP_ACP)
        return StubGetEncodingByIndex(Encoding, CpIndex);

    Encoding->Begin = (PWSTR)Acp;
    Encoding->End   = (PWSTR)(Acp + CONST_STRLEN(Acp));

    return Encoding;
}

LONG_PTR GetDefaultEncodingIndex()
{
    return STCP_ACP;
}

ULONG STDCALL ACPToUnicode(PSTR *Ansi, PSTR AnsiEnd, PWSTR *Unicode, ULONG CpIndex)
{
    if (CpIndex == STCP_ACP)
    {
        ULONG_PTR Length;

        Length = AnsiEnd - *Ansi;
        AnsiToUnicode(*Unicode, Length, *Ansi, Length, &Length);

        *Unicode    = PtrAdd(*Unicode, Length);
        *Ansi       = AnsiEnd;

        return Length;
    }

    return 0;
}

NAKED ULONG NakedACPToUnicode_2()
{
    INLINE_ASM
    {
        push    eax;
        push    eax;
        push    esi;
        push    ebx;
        push    edi;
        call    ACPToUnicode;
        pop     eax;
        add     esp, 4;
        jmp     StubACPToUnicode;
    }
}

NAKED ULONG NakedACPToUnicode_3()
{
    INLINE_ASM
    {
        push    ecx;
        push    ecx;
        push    edi;
        push    ebx;
        push    esi;
        call    ACPToUnicode;
        pop     ecx;
        add     esp, 4;
        jmp     StubACPToUnicode;
    }
}

ULONG CDECL UnicodeToACP(ULONG CpIndex, PSUBLIME_TEXT_WSTRING Unicode, PSTR Ansi, LONG AnsiSize)
{
    if (CpIndex != STCP_ACP)
        return StubUnicodeToACP(CpIndex, Unicode, Ansi, AnsiSize);

    PSTR        AnsiBuffer;
    PWSTR       UnicodeBuffer;
    ULONG_PTR   Size, UnicodeSize;

    AnsiBuffer      = Ansi;
    UnicodeBuffer   = Unicode->Begin;
    UnicodeSize     = Unicode->Length();
    for (; UnicodeSize != 0 && AnsiSize > 0; AnsiSize -= Size, --UnicodeSize)
    {
        UnicodeToAnsi(AnsiBuffer, AnsiSize, UnicodeBuffer, 1, &Size);

        ++UnicodeBuffer;
        AnsiBuffer += Size;
    }

    Unicode->Begin = UnicodeBuffer;

    return AnsiBuffer - Ansi;
}

BOOL UnInitialize(PVOID BaseAddress)
{
    return FALSE;
}

BOOL Initialize(PVOID BaseAddress)
{
    LdrDisableThreadCalloutsForDll(BaseAddress);

#if ST_VERSION == 2

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY(STCP_ACP,  sizeof(STCP_ACP),   0x15DD14),
        PATCH_MEMORY(0x01B0,    2,                  0x0CC775),
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_JUMP_RVA(0x15D760, GetEncodingByIndex, StubGetEncodingByIndex),
        INLINE_HOOK_JUMP_RVA(0x15E880, UnicodeToACP, StubUnicodeToACP),
        PATCH_FUNCTION(CALL, AUTO_DISASMP | FORCE_JUMP_BACK, 0x15DE51, NakedACPToUnicode_2, 0, &StubACPToUnicode),
    };

    swprintf(Acp, L"ACP %d", CurrentPeb()->AnsiCodePageData[1]);

#elif ST_VERSION == 3

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY(0xC033, 2, 0x08D63C),
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_CALL_RVA_NULL(0x0C2F1A, GetDefaultEncodingIndex),

        INLINE_HOOK_JUMP_RVA(0x0C35CC, GetEncodingByIndex, StubGetEncodingByIndex),
        INLINE_HOOK_JUMP_RVA(0x0C33DB, UnicodeToACP, StubUnicodeToACP),

        PATCH_FUNCTION(CALL, AUTO_DISASMP | FORCE_JUMP_BACK, 0x0C2FCA, NakedACPToUnicode_3, 0, &StubACPToUnicode),
    };

    sprintf(Acp, "ACP %d", CurrentPeb()->AnsiCodePageData[1]);

#endif

    Nt_PatchMemory(p, countof(p), f, countof(f), GetExeModuleHandle());

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

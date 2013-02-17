#include "MyLibraryUser.h"

ULONG GetLoaderSize(PVOID Begin, PVOID End)
{
    ULONG Size;

    Size = (ULONG_PTR)End - (ULONG_PTR)Begin;
    while (*(PBYTE)End == 0xCC)
        --*(PBYTE *)&End;

    return (ULONG_PTR)End - (ULONG_PTR)Begin + 1;
}

#define Hash_LdrLoadDll                 0x8F8ED6B0
#define Hash_LdrAddRefDll               0x3822F35A
#define Hash_LdrGetProcedureAddress     0x01A12CE3

typedef struct
{
    PVOID BaseAddress;
    PVOID AddressOfFunctions;
    PVOID AddressOfNames;
    PVOID AddressOfNameOrdinals;
} FIND_API_INFO;

typedef struct
{
    PVOID LdrLoadDll;
    PVOID LdrAddRefDll;
    PVOID LdrGetProcedureAddress;
    PVOID ModuleHandle;
    union
    {
        UNICODE_STRING  DllName;
        ANSI_STRING     ProcName;
    };
} INIT_IAT_INFO;

typedef struct
{
    ULONG       Count;
    ULONG_PTR   OriginalIatOffset;
} COMPRESSED_IAT_INFO;

ASM VOID upxloader_ProcessImport()
{
    INLINE_ASM
    {
        lea     edi, [esi + 80h];       // compressed_imports
        cmp     [edi]COMPRESSED_IAT_INFO.Count, 0;
        je      upxloader_ProcessImport_End;

        lea     esp, [esp - 30h];

        mov     eax, fs:[30h];          // Peb
        mov     eax, [eax + 0Ch];       // PebLdr
        mov     eax, [eax + 1Ch];       // ntdll LdrModule.InInitializationOrderModuleList
        mov     eax, [eax + 08h];       // ntdll base
        lea     ecx, [esp];
        mov     edx, eax;
        call    InitFindApiInfo;
        lea     ecx, [esp];
        mov     edx, Hash_LdrLoadDll;
        call    GetProcByHash;
        mov     [esp + 10h]INIT_IAT_INFO.LdrLoadDll, eax;

        lea     ecx, [esp];
        mov     edx, Hash_LdrGetProcedureAddress;
        call    GetProcByHash;
        mov     [esp + 10h]INIT_IAT_INFO.LdrGetProcedureAddress, eax;

        lea     ecx, [esp];
        mov     edx, Hash_LdrAddRefDll;
        call    GetProcByHash;
        mov     [esp + 10h]INIT_IAT_INFO.LdrAddRefDll, eax;

        // init iat
        lea     ebp, [esp + 10h];
        mov     eax, [edi]COMPRESSED_IAT_INFO.Count;
INIT_IAT_LOOP:

            mov     ebx, [edi]COMPRESSED_IAT_INFO.OriginalIatOffset;
            lea     ebx, [ebx + esi];
            mov     eax, [edi + 08h];
            lea     edi, [edi + 0Ch];

            // load dll
            mov     dword ptr [ebp]INIT_IAT_INFO.DllName.Length, eax;
            mov     [ebp]INIT_IAT_INFO.DllName.Buffer, edi;
            shr     eax, 16;
            lea     edi, [edi + eax];
            lea     eax, [ebp]INIT_IAT_INFO.ModuleHandle;
            lea     ecx, [ebp]INIT_IAT_INFO.DllName;
            xor     edx, edx;
            push    eax;
            push    ecx;
            push    edx;
            push    edx;
            call    [ebp]INIT_IAT_INFO.LdrLoadDll;
            push    [ebp]INIT_IAT_INFO.ModuleHandle;
            push    1;
            call    [ebp]INIT_IAT_INFO.LdrAddRefDll;

            // init proc address
GET_PROC_ADDRESS_LOOP:

                inc     edi;
                or      al, [edi-1];
//                or      al, al;
                je      INIT_IAT_NEXT_DLL;
                push    ebx;            // FunctionAddress
                jns     IMPORT_BY_NAME;
                movzx   ax, word ptr [edi];
                inc     edi;
                inc     edi;
                push    eax;
                push    0;
                jmp     IMPORT_BY_ORDINAL;

IMPORT_BY_NAME:
                dec     eax;                    // if LdrGetProcedureAddress return STATUS_SUCCESS, eax == 0
                lea     ecx, [eax - 01h];       // eax == 1
                mov     [ebp]INIT_IAT_INFO.ProcName.Buffer, edi;
                repne scasb;
                not     ecx;
                dec     ecx;
                mov     [ebp]INIT_IAT_INFO.ProcName.Length, cx;
                mov     [ebp]INIT_IAT_INFO.ProcName.MaximumLength, cx;
                push    eax;
                lea     ecx, [ebp]INIT_IAT_INFO.ProcName;
                push    ecx;

IMPORT_BY_ORDINAL:

                push    [ebp]INIT_IAT_INFO.ModuleHandle;
                call    [ebp]INIT_IAT_INFO.LdrGetProcedureAddress;
                lea     ebx, [ebx + 04h];
            jmp     GET_PROC_ADDRESS_LOOP;

INIT_IAT_NEXT_DLL:

            lea     edi, [edi + 03h];
            and     edi, 0FFFFFFFCh;
            or      eax, [edi]COMPRESSED_IAT_INFO.Count;
        jnz     INIT_IAT_LOOP;

// INIT_IAT_END:

        lea     esp, [esp + 30h];

        jmp     upxloader_ProcessImport_End;

GetProcByHash:
        lea     esp, [esp - 10h];
        mov     [esp + 00h], ebx;
        mov     [esp + 04h], ebp;
        mov     [esp + 08h], esi;
        mov     [esp + 0Ch], edi;

        mov     ebp, [ecx]FIND_API_INFO.BaseAddress;
        mov     esi, [ecx]FIND_API_INFO.AddressOfNames;
        mov     edi, ecx;

        lodsd;
FIND_LOOP:
            xor     ebx, ebx;
            lea     eax, [eax + ebp];

            movzx   ecx, byte ptr [eax];
HASH_API_LOOP:
                rol     ebx, 0Dh;
                xor     ebx, ecx;
                inc     eax;
                movzx   ecx, byte ptr [eax];
                or      ecx, ecx;
            jnz HASH_API_LOOP;

            xor     ebx, edx;
            je      FOUND_API;

            lodsd;
            or      eax, eax;
        jnz     FIND_LOOP;
        xor     eax, eax;
        jmp     FIND_END;

FOUND_API:
        sub     esi, [edi]FIND_API_INFO.AddressOfNames;
        shr     esi, 1;
        lea     esi, [esi - 02h];
        add     esi, [edi]FIND_API_INFO.AddressOfNameOrdinals;
        movzx   esi, word ptr [esi];
        mov     ecx, [edi]FIND_API_INFO.AddressOfFunctions;
        mov     eax, [ecx + esi * 4];
        lea     eax, [eax + ebp];

FIND_END:

        mov     ebx, [esp + 00h];
        mov     ebp, [esp + 04h];
        mov     esi, [esp + 08h];
        mov     edi, [esp + 0Ch];
        lea     esp, [esp + 10h];

        ret;

InitFindApiInfo:
        mov     [ecx]FIND_API_INFO.BaseAddress, edx;
        mov     eax, edx;
        add     eax, [eax]PIMAGE_DOS_HEADER.e_lfanew;
        mov     eax, [eax]PIMAGE_NT_HEADERS.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
        lea     eax, [eax + edx];   // ExportDirectory

        mov     edx, [eax]PIMAGE_EXPORT_DIRECTORY.AddressOfFunctions;
        mov     [ecx]FIND_API_INFO.AddressOfFunctions, edx;

        mov     edx, [eax]PIMAGE_EXPORT_DIRECTORY.AddressOfNames;
        mov     [ecx]FIND_API_INFO.AddressOfNames, edx;

        mov     edx, [eax]PIMAGE_EXPORT_DIRECTORY.AddressOfNameOrdinals;
        mov     [ecx]FIND_API_INFO.AddressOfNameOrdinals, edx;

        mov     eax, [ecx]FIND_API_INFO.BaseAddress;
        add     [ecx]FIND_API_INFO.AddressOfFunctions, eax;
        add     [ecx]FIND_API_INFO.AddressOfNames, eax;
        add     [ecx]FIND_API_INFO.AddressOfNameOrdinals, eax;

        ret;

upxloader_ProcessImport_End:
    }
}

ASM VOID upxloader_ProcessImportEnd() {}

ASM VOID upxloader_JumpToOep()
{
    INLINE_ASM
    {
        lea     eax, [esi + 80h];
        lea     eax, [eax + 80h];
        mov     [esp + 01Ch], eax;
        popad;
        jmp     eax;
    }
}

ASM VOID upxloader_JumpToOepEnd() {}

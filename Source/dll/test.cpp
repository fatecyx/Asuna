//#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "ntdll.lib")

#include "MyLibraryUser.cpp"

#define THEMIDA

#if defined(ASPROTECT)

#pragma comment(linker,"/ENTRY:DllMain")

// Advance Import Protection

PVOID g_pAddressBase, g_JumpBack, g_ApiEntry;
PVOID g_SHE, g_ESP;
ULONG g_AIPJumpBack;

ASM void sca()  // save_call_addr
{
    INLINE_ASM
    {
        pushfd;
        pushad;
        mov  ecx, g_pAddressBase;
        mov  edi, [ecx];
        xchg eax, ebp;
        stosd;
        mov  [ecx], edi;
        popad;
        popfd;
        mov  eax, [ebx+0x2C];
        sub  eax, ebp;
        ret;
    }
}

// BA 0F 70
// 68 ordinal

ASM void iat()  // skip iat enc
{
    INLINE_ASM
    {
        xor   eax, eax;
        cmp   esi, 0x70;
        jnz   NEXT_CMP;
        mov   esi, 0xF;
        ret;
NEXT_CMP:
        cmp  esi, 0xBA;
        je   NOT_AIP;
        cmp  esi, 0xF;
        je   NOT_AIP;
        nop;
NOT_AIP:
        ret;
    }
}

PVOID STDCALL FixWorker(PBYTE pCall, ULONG_PTR pApiEntry)
{
    PULONG_PTR pIATStart = (PULONG_PTR)0x574000;
    PULONG_PTR pIATEnd   = pIATStart + 0x42C / sizeof(ULONG_PTR);

    while (pIATStart < pIATEnd)
    {
        if (*pIATStart != pApiEntry)
        {
            ++pIATStart;
            continue;
        }

        *(PWORD)pCall = *pCall == CALL ? 0x15FF : 0x25FF;
        *(PULONG_PTR)(pCall + 2) = (ULONG_PTR)pIATStart;
        break;
    }

    return pCall;
}

ASM void fix()
{
    INLINE_ASM
    {
        pushfd;
        pushad;
        mov  eax, JUMP_BACK;
        mov  g_JumpBack, eax;
        mov  esi, g_pAddressBase;
        add  esi, 4;

PROC_AIP:
        lodsd;
        or   eax, eax;
        je   PROC_END;
        xor  ecx, ecx;
        mov  edx, fs:[ecx];
        pushfd;
        pushad;
        mov  g_ESP, esp;
        jmp  eax;
JUMP_BACK:
        mov esp, g_ESP;
        mov g_ApiEntry, edx;
        popad;
        popfd;
        mov  fs:[ecx], edx;
        push g_ApiEntry;
        push eax;
        call FixWorker;
        jmp PROC_AIP;

PROC_END:
        popad;
        popfd;
        ret;
    }
}

ASM void jbk()
{
    INLINE_ASM
    {
        jmp g_JumpBack;
    }
}

ASM void spec()
{
    INLINE_ASM
    {
        xchg eax, edx;
        jmp jbk;
    }
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    if (ulReason == DLL_PROCESS_ATTACH)
    {
        g_pAddressBase = VirtualAllocEx(
                            NtCurrentProcess(),
                            NULL,
                            MEMORY_PAGE_SIZE * 10,
                            MEM_RESERVE|MEM_COMMIT,
                            PAGE_READWRITE);
        if (g_pAddressBase == NULL)
            return FALSE;
        *(PULONG_PTR)g_pAddressBase = (ULONG_PTR)g_pAddressBase + 4;
    }
    else if (ulReason == DLL_PROCESS_DETACH)
    {
        VirtualFreeEx(NtCurrentProcess(), g_pAddressBase, 0, MEM_RELEASE);
    }

    return TRUE;
}

#elif defined(THEMIDA) // ASPROTECT

FARPROC g_ApiEntry;

/*
  pop     eax
  cmp     al, 00E8h
  mov     ax, 015FFh
  je      short 02385023
  mov     ax, 025FFh
  stos    word ptr es:[edi]
  lea     eax, dword ptr [ebp+0AFD1742h]
  mov     dword ptr [eax], ecx
  add     dword ptr [eax], edi
  add     dword ptr [eax], 04h
  jmp     short 023850AB


  pop     eax
  cmp     al, 0E8h
  mov     ax, 015FFh
  je L005
  mov     ax, 025FFh
L005:
  stos    word ptr es:[edi]
  lea     eax, dword ptr [ebp+0AF4E4EFh]
  mov     dword ptr [eax], ecx
  add     dword ptr [eax], edi
  add     dword ptr [eax], 04h
  nop


*/

/*

pop     eax  //(Initial CPU selection)
cmp     al, 0xE8
mov     ax, 0x15FF
je      short 0058DDFC
mov     ax, 0x25FF
stos    word ptr es:[edi]
lea     eax, dword ptr [ebp+0x2AEE1811]
mov     dword ptr [eax], ecx
add     dword ptr [eax], edi
add     dword ptr [eax], 0x4
jmp     0058DE9A

58 3C E8 66 B8 FF 15 74 04 66 B8 FF 25 66 AB 8D 85 11 18 EE 2A 89 08 01 38 83 00 04 E9 8A 00 00 00 90 90
*/

EXTC DECL_EXPORT ASM Void CDECL set()
{
    INLINE_ASM
    {
        call ebx;
        mov  g_ApiEntry, eax;
        ret;
    }
}

EXTC DECL_EXPORT ASM Void CDECL get()
{
    INLINE_ASM
    {
        mov eax, g_ApiEntry;
        ret;
    }
}

#define TMD_TEMP

#if defined(TMD_TEMP)
    #define IAT_RVA_ADD         0xE8233783
    #define IAT_RVA_XOR         0x2A6E3E50
    #define CALL_RVA_ADD        0x6CBD6BF7
    #define CALL_RVA_XOR        0x76473C93
    #define MODULE_BASE_ADDR    dword ptr [ebp+0xB220CC1]
    #define IS_SKIP             dword ptr [ebp+0xB221521]
#elif defined(KUD_WAFTER)
    #define IAT_RVA_ADD         0xABB1F69
    #define IAT_RVA_XOR         0x66919C
    #define CALL_RVA_ADD        0x287B1258
    #define CALL_RVA_XOR        0xD16C9BB7
    #define MODULE_BASE_ADDR    dword ptr [ebp+0xAFD0309]
    #define IS_SKIP             dword ptr [ebp+0xAFD0E69]
#elif defined(FLYABLE_CANDY_HEART)
    #define IAT_RVA_ADD         0x8B4BA92E
    #define IAT_RVA_XOR         0x3CD1E3AE
    #define CALL_RVA_ADD        0x52ABD69F
    #define CALL_RVA_XOR        0x9F432520
    #define MODULE_BASE_ADDR    dword ptr [ebp+0x6C41429]
    #define IS_SKIP             dword ptr [ebp+0x6C40339]
#elif defined(SOTES)
    #define IAT_RVA_ADD         0x96F80549
    #define IAT_RVA_XOR         0x6A0CF498
    #define CALL_RVA_ADD        0x4BC7A172
    #define CALL_RVA_XOR        0xCB39E97E
    #define MODULE_BASE_ADDR    dword ptr [ebp+0x6A0323D]
    #define IS_SKIP             dword ptr [ebp+0x6A00F21]
#elif defined(TACTICS)
    #define IAT_RVA_ADD         0x2DCD03EE
    #define IAT_RVA_XOR         0x7E6839A5
    #define CALL_RVA_ADD        0xC5E1FA21
    #define CALL_RVA_XOR        0x185985CF
    #define MODULE_BASE_ADDR    dword ptr [ebp+0x98A1525]
    #define IS_SKIP             dword ptr [ebp+0x98A0589]
#elif defined(AIYOKU)
    #define IAT_RVA_ADD         0x867D6D82
    #define IAT_RVA_XOR         0x47920620
    #define CALL_RVA_ADD        0x88482E12
    #define CALL_RVA_XOR        0x98779195
    #define MODULE_BASE_ADDR    dword ptr [ebp+0x98D0921]
    #define IS_SKIP             dword ptr [ebp+0x98D02ED]
#elif defined(FONT_CREATOR_62)
    #define IAT_RVA_ADD         0xF43452C0
    #define IAT_RVA_XOR         0x6E613EDB
    #define CALL_RVA_ADD        0x91AA9507
    #define CALL_RVA_XOR        0xDC124071
    #define MODULE_BASE_ADDR    dword ptr [ebp+0xA260BF9]
    #define IS_SKIP             dword ptr [ebp+0xA261299]
#elif defined(IKINARI_ANATANI_KOISHITEIRU)
    #define IAT_RVA_ADD         0xD84DC72C
    #define IAT_RVA_XOR         0xA76BD018
    #define CALL_RVA_ADD        0xE6C9E1A0
    #define CALL_RVA_XOR        0x059DD64C
    #define MODULE_BASE_ADDR    dword ptr [ebp+0xA531309]
    #define IS_SKIP             dword ptr [ebp+0xA530041]
#elif defined(NEKOKOI)
    #define IAT_RVA_ADD         0x9785F7F2
    #define IAT_RVA_XOR         0x978668CD
    #define CALL_RVA_ADD        0xE9D6BCD0
    #define CALL_RVA_XOR        0x5F6B038D
    #define MODULE_BASE_ADDR    dword ptr [ebp+0x9430155]
    #define IS_SKIP             dword ptr [ebp+0x94305A9]
#elif defined(TENKA)
    #define IAT_RVA_ADD         0xFDCA5C00
    #define IAT_RVA_XOR         0xD51C8B05
    #define CALL_RVA_ADD        0x5B161AA4
    #define CALL_RVA_XOR        0x2FF44FEC
    #define MODULE_BASE_ADDR    dword ptr [ebp+0x8F50CD1]
    #define IS_SKIP             dword ptr [ebp+0x8F50349]
#else
    #error
#endif

/************************************************************************
add eax, E8233783
rol eax, 5
xor eax, 2A6E3E50

  392FF1DF
  21532962
  2A652C44
  000B1214

  16698E0D
  717FA8B1
  2FF5162E
  000159C2

************************************************************************/

EXTC DECL_EXPORT ASM Void CDECL t()
{
    INLINE_ASM
    {
        add     eax, IAT_RVA_ADD
        rol     eax, 05h
        xor     eax, IAT_RVA_XOR
        mov     ecx, g_ApiEntry;
        add     eax, MODULE_BASE_ADDR
        mov     dword ptr [eax], ecx
        xchg    eax, ecx
L007:
        lodsd
        cmp     eax, -01h
        jnz L014
        cmp     dword ptr [esi], 0DDDDDDDDh
        jnz L014
        ret
L014:
        cmp     IS_SKIP, 01h
        je L007
        cmp     dword ptr [esi], 0AAAAAAAAh
        push    015FFh
        jnz L021
        mov     dword ptr [esp], 025FFh
        add     esi, 04h
L021:
        add     eax, CALL_RVA_ADD
        rol     eax, 05h
        xor     eax, CALL_RVA_XOR
        add     eax, MODULE_BASE_ADDR
        pop     dword ptr [eax]
        mov     dword ptr [eax+02h], ecx
        jmp L007
    }
}

#define CODE_BASE   0x401000
#define CODE_SIZE   0x1C8A000

#define NTDLL_BASE  0x77020000
#define NTDLL_SIZE  0xD6000

/************************************************************************
  ntdll.DbgBreakPoint
  ntdll.DbgUiRemoteBreakin
  ntdll.ZwOpenThread

  NtSetInformationThread(NtCurrentThread(), ThreadHideFromDebugger, NULL, 0, NULL);
  NtQueryInformationProcess(NtCurrentProcess(), ProcessDebugPort, &DebugPort, sizeof(ULONG));

  hook all module IAT

  FreeLibrary
  GetProcAddress
  LoadLibraryExA
  LoadLibraryExW
  GetModuleFileNameA
  GetModuleFileNameW
************************************************************************/

#pragma comment(linker,"/ENTRY:DllMain")

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            LdrDisableThreadCalloutsForDll(hInstance);
//            AllocConsole();
//            AddVectoredExceptionHandler(True, VectoredHandler);
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

EXTC DECL_EXPORT ASM VOID CDECL d() {}

// THEMIDA

#elif defined(SECUROM)

#pragma comment(linker,"/ENTRY:DllMain")

#include <map>
#include "my_commsrc.h"

using namespace std;

map<PVOID, ULONG> *g_pAllocMap;

PVOID WINAPI MyVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
    PVOID pAddress = VirtualAllocEx(NtCurrentProcess(), lpAddress, dwSize, flAllocationType, flProtect);

    LOOP_ONCE
    {
        if (!(flAllocationType & MEM_COMMIT))
            break;

        if ((ULONG_PTR)_ReturnAddress() < 0x401000 || (ULONG_PTR)_ReturnAddress() >= 0x20AD000)
            break;

        (*g_pAllocMap)[pAddress] = dwSize;
    }

    return pAddress;
}

BOOL WINAPI MyVirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType)
{
    if (g_pAllocMap->count(lpAddress))
        g_pAllocMap->erase(lpAddress);

    return VirtualFreeEx(NtCurrentProcess(), lpAddress, dwSize, dwFreeType);
}

typedef VOID (CDECL *SecuromInitFunc)(...);

ULONG_PTR g_x = 0x01006CFD;

ASM VOID CDECL OldAddToMap(PVOID, PVOID)
{
    INLINE_ASM
    {
        push    ebp
        mov     ebp, esp
        push    ecx
        mov     ecx, dword ptr [0x165BC58]
        jmp     g_x;
    }
}

VOID AddToMap(PVOID key, PVOID pSRData)
{
    ULONG Length;
    WCHAR path[MAX_PATH];
    HANDLE hFile;

    Length = GetExecuteDirectoryW(path, countof(path));
    swprintf(path + Length, L"SRData\\%08X", pSRData);

    hFile = CreateFileW(
                path,
                GENERIC_WRITE,
                FILE_SHARE_READ,
                NULL,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        ULONG Bytes;
/*
        PBYTE p = (PBYTE)pSRData + 0x1000;
        while (*--p == 0);
        Length = ++p - (PBYTE)pSRData;
*/
        struct
        {
            PVOID Key;
            PVOID Base;
            ULONG Length;
        } hdr;

        Length = *(PULONG)((ULONG_PTR)key + 0xA);
        hdr.Key = key;
        hdr.Base = pSRData;
        hdr.Length = Length;

        WriteFile(hFile, &hdr, sizeof(hdr), &Bytes, NULL);
        WriteFile(hFile, pSRData, Length, &Bytes, NULL);
        CloseHandle(hFile);
    }
}

DECL_EXPORT VOID CDECL AddMaps(PVOID p)
{
    struct
    {
        PVOID Key;
        PVOID Base;
    } *entry;

    *(PVOID *)&entry = p;
    while (entry->Key != 0)
    {
        AddToMap(entry->Key, entry->Base);
        ++entry;
    }
}

typedef FILE* (CDECL *pfopen)(const char *filename, const char *mode);
typedef size_t (CDECL *pfread)(void *buffer,size_t size,size_t count,FILE *stream);
typedef int (CDECL *pfseek)(FILE *stream,long offset,int origin);
typedef long (CDECL *pftell)(FILE *stream);
typedef int (CDECL *pfclose)(FILE *stream);

/************************************************************************
  CreateFileA: 0xD40764
************************************************************************/

//WCHAR prefix[] = L"K:\\Program Files\\EDZero\\data";
WCHAR prefix[] = L"J:\\Falcom\\ED_Zero\\data";

LONG STDCALL DecCallback(PVOID, LPWIN32_FIND_DATAW pfd, ULONG_PTR)
{
    ULONG Header;
    CFileDisk file;

    file.Open(pfd->cFileName);
    file.Read(&Header, 4);
    file.Close();

    if (Header != TAG4('SDFA'))
        return 0;

    CHAR FileName[MAX_PATH];

    PrintConsoleW(L"%s\n", pfd->cFileName);
    WideCharToMultiByte(CP_ACP, 0, pfd->cFileName, -1, FileName, sizeof(FileName), NULL, NULL);

    pfopen  fopen   = (pfopen) 0x6585C3;
    pfseek  fseek   = (pfseek) 0x658587;
    pftell  ftell   = (pftell) 0x6585B9;
    pfread  fread   = (pfread) 0x6580FA;
    pfclose fclose  = (pfclose)0x65994B;

    fclose = (pfclose)0x659955;     // zero_tc

    FILE *fp = fopen(FileName, "rb");
    fseek(fp, 0, SEEK_END);
    Header = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    PBYTE p = new BYTE[Header];
    if (fread(p, Header, 1, fp) == 0)
        PrintConsoleW(L"failed\n");

    fclose(fp);

    ULONG len;
    static WCHAR suffix[] = L"_sc";

    len = StrLengthW(pfd->cFileName) - countof(prefix) + 1 + 1;
    RtlMoveMemory(
        pfd->cFileName + countof(prefix) - 1 + countof(suffix) - 1,
        pfd->cFileName + countof(prefix) - 1,
        len * 2
    );

    CopyMemory(
        pfd->cFileName + countof(prefix) - 1,
        suffix,
        sizeof(suffix) - 2
    );

    WCHAR c, *pname;

    pname = findnamew(pfd->cFileName);
    c = *pname;
    *pname = 0;
    MyCreateDirectoryW(pfd->cFileName);
    *pname = c;
    if (file.Create(pfd->cFileName))
    {
        file.Write(p, Header);
    }

    delete[] p;

    return 0;
}

EXTC_EXPORT VOID CDECL dec()
{
    SetPriorityClass(NtCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
    AllocConsole();

    EnumDirectoryFiles(
        NULL,
        L"*.*",
        0,
        prefix,
        NULL,
        DecCallback,
        0,
        ENUM_DIRECTORY_FILES_FLAG_ENUMSUBDIR
    );

    FreeConsole();

    ExitProcess(0);
}

EXTC_EXPORT VOID Print()
{
    AllocConsole();
    map<PVOID, ULONG>::iterator beg, end;

    beg = g_pAllocMap->begin();
    while (beg != g_pAllocMap->end())
    {
        PrintConsoleW(L"%08X %08X\n", beg->first, beg->second);
        ++beg;
    }
}

DWORD MyGetCurrentThreadId()
{
    return 0x1000;
}

DWORD MyGetTickCount()
{
    static DWORD Count;

    return Count += 0x4001;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);

//            g_pAllocMap = new map<PVOID, ULONG>;

            {
                HMODULE hModule = GetModuleHandleW(NULL);
                MEMORY_PATCH p[] =
                {
                    { (ULONG_PTR)MyGetCurrentThreadId,  4, 0x1512E10 },
                    { (ULONG_PTR)MyGetTickCount,        4, 0x1512D94 },  // GetTickCount
                };

                MEMORY_FUNCTION_PATCH f[] =
                {
//                    { JUMP, (ULONG_PTR)VirtualAlloc, MyVirtualAlloc },
//                    { JUMP, (ULONG_PTR)VirtualFree, MyVirtualFree },

//                    { JUMP, (ULONG_PTR)0x42C3D1, dec }, // zero_sc
                    { JUMP, (ULONG_PTR)0x427DE8, dec }, // zero_tc
                };

                PatchMemory(NULL, 0, f, countof(f), hModule);
            }
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

#else


#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "ddraw.lib")

#include "my_api.cpp"
#include "my_crtadd.cpp"

#if 0
#include "vm.h"

DECL_ALIGN(16) PBYTE Handlers[0x1000] =
{
    (PBYTE)VM + 0x00000, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x655A9, (PBYTE)VM + 0xBB1AC,
    (PBYTE)VM + 0x622F5, (PBYTE)VM + 0x498E5, (PBYTE)VM + 0x00000, (PBYTE)VM + 0xC2554,
    (PBYTE)VM + 0x9C803, (PBYTE)VM + 0xB857D, (PBYTE)VM + 0xADFCF, (PBYTE)VM + 0x0E0BD,
    (PBYTE)VM + 0xD5299, (PBYTE)VM + 0x00000, (PBYTE)VM + 0xF4DE2, (PBYTE)VM + 0x1B377,
    (PBYTE)VM + 0x198F1, (PBYTE)VM + 0xD1194, (PBYTE)VM + 0x61FED, (PBYTE)VM + 0xB60E8,
    (PBYTE)VM + 0xDA3B2, (PBYTE)VM + 0x0F314, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x1E495,
    (PBYTE)VM + 0x00000, (PBYTE)VM + 0xC0A32, (PBYTE)VM + 0x473FB, (PBYTE)VM + 0x0D151,
    (PBYTE)VM + 0x9031A, (PBYTE)VM + 0xE3407, (PBYTE)VM + 0xCA8F2, (PBYTE)VM + 0xB6429,
    (PBYTE)VM + 0xC5DF7, (PBYTE)VM + 0x00000, (PBYTE)VM + 0xEA52A, (PBYTE)VM + 0x00000,
    (PBYTE)VM + 0x91A3E, (PBYTE)VM + 0x1B50C, (PBYTE)VM + 0xCAE75, (PBYTE)VM + 0x3FE61,
    (PBYTE)VM + 0xAB44F, (PBYTE)VM + 0x90D03, (PBYTE)VM + 0x9C8FF, (PBYTE)VM + 0x624FF,
    (PBYTE)VM + 0x90D0D, (PBYTE)VM + 0x3AB6B, (PBYTE)VM + 0xE449D, (PBYTE)VM + 0x853C0,
    (PBYTE)VM + 0x3A1D9, (PBYTE)VM + 0xCA855, (PBYTE)VM + 0xD09D7, (PBYTE)VM + 0x4F739,
    (PBYTE)VM + 0x06161, (PBYTE)VM + 0x5B793, (PBYTE)VM + 0x9D332, (PBYTE)VM + 0xEEA38,
    (PBYTE)VM + 0xEA22F, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x00000,
    (PBYTE)VM + 0x914E2, (PBYTE)VM + 0x00000, (PBYTE)VM + 0xADA14, (PBYTE)VM + 0xB8FA0,
    (PBYTE)VM + 0xB07C3, (PBYTE)VM + 0xEC54C, (PBYTE)VM + 0x41807, (PBYTE)VM + 0x00000,
    (PBYTE)VM + 0x00000, (PBYTE)VM + 0x2D69E, (PBYTE)VM + 0xA6E32, (PBYTE)VM + 0xCC49B,
    (PBYTE)VM + 0xA4A93, (PBYTE)VM + 0x72733, (PBYTE)VM + 0x905E2, (PBYTE)VM + 0xF2AD0,
    (PBYTE)VM + 0x00000, (PBYTE)VM + 0x9E3B8, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x1ADA4,
    (PBYTE)VM + 0x51138, (PBYTE)VM + 0xE78E2, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x3F9FA,
    (PBYTE)VM + 0x6F99A, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x02FC0, (PBYTE)VM + 0x168EF,
    (PBYTE)VM + 0xB0034, (PBYTE)VM + 0x3AFF9, (PBYTE)VM + 0x3E760, (PBYTE)VM + 0xF97EF,
    (PBYTE)VM + 0xCB27A, (PBYTE)VM + 0x59E46, (PBYTE)VM + 0x6D86F, (PBYTE)VM + 0x0D29F,
    (PBYTE)VM + 0x0A538, (PBYTE)VM + 0x50E14, (PBYTE)VM + 0x2C0E3, (PBYTE)VM + 0x00000,
    (PBYTE)VM + 0x00000, (PBYTE)VM + 0x8FA9B, (PBYTE)VM + 0xCA919, (PBYTE)VM + 0x4DAB5,
    (PBYTE)VM + 0xB6FCD, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x31E05, (PBYTE)VM + 0x513F5,
    (PBYTE)VM + 0x0D146, (PBYTE)VM + 0xD303A, (PBYTE)VM + 0x36A10, (PBYTE)VM + 0x00000,
    (PBYTE)VM + 0x0A297, (PBYTE)VM + 0xD7E0B, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x56752,
    (PBYTE)VM + 0x00000, (PBYTE)VM + 0x00000, (PBYTE)VM + 0xF6F3F, (PBYTE)VM + 0x8513D,
    (PBYTE)VM + 0x00000, (PBYTE)VM + 0x69923, (PBYTE)VM + 0xF4BD4, (PBYTE)VM + 0xD6BBA,
    (PBYTE)VM + 0xB20CD, (PBYTE)VM + 0x72BCA, (PBYTE)VM + 0x42054, (PBYTE)VM + 0x526FF,
    (PBYTE)VM + 0xB104A, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x5F3C3, (PBYTE)VM + 0x42645,
    (PBYTE)VM + 0x73A69, (PBYTE)VM + 0xF1EFC, (PBYTE)VM + 0x6A323, (PBYTE)VM + 0x00000,
    (PBYTE)VM + 0x71635, (PBYTE)VM + 0x4C9C6, (PBYTE)VM + 0x1957E, (PBYTE)VM + 0x94048,
    (PBYTE)VM + 0x6945F, (PBYTE)VM + 0xBB339, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x10AA4,
    (PBYTE)VM + 0x00000, (PBYTE)VM + 0xC562D, (PBYTE)VM + 0xF4718, (PBYTE)VM + 0x00000,
    (PBYTE)VM + 0x52465, (PBYTE)VM + 0x63FB5, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x780B8,
    (PBYTE)VM + 0x320C7, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x00000,
    (PBYTE)VM + 0x364D2, (PBYTE)VM + 0xC2716, (PBYTE)VM + 0x065F6, (PBYTE)VM + 0x48844,
    (PBYTE)VM + 0x4A774, (PBYTE)VM + 0xB4F09, (PBYTE)VM + 0xF99D2, (PBYTE)VM + 0x74738,
    (PBYTE)VM + 0x8CF34, (PBYTE)VM + 0xB5961, (PBYTE)VM + 0x1AD3D, (PBYTE)VM + 0x912A0,
    (PBYTE)VM + 0x45DA3, (PBYTE)VM + 0xAF7BB, (PBYTE)VM + 0x475CB, (PBYTE)VM + 0xAFF45,
    (PBYTE)VM + 0x00000, (PBYTE)VM + 0x9C234, (PBYTE)VM + 0x01779, (PBYTE)VM + 0x4CB59,
    (PBYTE)VM + 0x2CA16, (PBYTE)VM + 0x692FF, (PBYTE)VM + 0xCFFAF, (PBYTE)VM + 0x00000,
    (PBYTE)VM + 0x586D2, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x00000, (PBYTE)VM + 0xB15A0,
    (PBYTE)VM + 0x919B3, (PBYTE)VM + 0x7C55C, (PBYTE)VM + 0x7A80D, (PBYTE)VM + 0x62581,
    (PBYTE)VM + 0x147BF, (PBYTE)VM + 0x41E4B, (PBYTE)VM + 0x3600D, (PBYTE)VM + 0x4A3FB,
    (PBYTE)VM + 0x00000, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x00000, (PBYTE)VM + 0x00000,
};

DECL_ALIGN(16) PBYTE pHandlers[0x1000] =
{
    (PBYTE)Handlers + 0x0000, (PBYTE)Handlers + 0x000C, (PBYTE)Handlers + 0x0018, (PBYTE)Handlers + 0x0024,
    (PBYTE)Handlers + 0x0030, (PBYTE)Handlers + 0x003C, (PBYTE)Handlers + 0x0048, (PBYTE)Handlers + 0x0054,
    (PBYTE)Handlers + 0x0060, (PBYTE)Handlers + 0x006C, (PBYTE)Handlers + 0x0078, (PBYTE)Handlers + 0x0084,
    (PBYTE)Handlers + 0x0090, (PBYTE)Handlers + 0x009C, (PBYTE)Handlers + 0x00A8, (PBYTE)Handlers + 0x00B4,
    (PBYTE)Handlers + 0x00C0, (PBYTE)Handlers + 0x00CC, (PBYTE)Handlers + 0x00D8, (PBYTE)Handlers + 0x00E4,
    (PBYTE)Handlers + 0x00F0, (PBYTE)Handlers + 0x00FC, (PBYTE)Handlers + 0x0108, (PBYTE)Handlers + 0x0114,
    (PBYTE)Handlers + 0x0120, (PBYTE)Handlers + 0x012C, (PBYTE)Handlers + 0x0138, (PBYTE)Handlers + 0x0144,
    (PBYTE)Handlers + 0x0150, (PBYTE)Handlers + 0x015C, (PBYTE)Handlers + 0x0168, (PBYTE)Handlers + 0x0174,
    (PBYTE)Handlers + 0x0180, (PBYTE)Handlers + 0x018C, (PBYTE)Handlers + 0x0198, (PBYTE)Handlers + 0x01A4,
    (PBYTE)Handlers + 0x01B0, (PBYTE)Handlers + 0x01BC, (PBYTE)Handlers + 0x01C8, (PBYTE)Handlers + 0x01D4,
    (PBYTE)Handlers + 0x01E0, (PBYTE)Handlers + 0x01EC, (PBYTE)Handlers + 0x01F8, (PBYTE)Handlers + 0x0204,
    (PBYTE)Handlers + 0x0210, (PBYTE)Handlers + 0x021C, (PBYTE)Handlers + 0x0228, (PBYTE)Handlers + 0x0234,
    (PBYTE)Handlers + 0x0240, (PBYTE)Handlers + 0x024C, (PBYTE)Handlers + 0x0258, (PBYTE)Handlers + 0x0264,
    (PBYTE)Handlers + 0x0270, (PBYTE)Handlers + 0x027C, (PBYTE)Handlers + 0x0288, (PBYTE)Handlers + 0x0294,
    (PBYTE)Handlers + 0x02A0, (PBYTE)Handlers + 0x02AC, (PBYTE)Handlers + 0x02B8, (PBYTE)Handlers + 0x02C4,
    (PBYTE)Handlers + 0x02D0, (PBYTE)Handlers + 0x02DC, (PBYTE)Handlers + 0x02E8, (PBYTE)Handlers + 0x02F4,
};

DECL_ALIGN(16) PBYTE Handlers2[0x1000] =
{
    (PBYTE)VM + 0x00000, (PBYTE)VM + 0x01779, (PBYTE)VM + 0x2D69E, (PBYTE)VM + 0x8FA9B,
    (PBYTE)VM + 0x31E05, (PBYTE)VM + 0x7A80D, (PBYTE)VM + 0xEA22F, (PBYTE)VM + 0x59E46,
    (PBYTE)VM + 0xAB44F, (PBYTE)VM + 0xCAE75, (PBYTE)VM + 0x586D2, (PBYTE)VM + 0x065F6,
    (PBYTE)VM + 0xC0A32, (PBYTE)VM + 0x4F739, (PBYTE)VM + 0x9C234, (PBYTE)VM + 0xB5961,
    (PBYTE)VM + 0xEEA38, (PBYTE)VM + 0xB857D, (PBYTE)VM + 0x2C0E3, (PBYTE)VM + 0x6945F,
    (PBYTE)VM + 0x3600D, (PBYTE)VM + 0x6F99A, (PBYTE)VM + 0x0A538, (PBYTE)VM + 0x198F1,
    (PBYTE)VM + 0x2CA16, (PBYTE)VM + 0xA6E32, (PBYTE)VM + 0x45DA3, (PBYTE)VM + 0x36A10,
    (PBYTE)VM + 0xF2AD0, (PBYTE)VM + 0x780B8, (PBYTE)VM + 0x0D151, (PBYTE)VM + 0x4C9C6,
    (PBYTE)VM + 0x73A69, (PBYTE)VM + 0x3E760, (PBYTE)VM + 0xF4718, (PBYTE)VM + 0xB6FCD,
    (PBYTE)VM + 0xF4DE2, (PBYTE)VM + 0xD09D7, (PBYTE)VM + 0x4DAB5, (PBYTE)VM + 0xD6BBA,
    (PBYTE)VM + 0x52465, (PBYTE)VM + 0x10AA4, (PBYTE)VM + 0x63FB5, (PBYTE)VM + 0x8513D,
    (PBYTE)VM + 0x3AB6B, (PBYTE)VM + 0xD7E0B, (PBYTE)VM + 0x02FC0, (PBYTE)VM + 0xE449D,
    (PBYTE)VM + 0x4A3FB, (PBYTE)VM + 0x692FF, (PBYTE)VM + 0x9D332, (PBYTE)VM + 0x94048,
    (PBYTE)VM + 0xF99D2, (PBYTE)VM + 0x0D146, (PBYTE)VM + 0x6A323, (PBYTE)VM + 0xB6429,
    (PBYTE)VM + 0x48844, (PBYTE)VM + 0x168EF, (PBYTE)VM + 0x72BCA, (PBYTE)VM + 0xADA14,
    (PBYTE)VM + 0xCA8F2, (PBYTE)VM + 0x42645, (PBYTE)VM + 0x320C7,
};

#include "vm_context.h"

/************************************************************************
 first VM_CONTEXT + 0xC4
 from  0012C894
 from  VM_Stack + 1FF8
 fuck.......
 src   0x4303647
************************************************************************/

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
//    WCHAR Buffer[0x400];

    static ULONG Count;

    if (Count < 6)
    {
        ++Count;
        return EXCEPTION_CONTINUE_SEARCH;
    }
/*
    swprintf(
        Buffer,
        L"code = %08X, addr = %08X\r\n"
        L"eax = %08X\r\n"
        L"ecx = %08X\r\n"
        L"edx = %08X\r\n"
        L"ebx = %08X\r\n"
        L"esp = %08X\r\n"
        L"ebp = %08X\r\n"
        L"esi = %08X\r\n"
        L"edi = %08X\r\n",
        ExceptionInfo->ExceptionRecord->ExceptionCode,
        ExceptionInfo->ExceptionRecord->ExceptionAddress,
        ExceptionInfo->ContextRecord->Eax,
        ExceptionInfo->ContextRecord->Ecx,
        ExceptionInfo->ContextRecord->Edx,
        ExceptionInfo->ContextRecord->Ebx,
        ExceptionInfo->ContextRecord->Esp,
        ExceptionInfo->ContextRecord->Ebp,
        ExceptionInfo->ContextRecord->Esi,
        ExceptionInfo->ContextRecord->Edi
    );
*/
    FILE *fp = fopen("E:\\Desktop\\FortuneSummoners\\exp.txt", "ab+");
    if (fp)
    {
        fprintf(
            fp,
            "code = %08X, addr = %08X\r\n"
            "eax = %08X\r\n"
            "ecx = %08X\r\n"
            "edx = %08X\r\n"
            "ebx = %08X\r\n"
            "esp = %08X\r\n"
            "ebp = %08X\r\n"
            "esi = %08X\r\n"
            "edi = %08X\r\n"
            "\r\n",
            ExceptionInfo->ExceptionRecord->ExceptionCode,
            ExceptionInfo->ExceptionRecord->ExceptionAddress,
            ExceptionInfo->ContextRecord->Eax,
            ExceptionInfo->ContextRecord->Ecx,
            ExceptionInfo->ContextRecord->Edx,
            ExceptionInfo->ContextRecord->Ebx,
            ExceptionInfo->ContextRecord->Esp,
            ExceptionInfo->ContextRecord->Ebp,
            ExceptionInfo->ContextRecord->Esi,
            ExceptionInfo->ContextRecord->Edi
        );

        fclose(fp);
    }

//    MessageBoxW(NULL, Buffer, NULL, 64);

    return EXCEPTION_CONTINUE_SEARCH;
}

DECL_ALIGN(16) BYTE VM_Stack[0x2000];

static ULONG Fuck = 0xC9078831;

#define SET_RVA(RVA1, RVA2) *(PULONG)((ULONG_PTR)VM_CONTEXT + RVA1) = (ULONG)VM_CONTEXT + (RVA2)
#define SET_VAL(RVA, Val)   *(PULONG)((ULONG_PTR)VM_CONTEXT + RVA) = (ULONG)(Val)

LANGID MyGetSystemDefaultLangID()
{
    return 0x411;
}
#endif
ULONG g_CountA, g_CountW;

BOOL WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    BOOL Result = PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);

    if (Result == FALSE)
    {
        ULONG TickCount;
        static ULONG LastTickCount;

        TickCount = GetTickCount();
        if (TickCount - LastTickCount < 10 && --g_CountA == 0)
        {
            g_CountA = 4;
            SleepEx(10, FALSE);
        }
        LastTickCount = TickCount;
    }

    return Result;
}

BOOL WINAPI MyPeekMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    BOOL Result = PeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);

    if (Result == FALSE)
    {
        ULONG TickCount;
        static ULONG LastTickCount;

        TickCount = GetTickCount();
        if (TickCount - LastTickCount < 10 && --g_CountW == 0)
        {
            g_CountW = 4;
            SleepEx(10, FALSE);
        }
        LastTickCount = TickCount;
    }

    return Result;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    if (ulReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hInstance);

        HMODULE hModule, hModuleEng;

//        hModule = GetModuleHandleW(NULL);
        hModuleEng = GetModuleHandleW(L"Engine.dll");
        hModule = hModuleEng;
        g_CountW = 4;
        g_CountA = 4;

        MEMORY_PATCH p[] =
        {
            { (ULONG_PTR)MyPeekMessageW, 4, IATLookupRoutineRVAByEntry(hModule, PeekMessageW) },
            { (ULONG_PTR)MyPeekMessageA, 4, IATLookupRoutineRVAByEntry(hModule, PeekMessageA) },
//            { (ULONG_PTR)MyPeekMessageW, 4, (ULONG_PTR)IATLookupRoutineByEntry(hModuleEng, PeekMessageW) - (ULONG_PTR)hModule },
//            { (ULONG_PTR)MyPeekMessageA, 4, (ULONG_PTR)IATLookupRoutineByEntry(hModuleEng, PeekMessageA) - (ULONG_PTR)hModule },
        };
/*
//        AddVectoredExceptionHandler(TRUE, VectoredHandler);
        *(PULONG_PTR)0x4303A03 = (ULONG_PTR)VM_CONTEXT;
        *(PULONG_PTR)0x4307E26 = (ULONG_PTR)VM_Stack;
        *(PULONG_PTR)0x4303647 = (ULONG_PTR)&Fuck;
//        *(PULONG_PTR)0x430645F = (ULONG_PTR)Sleep;

//        *(PULONG_PTR)0x4307E26 = (ULONG_PTR)VirtualAllocEx(NtCurrentProcess(), NULL, 0x2000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
//        VirtualAllocEx(NtCurrentProcess(), (PVOID)0x3F0000, 0x2000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

        SET_RVA(0x3C4, 0x84);
        SET_RVA(0x40C, 0x7D0);
        SET_RVA(0x474, 0x74);
        SET_VAL(0x4C0, VM);
        SET_RVA(0x524, 0xEC);
        SET_VAL(0x594, Handlers2);
        SET_VAL(0x5DC, pHandlers);

        MEMORY_PATCH p[] =
        {
            { 0x58081,  3, 0x1D8061 },
            { 0xEB,     1, 0x18D2D6 },

            { (ULONG)MyGetSystemDefaultLangID, 4, IATLookupRoutineRVAByEntry(hModule, GetSystemDefaultLangID) },
        };
*/
        PatchMemory(p, countof(p), NULL, 0, hModule);
    }

    return TRUE;
}

#endif
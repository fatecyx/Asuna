// 弼に竃でにけりわが禅は

#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/MERGE:.text=.Amano /SECTION:.Amano,ERW")

#include "denikeri.h"
#include "my_mem.h"
#include <shlobj.h>

EXTC IMAGE_DOS_HEADER __ImageBase;

HRESULT WINAPI MySHGetFolderPath(HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwFlags, LPTSTR pszPath)
{
    if (nFolder != CSIDL_APPDATA)
        return SHGetFolderPath(hwndOwner, nFolder, hToken, dwFlags, pszPath);

    UInt32 i;
    WChar szPath[MAX_PATH];

    i = GetModuleFileNameW((HMODULE)&__ImageBase, szPath, countof(szPath));
    while (szPath[--i] != '\\');
    szPath[i] = 0;
    WideCharToMultiByte(CP_OEMCP, 0, szPath, ++i, pszPath, MAX_PATH, 0, 0);

    return NO_ERROR;
}

Void STDCALL GenerateSavePath(PChar pszSavePath)
{
    UInt32 i;
    WChar szPath[MAX_PATH];
    
    __asm mov pszSavePath, ebx;

    i = GetModuleFileNameW((HMODULE)&__ImageBase, szPath, countof(szPath));
    while (szPath[--i] != '\\');
    ++i;
    *(LPDWORD)(szPath + i + 0) = TAG2('s\x0') | (TAG2('a\x0') << 16);
    *(LPDWORD)(szPath + i + 2) = TAG2('v\x0') | (TAG2('e\x0') << 16);
    *(LPDWORD)(szPath + i + 4) = TAG2('_\x0') | (TAG2('s\x0') << 16);
    *(LPDWORD)(szPath + i + 6) = TAG2('c\x0') | (TAG2('\x00') << 16);

    WideCharToMultiByte(CP_OEMCP, 0, szPath, i + 8, pszSavePath, MAX_PATH, 0, 0);
}

Void GetStartupConfigPath()
{
    PChar pszPath;
    static Char szConfigName[] = "config_sc\\startup_sc.xml";

    __asm mov pszPath, esi;
    memcpy(pszPath, szConfigName, sizeof(szConfigName));
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    static Bool bInit = False;

    if (bInit == False)
    {
        bInit = True;
        
        SPatch p[] =
        {
            // startup crack
            { 0xEB,          1, 0x2F85 }, 
            { 0x00,          1, 0x3133 },   // is cdrom
            { 0xEB,          1, 0x3197 },

            // misc
            { 0xEB,          1, 0x03197 },
            { 0xEB,          1, 0x99910 },   // bound

            // iat hook
            { (DWORD)MySHGetFolderPath, 4, 0x1BA2E8 },
        };

        SFuncPatch f[] = 
        {
            { CALL, 0x1AEE2B, GenerateSavePath,     0 }, 
//            { CALL, 0x1A266B, GetStartupConfigPath, 4 }, 
        };

        PatchMemory(p, countof(p), f, countof(f), GetModuleHandleW(NULL));
    }

    return True;
}
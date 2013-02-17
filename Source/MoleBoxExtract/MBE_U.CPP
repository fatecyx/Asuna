#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "ntdll.lib")
#define UNICODE
#define _UNICODE

#include <Windows.h>
#include <Shlwapi.h>
#include "my_headers.h"

HANDLE hHeap;
DWORD  dwBufferSize, dwStatus;
PBYTE  pbBuffer;
CHAR   QAFOrig[5], QAFMod[5];

enum MBU_Status
{
    EXE_IMPORT_DLL,
    PKG_IMPORT_DLL,
};

#undef  MessageBox
#define MessageBox(a, b, c, d)
#define PathFindFileNameW findnamew
#define PathFindExtensionW findextw

Void WINAPI ExtractU();

DWORD WINAPI GetFileAttributesWOrig(LPCWSTR lpFileName)
{
    DWORD dwAttributes, dwOlgProtect;
    static Bool bProtectChange;

    if (bProtectChange == False)
    {
        bProtectChange = True;
        VirtualProtectEx(NtCurrentProcess(), ZwQueryAttributesFile, sizeof(QAFMod), PAGE_EXECUTE_READWRITE, &dwOlgProtect);
    }

    memcpy(ZwQueryAttributesFile, QAFOrig, sizeof(QAFOrig));
    dwAttributes = GetFileAttributesW(lpFileName);
    memcpy(ZwQueryAttributesFile, QAFMod, sizeof(QAFMod));

    return dwAttributes;
}

HMODULE WINAPI MyLoadLibraryA(LPCSTR lpLibFileName)
{
    if (dwStatus == PKG_IMPORT_DLL)
    {
        ExtractU();
    }

    return LoadLibraryExA(lpLibFileName, NULL, 0);
}

UINT WINAPI MySetErrorMode(UINT uMode)
{
    if (dwStatus == EXE_IMPORT_DLL)
        dwStatus = PKG_IMPORT_DLL;

    return 0;

    return SetErrorMode(uMode);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    static BOOL bInit = False;

    if (bInit == False)
    {
        SFuncPatch f[] =
        {
            { JUMP, (DWORD)SetErrorMode, MySetErrorMode, 0 },
            { JUMP, (DWORD)LoadLibraryA, MyLoadLibraryA, 0 },
        };

        MessageBox(0, 0, 0, 0);
        bInit = True;
        dwStatus = EXE_IMPORT_DLL;
        memcpy(QAFOrig, ZwQueryAttributesFile, sizeof(QAFOrig));
        PatchMemory(0, 0, f, countof(f), 0);
    }

    return True;
}

NoInline Bool IsParentDirectory(PCWChar pszPath)
{
    return !lstrcmpW(pszPath, L".") ||
           !lstrcmpW(pszPath, L"..");
}

Void ProcessFile(PWChar pszInputFileName, PWChar pszRelativePath, PWChar pszOutPath)
{
    HANDLE hFile;
    DWORD  dwSize, dwRead;
    WChar  szOutFile[MAX_PATH];

    if (GetFileAttributesWOrig(pszInputFileName) != -1)
        return;

    hFile = CreateFileW(pszInputFileName,
                GENERIC_READ,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return;

    dwSize = GetFileSize(hFile, NULL);
    if (dwSize > dwBufferSize)
    {
        dwBufferSize = dwSize;
        pbBuffer = (PBYTE)HeapReAlloc(hHeap, 0, pbBuffer, dwBufferSize);
    }

    ReadFile(hFile, pbBuffer, dwSize, &dwRead, NULL);
    CloseHandle(hFile);
    swprintf(szOutFile, L"%s\\%s", pszOutPath, pszRelativePath);

    pszInputFileName = findnamew(szOutFile);
    if (pszInputFileName != szOutFile)
    {
        WChar ch = *pszInputFileName;
        *pszInputFileName = 0;
        MyCreateDirectoryW(szOutFile);
        *pszInputFileName = ch;
    }

    hFile = CreateFileW(szOutFile,
                GENERIC_WRITE,
                FILE_SHARE_WRITE,
                NULL,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return;

    WriteFile(hFile, pbBuffer, dwRead, &dwRead, NULL);
    CloseHandle(hFile);
}

NoInline Void UnpackExe(PWChar lpOutPath)
{
    DWORD   dwLength, dwHeaderSize, dwCurPos;
    HANDLE  hFile;
    WChar   szModuleName[0x1000];
    PIMAGE_DOS_HEADER        pDosHeader;
    PIMAGE_FILE_HEADER       pFileHeader;
    PIMAGE_OPTIONAL_HEADER32 pOptionalHeader;
    PIMAGE_SECTION_HEADER    pSectionHeader;

    pDosHeader = (PIMAGE_DOS_HEADER)GetModuleHandle(0);
    if (VirtualProtectEx((HANDLE)-1, pDosHeader, 0x1000, PAGE_READWRITE, &dwLength) == False)
        return;

    pFileHeader     = (PIMAGE_FILE_HEADER)((PBYTE)pDosHeader + pDosHeader->e_lfanew + 4);
    pOptionalHeader = (PIMAGE_OPTIONAL_HEADER32)((PBYTE)pFileHeader + sizeof(*pFileHeader));
    pSectionHeader  = (PIMAGE_SECTION_HEADER)((PBYTE)pOptionalHeader + pFileHeader->SizeOfOptionalHeader);

    for (int i = pFileHeader->NumberOfSections; i--; )
    {
        if (pSectionHeader[i].SizeOfRawData == 0)
            continue;

        if (VirtualProtectEx((HANDLE)-1,
                        pSectionHeader[i].VirtualAddress + (PBYTE)pDosHeader,
                        pSectionHeader[i].SizeOfRawData, PAGE_READWRITE, &dwLength) == False)
        {
            return;
        }
    }

    GetModuleFileNameW(0, szModuleName, countof(szModuleName));
    dwLength = lstrlenW(lpOutPath);
    *(LPDWORD)&lpOutPath[dwLength] = '\\';
    lstrcpyW(&lpOutPath[dwLength + 1], PathFindFileNameW(szModuleName));

    hFile = CreateFileW(lpOutPath,
                    GENERIC_READ|GENERIC_WRITE,
                    FILE_SHARE_READ|FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    *(LPDWORD)&lpOutPath[dwLength] = 0;
    if (hFile == INVALID_HANDLE_VALUE)
        return;

    dwLength = (PBYTE)&pSectionHeader[pFileHeader->NumberOfSections] - (PBYTE)pDosHeader;

    memset(szModuleName, 0, sizeof(szModuleName));
    WriteFile(hFile, pDosHeader, dwLength, &dwHeaderSize, NULL);
    if (dwLength = dwHeaderSize % pOptionalHeader->FileAlignment)
    {
        dwLength = pOptionalHeader->FileAlignment - dwLength;
        WriteFile(hFile, szModuleName, dwLength, &dwLength, NULL);
        dwHeaderSize += dwLength;
    }

    pFileHeader->Characteristics = IMAGE_FILE_32BIT_MACHINE|IMAGE_FILE_EXECUTABLE_IMAGE|IMAGE_FILE_RELOCS_STRIPPED;
    pOptionalHeader->MajorLinkerVersion = _MSC_VER / 100 - 6;
    pOptionalHeader->MinorLinkerVersion = 0;
    pOptionalHeader->SizeOfCode = 0;
    pOptionalHeader->AddressOfEntryPoint = 0;
    pOptionalHeader->CheckSum = 0;
    pOptionalHeader->SizeOfImage = pOptionalHeader->SizeOfHeaders;
    dwCurPos = dwHeaderSize;
    for (int i = 0; i != pFileHeader->NumberOfSections; ++i)
    {
        DWORD Size;

        Size = pSectionHeader[i].Misc.VirtualSize;
        Size += pOptionalHeader->SectionAlignment - Size % pOptionalHeader->SectionAlignment;
        pOptionalHeader->SizeOfImage += Size;
        pSectionHeader[i].PointerToRawData = dwCurPos;
        if (pSectionHeader[i].SizeOfRawData == 0)
            continue;

        WriteFile(hFile,
            pSectionHeader[i].VirtualAddress + (PBYTE)pDosHeader,
            pSectionHeader[i].SizeOfRawData,
            &dwLength,
            NULL);

        dwCurPos += dwLength;
        if (dwLength %= pOptionalHeader->FileAlignment)
        {
            dwLength = pOptionalHeader->FileAlignment - dwLength;
            WriteFile(hFile, szModuleName, dwLength, &dwLength, NULL);
            dwCurPos += dwLength;
        }
    }

    SetFilePointer(hFile, 0, 0, FILE_BEGIN);
    WriteFile(hFile, pDosHeader, dwHeaderSize, &dwLength, NULL);
    CloseHandle(hFile);
}

Int32 STDCALL GetDirectoryFilesCallBack(LPVoid lpBuffer, LPWIN32_FIND_DATAW pFindData, LPVoid lpParam)
{
    lstrcpyW((PWChar)lpBuffer, pFindData->cFileName);
    return 1;
}

Void EU()
{
    WChar  szOutPath[MAX_PATH], szFilter[MAX_PATH];
    PWChar lpFileName;

    MessageBox(0, 0, 0, 0);

    GetModuleFileNameW(NULL, szOutPath, sizeof(szOutPath));

    lpFileName = findnamew(szOutPath);
    *(lpFileName - 1) = 0;
    lstrcpyW(szFilter, szOutPath);
    lstrcatW(szFilter, L"\\*.*");

    UInt32 RelativePathPos;
    WChar (*szPath)[MAX_PATH];
    Large_Integer FileCount;

    if (!EnumDirectoryFiles(
            (LPVoid *)&szPath,
            L"*.*",
            sizeof(*szPath),
            szOutPath,
            &FileCount,
            GetDirectoryFilesCallBack,
            0,
            ENUM_DIRECTORY_FILES_FLAG_ENUMSUBDIR))
    {
        return;
    }

    hHeap = GetProcessHeap();
    dwBufferSize = 0x2000;
    pbBuffer = (PByte)HeapAlloc(hHeap, 0, dwBufferSize);

    *(lpFileName - 1) = '\\';
    RelativePathPos = lpFileName - szOutPath;
    lstrcpyW(findextw(szOutPath), L"_Files");
    CreateDirectoryW(szOutPath, NULL);
    
    UnpackExe(szOutPath);
    for (UInt32 i = 0; i != FileCount.LowPart; ++i)
    {
        ProcessFile(szPath[i], szPath[i] + RelativePathPos, szOutPath);
    }

    EnumDirectoryFilesFree(szPath);
    HeapFree(hHeap, 0, pbBuffer);
}

Void WINAPI ExtractU()
{
    if (QAFOrig[0])
    {
        memcpy(QAFMod, ZwQueryAttributesFile, sizeof(QAFMod));
        EU();
    }
    ExitProcess(0);
}
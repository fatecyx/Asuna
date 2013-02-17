#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
//#pragma comment(linker,"/MERGE:.data=.Kanade")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "ntdll.lib")

#include "MoleBoxExtract.h"
#include <Shlwapi.h>
#include "my_crt.h"
#include "my_api.h"
#include "my_mem.h"

BOOL  bGetFileTime = False;
DWORD dwPackageCount = 0, dwMaxPackage;
TMoleBoxFile **pMoleBoxFile = NULL;

DWORD dwOrigSection = 0;
PIMAGE_SECTION_HEADER gpSectionHeader;
DWORD dwImageSections = 0;
TSection ImageSections[0x100];

enum MB_Status
{
    INIT,
    UNPACKING_EXE,
    UNPACKED_EXE,
    HOOKED_MSVCRT_IAT,
    UNPACKING,
};

MB_Status Status;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    static BOOL bInit = False;

    if (ul_reason_for_call != DLL_PROCESS_ATTACH || bInit == True)
        return True;

    INT32                    EP;
    PIMAGE_DOS_HEADER        pDosHeader;
    PIMAGE_FILE_HEADER       pFileHeader;
    PIMAGE_OPTIONAL_HEADER32 pOptionalHeader;
    PIMAGE_SECTION_HEADER    pSectionHeader;

    pDosHeader = (PIMAGE_DOS_HEADER)GetModuleHandle(0);
    if (VirtualProtectEx((HANDLE)-1, pDosHeader, 0x1000, PAGE_READWRITE, (LPDWORD)&EP) == False)
        return True;

    pFileHeader     = (PIMAGE_FILE_HEADER)((PBYTE)pDosHeader + pDosHeader->e_lfanew + 4);
    pOptionalHeader = (PIMAGE_OPTIONAL_HEADER32)((PBYTE)pFileHeader + sizeof(*pFileHeader));
    pSectionHeader  = (PIMAGE_SECTION_HEADER)((PBYTE)pOptionalHeader + pFileHeader->SizeOfOptionalHeader);

    for (EP = 0; EP != pFileHeader->NumberOfSections; ++EP)
    {
        ImageSections[EP].dwAddressStart = pSectionHeader[EP].VirtualAddress + (DWORD)pDosHeader;
        ImageSections[EP].dwAddressEnd = ImageSections[EP].dwAddressStart + pSectionHeader[EP].Misc.VirtualSize;
    }

    dwImageSections = EP;

    SFuncPatch f[] =
    {
        { JUMP, (UInt32)VirtualAlloc,     MyVirtualAlloc  ,   0 },
        { JUMP, (UInt32)VirtualFree,      MyVirtualFree   ,   0 },
        { JUMP, (UInt32)VirtualProtect,   MyVirtualProtect,   0 },
//        { JUMP, (DWORD)LoadLibraryExA,   (DWORD)MyLoadLibraryExA,   0 },
        { JUMP, (UInt32)GetFileTime,      MyGetFileTime,      0 },
        { JUMP, (UInt32)CharUpperBuffA,   MyCharUpperBuffA,   0 },
        { JUMP, (UInt32)GetProcAddress,   MyGetProcAddress,   0 },
        { JUMP, (UInt32)GetModuleHandleA, MyGetModuleHandleA, 0 },
//        { JUMP, (DWORD)GetFullPathNameA, (DWORD)MyGetFullPathNameA, 0 },
    };

    PatchMemory(0, 0, f, countof(f), 0);
    Status = INIT;
    dwMaxPackage = 10;

    EP = (INT32)pDosHeader + pOptionalHeader->AddressOfEntryPoint;
    if (*(PBYTE)EP == 0xE8)
    {
        EP += *(PINT32)((PBYTE)(EP + 1)) + 5;
        if (*(PBYTE)EP++ == 0x60)     // pushad
        {
            gpSectionHeader = (PIMAGE_SECTION_HEADER)(EP + 6 - 0x3FA - 1);
            EP += *(PINT32)((PBYTE)(EP + 1)) + 5;
            EP += *(PINT32)((PBYTE)(EP + 1)) + 5;
            while (*(PINT32)EP != 0xE8D0FF58)
            {
                ++EP;
            }
            ++EP;
            *(PBYTE)EP = JUMP;
            *(PINT32)(EP + 1) = (DWORD)MyEntryPoint - (EP + 5);
        }
    }

    pMoleBoxFile = (TMoleBoxFile **)HeapAlloc(Nt_GetProcessHeap(),
                        HEAP_ZERO_MEMORY, dwMaxPackage * sizeof(*pMoleBoxFile));

    return True;
}

int STDCALL GetReturnAddress(LPVOID i)
{
    return *((int *)i - 1);
}

Bool IsCallerMainModule(LPVOID lpAddress)
{
    DWORD dwAddress = GetReturnAddress(lpAddress);
    for (DWORD i = 0; i != dwImageSections; ++i)
    {
        if (dwAddress >= ImageSections[i].dwAddressStart && dwAddress < ImageSections[i].dwAddressEnd)
            return True;
    }
    return False;
}

HMODULE WINAPI MyLoadLibraryExA(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
    HMODULE  hModule;
    ANSI_STRING ansiDll;
    UNICODE_STRING ustrDll;

    RtlInitAnsiString(&ansiDll, lpLibFileName);
    RtlAnsiStringToUnicodeString(&ustrDll, &ansiDll, True);
    hModule = LoadLibraryExW(ustrDll.Buffer, NULL, 0);
    RtlFreeUnicodeString(&ustrDll);

    return hModule;
}

HRESULT WINAPI MyGetFileTime(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)
{
    if (IsCallerMainModule(&hFile) && bGetFileTime == False)
    {
        bGetFileTime = True;
    }

    if (((DWORD)hFile & 0x10000003) == 3)
    {
        SetLastError(0xC0000008);
        return S_FALSE;
    }

    NTSTATUS NtStatus;
    IO_STATUS_BLOCK IoStatusBlock;
    FILE_BASIC_INFORMATION FileBasicInfo;

    NtStatus = ZwQueryInformationFile(hFile, &IoStatusBlock, &FileBasicInfo, sizeof(FileBasicInfo), FileBasicInformation);
    if (!NT_SUCCESS(NtStatus))
    {
        SetLastError(NtStatus);
        return S_FALSE;
    }

    if (lpCreationTime)
    {
        *(PLARGE_INTEGER)lpCreationTime = FileBasicInfo.ChangeTime;
    }
    if (lpLastAccessTime)
    {
        *(PLARGE_INTEGER)lpLastAccessTime = FileBasicInfo.LastAccessTime;
    }
    if (lpLastWriteTime)
    {
        *(PLARGE_INTEGER)lpLastWriteTime = FileBasicInfo.LastWriteTime;
    }

    return S_OK;
}

DWORD WINAPI MyGetFullPathNameA(IN LPSTR lpFileName, IN DWORD nBufferLength, OUT LPTSTR lpBuffer, OUT LPSTR* lpFilePart)
{
    WCHAR szFileName[MAX_PATH], szFullName[MAX_PATH];
    ANSI_STRING aString;
    UNICODE_STRING uString;
    static Bool bFirst;

    if (!bFirst)
    {
        bFirst = True;
        MessageBoxA(0, 0, 0, 0);
    }
    RtlInitAnsiString(&aString, lpFileName);
    uString.Buffer = szFileName;
    uString.Length = 0;
    uString.MaximumLength = countof(szFileName);
    RtlAnsiStringToUnicodeString(&uString, &aString, False);
    memset(lpBuffer, 0, nBufferLength);
    nBufferLength = GetFullPathNameW(szFileName, countof(szFullName), szFullName, (LPWSTR *)lpFilePart);
    if (lpFilePart)
    {
        *lpFilePart =  *lpFilePart ? lpBuffer + (*lpFilePart - (LPSTR)szFullName) / 2 : lpBuffer;
    }
    aString.Buffer = (LPSTR)szFileName;
    aString.MaximumLength = sizeof(szFileName);
    RtlInitUnicodeString(&uString, szFullName);
    RtlUnicodeStringToAnsiString(&aString, &uString, False);
    memcpy(lpBuffer, szFileName, nBufferLength);
    if (lpFilePart && Status == UNPACKING)
    {
        lpFileName = *lpFilePart;
        memmove(lpFileName + 2, lpFileName, nBufferLength - (lpFileName - lpBuffer));
        *(LPWORD)lpFileName = '\\/';
        nBufferLength += 2;
    }

    return nBufferLength;
}

DWORD WINAPI MyCharUpperBuffA(LPSTR lpsz, DWORD cchLength)
{
    if (IsCallerMainModule(&lpsz) && bGetFileTime == True && lpsz[1] != ':')
    {
        LPSTR lpFileName;
        DWORD dwCount = dwPackageCount++;

        bGetFileTime = False;
        lpFileName = lpsz;
        while ((LPSTR)*(LPDWORD)lpFileName != lpsz)
        {
            lpFileName += lstrlenA(lpFileName) + 1;
        }
        if (dwCount >= dwMaxPackage)
        {
            dwMaxPackage += dwMaxPackage >> 1;
            pMoleBoxFile = (TMoleBoxFile **)HeapReAlloc(Nt_GetProcessHeap(),
                HEAP_ZERO_MEMORY, pMoleBoxFile, dwMaxPackage * sizeof(*pMoleBoxFile));
        }
        pMoleBoxFile[dwCount] = (TMoleBoxFile *)(lpFileName);
    }
/*
    ANSI_STRING aString;
    UNICODE_STRING uString;

    RtlInitAnsiString(&aString, lpsz);
    RtlAnsiStringToUnicodeString(&uString, &aString, True);
    CharUpperBuffW(uString.Buffer, cchLength);
    RtlUnicodeStringToAnsiString(&aString, &uString, True);
    RtlFreeUnicodeString(&uString);
    memset(lpsz, 0, cchLength);
    memcpy(lpsz, aString.Buffer, min(cchLength, aString.Length));
    RtlFreeAnsiString(&aString);
*/
    strupr(lpsz);
    return cchLength;
}

LPVOID WINAPI MyVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
    LPVOID lpBaseAddress = VirtualAllocEx((HANDLE)-1, lpAddress, dwSize, flAllocationType, flProtect);

    if (lpBaseAddress && IsCallerMainModule(&lpAddress))
    {
        DWORD i = dwImageSections++;
        ImageSections[i].dwAddressStart = (DWORD)lpBaseAddress;
        ImageSections[i].dwAddressEnd   = (DWORD)lpBaseAddress + dwSize;
    }

    return lpBaseAddress;
}

BOOL WINAPI MyVirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType)
{
    if (IsCallerMainModule(&lpAddress))
    {
        DWORD i, j;

        j = dwImageSections;
        for (i = 0; i != j; ++i)
        {
            if (ImageSections[i].dwAddressStart == (DWORD)lpAddress)
                break;
        }
        if (i != j)
        {
            --dwImageSections;
            memmove(&ImageSections[i], &ImageSections[i + 1], sizeof(*ImageSections) * (j - i));
        }
    }

    return VirtualFreeEx((HANDLE)-1, lpAddress, dwSize, dwFreeType);
}

BOOL WINAPI MyVirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
{
    if (IsCallerMainModule(&lpAddress) && lpAddress == GetModuleHandleW(0))
    {
        switch (Status)
        {
            case INIT:
                if (flNewProtect == PAGE_READWRITE)
                {
                    Status = UNPACKING_EXE;
                    MessageBoxA(0, "正在解压主程序，可附加", 0, 64);
                }
                break;

            case UNPACKING_EXE:
                Status = UNPACKED_EXE;
                break;
        }
    }

    return VirtualProtectEx((HANDLE)-1, lpAddress, dwSize, flNewProtect, lpflOldProtect);
}

HMODULE WINAPI MyGetModuleHandleA(LPCSTR lpModuleName)
{
    HMODULE hModule;

    if (lpModuleName)
    {
        ANSI_STRING ansiDll;
        UNICODE_STRING ustrDll;

        if (Status == UNPACKING && !lstrcmpiA(lpModuleName, "oleoaut32.dll"))
        {
            MyEntryPoint();
        }

        RtlInitAnsiString(&ansiDll, lpModuleName);
        RtlAnsiStringToUnicodeString(&ustrDll, &ansiDll, True);
        hModule = GetModuleHandleW(ustrDll.Buffer);
        RtlFreeUnicodeString(&ustrDll);
    }
    else
    {
        if (Status == UNPACKED_EXE)
            Status = HOOKED_MSVCRT_IAT;

        hModule = GetModuleHandleW(0);
    }

    return hModule;
}

HMODULE WINAPI BasepMapModuleHandle(HMODULE hModule, int Value)
{
    if (hModule == NULL)
    {
        hModule = GetModuleHandleW(0);
    }
    else if ((DWORD)hModule & 3)
    {
        hModule = (HMODULE)(-Value & (DWORD)hModule);
    }

    return hModule;
}

FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    DWORD Oridinal;
    NTSTATUS NtStatus;
    ANSI_STRING ansiProcName, *pName;

    if (Status == HOOKED_MSVCRT_IAT)
    {
        Status = UNPACKING;
//        MyEntryPoint();
        Extract2(0);
    }

    if ((DWORD)lpProcName < 0x10000)
    {
        pName = NULL;
        Oridinal = (DWORD)lpProcName;
    }
    else
    {
        RtlInitAnsiString(&ansiProcName, lpProcName);
        pName = &ansiProcName;
        Oridinal = 0;
    }

    NtStatus = LdrGetProcedureAddress(hModule, pName, (WORD)Oridinal, (LPVOID *)&lpProcName);
    if (!NT_SUCCESS(NtStatus))
    {
        SetLastError(NtStatus);
        return NULL;
    }

    return (FARPROC)lpProcName;
}

int WINAPI MyEntryPoint()
{
    HANDLE hHeap;

    if (pMoleBoxFile == NULL)
    {
        CHAR szModule[MAX_PATH];
        GetModuleFileNameA(NULL, szModule, sizeof(szModule));
        if (MessageBoxA(NULL, "没有文件被打包，脱主程序？", szModule, MB_OKCANCEL|MB_ICONASTERISK) == IDOK)
            Extract2(0);
    }
    else
    {
        for (DWORD i = 0; i != dwPackageCount; ++i)
            Extract2(pMoleBoxFile[i]);
    }

    hHeap = GetProcessHeap();
    HeapFree(hHeap, 0, pMoleBoxFile);

    ExitProcess(0);
}

DWORD WINAPI uncompress(BYTE *dest, ULONG *destLen, const BYTE *source, ULONG sourceLen, LONG)
{
    DWORD status, NumberOfSections;

    __asm mov status, eax;

    if (gpSectionHeader)
    {
        NumberOfSections = *(int *)((PBYTE)gpSectionHeader - 4) - 3;
        if (dwOrigSection < NumberOfSections)
        {
            gpSectionHeader[dwOrigSection++].SizeOfRawData = *destLen;
            while (dwOrigSection < NumberOfSections && gpSectionHeader[dwOrigSection].VirtualAddress == 0)
            {
                ++dwOrigSection;
            }
        }
    }

    return status != 0;
}

NoInline Void UnpackExe(LPSTR lpOutPath)
{
    DWORD   dwLength, dwHeaderSize, dwCurPos;
    HANDLE  hFile;
    CHAR   szModuleName[0x1000];
    PIMAGE_DOS_HEADER        pDosHeader;
    PIMAGE_FILE_HEADER       pFileHeader;
    PIMAGE_OPTIONAL_HEADER32 pOptionalHeader;
    PIMAGE_SECTION_HEADER    pSectionHeader;
    static Bool bUnpacked = False;

    if (bUnpacked == True || dwOrigSection == 0 || gpSectionHeader == 0)
        return;

    bUnpacked = True;
    pDosHeader = (PIMAGE_DOS_HEADER)GetModuleHandle(0);
    if (VirtualProtectEx((HANDLE)-1, pDosHeader, 0x1000, PAGE_READWRITE, &dwLength) == False)
        return;

    pFileHeader     = (PIMAGE_FILE_HEADER)((PBYTE)pDosHeader + pDosHeader->e_lfanew + 4);
    pOptionalHeader = (PIMAGE_OPTIONAL_HEADER32)((PBYTE)pFileHeader + sizeof(*pFileHeader));
    pSectionHeader  = (PIMAGE_SECTION_HEADER)((PBYTE)pOptionalHeader + pFileHeader->SizeOfOptionalHeader);

    pFileHeader->NumberOfSections = *(LPWORD)((PBYTE)gpSectionHeader - 4) - 3;
    memcpy(pSectionHeader, gpSectionHeader, pFileHeader->NumberOfSections * sizeof(*pSectionHeader));

    for (int i = pFileHeader->NumberOfSections; i--; )
    {
        if (pSectionHeader[i].SizeOfRawData == 0 || pSectionHeader[i].VirtualAddress == 0)
            continue;

        DWORD dwSize;

        dwSize = pSectionHeader[i].SizeOfRawData;
        dwSize += pOptionalHeader->SectionAlignment - dwSize % pOptionalHeader->SectionAlignment;
        if (VirtualProtectEx((HANDLE)-1,
            pSectionHeader[i].VirtualAddress + (PBYTE)pDosHeader,
            dwSize, PAGE_READWRITE, &dwLength) == False)
        {
            return;
        }
    }

    GetModuleFileNameA(0, szModuleName, countof(szModuleName));
    dwLength = lstrlenA(lpOutPath);
    *(LPDWORD)&lpOutPath[dwLength] = '\\';
    lstrcpyA(&lpOutPath[dwLength + 1], PathFindFileNameA(szModuleName));

    hFile = CreateFileA(lpOutPath,
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
    }

    pFileHeader->Characteristics = IMAGE_FILE_32BIT_MACHINE|IMAGE_FILE_EXECUTABLE_IMAGE|IMAGE_FILE_RELOCS_STRIPPED;
    pOptionalHeader->MajorLinkerVersion = _MSC_VER / 100 - 6;
    pOptionalHeader->MinorLinkerVersion = 0;
    pOptionalHeader->SizeOfCode = 0;
    pOptionalHeader->AddressOfEntryPoint = 0;
    pOptionalHeader->CheckSum = 0;
    pOptionalHeader->SizeOfImage = pOptionalHeader->SizeOfHeaders;
    pOptionalHeader->DataDirectory[12].VirtualAddress = 0;
    pOptionalHeader->DataDirectory[12].Size = 0;

    dwCurPos = dwHeaderSize + dwLength;
    for (int i = 0; i != pFileHeader->NumberOfSections; ++i)
    {
        DWORD dwSize;

        if (pSectionHeader[i].VirtualAddress == 0)
        {
            pSectionHeader[i].VirtualAddress = pOptionalHeader->DataDirectory[2].VirtualAddress;
        }

        if (pSectionHeader[i].VirtualAddress == 0)
            continue;

        dwSize = pSectionHeader[i].Misc.VirtualSize;
        dwSize += pOptionalHeader->SectionAlignment - dwSize % pOptionalHeader->SectionAlignment;
        pOptionalHeader->SizeOfImage += dwSize;
        pSectionHeader[i].PointerToRawData = dwCurPos;
        if (pSectionHeader[i].SizeOfRawData == 0)
            continue;

        dwSize = pSectionHeader[i].SizeOfRawData;
        if (dwSize % pOptionalHeader->FileAlignment)
            dwSize += pOptionalHeader->FileAlignment - dwSize % pOptionalHeader->FileAlignment;
        WriteFile(hFile,
            pSectionHeader[i].VirtualAddress + (PBYTE)pDosHeader,
            dwSize,
            &dwLength,
            NULL);

        dwCurPos += dwLength;
    }

    SetFilePointer(hFile, 0, 0, FILE_BEGIN);
    WriteFile(hFile, pDosHeader, dwHeaderSize, &dwLength, NULL);
    CloseHandle(hFile);
}

Void WINAPI Extract2(TMoleBoxFile  *pMoleBoxFile)
{
    FILE *fp;
    intptr_t hFind;
    __finddata64_t wfd;

    HANDLE hFile, hHeap;
    CHAR  c, c1, szFileName[_MAX_FNAME], szPath[_MAX_FNAME];
    LPSTR lpName, lpFileName, lpExtension;
    PBYTE pbFile;
	DWORD dwRead, dwLength, dwSize, dwMaxSize = 0;

    GetModuleFileNameA(NULL, szFileName, sizeof(szFileName));
    lpFileName = PathFindFileNameA(szFileName);
    *(lpFileName - 1) = 0;
    SetCurrentDirectoryA(szFileName);
    lpExtension = PathFindExtensionA(lpFileName);
    if (lpExtension)
    {
        *lpExtension = 0;
    }
    wsprintf(szPath, "%s_Files\\", lpFileName);
	if (CreateDirectory(szPath, NULL) == False && GetFileAttributesA(szPath) == -1)
    {
        MessageBoxA(NULL, "CreateDirectoryA() failed", NULL, 64);
        return;
    }

    UnpackExe(szPath);
    if (pMoleBoxFile == NULL)
        return;

    hHeap  = GetProcessHeap();
	pbFile = (PBYTE)HeapAlloc(hHeap, 0, 0);

//    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), szPath, lstrlenA(szPath), &dwLength, NULL);
    dwLength = lstrlenA(szPath);
    while (lpFileName = pMoleBoxFile->lpFileName)
    {
        lpName = PathFindFileNameA(lpFileName);
        if (lpName != lpFileName)
        {
            DWORD dwAttributes;

            lstrcpyA(szFileName, szPath);
            c1 = *lpName;
            *lpName = 0;

            lstrcpyA(&szFileName[dwLength], lpFileName);
            dwAttributes = GetFileAttributesA(szFileName);
            szFileName[dwLength] = 0;

            if (dwAttributes == -1) do
            {
                if (*lpFileName == '\\' || *lpFileName == '/')
                {
                    c = *lpFileName;
                    *lpFileName = 0;
                    hFind = _findfirst64(pMoleBoxFile->lpFileName, &wfd);
                    if (hFind != -1)
                    {
                        lstrcatA(szFileName, wfd.name);
                        lstrcatA(szFileName, "\\");
                        CreateDirectoryA(szFileName, NULL);
                        _findclose(hFind);
                    }
                    *lpFileName = c;
                }
                ++lpFileName;
            } while (*lpFileName);
            else
            {
                lstrcatA(szFileName, lpFileName);
            }

            *lpName = c1;
        }
        else
        {
            szFileName[0] = 0;
        }

        hFind = _findfirst64(pMoleBoxFile->lpFileName, &wfd);
        if (hFind != -1)
        {
            _findclose(hFind);
        }

        fp = fopen(pMoleBoxFile->lpFileName, "rb");
        if (fp)
        {
            dwSize = fsize(fp);
            if (dwSize > dwMaxSize)
            {
                pbFile = (PBYTE)HeapReAlloc(hHeap, 0, pbFile, dwSize);
                dwMaxSize = dwSize;
            }
            if (fread(pbFile, dwSize, 1, fp))
            {
                if (hFind != -1)
                {
                    if (szFileName[0])
                        lstrcatA(szFileName, wfd.name);
                    else
                        wsprintfA(szFileName, "%s%s", szPath, wfd.name);
                }
                else
                {
                    lstrcpyA(szFileName, szPath);
                    lstrcat(szFileName, pMoleBoxFile->lpFileName);
                    strlwr(szFileName);
                }

                printf("Extracting \"%s\" ... ", szFileName);
                hFile = CreateFileA(szFileName,
                    GENERIC_WRITE,
                    FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
                if (hFile != INVALID_HANDLE_VALUE)
                {
                    WriteFile(hFile, pbFile, dwSize, &dwRead, NULL);
                    CloseHandle(hFile);
                }
            }
            else
            {
//                wsprintfA(szFileName, "读取\"%s\"失败.", lpFileName);
//                MessageBoxA(NULL, szFileName, NULL, 64);
            }
            fclose(fp);
        }

        ++pMoleBoxFile;
    }

    HeapFree(hHeap, 0, pbFile);
}

Void WINAPI Extract(READFILE      lpfnReadFile,
                    GETFILESIZE   lpfnGetFileSize,
                    CREATEFILEA   lpfnCreateFileA,
                    TMoleBoxFile *lpNames,
                    DWORD         dwFileNum)
{
	CHAR	szFileName[_MAX_FNAME], szPath[_MAX_FNAME];
	PBYTE	pbFile;
	DWORD	dwRead, dwSize, dwMaxSize = 0;
	HANDLE	hFile, hHeap;
	LPSTR	lpTemp, lpExtension, lpFileName;

    GetModuleFileNameA(NULL, szFileName, sizeof(szFileName));
    lpFileName = PathFindFileNameA(szFileName);
    *(lpFileName - 1) = 0;
    SetCurrentDirectoryA(szFileName);
    lpExtension = PathFindExtensionA(lpFileName);
    if (lpExtension)
    {
        *lpExtension = 0;
    }
    wsprintf(szPath, "%s_Files", lpFileName);

	hHeap = GetProcessHeap();
	pbFile = (PBYTE)HeapAlloc(hHeap, 0, 0);
	CreateDirectory(szPath, NULL);

	while (dwFileNum--)
    {
        lpFileName = lpNames[dwFileNum].lpFileName;
		hFile = lpfnCreateFileA(lpFileName,
							GENERIC_READ,
							FILE_SHARE_READ,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL);

		if (hFile != INVALID_HANDLE_VALUE)
		{
			dwSize = lpfnGetFileSize(hFile, NULL);
			if (dwSize > dwMaxSize)
			{
				pbFile = (PBYTE)HeapReAlloc(hHeap, 0, pbFile, dwSize);
				dwMaxSize = dwSize;
			}

			lpfnReadFile(hFile, pbFile, dwSize, &dwRead, NULL);
			CloseHandle(hFile);

			lpTemp = PathFindFileNameA(lpFileName);
			if (lpTemp != lpFileName)
			{
				BYTE byTemp = *lpTemp;
				*lpTemp = 0;
				wsprintf(szFileName, "%s\\%s", szPath, lpFileName);
				MyCreateDirectoryA(szFileName);
				*lpTemp = byTemp;
			}
			wsprintf(szFileName, "%s\\%s", szPath, lpFileName);

			hFile = CreateFileA(szFileName,
				GENERIC_WRITE,
				FILE_SHARE_WRITE,
				NULL,
                CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				WriteFile(hFile, pbFile, dwSize, &dwRead, NULL);
				CloseHandle(hFile);
			}
		}
	}

	HeapFree(hHeap, 0, pbFile);
}

#pragma comment(linker, "/ENTRY:main2")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "my_commsrc.h"

DECL_ALIGN(1) struct FILE_NAME_ENTRY
{
    ULONG Index;
    ULONG Length;
    CHAR  FileName[MAX_PATH];
};

ForceInline Void main2(Int, WChar**)
{
    CNtFileDisk      file;
    PVOID            Buffer;
    HMODULE          GameDllModule;
    ULONG            FileCount, BufferSize, FileSize, Length;
    LDR_MODULE      *LdrModule;
    FILE_NAME_ENTRY *FileNameBuffer, *Entry;
    UNICODE_STRING   GameDllPath;
    CHAR             FullPath[MAX_NTPATH], *pFullPathName;

    Nt_SetExecuteDirectoryAsCurrent();
    if (!NT_SUCCESS(file.Open(L"index.bin")))
        return;

    FileCount = file.GetSize32();
    FileNameBuffer = (FILE_NAME_ENTRY *)AllocateMemory(FileCount);
    if (FileNameBuffer == NULL)
        return;

    file.Read(FileNameBuffer, FileCount);
    FileCount /= sizeof(*Entry);
    Entry = FileNameBuffer;

    LdrModule = FIELD_BASE(Nt_CurrentPeb()->Ldr->InLoadOrderModuleList.Flink, LDR_MODULE, InLoadOrderModuleList);
    StrCopyW(LdrModule->BaseDllName.Buffer, L"BGI_CHS.exe");

    Nt_UnicodeToAnsi(
        FullPath,
        countof(FullPath),
        LdrModule->FullDllName.Buffer,
        LdrModule->BaseDllName.Buffer - LdrModule->FullDllName.Buffer,
        &Length
    );

    pFullPathName = FullPath + Length - 1;

    RTL_CONST_STRING(GameDllPath, L"Game.dll");
    LdrLoadDll(NULL, 0, &GameDllPath, &GameDllModule);

    BufferSize  = 0;
    Buffer      = NULL;
    for (ULONG Count = FileCount; Count; ++Entry, --Count)
    {
        HANDLE hFile;
        WCHAR  ch, FileName[MAX_NTPATH], *pFileName;

        StrCopyA(pFullPathName, Entry->FileName);
        hFile = CreateFileA(
                    FullPath,
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL
                 );

        if (hFile == INVALID_HANDLE_VALUE)
            continue;

        if (GetFileType(hFile) != FILE_TYPE_DISK)
        {
            CloseHandle(hFile);
            continue;
        }

        FileSize = GetFileSize(hFile, NULL);
        if (FileSize > BufferSize)
        {
            BufferSize = FileSize;
            Buffer = ReAllocateMemory(Buffer, BufferSize);
        }

        ReadFile(hFile, Buffer, FileSize, &FileSize, NULL);
        CloseHandle(hFile);

        Nt_AnsiToUnicode(FileName, countof(FileName), FullPath);
        pFileName = findnamew(FileName);
        ch = *pFileName;
        *pFileName = 0;
        MyCreateDirectoryW(FileName);
        *pFileName = ch;
        if (NT_SUCCESS(file.Create(FileName)))
            file.Write(Buffer, FileSize);
    }

    FreeMemory(FileNameBuffer);
    FreeMemory(Buffer);
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
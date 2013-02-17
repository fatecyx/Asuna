#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"

ForceInline Void main2(Int argc, WChar **argv)
{
    while (--argc)
    {
        WCHAR  szDllPath[MAX_PATH];
        DWORD  dwWritten, dwLength;
        LPVOID lpBuf;
        HANDLE hThread;
        STARTUPINFOW si;
        PROCESS_INFORMATION pi;

        si.cb = sizeof(si);
        GetStartupInfoW(&si);
        si.dwFlags |= STARTF_USESTDHANDLES;
        si.hStdInput  = GetStdHandle(STD_INPUT_HANDLE);
        si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        si.hStdError  = GetStdHandle(STD_ERROR_HANDLE);
        SetHandleInformation(si.hStdInput,  HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
        SetHandleInformation(si.hStdOutput, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
        SetHandleInformation(si.hStdError,  HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

        if (!CreateProcessW(argv[argc], NULL, NULL, NULL, True, CREATE_SUSPENDED, NULL, NULL, &si, &pi))
        {
            printf("CreateProcess() failed.\n");
            continue;
        }

        do
        {
            GetExecuteDirectoryW(szDllPath, countof(szDllPath));
            lstrcatW(szDllPath, L"mb.dll");
            dwLength = (lstrlenW(szDllPath) + 1) * sizeof(*szDllPath);

            lpBuf = VirtualAllocEx(pi.hProcess, NULL, dwLength, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
            if (lpBuf == NULL)
            {
                printf("VirtualAllocEx() failed\n.");
                TerminateProcess(pi.hProcess, 0);
                break;
            }

            if (WriteProcessMemory(pi.hProcess, lpBuf, szDllPath, dwLength, &dwWritten) == False ||
                dwLength != dwWritten)
            {
                printf("WriteProcessMemory failed.\n");
                VirtualFreeEx(pi.hProcess, lpBuf, dwLength, MEM_DECOMMIT);
                TerminateProcess(pi.hProcess, 0);
                break;
            }

            hThread = CreateRemoteThread(pi.hProcess, NULL, 0,
                (LPTHREAD_START_ROUTINE)LoadLibraryW, lpBuf, 0, NULL);
            if (hThread == NULL)
            {
                printf("CreateRemoteThread() failed.\n");
                VirtualFreeEx(pi.hProcess, lpBuf, dwLength, MEM_DECOMMIT);
                TerminateProcess(pi.hProcess, 0);
                break;
            }

            WaitForSingleObject(hThread, INFINITE);
            CloseHandle(hThread);
            VirtualFreeEx(pi.hProcess, lpBuf, 0, MEM_RELEASE);
            ResumeThread(pi.hThread);
            WaitForSingleObject(pi.hProcess, INFINITE);
        } while (0);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}

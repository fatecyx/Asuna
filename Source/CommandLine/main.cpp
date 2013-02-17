#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Hiromi /SECTION:.Hiromi,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Hiromi")
#pragma comment(linker,"/MERGE:.data=.Hiromi")
#pragma comment(lib, "ntdll.lib")

#include "my_headers.h"
#include <tlhelp32.h>
#include <stdio.h>
#include <conio.h>

EXTC char *_acmdln;

void __cdecl main(int argc, char **argv)
{
    CHAR                       *szCmdLine;
    DWORD                       dwRead, dwMaxBuffer;
    HANDLE                      hSnapshot, hHeap, hProcess;
    BOOL                        Old;
    ANSI_STRING                *lpCmdLine, ansiCmdLine;
    PROCESSENTRY32	            pe;
    PROCESS_BASIC_INFORMATION   ProcessInformation;
    PEB_BASE                   *Peb;
    PWSTR                       

    RtlAdjustPrivilege(SE_DEBUG_PRIVILEGE, TRUE, FALSE, &Old);
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    pe.dwSize = sizeof(pe);
    if (Process32First(hSnapshot, &pe) == FALSE)
        return;

    szCmdLine = (CHAR *)GetCommandLineA;
    while (1)
    {
        switch ((UCHAR)*szCmdLine++)
        {
        case 0xEB:
            szCmdLine = szCmdLine + *szCmdLine++;
            break;

        case 0xE9:
            szCmdLine = szCmdLine + *(LPDWORD)szCmdLine + 1;
            break;

        case 0xFF:
            szCmdLine = (CHAR *)*(LPDWORD)(szCmdLine + 1);
            szCmdLine = (CHAR *)*(LPDWORD)szCmdLine;
            break;

        default:
            lpCmdLine = (PANSI_STRING)(*(LPDWORD)szCmdLine - 4);
            goto OUT_LOOP;
            break;
        }
    }
OUT_LOOP:

    hHeap = GetProcessHeap();
    dwMaxBuffer = 0;
    szCmdLine = (CHAR *)HeapAlloc(hHeap, 0, 0);

    do
    {
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
        if(hProcess == NULL)
        {
            continue;
        }

        printf("程序名: %s\n",pe.szExeFile);
        if (ReadProcessMemory(hProcess, (LPCVOID)lpCmdLine, &ansiCmdLine, sizeof(ansiCmdLine), &dwRead))
        {
            if ((DWORD)ansiCmdLine.Length + 1 > dwMaxBuffer)
            {
                dwMaxBuffer = ansiCmdLine.Length + 1;
                szCmdLine = (CHAR *)HeapReAlloc(hHeap, 0, szCmdLine, dwMaxBuffer);
            }
            ReadProcessMemory(hProcess, ansiCmdLine.Buffer, szCmdLine, ansiCmdLine.Length + 1, &dwRead);
            printf("命令行: %s\n", szCmdLine);
        }
        printf("\n");

    } while (Process32Next(hSnapshot, &pe));

    HeapFree(hHeap, 0, szCmdLine);
    _getch();
}


#if 0

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <conio.h>
#include <my_mem.h>

#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Hiromi /SECTION:.Hiromi,ERW")
#pragma comment(linker,"/MERGE:.data=.Hiromi")
#pragma comment(linker,"/MERGE:.rdata=.Hiromi")
#pragma comment(lib,"msvcrt6.lib")

//定义命令行信息结构体
typedef struct tagCOMMANDLINEINFO {
    DWORD dwDestCommand_addr;  //目标进程命令行的起始地址
    DWORD iDestCommandLength;  //目标进程命令行的长度
} COMMANDLINEINFO;
//函数声明
BOOL UpgradeProcessPrivilege(HANDLE, LPCTSTR);
BOOL GetProcessCommandLineInfo(HANDLE, COMMANDLINEINFO *);

int main()
{
    PROCESSENTRY32	pe;
    BOOL			bFirstProcess = TRUE, bSucceed = FALSE;
    DWORD			dwMaxCmdLen = 0;
    HANDLE			hSnapshot, hProcess, hHeap;
    char			*szDestCommand;
    COMMANDLINEINFO	cli;

    UpgradeProcessPrivilege((HANDLE)-1,SE_DEBUG_NAME); //提升本进程的权限
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL); //创建进程快照
    mem_set(&pe, 0, sizeof(PROCESSENTRY32));
    pe.dwSize = sizeof(PROCESSENTRY32);
    hHeap = GetProcessHeap();
    szDestCommand = (char *)HeapAlloc(hHeap, 0, 0);

    do
    {
        if(bFirstProcess)
        {
            bFirstProcess = !(bSucceed = Process32First(hSnapshot, &pe)); //获取第一个进程的信息
        }
        else
        {
            bSucceed = Process32Next(hSnapshot, &pe); //获取下一个进程的信息
        }

        if(bSucceed == FALSE)
        {
            continue;
        }

        hProcess = OpenProcess (PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID); //打开进程
        if(hProcess == NULL)
        {
            continue;
        }

        printf("程序名: %s\n",pe.szExeFile);

        mem_set(&cli, 0, sizeof(COMMANDLINEINFO));
        if(GetProcessCommandLineInfo(hProcess,&cli)) //获取进程的命令行信息
        {
            {
                if (cli.iDestCommandLength > dwMaxCmdLen)
                {
                    szDestCommand = (char *)HeapReAlloc(hHeap, HEAP_ZERO_MEMORY, szDestCommand, cli.iDestCommandLength + 1);
                }
                //读取目标进程的命令行文本
                ReadProcessMemory(hProcess,
                    (const void *)cli.dwDestCommand_addr,
                    szDestCommand,
                    cli.iDestCommandLength,
                    NULL);
                szDestCommand[cli.iDestCommandLength] = 0;
                printf("命令行: %s\n", szDestCommand);
            }
        }
        printf("\n");

        CloseHandle(hProcess); //关闭进程句柄
    } while(bSucceed);

    HeapFree(hHeap, 0, szDestCommand);
    CloseHandle(hSnapshot);  //关闭快照句柄
    getch();
    return 0;
}

BOOL UpgradeProcessPrivilege(HANDLE hProcess,
                             LPCTSTR lpPrivilegeName = SE_DEBUG_NAME)
{
    HANDLE hToken = NULL;
    if(OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken))
    {
        LUID Luid;
        if(LookupPrivilegeValue(NULL, lpPrivilegeName, &Luid))
        {
            TOKEN_PRIVILEGES tp;
            tp.PrivilegeCount = 1;
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            tp.Privileges[0].Luid = Luid;
            return( AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL) );
        }
    }
    return FALSE;
}

BOOL GetProcessCommandLineInfo(HANDLE hProcess, COMMANDLINEINFO *CommandLineInfo)
{
    if(IsBadReadPtr(CommandLineInfo,sizeof(COMMANDLINEINFO))) //判断指针是否有效
        return FALSE;

    HANDLE hThread;

    //启动远程线程，使远程进程执行 GetCommandLineA 函数
    hThread = CreateRemoteThread(hProcess, NULL, 0,
        (LPTHREAD_START_ROUTINE)GetCommandLineA,NULL, 0, NULL);
    if(hThread == 0)
        return FALSE;
    WaitForSingleObject (hThread, INFINITE); //等待远程线程结束
    //获取远程 GetCommandLineA 的返回值，若正常返回，则该值为远程进程命令行的首地址
    GetExitCodeThread (hThread, &(CommandLineInfo->dwDestCommand_addr));
    CloseHandle (hThread);
    if(CommandLineInfo->dwDestCommand_addr == 0)
        return FALSE;

    //启动远程线程，使远程进程执行 lstrlenA 函数
    hThread = CreateRemoteThread(hProcess, NULL, 0,(LPTHREAD_START_ROUTINE)lstrlenA,
        (void *)CommandLineInfo->dwDestCommand_addr, 0, NULL);
    if(hThread == 0)
        return FALSE;
    WaitForSingleObject (hThread, INFINITE);
    //获取远程 lstrlenA 的返回值，若正常返回，则该值为远程进程命令行文本的长度
    GetExitCodeThread (hThread, &(CommandLineInfo->iDestCommandLength));
    CloseHandle (hThread);
    return TRUE;
}

#endif /* 0 */
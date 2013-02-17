#define AUTHOR_NAME "Amano"
#define SECTION_NAME "."AUTHOR_NAME

#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:"SECTION_NAME",ERW /MERGE:.text="SECTION_NAME)
#pragma warning(disable:4995)
#pragma comment(lib, "ImageHlp.lib")
#define UNICODE
#define _UNICODE

#include <Windows.h>
#include <shlobj.h>
#include <Tlhelp32.h>
#include <ImageHlp.h>
#include "my_crt.h"
#include "my_api.h"

typedef struct
{
    UInt32 Num;
    UInt32 dwIpAddress[1];
} SIPLog;

Void FASTCALL ExtractSubtitles(Int argc, PWChar *argv);

class CStopWatch
{
protected:
    LARGE_INTEGER m_Start, m_End, m_Freq;

public:
    CStopWatch()
    {
        QueryPerformanceFrequency(&m_Freq);
    }

    Void Start()
    {
        m_End.QuadPart = 0;
        QueryPerformanceCounter(&m_Start);
    }

    Void Stop()
    {
        QueryPerformanceCounter(&m_End);
    }

    LARGE_INTEGER Difference()
    {
        LARGE_INTEGER elapsed;
        elapsed.QuadPart = m_End.QuadPart - m_Start.QuadPart;
        return elapsed;
    }

    LARGE_INTEGER Elapsed100NanoSeconds()
    {
        LARGE_INTEGER elapsed;
        elapsed.QuadPart = Difference().QuadPart * 1000000000 / m_Freq.QuadPart;
        return elapsed;
    }

    LARGE_INTEGER ElapsedMicroSeconds()
    {
        LARGE_INTEGER elapsed;
        elapsed.QuadPart = Difference().QuadPart * 1000000 / m_Freq.QuadPart;
        return elapsed;
    }

    LARGE_INTEGER ElapsedMilliSeconds()
    {
        LARGE_INTEGER elapsed;
        elapsed.QuadPart = Difference().QuadPart * 1000 / m_Freq.QuadPart;
        return elapsed;
    }
};

double GetCPUFrequencyInMHz()
{
    Int32 Priority, ProcPriority;
    Int64 Cycles, Elapsed, ts1, ts2;
    CStopWatch sw;
    double freq;

    Priority = GetThreadPriority(NtCurrentThread());
    ProcPriority = GetPriorityClass(NtCurrentProcess());
    SetThreadPriority(NtCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
    SetPriorityClass(NtCurrentProcess(), REALTIME_PRIORITY_CLASS);

    sw.Start();
    ts1 = ReadTimeStampCounter();

    Sleep(1);

    ts2 = ReadTimeStampCounter();
    sw.Stop();

    SetThreadPriority(NtCurrentThread(), Priority);
    SetPriorityClass(NtCurrentProcess(), ProcPriority);

    Cycles = ts2 - ts1;
    Elapsed = sw.ElapsedMicroSeconds().QuadPart;
    printf("us: %I64d\n", Elapsed);
    freq = (double)Cycles / Elapsed;
    printf("freq: %lf\n", freq);

    return freq;
}

ForceInline Void main2(Int argc, TChar **argv)
{
    Char buf[0x500], buf2[sizeof(buf)];
    FILE *fp, *fout;

    fp = fopen("test.c", "r");
    if (!fp) return;

    while (fgets(buf, sizeof(buf), fp))
    {
        PChar p1, p2, p3;
        PChar ptype, pparam, pmsg;

        p1 = buf;
        while (*p1 == ' ' || *p1 == '\t') ++p1;
        if (strncmp(p1, "/*", 2))
            continue;

        p1 += 2;
        while (*p1 == ' ' || *p1 == '\t') ++p1;
        ptype = p1;
        p1 = strchr(p1, ' ');
        if (p1 == NULL)
            continue;
        
        *p1++ = 0;

        p1 = strchr(p1, '(');
        if (p1 == NULL)
            continue;

        pparam = p1;
        p1 = strchr(p1, ')');
        if (p1 == NULL)
            continue;

        *++p1 = 0;

        while (fgets(buf2, sizeof(buf2), fp))
        {
            p2 = buf2;
            while (*p2 == ' ' || *p2 == '\t') ++p2;
            if (strncmp(p2, "#define ", 7))
                continue;

            p2 += 7;
            while (*p2 == ' ' || *p2 == '\t') ++p2;
            p3 = strchr(p2, '(');
            if (p3 == NULL)
                continue;

            *p3 = 0;
            pmsg = p2;
            break;
        }

        if (feof(fp))
            break;

        fprintf(stdout, "#define DECL_MSG_HANDLER_%s(fn) %s (fn)%s\n", pmsg + 7, ptype, pparam);
    }

    fclose(fp);

    return;

    for (Int i = 1; i != argc; ++i)
    {
//        fp = _tfopen(*++argv, "rb");
        if (!fp) continue;

//        _tcscpy(buf, *argv);
        rmext(buf);
        strcat(buf, ".txt");
        fout = fopen(buf, "wb");
        if (!fout)
        {
            fclose(fp);
            continue;
        }

        while (fgets(buf, sizeof(buf), fp))
        {
            if (strnicmp(buf, ".message", 8))
                continue;

            Int   len;
            Char  ch;
            PChar pID1, pText1, pText2;

            pID1 = strchr(buf, '\t');
            pText1 = strchr(buf, ' ');
            if (!pID1)
                pID1 = pText1;
            else if (pText1 && pText1 < pID1)
                pID1 = pText1;

            if (!pID1)
                continue;

            ++pID1;
            pText1 = strchr(pID1, ' ');
            pText2 = strchr(pID1, '\t');
            if (!pText1)
                pText1 = pText2;
            else if (pText2 && pText2 < pText1)
                pText1 = pText2;

            if (!pText1)
                continue;

            ch = *pText1;
            *pText1 = 0;
            fprintf(fout, "================================================================%s\n", pID1);
            *pText1 = ch;

            len = strlen(buf) - 1;
            while (buf[len] == '\n' || buf[len] == '\t')
                buf[len--] = 0;

            fprintf(fout, "%s\n"
                          "------------------------------------------------------\n"
                          "%s\n",
                          buf, buf);
        }

        fclose(fp);
        fclose(fout);
    }

    return;

    fp = fopen("1.txt", "r");
    if (!fp) return;

//    fsize(fp);
    while (fgets(buf, sizeof(buf), fp))
    {
        PChar s, e;
        s = strchr(buf, '*');
        if (!s)
            continue;
        ++s;
        e = strchr(s, ')');
        if (!e)
            continue;
        *e = 0;
        printf("GetFuncAddress(f->%s, module, \"%s\");\n", s, s);
    }

    fclose(fp);
}

Void CDECL main(Int argc, TChar **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}

Void FASTCALL ExtractSubtitles(Int argc, PWChar *argv)
{
    UInt32 cur;
    WChar path[MAX_PATH];
    HANDLE hPipeRead, hPipeWrite;
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;

    if (argc < 2)
        return;
/*
    cur = GetModuleFileNameW(0, path, countof(path));
    while (path[--cur] != '\\');
    path[++cur] = 0;
*/

    _wsetlocale(LC_CTYPE, L"");

    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = True;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    wcscpy(path, L"G:\\x\\mkvtoolnix\\mkvinfo.exe");
    cur = wcslen(path);
    for (Int i = 1; i != argc; ++i)
    {
        if (CreatePipe(&hPipeRead, &hPipeWrite, &sa, 0x2000) == False)
        {
            PrintError(GetLastError());
            continue;
        }

        si.dwFlags = STARTF_USESTDHANDLES;
        si.hStdOutput = hPipeWrite;
        swprintf(path + cur, L" \"%s\"", *++argv);
        if (CreateProcessW(NULL, path, NULL, NULL, True, 0, NULL, NULL, &si, &pi) == False)
        {
            PrintError(GetLastError());
            CloseHandle(hPipeWrite);
            CloseHandle(hPipeRead);
            continue;
        }

        WaitForSingleObjectEx(pi.hProcess, INFINITE, False);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        CloseHandle(hPipeWrite);

        PChar pBuf, p1;
        DWORD dwRead, dwAvail;

        if (PeekNamedPipe(hPipeRead, 0, 0, NULL, &dwAvail, NULL))
        {
            pBuf = (PChar)malloc(dwAvail + 4);
            p1 = pBuf;
            ReadFile(hPipeRead, pBuf, dwAvail, &dwRead, NULL);
            *(PUInt32)&pBuf[dwRead] = 0;

            UInt32 count, n;
            PChar psubid, p;
            WChar cmd[MAX_PATH * 3];

            n = 0;
            count = swprintf(cmd, L"%s\"%s\" ", L"G:\\x\\mkvtoolnix\\mkvextract.exe tracks ", *argv);
            rmextw(*argv);
            while (psubid = strstr(pBuf, "Track type: subtitles"))
            {
                p = pBuf;
                pBuf = psubid + 1;
                psubid = StrRStrIA(p, psubid, "Track number:");
                if (psubid == NULL)
                    continue;

                if (sscanf(psubid, "Track number: %u", &dwRead) != 1)
                    continue;

                PCWChar fmt, param;
                static WChar *lang[] = { L"sc", L"tc", L"jp" };

                count += swprintf(cmd + count, L"%u:\"%s.", dwRead, *argv);

                if (n >= 0 && n < countof(lang))
                {
                    fmt = L"%s.ass\" ";
                    param = lang[n];
                }
                else
                {
                    fmt = L"%u.ass\" ";
                    param = (PCWChar)n;
                }

                count += swprintf(cmd + count, fmt, param);
                ++n;
            }

            si.dwFlags = 0;
            if (n && CreateProcessW(NULL, cmd, 0, 0, 0, 0, 0, 0, &si, &pi))
            {
                WaitForSingleObjectEx(pi.hProcess, INFINITE, False);
                CloseHandle(pi.hThread);
                CloseHandle(pi.hProcess);
            }

            free(p1);
        }

        CloseHandle(hPipeRead);
    }
}



















/*

void BassTest()
{
    DWORD   dwBytesPerSample;
    QWORD   qwLength, qwSmaples;
    HSTREAM hStream;
    BASS_CHANNELINFO ChannelInfo;

    if (BASS_Init(1, 44100, 0, NULL, 0) == False)
        return;

    hStream = BASS_MP4_StreamCreateFile(False, "Track02.m4a", 0, 0, 0);
    if (hStream == 0)
    {
        BASS_Free();
        return;
    }

    SetConsoleCtrlHandler(HandlerRoutine, TRUE);
    do
    {
        if (BASS_ChannelGetInfo(hStream, &ChannelInfo) == False)
            break;

        qwLength = BASS_ChannelGetLength(hStream, BASS_POS_BYTE);
        if (qwLength == BASS_INVALID_POSITION)
            break;

        dwBytesPerSample = (ChannelInfo.flags & BASS_SAMPLE_8BITS) ? 1 : 2;
        qwSmaples = qwLength / dwBytesPerSample;
//        if (BASS_ChannelSetPosition(hStream, 0x2900, BASS_POS_DECODE) == False) break;

        if (BASS_ChannelPlay(hStream, False))
        {
            do
            {
                Sleep(10);
                qwLength = BASS_ChannelGetPosition(hStream, BASS_POS_DECODE);
                printf("%I64X / %I64X      \r", qwLength, qwSmaples);
                if (qwLength >= qwSmaples &&
                    BASS_ChannelSetPosition(hStream, 0xB30, BASS_POS_DECODE) == False
//                    BASS_ChannelSetPosition(hStream, 0x2900, BASS_POS_BYTE) == False
                    )
                    break;
            } while (bCtrlC == False);
            BASS_ChannelStop(hStream);
        }
    } while (0);

    BASS_StreamFree(hStream);
    BASS_Free();
}
void CPUUsage()
{
    SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
    SYSTEM_TIME_INFORMATION SysTimeInfo;
    SYSTEM_BASIC_INFORMATION SysBaseInfo;
    DOUBLE dbIdleTime;
    LONG64 dbSystemTime;
    LONG status;
    LARGE_INTEGER liOldIdleTime = {0,0};
    LARGE_INTEGER liOldSystemTime = {0,0};

    // get number of processors in the system
    status = NtQuerySystemInformation(SystemBasicInformation,
        &SysBaseInfo, sizeof(SysBaseInfo), NULL);

    printf("CPU Usage\n");
    while(!_kbhit())
    {
        // get new system time
        NtQuerySystemInformation(SystemTimeInformation, &SysTimeInfo, sizeof(SysTimeInfo), 0);
        // get new CPU'sname idle time
        NtQuerySystemInformation(SystemPerformanceInformation,
            &SysPerfInfo, sizeof(SysPerfInfo), NULL);

        // if it'sname a first call-skip it
        if (liOldIdleTime.QuadPart != 0)
        {
            // CurrentValue = NewValue - OldValue
            dbIdleTime   = (DOUBLE)SysPerfInfo.liIdleTime.QuadPart - liOldIdleTime.QuadPart;
            dbSystemTime = SysTimeInfo.liKeSystemTime.QuadPart - liOldSystemTime.QuadPart;

            // CurrentCpuIdle = IdleTime / SystemTime
            dbIdleTime = dbIdleTime / dbSystemTime;

            // CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors
            dbIdleTime = 100.0 - dbIdleTime * 100.0 / SysBaseInfo.bKeNumberProcessors + 0.5;

            printf("%d%%             \r",(UINT)dbIdleTime);
        }

        // store new CPU'sname idle and system time
        liOldIdleTime = SysPerfInfo.liIdleTime;
        liOldSystemTime = SysTimeInfo.liKeSystemTime;

        // wait one second
        Sleep(1000);
    }
    printf("\n");
}
*/
// & > ^ > |

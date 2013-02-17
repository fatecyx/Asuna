#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(linker, "/subsystem:windows")

#include <dsound.h>
#include <Psapi.h>
#include "my_headers.h"

ForceInline void __cdecl main2(int argc, char **argv)
{
    HANDLE hEvent;
    IDirectSound *lpDS;

    hEvent = OpenEventW(EVENT_ALL_ACCESS, FALSE, L"_FIX_WIN7_SOUND_BUG_");
    if (hEvent)
    {
        WCHAR  end;
        LPWSTR lpCmdLine = GetCommandLineW();

        end = *lpCmdLine++ == '\"' ? '\"' : ' ';
        while (*lpCmdLine != end) ++lpCmdLine;
        ++lpCmdLine;
        while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;

        if ((*lpCmdLine++ & 0xDF) == 'Q')
        {
            switch (*lpCmdLine)
            {
            case ' ':
            case 0:
                SetEvent(hEvent);
                break;
            }
        }

        CloseHandle(hEvent);
        return;
    }

    hEvent = CreateEventW(NULL, FALSE, FALSE, L"_FIX_WIN7_SOUND_BUG_");
    if (hEvent == NULL)
    	return;

    if (FAILED(DirectSoundCreate(NULL, &lpDS, NULL)))
        return;

    DWORD  dwSize;
    LPVOID lpLockBuffer;
    WAVEFORMATEX wfx;
    STARTUPINFOW  si;
    PROCESS_INFORMATION pi;
    IDirectSoundBuffer *lpDSBuffer, *lpPrimaryDSBuffer;
    DSBUFFERDESC DSBufferDesc = { sizeof(DSBufferDesc) };

    do
    {
        if (FAILED(lpDS->SetCooperativeLevel(GetDesktopWindow(), DSSCL_PRIORITY)))
            break;

        DSBufferDesc.dwFlags = DSBCAPS_CTRLVOLUME|DSBCAPS_PRIMARYBUFFER;
        if (FAILED(lpDS->CreateSoundBuffer(&DSBufferDesc, &lpPrimaryDSBuffer, NULL)))
            break;

        wfx.wFormatTag      = WAVE_FORMAT_PCM;
        wfx.nChannels       = 2;
        wfx.nSamplesPerSec  = 44100;
        wfx.nAvgBytesPerSec = 176400;
        wfx.nBlockAlign     = 4;
        wfx.wBitsPerSample  = 16;
        wfx.cbSize          = sizeof(wfx);

        DSBufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS;
        DSBufferDesc.dwBufferBytes = 0x400;
        DSBufferDesc.lpwfxFormat = &wfx;

        if (FAILED(lpDS->CreateSoundBuffer(&DSBufferDesc, &lpDSBuffer, NULL)))
        {
            lpPrimaryDSBuffer->Release();
            break;
        }

        lpDSBuffer->Lock(0, 0, &lpLockBuffer, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER);
        memset(lpLockBuffer, 0, dwSize);
        lpDSBuffer->Unlock(lpLockBuffer, dwSize, NULL, 0);
        lpDSBuffer->Play(0, 0, 0);
        lpDSBuffer->Stop();

        lpDSBuffer->Release();
        lpPrimaryDSBuffer->Release();

        GetStartupInfoW(&si);

        SetExecuteDirectoryAsCurrentW();
        if (CreateProcessW(NULL, L"E:\\Python27\\python.exe s1mission.py", 0, 0, FALSE, 0, 0, 0, &si, &pi))
        {
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }

        if (CreateProcessW(NULL, L"C:\\Program Files\\ATI Tray Tools\\atitray.exe", 0, 0, FALSE, 0, 0, 0, &si, &pi))
        {
            WaitForInputIdle(pi.hProcess, INFINITE);
            TerminateProcess(pi.hProcess, 0);
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }

        WaitForSingleObjectEx(hEvent, INFINITE, FALSE);
/*
        SetCurrentDirectoryW(L"E:\\Desktop\\mix\\QQGet2D");

        dwSize = 0;
//        si.dwFlags = STARTF_USESHOWWINDOW;
//        si.wShowWindow = SW_MINIMIZE;

        do
        {
            if (dwSize == 0)
            {
                ++dwSize;
                continue;
            }
            else if (dwSize != 4)
            {
                ++dwSize;
                if (CreateProcessW(L"115PickStorage.exe", 0, 0, 0, FALSE, 0, 0, 0, &si, &pi))
                {
                    CloseHandle(pi.hThread);
                    CloseHandle(pi.hProcess);
                }
            }
        } while (WaitForSingleObjectEx(hEvent, 14400000, FALSE) == WAIT_TIMEOUT);
*/
    } while (0);

    lpDS->Release();
    CloseHandle(hEvent);
    return;
}

void __cdecl main(int argc, char **argv)
{
    main2(argc, argv);
    ExitProcess(0);
}
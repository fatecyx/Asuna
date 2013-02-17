#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"
#include "CrossDaysGpk.h"

Bool bCtrlC;

BOOL CALLBACK HandlerRoutine(DWORD dwCtrlType)
{
    switch(dwCtrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        bCtrlC = True;
        return True;
    }

    return False;
}

ForceInline void main2(int argc, WChar **argv)
{
    if (argc < 2)
    {
        wprintf(L"Usage: %s xxx.gpk yyy.gpk zzz.gpk ...\n", findnamew(argv[0]));
        return;
    }

    Char buf[20];
    WChar szPath[MAX_PATH];
    CCrossDaysGpk cdg;

    SetConsoleCtrlHandler(HandlerRoutine, True);
    for (int i = 1; i != argc && bCtrlC == False; ++i)
    {
        TMyGpkIndex *pIndex;
        if (cdg.Open(argv[i]) == CDG_SUCCESS)
        {
            wcscpy(szPath, argv[i]);
            rmextw(szPath);
            for (int i = 0; i != cdg.GetFileCount() && bCtrlC == False; ++i)
            {
                sprintf(buf, "%u / %u", i + 1, cdg.GetFileCount());
                SetConsoleTitleA(buf);
                pIndex = cdg.GetIndexPointer(i);
                wprintf(L"Extracting %s/%s ... ", findnamew(szPath), pIndex->szName);
                wprintf(L"%s\n", cdg.ExtractFile(pIndex, szPath) == CDG_SUCCESS ? L"OK" : L"failed");
            }
        }
        else
        {
            printf("Open \"%s\" failed\n", argv[i]);
        }
    }

    if (bCtrlC) printf("User abort\n");
}

void __cdecl main(int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
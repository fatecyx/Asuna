#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"
#include "neko.h"

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

ForceInline Void main2(Int argc, Char **argv)
{
    UInt32 len;
    Char *pszName, *p, szPath[MAX_PATH], buf[0x200];
    CNekoPack neko;
    FILE *fp;

    strcpy(szPath, argv[0]);
    rmname(szPath);
    strcat(szPath, "list.txt");
    fp = fopen(szPath, "r");
    if (fp == NULL)
        *(PUInt32)buf = TAG4('AUTO');

    SetConsoleCtrlHandler(HandlerRoutine, True);
    for (Int i = 1; i != argc && !bCtrlC; ++i)
    {
        fseek(fp, SEEK_SET, 0);
        if (neko.Open(*++argv))
        {
            pszName = *argv;
            strcpy(szPath, pszName);
            rmext(szPath);
            pszName = findname(pszName);
            while ((!fp || fgets(buf, sizeof(buf), fp)) && !bCtrlC)
            {
                if (buf[0] == ';')
                    continue;

                UInt32 v = *(PUInt32)buf & 0xDFDFDFDF;
                if (v == TAG4('AUTO'))
                {
                    neko.ExtractAll(szPath);
                    break;
                }
                else if (v == TAG4('EXIT'))
                    break;

                p = strchr(buf, ' ');
                if (p == NULL)
                    continue;

                *p++ = 0;
                if (stricmp(buf, pszName))
                    continue;

                len = strlen(p) - 1;
                while (p[len] == '\n' || p[len] == '\r')
                    p[len] = 0;
                if (*szPath == 0)
                    continue;

                if (neko.ExtractFile(p, szPath))
                    printf("Extracting \"%s\" ... OK\n", p);
            }
        }
    }
    if (bCtrlC)
    {
        printf("user abort\n");
        getch();
    }

    fclose(fp);
}

void __cdecl main(Int argc, Char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
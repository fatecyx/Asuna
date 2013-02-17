#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")
#pragma comment(lib, "Shlwapi.lib")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_mem.h"

/*

.img visual
.img0 back
.img1 ... .img7 actor

.env sound/env
.bgm bgm

:Õ¼¤¤¤ªŠ—¤µ¤ó:XXA_P00_0001:XXA	voice

*/
static Char *internal[] =
{
    "center", "right", "left",   "clear", "front", "back", "flat",
    "accel",  "decel", "normal", "slow",  "fast",  "fade", "to",
};

Void PeekFile(LPWSTR lpFileName, FILE *fp)
{
    FILE *fin;
    UInt32 len;
    Char c, *p, *p2, buf[0x1024];

    fin = _wfopen(lpFileName, L"r");
    if (!fin)
        return;

    while (fgets(buf, countof(buf), fin))
    {
        len = strlen(buf) - 1;
        while (buf[len] == '\n' || buf[len] == '\r')
            buf[len] = 0;
        if (buf[0] == 0)
            continue;

        p = buf;
        while (*p == ' ' || *p == '\t') ++p;
        c = *p;
        if (c == ';')  // comment
            continue;

        ++p;
        if (c == ':')   // char name
        {
            p2 = strchr(p, ':');
            if (p2 == NULL)
                continue;

            p = strchr(++p2, ':');
            if (p == NULL || p == p2)    // correct format :name:voice_name:AK
                continue;
            *p = 0;
            fprintf(fp, "voice.dat voice\\%s.ogg\n", p2);
            continue;
        }
        else if (c == '.')
        {
            UInt32 cnt, v = *(PUInt32)p & 0xDFDFDFDF;

            p2 = strchr(p, ' ');
            if (p2 == NULL || *++p2 == 0)
                continue;

            if (v == TAG4('CALL') || v == TAG4('HORO'))
            {
                fprintf(fp, "system.dat script\\%s.txt\n", p2);
            }

            for (cnt = 0; cnt != countof(internal); ++cnt)
            {
                len = strlen(internal[cnt]);
                if (!strncmp(p2, internal[cnt], len))
                    break;
            }
            if (cnt != countof(internal))
                    continue;

            p = strchr(p2, ' ');
            if (p) *p = 0;
            if (v == TAG4('SYST'))  // .system
            {
                fprintf(fp, "system.dat system\\%s\n", p2);
            }
            else if ((v & 0xFFFFFF) == TAG3('IMG'))
            {
                PChar pdir, p3;

                v >>= 24;
                pdir = v == 0 ? "visual" : v == ('0' & 0xDF) ? "back" : "actor";
                fprintf(fp, "image.dat image/%s\\%s.png\n", pdir, p2);
                continue;

                p = buf + strlen(buf) + 1;
                cnt = sprintf(p, "image.dat image/%s\\%s.png\n", pdir, p2);
                p3 = p;
                p = p + cnt - 7;
                c = *p++;
                if (c <= '9' && c >= '0' && (c = *p), c <= 'z' && c >= 'a')
                {
                    *p = 'a' - 1;
                    while (++*p != 'z' + 1)
                        fprintf(fp, "%s", p3);
                }
                else
                {
                    fprintf(fp, "%s", p3);
                }
            }
            else if ((v & 0xFFFFFF) == TAG3('BGM'))
            {
                fprintf(fp, "sound.dat sound/bgm\\%s.ogg\n", p2);
            }
            else if ((v & 0xFFFFFF) == TAG3('ENV'))
            {
                fprintf(fp, "sound.dat sound/env\\%s.ogg\n", p2);
            }
            else if ((v & 0xFFFFFF) == (TAG3('SE ') & 0xDFDFDF))
            {
                fprintf(fp, "sound.dat sound/se\\%s.ogg\n", p2);
            }
        }
    }

    fclose(fin);
}

Void PeekFolder(LPWSTR lpPath, LPWIN32_FIND_DATAW pWfd, FILE *fp)
{
    LPWSTR lpEnd;
    HANDLE hFind;

    if (GetFileAttributesW(lpPath) == -1)
        return;

    lpEnd = lpPath + lstrlenW(lpPath);
    lstrcpyW(lpEnd, L"\\*.*");

    hFind = FindFirstFileW(lpPath, pWfd);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!lstrcmpW(pWfd->cFileName, L".") || !lstrcmpW(pWfd->cFileName, L".."))
                continue;

            lstrcpyW(lpEnd + 1, pWfd->cFileName);
            if (pWfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                PeekFolder(lpPath, pWfd, fp);
            }
            else
            {
                PeekFile(lpPath, fp);
            }
        } while (FindNextFileW(hFind, pWfd));
        FindClose(hFind);
    }

    *lpEnd = 0;
}

void ForceInline main2(int argc, wchar_t **argv)
{
    LPWSTR lpFileName;
    WCHAR  szPath[MAX_PATH];
    HANDLE hFind;
    WIN32_FIND_DATAW wfd;
    FILE *fp;

    lstrcpyW(szPath, argv[0]);
    lpFileName = findnamew(szPath);
    lstrcpyW(lpFileName, L"list.txt");
    fp = _wfopen(szPath, L"wb");
    if (!fp)
    {
        _wperror(szPath);
        return;
    }

    fprintf(fp, "system.dat script\\start.txt\n");
    setlocale(LC_CTYPE, "");
    for (int i = 1; i != argc; ++i)
    {
        hFind = FindFirstFileW(argv[i], &wfd);
        if (hFind == INVALID_HANDLE_VALUE)
            continue;

        lstrcpyW(szPath, argv[i]);
        lpFileName = findnamew(szPath);

        do
        {
            if (!lstrcmpW(wfd.cFileName, L".") || !lstrcmpW(wfd.cFileName, L".."))
                continue;

            lstrcpyW(lpFileName, wfd.cFileName);

            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                PeekFolder(szPath, &wfd, fp);
            else
                PeekFile(szPath, fp);
        } while (FindNextFileW(hFind, &wfd));

        FindClose(hFind);
    }

    fclose(fp);
}

void __cdecl main(int argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
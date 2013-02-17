#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text /MERGE:.CRT=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma warning(disable:4530)
#pragma comment(lib, "Image.lib")

#include <Windows.h>
#include <vector>
#include "my_headers.h"
#include "Image.h"
#include "Mem.cpp"

OVERLOAD_OP_NEW

using std::vector;
typedef struct
{
    WChar FullPath[MAX_PATH];
} SFullPath;

typedef MyLib::Vector<SFullPath> VectorPath;

typedef struct
{
    VectorPath &pfiles;
    UInt32 CurIndex;
    PWChar opt;
    PWChar Options;
    PWChar pCurPath;
    Bool bQuiet;
} SThreadParam;

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

DWORD WINAPI EncodeThread(LPVoid lpParam)
{
    Bool   r;
    PByte  pbBuffer;
    WChar  szPath[MAX_PATH], opt[MAX_PATH * 4];
    ULong  BufferSize, BytesRead, OrigSize, UCISize;
    HANDLE hReadPipe, hWritePipe, hFile;
    SThreadParam *param;
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;
    CMem m;
    UCI_META_INFO UciMeta;

    BufferSize = 0x1000;
    param = (SThreadParam *)lpParam;
    pbBuffer = (PByte)m.Alloc(BufferSize);

    sa.nLength = sizeof(sa);
    sa.bInheritHandle = True;
    sa.lpSecurityDescriptor = NULL;

    GetStartupInfoW(&si);
    si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.wShowWindow = SW_HIDE;

    UciMeta.Magic  = TAG4('META');
    UciMeta.cbSize = sizeof(UciMeta);
    for (UInt32 i = 0, j = param->pfiles.size(); !bCtrlC;)
    {
        SImage *pImage;

        i = _InterlockedIncrement((PLong)&param->CurIndex) - 1;
        if (i >= j)
            break;

        hFile = CreateFileW(param->pfiles[i].FullPath,
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    &sa,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            continue;
        }

        OrigSize = GetFileSize(hFile, NULL);
        if (OrigSize > BufferSize)
        {
            BufferSize = OrigSize;
            pbBuffer = (PByte)m.ReAlloc(pbBuffer, BufferSize);
        }

        ReadFile(hFile, pbBuffer, OrigSize, &BytesRead, NULL);
        CloseHandle(hFile);
        pImage = Decode(pbBuffer, OrigSize);
        if (pImage == NULL)
            continue;

        Int32 bpp, stride;
        SBitMapHeader Header;

        bpp = pImage->pFrame[0].bpp;
        switch (bpp)
        {
            case 8:
                InitBitmapHeader(&Header, pImage->pFrame[0].width, pImage->pFrame[0].height, 24, &stride);
                BytesRead = stride * Header.Info.dwHeight + sizeof(Header);
                break;

            case 24:
            case 32:
                BytesRead = pImage->pFrame[0].size;
                break;

            default:
                Destroy(pImage);
                swprintf(opt, L"%s: bpp = %u: unsupport\n", param->pfiles[i].FullPath, bpp);
                MessageBoxW(0, opt, 0, 64);
                continue;
        }

        if (BytesRead > BufferSize)
        {
            BufferSize = BytesRead;
            pbBuffer = (PByte)m.ReAlloc(pbBuffer, BufferSize);
        }

        if (bpp == 8)
        {
            PByte buf, pSrc;
            Int32 gray_stride;
            LPCOLORREF pPalette;

            buf = pbBuffer;
            pPalette = (LPCOLORREF)(pImage->pFrame[0].buffer + sizeof(Header));

            memcpy(buf, &Header, sizeof(Header));
            buf += sizeof(Header);
            pSrc = pImage->pFrame[0].buffer;
            pSrc += ((SBitMapHeader *)pImage->pFrame[0].buffer)->dwRawOffset;
            gray_stride = (Header.Info.dwWidth + 3) & ~3;

            for (UInt32 h = 0; h != Header.Info.dwHeight; ++h)
            {
                PByte src;
                SPixel *dst;

                src = pSrc;
                dst = (SPixel *)buf;
                for (UInt32 w = 0; w != Header.Info.dwWidth; ++w)
                {
                    *(LPCOLORREF)dst++ = pPalette[*src++];
                }

                buf += stride;
                pSrc += gray_stride;
            }
        }
        else
        {
            memcpy(pbBuffer, pImage->pFrame[0].buffer, BytesRead);
        }

        UciMeta.Width        = pImage->pFrame->width;
        UciMeta.Height       = pImage->pFrame->height;
        UciMeta.BitsPerPixel = pImage->pFrame->bpp;

        Destroy(pImage);

        lstrcpyW(szPath, param->pfiles[i].FullPath);
        lstrcpyW(findextw(szPath), L".uci");

        if (CreatePipe(&hReadPipe, &hWritePipe, &sa, BytesRead) == False)
        {
            CloseHandle(hFile);
            continue;
        }

        hFile = CreateFileW(szPath,
                    GENERIC_WRITE,
                    FILE_SHARE_WRITE,
                    &sa,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            continue;
        }

        WriteFile(hWritePipe, pbBuffer, BytesRead, &BytesRead, NULL);
        CloseHandle(hWritePipe);

        swprintf(opt, L"%sucienc.exe - -o - %s", param->pCurPath, param->Options);
        si.hStdInput  = hReadPipe;
        si.hStdOutput = hFile;
        r = CreateProcessW(NULL, opt, 0, 0, True, CREATE_NEW_CONSOLE, 0, 0, &si, &pi);
        CloseHandle(hReadPipe);

        if (param->bQuiet == False)
            PrintConsoleW(L"%s => %s ... ", param->pfiles[i].FullPath, szPath);

        if (r == False)
        {
            if (param->bQuiet == False)
                PrintConsoleW(L"failed\n");
            CloseHandle(hFile);
            continue;
        }
        
        SetPriorityClass(pi.hProcess, BELOW_NORMAL_PRIORITY_CLASS);
        CloseHandle(pi.hThread);
        WaitForSingleObjectEx(pi.hProcess, INFINITE, False);
        CloseHandle(pi.hProcess);

        SetFilePointer(hFile, 0, 0, FILE_END);
        WriteFile(hFile, &UciMeta, sizeof(UciMeta), &BytesRead, NULL);

        UCISize = GetFileSize(hFile, NULL);
        CloseHandle(hFile);

        WChar symbol;
        if (OrigSize > UCISize)
            symbol = '>';
        else if (OrigSize < UCISize)
            symbol = '<';
        else
            symbol = '=';

        if (param->bQuiet == False)
            PrintConsoleW(L"OK @ %u %c %u (%.2f%%)\n\n",
                    OrigSize, symbol, UCISize, (double)UCISize * 100 / OrigSize);

        swprintf(szPath, L"%u / %u", i + 1, j);
        SetConsoleTitleW(szPath);
    }

    m.Free(pbBuffer);

    return 0;
}

LONG STDCALL CallBack(PVOID lpBuffer, LPWIN32_FIND_DATAW pFindData, ULONG_PTR lpParam)
{
    PWChar pszExtension;
    VectorPath *pFiles = (VectorPath *)lpParam;    
    static WChar *suffix[] = { L".bmp", L".png", L".tga", L".jpg", L".gif", L".tif" };

    UNREFERENCED_PARAMETER(lpBuffer);

    pszExtension = findextw(pFindData->cFileName);
    for (Int32 i = 0; i != countof(suffix); ++i)
    {
        if (!StrICompareW(pszExtension, suffix[i]))
        {
            (*pFiles).push_back(*(SFullPath *)&pFindData->cFileName);
            break;
        }
    }

    return 0;
}

void ForceInline main2(int argc, WChar **argv)
{
    Bool bDebug;
    UInt32 Threads;
    ULong  EnumFlags;

    PWChar InPath;
    VectorPath files;
    SThreadParam param = { files, 0, 0, 0, 0, 0 };

    EnumFlags = 0;
    bDebug  = False;
    Threads = 0;
    InPath  = NULL;
    setlocale(LC_CTYPE, "");
    SetConsoleCtrlHandler(HandlerRoutine, True);

    for (Int32 i = 1; i < argc; ++i)
    {        
        if (argv[i][0] != '-')
        {            
            InPath = argv[i];
            
            EnumDirectoryFiles(
                NULL,
                L"*.*",
                0,
                argv[i],
                NULL,
                CallBack,
                (ULONG_PTR)&files,
                EnumFlags);
        }
        else if (!StrICompareW(argv[i], L"-opt"))
        {
            if (++i >= argc)
                break;

            param.Options = argv[i];
        }
        else if (!StrICompareW(argv[i], L"-dbg"))
        {
            bDebug = True;
        }
        else if (!StrICompareW(argv[i], L"-q"))
        {
            param.bQuiet = True;
        }
        else if (!StrICompareW(argv[i], L"-threads"))
        {
            if (++i >= argc)
                break;

            Threads = (UInt32)StringToInt64W(argv[i]);
        }
        else if (!StrICompareW(argv[i], L"-subdir"))
        {
            EnumFlags |= ENUM_DIRECTORY_FILES_FLAG_ENUMSUBDIR;
        }
    }

    if (files.size() == 0)
        return;

    PHANDLE phTread;
    WChar *curpath, *Options;

    curpath = L"G:\\x\\UCI\\";
    if (param.Options == NULL)
        param.Options = L"-quiet -s";

    param.CurIndex = 0;
    param.pCurPath = curpath;
    Options = param.Options;

    while (Options = wcschr(Options, '\''))
    {
        *Options++ = '"';
    }

    if (bDebug || Threads == 1)
    {
        EncodeThread(&param);
        return;
    }

    if (Threads == 0)
    {
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        Threads = si.dwNumberOfProcessors;
    }

    phTread = (PHANDLE)_alloca(Threads * sizeof(*phTread));

    for (UInt32 i = 0; i != Threads; ++i)
    {
        phTread[i] = CreateThread(0, 0, EncodeThread, &param, 0, 0);
    }

    WaitForMultipleObjectsEx(Threads, phTread, True, INFINITE, False);
    for (UInt32 i = 0; i != Threads; ++i)
        CloseHandle(phTread[i]);
}

void __cdecl main(Int argc, WChar **argv)
{
    setlocale(LC_ALL, ".936");
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}

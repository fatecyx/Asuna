#pragma comment(linker,"/ENTRY:wWinMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "FtpUI.h"
#include "Mem.cpp"

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    static Bool b;
    Char buf[200];

    wsprintfA(buf, "code = %X\n"
        "addr = %p\n",
        ExceptionInfo->ExceptionRecord->ExceptionCode,
        ExceptionInfo->ExceptionRecord->ExceptionAddress);

    return EXCEPTION_CONTINUE_SEARCH;
}

ForceInline UInt WinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWChar lpCmdLine, INT nCmdShow)
{
    AddVectoredExceptionHandler(TRUE, VectoredHandler);

    CFtpUI ftp;
    UNUSED_VARIABLE(hPrevInstance);
    UNUSED_VARIABLE(lpCmdLine);
    UNUSED_VARIABLE(nCmdShow);
    return ftp.Run(hInstance);
}

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWChar lpCmdLine, INT nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
/*
    WChar end;
    lpCmdLine = GetCommandLineW();
    end = *lpCmdLine++ == '\"' ? '\"' : ' ';
    while (*lpCmdLine && *lpCmdLine != end) ++lpCmdLine;
    if (*++lpCmdLine)
    {
        while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;
    }
*/
    ExitProcess(WinMain2(GetModuleHandleW(NULL), 0, lpCmdLine, SW_SHOWDEFAULT));
}
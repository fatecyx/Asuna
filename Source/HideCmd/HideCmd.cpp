/* -*- C -*- */
/**
* \file hidecmd.c
* This file is part of LyX, the document processor.
* Licence details can be found in the file COPYING.
*
* \author hasherfrog
* \author Bo Peng
*
* Full author contact details are available in file CREDITS.
*/

/**
*  This utility function is used to start lyx under windows, but
*  hide the console window. It is adapted from program hidec at
*  http://www.msfn.org/board/index.php?showtopic=49184&mode=threaded
*
*  Usage:
*    hidecmd [/w] [/VAR=val] <filename> [<params>]
*  where: /w         wait for program termination
*        /VAR=val    set VAR=val
*        <filename>  executable program
*        <params>    program parameters
*
*  How to built this program:
*  msvc:
*    cl.exe hidecmd.c /GA /O1 /link /subsystem:windows \
*       kernel32.lib advapi32.lib user32.lib libcmt.lib
*  mingw/gcc:
*    gcc -mno-cygwin -mwindows hidecmd.c -o hidecmd
*
*/
// The original author used some tricks to reduce executable
// size. They are removed to make the program compatible to
// mingw/gcc.
//
// do not link to default libraries
//#pragma comment(linker,"/NODEFAULTLIB")
// unite code and data section (make the program smaller)
//#pragma comment(linker,"/MERGE:.rdata=.text")
// resolve record in section of code (?)
//#pragma comment(linker,"/SECTION:.text,EWR")
// the new entry point (why?)

#include <windows.h>
#include <process.h>

/*
char usage[] = "HideCmd [/w] [/VAR=val] <filename> [<params>]\n"
"  where: /w         wait for program termination\n"
"        /VAR=val    set VAR=val\n"
"        <filename>  executable program\n"
"        <params>    program parameters\n";
*/

#pragma comment(linker, "/ENTRY:wWinMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Hiromi,ERW /MERGE:.text=.Hiromi")
#pragma comment(lib, "undoc_k32.lib")

#include <Windows.h>
#include "my_headers.h"
#include "my_commsrc.h"

Int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWChar lpCmdLine, Int nCmdShow)
{
    WChar end;
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    lpCmdLine = Nt_GetCommandLine();
    end = *lpCmdLine++ == '\"' ? '\"' : ' ';
    while (*lpCmdLine && *lpCmdLine != end) ++lpCmdLine;
    if (*++lpCmdLine)
    {
        while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;
    }

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(STARTUPINFOW);
    si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

    return CreateProcessInternalW(
                NULL,
                NULL,
                lpCmdLine,
                NULL,
                NULL,
                FALSE,
                CREATE_NEW_CONSOLE,
                NULL,
                NULL,
                &si,
                &pi,
                NULL
             );
}

#if 0

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPWSTR cmdLine, int nCmd)
{
    PROCESS_INFORMATION pi;
    STARTUPINFOA si = { sizeof(STARTUPINFOA) };

	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	cmdLine = GetCommandLineW() + 1;
	while (*cmdLine != '"')
        ++cmdLine;

	++cmdLine;
	while (*cmdLine == ' ' || *cmdLine == 0x9)
        ++cmdLine;

	return 0;

	int bWait = 0;
	DWORD exitcode = 0;
	char delim = ' ';
	char var[128];
	char val[128];
	int err = 0;
	int i;
	// start and end of variable/value
	char * s;
	char * e;
	hInst = GetModuleHandle(NULL);
	hPrev = NULL;
	cmdLine = GetCommandLine();
	nCmd = SW_SHOWNORMAL;

	// use WinMain, command name is excluded ...
	// skip over ' ' or '\t'
	while ((cmdLine[0] != 0) && ((cmdLine[0] == ' ') || (cmdLine[0] == '\t')))
		cmdLine++;

	while (*cmdLine == '/')
	{
		// /w or /W option
		if (((cmdLine[1] == 'w') || (cmdLine[1] == 'W')) &&
			(cmdLine[2] == ' '))
		{
			bWait = 1;
			cmdLine += 3;
			// environment variable
		}
		else
		{
			cmdLine++;

			// get var
			s = var;
			e = s + sizeof(var) - 1;

			while (*cmdLine != 0 && *cmdLine != '=')
			{
				if (s < e)
				{
					*s++ = *cmdLine++;
				}
				else
				{
					cmdLine++;
					err = 1;
				}
			}

			// get value
			*s = 0;
			if (*cmdLine == '=')
				cmdLine++;

			delim = ' ';

			if (*cmdLine == '\"')
			{
				delim = '\"';
				cmdLine++;
			}

			s = val;
			e = s + sizeof(val) - 1;

			while (*cmdLine != delim && *cmdLine != 0)
			{
				if (s < e)
				{
					*s++ = *cmdLine++;
				}
				else
				{
					cmdLine++;
					err = 1;
				}
			}
			*s = 0;
			if (*cmdLine == delim)
				cmdLine++;

			SetEnvironmentVariable(var, val);
			// MessageBox(0, val, var, 0);
		}

		// skip spaces
		while ((*cmdLine != 0) && ((*cmdLine == ' ') || (*cmdLine == '\t')))
			cmdLine++;
	}

	// report error if there is no parameter
	if (*cmdLine == 0)
	{
		MessageBox(NULL, usage, "Usage", MB_ICONINFORMATION);
		ExitProcess(0);
	}

	if (err)
	{
		MessageBox(NULL,
				   "One of the specified environment variables or its value is too long.",
				   "Error: Variable name or value too long",
				   MB_ICONERROR);
		ExitProcess(0);
    }

	// create process with new console
	// memset(&si, 0, sizeof(si));
	s = (char *) &si;
    for (i = 0; i < sizeof(si); ++i)
		s[i] = 0x00;
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	if (CreateProcess(NULL, cmdLine,
		NULL, NULL, FALSE, CREATE_NEW_CONSOLE,
		NULL, NULL, &si, &pi))
	{
		if (bWait)
			WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );
	}
	else
		exitcode = GetLastError();

	/* terminate this */
	ExitProcess(exitcode);
}

#endif

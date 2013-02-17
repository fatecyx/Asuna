// Process Scheduler

#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Hiromi /SECTION:.Hiromi,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Hiromi")
#pragma comment(linker,"/MERGE:.data=.Hiromi")

#include "Scheduler.h"
#include "Process.h"
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <conio.h>
#include "my_conio.h"
#include "getmainargs.h"

BOOL bCtrlC;
LONG lVal1, lVal2;
extern FILE *fOutput;
extern PCB pcb[MAX_PROCESS_NUM];

VOID CDECL SigIntHandler(int a)
{
    bCtrlC = TRUE;
}

int CDECL main(int argc, char **argv)
{
	DWORD  dwProcessId;
	HANDLE hProcess;

//	getargs(&argc, &argv);
	srand(time(NULL));
	Initialization(argc, argv);

	fprintf(stdout, "%u.%u\n", _MSC_VER / 100, _MSC_VER % 100);
	fprintf(fOutput, "lVal1 = %d, lVal2 = %d\n", lVal1, lVal2);
	for (int i = 0; i != MAX_PROCESS_NUM; ++i)
	{
		fprintf(fOutput, "Process %d priority: %d\n", i, pcb[i].dwPriorityClass);
	}
	fprintf(stdout, "Press any key to start");
	getch();
	fprintf(stdout, "\r                      \n");

	signal(SIGINT, SigIntHandler);

	while (bCtrlC == FALSE)
	{
		hProcess = Scheduler();
		if (hProcess == INVALID_HANDLE_VALUE)
			break;

		switch (dwProcessId = MyGetProcessId(hProcess))
		{
		case 0:
			Process1(hProcess);
			break;

		case 1:
			Process2(hProcess);
			break;

		case 2:
			Process3(hProcess);
			break;

		default:
			fprintf(fOutput, "Error process id: %d\n", dwProcessId);
			break;
		}
	}

	if (bCtrlC)
	{
		fprintf(fOutput, "Aborted by user.\n");
		getch();
	}

	fprintf(fOutput, "Value1 = %d, Value2 = %d\n"
					 "Elapsed time: %d ms\n", lVal1, lVal2, clock());
	fclose(fOutput);
	getch();

	return 0;
}
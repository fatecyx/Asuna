#include "Scheduler.h"
#include <stdio.h>

extern LONG lVal1, lVal2;
FILE      *fOutput;
INT32      iRegister, Protection[MAX_PROCESS_NUM];
HANDLE     hCurrentProcess;
PCB        pcb[MAX_PROCESS_NUM];
TSemaphore sem[SEMAPHORE_NUM];
CHAR       *szStates[] =
{
	"STATE_EXECUTION",
	"STATE_WAITING",
	"STATE_LOWREADY",
	"STATE_HIGHREADY",
	"STATE_COMPLETION",
};

VOID STDCALL Initialization(int argc, char **argv)
{
	for (DWORD i = 0; i != countof(pcb); ++i)
	{
		pcb[i].bFirst = TRUE;
		pcb[i].dwProcessId = i;
		pcb[i].State = STATE_HIGHREADY;
		pcb[i].dwNextProcessId = INVALID_PROCESS_ID;
		pcb[i].dwPriorityClass = rand() % MAX_PRIORITY;
	}
	
	for (DWORD i = 0; i != countof(sem); ++i)
	{
		sem[i].lCount = 1;
		sem[i].dwFirstProcessId = INVALID_PROCESS_ID;
	}
	
	for (int i = 1; i != argc; ++i)
	{
		if (*(PWORD)argv[i] == 'f-')
		{
			if (i + 1 < argc)
				fOutput = fopen(argv[i + 1], "wb");
		}
	}
	fOutput = fOutput == NULL ? stdout : fOutput;
	hCurrentProcess = INVALID_HANDLE_VALUE;
}

HANDLE STDCALL Scheduler()
{
	DWORD  dwProcessId, dwCurrentProcessId;
	HANDLE hProcess;
	PROCESS_STATE OldState;
	
	hProcess = FindNextProcess();
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		if (hCurrentProcess == INVALID_HANDLE_VALUE)
			return INVALID_HANDLE_VALUE;
	}
	else
	{
		dwProcessId = MyGetProcessId(hProcess);
		dwCurrentProcessId = MyGetProcessId(hCurrentProcess);
		if (hCurrentProcess == INVALID_HANDLE_VALUE)
		{
			OldState = pcb[dwProcessId].State;
			pcb[dwProcessId].State = STATE_EXECUTION;
			hCurrentProcess = hProcess;
			fprintf(fOutput, "Process %d: %s -> %s\n",
				dwProcessId,
				szStates[OldState],
				szStates[pcb[dwProcessId].State]);
		}
		else if (pcb[dwProcessId].dwPriorityClass < pcb[dwCurrentProcessId].dwPriorityClass)
		{
			hCurrentProcess = hProcess;
			OldState = pcb[dwCurrentProcessId].State;
			pcb[dwCurrentProcessId].State = STATE_HIGHREADY;
			fprintf(fOutput, "Process %d: %s -> %s\n",
				dwCurrentProcessId,
				szStates[OldState],
				szStates[pcb[dwCurrentProcessId].State]);
			
			OldState = pcb[dwProcessId].State;
			pcb[dwProcessId].State = STATE_EXECUTION;
			fprintf(fOutput, "Process %d: %s -> %s\n",
				dwProcessId,
				szStates[OldState],
				szStates[pcb[dwProcessId].State]);
		}
	}

	fprintf(fOutput, "\nCurrent process id: %d\n", MyGetProcessId(hCurrentProcess));
	iRegister = Protection[MyGetProcessId(hCurrentProcess)];
	
	return hCurrentProcess;
}

HANDLE STDCALL FindNextProcess()
{
	DWORD  dwPriorityClass;
	HANDLE hProcess;
	
	hProcess = INVALID_HANDLE_VALUE;
	dwPriorityClass = MAX_PRIORITY;
	for (DWORD i = 0; i != countof(pcb); ++i)
	{
		if (pcb[i].State == STATE_HIGHREADY && pcb[i].dwPriorityClass < dwPriorityClass)
		{
			dwPriorityClass = pcb[i].dwPriorityClass;
			hProcess = (HANDLE)i;
		}
	}
	
	if (hProcess != INVALID_HANDLE_VALUE)
	{
		return hProcess;
	}
	
	for (DWORD i = 0; i != countof(pcb); ++i)
	{
		if (pcb[i].State == STATE_LOWREADY && pcb[i].dwPriorityClass < dwPriorityClass)
		{
			dwPriorityClass = pcb[i].dwPriorityClass;
			hProcess = (HANDLE)i;
		}
	}
	
	return hProcess;
}

VOID STDCALL Exit_Process(UINT uExitCode)
{
	DWORD dwProcessId = MyGetProcessId(hCurrentProcess);
	
	pcb[dwProcessId].State = STATE_COMPLETION;
	hCurrentProcess = INVALID_HANDLE_VALUE;
	fprintf(fOutput, "进程%d已经完成\n", dwProcessId);
}



VOID STDCALL BlockProcess(DWORD dwSemaphoreIndex)
{
	DWORD dwProcessId, dwCurProcessId = MyGetProcessId(hCurrentProcess);
	
	fprintf(fOutput, "进程%d申请资源%i时被阻塞\n", dwCurProcessId, dwSemaphoreIndex);
	pcb[dwCurProcessId].State = STATE_WAITING;
	pcb[dwCurProcessId].dwNextProcessId = INVALID_PROCESS_ID;
	
	dwProcessId = sem[dwSemaphoreIndex].dwFirstProcessId;
	if (dwProcessId == INVALID_PROCESS_ID)
	{
		sem[dwSemaphoreIndex].dwFirstProcessId = dwCurProcessId;
	}
	else
	{
		while (pcb[dwProcessId].dwNextProcessId != INVALID_PROCESS_ID)
			dwProcessId = pcb[dwProcessId].dwNextProcessId;
		pcb[dwProcessId].dwNextProcessId = dwCurProcessId;
	}
}

VOID STDCALL WakeupProcess(DWORD dwSemaphoreIndex)
{
	DWORD dwProcessId;
	
	dwProcessId = sem[dwSemaphoreIndex].dwFirstProcessId;
	if (dwProcessId != INVALID_PROCESS_ID)
	{
		sem[dwSemaphoreIndex].dwFirstProcessId = pcb[dwProcessId].dwNextProcessId;
		pcb[dwProcessId].State = STATE_HIGHREADY;
		fprintf(fOutput, "进程%d被唤醒, 得到资源%d\n", dwProcessId, dwSemaphoreIndex);
	}
}

BOOL STDCALL Proberen(DWORD dwSemaphoreIndex)
{
	DWORD dwProcessId;
	if (--sem[dwSemaphoreIndex].lCount >= 0)
		return TRUE;
	
	BlockProcess(dwSemaphoreIndex);
	dwProcessId = MyGetProcessId(hCurrentProcess);
	Protection[dwProcessId] = iRegister;
	hCurrentProcess = INVALID_HANDLE_VALUE;
	
	return FALSE;
}

BOOL STDCALL Verhogen(DWORD dwSemaphoreIndex)
{
	DWORD dwProcessId;
	
	if (++sem[dwSemaphoreIndex].lCount > 0)
		return TRUE;
	
	WakeupProcess(dwSemaphoreIndex);
	dwProcessId = MyGetProcessId(hCurrentProcess);
	Protection[dwProcessId] = iRegister;
	return FALSE;
}

#define GetRandom(min, max) \
	max <  min ? 0 : \
max == min ? min : (rand() % (max + 1 - min) + min)

BOOL STDCALL GetTimeSlice()
{
	DWORD dwTimeSlice, dwProcessId;
	
	dwTimeSlice = GetRandom(0, 2);
	if (dwTimeSlice == (DWORD)hCurrentProcess)
		return TRUE;
	
	dwProcessId = MyGetProcessId(hCurrentProcess);
	pcb[dwProcessId].State = STATE_LOWREADY;
	Protection[dwProcessId] = iRegister;
	fprintf(fOutput, "时间片中断, 进程%d转入就绪态\n", dwProcessId);
	hCurrentProcess = INVALID_HANDLE_VALUE;
	
	return FALSE;
}
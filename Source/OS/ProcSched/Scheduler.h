#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include <Windows.h>
#include <setjmp.h>
#include "my_common.h"

#define MAX_PROCESS_NUM    3
#define SEMAPHORE_NUM      2
#define INVALID_PROCESS_ID -1
#ifndef MAX_PRIORITY
    #define MAX_PRIORITY 99
#endif /* MAX_PRIORITY */

enum PROCESS_STATE
{
	STATE_EXECUTION, 
	STATE_WAITING, 
	STATE_LOWREADY,
	STATE_HIGHREADY, 
	STATE_COMPLETION, 
};

typedef struct  
{
	LONG  lCount;
	DWORD dwFirstProcessId;
} TSemaphore, *LPTSemaphore;

typedef struct  
{
	DWORD         dwProcessId;
	PROCESS_STATE State;
	DWORD         dwPriorityClass;
	DWORD         dwNextProcessId;
	jmp_buf       JumpBuffer;
	BOOL          bFirst;
} PROCESS_CONTROL_BLOCK, PCB, *LPPCB;

HANDLE STDCALL Scheduler();
VOID   STDCALL Initialization(int argc, char **argv);
HANDLE STDCALL FindNextProcess();
BOOL   STDCALL GetTimeSlice();
BOOL   STDCALL Proberen(DWORD dwProcessId);
BOOL   STDCALL Verhogen(DWORD dwProcessId);
VOID   STDCALL BlockProcess(DWORD dwSemaphoreIndex);
VOID   STDCALL WakeupProcess(DWORD dwSemaphoreIndex);
VOID   STDCALL Exit_Process(UINT uExitCode);

static FORCEINLINE DWORD STDCALL MyGetProcessId(HANDLE hProcess)
{
	return (DWORD)hProcess;
}

#endif /* _SCHEDULER_H_ */
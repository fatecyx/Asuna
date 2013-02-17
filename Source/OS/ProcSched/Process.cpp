#include "Process.h"
#include "Scheduler.h"

extern INT32 iRegister;
extern LONG  lVal1, lVal2;
extern PCB   pcb[MAX_PROCESS_NUM];
extern FILE *fOutput;

VOID Process1(HANDLE hProcess)
{
	DWORD dwProcessId = MyGetProcessId(hProcess);

	if (pcb[dwProcessId].bFirst == TRUE)
		pcb[dwProcessId].bFirst = FALSE;
	else
		longjmp(pcb[dwProcessId].JumpBuffer, 1);

	for (iRegister = 0; iRegister != PROCESS1_LOOP_COUNT; ++iRegister)
	{
		fprintf(fOutput, "进程%d申请信号量1（与lValue1相联系）\n", dwProcessId);
		if (Proberen(0) == FALSE)		// 申请资源失败, 已被放入等待队列
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "进程%d得到s1, 正在临界区1\n", dwProcessId);
		if (GetTimeSlice() == FALSE)	// 时间片用尽
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "Added by Process %d: lValue1 = %d\n", dwProcessId, ++lVal1);
		fprintf(fOutput, "进程%d释放信号量1（与s1相联系）并退出临界区\n", dwProcessId);
		if (Verhogen(0) == FALSE)		// 有进程在等待该资源则中断,否则继续执行
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "进程%d申请信号量2（与s2相联系）\n", dwProcessId);
		if (Proberen(1) == FALSE)
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "进程%d得到s2, 正在临界区2\n", dwProcessId);
		if (GetTimeSlice() == FALSE)
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "Added by Process %d: lValue2 = %d\n", dwProcessId, ++lVal2);
		fprintf(fOutput, "进程%d释放信号量2（与s2相联系）并退出临界区\n", dwProcessId);
		if (Verhogen(1) == FALSE)
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "进程%d循环计算次数 = %d\n", dwProcessId, iRegister);
	}

	if (iRegister == PROCESS1_LOOP_COUNT)
		Exit_Process(0);
}

void Process2(HANDLE hProcess)
{
	DWORD dwProcessId = MyGetProcessId(hProcess);

	if (pcb[dwProcessId].bFirst == TRUE)
		pcb[dwProcessId].bFirst = FALSE;
	else
		longjmp(pcb[dwProcessId].JumpBuffer, 1);

	for (iRegister = 0; iRegister != PROCESS2_LOOP_COUNT; ++iRegister)
	{
		fprintf(fOutput, "进程%d申请信号量1（与lValue1相联系）\n", dwProcessId);
		if (Proberen(0) == FALSE)		// 申请资源失败, 已被放入等待队列
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "进程%d得到s1, 正在临界区1\n", dwProcessId);
		if (GetTimeSlice() == FALSE)	// 时间片用尽
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "Added by Process %d: lValue1 = %d\n", dwProcessId, ++lVal1);
		fprintf(fOutput, "进程%d释放信号量1（与s1相联系）并退出临界区\n", dwProcessId);
		if (Verhogen(0) == FALSE)		// 有进程在等待该资源则中断,否则继续执行
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "进程%d循环计算次数 = %d\n", dwProcessId, iRegister);
	}

	if (iRegister == PROCESS2_LOOP_COUNT)
		Exit_Process(0);
}

void Process3(HANDLE hProcess)
{
	DWORD dwProcessId = MyGetProcessId(hProcess);

	if (pcb[dwProcessId].bFirst == TRUE)
		pcb[dwProcessId].bFirst = FALSE;
	else
		longjmp(pcb[dwProcessId].JumpBuffer, 1);

	for (iRegister = 0; iRegister != PROCESS3_LOOP_COUNT; ++iRegister)
	{
		fprintf(fOutput, "进程%d申请信号量2（与lValue2相联系）\n", dwProcessId);
		if (Proberen(1) == FALSE)		// 申请资源失败, 已被放入等待队列
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "进程%d得到s2, 正在临界区2\n", dwProcessId);
		if (GetTimeSlice() == FALSE)	// 时间片用尽
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "Added by Process %d: lValue2 = %d\n", dwProcessId, ++lVal2);
		fprintf(fOutput, "进程%d释放信号量2（与s2相联系）并退出临界区\n", dwProcessId);
		if (Verhogen(1) == FALSE)		// 有进程在等待该资源则中断,否则继续执行
		{
			if (!setjmp(pcb[dwProcessId].JumpBuffer))
				break;
		}

		fprintf(fOutput, "进程%d循环计算次数 = %d\n", dwProcessId, iRegister);
	}

	if (iRegister == PROCESS3_LOOP_COUNT)
		Exit_Process(0);
}
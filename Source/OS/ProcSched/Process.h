#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <Windows.h>
#include <stdio.h>
#include "my_common.h"

#define PROCESS1_LOOP_COUNT 10
#define PROCESS2_LOOP_COUNT 13
#define PROCESS3_LOOP_COUNT 7

VOID Process1(HANDLE hProcess);
VOID Process2(HANDLE hProcess);
VOID Process3(HANDLE hProcess);

#endif /* _PROCESS_H_ */
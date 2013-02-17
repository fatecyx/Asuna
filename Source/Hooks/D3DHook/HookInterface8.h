#ifndef _HOOKINTERFACE8_H_7a1f20c7_d27a_46d6_b73c_a7b393102243_
#define _HOOKINTERFACE8_H_7a1f20c7_d27a_46d6_b73c_a7b393102243_

#include "MyLibraryUser.h"

NTSTATUS HookDirect3D8(PVOID *ModuleBase, PDHOOK_HOOK_INFO Context);
NTSTATUS UnHookDirect3D8(PVOID ModuleBase);

NTSTATUS HookDirectInput8(PVOID *ModuleBase, PDHOOK_HOOK_INFO Context);
NTSTATUS UnHookDirectInput8(PVOID ModuleBase);

#endif // _HOOKINTERFACE8_H_7a1f20c7_d27a_46d6_b73c_a7b393102243_

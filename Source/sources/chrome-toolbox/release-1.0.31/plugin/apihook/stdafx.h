#ifndef APIHOOK_STDAFX_H_
#define APIHOOK_STDAFX_H_

#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

inline void* __cdecl operator new[](size_t size)
{
    return size ? malloc(size) : NULL;
}

inline void* __cdecl operator new(size_t size)
{
    return (void *)(new char[size]);
}

inline void __cdecl operator delete(void *p)
{
    if (p != NULL)
        free(p);
}

inline void __cdecl operator delete[](void *p)
{
    delete(p);
}

#endif
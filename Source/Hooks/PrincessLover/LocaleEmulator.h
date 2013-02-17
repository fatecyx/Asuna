#ifndef _LOCALEEMULATOR_H_
#define _LOCALEEMULATOR_H_

#include "pragma_once.h"
#include <Windows.h>
#include <commctrl.h>
#include "MyLibraryUser.h"
//#include "gal_common.h"

#if defined(MY_COMPILER_INTEL)
    #pragma warning(disable:1899)
#else
    #pragma warning(disable:627)
#endif

#pragma pack(1)

#define LOCALE_EMULATOR_THREAD_INFO_MAGIC   TAG4('LETM')
#define LOCALE_EMULATOR_BEGIN               -1
#define LOCALE_EMULATOR_END                 -2

typedef BOOL (STDCALL *BeginLocalEmulatorRoutine)(PVOID BaseAddress, ULONG Reason, ULONG CodePage);
typedef BOOL (STDCALL *EndLocalEmulatorRoutine)(PVOID BaseAddress, ULONG Reason, PVOID Context);

struct LOCALE_EMULATOR_THREAD_INFO : public TEB_ACTIVE_FRAME
{
//    BOOL    bRecursion;
    HHOOK   hHook;
    DLGPROC OldDlgProcA;
};

typedef struct
{
    WNDPROC OldWndProcA;
//    HFONT   hFont;
} WINDOW_PROP_INFO;

typedef struct
{
    ULONG   CodePage;
    ULONG   FontCharSet;
    LANGID  DefaultSystemLangID;
    LANGID  DefaultUserLangID;
    LCID    DefaultSystemLCID;
    LCID    DefaultUserLCID;
} LOCALE_INFO;

#pragma pack()

BOOL BeginLocalEmulator(ULONG CodePage);
BOOL EndLocalEmulator();
BOOL ReleaseThreadLocalStorage();

#define LOCALE_EMULATOR_PROP_NAME L"AMANO_LOCALE_EMULATOR_PROP_NAME"

#define WCharToMByteStack(lpUnicode, Length, lpAnsiBuffer, pLength) \
    if ((ULONG_PTR)(lpUnicode) & 0xFFFF0000) \
    { \
        DWORD __Length; \
        LPWSTR _pUnicode = (LPWSTR)(lpUnicode); \
        __Length = StrLengthW(_pUnicode) + 1; \
        __Length *= sizeof(WCHAR); \
        *(LPSTR *)&(lpAnsiBuffer) = (LPSTR)AllocStack(__Length); \
        __Length = WCharToMByte(_pUnicode, __Length / sizeof(WCHAR) - 1, (LPSTR)(lpAnsiBuffer), __Length); \
        if (pLength) \
            *(PDWORD)pLength = __Length; \
    } \
    else \
    { \
        *(ULONG_PTR *)&(lpAnsiBuffer) = (ULONG_PTR)(lpUnicode); \
    }

#define MByteToWCharStack(lpAnsi, Length, lpUnicodeBuffer, pLength) \
    if ((ULONG_PTR)(lpAnsi) & 0xFFFF0000) \
    { \
        DWORD __Length; \
        LPSTR _pAnsi = (LPSTR)(lpAnsi); \
        __Length = StrLengthA(_pAnsi) + 1; \
        *(LPWSTR *)&(lpUnicodeBuffer) = (LPWSTR)AllocStack(__Length * sizeof(WCHAR)); \
        MByteToWChar(_pAnsi, __Length - 1, (LPWSTR)(lpUnicodeBuffer), __Length); \
        if (pLength) \
            *(PDWORD)pLength = __Length; \
    } \
    else \
    { \
        *(ULONG_PTR *)&(lpUnicodeBuffer) = (ULONG_PTR)(lpAnsi); \
    }


#define WriteLog()
#ifndef WriteLog
#define WriteLog() \
        { \
        FILE *fp; \
        WCHAR path[MAX_PATH]; \
        GetExecuteDirectoryW(path, countof(path)); \
        lstrcatW(path, L"log.txt"); \
        fp = _wfopen(path, L"ab"); \
        if (fp) \
            { \
            SYSTEMTIME st; \
            GetClassNameW(hWnd, path, countof(path)); \
            GetLocalTime(&st); \
            fprintf(fp, \
            "%02d:%02d:%02d %-31s: MSG=%04X, WPARAM=%08X, LPARAM=%08X, HWND=%08X, %S\r\n", \
            st.wHour, st.wMinute, st.wSecond, \
            __FUNCTION__, Message, wParam, lParam, hWnd, path); \
            fclose(fp); \
            } \
        }

#endif

#endif // _LOCALEEMULATOR_H_

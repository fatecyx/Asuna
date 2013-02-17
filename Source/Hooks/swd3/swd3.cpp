#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "swd3.h"
#include <commctrl.h>
#include "Mem.cpp"

enum EStartDlgRetID { ID_ERROR = -1, ID_EXIT, ID_LOAD, ID_START };

BOOL    g_bWindowMode = FALSE;

RECT    g_rcGameWindow, g_rcGameClient;
DWORD   g_Count;
WNDPROC g_OldGameWndProc;
WCHAR   path[MAX_PATH];

OVERLOAD_CPP_NEW_WITH_HEAP(CMem::GetGlobalHeap())

HRESULT WINAPI MyDirectDrawCreate(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter)
{
    MyDirectDraw *pMyDD;

    pMyDD = new MyDirectDraw;
    if (pMyDD == NULL)
        return DirectDrawCreate(lpGUID, lplpDD, pUnkOuter);

    DDRAW_HOOK_OPTION Option;

    Option.bWindowMode = g_bWindowMode;
    Option.prcWindow = &g_rcGameClient;
    pMyDD->SetOption(&Option);

    return pMyDD->CreateDirectDraw(lpGUID, lplpDD, pUnkOuter);
}

ASM DWORD STDCALL SurfaceTo16(DWORD, DWORD)
{
    __asm
    {
        push    ebp;
        mov     ebp, esp;
        push    ecx;
        push    ebx;
        mov     eax, dword ptr [ebp+8];
        mov     ebx, dword ptr [ebp+0Ch];
        shr     eax, 3;
        shr     ebx, 3;
        shl     al, 3;
        shl     bl, 3;
        shl     ax, 3;
        shl     bx, 3;
        shr     eax, 6;
        shr     ebx, 6;
        shl     ebx, 010h;
        and     eax, 0FFFFh;
        and     ebx, 0FFFF0000h;
        or      eax, ebx;
        mov     dword ptr [ebp-4], eax;
        mov     eax, dword ptr [ebp-4];
        pop     ebx;
        mov     esp, ebp;
        pop     ebp;
        ret     8;
    }
}

VOID Surface32To16(LPDWORD lpSurface, int w, int h)
{
    LONG iPixel = (w * h) / 2;

    if (iPixel <= 0)
        return;

    LPDWORD lpSrcSurface = lpSurface;
    while (iPixel--)
    {
        *lpSrcSurface = SurfaceTo16(*lpSurface, *(lpSurface + 1));
        ++lpSrcSurface;
        lpSurface += 2;
    }
}

ASM
BOOL
FASTCALL
OldDrawImage(
    PVOID pThis,
    PVOID Dummy,
    PVOID lpSurface,
    PVOID pImageInfo
)
{
    UNREFERENCED_PARAMETER(pThis);
    UNREFERENCED_PARAMETER(Dummy);
    UNREFERENCED_PARAMETER(lpSurface);
    UNREFERENCED_PARAMETER(pImageInfo);
    ASM_DUMMY_AUTO();
}

BOOL
FASTCALL
DrawImage(
    PVOID pThis,
    PVOID Dummy,
    PVOID lpSurface,
    PVOID pImageInfo
)
{
    LPSIZE pSize = (LPSIZE)((ULONG_PTR)pThis + 0xB50);
    pSize->cx = 640;
    pSize->cy = 480;
    return OldDrawImage(pThis, Dummy, lpSurface, pImageInfo);
}

ASM
VOID
FASTCALL
OldDrawString(
    PVOID   pThis,
    PVOID,
    PVOID   lpSurface,
    INT     X,
    INT     Y,
    LPSTR   lpText,
    PVOID   Unknown,
    ULONG   Flags
)
{
    UNREFERENCED_PARAMETER(pThis);
    UNREFERENCED_PARAMETER(lpSurface);
    UNREFERENCED_PARAMETER(X);
    UNREFERENCED_PARAMETER(Y);
    UNREFERENCED_PARAMETER(lpText);
    UNREFERENCED_PARAMETER(Unknown);
    UNREFERENCED_PARAMETER(Flags);
    ASM_DUMMY_AUTO();
}

VOID
FASTCALL
DrawString(
    PVOID   pThis,
    PVOID   Dummy,
    PVOID   lpSurface,
    INT     X,
    INT     Y,
    LPSTR   lpText,
    PVOID   Unknown,
    ULONG   Flags
)
{
    LPSIZE pSize = (LPSIZE)((ULONG_PTR)pThis + 0xFF0);

    pSize->cx = 640;
    pSize->cy = 480;

    return OldDrawString(pThis, Dummy, lpSurface, X, Y, lpText, Unknown, Flags);
}

PVOID CDECL GetSurfacePtr(LPDIRECTDRAWSURFACE7 pDDS)
{
    PVOID lpSurface;
    PVOID (CDECL *pfGetSurfacePtr)(LPDIRECTDRAWSURFACE7 pDDS);

    *(PVOID *)&pfGetSurfacePtr = (PVOID)0x416F10;
    lpSurface = pfGetSurfacePtr(pDDS);
    if (lpSurface == NULL || !g_bWindowMode)
        return lpSurface;

    Surface32To16((LPDWORD)lpSurface, 64, 64);

    return lpSurface;
}

INT WINAPI MyGetSystemMetrics(INT Index)
{
    switch (Index)
    {
        case SM_CYSCREEN:
            return g_rcGameClient.bottom - g_rcGameClient.top;

        case SM_CXSCREEN:
            return g_rcGameClient.right - g_rcGameClient.left;
    }

    return GetSystemMetrics(Index);
}

VOID CenterWindow(HWND hWnd)
{
    int  x, y;
    RECT rcWindow, rcSys;

    SystemParametersInfoW(SPI_GETWORKAREA, 0, &rcSys, 0);
    GetWindowRect(hWnd, &rcWindow);
    x = ((rcSys.right - rcSys.left) - (rcWindow.right - rcWindow.left)) >> 1;
    y = ((rcSys.bottom - rcSys.top) - (rcWindow.bottom - rcWindow.top)) >> 1;
    SetWindowPos(hWnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
}

BOOL WINAPI MySetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
    if (hWndInsertAfter == HWND_NOTOPMOST &&
        X == 0 &&
        Y == 0 &&
        cx == 640 &&
        cy == 480 &&
        uFlags == SWP_NOACTIVATE)
    {
        X = g_rcGameWindow.left;
        Y = g_rcGameWindow.top;
        cx = g_rcGameWindow.right - g_rcGameWindow.left;
        cy = g_rcGameWindow.bottom - g_rcGameWindow.top;
    }

    return SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags|SWP_SHOWWINDOW);
}

BOOL WINAPI MyGetWindowRect(HWND hWnd, LPRECT lpRect)
{
    UNREFERENCED_PARAMETER(hWnd);

    lpRect->left    = 0;
    lpRect->top     = 0;
    lpRect->right   = g_rcGameClient.right - g_rcGameClient.left;
    lpRect->bottom  = g_rcGameClient.bottom - g_rcGameClient.top;

    return TRUE;
}

BOOL WINAPI MyShowWindow(HWND hWnd, int nCmdShow)
{
    switch (nCmdShow)
    {
        case SW_MINIMIZE:
        case SW_RESTORE:
            return TRUE;
    }

    return ShowWindow(hWnd, nCmdShow);
}

LRESULT WINAPI GameWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
        case WM_MOVE:
            GetWindowRect(hWnd, &g_rcGameWindow);
            GetClientRect(hWnd, &g_rcGameClient);
            ClientToScreen(hWnd, (LPPOINT)&g_rcGameClient);
            ClientToScreen(hWnd, (LPPOINT)&g_rcGameClient + 1);
            ClipCursor(&g_rcGameWindow);
            break;

        case WM_ACTIVATE:
            ClipCursor(wParam != WA_INACTIVE ? &g_rcGameWindow : NULL);
            break;

        case WM_ACTIVATEAPP:
            ClipCursor((BOOL)wParam ? &g_rcGameWindow : NULL);
            break;

        case WM_SETFOCUS:
        case WM_KILLFOCUS:
            ClipCursor(Message == WM_SETFOCUS ? &g_rcGameWindow : NULL);
            break;
    }

    return CallWindowProcA(g_OldGameWndProc, hWnd, Message, wParam, lParam);
}

HWND WINAPI MyCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    HWND hWnd;
    RECT rcWindow;

    dwStyle |= WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX;
    hWnd = CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    if (hWnd == NULL)
        return hWnd;

    GetWindowRect(hWnd, &rcWindow);
    AdjustWindowRect(&rcWindow, dwStyle, FALSE);
    SetWindowPos(hWnd, NULL, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top, SWP_NOMOVE);

    CenterWindow(hWnd);
    GetWindowRect(hWnd, &g_rcGameWindow);
    GetClientRect(hWnd, &g_rcGameClient);
    ClientToScreen(hWnd, (LPPOINT)&g_rcGameClient);
    ClientToScreen(hWnd, (LPPOINT)&g_rcGameClient + 1);
    ClipCursor(&g_rcGameWindow);

    return hWnd;
}

BOOL WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    BOOL Result = PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);

    if (Result == FALSE)
    {
        DWORD TickCount;
        static DWORD LastTickCount;

        TickCount = GetTickCount();
        if (TickCount - LastTickCount < 10 && !--g_Count)
        {
            g_Count = 4;
            SleepEx(1, FALSE);
        }
        LastTickCount = TickCount;
    }

    return Result;
}

ForceInline DWORD ChangeCodePage(DWORD SrcCP, DWORD DestCP, PCHAR pszString, DWORD Length, PCHAR pszOutString, DWORD OutLength)
{
    DWORD nChar;
    WCHAR  szPath[MAX_PATH * 2];

    nChar = MultiByteToWideChar(SrcCP, 0, pszString, Length, szPath, countof(szPath));
    return WideCharToMultiByte(DestCP, 0, szPath, nChar, pszOutString, OutLength, 0, 0);
}

LRESULT WINAPI MySendMessageA(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Int32  MsgDiff;
    WCHAR  szText[0x500];
    PCHAR  pszText;

    union UItem
    {
        TCITEMA   tcItem;
        LVITEMA   lvItem;
        LVCOLUMNA lvcolItem;
        TCITEMW   tcItemW;
        LVITEMW   lvItemW;
        LVCOLUMNW lvcolItemW;
    } Item;

    switch (uMsg)
    {
        case TCM_INSERTITEMA:
            Item.tcItem = *(LPTCITEMA)lParam;
            if ((Item.tcItem.mask & TCIF_TEXT) == 0)
                break;

            pszText = Item.tcItem.pszText;
            Item.tcItemW.pszText = szText;
            MsgDiff = TCM_INSERTITEMW - TCM_INSERTITEMA;
            goto CONV_TO_UNICODE;

        case LVM_INSERTCOLUMNA:
            Item.lvcolItem = *(LPLVCOLUMNA)lParam;
            if ((Item.lvcolItem.mask & LVCF_TEXT) == 0)
                break;

            pszText = Item.lvcolItem.pszText;
            Item.lvcolItemW.pszText = szText;
            MsgDiff = LVM_INSERTCOLUMNW - LVM_INSERTCOLUMNA;
            goto CONV_TO_UNICODE;

        case LVM_INSERTITEMA:
        case LVM_SETITEMTEXTA:
            Item.lvItem = *(LPLVITEMA)lParam;

            pszText = Item.lvItem.pszText;
            Item.lvItemW.pszText = szText;
            MsgDiff = LVM_SETITEMTEXTW - LVM_SETITEMTEXTA;

CONV_TO_UNICODE:
            if (pszText == NULL || pszText == LPSTR_TEXTCALLBACKA)
                break;

            MultiByteToWideChar(CP_BIG5, 0, pszText, -1, szText, countof(szText));
            lParam = (LPARAM)&Item;
            uMsg += MsgDiff;
            break;

        case WM_USER + 4:
            ShowWindow(hWnd, SW_HIDE);
            SendMessageA(hWnd, uMsg, wParam, lParam);
            ShowWindow(hWnd, SW_SHOWDEFAULT);
            g_OldGameWndProc = (WNDPROC)SetWindowLongA(hWnd, GWLP_WNDPROC, (LONG_PTR)GameWndProc);
            return 0;

    }

    return SendMessageW(hWnd, uMsg, wParam, lParam);
}

DLGPROC g_OrigDlgProc;
WNDPROC g_OrigWndProc;

HRESULT CALLBACK MyWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_KEYDOWN:
        case WM_KEYUP:
            switch (wParam & 0xFFFF)
            {
            case VK_RETURN:
                {
                    POINT pt;
                    GetCursorPos(&pt);
                    ScreenToClient(hWnd, &pt);
                    SendMessageA(hWnd, uMsg == WM_KEYDOWN ? WM_LBUTTONDOWN : WM_LBUTTONUP, 0, pt.x|(pt.y << 16));
                }

                break;
            }

            break;
    }

    return g_OrigWndProc(hWnd, uMsg, wParam, lParam);
}

INT_PTR CALLBACK MyDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
            g_OrigDlgProc = (DLGPROC)lParam;
            lParam = 0;
//            g_OrigWndProc = (WNDPROC)SetWindowLong(GetParent(hWnd), GWL_WNDPROC, (Long)MyWndProc);
            SetWindowLongW(hWnd, GWL_EXSTYLE, GetWindowLongW(hWnd, GWL_EXSTYLE) & ~WS_EX_TOOLWINDOW);
            break;
    }

    return g_OrigDlgProc ? CallWindowProcA((WNDPROC)g_OrigDlgProc, hWnd, uMsg, wParam, lParam) : FALSE;
}

INT_PTR CALLBACK CheetDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HFONT    hFont;
    LOGFONTW lf;
    static HFONT s_hFont;
    static WCHAR szFont[] = L"Tahoma";

    switch (uMsg)
    {
        case WM_INITDIALOG:
            g_OrigDlgProc = (DLGPROC)lParam;
            hFont = (HFONT)SendMessageW(GetDlgItem(hWnd, 1017), WM_GETFONT, 0, 0);
            GetObjectW(hFont, sizeof(lf), &lf);
            CopyStruct(lf.lfFaceName, szFont, sizeof(szFont));
            hFont = CreateFontIndirectW(&lf);
            SendMessageW(hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessageW(GetDlgItem(hWnd, 1009), WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessageW(GetDlgItem(hWnd, 1017), WM_SETFONT, (WPARAM)hFont, TRUE);
            if (s_hFont)
                DeleteObject(s_hFont);
            s_hFont = hFont;
            break;

        case WM_COMMAND:
            switch (wParam & 0xFFFF)
            {
                case IDCANCEL:
                    wParam = 1000;
                    break;
            }
            break;
    }

    return g_OrigDlgProc ? CallWindowProcA((WNDPROC)g_OrigDlgProc, hWnd, uMsg, wParam, lParam) : FALSE;
}

EStartDlgRetID ParseCommandLine()
{
    typedef struct
    {
        PWChar opt;
        EStartDlgRetID id;
    } SStartupOption;

    WCHAR end, *lpCmdLine;
    SStartupOption opts[] =
    {
        { L"-start", ID_START },
        { L"-load",  ID_LOAD  },
        { L"-exit",  ID_EXIT  },
    };

    lpCmdLine = GetCommandLineW();
    end = *lpCmdLine++ == '\"' ? '\"' : ' ';
    while (*lpCmdLine && *lpCmdLine != end) ++lpCmdLine;
    if (*++lpCmdLine)
        while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;

    for (DWORD i = 0; i != countof(opts); ++i)
    {
        if (!StrICompareW(lpCmdLine, opts[i].opt))
            return opts[i].id;
    }

    return ID_ERROR;
}

INT_PTR WINAPI MyDialogBoxParamA(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
    Int32 DlgID = (Int32)lpTemplateName;
    if (DlgID == 0x6B)
    {
        EStartDlgRetID ret = ParseCommandLine();
        if (ret != ID_ERROR)
            return ret;

        dwInitParam = (LPARAM)lpDialogFunc;
        lpDialogFunc = MyDialogProc;
    }
    else if (DlgID == 0x6A)
    {
        dwInitParam = (LPARAM)lpDialogFunc;
        lpDialogFunc = CheetDialogProc;
    }

    return DialogBoxParamA(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

HFONT WINAPI MyCreateFontIndirectA(LOGFONTA *lplf)
{
    LOGFONTW lf;
    CopyStruct(&lf, lplf, GetStructMemberOffset(LOGFONTA, lfHeight, lfFaceName));
    MultiByteToWideChar(CP_BIG5, 0, lplf->lfFaceName, sizeof(lplf->lfFaceName), lf.lfFaceName, countof(lf.lfFaceName));
    return CreateFontIndirectW(&lf);
}

ULONG CDECL GetCDRomPath(PCHAR pszOutBuffer)
{
    return GetExecuteDirectoryA(pszOutBuffer, MAX_PATH);
}

LPSTR WINAPI GetVideoPath(LPSTR lpString1, LPCSTR lpString2)
{
    ULONG Length;
    static CHAR szVideoFolder[] = "Video\\\0";

    UNREFERENCED_PARAMETER(lpString2);
    Length = GetCDRomPath(lpString1);
    if (Length == 0)
        return lpString1;

    CopyStruct(lpString1 + Length, szVideoFolder, sizeof(szVideoFolder));

    return lpString1;
}

// 怒气 0x38 max
// 4ACF50 4FB7F0 52418C 5242FC

#define GET_API_RVA(_ApiEntry, _Module) \
            { (ULONG_PTR)My##_ApiEntry, 4, g_bWindowMode ? IATLookupRoutineRVAByEntry(_Module, _ApiEntry) :   IMAGE_INVALID_RVA }

Void Init()
{
    HANDLE hFile;
    HMODULE hModule;

    lstrcpyW(path + GetExecuteDirectoryW(path, countof(path)), L"log.txt");
    DeleteFileW(path);

    CMem::CreateGlobalHeap();

    hModule = GetModuleHandleW(NULL);

    MEMORY_PATCH p[] =
    {
        { STRTOULONG("軒轅劍參 DVD"),   4, 0x09FB0 },    // title
        { STRTOULONG("%s%s"),           4, 0x1198C },    // video path format
        { 0x4E21,                       4, 0x24FA8 },    // force window mode
        { 0x32EB,                       2, 0x24238 },    // path: swd3
        { 0xC08B,                       2, 0x2426D },
        { 0xC08B,                       2, 0x119B9 },    // mov eax, eax
        { 0x01,                         4, 0xBA428 },    // default-run
        { 0x0B,                         4, 0x25049 },    // volume
        { 0x8C,                         4, 0x2506D },    // space
        { 0x8B,                         1, 0x25071 },    // text speed
        { 0xB8,                         1, 0x09EEE },    // disable env.dat path
        { 0x703801C6,                   4, 0x5A200 },    // 无限怒气
        { 0x80,                         1, 0x03025 },    // set flag 52

        // default setting to write to env.dat
        { 0x006A0B6A,          4, 0x240B5 },    // text speed and battle speed
        { 0x8C,                1, 0x240BE },    // space
        { 0x0B6A0B6A,          4, 0x240BF },    // volume

        // iat
        { (ULONG_PTR)MyDialogBoxParamA,     4, IATLookupRoutineRVAByEntry(hModule, DialogBoxParamA) },
        { (ULONG_PTR)MySendMessageA,        4, IATLookupRoutineRVAByEntry(hModule, SendMessageA)    },
        { (ULONG_PTR)MyPeekMessageA,        4, IATLookupRoutineRVAByEntry(hModule, PeekMessageA)    },
        { (ULONG_PTR)MyCreateFontIndirectA, 4, IATLookupRoutineRVAByEntry(hModule, CreateFontIndirectA) },

//        GET_API_RVA(GetSystemMetrics,   hModule),
        GET_API_RVA(CreateWindowExA,    hModule),
        GET_API_RVA(SetWindowPos,       hModule),
        GET_API_RVA(ShowWindow,         hModule),
        GET_API_RVA(GetWindowRect,      hModule),
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        { JUMP, 0x242B0, GetCDRomPath    },
        { JUMP, 0x36AD0, DrawString,   2, OldDrawString },
        { JUMP, 0x34790, DrawImage,    3, OldDrawImage },
        { CALL, 0x847EE, GetVideoPath, 1 },
        { CALL, 0x36851, GetSurfacePtr   },
    };

    PatchMemory(p, countof(p), f, countof(f), hModule);

    g_Count = 4;

    SetExecuteDirectoryAsCurrentW();

    hFile = CreateFileW(L"Env.dat",
                GENERIC_WRITE,
                0,
                NULL,
                OPEN_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if (hFile != INVALID_HANDLE_VALUE)
        CloseHandle(hFile);
}

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    FILE *fp;

    fp = _wfopen(path, L"ab");
    if (fp)
    {
        SYSTEMTIME st;

        GetLocalTime(&st);
        fprintf(
            fp,
            "%02d:%02d:%02d: code = %08X, addr = %08X, rva = %08X\r\n",
            st.wHour, st.wMinute, st.wSecond,
            ExceptionInfo->ExceptionRecord->ExceptionCode,
            ExceptionInfo->ExceptionRecord->ExceptionAddress,
            (ULONG_PTR)ExceptionInfo->ExceptionRecord->ExceptionAddress - (ULONG_PTR)GetImageBaseAddress(ExceptionInfo->ExceptionRecord->ExceptionAddress));

        fclose(fp);
    }

    if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID)0x0042085A)
    {
        __asm nop;
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    switch (ulReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            AddVectoredExceptionHandler(True, VectoredHandler);
            Init();
            break;

        case DLL_PROCESS_DETACH:
            CMem::DestroyGlobalHeap();
            break;
    }

    return TRUE;
}

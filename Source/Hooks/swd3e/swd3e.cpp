#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "ddraw.lib")

#include "swd3e.h"
#include "MyLibrary.cpp"

RECT  rcGame;
DWORD dwTemp;

LPSTR FASTCALL FixGamePath(PVOID, LPSTR lpPath)
{
    UINT i;
    LPSTR lpDrive;
    PLDR_MODULE Module;

    __asm mov lpDrive, eax;

    Module = Nt_FindLdrModuleByHandle(NULL);
    Nt_UnicodeToAnsi(lpPath, MAX_PATH, Module->FullDllName.Buffer, (Module->FullDllName.Length - Module->BaseDllName.Length) / sizeof(WCHAR));

    return lpDrive;
}

static BYTE byInsLength[] =
{
    0x4F, 0x02, 0x02, 0x00, 0x00,
    0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x00, 0x02, 0x06,
    0x02, 0x02, 0x01, 0x01,
};

VOID STDCALL _SetMonsterFlag(PBYTE pbMonster)
{
    DWORD dwInst, ITEM_FLAG;
    enum { IF_BOSS = 0x01, IF_BEING = 0x02 };

    ITEM_FLAG = 0;
    pbMonster += 0x4F;
    while (ITEM_FLAG ^ (IF_BOSS | IF_BEING))
    {
        dwInst = *(LPWORD)pbMonster - 1;
        pbMonster += 2;
        if (dwInst == 0x63)
        {
            pbMonster += 2;
        }
        else if (dwInst <= 0x1D)
        {
            switch (dwInst)
            {
            case 0x19 - 1:
                *(pbMonster + 3) = 0x8;
                ITEM_FLAG |= IF_BOSS;
                break;
            case 0x1A - 1:
                *(LPWORD)pbMonster = 0xF001;
                ITEM_FLAG |= IF_BEING;
                break;
            }
            pbMonster += byInsLength[dwInst];
        }
    }
}

ASM VOID STDCALL SetMonsterFlag()
{
    __asm
    {
        push ebp;
        call _SetMonsterFlag;
        mov ecx, 13h;
        ret;
    }
}

void WINAPI CenterWindow(HWND hWnd)
{
    int  x, y;
    RECT rcGame, rcSys;

    SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcSys, 0);
    GetWindowRect(hWnd, &rcGame);
    x = ((rcSys.right - rcSys.left) - (rcGame.right - rcGame.left)) >> 1;
    y = ((rcSys.bottom - rcSys.top) - (rcGame.bottom - rcGame.top)) >> 1;
    SetWindowPos(hWnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
    GetWindowRect(hWnd, &rcGame);
    ClipCursor(&rcGame);
}

BOOL WINAPI MySetWindowPos(IN HWND hWnd, IN OPTIONAL HWND hWndInsertAfter, IN int X, IN int Y, IN int cx, IN int cy, IN UINT uFlags)
{
    CenterWindow(hWnd);
    return TRUE;
}

INT_PTR WINAPI MyDialogBoxParamA(IN OPTIONAL HINSTANCE hInstance, IN LPCSTR lpTemplateName, IN OPTIONAL HWND hWndParent, IN OPTIONAL DLGPROC lpDialogFunc, IN LPARAM dwInitParam)
{
    INT_PTR iRet;
    iRet = DialogBoxParamA(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
    if (MAKEINTRESOURCEA(0x6B) == lpTemplateName)
    {
        HWND hWnd = *(HWND *)0x4E5824;
        CenterWindow(hWnd);
        GetWindowRect(hWnd, &rcGame);
    }
    return iRet;
}

HWND WINAPI MyCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    HWND hWnd;
    hWnd = CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    GetWindowRect(hWnd, &rcGame);
    return hWnd;
}

ASM VOID STDCALL ColorConvert32(DWORD dwPixel, LPDWORD lpPixel1, LPDWORD lpPixel2)
{
    __asm
    {
        push    ebp
            mov     ebp, esp
            sub     esp, 8
            push    ebx
            mov     eax, dword ptr [ebp+8]
            mov     ebx, dword ptr [ebp+8]
            and     eax, 0FFFFh
            and     ebx, 0FFFF0000h
            shr     ebx, 010h
            shl     eax, 6
            shl     ebx, 6
            shr     ax, 3
            shr     bx, 3
            shr     al, 3
            shr     bl, 3
            shl     eax, 3
            shl     ebx, 3
            mov     dword ptr [ebp-4], eax
            mov     dword ptr [ebp-8], ebx
            mov     eax, dword ptr [ebp+0Ch]
            mov     ecx, dword ptr [ebp-4]
            mov     edx, dword ptr [ebp+010h]
            pop     ebx
            mov     dword ptr [eax], ecx
            mov     eax, dword ptr [ebp-8]
            mov     dword ptr [edx], eax
            mov     al, 1
            mov     esp, ebp
            pop     ebp
            ret     0Ch
    }
}

BOOL STDCALL ConvertSurface(LPDIRECTDRAWSURFACE lpDDSurface)
{
    HRESULT hResult;
    DDSURFACEDESC ddsd;

    if (*(LPDWORD)lpDDSurface == NULL)
    {
        return DD_FALSE;
    }

    ddsd.dwSize = sizeof(ddsd);
    hResult = lpDDSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
    if (hResult != DD_OK)
    {
        return DD_FALSE;
    }

    LONG   lLine = 0, lPixelNumPerLine = ddsd.lPitch >> 2;			// 每行像素数
    PBYTE  pbSurface;
    LPVOID lpSurface;
    HANDLE hHeap;

    pbSurface = (PBYTE)AllocateMemoryP(ddsd.lPitch);

    lpSurface = ddsd.lpSurface;
    while (lLine < (LONG)ddsd.dwHeight)
    {
        LONG lCount;

        memcpy(pbSurface, lpSurface, ddsd.lPitch);
        lCount = lPixelNumPerLine / 2;
        if (lCount > 0)
        {
            LPDWORD lpBakSurface, lpSF;

            lpBakSurface = (LPDWORD)pbSurface;
            lpSF = (LPDWORD)lpSurface;
            while (lCount--)
            {
                ColorConvert32(*lpBakSurface, lpSF, lpSF + 1);
                lpSF += 2;
                ++lpBakSurface;
            }
        }

        lpSurface = (PBYTE)lpSurface + ddsd.dwWidth * 4;
        ++lLine;
    }

    FreeMemoryP(pbSurface);
    lpDDSurface->Unlock(NULL);

    return DD_OK;
}

ASM VOID _ConvertSurface(LPDIRECTDRAWSURFACE lpDDSurface)
{
    __asm
    {
        pushad;
        push  dword ptr [esp+24h];
        call  ConvertSurface;
        popad;
        ret   4;
    }
}

ASM VOID _ConvertSurface1()
{
    __asm
    {
        push   ecx;
        call   _ConvertSurface;
        push   0;
        push   1000000h;
        push   0;
        push   ecx;
        push   offset rcGame;
        push   eax;
        call   dword ptr [edx+ 14h];
        ret;
    }
}

ASM VOID _ConvertSurface2()
{
    __asm
    {
        push    ecx;
        call   _ConvertSurface;
        pop    dwTemp;
        push   offset rcGame;
        push   eax;
        call   dword ptr [edx+14h];
        jmp    dwTemp;
    }
}

ASM VOID _ConvertSurface3()
{
    __asm
    {
        push    ecx;
        call   _ConvertSurface;
        xchg    ebx, dword ptr [esp];
        push    offset rcGame;
        push    eax;
        call    dword ptr [edx+14h];
        mov     dword ptr [esp], ebx;
        ret;
    }
}

ASM VOID _ConvertSurface4()
{
    __asm
    {
        push    edx;
        call   _ConvertSurface;
        pop    dwTemp;
        push   offset rcGame;
        push   eax;
        call   dword ptr [ecx+14h];
        jmp    dwTemp;
    }
}

LPVOID lpGetSurfacePtr = (LPVOID)0x417740;

ASM VOID FixTextOut()
{
    __asm
    {
        push   dword ptr [esp+4h];
        call   lpGetSurfacePtr;
        pop    ecx;
        pushad;
        push   40h;
        push   40h;
        push   eax;
        call   BufferTo16;
        popad;
        ret;
    }
}

ASM DWORD SurfaceTo16(DWORD a, DWORD b)
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

VOID STDCALL BufferTo16(LPDWORD lpSurface, int w, int h)
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

VOID CDECL SaveScreenShot(LPDWORD lpSurface, DWORD dwWidth, DWORD dwHeight, LPCSTR lpFileName)
{
    HANDLE hFile;

    hFile = CreateFileA(lpFileName,
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return;

    PBYTE pbBuffer, pbBits;
    DWORD dwBitmapSize, dwWritten;

    dwBitmapSize = dwWidth * dwHeight * 3 + 0x36;
    pbBuffer = (PBYTE)AllocateMemoryP(dwBitmapSize + 1, HEAP_ZERO_MEMORY);
    *(LPDWORD)pbBuffer = 'MB';
    *(LPDWORD)(pbBuffer + 2) = dwBitmapSize;
    pbBuffer[0xA] = 0x36;
    pbBuffer[0xE] = 0x28;
    *(LPDWORD)(pbBuffer + 0x12) = dwWidth;
    *(LPDWORD)(pbBuffer + 0x16) = dwHeight;
    *(LPDWORD)(pbBuffer + 0x1A) = 0x180001;
    *(LPDWORD)(pbBuffer + 0x23) = dwWidth * dwHeight * 3;

    pbBits = pbBuffer + 0x36;
    lpSurface += (dwHeight - 1) * dwWidth;
    while (dwHeight--)
    {
        for (DWORD i = 0; i != dwWidth; ++i)
        {
            *(LPDWORD)pbBits = *lpSurface;
            ++lpSurface;
            pbBits += 3;
        }
        lpSurface -= dwWidth * 2;
    }

    WriteFile(hFile, pbBuffer, dwBitmapSize, &dwWritten, NULL);
    CloseHandle(hFile);
    FreeMemoryP(pbBuffer);
}



inline BOOL UnInitialize(PVOID BaseAddress)
{
    return FALSE;
}

BOOL Initialize(PVOID BaseAddress)
{
    ml::MlInitialize();

    Nt_SetExeDirectoryAsCurrent();

    MEMORY_PATCH patch[] =
    {
#if PATCH_WINDOW_MODE == 1
        {0x0,		1,	0x3C061},	// 强制窗口
        {0x2C,		1,	0x3C07B},	// 强制窗口
        {0x00,		1,	0x27273},	// 默认为555色进行处理
        {0x4B000,	4,	0x08B7C},	// 页面大小

        {0x14EB,	2,	0x39D63},	// 16位页面右移一位
        {0x02F8C1,	3,	0x39D79},	// 变成一行的点数
        {0xE7EB,	2,	0x39D7C},	// 32位要右移两位

        // Alpha层页面大小
        {0x96000,	4,	0x14DA1},
        {0x96000,	4,	0x15BD0},
        {0x96000,	4,	0x3F346},
        {0x96000,	4,	0x51E3E},
        {0x96000,	4,	0x52278},
        {0x96000,	4,	0x52711},
        {0x96000,	4,	0x662AB},
        {0x96000,	4,	0x662C3},
        {0x96000,	4,	0x662DA},

        // 买东西下半部分花屏
        {0x12C000,	4,	0x54FF8},	// 分配内存
        {0x12C000,	4,	0x55002},	// 分配内存
        {0x4B000,	4,	0x5501D},	// memcpy
        {0x4B000,	4,	0x5505C},	// memcpy
        {0x4B000,	4,	0x56198},	// memcpy
        {0x96000,	4,	0x55035},	// Alpha混合
        {0x96000,	4,	0x55045},	// Alpha混合

        // 存档缩略图
        {0x23,		1,	0x0E413},

        // MyDialogParam
        {(DWORD)MyDialogBoxParamA, 4, 0xAA19C},
#endif
        // 字体名
        {szFont,	4,	0x0F6B8},
        {szFont,	4,	0x39C63},

        // 标题
        {szTitle,	4,	0x0A263},

        // 默认跑步
        {0x01,		1,	0xD3C70},

        // 强制可收化
        {0x81,		1,	0x72632},
        {0xEB,		1,	0x6CE4B},

        {0x00,		2,	0x5D426},	// 强制收化成功

        //{0x00,		1,	0xAF91C},	// BOSS归类为活物

        {0x00,		1,	0x7587A},	// 强制显示生命
        {0x00,		1,	0x758EA},	// 强制显示行动条
        //{0x52,		1,	0x28008},	// 修正游戏目录 push edx
        //{0x08EB,	2,	0x2ED2B},	// 动画目录强制为游戏目录
        //{0x08EB,	2,	0x9C63C},	// 动画目录强制为游戏目录
    };

    MEMORY_FUNCTION_PATCH func[] =
    {
#if PATCH_WINDOW_MODE == 1
	    {JUMP, 0x408BA1, (DWORD)_ConvertSurface1,	0x02},	// 读档
	    {CALL, 0x40F2F2, (DWORD)_ConvertSurface3,	0x00},	// 大地图
	    {CALL, 0x43F374, (DWORD)_ConvertSurface1,	0x0B},	// 主界面
	    {CALL, 0x469676, (DWORD)_ConvertSurface2,	0x00},
	    {CALL, 0x469724, (DWORD)_ConvertSurface2,	0x00},
	    {CALL, 0x412D48, (DWORD)_ConvertSurface4,	0x00},	// 大地图2
	    {CALL, 0x4124E7, (DWORD)_ConvertSurface4,	0x01},	// 未测
	    {CALL, 0x456D6C, (DWORD)_ConvertSurface4,	0x01},	// 未测
	    {CALL, 0x45B85E, (DWORD)_ConvertSurface4,	0x00},	// 未测

	    {CALL, 0x43B311, (DWORD)FixTextOut,			0x00},	// 修正文字显示不正常

	    {CALL, 0x40A5B8, (DWORD)SaveScreenShot,		0x00},	// P键截图

	    {CALL, 0x40AF5A, (DWORD)MySetWindowPos,		0x01},
#endif
        // PATCH_FUNCTION(CALL, 0, 0x28008, FixGamePath, 0x10),
        PATCH_FUNCTION(CALL, 0, 0x89D69, SetMonsterFlag),
    };

    Nt_PatchMemory(patch, countof(patch), func, countof(func), Nt_GetExeModuleHandle());

    return TRUE;
}

BOOL WINAPI DllMain(PVOID BaseAddress, ULONG Reason, PVOID Reserved)
{
    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Initialize(BaseAddress) || UnInitialize(BaseAddress);

        case DLL_PROCESS_DETACH:
            UnInitialize(BaseAddress);
            break;
    }

    return TRUE;
}
#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include <d3d9.h>
#include "my_headers.h"
#include "my_commsrc.h"

#define TEXTURE_COUNT   (8)

#define DOWN_CPU_USAGE 1

typedef struct
{
    PVOID               VirtualMethodTable;
    ULONG               Unknown[2];
    IDirect3DTexture9  *Texture;
} KENGEKI_TEXTURE, *PKENGEKI_TEXTURE;

PKENGEKI_TEXTURE    g_Texture[TEXTURE_COUNT];
D3DLOCKED_RECT      g_LockedRect[TEXTURE_COUNT];

VOID
(FASTCALL
*GenerateCharInfoFunc)(
    HDC             hDC,
    D3DLOCKED_RECT *LockedRect,
    PVOID           CharInfo,
    USHORT          uChar
);

PKENGEKI_TEXTURE
(CDECL
*CreateTextureFunc)(
    ULONG Width,
    ULONG Height,
    ULONG Levels,
    ULONG Usage,
    ULONG Format,
    ULONG Unknown
);

ULONG g_Count;
BOOL (WINAPI *OldPeekMessageA)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

BOOL WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    BOOL Result = OldPeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);

    if (Result == FALSE)
    {
        ULONG TickCount;
        static ULONG LastTickCount;

        TickCount = GetTickCount();
        if (TickCount - LastTickCount < 10 && --g_Count == 0)
        {
            LARGE_INTEGER TimeOut;
            g_Count = 4;

            BaseFormatTimeOut(&TimeOut, 1);
            NtDelayExecution(FALSE, &TimeOut);
        }
        LastTickCount = TickCount;
    }

    return Result;
}

HFONT
WINAPI
MyCreateFontA(
    int cHeight,
    int cWidth,
    int cEscapement,
    int cOrientation,
    int cWeight,
    ULONG bItalic,
    ULONG bUnderline,
    ULONG bStrikeOut,
    ULONG /* iCharSet */,
    ULONG iOutPrecision,
    ULONG iClipPrecision,
    ULONG iQuality,
    ULONG iPitchAndFamily,
    LPCSTR /* pszFaceName */
)
{
//    PWCHAR  FaceName;
//    ULONG   Length;

//    Length = StrLengthA(pszFaceName) + 1;
//    FaceName = (PWCHAR)AllocStack(Length * sizeof(WCHAR));
//    Nt_AnsiToUnicode(FaceName, Length, pszFaceName, Length - 1);

    return CreateFontW(
                cHeight,
                cWidth,
                cEscapement,
                cOrientation,
                cWeight,
                bItalic,
                bUnderline,
                bStrikeOut,
                GB2312_CHARSET,
                iOutPrecision,
                iClipPrecision,
                iQuality,
                iPitchAndFamily,
                L"ºÚÌå"
             );
}

VOID FASTCALL SetGameTitle(PVOID This, PVOID, PCSTR /* GameTitle */)
{
    struct
    {
        DUMMY_STRUCT(0x20);
        HWND hWnd;
        DUMMY_STRUCT(0x48);
        VOID (FASTCALL **SetGameTitleRoutine)(PVOID This, PVOID, PCSTR GameTitle);
    } *GameWindow;

    *(PULONG_PTR)&GameWindow = (ULONG_PTR)This;

    if (GameWindow == NULL)
        DebugBreakPoint();

    if (IsWindow(GameWindow->hWnd))
    {
        if (GameWindow->SetGameTitleRoutine == NULL)
        {
            SetWindowTextW(GameWindow->hWnd, L"ÑýÑý½£êªÃÎÏë");
        }
        else
        {
            GameWindow->SetGameTitleRoutine[34](This, 0, "ÑýÑý½£êªÃÎÏë");
        }
        
        return;
    }
    else if (GameWindow->SetGameTitleRoutine == NULL)
    {
        DebugBreakPoint();
    }
    else
    {
        GameWindow->SetGameTitleRoutine[34](This, 0, "ÑýÑý½£êªÃÎÏë");
    }
}

HRESULT STDCALL LockRect(ULONG, D3DLOCKED_RECT *LockedRect, PRECT, ULONG)
{
    *LockedRect = g_LockedRect[0];
    return S_OK;
}

HRESULT STDCALL UnlockRect()
{
    PKENGEKI_TEXTURE *Texture, *TextureBase;

    TextureBase = g_Texture;
    Texture     = TextureBase + 1;

    for (ULONG Count = TEXTURE_COUNT - 1; Count; --Count)
    {
        if (*Texture != NULL)
        {
            (*Texture)->Texture->UnlockRect(0);
            (*Texture)->Texture->GenerateMipSubLevels();
        }

        ++Texture;
    }

    if (*TextureBase != NULL)
        (*TextureBase)->Texture->UnlockRect(0);

    return S_OK;
}

ASM PKENGEKI_TEXTURE OldSelectTexture()
{
    ASM_DUMMY_AUTO();
}

ASM PKENGEKI_TEXTURE SelectTexture()
{
    INLINE_ASM
    {
        lea edi, [g_Texture - 0xC];
        jmp OldSelectTexture;
    }
}

PKENGEKI_TEXTURE
CDECL
CreateTexture(
    ULONG Width,
    ULONG Height,
    ULONG Levels,
    ULONG Usage,
    ULONG Format,
    ULONG Unknown
)
{
    PKENGEKI_TEXTURE *Texture, *TextureBase;
    D3DLOCKED_RECT   *LockedRect;

    TextureBase = g_Texture;
    Texture     = TextureBase;
    LockedRect  = g_LockedRect;

    for (ULONG Count = TEXTURE_COUNT; Count; --Count)
    {
        *Texture = CreateTextureFunc(Width, Height, Levels, Usage, Format, Unknown);
        if (*Texture == NULL)
            goto CLEAN_UP;

        if (FAILED((*Texture)->Texture->LockRect(0, LockedRect, NULL, D3DLOCK_DISCARD)))
            goto CLEAN_UP;

        ++LockedRect;
        ++Texture;
    }

//    Texture[-TEXTURE_COUNT]->Texture->UnlockRect(0);
    return Texture[-TEXTURE_COUNT];

CLEAN_UP:

    while (Texture >= TextureBase)
    {
        (*Texture)->Texture->UnlockRect(0);
        (*Texture)->Texture->Release();
        *Texture = NULL;
        --Texture;
    }

    return NULL;
}

VOID
FASTCALL
GenerateCharInfo(
    HDC             hDC,
    D3DLOCKED_RECT *LockedRect,
    PVOID           CharInfo,
    USHORT          uChar
)
{
    LockedRect = g_LockedRect;
    GenerateCharInfoFunc(hDC, LockedRect, CharInfo, uChar);
}

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    CHAR Buffer[0xF00];
    sprintf(
        Buffer,
        "code = %08X, addr = %08X\r\n",
        ExceptionInfo->ExceptionRecord->ExceptionCode,
        ExceptionInfo->ExceptionRecord->ExceptionAddress
    );

    return EXCEPTION_CONTINUE_SEARCH;
}

BOOL Init()
{
//    RtlAddVectoredExceptionHandler(TRUE, VectoredHandler);
    PVOID BaseAddress = Nt_GetExeModuleHandle();

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY(".936",        4, 0x25D360),   // setlocale
        PATCH_MEMORY(0xFEFE,        2, 0x25D8A1),   // gbk char
        PATCH_MEMORY(0x00,          1, 0x25D88C),   // gbk char
        PATCH_MEMORY(0x90903DEB,    4, 0x25D8AC),   // gbk char

        PATCH_MEMORY(MyCreateFontA,     sizeof(ULONG_PTR), 0x3261E0),

#if DOWN_CPU_USAGE
        PATCH_MEMORY(0x00,          1, 0x27ECD0),   // cpu usage
        PATCH_MEMORY(0x01,          1, 0x27ECDC),   // cpu usage
        PATCH_MEMORY(MyPeekMessageA,    sizeof(ULONG_PTR), 0x3268D0),
#endif
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        PATCH_FUNCTION(JUMP, 0, 0x25D3E5, (PVOID)(0x25D5CF + (ULONG_PTR)BaseAddress)),  // bypass LockRect
//        PATCH_FUNCTION(JUMP, 0, 0x25D659, (PVOID)(0x25D826 + (ULONG_PTR)BaseAddress)),  // bypass LockRect

        PATCH_FUNCTION(CALL, 0, 0x2D79A5, SetGameTitle),
        PATCH_FUNCTION(JUMP, 0, 0x26E021, SelectTexture, 2, OldSelectTexture),
        PATCH_FUNCTION(CALL, 0, 0x25D3D5, CreateTexture),
        PATCH_FUNCTION(CALL, 0, 0x25D663, LockRect),
        PATCH_FUNCTION(CALL, 0, 0x25D8FC, UnlockRect),
        PATCH_FUNCTION(CALL, 0, 0x25D899, GenerateCharInfo),
    };

    Nt_PatchMemory(p, countof(p), f, countof(f), BaseAddress);

    *(PULONG_PTR)&CreateTextureFunc     = (ULONG_PTR)BaseAddress + 0x2FC470;
    *(PULONG_PTR)&GenerateCharInfoFunc  = (ULONG_PTR)BaseAddress + 0x25CB10;

#if DOWN_CPU_USAGE
    *(PULONG_PTR)&OldPeekMessageA       = (ULONG_PTR)p[countof(p) - 1].DataBak;
    g_Count = 4;
#endif

    return TRUE;
}

ULONG
WINAPI
MyGetGlyphOutlineA(
    HDC             hDC,
    UINT            uChar,
    UINT            uFormat,
    LPGLYPHMETRICS  lpgm,
    DWORD           cbBuffer,
    LPVOID          lpvBuffer,
    CONST MAT2     *lpmat2
)
{
    uChar &= 0xFFFF;
    uChar = SWAPCHAR(uChar);

    LOOP_ONCE
    {
        if (uChar >= 0x824F && uChar <= 0x8258)
        {
            uChar = 0x824F - 0x824F + '£°';
        }
        else if (uChar == 0x8145)
        {
            uChar = '¡¤';
        }
        else if (uChar == 0x815E)
        {
            uChar = '£¯';
        }
        else
        {
            break;
        }

        uChar = SWAPCHAR(uChar);
    }

    return GetGlyphOutlineA(hDC, uChar, uFormat, lpgm, cbBuffer, lpvBuffer, lpmat2);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            if (MyGetGlyphOutlineA == NULL)
                return FALSE;

            LdrDisableThreadCalloutsForDll(hInstance);
            return Init();

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

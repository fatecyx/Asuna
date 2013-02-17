#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
//#pragma comment(linker,"/MERGE:.data=.Kanade")

#if defined(MY_DEBUG)
#pragma comment(linker,"/ENTRY:DllMain")
#endif

#include <Windows.h>
#include "my_common.h"
#include "crt_h.h"
#include "my_mem.h"
#include "nt_api.h"
#include "my_crt.h"
#include "my_image.h"
#include "my_audio.h"
#include "asairo.h"

DWORD dwCount;

#define USE_CACHE
//#define USE_DYNAMIC

#if defined(USE_CACHE)

const DWORD dwMaxCacheCount = 61, dwMaxWasteCount = 5;
DWORD g_dwUCIReadCount, g_dwCacheHitCount, g_dwCacheCount;
SCacheIndex CacheIndex[dwMaxCacheCount], *g_pCache;
HANDLE g_hHeap;

#endif

#if defined(USE_DYNAMIC)
#include "sha2.c"
#include "TextHandler.h"
#include "TextHandler.cpp"
CText *Text;
#endif

SHORT WINAPI MyGetAsyncKeyState(int vKey)
{
    if (vKey == VK_ESCAPE)
        return 0;
    return GetAsyncKeyState(vKey);
}

BOOL WINAPI MySetWindowTextA(HWND hWnd, LPSTR lpString)
{
    Int32 iLength = StrLengthA(lpString) - 2;

    if (iLength > 0)
    {
        Int32 i = iLength;
        while (*(PUInt16)&lpString[iLength] == TAG2('，') || *(PUInt16)&lpString[iLength] == '\r\n')
            iLength -= 2;
        if (iLength != i)
            lpString[iLength + 2] = 0;
    }

    return SetWindowTextA(hWnd, lpString);
}

HANDLE WINAPI MyCreateFileA(LPSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    Char  szFile[MAX_PATH];
    DWORD dwLength;

    do if ((dwDesiredAccess & GENERIC_WRITE) == 0)
    {
        dwLength = StrLengthA(lpFileName);
        if (dwLength < 3 ||
            lpFileName[dwLength - 4] != '.' ||
            (*(LPDWORD)(&lpFileName[dwLength - 3]) & 0xFFDFDFDF) != TAG3('MPK') ||
            GetFileAttributesA(lpFileName) != -1)
            break;

        dwLength -= 4;
        memcpy(szFile, lpFileName, dwLength);
        *(LPDWORD)(szFile + dwLength) = TAG4('_sc.');
        *(LPDWORD)(szFile + dwLength + 4) = TAG3('mpk');
        lpFileName = szFile;
    } while (0);

    return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

#if defined(USE_DYNAMIC) || defined(USE_CACHE)

Void WINAPI ExitGame()
{
    HANDLE hHeap;
    SCacheIndex *pCache;

    __asm mov  eax, 445AA0h;
    __asm call eax;

#if defined(USE_DYNAMIC)
    if (Text)
    {
        delete Text;
        Text = NULL;
    }
#endif

#if defined(USE_CACHE)
    hHeap = g_hHeap;
    pCache = CacheIndex;
    for (UInt32 i = 0; i != dwMaxCacheCount; ++i)
    {
        if (pCache->pbBuffer)
            HeapFree(hHeap, 0, pCache->pbBuffer);
        ++pCache;
    }
#endif

}

#endif

BOOL WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    BOOL bResult = PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);

    if (bResult == False)
    {
        DWORD dwTickCount;
        static DWORD dwLastTickCount;

        dwTickCount = GetTickCount();
        if (dwTickCount - dwLastTickCount < 10 && --dwCount == 0)
        {
            dwCount = 4;
            Sleep(1);
        }
        dwLastTickCount = dwTickCount;
    }
    else
    {
        switch (lpMsg->message)
        {
        case WM_KEYDOWN:
            switch (lpMsg->wParam)
            {
#if defined(USE_CACHE)
            case VK_DELETE:
                if (MessageBoxA(lpMsg->hwnd, "确定要清空所有CG缓存吗?", NULL, MB_OKCANCEL|MB_ICONASTERISK) == IDOK)
                {
                    HANDLE hHeap = g_hHeap;
                    SCacheIndex *pCache;

                    pCache = CacheIndex;
                    for (UInt32 i = 0; i != dwMaxCacheCount; ++i)
                    {
                        if (pCache->pbBuffer)
                        {
                            HeapFree(hHeap, 0, pCache->pbBuffer);
                            pCache->pbBuffer = NULL;
                        }
                        ++pCache;
                    }
                    g_dwCacheCount = 0;
                    g_dwCacheHitCount = 0;
                    g_dwUCIReadCount = 0;
                }
                break;

            case VK_HOME:
                {
                    Char szBuffer[200];
                    DWORD dwCacheSize;

                    dwCacheSize = 0;
                    for (int i = 0; i != dwMaxCacheCount; ++i)
                    {
                        if (CacheIndex[i].pbBuffer)
                            dwCacheSize += CacheIndex[i].dwMaxSize;
                    }

                    wsprintfA(szBuffer, "Cache总数量: %u\n"
                                        "当前cache数: %u\n"
                                        "读取UCI次数: %u\n"
                                        "命中cache数: %u\n"
                                        "cache命中率: %u%%\n"
                                        "cache总大小: %u MB\n",
                        dwMaxCacheCount, g_dwCacheCount,
                        g_dwUCIReadCount, g_dwCacheHitCount,
                        g_dwUCIReadCount ? g_dwCacheHitCount * 100 / g_dwUCIReadCount : 0,
                        dwCacheSize / 1024 / 1024);

                    MessageBoxA(lpMsg->hwnd, szBuffer, NULL, 64);
                }
                break;
#endif
            }
            break;
        }
    }

    return bResult;
}

#if defined(USE_DYNAMIC)

LPVoid CDECL GetText(void *dst, LPCSTR lpSrcString, UInt32 uLength)
{
    if (uLength)
    {
        PChar  pMultiByte;
        PWChar pWideChar;
        Int32  iWideLength, iMultiLength, i;
        if (Text == NULL)
            return memcpy(dst, lpSrcString, uLength);

        iMultiLength = uLength + 4;
        iWideLength  = iMultiLength;
        pWideChar    = (PWChar)_alloca(iWideLength * 2 + iMultiLength);
        pMultiByte   = (PChar)pWideChar + iWideLength * 2;
        iWideLength = MultiByteToWideChar(932, 0, lpSrcString, uLength, pWideChar, iWideLength);
        pWideChar[iWideLength] = 0;
        for (Int i = 0; ; i++)
        {
            WChar c = pWideChar[i];
            if (c == 0)
                break;
            else if (c == 0x30FB)
                pWideChar[i] = L'·';
        }

        i = WideCharToMultiByte(936, 0, pWideChar, iWideLength, pMultiByte, iMultiLength, 0, 0);
        pMultiByte[i] = 0;
        if (Text->GetText(dst, pMultiByte) == 0)
            return memcpy(dst, lpSrcString, uLength);
    }

    return dst;
}

#endif

ASM UInt32 GetDecodedSizeCG()
{
    __asm
    {
        push esi;
        lea  eax, dword ptr [edi+42A0h];
        push eax;
        lea  eax, dword ptr [ecx+esi];
        push eax;
        call GetDecodedSizeNative;
        mov  ebx, eax;
        ret;
    }
}

ASM UInt32 GetDecodedSizeEff()
{
    __asm
    {
        mov  eax, [esp+44Ch];
        push edi;
        push eax;
        lea  eax, dword ptr [edi+ebp];
        push eax;
        call GetDecodedSizeNative;
        mov  ebx, eax;
        ret;
    }
}

ASM UInt32 GetDecodedSize1()
{
    __asm
    {
        lea  eax, [esp+70h];
        push 2;
        push eax;
        lea  eax, dword ptr [edi+2];
        push eax;
        call GetDecodedSizeNative;
        mov  ebx, eax;
        mov  eax, edx;
        ret;
    }
}

ASM UInt32 GetDecodedSize2()
{
    __asm
    {
        mov  eax, [esp+40h];
        push 2;
        push eax;
        lea  eax, dword ptr [esi+2];
        push eax;
        call GetDecodedSizeNative;
        mov  ebx, eax;
        mov  ebp, edx;
        ret;
    }
}

UInt64 WINAPI GetDecodedSizeNative(LPVoid lpBuffer, LPCSTR lpFileName, Int32 iOffset)
{
    Int32 w, h, b;

    b = *(PInt32)lpBuffer;
    do if ((b & 0xFFFFFF) == TAG3('UCI') && ((UInt32)b >> 24) >= '3')
    {
        if (UCIDecode(lpBuffer, INT_MAX, NULL, NULL, &w, &h, &b) < 0)
            break;

#if defined(USE_CACHE)
        SCacheIndex *pCache;

        pCache = &CacheIndex[(HashAPI(lpFileName) ^ (iOffset << 12)) % dwMaxCacheCount];
        g_pCache = pCache;
        if (pCache->pbBuffer && pCache->dwOffset == iOffset && !lstrcmpiA(pCache->szName, lpFileName))
        {
            *(PInt32)&pCache->pbBuffer |= 0x80000000;
            return pCache->dwSize;
        }
        else
        {
            lstrcpyA(pCache->szName, lpFileName);
            *(PInt32)&pCache->pbBuffer &= 0x7FFFFFFF;
            pCache->dwOffset = iOffset;
        }

#endif

        b /= 8;
        return h * (w * b + (b == 3 ? w & 3 : 0)) + sizeof(SBitMapHeader);

    } while(0);

    return b|((UInt64)*(PUInt32)((PByte)lpBuffer + 4) << 32);
}

UInt32 CDECL Decompress(Int32 iDestLen)
{
    PByte pbInput, pbOutput, pbBitmap;
    Int32 w, h, b, stride, stride_raw, iSrcLen;
    SBitMapHeader *pHeader;

    __asm
    {
        mov  pbInput,  eax;
        mov  pbOutput, ebx;
        mov  iSrcLen,  ecx;
    }

    b = *(PInt32)(pbInput - 8);
    if ((b & 0xFFFFFF) != TAG3('UCI') || ((UInt32)b >> 24) < '3')
    {
        __asm
        {
            mov  eax, pbInput;
            mov  ebx, pbOutput;
            mov  ecx, iSrcLen;
            mov  edx, 441700h;
            push ebx;
            call edx;
            add  esp, 4;
            mov  iDestLen, eax;
        }

        return iDestLen;
    }

#if defined(USE_CACHE)
    HANDLE hHeap;
    SCacheIndex *pCache = g_pCache;

    ++g_dwUCIReadCount;
    if (pCache && (Int32)pCache->pbBuffer < 0)
    {
        ++g_dwCacheHitCount;
        *(PInt32)&pCache->pbBuffer &= 0x7FFFFFFF;
        memcpy(pbOutput, pCache->pbBuffer, pCache->dwSize);
        return pCache->dwSize;
    }
#endif

    if (UCIDecode(pbInput - 8, INT_MAX, (void **)&pbBitmap, &stride_raw, &w, &h, &b) < 0)
        return 0;

    pbInput = pbBitmap + stride_raw * h;
    pHeader = (SBitMapHeader *)pbOutput;
    InitBitmapHeader(pHeader, w, h, b, &stride);
    pbOutput += sizeof(*pHeader);

    if (b == 32)
    {
        PByte pbTempRow, pbTemp;

        pbTempRow = (PByte)_alloca(stride);
        memset4(pbTempRow, RGBA(1, 1, 1, 255), stride);
        pbTemp = pbInput - stride_raw;
        for (Int32 i = h; i; --i, pbTemp -= stride_raw)
            if (memcmp(pbTemp, pbTempRow, stride))
                goto NOT_PURE_BLACK;

        ZeroMemory(pbOutput, iDestLen - sizeof(*pHeader));
        goto FINISH_DEC;
    }

NOT_PURE_BLACK:
    while (h--)
    {
        pbInput -= stride_raw;
        memcpy(pbOutput, pbInput, stride_raw);
        pbOutput += stride;
    }

FINISH_DEC:
    UCIFree(pbBitmap);

#if defined(USE_CACHE)

    ULong ulNewSize;

    do if (pCache)
    {
        hHeap = g_hHeap;
        if (pCache->pbBuffer == NULL)
        {
            pCache->pbBuffer = (PByte)HeapAlloc(hHeap, 0, iDestLen);
            if (pCache->pbBuffer == NULL)
                break;

            ++g_dwCacheCount;
            pCache->dwWaste = 0;
            pCache->dwMaxSize = iDestLen;
        }
        else if (pCache->dwMaxSize < (ULong)iDestLen)
        {
            PByte pbRealloc;
            pbRealloc = (PByte)HeapReAlloc(hHeap, 0, pCache->pbBuffer, iDestLen);
            if (pbRealloc == NULL)
            {
                HeapFree(hHeap, 0, pCache->pbBuffer);
                pCache->pbBuffer = NULL;
                break;
            }

            pCache->pbBuffer = pbRealloc;
            pCache->dwMaxSize = iDestLen;
            pCache->dwWaste = 0;
        }
        else if ((ulNewSize = iDestLen/* * 3 / 2*/) < pCache->dwMaxSize && ++pCache->dwWaste == dwMaxWasteCount)
        {
            PByte pbReAlloc;

            pbReAlloc = (PByte)HeapReAlloc(hHeap, 0, pCache->pbBuffer, ulNewSize);
            if (pbReAlloc == NULL)
            {
                HeapFree(hHeap, 0, pCache->pbBuffer);
                pCache->pbBuffer = NULL;
                break;
            }

            pCache->dwWaste = 0;
            pCache->pbBuffer = pbReAlloc;
            pCache->dwMaxSize = ulNewSize;
        }

        pCache->dwSize = iDestLen;
        memcpy(pCache->pbBuffer, pHeader, iDestLen);

    } while (0);
#endif

    return iDestLen;
}

Bool WINAPI ReadAudioNative(LPVoid lpBuffer, UInt32 uSize, Long lOffset, LPVoid *pBufferPointer, SFileInfo *pFileInfo)
{
    Bool r;
    DWORD dwRead;
    LPVoid lpWave;
    LPVoid (CDECL *GMalloc)(size_t)  = (LPVoid(CDECL *)(size_t))0x419C28;
    LPVoid (CDECL *GRealloc)(LPVoid, size_t) = (LPVoid(CDECL *)(LPVoid, size_t))0x42555D;
    Void   (CDECL *GFree)(LPVoid)    = (Void  (CDECL *)(LPVoid))0x419A09;

    if (pFileInfo->hFile == NULL)
        return False;

    if (pFileInfo->bPack)
        lOffset += pFileInfo->lOffset;
    if (SetFilePointer(pFileInfo->hFile, lOffset, NULL, FILE_BEGIN) == -1 && GetLastError() != NO_ERROR)
        return False;

    if (uSize == 0 && pFileInfo->bPack == False)
        uSize = GetFileSize(pFileInfo->hFile, NULL);
    else
        uSize = pFileInfo->uSize;

    r = ReadFile(pFileInfo->hFile, lpBuffer, uSize, &dwRead, NULL);
    if (r == False || uSize != dwRead)
        return False;

    if ((*(PUInt32)lpBuffer & 0xFFFFFF) != TAG3('UCA'))
        return True;

    dwRead = -1;
    if (UCADecode2(lpBuffer, uSize, &lpWave, (PInt)&dwRead, 44100) < 0)
        return 0;

    lpBuffer = GRealloc(lpBuffer, dwRead);
    if (lpBuffer == NULL)
    {
        UCAFree(lpWave);
        return True;
    }

    memcpy(lpBuffer, lpWave, dwRead);
    *pBufferPointer = lpBuffer;
    pFileInfo->uSize = dwRead;
    UCAFree(lpWave);

    return True;
}

ASM Bool WINAPI ReadAudio(LPVoid lpBuffer)
{
    __asm
    {
        mov  edx, dword ptr [ebp+8];
        lea  edx, dword ptr [edi+edx*4+4Ch];
        push esi;
        push edx;
        push ecx;
        push eax;
        push dword ptr [esp+14h];
        call ReadAudioNative;
        ret 4;
    }
}
/*
ASM Void GetFixedColor()
{
    __asm
    {
        mov  eax, [esp+4];
        cmp  eax, 0FF010101h;
        jnz  NOT_PURE_BLACK;
        xor  eax, eax;
NOT_PURE_BLACK:
        ret 4;
    }
}

ASM Void FixColor1()
{
    __asm
    {
        push eax;
        push edx;
        call GetFixedColor;
        cmp  edx, eax;
        je   SAME;
        mov  edx, eax;
        mov  [ecx], eax;
SAME:
        mov  ebp, edx;
        shr  edx, 8;
        pop  eax;
        ret;
    }
}

ASM Void FixColor2()
{
    __asm
    {
        push eax;
        mov  edx, [ebp];
        push edx;
        call GetFixedColor;
        cmp  edx, eax;
        je   SAME;
        mov  edx, eax;
        mov  [ebp], eax;
SAME:
        mov  ebp, edx;
        pop  eax;
        ret;
    }
}

ASM Void FixColor3()
{
    __asm
    {
        push eax;
        push edx;
        call GetFixedColor;
        cmp  edx, eax;
        je   SAME;
        mov  edx, eax;
        mov  [ecx], eax;
SAME:
        mov  edi, edx;
        shr  edx, 8;
        pop  eax;
        ret;
    }
}

ASM Void FixColor4()
{
    __asm
    {
        push eax;
        push edx;
        call GetFixedColor;
        cmp  edx, eax;
        je   SAME;
        mov  edx, eax;
        mov  [ecx+ebp*4-4], eax;
SAME:
        mov  ebp, edx;
        shr  edx, 8;
        pop  eax;
        ret;
    }
}

ASM Void FixColor5()
{
    __asm
    {
        push eax;
        lea  ecx, dword ptr [ecx+edx*4];
        mov  edx, [ecx];
        push edx;
        call GetFixedColor;
        cmp  edx, eax;
        je   SAME;
        mov  edx, eax;
        mov  [ecx], eax;
SAME:
        mov  ecx, edx;
        shr  ecx, 8;
        pop  eax;
        add  [esp], 4;
        ret;
    }
}
*/
LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    Char buf[200];

    wsprintfA(buf, "code = %X\n"
                   "addr = %p\n",
                   ExceptionInfo->ExceptionRecord->ExceptionCode,
                   ExceptionInfo->ExceptionRecord->ExceptionAddress);
    MessageBoxA(0, buf, 0, 64);
    return EXCEPTION_CONTINUE_SEARCH;
}

#if defined(USE_DYNAMIC)

Void InitText()
{
    BOOL   bResult;
    PBYTE  pbBuffer;
    DWORD  dwSize;
    HANDLE hFile, hHeap;

    do
    {
        hFile = CreateFileA("asairo_sc.bin",
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (hFile == INVALID_HANDLE_VALUE)
            break;

        dwSize = GetFileSize(hFile, NULL);
        hHeap = GetProcessHeap();
        pbBuffer = (PBYTE)HeapAlloc(hHeap, 0, dwSize);
        if (pbBuffer == NULL)
        {
            CloseHandle(hFile);
            break;
        }
        bResult = ReadFile(hFile, pbBuffer, dwSize, &dwSize, NULL);
        CloseHandle(hFile);

        if (bResult)
        {
            if (Text) delete Text;
            Text = new CText;
            if (Text)
            {
                if (Text->Init(pbBuffer, dwSize) == False)
                {
                    delete Text;
                    Text = NULL;
                }
            }
        }

        HeapFree(hHeap, 0, pbBuffer);
    } while (0);
}

#endif

Void Init()
{
    DWORD i;
    WChar szPath[MAX_PATH];
    SPatch p[] =
    {
        { GB2312_CHARSET, 4, 0x45DBF },     // CreateFontA charset
        { GB2312_CHARSET, 1, 0x55E63 },     // enumfont charset
        { 0x0,            1, 0x55D91 },     // enumfont call back

        // bound
        { 0xEB,           1, 0x4C378 },
        { 0xEB,           1, 0x4C568 },
        { 0xEB,           1, 0x4FE78 },

        { 0x17EB,         2, 0x45F5A },
        { 0xEB,           1, 0x4603B },
        { 0x1BEB,         2, 0x4713B },
        { 0x1BEB,         2, 0x4A18F },
        { 0x1DEB,         2, 0x4A203 },
        { 0x1BEB,         2, 0x4A280 },
        { 0x1DEB,         2, 0x4A3D5 },
        { 0x1CEB,         2, 0x4A44A },
        { 0x1BEB,         2, 0x4A5DF },
        { 0x1BEB,         2, 0x4A7DB },

        { 0x19EB,         2, 0x4A904 },
        { 0x1DEB,         2, 0x4AA29 },
        { 0x1BEB,         2, 0x4AAE2 },
        { 0x1BEB,         2, 0x4AC41 },
        { 0x19EB,         2, 0x4AD0F },
        { 0x19EB,         2, 0x4AD92 },
        { 0x18EB,         2, 0x4AF7A },
        { 0x1BEB,         2, 0x4AFF0 },
        { 0x1BEB,         2, 0x4B187 },
        { 0x1BEB,         2, 0x4B2C6 },

        { 0x1BEB,         2, 0x4C155 },
        { 0x1CEB,         2, 0x4C999 },
        { 0x17EB,         2, 0x4CA92 },
        { 0x1BEB,         2, 0x4CB26 },
        { 0x1BEB,         2, 0x4E924 },
        { 0x1BEB,         2, 0x4EC95 },
        { 0x19EB,         2, 0x4ED4F },
        { 0x19EB,         2, 0x4EDCF },
        { 0x19EB,         2, 0x4EE4F },

#if defined(MY_DEBUG)
        { 0x8D,                   1, 0x60ED1 },  // lea esi, MyPeekMessageA
        { (DWORD)&MyPeekMessageA, 4, 0x60ED3 },

        // iat hooks
        { (DWORD)MyCreateFileA,      4, 0x66098 },
        { (DWORD)MyGetAsyncKeyState, 4, 0x66348 },
        { (DWORD)MySetWindowTextA,   4, 0x66248 },
#endif
    };

    SFuncPatch f[] =
    {
        { CALL, 0x5960A, GetDecodedSizeCG,  2 },
        { CALL, 0x594AD, GetDecodedSizeEff, 2 },
        { CALL, 0x5AEE3, GetDecodedSize1,   1 },
        { CALL, 0x59251, GetDecodedSize2,   1 },
        { CALL, 0x594D3, Decompress,        0 },
        { CALL, 0x59632, Decompress,        0 },
        { CALL, 0x59270, Decompress,        0 },
        { CALL, 0x5AEFC, Decompress,        0 },
        { CALL, 0x55808, ReadAudio,         0 },
#if defined(USE_DYNAMIC)
        { CALL, 0x57DF8, GetText,           0 },
//        { JUMP, 0x4C220, GetText,         1 },
#endif
#if defined(USE_CACHE) || defined(USE_DYNAMIC)
        { CALL, 0x546D2, ExitGame,          0 },
#endif
/*
        { CALL, 0x10032, FixColor1, 0 },
        { CALL, 0x10077, FixColor2, 0 },
        { CALL, 0x100C5, FixColor3, 0 },
        { CALL, 0x100FB, FixColor4, 0 },
        { CALL, 0x10127, FixColor3, 0 },
        { CALL, 0x10174, FixColor5, 0 },
        { CALL, 0x1028B, FixColor2, 0 },
*/
    };

#if defined(MY_DEBUG)
    PatchMemory(p, countof(p), f, countof(f), GetModuleHandleA(0));
#else
    PatchMemoryNoVP(p, countof(p), f, countof(f), GetModuleHandleA(0));
#endif

    dwCount = 4;

#if defined(USE_CACHE)
    g_hHeap = GetProcessHeap();
#endif

    AddVectoredExceptionHandler(True, VectoredHandler);

    i = GetModuleFileNameW(0, szPath, countof(szPath));
    while (szPath[--i] != L'\\');
    szPath[i] = 0;
    SetCurrentDirectoryW(szPath);

#if defined(USE_DYNAMIC)
    InitText();
#endif
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID lpReserved)
{
    static Bool bInit = False;

    if (bInit == False)
    {
        bInit = True;
        Init();
    }

    return True;
}
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "d3d8.lib")

#include "ZWEI2Plus.h"
#include <d3d8.h>
#include "TextHandler.h"
//#include "Trainer/CWindow.h"

OVERLOAD_OP_NEW

#if defined(USE_ENCRYPT_TEXT)
CText *Text;
#endif

DWORD dwCount;

//typedef CWindow* (STDCALL *F_Create)();
//typedef Void (STDCALL *F_Destroy)(CWindow*);
typedef int (CDECL *F_vsprintf)(LPTSTR *lpOutput, LPCTSTR lpFmt, va_list arglist);

BOOL WINAPI MySetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
    RECT rcDesktop;

    SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcDesktop, 0);
    X = ((rcDesktop.right - rcDesktop.left) - cx) >> 1;
    Y = ((rcDesktop.bottom - rcDesktop.top) - cy) >> 1;
    return SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags&~SWP_NOMOVE);
}

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
#if defined(USE_ENCRYPT_TEXT)
        case WM_QUIT:
            if (Text)
            {
                delete Text;
                Text = NULL;
            }
            break;
#endif

        case WM_KEYUP:
            switch (lpMsg->wParam)
            {
                case 0:
                    break;
                default:
                    break;
#if defined(USE_ENCRYPT_TEXT)
            case VK_F5:
                if (GetAsyncKeyState(VK_SHIFT) < 0)
                {
                    Init();
                }
                break;
#endif
/*
            case VK_F1:
                break;
                if (GetAsyncKeyState(VK_SHIFT) < 0)
                {
                    CWindow *wnd;
                    HMODULE hModuleTrainer;
                    F_Create  Create;
                    F_Destroy Destroy;

                    hModuleTrainer = LoadLibraryA("Trainer.dll");
                    if (hModuleTrainer == NULL)
                        return bResult;

                    Create  = (F_Create)GetProcAddress(hModuleTrainer, "Create");
                    Destroy = (F_Destroy)GetProcAddress(hModuleTrainer, "Destroy");
                    if (Create && Destroy)
                    {
                        wnd = Create();
                        if (wnd)
                        {
                            wnd->Show(GetModuleHandleA(0), SW_SHOWDEFAULT, "ZW2P", "ZW2P");
                            Destroy(wnd);
                        }
                    }
                }
*/
                break;
            }
        }
    }

    return bResult;
}

#if defined(USE_ENCRYPT_TEXT)

Bool IsAPIHooked()
{
    return *(PBYTE)TextOutA == JUMP || 
           *(PBYTE)GetGlyphOutlineW == JUMP || 
           *(PBYTE)GetGlyphOutlineA == JUMP;
}

int CDECL Mywvsprintf(LPSTR *lpOutput, LPSTR lpFmt, va_list arglist)
{
    int i, j;
    F_vsprintf vsprintf = (F_vsprintf)0x543C53;
    static CHAR szText[20][0x200];

    if (!IsAPIHooked() && Text)
    {
        CHAR  ch;
        LPSTR *lpArgList, lpFormat;

        j = 0;
        lpFormat = lpFmt;
        lpArgList = (CHAR **)arglist;
        while (ch = *lpFormat++)
        {
            if (ch == '%')
            {
                switch (*lpFormat++)
                {
                case 'f':
                    ++j;
                    goto _DEFAULT_;
                case 's':
                    if (Text->GetText(szText[j], lpArgList[j]))
                        lpArgList[j] = szText[j];
                case 'i':
                case 'd':
                case 'u':
                case 'X':
                case 'x':
_DEFAULT_:
                    ++j;
                    if (*lpFormat == '\\')
                        lpFormat += lpFormat[1] == '\\' ? 2 : 1;
                case '%':
                    break;
                }
            }
        }

        if (j == 0)
        {
            if (Text->GetText(szText[j], lpFmt))
                lpFmt = szText[j];
        }
    }

    i = vsprintf(lpOutput, lpFmt, arglist);

    return i;
}

Void WINAPI ProcessCharName(LPSTR lpString1, LPCSTR lpString2)
{
    if (Text == NULL || IsAPIHooked() || Text->GetText(lpString1, lpString2) == 0)
    {
        lstrcpyA(lpString1, lpString2);
    }
}

Void WINAPI ProcessNiikki(LPSTR lpString1, LPCSTR lpString2)
{
    ProcessCharName(lpString1, lpString2);
}

LPSTR CDECL ProcessBuildingName(LPSTR lpText)
{
    __asm
    {
        mov eax, lpText;
        lea eax, dword ptr [eax+63CF50h];
        mov lpText, eax;
    }

    if (Text)
    {
        Text->GetText(lpText, lpText);
    }

    return lpText;
}

DWORD CDECL Mystrncpy(LPSTR lpDest, LPSTR lpSource, DWORD dwLength)
{
    CHAR ch;
    DWORD dwLen;
    LPSTR lpDst;

    if (Text == NULL || IsAPIHooked() || (dwLen = Text->GetText(lpDest, lpSource)) == 0)
    {
        dwLen = dwLength;
        lpDst = lpDest;
        while (dwLength--)
        {
            ch = *lpSource++;
            *lpDst++ = ch;
            if (ch == 0)
            {
                memset(lpDst, 0, dwLength);
                break;
            }
        }
    }

    return dwLen;
}

Void Init()
{
    BOOL   bResult;
    PBYTE  pbBuffer;
    DWORD  dwSize;
    HANDLE hFile, hHeap;

    do
    {
        hFile = CreateFileA("scp.sc", 
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

IDirect3D8* WINAPI MyDirect3DCreate8(UINT SDKVersion)
{

#if defined(USE_ENCRYPT_TEXT)
    if (!IsAPIHooked())
#endif
    {
        DisableThreadLibraryCalls((HMODULE)&__ImageBase);

#if defined(USE_ENCRYPT_TEXT)
        Init();
#endif

        dwCount = 4;
        PatchMemory(p, countof(p), f, countof(f), GetModuleHandleA(NULL));
    }

    return Direct3DCreate8(SDKVersion);
}

HANDLE WINAPI MyCreateFileA(LPSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    CHAR szFileName[MAX_PATH];
    LPSTR lpFile;
    DWORD  dwLength, dwLength2;
    static CHAR szPath[] = "DATA\\S??\\";

    dwLength = StrLengthA(lpFileName);
    lpFile = lpFileName + dwLength;

    for (Int i = 0; i != 3 && dwLength-- >= 4; ++i)
        while (dwLength-- >= 4 && *--lpFile != '\\');

    if (dwLength >= 3)
    {
        Int i;

        for (i = 0; i != sizeof(szPath) - 1; ++i)
        {
            if (szPath[i] == '?')
            {
                if (*++lpFile == 0)
                    break;

                continue;
            }
            if (((*++lpFile ^ szPath[i]) & 0xDF) != 0)
                break;
        }

        if (i == sizeof(szPath) - 1)
        {
            lpFile -= 4;
            dwLength2 = lpFile - lpFileName;
            memcpy(szFileName, lpFileName, dwLength2);
            *(LPDWORD)&szFileName[dwLength2] = TAG4('_sc\\');
            dwLength2 += 4;
            while (szFileName[dwLength2++] = *++lpFile);
            if (GetFileAttributesA(szFileName) != -1)
                lpFileName = szFileName;
        }
    }

    return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

ASM void GetCharSurfaceOrig()
{
    __asm
    {
        cmp dword ptr [esp+4], 0;
        je  _GET_CHAR_HEIGHT_;
        sub esp, 18h;
        mov ax, word ptr [esp+28h];
        mov edx, 4D9C48h;
        jmp edx;

_GET_CHAR_HEIGHT_:
        mov edx, dword ptr [ecx+238Ch];
        mov eax, 4D9BC6h;
        jmp eax;
    }
}

UINT WINAPI CharFilter(UINT uChar)
{
    uChar = HIBYTE(uChar)|(LOBYTE(uChar) << 8);
    switch (uChar)
    {
        case '丵':
        case '噵': uChar = '　'; break;
        case '侽': uChar = '０'; break;
        case '侾': uChar = '１'; break;
        case '俀': uChar = '２'; break;
        case '俁': uChar = '３'; break;
        case '係': uChar = '４'; break;
        case '俆': uChar = '５'; break;
        case '俇': uChar = '６'; break;
        case '俈': uChar = '７'; break;
        case '俉': uChar = '８'; break;
        case '俋': uChar = '９'; break;
        case '亅': uChar = '－'; break;
        case '丏': uChar = '．'; break;
        case '丒': uChar = '·';  break;
    }

    return uChar;
}

BOOL WINAPI IsShiftJIS(UINT uChar);
enum CHAR_TYPE { ERR, SPACE, NUM, LALPHA, UALPHA };

NoInline int WINAPI IsHalfWidthAlpha(UINT uChar)
{
    uChar &= 0xFF;
    if (uChar == ' ')
        return SPACE;

    if (uChar >= '0' && uChar <= '9')
        return NUM;

    if (uChar >= 'A' && uChar <= 'Z')
        return UALPHA;

    if (uChar >= 'a' && uChar <= 'z')
        return LALPHA;

    return ERR;
}

ForceInline UINT WINAPI GetChar(UINT uChar)
{
    Int32 flag;
    uChar = HIBYTE(uChar)|(LOBYTE(uChar) << 8);

    if (uChar >= '０' && uChar <= '９')
    {
        uChar = uChar - '０' + '侽';
        flag = 0x80000000;
    }
    else if (uChar >= 'Ａ' && uChar <= 'Ｚ')
    {
        uChar = uChar - 'Ａ' + '俙';
        flag = 0x80000000;
    }
    else if (uChar >= 'ａ' && uChar <= 'ｚ')
    {
        uChar = uChar - 'ａ' + '倎';
        flag = 0x80000000;
    }
    else
    {
        TCharMap CharMap[] = 
        {
            { '’', '乫' }, 
        };

        flag = 0;
        for (DWORD i = 0; i != countof(CharMap); ++i)
            if (uChar == CharMap[i].Orig)
            {
                uChar = CharMap[i].Relpace;
                break;
            }
    }

    return HIBYTE(uChar)|(LOBYTE(uChar) << 8)|flag;
}

DWORD WINAPI GetCharSurface(PBYTE pbSurface, LONG lHeight, int iOffset, UINT uChar, DWORD dwColor, DWORD dwColor2)
{
    static HDC hDC;
    static MAT2 mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
    static BYTE byLumaTable[] =
    {
        0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x04,
        0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x08,
        0x08, 0x08, 0x09, 0x09, 0x09, 0x09, 0x0A, 0x0A, 0x0A, 0x0A,
        0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
        0x0C, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0E, 0x0E,
        0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0F, 0x0F, 0x0F, 0x0F,
        0x0F, 0x0F, 0x0F, 0x0F, 0x0F
    };

    int    x, y;
    BYTE   byBuffer[0x800], byOutline[0x400], *pbOutline, *pbBuffer;
    UINT   uCodePage, uWideChar, uHighByte;
    LONG   lfHeight, lfAlphaHeight;
    DWORD  dwSize, nBytesPerLine;
    LPVOID lpThis;
    GLYPHMETRICS gm;

//    static UINT uLastHighByte, uLastBlackBoxY;

    __asm mov lpThis, ecx;

    UNREFERENCED_PARAMETER(lfAlphaHeight);
    UNREFERENCED_PARAMETER(uHighByte);

    uChar = GetChar(uChar);

    if ((Int32)uChar < 0 || IsShiftJIS(uChar))
    {
        __asm
        {
            push dwColor2;
            push dwColor;
            push uChar;
            push iOffset;
            push lHeight;
            push pbSurface;
            mov  ecx, lpThis;
            call GetCharSurfaceOrig;
            mov  lfHeight, eax;
        }

        return lfHeight;
    }

    lfHeight = 0x11;
    if (pbSurface == NULL)
    {
        return lfHeight;
    }
    else if (hDC == NULL)
    {
        HFONT  hFont, hOldFont;
        int   iFontsAdded;
        DWORD iQuality, dwMajorVersion;
        LPSTR lpFaceName;
        //        OSVERSIONINFOA osInfo;

        UNREFERENCED_PARAMETER(iFontsAdded);

        hDC = CreateCompatibleDC(NULL);
        if (hDC == NULL)
            return 0;

        dwMajorVersion = GetVersion() & 0xFF;
        if (dwMajorVersion >= 5)
            iQuality = CLEARTYPE_QUALITY;
        else
            iQuality = ANTIALIASED_QUALITY;

        GetPrivateProfileStringA("Kanade", "FileName", "Font.ttf", (LPSTR)byBuffer, sizeof(byBuffer), ".\\Kanade.ini");
        if (AddFontResourceExA((LPSTR)byBuffer, FR_PRIVATE, NULL))
        {
            GetPrivateProfileStringA("Kanade", "FaceName", "黑体", (LPSTR)byBuffer, sizeof(byBuffer), ".\\Kanade.ini");
            lpFaceName = (LPSTR)byBuffer;
        }
        else
        {
            lpFaceName = "黑体";
        }
        hFont = CreateFontA(lfHeight,
            0, 0, 0,
            FW_NORMAL,
            0, 0, 0,
            GB2312_CHARSET,
            0, 0,
            iQuality,
            FIXED_PITCH,
            lpFaceName);
        hOldFont = (HFONT)SelectObject(hDC, hFont);
/*
        GetTextFaceA(hDC, sizeof(byOutline), (LPSTR)byOutline);
        if (StrCompareA((LPSTR)byOutline, lpFaceName))
        {
            DeleteObject(hFont);
            hFont = CreateFontA(lfHeight,
                0, 0, 0,
                FW_NORMAL,
                0, 0, 0,
                GB2312_CHARSET,
                0, 0,
                iQuality,
                FIXED_PITCH,
                "黑体");
            SelectObject(hDC, hFont);
        }
*/
    }

    if (uChar != '　' && uChar != 0xDFA3)   // '＿'
    {
        UINT ch;

        ch = GetChar(uChar);
        uCodePage = 936;
        MultiByteToWideChar(uCodePage, 0, (LPSTR)&ch, 2, (LPWSTR)&uWideChar, 1);
        dwSize = GetGlyphOutlineW(hDC,
            uWideChar,
            GGO_GRAY8_BITMAP,
            &gm,
            sizeof(byBuffer),
            byBuffer,
            &mat);
    }
    else
    {
        dwSize = -1;
    }

    memset(byOutline, 0, lfHeight * lfHeight);
    if (dwSize != -1)
    {
        nBytesPerLine = (gm.gmBlackBoxX + 3) & ~3;
        x = lfHeight - gm.gmBlackBoxY;
        y = lfHeight - gm.gmptGlyphOrigin.y - 2;
        if (y > x) y = x;
        if (y < 0) y = 0;

        pbBuffer  = byBuffer;
        pbOutline = byOutline + y * lfHeight + gm.gmptGlyphOrigin.x;

        for (UINT j = 0; j != gm.gmBlackBoxY; ++j)
        {
            for (UINT i = 0; i != nBytesPerLine; ++i)
            {
                BYTE c = *pbBuffer++;
                if (c && i < lfHeight)
                {
                    pbOutline[i] = byLumaTable[c];
                }
            }
            pbOutline += lfHeight;
        }
    }

    pbOutline = byOutline;
    pbSurface += (lHeight + (iOffset << 9)) * 2;
    for (int i = 0; i != lfHeight; ++i)
    {
        for (int j = 0; j != lfHeight; ++j)
        {
            DWORD c = *pbOutline++;
            *(LPWORD)(pbSurface + j * 2) =  c ? (WORD)((c << 0xC)|dwColor) : (WORD)dwColor;
        }
        pbSurface += 0x400;
    }

    return lfHeight;
}

BOOL WINAPI IsShiftJIS(UINT uChar)
{
    BYTE b;
    UNREFERENCED_PARAMETER(b);
#if defined(USE_ENCRYPT_TEXT)
    static WCHAR spec[] = 
    {
        TAG2('階'), TAG2('態'), TAG2('機'), TAG2('処'), TAG2('領'), TAG2('長'), TAG2('風'), TAG2('換'), TAG2('鏡'), TAG2('楽'), 
        TAG2('員'), TAG2('乗'), TAG2('開'), TAG2('別'), TAG2('単'), TAG2('間'), TAG2('俴'), TAG2('渓'), TAG2('宮'), TAG2('無'), 
        TAG2('時'), TAG2('歴'), TAG2('関'), TAG2('飛'), TAG2('亂'), TAG2('亃'), TAG2('恵'), TAG2('個'), TAG2('倎'), TAG2('們'), 
        TAG2('倕'), TAG2('倛'), TAG2('増'), TAG2('張'), TAG2('倝'), TAG2('棄'), TAG2('噴'), TAG2('強'), TAG2('電'), TAG2('倢'), 
        TAG2('倣'), TAG2('値'), TAG2('弾'), TAG2('陸'), TAG2('倰'), TAG2('倲'), TAG2('倳'), TAG2('頃'), TAG2('問'), TAG2('厳'), 
        TAG2('闇'), TAG2('対'), TAG2('帯'), TAG2('帷'), TAG2('殺'), TAG2('啵'), TAG2('悚'), TAG2('収'), TAG2('歆'), TAG2('瞌'), 
        TAG2('啫'), TAG2('猕'), TAG2('瞑'), TAG2('喋'), TAG2('啰'), TAG2('姫'), TAG2('嗒'), TAG2('岐'), TAG2('岖'), TAG2('猥'), 
        TAG2('瀚'), TAG2('娅'), TAG2('飓'), TAG2('喱'), TAG2('娆'), TAG2('璀'), TAG2('飙'), TAG2('锃'), TAG2('町'), TAG2('惘'), 
        TAG2('啾'), TAG2('绫'), TAG2('绮'), TAG2('敵'), TAG2('宕'), TAG2('喽'), TAG2('愣'), TAG2('喔'), TAG2('旮'), TAG2('喙'), 
        TAG2('嗷'), TAG2('饨'), TAG2('憬'), TAG2('缇'), TAG2('憧'), TAG2('淇'), TAG2('嗬'), TAG2('肓'), TAG2('嗦'), TAG2('渎'), 
        TAG2('撃'), TAG2('昴'), TAG2('柵'), TAG2('嗯'), TAG2('馀'), TAG2('炫'), TAG2('馄'), TAG2('迦'), TAG2('嗨'), TAG2('逅'), 
        TAG2('崽'), TAG2('嗤'), TAG2('胄'), TAG2('柩'), TAG2('嬉'), TAG2('煲'), TAG2('動'), TAG2('売'), TAG2('嘤'), TAG2('缭'), 
        TAG2('樵'), TAG2('镌'), TAG2('嘭'), TAG2('阖'), TAG2('勝'), TAG2('镖'), TAG2('噗'), TAG2('彷'), TAG2('噢'), TAG2('孢'), 
        TAG2('噜'), TAG2('噌'), TAG2('後'), TAG2('団'), TAG2('徕'), TAG2('邂'), TAG2('忏'), TAG2('変'), TAG2('囧'), TAG2('徨'), 
        TAG2('沐'), TAG2('珂'), TAG2('腌'), TAG2('扉'), TAG2('嚓'), TAG2('珀'), TAG2('嚯'), TAG2('掛'), TAG2('潇'), TAG2('镯'), 
        TAG2('犸'), TAG2('觑'), TAG2('盹'), TAG2('骛'), TAG2('镳'), TAG2('採'), TAG2('報'), TAG2('怏'), TAG2('狩'), TAG2('琪'), 
        TAG2('戻'), TAG2('汎'), TAG2('眸'), TAG2('铠'), TAG2('琥'), TAG2('廃'), TAG2('辄'), 
    };
    for (int i = 0, j = uChar; i != countof(spec); ++i)
        if ((WCHAR)j == spec[i])
            return False;
#else
    switch ((WChar)uChar)
    {
        case (WChar)TAG2('嘆'): case (WChar)TAG2('園'): case (WChar)TAG2('顯'): case (WChar)TAG2('丄'): case (WChar)TAG2('傾'): case (WChar)TAG2('圓'): case (WChar)TAG2('夾'): case (WChar)TAG2('階'): case (WChar)TAG2('預'): case (WChar)TAG2('丅'): 
        case (WChar)TAG2('態'): case (WChar)TAG2('滲'): case (WChar)TAG2('頑'): case (WChar)TAG2('機'): case (WChar)TAG2('鐲'): case (WChar)TAG2('頒'): case (WChar)TAG2('嘍'): case (WChar)TAG2('圖'): case (WChar)TAG2('婦'): case (WChar)TAG2('頓'): 
        case (WChar)TAG2('團'): case (WChar)TAG2('鐵'): case (WChar)TAG2('霧'): case (WChar)TAG2('丟'): case (WChar)TAG2('丠'): case (WChar)TAG2('侶'): case (WChar)TAG2('僅'): case (WChar)TAG2('際'): case (WChar)TAG2('頗'): case (WChar)TAG2('処'): 
        case (WChar)TAG2('嘔'): case (WChar)TAG2('婭'): case (WChar)TAG2('廔'): case (WChar)TAG2('業'): case (WChar)TAG2('淚'): case (WChar)TAG2('濱'): case (WChar)TAG2('鍵'): case (WChar)TAG2('領'): case (WChar)TAG2('嘕'): case (WChar)TAG2('銳'): 
        case (WChar)TAG2('闖'): case (WChar)TAG2('並'): case (WChar)TAG2('嘖'): case (WChar)TAG2('塊'): case (WChar)TAG2('慘'): case (WChar)TAG2('鐺'): case (WChar)TAG2('嘗'): case (WChar)TAG2('滾'): case (WChar)TAG2('長'): case (WChar)TAG2('闘'): 
        case (WChar)TAG2('隠'): case (WChar)TAG2('風'): case (WChar)TAG2('擬'): case (WChar)TAG2('橫'): case (WChar)TAG2('滿'): case (WChar)TAG2('廚'): case (WChar)TAG2('昇'): case (WChar)TAG2('銷'): case (WChar)TAG2('錘'): case (WChar)TAG2('孫'): 
        case (WChar)TAG2('極'): case (WChar)TAG2('凱'): case (WChar)TAG2('揚'): case (WChar)TAG2('關'): case (WChar)TAG2('換'): case (WChar)TAG2('決'): case (WChar)TAG2('淨'): case (WChar)TAG2('鉗'): case (WChar)TAG2('匯'): case (WChar)TAG2('廟'): 
        case (WChar)TAG2('擱'): case (WChar)TAG2('鍾'): case (WChar)TAG2('鏡'): case (WChar)TAG2('係'): case (WChar)TAG2('擲'): case (WChar)TAG2('楽'): case (WChar)TAG2('鏢'): case (WChar)TAG2('隨'): case (WChar)TAG2('員'): case (WChar)TAG2('塗'): 
        case (WChar)TAG2('慣'): case (WChar)TAG2('鑄'): case (WChar)TAG2('門'): case (WChar)TAG2('廢'): case (WChar)TAG2('擴'): case (WChar)TAG2('桿'): case (WChar)TAG2('險'): case (WChar)TAG2('颱'): case (WChar)TAG2('廣'): case (WChar)TAG2('錠'): 
        case (WChar)TAG2('闢'): case (WChar)TAG2('僕'): case (WChar)TAG2('奧'): case (WChar)TAG2('學'): case (WChar)TAG2('歐'): case (WChar)TAG2('閃'): case (WChar)TAG2('颳'): case (WChar)TAG2('奨'): case (WChar)TAG2('錢'): case (WChar)TAG2('淵'): 
        case (WChar)TAG2('嘮'): case (WChar)TAG2('奪'): case (WChar)TAG2('嶼'): case (WChar)TAG2('醃'): case (WChar)TAG2('颶'): case (WChar)TAG2('嶽'): case (WChar)TAG2('擺'): case (WChar)TAG2('隱'): case (WChar)TAG2('乗'): case (WChar)TAG2('淺'): 
        case (WChar)TAG2('錦'): case (WChar)TAG2('廬'): case (WChar)TAG2('慮'): case (WChar)TAG2('揮'): case (WChar)TAG2('沒'): case (WChar)TAG2('閉'): case (WChar)TAG2('區'): case (WChar)TAG2('奮'): case (WChar)TAG2('鉤'): case (WChar)TAG2('錨'): 
        case (WChar)TAG2('頭'): case (WChar)TAG2('擾'): case (WChar)TAG2('沖'): case (WChar)TAG2('開'): case (WChar)TAG2('隸'): case (WChar)TAG2('靈'): case (WChar)TAG2('錫'): case (WChar)TAG2('鑑'): case (WChar)TAG2('鋌'): case (WChar)TAG2('隻'): 
        case (WChar)TAG2('乧'): case (WChar)TAG2('慶'): case (WChar)TAG2('廳'): case (WChar)TAG2('別'): case (WChar)TAG2('錯'): case (WChar)TAG2('協'): case (WChar)TAG2('噁'): case (WChar)TAG2('閒'): case (WChar)TAG2('単'): case (WChar)TAG2('歡'): 
        case (WChar)TAG2('瀏'): case (WChar)TAG2('鈍'): case (WChar)TAG2('間'): case (WChar)TAG2('漢'): case (WChar)TAG2('焗'): case (WChar)TAG2('醜'): case (WChar)TAG2('鋒'): case (WChar)TAG2('飄'): case (WChar)TAG2('昳'): case (WChar)TAG2('歩'): 
        case (WChar)TAG2('鎖'): case (WChar)TAG2('頸'): case (WChar)TAG2('飆'): case (WChar)TAG2('條'): case (WChar)TAG2('瀕'): case (WChar)TAG2('錶'): case (WChar)TAG2('頻'): case (WChar)TAG2('塵'): case (WChar)TAG2('宮'): case (WChar)TAG2('雖'): 
        case (WChar)TAG2('憂'): case (WChar)TAG2('檔'): case (WChar)TAG2('鈔'): case (WChar)TAG2('鏽'): case (WChar)TAG2('無'): case (WChar)TAG2('鈕'): case (WChar)TAG2('靜'): case (WChar)TAG2('巔'): case (WChar)TAG2('損'): case (WChar)TAG2('減'): 
        case (WChar)TAG2('雙'): case (WChar)TAG2('歲'): case (WChar)TAG2('漲'): case (WChar)TAG2('價'): case (WChar)TAG2('巖'): case (WChar)TAG2('攔'): case (WChar)TAG2('時'): case (WChar)TAG2('況'): case (WChar)TAG2('卻'): case (WChar)TAG2('榮'): 
        case (WChar)TAG2('歴'): case (WChar)TAG2('雜'): case (WChar)TAG2('則'): case (WChar)TAG2('醫'): case (WChar)TAG2('島'): case (WChar)TAG2('恥'): case (WChar)TAG2('搖'): case (WChar)TAG2('渦'): case (WChar)TAG2('漸'): case (WChar)TAG2('醬'): 
        case (WChar)TAG2('閡'): case (WChar)TAG2('雞'): case (WChar)TAG2('憊'): case (WChar)TAG2('搗'): case (WChar)TAG2('歷'): case (WChar)TAG2('歸'): case (WChar)TAG2('顆'): case (WChar)TAG2('飛'): case (WChar)TAG2('儀'): case (WChar)TAG2('晉'): 
        case (WChar)TAG2('離'): case (WChar)TAG2('亂'): case (WChar)TAG2('妝'): case (WChar)TAG2('攜'): case (WChar)TAG2('測'): case (WChar)TAG2('銀'): case (WChar)TAG2('難'): case (WChar)TAG2('倆'): case (WChar)TAG2('憐'): case (WChar)TAG2('攝'): 
        case (WChar)TAG2('檢'): case (WChar)TAG2('鎧'): case (WChar)TAG2('憑'): case (WChar)TAG2('漿'): case (WChar)TAG2('億'): case (WChar)TAG2('墊'): case (WChar)TAG2('東'): case (WChar)TAG2('飢'): case (WChar)TAG2('倉'): case (WChar)TAG2('噠'): 
        case (WChar)TAG2('題'): case (WChar)TAG2('銅'): case (WChar)TAG2('額'): case (WChar)TAG2('個'): case (WChar)TAG2('鍊'): case (WChar)TAG2('鑰'): case (WChar)TAG2('拋'): case (WChar)TAG2('鋪'): case (WChar)TAG2('鍋'): case (WChar)TAG2('顏'): 
        case (WChar)TAG2('剛'): case (WChar)TAG2('悅'): case (WChar)TAG2('攤'): case (WChar)TAG2('鎮'): case (WChar)TAG2('鑲'): case (WChar)TAG2('飩'): case (WChar)TAG2('們'): case (WChar)TAG2('剝'): case (WChar)TAG2('晝'): case (WChar)TAG2('釀'): 
        case (WChar)TAG2('拝'): case (WChar)TAG2('檯'): case (WChar)TAG2('釁'): case (WChar)TAG2('雲'): case (WChar)TAG2('亞'): case (WChar)TAG2('倖'): case (WChar)TAG2('巻'): case (WChar)TAG2('渾'): case (WChar)TAG2('閱'): case (WChar)TAG2('陣'): 
        case (WChar)TAG2('増'): case (WChar)TAG2('張'): case (WChar)TAG2('攬'): case (WChar)TAG2('殘'): case (WChar)TAG2('飯'): case (WChar)TAG2('棄'): case (WChar)TAG2('噴'): case (WChar)TAG2('強'): case (WChar)TAG2('潑'): case (WChar)TAG2('鐘'): 
        case (WChar)TAG2('電'): case (WChar)TAG2('願'): case (WChar)TAG2('墜'): case (WChar)TAG2('構'): case (WChar)TAG2('飲'): case (WChar)TAG2('媽'): case (WChar)TAG2('搶'): case (WChar)TAG2('槍'): case (WChar)TAG2('殞'): case (WChar)TAG2('釋'): 
        case (WChar)TAG2('鑼'): case (WChar)TAG2('儘'): case (WChar)TAG2('噸'): case (WChar)TAG2('實'): case (WChar)TAG2('憤'): case (WChar)TAG2('潔'): case (WChar)TAG2('鑽'): case (WChar)TAG2('顛'): case (WChar)TAG2('寧'): case (WChar)TAG2('弾'): 
        case (WChar)TAG2('檸'): case (WChar)TAG2('陰'): case (WChar)TAG2('審'): case (WChar)TAG2('崗'): case (WChar)TAG2('鄰'): case (WChar)TAG2('倫'): case (WChar)TAG2('湊'): case (WChar)TAG2('陳'): case (WChar)TAG2('類'): case (WChar)TAG2('寫'): 
        case (WChar)TAG2('銘'): case (WChar)TAG2('鍛'): case (WChar)TAG2('陸'): case (WChar)TAG2('響'): case (WChar)TAG2('厭'): case (WChar)TAG2('寬'): case (WChar)TAG2('創'): case (WChar)TAG2('嚀'): case (WChar)TAG2('潛'): case (WChar)TAG2('鋼'): 
        case (WChar)TAG2('償'): case (WChar)TAG2('釘'): case (WChar)TAG2('頂'): case (WChar)TAG2('剷'): case (WChar)TAG2('彆'): case (WChar)TAG2('頃'): case (WChar)TAG2('飼'): case (WChar)TAG2('厲'): case (WChar)TAG2('問'): case (WChar)TAG2('陽'): 
        case (WChar)TAG2('飽'): case (WChar)TAG2('彈'): case (WChar)TAG2('項'): case (WChar)TAG2('飾'): case (WChar)TAG2('嚇'): case (WChar)TAG2('針'): case (WChar)TAG2('順'): case (WChar)TAG2('墮'): case (WChar)TAG2('寵'): case (WChar)TAG2('悪'): 
        case (WChar)TAG2('櫃'): case (WChar)TAG2('殭'): case (WChar)TAG2('潤'): case (WChar)TAG2('顧'): case (WChar)TAG2('寶'): case (WChar)TAG2('須'): case (WChar)TAG2('帥'): case (WChar)TAG2('憶'): case (WChar)TAG2('錄'): case (WChar)TAG2('闆'): 
        case (WChar)TAG2('鏈'): case (WChar)TAG2('闇'): case (WChar)TAG2('餃'): case (WChar)TAG2('劃'): case (WChar)TAG2('対'): case (WChar)TAG2('彎'): case (WChar)TAG2('槤'): case (WChar)TAG2('優'): case (WChar)TAG2('劄'): case (WChar)TAG2('墳'): 
        case (WChar)TAG2('悶'): case (WChar)TAG2('暈'): case (WChar)TAG2('釣'): case (WChar)TAG2('嚐'): case (WChar)TAG2('師'): case (WChar)TAG2('鉄'): case (WChar)TAG2('闊'): case (WChar)TAG2('偁'): case (WChar)TAG2('鐮'): case (WChar)TAG2('隊'): 
        case (WChar)TAG2('劇'): case (WChar)TAG2('敗'): case (WChar)TAG2('偄'): case (WChar)TAG2('參'): case (WChar)TAG2('啟'): case (WChar)TAG2('將'): case (WChar)TAG2('殺'): case (WChar)TAG2('灑'): case (WChar)TAG2('姊'): case (WChar)TAG2('嚕'): 
        case (WChar)TAG2('專'): case (WChar)TAG2('偆'): case (WChar)TAG2('尋'): case (WChar)TAG2('帳'): case (WChar)TAG2('殼'): case (WChar)TAG2('悚'): case (WChar)TAG2('偉'): case (WChar)TAG2('湧'): case (WChar)TAG2('啷'): case (WChar)TAG2('睽'): 
        case (WChar)TAG2('偊'): case (WChar)TAG2('儲'): case (WChar)TAG2('劍'): case (WChar)TAG2('對'): case (WChar)TAG2('恙'): case (WChar)TAG2('導'): case (WChar)TAG2('帶'): case (WChar)TAG2('毀'): case (WChar)TAG2('恣'): case (WChar)TAG2('瞌'): 
        case (WChar)TAG2('偍'): case (WChar)TAG2('偐'): case (WChar)TAG2('劑'): case (WChar)TAG2('彥'): case (WChar)TAG2('應'): case (WChar)TAG2('槳'): case (WChar)TAG2('洩'): case (WChar)TAG2('嗒'): case (WChar)TAG2('偒'): case (WChar)TAG2('棲'): 
        case (WChar)TAG2('湯'): case (WChar)TAG2('偔'): case (WChar)TAG2('偗'): case (WChar)TAG2('壇'): case (WChar)TAG2('惘'): case (WChar)TAG2('偙'): case (WChar)TAG2('尡'): case (WChar)TAG2('懕'): case (WChar)TAG2('啾'): case (WChar)TAG2('叢'): 
        case (WChar)TAG2('澆'): case (WChar)TAG2('獠'): case (WChar)TAG2('偝'): case (WChar)TAG2('敵'): case (WChar)TAG2('暢'): case (WChar)TAG2('兇'): case (WChar)TAG2('摯'): case (WChar)TAG2('偟'): case (WChar)TAG2('嚨'): case (WChar)TAG2('數'): 
        case (WChar)TAG2('樁'): case (WChar)TAG2('於'): case (WChar)TAG2('偡'): case (WChar)TAG2('樂'): case (WChar)TAG2('夥'): case (WChar)TAG2('幐'): case (WChar)TAG2('喔'): case (WChar)TAG2('偣'): case (WChar)TAG2('椆'): case (WChar)TAG2('楣'): 
        case (WChar)TAG2('兒'): case (WChar)TAG2('壓'): case (WChar)TAG2('惡'): case (WChar)TAG2('暫'): case (WChar)TAG2('偦'): case (WChar)TAG2('嚮'): case (WChar)TAG2('惢'): case (WChar)TAG2('櫥'): case (WChar)TAG2('偨'): case (WChar)TAG2('嘟'): 
        case (WChar)TAG2('憬'): case (WChar)TAG2('偩'): case (WChar)TAG2('喚'): case (WChar)TAG2('憧'): case (WChar)TAG2('淇'): case (WChar)TAG2('嚴'): case (WChar)TAG2('尷'): case (WChar)TAG2('惱'): case (WChar)TAG2('嗦'): case (WChar)TAG2('幟'): 
        case (WChar)TAG2('壞'): case (WChar)TAG2('從'): case (WChar)TAG2('撃'): case (WChar)TAG2('災'): case (WChar)TAG2('昴'): case (WChar)TAG2('偱'): case (WChar)TAG2('勁'): case (WChar)TAG2('幣'): case (WChar)TAG2('斉'): case (WChar)TAG2('柵'): 
        case (WChar)TAG2('嗯'): case (WChar)TAG2('炫'): case (WChar)TAG2('屍'): case (WChar)TAG2('樓'): case (WChar)TAG2('側'): case (WChar)TAG2('內'): case (WChar)TAG2('迦'): case (WChar)TAG2('烊'): case (WChar)TAG2('偵'): case (WChar)TAG2('兩'): 
        case (WChar)TAG2('嬌'): case (WChar)TAG2('喪'): case (WChar)TAG2('娛'): case (WChar)TAG2('準'): case (WChar)TAG2('標'): case (WChar)TAG2('嗨'): case (WChar)TAG2('逅'): case (WChar)TAG2('偺'): case (WChar)TAG2('喬'): case (WChar)TAG2('囂'): 
        case (WChar)TAG2('執'): case (WChar)TAG2('懱'): case (WChar)TAG2('偼'): case (WChar)TAG2('幫'): case (WChar)TAG2('復'): case (WChar)TAG2('懲'): case (WChar)TAG2('嗤'): case (WChar)TAG2('偽'): case (WChar)TAG2('呂'): case (WChar)TAG2('單'): 
        case (WChar)TAG2('捨'): case (WChar)TAG2('撐'): case (WChar)TAG2('溝'): case (WChar)TAG2('懶'): case (WChar)TAG2('樞'): case (WChar)TAG2('胄'): case (WChar)TAG2('佈'): case (WChar)TAG2('喲'): case (WChar)TAG2('壯'): case (WChar)TAG2('懷'): 
        case (WChar)TAG2('柩'): case (WChar)TAG2('懸'): case (WChar)TAG2('動'): case (WChar)TAG2('囉'): case (WChar)TAG2('層'): case (WChar)TAG2('樣'): case (WChar)TAG2('冊'): case (WChar)TAG2('堅'): case (WChar)TAG2('懺'): case (WChar)TAG2('捲'): 
        case (WChar)TAG2('曉'): case (WChar)TAG2('務'): case (WChar)TAG2('壷'): case (WChar)TAG2('幹'): case (WChar)TAG2('懼'): case (WChar)TAG2('渲'): case (WChar)TAG2('佔'): case (WChar)TAG2('堊'): case (WChar)TAG2('幾'): case (WChar)TAG2('壺'): 
        case (WChar)TAG2('徹'): case (WChar)TAG2('懾'): case (WChar)TAG2('斬'): case (WChar)TAG2('溫'): case (WChar)TAG2('勝'): case (WChar)TAG2('屬'): case (WChar)TAG2('戀'): case (WChar)TAG2('勞'): case (WChar)TAG2('広'): case (WChar)TAG2('欄'): 
        case (WChar)TAG2('壽'): case (WChar)TAG2('愛'): case (WChar)TAG2('噗'): case (WChar)TAG2('傑'): case (WChar)TAG2('柢'): case (WChar)TAG2('傒'): case (WChar)TAG2('勢'): case (WChar)TAG2('気'): case (WChar)TAG2('掃'): case (WChar)TAG2('孢'): 
        case (WChar)TAG2('斷'): case (WChar)TAG2('權'): case (WChar)TAG2('嗎'): case (WChar)TAG2('撫'): case (WChar)TAG2('噌'): case (WChar)TAG2('後'): case (WChar)TAG2('団'): case (WChar)TAG2('氣'): case (WChar)TAG2('濃'): case (WChar)TAG2('邂'): 
        case (WChar)TAG2('併'): case (WChar)TAG2('樸'): case (WChar)TAG2('備'): case (WChar)TAG2('変'): case (WChar)TAG2('撲'): case (WChar)TAG2('樹'): case (WChar)TAG2('沐'): case (WChar)TAG2('旀'): case (WChar)TAG2('嶇'): case (WChar)TAG2('楃'): 
        case (WChar)TAG2('滅'): case (WChar)TAG2('徵'): case (WChar)TAG2('沌'): case (WChar)TAG2('嗚'): case (WChar)TAG2('戦'): case (WChar)TAG2('為'): case (WChar)TAG2('扉'): case (WChar)TAG2('傟'): case (WChar)TAG2('掙'): case (WChar)TAG2('珀'): 
        case (WChar)TAG2('嬰'): case (WChar)TAG2('祀'): case (WChar)TAG2('勳'): case (WChar)TAG2('囲'): case (WChar)TAG2('庫'): case (WChar)TAG2('掛'): case (WChar)TAG2('撿'): case (WChar)TAG2('來'): case (WChar)TAG2('傢'): case (WChar)TAG2('擁'): 
        case (WChar)TAG2('勵'): case (WChar)TAG2('楊'): case (WChar)TAG2('祛'): case (WChar)TAG2('嬸'): case (WChar)TAG2('戰'): case (WChar)TAG2('勸'): case (WChar)TAG2('採'): case (WChar)TAG2('擇'): case (WChar)TAG2('曬'): case (WChar)TAG2('濕'): 
        case (WChar)TAG2('怦'): case (WChar)TAG2('傭'): case (WChar)TAG2('夠'): case (WChar)TAG2('戲'): case (WChar)TAG2('橋'): case (WChar)TAG2('報'): case (WChar)TAG2('夢'): case (WChar)TAG2('戶'): case (WChar)TAG2('擊'): case (WChar)TAG2('擋'): 
        case (WChar)TAG2('烏'): case (WChar)TAG2('凍'): case (WChar)TAG2('場'): case (WChar)TAG2('涼'): case (WChar)TAG2('漩'): case (WChar)TAG2('傳'): case (WChar)TAG2('狩'): case (WChar)TAG2('琪'): case (WChar)TAG2('國'): case (WChar)TAG2('戻'): 
        case (WChar)TAG2('書'): case (WChar)TAG2('汎'): case (WChar)TAG2('眸'): case (WChar)TAG2('債'): case (WChar)TAG2('圍'): case (WChar)TAG2('廁'): case (WChar)TAG2('擔'): case (WChar)TAG2('濟'): case (WChar)TAG2('潸'): case (WChar)TAG2('琥'): 
        case (WChar)TAG2('傷'): case (WChar)TAG2('橕'): case (WChar)TAG2('廃'): case (WChar)TAG2('濤'): case (WChar)TAG2('據'): case (WChar)TAG2('會'): case (WChar)TAG2('滯'): 
            return False;
    }
#endif

    uChar = HIBYTE(uChar)|(LOBYTE(uChar) << 8);
    if ((uChar >= 0x8140 && uChar <= 0x9F7E) || (uChar >= 0xE080 && uChar <= 0xEFFC))
        return True;

    return False;
}
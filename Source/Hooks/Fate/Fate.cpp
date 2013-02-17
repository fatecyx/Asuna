//#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(lib, "ucadec.lib")
#pragma comment(lib, "ucidec.lib")
#pragma comment(lib, "bass.lib")
#pragma comment(lib, "bass_aac.lib")

#include <Windows.h>
#include "Fate.h"
#include "SPI.h"
#include "my_common.h"

_MY_C_HEAD_
#include "LZMA/Alloc.h"
#include "LZMA/LzmaDec.h"
#include "LZMA/Lzma86.h"
_MY_C_TAIL_

HANDLE g_hHeap = 0;
DWORD  g_dwMaxDecBuffer = 0;
PBYTE  g_pbDecBuffer = NULL;
BOOL   g_bCtrlPress = FALSE;

VOID Init()
{
    int i;
    CHAR szPath[MAX_PATH];
    DWORD dwBaseAddress, dwOld;

    g_hHeap = GetProcessHeap();
    i = GetModuleFileNameA(NULL, szPath, sizeof(szPath));
    while (szPath[i] != '\\') --i;
    szPath[i] = 0;
    SetCurrentDirectoryA(szPath);
    g_pbDecBuffer = (PBYTE)HeapAlloc(g_hHeap, 0, 0);

    dwBaseAddress = (DWORD)GetModuleHandleA(0);
    if (dwBaseAddress == NULL)
        return;

    dwOld = *(LPDWORD(0x1013 + dwBaseAddress));
    if (dwOld == 0x623693)
    {
        PatchMemory(0, 0, func_fsn, countof(func_fsn), dwBaseAddress);
    }
    else if (dwOld == 0x67C6A3)
    {
        PatchMemory(0, 0, func_fha, countof(func_fha), dwBaseAddress);
    }
}

BOOL WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    BOOL ret;
    ret = PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);

    if (ret == FALSE)
    {
        Sleep(1);
    }
    else
    {
        switch (lpMsg->message)
        {
        case WM_KEYDOWN:
            switch (lpMsg->wParam)
            {
            case VK_CONTROL:
                g_bCtrlPress = TRUE;
                break;
            }
            break;

        case WM_KEYUP:
            switch (lpMsg->wParam)
            {
            case VK_CONTROL:
                g_bCtrlPress = FALSE;
                break;
            }
            break;
        }
    }

    return ret;
}

int WINAPI MyMultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar)
{
    int ret;

    ret = MultiByteToWideChar(CodePage, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, ++cchWideChar);

    if (lpWideCharStr)
    {
        for (int i = 0; i != cchWideChar; ++i)
        {
            if (lpWideCharStr[i] == '?')
            {
                lpWideCharStr[i] = 0x30FB;
            }
        }
    }

    return ret;
}

int WINAPI GetPluginInfo(int infono, LPSTR buf,int buflen)
{
    static char *szInfo[] = { "00AM", "Fate Package extract Plug-in 0.01", "*.*", "Fate Package" };

    switch (infono)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        return (int)lstrcpynA(buf, szInfo[infono], buflen);
    }

    return 0;
}

int WINAPI IsSupported(LPSTR filename, HANDLE hFile)
{
    LPDWORD lpdTag;

    if (((DWORD)hFile & 0xFFFF0000) == 0)
    {
        DWORD dwRead;

        ReadFile(hFile, &hFile, 4, &dwRead, NULL);
        lpdTag = (LPDWORD)&hFile;
    }
    else
    {
        lpdTag = (LPDWORD)hFile;
    }

    return *lpdTag == TAG4('Fate');
}

int WINAPI GetArchiveInfo(LPSTR buf, LONG len, UINT flag, HLOCAL *lphInf)
{
    int     ret;
    UInt64	outSize64;
    SizeT	inSize, outSize;
    HANDLE  hFile, hMap;
    PBYTE   pbFile, inBuffer, outBuffer;
    TUCXPHeader *pHeader;

    if (g_hHeap == 0)
    {
        Init();
    }

    ret = SPIERR_FILEREAD;
    do if (SPI_INPUT_DISK(flag) == TRUE)
    {
        hFile = CreateFileA(buf,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            ret = SPIERR_FILEREAD;
            break;
        }

        hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
        CloseHandle(hFile);
        if (hMap == NULL)
        {
            ret = SPIERR_FILEREAD;
            break;
        }

        pbFile = (PBYTE)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
        CloseHandle(hMap);
        if (pbFile == NULL)
        {
            ret = SPIERR_FILEREAD;
            break;
        }

        pHeader  = (TUCXPHeader *)pbFile;
        inSize   = pHeader->dwIndexSize;
        inBuffer = pbFile + pHeader->dwIndexOffset;

        Lzma86_GetUnpackSize(inBuffer, inSize, &outSize64);

        outSize = (SizeT)outSize64;
        outBuffer = (PBYTE)HeapAlloc(g_hHeap, 0, outSize);

        Lzma86_Decode(outBuffer, &outSize, inBuffer, &inSize);
        *lphInf = outBuffer;

        UnmapViewOfFile(pbFile);
        ret = S_OK;
    } while (0);

    return ret;
}

int WINAPI GetFile(LPSTR src, LONG len, LPSTR dest, UINT flag,
                   PROGRESSCALLBACK progressCallback, LONG lData)
{
    if (SPI_INPUT_DISK(flag) == FALSE || SPI_OUTPUT_MEM(flag) == FALSE)
    {
        return SPIERR_UNSUPPORTED;
    }

    int     ret;
    BOOL    bSuccess = FALSE, bEncoded = FALSE;
    SizeT	outSize;
    HANDLE  hFile, hMap;
    PBYTE   pbFile, outBuffer;
    FILE_TYPE FileType;

    hFile = CreateFileA(src,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return SPIERR_FILEREAD;
    }

    hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    CloseHandle(hFile);
    if (hMap == NULL)
    {
        return SPIERR_FILEREAD;
    }

    pbFile = (PBYTE)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
    CloseHandle(hMap);
    if (pbFile == NULL)
    {
        return SPIERR_FILEREAD;
    }

    outBuffer = pbFile + len;
    if (*(LPDWORD)(outBuffer) == 0x5D00)
    {
        LZMADecode(outBuffer, -1, &outBuffer, (LPDWORD)&outSize);
        FileType = CheckFileType(outBuffer);
    }
    else
    {
        FileType = CheckFileType(outBuffer);
        if (FileType != UCI && FileType != UCA)
        {
            outSize = *(LPDWORD)outBuffer;
            outBuffer += 4;
            FileType = IsAAC(outBuffer) ? AAC : IsM4A(outBuffer) ? M4A : UNKNOWN;
        }
    }

    do if (FileType == UCA)
    {
        PBYTE pbData;

        bSuccess = TRUE;
        if (!g_bCtrlPress && UCADecode(outBuffer, INT_MAX, (void **)&pbData, (int *)&outSize) >= 0)
        {
            outBuffer = (PBYTE)HeapAlloc(g_hHeap, 0, outSize);
            if (outBuffer)
            {
                memcpy(outBuffer, pbData, outSize);
                UCAFree(pbData);
                ret = SPI_OK;
            }
            else
            {
                ret = SPIERR_OUTOFMEMORY;
            }
        }
        else
        {
            outBuffer = NULL;
            ret = SPIERR_FILEREAD;
        }
    }
    else if (FileType == UCI)
    {
        int w, h, b, stride;
        PBYTE pbData;

        bSuccess = TRUE;
        if (UCIDecode(outBuffer, INT_MAX, (void **)&pbData, &stride, &w, &h, &b) >= 0)
        {
            PBYTE pbDest;
            TBitMapHeader header = { 'MB', 0, 0, 0x36, 0x28, {0, 0, 1, 0} };

            outSize = (w * b / 8 + (b == 0x18 ? (w & 3) : 0)) * h + sizeof(header);
            header.dwFileSize = outSize;
            header.BitMapInfoHeader.dwHeight = h;
            header.BitMapInfoHeader.dwWidth = w;
            header.BitMapInfoHeader.wBit = b;

            outBuffer = (PBYTE)HeapAlloc(g_hHeap, 0, outSize);
            if (outBuffer)
            {
                memcpy(outBuffer, &header, sizeof(header));

                pbDest = outBuffer + header.dwRawOffset;
                for(int i = h - 1; i >= 0; --i)
                {
                    DWORD dwSize = w * (b / 8);

                    memcpy(pbDest, pbData + i * stride, dwSize);
                    pbDest += dwSize;

                    if (b == 0x18)
                    {
                        memset(pbData, 0, w & 3);
                        pbDest += w & 3;
                    }
                }
                ret = SPI_OK;
            }
            else
            {
                ret = SPIERR_OUTOFMEMORY;
            }

            UCIFree(pbData);
        }
        else
        {
            outBuffer = NULL;
            ret = SPIERR_FILEREAD;
        }
    }
    else if (FileType == AAC || FileType == M4A)
    {
        HSTREAM hStream;
        DWORD dwDataSize;
        TWaveHeader *pWaveHeader;
        BASS_CHANNELINFO ChannelInfo;
        static BOOL bBassInit = FALSE;
        static TWaveHeader header =
        {
            'FFIR', 0x24, 'EVAW', ' tmf',
            0x10, WAVE_FORMAT_PCM, 2, 48000, 48000 * 4,
            4, 0x10, 'atad', 0,
        };

        if (bBassInit == FALSE)
        {
            bBassInit = TRUE;
            if (BASS_Init(0, 44100, 0, NULL, NULL) == FALSE)
                break;
        }

        hStream = IsAAC(outBuffer) ?
            BASS_AAC_StreamCreateFile(TRUE, outBuffer, 0, outSize, BASS_STREAM_DECODE) :
            BASS_MP4_StreamCreateFile(TRUE, outBuffer, 0, outSize, BASS_STREAM_DECODE);

        if (hStream == 0)
            break;

        if (BASS_ChannelGetInfo(hStream, &ChannelInfo) == TRUE)
        {
            dwDataSize = (DWORD)BASS_ChannelGetLength(hStream, BASS_POS_BYTE);
            if (dwDataSize != BASS_INVALID_POSITION)
            {
                outBuffer = (PBYTE)HeapAlloc(g_hHeap, 0, dwDataSize + sizeof(*pWaveHeader));
                if (outBuffer)
                {
                    pWaveHeader = (TWaveHeader *)outBuffer;
                    memcpy(pWaveHeader, &header, sizeof(header));

                    pWaveHeader->wChannels = (WORD)ChannelInfo.chans;
                    pWaveHeader->wBitsPerSample = (ChannelInfo.flags & BASS_SAMPLE_8BITS) ? 8 : 16;
                    pWaveHeader->wBlockAlign = (WORD)(ChannelInfo.chans * pWaveHeader->wBitsPerSample / 8);
                    pWaveHeader->dwSamplesPerSec = ChannelInfo.freq;
                    pWaveHeader->dwAvgBytesPerSec = ChannelInfo.freq * pWaveHeader->wBlockAlign;
                    pWaveHeader->dwDataSize = dwDataSize;
                    pWaveHeader->dwSize = dwDataSize + sizeof(*pWaveHeader) - 8;

                    BASS_ChannelGetData(hStream, outBuffer + sizeof(*pWaveHeader), dwDataSize);
                    bSuccess = TRUE;
                    ret = SPI_OK;
                }
                else
                {
                    ret = SPIERR_OUTOFMEMORY;
                }
            }
        }

        BASS_StreamFree(hStream);

    } while (0);

    if (bSuccess == FALSE)
    {
        PBYTE pbOutput = outBuffer;

        outBuffer = (PBYTE)HeapAlloc(g_hHeap, 0, outSize);
        if (outBuffer)
        {
            memcpy(outBuffer, pbOutput, outSize);
            ret = SPI_OK;
        }
        else
        {
            ret = SPIERR_OUTOFMEMORY;
        }
    }

    *(LPVOID *)dest = outBuffer;

    UnmapViewOfFile(pbFile);

    return ret;
}

int WINAPI LZMADecode(PBYTE inBuffer, DWORD inSize, PBYTE *outBuffer, LPDWORD outSize)
{
    int    ret;
    UInt64 outSize64;
    SizeT  unpackSize;

    Lzma86_GetUnpackSize(inBuffer, -1, &outSize64);

    unpackSize = (DWORD)outSize64;
    *outSize = unpackSize;

    if (unpackSize > g_dwMaxDecBuffer)
    {
        g_dwMaxDecBuffer = unpackSize;
        g_pbDecBuffer = (PBYTE)HeapReAlloc(g_hHeap, 0, g_pbDecBuffer, unpackSize);
    }

    inSize = -1;
    ret = Lzma86_Decode(g_pbDecBuffer, (SizeT *)outSize, inBuffer, (SizeT *)&inSize);
    *outBuffer = g_pbDecBuffer;

    return ret;
}

PBYTE pbWord = NULL;
WORD Filter[] =
{
	0x30FB, 0x266A, 0xEC6A,
};

HFONT WINAPI MyCreateFontIndirectA(LOGFONTA *lplf)
{
    LOGFONT lf = *lplf;

    if (pbWord)
    {
        WORD word;

        word = *(LPWORD)(pbWord + 8);
        pbWord = NULL;
        if (word)
        {
			int i;
			for (i = 0; i != countof(Filter); ++i)
				if (word == Filter[i])
					break;
			if (i == countof(Filter))
			{
				lstrcpyA(lf.lfFaceName, "ºÚÌå");
			}
        }
    }

    return CreateFontIndirectA(&lf);
}

static DWORD func = 0x530580;

ASM VOID WINAPI RenderAWord()
{
    __asm
    {
        push  ebx;
        mov   ebx, dword ptr [edx];
        mov   pbWord, ebx;
        mov   ebx, eax;
        call  func;
        mov   eax, dword ptr [ebx+70h];
        pop   ebx;
        ret;
    }
}
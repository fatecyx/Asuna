#if defined(MY_DEBUG)
    #pragma comment(linker,"/ENTRY:DllMain")
#endif

#if defined(MY_COMPILER_INTEL)
    #pragma warning(disable:1899)
#else
    #pragma warning(disable:627)
#endif

#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "PrincessLover.h"
#include <Windowsx.h>
#include "MyLibraryUser.cpp"
#include "LocaleEmulator.h"

#define HAVE_COMPRESS

OVERLOAD_CPP_NEW_WITH_HEAP(MemoryAllocator::GetGlobalHeap())

#if defined(HAVE_COMPRESS)
    #include "vorbishook.cpp"
//    #pragma comment(lib, "delayimp.lib")
#endif

#define pfReadFileName      0x470808
#define pfDecryptIndexName  0x470900
#define pfUncompress        0x4712F0
#define pfFindFile          0x473414
#define pfCreateMemStm      0x473270
#define pfDisplayBMP        0x4331A8
#define pfReadString        0x470808

#define DEFAULT_FONT_NAME "ºÚÌå"
#define _MAKE_WSTR(str) L##str
#define MAKE_WSTR(str) _MAKE_WSTR(str)

//DWORD  g_PeekMsgFalseCount;
PWCHAR g_pCharMap;
WCHAR  g_szFaceName[] = MAKE_WSTR(DEFAULT_FONT_NAME);

//SDelphiString g_DefaultFont = DELPHI_CONST_STRING(DEFAULT_FONT_NAME);
DELPHI_STRING g_SaveData = DELPHI_CONST_STRING("SaveDataChs\\");
DELPHI_STRING g_SaveData2 = DELPHI_CONST_STRING("SaveDataChs\\SaveData");
DELPHI_STRING g_ConfigPath = DELPHI_CONST_STRING("config_sc.txt");

#if !defined(LOCALE_EMULATOR_ONLY)

#if defined(HAVE_COMPRESS)

ASM ULONG STDCALL SetStreamSize(MEMORY_STREAM *pStream, Large_Integer Size)
{
    UNUSED_VARIABLE(pStream);
    UNUSED_VARIABLE(Size);
    INLINE_ASM
    {
        mov  eax, [esp+4];
        push [esp+0Ch];
        push [esp+0Ch];
        mov  edx, [eax];
        call [edx+4];
        ret 0Ch;
    }
}

ASM VOID STDCALL OldDisplayBMP(PVOID lpThis, Int32 StreamSize, MEMORY_STREAM *pStream)
{
    UNUSED_VARIABLE(lpThis);
    UNUSED_VARIABLE(StreamSize);
    UNUSED_VARIABLE(pStream);
    INLINE_ASM
    {
        mov  eax, [esp+4];
        mov  ecx, [esp+8];
        mov  edx, [esp+0Ch];
        push ebx;
        mov  ebx, pfDisplayBMP;
        call ebx;
        pop ebx;
        ret 0Ch;
    }
}

BOOL DecodeUCI(MEMORY_STREAM *pStream)
{
    UCIInfo uci;
    PBYTE pbBuffer, pbRaw;
    Int32 Stride;
    Large_Integer NewSize;
    SBitMapHeader header;

    if ((*(PULONG)pStream->pbBuffer & 0xFFFFFF) != TAG3('UCI'))
        return False;

    if (UCIDecodeEx(pStream->lpBuffer, pStream->Size, &uci, False) < 0)
        return False;

    InitBitmapHeader(&header, uci.Width, uci.Height, uci.BitsPerPixel, &Stride);
    NewSize.QuadPart = header.dwFileSize;
    SetStreamSize(pStream, NewSize);

    pbBuffer = pStream->pbBuffer;
    *(SBitMapHeader *)pbBuffer = header;

    pbBuffer += sizeof(header);
    pbBuffer += (uci.Height - 1) * Stride;
    pbRaw = uci.pbBuffer;

    for (LONG h = 0; h != uci.Height; ++h)
    {
        CopyMemory(pbBuffer, pbRaw, uci.Stride);
        pbBuffer -= Stride;
        pbRaw += uci.Stride;
    }

    UCIFreeEx(&uci);

    return True;
}

VOID DisplayBMP()
{
    PVOID lpThis;
    Int32 StreamSize;
    MEMORY_STREAM *pStream;

    INLINE_ASM
    {
        mov  lpThis, eax;
        mov  StreamSize, ecx;
        mov  pStream, edx;
    }

    DecodeUCI(pStream);
    return OldDisplayBMP(lpThis, pStream->Size, pStream);
}

LRESULT FASTCALL CompareExtensionWorkerA(PCChar pString1, Int32 Len1, PCChar pString2, Int32 Len2, MEMORY_STREAM *pStream)
{
    LOOP_ONCE
    {
        if (pStream->pbBuffer == NULL || pStream->Size < 8)
            break;

        ULONG v = *(PULONG)pStream->pbBuffer;

        if ((v & 0xFFFFFF) == TAG3('UCI'))
        {
            *(PULONG)pString1 = TAG4('.bmp');
        }
        else if ((v & 0xFFFFFF) == TAG3('UCA') || *(PULONG)(pStream->pbBuffer + 4) == TAG4('ftyp'))
        {
            *(PULONG)pString1 = TAG4('.ogg');
        }
        else
        {
            break;
        }

        return NO_ERROR;

    }

    if (pString1 == pString2 ||
        pString2 == NULL     ||
        pString1 == NULL     ||
        Len1 != 4            ||
        Len2 != 4)
    {
        return ~NO_ERROR;
    }

    Len1 = *(PULONG)pString1 & 0xDFDFDFFF;
    Len2 = *(PULONG)pString2 & 0xDFDFDFFF;

    return Len1 == Len2 ? NO_ERROR : ~NO_ERROR;
}

ASM VOID CompareExtensionA()
{
    INLINE_ASM
    {
/*
        mov pString1, eax;
        mov eax, [eax-4];
        mov Len1, eax;
        mov pString2, edx;
        mov eax, [edx-4];
        mov Len2, eax;
        mov pStream, esi;
*/
        push esi;
        push [edx-4];
        push edx;
        mov  ecx, eax;
        mov  edx, [eax-4];
        call CompareExtensionWorkerA;
        or   eax, eax;
        ret;
    }
}

ASM PUSHORT STDCALL OldFindFile(PVOID lpPackIndexData, PCChar pFileName)
{
    UNUSED_VARIABLE(lpPackIndexData);
    UNUSED_VARIABLE(pFileName);
    INLINE_ASM
    {
        mov  eax, [esp+4];
        mov  edx, [esp+8];
        mov  ecx, pfFindFile;
        call ecx;
        ret  8;
    }
}

PUSHORT FindFile()
{
    PCHAR   pFileName, pSuffix;
    Int32   Length, FileType;
    PUSHORT pFileIndex;
    PVOID  lpPackIndexData;
    enum EType { AUDIO, IMAGE };

    INLINE_ASM
    {
        mov pFileName, edx;
        mov lpPackIndexData, eax;
    }

    pFileIndex = OldFindFile(lpPackIndexData, pFileName);
    if (pFileIndex)
        return pFileIndex;

    if (pFileName == NULL)
        return NULL;

    Length = *(PInt32)(pFileName - 4);
    pSuffix = pFileName + Length - 4;
    if (*pSuffix != '.')
        return NULL;

    ULONG Ext;
    switch (*(PULONG)++pSuffix & 0xFFDFDFDF)
    {
        case TAG3('PNG'):
        case TAG3('BMP'):
        case TAG3('JPG'):
            FileType = IMAGE;
            break;

        case TAG3('WAV'):
        case TAG3('OGG'):
            FileType = AUDIO;
            break;

        default:
            return NULL;
    }

    Ext = *(PULONG)pSuffix;

    if (FileType == IMAGE)
    {
        *(PULONG)pSuffix = TAG3('uci');
        pFileIndex = OldFindFile(lpPackIndexData, pFileName);
    }
    else
    {
        *(PULONG)pSuffix = TAG3('uca');
        pFileIndex = OldFindFile(lpPackIndexData, pFileName);
        if (pFileIndex == NULL)
        {
            *(PULONG)pSuffix = TAG3('m4a');
            pFileIndex = OldFindFile(lpPackIndexData, pFileName);
        }
    }

    *(PULONG)pSuffix = Ext;

    return pFileIndex;
}

#endif // HAVE_COMPRESS

DWORD AnsiToUnicode(LPCSTR lpAnsiString, DWORD Length, LPWSTR lpUnicodeBuffer, DWORD BufferCount)
{
    UINT CodePage;

    if (lpAnsiString == NULL)
        return 0;

    CodePage = IsShiftJISString(lpAnsiString, Length) ? CP_SHIFTJIS : CP_GB2312;
    return MultiByteToWideChar(CodePage, 0, lpAnsiString, Length, lpUnicodeBuffer, BufferCount);
}

ULONG ChangeCodePage(ULONG SrcCP, ULONG DestCP, PCHAR pszString, ULONG Length)
{
    ULONG nChar;
    PWCHAR pString;

    if (Length == -1)
        Length = StrLengthA(pszString);

    if (Length == 0)
        return Length;

    nChar = (Length + 1) * 2;
    pString = (PWCHAR)AllocStack(nChar);

    nChar = MultiByteToWideChar(SrcCP, 0, pszString, Length, pString, nChar);
    FilterStringWithConvertTable(pString, nChar, g_pCharMap);
    return WideCharToMultiByte(DestCP, 0, pString, nChar, pszString, Length, 0, 0);
}

ASM MEMORY_STREAM* FASTCALL OldGameLoadFile(PVoid, PCHAR pszFileName)
{
    UNUSED_VARIABLE(pszFileName);
    ASM_DUMMY_AUTO();
}

MEMORY_STREAM* FASTCALL GameLoadFile(PVoid, PCHAR pszFileName)
{
    MEMORY_STREAM *pMemoryFile;

    INLINE_ASM
    {
        call OldGameLoadFile;
        mov  pMemoryFile, eax;
    }

    if (pMemoryFile == NULL ||
        pMemoryFile->Size < 2 ||
        *(PUSHORT)pMemoryFile->lpBuffer != BOM_UTF16_LE)
    {
        return pMemoryFile;
    }

    ULONG Extenstion = *(PULONG)findexta(pszFileName);
    if ((Extenstion & 0xDFFF)     != TAG2('.S') &&
        (Extenstion & 0xDFDFDFFF) != TAG4('.TXT') &&
        (Extenstion & 0xDFDFDFFF) != TAG4('.DAT'))
    {
        return pMemoryFile;
    }

    ULONG  Length;
    PWCHAR pScript;
/*
    if (*(PUSHORT)pMemoryFile->lpBuffer != BOM_UTF16_LE)
    {
        if ((Extenstion & 0xDFFF) != TAG2('.S'))
            return pMemoryFile;

        Length = MY_MIN(0x200, pMemoryFile->Size);
        if (!IsShiftJISString((PCHAR)pMemoryFile->lpBuffer, Length))
            return pMemoryFile;

        ChangeCodePage(CP_SHIFTJIS, CP_GB2312, (PCHAR)pMemoryFile->lpBuffer, pMemoryFile->Size);

        return pMemoryFile;
    }
*/
    LOOP_ONCE
    {
        Length = pMemoryFile->Size - 2;
        pScript = (PWCHAR)&pMemoryFile->pbBuffer[2];

        FilterStringWithConvertTable(pScript, -1, g_pCharMap);
        Nt_UnicodeToAnsi((PCHAR)(pScript - 1), pMemoryFile->MaxSize, pScript, Length / sizeof(WCHAR), &Length);
/*
        Length = WideCharToMultiByte(
                     CP_GB2312,
                     0,
                     pScript,
                     Length / 2,
                     (PCHAR)(pScript - 1),
                     pMemoryFile->MaxSize,
                     NULL,
                     NULL);
*/
        pMemoryFile->pbBuffer[Length] = 0;
        pMemoryFile->Size = Length;

    }

    return pMemoryFile;
}

ASM bool FASTCALL OldOpenVideo(PVoid pThis, PCHAR pszVideoFile)
{
    UNREFERENCED_PARAMETER(pThis);
    UNREFERENCED_PARAMETER(pszVideoFile);
    INLINE_ASM xchg eax, ecx;
    ASM_DUMMY_AUTO();
}

BOOL FASTCALL OpenVideoWorker(PVoid pThis, PCHAR pszVideoFile)
{
    BOOL  Result;
    PCHAR pszExtension;
    ULONG Extension;

    if (OldOpenVideo(pThis, pszVideoFile))
        return True;

    pszExtension = findexta(pszVideoFile);
    if (pszExtension[4] != 0)
        return False;

    Extension = *(PULONG)++pszExtension;
    switch (Extension & 0x00DFDFDF)
    {
        case TAG3('MPG'):
            Extension = _InterlockedExchange((PLong)pszExtension, TAG3('mkv'));
            break;

        default:
            return False;
    }

    Result = OldOpenVideo(pThis, pszVideoFile);
    if (!Result)
        *(PULONG)pszExtension = Extension;

    return Result;
}

ASM bool FASTCALL OpenVideo(PVoid pThis, PCHAR pszVideoFile)
{
    UNREFERENCED_PARAMETER(pThis);
    UNREFERENCED_PARAMETER(pszVideoFile);

    INLINE_ASM
    {
        xchg eax, ecx;
        jmp OpenVideoWorker;
    }
}

ULONG CRC(PCChar pszString, ULONG Length)
{
    ULONG Crc;

    Crc = 0;
    for (ULONG i = 0; Length; --Length)
    {
        ULONG c = *(PBYTE)pszString++;
        BREAK_IF(c == 0);
        Crc += c * ((++i ^ 0xE7) & 0xFF);
    }

    return Crc;
}

ASM VOID FASTCALL OldReadString(MEMORY_STREAM *pStream, PCHAR *ppString)
{
    UNREFERENCED_PARAMETER(pStream);
    UNREFERENCED_PARAMETER(ppString);
    INLINE_ASM
    {
        xchg eax, ecx;
    }

    ASM_DUMMY_AUTO();
}

VOID FASTCALL ReadString(PVOID, PCHAR *ppString)
{
    MEMORY_STREAM *pStream;
    DELPHI_STRING *pString;

    INLINE_ASM mov pStream, eax;

    OldReadString(pStream, ppString);
    if (*ppString == NULL)
        return;

    pString = (DELPHI_STRING *)((ULONG_PTR)*ppString - 8);
    if (IsShiftJISString(pString->Buffer, pString->Length))
        ChangeCodePage(CP_SHIFTJIS, CP_GB2312, pString->Buffer, pString->Length);
}

ASM bool FASTCALL OldLoadSave(PVOID Zero, PCHAR pszSaveFile, PVOID pThis)
{
    UNREFERENCED_PARAMETER(Zero);
    UNREFERENCED_PARAMETER(pszSaveFile);
    UNREFERENCED_PARAMETER(pThis);
    INLINE_ASM
    {
        pop  eax;           // 1
        xchg [esp], eax;    // 3
    }

    ASM_DUMMY_AUTO();
}

BOOL FASTCALL LoadSave(PVOID Zero, PCHAR pszSaveFile)
{
    BOOL    Result;
    PVOID   pThis;

    INLINE_ASM mov pThis, eax;

    MEMORY_FUNCTION_PATCH f[] = { JUMP, 0x70808, ReadString, 0x01, (PBYTE)OldReadString + 1 };
    HMODULE hModule = Nt_GetExeModuleHandle();
    Nt_PatchMemory(NULL, 0, f, countof(f), hModule);
    Result = OldLoadSave(Zero, pszSaveFile, pThis);
    Nt_RestoreMemory(NULL, 0, f, countof(f), hModule);

    return Result;
}

VOID ConvertFileName()
{
    ULONG  StrLength;
    PCHAR  *ppStringBuffer, pString;

    INLINE_ASM
    {
        mov  ppStringBuffer, edx;
        mov  ecx, pfReadFileName;
        call ecx;
        mov  StrLength, eax;
    }

    if (ppStringBuffer == NULL)
        return;

    pString = *ppStringBuffer;
    if (pString == NULL)
        return;

    if (!IsShiftJISString(pString, StrLength))
        return;

    ChangeCodePage(CP_SHIFTJIS, CP_GB2312, pString, StrLength);
}

VOID STDCALL ConvertPathInIndex(PCHAR *ppString)
{
    PCHAR  pString;
    ULONG Length;

    INLINE_ASM
    {
        push ppString;
        mov  ebx, pfDecryptIndexName;
        call ebx;
    }

    if (ppString == NULL)
        return;

    pString = *ppString;
    if (pString == NULL)
        return;

    Length = *(PULONG)(pString - 4);
    if (!IsShiftJISString(pString, Length))
        return;

    ChangeCodePage(CP_SHIFTJIS, CP_GB2312, pString, Length);
}

ULONG GetStringSubIndex(PCChar pszString, Int32 Length, ULONG MaxIndex)
{
    if (MaxIndex == 0)
        return 0;

    ULONG Hash = 0;

    for (Int32 i = 0; i != Length; ++i)
    {
        ULONG b = *(PBYTE)pszString++;
        if (b == 0)
            break;

        Hash += b * ((i + 1) & 0xFF);
    }

    return Hash % MaxIndex;
}

ULONG GetSubTalbeIndex()
{
    PCHAR pString;
    ULONG MaxIndex, Length;

    INLINE_ASM
    {
        mov pString, edx;
        mov eax, [eax+4];
        mov MaxIndex, eax;
    }

    if (pString == NULL)
        return 0;

    Length = *(PULONG)(pString - 4);
    if (IsShiftJISString(pString, Length))
    {
        ChangeCodePage(CP_SHIFTJIS, CP_GB2312, pString, Length);
    }

    return GetStringSubIndex(pString, Length, MaxIndex);
}

/*
00422DB6
Parse script
 */

MEMORY_STREAM* RegenerateHashTable()
{
    ULONG         FileNum, SubTableNum;
    MY_PACK_INDEX  *pIndex, *pPackIndex;
    MEMORY_STREAM *pStream;

    INLINE_ASM
    {
        mov  ecx, pfUncompress;
        call ecx;
        mov  pStream, eax;
        mov  eax, [ebx+4h];
        mov  SubTableNum, eax;
        mov  eax, [ebx+14h];
        mov  FileNum, eax;
    }

    if (pStream == NULL)
        return pStream;

    MemoryAllocator   m;
    pbool  pMaskConverted;
    PBYTE  pbBuffer, pbEnd;

    pMaskConverted = (pbool)m.Alloc(FileNum);
    if (pMaskConverted == NULL)
        return pStream;

    pPackIndex = (MY_PACK_INDEX *)m.Alloc(FileNum * sizeof(*pPackIndex));
    if (pPackIndex == NULL)
    {
        m.Free(pMaskConverted);
        return pStream;
    }

    pIndex   = pPackIndex;
    pbBuffer = pStream->pbBuffer;
    pbEnd    = pbBuffer + pStream->Size;
    for (ULONG n = 0; n != FileNum && pbBuffer < pbEnd; )
    {
        UInt16 Len, Count;
        ULONG nChar;

        Count = *(PUSHORT)pbBuffer;
        pbBuffer += 2;
        for (ULONG i = 0; i != Count; ++i)
        {
            Len = *(PUSHORT)pbBuffer;
            pbBuffer += 2;
//            CodePage = IsShiftJISString((PChar)pbBuffer, Len) ? CP_SHIFTJIS : CP_GB2312;
//            nChar = MultiByteToWideChar(CodePage, 0, (LPCSTR)pbBuffer, Len, pIndex->Name, countof(pIndex->Name));
            nChar = AnsiToUnicode((LPCSTR)pbBuffer, Len, pIndex->Name, countof(pIndex->Name));
            pIndex->Name[nChar] = 0;
            FilterStringWithConvertTable(pIndex->Name, nChar, g_pCharMap);
            pbBuffer += Len;
            pIndex->Offset = *(PLarge_Integer)pbBuffer;
            pbBuffer += 8;
            pIndex->crc = *(PULONG)pbBuffer;
            pbBuffer += 4;

            ++pIndex;
            ++n;
        }
    }

    ZeroMemory(pMaskConverted, FileNum);
    pbBuffer = pStream->pbBuffer;
    for (ULONG i = 0; i != SubTableNum && pbBuffer < pbEnd; ++i)
    {
        PBYTE pbOutput;
        ULONG Count;
        CHAR  szFile[MAX_NTPATH];

        Count = 0;
        pbOutput = pbBuffer + 2;
        pIndex = pPackIndex;
        for (ULONG j = 0; j != FileNum; ++j, ++pIndex)
        {
            ULONG Len;

            if (pMaskConverted[j])
                continue;

//            Len = WideCharToMultiByte(CP_GB2312, 0, pIndex->Name, -1, szFile, sizeof(szFile), 0, 0) - 1;
            Nt_UnicodeToAnsi(szFile, countof(szFile), pIndex->Name, -1, &Len);
            if(GetStringSubIndex(szFile, Len, SubTableNum) != i)
                continue;

            pMaskConverted[j] = true;
            ++Count;

            *(PUSHORT)pbOutput = Len;       // name len
            pbOutput += 2;
            memcpy(pbOutput, szFile, Len);  // name
            pbOutput += Len;
            *(PLarge_Integer)pbOutput = pIndex->Offset;     // offset
            pbOutput += 8;
            *(PULONG)pbOutput = CRC(szFile, Len);
            pbOutput += 4;
        }

        *(PUSHORT)pbBuffer = Count;
        pbBuffer = pbOutput;
    }

    for (ULONG i = 0; i != FileNum; ++i)
    {
        *(PUSHORT)pbBuffer = i;
        pbBuffer += 2;
    }

    m.Free(pMaskConverted);
    m.Free(pPackIndex);

    return pStream;
}

HANDLE
WINAPI
MyCreateFileA(
    LPSTR                   lpFileName,
    ULONG                   dwDesiredAccess,
    ULONG                   dwShareMode,
    LPSECURITY_ATTRIBUTES   lpSecurityAttributes,
    ULONG                   dwCreationDisposition,
    ULONG                   dwFlagsAndAttributes,
    HANDLE                  hTemplateFile
)
{
    WCHAR       szFileName[MAX_NTPATH], *pszFileName;
    ULONG       Length;
    HANDLE      FileHandle;
    NTSTATUS    Status;

    UNREFERENCED_PARAMETER(lpSecurityAttributes);
    UNREFERENCED_PARAMETER(dwCreationDisposition);
    UNREFERENCED_PARAMETER(dwFlagsAndAttributes);
    UNREFERENCED_PARAMETER(hTemplateFile);

    pszFileName = szFileName;
    LOOP_ONCE
    {
//        Length = MultiByteToWideChar(CP_ACP, 0, lpFileName, -1, szFileName, countof(szFileName));
//        --Length;
        Nt_AnsiToUnicode(szFileName, countof(szFileName), lpFileName, -1, &Length);
        Length /= sizeof(WCHAR);

        if (Length < 6 ||
            szFileName[Length - 5] != L'.' ||
            (*(PUInt64)&szFileName[Length - 4] & 0xFFDFFFDFFFDFFFDF) != TAG4W('PACK') ||
            Nt_GetFileAttributes(szFileName) != -1)
        {
            break;
        }

        pszFileName = findnamew(szFileName);
        if (Nt_GetFileAttributes(pszFileName) != -1)
            break;

        Length -= 5;
        *(PUInt64)(szFileName + Length + 0) = TAG4W('_sc.');
        *(PUInt64)(szFileName + Length + 4) = TAG4W('pack');
        szFileName[Length + 8] = 0;

        if (Nt_GetFileAttributes(szFileName) != -1)
        {
            pszFileName = szFileName;
        }

    }

    Status = CNtFileDisk::Open(&FileHandle, pszFileName, dwShareMode, dwDesiredAccess);
    return NT_SUCCESS(Status) ? FileHandle : INVALID_HANDLE_VALUE;
//    return CreateFileW(pszFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

BOOL WINAPI MyFindClose(HANDLE FindFileHandle)
{
    return Nt_FindClose(FindFileHandle);
}

HANDLE WINAPI MyFindFirstFileA(LPSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
    ULONG Length;
    WCHAR  szFileName[MAX_NTPATH], *pszFileName;
    HANDLE hFind;
    WIN32_FIND_DATAW wfd;

//    Length = MultiByteToWideChar(CP_ACP, 0, lpFileName, -1, szFileName, countof(szFileName));
    Nt_AnsiToUnicode(szFileName, countof(szFileName), lpFileName, -1, &Length);
    Length /= sizeof(WCHAR);
    hFind = Nt_FindFirstFile(szFileName, &wfd);
    if (hFind == INVALID_HANDLE_VALUE) LOOP_ONCE
    {
//        --Length;
        if (Length < 6)
            break;
        if (szFileName[Length - 5] != '.')
            break;
        if ((*(PUInt64)&szFileName[Length - 4] & 0xFFDFFFDFFFDFFFDF) != TAG4W('PACK'))
            break;

        pszFileName = findnamew(szFileName);
        hFind = Nt_FindFirstFile(pszFileName, &wfd);
        if (hFind != INVALID_HANDLE_VALUE)
            break;

        Length -= 5;
        *(PUInt64)(szFileName + Length + 0) = TAG4W('_sc.');
        *(PUInt64)(szFileName + Length + 4) = TAG4W('pack');
        szFileName[Length + 8] = 0;

        hFind = Nt_FindFirstFile(szFileName, &wfd);
        if (hFind != INVALID_HANDLE_VALUE)
            break;

        hFind = Nt_FindFirstFile(pszFileName, &wfd);

    }

    if (hFind != INVALID_HANDLE_VALUE)
    {
        lpFindFileData->dwFileAttributes = wfd.dwFileAttributes;
        lpFindFileData->ftCreationTime   = wfd.ftCreationTime;
        lpFindFileData->ftLastAccessTime = wfd.ftLastAccessTime;
        lpFindFileData->ftLastWriteTime  = wfd.ftLastWriteTime;
        lpFindFileData->nFileSizeHigh    = wfd.nFileSizeHigh;
        lpFindFileData->nFileSizeLow     = wfd.nFileSizeLow;
        lpFindFileData->dwReserved0      = wfd.dwReserved0;
        lpFindFileData->dwReserved1      = wfd.dwReserved1;
//        WideCharToMultiByte(CP_ACP, 0, wfd.cFileName, -1, lpFindFileData->cFileName, sizeof(lpFindFileData->cFileName), 0, 0);
        Nt_UnicodeToAnsi(lpFindFileData->cFileName, sizeof(lpFindFileData->cFileName), wfd.cFileName);
    }

    return hFind;
}

VOID OnKeyUp(HWND hWnd, UINT VirtualKey, BOOL fDown, int cRepeat, UINT flags)
{
    CHOOSEFONTW choosefont;
    LOGFONTW logfont;

    UNUSED_VARIABLE(fDown);
    UNUSED_VARIABLE(cRepeat);
    UNUSED_VARIABLE(flags);

    switch (VirtualKey)
    {
        case VK_F1:
            ZeroMemory(&logfont, sizeof(logfont));
            CopyStruct(logfont.lfFaceName, g_szFaceName, sizeof(g_szFaceName));
            logfont.lfWidth = 24;
            ZeroMemory(&choosefont, sizeof(choosefont));
            choosefont.lStructSize = sizeof(choosefont);
            choosefont.lpLogFont   = &logfont;
            choosefont.hwndOwner   = hWnd;
            choosefont.Flags       = CF_BOTH|CF_TTONLY|CF_INITTOLOGFONTSTRUCT|CF_INACTIVEFONTS;
            if (ChooseFontW(&choosefont))
            {
                CopyStruct(g_szFaceName, logfont.lfFaceName, sizeof(g_szFaceName));
            }
            break;
    }
}

/*
BOOL WINAPI MyPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    BOOL bResult = PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);

    if (!bResult)
    {
        SleepEx(1, FALSE);
    }
    if (bResult)
    {
        switch (lpMsg->message)
        {
            case WM_KEYUP:
                HANDLE_WM_KEYUP(hWnd, lpMsg->wParam, lpMsg->lParam, OnKeyUp);
                break;
        }
    }
    return bResult;
}
*/

HFONT WINAPI MyCreateFontIndirectA2(LOGFONTA *lplf)
{
    LOGFONTW lf;

    CopyStruct(&lf, lplf, GetStructMemberOffset(LOGFONTA, lfHeight, lfFaceName));

    lf.lfCharSet = GB2312_CHARSET;

#if 1
    if (IsShiftJISString(lplf->lfFaceName, -1))
    {
        CopyStruct(lf.lfFaceName, g_szFaceName, sizeof(g_szFaceName));
    }
    else
    {
//        MultiByteToWideChar(CP_ACP, 0, lplf->lfFaceName, sizeof(lplf->lfFaceName), lf.lfFaceName, countof(lf.lfFaceName));
        Nt_AnsiToUnicode(lf.lfFaceName, countof(lf.lfFaceName), lplf->lfFaceName, countof(lplf->lfFaceName));
    }
#else
    AnsiToUnicode(lplf->lfFaceName, sizeof(lplf->lfFaceName), lf.lfFaceName, countof(lf.lfFaceName));
#endif

    return CreateFontIndirectW(&lf);
}

int WINAPI MyDrawTextA(HDC hDC, LPCSTR lpchText, int cchText, LPRECT lprc, UINT format)
{
    HFONT hFont;
    LOGFONTW lf;

    hFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
    GetObjectW(hFont, sizeof(lf), &lf);

    return DrawTextA(hDC, lpchText, cchText, lprc, format);
}

BOOL WINAPI MyExtTextOutA(HDC hDC, int X, int Y, UINT fuOptions, CONST RECT* lprc, LPCSTR lpString, UINT cbCount, CONST INT* lpDx)
{
    BOOL    Result;
    WCHAR   c, ch[0x400];
    ULONG   CodePage;
    HFONT   hFont, hFontOld;

    hFont       = NULL;
    hFontOld    = NULL;
    CodePage    = CP_GB2312;
    if (cbCount > 2 && IsShiftJISString((PCHAR)lpString, cbCount))
    {
        CodePage = CP_SHIFTJIS;
        goto MBYTE_TO_WCHAR;
    }
    else if (cbCount == 2)
    {
        c = *(PWCHAR)lpString;
        switch (c)
        {
            case (SWAPCHAR('¡Ñ')):
//                c = SWAPCHAR('ô');
                ch[0] = 0x266A;
                break;
/*
            case SWAPCHAR('¡÷'):
                c = SWAPCHAR('¢');
                break;

            case SWAPCHAR('¡õ'):
                c = SWAPCHAR(' ');
                break;

            case SWAPCHAR('¡ð'):
                c = SWAPCHAR('›');
                break;
*/
            default:
//                if (IsShiftJISChar(SWAPCHAR(c)))
//                    CodePage = CP_SHIFTJIS;

                goto MBYTE_TO_WCHAR;
        }

        hFont = DuplicateFontW(hDC, SHIFTJIS_CHARSET);
        if (hFont != NULL)
        {
            hFontOld = (HFONT)SelectObject(hDC, hFont);
            if (hFontOld == NULL)
            {
                DeleteObject(hFont);
                hFont = NULL;
            }
        }

        cbCount = 1;
        goto SKIP_CONV;
    }

MBYTE_TO_WCHAR:
    cbCount = MultiByteToWideChar(CodePage, 0, lpString, cbCount, ch, countof(ch));

SKIP_CONV:
    Result = ExtTextOutW(hDC, X, Y, fuOptions, lprc, ch, cbCount, lpDx);

    if (hFont != NULL)
    {
        SelectObject(hDC, hFontOld);
        DeleteObject(hFont);
    }

    return Result;
}

int WINAPI GameMyEnumFontFamiliesExA(HDC hdc, LPLOGFONTA lpLogfont, FONTENUMPROCA lpProc, LPARAM lParam, ULONG dwFlags)
{
    lpLogfont->lfCharSet = GB2312_CHARSET;
    return EnumFontFamiliesExA(hdc, lpLogfont, lpProc, lParam, dwFlags);
}

#if defined(HAVE_COMPRESS)

HANDLE hEvent;
DWORD  dwThreadId;

enum
{
    WM_APP_MSG_FIRST = WM_APP + 1,

    WM_APP_AUDIO_OPEN = WM_APP_MSG_FIRST,
    WM_APP_AUDIO_READ,
    WM_APP_AUDIO_CLEAR,

    WM_APP_MSG_LAST,
};

typedef struct
{
    HANDLE  hEvent;
    ULONG_PTR Result;
} SThreadParamBase;

typedef struct
{
    SThreadParamBase Base;
    PVOID f;
    OggVorbis_File *vf;
    PCHAR initial;
    Long ibytes;
    ov_callbacks callbacks;
} SThreadParamAudioOpen;

typedef struct
{
    SThreadParamBase Base;
    OggVorbis_File *vf;
    char *buffer;
    int   length;
    int   bigendianp;
    int   word;
    int   sgned;
    int  *bitstream;
} SThreadParamAudioRead;

typedef struct
{
    SThreadParamBase Base;
    OggVorbis_File *vf;
} SThreadParamAduioClear;

DWORD WINAPI DecodeAudioThread(PVOID lpParam)
{
    MSG msg;
    SThreadParamAudioOpen *pAudioOpen;
    SThreadParamAudioRead *pAudioRead;
    SThreadParamAduioClear *pAudioClear;

    PeekMessageW(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
    SetEvent((HANDLE)lpParam);

    while ((LONG)GetMessageW(&msg, NULL, WM_APP_MSG_FIRST, WM_APP_MSG_LAST) > 0)
    {
        switch (msg.message)
        {
            case WM_APP_AUDIO_OPEN:
                pAudioOpen = (SThreadParamAudioOpen *)msg.lParam;
                pAudioOpen->Base.Result =
                    my_ov_open_callbacks(
                        pAudioOpen->f,
                        pAudioOpen->vf,
                        pAudioOpen->initial,
                        pAudioOpen->ibytes,
                        pAudioOpen->callbacks);

                SetEvent(pAudioOpen->Base.hEvent);
                break;

            case WM_APP_AUDIO_READ:
                pAudioRead = (SThreadParamAudioRead *)msg.lParam;
                pAudioRead->Base.Result = my_ov_read(
                                              pAudioRead->vf,
                                              pAudioRead->buffer,
                                              pAudioRead->length,
                                              pAudioRead->bigendianp,
                                              pAudioRead->word,
                                              pAudioRead->sgned,
                                              pAudioRead->bitstream);

                SetEvent(pAudioRead->Base.hEvent);
                break;

            case WM_APP_AUDIO_CLEAR:
                pAudioClear = (SThreadParamAduioClear *)msg.lParam;
                pAudioClear->Base.Result = my_ov_clear(pAudioClear->vf);

                SetEvent(pAudioClear->Base.hEvent);
                break;
        }
    }

    return 0;
}

// [[esi+C]+8]+34+50+C

// [[[[[eax+30]+44]+30]+30]]+1c7c

ASM
int
CDECL
hook_ov_open_callbacks(
    PVOID          f,
    OggVorbis_File *vf,
    PCHAR           initial,
    Long            ibytes,
    ov_callbacks    callbacks
)
{
    UNUSED_VARIABLE(f);
    UNUSED_VARIABLE(vf);
    UNUSED_VARIABLE(initial);
    UNUSED_VARIABLE(ibytes);
    UNUSED_VARIABLE(callbacks);
    INLINE_ASM
    {
        finit;
        jmp my_ov_open_callbacks;
    }
/*
    INLINE_ASM finit;
    return my_ov_open_callbacks(f, vf, initial, ibytes, callbacks);

    if (dwThreadId == 0)
    {
        HANDLE hThread;

        if (hEvent == NULL)
        {
            hEvent = CreateEventW(0, False, False, NULL);
            if (hEvent == NULL)
                return OV_FALSE;
        }

        hThread = CreateThread(0, 0, DecodeAudioThread, (LPVoid)hEvent, 0, &dwThreadId);
        if (hThread == NULL)
            return OV_FALSE;

        CloseHandle(hThread);
        WaitForSingleObjectEx(hEvent, INFINITE, False);
    }

    SThreadParamAudioOpen OpenAudioParam = { hEvent, 0, f, vf, initial, ibytes, callbacks };

    if (!PostThreadMessageW(dwThreadId, WM_APP_AUDIO_OPEN, 0, (LPARAM)&OpenAudioParam))
        return OV_FALSE;

    WaitForSingleObjectEx(OpenAudioParam.Base.hEvent, INFINITE, False);

    return OpenAudioParam.Base.Result;
*/
}

long
CDECL
hook_ov_read(
    OggVorbis_File *vf,
    char           *buffer,
    int             length,
    int             bigendianp,
    int             word,
    int             sgned,
    int            *bitstream
)
{
//    if (IS_OGG_HOOKED(vf) && vf->vi->channels == 1)
        length = min(length, 0x800);

    length = my_ov_read(vf, buffer, length, bigendianp, word, sgned, bitstream);

    return length;
/*
    SThreadParamAudioRead AudioRead = { hEvent, 0, vf, buffer, length, bigendianp, word, sgned, bitstream };

    if (!PostThreadMessageW(dwThreadId, WM_APP_AUDIO_READ, 0, (LPARAM)&AudioRead))
        return OV_FALSE;

    WaitForSingleObjectEx(AudioRead.Base.hEvent, INFINITE, False);

    return AudioRead.Base.Result;
*/
}

int CDECL hook_ov_clear(OggVorbis_File *vf)
{
    SThreadParamAduioClear AudioClear = { hEvent, 0, vf };

    if (!PostThreadMessageW(dwThreadId, WM_APP_AUDIO_CLEAR, 0, (LPARAM)&AudioClear))
        return OV_FALSE;

    WaitForSingleObjectEx(AudioClear.Base.hEvent, INFINITE, False);

    return AudioClear.Base.Result;
}

FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    FARPROC Proc = Nt_GetProcAddress(hModule, lpProcName);

    if ((ULONG_PTR)lpProcName & 0xFFFF0000)
    {
        switch (HashAPI(lpProcName))
        {
            case 0xE481C812:
                *(FARPROC *)&vorbis_func.ov_clear = Proc;
                return (FARPROC)my_ov_clear;

            case 0x45CABB2D:
                *(FARPROC *)&vorbis_func.ov_open_callbacks = Proc;
                return (FARPROC)hook_ov_open_callbacks;

            case 0x6707AC8B:
                *(FARPROC *)&vorbis_func.ov_read = Proc;
                return (FARPROC)hook_ov_read;
/*
            case 0x484BC096:
                *(FARPROC *)&vorbis_func.ov_seekable = Proc;
                return (FARPROC)my_ov_seekable;
*/
            case 0x29404C8D:
                *(FARPROC *)&vorbis_func.ov_pcm_total = Proc;
                return (FARPROC)my_ov_pcm_total;

            case 0x5CAE8292:
                *(FARPROC *)&vorbis_func.ov_time_total = Proc;
                return (FARPROC)my_ov_time_total;

            case 0x3FF0C6FE:
                *(FARPROC *)&vorbis_func.ov_time_seek = Proc;
                return (FARPROC)my_ov_time_seek;

            case 0x3FF1E579:
                *(FARPROC *)&vorbis_func.ov_time_tell = Proc;
                return (FARPROC)my_ov_time_tell;
/*
            case 0x4B074100:
                *(FARPROC *)&vorbis_func.ov_info = Proc;
                return (FARPROC)my_ov_info;

            case 0x171FC152:
                *(FARPROC *)&vorbis_func.ov_comment = Proc;
                return (FARPROC)my_ov_comment;
*/
        }
    }

    return Proc;
}

#endif // HAVE_COMPRESS

ASM VOID GetFontFaceNameOutOfIndex()
{
    INLINE_ASM
    {
        xor     esi, esi;
        cmp     edx, eax;
        cmovge  edx, esi;
        mov     eax, dword ptr [ebx-0xB4];
        ret;
    }
}

BOOL CDECL CheckBoundInBRegExp(CHAR ch)
{
    return (UChar)ch >> 7;
}

VOID InitGame(HMODULE hModule)
{
    HANDLE hFind;
    NTSTATUS Status;
    WIN32_FIND_DATAW wfd;

//    g_PeekMsgFalseCount = 4;
    g_pCharMap = CreateCharMapW(NULL, 0);

//    CloseHandle(CreateThread(0, 0, DecodeAudioThread, 0, 0, 0));

//    GetExecuteDirectoryW(wfd.cFileName, countof(wfd.cFileName));
//    SetCurrentDirectoryW(wfd.cFileName);

    hFind = Nt_FindFirstFile(L"*.tt?", &wfd);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            AddFontResourceExW(wfd.cFileName, FR_PRIVATE, 0);
        } while (Nt_FindNextFile(hFind, &wfd));
        Nt_FindClose(hFind);
    }

    INTEL_STATIC MEMORY_FUNCTION_PATCH f[] =
    {
        { JUMP, 0xFB54C, LoadSave,              0x04, (PBYTE)OldLoadSave + 4 },
        { CALL, 0x73898, ConvertFileName,       0x00 },
        { CALL, 0x74771, ConvertPathInIndex,    0x00 },
        { CALL, 0xC427E, ConvertFileName,       0x00 },  // In .b file
        { CALL, 0xC2A17, ConvertFileName,       0x00 },  // In .b meta data
        { JUMP, 0x73398, GetSubTalbeIndex,      0x00 },
        { CALL, 0x73737, RegenerateHashTable,   0x00 },
        { JUMP, 0x74120, GameLoadFile,          0x00, OldGameLoadFile },
        { JUMP, 0xE9C6C, OpenVideo,             0x04, (PBYTE)OldOpenVideo + 1 },
        { CALL, 0x0B3AD, MyCreateFileA,         0x00 },
        { CALL, 0x0B497, MyFindFirstFileA,      0x00 },
        { CALL, 0x0B4A2, MyFindClose,           0x00 },
        { CALL, 0x7FEAA, GetFontFaceNameOutOfIndex, 0x01 },
//        { CALL, 0x55033, MyPeekMessageA,      0x00 },

#if defined(HAVE_COMPRESS)
        { CALL, 0xA9C5D, CompareExtensionA,     0x00 },   // image
        { CALL, 0xB7605, CompareExtensionA,     0x00 },   // audio
        { CALL, 0x32B10, DisplayBMP,            0x00 },
        { CALL, 0x32C35, DisplayBMP,            0x00 },
        { CALL, 0x7310C, FindFile,              0x00 },
        { CALL, 0x7336C, FindFile,              0x00 },
        { CALL, 0xAE90F, MyGetProcAddress,      0x00 },
#endif
    };

    INTEL_STATIC MEMORY_PATCH p[] =
    {
        // bound
        { 0xEB,   0x01, 0x707AE },
        { 0xEB,   0x01, 0x72E3A },
        { 0xEB,   0x01, 0x7D3A4 },
        { 0xEB,   0x01, 0x7DDA0 },
        { 0xEB,   0x01, 0x7F259 },
        { 0xEB,   0x01, 0xA7EFC },
        { 0xEB,   0x01, 0xB61B6 },

        // charset
        { GB2312_CHARSET, 01, 0x7E992 },

        // bug
//        { 0x14EB, 0x02, 0x23224 },  // index out of bound   004801E7
//        { 0xEB,   0x01, 0x2321C },  // index out of bound
        { 0x0A81,   0x02, 0x7F653 },  // lf.lfCharSet == SHIFTJIS_CHARSET jno
        { 0x80,     0x01, 0x7F503 },  // lf.lfCharSet == SHIFTJIS_CHARSET
        { 0x0A81,   0x02, 0x7F7AB },  // lf.lfCharSet == SHIFTJIS_CHARSET

        // misc
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x0FB5A8 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x0FB5E0 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x0FBBB7 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x0FBD17 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x0FC152 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x0FFACD },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x0FFB62 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x0FFBDB },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x0FFBFD },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x0FFDB4 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x1001D8 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x100249 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x107C01 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x1092CC },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x109348 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x114DB4 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x114DCA },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x1216D7 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x121712 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x122058 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x122093 },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x12553B },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x1283CF },
        { (ULONG)&g_SaveData.Buffer,  0x04, 0x128C9C },

        { (ULONG)&g_SaveData2.Buffer,  0x04, 0x123DBB },

        { (ULONG)&g_ConfigPath.Buffer,  0x04, 0x12B215 },   // read * 3
        { (ULONG)&g_ConfigPath.Buffer,  0x04, 0x12B270 },
        { (ULONG)&g_ConfigPath.Buffer,  0x04, 0x12B292 },
        { (ULONG)&g_ConfigPath.Buffer,  0x04, 0x12A98A },   // write

        { 0xB8, 0x01, 0x81ECB },  // don't create config.bak

//        { (ULong)&g_DefaultFont.szText,  0x04, 0x806E5 },

        // iat
        { (ULONG)MyCreateFontIndirectA2,     0x04, 0x166570 },
        { (ULONG)MyExtTextOutA,             0x04, 0x166544 },
        { (ULONG)GameMyEnumFontFamiliesExA, 0x04, 0x16654C },
//        { (UInt32)MyPeekMessageA,            0x04, 0x166670 },
    };
/*
    SPatch iat_hook[] =
    {
        { (UInt32)MyCreateFontIndirectA2, 0x04, IATLookupRoutineRVAByEntry(hModule, CreateFontIndirectA) },
        { (UInt32)MyExtTextOutA,         0x04, IATLookupRoutineRVAByEntry(hModule, ExtTextOutA) },
        { (UInt32)MyEnumFontFamiliesExA, 0x04, IATLookupRoutineRVAByEntry(hModule, EnumFontFamiliesExA) },
    };
*/

    PVOID           DllBaseAddress;
    UNICODE_STRING  BregExpDll;

    RTL_CONST_STRING(BregExpDll, L"dll\\bregexp.dll");
    Status = LdrLoadDll(NULL, 0, &BregExpDll, &DllBaseAddress);
    if (NT_SUCCESS(Status))
    {
        INTEL_STATIC MEMORY_FUNCTION_PATCH bregexp_f[] =
        {
            { JUMP, 0x07900, CheckBoundInBRegExp, 0x00 },
        };
        Nt_PatchMemory(0, countof(p), bregexp_f, countof(bregexp_f), DllBaseAddress);
    }

#if defined(MY_DEBUG)
    Nt_PatchMemory(p, countof(p), f, countof(f), hModule);
    IF_EXIST(iat_hook)
    {
        Nt_PatchMemory(iat_hook, countof(iat_hook), 0, 0, hModule);
    }
#else
    PatchMemoryNoVP(p, countof(p), f, countof(f), hModule);
    IF_EXIST(iat_hook)
    {
        PatchMemoryNoVP(iat_hook, countof(iat_hook), 0, 0, hModule);
    }
#endif

    if (Nt_CurrentPeb()->AnsiCodePageData[1] != CP_GB2312)
    LOOP_ONCE
    {
        NTSTATUS                    Status;
        UNICODE_STRING              LocaleEmulator;
        PIMAGE_DOS_HEADER           DosHeader;
        PIMAGE_NT_HEADERS           NtHeaders;
        BeginLocalEmulatorRoutine   BeginLocalEmulator;

        RTL_CONST_STRING(LocaleEmulator, L"LocaleEmulator.dll");

        Status = LdrLoadDll(NULL, 0, &LocaleEmulator, (PVOID *)&hModule);
        if (!NT_SUCCESS(Status))
            break;

        DosHeader = (PIMAGE_DOS_HEADER)hModule;
        NtHeaders = (PIMAGE_NT_HEADERS)((ULONG_PTR)DosHeader + DosHeader->e_lfanew);
        *(PULONG_PTR)&BeginLocalEmulator = (ULONG_PTR)hModule + NtHeaders->OptionalHeader.AddressOfEntryPoint;
        BeginLocalEmulator(hModule, LOCALE_EMULATOR_BEGIN, CP_GB2312);
    }
}

VOID InitConfig(HMODULE hModule)
{
    MEMORY_PATCH p[] =
    {
        // iat
        { (ULONG)MyCreateFontIndirectA2, 0x04, 0x83C38 },
    };

#if defined(MY_DEBUG)
    Nt_PatchMemory(p, countof(p), 0, 0, hModule);
#else
    PatchMemoryNoVP(p, countof(p), 0, 0, hModule);
#endif
}

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    static BOOL b;
    CHAR buf[200];

    UNREFERENCED_PARAMETER(buf);
//    if (_InterlockedCompareExchange((PLong)&b, True, False) == False) do
//    {


        WCHAR path[MAX_NTPATH];
        FILE *fp;

        lstrcpyW(path + GetExecuteDirectoryW(path, countof(path)), L"log.txt");
        fp = _wfopen(path, L"ab");
        if (fp)
        {
            SYSTEMTIME st;

            GetLocalTime(&st);
            fprintf(
                fp,
                "%02d:%02d:%02d: code = %08X, addr = %08X\r\n",
                st.wHour, st.wMinute, st.wSecond,
                ExceptionInfo->ExceptionRecord->ExceptionCode,
                ExceptionInfo->ExceptionRecord->ExceptionAddress);

            fclose(fp);
        }

//        MessageBoxA(0, buf, 0, 64);

//        _InterlockedCompareExchange((PLong)&b, False, True);
//        ExitProcess(0);
        return EXCEPTION_CONTINUE_SEARCH;
//    } while (0);

//    return EXCEPTION_CONTINUE_SEARCH;
}

#include "LocaleEmulator.h"
VOID Init()
{
    ULONG   TimeStamp;
    HMODULE hModule;

    MemoryAllocator::CreateGlobalHeap();
//    AddVectoredExceptionHandler(True, VectoredHandler);

    Nt_SetExecuteDirectoryAsCurrent();

    hModule = Nt_GetExeModuleHandle();
    TimeStamp = *(PULONG)((ULONG_PTR)hModule + 0x108);

    switch (TimeStamp)
    {
//        case 0x49D4CFC5:
//            InitConfig(hModule);
//            break;

        case 0x2A425E19:
            InitGame(hModule);
            break;
    }
}

VOID UnInit()
{
    if (g_pCharMap)
        FreeCharMap(g_pCharMap);

    MemoryAllocator::DestroyGlobalHeap();

//    EndLocalEmulator();
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID lpReserved)
{
    UNUSED_VARIABLE(lpReserved);
    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            LdrDisableThreadCalloutsForDll(hInstance);
            Init();
            break;

        case DLL_PROCESS_DETACH:
            UnInit();
            break;
    }

    return TRUE;
}

#else   // LOCALE_EMULATOR_ONLY

//#include "nt_api.cpp"

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, PVOID Reserved)
{
    UNREFERENCED_PARAMETER(hInstance);
    switch (Reason + 1)
    {
        case LOCALE_EMULATOR_BEGIN + 1:
//            LdrDisableThreadCalloutsForDll(hInstance);
            return BeginLocalEmulator((ULONG)Reserved);

        case DLL_THREAD_DETACH + 1:
            ReleaseThreadLocalStorage();
            break;

        case LOCALE_EMULATOR_END + 1:
//            EndLocalEmulator();
            break;
    }

    return TRUE;
}

#endif

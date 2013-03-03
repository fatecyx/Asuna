#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(linker, "/EXPORT:Direct3DCreate9=d3d9.Direct3DCreate9")

#include "cmvs.h"
#include "MyLibrary.cpp"
#include "HandleTable.cpp"

OVERLOAD_CPP_NEW_WITH_HEAP(MemoryAllocator::GetGlobalHeap())

CmvsObject*     g_CmvsObject;
MlHandleTable*  g_TextTable;
PVOID           g_TextBuffer;

CmvsObject* (CDECL *StubCreateCmvsObject)(ULONG_PTR Size);

CmvsObject* CDECL CreateCmvsObject(ULONG_PTR Size)
{
    g_CmvsObject = StubCreateCmvsObject(Size);
    return g_CmvsObject;
}

WNDPROC OrigWndProc;

VOID DropFiles(HWND hWnd, HDROP hDrop)
{
    WCHAR CpzPathW[MAX_NTPATH];
    CmvsImageManager *ImageManager = g_CmvsObject->ImageManager;

    AllocConsole();
    for (ULONG_PTR Index = 0; DragQueryFileW(hDrop, Index, CpzPathW, countof(CpzPathW)); ++Index)
    {
        CmvsUnpackerX cpz(ImageManager);

        cpz.Auto(CpzPathW);
    }
    FreeConsole();

    DragFinish(hDrop);
}

int WINAPI HMessageBoxA(_In_opt_ HWND hWnd, _In_opt_ LPCSTR lpText, _In_opt_ LPCSTR lpCaption, _In_ UINT uType)
{
    AllocConsole();

    CmvsUnpackerX cpz(g_CmvsObject->ImageManager);
    cpz.Auto(L"E:\\Desktop\\ハピメア\\data\\pack\\script.cpz");

    Ps::ExitProcess(0);
}

LRESULT CALLBACK CMVS_MainWindowProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
        case WM_DROPFILES:
            DropFiles(hWnd, (HDROP)wParam);
            return 0;
    }

    return CallWindowProcA(OrigWndProc, hWnd, Message, wParam, lParam);
}

HWND WINAPI HookCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    RECT    rcWordArea;
    ULONG   Length;
    LPWSTR  ClassName, WindowName;
    HWND    hWnd;

    Length = StrLengthA(lpClassName) + 1;
    ClassName = (LPWSTR)AllocStack(Length * sizeof(WCHAR));
    AnsiToUnicode(ClassName, Length * sizeof(WCHAR), lpClassName, Length);

    Length = StrLengthA(lpWindowName) + 1;
    WindowName = (LPWSTR)AllocStack(Length * sizeof(WCHAR));
    AnsiToUnicode(WindowName, Length * sizeof(WCHAR), lpWindowName, Length);

    hWnd = CreateWindowExW(dwExStyle, ClassName, WindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    if (hWnd == NULL)
        return hWnd;

    OrigWndProc = (WNDPROC)SetWindowLongPtrA(hWnd, GWLP_WNDPROC, (LONG_PTR)CMVS_MainWindowProc);
    DragAcceptFiles(hWnd, TRUE);

    return hWnd;
}

HFONT WINAPI HookCreateFontA(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic, DWORD bUnderline, __in DWORD bStrikeOut, __in DWORD iCharSet, __in DWORD iOutPrecision, __in DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, LPCSTR pszFaceName)
{
    LOGFONTW lf;

    lf.lfHeight         = cHeight;
    lf.lfWidth          = cWidth;
    lf.lfEscapement     = cEscapement;
    lf.lfOrientation    = cOrientation;
    lf.lfWeight         = cWeight;
    lf.lfItalic         = (BYTE)bItalic;
    lf.lfUnderline      = (BYTE)bUnderline;
    lf.lfStrikeOut      = (BYTE)bStrikeOut;
    lf.lfOutPrecision   = (BYTE)iOutPrecision;
    lf.lfClipPrecision  = (BYTE)iClipPrecision;
    lf.lfQuality        = CLEARTYPE_QUALITY;
    lf.lfPitchAndFamily = (BYTE)iPitchAndFamily;

    if (iCharSet == SHIFTJIS_CHARSET && g_TextTable != NULL)
    {
        iCharSet = GB2312_CHARSET;
        CopyStruct(lf.lfFaceName, L"SIMHEI", sizeof(L"SIMHEI"));
    }
    else
    {
        AnsiToUnicode(lf.lfFaceName, countof(lf.lfFaceName), pszFaceName);
    }

    lf.lfCharSet = (BYTE)iCharSet;

    return CreateFontIndirectW(&lf);
}

BOOL STDCALL IsLeadByte(CHAR ch)
{
    return ch < 0;
}

PVOID FASTCALL Cmvs_GetStringPtr(CmvsObject *Cmvs, ULONG TextOffset, ULONG)
{
    ULONG_PTR               Index;
    MlHandleTable          *TextTable, *SubTable;
    PML_HANDLE_TABLE_ENTRY  Entry;
    PTEXTBIN_ENTRY          Text;
    PCMVS_PS2_HEADER        PsHeader;

    Index = Cmvs->PsIndex;
    TextTable = g_TextTable;

    LOOP_ONCE
    {
        if (TextTable == NULL)
            continue;

        PsHeader = Cmvs->Ps2Buffer[Index];

        Entry = TextTable->Lookup(PsHeader->Crc);
        if (Entry == NULL)
            break;

        SubTable = (MlHandleTable *)Entry->Handle;
        Entry = SubTable->Lookup(TextOffset);
        if (Entry == NULL)
            break;

        Text = (PTEXTBIN_ENTRY)Entry->Handle;
        if (Text == NULL)
            break;

        Text->Text[Text->Length] = 0;

        return Text->Text;
    }

    return Cmvs->Ps2StringBuffer[Index] + TextOffset;
}

NAKED PVOID Cmvs_GetStringPtr2()
{
    INLINE_ASM
    {
        mov     ecx, esi;
        mov     edx, eax;
        lea     esp, [esp - 4];
        call    Cmvs_GetStringPtr;
        mov     ecx, eax;
        ret;
    }
}

VOID DestroyTextTable()
{
    MlHandleTable *TextTable;

    TextTable = g_TextTable;
    if (TextTable == NULL)
        return;

    TextTable->Destroy(
        HandleTableDestroyM(Entry, Count, Context)
        {
            MlHandleTable *SubTable;

            for (; Count; ++Entry, --Count)
            {
                SubTable = (MlHandleTable *)Entry->Handle;
                delete SubTable;
            }

            return STATUS_SUCCESS;
        },
        0
    );

    delete TextTable;

    FreeMemoryP(g_TextBuffer);

    g_TextBuffer = NULL;
    g_TextTable = NULL;
}

NTSTATUS InitTextBin()
{
    WCHAR           MiraiText[MAX_NTPATH];
    NtFileMemory    bin;
    PVOID           Buffer;
    ULONG_PTR       CompressedSize, UncompressedSize;
    NTSTATUS        Status;
    PTEXTBIN_HEADER Header, End;
    PTEXTBIN_ENTRY  Entry;
    MlHandleTable  *TextTable, *SubTable;
    PML_HANDLE_TABLE_ENTRY  HtEntry;

    TextTable = new MlHandleTable;
    if (TextTable == NULL)
        return STATUS_NO_MEMORY;

    if (TextTable->Create() == NULL)
    {
        delete TextTable;
        return STATUS_NO_MEMORY;
    }

    g_TextTable = TextTable;

    SCOPE_EXIT
    {
        if (NT_FAILED(Status))
        {
            DestroyTextTable();
        }
    }
    SCOPE_EXIT_END;

    *(PULONG64)&MiraiText[0] = TAG4W('mira');
    *(PULONG64)&MiraiText[4] = TAG4W('i.bi');
    *(PULONG32)&MiraiText[8] = 'n';

    Status = bin.Open(MiraiText);
    FAIL_RETURN(Status);

    Status = STATUS_NO_MEMORY;

    CompressedSize = *(PULONG)bin.GetBuffer();
    UncompressedSize = *((PULONG)bin.GetBuffer() + 1);

    Buffer = AllocateMemoryP(UncompressedSize);
    if (Buffer == NULL)
        return Status;

    UCL_NRV2E_Decompress(PtrAdd(bin.GetBuffer(), 8), CompressedSize, Buffer, &UncompressedSize);

    g_TextBuffer = Buffer;

    Header  = (PTEXTBIN_HEADER)Buffer;
    End     = PtrAdd(Header, UncompressedSize);

    while (Header < End)
    {
        SubTable = new MlHandleTable;
        if (SubTable == NULL)
            return Status;

        if (SubTable->Create() == NULL)
            return Status;

        HtEntry = TextTable->Insert(Header->Crc);
        if (HtEntry == NULL)
            return Status;

        HtEntry->Handle = SubTable;

        Entry = Header->Entry;
        for (ULONG_PTR Count = Header->Count; Count; --Count)
        {
            HtEntry = SubTable->Insert(Entry->Offset);
            if (HtEntry == NULL)
                return Status;

            HtEntry->Handle = Entry;
            Entry = Entry->Next();
        }

        Header = (PTEXTBIN_HEADER)Entry;
    }

    Status = STATUS_SUCCESS;

    return Status;
}

inline BOOL UnInitialize(PVOID BaseAddress)
{
    return FALSE;
}

BOOL Initialize(PVOID BaseAddress)
{
    ml::MlInitialize();

    LdrDisableThreadCalloutsForDll(BaseAddress);
/*
    if (NT_FAILED(InitTextBin()))
        return TRUE;
*/
#if MIRAI

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY('　', 2, 0x12603C),

        PATCH_MEMORY(HookCreateFontA, sizeof(PVOID), 0x123050),
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_CALL_RVA_NULL(0x04538, HookCreateWindowExA),

        INLINE_HOOK_JUMP_RVA_NULL(0x50F87, Cmvs_GetStringPtr),
        INLINE_HOOK_JUMP_RVA_NULL(0x035C0, IsLeadByte),

        PATCH_FUNCTION(CALL, 0, 0x4AFC2, Cmvs_GetStringPtr2, 0xA),
        PATCH_FUNCTION(CALL, 0, 0x4B64C, Cmvs_GetStringPtr2, 0xA),

        INLINE_HOOK_CALL_RVA(0x01054, CreateCmvsObject, StubCreateCmvsObject),
    };

#elif HAPIMEA

    MEMORY_PATCH p[] =
    {
        PATCH_MEMORY(0, 0, IMAGE_INVALID_RVA),
    };

    MEMORY_FUNCTION_PATCH f[] =
    {
        INLINE_HOOK_CALL_RVA_NULL(0x04AD1, HookCreateWindowExA),
        INLINE_HOOK_JUMP_NULL(MessageBoxA, HMessageBoxA),

        INLINE_HOOK_CALL_RVA(0x01055, CreateCmvsObject, StubCreateCmvsObject),
    };

#endif

    BaseAddress = GetExeModuleHandle();
    Nt_PatchMemory(p, countof(p), f, countof(f), BaseAddress);

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

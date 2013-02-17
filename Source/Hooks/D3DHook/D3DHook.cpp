#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#define D3D9_DEBUG 0
#define DISABLE_DXUT_DEMO_MAIN 1

#include "D3DHook.h"
#include "DXUT/DXUTgui.h"
#include "HookInterface8.h"
#include "HookInterface9.h"
#include "D3DHookStub.h"
#include "../../GUI/DXUT/DXUTDemo.cpp"

// OVERLOAD_CPP_NEW_WITH_HEAP(MemoryAllocator::GetGlobalHeap())

PDHOOK_HOOK_INFO  g_Info;
WNDPROC         AnsiWindowProc, UnicodeWindowProc;

HRESULT
CALLBACK
DXUT_OnFrameRender(
    IDirect3DDevice9   *Device,
    double              Time,
    float               ElapsedTime,
    DXUTLolBox           *Dialog
)
{
    Device->BeginScene();

//    Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0);

    if (Dialog->m_DialogPos != NULL)
    {
        WCHAR buf[0x100];
        POINT pt;

        Dialog->m_Dialog.GetLocation(pt);
        swprintf(buf, L"X = %d, Y = %d, W = %d, H = %d", pt, Dialog->m_Dialog.GetWidth(), Dialog->m_Dialog.GetHeight());
        Dialog->m_DialogPos->SetText(buf);
    }

    Dialog->m_Dialog.OnRender(ElapsedTime);
    Device->EndScene();

    return S_OK;
}

HRESULT
CALLBACK
DXUT_OnCreateDevice(
    IDirect3DDevice9*   Device,
    D3DSURFACE_DESC*    BackBufferSurfaceDesc,
    DXUTLolBox         *Dialog
)
{
    HRESULT Result;

    Result = Dialog->m_DialogResourceManager.OnD3D9CreateDevice(Device);
    if (FAILED(Result))
        return Result;

    Dialog->Initialize();

    return S_OK;
}

HRESULT
CALLBACK
DXUT_OnResetDevice(
    IDirect3DDevice9    *Device,
    D3DSURFACE_DESC     *BackBufferSurfaceDesc,
    DXUTLolBox          *Dialog
)
{
    Dialog->m_DialogResourceManager.OnD3D9ResetDevice();

    return S_OK;
}

HRESULT CALLBACK DXUT_OnLostDevice(DXUTLolBox *Dialog)
{
    Dialog->m_DialogResourceManager.OnD3D9LostDevice();
    return S_OK;
}

HRESULT CALLBACK DXUT_OnDestroyDevice(DXUTLolBox *Dialog)
{
    Dialog->m_DialogResourceManager.OnD3D9DestroyDevice();
    return S_OK;
}

LRESULT
CALLBACK
DXUT_MsgProc(
    HWND        hWnd,
    UINT        Message,
    WPARAM      wParam,
    LPARAM      lParam,
    BOOL       &NoFurtherProcessing,
    DXUTLolBox   *Dialog
)
{
    NoFurtherProcessing = Dialog->m_Dialog.MsgProc(hWnd, Message, wParam, lParam);

    return 0;
}

PCALLBACKDXUTGUIEVENT g_EventCallback;

VOID
CALLBACK
DXUT_OnGUIEvent(
    UINT            Event,
    INT             ControlID,
    CDXUTControl   *Control,
    DXUTLolBox     *Dialog
)
{
    WCHAR buf[0x100];
    CDXUTButton *Button;

    if (g_EventCallback != NULL)
    {
        g_EventCallback(Event, ControlID, Control, Dialog);
        return;
    }

    switch (ControlID)
    {
        case QMSG_1:
        case QMSG_2:
        case QMSG_3:
        case QMSG_4:
        case QMSG_5:
        case QMSG_6:
        case QMSG_7:
        case QMSG_8:
        case QMSG_9:
            Button = (CDXUTButton *)Control;
            SetWindowTextW(DXUTGetHWND(), Button->GetText());
            break;
    }
}

LRESULT
MessageFilter(
    HWND    hWnd,
    UINT    Message,
    WPARAM  wParam,
    LPARAM  lParam,
    BOOL    UnicodeWindow,
    BOOL   &Handled
)
{
    BOOL                BeingActivated;
    LRESULT             Result;
    PDHOOK_HOOK_INFO    Info = g_Info;

    switch (Message)
    {
        case WM_KEYDOWN:
            switch (wParam)
            {
                case VK_OEM_3:
                    Info->ShowDialog = TRUE;
                    break;
            }
            break;

        case WM_KEYUP:
            switch (wParam)
            {
                case VK_F6:
                    Info->ShowDialog ^= TRUE;
                    break;

                case VK_OEM_3:
                    Info->ShowDialog = FALSE;
                    break;
            }
            break;
    }

    if (!Info->ShowDialog)
        return NO_ERROR;

    Result = Info->dxut->RealWindowProc(hWnd, Message, wParam, lParam, UnicodeWindow, Handled);

    if (!Handled)
        return Result;

    switch (Message)
    {
        case WM_KEYUP:
        case WM_SYSKEYUP:
            Info->KeyReleased = TRUE;
            break;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            Info->KeyPressed = TRUE;
            break;

        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
        case WM_XBUTTONUP:
            Info->MouseReleased = TRUE;
            break;

        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONDBLCLK:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONDBLCLK:
        case WM_MOUSEWHEEL:
        case WM_MOUSEMOVE:
            Info->MousePressed = TRUE;
            break;
    }

    return Result;
}

LRESULT WINAPI MainWindowProcA(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    BOOL    Handled = FALSE;
    LRESULT Result;

    Result = MessageFilter(hWnd, Message, wParam, lParam, FALSE, Handled);

    return Handled ? Result : CallWindowProcA(AnsiWindowProc, hWnd, Message, wParam, lParam);
}

LRESULT WINAPI MainWindowProcW(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    BOOL    Handled = FALSE;
    LRESULT Result;

    Result = MessageFilter(hWnd, Message, wParam, lParam, TRUE, Handled);

    return Handled ? Result : CallWindowProcW(UnicodeWindowProc, hWnd, Message, wParam, lParam);
}

NTSTATUS
OnCreateDevice(
    PDHOOK_HOOK_INFO          Info,
    PDHOOK_CALLBACK_PARAMETER Parameter
)
{
    HRESULT Result;

    Info->Windowed = !!Parameter->d3d9.CreateDevice.Windowed;
    Info->MainWindow = Parameter->d3d9.CreateDevice.MainWindow;
    Info->dxut->SetFocusWindow(Info->MainWindow);
    Result = Info->dxut->CreateDevice(Parameter->Device9, Parameter->Version);
    if (FAILED(Result))
        return Result;

    if (IsWindowUnicode(Info->MainWindow))
        UnicodeWindowProc = (WNDPROC)SetWindowLongPtrW(Info->MainWindow, GWLP_WNDPROC, (LONG_PTR)MainWindowProcW);
    else
        AnsiWindowProc = (WNDPROC)SetWindowLongPtrA(Info->MainWindow, GWLP_WNDPROC, (LONG_PTR)MainWindowProcA);

    return STATUS_SUCCESS;
}

NTSTATUS
OnLostDevice(
    PDHOOK_HOOK_INFO          Info,
    PDHOOK_CALLBACK_PARAMETER Parameter
)
{
    return Info->dxut->LostDevice(Parameter->Device9);
}

NTSTATUS
OnResetDevice(
    PDHOOK_HOOK_INFO          Info,
    PDHOOK_CALLBACK_PARAMETER Parameter
)
{
    Info->dxut->ResetDevice(Parameter->Device9);

    return STATUS_SUCCESS;
}

NTSTATUS
OnDestroyDevice(
    PDHOOK_HOOK_INFO          Info,
    PDHOOK_CALLBACK_PARAMETER Parameter
)
{
    HRESULT Result;

    Result = Info->dxut->DestroyDevice(Parameter->Device);

    Info->dxut->SetFocusWindow(NULL);

    return Result;
}

NTSTATUS
OnRenderFrame(
    PDHOOK_HOOK_INFO          Info,
    PDHOOK_CALLBACK_PARAMETER Parameter
)
{
    if (!Info->ShowDialog)
        return STATUS_SUCCESS;

    Info->dxut->RenderFrame(Parameter->Device9);
    return STATUS_SUCCESS;
}

ULONG
GetDirectInputDeviceType(
    PDHOOK_HOOK_INFO    Info,
    PVOID               Device,
    BOOL                Unicode
)
{
    HRESULT Result;
    DHOOK_HOOK_INFO::DINPUT_DEVICE_POOL *Pool;

    union
    {
        DIDEVICEINSTANCEA InfoA;
        DIDEVICEINSTANCEW InfoW;
    };

    Pool = &Info->DinputDevicePool[((ULONG_PTR)Device & 0xFFFF) % countof(Info->DinputDevicePool)];
    if (Pool->Device == Device)
        return Pool->Type;

    if (Unicode)
    {
        InfoW.dwSize = sizeof(InfoW);
        Result = ((LPDIRECTINPUTDEVICE8W)Device)->GetDeviceInfo(&InfoW);
    }
    else
    {
        InfoA.dwSize = sizeof(InfoA);
        Result = ((LPDIRECTINPUTDEVICE8A)Device)->GetDeviceInfo(&InfoA);
    }

    if (FAILED(Result))
        return ~0u;

    Pool->Device    = Device;
    Pool->Type      = GET_DIDEVICE_TYPE(InfoW.dwDevType);

    return Pool->Type;
}

NTSTATUS
QueryDeviceStateOrData(
    PDHOOK_HOOK_INFO    Info,
    PVOID               Device,
    PVOID               Output,
    ULONG               OutputSize,
    PULONG              ReturnedLength,
    BOOL                Unicode
)
{
    ULONG DeviceType;

    DeviceType = GetDirectInputDeviceType(Info, Device, Unicode);

    switch (DeviceType)
    {
        case DI8DEVTYPE_KEYBOARD:
            switch (Info->WindowFlags & (DHOOK_KEY_RELEASED | DHOOK_KEY_PRESSED))
            {
                case DHOOK_KEY_RELEASED:
                case DHOOK_KEY_PRESSED:
                    break;

                case DHOOK_KEY_RELEASED | DHOOK_KEY_PRESSED:
                    if (Output == NULL || OutputSize == 0)
                        break;

                    Info->KeyPressed    = FALSE;
                    Info->KeyReleased   = FALSE;
                    break;

                default:
                    return STATUS_SUCCESS;
            }
            break;

        case DI8DEVTYPE_MOUSE:
            switch (Info->WindowFlags & (DHOOK_MOUSE_RELEASED | DHOOK_MOUSE_PRESSED))
            {
                case DHOOK_MOUSE_RELEASED:
                case DHOOK_MOUSE_PRESSED:
                    break;

                case DHOOK_MOUSE_RELEASED | DHOOK_MOUSE_PRESSED:
                    if (Output == NULL || OutputSize == 0)
                        break;

                    Info->MousePressed  = FALSE;
                    Info->MouseReleased = FALSE;
                    break;

                default:
                    return STATUS_SUCCESS;
            }
            break;
    }

    if (Output != NULL && OutputSize != 0)
        ZeroMemory(Output, OutputSize);

    if (ReturnedLength != NULL)
        *ReturnedLength = OutputSize;

    return STATUS_ACCESS_DENIED;
}

NTSTATUS
OnGetDeviceState(
    PDHOOK_HOOK_INFO            Info,
    PDHOOK_CALLBACK_PARAMETER   Parameter
)
{
    return QueryDeviceStateOrData(
                Info,
                Parameter->Device,
                Parameter->dinput8.GetState.Data,
                Parameter->dinput8.GetState.DataSize,
                NULL,
                Parameter->dinput8.GetState.Unicode
            );
}

NTSTATUS
OnGetDeviceData(
    PDHOOK_HOOK_INFO            Info,
    PDHOOK_CALLBACK_PARAMETER   Parameter
)
{
    return QueryDeviceStateOrData(
                Info,
                Parameter->Device,
                Parameter->dinput8.GetData.ObjectData,
                Parameter->dinput8.GetData.ObjectDataSize,
                Parameter->dinput8.GetData.OutputSize,
                Parameter->dinput8.GetData.Unicode
            );
}

VOID CheckDllLoadUnLoad(PLDR_DATA_TABLE_ENTRY DllEntry, BOOL Loading)
{
    PDHOOK_HOOK_INFO Info;

    if (!Loading && DllEntry->LoadCount != 0)
        return;

    if (Loading && DllEntry->LoadCount != 1)
        return;

    Info = g_Info;

    if (!StrICompareW(DllEntry->BaseDllName.Buffer, L"d3d9.dll"))
    {
        if (Info->D3D9Hooked)
        {
            if (!Loading && DllEntry->DllBase == Info->D3D9Module)
            {
                UnHookDirect3D9(Info->D3D9Module);
                Info->D3D9Hooked = FALSE;
            }
        }
        else if (Loading)
        {
            Info->D3D9Hooked = TRUE;
            Info->D3D9Hooked = NT_SUCCESS(HookDirect3D9(&Info->D3D9Module, Info));
        }
    }
    else if (!StrICompareW(DllEntry->BaseDllName.Buffer, L"dinput8.dll"))
    {
        if (Info->DInput8Hooked)
        {
            if (!Loading && DllEntry->DllBase == Info->DInput8Module)
            {
                UnHookDirectInput8(Info->DInput8Module);
                Info->DInput8Hooked = FALSE;
            }
        }
        else if (Loading)
        {
            Info->DInput8Hooked = TRUE;
            Info->DInput8Hooked = NT_SUCCESS(HookDirectInput8(&Info->DInput8Module, Info));
        }
    }
}

BOOL UnInitialize(PVOID BaseAddress)
{
    PDHOOK_HOOK_INFO Info;

    UNREFERENCED_PARAMETER(BaseAddress);

    Info = g_Info;

    if (Info != NULL)
    {
        if (Info->dxut != NULL)
        {
            UnInitializeDXUTLite();
            Info->dxut = NULL;
        }

        delete Info;
    }

    MemoryAllocator::DestroyGlobalHeap();

    return FALSE;
}

LONG WINAPI expfilter(PEXCEPTION_POINTERS ExceptionPointers)
{
    PLDR_MODULE Module;

    Module = Nt_FindLdrModuleByHandle((PVOID)ExceptionPointers->ContextRecord->Eip);

    PrintConsoleW(
        L"Exception: Address = %08X, Code = %08X, Eip = %08X, RVA = %08X, %s\n",
		ExceptionPointers->ExceptionRecord->ExceptionAddress,
		ExceptionPointers->ExceptionRecord->ExceptionCode,
		ExceptionPointers->ContextRecord->Eip,
        Module == NULL ? 0 : PtrOffset(ExceptionPointers->ContextRecord->Eip, Module->DllBase),
        Module == NULL ? 0 : Module->FullDllName.Buffer
	);

    return EXCEPTION_CONTINUE_SEARCH;
}

TYPE_OF(VirtualProtect)     *StubVirtualProtect;
TYPE_OF(OutputDebugStringA) *StubOutputDebugStringA;

BOOL WINAPI HookVirtualProtect( __in LPVOID lpAddress, __in SIZE_T dwSize, __in DWORD flNewProtect, __out PDWORD lpflOldProtect )
{
    if ((ULONG_PTR)lpAddress >= 0x401000 && (ULONG_PTR)lpAddress < 0x9C0000)
        DXUT_DbgPrint(L"addr = %08X, size = %08X\n", lpAddress, dwSize);

    return StubVirtualProtect(lpAddress, dwSize, flNewProtect, lpflOldProtect);
}

VOID WINAPI HookOutputDebugStringA(LPCSTR lpOutputString)
{
    DXUT_DbgPrint(L"%S", lpOutputString);
    return StubOutputDebugStringA(lpOutputString);
}

ULONG WINAPI DumpMemory(PVOID)
{
    WCHAR           Buffer[MAX_NTPATH];
    PWSTR           FileName;
    ULONG           SizeOfImage;
    LARGE_INTEGER   Interval;

    FormatTimeOut(&Interval, 50);

    CopyStruct(Buffer, L"E:\\Desktop\\dump\\", sizeof(L"E:\\Desktop\\dump\\"));
    FileName = Buffer + CONST_STRLEN(L"E:\\Desktop\\dump\\");

    SizeOfImage = Nt_FindLdrModuleByHandle(NULL)->SizeOfImage;

    LOOP_FOREVER
    {
        NtDelayExecution(FALSE, &Interval);
        if (GetAsyncKeyState(VK_SHIFT) >= 0)
            continue;

        NtFileDisk file;

        swprintf(FileName, L"%08X", NtGetTickCount());

        file.Create(Buffer);
        file.Write((PVOID)0x400000, SizeOfImage);

        DXUT_DbgPrint(L"dump\n");
    }
}

ULONG CDECL HashSectionKey(PSTR Key)
{
    PSTR Section;

    INLINE_ASM
    {
        mov Section, eax;
    }

    ULONG_PTR Hash = 0;

    SCOPE_EXIT
    {
        FILE *fp;

        fp = _wfopen(L"E:\\Desktop\\lollog.txt", L"ab+");
        fprintf(fp, "Hash = %08X, Section = %s, Key = %s\n", Hash, Section, Key);
        fclose(fp);
    }
    SCOPE_EXIT_END;

    if (Section == NULL)
        return Hash;

    Hash = HashAnsiLower(Section, Hash);
    Hash = HashAnsiLower("*", Hash);

    if (Key != NULL)
        Hash = HashAnsiLower(Key, Hash);

    return Hash;
}

BOOL Initialize(PVOID BaseAddress)
{
    PDHOOK_HOOK_INFO Info;

//    AllocConsole();
//    RtlAddVectoredExceptionHandler(1, expfilter);

    UNREFERENCED_PARAMETER(BaseAddress);

    if (MemoryAllocator::CreateGlobalHeap() == NULL)
        return FALSE;

    Info = new DHOOK_HOOK_INFO;
    if (Info == NULL)
        return FALSE;

    ZeroMemory(Info, sizeof(*Info));

    Info->D3D9Hooked = NT_SUCCESS(HookDirect3D9(&Info->D3D9Module, Info));
//    Info->DInput8Hooked = NT_SUCCESS(HookDirectInput8(&Info->DInput8Module, Info));

    g_Info = Info;

    LdrDisableThreadCalloutsForDll(BaseAddress);
//    LdrInitShimEngineDynamic(BaseAddress);

    InitializeDXUTLite(&Info->dxut);

    DXUTLolBox *test;

    test = new DXUTLolBox;

    test->m_Dialog.SetCallback(DXUT_OnGUIEvent, test);
    Info->dxut->SetNotifyRoutine(Info->dxut->NotifyCreateDevice,    DXUT_OnCreateDevice,    test);
    Info->dxut->SetNotifyRoutine(Info->dxut->NotifyResetDevice,     DXUT_OnResetDevice,     test);
    Info->dxut->SetNotifyRoutine(Info->dxut->NotifyLostDevice,      DXUT_OnLostDevice,      test);
    Info->dxut->SetNotifyRoutine(Info->dxut->NotifyDestroyDevice,   DXUT_OnDestroyDevice,   test);
    Info->dxut->SetNotifyRoutine(Info->dxut->NotifyRenderFrame,     DXUT_OnFrameRender,     test);
    Info->dxut->SetNotifyRoutine(Info->dxut->NotifyMessageProc,     DXUT_MsgProc,           test);

//    MEMORY_FUNCTION_PATCH f[] =
//    {
//        INLINE_HOOK2(VirtualProtect,        HookVirtualProtect,     StubVirtualProtect),
//        INLINE_HOOK2(OutputDebugStringA,    HookOutputDebugStringA, StubOutputDebugStringA),
//        PATCH_FUNCTION(JUMP, 0, 0x767DD0, HashSectionKey),
//    };

//    Nt_PatchMemory(0, 0, f, countof(f), NULL);

//    Nt_DeleteFile(L"E:\\Desktop\\lollog.txt");

    return TRUE;
}

BOOL WINAPI DllMain(PVOID BaseAddress, ULONG Reason, PVOID Reserved)
{
    UNREFERENCED_PARAMETER(Reserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Initialize(BaseAddress) || UnInitialize(BaseAddress);

        case DLL_PROCESS_DETACH:
            UnInitialize(BaseAddress);
            break;

        case -1:
            *(PVOID *)&g_EventCallback = Reserved;
            break;
    }

    return TRUE;
}

#if D3D9_DEBUG

#pragma comment(linker, "/EXPORT:Direct3DCreate9=_Direct3DCreate9@4")
#pragma comment(linker, "/EXPORT:D3DPERF_SetMarker=_D3DPERF_SetMarker@8")

#include <d3d9.h>

EXTC IDirect3D9* STDCALL Direct3DCreate9(UINT SDKVersion)
{
    static IDirect3D9* (STDCALL *pfDirect3DCreate9)(UINT SDKVersion);

    if (pfDirect3DCreate9 == NULL)
    {
        ULONG           Length;
        NTSTATUS        Status;
        PVOID           hModule;
        WCHAR           szPath[MAX_NTPATH];
        UNICODE_STRING  DllPath;

        static WCHAR D3d9Dll[] = L"d3d9.dll";

        Length = Nt_GetSystemDirectory(szPath, countof(szPath));

        CopyStruct(szPath + Length, D3d9Dll, sizeof(D3d9Dll));
        DllPath.Buffer = szPath;
        DllPath.Length = (USHORT)((Length + CONST_STRLEN(D3d9Dll)) * sizeof(WCHAR));
        DllPath.MaximumLength = DllPath.Length;

        Status = LdrLoadDll(NULL, 0, &DllPath, &hModule);
        if (!NT_SUCCESS(Status))
            return NULL;

        LdrAddRefDll(GET_MODULE_HANDLE_EX_FLAG_PIN, hModule);

        *(PVOID *)&pfDirect3DCreate9 = Nt_GetProcAddress(hModule, "Direct3DCreate9");
        if (pfDirect3DCreate9 == NULL)
            return NULL;
    }

    return pfDirect3DCreate9(SDKVersion);
}

EXTC VOID WINAPI D3DPERF_SetMarker(D3DCOLOR Color, PCWSTR Name)
{
    static VOID (STDCALL *pfD3DPERF_SetMarker)(D3DCOLOR Color, PCWSTR Name);

    if (pfD3DPERF_SetMarker == NULL)
    {
        ULONG           Length;
        NTSTATUS        Status;
        PVOID           hModule;
        WCHAR           szPath[MAX_NTPATH];
        UNICODE_STRING  DllPath;

        static WCHAR D3d9Dll[] = L"d3d9.dll";

        Length = Nt_GetSystemDirectory(szPath, countof(szPath));

        CopyStruct(szPath + Length, D3d9Dll, sizeof(D3d9Dll));
        DllPath.Buffer = szPath;
        DllPath.Length = (USHORT)((Length + CONST_STRLEN(D3d9Dll)) * sizeof(WCHAR));
        DllPath.MaximumLength = DllPath.Length;

        Status = LdrLoadDll(NULL, 0, &DllPath, &hModule);
        if (!NT_SUCCESS(Status))
            return;

        LdrAddRefDll(GET_MODULE_HANDLE_EX_FLAG_PIN, hModule);

        *(PVOID *)&pfD3DPERF_SetMarker = Nt_GetProcAddress(hModule, "D3DPERF_SetMarker");
        if (pfD3DPERF_SetMarker == NULL)
            return;
    }

    pfD3DPERF_SetMarker(Color, Name);
}

#endif // D3D9_DEBUG

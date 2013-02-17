a::#d:
#define 
a::#u:
#undef 
a::#p:
#pragma 
a::#in:
#include "$end$"
a::#inn:
#include <$end$>
a::#im:
#import "$end$"
a::#im:
#import <$end$>
a:#ifdef ... #endif:#if:
#ifdef $end$
$selected$
#endif
a:#if 0 ... #endif:#if:
#if 0
$selected$$end$
#endif
a:#ifndef ... #endif:#ifn:
#ifndef $end$
$selected$
#endif
a::#e:
#else
a::#en:
#endif
a::A:
ASSERT($end$)
a::b:
bool
a::DW:
DWORD
a::r:
return
a::T:
True
a::t:
true
a::F:
False
a::f:
false
a::fl:
float
a::HA:
HANDLE
a::HI:
HINSTANCE
a::HR:
HRESULT
a::H:
HWND
a::ll:
long long
a::LP:
LPARAM
a::LPB:
LPBYTE
a::LPC:
LPCTSTR
a::LPT:
LPTSTR
a::LR:
LRESULT
a::TC:
TCHAR
a::U:
UINT
a::ui:
unsigned int
a::ul:
unsigned long
a::UL:
ULONG
a::W:
WORD
a::WP:
WPARAM
a::N:
NULL
a::nn:
!= NULL
a::n0:
!= 0
a:GUID IMPLEMENT_OLECREATE:#guid:
// {$GUID_STRING$} 
IMPLEMENT_OLECREATE($GUID_Class$, $GUID_ExternalName$, 
$GUID_DEFINITION$);

a:DEFINE_GUID:#guid:
// {$GUID_STRING$} 
DEFINE_GUID($GUID_Name$, 
$GUID_DEFINITION$);

a:GUID struct instance:#guid:
// {$GUID_STRING$} 
static const GUID $GUID_InstanceName$ = 
{ $GUID_STRUCT$ };

a:GUID string:#guid:
"{$GUID_STRING$}"
a:IDL uuid:#uuid:
uuid($GUID_STRING$)
a::usi:
using namespace $end$;

a::class:
class $end$
{
public:
protected:
private:
};

a:class with prompt for name:class:
class $Class_name$
{
public:
	$Class_name$();
	~$Class_name$();
protected:
	$end$
private:
};

a:dynamic cast, run code on valid cast:dyna:
$New_type$ *$New_pointer$ = dynamic_cast<$New_type$ *>($Cast_this$);
if (NULL != $New_pointer$)
{
	$end$
}

a::struct:
struct
{
    $selected$
};
a:union:union:
union
{
    $selected$
};
a::switch:
switch ($end$)
{
	$selected$
}

a::switch:
switch ($end$)
{
    case :
	    break;
}

a:://-:
// $end$ [$MONTH$/$DAY$/$YEAR$ %USERNAME%]
a::///:
//////////////////////////////////////////////////////////////////////////

a::/*-:
/*
 *	$end$
 */
a::/**:
/*++

$end$

--*/

a://*://*:
//
// $end$
//
a:routine desc:/**f:
/*++

Routine Description:

    $end$

Arguments:

    

Return Value:

    

--*/

a:/*****/:/***:
/************************************************************************
  $end$
************************************************************************/
a:atoi(...)::
atoi($selected$)$end$
a:_T(...)::
_T($selected$)$end$
a:_T():tc:
_T($end$)
a:if () { ... }:if:
if ($end$)
{
	$selected$
}

a:if () { ... } else { }:if:
if ($end$)
{
	$selected$
} 
else
{
}

a:if () { } else { ... }::
if ($end$)
{
} 
else
{
	$selected$
}

a:while () { ... }:while:
while ($end$)
{
	$selected$
}

a:for () { ... }:for:
for ($end$)
{
	$selected$
}

a:for loop reverse:forr:
for (ULONG_PTR $Index$ = $Length$; $Index$ != 0; --$Index$)
{
	$end$
}

a:for loop forward:forf:
for (ULONG_PTR $Index$ = 0; $Index$ < $Length$; $Index$++)
{
	$end$
}

a:for loop forward equ:fore:
for (ULONG_PTR $Index$ = 0; $Index$ != $Length$; $Index$++)
{
	$end$
}

a:do { ... } while ():do:
do
{
	$selected$
} while ($end$);

a:try { ... } catch {} catch {} catch {}:try:
try
{
	$selected$
}
catch (CMemoryException* e)
{
	$end$
}
catch (CFileException* e)
{
}
catch (CException* e)
{
}

a:TRY { ... } CATCH {}:TRY:
TRY 
{
	$selected$
}
CATCH (CMemoryException, e)
{
	$end$
}
END_CATCH

a::bas:
$BaseClassName$::$MethodName$($MethodArgs$);


a::sup:
__super::$MethodName$($MethodArgs$);


a:#ifdef guard in a header::
#ifndef $FILE_BASE$_h__
#define $FILE_BASE$_h__

$selected$
#endif // $FILE_BASE$_h__

a:File header detailed:///fhd:
/********************************************************************
	created:	$DATE$
	created:	$DAY$:$MONTH$:$YEAR$   $HOUR$:$MINUTE$
	filename: 	$FILE$
	file path:	$FILE_PATH$
	file base:	$FILE_BASE$
	file ext:	$FILE_EXT$
	author:		$Author$
	
	purpose:	$end$
*********************************************************************/

a:Win32 standard application::
#include <windows.h>
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT ("$end$");
    HWND         hwnd;
    MSG          msg;
    WNDCLASSEX   wndclassex = {0};
    wndclassex.cbSize        = sizeof(WNDCLASSEX);
    wndclassex.style         = CS_HREDRAW | CS_VREDRAW;
    wndclassex.lpfnWndProc   = WndProc;
    wndclassex.cbClsExtra    = 0;
    wndclassex.cbWndExtra    = 0;
    wndclassex.hInstance     = hInstance;
    wndclassex.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
    wndclassex.hCursor       = LoadCursor (NULL, IDC_ARROW);
    wndclassex.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
    wndclassex.lpszMenuName  = NULL;
    wndclassex.lpszClassName = szAppName;
    wndclassex.hIconSm       = wndclassex.hIcon;
	
    if (!RegisterClassEx (&wndclassex))
    {
        MessageBox (NULL, TEXT ("RegisterClassEx failed!"), szAppName, MB_ICONERROR);
        return 0;
    }
    hwnd = CreateWindowEx (WS_EX_OVERLAPPEDWINDOW, 
		                  szAppName, 
        		          TEXT ("WindowTitle"),
                		  WS_OVERLAPPEDWINDOW,
		                  CW_USEDEFAULT, 
        		          CW_USEDEFAULT, 
                		  CW_USEDEFAULT, 
		                  CW_USEDEFAULT, 
        		          NULL, 
                		  NULL, 
		                  hInstance,
        		          NULL); 
						  
    ShowWindow (hwnd, iCmdShow);
    UpdateWindow (hwnd);
	
    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }
    return msg.wParam;
}
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (message)
    {
    case WM_CREATE:
        return (0);
		
    case WM_PAINT:
        hdc = BeginPaint (hwnd, &ps);
        TextOut (hdc, 0, 0, "A Window!", 27);
        EndPaint (hwnd, &ps);
        return (0);
		
    case WM_DESTROY:
        PostQuitMessage (0);
        return (0);
    }
    return DefWindowProc (hwnd, message, wParam, lParam);
}

a:Dialog procedure::
BOOL CALLBACK $end$ (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:
        {
			
        }
		return (TRUE);
	case WM_CLOSE:
        {
            EndDialog(hDlg,0);
        }
		return (TRUE);
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
            {
                SendMessage(hDlg, WM_CLOSE, 0, 0);
            }
            return (TRUE);
		case IDOK:
            {
                
            }
			return (TRUE);
		}
		return (FALSE);
	}
	return (FALSE);
}

a:Window procedure::
LRESULT CALLBACK $end$ (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (message)
    {
    case WM_CREATE:
        return (0);
		
    case WM_PAINT:
        hdc = BeginPaint (hwnd, &ps);
        
        EndPaint (hwnd, &ps);
        return (0);
		
    case WM_DESTROY:
        PostQuitMessage (0);
        return (0);
    }
    return DefWindowProc (hwnd, message, wParam, lParam);
}

readme:
VA Snippet used for suggestions of types:

a:SuggestionsForType bool::
true
false

readme:
VA Snippet used for suggestions of types:

a:SuggestionsForType BOOL::
TRUE
FALSE

readme:
VA Snippet used for suggestions of types:

a:SuggestionsForType HRESULT::
S_OK
S_FALSE

readme:
VA Snippet used for refactoring: Change Signature, Create Implementation, and Move Implementation to Source File.
Delete this item to restore the default upon next use.

a:Refactor Create Implementation::

$SymbolType$ $SymbolContext$( $ParameterList$ ) $MethodQualifier$
{
	$end$$MethodBody$
}

readme:
VA Snippet used for refactoring.
Delete this item to restore the default upon next use.

a:Refactor Document Method::
//************************************
// Method:    $SymbolName$
// FullName:  $SymbolContext$
// Access:    $SymbolVirtual$$SymbolPrivileges$$SymbolStatic$
// Returns:   $SymbolType$
// Qualifier: $MethodQualifier$
// Parameter: $MethodArg$
//************************************

readme:
VA Snippet used for refactoring.
Delete this item to restore the default upon next use.

a:Refactor Encapsulate Field::
	$end$$SymbolType$ $GeneratedPropertyName$() const { return $SymbolName$; }
	void $GeneratedPropertyName$($SymbolType$ val) { $SymbolName$ = val; }

readme:
VA Snippet used for refactoring.
Delete this item to restore the default upon next use.

a:Refactor Extract Method::

$end$$SymbolType$ $SymbolContext$( $ParameterList$ ) $MethodQualifier$
{
	$MethodBody$
}

readme:
VA Snippet used for refactoring.
Delete this item to restore the default upon next use.

a:Refactor Create From Usage Method Body::
throw std::exception("The method or operation is not implemented.");
readme:
VA Snippet used by Surround With #ifdef.
Delete this item to restore the default upon next use.

a:#ifdef (VA X):#if:
#ifdef $condition=_DEBUG$$end$
$selected$
#endif // $condition$

readme:
VA Snippet used by Surround With #region.
Delete this item to restore the default upon next use.

a:#region (VA X):#r:
#pragma region $end$$regionName$
$selected$
#pragma endregion $regionName$

readme:
Delete this item to restore the default when the IDE starts.

a:{...}::
{
	$end$$selected$
}

a:WinMainT:#winm:
#pragma comment(linker, "/ENTRY:tWinMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")

#include "MyLibrary.cpp"

ForceInline UInt WinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, PTChar lpCmdLine, Int nCmdShow)
{
    $selected$
    return 0;
}

Int WINAPI tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PTChar lpCmdLine, Int nCmdShow)
{
    TChar end;
    lpCmdLine = GetCommandLine();
    end = *lpCmdLine++ == '\"' ? '\"' : ' ';
    while (*lpCmdLine && *lpCmdLine != end) ++lpCmdLine;
    if (*++lpCmdLine)
    {
        while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;
    }
    ExitProcess(WinMain2(GetModuleHandle(NULL), 0, lpCmdLine, SW_SHOWDEFAULT));
}
readme:
Delete this item to restore the default when the IDE starts.

a:WinMain:#winmA:
#pragma comment(linker, "/ENTRY:WinMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")

#include "MyLibrary.cpp"

ForceInline UInt WinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, Int nCmdShow)
{
    $selected$
    return 0;
}

Int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, Int nCmdShow)
{
    Char end;
    lpCmdLine = GetCommandLineA();
    end = *lpCmdLine++ == '\"' ? '\"' : ' ';
    while (*lpCmdLine && *lpCmdLine != end) ++lpCmdLine;
    if (*++lpCmdLine)
    {
        while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;
    }
    ExitProcess(WinMain2(GetModuleHandleA(NULL), 0, lpCmdLine, SW_SHOWDEFAULT));
}
a:WinMainW:#winmw:
#pragma comment(linker, "/ENTRY:WinMain2")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")

#include "MyLibrary.cpp"

ForceInline ULONG WinMain2(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, LONG CmdShow)
{
    UNREFERENCED_PARAMETER(Instance);
    UNREFERENCED_PARAMETER(PrevInstance);
    UNREFERENCED_PARAMETER(CmdLine);
    UNREFERENCED_PARAMETER(CmdShow);

    $selected$

    return 0;
}

INT WINAPI wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, INT CmdShow)
{
    WCHAR end;

    UNREFERENCED_PARAMETER(Instance);
    UNREFERENCED_PARAMETER(PrevInstance);
    UNREFERENCED_PARAMETER(CmdShow);

    CmdLine = Nt_GetCommandLine();

    end = *CmdLine++ == '\"' ? '\"' : ' ';
    while (*CmdLine && *CmdLine != end) ++CmdLine;
    if (*++CmdLine)
    {
        while (*CmdLine == ' ' || *CmdLine == '\t') ++CmdLine;
    }

    return Nt_ExitProcess(WinMain2(Nt_GetExeModuleHandle(), 0, CmdLine, SW_SHOWDEFAULT));
}

a:DllMain:#dllm:
#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")

#include "MyLibrary.cpp"

BOOL UnInitialize(PVOID BaseAddress)
{
    return FALSE;
}

BOOL Initialize(PVOID BaseAddress)
{
    $selected$

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

a:Console Main:#conm:
#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")

#include "MyLibrary.cpp"

ForceInline Void main2(Long_Ptr argc, TChar **argv)
{
    $selected$
}

void __cdecl main(Long_Ptr argc, TChar **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}
a:Console MainW:#conmw:
#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")

#include "MyLibrary.cpp"

ForceInline Void main2(Long_Ptr argc, WChar **argv)
{
    $selected$
}

int __cdecl main(Long_Ptr argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    ReleaseArgv(argv);
    Nt_ExitProcess(0);
}
a:DriverEntry:#drvm:
#pragma comment(linker, "/ENTRY:DriverEntry")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna /subsystem:native")

#define _X86_ 1
#define _WIN32_WINNT 0x0502

#include <ntifs.h>
#include <ntstrsafe.h>
#include "MyLibrary.cpp"

VOID NTAPI DriverUnload(PDRIVER_OBJECT DriverObject)
{
    
}

NTSTATUS NTAPI DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    DriverObject->DriverUnload = DriverUnload;
    $selected$

    return STATUS_SUCCESS;
}

a:ifdef Guard in H:#ifdg:
#ifndef _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_
#define _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_

#include "MyLibrary.h"

$selected$

#endif // _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_

a:ifdef Guard in H:#ifdgt:
#ifndef _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_
#define _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_

#include "Object.h"

$selected$

#endif // _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_

a:#ifdgu:#ifdgu:
#ifndef _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_
#define _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_

#include "MyLibraryUser.h"

$selected$

#endif // _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_

a:#ifdgk:#ifdgk:
#ifndef _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_
#define _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_

#include "MyLibraryKernel.h"

$selected$

#endif // _$FILE_BASE_UPPER$_$FILE_EXT_UPPER$_$GUID_SYMBOL$_

a:Tls Callback:#tcb:
#pragma comment(linker, "/INCLUDE:__tls_used")

VOID NTAPI TlsCallBackFunction(PVOID ModuleBase, ULONG Reason, PVOID Reserved);
EXTC PIMAGE_TLS_CALLBACK _my_tls_callbacktbl[] = { TlsCallBackFunction, 0 };
EXTC IMAGE_TLS_DIRECTORY _tls_used = { (ULONG_PTR)&_my_tls_callbacktbl[countof(_my_tls_callbacktbl) - 1], _tls_used.StartAddressOfRawData, _tls_used.StartAddressOfRawData, (ULONG_PTR)_my_tls_callbacktbl, 0, 0 };

$selected$
a:Tls Callback2:#tcb2:
#pragma comment(linker, "/INCLUDE:__tls_used")

VOID NTAPI StubTlsCallBackFunction(PVOID ModuleBase, ULONG Reason, PVOID Reserved)
{
    return;
}

VOID NTAPI TlsCallBackFunction(PVOID ModuleBase, ULONG Reason, PVOID Reserved);
EXTC PIMAGE_TLS_CALLBACK _my_tls_callbacktbl[] = { StubTlsCallBackFunction, TlsCallBackFunction, 0 };
EXTC IMAGE_TLS_DIRECTORY _tls_used = { (ULONG_PTR)&_my_tls_callbacktbl[countof(_my_tls_callbacktbl) - 1], _tls_used.StartAddressOfRawData, _tls_used.StartAddressOfRawData, (ULONG_PTR)_my_tls_callbacktbl, 0, 0 };

$selected$
a:ConsoleHandlerRoutine:#chr:
Bool bCtrlC;

BOOL CALLBACK HandlerRoutine(ULONG CtrlType)
{
    switch(CtrlType)
    {
	    case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
        case CTRL_CLOSE_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            bCtrlC = True;
            return True;
    }
    return False;
}
readme:
Delete this item to restore the default when the IDE starts.

a:(...)::
($selected$)
a:ALT Msg Handler:#amh:
LRESULT $selected$(UINT uMsg, WPARAM wParam, LPARAM lParam, Bool& bHandled)
{
    
}
a:Windows Msg Handler:#wmh:
LRESULT CALLBACK $selected$(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    
}
a:Add Handler:#h:

DECL_HANDLER(Handle$selected$);
readme:
VA Snippet used for suggestions in loops.
Delete this item to restore the default upon next use.

a:SuggestionsForType loop::
continue;
break;

readme:
VA Snippet used for suggestions in switch statements.
Delete this item to restore the default upon next use.

a:SuggestionsForType switch::
case 
default:
break;

readme:
VA Snippet used for suggestions in class definitions.
Delete this item to restore the default upon next use.

a:SuggestionsForType class::
public:
private:
protected:
virtual
void
bool
string
static
const

readme:
VA Snippet used for suggestions of type VARIANT_BOOL.
Delete this item to restore the default upon next use.

a:SuggestionsForType VARIANT_BOOL::
VARIANT_TRUE
VARIANT_FALSE

readme:
VA Snippet used for suggestions of type HANDLE.
Delete this item to restore the default upon next use.

a:SuggestionsForType HANDLE::
INVALID_HANDLE_VALUE
NULL

readme:
VA Snippet used for refactoring: Create From Usage and Implement Interface.
Delete this item to restore the default upon next use.

a:Refactor Create From Usage Method Body (Managed)::
throw gcnew System::Exception("The method or operation is not implemented.");
readme:
VA Snippet used for refactoring: Create From Usage and Implement Interface.
Delete this item to restore the default upon next use.

a:Refactor Create From Usage Method Body (Platform)::
throw ref new Platform::Exception(E_NOTIMPL);
readme:
VA Snippet used for refactoring: Create From Usage and Implement Interface.
Delete this item to restore the default upon next use.

a:Refactor Create From Usage Method Body (C)::
assert(!"The method or operation is not implemented.");
readme:
VA Snippet used for refactoring: Create File.
Delete this item to restore the default upon next use.

a:Refactor Create Header File::
#pragma once

$body$$end$


readme:
VA Snippet used for refactoring: Create File.
Delete this item to restore the default upon next use.

a:Refactor Create Source File::
#include "$FILE_BASE$.h"

$body$$end$



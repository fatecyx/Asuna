#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "QQ2011.h"
#include "MyLibraryUser.cpp"

WCHAR szRegistryDB[0x10] = L"Registry.db";
WCHAR szRegistryDB_IM[0x20] = L"%lu\\QQ\\Registry.db";

TYPE_OF(SetWindowPos)           *StubSetWindowPos;
TYPE_OF(GetPrivateProfileIntW)  *StubGetPrivateProfileIntW;
BOOL (CDECL *StubUtilCoreCenterAddPlugin)(PWSTR PluginPath);

#define GROUP_WIDTH     722
#define GROUP_HEIGHT    671
#define BUDDY_WIDTH     506
#define BUDDY_HEIGHT    507

LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    WCHAR buf[0x100];
    swprintf(buf, L"%08X", ExceptionInfo->ContextRecord->Eip);
    MessageBoxW(NULL, buf, NULL, 64);
    return EXCEPTION_CONTINUE_SEARCH;
}

VOID WINAPI ShowDBClickPicture(PVOID Object, PWSTR PicturePath)
{
    SHELLEXECUTEINFOW ShellExecueInfo;

    ZeroMemory(&ShellExecueInfo, sizeof(ShellExecueInfo));
    ShellExecueInfo.cbSize  = sizeof(ShellExecueInfo);
    ShellExecueInfo.lpFile  = PicturePath;
    ShellExecueInfo.lpVerb  = L"open";

    ShellExecuteExW(&ShellExecueInfo);
}

BOOL
WINAPI
HookSetWindowPos(
    HWND    hWnd,
    HWND    hWndInsertAfter,
    int     X,
    int     Y,
    int     cx,
    int     cy,
    UINT    Flags
)
{
    BOOL Success;
    LONG BuddyWidth     = 697;
    LONG BuddyHeight    = 520;
    LONG GroupWidth     = 600;
    LONG GroupHeight    = 521;

    if (
        (cx == BuddyWidth && cy == BuddyHeight) ||
        (cx == GroupWidth && cy == GroupHeight)
       )
    {
        RECT WorkArea;

        SystemParametersInfoW(SPI_GETWORKAREA, 0, &WorkArea, 0);

        if (cx == BuddyWidth)
        {
            cx = BUDDY_WIDTH;
            cy = BUDDY_HEIGHT;
        }
        else
        {
            cx = GROUP_WIDTH;
            cy = GROUP_HEIGHT;
        }

        X = ((WorkArea.right - WorkArea.left) - cx) / 2;
        Y = ((WorkArea.bottom - WorkArea.top) - cy) / 2;

        CLEAR_FLAG(Flags, SWP_NOSIZE);
    }

    return StubSetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, Flags);
}

UINT WINAPI HookGetPrivateProfileIntW(LPCWSTR lpAppName, LPCWSTR lpKeyName, INT nDefault, LPCWSTR lpFileName)
{
    UINT UserDataSavePathType;
    UserDataSavePathType = StubGetPrivateProfileIntW(lpAppName, lpKeyName, nDefault, lpFileName);
    if (!StrICompareW(lpKeyName, L"UserDataSavePathType"))
        return UserDataSavePathType == 1 ? 0 : UserDataSavePathType;

    return UserDataSavePathType;
}

BOOL CDECL UtilCoreCenterAddPlugin(PWSTR PluginPath)
{
    if (!Nt_IsPathExists(PluginPath))
        return FALSE;

    return StubUtilCoreCenterAddPlugin(PluginPath);
}

typedef struct
{
    ULONG Length;
    ULONG MaximumLength;
    PWSTR Buffer;
} LARGE_UNICODE_STRING, *PLARGE_UNICODE_STRING;

VOID (FASTCALL *StubCheckSecurityUrl)(PVOID This, PVOID, BOOL IsUrlString, PWSTR Url);

VOID FASTCALL CheckSecurityUrl(PVOID This, PVOID, BOOL IsUrlString, PWSTR Url)
{
    static WCHAR SafeUrl[] = L"www.qq.com";

    struct
    {
        PVOID Unknown;
        ULONG Unknown2;
        ULONG Length;
        ULONG MaximumLength;
        WCHAR Buffer[1];

    } PrevUrl, *UrlBuffer;

    if (!IsUrlString)
    {
        StubCheckSecurityUrl(This, NULL, IsUrlString, Url);
        return;
    }

    PWSTR PrevUrlBuffer;

    UrlBuffer = (TYPE_OF(UrlBuffer))FIELD_BASE(Url, TYPE_OF(*UrlBuffer), Buffer);

    PrevUrl                     = *UrlBuffer;
    UrlBuffer->Length           = CONST_STRLEN(SafeUrl) * sizeof(WCHAR);
    UrlBuffer->MaximumLength    = CONST_STRLEN(SafeUrl) * sizeof(WCHAR);

    static const ULONG BackupLength = CONST_STRLEN(SafeUrl) * sizeof(WCHAR) + sizeof(WCHAR);

    PrevUrlBuffer = (PWSTR)AllocStack(BackupLength);
    CopyMemory(PrevUrlBuffer, Url, BackupLength);
    CopyStruct(UrlBuffer->Buffer, SafeUrl, BackupLength);
    StubCheckSecurityUrl(This, NULL, IsUrlString, Url);
    CopyMemory(UrlBuffer->Buffer, PrevUrlBuffer, BackupLength);

    *UrlBuffer = PrevUrl;
}

typedef HRESULT (STDCALL *QQGetConfigByNameRoutine)(IQQGetConfigData *Object, PWSTR ConfigName, PVOID ConfigData);
typedef HRESULT (CDECL *GetConfigFieldDataRoutine)(PWSTR Platform, PWSTR ConfigName, IQQGetConfigData **Interface);

QQGetConfigByNameRoutine    StubQQGetConfigByName;
GetConfigFieldDataRoutine   StubQQGetConfigFieldData;

// Common.ModuleConfig::GetConfigFieldData
// ?GetConfigFieldData@ModuleConfig@@YAJPB_W0PAPAUITXDataRead@@@Z
HRESULT STDCALL QQGetConfigByName(IQQGetConfigData *Object, PWSTR ConfigName, PVOID ConfigData)
{
    PULONG Data = (PULONG)ConfigData;

    typedef struct
    {
        PWSTR Config;
        ULONG Data;

    } CONFIG_DATA_MAP;

    static CONFIG_DATA_MAP DataMap[] =
    {
        { L"GroupDefaultWidthWithSideBar",  GROUP_WIDTH     },
        { L"GroupDefaultHeightWithSideBar", GROUP_HEIGHT    },
        { L"BuddyDefaultWidthWithSideBar",  BUDDY_WIDTH     },
        { L"BuddyDefaultHeightWithSideBar", BUDDY_HEIGHT    },
    };

    CONFIG_DATA_MAP *p = DataMap;

    if (Data == NULL)
        Data = (PULONG)&Data;

    for (ULONG Count = countof(DataMap); Count != 0; ++p, --Count)
    {
    	if (!StrICompareW(p->Config, ConfigName))
        {
            *Data = p->Data;
            return S_OK;
        }
    }

    return StubQQGetConfigByName(Object, ConfigName, ConfigData);
}

HRESULT CDECL QQGetConfigFieldData(PWSTR Platform, PWSTR ConfigName, IQQGetConfigData **Interface)
{
    HRESULT Result;

    Result = StubQQGetConfigFieldData(Platform, ConfigName, Interface);
    if (FAILED(Result))
        return Result;

    if (!StrICompareW(ConfigName, L"BuddyAIOcfg") ||
        !StrICompareW(ConfigName, L"GroupAIOcfg"))
    {
        MEMORY_FUNCTION_PATCH f[] =
        {
            INLINE_HOOK_JUMP((*Interface)->lpVtbl->GetConfigByName, QQGetConfigByName, StubQQGetConfigByName),
        };

        Nt_PatchMemory(NULL, 0, f, countof(f), NULL);
        Nt_RestoreMemory(&StubQQGetConfigFieldData);
    }

    return Result;
}

VOID CDECL TXLogSafe(PWSTR Title, PWSTR Format, va_list arg)
{
    wprintf(L"%s\n", Title);
    vwprintf(Format, arg);
    wprintf(L"\n\n");
}

VOID CDECL TXLog(PVOID, PWSTR Title, PWSTR Format, va_list arg)
{
    wprintf(L"%s\n", Title);
    vwprintf(Format, arg);
    wprintf(L"\n");
    wprintf(L"return addr = %08X, module = %s\n", _ReturnAddress(), Nt_FindLdrModuleByHandle(_ReturnAddress())->BaseDllName.Buffer);
    wprintf(L"\n");
}

BOOL UnInitialize(PVOID BaseAddress)
{
    return FALSE;
}

BOOL Initialize(PVOID BaseAddress)
{
    BOOL                        Wow64;
    NTSTATUS                    Status;
//    PVOID                       CommonBase;
//    IQQGetConfigData           *GetConfigData;

    LdrDisableThreadCalloutsForDll(BaseAddress);
/*
    setlocale(LC_ALL, ".936");
    Nt_DeleteFile(L"E:\\Desktop\\QQ2009\\Bin\\log.txt");
    _wfreopen(L"E:\\Desktop\\QQ2009\\Bin\\log.txt", L"w", stdout);
*/

//    VOID (CDECL *GetConfigFieldData)(PWSTR Platform, PWSTR ConfigName, IQQGetConfigData **Interface);

//    RtlAddVectoredExceptionHandler(TRUE, VectoredHandler);
    Wow64 = Nt_IsWow64Process(NtCurrentProcess());
    if (Wow64)
    {
        wcscpy(szRegistryDB + 8, L"_x64.db");
        wcscpy(szRegistryDB_IM + 14, L"_x64.db");
    }

//    CommonBase = Nt_LoadLibrary(L"Common.dll");
//    if (CommonBase == NULL)
//        return FALSE;

//    *(PVOID *)&GetConfigFieldData = Nt_GetProcAddress(CommonBase, "?GetConfigFieldData@ModuleConfig@@YAJPB_W0PAPAUITXDataRead@@@Z");
//    if (GetConfigFieldData == NULL)
//        return FALSE;

    /************************************************************************
    UNICODE GroupDefaultHeightWithSidebar

    mov     r32, dword ptr [r32+const]
    mov     r32, dword ptr [r32+const]
    mov     r32, dword ptr [r32-const]
    mov     dword ptr [r32], r32
    mov     dword ptr [r32+const], r32
    jmp     short const
    ************************************************************************/
/*
    MEMORY_FUNCTION_PATCH func_groupapp[] =
    {
        // GroupDefaultWidthWithSideBar
        PATCH_FUNCTION(CALL, 0, 0x846C8, FixGroupSize),
    };
*/

    /************************************************************************
    UNICODE BuddyDefaultHeightWithSidebar

    mov     r32, dword ptr [r32+const]
    mov     r32, dword ptr [r32+const]
    mov     r32, dword ptr [r32-const]
    mov     dword ptr [r32], r32
    mov     dword ptr [r32+const], r32
    jmp     short const

    jmp     short const
    mov     edi, dword ptr [ebp-0x18]
    neg     edi

    cmp     dword ptr [ebp-0x44], 0x0
    ja      const
    jb      short const
    cmp     dword ptr [ebp-0x48], 0x500000

    call Util::Contact::IsOnline
    add     esp, 0x4
    test    eax, eax
    jnz long const
    ...
    operator wchar_t *
    ~CTXBSTR
    // CCsGetOfflinePicLimit
    ************************************************************************/
    MEMORY_PATCH patch_appframe[] =
    {
        /*++
            jmp     short const
            mov     edi, dword ptr [ebp-0x18]
            neg     edi
        --*/
        PATCH_MEMORY(0xFF33,   0x02, 0xDA444),  // 聊天窗口大小

        /*++
            cmp     dword ptr [ebp-0x44], 0x0
            ja      const
            jb      short const
            cmp     dword ptr [ebp-0x48], 0x500000
        --*/
        PATCH_MEMORY(0x80,     0x01, 0x091A47),  // 图片大小限制
        PATCH_MEMORY(0x81,     0x01, 0x119EAE),  // 图片大小限制

        /*++
          call Util::Contact::IsOnline
          add     esp, 0x4
          test    eax, eax
          jnz long const
          ...
          operator wchar_t *
          ~CTXBSTR
            // CCsGetOfflinePicLimit
        --*/
        PATCH_MEMORY(0x81,     0x01, 0x099C2A),  // 离线图片大小限制   Util::Contact::IsOnline
    };

    MEMORY_FUNCTION_PATCH func_appframe[] =
    {
        // wURLTipsID
        // ShowWindow
        PATCH_FUNCTION(CALL, FIRST_CALL_TO_JUMP | AUTO_DISASM2, 0x8B4F6, CheckSecurityUrl, 0, &StubCheckSecurityUrl),
    };

    MEMORY_PATCH patch_kernelutil[] =
    {
        /************************************************************************
            mov     r32, dword ptr [r32-const]
            cmp     r32, const
            jg      short const
        ************************************************************************/
        PATCH_MEMORY(0x4CEB,                    0x02,   0x121CE), // 发图+表情无限制  0x500000
        PATCH_MEMORY(0xEB,                      0x01,   0x1214A), // 群图片大小限制
        PATCH_MEMORY(szRegistryDB,              0x04,   0x420BF), // registry.db LoginInfo  find ref: 1 5 6 7
//        PATCH_MEMORY(szRegistryDB,              0x04,   0x44D45), // registry.db UserDataRoot
        PATCH_MEMORY(szRegistryDB,              0x04,   0x46AF7), // registry.db UserDataPubRegistry
        PATCH_MEMORY(szRegistryDB,              0x04,   0x46B31), // registry.db UserDataRegistry
        PATCH_MEMORY(HookGetPrivateProfileIntW, 0x04,   0x684A4), // 强制"保存到安装目录"
    };

    MEMORY_PATCH patch_chatframeapp[] =
    {
        /************************************************************************
            窗口全部居中
            cmp r32, -1
            jnb const
            xxxxx
            ret 4
                <- jnb to here
            xxxx
            mov r32, dword ptr [GetSystemMetrics]
            call r32
            call r32
        ************************************************************************/
        PATCH_MEMORY(0x00, 0x01, 0x96CCE),

        /************************************************************************
            不提示有窗口未关闭
            CF_MESSAGE_TITLE
            push eax
            mov [ebp+const], ebx
            call const
            cmp  dword ptr [ebp-const], ebx
            jbe long const
        ************************************************************************/
        PATCH_MEMORY(0x81, 0x01, 0x54136),

        /************************************************************************
            去插件检测
            mov edi, eax
            call const
            add esp,2c
            cmp edi, ebx
            je short const
        ************************************************************************/
        PATCH_MEMORY(0x3D, 0x01, 0x07DC3),
    };

    MEMORY_PATCH patch_msgmgr[] =
    {
        PATCH_MEMORY(0x3D, 0x01, 0x374B3),  // 去插件检测 1 to last
    };

    MEMORY_PATCH patch_afutil[] =
    {
        PATCH_MEMORY(0x02, 0x01, 0x1F7DC),   // |= CC_FULLOPEN 102
    };

    MEMORY_PATCH patch_apputil[] =
    {
        /************************************************************************
            自校验
            je const
            mov dword[ebp-const], const
            mov dword[ebp-const], const
            mov dword[ebp-const], const
            mov [ebp-const], esi
            mov [ebp-const], esi

            dlc fail
            plugin security check failed
        ************************************************************************/
        PATCH_MEMORY(0xEB, 0x01, 0x05CAE),
        PATCH_MEMORY(0xEB, 0x01, 0x12F1D),
    };

    MEMORY_PATCH patch_appmisc[] =
    {
        /************************************************************************
            PluginListCheck

            call const
            add esp, 1c
            test eax, eax
            jnz const

            OnInitPluginListSuccess
        ************************************************************************/
        PATCH_MEMORY(0xB8, 0x01, 0x14935D),
    };

    MEMORY_FUNCTION_PATCH func_appmisc[] =
    {
        PATCH_FUNCTION(JUMP, 0, 0x1E6FC0, ShowDBClickPicture),    // PicPath
        INLINE_HOOK_JUMP(SetWindowPos, HookSetWindowPos, StubSetWindowPos),
    };

    MEMORY_PATCH patch_common[] =
    {
        PATCH_MEMORY(szRegistryDB,  0x04,   0xBE746),   // registry.db   find ref all
    };

    MEMORY_FUNCTION_PATCH func_common[] =
    {
//        INLINE_HOOK_JUMP(GetConfigFieldData, QQGetConfigFieldData, StubQQGetConfigFieldData),
        INLINE_HOOK_JUMP_RVA(0x2B197, UtilCoreCenterAddPlugin, StubUtilCoreCenterAddPlugin),
//        PATCH_FUNCTION(JUMP, 0, 0x8074A, TXLog),
//        PATCH_FUNCTION(0, 0, IMAGE_INVALID_RVA),
    };

    MEMORY_PATCH patch_im[] =
    {
        PATCH_MEMORY(szRegistryDB_IM,   0x04,   0x2A3422),  // %lu\QQ\Registry.db find ref all
        PATCH_MEMORY(szRegistryDB_IM,   0x04,   0x2A4142),  // %lu\QQ\Registry.db
    };

    PATCH_SET lppatch[] =
    {
//        { L"GroupApp.dll",      NULL,               0,                          func_groupapp, countof(func_groupapp)   },
        { L"AppFramework.dll",  patch_appframe,     countof(patch_appframe),    },
        { L"ChatFrameApp.dll",  patch_chatframeapp, countof(patch_chatframeapp) },
        { L"AppUtil.dll",       patch_apputil,      countof(patch_apputil),     },
        { L"AFUtil.dll",        patch_afutil,       countof(patch_afutil),      },
        { L"AppMisc.dll",       patch_appmisc,      countof(patch_appmisc),     func_appmisc,   countof(func_appmisc)   },
        { L"MsgMgr.dll",        patch_msgmgr,       countof(patch_msgmgr),      },
        { L"Common.dll",        patch_common,       countof(patch_common),      func_common,    countof(func_common)    },
        { L"IM.dll",            patch_im,           countof(patch_im),          },
        { L"KernelUtil.dll",    patch_kernelutil,   countof(patch_kernelutil)   },
    };

    DWORD          OldProtect, dwOld2;
    ULONG          ulProtectSize;
    UNICODE_STRING ustrDll;

    for (int j = 0; j != countof(lppatch); ++j)
    {
        RtlInitUnicodeString(&ustrDll, lppatch[j].DllName);
        Status = LdrLoadDll(NULL, NULL, &ustrDll, &BaseAddress);
        if (!NT_SUCCESS(Status))
        {
            continue;
        }

        Nt_PatchMemory(lppatch[j].Patch, lppatch[j].PatchCount, lppatch[j].Function, lppatch[j].FunctionCount, BaseAddress);
    }

    *(PULONG_PTR)&StubGetPrivateProfileIntW = patch_kernelutil[countof(patch_kernelutil) - 1].DataBak;

    LOOP_ONCE
    {
        WCHAR c, *szCmdLine, *szNumber;
        LPVOID lpBase;

        static WCHAR szQQNumber[20];

        szCmdLine   = Nt_GetCommandLine();

        c = szCmdLine[0] == '\"' ? szCmdLine[0] : ' ';
        ++szCmdLine;
        while (*szCmdLine != c) ++szCmdLine;
        ++szCmdLine;
        while (*szCmdLine == ' ' || *szCmdLine == 0x9) ++szCmdLine;
        if (*szCmdLine++ == '/')
        {
            if (StrNICompareW(szCmdLine, L"START", 5))
            {
                break;
            }
            szCmdLine += 5;
            while (*szCmdLine == ' ' || *szCmdLine == '\t') ++szCmdLine;
            if (StrNICompareW(szCmdLine, L"QQUIN:", 6))
            {
                break;
            }
            szCmdLine += 6;
            szNumber = szCmdLine;
            while (*szCmdLine != ' ' && *szCmdLine != '\t' && *szCmdLine != 0) ++szCmdLine;
            c = *szCmdLine;
            *szCmdLine = 0;
            wcscpy(szQQNumber, szNumber);
            if (Wow64)
                wcscat(szQQNumber, L"_x64");
            wcscat(szQQNumber, L".db");
            BaseAddress = (PBYTE)BaseAddress + 0x45FF2;     // find ref: 2 3    GlobalDataPublic
            Status = Nt_ProtectMemory(NtCurrentProcess(), BaseAddress, 0x50, PAGE_EXECUTE_READWRITE, &OldProtect);
            if (NT_SUCCESS(Status))
            {
                *(LPWSTR *)BaseAddress = szQQNumber;
                *(LPWSTR *)(0x40 + (DWORD)BaseAddress) = szQQNumber;
                Nt_ProtectMemory(NtCurrentProcess(), BaseAddress, 0x50, OldProtect, &OldProtect);
            }

            *szCmdLine = c;
        }
    }

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

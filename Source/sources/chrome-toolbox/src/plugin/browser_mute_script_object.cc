#include "browser_mute_script_object.h"

#include <Psapi.h>
#include <TlHelp32.h>

#include "browser_mute_plugin.h"
#include "Log.h"
#include "utils.h"

extern Log g_log;
extern HMODULE g_module;

NPObject* BrowserMuteScriptObject::Allocate(NPP npp, NPClass *aClass) {
  BrowserMuteScriptObject* script_object = new BrowserMuteScriptObject;
  char logs[256];
  sprintf(logs, "BrowserMuteScriptObject this=%ld", script_object);
  g_log.WriteLog("Allocate", logs);
  if (script_object != NULL) {
    script_object->set_plugin((PluginBase*)npp->pdata);
  }
  return script_object;
}

void BrowserMuteScriptObject::InitHandler() {
  FunctionItem item;
  item.function_name = "MuteBrowser";
  item.function_pointer = ON_INVOKEHELPER(
      &BrowserMuteScriptObject::MuteBrowser);
  AddFunction(item);
  item.function_name = "CheckMuteAvailable";
  item.function_pointer = ON_INVOKEHELPER(
      &BrowserMuteScriptObject::CheckMuteAvailable);
  AddFunction(item);
}

void BrowserMuteScriptObject::Deallocate() {
  char logs[256];
  sprintf_s(logs, "BrowserMuteScriptObject this=%ld", this);
  g_log.WriteLog("Deallocate", logs);
  delete this;
}

bool BrowserMuteScriptObject::MuteBrowser(const NPVariant *args,
                                          uint32_t argCount,
                                          NPVariant *result) {
  if (argCount != 1 || !NPVARIANT_IS_BOOLEAN(args[0]))
    return false;

  mute_flag_ = NPVARIANT_TO_BOOLEAN(args[0]);

  if (!((BrowserMutePlugin*)get_plugin())->get_use_api_hook_flag())
    return true;
  
  g_log.WriteLog("Msg", "SetBrowserMute");

  if (!api_hook_module_) {
    HANDLE hmodule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 
                                              GetCurrentProcessId());
    if (hmodule == INVALID_HANDLE_VALUE) {
      g_log.WriteLog("Error", "TH32CS_SNAPMODULE");
    }
    MODULEENTRY32 mod = { sizeof(MODULEENTRY32) };
    BOOL flag = FALSE;
    if (Module32First(hmodule, &mod)) {
      while(Module32Next(hmodule, &mod)) {
        if (_tcsicmp(mod.szModule, _T("mutechrome.dll")) == 0 ||
            _tcsicmp(mod.szModule, _T("apihook.dll")) == 0) {
          flag = TRUE;
          api_hook_module_ = mod.hModule;
          break;
        }
      }        
    }
    if (hmodule != INVALID_HANDLE_VALUE)
      CloseHandle(hmodule);

    if (!flag) {
      TCHAR dllpath[MAX_PATH*2];
      GetModuleFileName(g_module, dllpath, MAX_PATH);
      TCHAR* postfix = _tcsrchr(dllpath, '\\');
      if (postfix != NULL) {
        *(postfix+1) = 0;
        _tcscat(dllpath, _T("mutechrome.dll"));
        g_log.WriteLog("Msg", "Before LoadLibrary");
        api_hook_module_ = LoadLibrary(dllpath);
        g_log.WriteLog("Msg", "After LoadLibrary");
      }
    }
    set_browser_mute_ = (Pfn_SetBrowserMute)GetProcAddress(api_hook_module_, 
                                                            "SetBrowserMute");
    g_log.WriteLog("Msg", "After GetProcAddress");
    if (set_browser_mute_) {
      set_browser_mute_(NPVARIANT_TO_BOOLEAN(args[0]));
      g_log.WriteLog("Msg", "SetBrowserMute1");
    }
  } else {
    if (set_browser_mute_) {
      set_browser_mute_(NPVARIANT_TO_BOOLEAN(args[0]));
      g_log.WriteLog("Msg", "SetBrowserMute2");
    }
  }

  return true;
}

bool BrowserMuteScriptObject::CheckMuteAvailable(const NPVariant *args, 
                                                 uint32_t argCount, 
                                                 NPVariant *result) {
  INT32_TO_NPVARIANT(kUnavailableMute, *result);
  if (utils::GetWinVersion() == utils::WINVERSION_WIN7) {
    INT32_TO_NPVARIANT(kAvailableMute, *result);
  } else {
    // Get parent process id;
    DWORD parent_pid = 0;
    DWORD current_process_id = GetCurrentProcessId();
    HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process = { sizeof(PROCESSENTRY32) };
    BOOL ret = Process32First(hprocess, &process);

    while (ret) {
      if (process.th32ProcessID == current_process_id) {
        parent_pid = process.th32ParentProcessID;
        break;
      }
      ret = Process32Next(hprocess, &process);
    }
    if (hprocess != INVALID_HANDLE_VALUE)
      CloseHandle(hprocess);

    // Get gcswf32.dll process.
    bool find_gcswf32_flag = false;
    bool find_apihook_flag = false;

    hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    TCHAR exe_name[MAX_PATH];
    GetModuleBaseName(
        GetCurrentProcess(), GetModuleHandle(NULL), exe_name, MAX_PATH);
    ret = Process32First(hprocess, &process);
    while (ret) {
      if (process.th32ParentProcessID != parent_pid || 
          _tcsicmp(process.szExeFile, exe_name) != 0) {
        ret = Process32Next(hprocess, &process);
        continue;
      }

      find_apihook_flag = false;
      find_gcswf32_flag = false;

      HANDLE hmodule = CreateToolhelp32Snapshot(
          TH32CS_SNAPMODULE, process.th32ProcessID);
      MODULEENTRY32 mod = { sizeof(MODULEENTRY32) };
      if (Module32First(hmodule, &mod)) {
        while(Module32Next(hmodule, &mod)) {
          if (_tcsicmp(mod.szModule, _T("gcswf32.dll")) == 0)
            find_gcswf32_flag = true;
          if (_tcsicmp(mod.szModule, _T("mutechrome.dll")) == 0 ||
              _tcsicmp(mod.szModule, _T("apihook.dll")) == 0) {
            find_apihook_flag = true;
          }
        }
      }
      if (hmodule != INVALID_HANDLE_VALUE)
        CloseHandle(hmodule);

      if (find_gcswf32_flag)
        break;
      ret = Process32Next(hprocess, &process);
    }
    if (hprocess != INVALID_HANDLE_VALUE)
      CloseHandle(hprocess);

    // Injected flash plugin process.
    if (find_gcswf32_flag && find_apihook_flag) {
      INT32_TO_NPVARIANT(kAvailableMute, *result);
    } else if (find_gcswf32_flag) {  // flash plugin process in sandbox.
      INT32_TO_NPVARIANT(kUnavailableMute, *result);
    } else {  // Not find flash plugin process.
      INT32_TO_NPVARIANT(kFlashPluginNotRun, *result);
    }
  }
  return true;
}
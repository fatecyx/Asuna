#include "browser_mute_plugin.h"

#include <map>

#include <Audiopolicy.h>
#include <Mmdeviceapi.h>
#include <Psapi.h>
#include <winternl.h>
#include <TlHelp32.h>

#include "browser_mute_script_object.h"
#include "log.h"
#include "script_object_factory.h"
#include "utils.h"

extern Log g_log;
extern HMODULE g_module;

#define CHECK_RESULT(hr)     if (FAILED(hr)) {\
  Sleep(100);\
  continue;\
}

#define MAX_PROCESS_COUNT   1024

typedef NTSTATUS (NTAPI *pfnNtQueryInformationProcess)(
    IN  HANDLE ProcessHandle,
    IN  PROCESSINFOCLASS ProcessInformationClass,
    OUT PVOID ProcessInformation,
    IN  ULONG ProcessInformationLength,
    OUT PULONG ReturnLength OPTIONAL);

bool BrowserMutePlugin::InjectIntoProcess(HANDLE hprocess) {
  // allocate remote process memory address
  TCHAR dllpath[MAX_PATH];
  LPVOID memory_pointer = VirtualAllocEx(
      hprocess, NULL, sizeof(dllpath), MEM_COMMIT | MEM_RESERVE, 
      PAGE_READWRITE);

  char logs[256];
  if (memory_pointer) {
    // get absolute path of mutechrome.dll 
    GetModuleFileName(g_module, dllpath, MAX_PATH);
    TCHAR* postfix = _tcsrchr(dllpath, '\\');
    if (postfix == NULL)
      return false;
    *(postfix + 1) = 0;
    _tcscat(dllpath, _T("mutechrome.dll"));

    BOOL ret = WriteProcessMemory(hprocess, memory_pointer, dllpath, 
                                  sizeof(dllpath), NULL);
    if (!ret) {
      sprintf(logs, "WriteProcessMemory Failed,GetLastError=%ld", 
              GetLastError());
      g_log.WriteLog("Error", logs);
      return false;
    }
    HANDLE remote_thread = CreateRemoteThread(
        hprocess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, 
        memory_pointer, 0, NULL);
    if (remote_thread) {
      g_log.WriteLog("Msg", "CreateRemoteThread Success");
      CloseHandle(remote_thread);
      return true;
    } else {
      sprintf(logs, "CreateRemoteThread Failed,GetLastError=%ld", 
              GetLastError());
      g_log.WriteLog("Error", logs);
    }
  } else {
    sprintf(logs, "VirtualAllocEx Failed,GetLastError=%ld", GetLastError());
    g_log.WriteLog("Error", logs);
  }
  return false;
}

void BrowserMutePlugin::RenameApiHookDll() {
  TCHAR dllpath[MAX_PATH] = _T("");
  TCHAR newdllpath[MAX_PATH] = _T("");
  GetModuleFileName(g_module, dllpath, MAX_PATH);
  _tcscpy(newdllpath, dllpath);
  TCHAR* postfix = _tcsrchr(newdllpath, '\\');
  if (postfix != NULL) {
    *(postfix+1) = 0;
    _tcscat(newdllpath, _T("mutechrome.dll"));
  }
  postfix = _tcsrchr(dllpath, '\\');
  if (postfix != NULL) {
    *(postfix+1) = 0;
    _tcscat(dllpath, _T("apihook.dll"));
  }
  FILE* src_file = _tfopen(dllpath, _T("rb"));
  FILE* dest_file = _tfopen(newdllpath, _T("wb"));
  if (src_file && dest_file) {
    byte buffer[1024];
    int len = fread(buffer, 1, 1024, src_file);
    while (len > 0) {
      fwrite(buffer, 1, len, dest_file);
      len = fread(buffer, 1, 1024, src_file);
    }
    fclose(src_file);
    fclose(dest_file);
  }
}

DWORD BrowserMutePlugin::Mute_Thread(void* param) {
  BrowserMutePlugin* plugin = (BrowserMutePlugin*)param;
  g_log.WriteLog("msg", "Start Mute_Thread");
  CoInitialize(NULL);

  HRESULT hr = E_FAIL;
  IMMDeviceEnumerator* device_enumerator;
  IMMDevice* defaultdevice;
  IAudioSessionManager2* audio_session_mamanger2;
  IAudioSessionEnumerator* audio_session_enumerator;
  ISimpleAudioVolume* simple_audio_volume;
  BOOL mute_flag = FALSE;
  std::map<DWORD,DWORD> chrome_process_map;
  DWORD parent_pid = 0;

  // get parent process id
  HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 process = { sizeof(PROCESSENTRY32) };
  BOOL ret = Process32First(hprocess, &process);
  while (ret) {
    if (process.th32ProcessID == GetCurrentProcessId()) {
      parent_pid = process.th32ParentProcessID;
      break;
    }
    ret = Process32Next(hprocess, &process);
  }
  if (hprocess != INVALID_HANDLE_VALUE)
    CloseHandle(hprocess);

  hr = CoCreateInstance(
      __uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, 
      __uuidof(IMMDeviceEnumerator), (void**)&device_enumerator);
  if (FAILED(hr))
    return hr;

  DWORD process_list[MAX_PROCESS_COUNT], needed, process_count;

  while(WaitForSingleObject(plugin->stop_event_, 1000) == WAIT_TIMEOUT) {
    if (plugin->script_object_ == NULL)
      continue;
    mute_flag = ((BrowserMuteScriptObject*)plugin->script_object_)->
          get_mute_flag();

    chrome_process_map.clear();

    if (!EnumProcesses(process_list, sizeof(process_list), &needed))
      continue;
    process_count = needed / sizeof(DWORD);
    
    PROCESS_BASIC_INFORMATION process_info;
    pfnNtQueryInformationProcess pfnQIP = (pfnNtQueryInformationProcess)
        GetProcAddress(plugin->ntdll_handle_, "NtQueryInformationProcess");
    if (!pfnQIP)
      continue;

    for (int i = 0; i < process_count; i++) {
      if(process_list[i] == 0)
        continue;
      TCHAR process_name[MAX_PATH] = _T("");
      ULONG return_len;
      HANDLE hprocess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                    PROCESS_VM_READ, FALSE, process_list[i]);

      if (hprocess != NULL) {
        NTSTATUS status = pfnQIP(hprocess, ProcessBasicInformation, 
                                 &process_info, sizeof(process_info), 
                                 &return_len);
        DWORD parentid = (DWORD)process_info.Reserved3;
        if (status >= 0 && (parentid == parent_pid || 
            process_info.UniqueProcessId == parent_pid)) {
          chrome_process_map.insert(std::make_pair(
              process_info.UniqueProcessId, process_info.UniqueProcessId));
        }
        CloseHandle(hprocess);
      }
    }

    CHECK_RESULT(device_enumerator->GetDefaultAudioEndpoint(
        eRender, eConsole, &defaultdevice));

    CHECK_RESULT(defaultdevice->Activate(
        __uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, 
        (void**)&audio_session_mamanger2));

    CHECK_RESULT(audio_session_mamanger2->
        GetSessionEnumerator(&audio_session_enumerator));

    int count;
    CHECK_RESULT(audio_session_enumerator->GetCount(&count));

    for (int i = 0; i < count; i++) {
      IAudioSessionControl* audio_session_control;
      IAudioSessionControl2* audio_session_control2;
      CHECK_RESULT(audio_session_enumerator->
          GetSession(i, &audio_session_control));
      CHECK_RESULT(audio_session_control->QueryInterface(
          __uuidof(IAudioSessionControl2), (void**)&audio_session_control2));
      DWORD processid;
      CHECK_RESULT(audio_session_control2->GetProcessId(&processid));
      if (chrome_process_map.find(processid) != chrome_process_map.end()) {
        CHECK_RESULT(audio_session_control2->QueryInterface(
            __uuidof(ISimpleAudioVolume), (void**)&simple_audio_volume));
        CHECK_RESULT(simple_audio_volume->SetMute(mute_flag, NULL));
        simple_audio_volume->Release();
      }
      audio_session_control->Release();
      audio_session_control2->Release();
    }

    audio_session_mamanger2->Release();
    audio_session_enumerator->Release();
    defaultdevice->Release();
  }
  CoUninitialize();
  g_log.WriteLog("msg", "Stop Mute_Thread");

  return 0;
}

void BrowserMutePlugin::ScanAndInject() {
  DWORD parent_pid = 0;
  BOOL find_apihook_flag = FALSE;

  // Get parent process id
  HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 process = { sizeof(PROCESSENTRY32) };
  BOOL ret = Process32First(hprocess, &process);
  while (ret) {
    if (process.th32ProcessID == GetCurrentProcessId()) {
      parent_pid = process.th32ParentProcessID;
      HANDLE hmodule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, parent_pid);
      MODULEENTRY32 mod = { sizeof(MODULEENTRY32) };
      if (Module32First(hmodule, &mod)) {
        while(Module32Next(hmodule, &mod)) {
          if (_tcsicmp(mod.szModule, _T("mutechrome.dll")) == 0 ||
              _tcsicmp(mod.szModule, _T("apihook.dll")) == 0) {
            find_apihook_flag = TRUE;
            break;
          }
        }
      }
      if (hmodule != INVALID_HANDLE_VALUE)
        CloseHandle(hmodule);
      break;
    }
    ret = Process32Next(hprocess, &process);
  }
  if (hprocess != INVALID_HANDLE_VALUE)
    CloseHandle(hprocess);

  // If the main chrome process has been injected then return directly.
  if (find_apihook_flag)
    return;

  hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  ret = Process32First(hprocess, &process);
  while (ret) {
    if (process.th32ProcessID == parent_pid ||
        process.th32ParentProcessID == parent_pid) {
      HANDLE process_handle = OpenProcess(
          PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | 
          PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, 
          FALSE, process.th32ProcessID);
      char logs[256];
      if (!process_handle) {
        sprintf(logs, "OpenProcess GetLastError=%ld", GetLastError());
        g_log.WriteLog("Error", logs);
      } else {
        sprintf(logs, "InjectIntoProcess, ProcessId=%ld", 
                process.th32ProcessID);
        g_log.WriteLog("Msg", logs);
      }
      InjectIntoProcess(process_handle);
      if (process_handle)
        CloseHandle(process_handle);
    }
    ret = Process32Next(hprocess, &process);
  }
  if (hprocess != INVALID_HANDLE_VALUE)
    CloseHandle(hprocess);
}

NPError BrowserMutePlugin::Init(NPP instance, uint16_t mode, int16_t argc,
                                char *argn[], char *argv[],
                                NPSavedData *saved) {
  script_object_ = NULL;
  g_log.WriteLog("Msg", "BrowserMutePlugin Init");
  instance->pdata = this;
  use_apihook_flag_ = TRUE;
  ntdll_handle_ = LoadLibrary(_T("ntdll.dll"));
  if (!ntdll_handle_)
    return NPERR_GENERIC_ERROR;

  if (utils::GetWinVersion() == utils::WINVERSION_WIN7) {
    use_apihook_flag_ = FALSE;
    stop_event_ = CreateEvent(NULL, FALSE, FALSE, NULL);
    mute_thread_handle_ = CreateThread(NULL, 0, Mute_Thread, this, 0, 0);
  } else {
    RenameApiHookDll();
    ScanAndInject();
  }
  return PluginBase::Init(instance, mode, argc, argn, argv, saved);
}

NPError BrowserMutePlugin::UnInit(NPSavedData **save) {
  PluginBase::UnInit(save);
  script_object_ = NULL;
  if (ntdll_handle_)
    FreeLibrary(ntdll_handle_);

  g_log.WriteLog("Msg", "BrowserMutePlugin UnInit");
  if (!use_apihook_flag_) {
    SetEvent(stop_event_);
    if (WaitForSingleObject(mute_thread_handle_, 10) == WAIT_TIMEOUT) {
      TerminateThread(mute_thread_handle_, 0);
      mute_thread_handle_ = INVALID_HANDLE_VALUE;
    }
  }

  return NPERR_NO_ERROR;
}

NPError BrowserMutePlugin::GetValue(NPPVariable variable, void *value) {
  switch(variable) {
    case NPPVpluginScriptableNPObject:
      g_log.WriteLog("GetValue", "GetValue");
      if (script_object_ == NULL) {
        script_object_ = ScriptObjectFactory::CreateObject(
            get_npp(), BrowserMuteScriptObject::Allocate);
        NPN_RetainObject(script_object_);
      }
      if (script_object_ != NULL) {
        *(NPObject**)value = script_object_;
      }
      else
        return NPERR_OUT_OF_MEMORY_ERROR;
      break;
    default:
      return NPERR_GENERIC_ERROR;
  }

  return NPERR_NO_ERROR;
}
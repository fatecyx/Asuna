#include "convenience_plugin.h"

#include <map>

#include <Psapi.h>
#include <TlHelp32.h>

#include "client_process_functions.h"
#include "convenience_script_object.h"
#include "log.h"
#include "script_object_factory.h"
#include "utils.h"
#include "video_alone_script_object.h"

using namespace client_process_unit;

extern Log g_log;
extern HMODULE g_module;

LocalMessageItem g_local_message;
DWORD g_chrome_main_thread = 0;
TCHAR g_ChromeClassName[MAX_PATH] = _T("");

namespace {

const TCHAR* kFileMappingName = _T("Convenience_File");
const TCHAR* kMsgFileMappingName = _T("Convenience_Message_File");
const TCHAR* kPipeName = _T("\\\\.\\pipe\\convenience");
const int kClassNameChangedChromeVersion = 19;

void WriteBaseInfomation(const TCHAR* appname, const TCHAR* cfgname, 
                         const TCHAR* value) {
  TCHAR current_path[MAX_PATH];
  GetCurrentDirectory(MAX_PATH, current_path);
  TCHAR file_name[MAX_PATH];
  _stprintf(file_name, _T("%s\\convenience.ini"), current_path);
  WritePrivateProfileString(appname, cfgname, value, file_name);
}

void WriteMessageToMemory() {
  TCHAR filemap_name[MAX_PATH];
  _stprintf(filemap_name, _T("%s_%ld"), kMsgFileMappingName, 
            ReadBaseInfomation(_T("CFG"), _T("PID")));

  HANDLE memory_file_handle = CreateFileMapping(
      NULL, NULL, PAGE_READWRITE|SEC_COMMIT,
      0, sizeof(g_local_message), filemap_name);
  if (memory_file_handle) {
    LPVOID p = MapViewOfFile(memory_file_handle,
                             FILE_MAP_WRITE, 0, 0, sizeof(g_local_message));
    if (p) {
      memcpy(p, &g_local_message, sizeof(g_local_message));
      UnmapViewOfFile(p);
    }
  }
}

int GetChromeMajorVersion(std::string& user_agent) {
  int index = user_agent.find("Chrome/");
  if (index != std::string::npos) {
    int last_index = user_agent.find('.', index);
    if (last_index != std::string::npos) {
      std::string majorversion = user_agent.substr(index + 7, 
        last_index - index - 7);
      return atoi(majorversion.c_str());
    }
  }
  return 0;
}

}


//////////////////////////////////////////////////////////////////////////
//Server pipe thread
DWORD ConveniencePlugin::Server_Thread(void* param) {
  char szLog[256];
  char buffer[MAX_BUFFER_LEN];
  DWORD outlen;
  int offset = 0;
  int readlen = sizeof(CmdMsgItem);
  CmdMsgItem cmd;

  ConveniencePlugin* plugin = (ConveniencePlugin*)param;
  TCHAR pipe_name[MAX_PATH];
  _stprintf(pipe_name, _T("%s_%ld"), kPipeName, 
            ReadBaseInfomation(_T("CFG"), _T("PID")));

  plugin->server_pipe_handle_ = CreateNamedPipe(
      pipe_name, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
      PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
      1, MAX_BUFFER_LEN, MAX_BUFFER_LEN, 0, NULL);
  if (plugin->server_pipe_handle_ == INVALID_HANDLE_VALUE) {
    sprintf(szLog, "CreateNamedPipe Failed,GetLastError=%ld", GetLastError());
    g_log.WriteLog("Error", szLog);
    return -1;
  }
  g_log.WriteLog("Msg", "Start Server_Thread");

  OVERLAPPED ol = {0};
  ol.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  while (true) {
	  if (ConnectNamedPipe(plugin->server_pipe_handle_, &ol)) {
      g_log.WriteLog("Error", "ConnectNamedPipe Failed");
      Sleep(10);
      continue;
    } else {
      WaitForSingleObject(ol.hEvent, INFINITE);
      g_log.WriteLog("msg", "pipe client connected");
    }

    // send some flag to client process
    plugin->UpdateDBClick_CloseTab(db_click_close_tab_);
    plugin->UpdateCloseChromePromptFlag(close_chrome_prompt_);
    plugin->UpdateCloseLastTab(close_last_tab_);
    plugin->EnableMouseSwitchTab(enable_switch_tab_);
    plugin->PressEnterOpenNewTab(press_enter_open_new_tab_);
    ChromeWindowIdMap::iterator iter;
    for (iter = chrome_window_map_.begin(); iter != chrome_window_map_.end();
         iter++) {
      CmdMsgItem item;
      item.cmd = kCmdChromeWindowCreated;
      item.value.chrome_window.chrome_handle = iter->first;
      item.value.chrome_window.windowid = iter->second.windowid;
      plugin->WriteToClient(item);
      item.cmd = kCmdUpdateTabCount;
      item.value.tabcount.windowid = iter->second.windowid;
      item.value.tabcount.tabcount = iter->second.tabcount;
      plugin->WriteToClient(item);
    }
    chrome_window_map_.clear();
    
    BOOL result;
    while (true) {
      result = ReadFile(plugin->server_pipe_handle_, buffer+offset, readlen,
                        NULL, &ol);
      if (result || (!result && GetLastError() == ERROR_IO_PENDING)) {
        if (!GetOverlappedResult(plugin->server_pipe_handle_, 
                                 &ol, &outlen, TRUE))
          break;
      } else {
        sprintf(szLog, "ReadFile Error,GetLastError=%ld", GetLastError());
        g_log.WriteLog("Error", szLog);
        break;
      }

      if (outlen == readlen) {
        memcpy(&cmd, buffer, sizeof(cmd));
        sprintf(szLog, "recv from client, cmd=%ld", cmd.cmd);
        g_log.WriteLog("ReadFile", szLog);
        switch(cmd.cmd) {
        case kCmdRequestUpdate:
          if (plugin->memory_file_handle_) {
            CmdMsgItem item;
            item.cmd = kCmdUpdateShortcuts;
            plugin->WriteToClient(item);
          } else {
            CmdMsgItem item;
            item.cmd = kCmdResponseUpdate;
            plugin->WriteToClient(item);
          }
          break;
        case kCmdEvent:
          EnterCriticalSection(&plugin->cs_);
          plugin->shortcuts_queue_.push(cmd.value.shortcuts_Id);
          LeaveCriticalSection(&plugin->cs_);
          break;
        case kCmdChromeClose:
          PostMessage(plugin->get_hwnd(), WM_CHROMECLOSE, 0, 0);
          break;
        case kCmdTabClose:
          PostMessage(plugin->get_hwnd(), WM_TABCLOSE, 0, 0);
          break;
        case kCmdUpdateCloseChromePrompt:
          PostMessage(plugin->get_hwnd(), WM_UPDATE_CLOSECHROME_PROMPT,
                      cmd.value.is_closechrome_prompt, 0);
          break;
        case kCmdDBClickCloseTab:
          PostMessage(plugin->get_hwnd(), WM_CLOSE_CURRENT_TAB, 0, 0);
          break;
        case kCmdPressEnterOpenNewTab:
          PostMessage(plugin->get_hwnd(), WM_PRESS_ENTER_OPEN_NEW_TAB, 0, 0);
          break;
        case kCmdKeyDown:
          PostMessage(plugin->get_hwnd(), WM_KEYDOWN, 
                      cmd.value.key_down.wparam, cmd.value.key_down.lparam);
          break;
        case kCmdKeyUp:
          PostMessage(plugin->get_hwnd(), WM_KEYUP, cmd.value.key_down.wparam,
                      cmd.value.key_down.lparam);
          break;
        case kCmdMouseRotated:
          PostMessage(plugin->get_hwnd(), WM_CHROMEMOUSEWHEEL, 
                      0, cmd.value.rotatedcount);
          break;
        case kCmdClientShutDown:
          if (plugin->memory_file_handle_)
            CloseHandle(plugin->memory_file_handle_);
          if (plugin->server_pipe_handle_)
            CloseHandle(plugin->server_pipe_handle_);
          return 0;
        }
        readlen = sizeof(CmdMsgItem);
        offset = 0;
      } else {
        offset += outlen;
        if (offset == sizeof(CmdMsgItem))
          offset = 0;
        readlen = sizeof(CmdMsgItem) - offset;
      }
    }
    g_log.WriteLog("Error", "recv from client failed, DisconnectNamedPipe");
    DisconnectNamedPipe(plugin->server_pipe_handle_);
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////


// ConveniencePlugin static variables
WNDPROC ConveniencePlugin::old_proc_ = NULL;
bool ConveniencePlugin::close_last_tab_ = false;
bool ConveniencePlugin::close_chrome_prompt_ = true;
bool ConveniencePlugin::db_click_close_tab_ = true;
bool ConveniencePlugin::enable_switch_tab_ = false;
bool ConveniencePlugin::press_enter_open_new_tab_ = false;
ChromeWindowIdMap ConveniencePlugin::chrome_window_map_;

ConveniencePlugin::ConveniencePlugin(void) {
  memory_file_handle_ = NULL;
  server_thread_handle_ = NULL;
  get_local_message_flag_ = false;
  InitializeCriticalSection(&cs_);
}

ConveniencePlugin::~ConveniencePlugin(void) {
  DeleteCriticalSection(&cs_);
}

NPError ConveniencePlugin::Init(NPP instance, uint16_t mode, int16_t argc,
                                char *argn[], char *argv[],
                                NPSavedData *saved) {
  scriptobject_ = NULL;
  instance->pdata = this;
  g_log.WriteLog("Msg", "ConveniencePlugin Init");
  TCHAR info[MAX_PATH];
  _stprintf(info, _T("%d"), GetCurrentProcessId());
  WriteBaseInfomation(_T("CFG"), _T("PID"), info);
  std::string user_agent = NPN_UserAgent(instance);
  int chrome_version = GetChromeMajorVersion(user_agent);
  _stprintf(info, _T("%d"), chrome_version);
  WriteBaseInfomation(_T("CFG"), _T("MAJORVERSION"), info);

  server_thread_handle_ = CreateThread(NULL, 0, Server_Thread, this, 0, NULL);
  TCHAR exe_name[MAX_PATH];
  GetModuleBaseName(GetCurrentProcess(), GetModuleHandle(NULL), exe_name, MAX_PATH);
  HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 process = { sizeof(PROCESSENTRY32) };
  DWORD parent_processid = 0;
  BOOL ret = Process32First(hprocess, &process);
  while (ret) {
    if (_tcsicmp(process.szExeFile, exe_name) == 0 && 
        process.th32ProcessID == GetCurrentProcessId()) {
      parent_processid = process.th32ParentProcessID;
      break;
    }
    ret = Process32Next(hprocess, &process);
  }
  if (hprocess != INVALID_HANDLE_VALUE)
    CloseHandle(hprocess);
  if (chrome_version >= kClassNameChangedChromeVersion)
    _tcscpy(g_ChromeClassName, _T("Chrome_WidgetWin_1"));
  else
    _tcscpy(g_ChromeClassName, _T("Chrome_WidgetWin_0"));
  WriteBaseInfomation(_T("CFG"), _T("CLASSNAME"), g_ChromeClassName);

  HWND chrome_hwnd = FindWindowEx(NULL, NULL, g_ChromeClassName, NULL);
  while (chrome_hwnd) {
    DWORD process_id;
    g_chrome_main_thread = GetWindowThreadProcessId(chrome_hwnd, &process_id);
    if (process_id == parent_processid) {
      keyboard_hook_ = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_module, 
                                        g_chrome_main_thread);
      get_msg_hook_ = SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, g_module, 
                                       g_chrome_main_thread);
      call_wnd_hook_ = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProcHook, 
                                        g_module, g_chrome_main_thread);
      if (!keyboard_hook_ || !get_msg_hook_ || !call_wnd_hook_) {
        return NPERR_GENERIC_ERROR;
      } else {
        g_log.WriteLog("Msg", "ConveniencePlugin Init Success");
        break;
      }
    } else {
      chrome_hwnd = FindWindowEx(NULL, chrome_hwnd, g_ChromeClassName, NULL);
    }
  }
  
  return PluginBase::Init(instance, mode, argc, argn, argv, saved);
}

NPError ConveniencePlugin::UnInit(NPSavedData **save) {
  PluginBase::UnInit(save);
  scriptobject_ = NULL;

  CmdMsgItem item;
  item.cmd = kCmdServerShutDown;
  WriteToClient(item);

  UnhookWindowsHookEx(get_msg_hook_);
  UnhookWindowsHookEx(keyboard_hook_);
  UnhookWindowsHookEx(call_wnd_hook_);

  if (WaitForSingleObject(server_thread_handle_, 10) == WAIT_TIMEOUT) {
    TerminateThread(server_thread_handle_, 0);
    if (memory_file_handle_)
      CloseHandle(memory_file_handle_);
    if (server_pipe_handle_)
      CloseHandle(server_pipe_handle_);
  }

  return NPERR_NO_ERROR;
}

bool ConveniencePlugin::GetNPMessage(int index, TCHAR* msg, int msglen) {
  NPObject* window;
  NPN_GetValue(get_npp(), NPNVWindowNPObject, &window);
  NPIdentifier id;
  id = NPN_GetStringIdentifier("getNPMessage");
  NPVariant result;
  VOID_TO_NPVARIANT(result);
  if (id) {
    NPVariant param;
    INT32_TO_NPVARIANT(index, param);
    if (NPN_Invoke(get_npp(), window, id, &param, 1, &result)) {
      utils::Utf8ToUnicode message(NPVARIANT_TO_STRING(result).UTF8Characters,
                                   NPVARIANT_TO_STRING(result).UTF8Length);
      _tcsncpy(msg, message, msglen);
      msg[msglen - 1] = 0;
      NPN_ReleaseVariantValue(&result);
      return true;
    }
  }

  return false;
}

NPError ConveniencePlugin::GetValue(NPPVariable variable, void *value) {
  switch(variable) {
    case NPPVpluginScriptableNPObject:
      if (scriptobject_ == NULL) {
        scriptobject_ = ScriptObjectFactory::CreateObject(
            get_npp(), ConvenienceScriptObject::Allocate);
        g_log.WriteLog("GetValue", "GetValue");
        NPN_RetainObject(scriptobject_);
      }
      if (scriptobject_ != NULL) {
        *(NPObject**)value = scriptobject_;
      }
      else
        return NPERR_OUT_OF_MEMORY_ERROR;
      break;
    default:
      return NPERR_GENERIC_ERROR;
  }

  return NPERR_NO_ERROR;
}

NPError ConveniencePlugin::SetWindow(NPWindow* window) {
  PluginBase::SetWindow(window);

  if (get_hwnd() == NULL && old_proc_ != NULL) {
    KillTimer(get_hwnd(), 1);
    SubclassWindow(get_hwnd(), old_proc_);
    old_proc_ = NULL; 
  }

  if (get_hwnd() != NULL && old_proc_ == NULL) {
    old_proc_ = SubclassWindow(get_hwnd(), WndProc);
    SetWindowLong(get_hwnd(), GWLP_USERDATA, (LONG)this);
    SetTimer(get_hwnd(), 1, 10, NULL);
  }

  return NPERR_NO_ERROR;
}

void ConveniencePlugin::SetShortcutsToMemory(ShortCutItem* list, int count) {
  if (!memory_file_handle_)
    CloseHandle(memory_file_handle_);

  int num = sizeof(ShortCutItem)*count + sizeof(int);
  TCHAR filemap_name[MAX_PATH];
  _stprintf(filemap_name, _T("%s_%ld"), kFileMappingName, 
            ReadBaseInfomation(_T("CFG"), _T("PID")));

  memory_file_handle_ = CreateFileMapping(NULL, NULL,
                                          PAGE_READWRITE|SEC_COMMIT,
                                          0, num, filemap_name);
  if (memory_file_handle_) {
    LPVOID p = MapViewOfFile(memory_file_handle_,
                             FILE_MAP_WRITE, 0, 0, num);
    if (p) {
      memcpy(p, &count, sizeof(int));
      memcpy((BYTE*)p+sizeof(int), list, sizeof(ShortCutItem)*count);
      UnmapViewOfFile(p);
      CmdMsgItem item;
      item.cmd = kCmdUpdateShortcuts;
      WriteToClient(item);
    }
  } else {
    char szLog[256];
    sprintf(szLog, "GetLastError=%ld", GetLastError());
    g_log.WriteLog("Error", szLog);
  }
}

void ConveniencePlugin::UpdateDBClick_CloseTab(bool double_click_closetab) {
  CmdMsgItem item;
  item.cmd = kCmdUpdateDBClickCloseTab;
  item.value.double_click_closetab = double_click_closetab;
  db_click_close_tab_ = double_click_closetab;
  WriteToClient(item);
}

void ConveniencePlugin::UpdateIsListening(bool is_listening) {
  CmdMsgItem item;
  item.cmd = kCmdUpdateIsListening;
  item.value.is_listening = is_listening;
  WriteToClient(item);
}

void ConveniencePlugin::UpdateTabCount(int windowid, int tabcount) {
  CmdMsgItem item;
  item.cmd = kCmdUpdateTabCount;
  item.value.tabcount.windowid = windowid;
  item.value.tabcount.tabcount = tabcount;
  if (!chrome_window_map_.empty()) {
    ChromeWindowIdMap::iterator iter;
    for (iter = chrome_window_map_.begin(); iter != chrome_window_map_.end();
         iter++) {
      if (iter->second.windowid == windowid) {
        iter->second.tabcount = tabcount;
      }
    }
  }
  WriteToClient(item);
}

void ConveniencePlugin::UpdateCloseChromePromptFlag(bool flag) {
  CmdMsgItem item;
  item.cmd = kCmdUpdateCloseChromePrompt;
  item.value.is_closechrome_prompt = flag;
  close_chrome_prompt_ = flag;
  WriteToClient(item);
}

void ConveniencePlugin::UpdateCloseLastTab(bool close_last_tab) {
  CmdMsgItem item;
  item.cmd = kCmdUpdateCloseLastTab;
  item.value.close_last_tab = close_last_tab;
  close_last_tab_ = close_last_tab;
  WriteToClient(item);
}

void ConveniencePlugin::ChromeWindowCreated(int windowid) {
  CmdMsgItem item;
  item.cmd = kCmdChromeWindowCreated;
  item.value.chrome_window.windowid = windowid;
  item.value.chrome_window.chrome_handle = NULL;
  VideoAloneScriptObject::WindowMap* window_list = 
      VideoAloneScriptObject::get_video_alone_list();

  HWND chrome_hwnd = FindWindowEx(NULL, NULL, g_ChromeClassName, NULL);
  char logs[256];
  while(chrome_hwnd) {
    BOOL visible = IsWindowVisible(chrome_hwnd);
    HWND hwnd = GetParent(chrome_hwnd);
    sprintf(logs, "chrome_hwnd=%X,IsWindowVisible=%d,GetParent=%X", 
            chrome_hwnd, visible, hwnd);
    g_log.WriteLog("create", logs);
    if (GetWindowThreadProcessId(chrome_hwnd, NULL) == g_chrome_main_thread &&
        hwnd == NULL && window_list->find(chrome_hwnd) == window_list->end() &&
        visible && GetWindow(chrome_hwnd, GW_CHILD)) {
      item.value.chrome_window.chrome_handle = chrome_hwnd;
      CmdMsgItem::CmdMsgValue::TabCount tabcount;
      tabcount.windowid = windowid;
      tabcount.tabcount = 1;
      chrome_window_map_.insert(std::make_pair(chrome_hwnd, tabcount));
      break;
    }
    chrome_hwnd = FindWindowEx(NULL, chrome_hwnd, g_ChromeClassName, NULL);
  }

  WriteToClient(item);
}

void ConveniencePlugin::ChromeWindowRemoved(int windowid) {
  CmdMsgItem item;
  item.cmd = kCmdChromeWindowRemoved;
  item.value.chrome_window.windowid = windowid;
  WriteToClient(item);
}

void ConveniencePlugin::EnableMouseSwitchTab(bool flag) {
  CmdMsgItem item;
  item.cmd = kCmdUpdateSwitchTab;
  item.value.enable_switch_tab = flag;
  enable_switch_tab_ = flag;
  WriteToClient(item);
}

void ConveniencePlugin::PressEnterOpenNewTab(bool flag) {
  CmdMsgItem item;
  item.cmd = kCmdUpdatePressEnterOpenNewTab;
  item.value.press_enter_open_new_tab = flag;
  press_enter_open_new_tab_ = flag;
  WriteToClient(item);
}

void ConveniencePlugin::ExistsPinnedTab(int windowid, bool pinned) {
  CmdMsgItem item;
  item.cmd = kCmdExistsPinnedTabs;
  item.value.tabcount.windowid = windowid;
  item.value.tabcount.pinnedtab = pinned;
  WriteToClient(item);
}

void ConveniencePlugin::GetLocalMessage() {
  if (get_local_message_flag_)
    return;

  GetNPMessage(MSG_ALWAYS_ON_TOP, g_local_message.msg_always_on_top, 256);
  GetNPMessage(MSG_CLOSECHROME_TITLE, g_local_message.msg_closechrome_title, 
               256);
  GetNPMessage(MSG_CLOSECHROME_MESSAGE, g_local_message.msg_closechrome_message,
               256);
  GetNPMessage(MSG_CLOSECHROME_OK, g_local_message.msg_closechrome_ok, 256);
  GetNPMessage(MSG_CLOSECHROME_CANCEL, g_local_message.msg_closechrome_cancel,
               256);
  GetNPMessage(
      MSG_CLOSECHROME_NOALERT, g_local_message.msg_closechrome_noalert, 256);

  WriteMessageToMemory();
  get_local_message_flag_ = true;
  CmdMsgItem item;
  item.cmd = kCmdUpdateLocalMessage;
  WriteToClient(item);
}

LRESULT ConveniencePlugin::WndProc(HWND hWnd, UINT Msg, 
                                    WPARAM wParam, LPARAM lParam) {
  ConveniencePlugin* plugin = (ConveniencePlugin*)GetWindowLong(hWnd, 
                                                                GWLP_USERDATA);
  ConvenienceScriptObject* pObject = (ConvenienceScriptObject*)plugin->
      scriptobject_;
  if (!pObject)
    return CallWindowProc(old_proc_, hWnd, Msg, wParam, lParam);

  switch(Msg) {
    case WM_TIMER:
      EnterCriticalSection(&plugin->cs_);
      while (!plugin->shortcuts_queue_.empty()) {
        g_log.WriteLog("WndProc", "WM_TIMER");
        int shortcut_id = plugin->shortcuts_queue_.front();
        plugin->shortcuts_queue_.pop();
        if (!pObject->get_is_listened())
          pObject->TriggerEvent(shortcut_id);
      }
      LeaveCriticalSection(&plugin->cs_);
      break;
    case WM_CHROMECLOSE:
      pObject->TriggerShortcuts(MOD_ALT, VK_F4);
      break;
    case WM_TRIGGER_CHROME_SHORTCUTS:
      pObject->TriggerShortcuts(wParam, lParam);
      break;
    case WM_TABCLOSE:
      pObject->InvokeJSMethod("beforeLastTabClose");
      break;
    case WM_CLOSE_CURRENT_TAB:
      pObject->InvokeJSMethod("closeCurrentTab");
      break;
    case WM_PRESS_ENTER_OPEN_NEW_TAB:
      pObject->TriggerShortcuts(MOD_ALT, VK_RETURN);
      break;
    case WM_UPDATE_CLOSECHROME_PROMPT:
      pObject->UpdateCloseChromePromptFlag(wParam);
      break;
    case WM_CHROMEMOUSEWHEEL: {
      bool forward = lParam > 0 ? true : false;
      pObject->TriggerSwitchTab(forward);
      break;
    }
    case WM_KEYDOWN: {
      bool control = false;
      bool alt = false;
      bool shift = false;
      if (GetKeyState(VK_CONTROL) & 0x80)
        control = true;
      if (GetKeyState(VK_MENU) & 0x80)
        alt = true;
      if (GetKeyState(VK_SHIFT) & 0x80)
        shift = true;
      char logs[256];
      sprintf(logs, "wparam=%d, lparam=%d, control=%d, shift=%d, alt=%d", 
              wParam, lParam, control, shift, alt);
      g_log.WriteLog("keydown", logs);
      pObject->OnKeyDown(control, alt, shift, wParam, lParam);
      break;
    }
    case WM_KEYUP:
      break;
    case WM_HOTKEY: {
      if (pObject->get_is_listened())
        break;

      g_log.WriteLog("msg", "WM_HOTKEY");
      char shortcuts_name[MAX_KEY_LEN];
      GlobalGetAtomNameA(wParam, shortcuts_name, MAX_KEY_LEN);
      pObject->TriggerEvent(shortcuts_name);
      break;
    }
    default:
      return CallWindowProc(old_proc_, hWnd, Msg, wParam, lParam);
  }
  return TRUE;
}

void ConveniencePlugin::WriteToClient(const CmdMsgItem& item) {
  char logs[256];
  sprintf(logs, "WriteToClient, cmd=%d", item.cmd);
  DWORD writelen;
  if (WriteFile(server_pipe_handle_, &item, sizeof(item), &writelen, NULL))
    g_log.WriteLog("Send", logs);
  else
    g_log.WriteLog("Send Error", logs);
}
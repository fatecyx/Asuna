#include "client_process_functions.h"

#include <map>
#include <string>

#include "convenience_script_object.h"
#include "log.h"
#include "resource.h"
#include "utils.h"

extern Log g_log;
extern HMODULE g_module;
extern LocalMessageItem g_local_message;

namespace client_process_unit {

bool is_listening = false;
bool close_last_tab = false;
bool close_chrome_prompt = true;
bool db_click_close_tab = true;
bool enable_switch_tab = false;
bool press_enter_open_new_tab = false;

HANDLE client_pipe_handle = INVALID_HANDLE_VALUE;
HANDLE client_thread_handle = INVALID_HANDLE_VALUE;

const TCHAR* kFileMappingName = _T("Convenience_File");
const TCHAR* kMsgFileMappingName = _T("Convenience_Message_File");
const TCHAR* kRenderClassName = _T("Chrome_RenderWidgetHostHWND");
const TCHAR* kPipeName = _T("\\\\.\\pipe\\convenience");
const TCHAR* kAddressBarClassName = _T("Chrome_AutocompleteEditView");
const TCHAR* kOmniboxViewClassName = _T("Chrome_OmniboxView");

TCHAR g_ChromeClassName[MAX_PATH] = _T("");

ChromeWindowIdMap chrome_window_map;

const int kCloseTabButtonLeftOffset = 186;
const int kCloseTabButtonTopOffset = 18;
const int kCloseTabButtonLeftOffset_MaxState = 182;
const int kCloseTabButtonTopOffset_MaxState = 5;
const int kChromeWindowMinChangeSize = 343;
const int kCloseTabButtonWidth = 20;
const int kCloseTabButtonHeight = 20;
const int kVerticalTabsWidth = 150;
const int kVerticalTabsLeftOffset = 122;
const int kVerticalTabsTopOffset = 65;

int map_current_used_flag = 2;
ConvenienceScriptObject::ShortCutKeyMap map_one;
ConvenienceScriptObject::ShortCutKeyMap map_two;

int ReadBaseInfomation(const TCHAR* appname, const TCHAR* cfgname) {
  TCHAR current_path[MAX_PATH];
  GetCurrentDirectory(MAX_PATH, current_path);
  TCHAR file_name[MAX_PATH];
  _stprintf(file_name, _T("%s\\convenience.ini"), current_path);
  return GetPrivateProfileInt(appname, cfgname, 0, file_name);
}

void ReadBaseInfomation(const TCHAR* appname, const TCHAR* cfgname, 
                        TCHAR* buffer, unsigned int len) {
  TCHAR current_path[MAX_PATH];
  GetCurrentDirectory(MAX_PATH, current_path);
  TCHAR file_name[MAX_PATH];
  _stprintf(file_name, _T("%s\\convenience.ini"), current_path);
  GetPrivateProfileString(appname, cfgname, _T(""), buffer, len, file_name);
}

// update shortcuts map from memory file.
void UpdateShortcutsFromMemory() {
  g_log.WriteLog("msg", "UpdateShortcutsFromMemory");
  TCHAR filemap_name[MAX_PATH];
  _stprintf(filemap_name, _T("%s_%ld"), kFileMappingName, 
            ReadBaseInfomation(_T("CFG"), _T("PID")));
  HANDLE memory_file_handle = OpenFileMapping(FILE_MAP_READ, FALSE,
                                              filemap_name);
  if (memory_file_handle) {
    LPVOID p = MapViewOfFile(memory_file_handle, FILE_MAP_READ, 0, 0, 0);
    if (p) {
      int count = 0;
      memcpy(&count, p, sizeof(int));
      ShortCutItem* list = (ShortCutItem*)((BYTE*)p+sizeof(int));
      ConvenienceScriptObject::ShortCutKeyMap* key_map_new;
      ConvenienceScriptObject::ShortCutKeyMap* key_map_old;
      if (map_current_used_flag == 1) {
        key_map_new = &map_two;
        key_map_old = &map_one;
      } else {
        key_map_new = &map_one;
        key_map_old = &map_two;
      }

      for (int i = 0; i < count; i++) {
        key_map_new->insert(std::make_pair(std::string(list[i].shortcuts_key), list[i]));
      }
      map_current_used_flag = map_current_used_flag == 1 ? 2 : 1;
      key_map_old->clear();
      g_log.WriteLog("msg", "UpdateShortcutsSuccess");
      UnmapViewOfFile(p);
    }
    CloseHandle(memory_file_handle);
  }
}

// get some local information from memory file
void GetMessageFromMemory() {
  g_log.WriteLog("msg", "GetMessageFromMemory");
  TCHAR filemap_name[MAX_PATH];
  _stprintf(filemap_name, _T("%s_%ld"), kMsgFileMappingName, 
            ReadBaseInfomation(_T("CFG"), _T("PID")));
  HANDLE memory_file_handle = OpenFileMapping(FILE_MAP_READ, FALSE,
                                              filemap_name);
  if (memory_file_handle) {
    LPVOID p = MapViewOfFile(memory_file_handle, FILE_MAP_READ, 0, 0, 0);
    if (p) {
      memcpy(&g_local_message, p, sizeof(g_local_message));
      UnmapViewOfFile(p);
    }
    CloseHandle(memory_file_handle);
  }
}

// the dialog procedure for multi-tab closing information
BOOL CALLBACK CloseChromeDialgProc(HWND dlg, UINT message, WPARAM wParam, 
                                   LPARAM lParam) {
  switch (message) { 
    case WM_INITDIALOG: {
      NONCLIENTMETRICS metrics;
      utils::GetNonClientMetrics(&metrics);
      HFONT font = CreateFontIndirect(&(metrics.lfMenuFont));
      SendMessage(GetDlgItem(dlg, IDC_MESSAGE), WM_SETFONT, 
                  (WPARAM)font, TRUE);
      SendMessage(GetDlgItem(dlg, IDC_NOALERT), WM_SETFONT, 
                  (WPARAM)font, TRUE);
      SendMessage(GetDlgItem(dlg, IDOK), WM_SETFONT, (WPARAM)font, TRUE);
      SendMessage(GetDlgItem(dlg, IDCANCEL), WM_SETFONT, (WPARAM)font, TRUE);
      SetWindowText(dlg, g_local_message.msg_closechrome_title);
      SetDlgItemText(dlg, IDOK, g_local_message.msg_closechrome_ok);
      SetDlgItemText(dlg, IDCANCEL, g_local_message.msg_closechrome_cancel);
      SetDlgItemText(dlg, IDC_MESSAGE, 
                     g_local_message.msg_closechrome_message);
      SetDlgItemText(dlg, IDC_NOALERT, 
                     g_local_message.msg_closechrome_noalert);
      break;
    }
    case WM_COMMAND: {
      if (LOWORD(wParam) == IDOK) {
        if (Button_GetCheck(GetDlgItem(dlg, IDC_NOALERT)) == BST_CHECKED) {
          CmdMsgItem item;
          item.cmd = kCmdUpdateCloseChromePrompt;
          item.value.is_closechrome_prompt = false;
          WriteToServer(item);
          close_chrome_prompt = false;
        }
        HFONT font = (HFONT)SendMessage(GetDlgItem(dlg, IDC_MESSAGE), 
                                        WM_GETFONT, 0, 0);
        if (font)
          DeleteObject(font);
        EndDialog(dlg, IDOK);
      }
      else if (LOWORD(wParam) == IDCANCEL)
        EndDialog(dlg, IDCANCEL);
      break;
    }
  }
  return FALSE; 
} 

DWORD WINAPI Client_Thread(void* param) {
  char szLog[256];
  char buffer[MAX_BUFFER_LEN];
  DWORD outlen;
  int offset = 0;
  int readlen = sizeof(CmdMsgItem);
  CmdMsgItem cmd;

  OVERLAPPED ol = { 0 };
  ol.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  TCHAR pipe_name[MAX_PATH];
  _stprintf(pipe_name, _T("%s_%ld"), kPipeName, 
            ReadBaseInfomation(_T("CFG"), _T("PID")));
  ReadBaseInfomation(_T("CFG"), _T("CLASSNAME"), g_ChromeClassName, MAX_PATH);

  while(true) {
    client_pipe_handle = CreateFile(pipe_name, GENERIC_READ | GENERIC_WRITE,
                                    0, NULL, OPEN_EXISTING, 
                                    FILE_FLAG_OVERLAPPED, NULL);

    if (client_pipe_handle == INVALID_HANDLE_VALUE) {
      DWORD errorcode = GetLastError();
      if (errorcode == ERROR_PIPE_BUSY) {
        sprintf(szLog, "CreateFile Failed,GetLastError=%ld", errorcode);
        g_log.WriteLog("Error", szLog);
        Sleep(10);
        continue;
      } else {
        sprintf(szLog, "CreateFile Failed,GetLastError=%ld", errorcode);
        g_log.WriteLog("Error", szLog);
        Sleep(10);
        continue;
      }
    } else {
      g_log.WriteLog("Msg", "CreateFile success, start client thread");
    }

    cmd.cmd = kCmdRequestUpdate;
    WriteToServer(cmd);

    BOOL result;
    while (true) {
      result = ReadFile(client_pipe_handle, buffer+offset, readlen,
                        NULL, &ol);
      if (result || (!result && GetLastError() == ERROR_IO_PENDING)) {
        result = GetOverlappedResult(client_pipe_handle, &ol, &outlen, TRUE);
        if (!result && GetLastError() == ERROR_BROKEN_PIPE) {
          return -1;
        } else if (!result) {
          break;
        }
      } else {
        sprintf(szLog, "Client ReadFile Error,GetLastError=%ld", 
          GetLastError());
        g_log.WriteLog("Error", szLog);
        break;
      }
      if (outlen == readlen) {
        memcpy(&cmd, buffer, sizeof(cmd));
        sprintf(szLog, "recv from server, cmd=%ld",cmd.cmd);
        g_log.WriteLog("ReadFile", szLog);
        switch(cmd.cmd) {
          case kCmdUpdateShortcuts:
            UpdateShortcutsFromMemory();
            break;
          case kCmdResponseUpdate:
            break;
          case kCmdUpdateLocalMessage:
            GetMessageFromMemory();
            break;
          case kCmdUpdateCloseChromePrompt:
            close_chrome_prompt = cmd.value.is_closechrome_prompt;
            break;
          case kCmdUpdateDBClickCloseTab:
            db_click_close_tab = cmd.value.double_click_closetab;
            break;
          case kCmdUpdateIsListening:
            is_listening = cmd.value.is_listening;
            break;
          case kCmdUpdateCloseLastTab:
            close_last_tab = cmd.value.close_last_tab;
            break;
          case kCmdUpdateSwitchTab:
            enable_switch_tab = cmd.value.enable_switch_tab;
            break;
          case kCmdUpdatePressEnterOpenNewTab:
            press_enter_open_new_tab = cmd.value.press_enter_open_new_tab;
            break;
          case kCmdExistsPinnedTabs:{
            ChromeWindowIdMap::iterator iter;
            for (iter = chrome_window_map.begin(); 
                 iter != chrome_window_map.end(); iter++) {
              if (iter->second.windowid == cmd.value.tabcount.windowid) {
                iter->second.pinnedtab = cmd.value.tabcount.pinnedtab;
                break;
              }
            }
            break;
          }
          case kCmdUpdateTabCount: {
            ChromeWindowIdMap::iterator iter;
            for (iter = chrome_window_map.begin(); 
                 iter != chrome_window_map.end(); iter++) {
              if (iter->second.windowid == cmd.value.tabcount.windowid) {
                iter->second.tabcount = cmd.value.tabcount.tabcount;
                sprintf(szLog, "windowid=%d, tabcount=%ld", 
                        cmd.value.tabcount.windowid, 
                        cmd.value.tabcount.tabcount);
                g_log.WriteLog("Cmd_Update_TabCount", szLog);
                break;
              }
            }
            break;
          }
          case kCmdChromeWindowCreated: {
            CmdMsgItem::CmdMsgValue::TabCount tabcount = {0};
            tabcount.windowid = cmd.value.chrome_window.windowid;
            tabcount.tabcount = 1;
            chrome_window_map.insert(std::make_pair(
                cmd.value.chrome_window.chrome_handle, tabcount));
            sprintf(szLog, "handle=%X, windowid=%ld", 
                    cmd.value.chrome_window.chrome_handle,
                    cmd.value.chrome_window.windowid);
            g_log.WriteLog("ChromeWindowCreated", szLog);
            break;
          }
          case kCmdChromeWindowRemoved: {
            ChromeWindowIdMap::iterator iter;
            for (iter = chrome_window_map.begin(); 
                 iter != chrome_window_map.end(); iter++) {
              if (iter->second.windowid == cmd.value.chrome_window.windowid) {
                chrome_window_map.erase(iter);
                break;
              }
            }
            break;
          }
          case kCmdServerShutDown: {
            CmdMsgItem item;
            item.cmd = kCmdClientShutDown;
            WriteToServer(item);
            CloseHandle(client_pipe_handle);
            client_thread_handle = INVALID_HANDLE_VALUE;
          }
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
    g_log.WriteLog("error", "client thread readfile failed, closefile");
    CloseHandle(client_pipe_handle);
    client_pipe_handle = INVALID_HANDLE_VALUE;
  }
  return 0;
}

bool CheckVerticalTabsEnable(HWND chrome_hwnd) {
  // Check vertical tab is enabled/disabled.
  HWND render_window = FindWindowEx(chrome_hwnd, NULL, g_ChromeClassName, NULL);
  bool enable_vertical_tabs = false;
  while (render_window) {
    RECT render_rect;
    HWND hwnd = FindWindowEx(render_window, NULL, 
                             kRenderClassName, NULL);
    if (!hwnd) {
      render_window = FindWindowEx(chrome_hwnd, render_window, 
                                   g_ChromeClassName, NULL);
      continue;
    }
    GetWindowRect(render_window, &render_rect);
    RECT chrome_rect = { 0 };
    GetWindowRect(chrome_hwnd, &chrome_rect);
    if (render_rect.left - chrome_rect.left > 20)
      enable_vertical_tabs = true;
    break;
  }

  return enable_vertical_tabs;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (!(HIWORD(lParam) & KF_REPEAT)) {
    std::string shortcuts;
    char virual_key[MAX_KEY_LEN];
    if (GetKeyState(VK_CONTROL) & 0x80)
      shortcuts = "17";
    if (GetKeyState(VK_MENU) & 0x80) {
      if (shortcuts.length() > 0)
        shortcuts += "+18";
      else
        shortcuts = "18";
    }
    if (GetKeyState(VK_SHIFT) & 0x80) {
      if (shortcuts.length() > 0)
        shortcuts += "+16";
      else
        shortcuts = "16";
    }
    _itoa(wParam, virual_key, 10);
    if (shortcuts.length() > 0) {
      shortcuts += "+";
      shortcuts += virual_key;
    }
    else
      shortcuts = virual_key;

    HWND hwnd = GetForegroundWindow();
    ChromeWindowIdMap::iterator tabcount_iter = chrome_window_map.find(hwnd);
    switch (wParam)
    {
        case 'W':
            if (GetKeyState(VK_CONTROL) >= 0)
                break;
            // fall through
        case VK_F4:
            if (GetKeyState(VK_SHIFT) < 0 || GetKeyState(VK_MENU) < 0)
                break;

            if (close_last_tab &&
                tabcount_iter != chrome_window_map.end() &&
                tabcount_iter->second.tabcount == 1)
            {
                CmdMsgItem item;
                item.cmd = kCmdTabClose;
                WriteToServer(item);
                return TRUE;
            }
    }

    ConvenienceScriptObject::ShortCutKeyMap* shortcut_map;
    if (map_current_used_flag == 1)
      shortcut_map = &map_one;
    else
      shortcut_map = &map_two;

    ConvenienceScriptObject::ShortCutKeyMap::iterator iter = 
        shortcut_map->find(shortcuts);

    CmdMsgItem item;
    if (is_listening) {
      item.cmd = kCmdKeyDown;
      item.value.key_down.wparam = wParam;
      item.value.key_down.lparam = lParam;
      WriteToServer(item);
    } else {
      item.cmd = kCmdEvent;
      if (iter != shortcut_map->end() && client_pipe_handle) {
        item.value.shortcuts_Id = iter->second.index;
        WriteToServer(item);
      }
    }
  }
  else if (HIWORD(lParam) & KF_UP) {
    if (is_listening) {
      CmdMsgItem item;
      item.cmd = kCmdKeyUp;
      item.value.key_down.wparam = wParam;
      item.value.key_down.lparam = lParam;
      WriteToServer(item);
    }
  }

  return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK GetMsgProc(int code, WPARAM wParam, LPARAM lParam){
  if (client_thread_handle == INVALID_HANDLE_VALUE) {
    client_thread_handle = CreateThread(NULL, 0, Client_Thread, NULL, 0, 
                                        NULL);
  }
  MSG* msg = (MSG*)lParam;

  // Check user press enter key in the address bar.
  if (msg->message == WM_KEYDOWN && msg->wParam == VK_RETURN &&
      press_enter_open_new_tab) {
    HWND chrome_hwnd = GetParent(msg->hwnd);
    if (chrome_hwnd) {
      ChromeWindowIdMap::iterator iter = chrome_window_map.find(chrome_hwnd);
      if (iter != chrome_window_map.end()) {
       TCHAR class_name[256];
        GetClassName(msg->hwnd, class_name, 256);
        if (_tcscmp(class_name, kAddressBarClassName) == 0 ||
            _tcscmp(class_name, kOmniboxViewClassName) == 0) {
          CmdMsgItem item;
          item.cmd = kCmdPressEnterOpenNewTab;
          WriteToServer(item);
          msg->message = WM_NULL;
        }
      }
    }
  }

  ChromeWindowIdMap::iterator iter = chrome_window_map.find(msg->hwnd);
  if (iter == chrome_window_map.end())
    return CallNextHookEx(NULL, code, wParam, lParam);

  bool is_only_one_tab = (iter->second.tabcount == 1);
  bool enable_vertical_tabs = CheckVerticalTabsEnable(msg->hwnd);

  if ((msg->message == WM_LBUTTONDOWN || msg->message == WM_LBUTTONDBLCLK) 
      && wParam == PM_REMOVE && msg->wParam == MK_LBUTTON && close_last_tab 
      && is_only_one_tab) {
    TCHAR class_name[256];
    GetClassName(msg->hwnd, class_name, 256);
    if (_tcscmp(class_name, g_ChromeClassName) == 0 && 
        GetParent(msg->hwnd) == NULL) { 
      RECT rt = {0};
      if (enable_vertical_tabs) {
        if (iter->second.pinnedtab)
          rt.top = 35;
        else
          rt.top = kVerticalTabsTopOffset;
        rt.left = kVerticalTabsLeftOffset;        
      } else {
        if (IsMaximized(msg->hwnd)) {
          rt.left = kCloseTabButtonLeftOffset_MaxState;
          rt.top = kCloseTabButtonTopOffset_MaxState;
        } else {
          RECT chrome_rect = { 0 };
          GetWindowRect(msg->hwnd, &chrome_rect);
          if (chrome_rect.right - chrome_rect.left < 
              kChromeWindowMinChangeSize) {
            rt.left = 
                kCloseTabButtonLeftOffset - (kChromeWindowMinChangeSize - 
                (chrome_rect.right - chrome_rect.left));
            rt.top = kCloseTabButtonTopOffset;
          } else {
            rt.left = kCloseTabButtonLeftOffset;
            rt.top = kCloseTabButtonTopOffset;
          }
        }
      }
      rt.bottom = rt.top + kCloseTabButtonHeight;
      rt.right = rt.left + kCloseTabButtonWidth;

      POINT pt;
      pt.x = GET_X_LPARAM(msg->lParam);
      pt.y = GET_Y_LPARAM(msg->lParam);
      char logs[256];
      sprintf(logs, "x=%ld, y=%ld", pt.x, pt.y);
      g_log.WriteLog("ClickCloseTab", logs);
      if (PtInRect(&rt, pt)) {
        msg->message = WM_NULL;
        CmdMsgItem item;
        item.cmd = kCmdTabClose;
        WriteToServer(item);
      }
    }
  }

  if ((msg->message == WM_NCLBUTTONDOWN && wParam == PM_REMOVE && 
       msg->wParam == HTCLOSE) && close_chrome_prompt && !is_only_one_tab) {
    msg->message = WM_NULL;
    CmdMsgItem item;
    item.cmd = kCmdChromeClose;
    WriteToServer(item);
  }

  if ((msg->message == WM_SYSCOMMAND && wParam == PM_REMOVE && 
      msg->wParam == SC_CLOSE) && close_chrome_prompt && !is_only_one_tab) {
    if (DialogBox(g_module, MAKEINTRESOURCE(IDD_CLOSECHROME), msg->hwnd,
                  CloseChromeDialgProc) != IDOK) {
      msg->message = WM_NULL;
    }
  }

  if ((msg->message == WM_LBUTTONDBLCLK || msg->message == WM_MBUTTONDOWN ||
      msg->message == WM_MBUTTONDBLCLK) && wParam == PM_REMOVE) {
    POINT pt;
    pt.x = GET_X_LPARAM(msg->lParam);
    pt.y = GET_Y_LPARAM(msg->lParam);
    RECT tab_client_rect = { 0 };
    GetClientRect(msg->hwnd, &tab_client_rect);
    if (enable_vertical_tabs) {
      tab_client_rect.right = tab_client_rect.left + kVerticalTabsWidth;
    } else {
      if (IsMaximized(msg->hwnd)) {
        tab_client_rect.top = 0;
        tab_client_rect.bottom = 25;
      } else {
        tab_client_rect.top += 15;
        tab_client_rect.bottom = tab_client_rect.top + 25;
      }
    }
    if (!PtInRect(&tab_client_rect, pt))
      return CallNextHookEx(NULL, code, wParam, lParam);

    TCHAR class_name[256];
    GetClassName(msg->hwnd, class_name, 256);
    if (_tcscmp(class_name, g_ChromeClassName) == 0 && 
        GetParent(msg->hwnd) == NULL) {
      CmdMsgItem item;
      if (close_last_tab && is_only_one_tab) {
        msg->message = WM_NULL;
        item.cmd = kCmdTabClose;
        WriteToServer(item);
      } else if (msg->message == WM_LBUTTONDBLCLK && db_click_close_tab) {
        msg->message = WM_NULL;
        item.cmd = kCmdDBClickCloseTab;
        WriteToServer(item);
      }
    }
  }
  return CallNextHookEx(NULL, code, wParam, lParam);
}

LRESULT CALLBACK CallWndProcHook(int code, WPARAM wParam, LPARAM lParam) {
  CWPSTRUCT* msg = (CWPSTRUCT*)lParam;

  ChromeWindowIdMap::iterator iter = chrome_window_map.find(msg->hwnd);
  if (enable_switch_tab && iter != chrome_window_map.end()) {
    bool enable_vertical_tabs = CheckVerticalTabsEnable(msg->hwnd);

    switch(msg->message) {
      case WM_MOUSEWHEEL: {
        RECT window_rect = {0};
        POINT pt;
        pt.x = GET_X_LPARAM(msg->lParam);
        pt.y = GET_Y_LPARAM(msg->lParam);
        GetWindowRect(msg->hwnd, &window_rect);
        if (enable_vertical_tabs) {
          window_rect.right = window_rect.left + kVerticalTabsWidth;
        } else {
          if (IsMaximized(msg->hwnd)) {
            window_rect.bottom = window_rect.top + 
               GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);
          } else {
            window_rect.bottom = window_rect.top + CONST_FRAME_CAPTION_HEIGHT;
          }
        }
        if (PtInRect(&window_rect, pt)) {
          CmdMsgItem item;
          item.cmd = kCmdMouseRotated;
          item.value.rotatedcount = 
              ((short)HIWORD(msg->wParam) / WHEEL_DELTA);
          WriteToServer(item);
        }
        break;
      }
    default:
      break;
    }
  }
  return CallNextHookEx(NULL, code, wParam, lParam);
}

void WriteToServer(const CmdMsgItem& item) {
  char logs[256];
  sprintf(logs, "WriteToServer, cmd=%d", item.cmd);
  DWORD writelen;
  if (WriteFile(client_pipe_handle, &item, sizeof(item), &writelen, NULL))
    g_log.WriteLog("Send", logs);
  else
    g_log.WriteLog("Send Error", logs);
}

void ExitClientThread() {
  if (!client_pipe_handle)
    return;

  if (WaitForSingleObject(client_thread_handle, 10) == WAIT_TIMEOUT) {
    TerminateThread(client_thread_handle, 0);
  }
}

}
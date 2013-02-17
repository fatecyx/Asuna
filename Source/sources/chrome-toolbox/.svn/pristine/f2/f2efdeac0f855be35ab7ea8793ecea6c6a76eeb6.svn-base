#include "video_alone_script_object.h"

#include <dwmapi.h>

#include "log.h"
#include "utils.h"
#include "video_window_manager.h"

HHOOK hCallWndProcHook = NULL;
extern Log g_log;
extern HMODULE g_module;
VideoWindowManager g_video_win_man;

int g_chrome_major_version = 0;
BOOL g_enable_dwm = FALSE;

WNDPROC g_old_proc = NULL;

int ReadChromeMajorVersion() {
  TCHAR current_path[MAX_PATH];
  GetCurrentDirectory(MAX_PATH, current_path);
  TCHAR file_name[MAX_PATH];
  _stprintf(file_name, _T("%s\\convenience.ini"), current_path);
  return GetPrivateProfileInt(_T("CFG"), _T("MAJORVERSION"), 0, file_name);
}

void WriteChromeMajorVersion() {
  TCHAR current_path[MAX_PATH];
  GetCurrentDirectory(MAX_PATH, current_path);
  TCHAR file_name[MAX_PATH];
  _stprintf(file_name, _T("%s\\convenience.ini"), current_path);
  TCHAR value[32];
  _stprintf(value, _T("%ld"), g_chrome_major_version);
  WritePrivateProfileString(_T("CFG"), _T("MAJORVERSION"), value, file_name);
}

LRESULT CALLBACK NewWndProc(HWND hWnd, UINT Msg, WPARAM wParam, 
                            LPARAM lParam) {
  LRESULT ret = 0;
  if (Msg == WM_PAINT) {
    ret = CallWindowProc(g_old_proc, hWnd, Msg, wParam, lParam);
    g_video_win_man.WndProc(hWnd, Msg, wParam, lParam);
  } else {
    ret = g_video_win_man.WndProc(hWnd, Msg, wParam, lParam);
    ret = CallWindowProc(g_old_proc, hWnd, Msg, wParam, lParam);
    if (Msg == WM_NCHITTEST && ret == HTCLIENT)
      ret = HTCAPTION;
  }
  return ret;
}

LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam) {
  CWPSTRUCT * pRet = (CWPSTRUCT *)lParam;

  if (pRet->message == WM_CHROMEHWND) {
    if (g_chrome_major_version == 0)
      g_chrome_major_version = ReadChromeMajorVersion();

    HMODULE h = LoadLibrary(_T("dwmapi.dll"));
    if (h) {
      DwmIsCompositionEnabled(&g_enable_dwm);
      FreeLibrary(h);
    }

    g_video_win_man.AddNewVideoWindow((HWND)pRet->wParam, (HWND)pRet->lParam);
    g_old_proc = SubclassWindow((HWND)pRet->wParam, NewWndProc);


    if (g_chrome_major_version >= MINIMUM_VERSION_SUPPORT_POPUP && 
        g_enable_dwm) {
      DwmSetWindowAttribute((HWND)pRet->wParam, DWMWA_ALLOW_NCPAINT, 
                            &g_enable_dwm, sizeof(g_enable_dwm));
      SendMessage((HWND)pRet->wParam, WM_NCPAINT, 0, 0);
    }

    if (g_chrome_major_version < MINIMUM_VERSION_SUPPORT_POPUP) {
      SetTimer((HWND)pRet->wParam, EVENTID_FRESH, 100, NULL);
    }
  }
  
  return CallNextHookEx(hCallWndProcHook, nCode, wParam, lParam);
}

VideoAloneScriptObject::WindowMap VideoAloneScriptObject::window_list_;

NPObject* VideoAloneScriptObject::Allocate(NPP npp, NPClass *aClass) {
  VideoAloneScriptObject* script_object = new VideoAloneScriptObject;
  if (script_object != NULL) {
    script_object->set_plugin((PluginBase*)npp->pdata);
  }
  return script_object;
}

void VideoAloneScriptObject::InitHandler() {
  FunctionItem item;
  item.function_name = "ShowVideoAlone";
  item.function_pointer = ON_INVOKEHELPER(&VideoAloneScriptObject::
      ShowVideoAlone);
  AddFunction(item);
  item.function_name = "GetWindowMetric";
  item.function_pointer = ON_INVOKEHELPER(&VideoAloneScriptObject::
      GetWindowMetric);
  AddFunction(item);
}

void VideoAloneScriptObject::Deallocate() {
  delete this;
}

bool VideoAloneScriptObject::GetWindowMetric(const NPVariant* args, 
                                             uint32_t argCount, 
                                             NPVariant* result) {
  int caption_height = GetSystemMetrics(SM_CYCAPTION);
  int border_width = GetSystemMetrics(SM_CXFRAME);
  int border_height = GetSystemMetrics(SM_CYFRAME);
  
  char buffer[200] = "";
  _snprintf(buffer, 200,
      "{\"captionHeight\": %ld, \"borderWidth\": %ld, \"borderHeight\": %ld}", 
      caption_height, border_width, border_height);
  int len = strlen(buffer) + 1;
  char* json_string = (char*)NPN_MemAlloc(len);
  if (json_string) {
    strncpy(json_string, buffer, len);
    STRINGZ_TO_NPVARIANT(json_string, *result);
  }

  return true;
}

bool VideoAloneScriptObject::ShowVideoAlone(const NPVariant *args,
                                            uint32_t argCount,
                                            NPVariant *result) {
  char szLog[512];

  if (argCount < 5)
    return false;

  for(int i = 0; i < 2; i++) {
    if (!NPVARIANT_IS_STRING(args[i])) {
      return false;
    }
  }

  for (int i = 2; i < 5; i++) {
    if (!NPVARIANT_IS_INT32(args[i]) && !NPVARIANT_IS_DOUBLE(args[i])) {
      return false;
    }
  }

  if (g_chrome_major_version == 0) {
    std::string user_agent = NPN_UserAgent(get_plugin()->get_npp());
    int index = user_agent.find("Chrome/");
    if (index != std::string::npos) {
      int last_index = user_agent.find('.', index);
      if (last_index != std::string::npos) {
        std::string majorversion = user_agent.substr(index + 7, 
                                                     last_index - index - 7);
        g_chrome_major_version = atoi(majorversion.c_str());
        WriteChromeMajorVersion();
      }
    }
  }

  utils::Utf8ToUnicode title(NPVARIANT_TO_STRING(args[0]).UTF8Characters,
                             NPVARIANT_TO_STRING(args[0]).UTF8Length);

  int loop = 0;
  HWND parent_hwnd = NULL;
  HWND hwnd;
  while(loop < 100) {
    parent_hwnd = FindWindowEx(NULL, parent_hwnd, 
                               _T("Chrome_WidgetWin_0"), NULL);
    if (parent_hwnd != NULL) {
      hwnd = FindWindowEx(parent_hwnd, NULL, _T("Chrome_WidgetWin_0"), title);
      if (hwnd)
        break;
    }
    sprintf(szLog, "WindowText=%s,Len=%ld,hParentWnd=0x%X",
            NPVARIANT_TO_STRING(args[0]).UTF8Characters,
            NPVARIANT_TO_STRING(args[0]).UTF8Length,
            parent_hwnd);
    g_log.WriteLog("Loop", szLog);
    loop++;
    Sleep(10);
  }

  if (!hwnd) {
    g_log.WriteLog("Error", "No Find Window");
    return false;
  }

  utils::Utf8ToUnicode original_title(
      NPVARIANT_TO_STRING(args[1]).UTF8Characters,
      NPVARIANT_TO_STRING(args[1]).UTF8Length);

  SetWindowText(hwnd, original_title);
  if (GetFirstChild(hwnd))
    SetWindowText(GetFirstChild(hwnd), original_title);
  if (!SetWindowText(parent_hwnd, original_title)) {
    sprintf(szLog, "SetWindowText GetLastError=%ld", GetLastError());
    g_log.WriteLog("Error", szLog);
  }

  hwnd = parent_hwnd;
  if (!hwnd) {
    sprintf(szLog, "WindowText=%s,Len=%ld,hParentWnd=0x%X",
            NPVARIANT_TO_STRING(args[0]).UTF8Characters,
            NPVARIANT_TO_STRING(args[0]).UTF8Length,
            parent_hwnd);
    g_log.WriteLog("ShowVideoAlone4", szLog);
    return false;
  }

  DWORD threadid = GetWindowThreadProcessId(hwnd, NULL);
  sprintf(szLog, "Chrome hwnd=0x%x,threadid=%ld", hwnd, threadid);
  g_log.WriteLog("Msg", szLog);

  if (!hCallWndProcHook)
    hCallWndProcHook = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc,
                                        g_module, threadid);
  if (!hCallWndProcHook) {
    sprintf(szLog, "SetWindowsHookEx Failed,GetLastError=%ld",
            GetLastError());
    g_log.WriteLog("Error", szLog);
  } else {
    g_log.WriteLog("Msg", "SetWindowsHookEx Success");
    SendMessage(hwnd, WM_CHROMEHWND, (WPARAM)hwnd, 
                (LPARAM)get_plugin()->get_hwnd());
  }

  HWND hEditHwnd = GetWindow(hwnd, GW_CHILD);
  while ((hEditHwnd = GetWindow(hEditHwnd, GW_HWNDNEXT)) != NULL && 
          GetClassNameA(hEditHwnd, szLog, 256) != 0 && 
          _stricmp(szLog, "Chrome_AutocompleteEditView") == 0) {
    SendMessage(hEditHwnd, WM_CLOSE, 0, 0);
    break;
  }

  WindowIDItem item = { 0 };
  item.parent_window_id = NPVARIANT_IS_INT32(args[2]) ? 
      NPVARIANT_TO_INT32(args[2]) : NPVARIANT_TO_DOUBLE(args[2]);
  item.window_id = NPVARIANT_IS_INT32(args[3]) ? 
      NPVARIANT_TO_INT32(args[3]) : NPVARIANT_TO_DOUBLE(args[3]);
  item.tab_id = NPVARIANT_IS_INT32(args[4]) ? 
      NPVARIANT_TO_INT32(args[4]) : NPVARIANT_TO_DOUBLE(args[4]);
  window_list_.insert(WindowMapPair(hwnd, item));

  BOOLEAN_TO_NPVARIANT(true, *result);

  return true;
}
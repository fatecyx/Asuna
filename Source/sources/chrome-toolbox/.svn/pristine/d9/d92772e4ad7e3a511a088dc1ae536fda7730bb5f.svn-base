#include "convenience_script_object.h"

#include "convenience_plugin.h"
#include "log.h"
#include "resource.h"
#include "utils.h"

extern Log g_log;
extern HMODULE g_module;
extern TCHAR g_ChromeClassName[MAX_PATH];
extern DWORD g_chrome_main_thread;
extern LocalMessageItem g_local_message;

std::list<HWND> ConvenienceScriptObject::hidden_window_list_;

NPObject* ConvenienceScriptObject::Allocate(NPP npp, NPClass *aClass) {
  ConvenienceScriptObject* script_object = new ConvenienceScriptObject;
  char logs[256];
  sprintf(logs, "CConvenienceScriptObject this=%ld", script_object);
  g_log.WriteLog("Allocate", logs);
  if (script_object != NULL) {
    script_object->set_plugin((PluginBase*)npp->pdata);
  }
  return script_object;
}

void ConvenienceScriptObject::InitHandler() {
  FunctionItem item;
  item.function_name = "UpdateShortCutList";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      UpdateShortCutList);
  AddFunction(item);
  item.function_name = "TriggerChromeShortcuts";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      TriggerChromeShortcuts);
  AddFunction(item);
  item.function_name = "PressBossKey";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      PressBossKey);
  AddFunction(item);
  item.function_name = "SetDBClickCloseTab";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      SetDBClickCloseTab);
  AddFunction(item);  
  item.function_name = "AddListener";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      AddListener);
  AddFunction(item);    
  item.function_name = "RemoveListener";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      RemoveListener);
  AddFunction(item);    
  item.function_name = "UpdateTabCount";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      UpdateTabCount);
  AddFunction(item);
  item.function_name = "CloseLastTab";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      CloseLastTab);
  AddFunction(item);
  item.function_name = "CloseChromePrompt";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      CloseChromePrompt);
  AddFunction(item);
  item.function_name = "ChromeWindowCreated";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      ChromeWindowCreated);
  AddFunction(item);
  item.function_name = "ChromeWindowRemoved";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      ChromeWindowRemoved);
  AddFunction(item);
  item.function_name = "EnableMouseSwitchTab";
  item.function_pointer = ON_INVOKEHELPER(&ConvenienceScriptObject::
      EnableMouseSwitchTab);
  AddFunction(item);
  item.function_name = "ExistsPinnedTab";
  item.function_pointer = ON_INVOKEHELPER(
      &ConvenienceScriptObject::ExistsPinnedTab);
  AddFunction(item);
  item.function_name = "PressEnterOpenNewTab";
  item.function_pointer = ON_INVOKEHELPER(
    &ConvenienceScriptObject::PressEnterOpenNewTab);
  AddFunction(item);
  item.function_name = "HideCurrentChromeWindow";
  item.function_pointer = ON_INVOKEHELPER(
      &ConvenienceScriptObject::HideCurrentChromeWindow);
  AddFunction(item);
  item.function_name = "RestoreLastHiddenWindow";
  item.function_pointer = ON_INVOKEHELPER(
      &ConvenienceScriptObject::RestoreLastHiddenWindow);
  AddFunction(item);
}

void ConvenienceScriptObject::Deallocate() {
  char szLog[256];
  sprintf(szLog, "CConvenienceScriptObject this=%ld", this);
  g_log.WriteLog("Deallocate", szLog);
  delete this;
}

bool ConvenienceScriptObject::UpdateShortCutList(const NPVariant *args,
                                                 uint32_t argCount,
                                                 NPVariant *result) {
  NPObject* window;
  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->GetLocalMessage();
  NPN_GetValue(plugin->get_npp(), NPNVWindowNPObject, &window);

  if (argCount != 1 || !NPVARIANT_IS_OBJECT(args[0])) {
    NPN_SetException(this, "parameter is invalid");
    return false;
  }
  if (shortcuts_object_ != NULL) 
    NPN_ReleaseObject(shortcuts_object_);

  shortcuts_object_ = NPVARIANT_TO_OBJECT(args[0]);
  NPN_RetainObject(shortcuts_object_);
  NPVariant length;

  NPIdentifier id;
  id = NPN_GetStringIdentifier("length");
  if (!id) {
    NPN_SetException(this, "object has not property of length");
    return false;
  }

  if (NPN_GetProperty(plugin->get_npp(), shortcuts_object_, id, &length)) {
    int len = 0;
    if (NPVARIANT_IS_INT32(length))
      len = NPVARIANT_TO_INT32(length);
    else if (NPVARIANT_IS_DOUBLE(length))
      len = NPVARIANT_TO_DOUBLE(length);

    NPVariant array_item;
    NPObject* array_object;
    NPVariant property_value;

    ShortCutKeyMap* key_map_new;
    ShortCutKeyMap* key_map_old;
    if (shortcuts_used_flag_ == 2) {
      key_map_new = &map_one_;
      key_map_old = &map_two_;
    } else {
      key_map_new = &map_two_;
      key_map_old = &map_one_;
    }
    if (shortcuts_list_ != NULL)
      delete[] shortcuts_list_;

    shortcuts_list_ = new ShortCutItem[len];

    for (int i = 0; i < len; i++) {
      ShortCutItem item = { 0 };
      item.index = i;
      id = NPN_GetIntIdentifier(i);
      NPN_GetProperty(plugin->get_npp(), shortcuts_object_, id, &array_item);
      array_object = NPVARIANT_TO_OBJECT(array_item);
      id = NPN_GetStringIdentifier("shortcut");
      if (id) {
        NPN_GetProperty(plugin->get_npp(), array_object,
                        id, &property_value);
        if (NPVARIANT_IS_STRING(property_value)) {
          std::string temp(NPVARIANT_TO_STRING(property_value).UTF8Characters,
                           NPVARIANT_TO_STRING(property_value).UTF8Length);
          strcpy(item.shortcuts_key, temp.c_str());
        }
      }
      id = NPN_GetStringIdentifier("operation");
      if (id) {
        NPN_GetProperty(plugin->get_npp(), array_object,
                        id, &property_value);
        if (NPVARIANT_IS_STRING(property_value)) {
          std::string temp(NPVARIANT_TO_STRING(property_value).UTF8Characters,
                           NPVARIANT_TO_STRING(property_value).UTF8Length);
          strcpy(item.function, temp.c_str());
        }
      }
      id = NPN_GetStringIdentifier("type");
      if (id) {
        NPN_GetProperty(plugin->get_npp(), array_object, id, &property_value);
        if (NPVARIANT_IS_BOOLEAN(property_value))
          item.ishotkey = NPVARIANT_TO_BOOLEAN(property_value);
      }
      item.object = array_object;
      key_map_new->insert(ShortCutPair(item.shortcuts_key, item));
      shortcuts_list_[i] = item;
    }

    plugin->SetShortcutsToMemory(shortcuts_list_, len);
    
    ShortCutKeyMap::iterator iter;
    for (iter = key_map_old->begin(); iter != key_map_old->end(); iter++) {
      if (iter->second.ishotkey) {
        ATOM atom = GlobalFindAtomA(iter->second.shortcuts_key);
        UnregisterHotKey(plugin->get_hwnd(), atom);
        GlobalDeleteAtom(atom);
      }
    }
    key_map_old->clear();
    for (iter = key_map_new->begin(); iter != key_map_new->end(); iter++) {
      if (iter->second.ishotkey) {
        ATOM atom = GlobalAddAtomA(iter->second.shortcuts_key);
        UINT vk = 0, modify = 0;
        GetShortCutsKey(iter->second.shortcuts_key, &modify, &vk);
        BOOL register_ret = RegisterHotKey(plugin->get_hwnd(), 
                                           atom, modify, vk);
      }
    }
    shortcuts_used_flag_ = shortcuts_used_flag_ == 2 ? 1 : 2;
  }

  return true;
}

void ConvenienceScriptObject::GetShortCutsKey(const char* shortcuts, UINT* modify,
                                              UINT* vk) {
  const char* pStart = shortcuts;
  const char* pEnd = pStart;
  char temp_value[10];
  int temp_key;
  *modify = 0;
  pEnd = strstr(pStart, "+");
  if (!pEnd) {
    *vk = atoi(shortcuts);
    return;
  }

  while (pEnd = strstr(pStart, "+")) {
    memcpy(temp_value, pStart, pEnd-pStart);
    temp_value[pEnd-pStart]=0;
    pStart = pEnd+1;
    temp_key = atoi(temp_value);
    switch(temp_key) {
      case VK_CONTROL:
        *modify |= MOD_CONTROL;
        break;
      case VK_SHIFT:
        *modify |= MOD_SHIFT;
        break;
      case VK_MENU:
        *modify |= MOD_ALT;
        break;
      case VK_LWIN:
      case VK_RWIN:
        *modify |= MOD_WIN;
        break;
      default:
        *vk = temp_key;
        break;
    }
  }

  strcpy(temp_value, pStart);
  temp_key = atoi(temp_value);
  switch(temp_key) {
      case VK_CONTROL:
        *modify |= MOD_CONTROL;
        break;
      case VK_SHIFT:
        *modify |= MOD_SHIFT;
        break;
      case VK_MENU:
        *modify |= MOD_ALT;
        break;
      case VK_LWIN:
      case VK_RWIN:
        *modify |= MOD_WIN;
        break;
      default:
        *vk = temp_key;
        break;
  }
}

void ConvenienceScriptObject::TriggerEvent(const char* shortcuts) {
  g_log.WriteLog("TriggerEvent", shortcuts);
  ShortCutKeyMap* shortcut_map;
  if (shortcuts_used_flag_ == 1)
    shortcut_map = &map_one_;
  else
    shortcut_map = &map_two_;

  ShortCutKeyMap::iterator iter = shortcut_map->find(shortcuts);
  if (iter != shortcut_map->end()) {
    NPVariant param;
    OBJECT_TO_NPVARIANT((NPObject*)iter->second.object, param);
    InvokeJSMethod("executeShortcut", &param, 1);
  }
}

void ConvenienceScriptObject::TriggerEvent(int index) {
  g_log.WriteLog("TriggerEvent", "index");
  if (shortcuts_list_[index].ishotkey)
    return;

  NPVariant param;
  OBJECT_TO_NPVARIANT((NPObject*)shortcuts_list_[index].object, param);
  InvokeJSMethod("executeShortcut", &param, 1);
}

void ConvenienceScriptObject::TriggerSwitchTab(bool forward) {
  g_log.WriteLog("Invoke", "TriggerSwitchTab");
  NPVariant param;
  BOOLEAN_TO_NPVARIANT(forward, param);
  InvokeJSMethod("wheelSwitchTab", &param, 1);
}

void ConvenienceScriptObject::TriggerShortcuts(UINT modify, UINT vk, 
                                               bool issleep /* = true */) {
  INPUT inputs[4] = { 0 };
  int keycount = 0;

  if (issleep)
    Sleep(100);

  if (modify & MOD_CONTROL) {
    inputs[keycount].type = INPUT_KEYBOARD;
    inputs[keycount].ki.wVk = VK_CONTROL;
    inputs[keycount].ki.wScan = MapVirtualKey(VK_CONTROL, MAPVK_VK_TO_VSC);
    inputs[keycount].ki.time = GetTickCount();
    keycount++;
  }
  if (modify & MOD_SHIFT) {
    inputs[keycount].type = INPUT_KEYBOARD;
    inputs[keycount].ki.wVk = VK_SHIFT;
    inputs[keycount].ki.wScan = MapVirtualKey(VK_SHIFT, MAPVK_VK_TO_VSC);
    inputs[keycount].ki.time = GetTickCount();
    keycount++;
  }
  if (modify & MOD_ALT) {
    inputs[keycount].type = INPUT_KEYBOARD;
    inputs[keycount].ki.wVk = VK_MENU;
    inputs[keycount].ki.wScan = MapVirtualKey(VK_MENU, MAPVK_VK_TO_VSC);
    inputs[keycount].ki.time = GetTickCount();
    keycount++;
  }
  inputs[keycount].type = INPUT_KEYBOARD;
  inputs[keycount].ki.wVk = vk;
  if ((vk >= VK_PRIOR && vk <= VK_DELETE) || (vk >= VK_LWIN && vk <= VK_APPS) ||
      vk == VK_NUMLOCK || vk == VK_DIVIDE)
    inputs[keycount].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
  inputs[keycount].ki.wScan = MapVirtualKey(vk, MAPVK_VK_TO_VSC);
  inputs[keycount].ki.time = GetTickCount();
  keycount++;
  char logs[256];
  sprintf(logs, "keycount=%d, vk=%d", keycount, vk);
  g_log.WriteLog("SendInput start", logs);
  SendInput(keycount, inputs, sizeof(INPUT));

  for (int i = 0; i < keycount; i++) {
    inputs[i].ki.dwFlags |= KEYEVENTF_KEYUP;
  }
  SendInput(keycount, inputs, sizeof(INPUT));
  sprintf(logs, "keycount=%d", keycount);
  g_log.WriteLog("SendInput end", logs);
}

bool ConvenienceScriptObject::PressBossKey(const NPVariant *args,
                                           uint32_t argCount,
                                           NPVariant *result) {
  static BOOL bosskey_state = FALSE;
  static std::vector<HWND> window_list;
  HWND chrome_hwnd;
  if (bosskey_state){
    bosskey_state = FALSE;
    chrome_hwnd = FindWindowEx(NULL, NULL, g_ChromeClassName, NULL);
    while(chrome_hwnd) {
      if (IsWindowVisible(chrome_hwnd) && 
          GetWindowThreadProcessId(chrome_hwnd, NULL) == g_chrome_main_thread) {
        window_list.insert(window_list.begin(), chrome_hwnd);
        bosskey_state = TRUE;
      }
      chrome_hwnd = FindWindowEx(NULL, chrome_hwnd, g_ChromeClassName, NULL);
    }
    if (bosskey_state) {
      std::vector<HWND>::iterator iter;
      for (iter = window_list.begin(); iter != window_list.end(); iter++) {
        ShowWindow(*iter, SW_HIDE);
      }
      return true;
    }

    std::vector<HWND>::iterator iter;
    for (iter = window_list.begin(); iter != window_list.end(); iter++) {
      ShowWindow(*iter, SW_SHOW);
    }
    window_list.clear();
  } else {
    bosskey_state = TRUE;
    chrome_hwnd = FindWindowEx(NULL, NULL, g_ChromeClassName, NULL);
    while(chrome_hwnd) {
      if (IsWindowVisible(chrome_hwnd) && 
          GetWindowThreadProcessId(chrome_hwnd, NULL) == g_chrome_main_thread) {
        window_list.insert(window_list.begin(), chrome_hwnd);
      }
      chrome_hwnd = FindWindowEx(NULL, chrome_hwnd, g_ChromeClassName,NULL);
    }
    std::vector<HWND>::iterator iter;
    for (iter = window_list.begin(); iter != window_list.end(); iter++) {
      ShowWindow(*iter, SW_HIDE);
    }
  }

  return true;
}

bool ConvenienceScriptObject::HideCurrentChromeWindow(const NPVariant* args, 
                                                      uint32_t argCount, 
                                                      NPVariant* result) {
  HWND chrome_hwnd = FindWindowEx(NULL, NULL, g_ChromeClassName, NULL);
  while(chrome_hwnd) {
    if (IsWindowVisible(chrome_hwnd) && GetParent(chrome_hwnd) == NULL &&
        GetWindowThreadProcessId(chrome_hwnd, NULL) == g_chrome_main_thread) {
      ShowWindow(chrome_hwnd, SW_HIDE);
      if (!IsWindowVisible(chrome_hwnd))
        hidden_window_list_.push_back(chrome_hwnd);
      break;
    }
    chrome_hwnd = FindWindowEx(NULL, chrome_hwnd, g_ChromeClassName, NULL);
  }

  return true;
}

bool ConvenienceScriptObject::RestoreLastHiddenWindow(const NPVariant* args, 
                                                      uint32_t argCount, 
                                                      NPVariant* result) {
  if (hidden_window_list_.size() > 0) {
    std::list<HWND>::reverse_iterator iter = hidden_window_list_.rbegin();
    ShowWindow(*iter, SW_SHOW);
    if (IsWindowVisible(*iter))
      hidden_window_list_.pop_back();
  }
  return true;
}

bool ConvenienceScriptObject::TriggerChromeShortcuts(const NPVariant *args, 
                                                     uint32_t argCount, 
                                                     NPVariant *result) {
  BOOLEAN_TO_NPVARIANT(FALSE, *result);
  if (argCount != 1 || !NPVARIANT_IS_STRING(args[0]))
    return false;

  std::string shortcuts(NPVARIANT_TO_STRING(args[0]).UTF8Characters,
                        NPVARIANT_TO_STRING(args[0]).UTF8Length);
  g_log.WriteLog("Shortcuts", shortcuts.c_str());

  UINT modify, vk, keycount = 0;
  GetShortCutsKey(shortcuts.c_str(), &modify, &vk);
  INPUT inputs[4] = { 0 };
  inputs[0].type = INPUT_KEYBOARD;
  inputs[0].ki.wVk = VK_ESCAPE;
  inputs[0].ki.wScan = MapVirtualKey(VK_ESCAPE, MAPVK_VK_TO_VSC);
  inputs[0].ki.time = GetTickCount();
  SendInput(1, inputs, sizeof(INPUT));
  inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, inputs, sizeof(INPUT));

  PostMessage(get_plugin()->get_hwnd(), WM_TRIGGER_CHROME_SHORTCUTS, modify, vk);

  BOOLEAN_TO_NPVARIANT(TRUE, *result);

  return true;
}

bool ConvenienceScriptObject::SetDBClickCloseTab(const NPVariant *args,
                                                 uint32_t argCount, 
                                                 NPVariant *result) {
  BOOLEAN_TO_NPVARIANT(FALSE, *result);
  if (argCount != 1 || !NPVARIANT_IS_BOOLEAN(args[0]))
    return true;
  
  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->UpdateDBClick_CloseTab(NPVARIANT_TO_BOOLEAN(args[0]));
  BOOLEAN_TO_NPVARIANT(TRUE, *result);
  return true;
}

bool ConvenienceScriptObject::AddListener(const NPVariant *args,
                                          uint32_t argCount,
                                          NPVariant *result) {
  if (argCount != 1 || !NPVARIANT_IS_OBJECT(args[0]))
    return false;

  char logs[256];
  input_object_ = NPVARIANT_TO_OBJECT(args[0]);
  sprintf(logs, "input_object_=%ld", input_object_);
  g_log.WriteLog("AddListener", logs);
  NPN_RetainObject(input_object_);
  is_listened_ = true;
  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->UpdateIsListening(is_listened_);
  return true;
}

bool ConvenienceScriptObject::RemoveListener(const NPVariant *args, 
                                             uint32_t argCount, 
                                             NPVariant *result) {
  if (!is_listened_)
    return true;

  is_listened_ = false;
  NPN_ReleaseObject(input_object_);
  char logs[256];
  sprintf(logs, "input_object_=%ld", input_object_);
  g_log.WriteLog("RemoveListener", logs);
  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->UpdateIsListening(is_listened_);
  return true;
}

bool ConvenienceScriptObject::UpdateTabCount(const NPVariant *args, 
                                             uint32_t argCount, 
                                             NPVariant *result) {
  if (argCount != 2)
    return false;

  int windowid = NPVARIANT_IS_INT32(args[0]) ? NPVARIANT_TO_INT32(args[0]) :
      NPVARIANT_TO_DOUBLE(args[0]);
  int tabcount = NPVARIANT_IS_INT32(args[1]) ? NPVARIANT_TO_INT32(args[1]) :
      NPVARIANT_TO_DOUBLE(args[1]);
  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->UpdateTabCount(windowid, tabcount);
  return true;
}

bool ConvenienceScriptObject::CloseChromePrompt(const NPVariant *args, 
                                                uint32_t argCount, 
                                                NPVariant *result) {
  if (argCount != 1 || !NPVARIANT_IS_BOOLEAN(args[0]))
    return false;

  bool prompt  = NPVARIANT_TO_BOOLEAN(args[0]);
  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->UpdateCloseChromePromptFlag(prompt);
  return true;
}

bool ConvenienceScriptObject::CloseLastTab(const NPVariant *args, 
                                           uint32_t argCount, 
                                           NPVariant *result) {
  if (argCount != 1 || !NPVARIANT_IS_BOOLEAN(args[0]))
    return false;

  bool close_last_tab  = NPVARIANT_TO_BOOLEAN(args[0]);
  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->UpdateCloseLastTab(close_last_tab);
  return true;
}

bool ConvenienceScriptObject::ChromeWindowCreated(const NPVariant *args, 
                                                  uint32_t argCount, 
                                                  NPVariant *result) {
  if (argCount != 1)
    return false;

  int windowid = NPVARIANT_IS_INT32(args[0]) ? NPVARIANT_TO_INT32(args[0]) :
      NPVARIANT_TO_DOUBLE(args[0]);
  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->ChromeWindowCreated(windowid);

  return true;
}

bool ConvenienceScriptObject::ChromeWindowRemoved(const NPVariant *args, 
                                                  uint32_t argCount, 
                                                  NPVariant *result) {
  if (argCount != 1)
    return false;

  int windowid = NPVARIANT_IS_INT32(args[0]) ? NPVARIANT_TO_INT32(args[0]) :
      NPVARIANT_TO_DOUBLE(args[0]);

  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->ChromeWindowRemoved(windowid);

  return true;
}

bool ConvenienceScriptObject::EnableMouseSwitchTab(const NPVariant* args, 
                                                   uint32_t argCount, 
                                                   NPVariant* result) {
  if (argCount != 1 || !NPVARIANT_IS_BOOLEAN(args[0]))
    return false;

  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->EnableMouseSwitchTab(NPVARIANT_TO_BOOLEAN(args[0]));
  return true;
}

bool ConvenienceScriptObject::ExistsPinnedTab(const NPVariant* args, 
                                              uint32_t argCount, 
                                              NPVariant* result) {
  if (argCount != 2 || 
      (!NPVARIANT_IS_DOUBLE(args[0]) && !NPVARIANT_IS_INT32(args[0])) ||
      !NPVARIANT_IS_BOOLEAN(args[1]))
    return false;

  int windowid = NPVARIANT_IS_INT32(args[0]) ? NPVARIANT_TO_INT32(args[0]) :
      NPVARIANT_TO_DOUBLE(args[0]);
  bool pinned = NPVARIANT_TO_BOOLEAN(args[1]);
  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->ExistsPinnedTab(windowid, pinned);
  return true;
}

bool ConvenienceScriptObject::PressEnterOpenNewTab(const NPVariant* args, 
                                                   uint32_t argCount, 
                                                   NPVariant* result) {
  if (argCount != 1 || !NPVARIANT_IS_BOOLEAN(args[0]))
    return false;

  ConveniencePlugin* plugin = (ConveniencePlugin*)get_plugin();
  plugin->PressEnterOpenNewTab(NPVARIANT_TO_BOOLEAN(args[0]));
  return true;
}

void ConvenienceScriptObject::UpdateCloseChromePromptFlag(BOOL flag) {
  NPVariant param;
  BOOLEAN_TO_NPVARIANT(flag, param);
  InvokeJSMethod("updateCloseChromePromptFlag", &param, 1);
}

void ConvenienceScriptObject::InvokeJSMethod(const char* method_name, 
                                             NPVariant* args /* = NULL */, 
                                             uint32_t argCount /* = 0 */) {
  NPObject* window;
  PluginBase* plugin = get_plugin();
  NPN_GetValue(plugin->get_npp(), NPNVWindowNPObject, &window);
  NPIdentifier id;
  id = NPN_GetStringIdentifier(method_name);
  NPVariant result;
  VOID_TO_NPVARIANT(result);
  if (id) {
    NPN_Invoke(plugin->get_npp(), window, id, args, argCount, &result);
    NPN_ReleaseVariantValue(&result);
  }
}

void ConvenienceScriptObject::OnKeyDown(bool contrl, bool alt, bool shift,
                                        WPARAM wParam, LPARAM lParam) {
  g_log.WriteLog("msg", "OnKeyDown");
  if (is_listened_) {
    std::string keys = "";
    if (contrl)
      keys += "17+";
    if (alt)
      keys += "18+";
    if (shift)
      keys += "16+";

    if (wParam != VK_CONTROL && wParam != VK_MENU && wParam != VK_SHIFT) {
      char key[MAX_KEY_LEN];
      _itoa(wParam, key, 10);
      keys += key;
    }

    g_log.WriteLog("keyvalue", keys.c_str());
    NPVariant params[2];
    OBJECT_TO_NPVARIANT(input_object_, params[0]);
    STRINGZ_TO_NPVARIANT(keys.c_str(), params[1]);
    InvokeJSMethod("setShortcutsToInputBox", params, 2);
  }
}
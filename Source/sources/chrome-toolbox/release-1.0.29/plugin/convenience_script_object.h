#ifndef CONVENIENCE_SCRIPT_OBJECT_H_
#define CONVENIENCE_SCRIPT_OBJECT_H_

#include <list>
#include <map>
#include <string> 

#include "script_object_base.h"

// Script object for ConveniencePlugin.
class ConvenienceScriptObject : public ScriptObjectBase {
private:
  ConvenienceScriptObject(void) : shortcuts_list_(NULL), 
                                  shortcuts_object_(NULL), 
                                  is_listened_(false) {}
  virtual ~ConvenienceScriptObject(void) {}

public:
  static NPObject* Allocate(NPP npp, NPClass *aClass); 

  void InitHandler();

  void Deallocate();
  void Invalidate() {}
  bool Construct(const NPVariant *args, uint32_t argCount,
                 NPVariant *result) { return true; }

  // Some interface for front-end.

  // Update shortcuts list to memory, notify client process update from
  // memory file.
  bool UpdateShortCutList(const NPVariant *args, uint32_t argCount,
                          NPVariant *result);

  // Front-end call this function to implement boss key feature.
  bool PressBossKey(const NPVariant *args, uint32_t argCount,
                    NPVariant *result);

  // Notify plugin to trigger chrome's shortcuts.
  bool TriggerChromeShortcuts(const NPVariant *args, uint32_t argCount,
                              NPVariant *result);

  // Set state of double click close tab.
  bool SetDBClickCloseTab(const NPVariant *args, uint32_t argCount,
                          NPVariant *result);

  // Notify plugin current state is set shortcuts, and deliver
  // the input box object from front-end to plugin.
  bool AddListener(const NPVariant *args, uint32_t argCount,
                   NPVariant *result);

  // Notify plugin that set shortcuts has finished.
  bool RemoveListener(const NPVariant *args, uint32_t argCount,
                      NPVariant *result);

  // Notify plugin current chrome window has or not only one tab.
  bool UpdateTabCount(const NPVariant *args, uint32_t argCount,
                    NPVariant *result);

  // Notify plugin is prompt when chrome close with more than one tab.
  bool CloseChromePrompt(const NPVariant *args, uint32_t argCount,
                         NPVariant *result);

  // Notify plugin when close the last tab, whether close the chrome.
  bool CloseLastTab(const NPVariant *args, uint32_t argCount,
                    NPVariant *result);

  // Notify plugin a chrome window created.
  bool ChromeWindowCreated(const NPVariant *args, uint32_t argCount,
                           NPVariant *result);

  // Notify plugin a chrome window removed.
  bool ChromeWindowRemoved(const NPVariant *args, uint32_t argCount,
                           NPVariant *result);

  // Notify plugin to enable mouse wheel switch tab or not.
  bool EnableMouseSwitchTab(const NPVariant* args, uint32_t argCount,
                            NPVariant* result);

  // Notify plugin the specified chrome window has pinned tab or not.
  bool ExistsPinnedTab(const NPVariant* args, uint32_t argCount,
                       NPVariant* result);

  // Notify plugin to enable press enter to open new tab or not.
  bool PressEnterOpenNewTab(const NPVariant* args, uint32_t argCount,
                            NPVariant* result);

  // Hide current chrome window.
  bool HideCurrentChromeWindow(const NPVariant* args, uint32_t argCount,
                               NPVariant* result);

  // Restore last hidden window.
  bool RestoreLastHiddenWindow(const NPVariant* args, uint32_t argCount,
                               NPVariant* result);


  // For plugin object used. when plugin receive keyboard stroke key, 
  // then call this function to notify frontend some key pressed.
  void OnKeyDown(bool contrl, bool alt, bool shift, WPARAM wParam,
                 LPARAM lParam);

  void UpdateCloseChromePromptFlag(BOOL flag);
  
  // Call the front-end functions.
  void InvokeJSMethod(const char* method_name, NPVariant* args = NULL, 
                      uint32_t argCount = 0);

  // Notify front-end user has trigger a feature.
  void TriggerEvent(const char* shortcuts);

  // Notify front-end user has trigger a feature.
  void TriggerEvent(int index);

  // Send shortcuts to chrome.
  void TriggerShortcuts(UINT modify, UINT vk, bool issleep = true);

  // Notify front-end switch tab.
  void TriggerSwitchTab(bool forward);

  typedef std::map<std::string, ShortCutItem> ShortCutKeyMap;
  typedef std::pair<std::string, ShortCutItem> ShortCutPair;

  bool get_is_listened() { return is_listened_; }

private:
  // According shortcuts string to generate modify flag and virtual key code.
  void GetShortCutsKey(const char* shortcuts, UINT* modify, UINT* vk);
  
private:
  // The flag indicate current shortcut key map used.
  int shortcuts_used_flag_;  //flag = 1,flag = 2
  ShortCutKeyMap map_one_;
  ShortCutKeyMap map_two_;

  // Shortcuts list store current shortcuts.
  ShortCutItem* shortcuts_list_;

  // Shortcuts array object from front-end.
  NPObject* shortcuts_object_;

  // Indicate current state is or not set shortcuts.
  bool is_listened_;

  // Input box object.
  NPObject* input_object_;

  // Store hidden chrome window.
  static std::list<HWND> hidden_window_list_;

};

#endif
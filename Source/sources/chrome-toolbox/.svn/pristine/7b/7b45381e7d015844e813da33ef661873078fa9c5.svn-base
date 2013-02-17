#ifndef BROWSER_MUTE_PLUGIN_H_
#define BROWSER_MUTE_PLUGIN_H_

#include "plugin_base.h"
#include "script_object_base.h"

// Plugin for browser mute feature.
class BrowserMutePlugin : public PluginBase {
private:
  BrowserMutePlugin(void) {}
  virtual ~BrowserMutePlugin(void) {}

public:
  NPError Init(NPP instance, uint16_t mode, int16_t argc, char* argn[],
               char* argv[], NPSavedData* saved);
  NPError UnInit(NPSavedData** save);
  NPError GetValue(NPPVariable variable, void *value);

  // Create browser mute plugin object.
  static PluginBase* CreateObject() { return new BrowserMutePlugin; }

  // Get flag that current plugin is using apihook or not.
  BOOL get_use_api_hook_flag() { return use_apihook_flag_; }

  // When plugin initializing, call this function for inject apihook dll.
  void ScanAndInject();

  // Because chrome update feature, rename apihook dll as mutechrome.dll.
  void RenameApiHookDll();

  // Inject mutechrome.dll to process.
  bool InjectIntoProcess(HANDLE hprocess);

private:
  // Muting thread only use in win7 system.
  static DWORD WINAPI Mute_Thread(void* param);

private:
  ScriptObjectBase* script_object_;
  
  // Handle of ntdll.dll
  HMODULE ntdll_handle_;

  // Muting thread handle.
  HANDLE mute_thread_handle_;

  // When plugin is unloaded, using this event handle to notify
  // muting thread to stop.
  HANDLE stop_event_;
  BOOL use_apihook_flag_;

};

#endif
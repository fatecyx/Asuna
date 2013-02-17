#ifndef BROWSER_MUTE_SCRIPT_OBJECT_H_
#define BROWSER_MUTE_SCRIPT_OBJECT_H_

#include "script_object_base.h"

typedef void (*Pfn_SetBrowserMute)(BOOL flag);

// Script object for browser mute feature.
class BrowserMuteScriptObject : public ScriptObjectBase {
private:
  BrowserMuteScriptObject(void) : api_hook_module_(NULL) {}
  virtual ~BrowserMuteScriptObject(void) {}

public:
  static NPObject* Allocate(NPP npp, NPClass *aClass);

  void InitHandler();

  void Deallocate();
  void Invalidate() {}
  bool Construct(const NPVariant *args, uint32_t argCount,
                 NPVariant *result) { return true; }

  // Mute browser interface for frontend.
  bool MuteBrowser(const NPVariant *args, uint32_t argCount,
                   NPVariant *result);

  // Check mute is available.
  bool CheckMuteAvailable(const NPVariant *args, uint32_t argCount,
                          NPVariant *result);

  BOOL get_mute_flag() { return mute_flag_; }

private:
  enum ErrorCode {
    kAvailableMute = 1,
    kUnavailableMute,
    kFlashPluginNotRun,
  };

private:
  // The apihook.dll module hanlde.
  HMODULE api_hook_module_;

  // The function address of SetBrowseMute function in apihook.dll.
  Pfn_SetBrowserMute set_browser_mute_;

  BOOL mute_flag_;

};

#endif
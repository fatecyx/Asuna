#ifndef VIDEO_ALONE_PLUGIN_H_
#define VIDEO_ALONE_PLUGIN_H_

#include <GdiPlus.h>

#include "plugin_base.h"
#include "script_object_base.h"

using namespace Gdiplus;

// Plugin for video stand-alone.
class VideoAlonePlugin : public PluginBase {
private:
  VideoAlonePlugin(void);
  virtual ~VideoAlonePlugin(void);

public:
  NPError Init(NPP instance, uint16_t mode, int16_t argc, char* argn[],
               char* argv[], NPSavedData* saved);
  NPError UnInit(NPSavedData** save);
  NPError GetValue(NPPVariable variable, void *value);
  NPError SetWindow(NPWindow* window);

  // Create video alone object.
  static PluginBase* CreateObject() { return new VideoAlonePlugin; }

private:
  // The window procedure for subclass.
  static LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

  // Send flag of flash fullscreen status.
  static void SendFlashFullscreenStatus(bool fullscreen_flag);

private:
  ScriptObjectBase* script_object_;
  static WNDPROC old_proc_;
  ULONG_PTR token_;
  GdiplusStartupInput start_input_;

};

#endif
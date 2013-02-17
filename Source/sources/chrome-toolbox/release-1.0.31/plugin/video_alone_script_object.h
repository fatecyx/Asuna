#ifndef VIDEO_ALONE_SCRIPT_OBJECT_H_
#define VIDEO_ALONE_SCRIPT_OBJECT_H_

#include <map>

#include "script_object_base.h"

// Video alone script object, providing methods to find the video window.
class VideoAloneScriptObject : public ScriptObjectBase {
private:
  VideoAloneScriptObject(void) {}
  virtual ~VideoAloneScriptObject(void) {}

public:
  static NPObject* Allocate(NPP npp, NPClass *aClass); 

  void InitHandler();

  void Deallocate();
  void Invalidate() {}
  bool Construct(const NPVariant *args, uint32_t argCount,
                 NPVariant *result) { return true; }

  // Find the specified video window and hook it's window procedure.
  bool ShowVideoAlone(const NPVariant *args, uint32_t argCount,
                      NPVariant *result);

  // Get caption height, border width and height of system window.
  bool GetWindowMetric(const NPVariant* args, uint32_t argCount,
                        NPVariant* result);

public:
  struct WindowIDItem{
    int parent_window_id;
    int window_id;
    int tab_id;
  };

  typedef std::map<HWND, WindowIDItem> WindowMap;
  typedef std::pair<HWND, WindowIDItem> WindowMapPair;

  static WindowMap* get_video_alone_list() { return &window_list_; }

private:
  // A set of video stand-alone window.
  static WindowMap window_list_;

};

#endif
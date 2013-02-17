#ifndef VIDEO_WINDOW_MANAGER_H_
#define VIDEO_WINDOW_MANAGER_H_

#include <map>

#include "video_window.h"

// Video stand-alone window manager,
// managing creation and destroy of video window object.
class VideoWindowManager {
public:
  VideoWindowManager(void) {}
  ~VideoWindowManager(void);

  bool AddNewVideoWindow(HWND chromeHwnd, HWND videoHwnd);
  void RemoveVideoWindow(HWND chromeHwnd);
  BOOL WndProc(HWND hwnd, UINT& msg, WPARAM& wParam, LPARAM& lParam);

private:
  typedef std::map<HWND, VideoWindow*> VideoMap;
  typedef std::pair<HWND, VideoWindow*> VideoWinPair;

private:
  // Video stand-alone window list.
  VideoMap video_map_;
  
};

#endif
#ifndef VIDEO_WINDOW_H_
#define VIDEO_WINDOW_H_

#include "ncbutton.h"

enum ResizeState {
  kNeedResizeState = 1,
  kReadyResizeState,
  kFinishResizeState,
};

// Video stand-alone window class, this class is used for handling message
// that should be disposed
class VideoWindow {
public:
  VideoWindow(void) {}
  ~VideoWindow(void) {}

  bool InitWindow(HWND chromeHwnd, HWND videoHwnd);
  bool IsEnqual(HWND hwnd) { return hwnd == chrome_hwnd_; }

  // Window procedure.
  BOOL WndProc(HWND hwnd, UINT& msg, WPARAM& wParam, LPARAM& lParam);

  // Replace our window procedure by the original window procedure.
  void Unsubclass();

  // Used in aero theme for paint custom caption.
  void PaintCustomCaption(BOOL drawicon);

private:
  HWND chrome_hwnd_;
  HWND video_hwnd_;
  NCButton tip_button_;
  LPARAM last_size_param_;
  ResizeState resize_state_;
  UINT loop_num_;

};

#endif
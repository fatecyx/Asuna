#ifndef NCBUTTON_H_
#define NCBUTTON_H_

#include <GdiPlus.h>
#include <windows.h>

using namespace Gdiplus;

// Non-Client button class, it's used for video stand-alone feature.
// this class implement to draw a custom button in the Non-Client area
// and response the mouse's click and move event.
class NCButton {
public:
  NCButton(void);
  ~NCButton(void);

  void Init(HWND parenthwnd);

  // Dispose WM_PAINT message.
  void OnPaint(HDC paintdc = NULL);

  // Dispose WM_MOUSEOVER message.
  void OnMouseOver(POINT pt);

  // Dispose WM_MOUSEDOWN message.
  void OnMouseDown(POINT pt);

  // Dispose WM_MOUSEUP message.
  void OnMouseUp(POINT pt);

  // Dispose WM_MOUSELEAVE message.
  void OnMouseLeave();

  // Dispose WM_DWMCOMPOSITIONCHANGED message.
  void OnDwmEnableChanged();

  // Update flash fullscreen status.
  void UpdateFullscreenStatus(bool fullscreen_flag);

private:
  enum ButtonState{
    kButtonStateInvalid = 0,
    kButtonStateNormal,
    kButtonStateMouseOver,
    kButtonStateMouseDown,
  };

  // get the coordinates of a button's area. the coordinates are relative to
  // the upper-left corner of screen
  void GetButtonRect();

private:
  // load button image form local file
  void LoadButtonImage();

private:
  RECT rect_;
  HWND parent_hwnd_;
  ButtonState button_state_;
  bool is_topmost_;
  bool old_topmost_state_;
  Image* normal_image_;
  Image* mouse_over_image_;
  Image* mouse_down_image_;
  Image* notip_normal_image_;
  Image* notip_mouseover_image_;
  Image* notip_mousedown_image_;
  int tip_button_width_;
  int tip_button_height_;
  HDC mask_dc_;
  HBITMAP mask_bitmap_;
  Graphics* grph_;
  ULONG_PTR token_;
  GdiplusStartupInput start_input_;

};

#endif
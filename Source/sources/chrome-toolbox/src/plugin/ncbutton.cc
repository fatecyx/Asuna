#include "ncbutton.h"

#include <CommCtrl.h>
#include <dwmapi.h>

#include "log.h"
#include "video_alone_script_object.h"

extern Log g_log;
extern HMODULE g_module;
extern LocalMessageItem g_local_message;
extern int g_chrome_major_version;
extern BOOL g_enable_dwm;

NCButton::NCButton(void) {
  is_topmost_ = false;
  Gdiplus::GdiplusStartup(&token_, &start_input_, NULL);
}

NCButton::~NCButton(void) {
  Gdiplus::GdiplusShutdown(token_);
}

void NCButton::Init(HWND parenthwnd) {
  parent_hwnd_ = parenthwnd;
  mask_dc_ = NULL;
  mask_bitmap_ = NULL;
  normal_image_ = NULL;
  mouse_over_image_ = NULL;
  mouse_down_image_ = NULL;
  notip_normal_image_ = NULL;
  notip_mouseover_image_ = NULL;
  notip_mousedown_image_ = NULL;

  LoadButtonImage();

  grph_ = Graphics::FromHDC(GetWindowDC(parent_hwnd_));

  SetWindowPos(parent_hwnd_, HWND_TOPMOST, 0, 0, 0, 0,
               SWP_NOSIZE | SWP_NOMOVE);

  is_topmost_ = true;
}

void NCButton::OnPaint(HDC paintdc /* = NULL */) {
  POINT pt;

  GetButtonRect();

  RECT window_rect;
  HDC windowdc = NULL;
  GetWindowRect(parent_hwnd_, &window_rect);
  pt.x = rect_.left - window_rect.left;
  pt.y = rect_.top - window_rect.top;
  if (grph_ != NULL)
    delete grph_;
  if (paintdc != NULL)
    grph_ = Graphics::FromHDC(paintdc);
  else {
    grph_ = Graphics::FromHDC(GetWindowDC(parent_hwnd_));
  }

  if (mask_dc_) {
    DeleteDC(mask_dc_);
    DeleteObject(mask_bitmap_);
  }

  HDC hdc = grph_->GetHDC();
  mask_dc_ = CreateCompatibleDC(hdc);
  mask_bitmap_ = CreateCompatibleBitmap(hdc, normal_image_->GetWidth(),
                                        normal_image_->GetHeight());
  SelectObject(mask_dc_, mask_bitmap_);
  if (IsMaximized(parent_hwnd_) || 
      g_chrome_major_version >= MINIMUM_VERSION_SUPPORT_POPUP)
    BitBlt(mask_dc_, 0, 0, normal_image_->GetWidth(), normal_image_->GetHeight(),
           hdc, pt.x-tip_button_width_-CONST_FRAME_BORDER, pt.y, SRCCOPY);
  else {
    RECT rt;
    GetClientRect(parent_hwnd_, &rt);
    BitBlt(mask_dc_, 0, 0, normal_image_->GetWidth(), normal_image_->GetHeight(),
           hdc, rt.right-tip_button_width_-CONST_FRAME_BORDER, 
           pt.y+tip_button_height_, SRCCOPY);
  }
  grph_->ReleaseHDC(hdc);

  HDC hdc_temp = CreateCompatibleDC(mask_dc_);
  HBITMAP bitmap = CreateCompatibleBitmap(mask_dc_, normal_image_->GetWidth(), 
                                          normal_image_->GetHeight());
  SelectObject(hdc_temp, bitmap);
  BitBlt(hdc_temp, 0, 0, normal_image_->GetWidth(), normal_image_->GetWidth(),
         mask_dc_, 0, 0, SRCCOPY);
  Graphics g(hdc_temp);
  
  if (is_topmost_) {
    Status state = g.DrawImage(mouse_down_image_, 
        Rect(0, 0, tip_button_width_, tip_button_height_), 0, 0, 
        mouse_down_image_->GetWidth(), mouse_down_image_->GetHeight(), 
        UnitPixel);
  } else if (button_state_ == kButtonStateMouseOver) {
    Status state = g.DrawImage(notip_mouseover_image_, 
        Rect(0, 0, tip_button_width_, tip_button_height_), 0, 0,
        mouse_over_image_->GetWidth(), mouse_over_image_->GetHeight(), 
        UnitPixel);
    button_state_ = kButtonStateMouseOver;
  } else {
    Status state = g.DrawImage(notip_normal_image_, 
        Rect(0, 0, tip_button_width_, tip_button_height_), 0, 0,
        normal_image_->GetWidth(), normal_image_->GetHeight(), 
        UnitPixel);
    button_state_ = kButtonStateNormal;
  }
  HDC destdc = grph_->GetHDC();
  BitBlt(destdc, pt.x, pt.y, tip_button_width_, tip_button_height_, 
         hdc_temp, 0, 0, SRCCOPY);
  grph_->ReleaseHDC(destdc);
  DeleteDC(hdc_temp);
  DeleteObject(bitmap);
  if (paintdc) {
    delete grph_;
    grph_ = Graphics::FromHDC(GetWindowDC(parent_hwnd_));
  }
}

void NCButton::OnMouseLeave() {
  OnPaint();
}

void NCButton::OnMouseDown(POINT pt) {
  GetButtonRect();

  if (PtInRect(&rect_, pt)) {
    POINT pt;
    RECT window_rect;
    GetWindowRect(parent_hwnd_, &window_rect);
    pt.x = rect_.left - window_rect.left;
    pt.y = rect_.top - window_rect.top;
    HDC hdc = grph_->GetHDC();
    BitBlt(hdc, pt.x, pt.y, tip_button_width_, tip_button_height_, 
           mask_dc_, 0, 0, SRCCOPY);
    grph_->ReleaseHDC(hdc);
    if (is_topmost_) {
      SetWindowPos(parent_hwnd_, HWND_NOTOPMOST, 0, 0, 0, 0, 
                   SWP_NOSIZE | SWP_NOMOVE);

      Status state = grph_->DrawImage(mouse_down_image_, 
          Rect(pt.x, pt.y, tip_button_width_, tip_button_height_), 0, 0,
          normal_image_->GetWidth(), normal_image_->GetHeight(),UnitPixel);
      is_topmost_ = false;
    } else {
      SetWindowPos(parent_hwnd_, HWND_TOPMOST, 0, 0, 0, 0, 
                   SWP_NOSIZE | SWP_NOMOVE);
      Status state = grph_->DrawImage(notip_mousedown_image_, 
          Rect(pt.x, pt.y, tip_button_width_, tip_button_height_), 0, 0,
          mouse_down_image_->GetWidth(), mouse_down_image_->GetHeight(),
          UnitPixel);
      is_topmost_ = true;
    }
    button_state_ = kButtonStateMouseDown;
  }
}

void NCButton::OnMouseOver(POINT pt) {  
  static HWND hwnd_tooltip = NULL;
  static TOOLINFO toolinfo = {0};

  GetButtonRect();

  if (PtInRect(&rect_, pt) && button_state_ == kButtonStateNormal) {
    POINT pt;
    RECT window_rect;
    GetWindowRect(parent_hwnd_, &window_rect);
    pt.x = rect_.left - window_rect.left;
    pt.y = rect_.top - window_rect.top;
    HDC hdc = grph_->GetHDC();
    BitBlt(hdc, pt.x, pt.y, tip_button_width_, tip_button_height_, 
           mask_dc_, 0, 0, SRCCOPY);
    grph_->ReleaseHDC(hdc);
    if (is_topmost_)
      grph_->DrawImage(mouse_over_image_, 
          Rect(pt.x, pt.y, tip_button_width_, tip_button_height_), 0, 0,
          mouse_over_image_->GetWidth(), mouse_over_image_->GetHeight(),
          UnitPixel);
    else
      grph_->DrawImage(notip_mouseover_image_, 
          Rect(pt.x, pt.y, tip_button_width_, tip_button_height_), 0, 0,
          notip_mouseover_image_->GetWidth(), notip_mouseover_image_->GetHeight(),
          UnitPixel);

    if (!hwnd_tooltip) {
      INITCOMMONCONTROLSEX iccex; 

      iccex.dwICC = ICC_WIN95_CLASSES;
      iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
      InitCommonControlsEx(&iccex);

      hwnd_tooltip = CreateWindowEx(
          WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
          WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT, 
          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, 
          g_module, NULL);

      SetWindowPos(hwnd_tooltip, HWND_TOPMOST, 0, 0, 0, 0,
                   SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }

    if (hwnd_tooltip) {
      toolinfo.cbSize = sizeof(TOOLINFO);
      toolinfo.uFlags = TTF_SUBCLASS;
      toolinfo.hwnd = parent_hwnd_;
      toolinfo.hinst = g_module;
      toolinfo.uId = 0;
      toolinfo.lpszText = g_local_message.msg_always_on_top;
      pt.x = rect_.left;
      pt.y = rect_.top;
      ScreenToClient(parent_hwnd_, &pt);
      toolinfo.rect.left = pt.x;
      toolinfo.rect.top = pt.y;
      pt.x = rect_.right;
      pt.y = rect_.bottom;
      ScreenToClient(parent_hwnd_, &pt);
      toolinfo.rect.right = pt.x;
      toolinfo.rect.bottom = pt.y;
      SendMessage(hwnd_tooltip, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&toolinfo);
    }

    button_state_ = kButtonStateMouseOver;
  } else if (!PtInRect(&rect_, pt) && button_state_ != kButtonStateNormal) {
    toolinfo.hwnd = parent_hwnd_;
    SendMessage(hwnd_tooltip, TTM_DELTOOL, 0, (LPARAM) (LPTOOLINFO) &toolinfo);	
    button_state_ = kButtonStateNormal;
    OnPaint();
  }
}

void NCButton::OnMouseUp(POINT pt) {  
  GetButtonRect();

  if (PtInRect(&rect_, pt)) {
    POINT pt;
    RECT window_rect;
    GetWindowRect(parent_hwnd_, &window_rect);
    pt.x = rect_.left - window_rect.left;
    pt.y = rect_.top - window_rect.top;
    HDC hdc = grph_->GetHDC();
    BitBlt(hdc, pt.x, pt.y, tip_button_width_, tip_button_height_,
           mask_dc_, 0, 0, SRCCOPY);
    grph_->ReleaseHDC(hdc);
    if (is_topmost_)
      grph_->DrawImage(mouse_over_image_, 
          Rect(pt.x, pt.y, tip_button_width_, tip_button_height_), 0, 0,
          mouse_over_image_->GetWidth(), mouse_over_image_->GetHeight(),
          UnitPixel);
    else
      grph_->DrawImage(notip_mouseover_image_, 
          Rect(pt.x, pt.y, tip_button_width_, tip_button_height_), 0, 0,
          notip_mouseover_image_->GetWidth(), notip_mouseover_image_->GetHeight(),
          UnitPixel);
    button_state_ = kButtonStateMouseOver;
  }
}

void NCButton::OnDwmEnableChanged() {
  LoadButtonImage();
}

void NCButton::LoadButtonImage() {
  TCHAR filename[MAX_PATH];
  TCHAR png_filename[MAX_PATH];
  GetModuleFileName(g_module, filename, MAX_PATH);
  TCHAR* postfix = _tcsrchr(filename, '\\');
  if (postfix)
    *postfix = 0;

  if (normal_image_)
    delete normal_image_;
  if (mouse_over_image_)
    delete mouse_over_image_;
  if (mouse_down_image_)
    delete mouse_down_image_;
  if (notip_normal_image_)
    delete notip_normal_image_;
  if (notip_mouseover_image_)
    delete notip_mouseover_image_;
  if (notip_mousedown_image_)
    delete notip_mousedown_image_;

  if (g_chrome_major_version >= MINIMUM_VERSION_SUPPORT_POPUP && 
      g_enable_dwm) {
    _stprintf(
        png_filename, _T("%s\\resources\\tip_mousedown_win7.png"), filename);
    normal_image_ = new Image(png_filename);
    _stprintf(
        png_filename, _T("%s\\resources\\tip_mouseover_win7.png"), filename);
    mouse_over_image_ = new Image(png_filename);
    _stprintf(
        png_filename, _T("%s\\resources\\tip_mousedown_win7.png"), filename);
    mouse_down_image_ = new Image(png_filename);
    _stprintf(
        png_filename, _T("%s\\resources\\notip_normal_win7.png"), filename);
    notip_normal_image_ = new Image(png_filename);
    _stprintf(
        png_filename, _T("%s\\resources\\notip_mouseover_win7.png"), filename);
    notip_mouseover_image_ = new Image(png_filename);
    _stprintf(
        png_filename, _T("%s\\resources\\notip_mousedown_win7.png"), filename);
    notip_mousedown_image_ = new Image(png_filename);
  } else {
    _stprintf(png_filename, _T("%s\\resources\\tip_normal.png"), filename);
    normal_image_ = new Image(png_filename);
    _stprintf(png_filename, _T("%s\\resources\\tip_mouseover.png"), filename);
    mouse_over_image_ = new Image(png_filename);
    _stprintf(png_filename, _T("%s\\resources\\tip_mousedown.png"), filename);
    mouse_down_image_ = new Image(png_filename);
    _stprintf(png_filename, _T("%s\\resources\\notip_normal.png"), filename);
    notip_normal_image_ = new Image(png_filename);
    _stprintf(
        png_filename, _T("%s\\resources\\notip_mouseover.png"), filename);
    notip_mouseover_image_ = new Image(png_filename);
    _stprintf(
        png_filename, _T("%s\\resources\\notip_mousedown.png"), filename);
    notip_mousedown_image_ = new Image(png_filename);
  }
}

void NCButton::GetButtonRect() {
  RECT rt;

  GetWindowRect(parent_hwnd_, &rt);
  if (IsMaximized(parent_hwnd_)) {
    rt.top = 0;
    rt.right -= CONST_FRAME_BORDER;
  } else {
    rt.top++;
    if (g_chrome_major_version < MINIMUM_VERSION_SUPPORT_POPUP && g_enable_dwm)
      rt.right += CONST_FRAME_BORDER;
  }
  if (g_enable_dwm) {
    rect_.right = rt.right - VISTA_OFFSET_LEN;
  } else
    rect_.right = rt.right - OFFSET_LEN;

  tip_button_width_ = normal_image_->GetWidth();
  tip_button_height_ = normal_image_->GetHeight();

  rect_.top = rt.top;
  rect_.left = rect_.right - tip_button_width_;
  rect_.bottom = rect_.top + tip_button_height_;
}

void NCButton::UpdateFullscreenStatus(bool fullscreen_flag) {
  if (fullscreen_flag) {
    old_topmost_state_ = is_topmost_;
    is_topmost_ = false;
  } else {
    is_topmost_ = old_topmost_state_;
  }
  if (is_topmost_) {
    SetWindowPos(parent_hwnd_, HWND_TOPMOST, 0, 0, 0, 0, 
                 SWP_NOSIZE | SWP_NOMOVE);
  } else {
    SetWindowPos(parent_hwnd_, HWND_NOTOPMOST, 0, 0, 0, 0, 
                 SWP_NOSIZE | SWP_NOMOVE);
  }
  OnPaint();
}
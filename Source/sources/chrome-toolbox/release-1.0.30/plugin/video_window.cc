#include "video_window.h"

#include <dwmapi.h>
#include <Uxtheme.h>

#include "log.h"
#include "resource.h"
#include "video_window_manager.h"


extern Log g_log;
extern HMODULE g_module;
extern WNDPROC g_old_proc;
extern int g_chrome_major_version;
extern BOOL g_enable_dwm;
extern VideoWindowManager g_video_win_man;

const int kMinChromeHeight = 150;
const int kBorderWidth = 8;
const int kOffsetSize = 8;
const int kIconSize = 16;
const int kCaptionHeight = 30;

bool VideoWindow::InitWindow(HWND chromeHwnd, HWND videoHwnd) {
  chrome_hwnd_ = chromeHwnd;
  video_hwnd_ = videoHwnd;
  last_size_param_ = NULL;
  resize_state_ = kNeedResizeState;
  loop_num_ = 9;
  tip_button_.Init(chrome_hwnd_);

  return true;
}

void VideoWindow::Unsubclass() {
  if (IsWindow(chrome_hwnd_) && g_old_proc != NULL) {
    SubclassWindow(chrome_hwnd_, g_old_proc);
    if (g_chrome_major_version >= MINIMUM_VERSION_SUPPORT_POPUP && 
        g_enable_dwm) {
      BOOL enable_dwm = FALSE;
      DwmSetWindowAttribute(chrome_hwnd_, DWMWA_ALLOW_NCPAINT, 
                            &enable_dwm, sizeof(enable_dwm));
      SendMessage(chrome_hwnd_, WM_NCPAINT, 0, 0);
    }
  }
}

void VideoWindow::PaintCustomCaption(BOOL drawicon) {
  RECT rcClient;
  GetWindowRect(chrome_hwnd_, &rcClient);
  HDC hdc = GetWindowDC(chrome_hwnd_);
  HTHEME hTheme = OpenThemeData(NULL, L"CompositedWindow::Window");
  if (hTheme) {
    HDC hdcPaint = CreateCompatibleDC(hdc);
    if (hdcPaint) {
      int cx = rcClient.right - rcClient.left;
      int cy = rcClient.bottom -rcClient.top;

      // Define the BITMAPINFO structure used to draw text.
      // Note that biHeight is negative. This is done because
      // DrawThemeTextEx() needs the bitmap to be in top-to-bottom
      // order.
      BITMAPINFO dib = { 0 };
      dib.bmiHeader.biSize            = sizeof(BITMAPINFOHEADER);
      dib.bmiHeader.biWidth           = cx;
      dib.bmiHeader.biHeight          = -cy;
      dib.bmiHeader.biPlanes          = 1;
      dib.bmiHeader.biBitCount        = 32;
      dib.bmiHeader.biCompression     = BI_RGB;

      HBITMAP hbm = CreateDIBSection(hdc, &dib, DIB_RGB_COLORS, NULL, NULL, 0);
      if (hbm) {
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcPaint, hbm);

        // Setup the theme drawing options.
        DTTOPTS DttOpts = {sizeof(DTTOPTS)};
        DttOpts.dwFlags = DTT_COMPOSITED | DTT_GLOWSIZE;
        DttOpts.iGlowSize = 15;

        // Select a font.
        LOGFONT lgFont;
        HFONT hFontOld = NULL;
        if (SUCCEEDED(GetThemeSysFont(hTheme, 801, &lgFont))) {
          HFONT hFont = CreateFontIndirect(&lgFont);
          hFontOld = (HFONT) SelectObject(hdcPaint, hFont);
        }

        // Draw the title.
        TCHAR szTitle[1024];
        GetWindowText(chrome_hwnd_, szTitle, 1024);
        RECT rcPaint = rcClient;
        rcPaint.top  = kOffsetSize;
        rcPaint.right = cx - VISTA_OFFSET_LEN - 3*TIP_BUTTON_WIDTH;
        rcPaint.left = kCaptionHeight;
        rcPaint.bottom = kCaptionHeight;
        DrawThemeTextEx(hTheme, hdcPaint, 0, 0, szTitle, -1, 
                        DT_LEFT | DT_WORD_ELLIPSIS, &rcPaint, 
                        &DttOpts);

        DrawIconEx(hdcPaint, kOffsetSize, kOffsetSize, 
                   (HICON)SendMessage(chrome_hwnd_, WM_GETICON, 0, 0), 
                   kIconSize, kIconSize, 0, NULL, DI_NORMAL | DI_COMPAT);
        tip_button_.OnPaint(hdcPaint);
        if (drawicon) {
          cx = kCaptionHeight;
          cy = kCaptionHeight;
          BitBlt(hdc, 0, 0, cx, cy, hdcPaint, 0, 0, SRCCOPY);
        } else {
          BitBlt(hdc, 0, 0, cx, kCaptionHeight, hdcPaint, 0, 0, SRCCOPY);
          BitBlt(hdc, 0, 0, kBorderWidth, cy, hdcPaint, 0, 0, SRCCOPY);
          BitBlt(hdc, cx-kBorderWidth, 0, kBorderWidth, cy, hdcPaint,
                 cx-kBorderWidth, 0, SRCCOPY);
          BitBlt(hdc, 0, cy-kBorderWidth, cx, kBorderWidth, hdcPaint, 0,
                 cy-kBorderWidth, SRCCOPY);
        }

        SelectObject(hdcPaint, hbmOld);
        if (hFontOld) {
          SelectObject(hdcPaint, hFontOld);
        }
        DeleteObject(hbm);
      }
      DeleteDC(hdcPaint);
    }
    CloseThemeData(hTheme);
  }
  ReleaseDC(chrome_hwnd_, hdc);
}

BOOL VideoWindow::WndProc(HWND hwnd, UINT& msg, WPARAM& wParam, LPARAM& lParam) {
  if (hwnd != chrome_hwnd_) {
    return FALSE;
  }  
  
  POINT pt;
  
  char logs[256]; 
  sprintf(logs, "hwnd=0x%X,msg=0x%04X,wParam=%ld,lParam=%ld,ThreadID=%ld",
          hwnd, msg, wParam, lParam, GetCurrentThreadId());
  g_log.WriteLog("WndProc", logs);
  switch(msg) {
    case WM_NCPAINT:
      if (g_chrome_major_version >= MINIMUM_VERSION_SUPPORT_POPUP && 
          g_enable_dwm) {
        PaintCustomCaption(FALSE);
      }
      break;
    case WM_PAINT:
    case WM_ACTIVATE:
      if (g_chrome_major_version >= MINIMUM_VERSION_SUPPORT_POPUP || 
          resize_state_ == kReadyResizeState || 
          resize_state_ == kFinishResizeState)
        tip_button_.OnPaint();
      break;
    case WM_SETICON:
      if (g_chrome_major_version >= MINIMUM_VERSION_SUPPORT_POPUP &&
          g_enable_dwm) {
        PaintCustomCaption(TRUE);
      }
      break;
    case WM_DWMCOMPOSITIONCHANGED: 
      if (DwmIsCompositionEnabled(&g_enable_dwm) == S_OK) {
        tip_button_.OnDwmEnableChanged();
        if (g_chrome_major_version >= MINIMUM_VERSION_SUPPORT_POPUP && 
            g_enable_dwm) {
          DwmSetWindowAttribute(hwnd, DWMWA_ALLOW_NCPAINT, 
                                &g_enable_dwm, sizeof(g_enable_dwm));
          SendMessage(hwnd, WM_NCPAINT, 0, 0);
        }
      }
      break;
    case WM_TIMER: {
      if (wParam != EVENTID_FRESH)
        break;

      HWND hChildWnd = FindWindowEx(chrome_hwnd_, NULL, 
                                    _T("Chrome_WidgetWin_0"), NULL);
      int cy = CONST_FRAME_CAPTION_HEIGHT;
      if (IsMaximized(chrome_hwnd_))
        cy = 25;
      int cx = CONST_FRAME_BORDER;
      RECT rt;
      GetWindowRect(chrome_hwnd_, &rt);
      if (loop_num_++ % 10 == 0) {
        if (last_size_param_ == NULL) {
          int height = rt.bottom - rt.top;
          if (height < kMinChromeHeight)
            height = kMinChromeHeight;
          resize_state_ = kReadyResizeState;
          SetWindowPos(chrome_hwnd_, NULL, 0, 0, rt.right-rt.left, height, 
                       SWP_NOMOVE | SWP_NOREPOSITION);
          last_size_param_ = MAKELPARAM(rt.right-rt.left, height);
        } else if (resize_state_ == kNeedResizeState) {
          resize_state_ = kReadyResizeState;
          SendMessage(chrome_hwnd_, WM_SIZE, SIZE_RESTORED, last_size_param_);
        }
        GetWindowRect(chrome_hwnd_, &rt);
      }

      if (hChildWnd != NULL) {
        RECT rt1;
        GetWindowRect(hChildWnd, &rt1);
        if (rt1.top != rt.top + cy) {
          MoveWindow(hChildWnd, cx, cy, rt.right-rt.left-2*cx,
                     rt.bottom-rt.top-cy-2*cx, FALSE);
          sprintf(logs, "rt1.top=%ld,rt.top=%ld,cx=%ld", rt1.top, 
                  rt.top, cy);
          g_log.WriteLog("MoveWindow", logs);
        }
      } else
        g_log.WriteLog("Error", "hChildWnd==NULL");
      break;
    }
    case WM_NCMOUSEMOVE:
      pt.x = GET_X_LPARAM(lParam);
      pt.y = GET_Y_LPARAM(lParam);
      tip_button_.OnMouseOver(pt);
      break;
    case WM_NCLBUTTONDOWN:
      pt.x = GET_X_LPARAM(lParam);
      pt.y = GET_Y_LPARAM(lParam);
      tip_button_.OnMouseDown(pt);
      if (wParam == HTCLOSE)
        msg = WM_NULL;
      break;
    case WM_NCLBUTTONUP:
      pt.x = GET_X_LPARAM(lParam);
      pt.y = GET_Y_LPARAM(lParam);
      if (wParam == HTCLOSE) {
        PostMessage(video_hwnd_, WM_CHROMECLOSE, (WPARAM)chrome_hwnd_, 0);
        Unsubclass();
        g_video_win_man.RemoveVideoWindow(chrome_hwnd_);
      }
      tip_button_.OnMouseUp(pt);
      break;
    case WM_NCLBUTTONDBLCLK:
      if (g_chrome_major_version < MINIMUM_VERSION_SUPPORT_POPUP)
        msg = WM_NULL;
      break;
    case WM_NCMOUSELEAVE:
      tip_button_.OnMouseLeave();
      break;
    case WM_FLASH_FULLSCREEN_STATUS:
      tip_button_.UpdateFullscreenStatus(lParam);
      break;
    case WM_DESTROY:
      g_log.WriteLog("WM_DESTROY", "WM_DESTROY");
      break;
    case WM_CLOSE:
      g_log.WriteLog("WM_CLOSE", "WM_CLOSE");
      break;
    case WM_QUIT:
      g_log.WriteLog("WM_QUIT", "WM_QUIT");
      break;
    case WM_SYSCOMMAND:
      if (wParam == SC_CLOSE) {
        msg = WM_NULL;
        PostMessage(video_hwnd_, WM_CHROMECLOSE, (WPARAM)chrome_hwnd_, 0);
        Unsubclass();
        g_video_win_man.RemoveVideoWindow(chrome_hwnd_);
      }
      break;
    case WM_SIZE: {
      if (g_chrome_major_version >= MINIMUM_VERSION_SUPPORT_POPUP)
        break;

      if (resize_state_ != kReadyResizeState) {
        msg = WM_NULL;
        resize_state_ = kNeedResizeState;
      } else if (resize_state_ == kReadyResizeState) {
        resize_state_ = kFinishResizeState;
      }

      HWND hChildWnd = FindWindowEx(chrome_hwnd_, NULL, 
                                    _T("Chrome_WidgetWin_0"), NULL);
      int cy = CONST_FRAME_CAPTION_HEIGHT;
      int cx = CONST_FRAME_BORDER;
      int width, height;
      width = LOWORD(lParam);
      height = HIWORD(lParam);
      if (height < kMinChromeHeight) {
        SetWindowPos(chrome_hwnd_, NULL, 0, 0, width, kMinChromeHeight, 
                     SWP_NOMOVE | SWP_NOREPOSITION);
        lParam = MAKELPARAM(width, kMinChromeHeight);
        height = kMinChromeHeight;
      }
      last_size_param_ = lParam;

      if (hChildWnd != NULL) {
        MoveWindow(hChildWnd, cx, cy, width-2*cx, height-cy-2*cx, FALSE);
        sprintf(logs, "width=%ld,heigth=%ld,cx=%ld,cy=%ld",
                width, height, cx, cy);
        g_log.WriteLog("MoveWindow", logs);
      } else
        g_log.WriteLog("Error", "hChildWnd==NULL");
      break;
    }
  }

  return FALSE;
}
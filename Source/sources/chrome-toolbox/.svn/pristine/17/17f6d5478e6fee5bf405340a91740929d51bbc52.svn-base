#include "background_script_object.h"

#include <atlenc.h>

#include "log.h"
#include "resource.h"
#include "script_object_factory.h"
#include "utils.h"

extern HMODULE g_module;
extern Log g_log;
extern TCHAR g_ChromeClassName[MAX_PATH];

namespace {

// Window handle for setting wallpaper.
HWND g_WallPapperWindow = NULL;

// get the classid by format
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
  UINT num = 0;          // number of image encoders
  UINT size = 0;         // size of the image encoder array in bytes

  ImageCodecInfo* pImageCodecInfo = NULL;

  GetImageEncodersSize(&num, &size);
  if(size == 0)
    return -1;  // Failure

  pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
  if(pImageCodecInfo == NULL)
    return -1;  // Failure

  GetImageEncoders(num, size, pImageCodecInfo);

  for(UINT j = 0; j < num; ++j) {
    if(wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
      *pClsid = pImageCodecInfo[j].Clsid;
      free(pImageCodecInfo);
      return j;  // Success
    }
  }

  free(pImageCodecInfo);
  return -1;  // Failure
}

// timer procedure for removing the omnibox and 
// modifying the chrome window style.
void WINAPI TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) {
  TCHAR class_name[256];
  if (!GetClassName(g_WallPapperWindow, class_name, 256))
    return;

  if (_tcscmp(class_name, g_ChromeClassName) == 0) {
    HWND hChildWnd = FindWindowEx(
        g_WallPapperWindow, NULL, _T("Chrome_AutocompleteEditView"), NULL);
    if (hChildWnd)
      SendMessage(hChildWnd, WM_CLOSE, 0, 0);
    hChildWnd = FindWindowEx(
        g_WallPapperWindow, NULL, _T("Chrome_WidgetWin_0"), NULL);
    int cx, cy;
    cx = CONST_FRAME_BORDER;
    cy = 25;
    static utils::WinVersion version = utils::GetWinVersion();
    if (version == utils::WINVERSION_WIN7) {
      cx = cy = 0;
    }

    SetWindowLong(
        g_WallPapperWindow, GWL_STYLE, WS_CAPTION | WS_VISIBLE | 
        DS_FIXEDSYS | WS_OVERLAPPED | WS_CLIPCHILDREN | WS_CLIPSIBLINGS 
        | WS_SYSMENU | WS_MINIMIZEBOX);

    int width, height;
    static RECT rt = { 0 };
    if (rt.left == rt.right && rt.top == rt.bottom) {
      GetWindowRect(g_WallPapperWindow, &rt);
      width = rt.right - rt.left;
      height = rt.bottom - rt.top;
    } else {
      width = rt.right - rt.left;
      height = rt.bottom - rt.top;
      SetWindowPos(
          g_WallPapperWindow, NULL, 0, 0, width, height, 
          SWP_NOMOVE | SWP_NOREPOSITION);
    }

    if (hChildWnd != NULL) {
      MoveWindow(hChildWnd, cx, cy, width-2*cx, height-cy-2*cx, TRUE);
    }
  }
}

}

NPObject* BackgroundScriptObject::Allocate(NPP npp, NPClass *aClass) {
  BackgroundScriptObject* background_object = new BackgroundScriptObject;
  char logs[256];
  sprintf(logs, "BackgroundScriptObject this=%ld", background_object);
  g_log.WriteLog("Allocate", logs);
  if (background_object != NULL) {
    background_object->set_plugin((PluginBase*)npp->pdata);
  }
  return background_object;
}

void BackgroundScriptObject::InitHandler() {
  FunctionItem item;
  item.function_name = "SetWallPaper";
  item.function_pointer = ON_INVOKEHELPER(&BackgroundScriptObject::
      SetWallPaper);
  AddFunction(item);
  item.function_name = "ApplyWallPaper";
  item.function_pointer = ON_INVOKEHELPER(&BackgroundScriptObject::
      ApplyWallPaper);
  AddFunction(item);
  item.function_name = "RestoreWallPaper";
  item.function_pointer = ON_INVOKEHELPER(&BackgroundScriptObject::
      RestoreWallPaper);
  AddFunction(item);
  item.function_name = "SaveImage";
  item.function_pointer = ON_INVOKEHELPER(&BackgroundScriptObject::SaveImage);
  AddFunction(item);
}

void BackgroundScriptObject::Deallocate() {
  char logs[256];
  sprintf(logs, "this=%ld", this);
  g_log.WriteLog("Deallocate", logs);
  delete this;
}
 
bool BackgroundScriptObject::SetWallPaper(const NPVariant *args,
                                          uint32_t argCount,
                                          NPVariant *result) {
  BOOLEAN_TO_NPVARIANT(FALSE, *result);
  HRESULT hr;
  IActiveDesktop* active_desktop;
  g_WallPapperWindow = GetForegroundWindow();

  SetTimer(get_plugin()->get_hwnd(), 1, 100, TimerProc);

  hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,
      IID_IActiveDesktop, (void**)&active_desktop);
  if (FAILED(hr))
    return true;

  hr = active_desktop->GetWallpaper(ori_wallpaper_, MAX_PATH, AD_GETWP_BMP);
  if (FAILED(hr)) {
    active_desktop->Release();
    return true;
  }
  ori_opt_.dwSize = sizeof(ori_opt_);
  hr = active_desktop->GetWallpaperOptions(&ori_opt_, 0);
  if (FAILED(hr)) {
    active_desktop->Release();
    return true;
  }

  active_desktop->Release();
  BOOLEAN_TO_NPVARIANT(TRUE, *result);

  return true; 
}

bool BackgroundScriptObject::ApplyWallPaper(const NPVariant *args,
                                            uint32_t argCount,
                                            NPVariant *result) {
  std::string type;
  const char* base64 = NULL;
  BOOLEAN_TO_NPVARIANT(FALSE, *result);

  if (argCount == 2 && NPVARIANT_IS_STRING(args[0]) &&
      NPVARIANT_IS_STRING(args[1])) {
    type.append(NPVARIANT_TO_STRING(args[1]).UTF8Characters,
                NPVARIANT_TO_STRING(args[1]).UTF8Length); 
  } else if (argCount != 1 || !NPVARIANT_IS_STRING(args[0]))
    return false;
  
  base64 = strstr(NPVARIANT_TO_STRING(args[0]).UTF8Characters,
                  "base64,");
  if (!base64)
    return true;
  base64 += 7;
  int base64size = NPVARIANT_TO_STRING(args[0]).UTF8Length - 7;

  int byteLength = Base64DecodeGetRequiredLength(base64size);
  HGLOBAL handle = GlobalAlloc(GMEM_MOVEABLE, byteLength);
  if (!handle)
    return true;
  LPVOID bytes = GlobalLock(handle);
  if (!bytes) {
    GlobalFree(handle);
    return true;
  }
  Base64Decode(base64, base64size, (BYTE*)bytes, &byteLength);
  CreateStreamOnHGlobal(handle, FALSE, &stream_);
  image_ = new Image(stream_);
  if (!image_) {
    stream_->Release();
    GlobalUnlock(handle);
    GlobalFree(handle);
    return true;
  }
  stream_->Release();
  GlobalUnlock(handle);
  GlobalFree(handle);

  WCHAR current_path[MAX_PATH];
  GetCurrentDirectoryW(MAX_PATH, current_path);
  WCHAR file_name[MAX_PATH];
  wsprintf(file_name, L"%s\\ExtensionWallPaper.bmp", current_path);
  CLSID bmp_clsid;
  GetEncoderClsid(L"image/bmp", &bmp_clsid);
  if (image_->Save(file_name, &bmp_clsid) != Ok) {
    delete image_;
    return true;
  }

  delete image_;

  HRESULT hr;
  IActiveDesktop* active_desktop;

  hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,
                        IID_IActiveDesktop, (void**)&active_desktop);
  if (FAILED(hr)) {
    return false;
  }

  hr = active_desktop->SetWallpaper(file_name, 0);
  if (FAILED(hr)) {
    active_desktop->Release();
    return true;
  }

  WALLPAPEROPT opt;
  opt.dwSize = sizeof(WALLPAPEROPT);
  if (type == "Center") {
    opt.dwStyle = WPSTYLE_CENTER;
    active_desktop->SetWallpaperOptions(&opt, 0);
  } else if (type == "Stretch") {
    opt.dwStyle = WPSTYLE_STRETCH;
    active_desktop->SetWallpaperOptions(&opt, 0);
  } else if (type == "Tile") {
    opt.dwStyle = WPSTYLE_TILE;
    active_desktop->SetWallpaperOptions(&opt, 0);
  }

  hr = active_desktop->ApplyChanges(AD_APPLY_ALL);
  if (FAILED(hr)) {
    active_desktop->Release();
    return true;
  }

  active_desktop->Release();
  BOOLEAN_TO_NPVARIANT(TRUE, *result);
  return true;
}

bool BackgroundScriptObject::RestoreWallPaper(const NPVariant *args,
                                              uint32_t argCount,
                                              NPVariant *result) {
  BOOLEAN_TO_NPVARIANT(FALSE, *result);
  HRESULT hr;
  IActiveDesktop *active_desktop;

  hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,
                        IID_IActiveDesktop, (void**)&active_desktop);
  if (FAILED(hr))
    return false;

  hr = active_desktop->SetWallpaper(ori_wallpaper_, 0);
  if (FAILED(hr)) {
    active_desktop->Release();
    return true;
  }

  hr = active_desktop->SetWallpaperOptions(&ori_opt_, 0);
  if (FAILED(hr)) {
    active_desktop->Release();
    return true;
  }

  hr = active_desktop->ApplyChanges(AD_APPLY_ALL);
  if (FAILED(hr)) {
    active_desktop->Release();
    return true;
  }

  active_desktop->Release();

  BOOLEAN_TO_NPVARIANT(TRUE, *result);
  return true;
}

bool BackgroundScriptObject::SaveImage(const NPVariant* args, 
                                       uint32_t argCount, 
                                       NPVariant* result) {
  if (argCount != 1 || !NPVARIANT_IS_STRING(args[0]))
    return false;

  const char* image_url = NPVARIANT_TO_STRING(args[0]).UTF8Characters;

  // request image resource, if success, browser will call NewStream,
  // WriteReady, Write method of background plugin sequentially.
  NPN_GetURL(get_plugin()->get_npp(), image_url, NULL);

  return true;
}
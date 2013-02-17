#include "video_alone_plugin.h"

#include <TlHelp32.h>

#include "script_object_factory.h"
#include "video_alone_script_object.h"

WNDPROC VideoAlonePlugin::old_proc_ = NULL;

VideoAlonePlugin::VideoAlonePlugin(void) {
  Gdiplus::GdiplusStartup(&token_, &start_input_, NULL);
}

VideoAlonePlugin::~VideoAlonePlugin(void) {
  Gdiplus::GdiplusShutdown(token_);
}

NPError VideoAlonePlugin::Init(NPP instance, uint16_t mode, int16_t argc,
                               char *argn[], char *argv[], 
                               NPSavedData *saved) {
  script_object_ = NULL;
  old_proc_ = NULL;
  instance->pdata = this;
  return PluginBase::Init(instance, mode, argc, argn, argv, saved);
}

NPError VideoAlonePlugin::UnInit(NPSavedData **save) {
  PluginBase::UnInit(save);
  script_object_ = NULL;
  old_proc_ = NULL;
  return NPERR_NO_ERROR;
}

NPError VideoAlonePlugin::GetValue(NPPVariable variable, void *value) {
  switch(variable) {
    case NPPVpluginScriptableNPObject:
      if (script_object_ == NULL) {
        script_object_ = ScriptObjectFactory::CreateObject(
            get_npp(), VideoAloneScriptObject::Allocate);
        NPN_RetainObject(script_object_);
      }
      if (script_object_ != NULL) {
        *(NPObject**)value = script_object_;
      }
      else
        return NPERR_OUT_OF_MEMORY_ERROR;
      break;
    default:
      return NPERR_GENERIC_ERROR;
  }

  return NPERR_NO_ERROR;
}

NPError VideoAlonePlugin::SetWindow(NPWindow* window) {
  PluginBase::SetWindow(window);

  if (get_hwnd() == NULL && old_proc_ != NULL) {
    SubclassWindow(get_hwnd(), old_proc_);
    old_proc_ = NULL;
    KillTimer(get_hwnd(), 1);
  }

  if (get_hwnd() != NULL && old_proc_ == NULL) {
    old_proc_ = SubclassWindow(get_hwnd(), WndProc);
    SetWindowLong(get_hwnd(), GWLP_USERDATA, (LONG)this);
    SetTimer(get_hwnd(), 1, 10, NULL);
  }

  return NPERR_NO_ERROR;
}

LRESULT VideoAlonePlugin::WndProc(HWND hWnd, UINT Msg, 
                                  WPARAM wParam, LPARAM lParam) {
  switch(Msg) {
    case WM_TIMER: {
      if (wParam == 1) {
        static bool fullscreen_flag = false;
        // find flash fullscreen window.
        HWND flash_fullscreen_window = FindWindowEx(
            NULL, NULL, _T("ShockwaveFlashFullScreen"), NULL);
        if (flash_fullscreen_window) {
          // verify whether the window is belonged to the current chrome.
          DWORD proccess_id;
          GetWindowThreadProcessId(flash_fullscreen_window, &proccess_id);
          TCHAR chrome_exe_path[MAX_PATH];
          GetModuleFileName(GetModuleHandle(NULL), 
                            chrome_exe_path, MAX_PATH);
          HANDLE hmodule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 
                                                    proccess_id);
          MODULEENTRY32 mod = { sizeof(MODULEENTRY32) };
          if (Module32First(hmodule, &mod)) {
            if (_tcsicmp(mod.szExePath, chrome_exe_path) == 0) {
              if (!fullscreen_flag) {
                fullscreen_flag = true;
                SendFlashFullscreenStatus(fullscreen_flag);
                SetForegroundWindow(flash_fullscreen_window);
              }
            } else {
              if (fullscreen_flag) {
                fullscreen_flag = false;
                SendFlashFullscreenStatus(fullscreen_flag);
              }
            }
          }
          CloseHandle(hmodule);
        } else {
          if (fullscreen_flag) {
            fullscreen_flag = false;
            SendFlashFullscreenStatus(fullscreen_flag);
          }
        }
      }
      break;
    }
    case WM_CHROMECLOSE: {
      // the video stand-alone window will close, notify front-end to dispose.
      VideoAlonePlugin* plugin = (VideoAlonePlugin*)GetWindowLong(
          hWnd, GWLP_USERDATA);
      VideoAloneScriptObject::WindowMap* window_list = 
          VideoAloneScriptObject::get_video_alone_list();

      NPObject* window;
      NPN_GetValue(plugin->get_npp(), NPNVWindowNPObject, &window);

      VideoAloneScriptObject::WindowMap::iterator item = 
          window_list->find(HWND(wParam));
      if (item != window_list->end()) {
        NPVariant params[3];
        INT32_TO_NPVARIANT(item->second.parent_window_id, params[0]);
        INT32_TO_NPVARIANT(item->second.window_id, params[1]);
        INT32_TO_NPVARIANT(item->second.tab_id, params[2]);

        NPVariant varObject;
        NPVariant vRet;
        NPN_GetProperty(plugin->get_npp(), window,
                        NPN_GetStringIdentifier("videoAlone"), &varObject);
        NPN_Invoke(plugin->get_npp(), varObject.value.objectValue,
                   NPN_GetStringIdentifier("restore"), params, 3, &vRet);
        NPN_ReleaseVariantValue(&vRet);
        NPN_ReleaseVariantValue(&varObject);
        window_list->erase(item);
      }
    }
    return 1;
  }
  return CallWindowProc(old_proc_, hWnd, Msg, wParam, lParam);
}

void VideoAlonePlugin::SendFlashFullscreenStatus(bool fullscreen_flag) {
  VideoAloneScriptObject::WindowMap* window_list = 
      VideoAloneScriptObject::get_video_alone_list();
  VideoAloneScriptObject::WindowMap::iterator item;
  for (item = window_list->begin(); item != window_list->end(); item++) {
    // send message to all video stand-alone window 
    SendMessage(item->first, WM_FLASH_FULLSCREEN_STATUS, 0, fullscreen_flag);
  }
}
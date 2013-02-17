#include "background_plugin.h"

#include <GdiPlus.h>

#include "background_script_object.h"
#include "log.h"
#include "script_object_factory.h"
#include "video_alone_script_object.h"

extern Log g_log;
extern const TCHAR* kChromeClassName;
extern DWORD g_chrome_main_thread;

NPError BackgroundPlugin::Init(NPP instance, uint16_t mode, int16_t argc,
                               char *argn[], char *argv[], 
                               NPSavedData *saved) {
  instance->pdata = this;
  script_object_= NULL;
  return PluginBase::Init(instance, mode, argc, argn, argv, saved);
}

NPError BackgroundPlugin::UnInit(NPSavedData **save) {
  PluginBase::UnInit(save);
  script_object_= NULL;
  return NPERR_NO_ERROR;
}

NPError BackgroundPlugin::GetValue(NPPVariable variable, void *value) {
  switch(variable) {
    case NPPVpluginScriptableNPObject:
      if (!script_object_) {
        script_object_ = ScriptObjectFactory::CreateObject(
            get_npp(), BackgroundScriptObject::Allocate);
        NPN_RetainObject(script_object_);
        g_log.WriteLog("GetValue", "GetValue");
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

NPError BackgroundPlugin::NewStream(NPMIMEType type, NPStream* stream, 
                                    NPBool seekable, uint16_t* stype) {
  // we dispose it if the resource is image, otherwise return error.
  if (memcmp(type, "image", 5) == 0) {
    ImageData* image_data = new ImageData;
    stream->pdata = image_data;
    if (!image_data)
      return NPERR_OUT_OF_MEMORY_ERROR;
    image_data->mimetype = type;
    image_data->image_url = stream->url;
    image_data->size = stream->end;
    if (!image_data->size)
      return NPERR_GENERIC_ERROR;
    // initialize buffer for this resource.
    image_data->data = new byte[image_data->size];
    if (!image_data->data)
      return NPERR_OUT_OF_MEMORY_ERROR;
    return NPERR_NO_ERROR;
  } else
    return NPERR_GENERIC_ERROR;
}

NPError BackgroundPlugin::DestroyStream(NPStream* stream, NPReason reason) {
  if (stream->pdata) {
    ImageData* image_data = (ImageData*)stream->pdata;
    // release buffer
    delete[] image_data->data;
    delete image_data;
    stream->pdata = NULL;
  }
  return NPERR_NO_ERROR;
}

int32_t BackgroundPlugin::WriteReady(NPStream* stream) {
  return MAX_BUFFER_LEN;
}

int32_t BackgroundPlugin::Write(NPStream* stream, int32_t offset, 
                                int32_t len, void* buffer) {
  ImageData* image_data = (ImageData*)stream->pdata;
  if (image_data) {
    memcpy(image_data->data + offset, buffer, len);
    if (offset + len == image_data->size) {
      // when data is received complete, save it to disk
      SaveImageFile(image_data);
    }
  }
  return len;
}

void BackgroundPlugin::SaveImageFile(const ImageData* image_data) {
  OPENFILENAMEA Ofn = {0};
  Ofn.lStructSize = sizeof(OPENFILENAMEA);

  char initial_path[MAX_PATH] = "";
  char file_name[MAX_PATH] = "Images";
  // get user picture path.
  PIDLIST_ABSOLUTE pIdList;
  SHGetSpecialFolderLocation(NULL, CSIDL_MYPICTURES, &pIdList);
  if (SHGetPathFromIDListA(pIdList, initial_path)) {
    Ofn.lpstrInitialDir = initial_path;
  } else
    Ofn.lpstrInitialDir = NULL;

  // get image file type.
  size_t position = image_data->mimetype.rfind('/');
  std::string file_type;
  if (position != std::string::npos) {
    file_type = image_data->mimetype.substr(position + 1);
  }

  // spell file filter string.
  char file_filter[MAX_PATH];
  strcpy(file_filter, file_type.c_str());
  _strupr(file_filter);
  _snprintf(file_filter, MAX_PATH, "%s Image$*.%s$All Files$*.*$$",
            file_filter, file_type.c_str());
  for (int i = 0; i < MAX_PATH; i++) {
    if (file_filter[i] == '$')
      file_filter[i] = 0;
  }

  // get default file name.
  size_t postfix = image_data->image_url.rfind('.');
  position = image_data->image_url.rfind('/');
  if (postfix != std::string::npos && postfix > position) {
    std::string default_name = image_data->image_url.substr(
        position + 1, postfix - position - 1);
    strcpy(file_name, default_name.c_str());
  }

  Ofn.hwndOwner = get_hwnd();
  Ofn.lpstrFilter = file_filter;
  Ofn.lpstrDefExt = file_type.c_str();
  Ofn.lpstrFile = file_name;
  Ofn.nMaxFile = sizeof(file_name);
  Ofn.lpstrFileTitle = NULL;
  Ofn.nMaxFileTitle = 0;
  Ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
  Ofn.lpstrTitle = NULL;

  // get foreground chrome window.
  VideoAloneScriptObject::WindowMap* window_list = 
      VideoAloneScriptObject::get_video_alone_list();
  HWND chrome_hwnd = FindWindowEx(NULL, NULL, kChromeClassName, NULL);
  while(chrome_hwnd) {
    BOOL visible = IsWindowVisible(chrome_hwnd);
    HWND hwnd = GetParent(chrome_hwnd);
    if (GetWindowThreadProcessId(chrome_hwnd, NULL) == g_chrome_main_thread &&
        hwnd == NULL && window_list->find(chrome_hwnd) == window_list->end()) {
      Ofn.hwndOwner = chrome_hwnd;
      break;
    }
    chrome_hwnd = FindWindowEx(NULL, chrome_hwnd, kChromeClassName, NULL);
  }

  if (GetSaveFileNameA(&Ofn)) {
    // save to disk
    FILE* out = fopen(file_name, "wb");
    if (out) {
      fwrite(image_data->data, image_data->size, 1, out);
      fclose(out);
    }
  }
}
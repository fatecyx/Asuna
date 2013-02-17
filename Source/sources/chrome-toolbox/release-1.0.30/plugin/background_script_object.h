#ifndef BACKGROUND_SCRIPT_OBJECT_H_
#define BACKGROUND_SCRIPT_OBJECT_H_

#include <comdef.h>
#include <GdiPlus.h>
#include <WinInet.h>
#include <shlobj.h>

#include "script_object_base.h"

using namespace Gdiplus;

// Script object for saving image and setting wallpaper.
class BackgroundScriptObject : public ScriptObjectBase {
private:
  BackgroundScriptObject(void) : image_(NULL), stream_(NULL) {}
  virtual ~BackgroundScriptObject(void) {}

public:
  // Chrome call this function to init object.
  static NPObject* Allocate(NPP npp, NPClass *aClass); 

  void Deallocate();
  void Invalidate() {}
  bool Construct(const NPVariant *args, uint32_t argCount,
                 NPVariant *result) { return true; }

  void InitHandler();

  // Some interface for front-end.

  // Notify NPAPI plugin that front-end will open a popup window to 
  // set wallpaper.
  // Save original wallpaper option for restoration.
  bool SetWallPaper(const NPVariant *args, uint32_t argCount,
                    NPVariant *result);

  // Apply selected type and picture as wallpaper.
  bool ApplyWallPaper(const NPVariant *args, uint32_t argCount,
                      NPVariant *result);

  // Restore saved original wallpaper.
  bool RestoreWallPaper(const NPVariant *args, uint32_t argCount,
                        NPVariant *result);

  // Request image data.
  bool SaveImage(const NPVariant* args, uint32_t argCount, NPVariant* result);

private:
  // Image object for generate picture file.
  Image* image_;

  // Stream object for load image binary data front-end delivered.
  IStream* stream_;

  // For save original wallpaper picture path.
  TCHAR ori_wallpaper_[MAX_PATH];

  // Original wallpaper option.
  WALLPAPEROPT ori_opt_;

};

#endif
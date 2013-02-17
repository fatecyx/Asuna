#ifndef BACKGROUND_PLUGIN_H_
#define BACKGROUND_PLUGIN_H_

#include "plugin_base.h"
#include "script_object_base.h"

// Plugin class for setting wallpaper and saving image to disk feature.
// This class doesn't have public constructor and destructor, and it can only be
// created by CreateObject function, which is used by plugin factory.
class BackgroundPlugin : public PluginBase {
private:
  BackgroundPlugin(void) {}
  virtual ~BackgroundPlugin(void) {}

public:
  NPError Init(NPP instance, uint16_t mode, int16_t argc, char* argn[],
               char* argv[], NPSavedData* saved);
  NPError UnInit(NPSavedData** save);
  NPError GetValue(NPPVariable variable, void *value);

  // Call this function when a new stream arrive to plugin.
  NPError NewStream(NPMIMEType type, NPStream* stream, NPBool seekable, 
                    uint16_t* stype);
  // Notify plugin to destroy stream.
  NPError DestroyStream(NPStream* stream, NPReason reason);

  // Request available buffer len.
  int32_t WriteReady(NPStream* stream);

  // Write to buffer.
  int32_t Write(NPStream* stream, int32_t offset, int32_t len, void* buffer);

  // Create set background plugin interface.
  static PluginBase* CreateObject() { return new BackgroundPlugin; }

private:
  struct ImageData{
    byte* data;
    std::string mimetype;
    std::string image_url;
    unsigned int size;
  };

  // Save image to disk.
  void SaveImageFile(const ImageData* image_data);

private:
  // Script object interface.
  ScriptObjectBase* script_object_;

};

#endif

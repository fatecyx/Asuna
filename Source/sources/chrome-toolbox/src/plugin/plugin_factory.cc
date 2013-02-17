#include "plugin_factory.h"

#include "background_plugin.h"
#include "browser_mute_plugin.h"
#include "convenience_plugin.h"
#include "video_alone_plugin.h"

PluginFactory::PluginTypeMap PluginFactory::plugin_type_map_;

void PluginFactory::Init() {
  PluginTypeItem item;
  item.mime_type = "application/x-npconvenience";
  item.constructor = &ConveniencePlugin::CreateObject;
  plugin_type_map_.insert(PluginTypeMap::value_type(item.mime_type, item));
  item.mime_type = "application/x-npwallpaper";
  item.constructor = &BackgroundPlugin::CreateObject;
  plugin_type_map_.insert(PluginTypeMap::value_type(item.mime_type, item));
  item.mime_type = "application/x-npvideoalone";
  item.constructor = &VideoAlonePlugin::CreateObject;
  plugin_type_map_.insert(PluginTypeMap::value_type(item.mime_type, item));
  item.mime_type = "application/x-browsermute";
  item.constructor = &BrowserMutePlugin::CreateObject;
  plugin_type_map_.insert(PluginTypeMap::value_type(item.mime_type, item));
}

PluginBase* PluginFactory::NewPlugin(NPMIMEType pluginType) {
  PluginBase* plugin = NULL;
  PluginTypeMap::iterator iter = plugin_type_map_.find(pluginType);
  if (iter != plugin_type_map_.end())
    plugin = iter->second.constructor();

  return plugin;
}

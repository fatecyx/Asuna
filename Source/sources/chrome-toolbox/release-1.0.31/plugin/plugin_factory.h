#ifndef PLUGIN_FACTORY_H_
#define PLUGIN_FACTORY_H_

#include <map>
#include <string>

#include "plugin_base.h"

typedef PluginBase* (*ConstructorPtr)();

// It is used for creating new plugin according MIMEType.
// This class can not be instanced
class PluginFactory {
private:
  PluginFactory(void);
  ~PluginFactory(void);

public:
  static void Init();

  // create plugin according MIMEType
  static PluginBase* NewPlugin(NPMIMEType pluginType);

public:
  struct PluginTypeItem {
    std::string mime_type;
    ConstructorPtr constructor;
  };

  typedef std::map<std::string, PluginTypeItem> PluginTypeMap;

private:
  static PluginTypeMap plugin_type_map_;
};

#endif
#include "DatabasePlugin.hpp"
#include "gui/plugins/database/utils.hpp"

#include <qqml.h>

void DatabasePlugin::registerTypes(const char *uri)
{
  // @uri org.example.io
  qmlRegisterType<gui::utils>(uri, 1, 0, "utils");
}

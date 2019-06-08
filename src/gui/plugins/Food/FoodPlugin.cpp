#include "Food.hpp"
#include "FoodPlugin.hpp"

#include <qqml.h>

void FoodPlugin::registerTypes(const char *uri)
{
  // @uri org.example.io
  qmlRegisterType<gui::Food>(uri, 1, 0, "Food");
}

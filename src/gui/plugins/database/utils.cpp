#include "database/utils.hpp"
#include "food/Food.hpp"
#include "food/Macronutrients.hpp"
#include "gui/plugins/database/utils.hpp"

#include <QtQuick/QQuickView>
#include <QtQml/QQmlContext>

#include <vector>

gui::utils::utils(QObject *parent) : QObject(parent) {}

gui::utils::~utils() = default;

void gui::utils::loadDatabase()
{
  const auto &food_data = database::utils::retrieve_all<food::Food>();
  QList<QObject *> object_data;
  for (const food::Food &f : food_data) {
    auto new_food = new gui::Food();
    new_food->setName(f.name().c_str());

    food::Macronutrients macros = f.macronutrients();
    new_food->setFat(macros.fat());
    new_food->setCarbohydrate(macros.carbohydrate());
    new_food->setFiber(macros.fiber());
    new_food->setProtein(macros.protein());
    object_data.append(new_food);
  }

  QQuickView view;
  view.setResizeMode(QQuickView::SizeRootObjectToView);
  QQmlContext *ctxt = view.rootContext();
  ctxt->setContextProperty("foodData", QVariant::fromValue(object_data));
}

// void utils::write()
//{
// if (source_.isEmpty()) { return; }
// QFile file(source_.toLocalFile());
// if (file.open(QIODevice::WriteOnly)) {
// QTextStream stream(&file);
// stream << text_;
//}
//}

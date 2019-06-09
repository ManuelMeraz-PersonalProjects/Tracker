#include "database/utils.hpp"
#include "food/Food.hpp"
#include "food/Macronutrients.hpp"
#include "gui/plugins/database/utils.hpp"
#include "gui/plugins/food/Food.hpp"

#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>

#include <vector>

gui::utils::utils(QObject *parent) : QObject(parent)
{
  loadDatabase(parent);
}

gui::utils::~utils() = default;

void gui::utils::loadDatabase(QObject *parent)
{
  auto &food_data = database::utils::retrieve_all<food::Food>();
  QList<QObject *> new_food_data;

  new_food_data.reserve(food_data.size());
  for (food::Food &food : food_data) {
    auto new_food = new gui::Food(food, parent);
    new_food_data.append(new_food);
  }

  m_food_data = new_food_data;
  emit foodDataChanged(new_food_data);
}

QList<QObject *> gui::utils::foodData() const
{
  return m_food_data;
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

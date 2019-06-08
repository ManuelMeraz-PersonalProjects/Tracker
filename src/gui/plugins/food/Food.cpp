#include "database/utils.hpp"
#include "food/Food.hpp"
#include "food/Macronutrients.hpp"
#include "gui/plugins/food/Food.hpp"

gui::Food::Food(QObject *parent) : QObject(parent)
{
  m_food = &database::utils::make<food::Food>();
}

gui::Food::~Food()
{
  database::utils::drop_table<food::Food>();
}

// void Food::read()
//{
// if (source_.isEmpty()) { return; }
// QFile file(source_.toLocalFile());
// if (!file.exists()) {
// qWarning() << "Does not exits: " << source_.toLocalFile();
// return;
//}
// if (file.open(QIODevice::ReadOnly)) {
// QTextStream stream(&file);
// text_ = stream.readAll();
// emit textChanged(text_);
//}
//}

// void Food::write()
//{
// if (source_.isEmpty()) { return; }
// QFile file(source_.toLocalFile());
// if (file.open(QIODevice::WriteOnly)) {
// QTextStream stream(&file);
// stream << text_;
//}
//}
auto gui::Food::key() -> int const
{
  return m_food->id();
}

auto gui::Food::name() -> QString const
{
  return m_food->name().c_str();
}

auto gui::Food::fat() -> double const
{
  return m_food->macronutrients().fat();
}

auto gui::Food::carbohydrate() -> double const
{
  return m_food->macronutrients().carbohydrate();
}

auto gui::Food::fiber() -> double const
{
  return m_food->macronutrients().fiber();
}

auto gui::Food::protein() -> double const
{
  return m_food->macronutrients().protein();
}

void gui::Food::setName(QString const &name)
{
  m_food->set_name(name.toStdString());
  emit nameChanged(name);
}

void gui::Food::setFat(double fat)
{
  food::Macronutrients macros = m_food->macronutrients();
  macros.set_fat(fat);
  m_food->set_macronutrients(macros);
  emit fatChanged(fat);
}

void gui::Food::setCarbohydrate(double carbohydrate)
{
  food::Macronutrients macros = m_food->macronutrients();
  macros.set_carbohydrate(carbohydrate);
  m_food->set_macronutrients(macros);
  emit carbohydrateChanged(carbohydrate);
}

void gui::Food::setFiber(double fiber)
{
  food::Macronutrients macros = m_food->macronutrients();
  macros.set_fiber(fiber);
  m_food->set_macronutrients(macros);
  emit fiberChanged(fiber);
}

void gui::Food::setProtein(double protein)
{
  food::Macronutrients macros = m_food->macronutrients();
  macros.set_protein(protein);
  m_food->set_macronutrients(macros);
  emit proteinChanged(protein);
}

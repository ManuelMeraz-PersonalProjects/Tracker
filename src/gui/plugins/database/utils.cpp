#include "database/utils.hpp"
#include "gui/plugins/database/utils.hpp"

gui::utils::utils(QObject *parent) : QObject(parent)
{
  m_data["Food"] = loadDatabase<food::Food, gui::Food>(parent);
}

gui::utils::~utils() = default;

// auto gui::utils::getData(QString const &table_name) -> QList<QObject *>
QList<QObject *> gui::utils::getData(QString const &table_name)
{
  return m_data[table_name];
}

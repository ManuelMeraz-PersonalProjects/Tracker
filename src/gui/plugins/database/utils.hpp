#pragma once

#include "database/Storable.hpp"
#include "database/utils.hpp"
#include "food/Food.hpp"
#include "gui/plugins/food/Food.hpp"

#include <QtCore>

namespace gui {
class utils : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(utils)
public:
  utils(QObject *parent = nullptr);
  ~utils() override;

  //Q_INVOKABLE auto getData(QString const &table_name) -> QList<QObject *>;
  Q_INVOKABLE QList<QObject *> getData(QString const &table_name);
private:
  template <typename Storable,
            typename std::enable_if_t<
                std::is_base_of_v<database::Storable, std::decay_t<Storable>>,
                int> = 0>
  auto loadDatabase(QObject *parent) -> QList<QObject *>;

  QHash<QString, QList<QObject *>> m_data;
};
} // namespace gui

// template implementation

template <
    typename Storable,
    typename std::enable_if_t<
        std::is_base_of_v<database::Storable, std::decay_t<Storable>>, int>>
auto gui::utils::loadDatabase(QObject *parent) -> QList<QObject *>
{
  auto &data = database::utils::retrieve_all<Storable>();
  QList<QObject *> new_data;

  new_data.reserve(data.size());
  for (Storable &storable : data) {
    auto new_storable = new gui::Food(storable, parent);
    new_data.append(new_storable);
  }
  return new_data;
}

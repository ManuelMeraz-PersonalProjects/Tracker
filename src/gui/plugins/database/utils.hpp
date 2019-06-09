#pragma once

#include "database/utils.hpp"
#include "gui/plugins/food/Food.hpp"

#include <QtCore>

namespace gui {
class utils : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(utils)
  Q_PROPERTY(QList<QObject *> foodData READ foodData NOTIFY foodDataChanged)
public:
  utils(QObject *parent = nullptr);
  ~utils() override;

  QList<QObject *> foodData() const;
signals:
  void foodDataChanged(QList<QObject *> const &arg);
private:
  void loadDatabase(QObject *parent);

  QList<QObject *> m_food_data;
};
} // namespace gui

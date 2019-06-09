#pragma once

#include "database/utils.hpp"
#include "gui/plugins/food/Food.hpp"

#include <QtCore>

namespace gui {
class utils : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(utils)
public:
  utils(QObject *parent = nullptr);
  ~utils() override;

  Q_INVOKABLE void loadDatabase();
};
} // namespace gui

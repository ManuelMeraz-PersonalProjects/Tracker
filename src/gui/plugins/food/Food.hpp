#pragma once

#include "food/Food.hpp"

#include <QtCore>

namespace gui {
class Food : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(Food)
  Q_PROPERTY(int key READ key NOTIFY keyChanged)
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(double fat READ fat WRITE setFat NOTIFY fatChanged)
  Q_PROPERTY(double carbohydrate READ carbohydrate WRITE setCarbohydrate NOTIFY
                 carbohydrateChanged)
  Q_PROPERTY(double fiber READ fiber WRITE setFiber NOTIFY fiberChanged)
  Q_PROPERTY(double protein READ protein WRITE setProtein NOTIFY proteinChanged)
public:
  Food(QObject *parent = nullptr);
  Food(food::Food &food, QObject *parent = nullptr);
  ~Food() override;

  // Q_INVOKABLE void read();
  // Q_INVOKABLE void write();
  auto key() -> int const;
  auto name() -> QString const;
  auto fat() -> double const;
  auto carbohydrate() -> double const;
  auto fiber() -> double const;
  auto protein() -> double const;
public slots:
  void setName(QString const &name);
  void setFat(double fat);
  void setCarbohydrate(double carbohydrate);
  void setFiber(double fiber);
  void setProtein(double protein);
signals:
  void keyChanged(int arg);
  void nameChanged(QString const &arg);
  void fatChanged(double arg);
  void carbohydrateChanged(double arg);
  void fiberChanged(double arg);
  void proteinChanged(double arg);

private:
  food::Food *m_food;
};
} // namespace gui

#pragma once

#include <QtCore>

namespace gui {
class Food : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(Food)
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(double fat READ fat WRITE setFat NOTIFY fatChanged)
public:
  Food(QObject *parent = nullptr);
  ~Food() override;

  // Q_INVOKABLE void read();
  // Q_INVOKABLE void write();
  auto name() const -> QString;
  auto fat() const -> double;
public slots:
  void setName(QString const &name);
  void setFat(double fat);
signals:
  void nameChanged(QString arg);
  void fatChanged(double arg);

private:
  QString m_name;
  double m_fat;
};
} // namespace gui

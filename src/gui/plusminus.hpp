#pragma once

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class PlusMinus : public QWidget {

  Q_OBJECT

public:
  PlusMinus(QWidget *parent = 0);

private slots:
  void OnPlus();
  void OnMinus();

private:
  QLabel *lbl;
};

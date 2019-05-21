#include "plusminus.hpp"

#include <QGridLayout>
#include <QTextStream>

PlusMinus::PlusMinus(QWidget *parent) : QWidget(parent)
{

  QPushButton *plsBtn = new QPushButton("+", this);
  QPushButton *minBtn = new QPushButton("-", this);
  lbl = new QLabel("0", this);

  QGridLayout *grid = new QGridLayout(this);
  grid->addWidget(plsBtn, 0, 0);
  grid->addWidget(minBtn, 0, 1);
  grid->addWidget(lbl, 1, 1);

  setLayout(grid);

  connect(plsBtn, &QPushButton::clicked, this, &PlusMinus::OnPlus);
  connect(minBtn, &QPushButton::clicked, this, &PlusMinus::OnMinus);
}

void PlusMinus::OnPlus()
{

  QTextStream out(stdout);
  int val = lbl->text().toInt();
  val++;
  lbl->setText(QString::number(val));
}

void PlusMinus::OnMinus()
{

  QTextStream out(stdout);

  int val = lbl->text().toInt();
  val--;
  lbl->setText(QString::number(val));
}

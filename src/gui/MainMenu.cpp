#include "MainMenu.hpp"

#include <QPushButton>
#include <QVBoxLayout>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{

  QVBoxLayout *vbox = new QVBoxLayout(this);
  vbox->setSpacing(1);

  QPushButton *food_database = new QPushButton("Food Database", this);
  food_database->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QPushButton *quit = new QPushButton("Quit", this);
  quit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  vbox->addWidget(food_database);
  vbox->addWidget(quit);

  setLayout(vbox);
}

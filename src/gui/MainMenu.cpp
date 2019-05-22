#include "MainMenu.hpp"

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QAction>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{

  auto *vbox = new QVBoxLayout(this);
  vbox->setSpacing(1);

  QPushButton *food_db_button = new QPushButton("Food Database", this);
  food_db_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  auto *quit_button = new QPushButton("Quit", this);
  quit_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  auto *quit = new QAction("Quit", this);
  quit->setShortcut(tr("CTRL+Q"));
  quit_button->addAction(quit);
  connect(quit_button, &QPushButton::clicked, qApp, &QApplication::quit);
  connect(quit, &QAction::triggered, qApp, &QApplication::quit);

  vbox->addWidget(food_db_button);
  vbox->addWidget(quit_button);

  setLayout(vbox);
}

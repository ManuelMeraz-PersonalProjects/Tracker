#include "gui/MainMenu.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{

  QApplication app(argc, argv);

  MainMenu window;

  window.resize(300, 190);
  window.setWindowTitle("Application");
  window.show();

  return app.exec();
}

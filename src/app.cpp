#include "gui/plusminus.hpp"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{

  QApplication app(argc, argv);

  PlusMinus window;
  QWidget widget;

  window.resize(300, 190);
  window.setWindowTitle("Plus minus");
  window.show();

  return app.exec();
}

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QFontDatabase>
#include <QTextStream>
#include <QStringList>

namespace gui {
int app(int argc, char *argv[])
{
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  int font_id = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
  if(font_id) {
    app.setFont(QFont("Ubuntu", 11, QFont::Normal, false));
  }

  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:///qml/MainWindow.qml"));
  if (engine.rootObjects().isEmpty()) { return -1; }

  return app.exec();
}
} // namespace gui

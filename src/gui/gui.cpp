#include <QApplication>
#include <QFontDatabase>
#include <QStringList>
#include <QTextStream>
#include <QtQml/QQmlApplicationEngine>

namespace gui {
int app(int argc, char *argv[])
{
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

  int font_id = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
  if (font_id) { app.setFont(QFont("Ubuntu", 11, QFont::Normal, false)); }

  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:///qml/main.qml"));
  if (engine.rootObjects().isEmpty()) { return -1; }

  return app.exec();
}
} // namespace gui

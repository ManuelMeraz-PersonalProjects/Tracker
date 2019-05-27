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

  QTextStream out(stdout);
  int font_id = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
  QStringList loaded_fonts = QFontDatabase::applicationFontFamilies(font_id);

  app.setFont(QFont("Ubuntu", 11, QFont::Normal, false));
  for(auto &font : loaded_fonts) {
    out << font <<  endl;
  }

  QQmlApplicationEngine engine;
  engine.load(QUrl("/home/manny/projects/tracker/src/gui/sidepanel.qml"));
  if (engine.rootObjects().isEmpty()) { return -1; }

  return app.exec();
}
} // namespace gui

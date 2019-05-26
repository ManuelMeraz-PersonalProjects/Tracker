#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

namespace gui {
int app(int argc, char *argv[])
{
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl("src/gui/sidepanel.qml"));
  if (engine.rootObjects().isEmpty()) { return -1; }

  return app.exec();
}
} // namespace gui

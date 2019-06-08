#include "Food.hpp"

gui::Food::Food(QObject *parent) : QObject(parent) {}

gui::Food::~Food() = default;

// void Food::read()
//{
// if (source_.isEmpty()) { return; }
// QFile file(source_.toLocalFile());
// if (!file.exists()) {
// qWarning() << "Does not exits: " << source_.toLocalFile();
// return;
//}
// if (file.open(QIODevice::ReadOnly)) {
// QTextStream stream(&file);
// text_ = stream.readAll();
// emit textChanged(text_);
//}
//}

// void Food::write()
//{
// if (source_.isEmpty()) { return; }
// QFile file(source_.toLocalFile());
// if (file.open(QIODevice::WriteOnly)) {
// QTextStream stream(&file);
// stream << text_;
//}
//}

QString gui::Food::name() const
{
  return m_name;
}

double gui::Food::fat() const
{
  return m_fat;
}

void gui::Food::setName(QString const &name)
{
  m_name = name;
  emit nameChanged(name);
}

void gui::Food::setFat(double fat)
{
  m_fat = fat;
  emit fatChanged(fat);
}

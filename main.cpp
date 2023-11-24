#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QDebug>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

//  QFile file(":/dark/stylesheet.qss");
//  file.open(QFile::ReadOnly | QFile::Text);
//  QTextStream stream(&file);
//  a.setStyleSheet(stream.readAll());

  MainWindow w;
  w.show();
  return a.exec();
}

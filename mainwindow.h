#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "numpad.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void showNumpad(bool hasFocus);

private:
  Ui::MainWindow *ui;

  Numpad *m_numpad;
};
#endif // MAINWINDOW_H

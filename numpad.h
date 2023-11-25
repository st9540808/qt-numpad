#ifndef NUMPAD_H
#define NUMPAD_H

#include <QDialog>
#include <QLineEdit>
#include <QMainWindow>
#include <QVariant>
#include <QWidget>

namespace Ui {
class Numpad;
}

class Numpad : public QDialog {
  Q_OBJECT

public:
  explicit Numpad(QWidget *parent = 0, QMainWindow *mainwindow = 0);
  ~Numpad();

  void activate(QWidget *widget, QVariant initValue);
  void setEchoMode(QLineEdit::EchoMode);

private slots:
  void showNumpad(QWidget *widget);
  void buttonClicked();
  void enterClicked();
  void escapeClicked();
  void clearClicked();
  void backspaceClicked();
  void periodClicked();
  void pmClicked();

private:
  Ui::Numpad *ui;
  QObjectList keyList;
  const QValidator *validator;
  QMainWindow *mainwindow;
  QWidget *focusWidget;

  bool bFirst;
  float min_, max_;
  void initKeys();
  void popData();
  void checkValue();
  void checkFirst();
  QPalette orgPalette;

signals:
  void dataSet(QVariant *);
};

#endif // NUMPAD_H

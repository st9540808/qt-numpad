#ifndef NUMPAD_H
#define NUMPAD_H

#include <QWidget>

namespace Ui {
class Numpad;
}

class Numpad : public QWidget {
  Q_OBJECT

public:
  explicit Numpad(QWidget *parent = nullptr);
  ~Numpad();

public slots:
  void showNumpad(void);

private:
  Ui::Numpad *ui;
};

#endif // NUMPAD_H

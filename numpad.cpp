#include "numpad.h"
#include "ui_numpad.h"
#include <QDebug>

Numpad::Numpad(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Numpad)
{
  ui->setupUi(this);
}

Numpad::~Numpad() { delete ui; }

void Numpad::showNumpad(void)
{
  qDebug() << "Numpad::showNumpad triggered" << this->isVisible();
  this->show();
}

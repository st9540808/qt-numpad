#include "numpad.h"
#include "ui_numpad.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QEvent>
#include <QGuiApplication>
#include <QLineEdit>
#include <QTextEdit>
#include <QValidator>
#include <QWidget>

Numpad::Numpad(QWidget *parent, QMainWindow *mainwindow)
    : QDialog(parent)
    , ui(new Ui::Numpad)
    , mainwindow(mainwindow)
    , validator(nullptr)
    , focusWidget(nullptr)
{
  ui->setupUi(this);

  orgPalette = ui->edValue->palette(); // save the original palette

  this->initKeys();
}

Numpad::~Numpad() { delete ui; }

void Numpad::showNumpad(QWidget *widget)
{
  qDebug() << "Numpad::showNumpad triggered" << this->isVisible();

  QLineEdit *lineEdit = qobject_cast<QLineEdit *>(widget);

  this->focusWidget = widget;
  this->mainwindow->setEnabled(false);
  this->activate(widget, lineEdit->text());
}

void Numpad::activate(QWidget *widget, QVariant initValue)
{
  QLineEdit *lineEdit = qobject_cast<QLineEdit *>(widget);
  this->validator = lineEdit->validator();
  ui->edValue->clear();
  ui->edValue->insert(initValue.toString());

  if (const QIntValidator *v = qobject_cast<const QIntValidator *>(validator)) {
    ui->lbl_max_value->setText(QString::number(v->top()));
    ui->lbl_min_value->setText(QString::number(v->bottom()));
  } else if (const QDoubleValidator *v
             = qobject_cast<const QDoubleValidator *>(validator)) {
    ui->lbl_max_value->setText(QString::number(v->top()));
    ui->lbl_min_value->setText(QString::number(v->bottom()));
  } else {
    ui->lbl_max_value->setText("---");
    ui->lbl_min_value->setText("---");
  }

  bFirst = true;

  show();
  checkValue();
}

void Numpad::setEchoMode(QLineEdit::EchoMode echoMode)
{
  ui->edValue->setEchoMode(echoMode);
}

void Numpad::initKeys()
{
  QVariantMap options;
  options.insert("color-off", QColor(Qt::white));

  for (QAbstractButton *abs_button : ui->buttonGroup->buttons()) {
    QPushButton *button = qobject_cast<QPushButton *>(abs_button);
    if (button != 0) {
      if ((button->property("btnMode").toInt() == 0)
          || (button->property("btnMode").toInt() == 1)) {
        connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
      } else if (button->property("btnMode").toInt() == 2) {
        if (button->property("btnNormal") == "ok") {
          // button->setIcon(awesome->icon(fa::fa_solid, fa::fa_check,
          // options));
          connect(button, SIGNAL(clicked()), this, SLOT(enterClicked()));
        } else if (button->property("btnNormal") == "escape") {
          connect(button, SIGNAL(clicked()), this, SLOT(escapeClicked()));
        } else if (button->property("btnNormal") == "clear") {
          // button->setIcon(awesome->icon(fa::fa_solid, fa::fa_remove,
          // options));
          connect(button, SIGNAL(clicked()), this, SLOT(clearClicked()));
        } else if (button->property("btnNormal") == "backspace") {
          // button->setIcon(
          //    awesome->icon(fa::fa_solid, fa::fa_backspace, options));
          connect(button, SIGNAL(clicked()), this, SLOT(backspaceClicked()));
        } else if (button->property("btnNormal") == "period") {
          connect(button, SIGNAL(clicked()), this, SLOT(periodClicked()));
        } else if (button->property("btnNormal") == "pm") {
          connect(button, SIGNAL(clicked()), this, SLOT(pmClicked()));
        }
      }
    }
  }
}

void Numpad::enterClicked()
{
  QString tmp1, tmp2;
  tmp1 = ui->edValue->text().right(1);
  tmp2 = ui->btn_period->text();
  if (tmp1 == tmp2) {
    ui->edValue->insert(
        ui->edValue->text().left(ui->edValue->text().length() - 1));
  }
  popData();
}

void Numpad::escapeClicked()
{
  close();
  this->mainwindow->setEnabled(true);
}

void Numpad::clearClicked()
{
  ui->edValue->clear();
  checkValue();
}

void Numpad::periodClicked()
{
  checkFirst();
  if (!ui->edValue->text().contains(ui->btn_period->text())) {
    if (ui->edValue->text().isEmpty())
      ui->edValue->insert("0");
    ui->edValue->insert(ui->btn_period->text());
    checkValue();
  }
}

void Numpad::pmClicked()
{
  checkFirst();
  QString text = ui->edValue->text();
  if (text.left(1) == "-") {
    text = text.right(text.length() - 1);
  } else {
    text = "-" + text;
  }
  ui->edValue->setText(text);
  checkValue();
}

void Numpad::backspaceClicked()
{
  QString text = ui->edValue->text();
  text.chop(1);
  ui->edValue->setText(text);
  checkValue();
}

void Numpad::popData()
{
  QVariant v(ui->edValue->text());
  QLineEdit *lineEdit = qobject_cast<QLineEdit *>(this->focusWidget);
  lineEdit->setText(v.toString());
  close();
  this->mainwindow->setEnabled(true);
}

void Numpad::buttonClicked()
{
  checkFirst();
  QPushButton *tmp;
  QString text;
  tmp = qobject_cast<QPushButton *>(sender());
  if (ui->edValue->text() == "0") {
    ui->edValue->clear();
  }
  ui->edValue->insert(tmp->text());
  checkValue();
}

void Numpad::checkValue()
{
  if (validator) {
    int pos = 0;
    QString str(ui->edValue->text());
    if (validator->validate(str, pos) == QValidator::Acceptable) {
      ui->edValue->setPalette(orgPalette);

      ui->btn_enter->setEnabled(true);
      ui->edValue->setStyleSheet("");
    } else {
      QPalette newPalette = ui->edValue->palette();
      newPalette.setColor(QPalette::Text, QColor(255, 0, 0));
      ui->edValue->setPalette(newPalette);

      ui->edValue->setStyleSheet("QLineEdit { color: red }");
      ui->btn_enter->setEnabled(false);
    }
  }
}

void Numpad::checkFirst()
{
  // if (bFirst) {
  //   ui->edValue->clear();
  //   bFirst = false;
  // }
}

#include "mylineedit.h"
#include <QDebug>

MyLineEdit::MyLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
}

MyLineEdit::~MyLineEdit() {}

void MyLineEdit::focusInEvent(QFocusEvent *e)
{
  QLineEdit::focusInEvent(e);
  emit(focussed(this));
}

void MyLineEdit::focusOutEvent(QFocusEvent *e)
{
  QLineEdit::focusOutEvent(e);
  /// Only emit when focus in
  // emit(focussed(false));
}

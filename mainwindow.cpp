#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDoubleValidator>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_numpad = new Numpad(parent, this);
  m_numpad->hide();

  ui->lineEdit->setValidator(new QDoubleValidator(0., 5., 3, ui->lineEdit));
  connect(ui->lineEdit, SIGNAL(focussed(QWidget *)), m_numpad,
          SLOT(showNumpad(QWidget *)));

  ui->lineEdit_2->setValidator(new QIntValidator(0., 100, ui->lineEdit_2));
  connect(ui->lineEdit_2, SIGNAL(focussed(QWidget *)), m_numpad,
          SLOT(showNumpad(QWidget *)));
}

MainWindow::~MainWindow() { delete ui; }

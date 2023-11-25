#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDoubleValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_numpad = new Numpad(parent, this);
  m_numpad->hide();

  ui->lineEdit->setValidator(new QDoubleValidator(0., 5., 5));

  connect(ui->lineEdit, SIGNAL(focussed(QWidget *)), m_numpad,
          SLOT(showNumpad(QWidget *)));
}

MainWindow::~MainWindow() { delete ui; }

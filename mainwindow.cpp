#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_numpad = new Numpad();
  m_numpad->setParent(this);
  m_numpad->hide();

  connect(ui->lineEdit, SIGNAL(focussed(bool)), m_numpad, SLOT(showNumpad()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::showNumpad(bool hasFocus) {}

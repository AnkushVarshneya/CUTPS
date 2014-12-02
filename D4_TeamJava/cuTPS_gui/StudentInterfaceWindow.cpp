#include "StudentInterfaceWindow.h"
#include "ui_StudentInterfaceWindow.h"

StudentInterfaceWindow::StudentInterfaceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentInterfaceWindow)
{
    ui->setupUi(this);
}

StudentInterfaceWindow::~StudentInterfaceWindow()
{
    delete ui;
}

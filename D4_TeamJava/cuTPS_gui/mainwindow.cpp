#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ContentManagerInterfaceWindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton* MainWindow::getContentManagerButton()
{
    return ui->contentManagerInterfaceButton;
}

QPushButton* MainWindow::getStudentButton()
{
    return ui->studentInterfaceButton;
}

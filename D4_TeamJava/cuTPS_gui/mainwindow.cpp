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

void MainWindow::on_studentInterfaceButton_clicked()
{
    studentInterface.show();
    this->hide();
}

void MainWindow::on_contentManagerInterfaceButton_clicked()
{
    contentManagerUI.show();
    this->hide();

}

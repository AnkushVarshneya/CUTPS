#include "ContentManagerInterfaceWindow.h"
#include "ui_ContentManagerInterfaceWindow.h"

ContentManagerInterfaceWindow::ContentManagerInterfaceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentManagerInterfaceWindow)
{
    ui->setupUi(this);
}

ContentManagerInterfaceWindow::~ContentManagerInterfaceWindow()
{
    delete ui;
}

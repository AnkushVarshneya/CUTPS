#include "ManageCoursesInterfaceWindow.h"
#include "ui_ManageCoursesInterfaceWindow.h"

ManageCoursesInterfaceWindow::ManageCoursesInterfaceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageCoursesInterfaceWindow)
{
    ui->setupUi(this);
}

ManageCoursesInterfaceWindow::~ManageCoursesInterfaceWindow()
{
    delete ui;
}

#include "LinkStudentFormWindow.h"
#include "ui_LinkStudentFormWindow.h"

LinkStudentFormWindow::LinkStudentFormWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkStudentFormWindow)
{
    ui->setupUi(this);
}

LinkStudentFormWindow::~LinkStudentFormWindow()
{
    delete ui;
}

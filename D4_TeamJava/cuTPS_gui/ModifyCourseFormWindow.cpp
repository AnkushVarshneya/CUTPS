#include "ModifyCourseFormWindow.h"
#include "ui_ModifyCourseFormWindow.h"

ModifyCourseFormWindow::ModifyCourseFormWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyCourseFormWindow)
{
    ui->setupUi(this);
}

ModifyCourseFormWindow::~ModifyCourseFormWindow()
{
    delete ui;
}

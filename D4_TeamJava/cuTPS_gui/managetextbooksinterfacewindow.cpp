#include "managetextbooksinterfacewindow.h"
#include "ui_managetextbooksinterfacewindow.h"

ManageTextbooksInterfaceWindow::ManageTextbooksInterfaceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageTextbooksInterfaceWindow)
{
    ui->setupUi(this);
}

ManageTextbooksInterfaceWindow::~ManageTextbooksInterfaceWindow()
{
    delete ui;
}

void ManageTextbooksInterfaceWindow::on_createTextbookOption_clicked()
{
    createTextbookForm.show();
    this->hide();
}

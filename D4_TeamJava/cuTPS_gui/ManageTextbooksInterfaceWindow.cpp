#include "ManageTextbooksInterfaceWindow.h"
#include "ui_ManageTextbooksInterfaceWindow.h"

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

void ManageTextbooksInterfaceWindow::on_deleteTextbookOption_clicked()
{

}

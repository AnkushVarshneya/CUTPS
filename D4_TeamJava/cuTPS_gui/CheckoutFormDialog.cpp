#include "CheckoutFormDialog.h"
#include "ui_CheckoutFormDialog.h"

CheckoutFormDialog::CheckoutFormDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckoutFormDialog)
{
    ui->setupUi(this);
}

CheckoutFormDialog::~CheckoutFormDialog()
{
    delete ui;
}

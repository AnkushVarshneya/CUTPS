#include "CheckoutDialogWidget.h"
#include "ui_CheckoutDialogWidget.h"

CheckoutDialogWidget::CheckoutDialogWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckoutDialogWidget)
{
    ui->setupUi(this);
}

CheckoutDialogWidget::~CheckoutDialogWidget()
{
    delete ui;
}

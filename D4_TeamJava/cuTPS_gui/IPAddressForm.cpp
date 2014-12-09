#include "IPAddressForm.h"
#include "ui_IPAddressForm.h"

IPAddressForm::IPAddressForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IPAddressForm)
{
    ui->setupUi(this);
}

IPAddressForm::~IPAddressForm()
{
    delete ui;
}
QLineEdit*      IPAddressForm::getIPAddressTextBox()    { return ui->ipAddressTextBox; }
QPushButton*    IPAddressForm::getOkButton()            { return ui->okButton; }

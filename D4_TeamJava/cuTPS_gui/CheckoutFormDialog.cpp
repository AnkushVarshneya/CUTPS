#include "CheckoutFormDialog.h"
#include "ui_CheckoutFormDialog.h"

CheckoutFormDialog::CheckoutFormDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckoutFormDialog)
{
    ui->setupUi(this);
}

CheckoutFormDialog*  CheckoutFormDialog::instance = 0;
//singleton instance getter
CheckoutFormDialog* CheckoutFormDialog::getInstance()
{
    if (instance == 0){
        instance = new CheckoutFormDialog();
        }
   return instance;
}

CheckoutFormDialog::~CheckoutFormDialog()
{
    delete ui;
}

QPushButton*    CheckoutFormDialog::getBackOption()                 { return ui->backOption; }
QPushButton*    CheckoutFormDialog::getConfirmOption()              { return ui->confirmOption; }

QLineEdit*      CheckoutFormDialog::getNameLineEdit()               { return ui->nameLineEdit; }
QLineEdit*      CheckoutFormDialog::getUnitNumberLineEdit()         { return ui->unitNumberLineEdit; }
QLineEdit*      CheckoutFormDialog::getStreetNameLineEdit()         { return ui->streetNameLineEdit; }
QLineEdit*      CheckoutFormDialog::getCityLineEdit()               { return ui->cityLineEdit; }
QLineEdit*      CheckoutFormDialog::getPostalCodeLineEdit()         { return ui->postalCodeLineEdit; }
QLineEdit*      CheckoutFormDialog::getProvinceLineEdit()           { return ui->provinceLineEdit; }

QLineEdit*      CheckoutFormDialog::getCreditCardNumberLineEdit()   { return ui->ccNumberLineEdit ;}
QLineEdit*      CheckoutFormDialog::getCardholderNameLineEdit()     { return ui->cardholderNameLineEdit; }
QLineEdit*      CheckoutFormDialog::getCvvLineEdit()                { return ui->cvvLineEdit; }
QComboBox*      CheckoutFormDialog::getCardTypeEdit()               { return ui->cardTypeComboBox; }
QLineEdit*      CheckoutFormDialog::getExpMonthLineEdit()           { return ui->expMonthLineEdit ; }
QLineEdit*      CheckoutFormDialog::getExpYearLineEdit()                { return ui->expYearLineEdit; }





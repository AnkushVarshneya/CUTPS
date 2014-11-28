#include "PaymentInformation.h"

//Constructor
PaymentInformation::PaymentInformation() {
   billAddress = BillingAddress();
   creditCardInfo = CreditCardInformation();
}

//Destructor
PaymentInformation::~PaymentInformation() {}

//Getters
BillingAddress PaymentInformation::getBillInfo() {return billAddress;}
CreditCardInformation PaymentInformation::getCreditCardInfo() {return creditCardInfo;}

//Setters
void PaymentInformation::setBillInfo(const BillingAddress &b){billAddress = b;}
void PaymentInformation::setCreditCardInfo(const CreditCardInformation &c){creditCardInfo = c;}


//JSON read and write functions
void PaymentInformation::read(const QJsonObject &json){
    billAddress.read( json["billInfo"].toObject() );
    creditCardInfo.read( json["ccInfo"].toObject() );
}

void PaymentInformation::write(QJsonObject &json) const {
    QJsonObject billing;
    QJsonObject cc;
    billAddress.write(billing);
    creditCardInfo.write(cc);
    json["billInfo"] = billing;
    json["ccInfo"] = cc;
}

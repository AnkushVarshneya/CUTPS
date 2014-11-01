#include "PaymentInformation.h"

PaymentInformation::PaymentInformation() {
   BillingAddress *billAddress = new BillingAddress();
   CreditCardInformation *creditCardInfo = new CreditCardInformation();
}

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

BillingAddress PaymentInformation::getBillInfo() {
    return billAddress;
}

CreditCardInformation PaymentInformation::getCreditCardInfo() {
    return creditCardInfo;
}

PaymentInformation::~PaymentInformation() {
//TODO
}


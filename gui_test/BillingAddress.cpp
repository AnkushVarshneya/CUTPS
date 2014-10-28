#include "BillingAddress.h"


BillingAddress::BillingAddress(QObject *parent) :
    CUtpsDataObject()
{
    name = "test person";
    city = "ottawa";
}

QString BillingAddress::getName() { return this->name ; }
int BillingAddress::getHouseNumber() { return this->houseNumber ; }
QString BillingAddress::getStreetName() { return this->streetName ; }
QString BillingAddress::getCity() { return this->city ; }
QString BillingAddress::getProvince() { return this->province ; }
QString BillingAddress::getPostalCode() { return this->postalCode ; }

void BillingAddress::setAddress(QString,int,QString,QString,QString,QString) {

}

void BillingAddress::setAddress(const BillingAddress&) {

}

void BillingAddress::insertToDataStream(QDataStream& dataStream) {
    dataStream << this->name << this->city;
}

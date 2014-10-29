#include "BillingAddress.h"


BillingAddress::BillingAddress(QObject *parent) :
    CUtpsDataObject()
{
    name = "test person";
    city = "ottawa";
    streetName = "colonel by dr.";
    houseNumber = 1125;
    province = "ontario";
    postalCode = "K1S 5B6";
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

void BillingAddress::read(const QJsonObject &json)
{
    name = json["name"].toString();
    houseNumber = json["house number"].toDouble();
    streetName = json["street name"].toString();
    city = json["city"].toString();
    province = json["province"].toString();
    postalCode = json["postal code"].toString();
}

void BillingAddress::write(QJsonObject &json) const
{
    json["name"] = name;
    json["house number"] = houseNumber;
    json["street name"] = streetName;
    json["city"] = city;
    json["province"] = province;
    json["postal code"] = postalCode;
}

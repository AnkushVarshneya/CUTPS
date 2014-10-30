#include "BillingAddress.h"



BillingAddress::BillingAddress(QString n,int hnum,QString sn,QString c,QString prov,QString pos)
{
    setAddress(n, hnum, sn, c, prov, pos);
}

QString BillingAddress::getName() const { return name ; }
int BillingAddress::getHouseNumber() const { return houseNumber ; }
QString BillingAddress::getStreetName() const { return streetName ; }
QString BillingAddress::getCity() const { return city ; }
QString BillingAddress::getProvince() const { return province ; }
QString BillingAddress::getPostalCode() const { return postalCode ; }

void BillingAddress::setAddress(QString n,int hnum,QString sn,QString c,QString prov,QString pos) {
    name = n;
    houseNumber = hnum;
    streetName = sn;
    city = c;
    province = prov;
    postalCode = pos;
}

void BillingAddress::setAddress(const BillingAddress& b) {
    name = b.getName();
    houseNumber = b.getHouseNumber();
    streetName = b.getStreetName();
    city = b.getCity();
    province = b.getProvince();
    postalCode = b.getPostalCode();

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



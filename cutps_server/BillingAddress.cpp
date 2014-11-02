/* Billing Address class source
 *
 *
 * Traceability: EO-06
 *
 *
 */

#include "BillingAddress.h"


//Default constructor
BillingAddress::BillingAddress(QString n,int hnum,QString sn,QString c,QString prov,QString pos)
    : name(n), houseNumber(hnum), streetName(sn), city(c), province(prov), postalCode(pos){
}

//Getters
QString BillingAddress::getName() const { return name ; }
int BillingAddress::getHouseNumber() const { return houseNumber ; }
QString BillingAddress::getStreetName() const { return streetName ; }
QString BillingAddress::getCity() const { return city ; }
QString BillingAddress::getProvince() const { return province ; }
QString BillingAddress::getPostalCode() const { return postalCode ; }

//Takes in primitive datatypes to set the individual attributes of the BillingAddress
void BillingAddress::setAddress(QString n,int hnum,QString sn,QString c,QString prov,QString pos) {
    name = n;
    houseNumber = hnum;
    streetName = sn;
    city = c;
    province = prov;
    postalCode = pos;
}

//Takes in a BillingAddress address copies over the passed in argument's attributes
void BillingAddress::setAddress(const BillingAddress& b) {
    name = b.getName();
    houseNumber = b.getHouseNumber();
    streetName = b.getStreetName();
    city = b.getCity();
    province = b.getProvince();
    postalCode = b.getPostalCode();

}

//Takes in a QJsonObject address and sets each of this object's attributes from
//The fields of the json object
void BillingAddress::read(const QJsonObject &json)
{
    name = json["name"].toString();
    houseNumber = json["house number"].toDouble();
    streetName = json["street name"].toString();
    city = json["city"].toString();
    province = json["province"].toString();
    postalCode = json["postal code"].toString();
}

//Takes in a QJsonObject address as an argument and creates fields
//That have the string value of each of this object's attribute values
void BillingAddress::write(QJsonObject &json) const
{
    json["name"] = name;
    json["house number"] = houseNumber;
    json["street name"] = streetName;
    json["city"] = city;
    json["province"] = province;
    json["postal code"] = postalCode;
}


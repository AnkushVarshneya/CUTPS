/*Billing Address header class
 *Date last modified: 10/24/2014
 *By: Rob
 *
 *Billing address is for use as part of the PaymentInformation class
 *that has this component
 *
 */
#ifndef BILLINGADDRESS_H
#define BILLINGADDRESS_H

#include <string>
#include "CUtpsDataObject.h"
#include <QString>
#include <QDataStream>


class BillingAddress : public CUtpsDataObject
{
public:
    BillingAddress();
    QString getName();
    int getHouseNumber();
    QString getStreetName();
    QString getCity();
    QString getProvince();
    QString getPostalCode();
    void setAddress(QString,int,QString,QString,QString,QString);
    void setAddress(const BillingAddress&);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    QString name;
    int houseNumber;
    QString streetName;
    QString city;
    QString province;
    QString postalCode;
    static const quint32 streamHeader;
    static const quint16 classVersion;
};



#endif // BILLINGADDRESS_H

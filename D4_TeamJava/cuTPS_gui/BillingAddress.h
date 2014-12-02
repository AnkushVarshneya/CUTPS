/*Billing Address class header
 *
 *
 *Billing address is for use as part of the PaymentInformation class
 *that has this component
 *A Billing address in this system will contain the following attributes:
 *- Name (to match correctly with the credit card info)
 *- House Number, Street name, city, province, and postal code
 *
 *Traceability: EO-06
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
    BillingAddress(QString = "test person",
                   int = 1125,
                   QString = "colonel by dr.",
                   QString = "ottawa",
                   QString = "ontario",
                   QString = "K1S 5B6");
    QString getName() const;
    int getHouseNumber() const;
    QString getStreetName() const;
    QString getCity() const;
    QString getProvince() const;
    QString getPostalCode() const;
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

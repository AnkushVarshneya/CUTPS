/*CreditCardInformation class header
 *
 *Purpose of class: This class is to contain the attributes for
 *a typical credit card, part of a Student's PaymentInformation
 *
 *Traceability: EO-07
 */


#ifndef CREDITCARDINFORMATION_H
#define CREDITCARDINFORMATION_H

#include <QString>
#include <QDate>
#include "CUtpsDataObject.h"

class CreditCardInformation : public CUtpsDataObject {

public:
    //Constructor
    CreditCardInformation(QString = "1234098712321234", QString = "908", QDate = QDate::fromString("20190120", "yyyyMMdd"), QString = "MasterCard", QString = "John Doe");

    //Destructor
    ~CreditCardInformation();

    //Getters
    QString         getCreditCardNo();
    QString         getCVV();
    QDate           getExpDate();
    QString         getCardType();
    QString         getNameOnCard();

    //Setters
    void            setCreditCardNo(QString);
    void            setCVV(QString);
    void            setExpDate(int,int,int);
    void            setCardType(QString);
    void            setNameOnCard(QString);
    void            read(const QJsonObject &json);
    void            write(QJsonObject &json) const;



private:
    QString         creditCardNo;
    QString         CVV;
    QDate           expDate;
    QString         cardType;
    QString         nameOnCard;
};

//ostream method for testing data purposes
std::ostream& operator<<(std::ostream&, CreditCardInformation&);

#endif // CREDITCARDINFORMATION_H

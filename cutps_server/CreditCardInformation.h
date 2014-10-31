/*CreditCardInformation header class
 *Date last modified 10/24/2014
 *Note: Expiry date might need a separate class for date,
 *but maybe not because of prototype purposes
 *
 */


#ifndef CREDITCARDINFORMATION_H
#define CREDITCARDINFORMATION_H

#include <QString>
#include <QDate>
//#include "Types.h"
#include "CUtpsDataObject.h"

class CreditCardInformation : public CUtpsDataObject {

public:
    //Constructor
    CreditCardInformation(QString = "", QString = "", QDate = *(new QDate()), QString = "", QString = "John Doe");

    //Destructor
    //~CreditCardInformation();

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
//std::ostream& operator<<(std::ostream&, CreditCardInformation&);

#endif // CREDITCARDINFORMATION_H

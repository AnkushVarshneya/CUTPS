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
class CreditCardInformation{

public:
    CreditCardInformation();
    ~CreditCardInformation();
    QString         getCreditCardNo();
    QString         getCVV();
    QDate           getExpDate();
    QString         getCardType();
    QString         getNameOnCard();

    void            setCreditCardNo(QString);
    void            setCVV(QString);
    void            setExpDate(int,int,int);
    void            setCardType(QString);
    void            setNameOnCard(QString);


private:
    QString         creditCardNo;
    QString         CVV;
    QDate           expDate;
    QString         cardType;
    QString         nameOnCard;
};

#endif // CREDITCARDINFORMATION_H

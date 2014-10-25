/*CreditCardInformation header class
 *Date last modified 10/24/2014
 *Note: Expiry date might need a separate class for date,
 *but maybe not because of prototype purposes
 *
 */


#ifndef CREDITCARDINFORMATION_H
#define CREDITCARDINFORMATION_H

#include <QString>
class CreditCardInformation{
public:
    CreditCardInformation();
    ~CreditCardInformation();
    QString getCreditCardNo();
    QString getCVV();
    QString getExpDate();
    QString getCardType();
    QString getNameOnCard();

private:
    QString creditCardNo;
    QString CVV;
    QString expDate;
    QString cardType;
    QString nameOnCard;
};

#endif // CREDITCARDINFORMATION_H

/*CreditCardInformation header class
 *Date last modified 10/24/2014
 *Note: Expiry date might need a separate class for date,
 *but maybe not because of prototype purposes
 *
 */


#ifndef CREDITCARDINFORMATION_H
#define CREDITCARDINFORMATION_H

#include <string>
class CreditCardInformation{
public:
    CreditCardInformation();
    ~CreditCardInformation();
    string getCreditCardNo();
    string getCVV();
    string getExpDate();
    string getCardType();
    string getNameOnCard();

private:
    string creditCardNo;
    string CVV;
    string expDate;
    string cardType;
    string nameOnCard;
};

#endif // CREDITCARDINFORMATION_H

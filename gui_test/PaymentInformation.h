/*PaymentInformation Class Header
 *Date Last modified: 10/24/2014
 *By:Rob
 *
 */
#ifndef PAYMENTINFORMATION_H
#define PAYMENTINFORMATION_H

#include "BillingAddress.h"
#include "CreditCardInformation.h"
class PaymentInformation{

public:
    PaymentInformation();
    ~PaymentInformation();

    BillingAddress getBillInfo();
    CreditCardInformation getCreditCardInfo();
    setBillInfo(const BillingAddress&);
    setCreditCardInfo(const CreditCardInformation&);

private:
    BillingAddress billAddress;
    CreditCardInformation creditCardInfo;
};

#endif // PAYMENTINFORMATION_H

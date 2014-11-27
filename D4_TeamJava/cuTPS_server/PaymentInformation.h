/*PaymentInformation Class Header
 *
 *Purpose: The Payment information for a given student if the student so chooses
 *to save their information through CUTPS for a later shopping session
 *Has a billing address and credit card info
 *
 *Traceability: EO-05
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

    BillingAddress                 getBillInfo();
    CreditCardInformation          getCreditCardInfo();
    void                           setBillInfo(const BillingAddress&);
    void                           setCreditCardInfo(const CreditCardInformation&);
    void                           read(const QJsonObject &json);
    void                           write(QJsonObject &json) const;

private:
    BillingAddress                 billAddress;
    CreditCardInformation          creditCardInfo;
};

#endif // PAYMENTINFORMATION_H

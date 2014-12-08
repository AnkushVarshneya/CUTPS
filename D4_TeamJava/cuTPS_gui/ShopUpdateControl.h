/*Class responsible for using the Client Communicator interface to retrieve persistently stored information
 *Used by the ShoppingControl for this purpose
 *
 *Traceability: SS-01-02 (Part of ShoppingManagement Subsystem)
 *
 */

#ifndef SHOPUPDATECONTROL_H
#define SHOPUPDATECONTROL_H
#include "ClientCommunicatorManagementControl.h"

class ShopUpdateControl
{
public:
    ShopUpdateControl();
    QList<Term*>* retrieveAllTerms();
    QList<Course*>* retrieveContent(Student*, Term*);
    ShoppingCart* retrieveShoppingCart(Student*);
    bool    updateShoppingCart(Student*,PurchasableItem*,qint32);
    bool    checkout(Student*,ShoppingCart*);
    bool    emptyShoppingCart(Student*);
    bool    updatePaymentInformation(Student*, PaymentInformation*);
    PaymentInformation* retrieveStudentPaymentInformation(Student*);

private:
    ClientCommunicatorManagementControl* mc;
};

#endif // SHOPUPDATECONTROL_H

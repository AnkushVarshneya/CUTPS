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
    QList<Term*>* retrieveAllTerms() throw (QString);
    QList<Course*>* retrieveContent(Student*, Term*) throw (QString);
    ShoppingCart* retrieveShoppingCart(Student*) throw (QString);
    bool    updateShoppingCart(Student*,PurchasableItem*,qint32) throw (QString);
    bool    checkOutShoppingCart(Student*) throw (QString);
    bool    emptyShoppingCart(Student*) throw (QString);
    bool    updatePaymentInformation(Student*, PaymentInformation*) throw (QString);
    PaymentInformation* retrieveStudentPaymentInformation(Student*)throw (QString);

private:
    ClientCommunicatorManagementControl* mc;
};

#endif // SHOPUPDATECONTROL_H

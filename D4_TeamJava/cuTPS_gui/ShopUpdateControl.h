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
private:
    ClientCommunicatorManagementControl mc;
};

#endif // SHOPUPDATECONTROL_H

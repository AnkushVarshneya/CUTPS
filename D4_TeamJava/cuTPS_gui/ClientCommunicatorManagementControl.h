/* Combines Classes of Serializer and ManagementControl in the Client Communicator Subsystem
 *Traceabilty: SS-05 (Part of Client Communicator Subsystem)
 */

#include "ClientCommunicatorRequestManager.h"
#include "ClientCommunicatorSerializer.h"
#include <QList>
#include "Term.h"
#include "Student.h"

#ifndef CLIENTCOMMUNICATORMANAGEMENTCONTROL_H
#define CLIENTCOMMUNICATORMANAGEMENTCONTROL_H

class ClientCommunicatorManagementControl
{
public:
    ClientCommunicatorManagementControl();
    QList<Term*>* retrieveAllTerms();
    QList<Course*>* retrieveContent(Student*, Term*);
    ShoppingCart*   retrieveShoppingCart(Student*);
    bool            updateShoppingCart(Student*, PurchasableItem*, qint32);
    QList<Textbook*>* retrieveAllContent();

private:
    ClientCommunicatorRequestManager requestManager;
    ClientCommunicatorSerializer    serializer;
};

#endif // CLIENTCOMMUNICATORMANAGEMENTCONTROL_H

/*
 *Traceabilty: SS-05 (Part of Client Communicator Subsystem)
 */

#include "ClientCommunicatorRequestManager.h"
#include "ClientCommunicatorSerializer.h"
#include <QList>
#include "Term.h"

#ifndef CLIENTCOMMUNICATORMANAGEMENTCONTROL_H
#define CLIENTCOMMUNICATORMANAGEMENTCONTROL_H

class ClientCommunicatorManagementControl
{
public:
    ClientCommunicatorManagementControl();
    QList<Term*>* retrieveAllTerms();

private:
    ClientCommunicatorRequestManager requestManager;
    ClientCommunicatorSerializer    serializer;
};

#endif // CLIENTCOMMUNICATORMANAGEMENTCONTROL_H

/* The Listener Control responsible for listening to client requests
 * Delegating functionality of deserializing request to a command to the Serializer class
 * And delegating functionality of using the RequestManager class to communicate with the database
 *
 * Traceability: SS-06 (Part of Server Subsystem) */

#include "ServerSerializer.h"
#include "ServerStorageControl.h"


#ifndef SERVERLISTENERCONTROL_H
#define SERVERLISTENERCONTROL_H

class ServerListenerControl
{
public:
    ServerListenerControl();
    QJsonObject processCommand(QJsonObject);
    static ServerListenerControl* getInstance();
private:
    ServerSerializer serializer;
    ServerStorageControl storage;
    static ServerListenerControl* instance;

};

#endif // SERVERLISTENERCONTROL_H

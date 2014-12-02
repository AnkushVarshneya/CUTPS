/*Serializer Class responsible for serializing and de-serializing to handle client requests
 *The Serializer determines the command the client has initiated, and is used by the Listener Control
 *to determine which function needs to be called to handle the request
 *
 *Traceability: SS-06 (Part of Server Subsystem)
 *
 */


#ifndef SERVERSERIALIZER_H
#define SERVERSERIALIZER_H

class ServerSerializer
{
public:
    ServerSerializer();
};

#endif // SERVERSERIALIZER_H

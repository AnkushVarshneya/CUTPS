/* The Listener Control responsible for listening to client requests
 * Delegating functionality of deserializing request to a command to the Serializer class
 * And delegating functionality of using the RequestManager class to communicate with the database
 *
 * Traceability: SS-06 (Part of Server Subsystem) */

#include "ServerSerializer.h"
#include "ServerStorageControl.h"
#include <QTcpServer>
#include <QTcpSocket>

#ifndef SERVERLISTENERCONTROL_H
#define SERVERLISTENERCONTROL_H

class ServerListenerControl : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerListenerControl(QObject *parent = 0);
    void startServer();
    void sendCommand(QJsonObject &json);
    QJsonObject processCommand(QJsonObject);
    static ServerListenerControl* getInstance();


private:
    void retrieveAllTerms(QJsonObject);
    void retrieveContent(QJsonObject);
    void retrieveShoppingCart(QJsonObject);
    void updateShoppingCart(QJsonObject);

    ServerSerializer serializer;
    ServerStorageControl storage;
    static ServerListenerControl* instance;
    QTcpSocket *tcpConnection;
    qint64 bytes;

signals:

public slots:
    void incomingConnection();
    void readBytes();
    void disconnected();
};

#endif // SERVERLISTENERCONTROL_H

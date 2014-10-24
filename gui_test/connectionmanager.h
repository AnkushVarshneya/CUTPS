#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include "BillingAddress.h"

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionManager(QObject *parent = 0);
    void connectToHost(QHostAddress hostAddress, int port);
    void insertToStream(BillingAddress *billingAddress);
    //void insertToStream(cutpsDataObject *object);
private:
    QTcpSocket *tcpConnection;
    QDataStream dataStream;
    void checkDataStream();


signals:

public slots:

private slots:
    void readyRead();

};

#endif // CONNECTIONMANAGER_H

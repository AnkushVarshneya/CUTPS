#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QTextStream>
#include "BillingAddress.h"
#include "CUtpsDataObject.h"

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionManager(QObject *parent = 0);
    void connectToHost(QHostAddress hostAddress, int port);
    void testSend(BillingAddress *testadr);

private:
    QTcpSocket *tcpConnection;
    QDataStream dataStream;
    qint64 bytes;

signals:

public slots:

private slots:
    void readyRead();

};

#endif // CONNECTIONMANAGER_H

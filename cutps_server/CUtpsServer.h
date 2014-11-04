#ifndef CUTPSSERVER_H
#define CUTPSSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "Student.h"
#include "ShoppingCart.h"
#include "CreditCardInformation.h"
#include "BillingAddress.h"
#include "APIControl.h"

class CutpsServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CutpsServer(QObject *parent = 0);
    void startServer();

private:
    QTcpSocket *tcpConnection;
    qint64 bytes;

signals:

public slots:
    void incomingConnection();
    //void readyRead();
    void readBytes();
    void disconnected(); //recieves signal from tcpConnection
};

#endif // CUTPSSERVER_H

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionManager(QObject *parent = 0);
    void connectToHost(QHostAddress hostAddress, int port);

private:
    QTcpSocket *tcpConnection;

signals:

public slots:

private slots:
    void readyRead();

};

#endif // CONNECTIONMANAGER_H

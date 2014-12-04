/*
 *Traceability: SS-05 (Part of Client Communicator Subsystem)
 */
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QTextStream>
#include <QJsonDocument>

#ifndef CLIENTCOMMUNICATORREQUESTMANAGER_H
#define CLIENTCOMMUNICATORREQUESTMANAGER_H

class ClientCommunicatorRequestManager : public QObject
{
    Q_OBJECT
public:
    explicit ClientCommunicatorRequestManager(QObject *parent = 0);
    void connectToHost(QHostAddress hostAddress, int port);
    void send(QJsonObject&);
    QJsonDocument getResult();
    QTcpSocket* getTcp();
    qint64 getBytes();
    void setBytes(qint64 bytes);

private:
    QTcpSocket *tcpConnection;
    QDataStream dataStream;
    qint64 bytes;
    QJsonDocument result;

signals:

public slots:

private slots:
    void readyRead();
};

#endif // CLIENTCOMMUNICATORREQUESTMANAGER_H

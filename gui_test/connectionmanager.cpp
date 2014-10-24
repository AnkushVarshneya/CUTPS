#include "connectionmanager.h"

ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent),
    tcpConnection(new QTcpSocket(this))
{

}

void ConnectionManager::connectToHost(QHostAddress host, int port) {
    this->tcpConnection->connectToHost(host, port);
    qDebug() << this->tcpConnection->state();
    qDebug() << this->tcpConnection->errorString();

}

void ConnectionManager::readyRead() {

}

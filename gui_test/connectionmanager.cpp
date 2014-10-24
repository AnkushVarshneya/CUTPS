#include "connectionmanager.h"
#include "BillingAddress.h"

ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent),
    tcpConnection(new QTcpSocket(this))
{
    this->dataStream.setDevice(tcpConnection); //sets the i/o device of the data stream
}

void ConnectionManager::connectToHost(QHostAddress host, int port) {
    this->tcpConnection->connectToHost(host, port);
    qDebug() << this->tcpConnection->state();
    qDebug() << this->tcpConnection->errorString();

}

void ConnectionManager::readyRead() {

}

void ConnectionManager::insertToStream(BillingAddress *address) {
    address->insertToDataStream(dataStream);
}

void ConnectionManager::checkDataStream() {
    qDebug() << this->dataStream.status();
}


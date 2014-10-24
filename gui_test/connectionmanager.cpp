#include "connectionmanager.h"
#include "BillingAddress.h"

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

void ConnectionManager::insertToStream(BillingAddress *address) {
    address->insertToDataStream(dataStream);
}

void ConnectionManager::checkDataStream() {
    qDebug() << this->dataStream.status();
}

//make base class for all our classes with insertToDataStream??

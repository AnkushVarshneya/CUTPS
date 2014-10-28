#include "connectionmanager.h"
#include "BillingAddress.h"

ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent),
    tcpConnection(new QTcpSocket(this))
{
    this->dataStream.setDevice(tcpConnection); //sets the i/o device of the data stream
    //this->textStream.setDevice(tcpConnection);
    this->textStream.setDevice(tcpConnection);
}

void ConnectionManager::connectToHost(QHostAddress host, int port) {
//    this->tcpConnection->connectToHost(host, port);
//    qDebug() << this->tcpConnection->state();
//    qDebug() << this->tcpConnection->errorString();

    const QString & testaddress = "0.0.0.0";
    QHostAddress address = QHostAddress(testaddress);
    this->tcpConnection->connectToHost(address, 1234);
//    this->tcpConnection->write(" testing data write to server. \n");
//    this->tcpConnection->write(" testing further data write to server. \n");

    connect(this->tcpConnection, SIGNAL(readyRead()), this, SLOT(readyRead()));

}

void ConnectionManager::readyRead() {
    qDebug() << "ready to read stuff from server \n";
    qDebug() << "bytes avail: " << this->tcpConnection->bytesAvailable();
    qDebug() << "peer info: " << this->tcpConnection->peerName() << this->tcpConnection->peerAddress() << this->tcpConnection->peerPort() << "\n";

}

void ConnectionManager::bytesWritten() {
    qDebug() << "bytes written to textstream";
}

void ConnectionManager::insertToStream(BillingAddress *address) {
    address->insertToDataStream(dataStream);
}

//void ConnectionManager::insertToStream(CUtpsDataObject *object) {
//    object->insertToDataStream(dataStream);
//}



void ConnectionManager::checkDataStream() {
    qDebug() << this->dataStream.status();
}



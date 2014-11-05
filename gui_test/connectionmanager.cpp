#include "connectionmanager.h"
#include "BillingAddress.h"

#include <iostream>
using namespace std;

ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent),
    tcpConnection(new QTcpSocket(this))
{
    this->dataStream.setDevice(tcpConnection); //sets the i/o device of the data stream
}

void ConnectionManager::connectToHost(QHostAddress host, int port) {

    const QString & testaddress = "0.0.0.0";
    QHostAddress address = QHostAddress(testaddress);
    this->tcpConnection->connectToHost(address, 1234);
    connect(this->tcpConnection, SIGNAL(readyRead()), this, SLOT(readyRead()));

}

QJsonDocument ConnectionManager::getResult() { return result ; }
QTcpSocket* ConnectionManager::getTcp() { return this->tcpConnection ; }
qint64 ConnectionManager::getBytes() { return this->bytes ; }

void ConnectionManager::setBytes(qint64 bytes) {this->bytes = bytes ; }

void ConnectionManager::testSend(CUtpsDataObject *data) {
      QJsonObject json;
      data->write(json);
      QJsonDocument jdoc = QJsonDocument(json);
      bytes = this->tcpConnection->write(jdoc.toJson()); //write function returns number of bytes written or -1 if an error occurred.
      if (bytes = -1 ){       qDebug() << this->tcpConnection->errorString() ;      }
      qDebug() << "bytes written: " << bytes << "\n";

}

//Send function to put the passed in argument into a JSON document to be sent over
//On the server. API calls by the client to the server will be sent over to the server this way
void ConnectionManager::send(QJsonObject &json){
    QJsonDocument jdoc = QJsonDocument(json);
    bytes = this->tcpConnection->write(jdoc.toJson()); //write function returns number of bytes written or -1 if an error occurred.
    if (bytes = -1 ){       qDebug() << this->tcpConnection->errorString() ;      }
    qDebug() << "bytes written: " << bytes << "\n";
}


void ConnectionManager::readyRead() {
    qDebug() << "ready to read stuff from server \n";
    qDebug() << "bytes avail: " << this->tcpConnection->bytesAvailable();
    qDebug() << "peer info: " << this->tcpConnection->peerName() << this->tcpConnection->peerAddress() << this->tcpConnection->peerPort() << "\n";

    this->bytes = 0;
    this->bytes = this->tcpConnection->bytesAvailable();
    qDebug() << "in client readbytes slot, bytes avail: " << this->bytes << "\n";  //to read

    char *data = new char[this->bytes];
   bytes = this->tcpConnection->read(data, bytes);
   qDebug() << "bytes read: " << bytes << "\n";
   result = QJsonDocument::fromJson(data);
//   qDebug() << result.toJson();

}




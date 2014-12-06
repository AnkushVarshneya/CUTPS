#include "ClientCommunicatorRequestManager.h"

ClientCommunicatorRequestManager::ClientCommunicatorRequestManager(QObject *parent) :
    QObject(parent),
    tcpConnection(new QTcpSocket(this))
{
    this->dataStream.setDevice(tcpConnection); //sets the i/o device of the data stream

    connectToHost(QHostAddress(), 60000);
}

void ClientCommunicatorRequestManager::connectToHost(QHostAddress host, int port) {

    const QString & testaddress = "0.0.0.0";
    QHostAddress address = QHostAddress(testaddress);
    this->tcpConnection->connectToHost(address, port);
    connect(this->tcpConnection, SIGNAL(readyRead()), this, SLOT(readyRead()));

}

QJsonDocument ClientCommunicatorRequestManager::getResult() { return result ; }
QTcpSocket* ClientCommunicatorRequestManager::getTcp() { return this->tcpConnection ; }
qint64 ClientCommunicatorRequestManager::getBytes() { return this->bytes ; }

void ClientCommunicatorRequestManager::resetResult(){this->result = QJsonDocument();}
void ClientCommunicatorRequestManager::setBytes(qint64 bytes) {this->bytes = bytes ; }

void ClientCommunicatorRequestManager::send(QJsonObject &json){
    QJsonDocument jdoc = QJsonDocument(json);
    bytes = this->tcpConnection->write(jdoc.toJson()); //write function returns number of bytes written or -1 if an error occurred.
    if (bytes = -1 ){       qDebug() << this->tcpConnection->errorString() ;      }
    qDebug() << "bytes written: " << bytes << "\n";
}

void ClientCommunicatorRequestManager::readyRead(){
    qDebug() << "ready to read stuff from server \n";
    qDebug() << "bytes avail: " << this->tcpConnection->bytesAvailable();
    qDebug() << "peer info: " << this->tcpConnection->peerName() << this->tcpConnection->peerAddress() << this->tcpConnection->peerPort() << "\n";


    while (!this->tcpConnection->atEnd()){
        qDebug() << "1";
        this->buffer.append(this->tcpConnection->read(this->tcpConnection->bytesAvailable()));
        qDebug() << "2";
    }
    qDebug() << "in client readbytes slot, bytes avail: " << buffer.length() << "\n";  //to read
    result = QJsonDocument::fromJson(buffer);
    //qDebug() << result.toJson();

}

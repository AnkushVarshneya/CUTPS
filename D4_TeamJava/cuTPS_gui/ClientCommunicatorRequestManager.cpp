#include "ClientCommunicatorRequestManager.h"

//Constructor
ClientCommunicatorRequestManager::ClientCommunicatorRequestManager(QObject *parent) :
    QObject(parent),
    tcpConnection(new QTcpSocket(this))
{
    this->dataStream.setDevice(tcpConnection); //sets the i/o device of the data stream

    connectToHost(QHostAddress(), 60000);
}

//Client connect to host for a given host and port argument
void ClientCommunicatorRequestManager::connectToHost(QHostAddress host, int port) {

    const QString & testaddress = "10.0.2.15";
    QHostAddress address = QHostAddress(testaddress);
    this->tcpConnection->connectToHost(address, port);
    connect(this->tcpConnection, SIGNAL(readyRead()), this, SLOT(readyRead()));

}

//Get the Server message result as a QJsonDocument
QJsonDocument ClientCommunicatorRequestManager::getResult() { return result ; }

//Gets the TCP connection
QTcpSocket* ClientCommunicatorRequestManager::getTcp() { return this->tcpConnection ; }

//Get the number of bytes
qint64 ClientCommunicatorRequestManager::getBytes() { return this->bytes ; }

//Resets the Buffer
void ClientCommunicatorRequestManager::resetBuffer(){buffer = QByteArray();}

//Sets the number of bytes
void ClientCommunicatorRequestManager::setBytes(qint64 bytes) {this->bytes = bytes ; }

//Sends the json message to the server
void ClientCommunicatorRequestManager::send(QJsonObject &json){
    QJsonDocument jdoc = QJsonDocument(json);
    bytes = this->tcpConnection->write(jdoc.toJson()); //write function returns number of bytes written or -1 if an error occurred.
    if (bytes = -1 ){       qDebug() << this->tcpConnection->errorString() ;      }
    qDebug() << "bytes written: " << bytes << "\n";
}

//Reads data from server
void ClientCommunicatorRequestManager::readyRead(){
    qDebug() << "ready to read stuff from server \n";
    qDebug() << "bytes avail: " << this->tcpConnection->bytesAvailable();
    qDebug() << "peer info: " << this->tcpConnection->peerName() << this->tcpConnection->peerAddress() << this->tcpConnection->peerPort() << "\n";

    this->bytes = 0;
    this->bytes = this->tcpConnection->bytesAvailable();
    qDebug() << "in client readbytes slot, bytes avail: " << this->bytes << "\n";  //to read

    //char *data = new char[this->bytes];
    while (!this->tcpConnection->atEnd()){
        buffer.append(this->tcpConnection->readAll());
    }
    //bytes = this->tcpConnection->read(buffer, bytes);
    bytes = buffer.length();
    qDebug() << "bytes read: " << bytes << "\n";
    result = QJsonDocument::fromJson(buffer);
    //qDebug() << result.toJson();


   // while (!this->tcpConnection->atEnd()){
   //     qDebug() << "1";
   //     this->buffer.append(this->tcpConnection->readAll());
   //     qDebug() << "2";
   // }

   // qDebug() << "in client readbytes slot, bytes avail: " << buffer.length() << "\n";  //to read
   // result = QJsonDocument::fromJson(buffer);
   // qDebug() << result.toJson();

}

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

//void ConnectionManager::testSend(BillingAddress *testadr) {
//    QJsonObject json;
//    testadr->write(json);
//    QJsonDocument jdoc = QJsonDocument(json);

//    QByteArray ary;

//    qDebug() << "length of json obj: " << json.length() << "\n";
//    qDebug() << "sizeof json obj: " << sizeof(json) << "\n";
//    qDebug() << json << "\n";

//    qDebug() << "sizeof jdoc obj: " << sizeof(jdoc) << "\n";
//    qDebug() << jdoc << "\n";

//    this->tcpConnection->write(jdoc.toJson());

//}

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

//void ConnectionManager::testSend(Chapter *chap) {
//    QJsonObject json;
//    chap->write(json);
//    QJsonDocument jdoc = QJsonDocument(json);
//    this->tcpConnection->write(jdoc.toJson());
//}

//void ConnectionManager::testSend(Textbook *text) {
//    QJsonObject json;
//    text->write(json);
//    QJsonDocument jdoc = QJsonDocument(json);
//    this->tcpConnection->write(jdoc.toJson());

//}


void ConnectionManager::readyRead() {
    qDebug() << "ready to read stuff from server \n";
    qDebug() << "bytes avail: " << this->tcpConnection->bytesAvailable();
    qDebug() << "peer info: " << this->tcpConnection->peerName() << this->tcpConnection->peerAddress() << this->tcpConnection->peerPort() << "\n";


//     char *data = new char[50];
//     bytes = this->tcpConnection->read(data, bytes);
//     cout << "does this even work";
//     cout << data;
//     cout << "really";

//     this->bytes = 0;
//     this->bytes = this->tcpConnection->bytesAvailable();
//     qDebug() << "in server readbytes slot, bytes avail: " << this->bytes << "\n";  //to read

//     char *data = new char[this->bytes];
//     bytes = this->tcpConnection->read(data, bytes);
//     qDebug() << "bytes read: " << bytes << "\n";
//     qDebug() << data;

}




#include "connectionmanager.h"
#include "BillingAddress.h"

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

void ConnectionManager::testSend(BillingAddress *testadr) {
    QJsonObject json;
    testadr->write(json);
    QJsonDocument jdoc = QJsonDocument(json);

    QByteArray ary;

    qDebug() << "length of json obj: " << json.length() << "\n";
    qDebug() << "sizeof json obj: " << sizeof(json) << "\n";
    qDebug() << json << "\n";

    qDebug() << "sizeof jdoc obj: " << sizeof(jdoc) << "\n";
    qDebug() << jdoc << "\n";

    this->tcpConnection->write(jdoc.toJson());

}

void ConnectionManager::testSend(Chapter *chap) {
    QJsonObject json;
    chap->write(json);
    QJsonDocument jdoc = QJsonDocument(json);
    this->tcpConnection->write(jdoc.toJson());
}

void ConnectionManager::testSend(Textbook *text) {
    QJsonObject json;
    text->write(json);
    QJsonDocument jdoc = QJsonDocument(json);
    this->tcpConnection->write(jdoc.toJson());

}


void ConnectionManager::readyRead() {
    qDebug() << "ready to read stuff from server \n";
    qDebug() << "bytes avail: " << this->tcpConnection->bytesAvailable();
    qDebug() << "peer info: " << this->tcpConnection->peerName() << this->tcpConnection->peerAddress() << this->tcpConnection->peerPort() << "\n";

}




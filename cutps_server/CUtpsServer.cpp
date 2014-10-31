#include "CUtpsServer.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include "BillingAddress.h"
#include "Textbook.h"

#include <iostream>
CutpsServer::CutpsServer(QObject *parent) :
    QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), SLOT(incomingConnection()));

}

void CutpsServer::startServer()
{
    int port = 1234;
    const QString & testaddress = "0.0.0.0";
    //const QString & testaddress = "1.2.3.4";
   QHostAddress address = QHostAddress(testaddress);

   if (!this->listen(address, port))
    {
        qDebug() << "Could not start server.";
        qDebug() << this->errorString();
    }
    else
    {
    qDebug() << "Server address is: " << address;
    qDebug() << "Listening on port: " << port << "...";
    }
}

void CutpsServer::incomingConnection() {
    qDebug() << "a new connection is available";
    tcpConnection = CutpsServer::nextPendingConnection();
    connect(tcpConnection, SIGNAL(readyRead()), this, SLOT(readBytes()));
    connect(tcpConnection, SIGNAL(disconnected()), this, SLOT(disconnected()));

    //    qDebug() << tcpConnection->peerName() << "\n";
    //    qDebug() << tcpConnection->peerAddress() << "\n";
    //    qDebug() << tcpConnection->peerPort() << "\n";

}

void CutpsServer::readBytes() {

    this->bytes = 0;
    this->bytes = this->tcpConnection->bytesAvailable();
    qDebug() << "in server readbytes slot, bytes avail: " << this->bytes << "\n";  //to read

    char *data = new char[this->bytes];
    this->tcpConnection->read(data, bytes);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

    //qDebug() << "\n" << data;
    //qDebug() << jsonDoc;
    qDebug() << jsonDoc.toJson();

    //test parsing textbook
    Textbook *text = new Textbook();
    text->read(jsonDoc.object());
    qDebug() << text->getItemTitle();
    qDebug() << text->getAuthor();
    QList<Chapter> chapList;
    QList<Chapter*>::Iterator i;
    for (i = text->getChapterList().begin(); i < text->getChapterList().end(); ++i) {
        chapList.append(**i);
    }
    QList<Chapter>::Iterator z;
    for (z = chapList.begin(); z < chapList.end(); ++z){
        cout << *z;
    }



    //test parsing json into a billing address object
//    BillingAddress *testAdr = new BillingAddress();
//    testAdr->read( jsonDoc.object() );

//    qDebug() << testAdr << "\n";
//    qDebug() << testAdr->getName() << "\n";
//    qDebug() << testAdr->getStreetName() << "\n";
//    qDebug() << testAdr->getHouseNumber() << "\n";
//    qDebug() << testAdr->getCity() << "\n";
//    qDebug() << testAdr->getProvince() << "\n";
//    qDebug() << testAdr->getPostalCode() << "\n";

}

//void CutpsServer::readyRead() {
//    qDebug() << "initial bytes available: " << this->tcpConnection->bytesAvailable() << "\n";  //to read
//    qDebug() << "can read line: " << this->tcpConnection->canReadLine() << "\n";
//    while(this->tcpConnection->canReadLine()) {
//        qDebug() << "bytes available: " << this->tcpConnection->bytesAvailable() << "\n";  //to read
//        qDebug() << this->tcpConnection->readLine();

//    }
//    this->bytes = this->tcpConnection->bytesAvailable();
//    qDebug() << "bytes avail: " << this->bytes << "\n";  //to read
//    QByteArray data = this->tcpConnection->read(bytes);
//    qDebug() << data.data();
//    //test writing to client process
//    this->tcpConnection->write("asdgadfh \n");
//    this->tcpConnection->write("testcity \n");
//}

void CutpsServer::disconnected(){
    qDebug() << "peer disconected. \n";
}

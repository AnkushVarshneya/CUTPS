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
   bytes = this->tcpConnection->read(data, bytes);
   QString cmd;
   qDebug() << "bytes read: " << bytes << "\n";
   QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
   cmd = jsonDoc.object()["Function:"].toString();
   qDebug() << cmd;
   if(cmd == "studentViewTextbooks()"){
       APIControl *apic = new APIControl();
       QJsonObject result = apic->studentViewTextbooks(jsonDoc.object());
       delete apic;
       QJsonDocument *doc = new QJsonDocument(result);
       qDebug() << doc->toJson();
       this->sendJson(result);
       //TODO: write back to client the list of courses in QJSON object
   }
   else if(cmd == "viewShoppingCart()"){

   }

   qDebug() << jsonDoc.toJson();
} //readbytes

void CutpsServer::sendJson(QJsonObject &json) {
        QJsonDocument jdoc = QJsonDocument(json);
        bytes = this->tcpConnection->write(jdoc.toJson());
}


void CutpsServer::disconnected(){
    qDebug() << "peer disconected. \n";
}

#include "ServerListenerControl.h"

//Constructor connects new connection with incoming connection
ServerListenerControl::ServerListenerControl(QObject *parent):
    QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), SLOT (incomingConnection()));
}

//Part of Singleton DP, default instance to 0
ServerListenerControl* ServerListenerControl::instance = 0;

//Process the Command for the client requested message
QJsonObject ServerListenerControl::processCommand(QJsonObject){

}

//Part of Singleton DP, if the instance is 0, make a new instance of the
//ServerListener control, eitherway return that one instance.
ServerListenerControl* ServerListenerControl::getInstance(){
    if (instance == 0){
        instance = new ServerListenerControl();
    }
    return instance;
}

void ServerListenerControl::incomingConnection(){
    qDebug() << "a new connection is available";
    tcpConnection = ServerListenerControl::nextPendingConnection();
    connect(tcpConnection, SIGNAL(readyRead()), this, SLOT(readBytes()));
    connect(tcpConnection, SIGNAL(disconnected()), this, SLOT(disconnected()));
}


void ServerListenerControl::readBytes() {

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

}

//writes a json object to the tcp socket
void ServerListenerControl::sendCommand(QJsonObject &json) {
        QJsonDocument jdoc = QJsonDocument(json);
        bytes = this->tcpConnection->write(jdoc.toJson());
}

void ServerListenerControl::disconnected(){
    qDebug() << "peer disconected. \n";
}



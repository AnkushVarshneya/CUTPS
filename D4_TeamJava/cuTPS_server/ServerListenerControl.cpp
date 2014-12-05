#include "ServerListenerControl.h"

//Constructor connects new connection with incoming connection
ServerListenerControl::ServerListenerControl(QObject *parent):
    QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), SLOT (incomingConnection()));
}

void    ServerListenerControl::startServer(){
    int port = 1234;
    const QString & testaddress = "0.0.0.0";
    //const QString & testaddress = "1.2.3.4";
    QHostAddress address = QHostAddress(testaddress);
    if (!this->listen(address, port)){
         qDebug() << "Could not start server.";
         qDebug() << this->errorString();
    }
    else{
         qDebug() << "Server address is: " << address;
         qDebug() << "Listening on port: " << port << "...";
    }


}

//Slot function that is invoked when the newConnection() signal is recieved. Gets the next pending connection
//and prepares to read bytes from the socket.
void ServerListenerControl::incomingConnection() {
    qDebug() << "a new connection is available";
    tcpConnection = ServerListenerControl::nextPendingConnection();
    connect(tcpConnection, SIGNAL(readyRead()), this, SLOT(readBytes()));
    connect(tcpConnection, SIGNAL(disconnected()), this, SLOT(disconnected()));
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

   if(cmd == "retrieveAllTerms()"){
       retrieveAllTerms(jsonDoc.object());
   }

   else if (cmd == "retrieveContent()"){
       retrieveContent(jsonDoc.object());
   }
}

//writes a json object to the tcp socket
void ServerListenerControl::sendCommand(QJsonObject &json) {
        QJsonDocument jdoc = QJsonDocument(json);
        bytes = this->tcpConnection->write(jdoc.toJson());
}

void ServerListenerControl::disconnected(){
    qDebug() << "peer disconected. \n";
}

void ServerListenerControl::retrieveAllTerms(QJsonObject json){
    QList<Term*>* termList = storage.retrieveAllTerms();
    QJsonArray resultArray;
    foreach (Term *term, *termList){
        QJsonObject json;
        term->write(json);
        resultArray.append(json);
        qDebug() << json;
    }
    qDeleteAll(termList->begin(), termList->end());
    delete termList;
    QJsonObject r;
    r["terms:"] = resultArray;
    this->sendCommand(r);
}

void ServerListenerControl::retrieveContent(QJsonObject json){
    Student stu;
    stu.read(json["Student"].toObject());
    Term term;
    term.read(json["Term"].toObject());
    QList<Course*>* courseList = storage.retrieveContent(&stu, &term);
    QJsonArray courseArray;
    foreach (Course *crs, *courseList){
        QJsonObject json;
        crs->write(json);
        courseArray.append(json);
        qDebug() << json;
    }
    qDeleteAll(courseList->begin(), courseList->end());
    delete courseList;
    QJsonObject r;
    r["courses:"] = courseArray;
    this->sendCommand(r);
}


#include "ServerListenerControl.h"

//Constructor connects new connection with incoming connection
ServerListenerControl::ServerListenerControl(QObject *parent):
    QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), SLOT (incomingConnection()));
}

void    ServerListenerControl::startServer(){
    int port = 60000;
    //IP Address for communicating between clients in the VMs in this lab : 10.0.2.15
    const QString & testaddress = "0.0.0.0";
    //const QString & testaddress = "10.0.2.15";
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
   else if (cmd == "retrieveShoppingCart()"){
       retrieveShoppingCart(jsonDoc.object());
   }
   else if (cmd == "updateShoppingCart()"){
       updateShoppingCart(jsonDoc.object());
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

//Gets the student and term arguments converted from json
//Uses the server storage class to retrieve the content ordered by
//The student's registered courses for a given term
//Sends back the information to client using sendCommand()
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

//Calls the ListenerControl's storage class to retrieve the shopping cart
//With the passed in student argument converted from json
//Writes the resultshopping cart to json to send back to the client
void ServerListenerControl::retrieveShoppingCart(QJsonObject json){
    Student stu;
    stu.read(json["student"].toObject());
    ShoppingCart* resultShoppingCart = storage.retrieveShoppingCart(&stu);
    QJsonObject cartObject;
    resultShoppingCart->write(cartObject);
    QJsonObject r;
    r["shoppingcart"] = cartObject;
    this->sendCommand(r);
}

//Calls the ListenerControl's storage class to update the shopping cart
//With the passed in json arguments
//Returns back to client a sucess flag
void ServerListenerControl::updateShoppingCart(QJsonObject json){
    Student stu;
    PurchasableItem* item;
    qint32 quantity;
    stu.read(json["student"].toObject());
    quantity = json["quantity"].toDouble();
    qDebug() << json;
    QJsonObject itemObject = json["purchasableItem"].toObject();
    if(itemObject.contains("isbn")){
        Textbook* newTextbook = new Textbook();
        newTextbook->read(itemObject);
        qDebug() << itemObject;
        bool success = storage.updateShoppingCart(&stu, newTextbook, quantity);
        QJsonObject r;
        r["success"] = success;
        this->sendCommand(r);
    }
    else if(itemObject.contains("chapterNumber")){
        Chapter* newChapter = new Chapter();
        newChapter->read(itemObject);
        bool success = storage.updateShoppingCart(&stu, newChapter, quantity);
        QJsonObject r;
        r["success"] = success;
        this->sendCommand(r);
    }
    else if(itemObject.contains("sectionNumber")){
        Section* newSection = new Section();
        newSection->read(itemObject);
        bool success = storage.updateShoppingCart(&stu,newSection, quantity);
        QJsonObject r;
        r["success"] = success;
        this->sendCommand(r);
    }
}




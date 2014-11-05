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
//Starts a tcp listen server on a configurable ip and port.
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

   //Data for testing purposes
   ShoppingCart emptyShoppingCart;
   ShoppingCart cartWithItems;
   Textbook* textbooktest1 = new Textbook("C++ Software Engineering", "Ted","1st ed",
                                          "APublisher","978-3-16-148410-0", "A description", 456, 100.00, true);
   Chapter*  chaptertest1 = new Chapter("Polymorphism", 1, 821, 10, true);
   Section*  sectiontest1 = new Section("How to polymorphic", 1, 822, 2.50, true);
   chaptertest1->addSection(sectiontest1);
   textbooktest1->addChapter(chaptertest1);
   cartWithItems.addItem((PurchasableItem*)textbooktest1);
   cartWithItems.addItem((PurchasableItem*)chaptertest1);
   cartWithItems.addItem((PurchasableItem*)sectiontest1);
   Textbook* textbooktest2 = new Textbook("A++ Software", "Alex Baldwin", "2nd ed", "McGraw", "987-9-92-149210-2", "A++ software programming", 890, 130.00, true);
   Chapter*  chaptertest2 = new Chapter("Programming in A++", 1, 102, 15.00, true);
   Section*  sectiontest2 = new Section("Basics of programming", 1, 500, 5.00, false);
   chaptertest2->addSection(sectiontest2);
   textbooktest2->addChapter(chaptertest2);
   cartWithItems.addItem((PurchasableItem*)textbooktest2);

   testStudentShoppingCart.insert("100848920",emptyShoppingCart);
   testStudentShoppingCart.insert("100859320",cartWithItems);

}

//Slot function that is invoked when the newConnection() signal is recieved. Gets the next pending connection
//and prepares to read bytes from the socket.
void CutpsServer::incomingConnection() {
    qDebug() << "a new connection is available";
    tcpConnection = CutpsServer::nextPendingConnection();
    connect(tcpConnection, SIGNAL(readyRead()), this, SLOT(readBytes()));
    connect(tcpConnection, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

//invoked automatically when bytes are available to be read from the socket. Determines the type
//of command to be processed and acts accordingly.
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
   }
   else if(cmd == "viewShoppingCart()"){
       APIControl *apic = new APIControl();
       QJsonObject result = apic->viewShoppingCart(jsonDoc.object(), testStudentShoppingCart);
       delete apic;
       this->sendJson(result);
   }
   else if (cmd == "getExistingBillingInfo()") {
       qDebug() << "processing command to get billing info..." << "\n";
       APIControl *apic = new APIControl();
       QJsonObject result = apic->getExistingPaymentInfo(jsonDoc.object());
      // qDebug() << result;
       delete apic;

       this->sendJson(result);
      // delete doc;
   }
   else if (cmd == "saveExistingPaymentInfo()") {
       qDebug() << "processing command to save billing info..." << "\n";
       APIControl *apic = new APIControl();
       QJsonObject result = apic->savePaymentInfo(jsonDoc.object());
       delete apic;

       this->sendJson(result);
   }
   else if (cmd == "createCourse()") {
       qDebug() << "processing command to create course..." << "\n";
       APIControl *apic = new APIControl();
       QJsonObject result = apic->createCourse(jsonDoc.object());
       delete apic;
       this->sendJson(result);
   }

   else if (cmd == "createTextbook()") {
       qDebug() << "processing command to create textbook..." << "\n";
       APIControl *apic = new APIControl();
       QJsonObject result = apic->createTextbook(jsonDoc.object());
       delete apic;
       this->sendJson(result);
   }

   else if (cmd == "cManagerViewCourses()") {
       qDebug() << "processing command to retrieve content manager list of courses..." << "\n";
       APIControl *apic = new APIControl();
       QJsonObject result = apic->cManagerViewCourses(jsonDoc.object());
       delete apic;
       this->sendJson(result);

   }
   else if (cmd == "cManagerViewTextbooks()") {
       qDebug() << "processing command to retries content manager list of textbook..." << "\n";
       APIControl *apic = new APIControl();
       QJsonObject result = apic->cManagerViewTextbooks(jsonDoc.object());
       delete apic;
       this->sendJson(result);
   }

} //readbytes

//writes a json object to the tcp socket
void CutpsServer::sendJson(QJsonObject &json) {
        QJsonDocument jdoc = QJsonDocument(json);
        bytes = this->tcpConnection->write(jdoc.toJson());
}


void CutpsServer::disconnected(){
    qDebug() << "peer disconected. \n";
}

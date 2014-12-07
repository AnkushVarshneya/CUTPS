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
   else if (cmd == "checkout()"){
       checkout(jsonDoc.object());
   }
   else if (cmd == "emptyShoppingCart()"){
       emptyShoppingCart(jsonDoc.object());
   }
   else if (cmd == "updatePaymentInformation()"){
       updatePaymentInformation(jsonDoc.object());
   }
   else if (cmd == "retrievePaymentInformation()"){
       retrievePaymentInformation(jsonDoc.object());
   }
   else if (cmd == "retrieveAllContent()"){
       retrieveAllContent();
   }
   else if (cmd == "updateContent()"){
       updateContent(jsonDoc.object());
   }
   else if (cmd == "deleteContent()"){
       deleteContent(jsonDoc.object());
   }
   else if (cmd == "retrieveCourseList()"){
       retrieveCourseList(jsonDoc.object());
   }
   else if (cmd == "retrieveAllTextbooks()"){
       retrieveAllTextbooks(jsonDoc.object());
   }
   else if (cmd == "updateCourse()"){
       updateCourse(jsonDoc.object());
   }
   else if (cmd == "deleteCourse()"){
       deleteCourse(jsonDoc.object());
   }
   else if (cmd == "updateCourseStudentLink()"){
       updateCourseStudentLink(jsonDoc.object());
   }
   else if (cmd == "updateCourseTextbookLink()"){
       updateCourseTextbookLink(jsonDoc.object());
   }

}

//writes a json object to the tcp socket
void ServerListenerControl::sendCommand(QJsonObject &json) {
        QJsonDocument jdoc = QJsonDocument(json);

        bytes = this->tcpConnection->write(jdoc.toJson());
        qDebug() << jdoc;
}

void ServerListenerControl::disconnected(){
    qDebug() << "peer disconected. \n";
}

//API call to retrieve all terms in the database, sends back an array of terms
//To the client
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
        sendSuccess(success);
    }
    else if(itemObject.contains("chapterNumber")){
        Chapter* newChapter = new Chapter();
        newChapter->read(itemObject);
        bool success = storage.updateShoppingCart(&stu, newChapter, quantity);
        sendSuccess(success);
    }
    else if(itemObject.contains("sectionNumber")){
        Section* newSection = new Section();
        newSection->read(itemObject);
        bool success = storage.updateShoppingCart(&stu,newSection, quantity);
        sendSuccess(success);
    }
}

//Handles API call to checkout the student's shopping cart
//Deserializes the json argument, making a student and shopping cart
//And passes along this argument to the storagecontrol, which returns a boolean
//Flag for success, sends this flag back to client
void ServerListenerControl::checkout(QJsonObject json){
    Student checkoutStu;
    checkoutStu.read(json["student"].toObject());

    ShoppingCart checkoutCart;
    checkoutCart.read(json["cart"].toObject());

    bool success = storage.updateOrderContents(&checkoutStu,&checkoutCart);
    sendSuccess(success);

}

//Handles API call to empty the student's shopping cart
//Returns a success flag to the client
void ServerListenerControl::emptyShoppingCart(QJsonObject json){
    Student stu;
    stu.read(json["student"].toObject());
    bool success = storage.emptyShoppingCart(&stu);
    sendSuccess(success);
}

//Handles API call to update the student's payment information
//Returns a success flag to the client
void ServerListenerControl::updatePaymentInformation(QJsonObject json){
    Student stu;
    stu.read(json["student"].toObject());
    PaymentInformation updatePayInfo;
    updatePayInfo.read(json["payInfo"].toObject());
    bool success = storage.updatePaymentInformation(&stu, &updatePayInfo);
    sendSuccess(success);
}

//Handles API call to retrieve the student's payment information
void ServerListenerControl::retrievePaymentInformation(QJsonObject json){
    Student stu;
    stu.read(json["student"].toObject());

    PaymentInformation* payInfo = storage.retrievePaymentInformation(&stu);
    QJsonObject payInfoObject;
    if(payInfo != 0){
        payInfo->write(payInfoObject);
    }
    QJsonObject r;
    r["payInfo"] = payInfoObject;
    this->sendCommand(r);
}

//Handles API call to retrieve All the purchasable content in the database in the form of
//A  list of textbooks, which has a list of chapters, and each chapter containing a list of chapter sections
void ServerListenerControl::retrieveAllContent(){
    QList<Textbook*>* result = storage.retrieveAllContent();
    QJsonArray contentArray;
    foreach (Textbook* text, *result){
        QJsonObject textObject;
        text->write(textObject);
        contentArray.append(textObject);
    }
    QJsonObject r;
    qDeleteAll(result->begin(), result->end());
    delete result;
    r["allContent"] = contentArray;
    this->sendCommand(r);
}


//Handles API call to update the content with the passed in textbook by making the ServerStorageControl
//Gets the boolean result back (whether it was successful or not) and sends this success flag back to the client to work with
void ServerListenerControl::updateContent(QJsonObject json){

    Textbook text;

    text.read(json["textbook"].toObject());

    bool result = storage.updateContent(&text);

    sendSuccess(result);
}

//Handles API call to delete some PurchasableItem. First determines what kind of purchasable item it is
//(As purchasableItem is abstract and doesn't have a fully defined json read)
//And then passes along the pointer to the storage control to delete the content
//Passes back a boolean flag if the operation was succesful or not
void ServerListenerControl::deleteContent(QJsonObject json){

    QJsonObject itemObject = json["purchasableItem"].toObject();
    if(itemObject.contains("isbn")){
        Textbook* newTextbook = new Textbook();
        newTextbook->read(itemObject);

        bool success = storage.deleteContent(newTextbook);
        sendSuccess(success);
    }
    else if(itemObject.contains("chapterNumber")){
        Chapter* newChapter = new Chapter();
        newChapter->read(itemObject);
        bool success = storage.deleteContent(newChapter);
        sendSuccess(success);
    }
    else if(itemObject.contains("sectionNumber")){
        Section* newSection = new Section();
        newSection->read(itemObject);
        bool success = storage.deleteContent(newSection);
        sendSuccess(success);
    }
    else{
        sendSuccess(false);
    }

}

//Handles API call by the course manager client to retrieve the courses list
//For a given term argument, returns back to client a list of courses as a json object
void ServerListenerControl::retrieveCourseList(QJsonObject json){
    Term selectedTerm;
    selectedTerm.read(json["term"].toObject());
    QList<Course*>* resultList = storage.retrieveCourseList(selectedTerm.getTermID());
    QJsonArray courseArray;
    foreach (Course *crs, *resultList){
        QJsonObject json;
        crs->write(json);
        courseArray.append(json);
    }
    QJsonObject result;
    result["courses:"] = courseArray;
    this->sendCommand(result);
}

//Handles API call to retrieve all of the textbooks only (no chapters/sections)
//For the Course Manager subsystem to link textbooks to courses to
void ServerListenerControl::retrieveAllTextbooks(QJsonObject json){
    QList<Textbook*>* result = storage.retrieveAllTextbook();
    QJsonArray textbookArray;
    foreach(Textbook *text, *result){
        QJsonObject json;
        text->write(json);
        textbookArray.append(json);
    }
    QJsonObject r;
    r["textbooks:"] = textbookArray;
    this->sendCommand(r);
}

//Handles API call to update the given course for a given term
//Sends the success flag determining if the update worked or not
//Is sent back to client
void ServerListenerControl::updateCourse(QJsonObject json){
    Course updateCrs;
    updateCrs.read(json["course"].toObject());
    Term term;
    term.read(json["term"].toObject());
    bool success = storage.updateCourse(&updateCrs, term.getTermID());
    sendSuccess(success);
}

//Handles API call to delete the given course for a given term
void ServerListenerControl::deleteCourse(QJsonObject json){
    Course deleteCrs;
    deleteCrs.read(json["course"].toObject());
    Term term;
    term.read(json["term"].toObject());

    bool success = storage.deleteCourse(&deleteCrs,term.getTermID());
    sendSuccess(success);
}

//Handles API call to update the assignment of students to a course
//For a given term
void ServerListenerControl::updateCourseStudentLink(QJsonObject json){
    Course assignedCrs;
    assignedCrs.read(json["course"].toObject());

    Student assignedStu;
    assignedStu.read(json["student"].toObject());

    Term inTerm;
    inTerm.read(json["term"].toObject());

    bool success = storage.updateCourseStudentLink(&assignedCrs, inTerm.getTermID(), &assignedStu);
    sendSuccess(success);
}

//Handles API call to assign a textbook to a course for a given term
//Returns back to client a boolean flag to indicate success
void ServerListenerControl::updateCourseTextbookLink(QJsonObject json){
    Course assignedCrs;
    assignedCrs.read(json["course"].toObject());

    Term inTerm;
    inTerm.read(json["term"].toObject());

    Textbook assignedText;
    assignedText.read(json["textbook"].toObject());

    bool success = storage.updateCourseTextbookLink(&assignedCrs,inTerm.getTermID(), &assignedText);
    sendSuccess(success);
}



//General success flag message to send back to the client
//Takes in boolean input, puts that as part of the success field of the
//Json object, and then sends that json object over to the client
void ServerListenerControl::sendSuccess(bool success){
    QJsonObject r;
    r["success"] = success;
    this->sendCommand(r);
}


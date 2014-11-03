

#include "mainwindow.h"
#include "connectionmanager.h"
#include "CUtpsDataObject.h"
#include "BillingAddress.h"
#include "Textbook.h"
#include "Chapter.h"
#include "Section.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <iostream>

using namespace std;

//Function prototypes TODO get rid of these once we move these function calls to the APIControl;
QList<Course*>& studentViewTextbooks(QString stuNum, Term *term, ConnectionManager *conMan);
QList<PurchasableItem*>& viewShoppingCart(QString stuNum, ConnectionManager *conMan);
bool addContent(QString stuNum, qint32 itemID, qint32 quantity, ConnectionManager *conMan);
bool emptyShoppingCart(QString stuNum, ConnectionManager *conMan);
bool getExistingPaymentInfo(QString stuNum, ConnectionManager *conMan);
bool savePaymentInfo(QString stuNum, PaymentInformation payInfo, ConnectionManager *conMan);
bool createTextbook(Textbook *aTextbook, ConnectionManager *conMan);
bool createCourse(Course *aCourse, ConnectionManager *conMan);
bool cManagerViewTextbooks(Term *aTerm, ConnectionManager *conMan);
bool cManagerViewCourses(Term *aTerm, ConnectionManager *conMan);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    const QString & testaddress = "0.0.0.0";
    const int port = 1234;
    QHostAddress address = QHostAddress(testaddress);
    w.show();
    ConnectionManager *conMan = new ConnectionManager(&w);


    conMan->connectToHost(address, port);
   // conMan->testSend(adr);
/*
    //test send and parse of chapter w/ nested sections
    Textbook*   textbook    = new Textbook("what goes here?", "two", "three", "four", "five", "six");
        Chapter*    chapter1    = new Chapter("Ryan Lays down the Law", 1);
        Chapter*    chapter2    = new Chapter("Robert Nguyen's Greatest Hits", 2);
        Chapter*    chapter3    = new Chapter("Ankush's Drug Dealing Ways", 3);
        //Section*    section    = new Section();
        textbook->addChapter(chapter1);
        textbook->addChapter(chapter2);
        textbook->addChapter(chapter3);

        Section*    c1sect1    = new Section("Legalese 101", 1);
        Section*    c1sect2    = new Section("Ryan's Roadsters", 2);
        Section*    c2sect1    = new Section("Chair Wars Episode XVI", 1);
        chapter1->addSection(c1sect1);
        chapter1->addSection(c1sect2);
        chapter3->addSection(c2sect1);

    //conMan->testSend(chapter1);
    //conMan->testSend ((CUtpsDataObject*)textbook);

   //test student
    Student *student = new Student();
    Course *crs = new Course();
    student->addCourse(crs);
//    qDebug() << student->getRegisteredCourses().length();
//    qDebug() << student->getRegisteredCourses().at(0)->getInstructor();

    QJsonObject stu;
    student->write(stu);
    QJsonDocument jdoc = QJsonDocument(stu);
    qDebug() << jdoc.toJson();
    conMan->testSend( (CUtpsDataObject*)student );
*/

    Student aStu;
    Term fall2014;
    Course *c1 = new Course("COMP3004","A","Christine Laurendeau");
    Course *c2 = new Course("COMP3804", "A", "Amin Gheibi");
    Course *c3 = new Course("COMP3005", "A", "Louis Nel");
    Course *c4 = new Course("BIOC3101", "A", "William Willmore");
    Course *c5 = new Course("COMP3803", "A", "John Oommen");
    c1->setTerm(fall2014);
    c2->setTerm(fall2014);
    c3->setTerm(fall2014);
    c4->setTerm(fall2014);

    //Adding courses
    aStu.addCourse(c1);
    aStu.addCourse(c2);
    aStu.addCourse(c3);
    aStu.addCourse(c4);
    aStu.addCourse(c5);
    studentViewTextbooks("100848920", &fall2014, conMan);
    viewShoppingCart("100848920", conMan);

    addContent("100848920", 19138, 5, conMan);
    emptyShoppingCart("100848920", conMan);
    getExistingPaymentInfo("100848920",conMan);
    savePaymentInfo("100848920",PaymentInformation(),conMan);
    Textbook *newTextbook = new Textbook();
    createTextbook(newTextbook, conMan);
    Course *newCourse = new Course();
    createCourse(newCourse, conMan);
    cManagerViewTextbooks(&fall2014, conMan);
    cManagerViewCourses(&fall2014, conMan);
    return a.exec();
}

//API call studentViewTextbooks where a student number and a term are arguments
//To send over to the server in which the server will query the database
//For the necessary textbooks required for the registered courses
//Traceability: SD-01 (sequence diagram 1)
QList<Course*>& studentViewTextbooks(QString stuNum, Term *term, ConnectionManager *conMan){

    QJsonObject api_server_call;
    //Set API call to initiate on serverside
    QString functionCall = "studentViewTextbooks()";
    api_server_call["Function:"] = functionCall;

    //Write the student number argument into the api_server_call object
    api_server_call["Student Number"] = stuNum;

    //Write the term argument into the api_server_call object
    QJsonObject termObject;
    term->write(termObject);
    api_server_call["Term"] = termObject;

    conMan->send(api_server_call);

    //Placeholder to when we read back from the server to get the list of textbooks
    QList<Course*> temp;
    return temp;

}

//API call to view a student's shopping cart
//This function makes a QJsonObject to send over to the server
//Which includes the API function call to execute server-side
//And what student is relevant (given student number)
//Returns a list of purchasable items
QList<PurchasableItem*>& viewShoppingCart(QString stuNum, ConnectionManager *conMan){
    QJsonObject api_server_call;
    QString functionCall = "viewShoppingCart()";
    api_server_call["Function:"] = functionCall;
    api_server_call["Student Number"] = stuNum;
    conMan->send(api_server_call);
    QList<PurchasableItem*> temp;
    return temp;
}

//API call to add some content to the student's shopping cart
//This function makes a QJsonObject to send over to the server
//Which includes the function name and the arguments to be passed
bool addContent(QString stuNum, qint32 itemID, qint32 quantity, ConnectionManager *conMan){
    QJsonObject api_server_call;
    QString functionCall = "addContent()";
    api_server_call["Function:"] = functionCall;
    api_server_call["Student Number"] = stuNum;
    api_server_call["Item ID"] = itemID;
    api_server_call["Quantity"] = quantity;
    conMan->send(api_server_call);
    return true;
}

//Empty the student's shopping cart, given the student's student number
bool emptyShoppingCart(QString stuNum, ConnectionManager *conMan){
    QJsonObject api_server_call;
    QString functionCall = "emptyShoppingCart()";
    api_server_call["Function:"] = functionCall;
    api_server_call["Student Number"] = stuNum;
    conMan->send(api_server_call);
    return true;
}

//Get the existing payment info for a given student
bool getExistingPaymentInfo(QString stuNum, ConnectionManager *conMan){
    QJsonObject api_server_call;
    QString functionCall = "getExistingBillingInfo()";
    api_server_call["Function:"] = functionCall;
    api_server_call["Student Number"] = stuNum;
    conMan->send(api_server_call);
    return true;
}

//Save the payment info for a student
bool savePaymentInfo(QString stuNum, PaymentInformation payInfo, ConnectionManager *conMan){
    QJsonObject api_server_call;
    QString functionCall = "saveExistingPaymentInfo()";
    api_server_call["Function:"] = functionCall;
    api_server_call["Student Number"] = stuNum;
    QJsonObject payInfoObject;
    payInfo.write(payInfoObject);
    api_server_call["Payment Info"] = payInfoObject;
    conMan->send(api_server_call);
    return true;

}

//Create a textbook
bool createTextbook(Textbook *aTextbook, ConnectionManager *conMan){
    QJsonObject api_server_call;
    QString functionCall = "createTextbook()";
    api_server_call["Function:"] = functionCall;
    QJsonObject textbookObject;
    aTextbook->write(textbookObject);
    api_server_call["Textbook"] = textbookObject;
    conMan->send(api_server_call);

    return true;
}

//Create a course
bool createCourse(Course *aCourse, ConnectionManager *conMan){
    QJsonObject api_server_call;
    QString functionCall = "createCourse()";
    api_server_call["Function:"] = functionCall;
    QJsonObject courseObject;
    aCourse->write(courseObject);
    api_server_call["Course"] = courseObject;
    conMan->send(api_server_call);
    return true;
}

//Content Manager View textbooks
bool cManagerViewTextbooks(Term *aTerm, ConnectionManager *conMan){
    QJsonObject api_server_call;
    QString functionCall = "cManagerViewTextbooks()";
    api_server_call["Function:"] = functionCall;
    QJsonObject termObject;
    aTerm->write(termObject);
    api_server_call["Term"] = termObject;
    conMan->send(api_server_call);
    return true;
}

//Content Manager View Courses
bool cManagerViewCourses(Term *aTerm, ConnectionManager *conMan){
    QJsonObject api_server_call;
    QString functionCall = "cManagerViewCourses()";
    api_server_call["Function:"] = functionCall;
    QJsonObject termObject;
    aTerm->write(termObject);
    api_server_call["Term"] = termObject;
    conMan->send(api_server_call);
    return true;
}

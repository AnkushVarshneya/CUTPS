

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
QList<Textbook*>& studentViewTextbooks(Student *stu, Term *term, ConnectionManager *conMan);

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
    studentViewTextbooks(&aStu, &fall2014, conMan);
    return a.exec();
}

//API call studentViewTextbooks where a student and a term are arguments
//To send over to the server in which the server will query the database
//For the necessary textbooks
//Traceability: SD-01 (sequence diagram 1)
QList<Textbook*>& studentViewTextbooks(Student *stu, Term *term, ConnectionManager *conMan){

    QJsonObject api_server_call;
    //Set API call to initiate on serverside
    QString functionCall = "studentViewTextbooks()";
    api_server_call["Function:"] = functionCall;

    //Write the student argument into the api_server_call object
    QJsonObject stuObject;
    stu->write(stuObject);
    api_server_call["Student"] = stuObject;

    //Write the term argument into the api_server_call object
    QJsonObject termObject;
    term->write(termObject);
    api_server_call["Term"] = termObject;

    conMan->send(api_server_call);

    //Placeholder to when we read back from the server to get the list of textbooks
    QList<Textbook*> temp;
    return temp;

}



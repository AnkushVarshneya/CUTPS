
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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    const QString & testaddress = "0.0.0.0";
    const int port = 1234;
    QHostAddress address = QHostAddress(testaddress);
    w.show();
    ConnectionManager *conMan = new ConnectionManager(&w);
    BillingAddress *adr = new BillingAddress("new student",251,"test street","toronto","ontario", "k3g6d3");


    qDebug() << adr->getName();
    qDebug() << adr->getCity();
    conMan->connectToHost(address, port);
   // conMan->testSend(adr);

    //test send and parse of chapter w/ nested sections
        Textbook*   textbook    = new Textbook();
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
    conMan->testSend(textbook);

    return a.exec();
}





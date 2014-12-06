#include "QueryControl.h"
#include "ServerStorageControl.h"
#include "ServerListenerControl.h"
#include <QApplication>
#include <QDebug>
#include <string>
using namespace std;
int main(int argc, char *argv[])
{
    QueryControl w;

    //Test queries
    w.test();
    /*    ServerStorageControl s;

    qDebug() << "starting tests" ;
    //--------------Testing retrieveContent()---------
    Student* student = w.retrieveStudent("100853074");

    QJsonObject json;
    student->write(json);
    qDebug() << " Student exists";
    qDebug() << json;
    QList<Term*>* termlist= w.retrieveTermList();
    Term *term = termlist->at(0);
    QList<Course*>* contentList = s.retrieveContent(student, term);
    qDebug() << "\nTEST NORMAL CASE\n";
    foreach(Course *crs, *contentList){
        QJsonObject json = QJsonObject();
        crs->write(json);
        qDebug() <<json;
    }
    qDebug() << "\nWith null student or term\n";
    QList<Course*>* nullList = s.retrieveContent(NULL, NULL);
    foreach(Course *crs, *nullList){
        QJsonObject json = QJsonObject();
        crs->write(json);
        qDebug() <<json;
    }
    */

    //-------------Testing updateShoppingCart() and retrieveShoppingCart() functions----
    /*
    foreach (Course* crs, *contentList){
        QList<Textbook*> textbookContent = crs->getRequiredTextbooks();
        //Adding a random number of textbooks to shopping cart for each textbook in the course
        foreach(Textbook* text, textbookContent){
            qint32 i = qrand() % 50 + 1;
            s.updateShoppingCart(student,(PurchasableItem*)text,i);
        }
    }
    */
    /*
    ShoppingCart* testShoppingCart = s.retrieveShoppingCart(student);
    qDebug() << testShoppingCart->getItems().empty();
    for(int i = 0; i < testShoppingCart->getItems().size() ; i++){
        QJsonObject json;
        testShoppingCart->getItems()[i].first->write(json);
        QString str;
        str.append(QString("%1").arg(testShoppingCart->getItems()[i].second));
        qDebug() << json;
        qDebug() << " Quantity: " + str;
    }
    */



    /*
    qDeleteAll(contentList->begin(),contentList->end());
    delete contentList;
    qDeleteAll(nullList->begin(), nullList->end());
    delete nullList;
    qDeleteAll(termlist->begin(),termlist->end());
    delete termlist;
    delete student;

    //----------------------------------------------//

    //------ Testing server ---------------//
    ServerListenerControl testServer;
    testServer.startServer();
    */
    QCoreApplication a(argc, argv);
    ServerListenerControl testServ;
    testServ.startServer();
    return a.exec();

}

#include "mainwindow.h"
#include <QApplication>

/*
#include "ContentInputOutputManager.h"
#include "EditTextbookFormWindow.h"
*/
#include "ClientCommunicatorManagementControl.h"
#include <QList>
#include "MainInputOutputManager.h"
#include "ShopUpdateControl.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    MainWindow w;
    w.show();
*/

    //ContentInputOutputManager b;

    MainInputOutputManager mainIOManager;

    //Testing for client
    ShopUpdateControl test;
    QList<Term*>* terms = test.retrieveAllTerms();
    foreach(Term *trm, *terms){
        QJsonObject json;
        trm->write(json);
        qDebug() <<json;
    }

    //Testing for retrieving content
    Student testStu;
    testStu.setStudentNum("100853074");

//    QList<Course*>* courses = test.retrieveContent(&testStu,(*terms)[0]);
//    foreach(Course *crs, *courses){
//        QJsonObject json;
//        crs->write(json);
//        qDebug() <<json;
//    }

    QList<Course*>* courses = test.retrieveContent(&testStu,(*terms)[0]);
    foreach(Course *crs, *courses){
        QJsonObject json;
        crs->write(json);
        qDebug() <<json;
    }

    qDebug() << "Testing for adding stuff to shopping cart and retrieving the shopping cart";

    foreach (Course* crs, *courses){
        QList<Textbook*> textbookContent = crs->getRequiredTextbooks();
        //Adding  1 textbooks to shopping cart for each textbook in the course
        foreach(Textbook* text, textbookContent){
            qint32 i = 1;
            test.updateShoppingCart(&testStu,(PurchasableItem*)text,i);
            //Adding 1 chapter for each chapter in the textbooks
            foreach(Chapter* chap, text->getChapterList()){
                test.updateShoppingCart(&testStu,(PurchasableItem*)chap,i);
                foreach(Section* sec, chap->getChapterSections()){
                    test.updateShoppingCart(&testStu,(PurchasableItem*)sec,i);
                }
            }
        }
    }

    ShoppingCart* testShoppingCart = test.retrieveShoppingCart(&testStu);
    for(int i = 0; i < testShoppingCart->getItems().size() ; i++){
        QJsonObject json;
        testShoppingCart->getItems()[i].first->write(json);
        QString str;
        str.append(QString("%1").arg(testShoppingCart->getItems()[i].second));
        qDebug() << json;
        qDebug() << " Quantity: " + str;
    }

    qDebug() << "Testing for retrieving all content";
    ContentManagementUpdateControl cmTest;

    QList<Textbook*>* testResult = cmTest.retrieveAllContent();

    foreach(Textbook* text, *testResult){
        QJsonObject json;
        text->write(json);

        qDebug() << json;
    }

    return a.exec();

}

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
    qDebug() << "Testing for Retrieving All terms";
    QList<Term*>* terms = test.retrieveAllTerms();
    foreach(Term *trm, *terms){
        QJsonObject json;
        trm->write(json);
        qDebug() <<json;
    }
    qDebug() << "End Test For Retrieving all terms";
    //Testing for retrieving content
    Student testStu;
    testStu.setStudentNum("100853074");
    qDebug() << "Test for Retrieving all content for student";

    QList<Course*>* courses = test.retrieveContent(&testStu,(*terms)[0]);
    foreach(Course *crs, *courses){
        QJsonObject json;
        crs->write(json);
        qDebug() <<json;
    }
    qDebug() << "End Test for retrieving all content for student";
    qDebug() << "Testing for adding stuff to shopping cart and retrieving the shopping cart";

    foreach (Course* crs, *courses){
        QList<Textbook*> textbookContent = crs->getRequiredTextbooks();
        //Adding  1 textbooks to shopping cart for each textbook in the course
        foreach(Textbook* text, textbookContent){
            qint32 i = 1;
            qDebug() << test.updateShoppingCart(&testStu,(PurchasableItem*)text,i);
            //Adding 1 chapter for each chapter in the textbooks
            foreach(Chapter* chap, text->getChapterList()){
             qDebug() << test.updateShoppingCart(&testStu,(PurchasableItem*)chap,i);
                foreach(Section* sec, chap->getChapterSections()){
                  qDebug() << test.updateShoppingCart(&testStu,(PurchasableItem*)sec,i);
                }
            }
        }
    }
    qDebug() << "End testing for adding stuff to shopping cart and retrieivng the shopping cart";
    ShoppingCart* testShoppingCart = test.retrieveShoppingCart(&testStu);
    qDebug() << "Test for retrieving shopping cart";
    for(int i = 0; i < testShoppingCart->getItems().size() ; i++){
        QJsonObject json;
        testShoppingCart->getItems()[i].first->write(json);
        QString str;
        str.append(QString("%1").arg(testShoppingCart->getItems()[i].second));
        qDebug() << json;
        qDebug() << " Quantity: " + str;
    }
    qDebug() << "End Test for retrieving shopping cart";
    qDebug() << "Testing for retrieving all content";
    ContentManagementUpdateControl cmTest;

    QList<Textbook*>* testResult = cmTest.retrieveAllContent();

    foreach(Textbook* text, *testResult){
        QJsonObject json;
        text->write(json);

        qDebug() << json;
    }
    qDebug() << "End Testing for retrieving all content";

    qDebug() << "Testing for updateContent()";

    Textbook* newTextbook = new Textbook("A Study in Scarlet", "Sherlock Holmes" , "1st ed", "Penguin", "987-0-15-298102-1", "Mystery", 456, 99.99, true);
    bool result = cmTest.updateContent(newTextbook);
    qDebug() << result;
    qDebug() << "End Testing for updateContent()";


    qDebug() << "Testing for deleteContent()";
    result = cmTest.deleteContent(newTextbook);
    qDebug() << result;

    qDebug() << "End testing for deleteContent()";
    return a.exec();

}

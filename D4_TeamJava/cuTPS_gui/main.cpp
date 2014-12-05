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
    return a.exec();

}

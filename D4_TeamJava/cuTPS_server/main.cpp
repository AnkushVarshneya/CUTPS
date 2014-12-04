#include "QueryControl.h"
#include "ServerStorageControl.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QueryControl w;
    ServerStorageControl s;

    //--------------Testing retrieveContent()---------
    Student* student = w.retrieveStudent("100853074");
    QList<Term*>* termlist= w.retrieveTermList();
    Term *term = termlist->at(0);
    QList<Course*>* contentList = s.retrieveContent(student, term);
    qDebug() << "TEST NORMAL CASE";
    foreach(Course *crs, *contentList){
        QJsonObject json = QJsonObject();
        crs->write(json);
        qDebug() <<json;
    }
    qDebug() << "With null student or term";
    QList<Course*>* nullList = s.retrieveContent(NULL, NULL);
    foreach(Course *crs, *nullList){
        QJsonObject json = QJsonObject();
        crs->write(json);
        qDebug() <<json;
    }

    qDeleteAll(contentList->begin(),contentList->end());
    qDeleteAll(nullList->begin(), nullList->end());
    //----------------------------------------------//

    return 0;
}

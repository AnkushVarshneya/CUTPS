#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("HostName");
    db.setDatabaseName("testDB");
    db.setUserName("rab");
    db.setPassword("test");
    db.open();
    db.transaction();
    QSqlQuery query;
    query.exec("INSERT INTO test(x,y,z)"
               "VALUES(10101, 'test', 'test2'");
    query.exec("SELECT * FROM test");
    db.commit();

    //"Hello this is a test lolol"
    return a.exec(); // its changed!!!!!!!!!!


    // more coments!!!!!!!!234 ankush was here

    // this is a change
    // wait what???
    // a change????

}

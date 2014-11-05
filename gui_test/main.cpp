

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

    w.getControl()->setConnectionManager(conMan);


    conMan->connectToHost(address, port);

    return a.exec();
}



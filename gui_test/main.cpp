
#include "mainwindow.h"
#include "connectionmanager.h"
#include "CUtpsDataObject.h"
#include "BillingAddress.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    const QString & testaddress = "0.0.0.0";
    const int port = 1234;
    QHostAddress address = QHostAddress(testaddress);
    w.show();
    ConnectionManager *conMan = new ConnectionManager(&w);
    BillingAddress *adr = new BillingAddress();
    qDebug() << adr->getName();
    qDebug() << adr->getCity();
    conMan->connectToHost(address, port);
    conMan->testSend(adr);
    return a.exec();
}





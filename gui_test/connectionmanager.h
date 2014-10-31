#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QTextStream>
#include "BillingAddress.h"
#include "CUtpsDataObject.h"
#include "Chapter.h"
#include "Textbook.h"
#include "Student.h"

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionManager(QObject *parent = 0);
    void connectToHost(QHostAddress hostAddress, int port);
//    void testSend(BillingAddress *testadr);
//    void testSend(Chapter *chap);
//    void testSend(Textbook *text);
    void testSend(CUtpsDataObject *data);

private:
    QTcpSocket *tcpConnection;
    QDataStream dataStream;
    qint64 bytes;

signals:

public slots:

private slots:
    void readyRead();
//    void createTextbook(Textbook *text);
//    void studentViewTextbooks(Student *student);
//    void viewShoppingCart(Student *student);
};

#endif // CONNECTIONMANAGER_H

/* The Listener Control responsible for listening to client requests
 * Combined class of Serializer and Listener Control as described in the Server Subsystem (SS-06)
 * -delegates functionality of using the RequestManager class to communicate with the database
 *
 * Traceability: SS-06 (Part of Server Subsystem) */

#include "ServerSerializer.h"
#include "ServerStorageControl.h"
#include <QTcpServer>
#include <QTcpSocket>

#ifndef SERVERLISTENERCONTROL_H
#define SERVERLISTENERCONTROL_H

class ServerListenerControl : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerListenerControl(QObject *parent = 0);
    void startServer();
    void sendCommand(QJsonObject &json);
    static ServerListenerControl* getInstance();


private:
    //Student API
    void retrieveAllTerms(QJsonObject);
    void retrieveContent(QJsonObject);
    void retrieveShoppingCart(QJsonObject);
    void updateShoppingCart(QJsonObject);
    void checkout(QJsonObject);
    void emptyShoppingCart(QJsonObject);
    void updatePaymentInformation(QJsonObject);
    void retrievePaymentInformation(QJsonObject);

    //ContentManager API
    void retrieveAllContent();
    void updateContent(QJsonObject);
    void deleteContent(QJsonObject);

    //Course Manager API (Shared by CM and Admin)
    void retrieveCourseList(QJsonObject);
    void retrieveCourseStudents(QJsonObject);
    void retrieveAllStudents();
    void retrieveCourseTextbooks(QJsonObject);
    void retrieveAllTextbooks();
    void updateCourse(QJsonObject);
    void deleteCourse(QJsonObject);
    void updateCourseStudentLink(QJsonObject);
    void updateCourseTextbookLink(QJsonObject);

    void sendSuccess(bool);
    ServerSerializer serializer;
    ServerStorageControl storage;
    static ServerListenerControl* instance;
    QTcpSocket *tcpConnection;
    qint64 bytes;



signals:

public slots:
    void incomingConnection();
    void readBytes();
    void disconnected();
};

#endif // SERVERLISTENERCONTROL_H

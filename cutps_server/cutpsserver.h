#ifndef CUTPSSERVER_H
#define CUTPSSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class CutpsServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CutpsServer(QObject *parent = 0);
    void startServer();
private:
    QTcpSocket *tcpConnection;

signals:

public slots:
    void incomingConnection();
    void readyRead();
    void disconnected(); //recieves signal from tcpConnection
};

#endif // CUTPSSERVER_H

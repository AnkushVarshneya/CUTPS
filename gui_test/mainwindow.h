#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QWidget>

#include "studentform.h"
#include "contentmanagerform.h"

class StudentForm;
class ContentManagerForm;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:

    QStatusBar *statusBar;
    Ui::MainWindow *ui;
    QTcpSocket *tcpConnection;
    QNetworkSession *networkSession;
    void connectTcp();

    StudentForm *studentForm;
    ContentManagerForm *contentManagerForm;


private slots:
    //void displayError(QAbstractSocket::SocketError socketError);
    void readyRead();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QWidget>

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


private slots:
    //void displayError(QAbstractSocket::SocketError socketError);
    void readyRead();
    void on_actionShopping_Cart_has_Items_triggered();
    void on_actionShopping_Cart_is_Empty_triggered();
    void on_actionViewShoppingCart_hasitems_triggered();
    void on_actionViewShoppingCart_noitems_triggered();
    void on_actionStudent_unenrolled_triggered();
    void on_actionStudent_ViewTextbooks_notextbooks_triggered();
    void on_actionStudent_ViewTextbooks_unenrolled_triggered();
    void on_actionStudent_ViewTextbooks_hastextbooks_triggered();
    void on_actionEmptyShoppingCart_hasitems_triggered();
    void on_actionEmptyShoppingCart_noitems_triggered();
    void on_actionStudent_EmptyShoppingCart_hasitems_triggered();
    void on_actionStudent_EmptyShoppingCart_noitems_triggered();
};

#endif // MAINWINDOW_H

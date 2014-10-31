#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    networkSession(0),
    tcpConnection(new QTcpSocket(this)) //does this work
{

    ui->setupUi(this);
   // this->connectTcp();
}

//void MainWindow::connectTcp() {
//   // this->tcpConnection = new QTcpSocket(this);
//    const QString & testaddress = "0.0.0.0";
//    QHostAddress address = QHostAddress(testaddress);
//    this->tcpConnection->connectToHost(address, 1234);
//    this->tcpConnection->write(" testing data write to server. \n");
//    this->tcpConnection->write(" testing further data write to server. \n");

//    connect(this->tcpConnection, SIGNAL(readyRead()), this, SLOT(readyRead()));
//}

void MainWindow::readyRead() {
    qDebug() << "ready to read stuff from server \n";
    qDebug() << "bytes avail: " << this->tcpConnection->bytesAvailable();
    qDebug() << "peer info: " << this->tcpConnection->peerName() << this->tcpConnection->peerAddress() << this->tcpConnection->peerPort() << "\n";
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Student View Shopping Cart

//ShoppingCart contains items
void MainWindow::on_actionViewShoppingCart_hasitems_triggered()
{

}
//ShoppingCart is empty
void MainWindow::on_actionViewShoppingCart_noitems_triggered()
{

}


//Student View Textbooks

//Student has no textbooks
void MainWindow::on_actionStudent_ViewTextbooks_notextbooks_triggered()
{

}
//Student is not enrolled in any Courses
void MainWindow::on_actionStudent_ViewTextbooks_unenrolled_triggered()
{

}
//Student has textbooks
void MainWindow::on_actionStudent_ViewTextbooks_hastextbooks_triggered()
{

}

//Student Empty Shopping Cart

//Shopping cart is already empty
void MainWindow::on_actionStudent_EmptyShoppingCart_noitems_triggered()
{

}

//Shopping cart contains items
void MainWindow::on_actionStudent_EmptyShoppingCart_hasitems_triggered()
{

}



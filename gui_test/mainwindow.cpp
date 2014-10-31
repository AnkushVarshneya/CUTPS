#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    networkSession(0),
    tcpConnection(new QTcpSocket(this)) //does this work
{

    ui->setupUi(this);
    studentForm = new StudentForm();
    contentManagerForm = new ContentManagerForm();
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
    delete studentForm;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    studentForm->parentForm = this;
    studentForm->show();
    this->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    contentManagerForm->parentForm = this;
    contentManagerForm->show();
    this->hide();
}

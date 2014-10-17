#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("../gui_test/testDB");

    if(!mydb.open())
        ui->label->setText("Failed to open the database");
    else
        ui->label->setText("connected....");
}

Login::~Login()
{
    delete ui;
}

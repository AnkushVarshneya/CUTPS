#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../gui_test/testDB");

    if(!db.open())
        ui->label->setText("Failed to open the database");
    else {
        ui->label->setText("connected....");
        QSqlQuery query;
        query.exec("INSERT INTO test(x,y,z) VALUES(10101, 'test', 'test2')");
        //query.exec("SELECT * FROM test");
        db.commit();
    }
}

Login::~Login()
{
    delete ui;
}

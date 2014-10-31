#include "studentform.h"
#include "ui_studentform.h"

StudentForm::StudentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentForm)
{
    ui->setupUi(this);
}

StudentForm::~StudentForm()
{
    delete ui;
}

void StudentForm::on_backButton_clicked()
{
    parentForm->show();
    this->hide();
}

void StudentForm::closeEvent(QCloseEvent *event)
{
//    this->parentForm->show();
//    event->accept();
    exit(0);
}

void StudentForm::on_StudentForm_destroyed(){}

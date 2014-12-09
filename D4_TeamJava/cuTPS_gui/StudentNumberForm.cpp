#include "StudentNumberForm.h"
#include "ui_StudentNumberForm.h"

StudentNumberForm::StudentNumberForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentNumberForm)
{
    ui->setupUi(this);
}

StudentNumberForm::~StudentNumberForm()
{
    delete ui;
}

QPushButton*    StudentNumberForm::getOkButton()            { return ui->okButton; }
QPushButton*    StudentNumberForm::getCancelButton()        { return ui->cancelButton; }
QLineEdit*      StudentNumberForm::getStudentNumberTextBox(){ return ui->studentNumberTextBox; }

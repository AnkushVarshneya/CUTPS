#include "contentmanagerform.h"
#include "ui_contentmanagerform.h"

ContentManagerForm::ContentManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentManagerForm)
{
    ui->setupUi(this);
}

ContentManagerForm::~ContentManagerForm()
{
    delete ui;
}


void ContentManagerForm::on_backButton_clicked()
{
    parentForm->show();
    this->hide();
}

void ContentManagerForm::closeEvent(QCloseEvent *event)
{
//    this->parentForm->show();
//    event->accept();
            exit(0);
}
